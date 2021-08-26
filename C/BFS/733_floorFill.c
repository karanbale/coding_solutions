/*
An image is represented by an m x n integer grid image where image[i][j] represents the pixel value of the image.

You are also given three integers sr, sc, and newColor. You should perform a flood fill on the image starting from the pixel image[sr][sc].

To perform a flood fill, consider the starting pixel,
plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel,
plus any pixels connected 4-directionally to those pixels (also with the same color), and so on. Replace the color of all of the aforementioned pixels with newColor.

Return the modified image after performing the flood fill.

 

Example 1:


Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation: From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel),
all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected to the starting pixel.
Example 2:

Input: image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, newColor = 2
Output: [[2,2,2],[2,2,2]]
 

Constraints:

m == image.length
n == image[i].length
1 <= m, n <= 50
0 <= image[i][j], newColor < 216
0 <= sr < m
0 <= sc < n
*/

#include "../standardHeaders.h"

typedef struct queue{
    int front;
    int rear;
    int queueItemCount;
    int queueSize;
    int *rowArr;
    int *colArr;
}queue_t;

typedef struct rowCol{
    int rowIdx;
    int colIdx;
}rowCol_t;

bool isQueueEmpty(queue_t *queue){
    return queue->queueItemCount == 0;
}

queue_t *createQueue(int queueSize){
    queue_t *queue = malloc(sizeof(queue_t));
    if(!queue)  return NULL;
    queue->front = 0;
    queue->rear = -1;
    queue->queueItemCount = 0;
    queue->rowArr = malloc(sizeof(int)*queueSize);
    if(!queue->colArr)  return NULL;
    queue->colArr = malloc(sizeof(int)*queueSize);
    if(!queue->colArr)  return NULL;
    return queue;
}

void queueEnqueue(queue_t *queue, int row, int col){
    // check if queue is full
    queue->rowArr[++queue->rear] = row;
    queue->colArr[queue->rear] = col;
    queue->queueItemCount++;
}

int queueRowDequeue(queue_t *queue){
    if(isQueueEmpty(queue)) return 0;
    return queue->rowArr[queue->front];
}

int queueColDequeue(queue_t *queue){
    if(isQueueEmpty(queue)) return 0;
    return queue->colArr[queue->front++];
}

rowCol_t *queueDequeue(queue_t *queue){
    rowCol_t *rowCol= malloc(sizeof(rowCol_t));
    rowCol->rowIdx = queueRowDequeue(queue);
    rowCol->colIdx = queueColDequeue(queue);
    queue->queueItemCount--;
    return rowCol;
}

void destroyQueue(queue_t *queue){
    free(queue->rowArr);
    free(queue->colArr);
    free(queue);
}


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int newColor, int* returnSize, int** returnColumnSizes){
    
    int rowSize = imageSize, colSize = *imageColSize;
    if(!colSize || !rowSize) return NULL;
    int visited[rowSize][colSize];
    memset(visited, 0, sizeof(int)*rowSize*colSize);

    queue_t *queue = createQueue(rowSize*colSize);
    *returnSize = imageSize;
    *returnColumnSizes = malloc(sizeof(int)*imageSize);
    for(int k=0;k<imageSize;k++)
        (*returnColumnSizes)[k] = *imageColSize;

    if(newColor == image[sr][sc])   return image;
    
    int startingColor = image[sr][sc];
    image[sr][sc] = newColor;
    queueEnqueue(queue,sr,sc);
    while(!isQueueEmpty(queue)){
        int currLevelNodeCount = queue->queueItemCount;
        int levelItemCount = 0;
        // iterate over all items in queue, pop them one at a time and add their kids to queue
        // until queue is empty
        while(currLevelNodeCount > levelItemCount){
            rowCol_t *rowCol = queueDequeue(queue);
            int rowIdx = rowCol->rowIdx;
            int colIdx = rowCol->colIdx;
            --currLevelNodeCount;
            free(rowCol);
            if(visited[rowIdx][colIdx] == 1) continue;
            if((rowIdx-1 >= 0) && (visited[rowIdx-1][colIdx] != 1) && (image[rowIdx-1][colIdx] == startingColor)){
                queueEnqueue(queue,rowIdx-1,colIdx);
                image[rowIdx-1][colIdx] = newColor;
                levelItemCount++;
            }
            if((rowIdx+1 < rowSize) && (visited[rowIdx+1][colIdx] != 1) && (image[rowIdx+1][colIdx] == startingColor)){
                queueEnqueue(queue,rowIdx+1,colIdx);
                image[rowIdx+1][colIdx] = newColor;
                levelItemCount++;
            }
            if((colIdx-1 >= 0) && (visited[rowIdx][colIdx-1] != 1) && (image[rowIdx][colIdx-1] == startingColor)) {
                queueEnqueue(queue,rowIdx,colIdx-1);
                image[rowIdx][colIdx-1] = newColor;
                levelItemCount++;
            }
            if((colIdx+1 < colSize) && (visited[rowIdx][colIdx+1] != 1) && (image[rowIdx][colIdx+1] == startingColor)) {
                queueEnqueue(queue,rowIdx,colIdx+1);
                image[rowIdx][colIdx+1] = newColor;
                levelItemCount++;
            }
            visited[rowIdx][colIdx] = 1;
        }
    }
    
    destroyQueue(queue);
    return image;

}

/*
[[1,1,1],[1,1,1]]
1
1
1
[[0,0,1],[1,1,1]]
1
1
1
[[1,1,1],[1,1,0],[1,0,1]]
1
1
2
[[0,0,0],[0,1,1]]
1
1
1
*/