#ifndef RING_BUFFER_H
#define RING_BUFFER_H


typedef struct RingBuf 
{
int * buffer;
long  mask;
long read_index;
long write_index;
}Ring_buf_t ; 

void buffer_setup(Ring_buf_t* rb, int* buffer, long size );
int buffer_empty(Ring_buf_t* rb);
int buffer_read(Ring_buf_t* rb, int* byte);
int buffer_write(Ring_buf_t* rb, int* byte);





#endif