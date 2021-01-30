
#include "queue.h"

queue_t *createQueue(int queueSize){
    queue_t *queue = (queue_t *) malloc(sizeof(queue_t));
    if(!queue){
        return NULL;
    }

    queue->numOfVertices = queueSize;
    queue->front = 0;
    queue->rear = -1;
    queue->currItemCount = 0;

    queue->array = calloc(queueSize, sizeof(int));
    if(!queue->array){
        return NULL;
    }

    return queue;
}

void insertQueue(queue_t *queue, int value){
    queue->array[++queue->rear] = value;
    queue->currItemCount++;
}

int removeQueue(queue_t *queue){
    queue->currItemCount--;
    return queue->array[queue->front++];
}

bool isQueueEmpty(queue_t *queue){
    return queue->currItemCount == 0;
}

void freeQueue(queue_t *queue){
    free(queue->array);
    free(queue);
}
