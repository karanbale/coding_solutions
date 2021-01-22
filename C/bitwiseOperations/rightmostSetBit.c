/*
Given a number, check if its a power of 2 or not.
Note: You cannot use looping or branching.

Method 1:
Property to remember: 
    Number and its negative representation,
    both will always have right most set bit of the number set, all other 
    bits to the left of this right most set bit, will be flipped.
E.g.
Number = 8
+(Num)   = 0b00001000 (-8)
bit flip = 0b11110111
add 1    = 0b00000001
-(Num)   = 0b11111000 (-8)

Number = 10
(+Num)   = 00001010 (+10)
bit flip = 11110101
add 1    = 00000001
-(Num)   = 11110110 (-10)

Number = 8
+(Num)   = 0b00011100 (+16)
bit flip = 0b11100011
add 1    = 0b00000001
-(Num)   = 0b11100100 (-16)

Property of numbers who are power of 2:
    Only 1 bit will be set for numbers, who are power of 2.
    E.g. Num = 0b 0000 1000 (8)
         Num = 0b 0001 0000 (16)

Theory of operation for negative numbers:
    To save negative numbers, we flip all the bits of number,
    then we add 1 to it. Hence right most set bit of both numbers, will always be same.

If you take AND of n and (n-1), we can unset right most set bit of n.
For a given number 'n', (n-1) will always have all of its bits flipped,
AFTER n's right most set bit.
    e.g.
    Number   = 0b00010100 (20)
    Number-1 = 0b00010011 (19)
    ANDing   = 0b00010000 ====> Right most bit of n was cleared.

Num AND (&) with its own negative value
+(Num)   = 0b00001000 (+8)
-(Num)   = 0b11111000 (-8)
 (ANS)   = 0b00001000 (8)

Number = 12
+(Num) = 0b00001010 (12)
-(Num) = 0b11110110 (-12)
 (ANS) = 0b00000010 (2)
*/

#include "../standardHeaders.h"

#define EVEN_ODD_METHOD_1(x) ((x)&(-(x)))
#define POS_OF_ONLY_SET_BIT(x) (((x) & ((x)-1)))
#define ARR_LEN 6


int findRightmostSetBitInNumber(void){

    int num[ARR_LEN] = {5,4,1,0,8,12};

    for(int i=0; i<ARR_LEN; i++){
        // if ANDing of a number and its negative counterpart is equal to the number itself,
        // then given number is always power of 2
        printf("Position of right most set bit for Num: %d is: %d.\n", num[i], EVEN_ODD_METHOD_1(num[i])); 
    }

    return 0;
}

/*
If you take AND of n and (n-1), we can unset right most set bit of n.
For a given number 'n', (n-1) will always have all of its bits flipped,
AFTER n's right most set bit.
    e.g.
    Number   = 0b00010100 (20)
    Number-1 = 0b00010011 (19)
    ANDing   = 0b00010000 ====> Right most bit of n was cleared.
*/

int findPositionOfOnlySetBitInNumber(void){

    int num[ARR_LEN] = {5,4,1,0,8,12};

    for(int i=0; i<ARR_LEN; i++){
        // if ANDing of a number and its negative counterpart is equal to 0, 
        // then it has only 1 set bit, other wise its invalid number
        if(POS_OF_ONLY_SET_BIT(num[i]) == 0){
        //if((num[i] & (num[i]-1)) == 0){
            printf("Position of only set bit for Num: %d is: %d.\n", num[i], (int)log2(num[i])+1);
            continue;
        }
        printf("This is invalid number.\n");
    }

    return 0;
}

int main(void){
    
  findRightmostSetBitInNumber();
  findPositionOfOnlySetBitInNumber();
  return 0;

}
