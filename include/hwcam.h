#ifndef HWCAM_H
#define HWCAM_H

#include <pthread.h>
#include <cyan/image/image.h>

typedef enum {
    HWRES_640x480 ,
    HWRES_800x600 ,
    HWRES_1024x768 ,
    HWRES_1280x1024 ,
} hw_resolution_t ;

typedef enum {
    HWFPS_15 ,
    HWFPS_24 ,
    HWFPS_30 ,
    HWFPS_60 ,
} hw_fps_t ;

typedef struct {
    hw_resolution_t resolution ;        // current resolution
    hw_fps_t        fps ;               // frames / sec
} hw_mode_t ;

struct imqueue ;

typedef struct {

    // camera

    void*           cam_handle ;    // handle to real_camera (will depend on underlying technology)
    unsigned char*  serial ;        // cam serial number 
    size_t          serial_length ; 

    int (*init)( void** cam_handle, ...  );
    int (*get_available_modes)( void* cam_handle, hw_mode_t* modes, int* nb_modes ) ;
    int (*get_serial)( void* cam_handle, unsigned char* serial, size_t serial_size ) ;
    int (*set_mode)( void* cam_handle, hw_fps_t, hw_resolution_t ) ;
    int (*start_acqui) ( void* cam_handle ) ;
    int (*stop_acqui) ( void* cam_handle ) ;
    int (*get_frame) ( void* cam_handle, image_t* img ) ;

    // image buffer

    struct imqueue*  img_queue ;

    // thread

    pthread_t   thread ;

} hwcam_t ;


hwcam_t* hwcam_new( unsigned char* plugin, ... ) ;
void     hwcam_del( hwcam_t* ) ;

int hwcam_get_available_modes(hwcam_t*, hw_mode_t* modes, int* nb_modes ) ;
int hwcam_get_serial( hwcam_t*, unsigned char* serial, size_t serial_size ) ;

int hwcam_set_mode( hwcam_t*, hw_fps_t, hw_resolution_t ) ;

int hwcam_start_stream( hwcam_t* ) ;
int hwcam_stop_stream( hwcam_t* ) ;

image_t* hwcam_dequeue ( hwcam_t* ) ;
int      hwcam_enqueue ( hwcam_t*, image_t* ) ;

#endif
