#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projeto2.h"


void insert_new_node(node** head,jg_node * jg)
{
    /*Aloca espaco para um novo node*/
    node * new_node = can_fail_malloc(sizeof(node));
    node * current;
    /*Aloca espaco para uma nova string*/
    new_node->nome_jogo = can_fail_malloc(sizeof(char)*(strlen(jg->value)+1));
    /*Copia e guarda nesse no a nova string*/
    strcpy(new_node->nome_jogo, jg->value);
    /*Liga o ponteiro jogo do no ao no da lista de jogos criada anteriormente*/
    new_node->jogo = jg;
    new_node->next = NULL;
    /*Caso o indice da hash ainda seja vazio*/
    if (*head == NULL)
    {
        /*Liga o novo no ao indice*/
        *head = new_node;
    }
    else
    {
        current = *head;
        /*Caso nao seja vazio o indice, vai percorre lo ate chegar ao fim*/
        while(current->next != NULL)
        {
            current = current->next;
        }
        /*Liga o novo no ao ultimo no do indice da hash*/
        current->next = new_node;
    }
}

/**************************************************************************************************/

void insert_into_table(node** hashtable,jg_node *jg)
{
    node * head;
    /*Determina a suposta localizacao da string na hash*/
    int location = get_location(jg->value);
    /*Caso o indice ainda nao tenha nenhum no la localizado*/
    if(hashtable[location] == NULL)
    {
        /*Cria um node e adiciona-o a hash naquele indice*/
        head = NULL;
        insert_new_node(&head,jg);
        hashtable[location] = head;
    }
    else
    {
        /*Vai adicionar o novo um novo no ao indice da hash*/
        head = hashtable[location];
        insert_new_node(&head,jg);
        hashtable[location] = head;
    }
}
/**************************************************************************************************/