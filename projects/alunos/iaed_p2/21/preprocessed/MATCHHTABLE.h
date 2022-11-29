#ifndef MATCHHTABLE_H
#define MATCHHTABLE_H

#define MAX 199999

#include "TEAM.h"
#include "MATCH.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Uso de hash table para arquivar os jogos no sistema*/
typedef struct matchnode{
  Match match;
  struct matchnode* next;
}*matchNode;

matchNode* matchHeads;

/*linked list que contem todos os jogos pela ordem em que foram introduzidos*/
matchNode head, tail;

int hashM(char* v, int m);
void matchInit();
void matchInsert(Match item);
void matchDelete(Match item);
matchNode matchSearch(char* name);
void matchHashListFREE(matchNode m);
void matchHashFREE();
void MlistInit();
matchNode newMatchNode(Match match, matchNode next);
void addMatchNodeList(Match match);
void MfreeHead(matchNode node);

#endif
