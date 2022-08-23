#ifndef P2_HASHTABLE_H
#define P2_HASHTABLE_H
#include "item.h"
typedef struct node{
    Item item;
    struct node* next;
}Node;

Node* * heads;

/*prototipos*/
void init(int);
void insert(int, Item);
void delete(int,char*,int);
Item search(int,char*);

void deleteTudo(int);
void deleteHeads();
Item* HashToArray(int, int);
void chk_hashtable(int*,int);

#endif
