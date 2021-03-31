#ifndef CYAN_MODES_H
#define CYAN_MODES_H

#include <stdint.h>

typedef struct {
    unsigned        int cols ;              // Width
    unsigned        int rows ;              // Height
    float           fps ;                   // Frames / sec
    uint32_t        pixel_format ;          // Camera pixel format
    uint32_t        image_format ;          // Compression type, if any
} hw_mode_t ;


#endif
