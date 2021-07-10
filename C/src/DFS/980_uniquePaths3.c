/*
On a 2-dimensional grid, there are 4 types of squares:

1 represents the starting square.  There is exactly one starting square.
2 represents the ending square.  There is exactly one ending square.
0 represents empty squares we can walk over.
-1 represents obstacles that we cannot walk over.
Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.

Example 1:
Input: [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

Example 2:
Input: [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
Output: 4
Explanation: We have the following four paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

Example 3:
Input: [[0,1],[2,0]]
Output: 0
Explanation: 
There is no path that walks over every empty square exactly once.
Note that the starting and ending square can be anywhere in the grid.

Note:

1 <= grid.length * grid[0].length <= 20
*/

#include "../../standardHeaders.h"
#include "common.h"

#define OBSTACLE -1
#define SPACE 0
#define START 1
#define END 2
#define VISITED 3

int dfs(int **grid, int rowSize, int colSize, int rowIdx, int colIdx, int totalEmptySpaces) {
    
    if((rowIdx < 0) || (rowIdx >= rowSize) || (colIdx < 0) || (colIdx >= colSize) || (grid[rowIdx][colIdx] == OBSTACLE)){
        return 0;
    }
    
    if(grid[rowIdx][colIdx] == END){
        return totalEmptySpaces == 0;
    }
    
    // block this path until we visit every node
    grid[rowIdx][colIdx] = OBSTACLE;
    
    int path = 0;
    
    path = dfs(grid, rowSize, colSize, rowIdx-1, colIdx, totalEmptySpaces-1) +
        dfs(grid, rowSize, colSize, rowIdx+1, colIdx, totalEmptySpaces-1) +
        dfs(grid, rowSize, colSize, rowIdx, colIdx-1, totalEmptySpaces-1) +
        dfs(grid, rowSize, colSize, rowIdx, colIdx+1, totalEmptySpaces-1);
    
    // restore the path again, for new iteration
    grid[rowIdx][colIdx] = SPACE;
    
    return path;
}

int uniquePathsIII(int** grid, int gridSize, int* gridColSize) {

    int rowSize = gridSize, colSize = *gridColSize;
    int emptySpaces = 1, x = -1, y = -1;
    
    for(int i=0;i<rowSize;i++){
        for(int j=0;j<colSize;j++){
            if(grid[i][j] == SPACE){
                // count total number of empty spaces
                emptySpaces++;
            }
            else if(grid[i][j] == START){
                x = i;
                y = j;
            }
        }
    }
    return dfs(grid, rowSize, colSize, x, y, emptySpaces);  
}
