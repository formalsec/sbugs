#ifndef _JOGO_
#define _JOGO_
#include <stdlib.h>
#include <string.h>
#include "equipa.h"
#define MAX_TABELA 1049
#define ganhou(A,B) (A>B)
#define empate(A,B) (A == B)


/*Utilizacao de listas duplamente ligadas para preservar a ordem em que os jogos ocorreram, na qual 
cada elemento da lista aponta para a posicao de memoria de um jogo.
Utilizacao de uma tabela de dispersao com encadeamento externo(listas duplamente
ligadas) para guardar os jogos,onde cada no da tabela aponta para a posicao do jogo na lista de jogos 
alem de apontar para os seus nos anterior e seguinte. Esta tabela aproveita o hash utilizado na tabela das equipas
Um jogo e constituido pelo seu nome, os nomes das equipas
e o score final (um par de inteiros). Aqui encontram-se  os prototipos das
funcoes de implementacao*/

typedef struct{
    char *nome;  /*nome jogo*/
    char *equipa1,*equipa2; /*nomes das equipas*/
    int score1,score2;  /*scores*/

} jogo;


typedef struct no_jogo_tabela{
    struct no_jogo_tabela *proximo; /*proximo no*/
    struct no_jogo_tabela *anterior; /*no anterior*/
    struct ordem *pos_fila;  /*posicao na lista de jogos*/
    jogo jogo1;
} no_jogo_tabela;

typedef struct ordem{
    struct ordem *proximo;  /*proximo no*/
    struct ordem *anterior;  /*no anterior*/
    no_jogo_tabela *jogo_n;      /*posicao de memoria do jogo*/
} no_jogos;

typedef struct lista_jogos{
    no_jogos *inicio,*fim;
} lista_jogos;

/*jogos*/
no_jogo_tabela *cria_jogo(char nome[],char equipa1[],char equipa2[],int score1,int score2);
void adiciona_jogo(no_equipa *tabela_equipas[],lista_jogos **fila_jogos,
no_jogo_tabela *tabela_jogos[],char nome[],char equipa1[],char equipa2[],int score1,int score2);
no_jogo_tabela *procura_jogo_lista(no_jogo_tabela *tabela_jogos[],char nome[]);
void apaga_jogo(no_equipa *tabela_equipas[],lista_jogos **fila_jogos,
no_jogo_tabela *tabela_jogos[],char nome[]);
void lista_todos_jogos(lista_jogos *fila_jogos,int linha);
void altera_score(no_equipa *tabela_equipas[],
no_jogo_tabela *tabela_jogos[],char nome[],int score_novo1,int score_novo2);

#endif 

