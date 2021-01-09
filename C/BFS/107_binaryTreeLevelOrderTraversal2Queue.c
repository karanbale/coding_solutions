/*
Given a binary tree, return the bottom-up level order traversal of its nodes' values.
(ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]
*/

#include "../standardHeaders.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct queueNode{
    struct TreeNode *node;
    struct queueNode *next;
}queueNode_t;

typedef struct queue{
    queueNode_t *front;
    queueNode_t *rear;
    int queueItemCount;
}queue_t;

queue_t *createQueue(void){
    queue_t *queue = malloc(sizeof(queue_t));
    queue->front = NULL;
    queue->rear = NULL;
    queue->queueItemCount = 0;
    return queue;
}

void queueEnqueue(queue_t *queue, struct TreeNode *node){
    if(!queue->front){
        queue->front = malloc(sizeof(struct queueNode));
        if(!queue->front)   return;
        queue->front->node = node;
        queue->front->next= NULL;
        queue->rear = queue->front;
    }
    else{
        queue->rear->next = malloc(sizeof(struct queueNode));
        if(!queue->rear->next)   return;
        queue->rear = queue->rear->next;
        queue->rear->node = node;
        queue->rear->next= NULL;
    }
    queue->queueItemCount++;
}

struct TreeNode *queueDequeue(queue_t *queue){
    if(!queue->front){
        return NULL;
    }
    queueNode_t *node = queue->front;
    struct TreeNode *retNode = node->node;
    queue->front = queue->front->next;
    if(!queue->front){
        queue->rear = NULL;
    }
    free(node);
    queue->queueItemCount--;
    return retNode;
}

bool isQueueEmpty(queue_t *queue){
    return queue->queueItemCount == 0;
}

void destroyQueue(queue_t *queue) {
    if (!queue->front) {
        return;
    } else if (!queue->front->next) {
        free(queue->front);
    } else {
        // QueueNode *queueNode = NULL;
        while (queue->front != queue->rear) {
            queueNode_t *queueNode = queue->front;
            queue->front = queue->front->next;
            free(queueNode);
        }
        free(queue->front);
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->queueItemCount = 0;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrderBottom(struct TreeNode* root, int* returnSize, int** returnColumnSizes){

    if(!root){
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    
    *returnSize = 0;
    int rowCount = 0;
    int **retArr = malloc(sizeof(int *)*1000);
    *returnColumnSizes = malloc(sizeof(int)*1000);
    queue_t *queue = createQueue();
    queueEnqueue(queue,root);
    int level[1000] = {0}, levelIdx = 0;
    while(!isQueueEmpty(queue)){
        int itemCount = 0;
        int itemAtCurrentLevel = queue->queueItemCount;
        level[levelIdx++] = queue->queueItemCount;
        retArr[rowCount] = malloc(sizeof(int)*itemAtCurrentLevel);
        if(!retArr[rowCount])    return NULL;
        while(itemAtCurrentLevel > itemCount){
            struct TreeNode *node = queueDequeue(queue);
            retArr[rowCount][itemCount++] = node->val;
            if(node->left){
                queueEnqueue(queue, node->left);
            }
            if(node->right){
                queueEnqueue(queue, node->right);
            }
        }
        rowCount++;
    }
    *returnSize = rowCount;
    destroyQueue(queue);
    free(queue);
    
    // reverse retArr
    int **tempRetArr = malloc(sizeof(int *)*1000);
    for(int i=rowCount-1; i>=0; i--){
        tempRetArr[rowCount-i-1] = malloc(sizeof(int)*level[i]);
        tempRetArr[rowCount-i-1] = retArr[i];
        (*returnColumnSizes)[rowCount-i-1] = level[i];
    }
    free(retArr);
    
    return tempRetArr;
}
