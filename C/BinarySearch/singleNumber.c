/*
Given a non-empty array of integers, every element appears twice except for one. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Example 1:

Input: [2,2,1]
Output: 1
Example 2:

Input: [4,1,2,1,2]
Output: 4
*/

#include "../standardHeaders.h"

/*
The key here to remember is, EVERY ELEMENT APPEARS ONLY TWICE.
Lets say, in following example, (2,1) appears 3 times.
[4,1,2,1,2,2,1]
The output for above input is: 7
Thus, its absolutely crucial to know, each elements appears in even forms.
*/
int singleNumber(int* nums, int numsSize){
    int return_val = 0, i = 0;
    for(i=0; i<numsSize; i++){
        return_val ^= nums[i];
    }    
    return return_val;
}

int main(void){

    int nums[][7] = {{1,1,2,3,3,4,4},{2,2,1,2,2,2,2},{4,1,2,1,2,3,3}};
    for(int i=0; i<3; i++){
        printf("Diff: %d \n",singleNumber(nums[i],7));
    }    
    return 0;
}
