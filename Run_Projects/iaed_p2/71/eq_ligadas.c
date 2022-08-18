#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eq_ligadas.h"

/*
NOTA: comparam-se lista->primeira->equipas e link->ultima->equipa,
pois podem ter a mesma equipa e seguintes diferentes (quando a lista so tem um elemento)
*/

/* Inicializa-se a lista com os dois links a NULL */
Lista_Equipas init_lista_eq()
{
	Lista_Equipas lista = malloc(sizeof(struct lista_ligada));
	lista->primeira = NULL;
	lista->ultima = NULL;
	return lista;
}

void acrescenta_eq(Lista_Equipas lista, Equipa equipa)
{
    int verifica = 0;
    eq_lig link = malloc(sizeof(struct node_equipas));
    eq_lig atual, anterior = NULL;
    link->equipa = equipa;
    if (lista->primeira == NULL)
    {
        lista->primeira = link;
        lista->ultima = link;
        lista->primeira->seguinte = lista->ultima;
    }
    /* Se ainda so existir um link fazemos ultima o seguinte de primeira */
    else if (lista->primeira->equipa == lista->ultima->equipa)
    {
        if (strcmp(lista->primeira->equipa->nome, link->equipa->nome) > 0)
        {
            lista->primeira = link;
        }
        else
        {
            lista->ultima = link;
        }
        lista->primeira->seguinte = lista->ultima;
    }
    /* Se houver mais do que um acrescentamos um novo*/
    else
    {
        for (atual = lista->primeira; atual != lista->ultima; atual = atual->seguinte)
        {
            /* Paramos se atual tem de ficar mais "a direita" na lista do que link */
            if (strcmp(atual->equipa->nome, link->equipa->nome) > 0)
            {
                verifica++;
                /* link passa a ser o primeiro */
                if (anterior == NULL)
                {
                    link->seguinte = lista->primeira;
                    lista->primeira = link;
                }
                else
                {
                    link->seguinte = atual;
                    anterior->seguinte = link;
                }
                break;
            }
            anterior = atual;
        }
        /* Se verifica for 0 entao nao foi encontrado nenhum antes do ultimo */
        if (!verifica)
        {
            /* link passa a ser o penultimo */
            if (strcmp(lista->ultima->equipa->nome, link->equipa->nome) > 0)
            {
                link->seguinte = lista->ultima;
                anterior->seguinte = link;
            }
            /* link passa a ser o ultimo */
            else
            {
                lista->ultima->seguinte = link;
                lista->ultima = link;
                lista->ultima->seguinte = NULL;
            }
        }
    }
    lista->ultima->seguinte = NULL;
}

void print_lista_eq(Lista_Equipas lista, int linha, int max_ganhos)
{
    /* x comeca como o primeira introduzido */
    eq_lig x = lista->primeira;

    /* Nao tem elementos */
    if(lista->primeira == NULL)
    {
        return;
    }
    /* So tem um elemento */
    else if (lista->ultima->equipa == lista->primeira->equipa)
    {
        printf("%d Melhores %d\n", linha, max_ganhos);
        printf("%d * %s\n", linha, x->equipa->nome);
    }
    /* Tem mais do que um elemento */
    else
    {
        printf("%d Melhores %d\n", linha, max_ganhos);

        while(x != lista->ultima)
        {
            printf("%d * %s\n", linha, x->equipa->nome);
            x = x->seguinte;
        }
        printf("%d * %s\n", linha, x->equipa->nome);
    }
}

void destroi_eq_ligadas(Lista_Equipas lista)
{
    eq_lig atual, seg;
    /* Nao tem elementos */
	if (lista->primeira == NULL)
    {
        free(lista);
        return;
    }
    /* So tem um elemento */
    else if (lista->primeira->equipa == lista->ultima->equipa)
    {
        free(lista->primeira);
        free(lista);
    }
    /* Tem mais do que um elemento */
    else
    {
        atual = lista->primeira;
        seg = atual->seguinte;

        while (atual != lista->ultima)
        {
            free(atual);
            atual = seg;
            seg = seg->seguinte;
        }
        free(lista->ultima);
        free(lista);
    }
}

