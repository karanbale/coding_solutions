
#include "sortingMethods.h"

void selectionSort(int input_arr[], int arr_size);

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


void selectionSort(int input_arr[], int arr_size){

    int i, j, iMin;
    /*
    Iterate over the array.
    Key is, to keep sorted elements at the beginning of the array.
    Everything on the left hand side of ith index will be sorted.
    Everything on the right hand side of the ith index will be unsorted.
    */
    for(i=0; i<(arr_size-1); i++){
        iMin = i;
        /*
        Iterate over remaining array after ith index.
        Find elements smaller than ith index element.
        */
        for(j=i+1; j<(arr_size); j++){
            if(input_arr[j] < input_arr[iMin]){
                iMin = j;
            }
        }
        /*
        Swap the smallest found element with ith index element
        */
        swap(&input_arr[iMin], &input_arr[i]);
    }

}

int main(void){

    int arr_size = 7;
    int input_arr[7] = {10,40,80,70,50,20,15};

    printArray(input_arr, arr_size);

    selectionSort(input_arr, arr_size);

    printArray(input_arr, arr_size);

    return 0;
}
