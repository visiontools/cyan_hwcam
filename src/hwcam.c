#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>

#include <cyan/common/error.h>
#include "cyan_hwcam/hwcam.h"
#include "imqueue.h"


void* loop_fct( void* img ) ;


hwcam_t* hwcam_new( unsigned char* plugin, ... ) {
    hwcam_t* tmp ; 
    int fps ;
    hw_resolution_t res ;
    int mono ;
    va_list args ;
    int ret ;
    
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

    if ( tmp->get_mode( tmp->cam_handle, &fps, &res, &mono ) != ERR_OK ) {
        CYAN_ERROR_MSG("Could not get camera mode") ;
        return NULL ;
    }

        // Default : Buffer is 1 sec of video

    tmp->img_queue = imqueue_new( fps, res.cols, res.rows, mono ) ; 

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


int hwcam_get_available_modes( hwcam_t* cam, hw_mode_t* modes, int* nb_modes ) {
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


int hwcam_get_serial( hwcam_t* cam, unsigned char** serial, size_t* serial_size ) {
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


int hwcam_set_mode( hwcam_t* cam, int fps, hw_resolution_t res, int mono) {
    if ( cam->running != 0 ) {
        CYAN_ERROR_MSG( "Camera is Running") ;
        return ERR_NOPE ;
    }
    if ( cam->set_mode( cam->cam_handle, fps, res, mono ) != ERR_OK ) {
        CYAN_ERROR( ERR_NOPE ) ;
        return ERR_NOPE ;
    }

    // TODO: must reallocate image queue

    return ERR_OK ;
}


int hwcam_get_mode( hwcam_t* cam, int* fps, hw_resolution_t* res, int* mono ) {
    if ( cam->running != 0 ) {
        CYAN_ERROR_MSG( "Camera is Running") ;
        return ERR_NOPE ;
    }
    if ( cam->get_mode( cam->cam_handle, fps, res, mono ) != ERR_OK ) {
        CYAN_ERROR( ERR_NOPE ) ;
        return ERR_NOPE ;
    }
    return ERR_OK ;
}


int hwcam_start( hwcam_t* cam) {
    
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


int hwcam_stop( hwcam_t* cam ) {
    int ret ;
    if ( cam->running != 1 ) {
        CYAN_ERROR_MSG( "Camera is not running ...") ;
        return ERR_NOPE ;
    }

    cam->running = 0 ;

    pthread_join( cam->pt_handle, NULL ) ;
    
    return ERR_OK ;

}

void* loop_fct( void* data ) {

    hwcam_t* cam = (hwcam_t*) data ;
    image_t* img ;

    cam->start_acqui( cam->cam_handle ) ;

    while ( cam->running ) {

            if ( imqueue_cam_pop( cam->img_queue, &img ) != ERR_OK ) {
                CYAN_ERROR_MSG( "Could not pop from queue" ) ;
                cam->running = 0 ;
            }

            if ( cam->get_frame( cam->cam_handle, img ) != ERR_OK ) {
                CYAN_ERROR_MSG( "Could not get frame" ) ;
                cam->running = 0 ;
            }
            
            if ( cam->get_frame( cam->cam_handle, img ) != ERR_OK ) {
                CYAN_ERROR_MSG( "Could not push into queue" ) ;
                cam->running = 0 ;
            }

    }

    cam->stop_acqui( cam->cam_handle ) ;

    pthread_exit( NULL ) ;

}
