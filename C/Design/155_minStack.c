/*
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
 

Example 1:

Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
 

Constraints:

Methods pop, top and getMin operations will always be called on non-empty stacks.

*/

#include "../standardHeaders.h"


#define SIZE 100000

typedef struct stack{
    int *arr;
    int size;
    int top;
    int min;
}MinStack;

/** initialize your data structure here. */

MinStack* minStackCreate() {
    MinStack *stack = (MinStack *) malloc(sizeof(MinStack));
    if(!stack)  return NULL;
    stack->arr = (int *) malloc(sizeof(int)*SIZE);
    if(!stack->arr) return NULL;
    stack->top = -1;
    stack->size = SIZE;
    stack->min = INT32_MAX;
    return stack;
}

bool isStackEmpty(MinStack *obj){
    return obj->top == -1;
}

bool isStackFull(MinStack *obj){
    return obj->top == obj->size;
}

int minStackTop(MinStack* obj) {
    return  obj->arr[obj->top];
}

int minStackGetMin(MinStack* obj) {
    return obj->min;
}

void minStackFree(MinStack* obj) {
    free(obj->arr);
    free(obj);
}

void minStackPush(MinStack* obj, int x) {
    if(isStackFull(obj))    return;
    if(isStackEmpty(obj)){
        obj->min = obj->arr[++obj->top] = x;
    }
    else if(x > obj->min){
        obj->arr[++obj->top] = x;
    }
    else{
        obj->arr[++obj->top] = obj->min;
        obj->arr[++obj->top] = x;
        obj->min = x;
    }
}

void minStackPop(MinStack* obj) {
    if(minStackTop(obj) <= obj->min){
        if(obj->top == 0){
            obj->top--;
            obj->min = INT32_MAX;
        }
        else{
            obj->min = obj->arr[obj->top-1];
            obj->top -= 2;
        }
    }
    else{
        obj->top--;
    }
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, x);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/