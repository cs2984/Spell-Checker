/****************************************************************************
 * dictionary.h
 *
 * MPATE-GE 2618
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/
#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <stdbool.h>

#define HASH_TABLE_SIZE 65536

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
extern const int MAX_WORD_LEN;


/* Structs for Hash Table */

typedef struct hash_node {
    char  *word;
    struct hash_node *next;
} hash_node;

typedef struct hash_table {
    int numwords; 
    hash_node **nodes;
} hash_table;

int hash_func(char* word);
hash_table* hash_create();
bool hash_insert(char *word);
void hash_print();



/* Returns true if word is in dictionary else false */
bool check(char *word);

/* Loads dictionary into memory.  Returns true if successful else false. */
bool load(char *dict);

/* Returns number of words in dictionary if loaded else 0 if not yet loaded. */
int size();

/* Deletes dynamically allocated memory */
void cleanUp();

#endif // _DICTIONARY_H_
