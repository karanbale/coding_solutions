/*
In a binary tree, the root node is at depth 0, and children of each depth k node are at depth k+1.

Two nodes of a binary tree are cousins if they have the same depth, but have different parents.

We are given the root of a binary tree with unique values, and the values x and y of two different nodes in the tree.

Return true if and only if the nodes corresponding to the values x and y are cousins.

Example 1:
Input: root = [1,2,3,4], x = 4, y = 3
Output: false

Example 2:
Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
Output: true

Example 3:
Input: root = [1,2,3,null,4], x = 2, y = 3
Output: false
 

Constraints:

The number of nodes in the tree will be between 2 and 100.
Each node has a unique integer value from 1 to 100.
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
    queue_t *queue = (queue_t *) malloc(sizeof(struct queue));
    queue->front = NULL;
    queue->rear = NULL;
    if(!queue)  return NULL;
    queue->queueItemCount = 0;
    return queue;
}

void queueEnqueue(queue_t *queue, struct TreeNode *node){
    if(!queue->front){
        queue->front = (struct queueNode *) malloc(sizeof(struct queueNode));
        if(!queue->front)   return;
        queue->front->node = node;
        queue->front->next = NULL;
        queue->rear = queue->front;
    }
    else{
        queue->rear->next = (struct queueNode *) malloc(sizeof(struct queueNode));
        if(!queue->rear)   return;
        queue->rear = queue->rear->next;
        queue->rear->node = node;
        queue->rear->next = NULL;
    }
    queue->queueItemCount++;
}

struct TreeNode *queueDequeue(queue_t *queue){
    if(!queue->front){
        return 0;
    }
    queueNode_t *tempQueueNode = queue->front;
    struct TreeNode *tempNode = tempQueueNode->node;
    queue->front = queue->front->next;
    if(queue->front == NULL){
        queue->rear = NULL;
    }
    free(tempQueueNode);
    queue->queueItemCount--;
    return tempNode;
}

bool isQueueEmpty(queue_t *queue){
    return queue->queueItemCount == 0;
}

void destroyQueue(queue_t *queue){
    if(!queue->front){
        return;
    }
    else if(!queue->front->next){
        free(queue->front);
    }
    else{
        while(queue->front != queue->rear){
            queueNode_t *tempQueueNode = queue->front;
            queue->front = queue->front->next;
            free(tempQueueNode);
        }
        free(queue->front);
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->queueItemCount = 0;
    free(queue);
}

// take a node, to track parents of x and y
typedef struct trackNode{
    int parentNodeVal;
    int searchNodeVal;
    int nodeLevel;
}trackNode_t;

bool isCousins(struct TreeNode* root, int x, int y){
    // => BFS On entire tree
    // => if node->left && node->right contain x and y, return
    // if node->left == x or y, store level as xLevel
    // compare xLevel against yLevel
    // if node->right == x or y store level as yLevel
    // compare yLevel against xLevel
    // if xLevel == yLevel && xLevel != -1 && yLevel != -1, return true
    // return false
    
    if(!root)   return false;
    
    // initialize the node with -1 values for parents
    trackNode_t xT;
    xT.parentNodeVal = -1;
    xT.searchNodeVal = x;
    xT.nodeLevel = -1;
    trackNode_t yT;
    yT.parentNodeVal = -1;
    yT.searchNodeVal = y;
    yT.nodeLevel = -1;
    
    // create queue and add root node to it
    queue_t *queue = createQueue();
    queueEnqueue(queue, root);

    int level = 0;
    // int xLevel = -1, yLevel = -1;
    while(!isQueueEmpty(queue)){
        level++;
        int parentItemCount = queue->queueItemCount;
        while(parentItemCount){
            struct TreeNode *node = queueDequeue(queue);
            if(node->left){
                // check if left node matches x or y
                if(node->left->val == x){
                    xT.nodeLevel = level;
                    xT.parentNodeVal = node->val;
                }
                else if(node->left->val == y){
                    yT.nodeLevel = level;
                    yT.parentNodeVal = node->val;
                }
                queueEnqueue(queue, node->left);
            }
            if(node->right){
                // check if right node matches x or y
                if(node->right->val == x){
                    xT.parentNodeVal = node->val;
                    xT.nodeLevel = level;
                }
                else if(node->right->val == y){
                    yT.parentNodeVal = node->val;
                    yT.nodeLevel = level;
                }
                queueEnqueue(queue, node->right);
            }

            // make sure we found parent nodes and xLevel / yLevels
            if((xT.nodeLevel != -1) && (yT.nodeLevel != -1) && (xT.parentNodeVal != -1) && (yT.parentNodeVal != -1)){
                // if parents of x and y are same, return false
                if(xT.parentNodeVal == yT.parentNodeVal){
                    destroyQueue(queue);
                    return false;
                }
                // if levels or x and y are same, but parents are not, return true
                else if(xT.nodeLevel == yT.nodeLevel){
                    destroyQueue(queue);
                    return true;
                }
            }
            parentItemCount--;
        }
    }
    
    // no match / valid case found, return false
    destroyQueue(queue);
    return false;
}

/*
Sample inputs to test:
[1,2,5,3,null,null,6,4]
x: 3
y: 6
output:
true

[1,2,3,null,4]
x: 2
y: 3
output:
false

[1,2,3,null,4,null,5]
x: 5
y: 4
output:
true

[1,2,3,4]
x: 4
y: 3
output:
false

*/