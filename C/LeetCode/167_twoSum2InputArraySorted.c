/*
Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.
The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.

Note:

Your returned answers (both index1 and index2) are not zero-based.
You may assume that each input would have exactly one solution and you may not use the same element twice.

Example 1:
Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.

Example 2:
Input: numbers = [2,3,4], target = 6
Output: [1,3]

Example 3:
Input: numbers = [-1,0], target = -1
Output: [1,2]

Constraints:

2 <= nums.length <= 3 * 104
-1000 <= nums[i] <= 1000
nums is sorted in increasing order.
-1000 <= target <= 1000

*/

#include "../standardHeaders.h"

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/

int* twoSumSolution1(int* numbers, int numbersSize, int target, int* returnSize){

    int * ret = (int *) malloc(2*sizeof(int));
    
    int i=0,j=numbersSize-1,sum=0;
    
    *returnSize = 2;
    
    while(i < j)
    {
        sum = numbers[i]+numbers[j];
        if(sum == target)
        {
            ret[0]=i+1;ret[1]=j+1;
            return ret;
        }
        else if(sum > target)
        {
            j--;
        }
        else
        {
            i++;
        }
    }
    
    ret[0]=0;ret[1]=0;
    return ret;
}

/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct hashNode{
    int key;
    int value;
    struct hashNode *next;
};

struct hashTable{
    int size;
    struct hashNode **list;
};

struct hashTable *createTable(int size){
    // Create hash table of given size
    struct hashTable *table = (struct hashTable*)malloc(sizeof(struct hashTable));
    table->size = size;
    
    // create entries equal to size of table, 1 entry per item
    table->list = (struct hashNode**)malloc(sizeof(struct hashNode*)*size);
    
    // iterate over table->list and mark all nodes as NULL
    for(int i=0; i<size; i++){
        table->list[i] = NULL;
    }
    return table;
}

int hashCode(struct hashTable *table, int key){
    // printf("Key: %d hash: %d\n",key, (key%(table->size)));
    if(key<0)
        return -(key%(table->size));
    return (key%(table->size));
}

void insert(int key, int value, struct hashTable *table){
    int position = hashCode(table, key);
    struct hashNode *list = table->list[position];
    struct hashNode *newNode = (struct hashNode*)malloc(sizeof(struct hashNode));
    struct hashNode *temp = list;
    while(temp){
        // check if key already exist in table, if it exists
        // update its value and return
        if(temp->key == key){
            // printf("updating key %d to val: %d", key, value);
            temp->value = value;
            return;
        }
        temp = temp->next;
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = list;
    table->list[position] = newNode;
    
}

void delete(struct hashTable *hashtable)
{
        struct hashNode *tmp;

        if (hashtable == NULL) {
                return;
        }

        for (int i = 0; i < hashtable->size; ++i) {
                if (hashtable->list[i] != NULL) {
                        /* Traverse the list and free the nodes. */
                        while(hashtable->list[i] != NULL) {
                          tmp = hashtable->list[i]->next;
                          free(hashtable->list[i]);
                          hashtable->list[i] = tmp;
                        }
                        free(hashtable->list[i]);
                }
        }
        free(hashtable->list);
        free(hashtable);
}

int lookup(struct hashTable *table,int key){
    int position = hashCode(table, key);
    struct hashNode *list = table->list[position];
    struct hashNode *temp = list;
    while(temp){
        if(temp->key==key){
            return temp->value;
        }
        temp = temp->next;
    }
    return -1;
}

int binSearch(int* nums, int numsSize, int skipLimit, int target){
    int mid, left, right;
    left = 0;
    right = numsSize - 1;
    
    if(numsSize == 1){
        if(target == nums[numsSize])    return numsSize;
        else    return -1;
    }
    
    while(left < right){
        mid = (left + right)/2;
        if(nums[mid] > target){
            right = mid - 1;
        }
        else if(nums[mid] < target){
            left = mid + 1;
        }
        if(nums[mid] == target){
            return mid;
        }
    }
    
    return -1;
}

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize){
    
    int *retNums;
    *returnSize = 2;
    retNums = calloc(2, sizeof(int));
    
    struct hashTable *table = createTable(numbersSize);

    for(int i=0; i<numbersSize; i++){
        insert(numbers[i],i+1,table);
    }
    
    // for(int i=0; i<numbersSize; i++){
    //     printf("Key: %d Val: %d\n", numbers[i], lookup(table, numbers[i]));
    // }

    for(int i=0; i<numbersSize; i++){
        int searchNum = target - numbers[i];
        // int foundIdx = binSearch(numbers, numbersSize, i, searchNum);
        int foundIdx = lookup(table, searchNum);
        // printf("Looking for %d\n", searchNum);
        if(foundIdx == -1){
            insert(numbers[i],i,table);
        }
        else if(foundIdx != i){
            // printf("foundIdx: %d\n", foundIdx);
            retNums[0] = i+1;
            retNums[1] = foundIdx;
            goto ret;
        }
    }
    
ret:    *returnSize = 2;
    delete(table);
    return retNums;

}
