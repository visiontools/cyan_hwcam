#ifndef CYAN_MODES_H
#define CYAN_MODES_H

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



#endif
