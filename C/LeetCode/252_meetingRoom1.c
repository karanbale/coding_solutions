/*
Given an array of meeting time intervals where intervals[i] = [starti, endi],
determine if a person could attend all meetings.

Example 1:
Input: intervals = [[0,30],[5,10],[15,20]]
Output: false

Example 2:
Input: intervals = [[7,10],[2,4]]
Output: true

Constraints:

0 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti < endi <= 106
*/

#include "../standardHeaders.h"

int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}


bool canAttendMeetings(int** intervals, int intervalsSize, int* intervalsColSize){
    
    if((intervals == NULL) || (intervalsSize == 0)){
        return true;
    }
    
    qsort((void *)intervals, intervalsSize, sizeof(int*), cmp);
    for(int i=0; i<intervalsSize-1; i++){
        if(intervals[i][1] > intervals[i+1][0]){
            return false;
        }
        // printf("temp: [%d, %d]\n", intervals[0], intervals[1]);
    }
    
    return true;
    
}
