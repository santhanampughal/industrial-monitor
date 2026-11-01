#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct ring_buffer {
    int16_t *data;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t count;
};

enum rb_status {
    RB_OK = 0,
    RB_FULL,
    RB_EMPTY,
    RB_INVALID
};

/* Initialize using caller-owned storage. */
enum rb_status rb_init(
    struct ring_buffer *rb,
    int16_t *storage,
    size_t capacity
);

/* Add an item at the newest end. */
enum rb_status rb_push(
    struct ring_buffer *rb,
    int16_t value
);

/* Remove the oldest item. */
enum rb_status rb_pop(
    struct ring_buffer *rb,
    int16_t *value
);

bool rb_is_empty(const struct ring_buffer *rb);
bool rb_is_full(const struct ring_buffer *rb);
size_t rb_size(const struct ring_buffer *rb);

#endif