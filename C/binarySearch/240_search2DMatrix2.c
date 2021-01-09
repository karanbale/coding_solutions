/*
Write an efficient algorithm that searches for a target value in an m x n integer matrix.
The matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

Example 1:
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true

Example 2:
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= n, m <= 300
-109 <= matix[i][j] <= 109
All the integers in each row are sorted in ascending order.
All the integers in each column are sorted in ascending order.
-109 <= target <= 109
*/

#include "../standardHeaders.h"


bool binSearch(int **matrix, int target, int start, bool vertical, int rowSize, int colSize){
    int left = start;
    int right = vertical ? colSize-1 : rowSize-1 ;
    while (left <= right) {
        int mid = left + (right - left)/2;
        if (vertical){ // searching a column
            if (matrix[start][mid] < target) {
                left = mid + 1;
            }
            else if (matrix[start][mid] > target) {
                right = mid - 1;
            }
            else {
                return true;
            }
        }
        else { // searching a row
            if (matrix[mid][start] < target) {
                left = mid + 1;
            }
            else if (matrix[mid][start] > target) {
                right = mid - 1;
            }
            else {
                return true;
            }
        }
    }
    return false;
}

bool searchMatrixSolution1(int** matrix, int matrixSize, int* matrixColSize, int target){
    
    if(!matrix || !matrixSize)  return false;
    
    int colSize = *matrixColSize;
    int rowSize = matrixSize;
    int minIterSize = fmin(colSize, rowSize);

    if((target == matrix[0][0])||(target == matrix[rowSize-1][colSize-1])){
        return true;
    }
    
    for(int i=0; i<minIterSize; i++){
        bool verticalFound = binSearch(matrix, target, i, true, rowSize, colSize);
        bool horizontalFound = binSearch(matrix, target, i, false, rowSize, colSize);
        if(verticalFound || horizontalFound){
            return true;
        }
    }
    
    return false;
}

bool searchMatrixSolution2(int** matrix, int matrixSize, int* matrixColSize, int target){
    
    if(!matrix || !matrixSize)  return false;
    
    int rowIdx = matrixSize-1;
    int colIdx=0;
    
    while(rowIdx>=0 && rowIdx < matrixSize && colIdx < *matrixColSize && colIdx >=0){
        int cellValue = matrix[rowIdx][colIdx];
        if(cellValue == target) return true;
        else if(cellValue > target){
            rowIdx--;
        }
        else{
            colIdx++;
        }
        
    }
    
    return false;
}

/*
Sample inputs:
[[1,4],[2,5]]
2
[[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]]
5
[[1],[3],[5]]
0
*/