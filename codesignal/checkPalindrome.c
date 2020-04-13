
/*
Given the string, check if it is a palindrome.

Example

For inputString = "aabaa", the output should be
checkPalindrome(inputString) = true;
For inputString = "abac", the output should be
checkPalindrome(inputString) = false;
For inputString = "a", the output should be
checkPalindrome(inputString) = true.
Input/Output

[execution time limit] 0.5 seconds (c)

[input] string inputString

A non-empty string consisting of lowercase characters.

Guaranteed constraints:
1 ≤ inputString.length ≤ 105.

[output] boolean

true if inputString is a palindrome, false otherwise.

*/

#include "../C/standardHeaders.h"

bool checkPalindrome(char * inputString) {
    int i = 0;
    int j = strlen(inputString)-1;
    while(j > i) {
        if(inputString[i++] != inputString[j--]) {
            return false;
        }
    }
    return true;
}

int main(){
    
    char palindromStr[] = {};
    printf("\nPlease enter a string: \n");
    scanf("%s", palindromStr);
    printf("\nuser input: %s\n", palindromStr);
    printf("\nisPalindorme: %s\n", checkPalindrome(palindromStr) ? "true" : "false");

    return 0;
}