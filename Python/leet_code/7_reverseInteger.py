"""
Given a 32-bit signed integer, reverse digits of an integer.

    Example 1:
    Input: 123
    Output: 321

    Example 2:
    Input: -123
    Output: -321

    Example 3:
    Input: 120
    Output: 21

Note:
    Assume we are dealing with an environment which could only store integers, 
    within the 32-bit signed integer range: [−231,  231 − 1]. 
    For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.

"""


max_num = ((2 ** 31) -1)
min_num = -(2 ** 31)

class Solution:
    def reverse(self, x: int) -> int:
        sign = ""
        if((int(x) > max_num) or (int(x) < min_num)):
            return 0
        if(int(x) < 0):
            sign = "-"
            x = x*(-1)
        retNum = int(sign+str(x)[::-1])
        
        if(retNum > max_num) or (retNum < min_num):
            return 0
        else:
            return retNum

"""
Sample inputs to test:
-312
1534236469
-2147483648
2147483647
"""