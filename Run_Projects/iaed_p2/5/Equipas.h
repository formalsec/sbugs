#ifndef EQUIPAS_H
#define EQUIPAS_H

/* Estrutura que define uma equipa. */
typedef struct Equipa
{
    char *nome;
    int vitorias;
} Equipa;

Equipa *novaEquipa(char nome[]);

/* Estrutura que define um no para a hash table de equipas. */
typedef struct Node_equipa
{
    Equipa *eq;
    struct Node_equipa *next;
} Node_equipa;

/* Estrutura que define uma hash table composta pelo tamanho da hash table e por um ponteiro para um array de ponteiros. */
typedef struct Hash_equipa
{
    Node_equipa **table_eq;
    int size;
} Hash_equipa;

/* Estrutura utilizada para definir equipas com maior pontuacao. */
typedef struct Node_equipa_max
{
    char *nome;
    int tamanho;
    int max;
    struct Node_equipa_max *next;
} Node_equipa_max;

void HT_Equipas_Init(int m, Hash_equipa *hash_ptr);
int HT_Get_Equipa(Hash_equipa *hash, char *nome, Equipa **equipa_ptr);
void HT_Equipas_Insert(char nome[], Hash_equipa *hash, int NL);
Equipa *novaEquipa(char nome[]);
void printEquipa(Hash_equipa *hash_eq, char nome[], int NL);
void deleteList(Node_equipa_max **head_ref) ;
void HT_Equipas_Delete(Hash_equipa *hash_eq);
void delete_Node_Equipa(Node_equipa *node_eq);
void seleciona_equipas(Hash_equipa *hash_eq, int NL);

#endif