#include "../../standardHeaders.h"

#define ENABLE_PRINTS 0
#define TM_PRINTF(f_, ...) ENABLE_PRINTS? printf((f_), ##__VA_ARGS__) : 0

int numOf1sInNum(int num);
char *int2bin(int a, char *buffer, int buf_size);
void printArr(int *nums, int numsSize);
void printArray_2D(char **grid, int rowIdxSize, int colIdxSize);
void swap(int *idx1, int *idx2);
int cmpInt(const void * a, const void * b);
void bubble_sort(int *nums, int start, int end);
