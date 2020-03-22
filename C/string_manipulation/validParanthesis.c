/*
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Example 1:

Input: "()"
Output: true
Example 2:

Input: "()[]{}"
Output: true
Example 3:

Input: "(]"
Output: false
Example 4:

Input: "([)]"
Output: false
Example 5:

Input: "{[]}"
Output: true

*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdarg.h>

char lut[] = {
        0,
        ['{'] = '}',
        ['['] = ']',
        ['('] = ')',
        [255] = 0,
};
bool lut_pop_characters[] = {
        false,
        [']'] = true,
        ['}'] = true,
        [')'] = true,
        [255] = 0
};

/***********************************************************************************************/
/*************************************** SOLTUION 1 ********************************************/
/***********************************************************************************************/

int isValidOpeningChar(char * s){
    // printf("char: %c", *s);
    if((*s == '{') || (*s == '(') || (*s == '[')){
        return 1;
    }
    else return 0;
}

char retClosingCompliment(char * s){
    if(*s == '(') return ')';
    if(*s == '{') return '}';
    if(*s == '[') return ']';
    return '?';
}

bool isValid1(char * s){
    char *temp = s;
    size_t round_cnt=0, par_cnt=0, sqr_cnt=0;
    if(strlen(s) %2 != 0) return false;
    
    while(*temp != '\0'){
        if(*temp == '(' || *temp == ')') round_cnt++;
        if(*temp == '{' || *temp == '}') par_cnt++;
        if(*temp == '[' || *temp == ']') sqr_cnt++;
        temp++;
    }
    if(((round_cnt % 2) != 0) || ((par_cnt % 2) != 0) || ((sqr_cnt % 2) != 0)) return false;
    
    size_t firstCharPos = 0, nxtCharPos = 0;
    while(s[firstCharPos] != '\0'){
        bool found = false;
        nxtCharPos = firstCharPos+1;
        if(isValidOpeningChar(s+firstCharPos) == 0) { 
            firstCharPos++; 
            continue;
        }
        printf("curr: %c next: %c compliment: %c \n",s[firstCharPos], s[nxtCharPos], prospectClosingChar);
        while(nxtCharPos != strlen(s)){
            // check if next closing bracket matches with current bracket
            if(s[nxtCharPos] == lut[*(s+firstCharPos)]){
                // both are equal, with even distance
                if(((nxtCharPos - firstCharPos)+1) % 2 == 0){
                    found = true;
                    break;
                }
            }
            // continue the loop
            nxtCharPos++;
        }
        if(found == false) return false;
        firstCharPos++;
    }
    
    printf("returning.\n");
    return true;
    
}

/***********************************************************************************************/
/*************************************** SOLTUION 2 ********************************************/
/***********************************************************************************************/

char NO_RESULT[] = "\0";
char* push_val( char* val )
{
    printf("val: %c, next:%c \n",*val, *(val+1));
        for( char* c = val + 1; *c != '\0'; c++ )
        {
            printf("char_val: %c\n", *c);
                if( lut[ *c ] != 0 ){
                    c = push_val( c );
                }
                else if( lut[ *val ] == *c ) {printf("ret: %c\n", *c); return c;}
                else if( lut_pop_characters[ *c ] ){ printf("breaking \n"); break;}
        }
        return NO_RESULT;
}
bool isValid2(char * s){
    // for(int i=0; i<5; i++) printf("lut_pop: %d\n", lut_pop_characters[i]);
    // for(int i=0; i<5; i++) printf("lut: %d\n", lut[i]);
    for( char* c = s; *c != '\0'; c++ )
        {
                // Failure condition
                printf("char: %c, lut_pop: %c\n", *c, lut_pop_characters[ *c ]);
                if( lut_pop_characters[ *c ] ) return false;
                // Pop condition
                printf("char: %c, lut: %c\n", *c, lut[ *c ]);
                if( lut[ *c ] ) c = push_val( c );
                // Propogated failure
                if( c == NO_RESULT ) return false;
        }
        return true;
}
/***********************************************************************************************/

int main(void){

    printf("\n");
    char str[] = "(){}[]";
    //printf("input: %s output: %d\n",str, isValid1(str));
    printf("input: %s output: %d\n",str, isValid2(str));
    return 0;

}