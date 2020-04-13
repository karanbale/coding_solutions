/*

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"

*/


#include "../standardHeaders.h"

char palindromeSubStr[1000];

char * longestPalindrome_1(char * inputStr){
    int maxLen = 1000;
    int retLen = 0;
    char* inputStrStart = inputStr;
    char* subInputStrEnd = inputStrStart;
    char* subInputStrStart = inputStrStart;
    
    if(strlen(inputStr) == 0) return NULL;
    if(strlen(inputStr) > maxLen) return NULL;
    if(strlen(inputStr) == 1) return inputStr;
    
    int numStrFound = 0;
    printf("bc %s\n", inputStr);
    for(char charIndex=0; *(inputStr+charIndex) != '\0'; charIndex++){
        int subStrStartLen = charIndex;
        int subStrEndLen = subStrStartLen+1;
        char subStrFwd[strlen(inputStr)];
        memset(subStrFwd, '\0', sizeof(subStrFwd));
        int revSubStrLen = 0;
        
        // take two pointers, start them at same character
        subInputStrStart = inputStrStart;
        subInputStrEnd = (inputStrStart+1);
        printf("Start: %c\t", *subInputStrStart);
        printf("%c\n", *subInputStrEnd);
        
        // increment end pointer and compare with start pointer
        // break if we match 
        printf("compare: %c\t", *(subInputStrStart+subStrStartLen));
        printf("%c\n", *(subInputStrStart+subStrEndLen));
        // while(*(subInputStrStart+subStrEndLen) != *(subInputStrStart+subStrStartLen)){
        //     // subStrFwd[revSubStrLen++] = subInputStrStart[subStrStartLen];
        //     printf("%c\t", *(subInputStrStart+subStrStartLen));
        //     printf("%c\n", *(subInputStrStart+subStrEndLen));
        //     subStrEndLen++;     // count length of this substring
        // }

        while(*subInputStrStart != *subInputStrEnd){
            printf("%c", *subInputStrEnd);
            revSubStrLen++;
            subInputStrEnd++;
        }
        printf("\n");

        strncpy(subStrFwd, (inputStr+subStrStartLen), revSubStrLen);

        // printf("strStart: %c \t strEnd: %d \n", *subInputStrStart, (subStrEndLen-subStrStartLen));        
        // strncpy(subStrFwd, (inputStr+subStrStartLen), (subStrEndLen-subStrStartLen));

        if(*(subInputStrStart+subStrEndLen) == *(inputStrStart+subStrStartLen)){
            printf("len: %d, max_len:%d\n", subStrEndLen, subStrEndLen+2);
            bool palindromeValid = false;
            while(subStrStartLen <= subStrEndLen){
                if(*(subInputStrStart+subStrStartLen) == *(subInputStrStart+subStrEndLen)){
                    palindromeValid = true; 
                }
                else{
                    palindromeValid = false; 
                }
                subInputStrEnd--;          // track back to previous char
                subStrStartLen++;        // keep walking to next char
            }

            if(palindromeValid){
                if(retLen <= (subStrStartLen-charIndex)){
                    retLen = (subStrStartLen-charIndex);
                    for (size_t i = (subStrStartLen-charIndex); i < subStrFwd[subStrStartLen-charIndex] != '\0'; subStrStartLen++, i++)
                    {                                       
                        palindromeSubStr[numStrFound++] = *(subStrFwd+(subStrStartLen-charIndex));                        
                        printf("%c\t",palindromeSubStr[numStrFound++]);
                    }
                    printf("\n");
                    //retLen = fmax(retLen,(subStrStartLen-charIndex));
                }
            }
        }
        // we've reached to the end of the string
        // and there is no matching string found, return NULL
        else if(*(subInputStrStart+subStrEndLen+1) == '\0'){
            printf("returning NULL\n");
            return NULL;
        }
        inputStrStart++; // move on to next character
    }
    
    // for(int i = 0; i<numStrFound; i++){
    //     printf("%s\n", palindromeSubStr[i]);
    //     if(palindromeSubStr[i] == retLen){
    //         return palindromeSubStr;
    //         // return NULL;
    //     }
    // }
    
    printf("returning: %s", palindromeSubStr);

    return palindromeSubStr;

}

#define MAX_PERMISSIBLE_LEN 1001
char retStr[MAX_PERMISSIBLE_LEN];
char * longestPalindrome(char * str){
    memset(retStr, '\0', sizeof(retStr));
    // by default 1st character will always be a palidrome
    strncpy(retStr, str, 1);

    char* inputStartStr = str;
    int maxRetLen = 0;
    if((strlen(str) <= 1) || (strlen(str) > 1000)) return str;
    if(strlen(str) == 2){
        if( *str == *(++inputStartStr)){
            return str;
        }
    }
    
    while(inputStartStr <= (str+strlen(str)-1)){
        char* inputEndStr = (str+strlen(str)-1);
        char* inputStart = inputStartStr;
        char outStr[MAX_PERMISSIBLE_LEN];
        while(inputEndStr != inputStart){
            bool isPalindrome = false;
            char* inputEnd = inputEndStr;
            int count = 0;
            memset(outStr, '\0', sizeof(outStr));
            do{
                if(*inputStart == *inputEnd){
                    isPalindrome = true;
                    outStr[count++] = *inputStart;
                    inputStart++;
                    inputEnd--;
                }
                else{
                    isPalindrome = false;
                } 
            }while((isPalindrome) && (inputEnd >= inputStart));

            if(isPalindrome){
                while(inputStart <= inputEndStr){
                    outStr[count++] = *inputStart;
                    inputStart++;
                }
                if(count > maxRetLen){
                    maxRetLen = count;
                    strcpy(retStr, outStr);
                    printf("found next max palindrome: %s \t len: %d\n", outStr, maxRetLen);
                }
                // ensure we dont max out already, if so, just return
                if(maxRetLen >= 1000){
                    return retStr;
                }
            }
            if(inputEndStr != str){
                // decrement end str
                inputEndStr--;
                // forcibly restore start back to its original index
                // since we may change inputStart while finding palindrome
                inputStart = inputStartStr;
            }  
            else{
                return NULL;
            }
        }
        inputStartStr++;
    }
    return retStr;
}

int main(void){

    // char inputStr[] = "bababb";
    char inputStr[][1000] = {"bababb", "sdfdsdfsdfsd", "cbbd", "BABAD", "a", "cb", "bb"};
    for(int i=0; i<7; i++){
        char * string = longestPalindrome(inputStr[i]);
        printf("\n*****************************\n");
        printf("Input: %s \t Palindrome: %s ", inputStr[i], string);
        printf("\n*****************************\n");
    }
    return 0;

}

