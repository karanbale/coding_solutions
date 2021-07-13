#include "queue.h"

bool isQueueEmpty(queue_t *queue) {
    return queue->queueItemCount == 0;
}

bool isQueueFull(queue_t *queue) {
    return queue->queueItemCount == queue->queueSize;
}

queue_t *createQueue(int queueSize) {
    queue_t *queue =(queue_t *) malloc(sizeof(queue_t));
    if(!queue)    return NULL;
    queue->queueArr = (int *) malloc(sizeof(int)*queueSize);
    if(!queue->queueArr)    return NULL;
    queue->front = 0;
    queue->queueItemCount = 0;
    queue->rear = -1;
    queue->queueSize = queueSize;
    return queue;
}

void queueEnqueue(queue_t *queue, int data) {
    if(isQueueFull(queue)) return;
    queue->queueArr[++queue->rear] = data;
    queue->queueItemCount++;
}

int queueDequeue(queue_t *queue) {
    if(isQueueEmpty(queue))    return 0;
    queue->queueItemCount--;
    return queue->queueArr[queue->front++];
}

void destroyQueue(queue_t *queue) {
    free(queue->queueArr);
    free(queue);
}
