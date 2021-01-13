/*
There are several cards arranged in a row, and each card has an associated number of points The points are given in the integer array cardPoints.
In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.
Your score is the sum of the points of the cards you have taken.
Given the integer array cardPoints and the integer k, return the maximum score you can obtain.

Example 1:
Input: cardPoints = [1,2,3,4,5,6,1], k = 3
Output: 12
Explanation: After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score. The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.

Example 2:
Input: cardPoints = [2,2,2], k = 2
Output: 4
Explanation: Regardless of which two cards you take, your score will always be 4.

Example 3:
Input: cardPoints = [9,7,7,9,7,7,9], k = 7
Output: 55
Explanation: You have to take all the cards. Your score is the sum of points of all cards.

Example 4:
Input: cardPoints = [1,1000,1], k = 1
Output: 1
Explanation: You cannot take the card in the middle. Your best score is 1. 

Example 5:
Input: cardPoints = [1,79,80,1,1,1,200,1], k = 3
Output: 202

Constraints:

1 <= cardPoints.length <= 10^5
1 <= cardPoints[i] <= 10^4
1 <= k <= cardPoints.length
*/

#include "../standardHeaders.h"

#define MAX(x, y) ((x) > (y) ? (x) : (y))

int maxScore(int* cardPoints, int cardPointsSize, int k){
    int sum=0, max;
    int i, e=cardPointsSize-1;
    
    // take sume of last K cards
    for (i=0;i<k;i++){
        sum += cardPoints[e--];
    }
    // if we only have K cards in array, return this sum
    if(k == cardPointsSize){
        return sum;
    }
    max = sum;
    // let's iterate over first K cards
    for(i=0;i<k;i++){
        // lets swap Kth card from end with Kth card from beginning of array
        // e.g. if K=  5, lets swap (cardPointsSize-1)th card with Kth card
        // next swap (cardPointsSize-2)th card with (K-1)th card
        // next swap (cardPointsSize-3)th card with (K-2)th card
        
        // remove kth card from end
        sum -= cardPoints[++e];
        // add its corresponding Kth card from beginning
        sum += cardPoints[i];
        
        // take max of current points tally and previous points tally
        // want the maximum of the two
        max = MAX(max, sum);
    }
    
    // return the maximum found
    return max;
}
