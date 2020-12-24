/*
You want to build a house on an empty land which reaches all buildings in the shortest amount of distance.
You can only move up, down, left and right. You are given a 2D grid of values 0, 1 or 2, where:

Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.
Example:

Input: [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]

1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0

Output: 7 

Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2),
             the point (1,2) is an ideal empty land to build a house, as the total 
             travel distance of 3+3+1=7 is minimal. So return 7.
Note:
There will be at least one building. If it is not possible to build such house according to the above rules, return -1.

Accepted
81,554
Submissions
192,411
*/

#include "../standardHeaders.h"

#define EMPTY_LAND  0
#define BUILDING    1
#define OBSTACLE    2

#define MIN(x,y) ((x) < (y) ? (x) : (y))

int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

typedef struct emptyPlotData{
    int rowColHash;
    int maxBuildingReachCount;
    int totalMinDistance;
}emptyPlotData_t;

typedef struct queue{
    int front;
    int rear;
    int queueSize;
    int numOfItems;
    int *arrayRows;
    int *arrayCols;
}queue_t;

queue_t *createQueue(int queueSize){
    queue_t *queue = malloc(sizeof(queue_t));
    if(!queue)  return NULL;
    queue->front = 0;
    queue->rear = -1;
    queue->numOfItems = 0;
    queue->arrayRows = malloc(sizeof(int)*queueSize);
    queue->arrayCols = malloc(sizeof(int)*queueSize);
    
    if(!queue->arrayRows || !queue->arrayCols)   return NULL;
    
    return queue;
}

int getQueueSize(queue_t *queue){
    return queue->numOfItems;
}

bool isQueueEmpty(queue_t *queue){
    return queue->numOfItems == 0;
}

void queueEnqueue(queue_t *queue, int rowIdx, int colIdx){
    queue->arrayRows[++queue->rear] = rowIdx;
    queue->arrayCols[queue->rear] = colIdx;
    queue->numOfItems++;
}

int queueDequeueRow(queue_t *queue){
    return queue->arrayRows[queue->front];
}

int queueDequeueCol(queue_t *queue){
    queue->numOfItems--;
    return queue->arrayCols[queue->front++];
}

void freeQueue(queue_t *queue){
    free(queue->arrayRows);
    free(queue->arrayCols);
    free(queue);
}

void printArray(int **grid, int rowIdxSize, int colIdxSize){
    printf("[\n");
    for(int i=0; i<rowIdxSize; i++){
        printf("[");
        for(int j=0; j<colIdxSize; j++){
            printf("%d,", grid[i][j]);
        }
        printf("],\n");
    }
    printf("]\n");
}

int shortestDistance(int** grid, int gridSize, int* gridColSize){
    
    if((gridSize == 0) || (*gridColSize == 0))  return -1;
    
    int numOfRows = gridSize;
    int numOfCols = *gridColSize;
    int minDistance = INT32_MAX;
    int queueSize = numOfRows*numOfCols;
    // emptyPlotData_t *emptyPlotDataArray[queueSize];
    
    int **distance = malloc(sizeof(int *)*numOfRows);
    int **reach = malloc(sizeof(int *)*numOfRows);
    int **visited = malloc(sizeof(int *)*numOfRows);
    for(int i=0; i<numOfRows; i++){
        distance[i] = calloc(numOfCols, sizeof(int));
        visited[i] = calloc(numOfCols, sizeof(int));
        reach[i] = calloc(numOfCols, sizeof(int));
    }
    
    int numOfBuildings = 0;
    for(int row=0; row<numOfRows; row++){
        for(int col=0; col<numOfCols; col++){     
            if(grid[row][col] == BUILDING){
                numOfBuildings++;
                int level=1;
                // printf("Resetting level\n");
                queue_t *queue = createQueue(queueSize);
                // printf("Pushing r: %d, c:%d\n",row, col);
                queueEnqueue(queue, row, col);

                int **visited = malloc(sizeof(int *)*numOfRows);
                for(int k=0; k<numOfRows; k++){
                    visited[k] = calloc(numOfCols, sizeof(int));
                }
                while(!isQueueEmpty(queue)){
                    int qSize = getQueueSize(queue);
                    // printf("Qsize: %d\n",qSize);
                    for(int k=0; k<qSize; k++){
                        int qSize = getQueueSize(queue);
                        int rowIdx = queueDequeueRow(queue);
                        int colIdx = queueDequeueCol(queue);
                        // printf("\t%d LEVEL:popping r:%d, c:%d\n", level, rowIdx, colIdx);
                        for(int i=0; i<4; i++){
                            int r = rowIdx + directions[i][0];
                            int c = colIdx + directions[i][1];
                            if(r >= 0 && r < numOfRows && c >= 0 && c < numOfCols && grid[r][c] == EMPTY_LAND && !visited[r][c]){
                                distance[r][c] += level;
                                //printArray(distance, numOfRows, numOfCols);
                                // printf("\n");
                                reach[r][c]++;
                                visited[r][c] = 1;
                                // printf("\tPushing r: %d, c:%d\n",r, c);
                                queueEnqueue(queue, r, c);
                            }
                        }
                    }
                    level++;
                }
                // printf("\n");
            }
        }
    }
    
    // printArray(distance, numOfRows, numOfCols);
    // printArray(visited, numOfRows, numOfCols);
    // printArray(reach, numOfRows, numOfCols);
    // printArray(grid, numOfRows, numOfCols);
    
    for (int i = 0; i < numOfRows; i++) {
        for (int j = 0; j < numOfCols; j++) {
            if (grid[i][j] == 0 && reach[i][j] == numOfBuildings) {
                minDistance = fmin(minDistance, distance[i][j]);
            }
        }
    }
    
    for(int i=0; i<numOfRows; i++){
        free(distance[i]);
        free(visited[i]);
        free(reach[i]);
    }
    
    free(distance);
    free(visited);
    free(reach);
    
    return (minDistance == INT32_MAX) ? -1 : minDistance;
    
}
