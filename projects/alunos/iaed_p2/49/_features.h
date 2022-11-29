#ifndef FEATURES_H_
#define FEATURES_H_

#include "hashT.h"
#include "hash.h"

/* The maximum number of characters for designating a game or a team*/
#define MAXDESC 1024
/* The maximum number of char instructions data to be stored*/
#define MAXINST 3

/* Define command '__a__' */
void new_match(int nl, int id, hashM *hashMt, hash *hashT, link head);
/* Define command '__A__' */
void add_team(int nl, hash *hashtable);
/* Define command '__l__' */
void list_all_matches(int nl, hashM *hashMt);
/* Define command '__p__' */
void search_match(int nl, hashM *hashMt);
/* Define command '__P__' */
void search_team(int nl, hashM *hashMt, hash *hashT);
/* Define command '__r__' */
void delete_match(int nl, hashM *hashMt);
/* Define command '__s__' */
void change_score(int nl, hashM *hashMt);


/* Auxiliar function to compare two matches by id */
int compare_id(const void *match1, const void *match2);
/* Auxiliar function to look for match name position in hashtable */
int hash_position(hashM *hashtable, char *name);

#endif