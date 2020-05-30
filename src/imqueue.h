#ifndef IMQUEUE_H
#define IMQUEUE_H

#include <pthread.h>
#include <cyan/image/image.h>

struct imqueue_s {

    // FIFO1 : Blank images

    image_t** fifo1 ;
    int head1 ;
    int size1 ;
    pthread_mutex_t mutex1 ;

    // FIFO2 : Filled images
    
    image_t** fifo2 ;
    int head2 ;
    int size2 ;
    pthread_mutex_t mutex2 ;

    // Allocated images ;

    image_t**   images ;
    int         buffer_size ;

} ;

typedef struct imqueue_s imqueue_t ;

imqueue_t* imqueue_new( int buffer_size , int cols, int rows, int monochrome) ;
void       imqueue_free( imqueue_t* ) ;

int imqueue_cam_push( imqueue_t*, image_t* ) ;
int imqueue_cam_pop(  imqueue_t*, image_t** ) ;

int imqueue_client_push( imqueue_t*, image_t* ) ;
int imqueue_client_pop(  imqueue_t*, image_t** ) ;

#endif
