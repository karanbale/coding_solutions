/*
Given an integer array nums and an integer k, return true if nums has a continuous subarray of,
size at least two whose elements sum up to a multiple of k, or false otherwise.
An integer x is a multiple of k if there exists an integer n such that x = n * k. 0 is always a multiple of k.

Example 1:

Input: nums = [23,2,4,6,7], k = 6
Output: true
Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
Example 2:

Input: nums = [23,2,6,4,7], k = 6
Output: true
Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements sum up to 42.
42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.
Example 3:

Input: nums = [23,2,6,4,7], k = 13
Output: false
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109
0 <= sum(nums[i]) <= 231 - 1
1 <= k <= 231 - 1
*/

#include "../standardHeaders.h"

#define NODE_SIZE 100

typedef struct
{
    int key; // sum
    int val; // pos
    struct node* next;
} node;

int lookupPos(node** myNode, int sum)
{
    int pos = abs(sum)%NODE_SIZE;
    node *temp = myNode[pos];
    while(temp)
    {
        if(temp->key == sum)
            return temp->val;
        temp = temp->next;
    }
    
    return -2;
}

void addPos(node** myNode, int sum, int i)
{
    int pos = abs(sum)%NODE_SIZE;
    node* temp = NULL;
    node* newNode = (node*)malloc(sizeof(node));
    
    newNode->key = sum;
    newNode->val = i;
    newNode->next = NULL;
    
    if(myNode[pos] == NULL)
        myNode[pos] = newNode;
    else
    {
        temp = myNode[pos];
        while(temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

bool checkSubarraySum(int* nums, int numsSize, int k){
    int sum = 0, i, pos, key;
    node** myNode = (node**)calloc(NODE_SIZE,sizeof(node*));
    bool result = false;
    node* temp = NULL, *prev = NULL;
    
    k = abs(k);
    // add 0 to -1 position
    addPos(myNode,0,-1);
    for(i=0;i<numsSize;i++)
    {
        sum += nums[i];
        if(k)
            sum = sum%k;
        pos = lookupPos(myNode,sum);
        // position has to be bigger than -2
        if((pos>-2) && ((i-pos)>1))
        {
            result = true;
            break;
        }
        else
        {
            addPos(myNode,sum,i);
        }
    }
    
    for(i=0;i<NODE_SIZE;i++)
    {
        temp = myNode[i];
        while(temp)
        {
            prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    return result;
}

/*
Sample test cases:
[0]
1
[1,0]
2
[0,0]
1
[23,2,4,6,6]
7
[23,2,4,6,7]
14
[23,2,4,6,7]
6
[23,2,6,4,7]
13
*/
