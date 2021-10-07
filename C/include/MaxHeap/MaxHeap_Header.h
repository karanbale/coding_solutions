#include "../../standardHeaders.h"

typedef struct heapStruct {
    size_t freqCount;
    size_t nextIndex;
}heapStruct_t;

char * rearrangeStringKDistanceApart(char * S, int K);

char* reorganizeString(char* S);

double mincostToHireWorkers(int* quality, int qualitySize, int* wage, int K);
