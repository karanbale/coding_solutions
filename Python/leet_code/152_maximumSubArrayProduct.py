"""
Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.

Example 1:
Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:
Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
"""

class Solution(object):
    def maxProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        
        if len(nums) == 0:
            return 0
        
        """
        Explanation:
            Things to consider:
            If we encounter 0 anywhere along the array, we need to start over and calculate product again.
            Store current max until just before we encountered 0 and start new product.

            Zeros will reset your combo chain. A high score which you have achieved will be recorded in placeholder result. 
            You will have to restart your combo chain after zero. 
            If you encounter another combo chain which is higher than the recorded high score in result, you just need to update the result.

            Negative numbers are a little bit tricky. A single negative number can flip the largest combo chain to a very small number. 
            This may sound like your combo chain has been completely disrupted but if you encounter another negative number, your combo chain can be saved. 
            Unlike zero, you still have a hope of saving your combo chain as long as you have another negative number in nums 
            (Think of this second negative number as an antidote for the poison that you just consumed). 
            However, if you encounter a zero while you are looking your another negative number to save your combo chain, 
            you lose the hope of saving that combo chain.

            max_so_far is updated by taking the maximum value among:

            Current number.
                This value will be picked if the accumulated product has been really bad (even compared to the current number). 
                This can happen when the current number has a preceding zero (e.g. [0,4]) or is preceded by a single negative number (e.g. [-3,5]).
            Product of last max_so_far and current number.
                This value will be picked if the accumulated product has been steadily increasing (all positive numbers).
            Product of last min_so_far and current number.
                This value will be picked if the current number is a negative number and the combo chain has been disrupted by a single 
                negative number before (In a sense, this value is like an antidote to an already poisoned combo chain).
            
            min_so_far is updated in using the same three numbers except that we are taking minimum among the above three numbers.

            Complexity Analysis

            Time complexity : 
                O(N)O(N) where NN is the size of nums. The algorithm achieves linear runtime since we are going through nums only once.

            Space complexity : 
                O(1)O(1) since no additional space is consumed rather than variables which keep track of the maximum product so far, 
                the minimum product so far, current variable, temp variable, and placeholder variable for the result.

        """
        max_so_far = nums[0]
        min_so_far = nums[0]
        result = max_so_far

        for i in range(1, len(nums)):
            curr = nums[i]
            temp_max = max(curr, max_so_far * curr, min_so_far * curr)
            min_so_far = min(curr, max_so_far * curr, min_so_far * curr)

            max_so_far = temp_max
            result = max(max_so_far, result)

        return result
