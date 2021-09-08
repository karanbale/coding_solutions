/*
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
Follow up:
Could you do get and put in O(1) time complexity? 

Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
 

Constraints:

1 <= capacity <= 3000
0 <= key <= 3000
0 <= value <= 104
At most 3 * 104 calls will be made to get and put.
*/

#include "../standardHeaders.h"

#define SIZE 3300

typedef struct packagedData{
    int key;
    int value;
    struct packagedData *prev;
    struct packagedData *next;
}cacheData_t;

typedef struct {
    cacheData_t **cacheArr;
    cacheData_t *headPtr;
    cacheData_t *tailPtr;
    int capacity;
    int cacheCount;
} LRUCache;

LRUCache *lRUCacheCreate(int capacity) {
    if (capacity > SIZE)
        return NULL;
    LRUCache *cache = (LRUCache *)calloc(1, sizeof *cache);
    
    cache->cacheArr = (cacheData_t **) calloc(1, sizeof(cacheData_t *)*SIZE);
    assert(cache->cacheArr != NULL);
    
    cache->headPtr = (cacheData_t *) calloc(1, sizeof(cacheData_t));
    assert(cache->headPtr != NULL);

    cache->tailPtr = (cacheData_t *) calloc(1, sizeof(cacheData_t));
    assert(cache->tailPtr != NULL);


    cache->headPtr->key = -1;
    cache->headPtr->next = cache->tailPtr;
    cache->headPtr->prev = NULL;
    
    cache->tailPtr->key = -1;
    cache->tailPtr->next = NULL;
    cache->tailPtr->prev = cache->headPtr;

    cache->capacity = capacity;
    return cache;
}

static inline int getHashCode(LRUCache* obj, int key){
    return (key % SIZE);
}

static inline bool isCacheFull(LRUCache *obj){
    return obj->cacheCount >= obj->capacity;
}

static inline bool isCacheEmpty(LRUCache *obj){
    return obj->cacheCount == 0;
}

void lRUCacheFree(LRUCache* obj) {
    if(isCacheEmpty(obj)){
        return;
    }
    LRUCache *cache = obj;
    cacheData_t *head = cache->headPtr->next;
    cacheData_t *nextNode = head->next;
    while(nextNode != cache->tailPtr){
        free(head);
        head = nextNode;
        nextNode = nextNode->next;
    }
    free(cache->cacheArr);
    free(cache->headPtr);
    free(cache->tailPtr);
    free(cache);
}

static inline void removeNode(LRUCache *obj, cacheData_t *node){
    
    int keyHash = getHashCode(obj, node->key);
    obj->cacheArr[keyHash] = NULL;
    cacheData_t *prevNode = node->prev;
    prevNode->next = node->next;
    node->next->prev = prevNode;
    node->prev = NULL;
    node->next = NULL;
    obj->cacheCount--;
    free(node);
    
}

void evictLRUItem(LRUCache *obj){
    // ptr to tail node, NOT tailPtr, but actual node
    removeNode(obj, obj->tailPtr->prev);
}

cacheData_t *createNode(int key, int value){
    cacheData_t *node = calloc(1, sizeof(cacheData_t));
    assert(node != NULL);
    node->key = key, node->value = value;
    node->prev = node->next = NULL;
    return node;
}

static inline void moveToHead(LRUCache *obj, cacheData_t *node){
    cacheData_t *head = obj->headPtr;
    cacheData_t *headNext = head->next;
    // if head-> next has some data, squeeze our node in at the head
    head->next = node;
    node->prev = head;
    headNext->prev = node;
    node->next = headNext;
}

static inline cacheData_t *keyExists(LRUCache* obj, int key){
    int keyHash = getHashCode(obj, key);
    return obj->cacheArr[keyHash] ? obj->cacheArr[keyHash] : NULL;
}

int lRUCacheGet(LRUCache* obj, int key) {
    if(isCacheEmpty(obj)){
        // printf("EMPTY CACHE! RETURNING\n");
        return -1;
    }
    // check if data already exists ==> lookup function
    cacheData_t *tempNode = keyExists(obj, key);
    if(tempNode){
        cacheData_t *nodePrev = tempNode->prev;
        cacheData_t *nodeNext = tempNode->next;
        nodeNext->prev = nodePrev;
        nodePrev->next = nodeNext;
        tempNode->next = NULL;
        tempNode->prev = NULL;
        moveToHead(obj, tempNode);
        return tempNode->value;
    }
    else{
        return -1;
    }
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    // create data
    cacheData_t *node = createNode(key, value);

    int keyHash = getHashCode(obj, key);
    
    // check if cache is empty, if yes, just add it
    if(isCacheEmpty(obj)){
        obj->cacheArr[keyHash] = node;
        moveToHead(obj, node);
        obj->cacheCount++;
        return;
    }
    else{
        // check if data already exists ==> lookup function
        cacheData_t *tempNode = keyExists(obj, key);
        // ==> if exist, update its value, move to head to bump up priority
        if(tempNode){
            free(node);
            tempNode->value = value;
            lRUCacheGet(obj, key);
        }
        // check if cache is full
        // => if cache is full, evict LRU data from the tail
        else if(isCacheFull(obj)){
            evictLRUItem(obj);
            obj->cacheArr[keyHash] = node;
            moveToHead(obj, node);
            obj->cacheCount++;
        }
        // cache is not full and key does not exist in cache
        else{
            obj->cacheArr[keyHash] = node;
            moveToHead(obj, node);
            obj->cacheCount++;
            return;
        }
    }
}


/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/

/*
Sample inputs to use:
["LRUCache","put","get"]
[[1],[2,1],[2]]
["LRUCache","put","put","get","put","put","get"]
[[2],[2,1],[2,2],[2],[1,1],[4,1],[2]]
["LRUCache","put","get"]
[[1],[2,1],[2]]
["LRUCache","put","put","get","put","get","put","get","get","get"]
[[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]
["LRUCache","put","put","put","put","get","get"]
[[2],[2,1],[1,1],[2,3],[4,1],[1],[2]]
*/

/*
obj->cacheArr[keyHash]->key
obj->headPtr->next->key
obj->tailPtr->prev->key
*/
