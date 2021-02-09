#ifndef PIXEL_FORMATS_H
#define PIXEL_FORMATS_H

#include <stdint.h>

int pixelformat_ismono( uint32_t ) ;

// Generated from GenICam Pixel Format Names and Values            
// Version 14-October-2020            

#define Mono8                     0x01080001   //  Monochrome 8-bit
#define Mono8s                    0x01080002   //  Monochrome 8-bit signed
#define Mono10                    0x01100003   //  Monochrome 10-bit unpacked
#define Mono10Packed              0x010C0004   //  Monochrome 10-bit packed
#define Mono12                    0x01100005   //  Monochrome 12-bit unpacked
#define Mono12Packed              0x010C0006   //  Monochrome 12-bit packed
#define Mono16                    0x01100007   //  Monochrome 16-bit
#define BayerGR8                  0x01080008   //  Bayer Green-Red 8-bit
#define BayerRG8                  0x01080009   //  Bayer Red-Green 8-bit
#define BayerGB8                  0x0108000A   //  Bayer Green-Blue 8-bit
#define BayerBG8                  0x0108000B   //  Bayer Blue-Green 8-bit
#define BayerGR10                 0x0110000C   //  Bayer Green-Red 10-bit unpacked
#define BayerRG10                 0x0110000D   //  Bayer Red-Green 10-bit unpacked
#define BayerGB10                 0x0110000E   //  Bayer Green-Blue 10-bit unpacked
#define BayerBG10                 0x0110000F   //  Bayer Blue-Green 10-bit unpacked
#define BayerGR12                 0x01100010   //  Bayer Green-Red 12-bit unpacked
#define BayerRG12                 0x01100011   //  Bayer Red-Green 12-bit unpacked
#define BayerGB12                 0x01100012   //  Bayer Green-Blue 12-bit unpacked
#define BayerBG12                 0x01100013   //  Bayer Blue-Green 12-bit unpacked
#define RGB8                      0x02180014   //  Red-Green-Blue 8-bit
#define BGR8                      0x02180015   //  Blue-Green-Red 8-bit
#define RGBa8                     0x02200016   //  Red-Green-Blue-alpha 8-bit
#define BGRa8                     0x02200017   //  Blue-Green-Red-alpha 8-bit
#define RGB10                     0x02300018   //  Red-Green-Blue 10-bit unpacked
#define BGR10                     0x02300019   //  Blue-Green-Red 10-bit unpacked
#define RGB12                     0x0230001A   //  Red-Green-Blue 12-bit unpacked
#define BGR12                     0x0230001B   //  Blue-Green-Red 12-bit unpacked
#define RGB10V1Packed             0x0220001C   //  Red-Green-Blue 10-bit packed - variant 1
#define RGB10p32                  0x0220001D   //  Red-Green-Blue 10-bit packed into 32-bit
#define YUV411_8_UYYVYY           0x020C001E   //  YUV 4:1:1 8-bit
#define YUV422_8_UYVY             0x0210001F   //  YUV 4:2:2 8-bit
#define YUV8_UYV                  0x02180020   //  YUV 4:4:4 8-bit
#define RGB8_Planar               0x02180021   //  Red-Green-Blue 8-bit planar
#define RGB10_Planar              0x02300022   //  Red-Green-Blue 10-bit unpacked planar
#define RGB12_Planar              0x02300023   //  Red-Green-Blue 12-bit unpacked planar
#define RGB16_Planar              0x02300024   //  Red-Green-Blue 16-bit planar
#define Mono14                    0x01100025   //  Monochrome 14-bit unpacked
#define BayerGR10Packed           0x010C0026   //  Bayer Green-Red 10-bit packed
#define BayerRG10Packed           0x010C0027   //  Bayer Red-Green 10-bit packed
#define BayerGB10Packed           0x010C0028   //  Bayer Green-Blue 10-bit packed
#define BayerBG10Packed           0x010C0029   //  Bayer Blue-Green 10-bit packed
#define BayerGR12Packed           0x010C002A   //  Bayer Green-Red 12-bit packed
#define BayerRG12Packed           0x010C002B   //  Bayer Red-Green 12-bit packed
#define BayerGB12Packed           0x010C002C   //  Bayer Green-Blue 12-bit packed
#define BayerBG12Packed           0x010C002D   //  Bayer Blue-Green 12-bit packed
#define BayerGR16                 0x0110002E   //  Bayer Green-Red 16-bit
#define BayerRG16                 0x0110002F   //  Bayer Red-Green 16-bit
#define BayerGB16                 0x01100030   //  Bayer Green-Blue 16-bit
#define BayerBG16                 0x01100031   //  Bayer Blue-Green 16-bit
#define YUV422_8                  0x02100032   //  YUV 4:2:2 8-bit
#define RGB16                     0x02300033   //  Red-Green-Blue 16-bit
#define RGB12V1Packed             0x02240034   //  Red-Green-Blue 12-bit packed - variant 1
#define RGB565p                   0x02100035   //  Red-Green-Blue 5/6/5-bit packed
#define BGR565p                   0x02100036   //  Blue-Green-Red 5/6/5-bit packed
#define Mono1p                    0x01010037   //  Monochrome 1-bit packed
#define Mono2p                    0x01020038   //  Monochrome 2-bit packed
#define Mono4p                    0x01040039   //  Monochrome 4-bit packed
#define YCbCr8_CbYCr              0x0218003A   //  YCbCr 4:4:4 8-bit
#define YCbCr422_8                0x0210003B   //  YCbCr 4:2:2 8-bit
#define YCbCr411_8_CbYYCrYY       0x020C003C   //  YCbCr 4:1:1 8-bit
#define YCbCr601_8_CbYCr          0x0218003D   //  YCbCr 4:4:4 8-bit BT.601
#define YCbCr601_422_8            0x0210003E   //  YCbCr 4:2:2 8-bit BT.601
#define YCbCr601_411_8_CbYYCrYY   0x020C003F   //  YCbCr 4:1:1 8-bit BT.601
#define YCbCr709_8_CbYCr          0x02180040   //  YCbCr 4:4:4 8-bit BT.709
#define YCbCr709_422_8            0x02100041   //  YCbCr 4:2:2 8-bit BT.709
#define YCbCr709_411_8_CbYYCrYY   0x020C0042   //  YCbCr 4:1:1 8-bit BT.709
#define YCbCr422_8_CbYCrY         0x02100043   //  YCbCr 4:2:2 8-bit
#define YCbCr601_422_8_CbYCrY     0x02100044   //  YCbCr 4:2:2 8-bit BT.601
#define YCbCr709_422_8_CbYCrY     0x02100045   //  YCbCr 4:2:2 8-bit BT.709
#define Mono10p                   0x010A0046   //  Monochrome 10-bit packed
#define Mono12p                   0x010C0047   //  Monochrome 12-bit packed
#define BGR10p                    0x021E0048   //  Blue-Green-Red 10-bit packed
#define BGR12p                    0x02240049   //  Blue-Green-Red 12-bit packed
#define BGR14                     0x0230004A   //  Blue-Green-Red 14-bit unpacked
#define BGR16                     0x0230004B   //  Blue-Green-Red 16-bit
#define BGRa10                    0x0240004C   //  Blue-Green-Red-alpha 10-bit unpacked
#define BGRa10p                   0x0228004D   //  Blue-Green-Red-alpha 10-bit packed
#define BGRa12                    0x0240004E   //  Blue-Green-Red-alpha 12-bit unpacked
#define BGRa12p                   0x0230004F   //  Blue-Green-Red-alpha 12-bit packed
#define BGRa14                    0x02400050   //  Blue-Green-Red-alpha 14-bit unpacked
#define BGRa16                    0x02400051   //  Blue-Green-Red-alpha 16-bit
#define BayerBG10p                0x010A0052   //  Bayer Blue-Green 10-bit packed
#define BayerBG12p                0x010C0053   //  Bayer Blue-Green 12-bit packed
#define BayerGB10p                0x010A0054   //  Bayer Green-Blue 10-bit packed
#define BayerGB12p                0x010C0055   //  Bayer Green-Blue 12-bit packed
#define BayerGR10p                0x010A0056   //  Bayer Green-Red 10-bit packed
#define BayerGR12p                0x010C0057   //  Bayer Green-Red 12-bit packed
#define BayerRG10p                0x010A0058   //  Bayer Red-Green 10-bit packed
#define BayerRG12p                0x010C0059   //  Bayer Red-Green 12-bit packed
#define YCbCr411_8                0x020C005A   //  YCbCr 4:1:1 8-bit
#define YCbCr8                    0x0218005B   //  YCbCr 4:4:4 8-bit
#define RGB10p                    0x021E005C   //  Red-Green-Blue 10-bit packed
#define RGB12p                    0x0224005D   //  Red-Green-Blue 12-bit packed
#define RGB14                     0x0230005E   //  Red-Green-Blue 14-bit unpacked
#define RGBa10                    0x0240005F   //  Red-Green-Blue-alpha 10-bit unpacked
#define RGBa10p                   0x02280060   //  Red-Green-Blue-alpha 10-bit packed
#define RGBa12                    0x02400061   //  Red-Green-Blue-alpha 12-bit unpacked
#define RGBa12p                   0x02300062   //  Red-Green-Blue-alpha 12-bit packed
#define RGBa14                    0x02400063   //  Red-Green-Blue-alpha 14-bit unpacked
#define RGBa16                    0x02400064   //  Red-Green-Blue-alpha 16-bit
#define YCbCr422_10               0x02200065   //  YCbCr 4:2:2 10-bit unpacked
#define YCbCr422_12               0x02200066   //  YCbCr 4:2:2 12-bit unpacked
#define SCF1WBWG8                 0x01080067   //  Sparse Color Filter #1 White-Blue-White-Green 8-bit
#define SCF1WBWG10                0x01100068   //  Sparse Color Filter #1 White-Blue-White-Green 10-bit unpacked
#define SCF1WBWG10p               0x010A0069   //  Sparse Color Filter #1 White-Blue-White-Green 10-bit packed
#define SCF1WBWG12                0x0110006A   //  Sparse Color Filter #1 White-Blue-White-Green 12-bit unpacked
#define SCF1WBWG12p               0x010C006B   //  Sparse Color Filter #1 White-Blue-White-Green 12-bit packed
#define SCF1WBWG14                0x0110006C   //  Sparse Color Filter #1 White-Blue-White-Green 14-bit unpacked
#define SCF1WBWG16                0x0110006D   //  Sparse Color Filter #1 White-Blue-White-Green 16-bit unpacked
#define SCF1WGWB8                 0x0108006E   //  Sparse Color Filter #1 White-Green-White-Blue 8-bit
#define SCF1WGWB10                0x0110006F   //  Sparse Color Filter #1 White-Green-White-Blue 10-bit unpacked
#define SCF1WGWB10p               0x010A0070   //  Sparse Color Filter #1 White-Green-White-Blue 10-bit packed
#define SCF1WGWB12                0x01100071   //  Sparse Color Filter #1 White-Green-White-Blue 12-bit unpacked
#define SCF1WGWB12p               0x010C0072   //  Sparse Color Filter #1 White-Green-White-Blue 12-bit packed
#define SCF1WGWB14                0x01100073   //  Sparse Color Filter #1 White-Green-White-Blue 14-bit unpacked
#define SCF1WGWB16                0x01100074   //  Sparse Color Filter #1 White-Green-White-Blue 16-bit
#define SCF1WGWR8                 0x01080075   //  Sparse Color Filter #1 White-Green-White-Red 8-bit
#define SCF1WGWR10                0x01100076   //  Sparse Color Filter #1 White-Green-White-Red 10-bit unpacked
#define SCF1WGWR10p               0x010A0077   //  Sparse Color Filter #1 White-Green-White-Red 10-bit packed
#define SCF1WGWR12                0x01100078   //  Sparse Color Filter #1 White-Green-White-Red 12-bit unpacked
#define SCF1WGWR12p               0x010C0079   //  Sparse Color Filter #1 White-Green-White-Red 12-bit packed
#define SCF1WGWR14                0x0110007A   //  Sparse Color Filter #1 White-Green-White-Red 14-bit unpacked
#define SCF1WGWR16                0x0110007B   //  Sparse Color Filter #1 White-Green-White-Red 16-bit
#define SCF1WRWG8                 0x0108007C   //  Sparse Color Filter #1 White-Red-White-Green 8-bit
#define SCF1WRWG10                0x0110007D   //  Sparse Color Filter #1 White-Red-White-Green 10-bit unpacked
#define SCF1WRWG10p               0x010A007E   //  Sparse Color Filter #1 White-Red-White-Green 10-bit packed
#define SCF1WRWG12                0x0110007F   //  Sparse Color Filter #1 White-Red-White-Green 12-bit unpacked
#define SCF1WRWG12p               0x010C0080   //  Sparse Color Filter #1 White-Red-White-Green 12-bit packed
#define SCF1WRWG14                0x01100081   //  Sparse Color Filter #1 White-Red-White-Green 14-bit unpacked
#define SCF1WRWG16                0x01100082   //  Sparse Color Filter #1 White-Red-White-Green 16-bit
#define YCbCr10_CbYCr             0x02300083   //  YCbCr 4:4:4 10-bit unpacked
#define YCbCr10p_CbYCr            0x021E0084   //  YCbCr 4:4:4 10-bit packed
#define YCbCr12_CbYCr             0x02300085   //  YCbCr 4:4:4 12-bit unpacked
#define YCbCr12p_CbYCr            0x02240086   //  YCbCr 4:4:4 12-bit packed
#define YCbCr422_10p              0x02140087   //  YCbCr 4:2:2 10-bit packed
#define YCbCr422_12p              0x02180088   //  YCbCr 4:2:2 12-bit packed
#define YCbCr601_10_CbYCr         0x02300089   //  YCbCr 4:4:4 10-bit unpacked BT.601
#define YCbCr601_10p_CbYCr        0x021E008A   //  YCbCr 4:4:4 10-bit packed BT.601
#define YCbCr601_12_CbYCr         0x0230008B   //  YCbCr 4:4:4 12-bit unpacked BT.601
#define YCbCr601_12p_CbYCr        0x0224008C   //  YCbCr 4:4:4 12-bit packed BT.601
#define YCbCr601_422_10           0x0220008D   //  YCbCr 4:2:2 10-bit unpacked BT.601
#define YCbCr601_422_10p          0x0214008E   //  YCbCr 4:2:2 10-bit packed BT.601
#define YCbCr601_422_12           0x0220008F   //  YCbCr 4:2:2 12-bit unpacked BT.601
#define YCbCr601_422_12p          0x02180090   //  YCbCr 4:2:2 12-bit packed BT.601
#define YCbCr709_10_CbYCr         0x02300091   //  YCbCr 4:4:4 10-bit unpacked BT.709
#define YCbCr709_10p_CbYCr        0x021E0092   //  YCbCr 4:4:4 10-bit packed BT.709
#define YCbCr709_12_CbYCr         0x02300093   //  YCbCr 4:4:4 12-bit unpacked BT.709
#define YCbCr709_12p_CbYCr        0x02240094   //  YCbCr 4:4:4 12-bit packed BT.709
#define YCbCr709_422_10           0x02200095   //  YCbCr 4:2:2 10-bit unpacked BT.709
#define YCbCr709_422_10p          0x02140096   //  YCbCr 4:2:2 10-bit packed BT.709
#define YCbCr709_422_12           0x02200097   //  YCbCr 4:2:2 12-bit unpacked BT.709
#define YCbCr709_422_12p          0x02180098   //  YCbCr 4:2:2 12-bit packed BT.709
#define YCbCr422_10_CbYCrY        0x02200099   //  YCbCr 4:2:2 10-bit unpacked
#define YCbCr422_10p_CbYCrY       0x0214009A   //  YCbCr 4:2:2 10-bit packed
#define YCbCr422_12_CbYCrY        0x0220009B   //  YCbCr 4:2:2 12-bit unpacked
#define YCbCr422_12p_CbYCrY       0x0218009C   //  YCbCr 4:2:2 12-bit packed
#define YCbCr601_422_10_CbYCrY    0x0220009D   //  YCbCr 4:2:2 10-bit unpacked BT.601
#define YCbCr601_422_10p_CbYCrY   0x0214009E   //  YCbCr 4:2:2 10-bit packed BT.601
#define YCbCr601_422_12_CbYCrY    0x0220009F   //  YCbCr 4:2:2 12-bit unpacked BT.601
#define YCbCr601_422_12p_CbYCrY   0x021800A0   //  YCbCr 4:2:2 12-bit packed BT.601
#define YCbCr709_422_10_CbYCrY    0x022000A1   //  YCbCr 4:2:2 10-bit unpacked BT.709
#define YCbCr709_422_10p_CbYCrY   0x021400A2   //  YCbCr 4:2:2 10-bit packed BT.709
#define YCbCr709_422_12_CbYCrY    0x022000A3   //  YCbCr 4:2:2 12-bit unpacked BT.709
#define YCbCr709_422_12p_CbYCrY   0x021800A4   //  YCbCr 4:2:2 12-bit packed BT.709
#define BiColorRGBG8              0x021000A5   //  Bi-color Red/Green - Blue/Green 8-bit
#define BiColorBGRG8              0x021000A6   //  Bi-color Blue/Green - Red/Green 8-bit
#define BiColorRGBG10             0x022000A7   //  Bi-color Red/Green - Blue/Green 10-bit unpacked
#define BiColorRGBG10p            0x021400A8   //  Bi-color Red/Green - Blue/Green 10-bit packed
#define BiColorBGRG10             0x022000A9   //  Bi-color Blue/Green - Red/Green 10-bit unpacked
#define BiColorBGRG10p            0x021400AA   //  Bi-color Blue/Green - Red/Green 10-bit packed
#define BiColorRGBG12             0x022000AB   //  Bi-color Red/Green - Blue/Green 12-bit unpacked
#define BiColorRGBG12p            0x021800AC   //  Bi-color Red/Green - Blue/Green 12-bit packed
#define BiColorBGRG12             0x022000AD   //  Bi-color Blue/Green - Red/Green 12-bit unpacked
#define BiColorBGRG12p            0x021800AE   //  Bi-color Blue/Green - Red/Green 12-bit packed
#define Coord3D_A8                0x010800AF   //  3D coordinate A 8-bit
#define Coord3D_B8                0x010800B0   //  3D coordinate B 8-bit
#define Coord3D_C8                0x010800B1   //  3D coordinate C 8-bit
#define Coord3D_ABC8              0x021800B2   //  3D coordinate A-B-C 8-bit
#define Coord3D_ABC8_Planar       0x021800B3   //  3D coordinate A-B-C 8-bit planar
#define Coord3D_AC8               0x021000B4   //  3D coordinate A-C 8-bit
#define Coord3D_AC8_Planar        0x021000B5   //  3D coordinate A-C 8-bit planar
#define Coord3D_A16               0x011000B6   //  3D coordinate A 16-bit
#define Coord3D_B16               0x011000B7   //  3D coordinate B 16-bit
#define Coord3D_C16               0x011000B8   //  3D coordinate C 16-bit
#define Coord3D_ABC16             0x023000B9   //  3D coordinate A-B-C 16-bit
#define Coord3D_ABC16_Planar      0x023000BA   //  3D coordinate A-B-C 16-bit planar
#define Coord3D_AC16              0x022000BB   //  3D coordinate A-C 16-bit
#define Coord3D_AC16_Planar       0x022000BC   //  3D coordinate A-C 16-bit planar
#define Coord3D_A32f              0x012000BD   //  3D coordinate A 32-bit floating point
#define Coord3D_B32f              0x012000BE   //  3D coordinate B 32-bit floating point
#define Coord3D_C32f              0x012000BF   //  3D coordinate C 32-bit floating point
#define Coord3D_ABC32f            0x026000C0   //  3D coordinate A-B-C 32-bit floating point
#define Coord3D_ABC32f_Planar     0x026000C1   //  3D coordinate A-B-C 32-bit floating point planar
#define Coord3D_AC32f             0x024000C2   //  3D coordinate A-C 32-bit floating point
#define Coord3D_AC32f_Planar      0x024000C3   //  3D coordinate A-C 32-bit floating point planar
#define Confidence1               0x010800C4   //  Confidence 1-bit unpacked
#define Confidence1p              0x010100C5   //  Confidence 1-bit packed
#define Confidence8               0x010800C6   //  Confidence 8-bit
#define Confidence16              0x011000C7   //  Confidence 16-bit
#define Confidence32f             0x012000C8   //  Confidence 32-bit floating point
#define R8                        0x010800C9   //  Red 8-bit
#define R10_Deprecated            0x010A00CA   //  Deprecated because size field is wrong
#define R12_Deprecated            0x010C00CB   //  Deprecated because size field is wrong
#define R16                       0x011000CC   //  Red 16-bit
#define G8                        0x010800CD   //  Green 8-bit
#define G10_Deprecated            0x010A00CE   //  Deprecated because size field is wrong
#define G12_Deprecated            0x010C00CF   //  Deprecated because size field is wrong
#define G16                       0x011000D0   //  Green 16-bit
#define B8                        0x010800D1   //  Blue 8-bit
#define B10_Deprecated            0x010A00D2   //  Deprecated because size field is wrong
#define B12_Deprecated            0x010C00D3   //  Deprecated because size field is wrong
#define B16                       0x011000D4   //  Blue 16-bit
#define Coord3D_A10p              0x010A00D5   //  3D coordinate A 10-bit packed
#define Coord3D_B10p              0x010A00D6   //  3D coordinate B 10-bit packed
#define Coord3D_C10p              0x010A00D7   //  3D coordinate C 10-bit packed
#define Coord3D_A12p              0x010C00D8   //  3D coordinate A 12-bit packed
#define Coord3D_B12p              0x010C00D9   //  3D coordinate B 12-bit packed
#define Coord3D_C12p  		      0x010C00DA   //  3D coordinate C 12-bit packed
#define Coord3D_ABC10p            0x021E00DB   //  3D coordinate A-B-C 10-bit packed
#define Coord3D_ABC10p_Planar     0x021E00DC   //  3D coordinate A-B-C 10-bit packed planar
#define Coord3D_ABC12p            0x022400DE   //  3D coordinate A-B-C 12-bit packed
#define Coord3D_ABC12p_Planar     0x022400DF   //  3D coordinate A-B-C 12-bit packed planar
#define Coord3D_AC10p             0x021400F0   //  3D coordinate A-C 10-bit packed
#define Coord3D_AC10p_Planar      0x021400F1   //  3D coordinate A-C 10-bit packed planar
#define Coord3D_AC12p             0x021800F2   //  3D coordinate A-C 12-bit packed
#define Coord3D_AC12p_Planar      0x021800F3   //  3D coordinate A-C 12-bit packed planar
#define YCbCr2020_8_CbYCr         0x021800F4   //  YCbCr 4:4:4 8-bit BT.2020
#define YCbCr2020_10_CbYCr        0x023000F5   //  YCbCr 4:4:4 10-bit unpacked BT.2020
#define YCbCr2020_10p_CbYCr       0x021E00F6   //  YCbCr 4:4:4 10-bit packed BT.2020
#define YCbCr2020_12_CbYCr        0x023000F7   //  YCbCr 4:4:4 12-bit unpacked BT.2020
#define YCbCr2020_12p_CbYCr       0x022400F8   //  YCbCr 4:4:4 12-bit packed BT.2020
#define YCbCr2020_411_8_CbYYCrYY  0x020C00F9   //  YCbCr 4:1:1 8-bit BT.2020
#define YCbCr2020_422_8           0x021000FA   //  YCbCr 4:2:2 8-bit BT.2020
#define YCbCr2020_422_8_CbYCrY    0x021000FB   //  YCbCr 4:2:2 8-bit BT.2020
#define YCbCr2020_422_10          0x022000FC   //  YCbCr 4:2:2 10-bit unpacked BT.2020
#define YCbCr2020_422_10_CbYCrY   0x022000FD   //  YCbCr 4:2:2 10-bit unpacked BT.2020
#define YCbCr2020_422_10p         0x021400FE   //  YCbCr 4:2:2 10-bit packed BT.2020
#define YCbCr2020_422_10p_CbYCrY  0x021400FF   //  YCbCr 4:2:2 10-bit packed BT.2020
#define YCbCr2020_422_12          0x02200100   //  YCbCr 4:2:2 12-bit unpacked BT.2020
#define YCbCr2020_422_12_CbYCrY   0x02200101   //  YCbCr 4:2:2 12-bit unpacked BT.2020
#define YCbCr2020_422_12p         0x02180102   //  YCbCr 4:2:2 12-bit packed BT.2020
#define YCbCr2020_422_12p_CbYCrY  0x02180103   //  YCbCr 4:2:2 12-bit packed BT.2020
#define Mono14p                   0x010E0104   //  Monochrome 14-bit packed
#define BayerGR14p                0x010E0105   //  Bayer Green-Red 14-bit packed
#define BayerRG14p                0x010E0106   //  Bayer Red-Green 14-bit packed
#define BayerGB14p                0x010E0107   //  Bayer Green-Blue 14-bit packed
#define BayerBG14p                0x010E0108   //  Bayer Blue-Green 14-bit packed
#define BayerGR14                 0x01100109   //  Bayer Green-Red 14-bit
#define BayerRG14                 0x0110010A   //  Bayer Red-Green 14-bit
#define BayerGB14                 0x0110010B   //  Bayer Green-Blue 14-bit
#define BayerBG14                 0x0110010C   //  Bayer Blue-Green 14-bit
#define BayerGR4p                 0x0104010D   //  Bayer Green-Red 4-bit packed
#define BayerRG4p                 0x0104010E   //  Bayer Red-Green 4-bit packed
#define BayerGB4p                 0x0104010F   //  Bayer Green-Blue 4-bit packed
#define BayerBG4p                 0x01040110   //  Bayer Blue-Green 4-bit packed
#define Mono32                    0x01200111   //  Monochrome 32-bit
#define YCbCr420_8_YY_CbCr_Semiplanar    0x020C0112   //  YCbCr 4:2:0 8-bit YY/CbCr Semiplanar
#define YCbCr422_8_YY_CbCr_Semiplanar    0x02100113   //  YCbCr 4:2:2 8-bit YY/CbCr Semiplanar
#define YCbCr420_8_YY_CrCb_Semiplanar    0x020C0114   //  YCbCr 4:2:0 8-bit YY/CrCb Semiplanar
#define YCbCr422_8_YY_CrCb_Semiplanar    0x02100115   //  YCbCr 4:2:2 8-bit YY/CrCb Semiplanar
#define Data8                     0x01080116   //  Data 8-bit
#define Data8s                    0x01080117   //  Data 8-bit signed
#define Data16                    0x01100118   //  Data 16-bit
#define Data16s                   0x01100119   //  Data 16-bit signed
#define Data32                    0x0120011A   //  Data 32-bit
#define Data32s                   0x0120011B   //  Data 32-bit signed
#define Data32f                   0x0120011C   //  Data 32-bit floating point
#define Data64                    0x0140011D   //  Data 64-bit
#define Data64s                   0x0140011E   //  Data 64-bit signed
#define Data64f                   0x0140011F   //  Data 64-bit floating point
#define R10                       0x01100120   //  Red 10-bit
#define R12                       0x01100121   //  Red 12-bit
#define G10                       0x01100122   //  Green 10-bit
#define G12                       0x01100123   //  Green 12-bit
#define B10                       0x01100124   //  Blue 10-bit
#define B12                       0x01100125   //  Blue 12-bit

#endif
