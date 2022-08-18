#ifndef _EQUIPA_
#define _EQUIPA_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define MAX_TABELA 1049
#define RETIRA 2
#define ADICIONA 3

/*Utilizacao de uma tabela de dispersao com encadeamento externo(listas ligadas) para
organizacao das equipas. A dispersao e calculada atraves de uma soma ponderada das letras
do nome. Cada equipa e representada pelo seu numero de vitorias e pelo seu nome.
Aqui encontram-se os prototipos das funcoes de implementacao*/

typedef struct equipa{
    char *nome;   /*guarda o nome*/
    int vitorias; /*guarda as vitorias da equipa*/
} equipa;

typedef struct no_equipa{
    struct no_equipa *proximo; /*proximo no*/
    equipa equipa_do_no;     /*equipa*/
} no_equipa;


int hash(char nome[]);
no_equipa *cria_equipa(char nome[]);
void adiciona_equipa(no_equipa *tabela_equipas[],char nome[],int *numero_equipas);
equipa *procura_equipa_lista(no_equipa *tabela_equipas[],char nome[]);
void altera_vitoria_equipa(no_equipa *tabela_equipas[],char nome[],int chave);
void retira_vitoria_equipa(char nome[]);
void lista_mais_vitorias(no_equipa *tabela_equipas[],int linha, int numero_equipas);


#endif

