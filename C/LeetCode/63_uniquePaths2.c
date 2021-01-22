/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time.
The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
Now consider if some obstacles are added to the grids. How many unique paths would there be?
An obstacle and space is marked as 1 and 0 respectively in the grid.

Example 1:
Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2

Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

Example 2:
Input: obstacleGrid = [[0,1],[0,0]]
Output: 1
 
Constraints:

m == obstacleGrid.length
n == obstacleGrid[i].length
1 <= m, n <= 100
obstacleGrid[i][j] is 0 or 1.

*/

#include "../standardHeaders.h"

#define OBSTACLE 1
#define SPACE 0

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/

int uniquePathsWithObstacles1(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize){
    
    int rowSize = obstacleGridSize, colSize = *obstacleGridColSize;
    int dp[rowSize][colSize];
    
    // if we start with an obstacle, we will never reach the end, return 0
    if(obstacleGrid[0][0] == OBSTACLE){
        return 0;
    }
    // initialize dp grid
    for(int i=0;i<rowSize;i++){
        for(int j=0;j<colSize;j++){
            dp[i][j] = 0;
        }
    }

    // assume you have just 1 row in input
    // update DP grid until you see spaces
    // as soon as you see obstacle stop, no point going further
    for(int i=0; i<rowSize; i++){
        // keep updating path until you see space
        if(obstacleGrid[i][0] == SPACE){
            dp[i][0] = 1;
        }
        // as soon as you hit a obstacle, we know we cant continue, so stop
        else{
            break;
        }
    }
    
    // assume you have just 1 column in input
    // update DP grid until you see spaces
    // as soon as you see obstacle stop, no point going further
    for(int i=0; i<colSize; i++){
        // keep updating path until you see space
        if(obstacleGrid[0][i] == SPACE){
            dp[0][i] = 1;
        }
        // as soon as you hit a obstacle, we know we cant continue, so stop
        else{
            break;
        }
    }

    // iterate over input    
    for(int i = 1; i < rowSize; i++){
        for(int j = 1; j < colSize; j++){
            // continue addition for each space that we observe
            if(obstacleGrid[i][j] == SPACE)
                dp[i][j] = dp[i][j-1] + dp[i-1][j];
            // for each obstacle, simply write 0 in DP
            else if(obstacleGrid[i][j] == OBSTACLE)
                dp[i][j] = 0;
        }
        
    }
    
    return dp[rowSize-1][colSize-1];
}

/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

int uniquePathsWithObstacles2(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize){
    
    int rowSize = obstacleGridSize, colSize = *obstacleGridColSize;
    
    // if we start with an obstacle, we will never reach the end, return 0
    if(obstacleGrid[0][0] == OBSTACLE){
        return 0;
    }
    
    obstacleGrid[0][0] = 1;
    for(int i=1; i<rowSize; i++){
        if((obstacleGrid[i][0] == SPACE) && (obstacleGrid[i-1][0] == OBSTACLE)){
            obstacleGrid[i][0] = 1;
        }
        else{
            obstacleGrid[i][0] = 0;
        }
    }
    
    for(int i=1; i<colSize; i++){
        if((obstacleGrid[0][i] == SPACE) && (obstacleGrid[0][i-1] == OBSTACLE)){
            obstacleGrid[0][i] = 1;
        }
        else{
            obstacleGrid[0][i] = 0;
        }
    }
    
    for(int i = 1; i < rowSize; i++){
        for(int j = 1; j < colSize; j++){
            if(obstacleGrid[i][j] == SPACE)
                obstacleGrid[i][j] = obstacleGrid[i][j-1] + obstacleGrid[i-1][j];
            else
                obstacleGrid[i][j] = 0;
        }
        
    }
    
    return obstacleGrid[rowSize-1][colSize-1];
}