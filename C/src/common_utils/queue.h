#include "common.h"

typedef struct queue{
    int *queueArr;
    int queueSize;
    int front;
    int rear;
    int queueItemCount;
}queue_t;

queue_t *createQueue(int queueSize);
void queueEnqueue(queue_t *queue, int data);
int queueDequeue(queue_t *queue);
void destroyQueue(queue_t *queue);
bool isQueueEmpty(queue_t *queue);
bool isQueueFull(queue_t *queue);
