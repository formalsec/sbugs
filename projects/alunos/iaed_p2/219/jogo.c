#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include "jogo.h"

jogo *cria_jogo(){
	jogo *novo_jogo = can_fail_malloc(sizeof(jogo)+1);
	novo_jogo -> nome = NULL;
	novo_jogo -> equipa1 = NULL;
	novo_jogo -> equipa2 = NULL;
	novo_jogo -> score1 = NULL;
	novo_jogo -> score2 = NULL;
	return novo_jogo;
}

lista_jogos *cria_lista_jogos(){
	lista_jogos *nova_lista = can_fail_malloc(sizeof(lista_jogos));
	nova_lista -> head = nova_lista -> last = NULL;
	return nova_lista;
}

void free_jogo(jogo *jg){
	free(jg -> nome);
	free(jg -> equipa1);
	free(jg -> equipa2);
	free(jg -> score1);
	free(jg -> score2);
	free(jg);

}

void preenche_jogo(jogo *jg, char* nome, char *equipa1, char *equipa2, char *score1, char *score2){
	jg -> nome = can_fail_malloc(sizeof(char) * strlen(nome)+1);
	jg -> equipa1 = can_fail_malloc(sizeof(char) * strlen(equipa1)+1);
	jg -> equipa2 = can_fail_malloc(sizeof(char) * strlen(equipa2)+1);
	jg -> score1 = can_fail_malloc(sizeof(char) * strlen(score1)+1);
	jg -> score2 = can_fail_malloc(sizeof(char) * strlen(score2)+1);
	strcpy(jg -> nome, nome);
	strcpy(jg -> equipa1, equipa1);
	strcpy(jg -> equipa2, equipa2);
	strcpy(jg -> score1, score1);
	strcpy(jg -> score2, score2);
}


/*O jogo e adicionado ao inicio da lista*/
void adiciona_jogo(jogo *jg, lista_jogos *l_jogos){
	jogo *old_first;
	if(l_jogos -> head == NULL){
		l_jogos -> head = jg;
		jg -> jogo_anterior = NULL;
		jg -> jogo_seguinte = NULL;
		l_jogos -> last = jg;
	}
	else{
		old_first = l_jogos -> head;
		old_first -> jogo_anterior = jg;
		jg -> jogo_seguinte = old_first;
		jg-> jogo_anterior = NULL;
		l_jogos -> head = jg;
	}
	l_jogos -> num_jogos ++;
}

void retira_jogo(lista_jogos *l_jogos, jogo *jg){
	if(jg -> jogo_anterior == NULL){
		l_jogos -> head = jg -> jogo_seguinte;
	}else{
		jg -> jogo_anterior -> jogo_seguinte = jg ->jogo_seguinte;
	}
	if(jg -> jogo_seguinte == NULL){
		l_jogos -> last = jg -> jogo_anterior;
	}
	else{
		jg -> jogo_seguinte -> jogo_seguinte = jg -> jogo_anterior;
	}
}

void free_jogos(lista_jogos *l_jogos){
	while (l_jogos -> head){
		jogo *auxjogo = l_jogos -> head -> jogo_seguinte;
		free_jogo(l_jogos -> head);
		l_jogos -> head = auxjogo;
	}
	free(l_jogos);
}

