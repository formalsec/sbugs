#ifndef _JOGOS_
#define _JOGOS_

#include "equipas.h"


/* Estrutura que armazena todos os dados relevantes a cada jogo */
typedef struct  
{ 
    char *nome_jogo;
    link_equipa *pequipa1, *pequipa2;
    int pontos1, pontos2; 
} jogo;


/* Estrutura que serve de ponte entre jogos, tendo cada uma um jogo associado */
typedef struct Link_Jogo
{
    jogo *pointer_jogo;

    struct Link_Jogo *jogo_anterior_lista, 
    *jogo_next_lista, *jogo_next_hashtable;

} link_jogo;


/* Estrutura que define o inicio de cada lista da hashtable */
typedef struct
{
    link_jogo *next;
} link_hashtable_jogos;


/* Hashtable com um tamanho maximo e um vetor de "cabecas" correspondentes as suas hashes */
typedef struct
{
    int tamanho_maximo;
    link_hashtable_jogos *vetor_hashes;
} hashtable_jogos;


/* Estrutura que define uma lista de jogos, com ponteiros para o primeiro e ultimo elemento */
typedef struct 
{
    link_jogo *head, *tail;
}lista_ord_jogos;


/* Funcoes para as diversas manipulacoes dos jogos */ 

hashtable_jogos* inicializa_jogos(int tamanho_maximo); 
lista_ord_jogos* inicializa_jogos_lista(); 

void inserir_jogo(char* nome_jogo, link_equipa *equipa1,link_equipa *equipa2,
int score1, int score2, hashtable_jogos *tabela_jogos, lista_ord_jogos *lista_jogos);

void listar_todos_jogos(int linha_input, lista_ord_jogos *lista_jogos);
link_jogo* procurar_jogo(char *nome_jogo, hashtable_jogos *tabela_jogos);
void apagar_jogo(char* nome_jogo, hashtable_jogos *tabela_jogos, lista_ord_jogos *lista_jogos);
void alterar_jogo(link_jogo *jogo, int score1, int score2);
void destruir_jogos(hashtable_jogos *tabela_jogos);
void destruir_lista(lista_ord_jogos *lista_jogos);

#endif