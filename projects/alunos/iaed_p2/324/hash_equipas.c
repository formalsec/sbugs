#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projeto2.h"


void insert_new_e_node(e_node** head, char *nome_equipa)
{   
    /*Aloca espaco para um novo e_node*/
    e_node * new_node = can_fail_malloc(sizeof(e_node));
    e_node * current;
    /*Aloca espaco para uma nova string*/
    new_node->nome = can_fail_malloc(sizeof(char)*(strlen(nome_equipa)+1));
    /*Copia e guarda nesse no a nova string*/
    strcpy(new_node->nome, nome_equipa);
    /*Inicializa o argumento vitorias do novo no a 0*/
    new_node->vitorias = 0;
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

void insert_into_equipas(e_node** hashtable, char *nome)
{
    e_node * head;
    /*Determina a suposta localizacao da string na hash*/
    int location = get_location(nome);
    /*Caso o indice ainda nao tenha nenhum no la localizado*/
    if(hashtable[location] == NULL)
    {
        /*Cria um e_node e adiciona-o a hash naquele indice*/
        head = NULL;
        insert_new_e_node(&head, nome);
        hashtable[location] = head;
    }
    else
    {
        /*Vai adicionar o novo um novo no ao indice da hash*/
        head = hashtable[location];
        insert_new_e_node(&head, nome);
        hashtable[location] = head;
    }
}
/**************************************************************************************************/