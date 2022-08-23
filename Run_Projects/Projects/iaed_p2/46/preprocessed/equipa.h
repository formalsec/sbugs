#ifndef _EQUIPA_
#define _EQUIPA_
#define hashM 631

typedef struct {
    /*Estrutura com dados de uma equipa*/
    char *nome;
    int *vit;

} Equipa; 

typedef struct Equipa_Node{
    /*Estrutura de nodes de equipas
    (organizado mutuamente em lista e tabela de dispersao sem repeticao)*/
    Equipa *equipa;
    struct Equipa_Node *nextHash, *nextList, *prevList;

}*linkEquipa; 

/*Funcoes necessarias para manipulacao de equipas
  (descritas no ficheiro "equipa.c")*/

int hash(char *v, int M);
linkEquipa ProcuraEHash(linkEquipa *tab, char *v);
linkEquipa NovaEquipa(char* nome);

void InserirEquipa(linkEquipa *pheade,linkEquipa *ptaile, linkEquipa *tabEquipas, linkEquipa e);
void ReposCima(linkEquipa *pheade,linkEquipa *ptaile, linkEquipa e);
void ReposBaixo(linkEquipa *pheade,linkEquipa *ptaile, linkEquipa e);
void freeEquipa(Equipa *e);
void freeLinkEquipa(linkEquipa e);
#endif
