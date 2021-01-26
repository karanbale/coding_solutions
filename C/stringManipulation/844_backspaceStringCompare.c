/*
Given two strings S and T, return if they are equal when both are typed into empty text editors.
# means a backspace character.

Note that after backspacing an empty text, the text will continue empty.

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.
Follow up:

Can you solve it in O(N) time and O(1) space?
*/

#include "../standardHeaders.h"

bool backspaceCompare(char * S, char * T){

    char sPtr = *S;
    char tPtr = *T;
    
    char s[strlen(S)+1];
    char t[strlen(T)+1];
    int sIdx = 0, tIdx = 0;
    for(int i=0; i<strlen(S); i++){
        if(S[i] != '#'){
            s[sIdx++] = S[i];
        }
        else{
            if(sIdx > 0) sIdx--;
        }
    }
    s[sIdx++] = '\0';
    
    for(int i=0; i<strlen(T); i++){
        if(T[i] != '#'){
            t[tIdx++] = T[i];
        }
        else{
            if(tIdx > 0) tIdx--;
        }
    }
    t[tIdx++] = '\0';

    return strcmp(s, t)==0;
}

/*
Sample inputs to test:
"a##c"
"#a#c"

"ab##"
"c#d#"

"ab#c"
"ad#c"
*/