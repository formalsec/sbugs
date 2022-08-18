#ifndef proj2_h
#define proj2_h
#include "proj2_h_j.h"


extern int M;				/*Numero primo para a hashtable*/
/*Prototipos*/
int hash_s(char *v, int M);
int get_higher_score(list_e *ls_e, list_e *ls_v);
int cstring_cmp(const void *a, const void *b);

#endif
