#include "common.h"

char *int2bin(int a, char *buffer, int buf_size) {
    buffer += (buf_size);
    *buffer-- = '\0';
    for (int i = buf_size-1; i >= 0; i--) {
        *buffer-- = (a & 1) + '0';

        a >>= 1;
    }

    return buffer+1;
}

int numOf1sInNum(int num) {
    int totalOnes = 0;
    while(num){
        num &= (num-1);
        totalOnes++;
    }
    return totalOnes;
}

void printArr(int *nums, int numsSize) {
    printf("[");
    for(int i=0; i<numsSize; i++){
        printf("%d,",nums[i]);
    }
    printf("]\n");
}

void printArray_2D(char **grid, int rowIdxSize, int colIdxSize) {
    printf("[\n");
    for(int i=0; i<rowIdxSize; i++){
        printf("[");
        for(int j=0; j<colIdxSize; j++){
            printf("%c,", grid[i][j]);
        }
        printf("],\n");
    }
    printf("]\n");
}

void swap(int *idx1, int *idx2) {
    int temp = *idx1;
    *idx1 = *idx2;
    *idx2 = temp;
}

int cmpInt(const void * a, const void * b) {
    return (*(int*)a - *(int*)b);
}

void bubble_sort(int *nums, int start, int end) {
    for(int i=end; i>=start; i--){
        int has_sorted = 0;
        for(int j=start; j<i; j++){
            if(nums[j] > nums[j+1]){
                swap(&nums[j], &nums[j+1]);
                has_sorted = 1;
            }
        }
        if(has_sorted == 0){
            break;
        }
    }
}
