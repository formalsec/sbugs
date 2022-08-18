#ifndef MATCH_LINKEDLIST_H
#define MATCH_LINKEDLIST_H

#include "Structs.h"
#include "LinkedHashStructs.h"

LinkedList_Match* mk_Match_LinkedList();
void addToMatchLinkedList(LinkedList_Match *llM, Hash_Node_Match *hNM);
void freeMatchLinkedList(LinkedList_Match *llM);

#endif