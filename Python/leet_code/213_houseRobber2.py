"""
You are a professional robber planning to rob houses along a street. 
Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. 
That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, 
and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers nums representing the amount of money of each house, 
return the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.
Example 2:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.
Example 3:

Input: nums = [0]
Output: 0
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 1000
"""

class Solution(object):
    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def house_robber(nums):
            dp = [0] * len(nums)
            # when we begin, we only have two choices, between first and second house
            # we can either start by robbing first house
            dp[0] = nums[0]
            # or we can start by robbing the house with max money between first two houses
            dp[1] = max(nums[0], nums[1])

            # now let's iterate over rest of the houses
            for i in range(2,len(nums)):
                # take max between (current house + current-2) OR (current-1)
                # we can only rob one of : (current-1) OR (current-2+current) due to police alert
                dp[i] = max(dp[i-1], nums[i]+dp[i-2])
            # at the end we will have two possible maximum profit values, in last two locations
            # take max of the two
            return max(dp[-1], dp[-2])

        if len(nums) <=2 : return max([0] + nums)
        
        # iterate over list from:
        # 0 to n-2 (nums[:-1]) or 
        # 1 to n-1 (nums[1:])
        return max(house_robber(nums[1:]), house_robber(nums[:-1]))

