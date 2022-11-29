#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "OOP.h"
#include "game.h"

/* These are elements of the ht type described below */
typedef struct stru_node {
  void *data;
  struct stru_node *prev, *next, *ht_next;
} node;

typedef struct {
  destructor free_data; /* a destructor for the type of data in the hash tale,
                           not for the node but for the content in the node*/
  key_getter get_data_key;
  int size;                  /* how many rows in the hash table */
  node **row_heads;          /* array of pointer to nodes which are heads */
  node *dll_head, *dll_tail; /* to keep the order of insertion */
} ht;

/* creates a node with inicialized pointers to NULL */
node *create_node(void *data);

/* destructor for node, deallocates all its memory, it needs to know the data
 * type of that element, and that is given by the ht struct */
void free_node(ht *, node *);

/* creates a hash table for a certain data type*/
ht *create_ht(int size, destructor destroy_data, key_getter get_key_data);

/* deallocates all the memory for a hash table. Frees all the nodes */
void free_ht(ht *h);

/* returns a hash (int) between 0 and M-1 based on the string key */
int hash(char *key, int M);

/* returns a pointer to data if it has the same key as argument.
 * returns NULL pointer if none is found. */
void *find_in_ht(ht *, char *key);

/* Adds any data type to ht. Does not check for repeated elements in ht */
void add_to_ht(ht *, void *data);

/* remove an element of a hash table by key and deallocates it's memory */
void remove_in_ht(ht *, char *key);

/* applies do_something to all elements (data atribute) of the hash table by
 * insertion order. This is somewhat similar to functional programming
 * languages' map combinator. This implementation is useful for printing
 * all the elements in the hash table */
void apply_all_in_ht(ht *, void (*do_something)(void *));

#endif
