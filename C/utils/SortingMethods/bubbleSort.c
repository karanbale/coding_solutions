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

    int i, j;
    for(i=0; i<arr_size; i++){
        bool swappingDone = false;
        for(j=0; j<(arr_size-i); j++){
            if(input_arr[j] > input_arr[j+1]){
                swappingDone = true;
                swap(&input_arr[j], &input_arr[j+1]);
            }
        }
        if(!swappingDone){
            break;
        }
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