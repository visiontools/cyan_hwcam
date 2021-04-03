#ifndef IMAGE_FORMATS_H
#define IMAGE_FORMATS_H

#include <stdint.h>

int imageformat_iscompressed( uint32_t ) ;

#define  FMT_UNSUPPORTED    0xFFFFFFFF      // Not supported by cyan
#define  FMT_PLANE          0x00000001      // No compression.
#define  FMT_JPEG           0x00000002      // TBD. See also VIDIOC_G_JPEGCOMP, VIDIOC_S_JPEGCOMP.
#define  FMT_MPEG           0x00000003      // MPEG multiplexed stream. The actual format is determined by extended control V4L2_CID_MPEG_STREAM_TYPE, see Codec Control IDs.
#define  FMT_H264           0x00000004      // H264 video elementary stream with start codes.
#define  FMT_H264_NO_SC     0x00000005      // H264 video elementary stream without start codes.
#define  FMT_H264_MVC       0x00000006      // H264 MVC video elementary stream.
#define  FMT_H263           0x00000007      // H263 video elementary stream.
#define  FMT_MPEG1          0x00000008      // MPEG1 video elementary stream.
#define  FMT_MPEG2          0x00000009      // MPEG2 video elementary stream.
#define  FMT_MPEG4          0x0000000A      // MPEG4 video elementary stream.
#define  FMT_XVID           0x0000000B      // Xvid video elementary stream.
#define  FMT_VC1_ANNEX_G    0x0000000C      // VC1, SMPTE 421M Annex G compliant stream.
#define  FMT_VC1_ANNEX_L    0x0000000D      // VC1, SMPTE 421M Annex L compliant stream.
#define  FMT_VP8            0x0000000E      // VP8 video elementary stream.
#define  FMT_VP9            0x0000000F      // VP9 video elementary stream.

#endif
