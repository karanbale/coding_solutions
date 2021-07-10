#include "../../standardHeaders.h"
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode_t;

struct Node {
     int val;
     int numChildren;
     struct Node** children;
 };

int climbStairsFibonnaci(int n);
int climbStairsBruteForce(int n);
int climbStairsBruteForceMemory(int n);

int* inorderTraversal(struct TreeNode* root, int* returnSize);

bool hasPathSum(struct TreeNode* root, int sum);

int maxPathSum(struct TreeNode* root);

void surroundingRegions(char** board, int boardSize, int* boardColSize);

int* postorderTraversal(struct TreeNode* root, int* returnSize);

int* postrderTraversalStack(struct TreeNode* root, int* returnSize);

int numIslands(char** grid, int gridSize, int* gridColSize);

int kthSmallest(struct TreeNode* root, int k);

void wallsAndGates(int** rooms, int roomsSize, int* roomsColSize);

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize);

int maxDepthDFS(struct Node* root);

int count(int *nums, int startIdx, int endIdx, int turn, int len);

bool isSubtree(struct TreeNode* s, struct TreeNode* t);

int findSecondMinimumValue(struct TreeNode* root);

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize);

int uniquePathsIII(int** grid, int gridSize, int* gridColSize);

bool canReach(int* arr, int arrSize, int start);
