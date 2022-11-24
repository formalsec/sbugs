#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "funcoes.h"

int main() {
	int exe, i;
	PRINCIPAL p;
	p = can_fail_malloc(sizeof(struct principal));
	p = init_stPrincipal(p);		/* Inicializa a estrutura principal e seus componentes*/
	exe = get_comando(p);
	
	/* Continua a pedir um novo comando ate receber a instrucao para terminar: x */
	while (exe == 1) {
		exe = get_comando(p);
		
	}


	/* Liberta a memoria das estruturas de dados criadas */
	freeList(p->lista_jogos);

	for (i = 0; i < p->cap_jogos; i++) {
		if (p->hashJogo[i] != NULL) {
			free(p->hashJogo[i]->nome);
			free(p->hashJogo[i]->equipa1);
			free(p->hashJogo[i]->equipa2);
			free(p->hashJogo[i]);
			p->hashJogo[i] = NULL;
		}
	}

	free(p->hashJogo);
	p->hashJogo = NULL;
	for (i = 0; i < p->cap_equipas; i++) {
		if (p->hashEquipa[i] != NULL) {
			free(p->hashEquipa[i]->nome);
			free(p->hashEquipa[i]);
			p->hashEquipa[i] = NULL;
		}
	}
	free(p->hashEquipa);
	free(p->lista_equipas);
	free(p);
	return 0;
}

