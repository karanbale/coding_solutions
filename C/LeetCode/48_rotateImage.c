/*
You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]

Example 2:
Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

Example 3:
Input: matrix = [[1]]
Output: [[1]]

Example 4:
Input: matrix = [[1,2],[3,4]]
Output: [[3,1],[4,2]]

Constraints:

matrix.length == n
matrix[i].length == n
1 <= n <= 20
-1000 <= matrix[i][j] <= 1000
*/

#include "../standardHeaders.h"

void rotateSolution1(int** matrix, int matrixSize, int* matrixColSize){
    // take matrix's transpose
    for(int row=0; row<matrixSize; row++){
        for(int col=row; col<matrixSize; col++){
            int temp = matrix[row][col];
            matrix[row][col] = matrix[col][row];
            matrix[col][row] = temp;
        }
    }
    
    // reverse rows
    for(int row=0; row<matrixSize; row++){
        for(int col=0; col<matrixSize/2; col++){
            int temp = matrix[row][col];
            matrix[row][col] = matrix[row][matrixSize-1-col];
            matrix[row][matrixSize-1-col] = temp;
        }
    }
}

void rotateSolution2(int** matrix, int matrixSize, int* matrixColSize){
    for(int row=0; row<matrixSize/2+matrixSize%2; row++){
        for(int col=0; col<matrixSize/2; col++){
            int temp = matrix[row][col];
            matrix[row][col] = matrix[matrixSize-1-col][row];
            matrix[matrixSize-1-col][row] = matrix[matrixSize-1-row][matrixSize-1-col];
            matrix[matrixSize-1-row][matrixSize-1-col] = matrix[col][matrixSize-1-row];
            matrix[col][matrixSize-1-row] = temp;
        }
    }
}