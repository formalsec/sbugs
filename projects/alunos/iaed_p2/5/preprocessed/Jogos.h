#ifndef JOGOS_H
#define JOGOS_H

/* Estrutura que define um jogo. */
typedef struct Jogo
{
    char *nome;
    char *equipa_1;
    char *equipa_2;
    int pontuacao_1;
    int pontuacao_2;
} Jogo;

Jogo *novoJogo(char nome[],char equipa_1[],char equipa_2[],int pontuacao_1,int pontuacao_2);

/* Estrutura que define um no para a hash table de jogos. */
typedef struct Node_jogo
{
    Jogo *jg;
    struct Node_jogo *next;
} Node_jogo;

/* Estrutura que define uma hash table composta pelo tamanho da hash table e por um ponteiro para um array de ponteiros. */
typedef struct Hash_jogo
{
    Node_jogo **table_jg;
    int size;   
} Hash_jogo;

struct Node_jogo *cabeca; /* Ponteiro para o inicio da lista de jogos. */

void HT_Jogos_Init(int m, Hash_jogo *hash_ptr);
int HT_Get_Jogo(Hash_jogo *hash, char *nome, Jogo **jogo_ptr);
void HT_Jogos_Insert(char nome_jogo[], char equipa_1[], char equipa_2[], int pontuacao_1, int pontuacao_2, Hash_jogo *hash_jg, Hash_equipa *hash_eq, int NL);
int HT_Jogo_Delete(Jogo *jogo_ptr, Hash_jogo *hash_jg);
Jogo *novoJogo(char nome[], char equipa_1[], char equipa_2[], int pontuacao_1, int pontuacao_2);
void printJogo(Hash_jogo *hash_jg, char nome[], int NL);
void insere(Jogo *jogo_ptr);
void imprimeLista(int NL);
struct Node_jogo *pesquisa(Jogo *jogo_ptr);
void remover(Jogo *jogo_ptr) ;
void remocao(Jogo *jogo_ptr);
void HT_Jogos_Delete(Hash_jogo *hash_jg);
void delete_Node_Jogo(Node_jogo *node_jg);
void deleteCabeca(Node_jogo **head_ref); 

#endif