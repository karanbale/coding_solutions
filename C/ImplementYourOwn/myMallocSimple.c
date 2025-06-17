#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define MEM_POOL_SIZE 1024
#define ALIGNMENT     8
#define ALIGN(x)      (((x) + (ALIGNMENT-1)) & ~(ALIGNMENT - 1))

typedef struct block {
  uint32_t size;
  struct block *next;
} blockMetadata_t;

static uint8_t mem_pool[MEM_POOL_SIZE] = {0};
blockMetadata_t *free_list = NULL;

void memInit(void) {
  free_list = (blockMetadata_t *)mem_pool;
  free_list->size = MEM_POOL_SIZE - sizeof(blockMetadata_t);
  free_list->next = NULL;
}

void *myMalloc(int size) {
  if(size <= 0) return NULL;
  size = ALIGN(size);
  
  blockMetadata_t *curr = free_list;
  blockMetadata_t *prev = NULL;
  
  while(curr) {
    if (curr->size >= size) {
      // split the block
      if (curr->size > (sizeof(blockMetadata_t) + ALIGNMENT + size)) {
        blockMetadata_t *nextblock = (blockMetadata_t *)((uint8_t *)curr + sizeof(blockMetadata_t) + size);
        nextblock->size = curr->size - size - sizeof(blockMetadata_t);
        nextblock->next = curr->next;

        curr->size = size;
        if (prev) {
          prev->next = nextblock;
        } else {
          free_list = nextblock;
        }
      } else {
        if (prev) {
          prev->next = curr->next;
        } else {
          free_list = curr->next;
        }
        curr->size = size;
      }
      return (void *)((uint8_t *)curr + sizeof(blockMetadata_t));
    }
    prev = curr;
    curr = curr->next;
  }
  return NULL;
}

void myFree(void *p) {
  if (!p) return;
  blockMetadata_t *block = (blockMetadata_t *)((uintptr_t)p - sizeof(blockMetadata_t));
  block->next = free_list;
  free_list = block;
}
