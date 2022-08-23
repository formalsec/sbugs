#include <stdlib.h>
#include "tab_jogos.h"
#include "hash.h"

lista** incializa_tabela_jogo() {
    int i;
    lista **jogos = malloc(TAB_JOGO * sizeof(lista*));
    /* Cria uma lista de listas de jogos */
    for (i = 0; i < TAB_JOGO; i++) {
        jogos[i] = cria_lista_jogos();
    }
    /* Retorna a lista atualizada */
    return jogos;
}

elem_j* encontra_jogo_tabela(lista **tab_jogos, char *nome) {
    /* Calcula o lugar onde estara o elemento */
    int h = hash(nome, TAB_JOGO);
    /* Retorna o elemento */
    return encontra_jogo_lista(tab_jogos[h], nome);
}

lista** insere_jogo_tabela(lista **tab_jogos, Item_j *el) {
    /* Calcula o lugar onde o elemento ira ficar */
    int h = hash(nome_jogo(el), TAB_JOGO);
    /* Adiciona na lista o elemento */
    adiciona_jogo_lista(tab_jogos[h], el);
    /* Retorna a tabela resultante */
    return tab_jogos;
}

lista** remove_jogo_tabela(lista **tab_jogos, elem_j *el) {
    /* Calcula o lugar onde o elemento deve estar */
    Item_j *aux = acede_jogo(el);
    int h = hash(nome_jogo(aux), TAB_JOGO);
    /* Remove o elemento da lista */
    remove_jogo_lista(tab_jogos[h], el);
    /* Retorna a tabela resultante */
    return tab_jogos;
}

void apaga_tabela_jogos(lista **tab_jogos) {
    int i;
    /* Apaga toda a memoria associada a listas e aos jogos nelas */
    for (i = 0; i < TAB_JOGO; i++) {
        apaga_lista_jogos(tab_jogos[i]);
    }
    free(tab_jogos);
}