/*
Compute modulo of two given numbers without using division operator,
where divisor will always be a power of 2.
E.g. divisor = 2,4,8,16,32,64....

Explanation:
    Remember, divisor is always a power of 2.
    And the property for power of 2 is, ONLY 1 bit is always set for number who is power of 2.
    Expression (divisor - 1) will always have all the bits from 0 to (i-1)th bit set to 1, 
    where i is first and only set bit (since its power of 2) of the divisor.
    E.g. Divide 9 by 8
    divisor   = 0b00001000 (8)
    divisor-1 = 0b00000111 (7)
    Number    = 0b00001001 (9)
    ANDing    = 0b00000001 (1)

*/

#include "utilities.h"

#define MODULO(num, divisor) ((num) & ((divisor)-1))
#define ARRAY_SIZE 10
#define OFFSET 5

int moduloWithoutDivision(void){

    int num[ARRAY_SIZE] = {2,6,8,21,19,100,125,679,1000,1001};
    int divisor[ARRAY_SIZE-OFFSET] = {2,4,8,16,32};

    for(int i=0; i<ARRAY_SIZE; i++){
        for(int j=0; j<ARRAY_SIZE-OFFSET; j++){
            printf("Num: %d, Divisor: %d Observed Remainder: %d Expected Remainder: %d\n",
            num[i],divisor[j],MODULO(num[i], divisor[j]), (num[i]%divisor[j]));
        }
    }

    return 0;
}


int main(void){

    moduloWithoutDivision();
    return 0;

}
