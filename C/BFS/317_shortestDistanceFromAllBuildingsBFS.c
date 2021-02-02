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

/*
Complexity analysis

Time complexity : O(MxNxK), 
    where m = number of rows, n = number of cols, k = number of gates.

Let us start with the case with only one building. 
The breadth-first search takes at most m×n steps to reach all empty spaces,
therefore the time complexity is O(MxN). 
And we are doing breadth-first search from K gates, thus O(MxNxK)

Space complexity : O(MxN).
The space complexity depends on the queue's size. We insert at most MxN points into the queue.

*/

#include "../standardHeaders.h"

#define EMPTY_LAND  0
#define BUILDING    1
#define OBSTACLE    2

#define MIN(x,y) ((x) < (y) ? (x) : (y))

int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

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

static inline int getQueueSize(queue_t *queue){
    return queue->numOfItems;
}

static inline bool isQueueEmpty(queue_t *queue){
    return queue->numOfItems == 0;
}

static inline void queueEnqueue(queue_t *queue, int rowIdx, int colIdx){
    queue->arrayRows[++queue->rear] = rowIdx;
    queue->arrayCols[queue->rear] = colIdx;
    queue->numOfItems++;
}

static inline int queueDequeueRow(queue_t *queue){
    return queue->arrayRows[queue->front];
}

static inline int queueDequeueCol(queue_t *queue){
    queue->numOfItems--;
    return queue->arrayCols[queue->front++];
}

static inline void freeQueue(queue_t *queue){
    free(queue->arrayRows);
    free(queue->arrayCols);
    free(queue);
}

void printArray(int rowIdxSize, int colIdxSize, int grid[][colIdxSize]){
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

static inline void resetArr(int rowSize, int colSize, int Arr[][colSize]){
    for(int i = 0; i<rowSize; i++){
        for(int j = 0; j<colSize; j++){
            Arr[i][j] = 0;
        }
    }
}

int shortestDistance(int** grid, int gridSize, int* gridColSize){
    
    if((gridSize == 0) || (*gridColSize == 0))  return -1;
    
    int numOfRows = gridSize;
    int numOfCols = *gridColSize;
    int minDistance = INT32_MAX;
    int queueSize = numOfRows*numOfCols;
    
    // 2D-array to calculate total distance for each EMPTY_LAND to all buildings it can reach
    int distance[numOfRows][numOfCols];
    resetArr(numOfRows, numOfCols, distance);
    // 2D-array to keep track of number of buildings we can reach from an EMPTY_LAND
    int reach[numOfRows][numOfCols];
    resetArr(numOfRows, numOfCols, reach);
    // 2D-Array to keep track of visited nodes of input grid
    int visited[numOfRows][numOfCols];
    resetArr(numOfRows, numOfCols, visited);
    
    int numOfBuildings = 0;
    for(int row=0; row<numOfRows; row++){
        for(int col=0; col<numOfCols; col++){     
            if(grid[row][col] == BUILDING){
                numOfBuildings++;
                int level=1;
                // create queue for traversal of each building
                queue_t *queue = createQueue(queueSize);
                queueEnqueue(queue, row, col);
                // reset visited array since its new traversal
                resetArr(numOfRows, numOfCols, visited);
                // traverse until all nodes are visited
                while(!isQueueEmpty(queue)){
                    int currLevelNodeCount = getQueueSize(queue);
                    // iterate over all nodes found at current level
                    // add each child node of current node to queue
                    for(int k=0; k<currLevelNodeCount; k++){
                        int rowIdx = queueDequeueRow(queue);
                        int colIdx = queueDequeueCol(queue);
                        // traverse in all 4 directions of current node and find its valid child node
                        // if this child is already visited or is NOT a land, ignore it
                        for(int i=0; i<4; i++){
                            int r = rowIdx + directions[i][0];
                            int c = colIdx + directions[i][1];
                            if((r >= 0) && (r < numOfRows) && (c >= 0) && (c < numOfCols) && (!visited[r][c]) && (grid[r][c] == EMPTY_LAND)){
                                // add level count to current count
                                distance[r][c] += level;
                                // printArray(numOfRows, numOfCols, distance);
                                reach[r][c]++;
                                visited[r][c] = 1;
                                queueEnqueue(queue, r, c);
                            }
                        }
                    }
                    level++;
                }
                freeQueue(queue);
            }
        }
    }
    
    // printArray(numOfRows, numOfCols, distance);
    // printArray(numOfRows, numOfCols, visited);
    // printArray(numOfRows, numOfCols, reach);
    
    for (int i = 0; i < numOfRows; i++) {
        for (int j = 0; j < numOfCols; j++) {
            // check if current node can reach all the buildings or not
            if (grid[i][j] == EMPTY_LAND && reach[i][j] == numOfBuildings) {
                minDistance = fmin(minDistance, distance[i][j]);
            }
        }
    }
    
    return (minDistance == INT32_MAX) ? -1 : minDistance;
    
}
