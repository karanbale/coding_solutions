#include <stdio.h>

#define PREF_OVER_SIZE (01)
#define SIZE_OVER_PERF (00)

#define UNALIGNED(X, Y) \
        (((long)(X) & (sizeof(long)-1)) | ((long)(Y) & (sizeof(long)-1)))

#define LITTLEBLOCKSIZE (sizeof(long))
#define BIGBLOCKSIZE (LITTLEBLOCKSIZE << 2)
#define DETECTNULL(X) (((X) - (0x01010101)) & -(X) & (0x80808080))

void *myStrCpy(void *dst0, const void *src0) {
    char *dst = (char *)dst0;
    char *src = (char *)src0;
    if(SIZE_OVER_PERF) {
        while((*dst++ = *src++));
        return dst0;
    }
    else if(PREF_OVER_SIZE) {
        long *dstAddr = (long *)dst0;
        const long *srcAddr = (long *)src0;
        if(!UNALIGNED(src0, dst0)) {
            while(DETECTNULL(*srcAddr)) {
                *dstAddr++ = *srcAddr;
            }
            src = (char *)srcAddr;
            dst = (char *)dstAddr;
        }
    }
    while((*dst++ = *src++));
    return dst0;
}

int main()
{
    printf("Hello World\n");
    char *src0 = "Hello I am being copied\n";
    char dst0[100] = {0};
    char *tempDst;
    printf("Src: %s, Dst: %s\n", src0, dst0);
    tempDst = myStrCpy(dst0, src0);
    printf("Src: %s, Dst: %s\n", src0, tempDst);
    return 0;
}
