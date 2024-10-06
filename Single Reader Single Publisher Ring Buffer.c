#include <stdint.h>  // For uint8_t type
#include <stdbool.h> // For bool type

// Define the size of the ring buffer
#define BUFFER_SIZE 8

// Structure definition for the ring buffer
typedef struct {
    uint8_t buffer[BUFFER_SIZE];  // Array to store buffer data
    uint8_t head;                 // Index for the next write position
    uint8_t tail;                 // Index for the next read position
} RingBuffer;

// Initialize the ring buffer (reset head and tail)
void RingBuffer_Init(RingBuffer *rb) {
    rb->head = 0;  // Initialize head to 0
    rb->tail = 0;  // Initialize tail to 0
}

// Check if the ring buffer is full
bool RingBuffer_IsFull(RingBuffer *rb) {
    // Buffer is full when the next position to write is the tail
    return ((rb->head + 1) % BUFFER_SIZE) == rb->tail;
}

// Check if the ring buffer is empty
bool RingBuffer_IsEmpty(RingBuffer *rb) {
    // Buffer is empty when head and tail point to the same position
    return rb->head == rb->tail;
}

// Write a byte to the ring buffer
bool RingBuffer_Write(RingBuffer *rb, uint8_t data) {
    // First, check if the buffer is full
    if (RingBuffer_IsFull(rb)) {
        return false;  // Return false if buffer is full, cannot write
    }

    // Write the data at the current head position
    rb->buffer[rb->head] = data;

    // Move head to the next position (wrap around using modulo)
    rb->head = (rb->head + 1) % BUFFER_SIZE;

    return true;  // Return true to indicate success
}

// Read a byte from the ring buffer
bool RingBuffer_Read(RingBuffer *rb, uint8_t *data) {
    // First, check if the buffer is empty
    if (RingBuffer_IsEmpty(rb)) {
        return false;  // Return false if buffer is empty, nothing to read
    }

    // Read the data from the current tail position
    *data = rb->buffer[rb->tail];

    // Move tail to the next position (wrap around using modulo)
    rb->tail = (rb->tail + 1) % BUFFER_SIZE;

    return true;  // Return true to indicate success
}

// Example usage
#include <stdio.h>

int main() {
    RingBuffer rb;  // Declare a ring buffer instance
    uint8_t data;   // Variable to hold read data

    // Initialize the ring buffer
    RingBuffer_Init(&rb);

    // Write some data to the buffer
    for (uint8_t i = 0; i < 5; i++) {
        if (RingBuffer_Write(&rb, i)) {
            printf("Wrote: %d\n", i);
        } else {
            printf("Buffer is full, cannot write: %d\n", i);
        }
    }

    // Read the data from the buffer
    while (RingBuffer_Read(&rb, &data)) {
        printf("Read: %d\n", data);
    }

    return 0;
}
