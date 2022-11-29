#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipa.h"
#include "HT_equipas.h"



/* Recebe o um numero inteiro e devolve uma hashtable de equipas com esse numero de divisoes */
HT_eq HTeq_inicializa(int max) {
    HT_eq equipas;
    int i;

    equipas = (HT_eq) can_fail_malloc(max * sizeof(link_eq));
    /* Inicializa todas as posicoes da tabela com o endereco NULL */
    for (i=0; i<max; i++)
        equipas[i] = NULL;
    return equipas;
}



/* Recebe um vetor de caracteres e o numero de divisoes da hashtable e devolve a
posicao correspondente na hashtable */
int hash(char *c, int max) {
    int h = 0, a = 127;
    for (; *c != '\0'; c++)
        h = (a*h + *c) % max;
    return h;
}


/* Recebe uma hashtable de equipas, um nome e o numero de divisoes da hastable, cria uma equipa
com esse nome e guarda-a na hashtable */
void HTeq_adiciona(HT_eq equipas, char* nome, int max) {
    int i = hash(nome, max);
    Equipa eq = nova_equipa(nome);
    link_eq novo = (link_eq) can_fail_malloc(sizeof(struct node_eq));

    novo->equipa = eq;
    novo->prox = equipas[i];
    equipas[i] = novo;
}



/* Recebe uma hashtable de equipas, um nome e o numero de divisoes da hashtable e devolve o
endereco da equipa com esse nome, se estiver guardada na hashtable. Senao devolve NULL */
Equipa HTeq_procura(HT_eq equipas, char* nome, int max) {
    link_eq link;
    int i = hash(nome, max);

    for (link=equipas[i]; link != NULL; link = link->prox)
        if (strcmp( nome_equipa(link->equipa), nome) == 0)
            return link->equipa;
    return NULL;
}



/* Recebe uma hashtable de equipas, e 2 ponteiros para inteiros. Guarda o numero maximo de jogos
ganhos por 1 equipa e o numero de equipas com essa quantidade de vitorias nesses inteiros */
void maximo_vitorias(HT_eq equipas, int* max_num, int max_eq) {
    int i, max, num, v;
    link_eq link;

    max = 0;
    num = 0;
    /* Para cada no' de cada posicao da hashtable */
    for (i=0; i<max_eq; i++) {
        for (link=equipas[i]; link != NULL; link = link->prox) {
            v = vitorias_equipa(link->equipa);
            /* Se o numero de vitorias da equipa for maior que o maximo, passa a ser o
            maximo e recomeca a contagem */
            if (v > max) {
                max = v;
                num = 1;
            }
            /* Se for igual ao maximo, soma 1 'a contagem */
            else if (v == max)
                num +=1;
        }         
    }
    max_num[0] = max;
    max_num[1] = num;
}



/* Recebe uma hashtable de equipas, um vetor de equipas, umm numero de vitorias e o numero de divisoes da hashtable
e guarda na tabela todas as equipas com esse numero de vitorias*/
void melhores_equipas(HT_eq equipas, Equipa *melhores, int max_v, int max_eq) {
    int i, j;
    link_eq link;

    j = 0;
    /* Para cada no' de cada posicao da hashtable */
    for (i=0; i<max_eq; i++) {
        for (link=equipas[i]; link != NULL; link = link->prox) {
            if (vitorias_equipa(link->equipa) == max_v) {
                melhores[j] = link->equipa;
                j++;
            }
        }     
    }
}



/* Recebe uma hashtable de equipas e o seu numero de divisoes e apaga a hashtable e todas
as equipas que esta guarda */
void HTeq_termina(HT_eq equipas, int max) {
    int i;
    link_eq link, prox;

    /* Para cada no' de cada posicao da hashtable */
    for (i=0; i< max; i++) {
        for (link=equipas[i]; link != NULL; link = prox) {
            prox = link->prox;
            apaga_equipa(link->equipa);
            free(link);

        }     
    }
    free(equipas);
}