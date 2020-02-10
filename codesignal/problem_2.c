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

arr_arr_integer rotateImage(arr_arr_integer a) {
    int i=0, j=0;

    int b[a.size][a.size];

    
    for(i=0; i<a.size;i++){
        for(j=0; j<a.size;j++){
    //      printf("i=%d, j=%d, %d\t",i,j,a.arr[i].arr[j]);
    //      printf("size: %d\n", a.arr[i].size);
            b[i][j]=a.arr[i].arr[j];
        }
    }
    

    for(i=0; i<a.size; i++){        
        for(j=0; j<a.size; j++){
            int temp=0;
            temp = a.size - j - 1;
            a.arr[i].arr[j] = b[temp][i];
        }
    }

    return a;
}