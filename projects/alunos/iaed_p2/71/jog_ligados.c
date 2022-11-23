#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
#include "jog_ligados.h"

/* Inicializa-se a lista com os dois links a NULL */
Lista_Jogos init_lista_jogos()
{
	Lista_Jogos lista = can_fail_malloc(sizeof(struct lista_ligada));
	lista->primeiro = NULL;
	lista->ultimo = NULL;
	return lista;
}

void acrescenta_jogo(Lista_Jogos lista, Jogo jogo)
{
    jog_lig link = can_fail_malloc(sizeof(struct node_jogos));
    link->jogo = jogo;
    if (lista->primeiro == NULL)
    {
        lista->primeiro = link;
        lista->ultimo = link;
        lista->primeiro->seguinte = lista->ultimo;
    }
    /* Se ainda so existir um link fazemos ultimo o seguinte de primeiro */
    else if (lista->primeiro->jogo == lista->ultimo->jogo)
    {
        lista->ultimo = link;
        lista->primeiro->seguinte = lista->ultimo;
    }
    /* Se houver mais do que um acrescentamos um novo*/
    else
    {
        lista->ultimo->seguinte = link;
        lista->ultimo = link;
    }
    lista->ultimo->seguinte = NULL;
}

void rem_aux1(Lista_Jogos lista, Jogo jogo)
{
    jog_lig atual, anterior;
    int verifica = 0;

    /* Se o primeiro for o que queremos substituimo-lo pelo seguinte */
    if (lista->primeiro->jogo == jogo)
    {
        atual = lista->primeiro;
        lista->primeiro = lista->primeiro->seguinte;
        free(atual);
    }    
    else
    {
        /* anterior comeca no primeiro link */
        anterior = lista->primeiro;
        /* atual comeca no segundo link */
        for (atual = lista->primeiro->seguinte; atual != lista->ultimo; atual = atual->seguinte)
        {
            if (atual->jogo == jogo)
            {
                verifica++;
                anterior->seguinte = atual->seguinte;
                free(atual);
                break;
            }
            anterior = atual;
        }
        /* Se verifica for 0 entao nao foi encontrado nenhum antes do ultimo */
        if (!verifica)
        {
            anterior->seguinte = NULL;
            free(lista->ultimo);
            lista->ultimo = anterior;
        }
    }
}

void destroi_jog_ligados(Lista_Jogos lista)
{
    jog_lig atual, seg;

    /* Nao tem elementos */
	if (lista->primeiro == NULL)
    {
        free(lista);
    }
    /* So tem um elemento */
    else if (lista->primeiro->jogo == lista->ultimo->jogo)
    {
        free(lista->primeiro);
        free(lista);
    }
    /* Tem dois ou mais elementos */
    else
    {
        atual = lista->primeiro;
        while (atual != lista->ultimo)
        {
            seg = atual->seguinte;
            free(atual);
            atual = seg;
        }
        free(atual);
        free(lista);
    }
}
