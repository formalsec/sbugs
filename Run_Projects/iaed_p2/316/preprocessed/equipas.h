#ifndef EQUIPAS_H
#define EQUIPAS_H

/* Estrutura de um node de uma lista simplesmente ligada que representa uma equipa. */
typedef struct node_struct_equipas {
    struct node_struct_equipas *next; /* Node seguinte. */
    char *nome;                       /* Nome da equipa. */
    int jogos_ganhos;                 /* Numero de jogos ganhos pela equipa. */

} node_equipas;

/* Estrutura de uma lista simplesmente ligada que representa todas as equipas. */
typedef struct {
    node_equipas *head; /* Primeira equipa da lista. */

} Equipas;

Equipas *init_equipas();         /* Inicializa as equipas. */
void destroy_equipas(Equipas *); /* Liberta a memoria associada as equipas. */

node_equipas *cria_equipa(char *);                  /* Inicializa uma equipa. */
Equipas *push_equipa(Equipas *, node_equipas *);    /* Adiciona uma equipa. */
void equipa_vencedora(node_equipas *);              /* Incrementa os jogos ganhos. */
void equipa_diminui_jogos_ganhos(node_equipas *);   /* Decrementa os jogos ganhos. */
node_equipas **melhores_equipas(Equipas *, long *); /* Devolve as melhores equipas. */
void destroy_melhores(node_equipas **); /* Liberta a memoria associada as melhores equipas. */

#endif
