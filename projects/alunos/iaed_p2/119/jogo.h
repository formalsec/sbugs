#ifndef _JOGO_
#define _JOGO_

typedef struct
/* Estrutura para jogos*/
{
  char *name;
  char *equipa1;
  char *equipa2;
  int score1;
  int score2;
} Jogo;

typedef struct n_j
/* Estrutura para nodulos de jogos*/
{
  Jogo j;
  struct n_j * next;
}node_j, * link_j;

typedef struct
/* Estrutura para hashtable de jogos*/
{
  link_j * L;
  int M;
} ht_j, *HT_J;

link_j createJogo(const char *name, const char *e1, const char *e2, int s1, int s2 ,link_j next);
void freeJogo(link_j x);
void pushJogo(link_j *head, const char *name, const char *e1, const char *e2, int s1, int s2);
void popJogo(link_j *head, const char *name);
HT_J initJogo(int m);
void insertJogo(HT_J Jogos, const char *name, const char *e1, const char *e2, int s1, int s2);
void removeJogo(HT_J Jogos, const char * name);
Jogo *searchJogo(HT_J Jogos, const char * name);

#endif