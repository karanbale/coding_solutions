/*
Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.
If possible, output any possible result.  If not possible, return the empty string.

Example 1:
Input: S = "aab"
Output: "aba"

Example 2:
Input: S = "aaab"
Output: ""

Note:
S will consist of lowercase letters and have length in range [1, 500].
 
*/

#include "MaxHeap_Header.h"
#include "common.h"
#include "heap.h"

char* reorganizeString(char* S) {
    int l = strlen(S);
    int s[26];
    memset(s, 0, sizeof(int) * 26);

    heap_t *h = createHeap(100, true);

    for (int n = 0; n < l; n++) s[S[n]-97] += 100;   
    for (int i = 0; i < 26; ++i) s[i] += i;

    for (int i = 0; i < 26; ++i) {
        if (s[i] >= 100) insertHeap(h, s[i]);
    }

    int p = 0; 

    int *pq = h->heapArr;

    for (int n = 0; p < l; n++) {
        int letter = removeHeap(h);
        int ct = letter / 100;
        int chr = 'a' + (letter % 100);

        int letter2 = removeHeap(h);
        int ct2 = letter2 / 100;
        int chr2 = 'a' + (letter2 % 100);

        if (ct > (l+1)/2) return "";
        if (ct2 > (l+1)/2) return "";

        if (p==0 || chr != S[p-1]) {
            S[p] = chr;
            letter -= 100;
            p++;

            if (p >= l) break;  

            S[p] = chr2;
            letter2 -= 100;
            p++;
        }
        else {
            S[p] = chr2;
            letter2 -= 100;
            p++;

            if (p >= l) break;  

            S[p] = chr;
            letter -= 100;
            p++;
        }

        if (letter >= 100) insertHeap(h, letter); 
        if (letter2 >= 100) insertHeap(h, letter2); 
    }

    return S;
}
