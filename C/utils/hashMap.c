#include "hashMap.h"

/*
 * hash() - Find the index of the key passed, or if it does not exist, return
 * an empty array index.
 * @key: The key to find in the hash table.
 * @size: The size of the hash table.
 *
 * Return: The index of the item.
 */
unsigned int hash(const char *key, unsigned int size)
{
        unsigned int hash;
        unsigned int i;

        hash = 0;
        i = 0;
        while (key && key[i]) {
                hash = (hash + key[i]) % size;
                ++i;
        }
        return (hash);
}

/*
 * main() - Create a hash table of size 1, put keyed item in the hashtable,
 * call printf to print the value of the key. Free the hash before returning.
 *
 * Return: 0 upon success, 1 upon failure.
 */
int main(void) {
        HashTable *ht;

        ht = ht_create(1);
        if (ht == NULL) {
                return 1;
        }

        if (ht_put(ht, "isFun", "C") == 0) {
                printf("%s\n", ht_get(ht, "isFun"));
                ht_free(ht);
                return 0;
        }

        return 1;
}

