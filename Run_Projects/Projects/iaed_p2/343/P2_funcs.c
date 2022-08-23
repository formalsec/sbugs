#include "funcs.h"

/*Funcao auxiliar que subtrai as vitorias de uma equipa 
  quando o score do jogo e mudado ou eliminado*/
void sub_score(jg *jogo){
	if (jogo->scr1 > jogo->scr2)
		jogo->eq1->vitorias--;
	else if (jogo->scr1 < jogo->scr2)
		jogo->eq2->vitorias--;
}

/* Funcao que realiza o comando a */
void acommand(int nl, node_jg *table_jg, node_eq *table_eq, link *lista){
	char nome[MDES], eq1[MDES], eq2[MDES];
	int sc1, sc2, i;
	jg *njogo;
	eq *equipa1, *equipa2;
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d\n", nome, eq1, eq2, &sc1, &sc2);
	i = f_hash(nome);
	equipa1 = search_eq(table_eq[f_hash(eq1)], eq1);
	equipa2 = search_eq(table_eq[f_hash(eq2)], eq2);
	if (search_jg(table_jg[i], nome) != NULL)
		printf("%d Jogo existente.\n", nl);
	else if (equipa1 == NULL || equipa2 == NULL)
		printf("%d Equipa inexistente.\n", nl);
	else{
		njogo = malloc(sizeof(jg));
		njogo->nome = malloc(sizeof(char) * (strlen(nome) + 1));
		strcpy(njogo->nome, nome);
		njogo->eq1 = equipa1;
		njogo->eq2 = equipa2;
		njogo->scr1 = sc1;
		njogo->scr2 = sc2;
		table_jg[i] = push_jg(table_jg[i], njogo);
		if (sc1 > sc2)
			equipa1->vitorias++;
		else if (sc1 < sc2)
			equipa2->vitorias++;
		push_lista(lista, njogo);
	}
}

/* Funcao que realiza o comando A */
void Acommand(int nl, node_eq *table_eq, node_eq *lista_eq){
	char dest[MDES];
	int i;
	eq *nequipa;
	scanf(" %[^:\n]\n", dest);
	i = f_hash(dest);
	if (search_eq(table_eq[i], dest) != NULL)
		printf("%d Equipa existente.\n", nl);
	else{
		nequipa = malloc(sizeof(eq));
		nequipa->des = malloc(sizeof(char) * (strlen(dest) + 1));
		strcpy(nequipa->des, dest);
		nequipa->vitorias = 0;
		table_eq[i] = push_eq(table_eq[i], nequipa);
		lista_eq[0] = push_eq(lista_eq[0], nequipa);
	}
}

/* Funcao que realiza o comando g */
void gcommand(int nl, node_eq *lista_eq){
	int max = 0, cont = 0, i = 0;
	node_eq atual;
	eq **lista;
	getchar();
	if (lista_eq[0] != NULL){
		for (atual = lista_eq[0]; atual != NULL; atual = atual->next){
			if (max < atual->equipa->vitorias){
				max = atual->equipa->vitorias;
				cont = 1;
			}
			else if (max == atual->equipa->vitorias)
				cont++;
		}
		lista = malloc(sizeof(eq*) * cont);
		for (atual = lista_eq[0]; atual != NULL; atual = atual->next){
			if (max == atual->equipa->vitorias)
				lista[i++] = atual->equipa;
		}
		quicksort(lista, 0, cont - 1);
		printf("%d Melhores %d\n", nl, max);
		for (i = 0; i < cont; i++)
			printf("%d * %s\n", nl, lista[i]->des);
		free(lista);
	}
}

/* Funcao que realiza o comando l */
void lcommand(int nl, link *lista){
	node_jg temp;
	getchar();
	for (temp = lista->head; temp != NULL; temp = temp->next)
		printf("%d %s %s %s %d %d\n", nl, temp->jogo->nome, temp->jogo->eq1->des, temp->jogo->eq2->des, temp->jogo->scr1, temp->jogo->scr2);
}

/* Funcao que realiza o comando p */
void pcommand(int nl, node_jg *table_jg){
	char nome[MDES];
	jg *jogo;
	getchar();
	scanf("%[^:\n]\n", nome);
	jogo = search_jg(table_jg[f_hash(nome)], nome);
	if (jogo == NULL)
		printf("%d Jogo inexistente.\n", nl);
	else
		printf("%d %s %s %s %d %d\n", nl, jogo->nome, jogo->eq1->des, jogo->eq2->des, jogo->scr1, jogo->scr2);
}

/* Funcao que realiza o comando P */
void Pcommand(int nl, node_eq *table_eq){
	char dest[MDES];
	eq *ver;
	scanf(" %[^:\n]\n", dest);
	ver = search_eq(table_eq[f_hash(dest)], dest);
	if (ver != NULL)
		printf("%d %s %d\n", nl, ver->des, ver->vitorias);
	else
		printf("%d Equipa inexistente.\n", nl);
}

/* Funcao que realiza o comando r */
void rcommand(int nl, node_jg *table_jg, link *lista){
	char nome[MDES];
	int i;
	jg *jogo;
	scanf(" %[^:\n]\n", nome);
	i = f_hash(nome);
	jogo = search_jg(table_jg[i], nome);
	if (jogo == NULL)
		printf("%d Jogo inexistente.\n", nl);
	else{
		/* Remove a vitoria, depois remove o jogo da hash_table e da lista para o comando l e da free na memoria */
		sub_score(jogo);
		remove_lista(lista, jogo);
		table_jg[i] = remove_jg(table_jg[i], jogo);
		free(jogo->nome);
		free(jogo);
	}
}

/* Funcao que realiza o comando s */
void scommand(int nl, node_jg *table_jg){
	char nome[MDES];
	jg *jogo;
	int sc1, sc2;
	scanf(" %[^:\n]:%d:%d\n", nome, &sc1, &sc2);
	jogo = search_jg(table_jg[f_hash(nome)], nome);
	if (jogo == NULL)
		printf("%d Jogo inexistente.\n", nl);
	else{
		sub_score(jogo);
		jogo->scr1 = sc1;
		jogo->scr2 = sc2;
		if (sc1 > sc2)
			jogo->eq1->vitorias++;
		else if (sc1 < sc2)
			jogo->eq2->vitorias++;
	}
}

/* Funcao que liberta a memoria no final do programa */
void xcommand(node_eq *table_eq, node_eq *lista_eq, node_jg *table_jg, link *lista){
	int i;
	node_eq eq, eq_temp;
	node_jg jg, jg_temp;
	/* Ciclo que da free em ambas as hash_tables */
	for (i=0; i < DIVISOR; i++){
		if (table_eq[i] != NULL){
			/* Ciclo que da free em todos os nos de equipas e equipas de indice i da tabela */
			for (eq = table_eq[i]; eq != NULL; eq = eq_temp){
				eq_temp = eq->next;
				free(eq->equipa->des);
				free(eq->equipa);
				free(eq);
			}
		}
		if (table_jg[i] != NULL){
			/* Ciclo que da free em todos os nos de jogos e jogos de indice i da tabela */
			for (jg = table_jg[i]; jg != NULL; jg = jg_temp){
				jg_temp = jg->next;
				free(jg->jogo->nome);
				free(jg->jogo);
				free(jg);
			}
		}
	}
	/* Da free nas hash_tables */
	free(table_eq);
	free(table_jg);
	/* Ciclo que da free em todos os nos da lista do comando g */
	for (eq = lista_eq[0]; eq != NULL; eq = eq_temp){
		eq_temp = eq->next;
		free(eq);
	}
	free(lista_eq);
	/* Ciclo que da free em todos os nos da lista do comando l */
	for (jg = lista->head; jg != NULL; jg = jg_temp){
		jg_temp = jg->next;
		free(jg);
	}
	free(lista);
}