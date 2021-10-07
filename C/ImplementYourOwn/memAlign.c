/* Allocate aligned memory in a portable way.
 *
 * Memory allocated with aligned alloc *MUST* be freed using aligned_free.
 *
 * @param alignment The number of bytes to which memory must be aligned. This
 *  value *must* be <= 255.
 * @param bytes The number of bytes to allocate.
 * @param zero If true, the returned memory will be zeroed. If false, the
 *  contents of the returned memory are undefined.
 * @returns A pointer to `size` bytes of memory, aligned to an `alignment`-byte
 *  boundary.
 */

#include "../standardHeaders.h"

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

void freeMem(void *aligned_ptr);
void test_mask(size_t alignment, size_t size, bool init);

static inline _Bool is_aligned(const void * pointer, size_t byte_count) {
    return (uintptr_t)pointer % (byte_count) == 0;
}

void freeMem(void *aligned_ptr) {
  int offset = *(((char *)aligned_ptr) - 1);
  free((char *)aligned_ptr - offset);
}

void test_mask(size_t alignment, size_t size, bool init) {
  // calculate total size
  size_t totalSize = alignment + size;

  // allocate memory
  void * buf = (void *)(init ? calloc(0, totalSize) : malloc(totalSize));
  if (NULL == buf) return;

  // check if returned memory address is aligned or not
  size_t remainder = ((uintptr_t) buf) % alignment;

  // if remainder is 0, we add extra alignment bytes to the base address, this is our worse case scenario
  // if remainder is positive, we add alignment - remainder worth bytes to base address
  size_t offset = alignment - remainder;

  // add extra bytes to the base address and maintain a pointer to new memory address that is aligned
  // and can be returned
  void * ret = (void *)((uintptr_t)buf + (unsigned char)offset);

  // save the number of extra bytes added to base address so we can free corretly, without memory leak
  *(unsigned char *)(ret - 1) = offset;

  // printf("Mask: 0x%08" PRIXPTR "\n", mask);
  printf("Buf: 0x%08" PRIXPTR ", Ret: 0x%08" PRIXPTR "\n", (uintptr_t)buf, (uintptr_t)ret);
  printf("is Buf aligned: %d, is Ret aligned: %d\n", is_aligned(buf, alignment), is_aligned(ret, alignment));
  freeMem(ret);
  // return the address that is aligned to alignment bytes given
  // return (void *)ret;
}

int main()
{
    test_mask(15, 1024, 1);
    test_mask(31, 1024, 1);
    test_mask(63, 1024, 1);
    test_mask(127, 1024, 1);
    return(0);
}
