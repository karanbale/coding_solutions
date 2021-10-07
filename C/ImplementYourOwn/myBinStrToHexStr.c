/**
 * @file myBinStrToHexStr.c
 * @author Karan Bale
 * @brief Write a function to convert binary string input to hex string output.
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>

void binToHex(const char *inPtr) {
    if(NULL == inPtr) return;
    const char *ptr = inPtr;
    size_t retNum = 0;
    int count = 0;
    char retPtr[32] = {0};
    char *tempPtr = retPtr;
    while(*ptr != '\0') {
        retNum = (retNum*2) + (*ptr - '0');
        ++ptr;
        ++count;
        if (count == 4) {
            count = 0;
            *tempPtr++ = (retNum > 9) ? (retNum - 10) + 'A' : retNum + '0';
            retNum = 0;
        }
    }
    *tempPtr = '\0';
    printf("Num str: %s, Num Hex: 0x%s\n", inPtr, retPtr);
}

int main()
{
    printf("Hello World\n");
    binToHex("00001111");
    binToHex("10001111");
    binToHex("01111111");
    binToHex("10111101");

    return 0;
}
