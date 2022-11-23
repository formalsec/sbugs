#ifndef _STRLIST_
#define _STRLIST_

typedef struct n
/* estrutura para nodulo com string */
{
  char * str;
  struct n *next;
} node, *link;

link newNode(const char *str, link next);
void freeStr(link x);
void append(link *L, const char *str);
void removeStr(link *L, const char *str);
void insertSorted(link *L, const char *equipa);
void freeList(link *L);
void printList(link *L);

#endif