#ifndef HWCAM_H
#define HWCAM_H

#include <cyan/color/colors.h>
#include <cyan/image/image.h>

typedef enum {
    HWCAM_FILE ;
    HWCAM_V4L2 ;
    HWCAM_GSTREAMER ;
} hw_camera_t ;

typedef enum {
    HWRES_640x480 ;
    HWRES_800x600 ;
    HWRES_1024x768 ;
    HWRES_1280x1024 ;
} hw_resolution_t ;

typedef enum {
    HWFPS_15 ;
    HWFPS_24 ;
    HWFPS_30 ;
    HWFPS_60 ;
} hw_fps_t ;

#endif
