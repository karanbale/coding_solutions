/*

Check if given number is even or odd.
Method 1: 
Property, for even numbers, LSB is always 0.
Simply check LSB. 
If LSB = 1, number is odd.
if LSB = 0, number is even.

*/

#include "utilities.h"

#define EVEN_ODD_METHOD_1(x) ((x) & (1))
#define ARR_LEN 5

int NumberIsEvenOrOdd(void){

    int num[ARR_LEN] = {5,4,1,0,8};

    for(int i=0; i<ARR_LEN; i++){
        if(EVEN_ODD_METHOD_1(num[i]) == 0)  printf("Num: %d is EVEN.\n", num[i]);
        else if(EVEN_ODD_METHOD_1(num[i]) == 1) printf("Num: %d is ODD.\n", num[i]);

    }

    return 0;
}

int main(void){

  NumberIsEvenOrOdd();
  return 0;

}
