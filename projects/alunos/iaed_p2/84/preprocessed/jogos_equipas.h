#ifndef __JogoEquipas__
#define __JogoEquipas__


/*
  -Valor de retorno das funcoes removeEq/removeJo e searchEq/removeJo 
  quando nao encontram o jogo/equipa pedido;
  -Retorno da funcao vencedor em caso de empate;
  -Identifica um empate na funcao atualiza_vencedores.
*/
#define NOT_FOUND -1
/*Valor devolvido pela funcao removeEq/removeJo quando a remocao da equipa/jogo e bem sucedida.*/
#define REMOVED 0
/*Valor devolvido pela funcao vencedor se o vencedor for a equipa 1.*/
#define EQUI1 1
/*Valor devolvido pela funcao vencedor se o vencedor for a equipa 2.*/
#define EQUI2 2

/*
Estrutura 'equipa':
    -nome: nome da equipa;
    -vit: numero de vitorias da equipa;
*/
typedef struct{
    char* nome;
    int vit;
}equipa;
/*
Estrutura 'pEquipa':
    Ponteiro para um uma estrutura do tipo equipa.
*/
typedef equipa* pEquipa;

/*
Estrutura 'jogo':
    -nome: nome do jogo;
    -e1: ponteiro para a equipa 1 do jogo;
    -e2: ponteiro para a equipa 2 do jogo;
    -sc1: pontuacao da equipa 1;
    -sc2: pontuacao da equipa 1;
    -next: ponteiro para o proximo jogo por ordem de introducao;
    -previous: ponteiro para o jogo antes por ordem de introducao;
*/
struct jogo{
    char* nome;
    pEquipa e1, e2;
    int sc1, sc2;
    struct jogo *next, *previous;
};
typedef struct jogo jogo;

/*
Estrutura 'pJogo':
    Ponteiro para um uma estrutura do tipo jogo.
*/
typedef jogo* pJogo;



pEquipa cria_equipa(char str[1024]);
pEquipa* cria_tabela_equi();
void insert_Eq(pEquipa eq);
long search_Eq(char* nome);
void freeTabEq();

pJogo cria_jogo(char nome[1024], pEquipa e1, pEquipa e2, int sc1, int sc2);
pJogo* cria_tabela_jogo();
void insert_Jo(pJogo jogo);
long search_Jo(char* nome);
int remove_Jo(char* nome);
int vencedor(int sc1, int sc2);
void atualiza_vencedores(int ant_venc, int novo_venc, pEquipa e1, pEquipa e2);
void mergesort(pEquipa *vetor, int e, int d);
void freeTabJo();

extern long tabEq_size, tabEq_ocup;
extern pEquipa* tabela_Equi;
extern long tabJo_size, tabJo_ocup;
extern pJogo* tabela_Jo;
extern pJogo head, tail;

#endif