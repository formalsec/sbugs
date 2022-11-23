#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include "equipa.h"
#include <stdlib.h>
#include <string.h>


linkEquipa ProcuraEHash(linkEquipa *tab, char *v){
    /*Funcao recebe um nome de uma equipa e acede a tabela de dispersao*/
    int i;
    linkEquipa e;

    i = hash(v, hashM);
    if(tab[i]!= NULL) e = tab[i];
    else return NULL; /*acesso vazio*/

    while(e != NULL){
        if ( strcmp(e->equipa->nome, v) == 0) return e;/*caso encontre*/

        e = e->nextHash;
    }

    return NULL;/*caso depois da pesquisa nao encontrar o nome*/

}


linkEquipa NovaEquipa(char* nome){
    /*Funcao recebe um nome e cria uma nova equipa alocando memoria dinamicamente*/
    linkEquipa x;
    Equipa *e = (Equipa*) can_fail_malloc(sizeof(Equipa));

    /*Novo node do tipo "equipa"*/
    x  = (linkEquipa) can_fail_malloc(sizeof(struct Equipa_Node));

    /*inicializa variaveis*/
    e->nome = (char*) can_fail_malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(e->nome, nome);

    e->vit = (int*) can_fail_malloc(sizeof(int));
    *(e->vit) = 0;

    x->equipa = e;

    x->nextHash = NULL;
    x->nextList = NULL;
    x->prevList = NULL;

    return x;
}


void InserirEquipa(linkEquipa *pheade,linkEquipa *ptaile, linkEquipa *tabEquipas, linkEquipa e){
    /*Funcao insere uma nova equipa na estrutura*/
    int i;

    /*Posiciona a equipa na tabela de dispersao*/
    i = hash(e->equipa->nome, hashM);


    if(tabEquipas[i] != NULL){
        e->nextHash = tabEquipas[i];
    }
    tabEquipas[i] = e;

    /*Posiciona a equipa na lista*/
    if (*pheade !=NULL){
        e->nextList = *pheade;
        (*pheade)->prevList = e;
        *pheade = e;
        ReposCima(pheade, ptaile, e);
    }
    else{/*caso seja a primeira equipa*/
        *pheade = e;
        *ptaile = e;
    }


}

void ReposCima(linkEquipa *pheade,linkEquipa *ptaile, linkEquipa e){
    /*Funcao reposiciona equipa cujas vitorias foram incrementadas,
    uma vez que a equipa ja esta proxima da sua verdadeira posicao,
    reposiciona-se*/ 
    linkEquipa aux;
    int ev, nauxv;
    char *enome, *nauxnome;

    if (e == *ptaile)/*Caso ja seja a equipa com mais vitorias*/
        return;

    aux = e; /*variavel vai ser posicionada na futura posicao da equipa*/
    ev = *(e->equipa->vit);
    nauxv = *(aux->nextList->equipa->vit);

    /*Aux Avanca ate estar a frente das equipas com menos vitorias*/
    while ((aux->nextList != NULL) && (ev > nauxv)){
        aux = aux->nextList;
        if( aux->nextList == NULL)
            break;
        nauxv = *(aux->nextList->equipa->vit);
    }
    /*Aux Avanca ate estar a frente das equipas com nome atras no alfabeto*/
    enome = e->equipa->nome;
    if (aux->nextList != NULL)
        nauxnome = aux->nextList->equipa->nome;
    while ((aux->nextList != NULL) && ev == nauxv && (strcmp(enome, nauxnome) < 0)){
        aux = aux->nextList;
        if( aux->nextList == NULL)
            break;
        nauxv = *(aux->nextList->equipa->vit);
        nauxnome = aux->nextList->equipa->nome;
        }
    
    if (aux == e) /*Caso nao altere de posicao*/
        return;
    else if (aux == *ptaile){ /*Caso avance para a tail*/
        if (e == *pheade){      /*Caso comece na head*/
            *pheade = (*pheade)->nextList;
            (*pheade)->prevList = NULL;
        }
        else{                  /*Caso nao comece na head*/
            (e->nextList)->prevList = e->prevList;
            (e->prevList)->nextList = e->nextList;
        }
        (*ptaile)->nextList = e;
        e->prevList = *ptaile;
        *ptaile = e;
        e->nextList = NULL;
    }
    else{ /*Caso avance mas nao para a tail*/
        if (e == *pheade){      /*Caso comece na head*/
            *pheade = (*pheade)->nextList;
            (*pheade)->prevList = NULL;
        }
        else{                  /*Caso nao comece na head*/
            (e->nextList)->prevList = e->prevList;
            (e->prevList)->nextList = e->nextList;
        }
        e->nextList = aux->nextList;
        e->prevList = aux;
        aux->nextList = e;
        (e->nextList)->prevList = e;
    }

}

void ReposBaixo(linkEquipa *pheade,linkEquipa *ptaile, linkEquipa e){
    /*Funcao reposiciona equipa cujas vitorias foram decrementadas,
    uma vez que a equipa ja esta proxima da sua verdadeira posicao,
    reposiciona-se*/

    linkEquipa aux;
    int ev, pauxv;
    char *enome, *pauxnome;

    if (e == *pheade)/*Caso ja seja a equipa com menos vitorias*/
        return;

    aux = e;/*variavel vai ser posicionada na futura posicao da equipa*/
    ev = *(e->equipa->vit);
    pauxv = *(aux->prevList->equipa->vit);

    /*Aux recua ate estar a atras das equipas com mais vitorias*/
    while ((aux->prevList != NULL) && (ev < pauxv)){
        aux = aux->prevList;
        if( aux->prevList == NULL)
            break;
        pauxv = *(aux->prevList->equipa->vit);
    }
    /*Aux recua ate estar a atras das equipas com nome a frente no alfabeto*/
    enome = e->equipa->nome;
    if (aux->prevList != NULL)
        pauxnome = aux->prevList->equipa->nome;
    while ((aux->prevList != NULL) && ev == pauxv && (strcmp(enome, pauxnome) > 0)){
        aux = aux->prevList;
        if( aux->prevList == NULL)
            break;
        pauxv = *(aux->prevList->equipa->vit);
        pauxnome = aux->prevList->equipa->nome;
        }
    
    if (aux == e) /*Caso nao altere de posicao*/
        return;
    else if (aux == *pheade){ /*Caso avance para a head*/
        if (e == *ptaile){      /*Caso comece na tail*/
            *ptaile = (*ptaile)->prevList;
            (*ptaile)->nextList = NULL;
        }
        else{                  /*Caso nao comece na tail*/
            (e->nextList)->prevList = e->prevList;
            (e->prevList)->nextList = e->nextList;
        }
        (*pheade)->prevList = e;
        e->nextList = *pheade;
        *pheade = e;
        e->prevList = NULL;
    }
    else{ /*Caso avance para o interior*/
        if (e == *ptaile){      /*Caso comece na tail*/
            *ptaile = (*ptaile)->prevList;
            (*ptaile)->nextList = NULL;
        }
        else{                  /*Caso nao comece na head*/
            (e->nextList)->prevList = e->prevList;
            (e->prevList)->nextList = e->nextList;
        }
        e->prevList = aux->prevList;
        e->nextList = aux;
        aux->prevList = e;
        (e->prevList)->nextList = e;
    }

}

void freeEquipa(Equipa *e){
    /*Funcao liberta a memoria dinamicamente alocada para uma equipa*/
    free(e->nome);
    free(e->vit);
    free(e);
}

void freeLinkEquipa(linkEquipa e){
    /*Funcao liberta a memoria dinamicamente alocada para um 
    encadeamento (lista) de nodes de equipas, recursivamente*/
    if (e->nextHash != NULL)
        freeLinkEquipa(e->nextHash);
    freeEquipa(e->equipa);
    free(e);
}