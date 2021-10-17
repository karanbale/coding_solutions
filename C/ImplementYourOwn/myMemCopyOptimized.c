#include <stdio.h>
#include <string.h>

#define UNALINGED(X, Y) \
    (((long)X & (sizeof(long)-1)) | ((long)Y & (sizeof(long)-1)))

#define LITTLEBLOCKSIZE (sizeof(long))
#define BIGBLOCKSIZE (LITTLEBLOCKSIZE << 2)
#define TOO_SMALL(LEN) (LEN < BIGBLOCKSIZE)

#define PERF_OVER_SIZE (01)
#define SIZE_OVER_PERF (00)

void *myOptimizedMemMove(void *dst0, const void *src0, size_t nBytes) {
    if(SIZE_OVER_PERF) {
        char *dst = (char *)dst0;
        char *src = (char *)src0;
        // check dst address is between src and (src + nBytes)
        // if it is, copy backwards
        if (src < dst && dst < (src + nBytes)) {
            src += nBytes;
            dst += nBytes;
            while(nBytes--) {
                *--dst = *--src;
            }
        }
        else {
            while(nBytes--) {
                *dst++ = *src++;
            }
        }
        return dst0;
    }
    else if(PERF_OVER_SIZE) {
        char *dst = (char *)dst0;
        char *src = (char *)src0;
        long *aligned_dst = (long *)dst0;
        long *aligned_src = (long *)src0;
        // destructive overlap, MUST copy backwards byte by byte, no other option
        // check dst address is between src and (src + nBytes)
        // if it is, copy backwards
        if (src < dst && dst < (src + nBytes)) {
            src += nBytes;
            dst += nBytes;
            while(nBytes--) {
                *--dst = *--src;
            }
        }
        else {
            if(!TOO_SMALL(nBytes) && !UNALINGED(src, dst)) {
                while(BIGBLOCKSIZE >= nBytes) {
                    *aligned_dst++ = *aligned_src++;
                    *aligned_dst++ = *aligned_src++;
                    *aligned_dst++ = *aligned_src++;
                    *aligned_dst++ = *aligned_src++;
                    nBytes -= BIGBLOCKSIZE;
                }
                while(LITTLEBLOCKSIZE >= nBytes) {
                    *aligned_dst++ = *aligned_src++;
                    nBytes -= LITTLEBLOCKSIZE;
                }
            }
            while(nBytes--) {
                *dst++ = *src++;
            }
        }
        return dst0;
    }
}

int main()
{
    printf("Hello World\n");
    char src0[] = "Hello I am new here";
    char dst0[100] = {0};
    char *tempDst;
    printf("src: %s, dst: %s\n", src0, dst0);
    tempDst = myOptimizedMemMove(dst0, src0, strlen(src0));
    printf("dst: %s\n", tempDst);
    tempDst = myOptimizedMemMove(src0+1, src0, strlen(src0));
    printf("dst: %s\n", src0);
    return 0;
}
