/*

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