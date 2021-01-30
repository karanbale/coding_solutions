/*
Given a function  f(x, y) and a value z, return all positive integer pairs x and y where f(x,y) == z.

The function is constantly increasing, i.e.:

f(x, y) < f(x + 1, y)
f(x, y) < f(x, y + 1)
The function interface is defined like this: 

interface CustomFunction {
public:
  // Returns positive integer f(x, y) for any given positive integer x and y.
  int f(int x, int y);
};
For custom testing purposes you're given an integer function_id and a target z as input, where function_id represent one function from an secret internal list, on the examples you'll know only two functions from the list.  

You may return the solutions in any order.

 

Example 1:

Input: function_id = 1, z = 5
Output: [[1,4],[2,3],[3,2],[4,1]]
Explanation: function_id = 1 means that f(x, y) = x + y
Example 2:

Input: function_id = 2, z = 5
Output: [[1,5],[5,1]]
Explanation: function_id = 2 means that f(x, y) = x * y
 

Constraints:

1 <= function_id <= 9
1 <= z <= 100
It's guaranteed that the solutions of f(x, y) == z will be on the range 1 <= x, y <= 1000
It's also guaranteed that f(x, y) will fit in 32 bit signed integer if 1 <= x, y <= 1000

*/

#include "../standardHeaders.h"

/*
 * // This is the definition for customFunction API.
 * // You should not implement it, or speculate about its implementation
 *
 * // Returns f(x, y) for any given positive integers x and y.
 * // Note that f(x, y) is increasing with respect to both x and y.
 * // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
 */

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findSolutionSolution1(int (*customFunction)(int, int), int z, int* returnSize, int** returnColumnSizes) {
	int *c = *returnColumnSizes = (int *) malloc(sizeof(int*)*z);
    int retArrayRowIdx = 0;
    int **retArray = malloc(sizeof(int*)*z);
    for (int i = 1 ; i <= z ; i++){
        for (int j = z ; j >= 1 ; j--){
            if (customFunction(i, j) == z){
                *(c+retArrayRowIdx) = 2;
                retArray[retArrayRowIdx] = (int *) malloc(sizeof(int)*2);
                retArray[retArrayRowIdx][0] = i;
                retArray[retArrayRowIdx++][1] = j;
                
            }
        }
    }
    
    *returnSize = retArrayRowIdx;
    
    return retArray;
}

int** findSolutionSolution2(int (*customFunction)(int, int), int z, int* returnSize, int** returnColumnSizes) {
    if(customFunction == NULL){
        return NULL;
    }
    *returnSize = 0;
    
    *returnColumnSizes = (int *) malloc(sizeof(int));
    int **retArray = (int **) malloc(sizeof(int*));

    if(!retArray || !returnColumnSizes){
        return NULL;
    }
    
    int retArrayRowIdx = 0;
    
    for(int i=1; i<=z; i++){
         for (int j = z ; j >=1 ; j--){
            // printf("i = %d, j = %d, z = %d\n",i,j,customFunction(i, j));
            if(customFunction(i, j) == z){
                (*returnSize)++;
                retArray =  realloc(retArray, *returnSize * sizeof(int*));
                retArray[*returnSize -1] = (int *) malloc(2*sizeof(int));
                if(!retArray[*returnSize-1])   return NULL;
                else{
                    retArray[*returnSize - 1][0] = i;
                    retArray[*returnSize - 1][1] = j;
                }
            }
        }
    }
    
    *returnColumnSizes = (int *) malloc(*returnSize * sizeof(int));
    for(int i = 0; i < *returnSize; i++)
    {
        (*returnColumnSizes)[i] = 2;
    }
    
    return retArray;

}
