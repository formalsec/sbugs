#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 131072
#define FNV_32BIT_PRIME 16777619UL
#define FNV_32BIT_BASIS 2166136261UL

typedef unsigned long ulong;

/* NOTE: info_struct has to be previously
   freed before freeing with ht_delete_node */
typedef struct ht_node
{
    void *info_struct;
    struct ht_node *next;
} ht_node;

/* pointer to function that frees infostruct*/
typedef void (*free_info_struct)(void*);

typedef struct hash_table
{
    ht_node *bucket[TABLE_SIZE];

} hash_table;

hash_table* create_ht();
ht_node* create_ht_node();
void ht_insert_node(hash_table *ht,ht_node *ht_node,ulong key);
void ht_delete_node(hash_table *ht,ht_node *ht_node,ulong key);
void ht_delete_ht(hash_table *ht);
void ht_delete_node_and_info(hash_table *ht,ht_node *ht_node,ulong key,free_info_struct func);
void ht_delete_ht_and_info(hash_table *ht,free_info_struct func);
ht_node* ht_get_base_node(hash_table *ht,ulong key);
ulong ht_key_from_str(char *str);
ulong fnv_1a(char *str);

#endif
