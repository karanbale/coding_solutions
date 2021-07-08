/*
Koko loves to eat bananas.  There are N piles of bananas, the i-th pile has piles[i] bananas.
The guards have gone and will come back in H hours.
Koko can decide her bananas-per-hour eating speed of K.  
Each hour, she chooses some pile of bananas, and eats K bananas from that pile.
If the pile has less than K bananas, she eats all of them instead, and won't eat any more bananas during this hour.
Koko likes to eat slowly, but still wants to finish eating all the bananas before the guards come back.
Return the minimum integer K such that she can eat all the bananas within H hours.

Example 1:
Input: piles = [3,6,7,11], H = 8
Output: 4

Example 2:
Input: piles = [30,11,23,4,20], H = 5
Output: 30

Example 3:
Input: piles = [30,11,23,4,20], H = 6
Output: 23
 

Constraints:

1 <= piles.length <= 10^4
piles.length <= H <= 10^9
1 <= piles[i] <= 10^9
*/

#include "../standardHeaders.h"

int isValid(int* piles, int pilesSize, int H,int midGuess){
    size_t hour=0;
    for(int i=0;i<pilesSize;i++){
        // when we divide, e.g. 10/3 = 3(quotient) +1 (remainder)
        // however when we divide 9/3 = 3(queotient) + 0 (remainder)
        // hence we subtract 1 from answer and then do the calculations
        
        // calculate what is average number of hours koko require to eat piles[i] # of bananas, at the eating rate of midGuess bananas per hour
        hour += (piles[i]-1)/midGuess+(piles[i]%midGuess!=0);
    }
    return hour <= H;
}

int minEatingSpeed(int* piles, int pilesSize, int H){
    size_t left=0, right=0;
    // take sume of all the bananas from all the piles, this is our right
    for(int i=0; i<pilesSize; i++){
        right += piles[i];
    }
    
    // calculate average # of babanas koko can eat during guard's H hour absence
    // this average may be 0, so we take right%H and add != 0 so we can add 1 to 
    // our answer, not having this additional check may cause us to run into
    // division by zerio runtime errors
    left = right/H+(right%H!=0);
    
    while(left<right){
        size_t mid = left+(right-left)/2;
        if(isValid(piles, pilesSize, H, mid))   right = mid;
        else left = mid+1;
    }
    return left;
}
