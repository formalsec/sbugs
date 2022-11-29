#ifndef EQUIPA_H
#define EQUIPA_H

/* Definicao das Estruturas */

typedef struct equipa {
    char *nome;
    int vitorias;
} *ptrEquipa; /* ptrEquipa e' um ponteiro para uma equipa */

/* Prototipos das Funcoes */

/* Cria uma nova equipa, devolvendo um ponteiro para a mesma */
ptrEquipa criar_equipa(char *nome);
/* Recebe uma equipa e liberta a memoria a ela associada */
void eliminar_equipa(ptrEquipa equipa);

#endif