#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

#define MAX_STRING 1023
#define MAX_INPUT 3100

/*#####################################################################*/
/*	FUNCOES                                                            */
/*#####################################################################*/

/* adiciona um novo jogo */
int __a__(listJogo *jogos, listEquipa *equipas, int NL){

	int c, _score1, _score2, i;
	char input[MAX_INPUT], _nomeJogo[MAX_STRING], _nomeEquipa1[MAX_STRING], _nomeEquipa2[MAX_STRING];
	char* token;
	
	c=getchar();	/* remove o espaco entre o 'a' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';
	
	token=strtok(input, ":");
	strcpy(_nomeJogo, token);	/* gurada o nome do jogo */

	token=strtok(NULL, ":");
	strcpy(_nomeEquipa1, token);	/* guarda o nome da equipa 1 */

	token=strtok(NULL, ":");
	strcpy(_nomeEquipa2, token);	/* guarda o nome da equipa 2 */

	token=strtok(NULL, ":");
	_score1=atoi(token);			/* guarda o resultado da equipa 1 */

	token=strtok(NULL, ":");
	_score2=atoi(token);			/* guarda o resultado da equipa 2 */	

	if(!existJogo(jogos, _nomeJogo)){
		printf("%d Jogo existente.\n", NL);
		return 0;
	}

	if(existEquipa(equipas, _nomeEquipa1) == 1 || existEquipa(equipas, _nomeEquipa2) == 1){ 
		printf("%d Equipa inexistente.\n", NL);
		return 0;
	}

	addNodeJogo(jogos, _nomeJogo, _nomeEquipa1, _nomeEquipa2, _score1, _score2);

	if(_score1 > _score2)	searchListEquipa(equipas, _nomeEquipa1)->vitorias++;	/* atualiza resultado da equipa vencedora*/
	else if(_score1 < _score2)	searchListEquipa(equipas, _nomeEquipa2)->vitorias++;	/* atualiza resultado da equipa vencedora*/

	return 0;
}

/* adiciona uma nova equipa */
int __A__(listEquipa *equipas, int NL){

	int c, i;
	char input[MAX_INPUT], _nomeEquipa[MAX_STRING];
	char* token;

	c=getchar();	/* remove o espaco entre o 'A' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';
	
	token=strtok(input, ":");
	strcpy(_nomeEquipa, token);	/* gurada o nome da Equipa */

	if(existEquipa(equipas, _nomeEquipa) == 0){ 
		printf("%d Equipa existente.\n", NL);
		return 0;
	}

	addNodeEquipa(equipas, _nomeEquipa);

	return 0;
}

/* lista todos os jogos pela ordem em que foram introduzidos */
int __l__(listJogo *jogos, int NL){

	nodeJogo *currentNode;

	for(currentNode = jogos->head; currentNode != NULL; currentNode = currentNode->next){
		printf("%d %s %s %s %d %d\n", NL,currentNode->nomeJogo, currentNode->nomeEquipa1, currentNode->nomeEquipa2, currentNode->resultado1, currentNode->resultado2);
	}

	return 0;	
}

/* procura um jogo */
int __p__(listJogo *jogos, int NL){

	nodeJogo *currentNode;
	char input[MAX_STRING], _nomeJogo[MAX_STRING];
	int c, i;
	char* token;

	c=getchar();	/* remove o espaco entre o 'p' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';
	
	token=strtok(input, ":");
	strcpy(_nomeJogo, token);	/* gurada o nome do Jogo */

	for(currentNode = jogos->head; currentNode != NULL; currentNode = currentNode->next){
		if(strcmp(_nomeJogo, currentNode->nomeJogo) == 0){
			printf("%d %s %s %s %d %d\n", NL,currentNode->nomeJogo, currentNode->nomeEquipa1, currentNode->nomeEquipa2, currentNode->resultado1, currentNode->resultado2);
			return 0;
		}
	}

	printf("%d Jogo inexistente.\n", NL);

	return 0;
}

/* procura uma equipa */
int __P__(listEquipa *equipas, int NL){

	nodeEquipa *currentNode;
	int c, i;
	char input[MAX_INPUT], _nomeEquipa[MAX_STRING];
	char* token;

	c=getchar();	/* remove o espaco entre o 'P' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';
	
	token=strtok(input, ":");
	strcpy(_nomeEquipa, token);	/* gurada o nome da Equipa */

	for(currentNode = equipas->head; currentNode != NULL; currentNode = currentNode->next){
		if(strcmp(_nomeEquipa, currentNode->nomeEquipa) == 0){
			printf("%d %s %d\n", NL, currentNode->nomeEquipa, currentNode->vitorias);
			return 0;
		}
	}

	printf("%d Equipa inexistente.\n", NL);

	return 0;
}

/* apaga um jogo */
int __r__(listJogo *jogos, listEquipa *equipas, int NL){

	int c, i;
	char _nomeJogo[MAX_STRING], input[MAX_STRING];
	nodeJogo *nJogo;
	char* token;

	c=getchar();	/* remove o espaco entre o 'r' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';
	
	token=strtok(input, ":");
	strcpy(_nomeJogo, token);	/* gurada o nome do Jogo */
	

	if(existJogo(jogos, _nomeJogo)){ 
		printf("%d Jogo inexistente.\n", NL);
		return 0;	
	}
		
	nJogo = searchListJogo(jogos, _nomeJogo);

	if(nJogo->resultado1 > nJogo->resultado2)	searchListEquipa(equipas, nJogo->nomeEquipa1)->vitorias--;	/* atualiza numero de vitorias */
	else if(nJogo->resultado1 < nJogo->resultado2)	searchListEquipa(equipas, nJogo->nomeEquipa2)->vitorias--;	/* atualiza numero de vitorias */

	removeNodeJogo(jogos, nJogo);

	return 0;
}

/* altera a pontuacao (score) de um jogo */
int __s__(listJogo *jogos, listEquipa *equipas, int NL){

	int c, _score1, _score2, i;
	char input[MAX_INPUT], _nomeJogo[MAX_STRING];
	char* token;
	nodeJogo *nJogo;

	c=getchar();	/* remove o espaco entre o 's' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';
	
	token=strtok(input, ":");
	strcpy(_nomeJogo, token);	/* gurada o nome do jogo */

	token=strtok(NULL, ":");
	_score1=atoi(token);			/* guarda o resultado da equipa 1 */

	token=strtok(NULL, ":");
	_score2=atoi(token);			/* guarda o resultado da equipa 2 */
	
	if(existJogo(jogos, _nomeJogo)){ 
		printf("%d Jogo inexistente.\n", NL);
		return 0;	
	}
		
	nJogo = searchListJogo(jogos, _nomeJogo);

	if(nJogo->resultado1 > nJogo->resultado2 && _score1 < _score2){			/* atualiza numero de vitorias */
		searchListEquipa(equipas, nJogo->nomeEquipa1)->vitorias--;
		searchListEquipa(equipas, nJogo->nomeEquipa2)->vitorias++;
	}
	else if(nJogo->resultado1 < nJogo->resultado2 && _score1 > _score2){	/* atualiza numero de vitorias */
		searchListEquipa(equipas, nJogo->nomeEquipa1)->vitorias++;
		searchListEquipa(equipas, nJogo->nomeEquipa2)->vitorias--;
	}
	else if(nJogo->resultado1 == nJogo->resultado2 && _score1 < _score2){	/* atualiza numero de vitorias */
		searchListEquipa(equipas, nJogo->nomeEquipa2)->vitorias++;
	}
	else if(nJogo->resultado1 == nJogo->resultado2 && _score1 > _score2){	/* atualiza numero de vitorias */
		searchListEquipa(equipas, nJogo->nomeEquipa1)->vitorias++;
	}
	else if(nJogo->resultado1 > nJogo->resultado2 && _score1 == _score2){	/* atualiza numero de vitorias */
		searchListEquipa(equipas, nJogo->nomeEquipa1)->vitorias--;
	}
	else if(nJogo->resultado1 < nJogo->resultado2 && _score1 == _score2){	/* atualiza numero de vitorias */
		searchListEquipa(equipas, nJogo->nomeEquipa2)->vitorias--;
	}

	nJogo->resultado1 = _score1;	/* atualiza resultados */
	nJogo->resultado2 = _score2;	/* atualiza resultados */

	return 0;
}

/* encontra as equipas que venceram mais jogos */
int __g__(listEquipa *equipas, int NL){

	int numeroVitorias = 0;
	nodeEquipa *currentNode, *nodeToPrint;
	listEquipa *equipasAux = mkListEquipa();	/* cria lista de equipas auxiliares */

	if(equipas->head == NULL) return 0; /* caso nao haja equipas */

	for(currentNode = equipas->head; currentNode != NULL; currentNode = currentNode->next){
		if(currentNode->vitorias > numeroVitorias){
			numeroVitorias = currentNode->vitorias; /* atualiza o novo numero de vitorias a comparar */
			freeListEquipa(equipasAux);				/* apaga a lista de equipas auxiliares anteriormente criada, para o numero de vitorias antigo */
			equipasAux = mkListEquipa();			/* cria uma nova lista de equipas auxiliares para o novo numero de vitorias */
			addNodeEquipa(equipasAux, currentNode->nomeEquipa);	/* adiciona uma nova equipa a essa nova lista de equipas auxiliares */
		}
		else if(currentNode->vitorias == numeroVitorias){
			addNodeEquipa(equipasAux, currentNode->nomeEquipa);
		}
	}

	printf("%d Melhores %d\n", NL, numeroVitorias);

	/* ORDENAR POR ORDEM ALFABETICA */
	while(equipasAux->head != NULL){		/* Enquanto houver Equipas auxiliares para ordenar */
		nodeToPrint = equipasAux->head;		/* Comeca sempre pela head da lista de equipas auxiliares */
		for(currentNode = equipasAux->head; currentNode != NULL; currentNode = currentNode->next){ /* percorre a lista de equipas auxiliares */
			if(strcmp(currentNode->nomeEquipa, nodeToPrint->nomeEquipa) < 0){	/* condicao de troca, por ordem alfabetica */
				nodeToPrint = currentNode;	/* nova equipa (ordem alfabetica mais abaixa que a anterior) */
			}
		}
		printf("%d * %s\n", NL, nodeToPrint->nomeEquipa); /* imprime a equipa com a ordem alfabetica mais baixa */
		removeNodeEquipa(equipasAux, nodeToPrint);		/* remove essa equipa da lista de equipas auxiliares para voltar a iterar */
	}

	return 0;
}

/*#####################################################################*/
/*	CODIGO                                                             */
/*#####################################################################*/

int main(){

	int c, NL = 0;


	/* INICIALIZACOES */
	listJogo *jogos = mkListJogo();			/* cria lista de jogos */
	listEquipa *equipas = mkListEquipa();	/* cria lista de equipas */

	
	while(c!='x'){
		c=getchar();
		switch(c){
			case 'a':			/* adiciona um novo jogo */	
				NL++;
				__a__(jogos, equipas, NL);
				break;
			case 'A':			/* adiciona uma nova equipa */
				NL++;
				__A__(equipas, NL);
				break;
			case 'l':			/* lista todos os jogos pela ordem em que foram introduzidos */
				NL++;
				__l__(jogos, NL);
				break;
			case 'p':			/* procura um jogo */
				NL++;
				__p__(jogos, NL);
				break;
			case 'P':			/* procura uma equipa */
				NL++;
				__P__(equipas, NL);
				break;
			case 'r':			/* apaga um jogo */
				NL++;
				__r__(jogos, equipas,NL);
				break;
			case 's':			/* altera a pontuacao (score) de um jogo */
				NL++;
				__s__(jogos, equipas,NL);
				break;
			case 'g':			/* encontra as equipas que venceram mais jogos */
				NL++;
				__g__(equipas, NL);
				break;		
			case 'x':			/* termina o programa */
				return 0;												
		}
	}

	return 0;
}

/*#####################################################################*/