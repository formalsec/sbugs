#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "jogos.h"
#include "common.h"

TabelaJogos *inicia_tabela_jogos(int capacidade) {
    int i;
    TabelaJogos *tabela = can_fail_malloc(sizeof(TabelaJogos));
    tabela->capacidade = capacidade * 2;
    tabela->tamanho = 0;
    tabela->jogos = can_fail_malloc(sizeof(Jogo*) * tabela->capacidade);
    tabela->first = NULL;
    tabela->last = NULL;

    for (i = 0; i < tabela->capacidade; i++)
        tabela->jogos[i] = NULL;
        
    return tabela;
}

void expandir_jogos(TabelaJogos *tabela);
void inserir_jogo(TabelaJogos *tabela, Jogo *jogo) {
    struct node *no;
    int i = hash(jogo->nome, tabela->capacidade);
    while (tabela->jogos[i] != NULL)
        i = (i + 1) % tabela->capacidade;
    tabela->jogos[i] = jogo;

    no = can_fail_malloc(sizeof(struct node));
    no->v = jogo;
    no->next = NULL;
    no->prev = tabela->last;

    if (tabela->first == NULL) {
        tabela->first = no;
        tabela->last = no;
    } else {
        tabela->last->next = no;
        tabela->last = no;
    }

    tabela->tamanho++;
    if (tabela->tamanho > tabela->capacidade / 2)
        expandir_jogos(tabela);
}

void expandir_jogos(TabelaJogos *tabela) {
    int i;
    TabelaJogos *tab = inicia_tabela_jogos(tabela->capacidade * 2);

    for (i = 0; i < tabela->capacidade; i++) {
        if (tabela->jogos[i] != NULL) {
            inserir_jogo(tab, tabela->jogos[i]);
        }
    }

    free(tabela->jogos);
    tabela->jogos = tab->jogos;
    tabela->capacidade = tab->capacidade;
    tabela->tamanho = tab->tamanho;
    free(tab);
}

Jogo *procura_jogo(TabelaJogos *tabela, char *nome) {
    int i = hash(nome, tabela->capacidade);

    while (tabela->jogos[i] != NULL) {
        if (strcmp(tabela->jogos[i]->nome, nome) == 0) {
            return tabela->jogos[i];
        } else {
            i = (i + 1) % tabela->capacidade;
        }
    }
    
    return NULL;
}

void apagar_jogo(TabelaJogos *tabela, char *nome) {
    int j, i = hash(nome, tabela->capacidade);
    struct node *no = tabela->first;

    while (tabela->jogos[i] != NULL) {
        if (strcmp(tabela->jogos[i]->nome, nome) == 0) {
            break;
        } else {
            i = (i + 1) % tabela->capacidade;
        }
    }
    if (tabela->jogos[i] == NULL) return;
    tabela->tamanho--;

    while (no->v != tabela->jogos[i]) {
        no = no->next;
    }

    no->v = NULL;
    free_jogo(tabela->jogos[i]);
    tabela->jogos[i] = NULL;
    for (j = (i+1) % tabela->capacidade; tabela->jogos[j] != NULL; j = (j + 1) % tabela->capacidade) {
        tabela->jogos[i] = tabela->jogos[j];
        tabela->jogos[j] = NULL;
        i++;
    }
}

void free_tabela_jogos(TabelaJogos *tabela) {
    int i;
    struct node *no = tabela->first;

    for (i = 0; i < tabela->capacidade; i++) {
        if (tabela->jogos[i] != NULL) {
            free_jogo(tabela->jogos[i]);
        }
    }

    while (no != NULL) {
        struct node *t = no;
        no = no->next;
        free(t);
    }

    free(tabela->jogos);
    free(tabela);
}
