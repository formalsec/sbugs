#ifndef EQUIPAS_H
#define EQUIPAS_H


typedef struct equipa {
	char *nome;
	int num_vitorias;
} equipa;



/* cria dinamicamente uma equipa */
/* input: nome da equipa */
/* output: ponteiro para a nova equipa */
equipa* nova_equipa(char nome_input[]);


/* liberta a memoria alocada por uma equipa */
/* input: ponteiro para a equipa a libertar */
void liberta_equipa(equipa *pt_equipa);

#endif