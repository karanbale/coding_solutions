/*
Given a binary tree, return the level order traversal of its nodes' values.
(ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]

*/

#include "../standardHeaders.h"

#define SIZE 1200

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode_t;

typedef struct Node {
     int level;
     struct TreeNode *val;
}Node_t;

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    if(root==NULL){
        * returnSize=0;
        returnColumnSizes[0]=(int*)calloc(1,sizeof(int));
        returnColumnSizes[0][0]=0;
        return (int**)malloc(sizeof(int*));
    }
    Node_t **array=(Node_t **)malloc(SIZE*sizeof(Node_t*));
    array[0]=(Node_t *) malloc(sizeof(Node_t));
    array[0]->level=0;
    array[0]->val=root;
    int left=0;
    int right=1;
    int maxDepth=0;
    while(left!=right){
        if(array[left]->val->left){
            array[right]=(Node_t *)malloc(sizeof(Node_t));
            array[right]->val=array[left]->val->left;
            array[right]->level=array[left]->level+1;
            if(maxDepth<array[right]->level){
                maxDepth=array[right]->level;
            }
            right++;
        }
        if(array[left]->val->right){
            array[right]=(Node_t *)malloc(sizeof(Node_t));
            array[right]->val=array[left]->val->right;
            array[right]->level=array[left]->level+1;
            if(maxDepth<array[right]->level){
                maxDepth=array[right]->level;
            }
            right++;
        }
        left++;
    }
    int **ret_array=(int**)malloc((maxDepth+1)*sizeof(int*));
    *returnSize=0;
    for(int i=0;i<maxDepth+1;i++){
        ret_array[i]=(int*)malloc(right*sizeof(int));
    }
    returnColumnSizes[0]=(int*)calloc(SIZE,sizeof(int));
    for(int i=0;i<right;i++){
        ret_array[array[i]->level][returnColumnSizes[0][array[i]->level]]=array[i]->val->val;
        returnColumnSizes[0][array[i]->level]++;
        if(*returnSize<array[i]->level+1){
            *returnSize=array[i]->level+1;
        }
    }
    return ret_array;
}

/*
Sample input to test:

[42,10,11,60,65,50,98,66,84,35,97,-6,null,-1,73,2,61,8,20,11,21,13,50,88,89,20,59,65,66,null,81,-7,12,20,
-5,82,-8,96,44,58,91,31,65,29,3,93,74,null,null,10,-4,91,55,85,20,52,18,null,null,11,6,91,6,58,82,null,
null,21,null,84,null,7,31,null,-9,57,32,94,61,44,61,35,31,-7,54,15,75,21,-9,65,57,74,null,-2,89,24,6,95,
null,null,47,null,null,79,null,36,31,79,86,9,5,86,92,-4,83,76,3,24,10,1,10,72,95,43,0,null,38,41,40,-6,
10,93,62,94,82,4,-3,25,91,19,36,null,95,37,67,13,15,18,39,57,13,64,50,null,null,26,-3,-7,99,null,-9,77,
16,91,9,null,null,null,26,null,78,83,19,76,92,74,96,46,14,null,null,8,98,null,null,26,null,-7,64,39,91,
79,60,80,10,3,-2,29,85,53,70,50,24,null,56,null,null,33,null,-5,71,8,62,72,35,83,null,null,null,14,85,
-5,17,null,5,2,14,-8,3,73,49,null,89,null,84,null,85,-3,16,8,-9,null,null,91,18,76,null,5,58,58,4,null,
null,null,null,95,null,-3,82,99,6,null,null,49,58,-3,54,91,63,null,12,null,26,34,64,93,null,null,null,
null,25,-9,91,64,33,76,27,null,null,80,null,null,null,50,68,null,null,null,10,null,null,60,null,null,50,
8,null,30,35,36,5,17,22,61,38,40,null,12,98,68,65,60,48,null,20,44,20,59,78,10,91,81,8,3,27,61,null,69,
null,53,null,null,null,null,null,92,null,null,null,99,91,15,71,21,66,37,5,null,null,null,12,52,null,null,
7,69,28,null,null,68,13,94,76,null,null,null,82,-7,94,null,null,null,42,null,3,null,22,null,25,null,89,99,
null,74,60,93,25,75,56,null,14,null,1,24,6,null,null,null,null,-1,null,null,66,3,73,91,60,null,null,16,42,
17,81,14,96,33,null,55,null,null,-9,67,4,9,53,null,null,null,null,null,null,null,null,null,42,96,null,29,16,
59,null,-3,56,90,null,72,null,null,87,null,null,null,null,null,null,null,null,null,75,null,null,54,null,4,39,
-2,null,44,80,14,null,95,8,76,19,null,null,null,null,null,null,null,66,null,68,92,94,5,8,96,null,80,null,null,
null,40,52,30,-7,85,null,72,90,1,44,4,59,19,null,null,null,-9,-8,32,63,1,null,25,null,21,33,37,96,-1,43,null,
83,80,65,68,99,88,null,48,77,14,null,14,8,null,null,null,null,null,null,null,null,null,89,null,null,14,null,37,
null,null,null,null,null,null,null,20,null,null,null,61,20,null,null,null,34,50,53,null,null,51,null,98,25,42,
77,59,36,18,68,4,-5,36,71,null,37,78,null,null,null,null,null,null,null,null,null,null,44,74,92,null,null,3,21,
76,32,79,null,59,3,86,-9,81,-4,null,null,null,31,61,32,null,null,98,null,-8,5,64,null,43,32,null,78,null,36,null,
null,null,48,null,null,null,78,71,null,71,80,12,null,null,null,null,null,29,52,1,83,5,95,2,56,93,65,86,95,null,null,
null,null,58,7,null,20,-2,84,null,-9,13,null,null,33,null,58,null,null,0,38,null,null,-9,null,88,null,78,24,null,
14,null,null,9,75,53,-3,null,88,71,84,76,62,85,53,null,null,null,79,36,-5,null,91,57,17,null,null,null,null,36,12,
-7,51,63,-3,77,40,13,17,10,5,89,-4,72,27,53,null,83,65,null,null,null,null,null,33,null,96,null,null,85,60,9,38,23,
null,null,null,39,null,null,null,16,85,99,51,null,null,null,null,null,null,54,null,null,62,null,null,57,90,61,99,69,
2,23,71,35,null,-4,51,-1,null,30,3,null,null,17,42,null,null,77,95,39,85,null,-8,43,5,86,null,33,56,47,78,9,70,57,3,
29,71,null,null,null,null,null,null,null,null,47,92,85,38,-3,null,null,22,null,null,34,37,null,86,79,68,84,null,null,
null,null,null,null,null,78,58,null,null,49,null,null,11,null,null,null,null,null,null,null,88,65,null,50,null,52,null,
55,null,13,0,null,null,null,null,30,86,60,68,48,85,null,null,null,20,null,null,null,39,52,77,62,null,82,-6,null,null,
60,null,71,null,null,null,39,0,53,null,null,11,null,null,null,3,85,3,78,null,78,-1,30,72,null,null,null,null,35,29,40,
79,86,12,21,null,48,46,70,98,62,22,93,null,null,null,null,null,null,null,45,null,null,null,null,null,-6,null,null,null,
null,71,null,null,null,null,68,null,41,93,null,null,62,78,-7,14,null,19,16,91,null,null,null,null,null,20,90,51,42,null,
null,93,85,null,null,58,9,null,-3,27,86,42,null,null,null,null,null,17,null,null,null,null,22,-8,93,8,49,90,null,null,
63,19,39,null,null,null,17,4,54,8,-5,76,null,null,-9,-6,null,34,null,51,10,20,null,23,14,91,26,47,null,47,67,null,null,
26,null,null,null,null,null,null,null,null,34,null,15,0,85,13,3,88,86,null,80,39,33,null,52,null,null,39,null,-4,21,null,
null,null,2,89,null,null,-1,-6,null,17,-1,65,null,null,null,null,null,19,null,null,63,null,null,null,null,null,-1,68,null,
null,null,null,null,null,null,null,17,null,null,null,93,42,null,null,null,12,null,null,null,92,85,82,8,null,null,34,18,90,
50,null,99,89,null,19,null,null,78,null,74,-2,null,null,null,63,null,null,38,38,null,null,null,null,null,null,null,null,
null,null,74,null,8,null,null,null,49,null,null,null,21,0,null,2,60,15,36,83,59,54,null,-3,null,null,null,-8,null,5,49,32,
null,null,null,null,null,7,null,null,null,55,null,null,26,78,98,null,null,57,null,null,83,63,null,null,null,null,81,null,
null,33,null,null,null,null,null,null,16,14,null,null,-4,44,null,null,37,16,16,33,null,84,null,25,10,null,null,30,null,
null,null,null,null,null,65,null,null,null,93,null,null,null,44,57,12,52,-4,67,null,49,null,null,null,null,null,null,null,
64,17,null,null,null,83,4,61,75,null,null,null,null,null,null,24,null,78,-7,null,-5,null,null,30,79,null,44,94,55,14,59,null,
null,null,null,null,null,60,null,null,null,null,25,null,null,null,null,97,34,null,null,null,null,80,67,0,null,22,null,96,
null,null,null,null,null,null,null,null,47,null,null,null,null,89,null,null,null,null,43,64,null,null,9,null,null,96,37,79,
null,null,null,28,81,null,null,5,null,null,7,96,41,82,-6,20,null,null,null,8,null,null,null,null,null,null,null,null,null,82,
8,null,null,null,null,null,null,null,null,39,6,null,null,null,null,90,59,-8,null,null,null,null,null,23,null,null,null,15,89,
null,null,86,50,40,70,null,null,32,null,null,null,44,-2,null,38,39,null,null,null,null,null,null,null,null,null,2,null,null,
null,null,2,null,null,65,47,null,null,62,27,62,38,31,27,null,null,37,null,null,null,null,null,null,null,62,74,86,-7,null,23,
null,null,56,null,null,null,6,null,86,72,30,null,null,21,41,92,null,null,null,null,22,null,74,96,87,null,null,null,null,null,
-7,null,51,34,80,null,null,null,null,null,null,null,16,20,null,null,15,81,null,55,null,61,null,null,22,null,5,14,null,34,23,
null,30,null,6,64,2,65,null,54,null,null,14,null,0,null,null,null,26,null,null,78,null,49,null,null,13,null,null,null,43,null,
null,-1,41,33,null,5,78,null,null,null,null,null,null,null,null,null,null,75,null,null,null,null,null,null,63,70,null,null,
null,null,null,40,null,null,null,66,null,null,15,null,7,43,null,60,12,null,null,null,null,null,null,null,19,null,74,-5,55,
null,null,null,null,52,-4,-5,null,null,null,65,null,null,67,null,3,null,null,95,null,null,36,null,81,null,null,null,null,
null,88,74,null,67,null,null,null,null,68,null,null,null,null,52,null,null,82,90,75,25,null,23,null,68,6,11,null,59,null,
null,null,null,null,null,null,null,-2,null,null,null,61,null,null,null,32,80,null,null,null,51,6,null,91,null,null,37,null,
26,null,78,null,null,null,null,null,null,null,34,null,null,null,null,null,null,24,31,null,null,99,56,null,null,62,12,43,null,
null,null,null,null,null,33,null,68,null,null,null,null,53,4,65,4,null,86,null,46,-9,null,null,83,null,null,null,null,93,null,
null,78,null,63,null,null,null,null,null,67,null,null,null,null,72,93,25,null,null,27,null,null,92,44,null,null,null,null,2,9,
31,null,null,73,92,62,86,null,null,-6,null,null,null,null,58,null,null,null,null,null,null,null,null,54,null,null,null,null,null,
null,null,null,16,null,null,null,null,null,null,null,null,null,null,null,28,null,48,null,null,null,null,null,26,null,null,null,
null,null,null,37,66,null,null,92,null,null,null,null,86,89,null,null,null,null,null,null,5,85,null,null,75,null,35,null,null,
null,null,null,null,null,27,null,null,null,null,null,null,67,84,94,44,null,null,null,null,null,null,null,null,null,null,70,null,
null,49,null,null,16,null,null,null,null,null,null,null,87,null,-7,52,null,null,null,67,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,80,null,76,null,25,null,91,null,12,41,null,null,26,null,null,null,null,null,null,null,null,null,null,null,null,null,null,94]
*/