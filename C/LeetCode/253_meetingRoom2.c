/*

Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

Example 1:

Input: [[0, 30],[5, 10],[15, 20]]
Output: 2
Example 2:

Input: [[7,10],[2,4]]
Output: 1

*/

#include "../standardHeaders.h"

void printArr(int **A, int r, int c){
    for (int i = 0; i <  r; i++){
        printf("[");
        for (int j = 0; j < c; j++){
            printf(" %d ", A[i][j]);
        }
        printf("]\n");
    }
}

int cmp(int **a, int **b){
    if (((*a)[0]) != ((*b)[0]))    return (**a - **b);
    else                       return (**b - **a);
}

int minMeetingRooms(int** intervals, int intervalsSize, int* intervalsColSize){
    
    if((intervals == NULL) || (intervalsSize == 0)){
        return 0;
    }
    
    qsort((void *)intervals, intervalsSize, sizeof(int*), cmp);
    
    int meetingRoomsRequired = intervalsSize;
    int *overlapTime = NULL;
    bool overlapfound = false;
    overlapTime = intervals[0];
    int i, max = 0;
    int retArrIdx = 0;
    
    // put all time in a array, mark 1 as start and mark -1 as end
    int **events=NULL;
    events = (int**)malloc(intervalsSize*2*sizeof(int*));
    for(i=0;i<intervalsSize;i++)
    {   
        events[i*2] = (int*)malloc(2*sizeof(int));
        events[i*2][0] = intervals[i][0];
        events[i*2][1] = 1;
        events[i*2+1] = (int*)malloc(2*sizeof(int));
        events[i*2+1][0] = intervals[i][1];
        events[i*2+1][1] = -1;
    }
    
    // sort entire array so that start and end times are organized in correct sequence
    qsort(events,intervalsSize*2,sizeof(int*), cmp);
    
    // printArr(events, intervalsSize*2, 2);
    // track running sum and max
    // acquiring and releasing rooms in orderly fashion
    // will keep the room count in check
    int runningSum = 0;
    for(i=0;i<intervalsSize*2;i++)
    {
        // everytime we acquire a room
        if(events[i][1] > 0)
            runningSum++;
        // everytime we leave a room
        else
            runningSum--;
        printf("remaining sum: %d\n", runningSum);
        // keep track of how many rooms are we occupying
        if(runningSum > max)
            max = runningSum;
        free(events[i]);
    }
    free(events);
    return max;   
}

