#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hash.h"

static link_jogo *htj;      /*tabela de ponteiros jogo*/
static link_equipa *hte; 	/*tabela de ponteiros equipa*/

int hash(char *nome){
	int h, a = 31415, b =  27183;
	for (h = 0; *nome != '\0'; nome++, a = a*b % (M-1)){
		h = (a*h + *nome) % M;
	}
	return h;
}

void Initjogo(){
	int i;
	htj = can_fail_malloc(M * sizeof(link_jogo));
	for(i=0; i<M; i++){
		htj[i] = NULL;
	}
}

jogo *searchListJogo(int hashID, char *nome){
	jogo *auxjogo = NULL;
	link_jogo aux = htj[hashID]; 
	while (aux != NULL){
		if (strcmp((aux -> j) -> nome, nome) == 0)
			return aux -> j;
		aux = aux -> next;
	}
	return auxjogo;
}

jogo *STsearchJogo(char *nome){
	int i = hash(nome);
	return searchListJogo(i, nome);
}

int insertBeginListJogo(int hashID, jogo *jg){
	jogo *auxjogo;
	link_jogo novoNo;
	auxjogo = searchListJogo(hashID, jg -> nome);
	if (auxjogo == NULL){
		novoNo = can_fail_malloc(sizeof(struct node_jogo));
		novoNo -> j = jg;
		novoNo -> next = htj[hashID];
		htj[hashID] = novoNo;
		return 0;
	}else{
		return -1;
	}
}

void STinsertJogo(jogo *jg){
	int i;
	i = hash(jg -> nome);
	insertBeginListJogo(i, jg); 
}

int removeItemJogo(int hashID, char *nome){
	link_jogo aux = htj[hashID];
	link_jogo auxRem;
	/*se for o primeiro jogo*/
	if(strcmp((aux -> j) -> nome, nome) == 0){
		htj[hashID] = aux -> next;
		free_jogo(aux -> j);
		free(aux);
		return 0;
	}

	/*se nao for o primeiro jogo*/
	while (aux -> next != NULL){
		if(strcmp((aux -> next -> j) -> nome, nome) == 0){
			auxRem = aux -> next;
			aux -> next = (aux -> next) -> next;
			free_jogo(auxRem -> j);
			free(auxRem);
			return 0;
		}else{
			auxRem = aux -> next;
			auxRem = aux -> next;
		}
		aux = (aux -> next) -> next;
	}
	return -1;
}

void STdelete(char *nome){
	int i = hash(nome);
	removeItemJogo(i, nome);
}

void ApagaHashJogo(){
	int i = 0;
	link_jogo hashtb;
	for (i = 0; i < M; i++){
		hashtb = htj[i];
		while (hashtb != NULL){
			link_jogo aux_free = hashtb -> next;
			free(hashtb);
			hashtb = aux_free;
		}
	}
	free(htj);
}

void Initequipa(){
	int i;
	hte = can_fail_malloc(M * sizeof(link_equipa));
	for(i=0; i<M; i++){
		hte[i] = NULL;
	}
}

equipa *searchListEquipa(int hashID, char *nome){
	equipa *auxequipa = NULL;
	link_equipa aux = hte[hashID]; 
	while (aux != NULL){
		if (strcmp((aux -> e) -> nome, nome) == 0)
			return aux -> e;
		aux = aux -> next;
	}
	return auxequipa;
}

equipa *STsearchEquipa(char *nome){
	int i = hash(nome);
	return searchListEquipa(i, nome);
}

int insertBeginListEquipa(int hashID, equipa *eq){
	equipa *auxequipa;
	link_equipa novoNo;
	auxequipa = searchListEquipa(hashID, eq->nome);
	if (auxequipa == NULL){
		novoNo = can_fail_malloc(sizeof(struct node_equipa));
		novoNo -> e = eq;
		novoNo -> next = hte[hashID];
		hte[hashID] = novoNo;	
		return 0;
	}else{
		return -1;
	}
}

void STinsertEquipa(equipa *eq){
	int i;
	i = hash(eq -> nome);
	insertBeginListEquipa(i, eq); 
}

void ApagaHashEquipa(){
	int i = 0;
	link_equipa hashtb;
	for (i = 0; i < M; i++){
		hashtb = hte[i];
		while (hashtb != NULL){
			link_equipa aux_free = hashtb -> next;
			free(hashtb);
			hashtb = aux_free;
		}
	}
	free(hte);
}
