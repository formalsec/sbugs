#ifndef EQUIPAS_H
#define EQUIPAS_H

/* Estrutura para guardar cada equipa adicionada ao sistema.
 * Contem o seu nome, o numero de vitorias e dois ponteiros
 * para a equipa seguinte na hashtable e na lista ligada. */
typedef struct node_equipa {
    char *nome_equipa;
    int vitorias;
    struct node_equipa *next_ht, *next_lista;
} *link_equipa;


/* Estrutura que representa a lista ligada dos jogos */
typedef struct {
    struct node_equipa *primeiro;
} lista_equipas;

link_equipa *inicializa_ht_equipas();
lista_equipas *inicializa_lista_equipas();
link_equipa nova_equipa(char *nome_equipa);
void adiciona_equipa_lista(link_equipa equipa, lista_equipas *lista);
void adiciona_equipa_ht(link_equipa equipa, link_equipa *ht);
link_equipa procura_equipa(char *nome_equipa, link_equipa *ht);
int encontra_max_vit(lista_equipas *lista);
void print_g(int NL, int max_vit, lista_equipas *lista);
void destroi_estrut_equipas(lista_equipas *lista, link_equipa *ht);
int hash(char *v);
#endif
