/*
*/

#include "../standardHeaders.h"

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int minMeetingRooms(int ** intervals, int intervalsSize, int * intervalsColSize)
{
    if(intervalsSize == 0) return 0;
    
    int startTimes[intervalsSize];
    int endTimes[intervalsSize];
    
    // separate out start times and end times
    for(int i=0; i<intervalsSize; i++){
        startTimes[i] = intervals[i][0];
        endTimes[i] = intervals[i][1];
    }

    // sort start times and end times
    qsort(startTimes,  intervalsSize, sizeof(startTimes[0]), cmpfunc);
    qsort(endTimes,  intervalsSize, sizeof(endTimes[0]), cmpfunc);

    int startPtr = 0, endPtr = 0, minRoomsRequired=0;
    // until all start times are not evaluated, keep going
    while(startPtr < intervalsSize){
        // if start time is >= end time, a meeting has ended
        // increment endPtr, to evaluate next endTime
        // we can reduce required room count by 1, since meeting is finished
        if(startTimes[startPtr] >= endTimes[endPtr]){
            minRoomsRequired -= 1;
            endPtr++;
        }
        // we will need a room at the start of each meetings,regardless if we use it or not
        // we must evaluate each starting point
        minRoomsRequired += 1;
        startPtr++;
    }
    return minRoomsRequired;
}