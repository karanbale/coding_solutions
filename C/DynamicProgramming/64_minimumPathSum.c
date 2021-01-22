/*
Given a m x n grid filled with non-negative numbers,
find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example 1:

Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.

Example 2:
Input: grid = [[1,2,3],[4,5,6]]
Output: 12

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 200
0 <= grid[i][j] <= 100

*/

#include "../standardHeaders.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/*
DP : Top-down approach
*/
int minPathSum1(int** grid, int gridSize, int* gridColSize){
    
    int rowSize = gridSize, colSize = *gridColSize;
    
    for(int rowIdx=0; rowIdx<rowSize; rowIdx++){
        for(int colIdx=0; colIdx<colSize; colIdx++){
            // base condition
            if(rowIdx == 0 && colIdx == 0){
                continue;
            }
            // top most row
            else if(rowIdx-1 < 0){
                grid[rowIdx][colIdx] = grid[rowIdx][colIdx] + grid[rowIdx][colIdx-1];
            }
            // left most column
            else if(colIdx-1 < 0){
                grid[rowIdx][colIdx] = grid[rowIdx][colIdx] + grid[rowIdx-1][colIdx];
            }
            // normal condition
            else{
                grid[rowIdx][colIdx] += MIN(grid[rowIdx-1][colIdx], grid[rowIdx][colIdx-1]);
            }
        }
    }
    return grid[rowSize-1][colSize-1];

}

/*
DP : Bottom-up approach
*/
int minPathSum(int** grid, int gridSize, int* gridColSize){
    
    int rowSize = gridSize, colSize = *gridColSize;
    int  dp[rowSize][colSize];
    
    // init work
    dp[0][0] = grid[0][0];
    
    // if we have one 1 col as input, then output would be
    // e.g. input = [[1],[2],[3],[4]]
    // output = [[1],[3],[6],[10]] ==> return 10 as output
    for(int i = 1; i < rowSize; i++){
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    
    // if we have one 1 row as input, then output would be
    // e.g. input = [[1,2,3,4]]
    // output = [1,3,6,10] ==> return 10 as output
    for(int i = 1; i < colSize; i++){
        dp[0][i] = dp[0][i-1] + grid[0][i];
    }
	
    // iterate over entire array with an offset of 1, 
    // since we already calculated output for 1 row and 1 column
    for(int i = 1; i < rowSize; i++){
        for(int j = 1; j < colSize; j++){
            dp[i][j] = MIN(dp[i-1][j],dp[i][j-1]) + grid[i][j];
        }
    }
    
    return dp[rowSize-1][colSize-1];
}

/*
Sample inputs to test:

[[1],[2],[3],[4]]
[[1,2,3,4]]
[[1,3,1],[1,5,1],[4,2,1]]
*/