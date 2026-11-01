#include <assert.h>
#include <stdio.h>

#include "../ring_buffer/ring_buffer.h"

#define CAPACITY 3U

int main(void)
{
    struct ring_buffer rb;
    int16_t storage[CAPACITY];
    int16_t value = 0;

    /* Test initialization. */
    assert(rb_init(&rb, storage, CAPACITY) == RB_OK);
    assert(rb_is_empty(&rb));
    assert(rb_size(&rb) == 0U);

    /* Test invalid initialization. */
    assert(rb_init(NULL, storage, CAPACITY) == RB_INVALID);
    assert(rb_init(&rb, NULL, CAPACITY) == RB_INVALID);
    assert(rb_init(&rb, storage, 0U) == RB_INVALID);

    /* An empty buffer must reject pop. */
    assert(rb_pop(&rb, &value) == RB_EMPTY);

    /* Fill the buffer. */
    assert(rb_push(&rb, 10) == RB_OK);
    assert(rb_push(&rb, 20) == RB_OK);
    assert(rb_push(&rb, 30) == RB_OK);

    assert(rb_is_full(&rb));
    assert(rb_size(&rb) == CAPACITY);

    /* Full-buffer policy: reject the newest item. */
    assert(rb_push(&rb, 40) == RB_FULL);
    assert(rb_size(&rb) == CAPACITY);

    /* FIFO order: oldest values come out first. */
    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 10);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 20);

    /* Wraparound: head advances past the end. */
    assert(rb_push(&rb, 40) == RB_OK);
    assert(rb_push(&rb, 50) == RB_OK);
    assert(rb_is_full(&rb));

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 30);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 40);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 50);

    assert(rb_is_empty(&rb));
    assert(rb_size(&rb) == 0U);

    /* Invalid output pointer. */
    assert(rb_pop(&rb, NULL) == RB_INVALID);

    puts("PASS: all ring buffer tests completed.");
    return 0;
}