#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"

#define MAX_CMD_SZ 2500


/* Recebe input do stdin no formato de <comando> <args>* */
int get_comando(PRINCIPAL p) {
	char *comando, *cmd_temp;
	int exit;
	cmd_temp = can_fail_malloc(sizeof(char)*3200);
	fgets(cmd_temp, sizeof(char)*3200, stdin);
	/* Se for introduzido um comando que tem argumentos */
	if (cmd_temp[0] != 'g' && cmd_temp[0] != 'l' && cmd_temp[0] != 'x') {
		/* separa o comando dos argumentos e executa o comando */
		comando = strdup(cmd_temp);
		comando = comando + 2;
		exit = exe_comando(cmd_temp[0], comando, p);
		comando = comando - 2;
		free(comando);
		free(cmd_temp);
	    return exit;
	}
	/* Se for introduzido um comando que NAO tem argumentos */
	else {
		exit = exe_comando(cmd_temp[0], " ", p);
		free(cmd_temp);
		return exit;
	}
}


/* Executa o comando de acordo com a acao escolhida */
int exe_comando(char action, char *args, PRINCIPAL p) {
	JOGO j;
	char *nome, *equipa1, *equipa2;
	int score1, score2;
	int len=strlen(args);
	p->input_contador++;
	switch(action) {

		/* Adiciona um novo jogo */
		case 'a':
			j = (JOGO) can_fail_malloc(sizeof(struct jogo));
			nome = can_fail_malloc(sizeof(char)*(len+1));
			equipa1 = can_fail_malloc(sizeof(char)*(len+1));
			equipa2 = can_fail_malloc(sizeof(char)*(len+1));
			sscanf(args, "%[^:]:%[^:]:%[^:]:%d:%d", nome, equipa1, equipa2, &score1, &score2);
			j->nome = strdup(nome);
			j->equipa1 = strdup(equipa1);
			j->equipa2 = strdup(equipa2);
			j->score1 = score1;
			j->score2 = score2;
			adiciona_jogo(j, p);
			free(j->nome);
			free(j->equipa1);
			free(j->equipa2);
			free(nome);
			free(equipa1);
			free(equipa2);
			free(j);
			return 1;

		/* Adiciona uma nova equipa */
		case 'A':
			nome = can_fail_malloc(sizeof(char)*(len+1));
			sscanf(args, "%[^\n]", nome);
			adiciona_equipa_cmd(nome, p);
			free(nome);
			return 1;

		/* Lista todos os jogos introduzidos */
		case 'l':
			lista_jogos(p);
			return 1;

		/* Procura um jogo com o nome dado */
		case 'p':
			nome = can_fail_malloc(sizeof(char)*(len+1));
			sscanf(args, "%[^\n]", nome);
			procura_jogo_cmd(nome, p);
			free(nome);
			return 1;

		/* Procura uma equipa dado um nome */
		case 'P':
			nome = can_fail_malloc(sizeof(char)*(len+1));
			sscanf(args, "%[^\n]", nome);
			procura_equipa_cmd(nome, p);
			free(nome);
			nome = NULL;
			return 1;

		/* Apaga um jogo dado um nome */
		case 'r':
			nome = can_fail_malloc(sizeof(char)*(len+1));
			sscanf(args, "%[^\n]", nome);
			remove_jogo_cmd(nome, p);
			free(nome);
			return 1;

		/* Altera o score de um jogo dado o nome */
		case 's':
			nome = can_fail_malloc(sizeof(char)*(len+1));
			sscanf(args, "%[^:\n]:%d:%d", nome, &score1, &score2);
			altera_score_cmd(nome, score1, score2, p);
			free(nome);
			return 1;

		/* Encontra as equipas que ganharam mais jogos e lista-as por ordem lexicografica */
		case 'g':
			lista_melhor_equipas(p);
			return 1;

		/* Termina o programa */
		case 'x':
			return 0;
		default:
			return 1;
	}
}




