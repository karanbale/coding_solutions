/*
Given the array candies and the integer extraCandies, where candies[i] represents the number of candies that the ith kid has.
For each kid check if there is a way to distribute extraCandies among the kids such that,
he or she can have the greatest number of candies among them. Notice that multiple kids can have the greatest number of candies.

Example 1:

Input: candies = [2,3,5,1,3], extraCandies = 3
Output: [true,true,true,false,true] 
Explanation: 
Kid 1 has 2 candies and if he or she receives all extra candies (3) will have 5 candies --- the greatest number of candies among the kids. 
Kid 2 has 3 candies and if he or she receives at least 2 extra candies will have the greatest number of candies among the kids. 
Kid 3 has 5 candies and this is already the greatest number of candies among the kids. 
Kid 4 has 1 candy and even if he or she receives all extra candies will only have 4 candies. 
Kid 5 has 3 candies and if he or she receives at least 2 extra candies will have the greatest number of candies among the kids. 

Example 2:
Input: candies = [4,2,1,1,2], extraCandies = 1
Output: [true,false,false,false,false] 
Explanation: There is only 1 extra candy, therefore only kid 1 will have the greatest number of candies among the kids regardless of who takes the extra candy.
Example 3:

Input: candies = [12,1,12], extraCandies = 10
Output: [true,false,true]
 

Constraints:

2 <= candies.length <= 100
1 <= candies[i] <= 100
1 <= extraCandies <= 50


*/

#include "../standardHeaders.h"

int maxCandie(int *candies, int candiesSize){
    int max = candies[0];
    for(int i=1; i<candiesSize; i++){
        if(candies[i] > max)   max = candies[i];
    }
    return max;
}

void printArray(bool *candies, int candiesSize){
    printf("[");
    for(int i=0; i<candiesSize; i++){
        printf("%d, ", candies[i]);
    }
    printf("]\n");
}

bool* kidsWithCandies(int* candies, int candiesSize, int extraCandies, int* returnSize){
    *returnSize = candiesSize;
    int maxCandieCount = 0;
    
    bool *retArray = (bool *) malloc(sizeof(bool *)*candiesSize);
    memset(retArray, false, sizeof(retArray[0]));
    
    // find kid with max candies in the array
    maxCandieCount = maxCandie(candies, candiesSize);
    
    // calulate if each kid can end up with max candies after adding extra candies
    for(int i=0; 
        (i<candiesSize) && 
         (((candies[i]+extraCandies) >= maxCandieCount) ? 
            (memset(retArray+i, true, sizeof(retArray[i]))) : 
            (memset(retArray+i, false, sizeof(retArray[i]))) ) ;
          i++);

    return retArray;
    
}
