#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sistema.h"
#include "lista.h"
#include "tabela_team.h"
#include "tabela_jogo.h"


Sistema *init_sistema(){
	Sistema *new = can_fail_malloc(sizeof(Sistema));
	new->tabela_jogos = init();
	new->tabela_teams = init_t();
	new->lista= NULL;
	return new;
}


void liberta_sistema(Sistema *s){
	liberta_table(s->tabela_jogos);
	liberta_table_t(s->tabela_teams);
	free_list_jogos(s->lista);
	free(s);
}

