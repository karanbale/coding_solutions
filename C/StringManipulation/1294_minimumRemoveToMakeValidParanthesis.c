/*
Given a string s of '(' , ')' and lowercase English characters. 

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
 
Example 1:
Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.

Example 2:
Input: s = "a)b(c)d"
Output: "ab(c)d"

Example 3:
Input: s = "))(("
Output: ""
Explanation: An empty string is also valid.

Example 4:
Input: s = "(a(b(c)d)"
Output: "a(b(c)d)"
 

Constraints:

1 <= s.length <= 10^5
s[i] is one of  '(' , ')' and lowercase English letters
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

void freeStack(stackT *stack, int *tempArr){
    free(stack->arr);
    free(stack);
    free(tempArr);
}

char * minRemoveToMakeValid(char * s){
    stackT *stack = createStack(strlen(s)+1);
    int *tempArr = (int *)calloc(sizeof(int), strlen(s)+1);
    int tempIdx = 0;
    for(tempIdx = 0; tempIdx < strlen(s); tempIdx++) {
        if(s[tempIdx] == '(') {
            stackPush(stack, tempIdx);
        }
        if(s[tempIdx] == ')') {
            if(isStackEmpty(stack)) {
                tempArr[tempIdx] = 1;
            }
            else {
                stackPop(stack);
            }
        }
    }
    while(!isStackEmpty(stack)) tempArr[stackPop(stack)] = 1;
    char *retStr = (char *)malloc(sizeof(char)*(strlen(s)+1));
    tempIdx = 0;
    int retStrIdx = 0;
    for(tempIdx = 0; tempIdx < strlen(s); tempIdx++) {
        if(tempArr[tempIdx] != 1) {
            retStr[retStrIdx++] = s[tempIdx];
        }
    }
    retStr[retStrIdx] = '\0';
    freeStack(stack, tempArr);
    return retStr;

}

/*
Sample testcases:
"lee(t(c)o)de)"
"))(("
*/
