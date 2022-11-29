#ifndef _PROJ2_
#define _PROJ2_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxchar 1024

struct jogo {
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1,score2;
    struct jogo *next;
};
struct equipa {
    char *nome;
    struct equipa *next;
};
typedef struct jogo *linkjogo;
typedef struct equipa *linkequipa;

linkjogo a(linkjogo headjogo,linkequipa headequipa,int contlinha);
linkequipa A(linkequipa headequipa,int contlinha);
linkjogo s(linkjogo headjogo,int contlinha);
linkjogo r(linkjogo headjogo,int contlinha);
void P(linkjogo headjogo,linkequipa headequipa,int contlinha);
void p(linkjogo headjogo,int contlinha);
void l(linkjogo headjogo,int contlinha);
void g(linkjogo headjogo,linkequipa headequipa,int contlinha);

linkjogo NEWjogo(char *nome,char *equipa1,char *equipa2,int score1,int score2);
linkequipa NEWequipa(char *nome_equipa);
linkjogo insertEndJogo(linkjogo headjogo,char *nome,char *equipa1,
char *equipa2,int score1,int score2);
linkequipa insertEndEquipa(linkequipa headequipa,char *nome_equipa);
linkjogo removeJogo(linkjogo headjogo,char *nome_jogo);
linkequipa removeEquipa(linkequipa headequipa,char *nome_equipa);
void procuraEquipa(linkjogo headjogo,char *nome,int contlinha);
int compare(const void *p1,const void *p2);
void listaGanhos(linkjogo headjogo,linkequipa headequipa,int contlinha,
int max_g,int quant_g);


#endif