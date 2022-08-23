#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Equipas.h"
#include "proj2.h"

/* Implementacao das funcoes referentes as equipas. */

/* Cria uma nova equipa. */
Equipa *novaEquipa(char nome[])
{
    Equipa *e = (Equipa *)malloc(sizeof(Equipa));
    e->nome = strdup(nome);
    e->vitorias = 0;
    return e;
}

/* Imprime uma equipa com base no nome. */
void printEquipa(Hash_equipa *hash_eq, char nome[], int NL)
{
    Equipa *equipa = NULL; 
    if(HT_Get_Equipa(hash_eq, nome, &equipa) == 0)
    {
        printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
        printf("%d %s %d\n", NL, equipa->nome, equipa->vitorias);
    }
}

/* Funcao que elimina a lista de equipas. */
void deleteList(struct Node_equipa_max **head_ref) 
{ 
   struct Node_equipa_max* current = *head_ref; 
   struct Node_equipa_max* next; 
   while (current != NULL)  
   { 
       next = current->next; 
       free(current); 
       current = next; 
   } 
   *head_ref = NULL; 
} 

/* Funcao utilizada para comparacao no qsort. */
int cmp(const void* a, const void* b) 
{ 
    return strcmp(*(const char**)a, *(const char**)b); 
} 

/* Funcao que inicializa a hash table de equipas. */
void HT_Equipas_Init(int m, Hash_equipa *hash_ptr)
{
    int i;
    hash_ptr->size = m;
    hash_ptr->table_eq = (Node_equipa **)malloc(m * sizeof(Node_equipa *)); /* Criacao de um array de m ponteiros para node*/
    for (i = 0; i < m; i++)
        hash_ptr->table_eq[i] = NULL;
}

/* Funcao que obtem equipa por nome. */
int HT_Get_Equipa(Hash_equipa *hash, char *nome, Equipa **equipa_ptr)
{
    int hash_value;
    Node_equipa *curr_node;
    hash_value = calc_hash(nome, hash->size);
    if(hash->table_eq[hash_value] == NULL)
    {
          return 0;
    }
    curr_node = hash->table_eq[hash_value];
    while(curr_node != NULL)
    {
        if (strcmp(curr_node->eq->nome, nome) == 0){
            if(equipa_ptr)
                (*equipa_ptr) = curr_node->eq;
            return 1;     
        }
        curr_node = curr_node->next;
    }
    return 0;
}

/* Funcao que liberta o espaco alocado por uma equipa e um node de equipa. */
void delete_Node_Equipa(Node_equipa *node_eq)
{
    free(node_eq->eq->nome);
    free(node_eq->eq);
    free(node_eq);
}

/* Funcao que liberta o espaco alocado pela hash table de equipas. */
void HT_Equipas_Delete(Hash_equipa *hash_eq)
{
    int i;
    Node_equipa *current;
    Node_equipa *next;
    for (i = 0; i < hash_eq->size ; i++)
    {
        current = hash_eq->table_eq[i];
        while (current != NULL)
        {
            next = current->next;
            delete_Node_Equipa(current);
            current = next;
        }
    }
    free(hash_eq->table_eq);
}

/* Funcao que insere uma equipa na hash table de equipas. */
void HT_Equipas_Insert(char nome[], Hash_equipa *hash, int NL)
{
    int hash_value;
    Node_equipa *node_tmp;
    Equipa *eq;

    if (HT_Get_Equipa(hash, nome, NULL) != 0)
    {
        printf("%d Equipa existente.\n", NL);
    }
    else
    {
        eq = novaEquipa(nome);
        hash_value = calc_hash(nome, hash->size);
        node_tmp = (Node_equipa*) malloc(sizeof(Node_equipa));
        node_tmp->eq = eq;
        node_tmp->next = hash->table_eq[hash_value];
        hash->table_eq[hash_value] = node_tmp;
    }
}

/* Funcao que seleciona e imprime todas as equipas com maior pontuacao. */
void seleciona_equipas(Hash_equipa *hash_eq, int NL)
{
    int i, k,count=0;
    int max = -1;
    char *string[10];
    Node_equipa *current;

    for (i = 0; i < hash_eq->size; i++)
    {
        if(hash_eq->table_eq[i] != NULL)
        {      
            current = hash_eq->table_eq[i];
            while(current != NULL)
            {
                if (current->eq->vitorias > max)
                {
                    max = current->eq->vitorias;
                    count=0;
                    string[count]=current->eq->nome;
                }
                else if (current->eq->vitorias == max)
                {
                    count++;
                    string[count]=current->eq->nome;
                }
                current = current->next;
            }
        }
    }
    if(max ==-1)
    {
     return;
    }
    else 
    {
        qsort(string, count+1, sizeof string[0], cmp);
        printf("%d Melhores %d\n", NL, max);
        for ( k = 0; k <= count; k++)
        {
            printf("%d * %s\n", NL, string[k]);
        }
    }
}

