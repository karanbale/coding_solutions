/*

Note: Try to solve this task in-place (with O(1) additional memory), since this is what you'll be asked to do during an interview.

You are given an n x n 2D matrix that represents an image. Rotate the image by 90 degrees (clockwise).

Example

For

a = [[1, 2, 3],
     [4, 5, 6],
     [7, 8, 9]]
the output should be

rotateImage(a) =
    [[7, 4, 1],
     [8, 5, 2],
     [9, 6, 3]]
Input/Output

[execution time limit] 0.5 seconds (c)

[input] array.array.integer a

Guaranteed constraints:
1 ≤ a.length ≤ 100,
a[i].length = a.length,
1 ≤ a[i][j] ≤ 104.

[output] array.array.integer

NOTES:
To access elements in C, please refer to following function/definitions:

typedef struct arr_integer {
int size;
int arr[];
};
typedef struct arr_arr_integer {
int size;
arr_integer arr[];
};

*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
int size;
int arr[];
} arr_integer;

typedef struct {
int size;
arr_integer *arr;
} arr_arr_integer;

arr_arr_integer alloc_arr_arr_integer(int len) {
  arr_arr_integer a = {len, len > 0 ? malloc(sizeof(arr_integer) * len) : NULL};
  return a;
}

/**********************************************************************************************************/
/* Solution 1 */
/**********************************************************************************************************/

arr_arr_integer rotateImage1(arr_arr_integer a) {

    int b[a.size][a.size];

    for(int i=0; i<a.size;i++){
        for(int j=0; j<a.size;j++){
    //      printf("i=%d, j=%d, %d\t",i,j,a.arr[i].arr[j]);
    //      printf("size: %d\n", a.arr[i].size);
            b[i][j]=a.arr[i].arr[j];
        }
    }

    for(int i=0; i<a.size; i++){        
        for(int j=0; j<a.size; j++){            
            a.arr[i].arr[j] = b[a.size-j-1][i];
        }
    }

    return a;
}

/**********************************************************************************************************/
/* Solution 2 */
/**********************************************************************************************************/

arr_arr_integer rotateImage(arr_arr_integer a) {

    int max_size = a.size;

    for(int i=0; i<max_size/2+max_size%2; i++){        
        for(int j=0; j<max_size/2; j++){
            int temp = a.arr[i].arr[j];
            a.arr[i].arr[j] = a.arr[max_size-1-j].arr[i];
            a.arr[max_size-1-j].arr[i] = a.arr[max_size-1-i].arr[max_size-1-j];
            a.arr[max_size-1-i].arr[max_size-1-j] = a.arr[j].arr[max_size-1-i];
            a.arr[j].arr[max_size-1-i] = temp;
        }
    }

    return a;
}
