/*
A character in UTF8 can be from 1 to 4 bytes long, subjected to the following rules:

For 1-byte character, the first bit is a 0, followed by its unicode code.
For n-bytes character, the first n-bits are all one's, the n+1 bit is 0, followed by n-1 bytes with most significant 2 bits being 10.
This is how the UTF-8 encoding would work:

   Char. number range  |        UTF-8 octet sequence
      (hexadecimal)    |              (binary)
   --------------------+---------------------------------------------
   0000 0000-0000 007F | 0xxxxxxx
   0000 0080-0000 07FF | 110xxxxx 10xxxxxx
   0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
   0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
Given an array of integers representing the data, return whether it is a valid utf-8 encoding.

Note:
The input is an array of integers. Only the least significant 8 bits of each integer is used to store the data. This means each integer represents only 1 byte of data.

Example 1:

data = [197, 130, 1], which represents the octet sequence: 11000101 10000010 00000001.

Return true.
It is a valid utf-8 encoding for a 2-bytes character followed by a 1-byte character.
Example 2:

data = [235, 140, 4], which represented the octet sequence: 11101011 10001100 00000100.

Return false.
The first 3 bits are all one's and the 4th bit is 0 means it is a 3-bytes character.
The next byte is a continuation byte which starts with 10 and that's correct.
But the second continuation byte does not start with 10, so it is invalid.
*/

#include "../standardHeaders.h"

int mask4 = 0xF8, pattern4 = 0xF0,
    mask3 = 0xF0, pattern3 = 0xE0,
    mask2 = 0xE0, pattern2 = 0xC0,
    mask5 = 0xC0, pattern5 = 0x80, // NOTE: remaining byte data must begin with 10xx xxxx ==> 0x80
    mask1 = 0x80, pattern1 = 0x00;

// All remaining numbers must have data which starts with 0x80
static inline int validRemaining(int data){
    return (data & mask5) == pattern5;
}

// UTF-8 encoding successful if current data is smaller than 0x80
// remainder of a number smaller than 0x80, ANDed with 0x80 will yield 0x00
// e.g. 0x7F & 0x80 = 0x00
static inline int valid1(int data){
    return (data & mask1) == pattern1;
}

// UTF-8 encoding successful if current data is smaller than 0xE0 and greater than 0xC0
// remainder of a number smaller than 0xE0, ANDed with 0xE0 will yield 0xC0
// e.g. 0xDF & 0xE0 = 0xC0
static inline int valid2(int data){
    return (data & mask2) == pattern2;
}

// UTF-8 encoding successful if current data is smaller than 0xF0 and greater than 0xE0
// remainder of a number smaller than 0xF0, ANDed with 0xF0 will yield 0xE0
// e.g. 0xEF & 0xF0 = 0xE0
static inline int valid3(int data){
    return (data & mask3) == pattern3;
}

// UTF-8 encoding successful if current data is smaller than 0xF8 and greater than 0xF0
// remainder of a number smaller than 0xF8, ANDed with 0xF8 will yield 0xF0
// e.g. 0xF7 & 0xF8 = 0xF0
static inline int valid4(int data){
    return (data & mask4) == pattern4;
}

// UTF-8 encoding successful if current data is smaller than 0xE0 and greater than 0xC0
// remainder of a number smaller than 0xE0, ANDed with 0xE0 will yield 0xC0
bool validUtf8(int* data, int dataSize){
    int numOfBytesToCheck = 0;
    for(int i=0; i<dataSize; i++){
        if(valid1(data[i])){
            continue;
        }
        else if(valid2(data[i])){
            numOfBytesToCheck = 1;
        }
        else if(valid3(data[i])){
            numOfBytesToCheck = 2;
        }
        else if(valid4(data[i])){
            numOfBytesToCheck = 3;
        }
        else{
            return false;
        }
        
        while(numOfBytesToCheck-- > 0){
            // if ran out of numbers to process in the array, return false
            // or if remaining data does NOT start with 0x80, return false
            if(++i >= dataSize || !validRemaining(data[i])){
                return false;
            }
        }
    }
    // processed all numbers successfully
    return true;
}
