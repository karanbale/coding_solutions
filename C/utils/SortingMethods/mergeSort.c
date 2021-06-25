#include "sortingMethods.h"

void printArray(int input_arr[], int arr_size);
void mergeSort(int input_arr[], int left, int right);
void merge(int input_arr[], int left, int mid, int right);

/* Function to print an array */
void printArray(int input_arr[], int arr_size){ 
    int i;
    printf("[");
    for (i=0; i < arr_size; i++) 
        printf("%d ", input_arr[i]); 
    printf("]\n");
}

// A utility function to swap two elements 
void merge(int input_arr[], int left, int mid, int right){

    printf("merging left index: %d, with right index: %d\n", left, right);

    // first subarray is arr[left ... mid]
    // second subarray is arr[mid-1 ... right]
    // we want to merge above two arrays in sorted manner

    // find length of first subarray
    int leftSubArrLen = (mid - left + 1);
    // find length of second subarray
    int rightSubArrLen = (right - mid);

    printf("leftArrLen: %d, rightArrLen: %d\n\n", leftSubArrLen, rightSubArrLen);

    // create temp sub arrays with above size and copy their respective data in those arrays
    int leftSubArr[leftSubArrLen];
    int rightSubArr[rightSubArrLen];

    for(int i=0; i<leftSubArrLen; i++){
        leftSubArr[i] = input_arr[left + i];
    }
    for(int i=0; i<rightSubArrLen; i++){
        rightSubArr[i] = input_arr[mid + 1 + i];
    }

    int leftSubArrIdx = 0, rightSubArrIdx = 0, combinedSubArrIdx = left;
    while(leftSubArrIdx<leftSubArrLen && rightSubArrIdx<rightSubArrLen){
        if(leftSubArr[leftSubArrIdx] <= rightSubArr[rightSubArrIdx]){
            input_arr[combinedSubArrIdx] = leftSubArr[leftSubArrIdx];
            leftSubArrIdx++;
        }
        else{
            input_arr[combinedSubArrIdx] = rightSubArr[rightSubArrIdx];
            rightSubArrIdx++;
        }
        combinedSubArrIdx++;
    }

    // copy remaining elements of leftSubArray
    while(leftSubArrIdx < leftSubArrLen){
        input_arr[combinedSubArrIdx] = leftSubArr[leftSubArrIdx];
        leftSubArrIdx++;
        combinedSubArrIdx++;
    }
    // copy remaining elements of rightSubArray
    while(rightSubArrIdx < rightSubArrLen){
        input_arr[combinedSubArrIdx] = rightSubArr[rightSubArrIdx];
        rightSubArrIdx++;
        combinedSubArrIdx++;
    }

}

void mergeSort(int input_arr[], int left, int right){

    if(left < right){
        int mid = (left + (right-1))/2;
        printf("mid:%d\n",mid);
        mergeSort(input_arr, left, mid);
        mergeSort(input_arr, mid+1, right);
        merge(input_arr, left, mid, right);
    }
}

int main(void){

    int arr_size = 7;
    int input_arr[7] = {10,40,80,70,50,20,15};

    printArray(input_arr, arr_size);

    mergeSort(input_arr, 0, (arr_size-1));

    printArray(input_arr, arr_size);

    return 0;
}