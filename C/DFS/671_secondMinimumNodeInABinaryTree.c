/*
*/

#include "../standardHeaders.h"

struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void helper(struct TreeNode* root, int *saver) {
	if (root == NULL) return;
    // if first minimum is not updated, let's update it
	if(saver[0]==-1) saver[0]=root->val;
    // if second minimum is not updated, let's update it
    // but let's only update it if first minimum is not equal to current root's value
	else if(saver[1]==-1 && root->val!=saver[0]) saver[1]=root->val;
    // if first minimum > current root's value i.e. current root's value is smaller than first min
    // let's update first min and second min
	else if (root->val < saver[0]) {
		saver[1] = saver[0];
		saver[0] = root->val;
	}
    // if current root's value is second smallest value, lets just update second smallest value
	else if (root->val > saver[0] && root->val < saver[1]) {
		saver[1] = root->val;
	}
    // keep traversing the tree
	helper(root->left, saver);
	helper(root->right, saver);
}
int findSecondMinimumValue(struct TreeNode* root) {
	// saver[0] is the smallest value in the binary tree
    // saver[1] is the second smallest value in the binary tree
    int saver[2] = {-1,-1};
	helper(root, saver);
	return saver[1];
}
