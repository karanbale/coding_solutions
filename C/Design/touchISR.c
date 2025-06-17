/*
This implementation achieves following things
✅ Bounded ring buffer (drops samples when full)
✅ Semaphore only posted when a sample is successfully enqueued
✅ Thread-safe and portable
✅ Efficient and safe under producer > consumer rate
*/

#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define RING_BUFFER_SIZE 16

typedef struct {
    uint16_t x;
    uint16_t y;
} touch_point_t;

typedef struct {
    touch_point_t buffer[RING_BUFFER_SIZE];
    int head;
    int tail;
    int count;
    pthread_mutex_t lock;
} touch_ring_buffer_t;

touch_ring_buffer_t touch_rb;
sem_t touch_sem;

/*
##################################################################
################### RING BUFFER IMPLEMENTATION ###################
##################################################################
*/
void ring_buffer_init(touch_ring_buffer_t *rb) {
    rb->head = rb->tail = rb->count = 0;
    pthread_mutex_init(&rb->lock, NULL);
}

// Returns true if data was enqueued, false if dropped
bool ring_buffer_push(touch_ring_buffer_t *rb, touch_point_t p) {
    pthread_mutex_lock(&rb->lock);

    if (rb->count == RING_BUFFER_SIZE) {
        // Buffer full: drop this sample
        pthread_mutex_unlock(&rb->lock);
        return false;
    }

    rb->buffer[rb->head] = p;
    rb->head = (rb->head + 1) % RING_BUFFER_SIZE;
    rb->count++;

    pthread_mutex_unlock(&rb->lock);
    return true;
}

bool ring_buffer_pop(touch_ring_buffer_t *rb, touch_point_t *p) {
    pthread_mutex_lock(&rb->lock);

    if (rb->count == 0) {
        pthread_mutex_unlock(&rb->lock);
        return false;
    }

    *p = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
    rb->count--;

    pthread_mutex_unlock(&rb->lock);
    return true;
}

/*
######################################################################
################### ISR & Deferred work / Producer ###################
######################################################################
*/

extern void touch_i2c_read(uint16_t *x, uint16_t *y);  // Provided
extern void schedule_touch_work(void);  // OS-specific deferred work trigger

void touch_isr(void) {
    schedule_touch_work();  // Schedule bottom-half
}

void touch_read_work(void) {
    uint16_t x, y;
    touch_i2c_read(&x, &y);

    touch_point_t point = { .x = x, .y = y };

    if (ring_buffer_push(&touch_rb, point)) {
        sem_post(&touch_sem);  // Only post if sample was stored
    } else {
        // Optional: log dropped sample
    }
}

/*
###########################################################
################### Consumer ###################
###########################################################
*/

extern void draw(int x, int y);  // Provided

void* draw_task(void *arg) {
    touch_point_t p;

    while (1) {
        sem_wait(&touch_sem);  // Wait for new touch input

        // Consume all available samples (may be >1)
        while (ring_buffer_pop(&touch_rb, &p)) {
            draw(p.x, p.y);  // Blocking until vsync
        }
    }

    return NULL;
}
