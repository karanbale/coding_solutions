/*
Design and implement a data structure for Least Frequently Used (LFU) cache.
Implement the LFUCache class:

LFUCache(int capacity) Initializes the object with the capacity of the data structure.
int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
void put(int key, int value) Sets or inserts the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item. For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be evicted.
Notice that the number of times an item is used is the number of calls to the get and put functions for that item since it was inserted. This number is set to zero when the item is removed.

Example 1:

Input
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]

Explanation
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);
lfu.put(2, 2);
lfu.get(1);      // return 1
lfu.put(3, 3);   // evicts key 2
lfu.get(2);      // return -1 (not found)
lfu.get(3);      // return 3
lfu.put(4, 4);   // evicts key 1.
lfu.get(1);      // return -1 (not found)
lfu.get(3);      // return 3
lfu.get(4);      // return 4
 

Constraints:

0 <= capacity, key, value <= 104
At most 105 calls will be made to get and put.
*/

#include "../standardHeaders.h"

#define MAX_CACHE_ITEMS 3192
#define MAX_FREQ 128

typedef struct LFUCache LFUCache;
typedef struct LFUCache {   // Cache entry
    int freq;
    int val;
    bool valid;
    LFUCache *prev;
    LFUCache *next;
} LFUCache;

struct freq_m {             // Freq-list data
    LFUCache *head;
    LFUCache *tail;
};

struct cache_data {         // Main data
    int capacity;
    int size;
    int lfreq_index;        // Indexes freq-lists
    LFUCache *cache;        // Cache entries
    struct freq_m *fm;      // Freq-lists
};

inline void *cache_alloc(int capacity);
inline void cache_dealloc(void *cache);
inline void refresh_cache(LFUCache *item, struct cache_data *cdata, bool new_entry);

LFUCache* lFUCacheCreate(int capacity) {
    return cache_alloc(capacity);
}

int lFUCacheGet(LFUCache* obj, int key) {
    struct cache_data *cdata = (void *)obj;
    LFUCache *item = &cdata->cache[key];
    if (cdata->capacity <= 0 || !item->valid)
        return -1;
    refresh_cache(item, cdata, false);
    return item->val;
}

void lFUCachePut(LFUCache* obj, int key, int value) {
    struct cache_data *cdata = (void *)obj;
    LFUCache *item = &cdata->cache[key];
    if (cdata->capacity <= 0 || key >= MAX_CACHE_ITEMS)
        return;
    refresh_cache(item, cdata, !item->valid);
    item->val = value; 
}

void lFUCacheFree(LFUCache* obj) {
    cache_dealloc(obj);
}

// Sets up cache
inline void *cache_alloc(int capacity)
{
    if (capacity > MAX_CACHE_ITEMS)
        return NULL;
    struct cache_data *cdata = calloc(1, sizeof *cdata);
    cdata->capacity = capacity;
    cdata->cache = calloc(1, sizeof(LFUCache [MAX_CACHE_ITEMS]));
    cdata->fm = calloc(1, sizeof(struct freq_m [MAX_FREQ]));
    return cdata;
}

// Relinquishes cache
inline void cache_dealloc(void *cache)
{
    struct cache_data *cdata = cache;
    free(cdata->cache), 
    free(cdata->fm);
    free(cdata);
}

// Removes item from current freq-list
inline void fix_node(LFUCache *item)
{
    LFUCache **prev = &item->prev, **next = &item->next;
    *prev ? (*prev)->next = *next : 0;
    *next ? (*next)->prev = *prev : 0;
} 

// Fixes current freq-list
inline void fix_chead_tail_lfreq(LFUCache *item, struct cache_data *cdata)
{
    struct freq_m *fm = &cdata->fm[item->freq];
    LFUCache **head = &fm->head, **tail = &fm->tail;
    item == *head ? *head = item->next : 0;
    item == *tail ? *tail = item->prev : 0;
    item->freq == cdata->lfreq_index && !fm->head ? cdata->lfreq_index++ : 0;
}

// Adds to front of next freq-list
inline void fix_nhead_tail(LFUCache *item, struct cache_data *cdata)
{                
    struct freq_m *fm = &cdata->fm[++item->freq];
    item->prev = NULL;                                      
    item->next = fm->head;                                    
    fm->head = fm->head ? fm->head->prev = item : (fm->tail = item);         
}

// Evicts least-used entry from least freq-list
inline void evict_lfreq_node(struct cache_data *cdata)                             
{   
    struct freq_m *fm = &cdata->fm[cdata->lfreq_index]; 
    LFUCache *lu = fm->tail;                         
    lu->prev ? lu->prev->next = NULL : 0;     
    lu->freq = 0;
    lu->valid = false;
    !(fm->tail = lu->prev) ? fm->head = NULL : 0;    
    lu->prev = lu->next = NULL;    
}

// Maintains cache
inline void refresh_cache(LFUCache *item, struct cache_data *cdata, bool new_entry)
{
    if (new_entry)
        if (cdata->size == cdata->capacity)
            evict_lfreq_node(cdata); // Evict least-used entry from least freq-list
        else
            cdata->size++;        
    else {
        fix_node(item); // Remove from current freq-list
        fix_chead_tail_lfreq(item, cdata); // Fix current freq-list
    }
    fix_nhead_tail(item, cdata); // Add to front of next freq-list  
    if (!cdata->lfreq_index || cdata->lfreq_index > item->freq)
        cdata->lfreq_index = item->freq; 
    item->valid = true;
}