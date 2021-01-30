/*
Given two sequences pushed and popped with distinct values, return true if and only if 
this could have been the result of a sequence of push and pop operations on an initially empty stack.

Example 1:
Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
Output: true
Explanation: We might do the following sequence:
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

Example 2:
Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
Output: false
Explanation: 1 cannot be popped before 2.
 
Constraints:

0 <= pushed.length == popped.length <= 1000
0 <= pushed[i], popped[i] < 1000
pushed is a permutation of popped.
pushed and popped have distinct values.
*/

#include "../standardHeaders.h"

typedef struct stackt{
    int *arr;
    int front;
    int stackSize;
}stackT;

bool isStackEmpty(stackT *stack){
    return stack->front == -1;
}

bool isStackFull(stackT *stack){
    return stack->front == stack->stackSize;
}

stackT *createStack(int stackSize){
    stackT *stack = (stackT *) malloc(sizeof(stackT));
    if(!stack)  return NULL;
    stack->arr = (int *) malloc(sizeof(int)*stackSize);
    if(!stack->arr) return NULL;
    stack->front = -1;
    stack->stackSize = stackSize;
    return stack;
}

int stackPush(stackT *stack, int inputIdx){
    if(isStackFull(stack))  return -1;
    stack->arr[++stack->front] = inputIdx;
    return 1;
}

int stackPop(stackT *stack){
    if(isStackEmpty(stack))  return -1;
    return stack->arr[stack->front--];
}

int stackPeek(stackT *stack){
    if(isStackEmpty(stack))  return -1;
    return stack->arr[stack->front];
}

void freeStack(stackT *stack){
    free(stack->arr);
    free(stack);
}

bool validateStackSequences(int* pushed, int pushedSize, int* popped, int poppedSize){
    
    if(pushedSize != poppedSize)    return false;
    
    stackT *stack = createStack(pushedSize);
    if(!stack)  return false;
    
    int stackPopPtr = 0;
    for(int i=0; i<pushedSize; i++){
        // push one item at a time
        stackPush(stack, pushed[i]);
        // pop as much as you can, greedily
        while((!isStackEmpty(stack)) && stackPeek(stack) == popped[stackPopPtr]){
            stackPop(stack);
            stackPopPtr++;
        }
    }
    free(stack);
    return (stackPopPtr == pushedSize);
    
}
