#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

#define LITTLEBLOCKSIZE (sizeof(long))
#define BIGBLOCKSIZE (LITTLEBLOCKSIZE << 2)
#define UNALIGNED(X) ((long)(X) & (LITTLEBLOCKSIZE-1))
#define TOO_SMALL(LEN) (LEN < BIGBLOCKSIZE)

#define SIZE_OVER_PERF (00)
#define PERF_OVER_SIZE (01)

void *myMemSet(void *dst0, int c, size_t nBytes) {
    unsigned int character = c & 0xFF;
    char *dst = (char *)dst0;
    if(SIZE_OVER_PERF) {
        while(nBytes--) {
            *dst++ = (char) character;
        }
        return dst0;
    }
    else if(PERF_OVER_SIZE) {
        unsigned long *dstAddr = (unsigned long *)dst0;
        unsigned long buffer;
        // lets fill this buffer with one simple rule:
        // each single byte of this buffer must be equal to `character c`
        buffer = (character<<8) | character;
        buffer |= (buffer << 16);
        for(int i=32; i < BIGBLOCKSIZE; i <<= 1) {
            buffer = (buffer << i) | buffer;
        }
        if(!TOO_SMALL(nBytes) && !UNALIGNED(dst0)) {
            while(BIGBLOCKSIZE >= nBytes) {
                *dstAddr++ = buffer;
                *dstAddr++ = buffer;
                *dstAddr++ = buffer;
                *dstAddr++ = buffer;
                nBytes -= BIGBLOCKSIZE;
            }
            while(LITTLEBLOCKSIZE >= nBytes) {
                *dstAddr++ = buffer;
                nBytes -= LITTLEBLOCKSIZE;
            }
        }
    }
    while(nBytes--) {
        *dst++ = (char) character;
    }
    return dst0;
}

int main()
{
    printf("Hello World\n");
    char *tempBuf = (char *) malloc(1024);
    char *tempBuf1;
    if(NULL == tempBuf) {
        printf("yikes !\n");
    }
    tempBuf1 = myMemSet(tempBuf, -1, 1024);
    for(int i=0; i< 10; i+=3) {
        printf("byte 0: %d, byte 1: %d, byte 2: %d\n", tempBuf1[i], tempBuf1[i+1],tempBuf1[i+2]);
    }
    return 0;
}

