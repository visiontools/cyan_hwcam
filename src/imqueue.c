#include <stdlib.h>
#include <cyan/common/error.h>
#include "imqueue.h"

imqueue_t* imqueue_new( int buffer_size , int cols, int rows, int mono) {
    int i ;
    imqueue_t* tmp ;
    tmp = (imqueue_t*) malloc( sizeof(imqueue_t) ) ;
    if ( tmp == NULL ) {
        CYAN_ERROR( ERR_MALLOC ) ;
        return NULL ;
    }
    tmp->fifo1 = (image_t**) malloc ( buffer_size* sizeof(image_t*)) ;
    if ( tmp->fifo1 == NULL ) {
        CYAN_ERROR( ERR_MALLOC ) ;
        return NULL ;
    }
    tmp->fifo2 = (image_t**) malloc ( buffer_size* sizeof(image_t*)) ;
    if ( tmp->fifo2 == NULL ) {
        CYAN_ERROR( ERR_MALLOC ) ;
        return NULL ;
    }
    tmp->images = (image_t**) malloc ( buffer_size* sizeof(image_t*)) ;
    if ( tmp->images == NULL ) {
        CYAN_ERROR( ERR_MALLOC ) ;
        return NULL ;
    }

    for ( i=0; i<buffer_size; i++ ) {
        tmp->images[i] = image_new( cols, rows, mono ) ;
        if ( tmp->images[i] == NULL ) {
            CYAN_ERROR( ERR_MALLOC ) ;
            return NULL ;
        }
        tmp->fifo1[i] = tmp->images[i] ;
    }

    tmp->head1 = 0 ;
    tmp->size1 = buffer_size ;
    tmp->head2 = 0 ;
    tmp->size2 = 0 ;
    
    pthread_mutex_init(&(tmp->mutex1), NULL) ;
    pthread_mutex_init(&(tmp->mutex2), NULL) ;

    return tmp ;
}

void imqueue_free( imqueue_t* queue ) {
    int i ;
    for( i=0; i<queue->buffer_size; i++ ) {
        image_free( queue->images[i] ) ;
    }

    free( queue->images ) ;
    free( queue->fifo1 ) ;
    free( queue->fifo2 ) ;
    free( queue ) ;

}

int imqueue_cam_push( imqueue_t* queue, image_t* img) {
    pthread_mutex_lock( &(queue->mutex2) ) ;
    if (  queue->size2 + 1 > queue->buffer_size ) {
        CYAN_ERROR( ERR_FULL ) ;
        pthread_mutex_unlock( &(queue->mutex2) ) ;
        return ERR_FULL ;
    }
    queue->fifo2[(queue->head2+queue->size2) % (queue->buffer_size)] = img ;
    queue->size2 += 1 ;
    pthread_mutex_unlock( &(queue->mutex2) ) ;
    return ERR_OK ;
}

int imqueue_cam_pop(  imqueue_t* queue, image_t** img ) {
    pthread_mutex_lock( &(queue->mutex1) ) ;
    if ( queue->size1 <= 0 ) {
        CYAN_ERROR( ERR_EMPTY ) ;
        pthread_mutex_unlock( &(queue->mutex1) ) ;
        return ERR_EMPTY ;
    }
    *img = queue->fifo1[ queue->head1 ] ;
    queue->head1 = ( queue->head1 + 1 ) % ( queue->buffer_size) ;
    queue->size1 -=1 ;
    pthread_mutex_unlock( &(queue->mutex1) ) ;
    return ERR_OK ;
}

int imqueue_client_push( imqueue_t* queue, image_t* img) {
    pthread_mutex_lock( &(queue->mutex1) ) ;
    if (  queue->size1 + 1 > queue->buffer_size ) {
        CYAN_ERROR( ERR_FULL ) ;
        pthread_mutex_unlock( &(queue->mutex1) ) ;
        return ERR_FULL ;
    }
    queue->fifo1[(queue->head1+queue->size1) % (queue->buffer_size)] = img ;
    queue->size1 += 1 ;
    pthread_mutex_unlock( &(queue->mutex1) ) ;
    return ERR_OK ;
}

int imqueue_client_pop(  imqueue_t* queue, image_t** img ) {
    pthread_mutex_lock( &(queue->mutex2) ) ;
    if ( queue->size2 <= 0 ) {
        CYAN_ERROR( ERR_EMPTY ) ;
        pthread_mutex_unlock( &(queue->mutex2) ) ;
        return ERR_EMPTY ;
    }
    *img = queue->fifo2[ queue->head2 ] ;
    queue->head2 = ( queue->head2 + 1 ) % ( queue->buffer_size) ;
    queue->size2 -=1 ;
    pthread_mutex_unlock( &(queue->mutex2) ) ;
    return ERR_OK ;
}

