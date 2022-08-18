#include "jogo.h"

pJogo criarJogo(char * nome, char * eq1, char * eq2, int pont1, int pont2, listaEq listaEquipas, int numINP){
    pJogo novoJogo;
    if (procurarEquipa(listaEquipas, eq1) != NULL && procurarEquipa(listaEquipas, eq2) != NULL){
        novoJogo = (pJogo) malloc (sizeof(struct jogo));
        novoJogo->nome = (char *) malloc(sizeof(char) * (strlen(nome)+1));
        strcpy(novoJogo->nome, nome);
        novoJogo->equipa1 = procurarEquipa(listaEquipas, eq1); /*Ponteiro para a equipa de nome eq1*/
        novoJogo->equipa2 = procurarEquipa(listaEquipas, eq2); /*Ponteiro para a equipa de nome eq2*/
        novoJogo->pont1 = pont1;
        novoJogo->pont2 = pont2;
        return novoJogo;
    }
    printf("%d Equipa inexistente.\n", numINP);
    novoJogo = NULL;
    return novoJogo;
}

void mostrarJogo(pJogo jogo, int numINP){
    if (jogo != NULL){
        printf("%d %s %s %s %d %d\n",numINP, jogo->nome, jogo->equipa1->nomeEquipa, jogo->equipa2->nomeEquipa, jogo->pont1, jogo->pont2);
    }
    else
    {
        printf("%d Jogo inexistente.\n", numINP);
    }
    
}

void adicionaVitoria(pJogo j){
    if (j->pont1 > j->pont2){
        j->equipa1->numVitorias++;
    }
    else if (j->pont2 > j->pont1){
        j->equipa2->numVitorias++;
    }
}

void retiraVitoria(pJogo j){
    if (j->pont1 > j->pont2){
        j->equipa1->numVitorias--;
    }
    else if (j->pont2 > j->pont1){
        j->equipa2->numVitorias--;
    }
}

void libertarJogo(pJogo jogo){
    if (jogo != NULL){
        free(jogo->nome);
        free(jogo);
    }
}