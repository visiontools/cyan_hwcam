#ifndef CYAN_MODES_H
#define CYAN_MODES_H

typedef struct {
    unsigned int cols ;
    unsigned int rows ;
} hw_resolution_t ;

typedef struct {
    hw_resolution_t resolution ;        // current resolution
    int             fps ;               // frames / sec
} hw_mode_t ;


#endif
