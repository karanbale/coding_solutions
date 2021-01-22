/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, 
find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

Example:
Input: [2,1,5,6,2,3]
Output: 10
 
Example 1:
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

Example 2:
Input: heights = [2,4]
Output: 4

Constraints:

1 <= heights.length <= 105
0 <= heights[i] <= 104

*/

#include "../standardHeaders.h"

/*
[2,1,5,6,2,3]

for row 0 - heihtsSize:

calculate width for each column :
if (i, j) == 1 then (i,j-1)+1 else 0
height = currRow - prevRow + 1
area: width*height

*/

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

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
    stackT *stack = malloc(sizeof(stackT));
    if(!stack)  return NULL;
    stack->arr = malloc(sizeof(int)*stackSize);
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
    if(isStackEmpty(stack))  return 0;
    return stack->arr[stack->front];
}

void freeStack(stackT *stack){
    free(stack->arr);
    free(stack);
}

int largestRectangleArea(int* heights, int heightsSize){
    
    int rowSize = heightsSize;
    int maxArea = 0;
    
    stackT *stack = createStack(heightsSize);
    if(!stack)  return false;
    
    for(int i=0; i<rowSize; i++){
        // iterate over stack, check if current item on top of stack is >= current item
        // if its greater or equal, pop this item
        while((!isStackEmpty(stack)) && (heights[stackPeek(stack)] >= heights[i])){
            // pop the item which is bigger than current item
            int currentHeight = heights[stackPop(stack)];
            // calculate width from current item back to last item on top
            int currentWidth = i-stackPeek(stack)-1;
            // take max between current width and max width so far
            maxArea = MAX(maxArea, currentHeight * currentWidth);
        }
        // keep pushing index of each rectanle to stack
        stackPush(stack, i);
    }
    
    while(!isStackEmpty(stack)){
        int currentHeight = heights[stackPop(stack)];
        int currentWidth = rowSize-stackPeek(stack)-1;
        maxArea = MAX(maxArea, currentHeight * currentWidth);
    }
    
    return maxArea;
    
}
