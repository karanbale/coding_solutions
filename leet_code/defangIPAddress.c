/*
Given a valid (IPv4) IP address, return a defanged version of that IP address.

A defanged IP address replaces every period "." with "[.]".

 

Example 1:

Input: address = "1.1.1.1"
Output: "1[.]1[.]1[.]1"
Example 2:

Input: address = "255.100.50.0"
Output: "255[.]100[.]50[.]0"
*/

#include "../C/standardHeaders.h"

char * defangIPaddr(char * address){
    
    // allocate heap memory of maximum, expected defanged array type
    char *temp_addr = calloc(1, sizeof("xxx[.]xxx[.]xxx[.]xxx"));
    
    // take a pointer to point to this address
    char *temp_addr_ptr = temp_addr;
    
    // iterate over given address, one character at a time
    for(char *c=address; *c; c++){
        // if current character is '.' then replace it with '[.]'
        // else simply store it in heap memory's array
        *c == '.' ? *temp_addr++='[',*temp_addr++='.',*temp_addr++=']':(*temp_addr++=*c);
    }
    
    // return newly formed array in defanged format
    return temp_addr_ptr;
}

int main(void){

    char ip_addr_list[2][16] = {"1.1.1.1", "100.100.100.100"};
    for(int i=0; i<2; i++){
        printf("Current IP address: %s\n", ip_addr_list[i]);
        printf("Defanged IP address: %s\n",defangIPaddr(ip_addr_list[i]));
        printf("\n");
    }
    return 0;
}
