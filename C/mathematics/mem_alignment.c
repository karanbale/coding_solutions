#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void memset_16aligned(void *space, char byte, size_t nbytes)
{
    assert((nbytes & 0x0F) == 0);
    assert(((uintptr_t)space & 0x0F) == 0);
    memset(space, byte, nbytes);  // Not a custom implementation of memset()
}

static void test_mask(size_t align)
{
    uintptr_t mask = ~(uintptr_t)(align - 1);
    void *mem = malloc(1024+align-1);
    void *ptr = (void *)(((uintptr_t)mem+align-1) & mask);
    assert((align & (align - 1)) == 0);
    printf("Mask: 0x%08" PRIXPTR "\n", mask);
    printf("0x%08" PRIXPTR ", 0x%08" PRIXPTR ", 0x%08" PRIXPTR "\n", (uintptr_t)mem, (uintptr_t)ptr, (uintptr_t)mask);
    memset_16aligned(ptr, 0, 1024);
    free(mem);
}

int main(void)
{
    test_mask(16);
    test_mask(32);
    test_mask(64);
    test_mask(128);
    return(0);
}
