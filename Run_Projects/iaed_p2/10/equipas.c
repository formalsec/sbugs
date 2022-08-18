#include "equipas.h"


pEquipa criarEquipa(char * nome){
    pEquipa novaEquipa;
    novaEquipa = (pEquipa) malloc (sizeof(struct equipa));
    novaEquipa->nomeEquipa = (char *) malloc(sizeof(char) * strlen(nome) + 1);
    strcpy(novaEquipa->nomeEquipa, nome);
    /*Numero de vitorias inicial sempre igual a 0*/
    novaEquipa->numVitorias = 0;
    return novaEquipa;
}

void libertarEquipa(pEquipa equipaFree){
    if (equipaFree != NULL){
        free(equipaFree->nomeEquipa);
        free(equipaFree);
    }
}

void mostrarEquipa(pEquipa equipa, int numINP){
    if( equipa != NULL){
        printf("%d %s %d\n", numINP, equipa->nomeEquipa, equipa->numVitorias);
    }
    else
    {
        printf("%d Equipa inexistente.\n", numINP);
    }
    
}

listaEq criarListaEquipas(){
    listaEq novaLista = NULL;
    return novaLista;
}

listaEq adicionarNovaEquipa(pEquipa novaEquipa, listaEq listaEquipas, int numINP){
    listaEq noAtual, noAnterior, novoNo;
    /*Caso ainda nao haja elementos na lista*/
    if (listaEquipas == NULL){
        listaEquipas = (listaEq ) malloc(sizeof(struct noEquipa));
        listaEquipas->ptrEquipa = novaEquipa;
        listaEquipas->proximo = NULL;
        return listaEquipas;
    }
    /*Caso ja existam elementos na lista*/
    novoNo = (listaEq ) malloc(sizeof(struct noEquipa));
    novoNo->ptrEquipa = novaEquipa;
    for (noAtual = listaEquipas, noAnterior = NULL; noAtual != NULL; 
                    noAnterior = noAtual, noAtual = noAtual->proximo){
        /*verificar se a equipa existe na lista*/
        if ( strcmp(noAtual->ptrEquipa->nomeEquipa, novaEquipa->nomeEquipa) == 0 ){
            printf("%d Equipa existente.\n", numINP);
            libertarEquipa(novoNo->ptrEquipa);
            free(novoNo);
            return listaEquipas;
        }

        /*a novaEquipa e menor lexicamente que a atual e vai ser inserida imediatamente antes*/
        else if (strcmp(noAtual->ptrEquipa->nomeEquipa, novaEquipa->nomeEquipa) > 0){
            /*caso em que e inserido antes do inicio da lista*/

            if (noAtual == listaEquipas){
                novoNo->proximo = noAtual;
                return novoNo;          
            }
            /*caso em que e inserido no meio da lista */
            else {
                novoNo->proximo = noAtual;
                noAnterior->proximo = novoNo;
                return listaEquipas;
            }      
        }      
    }
    /*caso em que e inserido no fim*/
    noAnterior->proximo = novoNo;
    novoNo->proximo = NULL;
    return listaEquipas;
}

pEquipa procurarEquipa(listaEq listaEquipas, char * nome){
    listaEq no = listaEquipas;
    for (; no != NULL; no = no->proximo){
        if (strcmp(no->ptrEquipa->nomeEquipa, nome) == 0){
            return no->ptrEquipa;
        }
    }
    /*nao encontrou a equipa*/
    return NULL;
}

int maxVitorias(listaEq listaEquipas){
    listaEq no;
    int max;
    no = listaEquipas;
    max = 0;
    for( ; no != NULL; no = no->proximo){
        if (max < no->ptrEquipa->numVitorias){
            max = no->ptrEquipa->numVitorias;
        }
    }
    return max;
}

void melhoresEquipas(listaEq listaEquipas, int numINP){
    int max, first;
    listaEq noLista;
    noLista = listaEquipas;
    first = 1;
    max = maxVitorias(listaEquipas);
    for (; noLista != NULL; noLista = noLista->proximo){
        /*Apresentar as equipas com o numero de vitorias igual ao maximo*/
        if (noLista->ptrEquipa->numVitorias == max && first == 1){
            printf("%d Melhores %d\n",numINP, max);
            printf("%d * %s\n", numINP, noLista->ptrEquipa->nomeEquipa);
            first = 0;
        }
        else if (noLista->ptrEquipa->numVitorias == max && first == 0){
            printf("%d * %s\n", numINP, noLista->ptrEquipa->nomeEquipa);
        }
    }
}

void libertarListaEquipas(listaEq listaEquipas){
    listaEq no, temp;
    no = listaEquipas;
    while( no != NULL){
        temp = no->proximo;
        libertarEquipa(no->ptrEquipa);
        free(no);
        no = temp;
    }
}