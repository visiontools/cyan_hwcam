#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#include "cyan_hwcam/plugin.h"
#include "cyan_hwcam/modes.h"
#include "cyan/common/error.h"


int init( void** cam_handle, va_list args ){
    
    return ERR_OK ;
}


int deinit( void* cam_handle){
    return ERR_OK ;
}

int get_available_modes( void* cam_handle, hw_mode_t** modes, int* nb_modes ) {

    return ERR_OK ;
}

int get_serial( void* cam_handle, unsigned char** serial, size_t* serial_size )  {
    return ERR_OK ;
}

int set_mode( void* cam_handle, int mode )  {
    return ERR_OK ;
}

int get_mode( void* cam_handle, int* mode ) {
    return ERR_OK ;
}

int start_acqui ( void* cam_handle ) {
    return ERR_OK ;
}

int stop_acqui ( void* cam_handle ) {
    return ERR_OK ;
}

int get_frame ( void* cam_handle, image_t* img ) {
    return ERR_OK ;
}
