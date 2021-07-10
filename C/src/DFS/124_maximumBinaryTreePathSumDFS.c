/*
Given the root of a binary tree, return the maximum path sum.
For this problem, a path is defined as any node sequence from some starting node,
to any node in the tree along the parent-child connections.
The path must contain at least one node and does not need to go through the root.

Example 1:
Input: root = [1,2,3]
Output: 6

Example 2:
Input: root = [-10,9,20,null,null,15,7]
Output: 42

Constraints:

The number of nodes in the tree is in the range [1, 3 * 104].
-1000 <= Node.val <= 1000
*/

#include "DFS_Header.h"
#include "common.h"

int calcMaxPathSum(struct TreeNode* root, int* maxSum) {
    if (root == NULL) {
        return 0;
    }
    
    int leftMax = calcMaxPathSum(root->left, maxSum);
    int rightMax = calcMaxPathSum(root->right, maxSum);
    
    // assume current roots value is maximum since, its children may be negative
    // thus, for negative values, we ignore roots children and just take root value
    int max = root->val;
    
    // check if total sum of current root and its left sub-tree is greater than root itself
    if (leftMax + root->val > max) {
        max = leftMax + root->val;
    }
    
    // check if total sum of current root and its right sub-tree is greater than previous maximum between root's value and sum of root's value and its left subtree
    if (rightMax + root->val > max) {
        max = rightMax + root->val;
    }
    
    // take total sum of current sub-tree
    int sum = leftMax + rightMax + root->val;
    
    // if current sub-tree's sum is less than current roots value, 
    // let's jus take current 
    sum = MAX(max, sum);
    
    // if total sum between EITHER side of subtree+root->val and sum of ALL subtrees+root->val is greater than what we've calculated so far, lets just update the max sum so far to this new value
    *maxSum = MAX(*maxSum, sum);

    return max;
}

int maxPathSum(struct TreeNode* root) {
    // cant initialize this value to 0 because
    // assume your tree has all negative values, for such tree, answer is going to be largest negative value of the tree
    // but if we initialize maxSum to 0, this negative value will be always less than 0 and we will always return 0 as max sum, unless we add special check for maxSum = 0, its just easy to instead initalize maxSum to smallest possible 32 bit int value
    int maxSum = INT32_MIN;
    
    calcMaxPathSum(root, &maxSum);
    
    return maxSum;
}
