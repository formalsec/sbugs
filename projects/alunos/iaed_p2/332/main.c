#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"
#include "hash_equipas.h"
#include "jogos.h"
#include "hash_jogos.h"



int main() {

	/* instrucao a ser recebida */
	char comando;
	/* indicador do numero de linhas de input */
	int nl = 1;

	/* inicializacao das hash tables de equipas e de jogos */
	equipa * ht_eq = init_tab_equipas();
	jogo * ht_jg = init_tab_jogos();

	while ((comando = getchar()) != 'x') {
		switch(comando) {
		 case 'a':
		 	/* adiciona um novo jogo */
		 	adiciona_jogo(nl, ht_jg, ht_eq);
		 	nl += 1;
		 	break;
		 case 'A':
		 	/* adiciona uma nova equipa */
		 	adiciona_equipa(nl, ht_eq);
		 	nl += 1;
		 	break;
		 case 'l':
		 	/* lista todos os jogos pela ordem em que foram introduzidos */
		 	lista_jogos(nl, ht_jg);
		 	nl += 1;
		 	break;
		 case 'p':
		 	/* procura um jogo */
		 	encontra_jogo(nl, ht_jg);
		 	nl += 1;
		 	break;
		 case 'P':
		 	/* procura uma equipa */
		 	encontra_equipa(nl, ht_eq);
		 	nl += 1;
		 	break;
		 case 'r':
		 	/* apaga um jogo */
		 	apaga_jogo(nl, ht_jg, ht_eq);
		 	nl += 1;
		 	break;
		 case 's':
		 	/* altera a pontuacao/score de um jogo */
		 	altera_score(nl, ht_jg, ht_eq);
		 	nl += 1;
		 	break;
		 case 'g':
		 	/* encontra as equipas que venceram mais jogos */
		 	melhores_equipas(nl, ht_eq);
		 	nl += 1;
		 	break;
		}
		getchar();
	}
	free_tabela_eq(ht_eq);
	free(ht_eq);
	free_tabela_jg(ht_jg);
	free(ht_jg);

	return 0;
}