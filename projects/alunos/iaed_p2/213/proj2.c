#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "cmds.h"


/* Inicializa estruturas */
void init(System system) {
	system->teams = T_init(SIZE_HT);
	system->games = G_init(SIZE_HT);
	system->games_dl = mk_list();
}


/* Destroi estruturas */
void destroy(System system) {
	dll_destroy(system->games_dl);
	G_destroy(system->games);
	T_destroy(system->teams);
	free(system);
}


/* Le o espaco em branco */
char rd_ws() {
    int w = getchar();
    if (w != ' ' && w != '\n' && w != EOF)
        puts("whitespace expected");
    return w;
}


/* Lida com os comandos dados pelo terminal */
int main() {
	int cmd; 		/* Comando recebido pelo terminal */
	long c = 1;		/* Contador de comandos */

	/* Sistema */
	System system = can_fail_malloc(sizeof(struct system_struct));

	init(system);		/* Inicializa estruturas */

	/* Lida com os inputs do terminal */
	while ((cmd = getchar()) != 'x') {
		switch(cmd) {
			case 'a': cmd_a(c, system); break;

			case 'A': cmd_A(c, system); break; 

			case 'l': cmd_l(c, system); break;

			case 'p': cmd_p(c, system); break;

			case 'P': cmd_P(c, system); break;

			case 'r': cmd_r(c, system); break;

			case 's': cmd_s(c, system); break;

			case 'g': cmd_g(c, system); break;
		}
		/* Incrementa contador e le espaco em branco */
		c++;
		rd_ws();
	}

	/* Liberta memoria */
	destroy(system);

	return 0;
}
