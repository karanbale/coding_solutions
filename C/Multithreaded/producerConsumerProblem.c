/*

*/

#include "../standardHeaders.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE         5   // Size of the buffer
#define MAX_ITEM_SIZE       5   // Max items producer can produce
#define MAX_PRODUCER_COUNT  5
#define MAX_CONSUMER_COUNT  5

// create two semaphores
sem_t empty, full;

// create a mutex for the shared buffer
pthread_mutex_t mutex;

// create shared resource
static int buffer[BUFFER_SIZE];
int producer_buffer_index = 0;
int consumer_buffer_index = 0;

void *producer(void *vargs) {
    int item;
    // run for loop to produce MAX_ITEM_SIZE resources
    for (int i=0; i<MAX_ITEM_SIZE; i++) {
        // create random item value
        item = rand();
        // wait for buffer to be empty ==> semaphore
        sem_wait(&empty);
        // acquire mutex on the buffer
        pthread_mutex_lock(&mutex);
        // produce resource and store in buffer
        buffer[producer_buffer_index] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)vargs),buffer[producer_buffer_index],producer_buffer_index);
        // increment counter
        producer_buffer_index = (producer_buffer_index+1) % BUFFER_SIZE;
        // release mutex
        pthread_mutex_unlock(&mutex);
        // post the semaphore
        sem_post(&full);
    }
}

void *consumer(void *vargs) {
    // Run for loop to consume resources
    for(int i=0; i<MAX_ITEM_SIZE; i++) {
        // wait for resource to be produced => check if full
        sem_wait(&full);
        // acquire mutex on the buffer
        pthread_mutex_lock(&mutex);
        // consume resource
        int item = buffer[consumer_buffer_index];
        printf("Consumer %d: Remove Item %d at %d\n", *((int *)vargs),buffer[consumer_buffer_index],consumer_buffer_index);
        // increment the counter
        consumer_buffer_index = (consumer_buffer_index+1) % BUFFER_SIZE;
        // release mutex
        pthread_mutex_unlock(&mutex);
        // post semaphore
        sem_post(&empty);
    }
}

int main(void) {
    // define threads for producer and consumer
    pthread_t producer[MAX_PRODUCER_COUNT];
    pthread_t consumer[MAX_CONSUMER_COUNT];
    // define some thread IDs
    int thread_id[MAX_PRODUCER_COUNT] = {1, 2, 3, 4, 5};
    // initialize mutex
    pthread_mutex_init(&mutex, NULL);
    // initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    // create producer threads
    for(int i=0; i<MAX_PRODUCER_COUNT; i++) {
        pthread_create(&producer[i], NULL, (void *)producer, (void *)&thread_id[i]);
    }
    // create consumer threads
    for(int i=0; i<MAX_CONSUMER_COUNT; i++) {
        pthread_create(&consumer[i], NULL, (void *)consumer, (void *)&thread_id[i]);
    }
    // wait for producer threads to finish
    for(int i=0; i<MAX_PRODUCER_COUNT; i++) {
        pthread_join(producer[i], NULL);
    }
    // wait for consumer threads to finish
    for(int i=0; i<MAX_CONSUMER_COUNT; i++) {
        pthread_join(consumer[i], NULL);
    }
    // destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    // destroy mutex
    pthread_mutex_destroy(&mutex);
}
