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

#include "../standardHeaders.h"

typedef struct queue{
    int front;
    int rear;
    int currItemCount;
    int *arrayRow;
    int *arrayCol;
}queue_t;

queue_t *createQueue(int queueSize){
    queue_t *queue = (queue_t *) malloc(sizeof(queue_t));
    if(!queue){
        return NULL;
    }
    queue->front = 0;
    queue->rear = -1;
    queue->currItemCount = 0;
    queue->arrayRow = (int *) malloc(sizeof(int)*queueSize) ;
    queue->arrayCol = (int *) malloc(sizeof(int)*queueSize) ;
    if(!(queue->arrayRow) || !(queue->arrayCol)){
        return NULL;
    }
    return queue;
}

void insertQueue(queue_t *queue, int rowIdx, int colIdx){
    queue->arrayRow[++queue->rear] = rowIdx;
    queue->arrayCol[queue->rear] = colIdx;
    queue->currItemCount++;
}

int removeQueueRow(queue_t *queue){
    return queue->arrayRow[queue->front];
}

int removeQueueCol(queue_t *queue){
    queue->currItemCount--;
    return queue->arrayCol[queue->front++];
}

bool isQueueEmpty(queue_t *queue){
    return queue->currItemCount == 0;
}

void freeQueue(queue_t *queue){
    free(queue->arrayRow);
    free(queue->arrayCol);
    free(queue);
}

int numIslands(char** grid, int gridSize, int* gridColSize)
{
    int i = 0, j = 0;
    int islandCount = 0;
    
    int numOfRows = gridSize;
    int numOfCols = *gridColSize;
    
    queue_t *queue = createQueue(numOfRows*numOfCols);
    
    for(i = 0; i < numOfRows; i++)
    {
        for(j = 0; j < numOfCols; j++)
        {
            if(grid[i][j] == '1')
            {
                int keyHash = i*numOfCols+j;
                islandCount++;
                insertQueue(queue, i, j);
                grid[i][j] = '0';
                while(!isQueueEmpty(queue)){
                    int rowIdx = removeQueueRow(queue);
                    int colIdx = removeQueueCol(queue);
                    if((rowIdx-1) >= 0 && grid[rowIdx-1][colIdx] == '1'){
                        insertQueue(queue, rowIdx-1, colIdx);
                        grid[rowIdx-1][colIdx] = '0';
                    }
                    if((rowIdx+1) < numOfRows && grid[rowIdx+1][colIdx] == '1'){
                        insertQueue(queue, rowIdx+1, colIdx);
                        grid[rowIdx+1][colIdx] = '0';
                    }
                    if((colIdx-1) >= 0 && grid[rowIdx][colIdx-1] == '1'){
                        insertQueue(queue, rowIdx, colIdx-1);
                        grid[rowIdx][colIdx-1] = '0';
                    }
                    if((colIdx+1) < numOfCols && grid[rowIdx][colIdx+1] == '1'){
                        insertQueue(queue, rowIdx, colIdx+1);
                        grid[rowIdx][colIdx+1] = '0';
                    }
                }
            }
        }
    }
    freeQueue(queue);
    return islandCount;
}
