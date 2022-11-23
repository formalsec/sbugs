#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "remove.h"


/*Funcao que decrementa o contador de vitorias de uma
* certa equipa com base na remocao de um jogo.*/
void rmvWin(list *tms, char *name){

	node *ptr = tms->head;

	while(ptr != NULL){

		ptr = ptr->next;
	}

	while(ptr){
		if(strcmp(ptr->name, name) == 0){
			(ptr->won)--;
			break;
		}
		ptr = ptr->next;
	}
}


/*Esta funcao vai libertar a memoria alocada para os nos das listas
* fazendo a particao atraves da flag.*/
void deleteNode(node *del_n, int flag){

	if(flag == 0){
		free(del_n->name);
		free(del_n->team1);
		free(del_n->team2);
	}

	else{
		free(del_n->name);
	}

	free(del_n);
}


/*Esta funcao vai remover um no da lista libertando todas as
* ligacoes , quer o no next, que o previous e e proprio no atual.
* Por ultimo, chama a funcao que ira libertar a memoria.*/
void pop(list *ls, node *del, int flag){

	if(del->previous == NULL){
		ls->head = del->next;
	}
	else{
		del->previous->next = del->next;
	}


	if(del->next == NULL){
		ls->end = del->previous;
	}
	else{
		del->next->previous = del->previous;
	}
	deleteNode(del, flag);
}


/*Estas duas funcoes tratam de remover um no de hash da respetiva hashtable.
* Sao usadas tambem para chamar a funcao para remover a informacao do no da lista
* associada.*/
void eraseGames(list *ls, char name[MAXC]){

	hashNode *del, *aux;

	int idx = getHashKey(name);
	
	del = games[idx].head;

	if(del == NULL){
		return;
	}

	else if(strcmp(del->point->name, name) == 0){

		aux = del->next;
		pop(ls, del->point, 0);
		free(del);
		games[idx].head = aux;
		return;
	}

	while(del->next != NULL){
		if(strcmp(del->next->point->name, name) == 0){
			break;
		}

		else
			del = del->next;
	}

	aux = del->next;
	pop(ls, aux->point, 0);
	free(aux);
	del->next = aux->next;

}

void eraseTeams(list *ls, char name[MAXC]){

	hashNode *del, *aux;

	int idx = getHashKey(name);
	
	del = teams[idx].head;

	if(del == NULL){
		return;
	}

	else if(strcmp(del->point->name, name) == 0){

		aux = del->next;
		pop(ls, del->point, 1);
		free(del);
		teams[idx].head = aux;
		return;
	}

	while(del->next != NULL){
		if(strcmp(del->next->point->name, name) == 0){
			break;
		}

		else
			del = del->next;
	}

	aux = del->next;
	pop(ls, aux->point, 1);
	free(aux);
	del->next = aux->next;
}


/*Nesta funcao sao recebidas as duas listas para se proceder ao decremento
* da variavel jogos ganhos e de chamar a funcao que ira remover um jogo do sistema.*/
void removeGame(list *ls, list *tms){

	hashNode *search, *team1, *team2;
	char name[MAXC];

	scanf(" %[^\n]", name);

	search = getNodeGames(name);

	if(search == NULL){
		printf("%d Jogo inexistente.\n", counter);
		return;
	}

	team1 = getNodeTeams(search->point->team1);
	team2 = getNodeTeams(search->point->team2);

	if(search->point->score1 > search->point->score2){
		rmvWin(tms, team1->point->name);
		(team1->point->won)--;
	}
	else if(search->point->score1 < search->point->score2){
		rmvWin(tms, team2->point->name);
		(team2->point->won)--;
	}

	eraseGames(ls, name);
}