#ifndef CYAN_HWCAM_PLUGIN_H
#define CYAN_HWCAM_PLUGIN_H

#include <cyan/image/image.h>
#include <cyan_hwcam/modes.h>

// This is the API every hwcam plugin should implement

int init( void** cam_handle, ...  );
int get_available_modes( void* cam_handle, hw_mode_t* modes, int* nb_modes ) ;
int get_serial( void* cam_handle, unsigned char* serial, size_t serial_size ) ;
int set_mode( void* cam_handle, hw_fps_t, hw_resolution_t ) ;
int start_acqui ( void* cam_handle ) ;
int stop_acqui ( void* cam_handle ) ;
int get_frame ( void* cam_handle, image_t* img ) ;

#endif

