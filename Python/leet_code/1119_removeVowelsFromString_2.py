"""
Given a string S, remove the vowels 'a', 'e', 'i', 'o', and 'u' from it, and return the new string.

Example 1:
Input: "leetcodeisacommunityforcoders"
Output: "ltcdscmmntyfrcdrs"

Example 2:
Input: "aeiou"
Output: ""
 

Note:
S consists of lowercase English letters only.
1 <= S.length <= 1000

"""

class Solution(object):
    def removeVowels(self, S):
        """
        :type S: str
        :rtype: str
        """

        if(len(S) > 1000):
            return ""
        vowels = ['a', 'e', 'i', 'o', 'u']
        retString = ""
        retStringIdx = 0
        for index in range(len(S)):
            if S[index] not in vowels:
                retString = retString[:retStringIdx] + S[index]
                retStringIdx += 1
                
        return retString
