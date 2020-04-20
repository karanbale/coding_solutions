/*
Given an array of integers, find the pair of adjacent elements that has the largest product and return that product.

Example

For inputArray = [3, 6, -2, -5, 7, 3], the output should be
adjacentElementsProduct(inputArray) = 21.

7 and 3 produce the largest product.

Input/Output

[execution time limit] 0.5 seconds (c)

[input] array.integer inputArray

An array of integers containing at least two elements.

Guaranteed constraints:
2 ≤ inputArray.length ≤ 10,
-1000 ≤ inputArray[i] ≤ 1000.

[output] integer

The largest product of adjacent elements.
*/

#include "../C/standardHeaders.h"

typedef struct {
int size;
int arr[];
} arr_integer;


#define MAX(x,y) ((x) >= (y) ? (x) : (y))

/*Function to find maximum of x and y*/
int max(int x, int y) 
{ 
  return x - ((x - y) & ((x - y) >> 
            (sizeof(int) * 8 - 1))); 
} 

int adjacentElementsProduct(arr_integer inputArray) {
    ssize_t maxVal = inputArray.arr[0]*(inputArray.arr[1]), maxindex = 0;
    for(int i=2; i<inputArray.size; i++){
        maxVal = MAX(maxVal, (inputArray.arr[i-1]*(inputArray.arr[i])));
        // printf("maxVal: %d, currVal: %d\n", maxVal, inputArray.arr[i]);
        if((inputArray.arr[i]) == maxVal){
            maxindex = i;
        } 
    }

    return maxVal;

}


int main(void){

    arr_integer inputArray;
    // inputArray.arr[6] = [3, 6, -2, -5, 7, 3] output: 21
    // inputArray: [-1, -2] output: 2
    // inputArray: [5, 1, 2, 3, 1, 4] output: 6
    // inputArray: [9, 5, 10, 2, 24, -1, -48] output: 50
    // inputArray: [-23, 4, -3, 8, -12] output: -12
    
    // @TODO: needs work done here to run this code

}