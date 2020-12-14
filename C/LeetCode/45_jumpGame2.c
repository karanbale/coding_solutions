/**
 * Given an array of non-negative integers nums, you are initially positioned at the first index of the array.
 * Each element in the array represents your maximum jump length at that position.
 * Your goal is to reach the last index in the minimum number of jumps.
 * You can assume that you can always reach the last index.
 * Example 1:
 *      Input: nums = [2,3,1,1,4]
 *      Output: 2
 *      Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
 * Example 2:
 *      Input: nums = [2,3,0,1,4]
 *      Output: 2
 * 
 * Constraints:
 * 1 <= nums.length <= 3 * 104
 * 0 <= nums[i] <= 10
 * 
*/

#define max(a, b)   (((a) > (b)) ? (a) : (b))

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/

int jumpFunction1(int* nums, int numsSize){
    int n = numsSize, start = 0, end = 0, count = 0, maxLen = 0;
    // travel till the end, skip last element, since we need to find if we can reach it
    while (end < n - 1) {
        // you're going to next level
        count++;
        // for current level, check if current level's max node is > last index, if yes, we can exit
        // if not, we need to go to this node with max index to explore
        for (int i = start; i <= end; i++) {
            // current jump will get us at or beyond last index
            if (i + nums[i] >= n - 1)
                return count;
            // current jump is not enough, so lets go to next jump at current level and see if has a max index 
            // that can take us to the last index or beyond
            if (i + nums[i] >= maxLen) {
                maxLen = i + nums[i];
                start = i;
            }
        }
        // don't stop until you've iterated over all the nodes in current level
        end = maxLen;
    }
    return count;

}

/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

int jumpFunction2(int* nums, int numsSize){
    if(numsSize <= 1){
        return 0;
    }
    
    // find max nodes at current level, and then go to next level
    // when we're at next level, find all ndoes at this level
    int maxNodes = 0;
    int currMaxNode = 0;
    int levels = 0;
    int i=0;
    while(i <= currMaxNode){                    // keep running until all nodes are visited
        levels++;                               // increment level, since we're at that level
        for(;i<=currMaxNode;i++){               // find the maximum node at current level 
                                                // ensure the maximum at current level is not exceeding last index
            maxNodes = max(maxNodes, i+nums[i]);
            if(maxNodes >= numsSize-1)  return levels;
        }
        currMaxNode = maxNodes;
    }
    return 0;
    
}