/*
Given the root of a binary tree, return the postorder traversal of its nodes' values.

Example 1:
Input: root = [1,null,2,3]
Output: [3,2,1]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]

Example 4:
Input: root = [1,2]
Output: [2,1]

Example 5:
Input: root = [1,null,2]
Output: [2,1]
 
Constraints:

The number of the nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100

Follow up:

Recursive solution is trivial, could you do it iteratively?
*/

#include "../standardHeaders.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct stackt{
    struct TreeNode **arr;
    int stackSize;
    int top;
}stack_T;

bool isStackFull(stack_T *stackt){
    return stackt->top == stackt->stackSize;
}

bool isStackEmpty(stack_T *stackt){
    return stackt->top == -1;
}

stack_T *createStack(int stackSize){
    stack_T *stackt = (stack_T *) malloc(sizeof(struct stackt));
    if(!stackt)  return NULL;
    stackt->arr = (struct TreeNode **) malloc(sizeof(struct TreeNode)*stackSize);
    if(!stackt->arr) return NULL;
    stackt->stackSize = stackSize;
    stackt->top = -1;
    return stackt;
}

bool stackPush(stack_T *stackt, struct TreeNode *node){
    if(isStackFull(stackt))  return false;
    stackt->arr[++stackt->top] = node;
    return true;
}

struct TreeNode *stackPop(stack_T *stackt){
    if(isStackEmpty(stackt)) return NULL;
    return stackt->arr[stackt->top--];
}

void freeStack(stack_T *stackt){
    free(stackt->arr);
    free(stackt);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorderTraversal(struct TreeNode* root, int* returnSize){
    *returnSize = 0;
    if(!root)   return 0;
    int *retArr = (int *) malloc(sizeof(int));
    if(!retArr) return NULL;
    stack_T *stackt = createStack(100);
    if(!stackt)  return NULL;
    
    stackPush(stackt, root);
    while(!isStackEmpty(stackt)){
        struct TreeNode *node = stackPop(stackt);
        (*returnSize)++;
        int newSize = ((*returnSize)+1)*sizeof(int);
        retArr = realloc(retArr, newSize);
        retArr[(*returnSize)-1] = node->val;
        if(node->left){
            stackPush(stackt, node->left);
        }
        if(node->right){
            stackPush(stackt, node->right);
        }
    }
    
    // simply revert the output of in-order traversal
    int *tempRetArr = (int *) malloc((*returnSize)*sizeof(int));
    for(int i=(*returnSize)-1; i>=0; i--){
        tempRetArr[(*returnSize)-1-i] = retArr[i];
    }
    free(retArr);
    freeStack(stackt);
    return tempRetArr;
}