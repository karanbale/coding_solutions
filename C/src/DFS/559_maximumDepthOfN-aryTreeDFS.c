/*
Given a n-ary tree, find its maximum depth.
The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).

Example 1:
Input: root = [1,null,3,2,4,null,5,6]
Output: 3

Example 2:
Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: 5

Constraints:

The depth of the n-ary tree is less than or equal to 1000.
The total number of nodes is between [0, 104].
*/

#include "DFS_Header.h"
#include "common.h"

/**
 * Definition for a Node.
 */

void maxDepth_recursive(struct Node* root, int height, int *max) {
   if(root == NULL)
      return;
   if(root->numChildren == 0) {
      *max = MAX(height, *max);
      return;
   }
   for(int i = 0; i < root->numChildren; i++)
      maxDepth_recursive(root->children[i], height + 1, max);
   
   return;
}

int maxDepthDFS(struct Node* root) {
   int max = 0;
   if(root == NULL)
      return max;
   maxDepth_recursive(root, 1, &max);
   return max;
}
