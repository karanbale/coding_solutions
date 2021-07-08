/*
Given n non-negative integers representing an elevation map where,
the width of each bar is 1, compute how much water it can trap after raining.

Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array,
[0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.

Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9
 

Constraints:

n == height.length
0 <= n <= 3 * 104
0 <= height[i] <= 105

*/

#include "../standardHeaders.h"

#define ENABLE_PRINTS 0
#define TM_PRINTF(f_, ...) ENABLE_PRINTS? printf((f_), ##__VA_ARGS__) : 0
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
    if(isStackEmpty(stack))  return -1;
    return stack->arr[stack->front];
}

void freeStack(stackT *stack){
    free(stack->arr);
    free(stack);
}

int trap(int* height, int heightSize){
    int currentIdx = 0;
    int level = 0, water = 0;
    
    stackT *stack = createStack(heightSize);
    if(!stack)  return false;
    
    while (currentIdx < heightSize) {
        while(!isStackEmpty(stack) && (height[currentIdx] > height[stackPeek(stack)])){
            int previousTowerIdx = stackPop(stack);
            TM_PRINTF("\tPopped height[%d]:%d from stack, currentIdx: %d\n",previousTowerIdx,height[previousTowerIdx], currentIdx);
            if(isStackEmpty(stack)) break;
            int waterLevel = MIN(height[currentIdx], height[stackPeek(stack)]) - height[previousTowerIdx];
            int distance = (currentIdx - stackPeek(stack) - 1);
            water += distance * waterLevel;
            TM_PRINTF("\t\tDistance: %d, waterLevel: %d, water: %d\n",distance, waterLevel, water);
        }
        stackPush(stack, currentIdx);
        TM_PRINTF("Pushing height[%d]:%d to stack\n",currentIdx,height[currentIdx]);
        currentIdx++;
    }
    return water;
}

int main(void) {
    int waterHeightArr[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    printf("Water level: %d\n", trap(&waterHeightArr,sizeof(waterHeightArr)/sizeof(waterHeightArr[0])));
    return 0;
}
