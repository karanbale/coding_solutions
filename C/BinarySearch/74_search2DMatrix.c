/*
Write an efficient algorithm that searches for a value in an m x n matrix. 
This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.

Example 1:
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true

Example 2:
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
 
Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-104 <= matrix[i][j], target <= 104

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
    
    int colSize = *matrixColSize;
    int rowSize = matrixSize;
    
    int left = 0, right = rowSize*colSize - 1;
    int leftIdx, rightIdx;
    while(left <= right){
        int mid = left + (right-left)/2;
        leftIdx = mid/colSize;
        rightIdx = mid%colSize;
        int currentElement = matrix[leftIdx][rightIdx];
        if(target == currentElement)    return true;
        else if(target > currentElement){
            left = mid+1;
        }
        else{
            right = mid-1;
        }
    }
    return false;
}

