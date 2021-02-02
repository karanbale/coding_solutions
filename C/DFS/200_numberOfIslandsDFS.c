/*
Given an m x n 2d grid map of '1's (land) and '0's (water), return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
You may assume all four edges of the grid are all surrounded by water.

Example 1:
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.
*/

/*
Complexity Analysis

Time complexity : O(MxN) where M is the number of rows and N is the number of columns.

Space complexity : worst case O(M×N) 
in case that the grid map is filled with lands where DFS goes by M×N deep.
*/

#include "../standardHeaders.h"

void dfs(char** grid, int gridSize, int gridColSize, int rowIdx, int colIdx){
    
    grid[rowIdx][colIdx] = '0';
    
    if(((rowIdx - 1) >= 0) && (grid[rowIdx-1][colIdx] == '1'))  dfs(grid, gridSize, gridColSize, rowIdx-1, colIdx);
    
    if(((rowIdx + 1) < gridSize) && (grid[rowIdx + 1][colIdx] == '1')) dfs(grid, gridSize, gridColSize, rowIdx+1, colIdx);
    
    if(((colIdx - 1) >= 0) && (grid[rowIdx][colIdx-1] == '1'))  dfs(grid, gridSize, gridColSize, rowIdx, colIdx-1);
    
    if(((colIdx + 1) < gridColSize) && (grid[rowIdx][colIdx+1] == '1')) dfs(grid, gridSize, gridColSize, rowIdx, colIdx+1);
    
}

int numIslands(char** grid, int gridSize, int* gridColSize){
    
    if((gridSize == 0) || (gridColSize == 0))   return 0;
    // printf("%d\n", *gridColSize);
    size_t numOfIslands = 0;
    for(int i=0; i<gridSize; i++){
        for(int j=0; j< (*gridColSize); j++){
            if(grid[i][j] == '1'){
                numOfIslands++;
                dfs(grid, gridSize, *gridColSize, i, j);
            }
        }
    }
    
    return numOfIslands;
}

/*
Inputs to test:
[["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]] ==> output: 1
[["1","1","1"],["0","1","0"], ["1","0","0"],["1","0","1"]]  ==> output : 3
*/
