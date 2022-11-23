#ifndef SISTEMA_H
#define SISTEMA_H

/* Estrutura das equipas */
typedef struct lista {
	int ordem_entrada;
	int numero_jogos_ganhos;
	char *nome_equipa;
	struct lista *proximo;
} *equipa;

/* Estrutura de um jogo */
typedef struct fila {
	int ordem_entrada_jogo;
	char *equipa1;
	char *equipa2;
	int pontos_1;
	int pontos_2;
	char *nome_jogo;
	struct fila *proximo;
} *jogo;


/* Estrutura para o podio */
typedef struct pilha {
	char *nome_equipa_podio;
	struct pilha *proximo;
} *podio;

#endif

