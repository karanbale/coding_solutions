/*
Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, 
and return an array of the non-overlapping intervals that cover all the intervals in the input.

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

Constraints:

1 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 104

*/

#include "../standardHeaders.h"

int cmpfunc(int **a, int **b)
{
    return (*a)[0] - (*b)[0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    int* temp=NULL;
    int retArrIdx = 0;
    
    int* col = malloc(sizeof(int)*intervalsSize);
    for(int i =0; i<intervalsSize; i++){
        col[i] = 2;
    }
    
    if((intervals==NULL) || (intervalsSize==0))
    {
        *returnSize = 0;
        return NULL;
    }
    
    qsort((void *)intervals, intervalsSize, sizeof(int*), cmpfunc);
    
    temp = intervals[0];
    printf("temp[0]: %d,temp[1] %d\n", temp[0], temp[1]);
    for(int i=1;i<intervalsSize;i++)
    {
        if(temp[1] >= intervals[i][0])
        {
            temp[1] = (temp[1] > intervals[i][1])?temp[1]:intervals[i][1];
        }
        else
        {
            intervals[retArrIdx][0] = temp[0];
            intervals[retArrIdx][1] = temp[1];
            retArrIdx++;
            temp = intervals[i];
        }
    }

    intervals[retArrIdx][0] = temp[0];
    intervals[retArrIdx][1] = temp[1];
    retArrIdx++;

    *returnColumnSizes = col;
    *returnSize = retArrIdx;
    return intervals;
}

