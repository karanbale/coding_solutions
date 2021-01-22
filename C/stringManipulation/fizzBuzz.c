/*

Write a program that outputs the string representation of numbers from 1 to n.

But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.

Example:

n = 15,

Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]

*/

#include "string_manipulation_headers.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

char ** fizzBuzz(int n, int* returnSize){
    *returnSize = n;
    char** retArr;
    retArr = (char**)malloc(sizeof(char*)*n);
    char buf[11]; //[11] is from 2^31=2147483648, 10*char + '\n'
    
    for(int i=0; i<n; i++){
        int num = 0;
        num = i+1;
        if(num%15 == 0){
            retArr[i] = (char*)malloc(sizeof("FizzBuzz"));
            memcpy(retArr[i],"FizzBuzz",sizeof("FizzBuzz"));
        }
        else if(num%3 == 0){
            retArr[i] = (char*)malloc(sizeof("Fizz"));
            memcpy(retArr[i],"Fizz",sizeof("Fizz"));
        }
        else if(num%5 == 0){
            retArr[i] = (char*)malloc(sizeof("Buzz"));
            memcpy(retArr[i],"Buzz",sizeof("Buzz"));
        }
        else{
            sprintf(buf,"%d",i+1);
            retArr[i] = (char*)malloc(sizeof(buf));
            memcpy(retArr[i],buf,sizeof(buf));
        }
    }
    
    for(int i=0; i<n; i++){
        printf("%s\n",retArr[i]);
    }
    
    return (retArr);

}
