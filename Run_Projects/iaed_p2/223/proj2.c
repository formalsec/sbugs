#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "equipas.h"
#include "jogos.h"
#include "game_lists.h"
#include "team_lists.h"
#include "game_hashtable.h"
#include "team_hashtable.h"
#include "iteam_hashtable.h"
#include "sort.h"

#define TAMANHOHT 2000 /* tamanho da hash table */
#define MAXTEXT 1024 /* tamanho maximo da string que caracteriza um jogo ou equipa */

static glink listOrd;	/* lista que guarda os jogos pela ordem em que foram adicionados ao sistema */
static int nl = 1; /* inteiro correspondente ao numero de linha de input que produziu o output impresso */

/* funcao que apaga uma lista, apagando apenas os seus nos, nao os elementos para que apontam */
void apagaLista(glink l) {
	glink tmp;
	while (l != NULL) {
		tmp = l;
		l = l->next;
		free(tmp);
	}
}

/* funcao que define o comando a. adiciona um jogo ao sistema caso nao exista um jogo com
o mesmo nome e existam ambas as equipas que formam o jogo */
void a() {
	char *nome, *equipa1, *equipa2;
	int score1, score2;
	Jogo jogo;
	Equipa eq1, eq2;
	nome = malloc((sizeof(char))*MAXTEXT);
	equipa1 = malloc((sizeof(char))*MAXTEXT);
	equipa2 = malloc((sizeof(char))*MAXTEXT);
	getchar();
	scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);
	if (haJogo(nome) != 1) {
		if (haEquipa(equipa1) && haEquipa(equipa2)) {
			eq1 = Tsearch(equipa1);
			eq2 = Tsearch(equipa2);
			jogo = novoJogo(nome, eq1, eq2, score1, score2);
			Ginsert(jogo);
			listOrd = GinsertEnd(listOrd, jogo);
			if (score1 > score2) {		/* confirma-se qual a equipa vencedora para lhe acrescentar uma vitoria no sistema */
				iTdelete(eq1);
				aumentaVitorias(eq1);
				iTinsert(eq1);
			}
			if (score2 > score1) {
				iTdelete(eq2);
				aumentaVitorias(eq2);
				iTinsert(eq2);
			}
		}
		else {
			printf("%d Equipa inexistente.\n", nl);
		}
	}
	else {
		printf("%d Jogo existente.\n", nl);
	}
	free(nome);
	free(equipa1);
	free(equipa2);
}

/* funcao que define o comando A. adiciona uma equipa ao sistma caso nao haja uma equipa com o mesmo nome */
void A() {
	char *nome;
	Equipa equipa;
	nome = malloc((sizeof(char))*MAXTEXT);
	getchar();
	scanf("%[^:\n]", nome);
	if (haEquipa(nome) == 0) {
		equipa = novaEquipa(nome);
		Tinsert(equipa);
		iTinsert(equipa);
	}
	else {
		printf("%d Equipa existente.\n", nl);
	}
	free(nome);
}

/* funcao que define o comando l. imprime os jogos pela ordem em que foram introduzidos no sistema */
void l() {
	glink t;
	for (t = listOrd; t != NULL; t = t->next) {
		printf("%d ", nl);
		imprimeJogo(t->jogo);
	}
}

/* funcao que define o comando p. dado um nome, procura o jogo que lhe corresponde, imprimindo as suas caracteristias caso exista*/
void p() {
	char *nome;
	Jogo jogo;
	nome = malloc((sizeof(char))*MAXTEXT);
	getchar();
	scanf("%[^:\n]", nome);
	if (haJogo(nome)) {
		jogo = Gsearch(nome);
		printf("%d ", nl);
		imprimeJogo(jogo);
	}
	else {
		printf("%d Jogo inexistente.\n", nl);
	}
	free(nome);
}

/* funcao que define o comando P. dado um nome, procura a equipa que lhe corresponde e, caso exista, imprime as suas caracteristicas */
void P() {
	char *nome;
	Equipa equipa;
	nome = malloc((sizeof(char))*MAXTEXT);
	getchar();
	scanf("%[^:\n]", nome);
	if (haEquipa(nome)) {
		equipa = Tsearch(nome);
		printf("%d ", nl);
		imprimeEquipa(equipa);
	}
	else {
		printf("%d Equipa inexistente.\n", nl);
	}
	free(nome);
}

/* funcao que define o comando r. caso exista um jogo com o nome dado, remove-o do sistema, processando
ainda as consequencias de tal acao, nomeadamente a alteracao do numero de vitorias das equipas envolvidas */
void r() {
	char *nome;
	Jogo jogo;
	Equipa e1, e2;
	int pont1, pont2;
	nome = malloc((sizeof(char))*MAXTEXT);
	getchar();
	scanf("%[^:\n]", nome);
	if (haJogo(nome)) {
		jogo = Gsearch(nome);
		pont1 = obtemPont(jogo, 1);
		pont2 = obtemPont(jogo, 2);
		e1 = obtemEquipa(jogo, 1);
		e2 = obtemEquipa(jogo, 2);
		if (pont1 > pont2) {
			iTdelete(e1);				/* apaga-se a equipa da hashtable que guarda as equipas pelo numero de vitorias */
			diminuiVitorias(e1);		/* altera-se o numero de vitorias da equipa */
			iTinsert(e1);				/* adiciona-se novamente a equipa, que agora ficara numa lista ligada diferente */
		}
		if (pont2 > pont1) {
				iTdelete(e2);
				diminuiVitorias(e2);
				iTinsert(e2);
		}
		Gdelete(jogo);
		listOrd = GremoveItem(listOrd, jogo, 1);		/* remove-se o jogo da lista ligada que guarda os jogos */
	}
	else {
		printf("%d Jogo inexistente.\n", nl);
	}
	free(nome);
}

/* funcao que define o comando s. caso haja um jogo com o nome dado, altera a sua pontuacao para os valores dados,
processando ainda todas as alteracoes consequentes, nomeadamente a alteracao do numero de vitorias das equipas envolvidas */
void s() {
	int score1, score2, s1, s2;
	char *nome;
	Jogo jogo;
	Equipa e1, e2;
	nome = malloc((sizeof(char))*MAXTEXT);
	getchar();
	scanf("%[^:\n]:%d:%d", nome, &score1, &score2);
	if (haJogo(nome)) {
		jogo = Gsearch(nome);
		s1 = obtemPont(jogo, 1);
		s2 = obtemPont(jogo, 2);
		e1 = obtemEquipa(jogo, 1);
		e2 = obtemEquipa(jogo, 2);
		if (s1 > s2) {
			if (score1 == score2) {
				iTdelete(e1);
				diminuiVitorias(e1);
				iTinsert(e1);
			}
			if (score1 < score2) {
				iTdelete(e1);
				diminuiVitorias(e1);
				iTinsert(e1);
				iTdelete(e2);
				aumentaVitorias(e2);
				iTinsert(e2);
			}
		}
		if (s2 > s1) {
			if (score1 == score2) {
				iTdelete(e2);
				diminuiVitorias(e2);
				iTinsert(e2);
			}
			if (score2 < score1) {
				iTdelete(e1);
				aumentaVitorias(e1);
				iTinsert(e1);
				iTdelete(e2);
				diminuiVitorias(e2);
				iTinsert(e2);
			}
		}
		if (s1 == s2) {
			if (score1 > score2) {
				iTdelete(e1);
				aumentaVitorias(e1);
				iTinsert(e1);
			}
			if (score1 < score2) {
				iTdelete(e2);
				aumentaVitorias(e2);
				iTinsert(e2);
			}
		}
		alteraPont(jogo, score1, score2);
	}
	else {
		printf("%d Jogo inexistente.\n", nl);
	}
	free(nome);
}

/* funcao que define o comando g. lista as equipas com maior numero de vitorias por ordem lexicografica */
void g() {
	tlink t, list;
	Equipa e;
	int v;
	char *nome;
	if (equipasVazioQ() == 0) {
		list = iLastList();
		sortlist(list);
		e = list->equipa;
		v = obterVitorias(e);
		printf("%d Melhores %d\n", nl, v);
		for (t = list; t != NULL; t = t->next) {
			e = t->equipa;
			nome = obterNomeEquipa(e);
			printf("%d * %s\n", nl, nome);
		}
	}
}

/* funcao principal que coordena o funcionamento do programa. */
int main() {
	int c;
	Ginit(TAMANHOHT);		/* inicia as hashtables necessarias */
	Tinit(TAMANHOHT);
	iTinit(TAMANHOHT);
	while ((c = getchar()) != EOF) {		/* verifica qual o comando a executar */
		if (c == 'a') {
			a();
			++nl;
		}
		if (c == 'A') {
			A();
			++nl;
		}
		if (c == 'l') {
			l();
			++nl;
		}
		if (c == 'p') {
			p();
			++nl;
		}
		if (c == 'P') {
			P();
			++nl;
		}
		if (c == 'r') {
			r();
			++nl;
		}
		if (c == 's') {
			s();
			++nl;
		}
		if (c == 'g') {
			g();
			++nl;
		}
		if (c == 'x') {
			Gclear();				/* antes de terminar o programa, liberta todas as hashtables */
			Tclear();				/* e listas que possam causar memory leaks */
			iTclear();
			apagaLista(listOrd);
			exit(0);
		}
	}
	return 0;
}