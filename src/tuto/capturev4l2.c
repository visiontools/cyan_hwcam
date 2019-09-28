#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>

#include <cyan/image.h>

uint8_t *buffer;
 
static int xioctl(int fd, int request, void *arg)
{
        int r;
 
        do r = ioctl (fd, request, arg);
        while (-1 == r && EINTR == errno);
 
        return r;
}
 
int print_caps(int fd)
{
        struct v4l2_capability caps = {};
        if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &caps))
        {
                perror("Querying Capabilities");
                return 1;
        }
 
        printf( "Driver Caps:\n"
                "  Driver: \"%s\"\n"
                "  Card: \"%s\"\n"
                "  Bus: \"%s\"\n"
                "  Version: %d.%d\n"
                "  Capabilities: %08x\n",
                caps.driver,
                caps.card,
                caps.bus_info,
                (caps.version>>16)&&0xff,
                (caps.version>>24)&&0xff,
                caps.capabilities);
 
 
        struct v4l2_cropcap cropcap = {0};
        cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (-1 == xioctl (fd, VIDIOC_CROPCAP, &cropcap))
        {
                perror("Querying Cropping Capabilities");
                return 1;
        }
 
        printf( "Camera Cropping:\n"
                "  Bounds: %dx%d+%d+%d\n"
                "  Default: %dx%d+%d+%d\n"
                "  Aspect: %d/%d\n",
                cropcap.bounds.width, cropcap.bounds.height, cropcap.bounds.left, cropcap.bounds.top,
                cropcap.defrect.width, cropcap.defrect.height, cropcap.defrect.left, cropcap.defrect.top,
                cropcap.pixelaspect.numerator, cropcap.pixelaspect.denominator);
 
        int support_grbg10 = 0;
 
        struct v4l2_fmtdesc fmtdesc = {0};
        fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        char fourcc[5] = {0};
        char c, e;
        printf("  FMT : CE Desc\n--------------------\n");
        while (0 == xioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc))
        {
                strncpy(fourcc, (char *)&fmtdesc.pixelformat, 4);
                if (fmtdesc.pixelformat == V4L2_PIX_FMT_SGRBG10)
                    support_grbg10 = 1;
                c = fmtdesc.flags & 1? 'C' : ' ';
                e = fmtdesc.flags & 2? 'E' : ' ';
                printf("  %s: %c%c %s\n", fourcc, c, e, fmtdesc.description);
                fmtdesc.index++;
        }
        /*
        if (!support_grbg10)
        {
            printf("Doesn't support GRBG10.\n");
            return 1;
        }*/
 
        struct v4l2_format fmt = {0};
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.width = 640;
        fmt.fmt.pix.height = 480;
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
        fmt.fmt.pix.field = V4L2_FIELD_NONE;
        
        if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
        {
            perror("Setting Pixel Format");
            return 1;
        }
 
        strncpy(fourcc, (char *)&fmt.fmt.pix.pixelformat, 4);
        printf( "Selected Camera Mode:\n"
                "  Width: %d\n"
                "  Height: %d\n"
                "  PixFmt: %s\n"
                "  Field: %d\n",
                fmt.fmt.pix.width,
                fmt.fmt.pix.height,
                fourcc,
                fmt.fmt.pix.field);
        return 0;
}
 
int init_mmap(int fd)
{
    struct v4l2_requestbuffers req = {0};
    req.count = 1;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
 
    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req))
    {
        perror("Requesting Buffer");
        return 1;
    }
 
    struct v4l2_buffer buf = {0};
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;
    if(-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf))
    {
        perror("Querying Buffer");
        return 1;
    }
 
    buffer = mmap (NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
    printf("Length: %d\nAddress: %p\n", buf.length, buffer);
    printf("Image Length: %d\n", buf.bytesused);
 
    return 0;
}

int clamp( int x, int min, int max){
if (x < min)
    return min;
else 
    if (x > max)
        return max;
return x ;
}


int capture_image(int fd, int ii)
{
    struct v4l2_buffer buf = {0};
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;
    if(-1 == xioctl(fd, VIDIOC_QBUF, &buf))
    {
        perror("Query Buffer");
        return 1;
    }
 
    if(-1 == xioctl(fd, VIDIOC_STREAMON, &buf.type))
    {
        perror("Start Capture");
        return 1;
    }
 
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    struct timeval tv = {0};
    tv.tv_sec = 2;
    int r = select(fd+1, &fds, NULL, NULL, &tv);
    if(-1 == r)
    {
        perror("Waiting for Frame");
        return 1;
    }
 
    if(-1 == xioctl(fd, VIDIOC_DQBUF, &buf))
    {
        perror("Retrieving Frame");
        return 1;
    }
    //printf ("saving image\n");
    
    image_t * tmp = image_new( 640, 480, CYAN_COLORTYPE_RGB ) ;
    int i,j,k ;
    int R,G,B ;
    int C,D,E ;
    k = 0 ;
    unsigned char* bb ;
    bb = buffer ;
    for(j=0;j<480;j++){
        for (i=0;i<640;i+=2) {
        unsigned char y1,u,y2,v;
        y1 = bb[k] ;
        u = bb[k+1] ;
        y2 = bb[k+2] ;
        v = bb[k+3] ;
        
        C = y1 - 16 ;
        D = u - 128 ;
        E = v - 128 ;
        R = ( 298*C + 409*E + 128 ) >> 8 ;
        G = ( 298*C - 100*D - 208*E + 128 ) >> 8 ;
        B = ( 298*C + 516*D + 128 ) >> 8 ;
        color_t* pixel = image_get_pixel_pointer( tmp, i,j ) ;
        pixel->coords[RGB_R] = ((double) clamp(R,0,255)) / 255.0 ;
        pixel->coords[RGB_G] = ((double) clamp(G,0,255)) / 255.0 ;
        pixel->coords[RGB_B] = ((double) clamp(B,0,255)) / 255.0 ;

        C = y2 - 16 ;
        D = u - 128 ;
        E = v - 128 ;
        R = ( 298*C + 409*E + 128 ) >> 8 ;
        G = ( 298*C - 100*D - 208*E + 128 ) >> 8 ;
        B = ( 298*C + 516*D + 128 ) >> 8 ;
        pixel = image_get_pixel_pointer( tmp, i+1,j ) ;
        pixel->coords[RGB_R] = ((double) clamp(R,0,255)) / 255.0 ;
        pixel->coords[RGB_G] = ((double) clamp(G,0,255)) / 255.0 ;
        pixel->coords[RGB_B] = ((double) clamp(B,0,255)) / 255.0 ;

        k+=4 ;
        }
    }

    char filename[255] ;
    sprintf(filename, "%d.ppm",ii ) ;
    //image_save_ppm( tmp, filename ) ; 

    image_free( tmp );


    return 0;
}
 
int main()
{
        int fd;
        fd = open("/dev/video2", O_RDWR);
        if (fd == -1)
        {
                perror("Opening video device");
                return 1;
        }
        if(print_caps(fd))
            return 1;
        
        if(init_mmap(fd))
            return 1;
        int i;
        for(i=0; i<15; i++)
        {
            if(capture_image(fd,i))
                return 1;
        }
        close(fd);
        return 0;
}
