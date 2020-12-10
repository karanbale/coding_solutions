/*
Given a string containing only three types of characters: '(', ')' and '*', write a function to check whether this string is valid.
We define the validity of a string by these rules:

Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
An empty string is also valid.

Example 1:
Input: "()"
Output: True

Example 2:
Input: "(*)"
Output: True

Example 3:
Input: "(*))"
Output: True

Note:
The string size will be in the range [1, 100].
*/

#include "../standardHeaders.h"


// code algorithm details:
//If we met "(" or "*" - increment left balance; else decrement it
// If we met ")" or "*" - increment right balance; else decrement it
// If we got negative values for left balance or right balance, we have unvaild string - wrong order of parenthesis 
// or unequal number of open/closed parenthesis.
// Repeat steps 1-3 until we reach the end of the string. Return True then, because string is properly balanced.


bool checkValidString(char * s){
    // empty string is a vali string
    if(strlen(s) == 0){
        return true;
    }
    
    // if just 1 string and its not a *, then its invalid string
    if(strlen(s) == 1 && *s != '*'){
        return false;
    }

    size_t len = strlen(s)-1;
    char *revS = s;
    int leftBalance = 0;
    int rightBalance = 0;
    
    // iterate over char array at the same time
    // one pointer will iterate over from front and other from end
    for(int i=0; i<strlen(s)-1; i++){
        // if opening bracket or * found, increment left balance
        if(s[i] == '(' || s[i] == '*'){
            leftBalance++;
        }
        // if closing bracket is found, decrement left balance
        else{
            leftBalance--;
        }
        
        // if closing bracket or * found, increment right balance
        if(revS[len-i] == ')' || revS[len-i] == '*'){
            rightBalance++;
        }
        // if opening bracket is found, decrement right balance
        else{
            rightBalance--;
        }
        
        if((leftBalance < 0)||(rightBalance < 0)){
            return false;
        }
    }
    
    return true;
}
