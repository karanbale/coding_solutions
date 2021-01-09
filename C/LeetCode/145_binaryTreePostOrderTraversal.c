/*
Given the root of a binary tree, return the postorder traversal of its nodes' values.

Example 1:
Input: root = [1,null,2,3]
Output: [3,2,1]

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
Output: [2,1]
 
Constraints:

The number of the nodes in the tree is in the range [0, 100].
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

int *postorderTraversalHelper(struct TreeNode *root, int *returnSize, int *retArr){
    if(!root)   return NULL;
    
    if(root->left){
        postorderTraversalHelper(root->left, returnSize, retArr);
    }
    if(root->right){
        postorderTraversalHelper(root->right, returnSize, retArr);
    }
    retArr[(*returnSize)++] = root->val;
    
    return NULL;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* postorderTraversal(struct TreeNode* root, int* returnSize){
    *returnSize = 0;
    if(!root)   return 0;
    int *retArr = malloc(sizeof(int)*100);
    postorderTraversalHelper(root, returnSize, retArr);
    return retArr;

}

