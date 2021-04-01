#ifndef CYAN_MODES_H
#define CYAN_MODES_H

#include <stdint.h>

typedef struct {
    unsigned        int cols ;              // Width
    unsigned        int rows ;              // Height
    float           fps ;                   // Frames / sec
    uint32_t        pixel_format ;          // Camera pixel format
    uint32_t        image_format ;          // Compression type, if any
    uint32_t        enabled ;               // Allows to know if this mode is implemented in cyan 
    char            description[100] ;      // textual description
} hw_mode_t ;


#endif
