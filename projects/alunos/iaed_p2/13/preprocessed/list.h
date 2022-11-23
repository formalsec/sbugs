#ifndef __LIST_H__
#define __LIST_H__
#include "games.h"

typedef struct list{
    struct list *prev, *next;
    item game; /* List only stores Games */
}*List; /* Internal representation of a list node */

void printList(int lineNumber);
void add(item game);
void cleanList();
void listRemove(char *str);
#endif
