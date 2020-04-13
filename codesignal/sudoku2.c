/*

Sudoku is a number-placement puzzle. The objective is to fill a 9 × 9 grid with numbers in such a way that each column, each row, and each of the nine 3 × 3 sub-grids that compose the grid all contain all of the numbers from 1 to 9 one time.

Implement an algorithm that will check whether the given grid of numbers represents a valid Sudoku puzzle according to the layout rules described above. Note that the puzzle represented by grid does not have to be solvable.

Example

For

grid = [['.', '.', '.', '1', '4', '.', '.', '2', '.'],
        ['.', '.', '6', '.', '.', '.', '.', '.', '.'],
        ['.', '.', '.', '.', '.', '.', '.', '.', '.'],
        ['.', '.', '1', '.', '.', '.', '.', '.', '.'],
        ['.', '6', '7', '.', '.', '.', '.', '.', '9'],
        ['.', '.', '.', '.', '.', '.', '8', '1', '.'],
        ['.', '3', '.', '.', '.', '.', '.', '.', '6'],
        ['.', '.', '.', '.', '.', '7', '.', '.', '.'],
        ['.', '.', '.', '5', '.', '.', '.', '7', '.']]
the output should be
sudoku2(grid) = true;

For

grid = [['.', '.', '.', '.', '2', '.', '.', '9', '.'],
        ['.', '.', '.', '.', '6', '.', '.', '.', '.'],
        ['7', '1', '.', '.', '7', '5', '.', '.', '.'],
        ['.', '7', '.', '.', '.', '.', '.', '.', '.'],
        ['.', '.', '.', '.', '8', '3', '.', '.', '.'],
        ['.', '.', '8', '.', '.', '7', '.', '6', '.'],
        ['.', '.', '.', '.', '.', '2', '.', '.', '.'],
        ['.', '1', '.', '2', '.', '.', '.', '.', '.'],
        ['.', '2', '.', '.', '3', '.', '.', '.', '.']]
the output should be
sudoku2(grid) = false.

The given grid is not correct because there are two 1s in the second column. Each column, each row, and each 3 × 3 subgrid can only contain the numbers 1 through 9 one time.

Input/Output

[execution time limit] 0.5 seconds (c)

[input] array.array.char grid

A 9 × 9 array of characters, in which each character is either a digit from '1' to '9' or a period '.'.

[output] boolean

Return true if grid represents a valid Sudoku puzzle, otherwise return false.

*/

#include "../C/standardHeaders.h"

typedef struct {
int size;
char arr[];
} arr_char;

typedef struct {
int size;
arr_char *arr;
} arr_arr_char;

arr_arr_char alloc_arr_arr_integer(int len) {
  arr_arr_char a = {len, len > 0 ? malloc(sizeof(arr_char) * len) : NULL};
  return a;
}

/**********************************************************************************************************/
/* Solution 1 */
/**********************************************************************************************************/

int isPresentInRow(arr_arr_char grid, const char currNum, int IpRowIndex, int IpColIndex){
    int colIndex=0;
    for(colIndex=0; colIndex<grid.size; colIndex++){
        if((currNum == grid.arr[IpRowIndex].arr[colIndex]) && (colIndex != IpColIndex)){
            printf("checking row 1 %c\t", currNum);
            printf("gotchu %c\n",currNum);
            return 1;
        }
    }

    return 0;
}

int isPresentInCol(arr_arr_char grid, const char currNum, int IpRowIndex, int IpColIndex){
    int rowIndex=0;
    int fwRowIndex=0, bkRowIndex=0;
    int fwColIndex=0, bkColIndex=0;
    // printf("curr num: %c\t IpRowIndex: %d\t IpColIndex: %d\n",currNum,IpRowIndex,IpColIndex);
    // printf("formula: %d\n",((IpColIndex+1) % 3));
    if(((IpColIndex+1) % 3) == 1) {
        bkColIndex = IpColIndex+1;
        fwColIndex = IpColIndex+2;
    }
    if(((IpColIndex+1) % 3) == 0){
        bkColIndex = IpColIndex-1;
        fwColIndex = IpColIndex-2;
    }
    if(((IpColIndex+1) % 3) == 2){
        bkColIndex = IpColIndex-1;
        fwColIndex = IpColIndex+1;
    }
    
    if(((IpRowIndex+1) % 3) == 1){
        bkRowIndex = IpRowIndex+1;
        fwRowIndex = IpRowIndex+2;
    }
    if (((IpRowIndex+1) % 3) == 0) {
        bkRowIndex = IpRowIndex-1;
        fwRowIndex = IpRowIndex-2;
    }
    if (((IpRowIndex+1) % 3) == 2){
        bkRowIndex = IpRowIndex-1;
        fwRowIndex = IpRowIndex+1;
    }
    
    // printf("            \t bkColIndex: %d\t fwColIndex: %d\n", bkColIndex, fwColIndex);
    // printf("            \t bkRowIndex: %d\t fwRowIndex: %d\n\n", bkRowIndex, fwRowIndex);
    for(rowIndex=0; rowIndex<grid.size; rowIndex++){
        // check current iterative row and IpColIndex
        if((currNum == grid.arr[rowIndex].arr[IpColIndex]) && (rowIndex != IpRowIndex)){
            // printf("checking col 1 %c\t", currNum);
            // printf("gotchu %c\n",currNum);
            return 1;
        }

        // check bkRowIndex with given IpColIndex-1 and IpColIndex+1
        if(rowIndex == bkRowIndex){
            if(currNum == grid.arr[rowIndex].arr[bkColIndex]){
                // printf("checking col 2 %c\t", currNum);
                // printf("gotchu %c\n",currNum);
                return 1;
            }
            if(currNum == grid.arr[rowIndex].arr[fwColIndex]){
                // printf("checking col 2 %c\t", currNum);
                // printf("gotchu %c\n",currNum);
                return 1;
            }
        }

        // check fwRowIndex with given IpColIndex-1 and IpColIndex+1
        if(rowIndex == fwRowIndex){
            if(currNum == grid.arr[rowIndex].arr[bkColIndex]){
                // printf("checking col 3 %c\t", currNum);
                // printf("gotchu %c\n",currNum);
                return 1;
            }
            if(currNum == grid.arr[rowIndex].arr[fwColIndex]){
                // printf("checking col 2 %c\t", currNum);
                // printf("gotchu %c\n",currNum);
                return 1;
            }
        }
    }

    return 0;
}


bool sudoku1(arr_arr_char grid) {
    int i=0, j=0;
    char currNum;
    for(i=0; i<grid.size; i++){
        for(j=0; j<grid.size; j++){
            currNum = grid.arr[i].arr[j];
            // if(currNum >='0' && currNum <= '9'){
            //     printf("present col: %d\t", isPresentInCol(grid, currNum, i, j));
            //     printf("present row: %d\t", isPresentInRow(grid, currNum, i, j));
            // }
            
            if(currNum >='0' && currNum <= '9'){
                if(isPresentInCol(grid, currNum, i, j)){
                    printf("returning mann...\n");
                    return false;
                }
                if(isPresentInRow(grid, currNum, i, j)){
                    printf("returning mann...\n");
                    return false;
                } 
            }  
        }
    }
    return true;
}

/**********************************************************************************************************/
/* Solution 2 */
/**********************************************************************************************************/

bool sudoku2(arr_arr_char grid) {
    int rowIndex=0, colIndex=0, currIndex=0;
    int numIndexInSubMatrix = 0;
    char currNum;
    /* Iterate over all the rows */
    for(rowIndex=0; rowIndex<grid.size; rowIndex++){
        /* Iterate over all the columns */
        for(colIndex=0; colIndex<grid.size; colIndex++){
            currNum = grid.arr[rowIndex].arr[colIndex];
            /* Find location of current value in its own sub-matrix.
             * A sub-matrix is of size 3x3.
             * A sub-matrix starts with index 0, ends with index 8
             * This location can be between 0-8 only. Label this as numIndexInSubMatrix             
             */
            numIndexInSubMatrix = (rowIndex%3*3+colIndex%3);
            if(currNum >='0' && currNum <= '9'){
                printf("num:%c, i=%d, j=%d\n", currNum, rowIndex, colIndex);
                for(currIndex=0; currIndex<grid.size; currIndex++){
                    
                    /* Find if currNum exists in all the colums of its own row, except its own column */
                    if((currNum == grid.arr[rowIndex].arr[currIndex]) &&
                    currIndex != colIndex){
                        return false;
                    }

                    /* Find if currNum exists in all the rows of its own column, except its own row */
                    if((currNum == grid.arr[currIndex].arr[colIndex]) &&
                    currIndex != rowIndex){
                        return false;
                    }

                    /* Check if currNum exists in its own sub-matrix, 
                     * except skipping on its own index in that sub matrix
                     * A slice is an entire row of size 3 of a sub-matrix.
                     * 
                     * rowIndex/3*3 will always divide your total rows in 3 slices and 
                     * reset you to beginning of that slice.
                     * e.g. 0-2 is one slice, 3-5 is second slice and 6-8 is third slice
                     * If rowIndex for currNum is 5 (we belong to 2nd slice), 
                     * we will always reset back to 5/3*3=1*3=3 i.e. beginning of 2nd slice.
                     *  
                     * colIndex/3*3 will always divide your total cols in 3 slices and 
                     * reset you to beginning of that slice.
                     * e.g. 0-2 is one slice, 3-5 is second slice and 6-8 is third slice
                     * If colIndex for currNum is 7 (we belong to 3rd slice), 
                     * we will always reset back to 7/3*3=2*3=6 i.e. beginning of 3rd slice.
                     * 
                     * currIndex/3 will increment only once, per slice. 
                     * e.g. for 1st slice 0-2, currIndex/3 will always be 0,0,0
                     *      for 2nd slice 3-5, currIndex/3 will always be 1,1,1
                     *      for 3rd slice 6-8, currIndex/3 will always be 2,2,2
                     * 
                     * currIndex%3 will increment per iteration in the slice and reset back to 0 for next slice. 
                     * e.g. for 1st slice 0-2, currIndex%3 will always be 0,1,2
                     *      for 2nd slice 3-5, currIndex%3 will always be 0,1,2
                     *      for 3rd slice 6-8, currIndex%3 will always be 0,1,2
                     */
                    printf("index: %d, row:%d, col: %d, k: %d\n", numIndexInSubMatrix, rowIndex/3*3+currIndex/3, colIndex/3*3+currIndex%3, currIndex);
                    if(currIndex != numIndexInSubMatrix &&
                    currNum == grid.arr[rowIndex/3*3+currIndex/3].arr[colIndex/3*3+currIndex%3]){
                        return false;
                    }
                }
            }  
        }
    }
    return true;
}

/**********************************************************************************************************/
/* Solution 3 */
/**********************************************************************************************************/

#define RST_START_OF_ROW_SLICE(row_num)             ((row_num/3)*3)     // 0 or 3 or 6

#define INC_PER_ROW_SLICE(row_num, currIdx)         ((RST_START_OF_ROW_SLICE(row_num))\
                                                    + ((currIdx)/3))

#define RST_START_OF_COL_SLICE(col_num)            ((col_num/3)*3)

#define INC_PER_COL_SLICE(col_num, currIdx)        ((RST_START_OF_COL_SLICE((col_num))\
                                                    + ((currIdx)%3)))

bool isValidSudoku(char** board, int boardSize, int* boardColSize){
    
    int count=0;
    
    // iterate over rows
    for(int rowNum = 0; rowNum<9; rowNum++){
        // iterate over columns
        for(int colNum = 0; colNum<9; colNum++){
            // get current num
            char currNum = board[rowNum][colNum];                
            // get current num's position in its own sub-matrix grid
            int currPosInSubMatrix = (((rowNum%3)*3)+(colNum%3));
            if(currNum >= '0' && currNum <= '9'){
                //printf("num: %c, row: %d, col: %d\n", currNum, rowNum, colNum);
                for(int currItr=0; currItr<9; currItr++){

                    // check if currNum exists in any other row, except its own row
                    if((currNum == board[currItr][colNum]) && (currItr != rowNum)){
                        return false;
                    }

                    // check if currNum exists in any other col, except its own col
                    if((currNum == board[rowNum][currItr]) && (currItr != colNum)){
                        return false;
                    }                

                    // check if number exist in its own sub-matrix, except itself
                    if((currItr != currPosInSubMatrix) && 
                       (currNum == board[INC_PER_ROW_SLICE(rowNum, currItr)][INC_PER_COL_SLICE(colNum, currItr)])){                       
                     return false;   
                    }                    
                }
            }
            else{
                count++;
            }
        }
    }    
    
    // if everything looks good, return true
    return (count<=81 ? true : false);
}

/**********************************************************************************************************/