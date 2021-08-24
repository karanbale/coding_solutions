/*
Given an array a that contains only numbers in the range from 1 to a.length, find the first duplicate number for which the second occurrence has the minimal index. In other words, if there are more than 1 duplicated numbers, return the number for which the second occurrence has a smaller index than the second occurrence of the other number does. If there are no such elements, return -1.

Example

For a = [2, 1, 3, 5, 3, 2], the output should be firstDuplicate(a) = 3.

There are 2 duplicates: numbers 2 and 3. The second occurrence of 3 has a smaller index than the second occurrence of 2 does, so the answer is 3.

For a = [2, 2], the output should be firstDuplicate(a) = 2;

For a = [2, 4, 3, 5, 1], the output should be firstDuplicate(a) = -1.

Input/Output

[execution time limit] 0.5 seconds (c)

[input] array.integer a

Guaranteed constraints:
1 ≤ a.length ≤ 105,
1 ≤ a[i] ≤ a.length.

[output] integer

The element in a that occurs in the array more than once and has the minimal index for its second occurrence. If there are no such elements, return -1.
*/

// Arrays are already defined with this interface:
// typedef struct arr_##name {
//   int size;
//   type *arr;
// } arr_##name;
//
// arr_##name alloc_arr_##name(int len) {
//   arr_##name a = {len, len > 0 ? malloc(sizeof(type) * len) : NULL};
//   return a;
// }
//
//

#include "../C/standardHeaders.h"

typedef struct {
int size;
int arr[];
} arr_integer;

int ret_length(int b[], int size){
    unsigned int i;
    unsigned int len = size;
    printf("Length of b: %d\n", len);
    unsigned int minimum_1 = len;
    
    for(i=0; i<len; i++){
        printf("b[%d]=%d\n",i,b[i]);
    }
    
    for(i=0;i<len;i++){
        if(minimum_1 > b[i] && b[i] != 0){
            minimum_1=b[i];
        }
        printf("\nMinimum:%d\n",minimum_1);
    }
    
    return ((minimum_1 == len) ? -1 : minimum_1);
}


int firstDuplicate(arr_integer a) {
    
    unsigned int ret = -1;
    int i = 0, j = 0;
    
    //unsigned int len = sizeof(a)/sizeof(a[0]);
    unsigned int len = a.size;
    printf("Length of a: %d\n", len);
    int b[len];
    unsigned int minimum;
    
    for(i=0; i<len; i++){
        printf("Re-entering...\n");
        for(j=i+1; j<len; j++){
            printf("a[%d]=%d\n",i, a.arr[i]);
            if(a.arr[i] == a.arr[j]){
                b[i] = j;
                printf("b[%d]=%d\n",i, b[i]);
                printf("a[%d]          = %d\n",i,a.arr[i]);
                printf("Matching Index = %d\n",b[i]);
                printf("breaking up !\n");
                break;
            }
            b[i] = 0;
            printf("b[%d]=%d\n",i, b[i]);
        }
    }
    
    unsigned int len_1 = sizeof(b)/sizeof(b[0]);
    printf("Length of b: %d\n", len_1);
    minimum = ret_length(b, len);
        
    if(minimum == -1){
        printf("Duplicate index NOT found !");
    }
    else{
        printf("Duplicate index is: %d", a.arr[minimum]);
    }
        
    return ((minimum == -1) ? -1 : a.arr[minimum]);

}

