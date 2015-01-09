/*
 * =====================================================================================
 *
 *       Filename:  hash.h
 *
 *    Description:  Hash Table Implementation
 *
 *        Version:  1.0
 *        Created:  11/02/2014 20:22:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Oriol Nieto (c), oriol@nyu.edu
 *        Company:  New York University
 *
 * =====================================================================================
 */

#ifndef __HASH_H__
#define __HASH_H__

#include <stdlib.h>

typedef struct hash_node {
    char *key;
    char *data;
    struct hash_node *next;
} hash_node;

typedef struct hash_table {
    int size; 
    hash_node **nodes;
} hash_table;

hash_table* hash_create( int size );
void hash_destroy( hash_table *ht );
int hash_insert( hash_table *ht, const char *key, const char *data );
char* hash_get( hash_table *ht, const char *key );
void hash_print( hash_table *ht );


#endif
