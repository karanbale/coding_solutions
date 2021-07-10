/*
Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example:

X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
Explanation:

Surrounded regions shouldn’t be on the border, which means that any 'O' on the border of the board are not flipped to 'X'.
Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'.
Two cells are connected if they are adjacent cells connected horizontally or vertically.

*/

/*
Complexity Analysis

Time Complexity: O(N), where N is the number of cells in the board. 
In the worst case where it contains only the O cells on the board, 
we would traverse each cell twice: once during the DFS traversal and the other time during the cell reversion in the last step.

Space Complexity: O(N) where N is the number of cells in the board. 
There are mainly two places that we consume some additional memory.

We keep a list of border cells as starting points for our traversal.
We could consider the number of border cells is proportional to the total number (NN) of cells.

During the recursive calls of DFS() function, we would consume some space in the function call stack, 
i.e. the call stack will pile up along with the depth of recursive calls. 
And the maximum depth of recursive calls would be NN as in the worst scenario mentioned in the time complexity.

As a result, the overall space complexity of the algorithm is \mathcal{O}(N)O(N).
*/

#include "DFS_Header.h"
#include "common.h"

void dfs(char** grid, int gridSize, int gridColSize, int rowIdx, int colIdx, char to) {
    
    // edge cases
    if((rowIdx < 0) || (rowIdx>=gridSize) || (colIdx >=gridColSize) || (colIdx < 0)){
        return;
    }
    
    // replace all 'O's with random character 'Z', this character is any character other than 'X' and 'O'
    if(grid[rowIdx][colIdx] == 'O'){
        grid[rowIdx][colIdx] = to;
    }
    else{
        return;
    }
    
    dfs(grid, gridSize, gridColSize, rowIdx-1, colIdx, to);
    dfs(grid, gridSize, gridColSize, rowIdx+1, colIdx, to);
    dfs(grid, gridSize, gridColSize, rowIdx, colIdx-1, to);
    dfs(grid, gridSize, gridColSize, rowIdx, colIdx+1, to);
    
}

void surroundingRegions(char** board, int boardSize, int* boardColSize) {
    if((boardSize == 0) || (boardColSize == 0))   return;
    
    // printArray_2D(board, boardSize, *boardColSize);
    
    // traverse across all the edges, and find if there is any 'O'
    // if there is any 'O', traverse down its depth and replace all it's connected 'O' with 'Z'
    // 'Z' is just a random character other than 'O' and 'X'
    for (int i = 0; i < *boardColSize; i++)
        dfs(board, boardSize, *boardColSize, 0, i, 'Z');
    // printArray_2D(board, boardSize, *boardColSize);
    for (int i = 0; i < boardSize; i++)
        dfs(board, boardSize, *boardColSize, i, 0, 'Z');
    // printArray_2D(board, boardSize, *boardColSize);
    for (int i = 0; i < *boardColSize; i++)
        dfs(board, boardSize, *boardColSize, boardSize-1, i, 'Z');
    // printArray_2D(board, boardSize, *boardColSize);
    for (int i = 0; i < boardSize; i++)
        dfs(board, boardSize, *boardColSize, i, *boardColSize-1, 'Z');
    // printArray_2D(board, boardSize, *boardColSize);
    

    // Now that all 'O' from edges are replaced with 'Z', remaining 'O's are all valid regions we can replace with 'X'
    // while replacing all remaining 'O's with 'X's, simply switch the 'Z's back to 'O's to restore original inputs
    for(int i=0; i<boardSize; i++){
        for(int j=0; j< (*boardColSize); j++){
            if (board[i][j] == 'Z')
                board[i][j] = 'O';
            else if (board[i][j] == 'O')
                board[i][j] = 'X';
        }
    }
}
