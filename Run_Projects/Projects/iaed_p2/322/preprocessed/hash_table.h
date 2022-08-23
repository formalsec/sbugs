#ifndef hash_table_h_265
#define hash_table_h_265

#include "main.h"

/* Elements for the hashtable */
typedef struct bucket {
    char *key;
    Game *data;
    struct bucket *next;
} Bucket;

/* Hashtable */
typedef struct {
    Bucket **entries;
    int size;
} Hash_Array;

/* Return the hash of the key received */
unsigned int hash(char *key, int size);

/* Initialize and allocate memory for the hashtable */
Hash_Array* hashtable_init(int size);

/* Receives a key and value and returns a bucket ready to be put into the array */
Bucket* create_bucket(char *key, Game *value);

/* Creates a bucket with the given information, hashes the key and inserts in the 
respective slot */
void hashtable_insert(Hash_Array *hashtable, char *key, Game *value);

/* Return the value of a given key */
Game* hashtable_get(Hash_Array *hashtable, char *key);

/* Used to print all availables games */
void hashtable_print_all(Hash_Array *hashtable);

/* Print the hashtable - used for debugging*/
void hashtable_visualize(Hash_Array *hashtable);

/* Erase the whole hashtable */
void hashtable_free_all(Hash_Array *hashtable);

/* Receives a key and deletes the bucket associated with that key */
void hashtable_del(Hash_Array *hashtable, char *key);

/* Free the data inside the hashtable */
void free_data(Game *data);

/* Get a list of games with the most amount of wins */
void biggest_wins(int line_number, Hash_Array *hashtable);

/* Compare function for qsort */
int compare_str(const void *p1, const void *p2);



#endif
