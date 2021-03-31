#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

#include "cyan/hwcam/plugin.h"
#include "cyan/hwcam/modes.h"
#include "cyan/hwcam/imageformats.h"
#include "cyan/hwcam/pixelformats.h"
#include "cyan/common/error.h"

typedef struct {

    image_t*    img ;

    hw_mode_t* modes ;
    int         nb_modes ;
    int         current_mode ;

    char*       serial ;
    size_t      serial_size ;

    int             img_count ;
    struct timeval  t0 ;
    useconds_t      wait ;
    useconds_t      wait_inc ;

} cam_still_t ;


int init( void** cam_handle, va_list args ){
    char* filename ;
    int fps ;
    char* serial ;
    cam_still_t* camera ;
    
    filename = va_arg(args, char*) ;
    fps = va_arg(args, int) ;
    serial = va_arg(args, char*) ;

    printf("filename: %s \n", filename ) ;
    printf("fps: %d \n", fps ) ;
    printf("serial: %s \n", serial ) ;

    camera = (cam_still_t*) malloc( sizeof(cam_still_t ) ) ;
    *cam_handle = (void*) camera ;
    if ( camera == NULL ) {
        CYAN_ERROR( ERR_MALLOC ) ;
        return ERR_MALLOC ;
    }

    
    if ( image_load( &(camera->img) , filename ) != ERR_OK ) {
        CYAN_ERROR( ERR_FILE ) ;
        return ERR_FILE ;
    }

    camera->nb_modes = 1;
    camera->modes = ( hw_mode_t* ) malloc( camera->nb_modes * sizeof( hw_mode_t ) ) ;
    if ( camera->modes == NULL ) {
        CYAN_ERROR( ERR_MALLOC ) ;
        return ERR_MALLOC ;
    }

    camera->modes[0].cols = camera->img->cols ;
    camera->modes[0].rows = camera->img->rows ;
    camera->modes[0].image_format = FMT_PLANE ;
    
    if ( camera->img->monochrome ) 
        camera->modes[0].pixel_format = Mono8 ;
    else
        camera->modes[0].pixel_format = RGB8 ;       // DIRTY FIXME

    camera->modes[0].fps = fps ;

    camera->serial = malloc( sizeof(serial) ) ;
    if ( camera->serial == NULL ) {
        CYAN_ERROR( ERR_MALLOC ) ;
        return ERR_MALLOC ;
    }

    memcpy( camera->serial, serial, sizeof(serial) ) ;
    camera->serial_size = sizeof(serial) ;

    camera->current_mode = 0 ;

    camera->img_count = 0 ;
    gettimeofday(&(camera->t0), NULL) ; 

    camera->wait = (1000000 / fps) ;
    camera->wait_inc = camera->wait / 100 ;

    return ERR_OK ;
}


int deinit( void* cam_handle){
    
    image_free( ((cam_still_t*) cam_handle)->img ) ;
    free( ((cam_still_t*)cam_handle)->modes ) ;
    free( ((cam_still_t*)cam_handle)->serial ) ;
    free( cam_handle ) ;

    return ERR_OK ;
}

int get_available_modes( void* cam_handle, hw_mode_t** modes, int* nb_modes ) {

    *modes = ((cam_still_t*)cam_handle)->modes ;
    *nb_modes = ((cam_still_t*)cam_handle)->nb_modes ;

    return ERR_OK ;
}

int get_serial( void* cam_handle, char** serial, size_t* serial_size )  {
    
    *serial = ((cam_still_t*)cam_handle)->serial ;
    *serial_size = ((cam_still_t*)cam_handle)->serial_size ;

    return ERR_OK ;
}

int set_mode( void* cam_handle, int mode )  {
    ((cam_still_t*) cam_handle)->current_mode = mode ;
    return ERR_OK ;
}

int get_mode( void* cam_handle, int* mode ) {
    *mode = ((cam_still_t*) cam_handle)->current_mode ;
    return ERR_OK ;
}

int start_acqui ( void* cam_handle ) {
    return ERR_OK ;
}

int stop_acqui ( void* cam_handle ) {
    return ERR_OK ;
}

int get_frame ( void* cam_handle, image_t* img ) {
    
    struct timeval now ;
    float fps ;
    cam_still_t* cam ;

    cam = (cam_still_t*) cam_handle ;
    
    usleep( cam->wait ) ;
    
    size_t size = img->rows*img->cols*sizeof(double) ;
    memcpy ( img->Y, cam->img->Y, size ) ;
    if ( !img->monochrome ) {
        memcpy ( img->X, cam->img->X, size ) ;
        memcpy ( img->Z, cam->img->Z, size ) ;
    }
   
    // Asservissement du temps d'attente

    cam->img_count++ ;
    
    if ( cam->img_count == 5 ) {
        
        gettimeofday( &now, NULL ) ;
        
        fps = 5.0/ ( now.tv_sec - cam->t0.tv_sec + 0.000001*(now.tv_usec - cam->t0.tv_usec) ) ; 
       
        if (fps > cam->modes[0].fps + 1 ) 
            cam->wait += cam->wait_inc ;
        
        if (fps < cam->modes[0].fps - 1 ) 
            cam->wait -= cam->wait_inc ;
    
        if ( ((int) cam->wait) < 0 )
            cam->wait = 1 ;
   
        printf("FPS : %f / %f ( %d ) \n", fps, cam->modes[0].fps, (int) cam->wait ) ;
        
        cam->img_count = 0 ;
        gettimeofday(&(cam->t0),NULL) ; 

    }

    return ERR_OK ;
}
