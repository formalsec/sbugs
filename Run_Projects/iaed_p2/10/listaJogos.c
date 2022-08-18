#include "listaJogos.h"

listaJogo novoJogoLista(pJogo novoJogo, int ordem){
    listaJogo novoNO = (listaJogo) malloc(sizeof(struct noJogo));
    novoNO->ptJogo = novoJogo;
    adicionaVitoria(novoJogo);
    novoNO->ordem = ordem;
    novoNO->proximo = NULL;
    return novoNO;
}

listaJogo adicionarNovoJogo(pJogo novoJogo, listaJogo * listaJogos, int ordem, int numINP){
    listaJogo no, noAnt;
    if (*listaJogos == NULL){
        return novoJogoLista(novoJogo, ordem);        
    }
    /*Insere o novo jogo no fim da lista*/
    for (no = *listaJogos, noAnt = NULL; no!= NULL; noAnt = no, no = no->proximo){
        if (strcmp(no->ptJogo->nome, novoJogo->nome) == 0){
            printf("%d Jogo existente.\n", numINP);
            return *listaJogos;
        }
    }
    noAnt->proximo = novoJogoLista(novoJogo, ordem);
    return *listaJogos;
}

pJogo procurarJogoLista(listaJogo * listaJogos, char * nome){
    listaJogo no = *listaJogos;
    for(; no != NULL; no = no->proximo){
        if (strcmp(no->ptJogo->nome, nome) == 0){
            return no->ptJogo;
        }
    }
    return NULL;
}

void apagarJogoLista(listaJogo * listaJogos, char * nome, int numINP){
    listaJogo no, noAnt;
    if (*listaJogos == NULL){
        printf("%d Jogo inexistente.\n", numINP);
        return;
    }
    else{
        for (no = *listaJogos, noAnt = NULL; no != NULL; noAnt = no, no = no->proximo){
            if (strcmp(no->ptJogo->nome, nome) == 0){
                /*Verifica que o jogo a ser eliminado esta na lista */
                if (noAnt == NULL){
                    *listaJogos = no->proximo;
                    retiraVitoria(no->ptJogo);
                    libertarJogo(no->ptJogo);
                    free(no);
                    return;
                }
                noAnt->proximo = no->proximo;
                retiraVitoria(no->ptJogo);
                libertarJogo(no->ptJogo);
                free(no);
                return;
            }
        }
    printf("%d Jogo inexistente.\n", numINP);
    }
}

void libertarListaJogos(listaJogo * listaJogos){
    listaJogo no, temp;
    no = *listaJogos;
    while (no != NULL){
        temp = no->proximo;
        libertarJogo(no->ptJogo);
        no = temp;
    }
    free(*listaJogos);
}