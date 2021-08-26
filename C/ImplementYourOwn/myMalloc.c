

#include "../standardHeaders.h"

#define _start_heap 0x80000000;
#define _end_heap 0x80001000;


#define USED_MEMORY 0xAABBCCDD
#define FREE_MEMORY 0xDEADC0DE

typedef struct malloc_block {
    unsigned int signature;
    unsigned int size;
} blk_s;

void *myMalloc(unsigned int size) {
    // grab blk_s pointer
    blk_s *blk;
    char *ret = NULL;
    // check where is current heap_end pointer
    static unsigned int end_heap = 0;
    if(!end_heap) {
        end_heap = (unsigned int *)&_end_heap;
    }
    // check if size is 32 bit aligned
    if(((size >> 2) << 2) != size) {
        size = ((size >> 2)+1) << 2;
    }
    // iterate until memory end
    blk = (unsigned int *)&_start_heap;
    while (blk < end_heap) {
        if((blk->signature == FREE_MEMORY) && (blk->size <= size)) {
            blk->signature = USED_MEMORY;
            blk->size = size;
            ret = (char *)blk + sizeof(blk_s);
            return ret;
        }
        blk = (blk_s *) ((char *)blk) + sizeof(blk_s) + blk->size;
    }
    // if memroy NOT found, allocate at the end of the heap_end
    blk = end_heap;
    blk->signature = USED_MEMORY;
    blk->size = size;
    ret = (char *)blk + sizeof(blk_s);
    end_heap = ret + size;
    return ret;
}

void free(void *ptr) {
    blk_s *blk = (blk_s *) (((char *)ptr) - sizeof(blk_s));
    if(!ptr)    return;
    if(blk->signature == FREE_MEMORY)   return;
    if(blk->signature == USED_MEMORY) {
        blk->signature = FREE_MEMORY;
        blk->size = 0;
    }
}
