/*
Implement atoi which converts a string to an integer.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. 
Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, 
and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, 
which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, 
or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

Note:

Only the space character ' ' is considered as whitespace character.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. 
If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.
Example 1:

Input: "42"
Output: 42
Example 2:

Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.
Example 3:

Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.
Example 4:

Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical 
             digit or a +/- sign. Therefore no valid conversion could be performed.
Example 5:

Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
             Thefore INT_MIN (−231) is returned.
*/

#include "string_manipulation_headers.h"

#define ENABLE_PRINTS 1

void printf_wrapper(const char * message, ...) {
    va_list args;
    va_start(args, message);
#ifdef ENABLE_PRINTS
    vprintf(message, args);
#endif
    va_end(args);
}

int myAtoi(const char *str){
    // define retVal as signed size_t since its going to be compared
    // against INT32_MAX/INT32_MIN with sign bit
    ssize_t retVal = 0;
    signed int sign = 1, count_digit=0;
    bool sign_found = false, first_num_found=false;

    // discard all white space characters at the beginning
    while (*str == ' ') str++;

    // check if current char is a + or - sign or a valid digit else return
    if((((*str - '0') >= 0) && ((*str - '0') <= 9)) || ((*str == '-') || (*str == '+'))){
       while(*str != '\0'){
           // if((retVal * sign) > INT32_MAX) return INT32_MAX;           
           // if((retVal * sign) < INT32_MIN) return INT32_MIN;
           if((*str == '-') || (*str == '+')){
               // if signs is seen AFTER numbers have been seen either for first
               // time or again after first sign
               // e.g. "-5-" or "123-"
               if(first_num_found){
                 return (sign_found ? (retVal*sign) : retVal);
               }
               
               // If we've already seen the sign and this is second occurance
               // of it, return the value along with sign
               if(sign_found) return (retVal*sign);
               
               // You've found the sign
               sign_found = true;
               
               // Assign appropriate sign and continue
               sign = ((*str++ == '-') ? -1 : 1);               
               continue;
           }
           
           // stop processing upon encountering first non-digit character
           // don't return yet, since we might have valid data calculated
           // which needs to be validated against INT32_MAX/INT32_MIN
           // e.g. "2014 blah blah" or "2147483646"
           if((*str < '0') || (*str > '9')) break;
           
           // ignore all 0 digits at the beginning of the number
           // e.g. "0000000000012345"
           if(count_digit == 0 && *str == '0'){ 
               first_num_found=true; 
               str++; 
               continue; 
           }
           
           // input number is > than 11 digits and is -ve return INT32_MIN   
           if(count_digit > 11 && sign == -1) return INT32_MIN;
           
           // input number is > than 11 digits and is -ve return INT32_MAX
           if(count_digit > 11 && sign == 1) return INT32_MAX;
           count_digit++;
           
           first_num_found=true;
           
           // take older value, multiply it by 10 and add existing number digit
           retVal = ((retVal * 10) + (*str++ - '0'));           
        } 
        // update number with its sign
        retVal *= sign;
    }
    
    // if number is OOB (Out of bounds) return MAX
    if(retVal > (INT32_MAX)){
        return INT32_MAX;
    }
    // if number is OOB (Out of bounds) return MIN
    if(retVal < (INT32_MIN)){
        return INT32_MIN;
    }

    return (retVal);
    
}

int main() {

    // return should be 42
    const char *str1 = "42";
    printf("atoi for %s : %d\t %d\n\n", str1, myAtoi(str1), atoi(str1));

    // return should be -2014
    const char *str2 = "      -2014";
    printf("atoi for %s : %d\t %d\n\n", str2, myAtoi(str2), atoi(str2));

    // return should be 2014
    const char *str3 = "2014 blah blah";
    printf("atoi for %s : %d\t %d\n\n", str3, myAtoi(str3), atoi(str3));

    // return should be 0
    const char *str4 = "whatever blah 2014";
    printf("atoi for %s : %d\t %d\n\n", str4, myAtoi(str4), atoi(str4));

    // return should be 1
    const char *str5 = "+1";
    printf("atoi for %s : %d\t %d\n\n", str5, myAtoi(str5), atoi(str5));

    // return should be -43
    const char *str6 = "      -43";
    printf("atoi for %s : %d\t %d\n\n", str6, myAtoi(str6), atoi(str6));

    // return should be 0 since its not a valid number
    const char *str7 = "      +-43";
    printf("atoi for %s : %d\t %d\n\n", str7, myAtoi(str7), atoi(str7));

    // this e.g. probably to test uint / int limits and check overflows in math
    const char *str8 = "-91283472332";
    printf("atoi for %s : %d\t %d\n\n", str8, myAtoi(str8), atoi(str8));

    // this e.g. probably to test uint / int limits and check overflows in math
    const char *str9 = "2147483646";
    printf("atoi for %s : %d\t %d\n\n", str9, myAtoi(str9), atoi(str9));

    // this e.g. probably to test sign appearing on either side of the number
    const char *str10 = "-5-";
    printf("atoi for %s : %d\t %d\n\n", str10, myAtoi(str10), atoi(str10));

}