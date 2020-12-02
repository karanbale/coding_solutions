"""
Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:

Input: [1,2,2]
Output:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]

Solution 1:
Recursively iterate over input list, if current item is duplicate of its previous, skip it.
Otherwise add current item to temp list and append this temp list to output. 
Then iterate over list that is AFTER current element.
e.g. if current item is at index i, then we iterate over list starting with index = i+1


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
    def subsetsWithDupMethod1(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        res = []
        self.genSubset(sorted(nums),res,[])
        return res
    
    def genSubset(self,nums,res,subArr):
        # append subArray to result as first step
        res.append(subArr)
        for i in range(len(nums)):
            # if i > 0 and if current element == previous element, skip current element
            if i > 0 and nums[i] == nums[i-1]:
                continue
            # drill down, lets iterate over remaining array
            # but before we do that, let's add current element to the list
            self.genSubset(nums[i+1:],res,subArr+[nums[i]])

    def subsetsWithDupMethod2(self, nums):
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
            tempOutput.sort()
            # Following is a simplified version of inner for loop above
            # output.append([nums[j] for j in range(n) if bitmask[j] == '1'])
            if tempOutput not in output:
                output.append(tempOutput)
        return output
        