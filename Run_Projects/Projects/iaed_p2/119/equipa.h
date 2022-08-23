#ifndef _EQUIPA_
#define _EQUIPA_

typedef struct equipa
/* Estrutura para equipas*/
{
  char *name;
  int wins;
} Equipa;

typedef struct n_e
/* Estrutura para nodulos com estrutura de equipa*/
{
  Equipa e;
  struct n_e * next;
}node_e, * link_e;

typedef struct
/* estrutura para hashtable com estrutura de equipa*/
{
  link_e * L;
  int M;
} ht_e, *HT_E;



link_e createEquipa(const char *name, link_e next);
void freeEquipa(link_e x);
void pushEquipa(link_e *head, const char *name);
void popEquipa(link_e *head, const char *name);
HT_E initEquipa(int m);
void insertEquipa(HT_E Equipas, const char *name);
void removeEquipa(HT_E Equipas, const char * name);
Equipa *searchEquipa(HT_E Equipas, const char * name);
void incWin(HT_E Equipas, const char *name, int direction);


#endif
