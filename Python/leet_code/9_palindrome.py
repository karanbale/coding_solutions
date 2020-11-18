"""

Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Follow up: Could you solve it without converting the integer to a string?

Example 1:

Input: x = 121
Output: true
Example 2:

Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
Example 4:

Input: x = -101
Output: false

Constraints:

-231 <= x <= 231 - 1

"""

INT32_MAX = ((2**32))
INT32_MIN = -((2**32)-1)

class Solution(object):
    def isPalindrome(self, x):
        """
        :type x: int
        :rtype: bool
        """
        if(x > INT32_MAX) or (x < INT32_MIN) or (X < 0):
            return False;
        
        # for all single digit numbers
        if((x % 10) == 0) and (x != 0):
            return False
        
        retNum = 0
        inputNum = x
        while(inputNum > retNum):
            retNum = (retNum*10) + (x%10);
            if(retNum > INT32_MAX):
                return False
            x = x//10
            
        return True if (inputNum == retNum) else False

"""

Sample inputs to test:
121
-312
1534236469
-2147483648
2147483647
6767676
22222222
10

"""