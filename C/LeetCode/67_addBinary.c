/*
Given two binary strings a and b, return their sum as a binary string.

Example 1:
Input: a = "11", b = "1"
Output: "100"

Example 2:
Input: a = "1010", b = "1011"
Output: "10101"

Constraints:

1 <= a.length, b.length <= 104
a and b consist only of '0' or '1' characters.
Each string does not contain leading zeros except for the zero itself.
*/

#include "../standardHeaders.h"

char* addBinary(char* a, char* b)
{
    int i, j, k, c = 0;
    char *res;
    
    i = strlen(a);
    j = strlen(b);
    k = i > j ? i : j;
    k += 2;

    res = malloc(k * sizeof(char));
    
    i--;
    j--;
    res[--k] = '\0';
    
    while (--k >= 0) {
        c += i >= 0 ? a[i--] - '0': 0;
        c += j >= 0 ? b[j--] - '0': 0;
        
        res[k] = c % 2 + '0';
        c /= 2;
    }
    
    if (res[0] == '0')
       memmove(res, res + 1, strlen(res) * sizeof(char));
    
    return res;
}


