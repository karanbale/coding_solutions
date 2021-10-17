/**
 * @file myMemCopy.c
 * @author Karansingh Bale
 * @brief Write a function that copies bytes from src to dst
 * If there is overlap in src and dst pointers, the behavior is undefined
 * Function should copy bytes in performance mode (after checking we have aligned addresses and large enough data size)
 * Function should copy bytes in one byte at a time format as well if addresses are unaligned OR data is not large enough.
 * This function implementation is from newlib's memcpy() function
 * https://interrupt.memfault.com/blog/memcpy-newlib-nano
 * @version 0.1
 * @date 2021-10-08
 * 
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

/* Nonzero if either X or Y is not aligned on a "long" boundary.  */
#define UNALIGNED(X, Y) \
  (((long)X & (sizeof (long) - 1)) | ((long)Y & (sizeof (long) - 1)))

/* How many bytes are copied each iteration of the word copy loop.  */
#define LITTLEBLOCKSIZE (sizeof (long))

/* How many bytes are copied each iteration of the 4X unrolled loop.  */
#define BIGBLOCKSIZE    (LITTLEBLOCKSIZE << 2)

/* Threshhold for punting to the byte copier.  */
#define TOO_SMALL(LEN)  ((LEN) < BIGBLOCKSIZE)

#define PREFER_SIZE_OVER_SPEED (01)
#define OPTIMIZE_SIZE (0)

/**
 * This function copies <[n]> bytes from the memory region 
 * pointed to by src0 to the memory region pointed to by dst0.
 * If the regions overlap, the behavior is undefined.
*/
void *myMemCpy(void *dst0, const void *src0, size_t nBytes) {
    printf("nBytes: %ld\n", nBytes);

    if((PREFER_SIZE_OVER_SPEED) || (OPTIMIZE_SIZE)) { // if you prefer size over speed
        char *tempSrc = (char *)src0;
        char *tempDst = (char *)dst0;
        void *retAddr = dst0;
        while(nBytes--) {
            *tempDst++ = *tempSrc++;
        }
        return retAddr;
    }
    else {
        // check if your size if multiples of 4x since we can copy 4 bytes at a time to gain speed
        char *dst = dst0;
        const char *src = src0;
        long *aligned_dst;
        const long *aligned_src;
        
        // check if src / dst are UNALIGNED
        // also check if they are too TOO_SMALL
        // in either of above two cases, we should perform byte copy
        if(!(TOO_SMALL(nBytes)) || !UNALIGNED(src, dst)) {
            aligned_src = (long *)src;
            aligned_dst = (long *)dst;
            // faster operation i.e. copy (long x 4) size bytes
            while(BIGBLOCKSIZE <= nBytes) {
                *aligned_dst++ = *aligned_src++;
                *aligned_dst++ = *aligned_src++;
                *aligned_dst++ = *aligned_src++;
                *aligned_dst++ = *aligned_src++;
                nBytes -= BIGBLOCKSIZE;
            }
            // slightly slower operation i.e. copy (long x 1) size bytes
            while(LITTLEBLOCKSIZE <= nBytes) {
                *aligned_dst++ = *aligned_src++;
                nBytes -= LITTLEBLOCKSIZE;
            }
            // update dst / src pointers
            dst = (char *)aligned_dst;
            src = (char *)aligned_src;
        }
        // simply char size byte copy
        while(nBytes--) {
            *dst++ = *src++;
        }
        return dst0;
    }
}

void test_memcpy(void* (*memCpy)(void *, void *, size_t)) {
  struct test_struct {
    char data[4096];
  };
  // instantiate 2 structs. for our purposes, we don't care what data is in
  // there. set them to `volatile` so the compiler won't optimize away what we
  // do with them
  volatile struct test_struct dest, source;

  // run through powers-of-two memcpy's, printing stats for each test
  for (size_t len = 1; len <= sizeof(dest); len <<= 1) {
    // Calculate the time taken by myMemCpy()
    clock_t t;
    t = clock();
    
    memCpy((void *)&dest, (void *)&source, len);
    
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("memcpy() took %f seconds to execute \n", time_taken);
  }
}

int main()
{
    const char src0[] = "Hello World I am a free bird copying bytes from here to there\n";
    char dst0[100] = {0};
    printf("Src: %s, Dst: %s, strlen(src0): %ld\n", src0, dst0, strlen(src0));
    char *tempDst = myMemCpy(dst0, src0, strlen(src0));
    printf("Src: %s, Dst: %s\n", src0, tempDst);
    
    test_memcpy((void *)myMemCpy);

    return 0;
}
