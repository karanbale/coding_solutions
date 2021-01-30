/*
Given a string containing just the characters '(' and ')', 
find the length of the longest valid (well-formed) parentheses substring.

Example 1:
Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".

Example 2:
Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".

Example 3:
Input: s = ""
Output: 0
 
Constraints:

0 <= s.length <= 3 * 104
s[i] is '(', or ')'.
*/

#include "../standardHeaders.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/

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

int longestValidParentheses(char * s){

    if(strlen(s) == 0)  return 0;
    
    stackT *stack = createStack(20000);
    if(!stack)  return 0;
    
    char *temp = s;
    
    int longestCount = 0;
    for(int i=0; i<strlen(s); i++){
        if(s[i] == '('){
            // push opening bracket's index to stack
            if(!stackPush(stack, i)){
                printf("STACK SIZE ERROR !!!!!");
                exit(0);
            }
        }
        else{
            if(!isStackEmpty(stack)){
                // found valid pair, remove index from stack
                if(s[stackPeek(stack)] == '('){
                    stackPop(stack);
                }
                else{
                    stackPush(stack, i);
                }
            }
            else{
                stackPush(stack, i);
            }
        }
    }
    
    if(isStackEmpty(stack))  return strlen(s);
    else{
        int maxLength = strlen(s);
        int minLength = 0;
        while(!isStackEmpty(stack)){
            minLength = stackPop(stack);
            longestCount = MAX(longestCount, maxLength-minLength-1);
            maxLength=minLength;
        }
        longestCount = MAX(longestCount, maxLength);
    }
    
    free(stack);
    
    return longestCount;
    
}

/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

int longestValidParentheses1(char * s){

    if(strlen(s) == 0)  return 0;
    
    int stack[strlen(s)*2];
    for(int i=0; i<strlen(s); i++){
        stack[i] = 0;
    }
    int longestCount = 0;
    for(int i=1; i<strlen(s); i++){
        if(s[i] == ')'){
            if(s[i-1] == '('){
                stack[i] = (i>=2 ? stack[i-2] : 0) + 2;
            }
            else if((i-stack[i-1] > 0) && (s[i-stack[i-1]-1] == '(')){
                stack[i] = stack[i-1] + ((i-stack[i-1]) >= 2 ? stack[i-stack[i-1]-2] : 0) + 2;
            }
        }
        longestCount = MAX(longestCount, stack[i]);
    }
    
    return longestCount;
    
}
