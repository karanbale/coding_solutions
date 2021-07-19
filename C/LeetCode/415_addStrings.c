/*
Given two non-negative integers, num1 and num2 represented as string, return the sum of num1 and num2 as a string.

You must solve the problem without using any built-in library for handling large integers (such as BigInteger). 
You must also not convert the inputs to integers directly.

Example 1:

Input: num1 = "11", num2 = "123"
Output: "134"
Example 2:

Input: num1 = "456", num2 = "77"
Output: "533"
Example 3:

Input: num1 = "0", num2 = "0"
Output: "0"
 

Constraints:

1 <= num1.length, num2.length <= 104
num1 and num2 consist of only digits.
num1 and num2 don't have any leading zeros except for the zero itself.
*/

#include "../standardHeaders.h"

char * addStrings(char * num1, char * num2){
    int carry = 0;
    int ansSize = 5100;
    char *ans = (char *)malloc(sizeof(char)*(ansSize+1));
    ans[ansSize-1] = '\0';
    int ansIdx = ansSize-2;
    int numSize1 = strlen(num1);
    int numSize2 = strlen(num2);
    int i = numSize1-1;
    int j = numSize2-1;
    for(; i>=0 && j>=0; i--, j--) {
        ans[ansIdx--] = (((num1[i]-'0') + (num2[j]-'0') + carry) % 10) + '0';
        carry = ((num1[i]-'0') + (num2[j]-'0') + carry)/10;
    }
    if(numSize1 > numSize2) {
        for(; i>=0; i--) {
            ans[ansIdx--] = (((num1[i]-'0') + carry) % 10) + '0';
            carry = ((num1[i]-'0') + carry)/10;
        }
    }
    else if(numSize1 < numSize2){
        for(; j>=0; j--) {
            ans[ansIdx--] = (((num2[j]-'0') + carry) % 10) + '0';
            carry = ((num2[j]-'0') + carry)/10;
        }
    } 
    if(carry) {
        ans[ansIdx] = carry + '0';
        return &ans[ansIdx];
    }
    return &ans[ansIdx+1];
}
