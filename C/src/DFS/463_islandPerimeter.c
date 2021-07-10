/*
You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
Grid cells are connected horizontally/vertically (not diagonally).
The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island.
One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100.
Determine the perimeter of the island.

Example 1:
Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
Output: 16
Explanation: The perimeter is the 16 yellow stripes in the image above.

Example 2:
Input: grid = [[1]]
Output: 4

Example 3:
Input: grid = [[1,0]]
Output: 4

Constraints:

row == grid.length
col == grid[i].length
1 <= row, col <= 100
grid[i][j] is 0 or 1.
*/

#include "DFS_Header.h"
#include "common.h"

int dfs(int** grid, int gridSize, int gridColSize, int rowIdx, int colIdx) {
    
    // edge cases
    if((rowIdx < 0) || (rowIdx>=gridSize) || (colIdx >=gridColSize) || (colIdx < 0) || (grid[rowIdx][colIdx] == 0)){
        return 0;
    }

     // if island is already visited, skip it
    if(grid[rowIdx][colIdx] == 2){
        return 0;
    }
    
    // since we're visiting this island, make it 0
    grid[rowIdx][colIdx] = 2;
    
    // count in all the 4 directions of current island, see if there is an island
    // add 1 to the count, since currently we're already on an island, count its area
    return (1 + dfs(grid, gridSize, gridColSize, rowIdx-1, colIdx) + 
                dfs(grid, gridSize, gridColSize, rowIdx+1, colIdx) +
                dfs(grid, gridSize, gridColSize, rowIdx, colIdx-1) +
                dfs(grid, gridSize, gridColSize, rowIdx, colIdx+1));

}

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize) {
    
    if((gridSize == 0) || (gridColSize == 0))   return 0;
    int maxArea = 0;

    for(int i=0; i<gridSize; i++){
        for(int j=0; j< (*gridColSize); j++){
            // if current index has an island, lets find out its area
            if(grid[i][j] == 1){
                int currenArea = dfs(grid, gridSize, *gridColSize, i, j);
                maxArea = MAX(maxArea, currenArea);
            }
        }
    }
    
    return maxArea;
}
