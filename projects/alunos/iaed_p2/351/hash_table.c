#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include "hash_table.h"

/*  creates a new hash_table and returns a pointer to it*/
hash_table* create_ht()
{
    /* can_fail_calloc sets every pointer to zero-NULL */
    hash_table* ptr = can_fail_calloc(1,sizeof(hash_table));
    return ptr;
}

/*  creates a new ht_node and returns a pointer to it*/
ht_node* create_ht_node()
{
    ht_node *ptr = can_fail_calloc(1,sizeof(ht_node));
    return ptr;
}

/*  inserts a node in the place indicated by the key*/
void ht_insert_node(hash_table *ht,ht_node *node,ulong key)
{
    ht_node *next_node;
    next_node = ht->bucket[key];
    ht->bucket[key] = node;
    node->next = next_node;

}

/*  deletes a given node stored in the hash_table   */
void ht_delete_node(hash_table *ht,ht_node *node,ulong key)
{
    ht_node *curr,*prev = NULL;
    for(curr = ht->bucket[key];curr != NULL;prev = curr, curr=curr->next)
    {
        /* if curr is node, process deletion of it*/
        if(curr->info_struct == node->info_struct && curr->next == node->next)
        {
            /* if there is a previous node, update its next ptr*/
            if(prev != NULL)
            {
                prev->next = curr->next;
            }
            else
            {
                ht->bucket[key] = curr->next;
            }
            free(curr);
            return;
        }
    }
    return;
}
/*  deletes a given node stored in the hash_table and also its info   */
void ht_delete_node_and_info(hash_table *ht,ht_node *node,ulong key,free_info_struct func)
{
    ht_node *curr,*prev = NULL;
    for(curr = ht->bucket[key];curr != NULL;prev = curr, curr=curr->next)
    {
        /* if curr points to node, process deletion of it*/
        if(curr->info_struct == node->info_struct && curr->next == node->next)
        {
            /* if there is a previous node, update its next ptr*/
            if(prev != NULL)
            {
                prev->next = curr->next;
            }
            else
            {
                ht->bucket[key] = curr->next;
            }
            func(curr->info_struct);
            free(curr);
            return;
        }
    }
    return;
}

/* deletes every node of the hash table, and the hash_table itself*/
void ht_delete_ht(hash_table *ht)
{
    int i;
    for(i = 0;i < TABLE_SIZE; i++)
    {
        while(ht->bucket[i] != NULL)
        {

            ht_delete_node(ht,ht->bucket[i],i);
        }
    }
    free(ht);
    return;
}

/* deletes every node and its info in the hash table, and the hash_table itself*/
void ht_delete_ht_and_info(hash_table *ht,free_info_struct func)
{
    int i;
    for(i = 0;i < TABLE_SIZE; i++)
    {
        while(ht->bucket[i] != NULL)
        {

            ht_delete_node_and_info(ht,ht->bucket[i],i,func);
        }
    }
    free(ht);
    return;
}

/* returns base node of the hash_table for a given key*/
ht_node* ht_get_base_node(hash_table *ht,ulong key)
{
    return ht->bucket[key];
}

/* returns the key in the hash_table for
 a given string, if numbers are ne */
ulong ht_key_from_str(char *str)
{
    ulong key = fnv_1a(str);
    key = key % TABLE_SIZE;
    return key;
}


/*FNV-1a hash function implementation*/

/* returns a 64 bit hash for a given set of chars */
ulong fnv_1a(char *str)
{
    ulong hash = FNV_32BIT_BASIS;
    ulong prime = FNV_32BIT_PRIME;
    for(;*str != '\0';str++)
    {
        hash = hash ^ *str;
        hash = hash * prime;
    }
    return hash;
}




