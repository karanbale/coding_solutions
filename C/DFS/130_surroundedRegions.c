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

#include "../standardHeaders.h"

void printArray(char **grid, int rowIdxSize, int colIdxSize){
    printf("[\n");
    for(int i=0; i<rowIdxSize; i++){
        printf("[");
        for(int j=0; j<colIdxSize; j++){
            printf("%c,", grid[i][j]);
        }
        printf("],\n");
    }
    printf("]\n");
}

void dfs(char** grid, int gridSize, int gridColSize, int rowIdx, int colIdx, char to){
    
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

void solve(char** board, int boardSize, int* boardColSize){
    if((boardSize == 0) || (boardColSize == 0))   return;
    int maxArea = 0;
    bool isEdgeCase = false;
    
    // printArray(board, boardSize, *boardColSize);
    
    // traverse across all the edges, and find if there is any 'O'
    // if there is any 'O', traverse down its depth and replace all it's connected 'O' with 'Z'
    // 'Z' is just a random character other than 'O' and 'X'
    for (int i = 0; i < *boardColSize; i++)
        dfs(board, boardSize, *boardColSize, 0, i, 'Z');
    // printArray(board, boardSize, *boardColSize);
    for (int i = 0; i < boardSize; i++)
        dfs(board, boardSize, *boardColSize, i, 0, 'Z');
    // printArray(board, boardSize, *boardColSize);
    for (int i = 0; i < *boardColSize; i++)
        dfs(board, boardSize, *boardColSize, boardSize-1, i, 'Z');
    // printArray(board, boardSize, *boardColSize);
    for (int i = 0; i < boardSize; i++)
        dfs(board, boardSize, *boardColSize, i, *boardColSize-1, 'Z');
    // printArray(board, boardSize, *boardColSize);
    

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