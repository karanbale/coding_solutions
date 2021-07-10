/*
You are given a m x n 2D grid initialized with these three possible values.

-1 : A wall or an obstacle.

0 : A gate.

INF : Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF,
as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate,
it should be filled with INF.

Example:

Given the 2D grid:

INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF

After running your function, the 2D grid should be:

  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4

*/

/*
Complexity analysis

Time complexity : O(mn x k).
For each gate k, we will visit (m x n) empty rooms.

Space complexity : O(mn).
We may invoke at max (mxn) recursive dfs function calls.
*/

#include "DFS_Header.h"
#include "common.h"

void dfs(int** rooms, int i, int j, int x, int y, int count) {
    if(count < rooms[i][j])
        rooms[i][j] = count;
    
    count++;
    if((i>0)&&(rooms[i-1][j] > count))
            dfs(rooms,i-1,j,x,y,count);
    if((i<x-1) &&(rooms[i+1][j] > count))
            dfs(rooms,i+1,j,x,y,count);
    if((j>0) && (rooms[i][j-1] > count))
            dfs(rooms,i,j-1,x,y,count);
    if((j<y-1) && (rooms[i][j+1] > count))
            dfs(rooms,i,j+1,x,y,count);
}

void wallsAndGates(int** rooms, int roomsSize, int* roomsColSize) {
    
    for(int i=0; i<roomsSize; i++){
        for(int j=0; j<*roomsColSize; j++){
            // found a gate, issue DFS 
            if(rooms[i][j] == 0){
                dfs(rooms, i, j, roomsSize, *roomsColSize, 0);
            }
        }
    }
}

/*
Sample inputs to test:

[[2147483647,-1,0,2147483647],[2147483647,2147483647,2147483647,-1],[2147483647,-1,2147483647,-1],[0,-1,2147483647,2147483647]]

[[-1,2147483647,0,2147483647,-1,2147483647,-1,-1,-1,0,0,2147483647,-1,0,0,0,0,0,-1,0,0,2147483647,0,2147483647,2147483647,-1,2147483647,-1,2147483647,-1,-1,-1,0]]

[[0,2147483647,0,2147483647],[-1,-1,-1,-1],[2147483647,2147483647,2147483647,2147483647]]
*/
