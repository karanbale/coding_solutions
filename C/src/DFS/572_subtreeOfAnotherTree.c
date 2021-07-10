/*
*/

#include "DFS_Header.h"
#include "common.h"

bool isIdentical(struct TreeNode *s, struct TreeNode *t) {
    // stop if any node is empty
    if(!s && !t)    return true;
    if(!s || !t)    return false;
    return ((s->val == t->val) && (isIdentical(s->left, t->left)) && (isIdentical(s->right, t->right)));
}

bool isSubtree(struct TreeNode* s, struct TreeNode* t) {
    if(!s)  return NULL;
    return (isIdentical(s,t) || isSubtree(s->left, t) || isSubtree(s->right, t));
}
