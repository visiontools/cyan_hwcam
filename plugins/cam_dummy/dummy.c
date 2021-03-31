#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#include "cyan/hwcam/plugin.h"
#include "cyan/hwcam/modes.h"
#include "cyan/hwcam/pixelformats.h"
#include "cyan/hwcam/imageformats.h"
#include "cyan/common/error.h"


int init( void** cam_handle, va_list args ){
    
    printf("[dummy] *** init()\n" ) ;
    *cam_handle = (void*) 12345 ;
    printf("[dummy] \t cam_handle is set to %p\n", *cam_handle ) ;
    return ERR_OK ;
}


int deinit( void* cam_handle){
    printf("[dummy] *** deinit()\n" ) ;
    printf("[dummy] \t cam_handle value is %p\n", cam_handle ) ;
    return ERR_OK ;
}

int get_available_modes( void* cam_handle, hw_mode_t** modes, int* nb_modes ) {
    int i ;
    printf("[dummy] *** get_available modes()\n" ) ;
    printf("[dummy] \t cam_handle value is %p\n", cam_handle ) ;
   
    *nb_modes = 3 ;
    *modes = (hw_mode_t*) malloc ( (*nb_modes)*sizeof(hw_mode_t) ) ;

    (*modes)[0].cols = 1280 ;
    (*modes)[0].rows = 960 ;
    (*modes)[0].pixel_format = Mono8 ;
    (*modes)[0].image_format = FMT_PLANE ;
    (*modes)[0].fps = 15 ;

    (*modes)[1].cols = 640 ;
    (*modes)[1].rows = 480 ; 
    (*modes)[1].pixel_format = RGB8 ;
    (*modes)[0].image_format = FMT_PLANE ;
    (*modes)[1].fps = 30 ;
    
    (*modes)[2].cols = 320 ;
    (*modes)[2].rows = 240 ;
    (*modes)[2].pixel_format = RGB8 ;
    (*modes)[0].image_format = FMT_PLANE ;
    (*modes)[2].fps = 60 ;

    for(i=0; i<(*nb_modes); i++) {
        printf("[dummy] \t Mode[%d] %dx%d(%d) @%f FPS\n", i, 
                (*modes)[i].cols, 
                (*modes)[i].rows, 
                pixelformat_ismono((*modes)[i].pixel_format),
                (*modes)[i].fps ) ;
    }

    return ERR_OK ;
}

int get_serial( void* cam_handle, char** serial, size_t* serial_size )  {
    char tmp_serial[]="00:11:22:33:44:55:66:77:88:99" ;
    printf("[dummy] *** get_serial()\n" ) ;
    printf("[dummy] \t cam_handle value is %p\n", cam_handle ) ;
    *serial_size = sizeof(tmp_serial) ;
    *serial = malloc ( *serial_size ) ;
    memcpy( *serial, tmp_serial, *serial_size ) ;
    printf("[dummy] \t serial_size %d\n", (int) *serial_size ) ;
    printf("[dummy] \t serial :  %s\n", *serial ) ;
    return ERR_OK ;
}

int set_mode( void* cam_handle, int mode )  {
    printf("[dummy] *** set_mode()\n" ) ;
    printf("[dummy] \t cam_handle value is %p\n", cam_handle ) ;
    printf("[dummy] \t mode :  %d\n", mode ) ;
    return ERR_OK ;
}

int get_mode( void* cam_handle, int* mode ) {
    *mode = 1 ;
    printf("[dummy] *** get_mode()\n" ) ;
    printf("[dummy] \t cam_handle value is %p\n", cam_handle ) ;
    printf("[dummy] \t mode :  %d\n", *mode ) ;
    return ERR_OK ;
}

int start_acqui ( void* cam_handle ) {
    printf("[dummy] *** start_acqui()\n" ) ;
    printf("[dummy] \t cam_handle value is %p\n", cam_handle ) ;
    return ERR_OK ;
}

int stop_acqui ( void* cam_handle ) {
    printf("[dummy] *** stop_acqui()\n" ) ;
    printf("[dummy] \t cam_handle value is %p\n", cam_handle ) ;
    return ERR_OK ;
}

int get_frame ( void* cam_handle, image_t* img ) {
    printf("[dummy] *** get_frame()\n" ) ;
    usleep( 1000 ) ;
    return ERR_OK ;
}
