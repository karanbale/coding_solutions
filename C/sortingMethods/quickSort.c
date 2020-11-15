
#include "sortingMethods.h"

void quick_sort(int input_arr[], int arr_size, int low, int high);
int partition(int input_arr[], int arr_size, int low, int high);

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

/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
   array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition(int input_arr[], int arr_size, int low, int high){

    int i = low;
    int pivot = input_arr[high];

    for(int j = low; j < high; j++){
        if(pivot >= input_arr[j]){
            swap(&input_arr[j],&input_arr[i]);
            i++;
        }
    }

    printArray(input_arr, )

    swap(&input_arr[i], &input_arr[high]);

    printf("2. [");
    for(int i=0; i<5; i++){
        printf("%d,", input_arr[i]);
    }
    printf("]\n");

    return i;

}

void quick_sort(int input_arr[], int arr_size, int low, int high){

    if(low<high){
        int pivot_index = partition(input_arr, arr_size, low, high);
        quick_sort(input_arr, arr_size, ow, pivot_index-1);
        quick_sort(input_arr, arr_size, pivot_index+1, high);
    }

}

int main(void){

    int arr_size = 5;
    int input_arr[5] = {10,40,80,70,50};

    printf("Before: [");
    for(int i=0; i<5; i++){
        printf("%d,", input_arr[i]);
    }
    printf("]\n");

    quick_sort(input_arr, arr_size, 0, 4);

    printf("After: [");
    for(int i=0; i<5; i++){
        printf("%d,", input_arr[i]);
    }
    printf("]\n");

    return 0;
}
