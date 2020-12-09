/*


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
