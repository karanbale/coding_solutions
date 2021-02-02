/*
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
*/

#include "../standardHeaders.h"

struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int search(int *in, int startIdx, int endIdx, int data){
    for(int i=startIdx; i<=endIdx; i++){
        if(in[i] == data)   return i;
    }
    return -1;
}

struct TreeNode *recurBuildTree(int* postorder, int* inorder, int left, int right, int* idx, struct TreeNode* pool, int* poolIdx)
{
    if (left >= right)
        return NULL;
    
    struct TreeNode* root = &pool[(*poolIdx)++];
    // post order always has root at its end
    root->val = postorder[(*idx)--];

    // look for the index of root in inorder list 
    // this index helps us point if the subtree is to the left or right
    int div = search(inorder, left, right, root->val);
    
    // right subtree is from index that we found to right
    root->right = recurBuildTree(postorder, inorder, div+1, right, idx, pool, poolIdx);

    // left subtree is from left to index that we found
    root->left = recurBuildTree(postorder, inorder, left, div, idx, pool, poolIdx);
    
    return root;
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize){

    int idx = postorderSize - 1;
    int poolIdx = 0;
    // create all nodes in one go
    struct TreeNode* pool = malloc(sizeof(struct TreeNode)*inorderSize);
    
    return recurBuildTree(postorder, inorder, 0, postorderSize, &idx, pool, &poolIdx);
}

/*
Inputs to test:
[1,2]
[2,1]

[3,9,20,15,7]
[9,3,15,20,7]

[-1]
[-1]
*/