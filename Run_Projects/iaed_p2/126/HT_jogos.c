#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipa.h"
#include "HT_equipas.h"
#include "jogo.h"
#include "HT_jogos.h"



/* Recebe o um numero inteiro e devolve uma hashtable de jogos com esse numero de divisoes */
HT_jg HTjg_inicializa(int max) {
    HT_jg jogos;
    int i;

    jogos = (HT_jg) malloc(max * sizeof(link_jg));
    /* Inicializa todas as posicoes da tabela com o endereco NULL */
    for (i=0; i<max; i++)
        jogos[i] = NULL;
    return jogos;
}



/* recebe um jogo e um link para o no' seguinte e devolve um link para um novo no' que
guarda o ponteiro para o jogo */
link_jg novo_node_jg(Jogo jogo, link_jg prox) {
    link_jg x = (link_jg) malloc(sizeof(struct node_jg));
    x->jogo = jogo;
    x->prox = prox;
    return x;
}



/* Recebe uma hashtable de jogos, um nome, um Jogo e o numero de divisoes da hastable e guarda
o jogo na hashtable */
void HTjg_adiciona(HT_jg jogos, char* nome, Jogo jogo, int max) {
    int i = hash(nome, max);
    jogos[i] = novo_node_jg(jogo, jogos[i]);
}



/* Recebe uma hashtable de jogos, um nome e o numero de divisoes da hashtable e devolve o
endereco do jogo com esse nome, se estiver guardada na hashtable. Senao devolve NULL */
Jogo HTjg_procura(HT_jg jogos, char* nome, int max) {
    link_jg l;
    int i = hash(nome, max);

    for (l=jogos[i]; l != NULL; l = l->prox)
        if (strcmp( nome_jogo(l->jogo), nome) == 0)
            return l->jogo;
    return NULL;
}



/* Recebe uma hashtable de jogos, um nome, um jogo e o numero de divisoes da hashtable e retira
o jogo da hashtable, apagando o no' correspondente */
void HTjg_apaga(HT_jg jogos, char* nome, Jogo jogo, int max) {
    int i = hash(nome, max);
    jogos[i] = apaga_jg_lista(jogos[i], jogo);
}



/* Recebe a cabeca de uma lista liga da que guarda jogos e um jogo e devolve a cabeca da mesma
lista, apagando o no' que contem esse jogo */
link_jg apaga_jg_lista(link_jg head, Jogo jogo) {
    link_jg t, ant;

    /* Para cada no' da lista */
    for (t=head, ant = NULL; t != NULL; ant = t, t = t->prox) {
        if (t->jogo == jogo) {

            if (t == head)
                head = t->prox;
            
            else
                ant->prox = t->prox;

            free(t);
            break;
        }
    }
    return head;
}



/* Recebe uma hashtable de jogos e o seu numero de divisoes e apaga a hashtable e todos os jogos
que esta guarda */
void HTjg_termina(HT_jg jogos, int max) {
    int i;
    link_jg link, prox;

    /* Para cada no' de cada posicao da hashtable */
    for (i=0; i< max; i++) {
        for (link=jogos[i]; link != NULL; link = prox) {
            prox = link->prox;
            apaga_jogo(link->jogo);
            free(link);
        }     
    }
    free(jogos);
}