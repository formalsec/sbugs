#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projeto2.h"


jogos * mk_list_jg()
{
    /*Aloca espaco para criar uma lista ligada de jogos*/
    jogos * l = malloc(sizeof(jogos));
    /*Inicializa a lista*/
    l->head =l->last=  NULL;
    return l;
}

/**************************************************************************************************/

jg_node *add_last_jg(jogos *l, const char *nome, const char *equipa1, const char *equipa2, int score1, int score2)
{
    /*Aloca espaco para um novo jg_node*/
    jg_node *nn = malloc(sizeof(jg_node));
    /*Vai adicionar o no ao fim da lista*/
    nn->previous =l->last;
    nn->next = NULL;
    /*Aloca espaco para os argumentos strings do novo no a adicionar*/
    nn->value = malloc(sizeof(char)*(strlen(nome)+1));
    nn->equipa1 = malloc(sizeof(char)*(strlen(equipa1)+1));
    nn->equipa2 = malloc(sizeof(char)*(strlen(equipa2)+1));
    /*Copia para esses espacos alocados/para o no os respetivos argumentos lidos anteriormente*/
    strcpy(nn->value, nome);
    strcpy(nn->equipa1, equipa1);
    strcpy(nn->equipa2, equipa2);
    
    nn->score1 = score1;
    nn->score2 = score2;
    /*Se a lista ja estiver elementos*/
    if(l->last)
    {
        /*Coloca o no a seguir ao ultimo*/
        l->last->next = nn;
    }
    /*Se a lista ainda estiver vazia*/
    else
    {
        /*Coloca o novo no como primeiro elemento da lista*/
        l->head = nn;
    }
    /*Apesar de poder ser o primeiro elemento da lista ou nao, torna se o ultimo elemento a ter sido adicionado*/
    l->last = nn;
    return nn;
}
/**************************************************************************************************/