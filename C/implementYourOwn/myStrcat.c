/*
Syntax strcat in C:
    char *strcat(char * restrict s1,const char * restrict s2);

Parameters:
    s1— pointer to the destination array.
    s2— pointer to the source array

Return:
    The strcat function returns the value of s1.

Things to remember about strncat:
You must include string.h header file before using the strcat function in C.
When we use strcat(), the size of the destination buffer must be large enough to store the resultant string,
otherwise the behavior of strcat would be undefined.
Let’s see an example code to understand this point.

*/

#include "../standardHeaders.h"

#define SIZE 40

char *my_strcat(char *s1, const char *s2)
{
    //Pointer should not null pointer
    if((s1 == NULL) && (s2 == NULL))
        return NULL;
    //Create copy of s1
    char *start = s1;
    //Find the end of the destination string
    while(*start != '\0')
    {
        start++;
    }
    //Now append the source string characters
    //until not get null character of s2
    while(*s2 != '\0')
    {
        *start++ = *s2++;
    }
    //Append null character in the last
    *start = '\0';
    return s1;
}

int main()
{
    char dest[SIZE] = "Welcome to ";
    char src[] = "Aticleworld";
    //Append src in dest
    my_strcat(dest, src);
    //print dest after appending src
    printf("%s\n\n",dest);
    printf("%s\n\n",src);
    return 0;
}
