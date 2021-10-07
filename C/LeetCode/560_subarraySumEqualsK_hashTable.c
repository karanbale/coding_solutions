/*
Given an array of integers nums and an integer k, return the total number of continuous subarrays whose sum equals to k.

Example 1:
Input: nums = [1,1,1], k = 2
Output: 2

Example 2:
Input: nums = [1,2,3], k = 3
Output: 2 

Constraints:

1 <= nums.length <= 2 * 104
-1000 <= nums[i] <= 1000
-107 <= k <= 107
*/

#include "../standardHeaders.h"

typedef struct node{
    int key;
    int val;
    struct node *next;
} nodeT;

typedef struct {
    nodeT **arr;
    int sizeOfArr;
} hashT;

int hashKey(hashT *h, int key) {
    if(key < 0) return -(key%(h->sizeOfArr));
    return (key%(h->sizeOfArr));
}

hashT *createHashTable(int sizeOfArr) {
    hashT *hashTable = (hashT *) malloc(sizeof(hashT));
    if(!hashTable)  return NULL;
    hashTable->sizeOfArr = sizeOfArr;
    hashTable->arr = (nodeT **)malloc(sizeof(nodeT *)*sizeOfArr);
    if(!hashTable->arr) return NULL;
    for(int i=0; i<sizeOfArr; i++) {
        hashTable->arr[i] = NULL;
    }
    return hashTable;
}

void insertHashTable(hashT *h, int key) {
    int pos = hashKey(h, key);
    nodeT *list = h->arr[pos];
    nodeT *temp = list;
    while(temp) {
        if(temp->key == key) {
            temp->val++;
            return;
        }
        temp = temp->next;
    }
    nodeT *newNode = (nodeT *)malloc(sizeof(nodeT));
    newNode->key = key;
    newNode->val = 1;
    newNode->next = list;
    h->arr[pos] = newNode;
}

int lookup(hashT *h, int key) {
    int pos = hashKey(h, key);
    nodeT *list = h->arr[pos];
    nodeT *temp = list;
    while(temp) {
        if(temp->key == key) {
            return temp->val;
        }
        temp = temp->next;
    }
    return -1;
}

int subarraySum(int* nums, int numsSize, int k){
    int sum = 0, count = 0, n;
    hashT *h = createHashTable(1000);
    if(h == NULL)   return 0;
    insertHashTable(h, 0);
    for(int i=0; i<numsSize; i++) {
        sum+= nums[i];
        if((n = lookup(h, sum-k)) != -1) {
            count += n;
        }
        insertHashTable(h, sum);
    }
    return count;
}

