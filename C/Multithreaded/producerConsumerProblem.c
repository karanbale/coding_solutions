/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define BUFFER_SIZE 5
#define PRODUCER_SIZE 2
#define CONSUMER_SIZE 2

// mutex for shared resource
pthread_mutex_t mutex;
// semaphore for signalling
sem_t empty, full;
// shared resource
static int buffer[BUFFER_SIZE];

uint8_t producer_index = 0;
uint8_t consumer_index = 0;

void get_sem_value(void *msg) {
    printf("%s\n", (char *)msg);
    int sem_value;
    sem_getvalue(&full, &sem_value);
    printf("\tCurrent FULL sem_value: %d\n", sem_value);
    sem_getvalue(&empty, &sem_value);
    printf("\tCurrent EMPTY sem_value: %d\n", sem_value);
}

void *producer(void *varg) {
    // make sure seed for rand() is different each time
    srand(time(0));
    for(int i=0; i<BUFFER_SIZE; i++) {
        // wait for buffer to be empty
        sem_wait(&empty);
        // read and print current semaphore value
        get_sem_value("Producer");
        // acquire mutex
        pthread_mutex_lock(&mutex);
        // fill up the buffer
        int item = rand();
        buffer[producer_index] = item;
        printf("\tProducer: %ld, produced item: %d at index: %d. \n", (uintptr_t)varg, item, producer_index);
        // advance the PRODUCER_INDEX
        producer_index = (producer_index+1) % BUFFER_SIZE;
        // release mutex
        pthread_mutex_unlock(&mutex);
        // singal buffer is full i.e. there is item for consumer to consume
        sem_post(&full);
    }
}

void *consumer(void *varg) {
    for(int i=0; i<BUFFER_SIZE; i++) {
        // wait for buffer to be empty
        sem_wait(&full);
        // read and print current semaphore value
        get_sem_value("Consumer");
        // acquire mutex
        pthread_mutex_lock(&mutex);
        // fill up the buffer
        int item = buffer[consumer_index];
        printf("\tConsumer: %ld, consumed item: %d at index: %d. \n", (uintptr_t)varg, item, consumer_index);
        // advance the PRODUCER_INDEX
        consumer_index = (consumer_index+1) % BUFFER_SIZE;
        // release mutex
        pthread_mutex_unlock(&mutex);
        // singal buffer is full i.e. there is item for consumer to consume
        sem_post(&empty);
    }
}

int main()
{
    printf("Hello World\n");

    pthread_t producer_t[PRODUCER_SIZE];
    pthread_t consumer_t[CONSUMER_SIZE];

    int prod_thread_id = 1, cons_thread_id = 1;

    // init mutex
    pthread_mutex_init(&mutex, NULL);

    // init semaphore
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // create threads for producer
    for(int i=0; i<PRODUCER_SIZE; i++) {
        pthread_create(&producer_t[i], NULL, &producer, (void *)&prod_thread_id);
        prod_thread_id++;
    }
    // create threads for consumer
    for(int i=0; i<CONSUMER_SIZE; i++) {
        pthread_create(&consumer_t[i], NULL, &consumer, (void *)&cons_thread_id);
        cons_thread_id++;
    }

    // wait to join producer
    for(int i=0; i<PRODUCER_SIZE; i++) {
        pthread_join(producer_t[i], NULL);
    }
    // wait to join consumer
    for(int i=0; i<CONSUMER_SIZE; i++) {
        pthread_join(consumer_t[i], NULL);
    }
    // destroy semaphore
    sem_destroy(&empty);
    sem_destroy(&full);
    // destroy mutex
    pthread_mutex_destroy(&mutex);
    return 0;
}
