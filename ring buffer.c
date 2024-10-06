#include <stdio.h>
#include"ring Buffer.h"
#include"stdint.h"

void buffer_setup(Ring_buf_t* rb, int* buffer, long size )
{
    rb->buffer = buffer;
    rb->read_index = 0;
    rb->write_index = 0;
    rb->mask = size - 1;

}

int buffer_empty(Ring_buf_t* rb)
{
  return rb->read_index == rb->write_index;
}

int buffer_read(Ring_buf_t* rb, int* byte)
{
//Local var used so that multiple users can read data simultaneously
//This program is made keeping is mind multiple readers not multiple publishers
    long local_read_index = rb->read_index;
    long local_write_index = rb->write_index;

    if (local_read_index == local_write_index)
        return 1 ;

    *byte = rb->buffer[local_read_index];
    local_read_index = (local_read_index + 1) & rb->mask;
    rb->read_index = local_read_index;
    return 0;
}

int buffer_write(Ring_buf_t* rb, int* byte)
{
    long local_read_index = rb->read_index;
    long local_write_index = rb->write_index;

    long next_write_index = (local_write_index + 1) & rb->mask;

    if (next_write_index == local_read_index)
    {
        return 1;
    }

    rb->buffer[local_write_index] = byte;
    rb->write_index = next_write_index;
    return 0;
}


