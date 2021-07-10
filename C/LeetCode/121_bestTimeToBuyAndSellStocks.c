/*
Say you have an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock),
design an algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.

Example 1:
Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             Not 7-1 = 6, as selling price needs to be larger than buying price.

Example 2:
Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/

#include "../standardHeaders.h"

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/

/*
Time Complexity:
    O(n^2) since two for loops are used.
    Our loop runs n(n-1)/2 times here.
Space Complexity:
    O(1) since only 2 variables are using
*/
int maxProfitSolution1(int* prices, int pricesSize){
    
    int maxProfit = 0;
    for(int i=0; i<pricesSize; i++){
        for(int j=i+1; j<pricesSize; j++){
            maxProfit = MAX(maxProfit, (prices[j]-prices[i]));
        }
    }
    return maxProfit;

}

/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

/*
Time Complexity:
    O(n) since only single pass is used.
Space Complexity:
    O(1) since only 2 variables are using
*/

int maxProfitSolution2(int* prices, int pricesSize){
    
    int maxProfit = 0;
    int current_min = INT32_MAX;

    for (int i=0; i<pricesSize; i++) {
        if (prices[i] < current_min) {
            current_min = prices[i];
        }
        if (((prices[i] - current_min)) > maxProfit) {
            maxProfit = (prices[i] - current_min);
        }
    }
    return maxProfit;

}

/**********************************************************************************************/
/******************************** Solution 3 **************************************************/
/**********************************************************************************************/

/*
Time Complexity:
    O(n) since only two for loop passes are used.
Space Complexity:
    O(1) since only 2 variables are using
*/

int maxProfitSolution3(int* prices, int pricesSize){
    int lowToLeft[pricesSize];
    lowToLeft[0] = INT32_MAX;
    for(int i=1; i<pricesSize; i++) {
        lowToLeft[i] = MIN(prices[i-1], lowToLeft[i-1]);
    }
    int maxProfit = 0;
    for(int i=1; i<pricesSize; i++) {
        maxProfit = MAX(maxProfit, prices[i] - lowToLeft[i]);
    }
    return maxProfit;
}
