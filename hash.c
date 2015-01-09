/*
 * =====================================================================================
 *
 *       Filename:  hash.c
 *
 *    Description:  Hash Table Implementation
 *
 *        Version:  1.0
 *        Created:  11/02/2014 20:26:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Oriol Nieto, oriol@nyu.edu
 *     University:  New York University
 *      Copyright:  Copyright (c) 2014, Oriol Nieto 
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"

int hash_func( const char *key );

/* 
 *  Description:  Hash function (private): Given a key, returns the index to its data
 */
int hash_func( const char *key ) {
    int i, hash = 0;
    for ( i = 0; i < strlen(key); i++ ) {
        hash += key[i];
    }
    return hash;
}

/* 
 *  Description:  Creates the hash table
 */
hash_table* hash_create( int size ) {
    // TODO
    
    /* Initialize the table */
    hash_table *ptable = (hash_table *) malloc (sizeof(hash_table));


    /* Make sure there is enough memory available */
    if (ptable == NULL){
        printf("Not enough memory availabe"); 
        exit (1);
    }
    
    /* Initialize the nodes in the double pointer */
    ptable->nodes = (hash_node**) malloc (sizeof(hash_node*) * size);
    
    /* Check to see if there is enough memory */
    if (!ptable-> nodes){
        printf ("Not enough memory available");
        exit(1);
    }

    /* Initialize the size of the table */
    ptable->size = size; 


    /* Set all the pointers to NULL */

    for (int i = 0; i < ptable->size, i++){
        ptable->nodes[i] = NULL; 

    }
    return ptable; 
}


/* 
 *  Description:  Destroys the hash table
 */
void hash_destroy( hash_table *ht ) {
    // TODO

    /* Make sure that table is not null */
    if (ht == NULL) {
        return;
    }

    /* Initialize the table */
    hash_node *curr;
    hash_node *tmp;

    /* for each position check to see that its not null */
    for (int i = 0; i < ht->size; i++){
        curr = ht->nodes [i];

        /* While its not null move the curr over while tmp is pointing to free the memory */
        while (curr != NULL){
            tmp = curr->next;
            free(curr);
            curr = tmp;
        }

    }
    /* Free the double pointer and then the table */
    free (ht->nodes);
    free(ht);
}


/* 
 *  Description:  Inserts a new data entry to the table
 */
int hash_insert( hash_table *ht, const char *key, const char *data ) {
    // TODO
    
    int index;
    index = hash_func(key) % ht->size;

    /* Create node for curr that is going through the index */
    hash_node *curr = ht->nodes[index];

    /* Allocate memory for the data nodes within the hash_node */
    if (!curr) {
        curr = (hash_node*) malloc(sizeof(hash_node);
        curr->key = (char) malloc(sizeof(char) * (strlen(key)+1));
        curr->data= (char) malloc(sizeof(char) * (strlen(data)+1));

        strcpy(curr->key, key); 
        strcpy(cur->data, data);
        curr->next = NULl; 

    }

    /* if curr is not empty */
    else {

        /* Create Temporary Pointer */

        hash_node *tmp = NULL;

        /* go element by element until you find NULL */
        while (curr != NULL){

            /* If the key is the same then we overwrite the data */
            if (strcmp (curr->key, key) == 0) {
                free(curr->data);
                curr->data = (char) malloc(sizeof(char) * (strlen(data) + 1));
                strcpy(curr->data, data);
                return 0

            }
            curr= curr->next;
        }

        /* If we get here we are going to be inserting at the beginning of the list */
        curr = (hash_node*) malloc(sizeof(hash_node);
        curr->key = (char) malloc(sizeof(char) * (strlen(key)+1));
        curr->data= (char) malloc(sizeof(char) * (strlen(data)+1));

        strcpy(curr->key, key); 
        strcpy(cur->data, data);

        /* Insert it into the beginning of the list */
        curr->next = ht->nodes[index]; 
        ht-nodes[index] = curr;
    }
}


/* 
 *  Description:  Gets the data corresponding to a given key (NULL if not found)
 */
char* hash_get( hash_table *ht, const char *key ) {
    // TODO
    int hash;
    hash_node *curr;
    char *data = NULL;

    hash = hash_func( key ) % ht->size;
    curr = ht->nodes[hash];

    while( curr != NULL ) {
        if ( strcmp( curr->key, key ) == 0 ) {
            data = curr->data;
            break;
        }
        curr = curr->next;
    }

    return data;
}


/* 
 *  Description:  Print the hash table
 */
void hash_print( hash_table *ht ) {
    // TODO
}
