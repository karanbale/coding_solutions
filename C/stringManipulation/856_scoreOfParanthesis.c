/*
Given a balanced parentheses string S, compute the score of the string based on the following rule:

()   ==> A,  has score 1
()() ==> A,B has score A + B, where A and B are balanced parentheses strings.
(()) ==>(A)  has score 2 * A, where A is a balanced parentheses string.
 

Example 1:
Input: "()"
Output: 1

Example 2:
Input: "(())"
Output: 2

Example 3:
Input: "()()"
Output: 2

Example 4:
Input: "(()(()))"
Output: 6

Note:

S is a balanced parentheses string, containing only ( and ).
2 <= S.length <= 50
*/

#include "../standardHeaders.h"

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/

int scoreOfParentheses(char * S){
    int score = 0, mult = 1;
    int len = strlen(S);
    
    // iterate over string
    for(int i=0; i<len; i++){
        // each opening bracket is *1
        if(S[i] == '('){
            mult *= 1;   // ideally we dont need this, keeping for better algorithm readability
            // each subsequent opening bracket is 2*previous bracket depth
            if(S[i+1] == '('){
                mult *= 2;
            }
            // each subsequent closing bracket (whose prefix bracket was opening bracket) requirs us to add the score until this point
            else{
                score += mult;
                i++;
            }
        }
        // each closing bracket (whose prefix bracket was a closing bracket) is equivalent to dividing multiplication by 2
        else{
            mult /= 2;
        }
    }
    return score;
}

/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

#define max(a,b) ((a) > (b) ? (a) : (b))

typedef struct stack{
    size_t *Arr;
    size_t top;
    size_t stackSize;
}stackt;

bool isStackEmpty(stackt *stack){
    return stack->top == -1;
}

bool isStackFull(stackt *stack){
    return stack->top == stack->stackSize;
}

stackt *createStack(size_t stackSize){
    stackt *stack = malloc(sizeof(stackt));
    if(!stack)  return NULL;
    stack->Arr = malloc(sizeof(int)*stackSize);
    if(!stack->Arr) return NULL;
    stack->top = -1;
    stack->stackSize = stackSize;
    return stack;
}

size_t stackPush(stackt *stack, int data){
    if(isStackFull(stack))  return 0;
    stack->Arr[++stack->top] = data;
    return 1;
}

size_t stackPop(stackt *stack){
    if(isStackEmpty(stack)) return -1;
    return stack->Arr[stack->top--];
}

size_t scoreOfParentheses1(char * S){
    
    stackt *stack = createStack(strlen(S)+1);
    if(!stack)  return 0;
    
    size_t length = strlen(S);
    int score = 0, depth = 0;
    
    for(int i=0; i<length; i++){
        if(S[i] == '('){
            // push current score to the stack
            stackPush(stack, score);
            // reset the score for next level i.e. we start all over again
            score = 0;
        }
        else if(S[i] == ')'){
            // things to keep in mind:
            // if current brackets are just "()" => then score is 1
            // if current brackets have outer opening brackets, then score will be 2 ** score
            
            // when you find a closing bracket
            // we take maximum between 2^score or simply 1
            // and we add this to total score tally
            int currentScore = max((2*score),1);
            int oldScore = stackPop(stack);
            score = oldScore + currentScore;
        }
    }
    return score;
}

/**********************************************************************************************/

/*
Sample inputs to test
"((()))"
"(()(()))"
"()"
"()(()(()))"
"()()"
"(()())"
"(())"
*/

/*
Sample inputs to test
"((()))"
"(()(()))"
"()"
"()(()(()))"
"()()"
"(()())"
"(())"
*/
