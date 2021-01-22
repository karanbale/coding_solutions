/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time.
The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

Example 1:
Input: m = 3, n = 7
Output: 28

Example 2:
Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down

Example 3:
Input: m = 7, n = 3
Output: 28

Example 4:
Input: m = 3, n = 3
Output: 6

Constraints:

1 <= m, n <= 100
It's guaranteed that the answer will be less than or equal to 2 * 109
*/

#include "../standardHeaders.h"

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/
int dfs(int rowSize, int colSize, int rowIdx, int colIdx){
    if((rowIdx < 0) || (colIdx < 0) || (rowIdx >= rowSize) || (colIdx >= colSize)){
        return 0;
    }
    if((rowIdx == rowSize-1) && (colIdx == colSize-1)){
        return 1;
    }
    return dfs(rowSize, colSize, rowIdx+1, colIdx) + dfs(rowSize, colSize, rowIdx, colIdx+1);
}

int uniquePaths1(int m, int n){
    return dfs(m, n, 0, 0);
}

/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

int uniquePaths2(int m, int n){
    int rowSize = m, colSize = n;
    int  dp[rowSize][colSize];
    
    // for single row / column, we will always reach the end of the array
    // for single row: keep traveling right->right->.....->right
    // for single col: keep traveling down->down->.....->down
    for(int i = 0; i < rowSize; i++){
        for(int j = 0; j < colSize; j++){
            dp[i][j] = 1;
        }
        
    }

    // iterate over entire array with an offset of 1, 
    // since we already calculated output for 1 row and 1 column
    for(int i = 1; i < rowSize; i++){
        for(int j = 1; j < colSize; j++){
            dp[i][j] = dp[i][j-1] + dp[i-1][j];
        }
    }
    
    return dp[rowSize-1][colSize-1];
}

/**********************************************************************************************/
/******************************** Solution 3 **************************************************/
/**********************************************************************************************/

int uniquePaths3(int m, int n){
    int rowSize = m, colSize = n;
    int  dp[rowSize][colSize];
    
    for(int i = 0; i < rowSize; i++){
        for(int j = 0; j < colSize; j++){
            // for single row / column, we will always reach the end of the array
            // for single row: keep traveling right->right->.....->right
            // for single col: keep traveling down->down->.....->down
            if(i == 0 || j == 0){
                dp[i][j] = 1;
            }
            // for every other condition, just keep calculating sum of paths
            // from going down or right
            else{
                dp[i][j] = dp[i][j-1] + dp[i-1][j];
            }
        }
        
    }
    
    return dp[rowSize-1][colSize-1];
}
