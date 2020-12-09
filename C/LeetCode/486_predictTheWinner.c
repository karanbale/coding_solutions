/**
 * Given an array of scores that are non-negative integers. 
 * Player 1 picks one of the numbers from either end of the array followed by the player 2 and then player 1 and so on. 
 * Each time a player picks a number, that number will not be available for the next player. This continues until all the scores have been chosen. The player with the maximum score wins.
 * Given an array of scores, predict whether player 1 is the winner. You can assume each player plays to maximize his score.

Example 1:

Input: [1, 5, 2]
Output: False
Explanation: Initially, player 1 can choose between 1 and 2. 
If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2). 
So, final score of player 1 is 1 + 2 = 3, and player 2 is 5. 
Hence, player 1 will never be the winner and you need to return False.
 

Example 2:

Input: [1, 5, 233, 7]
Output: True
Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
 

Constraints:

1 <= length of the array <= 20.
Any scores in the given array are non-negative integers and will not exceed 10,000,000.
If the scores of both players are equal, then player 1 is still the winner.
*/

#include "../standardHeaders.h"

int count(int *nums, int startIdx, int endIdx, int turn, int len);

bool PredictTheWinner(int* nums, int numsSize){
    if(numsSize == 1){
        return true;
    }
    // take total sum of the array
    int sum = 0;
    for(int i=0; i<numsSize; i++){
        sum += nums[i];
    }
    // take first value, forward second index
    int tempFirstPass = nums[0] + count(nums, 1, numsSize-1, 2, numsSize-1);
    // take last value, forward first index
    int tempLastPass = nums[numsSize-1] + count(nums, 0, numsSize-2, 2, numsSize-1);
    // take maximum of the above two cases, and find player 2 value
    int maxPlayer1 = (tempFirstPass > tempLastPass) ? tempFirstPass : tempLastPass;
    int maxPlayer2 = sum - maxPlayer1;
    // printf("Sum: %d, P1: %d P2: %d\n", sum, maxPlayer1, maxPlayer2);
    // return True if P1 >= P2, False otherwise
    return (maxPlayer1 >= maxPlayer2) ? true : false;
}

int count(int *nums, int startIdx, int endIdx, int turn, int len){
    // base case where indexes meet, we dont need to traverse further
    if(startIdx == endIdx){
        return nums[startIdx];
    }
    int returnVal = 0;
    // handle player 2
    if(turn == 2){
        // player 2 takes first value, ignores last value
        int temp1 = count(nums, startIdx+1, endIdx, 1, len);
        // player 2 takes last value, ignores first value
        int temp2 = count(nums, startIdx, endIdx-1, 1, len);
        // take min of the two values for P2
        // we're taking minimum of the two values since we're trying to find maximum value P1 can have
        returnVal = (temp1 < temp2) ? temp1 : temp2;
    }
    // handle player 1
    else{
        // player 1 takes first value, ignores last value
        int temp1 = nums[startIdx] + count(nums, startIdx+1, endIdx, 2, len);
        // player 1 takes last value, ignores first value
        int temp2 = nums[endIdx] + count(nums, startIdx, endIdx-1, 2, len);
        // take max of the two values for P1
        returnVal = (temp1 > temp2) ? temp1 : temp2;
    }
    return returnVal;
}
