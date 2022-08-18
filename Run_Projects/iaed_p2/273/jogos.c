#include <string.h>
#include <stdlib.h>

#include "equipas.h"
#include "jogos.h"


/* cria dinamicamente uma lista de jogos */
lista_jogos* cria_lista_jogos() {
	lista_jogos *lista = malloc(sizeof(lista_jogos));
	lista->jogo_inicial = lista->jogo_final = NULL;
	return lista;
}


/* cria dinamicamente um jogo */
jogo* novo_jogo(char nome_input[], equipa *equipa_1, equipa *equipa_2, int reslt_1, int reslt_2) {
	jogo *novo_jogo;
	novo_jogo = malloc(sizeof(jogo));
	novo_jogo->nome = malloc(sizeof(char)*strlen(nome_input)+1);
	strcpy(novo_jogo->nome, nome_input);
	novo_jogo->equipa_1 = equipa_1;
	novo_jogo->equipa_2 = equipa_2;
	novo_jogo->resultado_1 = reslt_1;
	novo_jogo->resultado_2 = reslt_2;
	novo_jogo->anterior = NULL;
	novo_jogo->seguinte = NULL;
	return novo_jogo;
}




/* liberta a memoria alocada por um jogo */
void liberta_jogo(jogo *jogo) {
	free(jogo->nome);
	free(jogo);
}



/* altera os valores do resultado no jogo, e atualiza o numero de vitorias das*/
/* equipas que o caracterizam */
void altera_resultados_jogo(jogo *jogo, int novo_reslt_1, int novo_reslt_2) {
	if (jogo->resultado_1 > jogo->resultado_2) { /* analisa valores ja guardados */
		if (novo_reslt_2 > novo_reslt_1) { /* analisa novo resultado */
			jogo->equipa_1->num_vitorias--; /* a vitoria agora e da equipa 2 */
			jogo->equipa_2->num_vitorias++;
		}
		else if (novo_reslt_1 == novo_reslt_2) {
			jogo->equipa_1->num_vitorias--; /* empate, nenhuma equipa ganha */
		}
	}
	else if (jogo->resultado_2 > jogo->resultado_1) {
		if (novo_reslt_1 > novo_reslt_2) {
			jogo->equipa_2->num_vitorias--; /* a vitoria e agora da equipa 1 */
			jogo->equipa_1->num_vitorias++;
		}
		else if (novo_reslt_1 == novo_reslt_2) {
			jogo->equipa_2->num_vitorias--; /* empate, nenhuma equipa ganha */
		}
	}
	else if (jogo->resultado_1 == jogo->resultado_2) {
		if (novo_reslt_1 > novo_reslt_2) {
			jogo->equipa_1->num_vitorias++;  /* a vitoria e agora da equipa 1 */
		}
		else if (novo_reslt_2 > novo_reslt_1) {
			jogo->equipa_2->num_vitorias++; /* a vitoria e agora da equipa 1 */
		}
	}
	jogo->resultado_1 = novo_reslt_1; /* atualiza novos valores dos resultados no jogo */
	jogo->resultado_2 = novo_reslt_2;
}
