/**
 * Inspriation: https://github.com/tmick0/toy-queue
 * Blog post: https://lo.calho.st/posts/black-magic-buffer/
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>

#include <linux/memfd.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <sys/types.h>

#define SUCCESS (0)
#define BUFFER_SIZE (getpagesize())
#define NUM_OF_THREADS (5)
#define MESSAGES_PER_THREAD (getpagesize() * 2)

sem_t _queue_empty, _queue_full;
mutex_t _mutex_buff;

typedef struct {
    void *bufferPtr;
    size_t bufferSize;
    uint32_t head;
    uint32_t tail;
    uint32_t fd;
} queue_t;

bool init(queue_t *queue, size_t size) {
    
    if(SUCCESS != getpagesize() % size) {
        return false;
    }
    // physical region for queue
    if (SUCCESS != (queue->fd = memfd_create("queue_region", 0))) {
        return false;
    }
    // set queue size
    if(SUCCESS != ftruncate(queue->fd, size)) {
        return false;
    }
    // get virtual space
    if(MAP_FAILED == (queue->bufferPtr = mmap(NULL, 2*size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0))) {
        return false;
    }
    // map virtual space 1 to queue
    if(MAP_FAILED == mmap(queue->bufferPtr, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, queue->fd, 0)) {
        return false;
    }
    // map virtual space 2 to queue
    if(MAP_FAILED == mmap((queue->bufferPtr + size), size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, queue->fd, 0)) {
        return false;
    }
    
    queue->head = 0;
    queue->tail = 0;
    queue->size = size;
    
}

static inline int getValidBytes(queue_t *queue, size_t size) {
    return (queue->head - queue->tail);
}

static inline int getAvailableBytes(queue_t *queue, size_t size) {
    return (queue->size - getValidBytes(queue, size));
}

void enqueue(queue_t *queue, uint8_t *buffer, size_t size) {
    // error condition
    if(getAvailableBytes(queue, size) < queue->size) {
        return;
    }
    // wait for semaphore
    sem_wait(&_queue_empty);
    // lock mutex
    pthread_mutex_lock(&_mutex_buff);
    memcpy(&queue->bufferPtr[queue->head], buffer, size);
    printf("queue current data: %ld\n", buffer);
    queue->head += size;
    // unlock mutex
    pthread_mutex_unlock(&_mutex_buff);
    // signal semaphore
    sem_post(&_queue_full);
}

bool dequeue(queue_t *queue, uint8_t *buffer, size_t size) {
    // wait for semaphore
    sem_wait(_queue_full);
    // error condition
    if(getValidBytes(queue, size) < queue->size) {
        // release semaphore
    }
    // lock mutex
    pthread_mutex_lock(&_mutex_buff);
    memcpy(buffer, &queue->bufferPtr[queue->tail], size);
    printf("dequeue current data: %ld\n", buffer);
    queue->tail += size;
    if(queue->size >= queue->tail) {
        queue->head -= queue->size;
        queue->tail -= queue->size;
    }
    // unlock mutex
    pthread_mutex_unlock(&_mutex_buff);
    // signal semaphore
    sem_post(_queue_empty);
    return true;
}

void *producer(void *arg) {
    queue_t *q = (queue_t *)arg;
    size_t i;
    for(i = 0; i< NUM_OF_THREADS * MESSAGES_PER_THREAD; i++) {
        enqueue(q, (uint8_t *)&i, sizeof(size_t));
    }
    return (void *)i;
}

void *consumer(void *arg) {
    queue_t *q = (queue_t *) arg;
    size_t count = 0;
    size_t i;
    for(i = 0; i < MESSAGES_PER_THREAD; i++){
        size_t x;
        dequeue(q, (uint8_t *) &x, sizeof(size_t));
        count++;
    }
    return (void *) count;
}

int main(void)
{
    queue_t q;
    queue_init(&q, BUFFER_SIZE);

    sem_init(&_queue_empty, 0, 1);
    sem_init(&_queue_full, 0, 0);
    pthread_mutex_init(&_mutex_buff, NULL);
    
    pthread_t producer;
    pthread_t consumer[NUM_OF_THREADS];
    
    pthread_create(&producer, 0, &producer, (void *)&q);
    
    sem_destroy(&_queue_empty);
    sem_destroy(&_queue_full);
    pthread_mutex_destroy(&_mutex_buff);
    
    return 0;
}

