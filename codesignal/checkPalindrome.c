
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

bool checkPalindrome_method1(char * inputString) {
    int i = 0;
    int j = strlen(inputString)-1;
    while(j > i) {
        if(inputString[i++] != inputString[j--]) {
            return false;
        }
    }
    return true;
}

bool checkPalindrome_method2(char * inputString) {

    char * temp = inputString+strlen(inputString)-1;
    size_t count = strlen(inputString);
    while(count/2){
        // printf("%c \t %c\n", *inputString, *temp);
        if(*inputString != *temp) return false;
        inputString++;
        temp--;
        count --;
    }

    return true;

}

int main(){
    
    char palindromes[][50] = {"aabaa", "abac", "a", "az", "abacaba", "aaabaaaa", "zzzazzazz", "hlbeeykoqqqqokyeeblh",
    "hlbeeykoqqqokyeeblh"};
    for(int i=0; i<10; i++){
        printf("String: %s, isPalindrome: %d\n", palindromes[i], checkPalindrome_method1(palindromes[i]));
        printf("String: %s, isPalindrome: %d\n", palindromes[i], checkPalindrome_method2(palindromes[i]));
        printf("\n");
    }

    return 0;
}