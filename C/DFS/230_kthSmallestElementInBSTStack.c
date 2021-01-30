/*
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Example 1:

Input: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
Output: 1

Example 2:

Input: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
Output: 3

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? 
How would you optimize the kthSmallest routine?

Constraints:

The number of elements of the BST is between 1 to 10^4.
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.
*/

#include "../standardHeaders.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode_t;

typedef struct stackt{
    struct TreeNode **stackArr;
    int top;
    int stackSize;
}stackt_t;

bool isStackEmpty(stackt_t *stack){
    return stack->top == -1;
}

bool isStackFull(stackt_t *stack){
    return stack->top == stack->stackSize;
}

stackt_t *createStack(int stackSize){
    stackt_t *stack = (stackt_t *) malloc(sizeof(stackt_t));
    if(!stack)  return NULL;
    stack->top = -1;
    stack->stackSize = stackSize;
    stack->stackArr = (struct TreeNode **) malloc(sizeof(struct TreeNode *)*stackSize);
    if(!stack->stackArr)    return NULL;
    return stack;
}

bool stackPush(stackt_t *stack, struct TreeNode *node){
    if(!isStackFull(stack)){
        stack->stackArr[++stack->top] = node;
        return true;
    }
    else{
        return false;
    }
}

struct TreeNode *stackPop(stackt_t *stack){
    if(!isStackEmpty(stack)){
        return stack->stackArr[stack->top--];
    }
    else{
        return NULL;
    }
}

void freeStack(stackt_t *stackt){
    free(stackt->stackArr);
    free(stackt);
}

int kthSmallest(struct TreeNode* root, int k){
    if(!root)   return -1;
    
    // create stack
    stackt_t *stack = createStack(100);
    if(!stack)  return -1;
    
    bool done = false;
    
    // iterate in-order
    // in-order traversal leaves binary tree in a sorted manner
    while(!done){
        // push left node if available
        if(root){
            stackPush(stack, root);
            // next node to be pushed is also left
            root = root->left;
        }
        else{
            // when reached NULL at left node, pop last node
            if(!isStackEmpty(stack)){
                root = stackPop(stack);
                // if current element is kth element, just return it
                if(--k == 0){
                    free(stack);
                    return root->val;
                }
                // it current element is not kth element, go to right of current node
                root = root->right;
            }
            else{
                // if stack is empty, stop, we've traversed all elements
                done = true;
            }
        }
    }
    
    free(stack);
    return -1;
}

/*
Sample inputs to test:
[1]
1

[5,3,6,2,4,null,null,1]
3

[1,null,2]
2

[3,1,4,null,2]
1
*/