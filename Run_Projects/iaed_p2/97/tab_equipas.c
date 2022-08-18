#include <stdlib.h>
#include "tab_equipas.h"
#include "hash.h"

elem_eq** incializa_tabela_equipa() {
    int i;
    elem_eq **equipas = malloc(TAB_EQUIPA * sizeof(equipa*));
    /* Cria uma lista de listas de equipas */
    for (i = 0; i < TAB_EQUIPA; i++) {
        equipas[i] = inicializa_lista_equipa();
    }
    /* Retorna a lista atualizada */
    return equipas;
}

elem_eq* encontra_equipa_tabela(elem_eq **tab_eqs, char *nome) {
    /* Calcula o lugar onde estara o elemento */
    int h = hash(nome, TAB_EQUIPA);
    /* Retorna o elemento */
    return encontra_equipa_lista(tab_eqs[h], nome);
}

elem_eq** insere_equipa_tabela(elem_eq **tab_eqs, Item_eq *e) {
    /* Calcula o lugar onde o elemento ira ficar */
    int h = hash(nome_equipa(e), TAB_EQUIPA);
    /* Adiciona na lista o elemento */
    tab_eqs[h] = adiciona_equipa_lista(tab_eqs[h], e);
    /* Retorna a tabela resultante */
    return tab_eqs;
}

void apaga_tabela_equipas(elem_eq **tab_eqs) {
    int i;
    /* Apaga toda a memoria associada a listas e aos jogos nelas */
    for (i = 0; i < TAB_EQUIPA; i++) {
        apaga_lista_equipas(tab_eqs[i]);
    }
    free(tab_eqs);
}

elem_eq* equipas_vencedoras(elem_eq **tab_eqs, int *maior) {
    int i;
    elem_eq *aux, *melhores = NULL;
    Item_eq *tmp;
    for (i = 0; i < TAB_EQUIPA; i++) {
        /* Percorrer cada lista de equipas */
        aux = tab_eqs[i];
        while (aux != NULL) {
            tmp = acede_equipa(aux);
            if (ganhos_equipa(tmp) > *maior) {
                /* Altera o valor de maior, e volta a popular melhores */
                *maior = ganhos_equipa(tmp);
                melhores = liberta_lista_equipas(melhores);
                melhores = adiciona_equipa_lista(melhores, tmp);
            } else if (ganhos_equipa(tmp) == *maior) {
                /* Adiciona a equipa a melhores */
                melhores = adiciona_equipa_lista(melhores, tmp);
            }
            aux = prox_equipa(aux);
        }
    }
    /* Retorna a lista de equipas vencedoras */
    return melhores;
}