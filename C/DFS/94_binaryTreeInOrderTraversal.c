/*
Given the root of a binary tree, return the inorder traversal of its nodes' values.

Example 1:
Input: root = [1,null,2,3]
Output: [1,3,2]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]

Example 4:
Input: root = [1,2]
Output: [2,1]

Example 5:
Input: root = [1,null,2]
Output: [1,2]

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100

Follow up:

Recursive solution is trivial, could you do it iteratively?
*/

#include "../standardHeaders.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int *inorderTraversalHelper(struct TreeNode *root, int *returnSize, int *retArr){
    if(!root)   return NULL;
    
    if(root->left){
        inorderTraversalHelper(root->left, returnSize, retArr);
    }
    retArr[(*returnSize)++] = root->val;
    if(root->right){
        inorderTraversalHelper(root->right, returnSize, retArr);
    }
    return NULL;
}

int* inorderTraversal(struct TreeNode* root, int* returnSize){
    
    *returnSize = 0;
    if(!root)   return 0;
    int *retArr = (int *) malloc(sizeof(int)*100);
    inorderTraversalHelper(root, returnSize, retArr);
    return retArr;
    
}


/*
Sample inputs to test:

[1,null,2,3]
output:
[1,3,2]

[]
output:
[]

[1]
output:
[1]
*/