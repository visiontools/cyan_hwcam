#ifndef CYAN_HWCAM_H
#define CYAN_HWCAM_H

#include <pthread.h>
#include <stdarg.h>

#include <cyan/image/image.h>
#include <cyan_hwcam/modes.h>

struct imqueue ;

typedef struct {

    // state

    int     running ;

    // camera

    void*           cam_handle ;    // handle to real_camera (will depend on underlying technology)

    int (*init)( void** cam_handle, va_list args  );
    int (*deinit)( void* cam_handle);
    int (*get_available_modes)( void* cam_handle, hw_mode_t** modes, int* nb_modes ) ;
    int (*get_serial)( void* cam_handle, unsigned char** serial, size_t* serial_size ) ;
    int (*set_mode)( void* cam_handle, int fps, hw_resolution_t,  int mono ) ;
    int (*get_mode)( void* cam_handle, int* fps, hw_resolution_t*, int* mono ) ;
    int (*start_acqui) ( void* cam_handle ) ;
    int (*stop_acqui) ( void* cam_handle ) ;
    int (*get_frame) ( void* cam_handle, image_t* img ) ;


    // image buffer

    struct imqueue_s*  img_queue ;

    // thread

    void*       dl_handle ;             // handle for dlopen/dlclose
    pthread_t   pt_handle ;             // handle for pthread

} hwcam_t ;


hwcam_t* hwcam_new( unsigned char* plugin, ... ) ;
void     hwcam_free( hwcam_t* ) ;

int hwcam_get_available_modes(hwcam_t*, hw_mode_t** modes, int* nb_modes ) ;
int hwcam_get_serial( hwcam_t*, unsigned char** serial, size_t* serial_size ) ;

int hwcam_set_mode( hwcam_t*, int fps, hw_resolution_t res, int mono) ;
int hwcam_get_mode( hwcam_t*, int* fps, hw_resolution_t* res, int* mono ) ;

int hwcam_start_stream( hwcam_t* ) ;
int hwcam_stop_stream( hwcam_t* ) ;

image_t* hwcam_dequeue ( hwcam_t* ) ;
int      hwcam_enqueue ( hwcam_t*, image_t* ) ;

#endif
