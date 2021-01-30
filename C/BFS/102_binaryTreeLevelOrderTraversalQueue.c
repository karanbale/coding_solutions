/*
Given a binary tree, return the level order traversal of its nodes' values.
(ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]

*/

#include "../standardHeaders.h"

struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode_t;

#define SIZE 1100

typedef struct _queue{
    struct TreeNode **node;
    int queueSize;
    int queueItemCount;
    int front;
    int rear;
}queue_t;

queue_t *createQueue(int queueSize){
    queue_t *queue = (queue_t *) malloc(sizeof(queue_t));
    if(!queue)  return NULL;
    queue->node = (struct TreeNode **) malloc(sizeof(struct TreeNode *)*queueSize);
    for(int i=0; i<queueSize; i++){
        queue->node[i] = NULL;
    }
    queue->front = 0;
    queue->rear = -1;
    queue->queueSize=queueSize;
    queue->queueItemCount=0;
    return queue;
}

bool isQueueEmpty(queue_t *queue){
    return queue->queueItemCount == 0;
}

void queueEnqueue(queue_t *queue, struct TreeNode *node){
    queue->node[++queue->rear] = node;
    queue->queueItemCount++;
}

struct TreeNode *queueDequeue(queue_t *queue){
    if(isQueueEmpty(queue)) return NULL;
    queue->queueItemCount--;
    return queue->node[queue->front++];
}

void freeQueue(queue_t *queue){
    if(!isQueueEmpty(queue)){
        for(int i=0; i<queue->queueSize; i++){
            free(queue->node[i]);
        }
    }
    free(queue);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    if (!root) {
        *returnColumnSizes = NULL;
        return NULL;
    }
    int **returnArray = (int **) malloc(sizeof(int*) * 1000);
    if (!returnArray) {
        exit(0);
    }
    *returnColumnSizes = (int *) malloc(sizeof(int) * 1000);

    queue_t *queue = createQueue(SIZE);
    if (!queue) {
        exit(0);
    }
    
    queueEnqueue(queue, root);
    int level = 0;
    while(!isQueueEmpty(queue)){
        level = queue->queueItemCount;
        int levelItemCount = 0;
        returnArray[*returnSize] = (int *) malloc(sizeof(int)*level);
        // iterate over all items in queue, pop them and add their kids to queue
        // until queue is empty
        while(level > levelItemCount){
            struct TreeNode *node = queueDequeue(queue);
            returnArray[*returnSize][levelItemCount++] = node->val;
            if(node->left){
                queueEnqueue(queue, node->left);
            }
            if(node->right){
                queueEnqueue(queue, node->right);
            }
        }
        (*returnColumnSizes)[(*returnSize)++] = level;
    }
    free(queue);
    return returnArray;
}