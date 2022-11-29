#ifndef _JOGO_
#define _JOGO_
#define hashM 631

typedef struct {
    /*Estrutura com dados de um jogo*/
    char *nome, *equipa1, *equipa2;
    int *score1, *score2;

} Jogo; 

typedef struct Jogo_Node{
    /*Estrutura de nodes de jogos
    (organizado mutuamente em lista e tabela de dispersao sem repeticao)*/
    Jogo *jogo;
    struct Jogo_Node *nextHash, *nextList;

}*linkJogo; 

/*Funcoes necessarias para manipulacao de jogos
  (descritas no ficheiro "jogo.c")*/
int hash(char *v, int M);

linkJogo ProcuraJHash(linkJogo *tab, char *v);
linkJogo NovoJogo(char* nome, char* equipa1, char* equipa2, int score1, int score2);

void InserirJogo(linkJogo *pheadj,linkJogo *ptailj, linkJogo *tabJogos, linkJogo j);
void RemoverJogo(linkJogo *pheadj, linkJogo *ptailj, linkJogo *tabJogos, linkJogo j);
void freeJogo(Jogo *j);
void freeLinkJogo(linkJogo j);

#endif
