#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>

#include <cyan/common/error.h>
#include "cyan/hwcam/hwcam.h"
#include "imqueue.h"

#define BACKOFF_TIME    50

void* loop_fct( void* img ) ;


hwcam_t* hwcam_new( unsigned char* plugin, ... ) {
    hwcam_t* tmp ; 
    va_list args ;
    int ret ;
    hw_mode_t*  modes ;
    int         nb_modes ;
    int         current_mode ;
    
    tmp = (hwcam_t*) malloc( sizeof( hwcam_t ) ) ;
    if ( tmp == NULL ) {
        CYAN_ERROR( ERR_MALLOC ) ;
        return NULL ;
    }

    tmp->cam_handle = NULL ;
    tmp->running = 0 ;

    tmp->init = NULL ;
    tmp->deinit = NULL ;
    tmp->get_available_modes = NULL ;
    tmp->get_serial = NULL ;
    tmp->set_mode = NULL ;
    tmp->start_acqui = NULL ;
    tmp->stop_acqui = NULL ;
    tmp->get_frame = NULL ;
    tmp->dl_handle = NULL ;
    tmp->img_queue = NULL ;

    // Load dynamic library for plugin 
    
    tmp->dl_handle = dlopen( plugin, RTLD_NOW | RTLD_GLOBAL ) ;

    if ( tmp->dl_handle == NULL ) {
        CYAN_ERROR( ERR_PLUGIN ) ;
        return NULL ;
    }

   tmp->init = dlsym( tmp->dl_handle, "init"); 
   tmp->deinit = dlsym( tmp->dl_handle, "deinit"); 
   tmp->get_available_modes = dlsym( tmp->dl_handle, "get_available_modes"); 
   tmp->get_serial = dlsym( tmp->dl_handle, "get_serial"); 
   tmp->set_mode = dlsym( tmp->dl_handle, "set_mode"); 
   tmp->get_mode = dlsym( tmp->dl_handle, "get_mode"); 
   tmp->start_acqui = dlsym( tmp->dl_handle, "start_acqui"); 
   tmp->stop_acqui = dlsym( tmp->dl_handle, "stop_acqui"); 
   tmp->get_frame = dlsym( tmp->dl_handle, "get_frame"); 


    if ( (tmp->init == NULL) ||
            (tmp->get_available_modes == NULL) ||
            (tmp->get_serial == NULL) ||
            (tmp->set_mode == NULL) ||
            (tmp->start_acqui == NULL) ||
            (tmp->stop_acqui == NULL) ||
            (tmp->get_frame == NULL) ) {

        CYAN_ERROR( ERR_PLUGIN ) ;
        return NULL ;
    }

    // Call plugin init function

    va_start( args, plugin ) ;
    ret = tmp->init( &(tmp->cam_handle), args ) ;
    va_end( args ) ;

    if ( ret != ERR_OK ) {
        CYAN_ERROR_MSG("Could not initialize plugin") ;
        return NULL ;
    }

    // Get the current resolution and create the buffer

    if ( tmp->get_available_modes( tmp->cam_handle, &modes, &nb_modes ) != ERR_OK ) {
        CYAN_ERROR_MSG("Could not get camera available modes") ;
        return NULL ;
    }

    if ( tmp->get_mode( tmp->cam_handle, &current_mode ) != ERR_OK ) {
        CYAN_ERROR_MSG("Could not get camera mode") ;
        return NULL ;
    }

        // Default : Buffer is 1 sec of video

    tmp->img_queue = imqueue_new( 
            modes[current_mode].fps, 
            modes[current_mode].resolution.cols, 
            modes[current_mode].resolution.rows, 
            modes[current_mode].monochrome ) ; 

    if ( tmp->img_queue == NULL ) {
        CYAN_ERROR_MSG("Could not allocate image queue") ;
        return NULL ;
    }

    return tmp ;
}


void hwcam_free( hwcam_t* cam ) {

    if ( cam->running != 0 ) {
        CYAN_ERROR_MSG("Camera is still running. Cannot desallocate.") ;
        return ;
    }

    // Free image queue

    imqueue_free( cam->img_queue ) ;
     
    // Call plugin deinit function

    if ( cam->deinit( cam->cam_handle ) != ERR_OK ) {
        CYAN_ERROR_MSG("Error in plugin Deinit() function") ;
    }

    // Unload dynamic lib

    dlclose( cam->dl_handle ) ;

    // Free structure

    free(cam) ;
}


int hwcam_get_available_modes( hwcam_t* cam, hw_mode_t** modes, int* nb_modes ) {
    if ( cam->running != 0 ) {
        CYAN_ERROR_MSG( "Camera is Running") ;
        return ERR_NOPE ;
    }
    if ( cam->get_available_modes( cam->cam_handle, modes, nb_modes ) != ERR_OK ) {
        CYAN_ERROR( ERR_NOPE ) ;
        return ERR_NOPE ;
    }
    return ERR_OK ;
}


int hwcam_get_serial( hwcam_t* cam, char** serial, size_t* serial_size ) {
    if ( cam->running != 0 ) {
        CYAN_ERROR_MSG( "Camera is Running") ;
        return ERR_NOPE ;
    }
    if ( cam->get_serial( cam->cam_handle, serial, serial_size ) != ERR_OK ) {
        CYAN_ERROR( ERR_NOPE ) ;
        return ERR_NOPE ;
    }
    return ERR_OK ;
}


int hwcam_set_mode( hwcam_t* cam, int mode) {
    int i ;
    hw_mode_t *modes ;
    int nb_modes ;

    if ( cam->running != 0 ) {
        CYAN_ERROR_MSG( "Camera is Running") ;
        return ERR_NOPE ;
    }
    if ( cam->set_mode( cam->cam_handle, mode ) != ERR_OK ) {
        CYAN_ERROR( ERR_NOPE ) ;
        return ERR_NOPE ;
    }

    // resize images in queue

    if ( cam->get_available_modes( cam->cam_handle, &modes, &nb_modes ) != ERR_OK ) {
        CYAN_ERROR_MSG("Could not retrieve available modes") ;
        return ERR_NOPE ;
    }

    for (i=0; i<cam->img_queue->buffer_size; i++ ) 
        if ( image_resize( cam->img_queue->images[i], 
                    modes[mode].resolution.cols,
                    modes[mode].resolution.rows,
                    modes[mode].monochrome, NULL ) != ERR_OK ) {
            CYAN_ERROR_MSG( "Could not resize images" ) ;
            return ERR_NOPE ;
        }

    // resize queue buffer if needed
    

    if ( modes[mode].fps > cam->img_queue->buffer_size ) {
            if ( imqueue_set_buffer_size( cam->img_queue, modes[mode].fps ) != ERR_OK ) {
            CYAN_ERROR_MSG( "Could not resize buffer" ) ;
            return ERR_NOPE ;
            }
    }

    return ERR_OK ;
}


int hwcam_get_mode( hwcam_t* cam, int* mode ) {
    if ( cam->running != 0 ) {
        CYAN_ERROR_MSG( "Camera is Running") ;
        return ERR_NOPE ;
    }
    if ( cam->get_mode( cam->cam_handle, mode) != ERR_OK ) {
        CYAN_ERROR( ERR_NOPE ) ;
        return ERR_NOPE ;
    }
    return ERR_OK ;
}


int hwcam_start_stream( hwcam_t* cam) {
    
    int ret ;

    if ( cam->running != 0 ) {
        CYAN_ERROR_MSG( "Camera is already running ...") ;
        return ERR_NOPE ;
    }

    cam->running = 1 ;

    ret = pthread_create(&(cam->pt_handle), NULL, loop_fct, (void*) cam );
    if (ret){
             CYAN_ERROR_MSG("Could not start thread");
             return ERR_NOPE ;
    }

    return ERR_OK ;
}


int hwcam_stop_stream( hwcam_t* cam ) {
    int ret ;
    if ( cam->running != 1 ) {
        CYAN_ERROR_MSG( "Camera is not running ...") ;
        return ERR_NOPE ;
    }

    cam->running = 0 ;

    pthread_join( cam->pt_handle, NULL ) ;
   
    imqueue_reset( cam->img_queue ) ;
    
    return ERR_OK ;

}

void* loop_fct( void* data ) {

    int ret ;
    hwcam_t* cam = (hwcam_t*) data ;
    image_t* img ;

    cam->start_acqui( cam->cam_handle ) ;

    while ( cam->running ) {

            do {
                ret = imqueue_cam_pop( cam->img_queue, &img ) != ERR_OK ;
                if ( ret != ERR_OK )
                    usleep( BACKOFF_TIME ) ;
             } while ( ret != ERR_OK ) ;

            if ( cam->get_frame( cam->cam_handle, img ) != ERR_OK ) {
                CYAN_ERROR_MSG( "Could not get frame" ) ;
                cam->running = 0 ;
            }
           

            do {
                ret = imqueue_cam_push( cam->img_queue, img ) != ERR_OK ;
                if ( ret != ERR_OK )
                    usleep( BACKOFF_TIME ) ;
             } while ( ret != ERR_OK ) ;

    }

    cam->stop_acqui( cam->cam_handle ) ;

    pthread_exit( NULL ) ;

}

int hwcam_dequeue ( hwcam_t* cam, image_t** image ) {
    int ret ;
    do { 
        ret = imqueue_client_pop( cam->img_queue, image ) ;
        if ( ret != ERR_OK )
            usleep( BACKOFF_TIME ) ;
    } while ( ret != ERR_OK ) ;
    return ERR_OK ;
}

int hwcam_enqueue ( hwcam_t* cam, image_t* image ) {
    int ret ;
    do { 
        ret = imqueue_client_push( cam->img_queue, image ) ;
        if ( ret != ERR_OK )
            usleep( BACKOFF_TIME ) ;
    } while ( ret != ERR_OK ) ;
    return ERR_OK ;
}
