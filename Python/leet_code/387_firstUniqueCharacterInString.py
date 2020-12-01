"""
Given a string, find the first non-repeating character in it and return its index. If it doesn't exist, return -1.

Examples:
s = "leetcode"
return 0.

s = "loveleetcode"
return 2.

Note: You may assume the string contains only lowercase English letters.

"""
class Solution(object):
    def firstUniqChar(self, s):
        """
        :type s: str
        :rtype: int
        """
        unique_character = {}
        
        if len(s) == 0:
            return -1
        
        # since all characters are going to be lowercase, our dict will be O(26) ~ O(1)
        # thus space complexity is O(1)
        # since we're iterating over all of the string length just twice, time complexity is O(n) as well.
        
        # store all characters in hash table, increment its count, if its already there
        # if its not there, assign a value of 0 (default) and add 1, since we've seen it once.
        for character in s:
            unique_character[character] = unique_character.get(character, 0) + 1
        
        print unique_character
        
        # iterate over input string in orderly fashion and see which character's value in hash table
        # is 1, and return it.
        # we iterate over input string, since we wish to return first unique character
        for index, val in enumerate(s):
            if unique_character[val] == 1:
                return index
        
        return -1
