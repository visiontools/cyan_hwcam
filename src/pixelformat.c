#include <cyan/hwcam/pixelformats.h>

int pixelformat_ismono( uint32_t format ) {

    switch (format) {
        case Mono8:
        case Mono8s:
        case Mono10:
        case Mono10Packed:
        case Mono12:
        case Mono12Packed:
        case Mono16:
        case Mono14:
        case Mono1p:
        case Mono2p:
        case Mono4p:
        case Mono10p:
        case Mono12p:
        case R8:
        case R16:
        case G8:
        case G16:
        case B8:
        case B16:
        case Mono14p:
        case Mono32:
        case Data8:
        case Data8s:
        case Data16:
        case Data16s:
        case Data32:
        case Data32s:
        case Data32f:
        case Data64:
        case Data64s:
        case Data64f:
        case R10:
        case R12:
        case G10:
        case G12:
        case B10:
        case B12:
            return 1 ;
            break ;
        default:
            break ;
            return 0 ;
    } 

    return 0 ;

}
