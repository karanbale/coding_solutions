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

Time complexity : O(mn)O(mn).

If you are having difficulty to derive the time complexity, start simple.

Let us start with the case with only one gate. 
The breadth-first search takes at most m×n steps to reach all rooms,
therefore the time complexity is O(mn). But what if you are doing breadth-first search from k gates?

Once we set a room's distance, we are basically marking it as visited,
which means each room is visited at most once. Therefore, the time complexity does not depend on the number of gates and is O(mn).

Space complexity : O(mn).
The space complexity depends on the queue's size. We insert at most m×n points into the queue.

*/


#include "../standardHeaders.h"

#define GATE 0
#define EMPTY 2147483647
#define WALL -1

int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

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

void wallsAndGates(int** rooms, int roomsSize, int* roomsColSize){
    
    if(roomsSize == 0 || *roomsColSize == 0) return;
    
    int numOfRows = roomsSize;
    int numOfCols = *roomsColSize;
    
    queue_t *queue = createQueue(numOfRows*numOfCols);
    
    // iterate over entire grid and find out where GATE is located
    // add the GATE to our list for traversal
    for(int r=0; r < numOfRows; r++) {
        for(int c=0; c < numOfCols; c++) {
            if(rooms[r][c] == GATE) {
                insertQueue(queue, r, c);
            }
        }
    }
    
    // iterate over all GATEs and traverse away from GATE
    // for each successful empty room, increment its count as distance
    while(!isQueueEmpty(queue)){
        int rowIdx = removeQueueRow(queue);
        int colIdx = removeQueueCol(queue);
        for(int i=0; i < 4; i++) {
            int r = rowIdx + directions[i][0];
            int c = colIdx + directions[i][1];
            if(r >= numOfRows || c >= numOfCols ||
               r < 0 || c < 0 || rooms[r][c] != EMPTY)
                continue;
            rooms[r][c] = rooms[rowIdx][colIdx]+1;
            insertQueue(queue, r, c);
        }
    }

}
