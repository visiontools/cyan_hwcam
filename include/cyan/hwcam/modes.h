#ifndef CYAN_MODES_H
#define CYAN_MODES_H

#include <cyan/hwcam/pixelformats.h>
#include <stdint.h>

typedef struct {
    unsigned int cols ;
    unsigned int rows ;
} hw_resolution_t ;

typedef struct {
    hw_resolution_t resolution ;        // resolution
    int             fps ;               // frames / sec
    uint32_t        pixel_format ;      // camera pixel format
} hw_mode_t ;


#endif
