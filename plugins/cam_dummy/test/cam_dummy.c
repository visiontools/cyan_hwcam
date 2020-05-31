#include <stdio.h>
#include <cyan/image/image.h>

#include <cyan_hwcam/hwcam.h>

int main (int argc, char** argv) {

    hwcam_t* camera ;
    hw_mode_t*   modes ;
    int nb_modes ;
    int i ;
    image_t* image ;

    camera = hwcam_new( "../libcam_dummy.so" ) ;
    
    hwcam_get_available_modes( camera, &modes, &nb_modes ) ;

    hwcam_start_stream( camera ) ;
    
    for (i=0; i<500; i++) {
        hwcam_dequeue( camera, &image ) ;
        hwcam_enqueue( camera, image ) ;
    }

    hwcam_stop_stream( camera ) ;

    hwcam_free( camera ) ;

    return 0 ;

}
