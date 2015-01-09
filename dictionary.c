/****************************************************************************
 * dictionary.c
 *
 * MPATE-GE 2618
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "dictionary.h"

/*Global pointer to hash table*/
hash_table* htable;

/* Returns true if word is in dictionary else false. */
bool check(char *word)
{
    /* Initialize variables */
    int i; 
    int hash_tmp;
    hash_node *curr;
    char tmp[MAX_WORD_LEN + 1]; 

    /* Make sure that the word that is inputted is lower case and put it into a tmp variable */
    for (i = 0; i < strlen(word); i++){
        tmp[i] = tolower(word[i]);
    }

    /* Add a null terminating character */
    tmp[strlen(word)] = '\0';

    /*  Create a key for the tmp by putting it in the hash function*/
    hash_tmp = hash_func(tmp);
    /* set the new hashed tmp to a curr node */
    curr = htable->nodes[hash_tmp];

    /* While the node is not null see if the new node is equal to the tmp */
    while (curr != NULL){
        if ( strcmp (tmp, curr->word) == 0) {
            return true;
        }
        /* increment up */
        curr = curr->next;
    }
    return false;
}


/* Loads dict into memory.  Returns true if successful else false. */
bool load(char *dict)
{
    /* initialize variables  */
    char word [MAX_WORD_LEN +1];
    bool insertWord; 

    /* initialize hash table */

    htable = hash_create();

    /* Open dictionary file */
    FILE *dictfp;
    dictfp = fopen(dict, "r");
    /* Check to see if it exists */
    if (dictfp == NULL){
        printf ("Not a correct filename");
        return false;
    }

    /* Read in words from dictionary */
    while (fscanf(dictfp, "%s", word) != EOF){
        /* check to see if the end of string */
        insertWord = hash_insert(word);
        /* if not able to insert the word */
        if(!insertWord){
            return false;
        }
        htable->numwords++;
    }

    fclose(dictfp);
    return true;
}


/* Returns number of words in dictionary if loaded else 0 if not yet loaded. */
int size()
{

    if (htable != NULL) {
        return htable->numwords;
    }
    else {
        return 0;
    }
}

/* Delete all dynamically allocated memory if necessary */
void cleanUp()
{
    /* If there is nothing in htable then return */
    if (!htable) {
        return;
    }

    /* Initialize Variables */
    int i;
    hash_node *curr, *tp;
    /* iterate through the hashtable and put the nodes into a curr variable and free them */
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        curr = htable->nodes[i];
        while (curr != NULL) {
            tp = curr->next;
            free(curr);
            curr = tp;
        }
    }
    /* Free the pointer to nodes */
    free(htable->nodes);
    /* Free the table */
    free(htable);
}


/* Hash Function */
int hash_func(char* word)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(word); i<n; i++)
        hash = (hash << 2) ^ word[i];
    return hash % HASH_TABLE_SIZE;
}

/* Create the Hash Node */
hash_node* create_hash_node( const char *word) {
    hash_node* curr = (hash_node*)malloc(sizeof(hash_node));
    curr->word = (char*)malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(curr->word, word);
    return curr;
}


/* Create Hash Table */

hash_table* hash_create() {

    /* Allocate memory to the table */
    hash_table *ptable = (hash_table*)malloc(sizeof(hash_table));
    if (!ptable) {
        printf("Not enough memory!\n");
        exit(1);
    }

    // Allocate memory for the actual nodes of the table
    ptable->nodes = (hash_node**)malloc(sizeof(hash_node*) * HASH_TABLE_SIZE);
    if (!ptable->nodes) {
        printf("Not enough memory!\n");
        exit(1);
    }


    // Initialize the nodes
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ptable->nodes[i] = NULL;
    }

    return ptable;
}

/* 
 *  Description:  Inserts a new data entry to the table
 */
bool hash_insert(char *word) {

    /* Perform hash funtion on a word and store integer in Index */
    int index = hash_func(word);


    /* Use index value to create a curr node */
    hash_node *curr = htable->nodes[index];
    /* If a node didnt exist then create it */
    if (!curr) {
        // Create new node if list is empty
        htable->nodes[index] = create_hash_node(word);
        htable->nodes[index]->next = NULL;

    }
    else {
        while (curr != NULL) {
            // If key is already in list, simply update the data of this list
            if (strcmp(curr->word, word) == 0) {
                return true;
            }
            curr = curr->next;
        }
        // Create new node
        curr = create_hash_node(word);

        if (curr == NULL){
            return false;
        }

        // Insert it into the beginning of the list
        curr->next = htable->nodes[index];
        htable->nodes[index] = curr;

    }
    return true;
}

void hash_print() {

    int i;
    hash_node *curr;

    printf("------- Printing Hash Table ------ \n");
    for ( i = 0; i < HASH_TABLE_SIZE; i++ ) {
        curr = htable->nodes[i];
        while ( curr != NULL ) {
            printf( "Key: %s\n ",  curr->word);
            curr = curr->next;
        }
    }
    printf("------- End of table --------\n");
}
