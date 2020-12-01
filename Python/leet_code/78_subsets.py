"""
Given an integer array nums, return all possible subsets (the power set).
The solution set must not contain duplicate subsets.

Example 1:
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:
Input: nums = [0]
Output: [[],[0]]

Constraints:

1 <= nums.length <= 10
-10 <= nums[i] <= 10

Solution 1:
We use list indexing.
Take output as: ret = [[]]
Now iterate over entire input list, and for each member of the input, iterate over output list (aka ret).
When you iterate over output list (aka ret), for each value in output list, add current number to the value.

Sample input: nums = [1,2,3]
Sample output with this algorithm:
ret:  [[]]
	current + [n]:  [1]
ret:  [[], [1]]
	current + [n]:  [2]
	current + [n]:  [1, 2]
ret:  [[], [1], [2], [1, 2]]
	current + [n]:  [3]
	current + [n]:  [1, 3]
	current + [n]:  [2, 3]
	current + [n]:  [1, 2, 3]


Solution 2:
We take bit-wise manipulation.
We have n numbers in the input list. 
We need output to be a combination of all the inputs.
e.g. for a input of size 3, output is 8 ==> input = n, output = 2**n

This indicates that we can simply create a bitmask of constant size n.
This bit-mask will go from 0 up to n.
NOTE: NUMBER OF BITS IN BITMASK MUST BE EQUAL TO N
i.e. 0->1->01->10->11 etc. are unacceptable for n=3
For n=3, acceptable bitmasks are:
000 -> 001 -> 010 -> 011 -> ..... -> 111

For any n, we can force bit-mask to be of size n using simple maths, where N=3:
bitmask = bin((1 << N) | number) [3:]

e.g. for N=3
output of (1 << N) = 8
output of ((1 << N) | number) = number + 8
output of bin((1 << N) | number) = '0b1xxx' where xxx is the number in binary
output of bin((1 << N) | number)[3:] = 'xxx' we ignore '0b1' from the string

Now that we have the bitmask, we just need to iterate over input list and add number to a list,
if bit-mask = '1'.
i.e. for each bit-mask, create a list of possible input number combinations, as long as bitmask is '1'


"""


class Solution(object):
    def subsets_solution_1(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        ret = [[]]
        for n in nums:
            l = len(ret)
            # print "ret: ", ret
            # print ret[:l]
            for current in ret[:l]:
                # print "\tcurrent + [n]: ", current+[n]
                ret.append(current + [n])
        return ret

    def subsets_solution_2(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        output = []
        n = len(nums)
        for i in range(2**n):
            # generate bitmask, from 0..00 to 1..11
            bitmask = bin(i | (1 << n))[3:]
            # print i, ":", bitmask
            tempOutput = []
            for j in range(n):
                if bitmask[j] == '1':
                    tempOutput.append(nums[j])
            # above for loop can be simplified as following commented line
            # output.append([nums[j] for j in range(n) if bitmask[j] == '1'])
            # print tempOutput
            output.append(tempOutput)
        return output
        