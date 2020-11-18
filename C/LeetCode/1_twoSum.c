/*

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

Example 1:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:
Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:
Input: nums = [3,3], target = 6
Output: [0,1]

*/

#include "../utils/hashMap.h"

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

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    
    int *retNums;
    *returnSize = 2;
    retNums = calloc(2, sizeof(int));
    
    struct hashTable *table = createTable(numsSize);

    for(int i=0; i<numsSize; i++){
        int searchNum = target - nums[i];
        int foundIdx = lookup(table, searchNum);
        if(foundIdx == -1){
            insert(nums[i],i,table);
        }
        else if(foundIdx != i){
            retNums[0] = i;
            retNums[1] = foundIdx;
            goto ret;
        }
    }
    
ret:    *returnSize = 2;
    return retNums;

}

