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

        for i in range(5):
            if "a" in S.lower():
                S = S.replace("a","")
            elif "e" in S.lower():
                S = S.replace("e","")
            elif "i" in S.lower():
                S = S.replace("i","")
            elif "o" in S.lower():
                S = S.replace("o","")
            elif "u" in S.lower():
                S = S.replace("u","")
        
        return S
