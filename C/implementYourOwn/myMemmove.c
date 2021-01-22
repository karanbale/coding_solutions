/*
Implement your own memmove() function.

Overview:
    The memmove function copies n characters from the source to the destination object.
    In memmove before copying the characters from source to destination object,
    first copied the n character from source to the temporary array,
    after that, copy n character from the temporary array to the destination object.
    It prevents from the undefined behavior when the source and destination object overlaps.

Syntax:
    void *memmove(void * restrict dst, const void *src, size_t n);

Parameters:
    dst— pointer to the destination  object
    src— pointer to the source object
    n — Number of bytes to copy.

Return value:
The memmove function returns the value of dst.

Things to remember about memmove.

1. If you can guarantee that the source and destination buffer do not overlap, you should use memcpy.
If you cannot guarantee that the buffers don’t overlap, you should use memmove.
The memcpy function shows undefined behavior with overlapped buffers. Let’s see an example,

2. The memcpy() function will always be at least as fast as memmove.
However, on most platforms, the difference will be minimal.
*/

#include "../standardHeaders.h"

#include<stdio.h>
void * my_memmove(void* dest, const void* src, unsigned int n)
{
    char *pDest = (char *)dest;
    const char *pSrc =( const char*)src;
    //allocate memory for tmp array
    char *tmp  = (char *)malloc(sizeof(char ) * n);
    if(NULL == tmp)
    {
        return NULL;
    }
    else
    {
        // copy src to tmp array
        for(int i =0; i < n ; ++i)
        {
            tmp[i] = pSrc[i];
        }
        //copy tmp to dest
        for(int i =0 ; i < n ; ++i)
        {
            pDest[i] = tmp[i];
        }
        free(tmp); //free allocated memory
    }
    return dest;
}
int main()
{
    char cSrc[] = "Aticleworld";
    // The destination string size is 14.
    char cDest[16] = {0};
    // copying n bytes of cSrc into cDest
    //Using own my_memcpy function
    my_memmove(cDest, cSrc, 12);
    printf("Copied string: %s\n", cDest);
    int iSrc[] = {10, 20, 30, 40, 50};
    int n = sizeof(iSrc)/sizeof(iSrc[0]);
    int iDest[n], index = 0;
    // copying n bytes of iSrc into iDest
    //Using own my_memcpy function
    my_memmove(iDest, iSrc, sizeof(iSrc));
    printf("\nCopied array is ");
    for (index=0; index<n; index++)
    {
        printf("%d ", iDest[index]);
    }
    return 0;
}
