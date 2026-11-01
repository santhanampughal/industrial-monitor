#include "ring_buffer.h"

enum rb_status rb_init(struct ring_buffer *rb, int16_t *storage, size_t capacity)
{
    if (rb == NULL || storage == NULL || capacity == 0U) {
        return RB_INVALID;
    }

    rb->data = storage;
    rb->capacity = capacity;
    rb->head = 0U;
    rb->tail = 0U;
    rb->count = 0U;
    return RB_OK;
}

enum rb_status rb_push(struct ring_buffer *rb, int16_t value)
{
    if (rb == NULL || rb->data == NULL || rb->capacity == 0U) {
        return RB_INVALID;
    }

    if (rb->count == rb->capacity) {
        return RB_FULL;
    }

    rb->data[rb->head] = value;
    rb->head = (rb->head + 1U) % rb->capacity;
    rb->count++;
    return RB_OK;
}

enum rb_status rb_pop(struct ring_buffer *rb, int16_t *value)
{
    if (rb == NULL || rb->data == NULL ||
        rb->capacity == 0U || value == NULL) {
        return RB_INVALID;
    }

    if (rb->count == 0U) {
        return RB_EMPTY;
    }

    *value = rb->data[rb->tail];
    rb->tail = (rb->tail + 1U) % rb->capacity;
    rb->count--;
    return RB_OK;
}

bool rb_is_empty(const struct ring_buffer *rb)
{
    return rb == NULL || rb->count == 0U;
}

bool rb_is_full(const struct ring_buffer *rb)
{
    return rb != NULL &&
           rb->capacity > 0U &&
           rb->count == rb->capacity;
}

size_t rb_size(const struct ring_buffer *rb)
{
    return rb == NULL ? 0U : rb->count;
}
