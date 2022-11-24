#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gameHTable.h"

/*inicializa a hashtable de jogos*/
glink ** init_HTgame(int number){
	int i;
	glink** HTgame = can_fail_malloc((number*2)*sizeof(glink*));
	for(i=0; i<(SIZE*2); i++){
		HTgame[i] = NULL;
	}
	return HTgame;
}

/*inicializa a tabela simples de equipas*/
glink ** init_STgame(int number){
	int i;
	glink** simple = can_fail_malloc((number*2)*sizeof(glink*));
	memset(simple, 0x0, sizeof(glink*)*2*SIZE);
	for(i=0; i<(SIZE*2); i++){
		simple[i] = NULL;
	}
	return simple;
}

/*expande a tabela das equipas, se esta for de tamanho inferior
as equipas inseridas*/
glink ** simplexpand(glink ** STgame, int number){
	int i, conta=-1;
	glink ** nv = STgame;
	glink ** newSTgame;
	newSTgame = init_STgame(number*4);
	for(i = 0; i<number*2; i++){
		if(Key(nv[i]->g) != NULL){
			gorderInsert(&nv[i], newSTgame, conta++);
		}
	}
	free(nv);
	return newSTgame;
}

/*insere na lista STgame, o ponteiro para o jogo pela ordem em que foi inserido 
i.e. o seu indice na tabela = numero do contador de jogos na insercao*/
glink ** gorderInsert(glink ** link, glink ** STgame, int count){
	STgame[count] = *link;
	return link;
}

/*duplica o tamanho da hashtable HTgame se esta chega a metade da sua capacidade*/
glink ** expand(glink ** HTgame, int number){
	int i;
	glink ** t = HTgame;
	glink ** newHTgame;
	newHTgame = init_HTgame(number*2);
	for(i = 0; i <number*2; i++){
		if(Key(t[i]->g) != NULL)
			gsimplyInsert(t[i], newHTgame);
	}
	free(t);
	return newHTgame;
}

/*remove jogo da lista STgame*/
glink** gorderRemove(char * buffer0, glink ** STgame, int counter_game){
	int i=0, j;
	glink *aux;
	for(i=0; i < counter_game; i++){
		/*copia o jogo ate encontrar o jogo a remover*/
		if(strcmp(buffer0, Key(STgame[i]->g)) == 0)
			break;
	}
	/*i tem o indice do jogo a remover*/
	/*posicao anteriormente apontada para jogo, aponta NULL*/
	STgame[i] = NULL;
	/*copia o elemento seguinte para o que foi posto a NULL
	e o resto dos elementos para a posicao anterior*/
	for(j = i; j < counter_game; j++){
		aux = STgame[j+1];
		STgame[j] = aux;
	}
	return STgame;
}

/*verifica o input na criacao de um jogo
retorna EXISTE_JOGO, se o jogo existe no sistema
retorna NAO_EXISTE_EQUIPA, se uma das equipas nao existe no sistema 
retorna INPUT_OK, se input satisfaz condicoes*/
int verifica_jogo(char * buffer0, char * buffer1, char * buffer2, 
				  glink ** HTgame, tlink **HTteams){
	if (search_game(HTgame, buffer0) != NULL) return EXISTE_JOGO;
	else if(((search_team(HTteams, buffer1) == NULL )||(search_team(HTteams, buffer2) == NULL)))
		return NAO_EXISTE_EQUIPA;
	else return INPUT_OK;
}

/*cria o jogo, dado o nome, as equipas e o resultado*/
pGame * create_game(char * buffer0, char* buffer1, char * buffer2, int res1, int res2,
	tlink ** HTteams){
	pGame * jogo = can_fail_malloc(sizeof(struct game));

	jogo->score1 = res1;
	jogo->score2 = res2;
	/*aloca memoria necessaria para o nome do jogo*/
	jogo->name = my_strdup(buffer0);
	/*procura na hashtable de equipas as que compoem jogo*/
	jogo->team1 = search_team(HTteams, buffer1)->t;
	jogo->team2 = search_team(HTteams, buffer2)->t;
	/*verifica qual a equipa vencedora*/
	if(res1>res2){
		change_win_team(HTteams, buffer1, WINNER);
	}
	else if(res2>res1)
		change_win_team(HTteams, buffer2, WINNER);
	/*retorna o ponteiro para o jogo criado*/
	return jogo;
}

/*retorna o ponteiro para o jogo, depois de criado, e insere na hashtable HTgame*/
glink * glinkInsert(char * buffer0, char* buffer1, char * buffer2, int res1, int res2,
					glink * link, glink ** HTgame, tlink ** HTteams){
	int i, k;
	link->g = create_game(buffer0, buffer1, buffer2, res1, res2, HTteams);
	i = hash(Key(link->g));
	k = hashtwo(Key(link->g));
	while(HTgame[i] != NULL) 
		i = (i + k) % (SIZE*2);
	HTgame[i] = link;/*insere na hashtable*/
	return link;
}

/*insere o jogo na hashtable dado o ponteiro para este*/
glink * gsimplyInsert(glink * new, glink ** HTgame){
	int i, k;
	i = hash(Key(new->g));
	k = hashtwo(Key(new->g));
	printf("volto a inserir %s\n", Key(new->g));
	while(HTgame[i] != NULLitem)
		i = (i + k) % SIZE;
	HTgame[i] = new;
	return new;
}

/*remove o jogo na hashtable, dado o nome*/
void glinkRemove(char * buffer0, glink ** HTgame){
	int i, j=0, k;
	glink * gaux;
	i = hash(buffer0);
	k = hashtwo(buffer0);
	while(HTgame[i] != NULL){
		if(strcmp(buffer0, Key(HTgame[i]->g))==0){
			break;
		}
		else
			i = (i+k) % SIZE;
	}
	if(HTgame[i] == NULLitem)return;
	/*liberta a memoria relacionada com o jogo*/
	free(HTgame[i]->g->name); free(HTgame[i]->g); HTgame[i] = NULL;
	/*aloca os elementos seguintes na hashtable*/
	for(j = (i+k) % SIZE; HTgame[j] != NULL; j = (j+k) % SIZE){ 
		gaux = HTgame[j];
		HTgame[j] = NULL;
		gaux = gsimplyInsert(gaux, HTgame);
	}
}

/*procura um jogo na hashtable dado o nome
retorna o jogo, se este existir na hashtable
retorna null, se o jogo nao for encontrado*/
glink * search_game(glink ** HTgame, char *nome){
	int i, k;
	glink * link;
	i = hash(nome);
	k = hashtwo(nome);
	while(HTgame[i]!= NULL){
		link = HTgame[i];
		if(strcmp(nome, Key(link->g)) == 0) return HTgame[i];
		else
			i = (i + k) % (SIZE*2);
	}
	return NULL;
}

/*dado o nome e os scores do jogo, altera a pontuacao deste na hashtable*/
glink * gchangeScore(char * buffer0, int res1, int res2, glink ** HTgame, tlink** HTteams){
	int i, k;
	glink * link;
	i = hash(buffer0);
	k = hashtwo(buffer0);
	/*procura o jogo na hashtable*/
	link = search_game(HTgame, buffer0);
	if (link != NULL){
		/*associa o novo resultado ao jogo*/
		link->g->score1 = res1;
		link->g->score2 = res2;
		while(HTgame[i] != NULLitem)
			i = (i+k) % SIZE;
		HTgame[i] = link;
		/*alteracoes necessarias a novas equipas perdedoras ou ganhadoras*/
		if(res1>res2){
			/*ganha a equipa 1*/
			change_win_team(HTteams, link->g->team1->name, WINNER);
			change_win_team(HTteams, link->g->team2->name, LOOSER);
		}
		else if(res2>res1){
			/*ganha a equipa 2*/
			change_win_team(HTteams, link->g->team2->name, WINNER);
			change_win_team(HTteams, link->g->team1->name, LOOSER);
		}
	}
	return link;
}

/*return false se a hashtable de jogos esta vazia, true caso contrario*/
bool isEmpty(glink ** HTgame){
	int i;
	for(i=0; i<(SIZE*2); i++){
		if (HTgame[i] != NULL)
			return true;
	}
	return false;
}

/*dado o jogo, liberta a sua memoria*/
void gameFree(pGame * g){
	free(g->name);
	free(g->team1);
	free(g->team2);
	free(g);
}

/*dado a tabela, liberta a sua memoria*/
void free_gTable(glink * gtable){
	int i;
	pGame * g;
	for(i = 0; i <= SIZE; i++){
		g = &gtable->g[i];
		if(g != NULL){
			gameFree(g);
		}
	}

	free(gtable->g);
	free(gtable);
}
