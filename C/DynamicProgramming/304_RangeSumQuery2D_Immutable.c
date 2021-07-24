/*
Given a 2D matrix matrix, handle multiple queries of the following type:

Calculate the sum of the elements of matrix inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
Implement the NumMatrix class:

NumMatrix(int[][] matrix) Initializes the object with the integer matrix matrix.
int sumRegion(int row1, int col1, int row2, int col2) Returns the sum of the elements of matrix inside the rectangle,
defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Example 1:

Input
["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
[[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [1, 1, 2, 2], [1, 2, 2, 4]]
Output
[null, 8, 11, 12]

Explanation
NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e sum of the red rectangle)
numMatrix.sumRegion(1, 1, 2, 2); // return 11 (i.e sum of the green rectangle)
numMatrix.sumRegion(1, 2, 2, 4); // return 12 (i.e sum of the blue rectangle)
 
Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
-105 <= matrix[i][j] <= 105
0 <= row1 <= row2 < m
0 <= col1 <= col2 < n
At most 104 calls will be made to sumRegion.
*/

#include "../standardHeaders.h"

void printArray_2D(int **grid, int rowIdxSize, int colIdxSize) {
    printf("[\n");
    for(int i=0; i<rowIdxSize; i++){
        printf("[");
        for(int j=0; j<colIdxSize; j++){
            printf("%d,", grid[i][j]);
        }
        printf("\b],\n");
    }
    printf("\b]\n");
}

typedef struct {
    int **matrixNew;
    int maxRow;
    int maxCol;
} NumMatrix;

NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize) {
    NumMatrix *m = (NumMatrix *)malloc(sizeof(NumMatrix));
    m->maxRow = matrixSize;
    m->maxCol = *matrixColSize;
    m->matrixNew = (int **)malloc(sizeof(int *)*(matrixSize+1));
    for(int i=0; i<(matrixSize+1); i++) {
        m->matrixNew[i] = (int *)malloc(sizeof(int)*(*matrixColSize+1));
        memset(m->matrixNew[i], 0, sizeof(int)*(*matrixColSize+1));
    }
    for(int i=0; i<matrixSize; i++) {
        for(int j=0; j<(*matrixColSize);j++) {
            m->matrixNew[i+1][j+1] = m->matrixNew[i+1][j]+m->matrixNew[i][j+1]+matrix[i][j]-m->matrixNew[i][j];
        }
    }
    // printArray_2D(matrix, matrixSize, *matrixColSize);
    // printArray_2D(m->matrixNew, matrixSize+1, *matrixColSize+1);
    return m;
}

int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2) {
    return obj->matrixNew[row2+1][col2+1] - obj->matrixNew[row1][col2 + 1] - obj->matrixNew[row2+1][col1] + obj->matrixNew[row1][col1];
}

void numMatrixFree(NumMatrix* obj) {
    for(int i=0; i<obj->maxRow; i++) {
        free(obj->matrixNew[i]);
    }
    free(obj->matrixNew);
    free(obj);
}

/**
 * Your NumMatrix struct will be instantiated and called as such:
 * NumMatrix* obj = numMatrixCreate(matrix, matrixSize, matrixColSize);
 * int param_1 = numMatrixSumRegion(obj, row1, col1, row2, col2);
 
 * numMatrixFree(obj);
*/


