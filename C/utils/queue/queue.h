
#include "../../standardHeaders.h"

typedef struct queue{
    int front;
    int rear;
    int numOfVertices;
    int currItemCount;
    int *array;
}queue_t;

void insertQueue(queue_t *queue, int value);
int removeQueue(queue_t *queue);
bool isQueueEmpty(queue_t *queue);
queue_t *createQueue(int queueSize);
