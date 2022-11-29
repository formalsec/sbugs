#ifndef JOGOS_H
#define JOGOS_H


typedef struct jogo_strct {
	char *nome;
	equipa *equipa_1;
	equipa *equipa_2;
	int resultado_1;
	int resultado_2;
	struct jogo_strct *anterior, *seguinte;
} jogo;

typedef struct lista_jogos {
	jogo *jogo_inicial, *jogo_final;
} lista_jogos;



/* cria dinamicamente uma lista de jogos */
/* output: nova lista de jogos criada */
lista_jogos* cria_lista_jogos();


/* cria dinamicamente um jogo */
/* input: nome do jogo
		  ponteiro para a equipa 1
		  ponteiro para a equipa 2
		  valor do numero de golos da equipa 1
		  valor do numero de golos da equipa 2 */
/* output: ponteiro para o novo jogo */
jogo* novo_jogo(char nome_input[], equipa *equipa_1, equipa *equipa_2, int reslt_1, int reslt_2);


/* liberta a memoria alocada por um jogo */
/* input: ponteiro para o jogo a libertar */
void liberta_jogo(jogo *jogo);


/* altera os valores do resultado no jogo, e atualiza o numero de vitorias das*/
/* equipas que o caracterizam */
/* input: ponteiro para o jogo a alterar
		  valor do novo numero de golos da equipa 1
		  valor do novo numero de golos da equipa 2 */
void altera_resultados_jogo(jogo *jogo, int novo_reslt_1, int novo_reslt_2);

#endif
