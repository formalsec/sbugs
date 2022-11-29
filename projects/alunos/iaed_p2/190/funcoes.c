#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "hashtable.h"
#include "hashtableEquipa.h"
#include "itemEquipa.h"

#define DIM 1024
/*Adiciona um novo jogo*/
int a(int i, char* str,int* keyJogo, int* tamHash, int* contadorJogos, int* tamHashEquipa){
    char nome[DIM];
    char equipa1[DIM];
    char equipa2[DIM];
    int score1 = 0;
    int score2 = 0;
    Item jogo;
    ItemEquipa ptr;
    sscanf(str,"%*c %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome,equipa1,equipa2,&score1,&score2);


    if (search(*tamHash,nome) != NULL) {
        printf("%d Jogo existente.\n", i);
        return 0;
    }
    if (searchEquipa(*tamHashEquipa,equipa1) == NULL || searchEquipa(*tamHashEquipa,equipa2) == NULL){
        printf("%d Equipa inexistente.\n", i);
        return 0;
    }
    if (score1 > score2) {
        ptr = searchEquipa(*tamHashEquipa,equipa1);
        ptr->pontosVencedores = ptr->pontosVencedores + 1;
    }
    if (score2 > score1) {
        ptr = searchEquipa(*tamHashEquipa,equipa2);
        ptr->pontosVencedores = ptr->pontosVencedores + 1;
    }
    jogo = (Item) can_fail_malloc(sizeof(struct jogo));

    jogo->nome = (char*) can_fail_malloc((strlen(nome)+1)*sizeof(char));
    strcpy(jogo->nome,nome);
    jogo->equipa1 = (char*) can_fail_malloc((strlen(equipa1)+1)*sizeof(char));
    strcpy(jogo->equipa1,equipa1);
    jogo->equipa2 = (char*) can_fail_malloc((strlen(equipa2)+1)*sizeof(char));
    strcpy(jogo->equipa2,equipa2);
    jogo->pontos.score1 = score1;
    jogo->pontos.score2 = score2;
    jogo->keyJogo = *keyJogo;

    insert(*tamHash,jogo);

    *keyJogo = *keyJogo + 1;
    *contadorJogos = *contadorJogos + 1;

    return 0;
}

/*Adiciona uma nova equipa*/
int A(int i, char* str, int* tamHashEquipa,int* contadorEquipas){
    char nome[DIM];
    ItemEquipa equipa;
    sscanf(str,"%*c %[^:]",nome);
    if (searchEquipa(*tamHashEquipa, nome) != NULL){
        printf("%d Equipa existente.\n", i);
        return 0;
    }
    equipa = (struct equipa*) can_fail_malloc(sizeof(struct equipa));
    equipa->nomeEquipa = (char*) can_fail_malloc((strlen(nome)+1)*sizeof(char));
    strcpy(equipa->nomeEquipa,nome);
    equipa->pontosVencedores = 0;
    insertEquipa(*tamHashEquipa,equipa);
    *contadorEquipas = *contadorEquipas + 1;

    return 0;
}
/*Procura um jogo com o nome dado*/
int p(int i,char* str,int* tamHash){
    char nome[DIM];
    Item ptr;
    sscanf(str,"%*c %[^:\n]",nome);
    if (search(*tamHash,nome) == NULL){
        printf("%d Jogo inexistente.\n", i);
        return 0;
    }
    else{
        ptr = search(*tamHash,nome);
        printf("%d %s %s %s %d %d\n",i,ptr->nome,ptr->equipa1,ptr->equipa2,ptr->pontos.score1,
                ptr->pontos.score2);
    }
    return 0;
}
/*Procura uma equipa dado um nome*/
int P(int i,char* str,int* tamHashEquipa){
    char nome[DIM];
    ItemEquipa ptr;
    sscanf(str,"%*c %[^:\n]",nome);
    if (searchEquipa(*tamHashEquipa,nome) == NULL){
        printf("%d Equipa inexistente.\n", i);
        return 0;
    }
    else{
        ptr = searchEquipa(*tamHashEquipa,nome);
        printf("%d %s %d\n",i,ptr->nomeEquipa,ptr->pontosVencedores);
    }
    return 0;
}
/*Termina o programa*/
void x(int tamHash, int tamHashEquipa){
    int i;
    for (i = 0; i < tamHash; ++i)
        deleteTudo(i);
    for (i = 0; i < tamHashEquipa; ++i)
        deleteTudoE(i);
    deleteHeads();
    deleteHeadsE();
}

/*Funcao de comparacao de inteiros usada no qsort*/
int compara_ints(const void *p, const void *q) {
    Item x = *(const Item*)p;
    Item y = *(const Item*)q;
    int xI = x->keyJogo;
    int yI = y->keyJogo;

    if (xI < yI)
        return -1;
    else if (xI > yI)
        return 1;

    return 0;
}

/*Lista todos os jogos introduzidos*/
int l(int e,int contadorJogos, int tamHash){
    Item * array;
    Item printA;
    int j;
    array = HashToArray(tamHash,contadorJogos);
    if (array == NULL)
        return 0;
    else{
        qsort(array,contadorJogos,sizeof(Item),compara_ints);
        for (j = 0; j < contadorJogos; ++j) {
            printA = array[j];
            printf("%d %s %s %s %d %d\n",e,printA->nome,printA->equipa1,printA->equipa2,
                    printA->pontos.score1,printA->pontos.score2);
        }
    }
    free(array);
    return 0;
}
/*Funcao de comparacao de strings usada no qsort*/
int compareEquipas(const void *p, const void *q) {
    ItemEquipa x = *(const ItemEquipa *) p;
    ItemEquipa y = *(const ItemEquipa *) q;
    char* xI = x->nomeEquipa;
    char* yI = y->nomeEquipa;
    if (strcmp(xI,yI) < 0)
        return -1;
    else if (strcmp(xI,yI) > 0)
        return 1;
    return 0;
}

/*Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica*/
int g(int e,int tamHashEquipa, int contadorEquipas) {
    ItemEquipa *array = NULL;
    ItemEquipa *best = NULL;
    int i, j = 0, k;
    int pontosMax = -1;
    if (contadorEquipas == 0)
        return 0;
    array = HashToArrayEquipa(tamHashEquipa, contadorEquipas);
    if (array == NULL)
        return 0;
    else {
        best = (ItemEquipa *) can_fail_malloc(sizeof(ItemEquipa) * contadorEquipas);
        for (i = 0; i < contadorEquipas; ++i) {
            if (array[i]->pontosVencedores == pontosMax) {
                best[j] = array[i];
                j++;/*max de elementos que deram*/
            } else if (array[i]->pontosVencedores > pontosMax) {
                for (k = 0; k < contadorEquipas; ++k) {
                    best[k] = NULL;
                    pontosMax = array[i]->pontosVencedores;
                    j = 0;
                    best[j] = array[i];
                    j++;

                }
            }
        }
        if (j > 1 && best[0] != NULL)
            qsort(best, j, sizeof(ItemEquipa), compareEquipas);
        if (contadorEquipas > 0) {
            printf("%d Melhores %d\n", e, best[0]->pontosVencedores);
            for (k = 0; k < j; ++k) {
                printf("%d * %s\n", e, best[k]->nomeEquipa);
            }
        }
    }
    free(best);
    free(array);
    return 0;
}
/*Apaga um jogo dado um nome*/
int r(int i, char* str, int tamHash, int tamHashEquipa, int* contadorJogos){
    char nome[DIM];
    sscanf(str,"%*c %[^:\n]",nome);
    if (search(tamHash,nome) == NULL) {
        printf("%d Jogo inexistente.\n", i);
        return 0;
    }
    delete(tamHash,nome,tamHashEquipa);
    *contadorJogos = *contadorJogos - 1;
    return 0;
}

/*Altera o score de um jogo dado um nome*/
int s(int i, char* str,int tamHash,int tamHashEquipa) {
    char nome[DIM];
    Item jogo;
    int score1 = 0;
    int score2 = 0;
    ItemEquipa ptr;
    sscanf(str, "%*c %[^:\n]:%d:%d", nome, &score1, &score2);
    if (search(tamHash, nome) == NULL) {
        printf("%d Jogo inexistente.\n", i);
        return 0;
    } else {
        jogo = search(tamHash, nome);
        if (jogo->pontos.score1 > jogo->pontos.score2) {
            if (score1 < score2) {
                ptr = searchEquipa(tamHashEquipa, jogo->equipa1);
                ptr->pontosVencedores = ptr->pontosVencedores - 1;

                ptr = searchEquipa(tamHashEquipa, jogo->equipa2);
                ptr->pontosVencedores = ptr->pontosVencedores + 1;
            }
        }
        if (jogo->pontos.score2 > jogo->pontos.score1) {
            if (score2 < score1) {
                ptr = searchEquipa(tamHashEquipa, jogo->equipa2);
                ptr->pontosVencedores = ptr->pontosVencedores - 1;

                ptr = searchEquipa(tamHashEquipa, jogo->equipa1);
                ptr->pontosVencedores = ptr->pontosVencedores + 1;
            }
        }
        if (jogo->pontos.score1 == jogo->pontos.score2){
            if (score1 > score2) {
                ptr = searchEquipa(tamHashEquipa,jogo->equipa1);
                ptr->pontosVencedores = ptr->pontosVencedores + 1;
            }
            if (score2 > score1) {
                ptr = searchEquipa(tamHashEquipa,jogo->equipa2);
                ptr->pontosVencedores = ptr->pontosVencedores + 1;
            }
        }
        if (score2 == score1) {
            if (jogo->pontos.score1 > jogo->pontos.score2) {
                ptr = searchEquipa(tamHashEquipa, jogo->equipa1);
                ptr->pontosVencedores = ptr->pontosVencedores - 1;
            }
            if (jogo->pontos.score2 > jogo->pontos.score1) {
                ptr = searchEquipa(tamHashEquipa, jogo->equipa2);
                ptr->pontosVencedores = ptr->pontosVencedores - 1;
            }
        }
        jogo->pontos.score1 = score1;
        jogo->pontos.score2 = score2;
    }
    return 0;
}