/*
Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and,return its area.

Example 1:
Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 4

Example 2:
Input: matrix = [["0","1"],["1","0"]]
Output: 1

Example 3:
Input: matrix = [["0"]]
Output: 0

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 300
matrix[i][j] is '0' or '1'.
*/

#include "../standardHeaders.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/

int maximalSquare1(char** matrix, int matrixSize, int* matrixColSize){
    
    int rowSize = matrixSize;
    int colSize = *matrixColSize;
    int maxSum = 0;
    
    int dp[rowSize+1][colSize+1];
    
    for(int i=0; i<=rowSize;i++){
        for(int j=0; j<=colSize; j++){
            dp[i][j] = 0;
        }
    }
    
    int maxArea = 0;
    for(int i=1; i<=rowSize;i++){
        for(int j=1; j<=colSize; j++){
            if(matrix[i-1][j-1] == '1'){
                // assume length of largest square containing only 1's is at bottom-right hand corner at [i][j]
                // thus we need take sum of left, top and top-left squares to calculate total sum
                // we can only calculate sum of a square, not rectangle
                // take min from left and top square
                int tempMin = MIN(dp[i][j-1],dp[i-1][j]);
                // then take min from above two and top-left square
                dp[i][j] = MIN(tempMin,dp[i-1][j-1])+1;
                // track max sum of squares at each calculation
                maxSum = MAX(maxSum, dp[i][j]);
            }
        }
    }
    return maxSum*maxSum;
}

/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

int maximalSquare2(char** matrix, int matrixSize, int* matrixColSize){
    
    int rowSize = matrixSize;
    int colSize = *matrixColSize;
    
    int dp[rowSize][colSize];

    
    int maxArea = 0;
    for(int i=0; i<rowSize;i++){
        for(int j=0; j<colSize; j++){
            // base condition, for top-most row boundary or left-most column boundary, value of square will be its current value
            if( (i==0) || (j==0) || (matrix[i][j] == '0')){
                // store matrix[i][j] because for i == 0 or j == 0, we may have matrix[i][j] = 1 OR 0 either
                dp[i][j] = matrix[i][j]-0x30;
            }
            // If matrix[i][j] = '1', we will have dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + 1, 
            // which means that the square will be limited by its left, upper and upper-left neighbors.
            // NOTE: // we can only calculate sum of a square, not rectangle
            else{
                // take min from left and top square
                int tempMin = MIN(dp[i-1][j], dp[i][j-1]);
                // then take min from above two and top-left square
                dp[i][j] = MIN(tempMin,dp[i-1][j-1])+1;
            }
            // track max sum of squares at each calculation
            maxArea = MAX(maxArea, dp[i][j]);
        }
    }
    
    return maxArea*maxArea;
}
