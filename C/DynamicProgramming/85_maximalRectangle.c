/*
Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

Example 1:
Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.

Example 2:
Input: matrix = []
Output: 0

Example 3:
Input: matrix = [["0"]]
Output: 0

Example 4:
Input: matrix = [["1"]]
Output: 1

Example 5:
Input: matrix = [["0","0"]]
Output: 0

Constraints:

rows == matrix.length
cols == matrix.length
0 <= row, cols <= 200
matrix[i][j] is '0' or '1'.
*/

#include "../standardHeaders.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize){
    
    int rowSize = matrixSize;
    if(!rowSize)    return 0;
    int colSize = *matrixColSize;
    if(!colSize)    return 0;
    
    int dp[rowSize][colSize];
    for(int i=0; i<rowSize;i++){
        for(int j=0; j<colSize; j++){
            dp[i][j] = 0;
        }
    }
    
    int maxArea = 0;
    for(int i=0; i<rowSize; i++){
        for(int j=0; j<colSize; j++){
            // compute maximum width at each column, for each row
            if(matrix[i][j] == '1'){
                // for first column, width will be 1, if current value at(i, j = 0) is 1
                // if not first column then just add 1 to previously calculated value
                // e.g. if current row is [1,1,1,1] then width will be => [1,2,3,4]
                dp[i][j] = (j == 0) ? 1 : dp[i][j-1]+1;
                int currWidth = dp[i][j];
                // iterate over all the rows above current row until we reach 0th row
                // include current row as well, since we have valid width here
                for(int k = i; k>=0 ; k--){
                    // between two widths, we take minimum width which is overlapping area of the two rectangles
                    // we can't take maximum because, it will exclude some overlapping area and not form a complete rectangle
                    currWidth = MIN(currWidth, dp[k][j]);
                    // for each rectangle calculate current width as
                    // currWidth = minWidth*(currentRowIdx - previousRowIdx + 1);
                    // add 1 since we calculate against current row as well
                    int currentArea = currWidth*(i - k + 1);
                    maxArea = MAX(maxArea, currentArea);
                }
            }
        }
    }
    return maxArea;
}

/*
Inputs to test:
[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]

*/