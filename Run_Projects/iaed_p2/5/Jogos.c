#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj2.h"
#include "Jogos.h"
#include "Equipas.h"

/* Implementacao das funcoes referentes aos jogos. */

/* Cria um novo jogo. */
Jogo *novoJogo(char nome[],char equipa_1[],char equipa_2[],int pontuacao_1,int pontuacao_2)
{
    Jogo *j = (Jogo *)malloc(sizeof(Jogo));
    j->nome = strdup(nome);
    j->equipa_1 = strdup(equipa_1);
    j->equipa_2 = strdup(equipa_2);
    j->pontuacao_1 = pontuacao_1;
    j->pontuacao_2 = pontuacao_2;
    return j;
}

/* Imprime um jogo com base no nome. */
void printJogo(Hash_jogo *hash_jg, char nome[], int NL)
{
    Jogo *jogo = NULL; 
    if(HT_Get_Jogo(hash_jg, nome, &jogo) == 0)
    {
        printf("%d Jogo inexistente.\n", NL);
    }
    else
    {
        printf("%d %s %s %s %d %d\n", NL, jogo->nome, jogo->equipa_1, jogo->equipa_2, jogo->pontuacao_1, jogo->pontuacao_2);
    }
}

/* Funcao que insere um jogo no fim da lista de jogos. */
void insere(Jogo *jogo_ptr) 
{
        struct Node_jogo *novono;
        novono = (struct Node_jogo *)malloc(sizeof(struct Node_jogo));
        novono->jg = jogo_ptr;
        novono->next = NULL;
        if (cabeca == NULL)
        {
           cabeca = novono;
        }
        else
        {
            Node_jogo* current = cabeca;
            while (1)
            {
                if (current->next == NULL)
                {
                    current->next = novono;
                    break;
                }      
                current = current->next;
            };
        };
}

/* Funcao que imprime a lista de jogos. */
void imprimeLista(int NL) 
{
 	struct Node_jogo * ap;
 	ap = cabeca;
 	while (ap!=NULL)
	{
        printf("%d %s %s %s %d %d\n", NL, ap->jg->nome, ap->jg->equipa_1, ap->jg->equipa_2, ap->jg->pontuacao_1, ap->jg->pontuacao_2);
   		ap = ap->next;
	}	
}

/* Funcao que procura um jogo. */
struct Node_jogo * pesquisa(Jogo *jogo_ptr) 
{
    struct Node_jogo * ap;
    ap = cabeca;
    while(ap!=NULL)
    {
     if(ap->jg == jogo_ptr)
         return ap;
     ap = ap->next;
    }     
    return NULL;
}

/* Funcao que remove um jogo da lista. */
void remover(Jogo *jogo_ptr) 
{
    struct Node_jogo * aux;
    struct Node_jogo * apaga;
    
    if(cabeca->jg == jogo_ptr) 
    {
        apaga = cabeca;
        cabeca = cabeca->next;
        free(apaga);
    }
    else
    {
       aux = cabeca; 
       while((aux->next)->jg != jogo_ptr) 
       {
           aux = aux->next;   
       }
       apaga = aux->next; 
       aux->next = apaga->next; 
       free(apaga);
    }
}

/* Funcao principal para a remocao de um jogo. */
void remocao(Jogo *jogo_ptr) 
{
    struct Node_jogo * ap;
    ap = pesquisa(jogo_ptr);
    if(ap != NULL)
    {
        remover(jogo_ptr);
    }
}

/* Funcao que inicializa a hash table de jogos. */
void HT_Jogos_Init(int m, Hash_jogo *hash_ptr)
{
    int i;
    hash_ptr->size = m;
    hash_ptr->table_jg = (Node_jogo **)malloc(m * sizeof(Node_jogo *)); /* criei um array de m ponteiros para node*/
    for (i = 0; i < m; i++)
        hash_ptr->table_jg[i] = NULL;
}

/* Funcao que obtem jogo por nome. */
int HT_Get_Jogo(Hash_jogo *hash, char *nome, Jogo **jogo_ptr)
{
    int hash_value;
    Node_jogo *curr_node;
    hash_value = calc_hash(nome, hash->size);
    if(hash->table_jg[hash_value] == NULL)
    {
        return 0;
    }
    curr_node = hash->table_jg[hash_value];
    while(curr_node != NULL)
    {     
        if (strcmp(curr_node->jg->nome, nome) == 0)
        {         
            if(jogo_ptr)
            {               
                (*jogo_ptr) = curr_node->jg;
            }
            return 1;     
        }
        curr_node = curr_node->next;
    }       
    return 0;
}

/* Funcao que insere um jogo na hash table de jogos. */
void HT_Jogos_Insert(char nome_jogo[], char equipa_1[], char equipa_2[], int pontuacao_1, int pontuacao_2, Hash_jogo *hash_jg, Hash_equipa *hash_eq, int NL)
{
    int hash_value;
    Node_jogo *node_tmp;
    Jogo *jg;
    Equipa *equipa1 ;
    Equipa *equipa2;
    if (HT_Get_Jogo(hash_jg, nome_jogo, NULL) != 0) 
    {
        printf("%d Jogo existente.\n", NL);
        return;
    }
    else if (HT_Get_Equipa(hash_eq, equipa_1, NULL) == 0)
    {
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    else if (HT_Get_Equipa(hash_eq, equipa_2, NULL) == 0)
    {
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    else
    {
        HT_Get_Equipa(hash_eq, equipa_1, &equipa1);
        HT_Get_Equipa(hash_eq, equipa_2, &equipa2);

        jg = novoJogo(nome_jogo, equipa_1, equipa_2, pontuacao_1, pontuacao_2);
        hash_value = calc_hash(nome_jogo, hash_jg->size);
        node_tmp = (Node_jogo*) malloc(sizeof(Node_jogo));
        node_tmp->jg = jg;
        node_tmp->next = hash_jg->table_jg[hash_value];
        hash_jg->table_jg[hash_value] = node_tmp;
        insere(jg);

        if (jg->pontuacao_1 > jg->pontuacao_2) 
        {
            HT_Get_Equipa(hash_eq,jg->equipa_1, &equipa1);
            equipa1->vitorias += 1;
        }
        else if(jg->pontuacao_1 < jg->pontuacao_2)
        {
            HT_Get_Equipa(hash_eq,jg->equipa_2, &equipa2);
            equipa2->vitorias += 1;
        }
    }
}

/* Funcao que elimina um jogo. */
int HT_Jogo_Delete(Jogo *jogo_ptr, Hash_jogo *hash_jg)
{
    int hash_value;
    Node_jogo *curr_node;
    Node_jogo *aux;

    hash_value = calc_hash(jogo_ptr->nome, hash_jg->size);
    if(hash_jg->table_jg[hash_value] == NULL)
    { 
        return 0;
    }
    curr_node = hash_jg->table_jg[hash_value];
    aux = NULL;
    while(curr_node != NULL)
    {
        if (strcmp(curr_node->jg->nome, jogo_ptr->nome) == 0)
        {       
            if(aux)
            {
                 aux->next = curr_node->next;
            }
            else
            {
                hash_jg->table_jg[hash_value] = curr_node->next;
            } 
            delete_Node_Jogo(curr_node);
            return 1;  
        }
        else
        {
           aux = curr_node;
           curr_node = curr_node->next;
        }
    }
    return 0;
}

/* Funcao que liberta o espaco alocado por um jogo e um node de jogo. */
void delete_Node_Jogo(Node_jogo *node_jg)
{
    free(node_jg->jg->nome);
    free(node_jg->jg->equipa_1);
    free(node_jg->jg->equipa_2);
    free(node_jg->jg);
    free(node_jg);
}

/* Funcao que liberta o espaco alocado pela hash table de jogos. */
void HT_Jogos_Delete(Hash_jogo *hash_jg)/*free HT*/
{
    int i;
    Node_jogo *current;
    Node_jogo *next;
    for (i = 0; i < hash_jg->size ; i++)
    {
        current = hash_jg->table_jg[i];
        while (current != NULL)
        {
            next = current->next;
            delete_Node_Jogo(current);
            current = next;
        }
    }
    free(hash_jg->table_jg);
}

/* Funcao que liberta o espaco alocado pela lista de jogos.  */
void deleteCabeca(Node_jogo **head_ref) 
{ 
   Node_jogo* current = *head_ref; 
   Node_jogo* next; 
   while (current != NULL)  
   { 
       next = current->next; 
       free(current); 
       current = next; 
   } 
   (*head_ref) = NULL; 
} 