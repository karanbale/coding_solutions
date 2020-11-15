#include "sortingMethods.h"

void mergeSort(int input_arr[], int arr_size);

/* Function to print an array */
void printArray(int arr[], int size) 
{ 
    int i;
    printf("[");
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("]\n");
}

// A utility function to swap two elements 
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
}

void mergeSort(int input_arr[], int arr_size){

    int i, j, currentValue, leftIndex = 0;
    for(i=1; i<arr_size; i++){
        currentValue = input_arr[i];
        leftIndex = i-1;
        while(leftIndex > 0 && currentValue < input_arr[leftIndex]){
            input_arr[leftIndex+1] = input_arr[leftIndex];
            leftIndex--;
        }
        input_arr[leftIndex+1] = currentValue;
    }
}

int main(void){

    int arr_size = 7;
    int input_arr[7] = {10,40,80,70,50,20,15};

    printArray(input_arr, arr_size);

    mergeSort(input_arr, arr_size);

    printArray(input_arr, arr_size);

    return 0;
}