#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdarg.h>

/**
 * @brief       : Structure for a pair of key and value 
 * @param key   : The key string of a pair
 * The key is unique in the HashTable
 * @param value : The value corresponding to a key
 * A value is not unique. It can correspond to several keys
 * @param next  : A pointer to the next node of the List
 */
typedef struct List
{
        char *key;
        char *value;
        struct List *next;
} List;

/**
 * @brief       : Structure to maintain hash-table
 * @param size  : The size of the array
 * @param array : An array of size @param size
 * Each cell of this array is a pointer to the first node of a linked list,
 * because we want our HashTable to use a Chaining collision handling
 */
typedef struct HashTable
{
        unsigned int size;
        List **array;
} HashTable;

/**
 * @param key   : The key to hash
 * @param size  : The size of the hashtable
 * @return      : An integer N like 0 <= N < @param size
 * This integer represents the index of @key in an array of size @size
 */
unsigned int hash(const char *key, unsigned int size);

HashTable *hashTableCreate(unsigned int);
int hashTablePut(HashTable *, const char *, const char *);
int addToTopOfList(List **, List *);
void nodeHandler(HashTable *, List *);
char *hashTableGet(HashTable *, const char *);
void hashTableFree(HashTable *);
void printStr(char *str);
int printChar(char c);
void printNum(int n);
