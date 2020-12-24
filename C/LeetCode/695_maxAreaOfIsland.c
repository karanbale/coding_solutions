/*
Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land),
connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)

Example 1:

[[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]
Given the above grid, return 6. Note the answer is not 11, because the island must be connected 4-directionally.
Example 2:

[[0,0,0,0,0,0,0,0]]
Given the above grid, return 0.
Note: The length of each dimension in the given grid does not exceed 50.
*/

#include "../standardHeaders.h"

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

int dfs(int** grid, int gridSize, int gridColSize, int rowIdx, int colIdx){
    
    // edge cases
    if((rowIdx < 0) || (rowIdx>=gridSize) || (colIdx >=gridColSize) || (colIdx < 0) || (grid[rowIdx][colIdx] == 0)){
        return 0;
    }

    // since we're visiting this island, make it 0
    grid[rowIdx][colIdx] = 0;
    
    // count in all the 4 directions of current island, see if there is an island
    // add 1 to the count, since currently we're already on an island, count its area
    return (1 + dfs(grid, gridSize, gridColSize, rowIdx-1, colIdx) + 
                dfs(grid, gridSize, gridColSize, rowIdx+1, colIdx) +
                dfs(grid, gridSize, gridColSize, rowIdx, colIdx-1) +
                dfs(grid, gridSize, gridColSize, rowIdx, colIdx+1));

}

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize){
    
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

/*
Sample input to test:
[[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],
[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],
[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
*/