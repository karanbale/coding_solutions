/*
The thief has found himself a new place for his thievery again. 
There is only one entrance to this area, called the "root." 
Besides the root, each house has one and only one parent house. 
After a tour, the smart thief realized that "all houses in this place forms a binary tree". 
It will automatically contact the police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:

Input: [3,2,3,null,3,null,1]

     3
    / \
   2   3
    \   \ 
     3   1

Output: 7 
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:

Input: [3,4,5,1,3,null,1]

     3
    / \
   4   5
  / \   \ 
 1   3   1

Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
*/

#include "../standardHeaders.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/
typedef struct {
    int robMoney;
    int notRobMoney;
} Money;

Money robMoney(struct TreeNode* root) {
    if (root == NULL) {
        Money money = {0};
        return money;
    }

    Money moneyFromLeft = robMoney(root->left);
    Money moneyFromRight = robMoney(root->right);
    Money money;
    money.robMoney = root->val + moneyFromLeft.notRobMoney + moneyFromRight.notRobMoney;
    money.notRobMoney = (moneyFromLeft.robMoney > moneyFromLeft.notRobMoney ?
    moneyFromLeft.robMoney : moneyFromLeft.notRobMoney)
    +
    (moneyFromRight.robMoney > moneyFromRight.notRobMoney ?
    moneyFromRight.robMoney : moneyFromRight.notRobMoney);
    
    return money;
}

int robSolution1(struct TreeNode* root) {
    Money money = robMoney(root);
    return money.robMoney > money.notRobMoney ? money.robMoney : money.notRobMoney;
}
/**********************************************************************************************/




/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/
int rob(struct TreeNode* root){
    
    if(!root){
        return 0;
    }
    
    if(root->left && !root->right){
        return fmax(root->val+rob(root->left->left)+rob(root->left->right), rob(root->left)+rob(root->right));
    }
    else if(!root->left && root->right){
        return fmax(root->val+rob(root->right->left)+rob(root->right->right), rob(root->left)+rob(root->right));
    }
    else if(!root->left && !root->right){
        return (root->val);
    }
    
    return fmax(root->val+rob(root->left->left)+rob(root->left->right)+
                rob(root->right->left)+rob(root->right->right),
                rob(root->left)+rob(root->right));

}
/**********************************************************************************************/
