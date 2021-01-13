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
