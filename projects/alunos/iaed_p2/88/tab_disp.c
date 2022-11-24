#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "tab_disp.h"

/* cria uma nova tabela de dispersao vazia */
tab_disp nova_tab(int tamanho) {

    int i;
    tab_disp nova_tabela = (tab_disp) can_fail_malloc(sizeof(struct stru_tab));
    nova_tabela->tamanho = tamanho;

    nova_tabela->tab = (no **) can_fail_malloc(tamanho * sizeof(no *));

    for (i=0; i<tamanho; i++) {
        nova_tabela->tab[i] = NULL;
    }
    
    return nova_tabela;

}

/* insere um item na tabela */
void insere_tab(tab_disp t, void *item, void *(*chave)(void *), int (*disp)(void *, int)) {

    int i = (*disp)((*chave)(item), t->tamanho);
    t->tab[i] = insere(t->tab[i], item);

}

/* apaga o primeiro item da tabela compativel com a chave */
void retira_tab(tab_disp t, void *chave, int (*disp)(void *, int), int (*igual)(void*, void*),
                                                                         void (*liberta)(void *)) {

    int i = (*disp)(chave, t->tamanho);
    t->tab[i] = retira(t->tab[i], chave, igual, liberta);

}

/* procura um item na tabela e retorna-o se existir, caso contrario retorna NULL */
void* procura_tab(tab_disp t, void *chave, int (*disp)(void *, int), int (*igual)(void* , void*)) {

    int i = (*disp)(chave, t->tamanho);
    void *item;

    item = procura(t->tab[i], chave, igual);

    return item;

}

/* Liberta a memoria associada a tabela */
void liberta_tab(tab_disp t, void (*liberta_item)(void *)) {

    int i;

    for (i=0; i<t->tamanho; i++) {

        if(t->tab[i] != NULL) {
            liberta_lista(t->tab[i], liberta_item);
        }
    }

    free(t->tab);
    free(t);
}


