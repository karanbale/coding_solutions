"""
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:
Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.

Example 1:
Input: s = "()"
Output: true

Example 2:
Input: s = "()[]{}"
Output: true

Example 3:
Input: s = "(]"
Output: false

Example 4:
Input: s = "([)]"
Output: false

Example 5:
Input: s = "{[]}"
Output: true

Constraints:
1 <= s.length <= 104
s consists of parentheses only '()[]{}'.
"""


class Solution(object):
    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        if not ((len(s) % 2) == 0):
            return False
        
        refDict = {
                    '{':'}',
                    '[':']',
                    '(':')'
        }
        
        stack = []
        stackPtr = 0
        
        for index in range(len(s)):
            # print s[index], index
            if(s[index] in refDict.keys()):
                stack.insert(stackPtr, refDict[s[index]])
                stackPtr = stackPtr+1
            else:
                # print s[index], index
                stackPtr = stackPtr-1
                if(stackPtr < 0):
                    return False
                if(s[index] != stack[stackPtr]):
                    return False
        
        return stackPtr == 0

