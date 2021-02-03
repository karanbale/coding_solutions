/*
Implement your own memset function in C.

Syntax memcpy in C:
    void *memset(void *s, int c, size_t n);

@Param:

    s— pointer to the destination object.
    c— Value to be filled.
    n — Number of bytes to be filled starting from s to be filled.

@Return:
The memset function returns the value of s. 

Note: s is a void pointer so that we can pass any type of pointer to this function.

Things to remember about memset:
We can use the memset for any memory buffer either for structure, array, or any data type.
We must input the correct memory buffer size, otherwise, show undefined behavior.
As I have mentioned in the above program, the memset function works on byte. It is very important to know.
Before using the memset we must include string.h header file in our program.
The value which you want to copy will first convert in unsigned char.
The memory which you are passing in memset must be valid otherwise you will get undefined behavior.

*/

#include "../standardHeaders.h"

#define SIZE_ARRAY 5
//Own Created memset
void *my_memset(void *s, int c,  unsigned int len)
{
    unsigned char *p = (unsigned char *)s;
    while(len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}
//function to print char of an char array
void printArray(char arr[], int n)
{
    int i =0;
    for (i=0; i<n; i++)
    {
        printf("%c\n", arr[i]);
    }
}
int main()
{
    char arr[SIZE_ARRAY] = "ABCD";
    // Print Array before calling memset
    printArray(arr,SIZE_ARRAY);
    //Calling own created memset
    my_memset(arr,'0', sizeof(arr));
    // Print Array After calling memset
    printArray(arr,SIZE_ARRAY);
    return 0;
}
