/*
Given a binary tree, find its minimum depth.
The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: 2

Example 2:
Input: root = [2,null,3,null,4,null,5,null,6]
Output: 5

Constraints:

The number of nodes in the tree is in the range [0, 105].
-1000 <= Node.val <= 1000
*/

#include "../standardHeaders.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define MIN(x,y) ((x) < (y) ? (x) : (y))

int minDepth(struct TreeNode* root){
    if(root == NULL) {
        return 0;
    }
    else {
        if (root->left == NULL) {
            return minDepth(root->right) + 1;
        }
        if (root->right == NULL) {
            return minDepth(root->left) + 1;
        }
        else {
            int left = minDepth(root->left) + 1;
            int right = minDepth(root->right) + 1;
            if(left < right) {
                return left;   
            }
            else {
                return right;
            }
        }
    }
}
