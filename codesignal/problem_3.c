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

bool sudoku2(arr_arr_char grid) {
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

