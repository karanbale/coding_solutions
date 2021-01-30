/*
In a given grid, each cell can have one of three values:

the value 0 representing an empty cell;
the value 1 representing a fresh orange;
the value 2 representing a rotten orange.
Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange.
If this is impossible, return -1 instead.

Example 1:
Input: [[2,1,1],[1,1,0],[0,1,1]]
Output: 4

Example 2:
Input: [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation:  The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.

Example 3:
Input: [[0,2]]
Output: 0
Explanation:  Since there are already no fresh oranges at minute 0, the answer is just 0.

Note:

1 <= grid.length <= 10
1 <= grid[0].length <= 10
grid[i][j] is only 0, 1, or 2.
*/

#include "../standardHeaders.h"

#define EMPTY 0
#define FRESH 1
#define ROTTEN 2

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
    queue->arrayRow = (int *) malloc(sizeof(int)*queueSize);
    queue->arrayCol = (int *) malloc(sizeof(int)*queueSize);
    if(!queue->arrayRow || !queue->arrayCol){
        return NULL;
    }
    return queue;
}

bool isQueueEmpty(queue_t *queue){
    return queue->currItemCount == 0;
}

void queueEnqueue(queue_t *queue, int rowIdx, int colIdx){
    queue->arrayRow[++queue->rear] = rowIdx;
    queue->arrayCol[queue->rear] = colIdx;
    queue->currItemCount++;
}

int queueDequeueRow(queue_t *queue){
    return queue->arrayRow[queue->front];
}

int queueDequeueCol(queue_t *queue){
    queue->currItemCount--;
    return queue->arrayCol[queue->front++];
}

void freeQueue(queue_t *queue){
    free(queue->arrayRow);
    free(queue->arrayCol);
    free(queue);
}

void printQueue(queue_t *queue, int queueSize){
    printf("Row:    [");
    for(int i=0; i<queueSize; i++){
        printf("%d,",queue->arrayRow[i]);
    }
    printf("]\n");
    printf("Column: [");
    for(int i=0; i<queueSize; i++){
        printf("%d,",queue->arrayCol[i]);
    }
    printf("]\n");
}

int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int orangesRotting(int** grid, int gridSize, int* gridColSize){
    
    if((gridSize == 0) || (*gridColSize == 0)){
        return 0;
    }
    
    int numOfRows = gridSize;
    int numOfCols = *gridColSize;
    int freshOranges = 0;
    int queueSize = numOfCols*numOfRows*2;
    
    queue_t *queue = createQueue(queueSize);
    
    for(int i=0; i<numOfRows; i++){
        for(int j=0; j<numOfCols; j++){
            if(grid[i][j] == ROTTEN){
                queueEnqueue(queue, i, j);
            }
            else if(grid[i][j] == FRESH){
                freshOranges++;
            }
        }
    }
    
    queueEnqueue(queue, -1, -1);
    int minutesElapsed = -1;
    // printQueue(queue, numOfRows, numOfCols);
    while(!isQueueEmpty(queue)){
        // printQueue(queue, queueSize);
        int rowIdx = queueDequeueRow(queue);
        int colIdx = queueDequeueCol(queue);
        if(rowIdx == -1){
            minutesElapsed++;
            if(!isQueueEmpty(queue)){
                queueEnqueue(queue, -1, -1);
            }
            // printf("\nAdding -1 again\n");
            // printQueue(queue, queueSize);
        }
        else{
            for(int i=0; i<4; i++){
                int r = rowIdx + directions[i][0];
                int c = colIdx + directions[i][1];
                if(r >= 0 && r < numOfRows && c >= 0 && c < numOfCols){
                    if(grid[r][c] == FRESH){
                        grid[r][c] = ROTTEN;
                        freshOranges--;
                        queueEnqueue(queue, r, c);
                    }
                }
            }
            // printQueue(queue, queueSize);
        }
    }
    
    freeQueue(queue);
    return freshOranges == 0 ? minutesElapsed : -1;
    
}
