#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Games.h"
#include "list.h"
#include "hashtabel.h"



void Solve (FILE *fpIn, FILE *fpOut){
	char *valor="";
	char *nome=NULL, *team1=NULL, *team2=NULL;
	int NL=1;
	char *string=(char *) malloc(sizeof(char)*(1023));
	char *s1=NULL;
	char *s2=NULL;
	Game *headG=NULL;
	Team *headT=NULL;
	int score1;
	int score2;
	

	while (!EOF){
		
		fscanf(fpIn, "%s", string);
		
		switch(string[0]){
			case'a':
				sscanf(string, "%c %s:%s:%s:%s:%s\n", valor,nome, team1, team2, s1, s2);
				score1=atoi(s1);
				score2=atoi(s2);
				Funcaocaso_a(fpOut, headG, headT, nome, team1, team2, score1, score2, NL);
				break;

			case'l':
				sscanf(string, "%c\n", valor);
				Funcaocaso_l(headG, fpOut, NL);
				break;
			
			case'p':
				sscanf(string, "%c %s\n", valor, nome);
				Funcaocaso_p(headG, fpOut, nome, NL);
				break;
			
			case'r':
				sscanf(string, "%c %s\n", valor, nome);
				Funcaocaso_r(nome, headG, fpOut, NL);
				break;
			
			case's':
				sscanf(string, "%c %s:%s:%s\n", valor, nome, s1, s2);
				score1=atoi(s1);
				score2=atoi(s2);
				Funcaocaso_s(headT, nome, score1, score2, headG, fpOut, NL);
				break;
			
			case'A':
				sscanf(string, "%c %s\n", valor, nome);
				Funcaocaso_A(nome, fpOut, headT, NL);
				break;
			
			case'P':
				sscanf(string, "%c %s\n", valor, nome);
				Funcaocaso_P(nome, headT, fpOut, NL);
				break;
			
			case'g':
				sscanf(string, "%c\n", valor);
				Funcaocaso_g(headT, fpOut, NL);
				break;
		}	

	NL+=1;
	}
	
	free(string);
	free(nome);
	free(team1);
	free(team2);
	FreeAll(headG);
	FreeT(headT);
}


void Funcaocaso_a( FILE *fpOut, Game *headG, Team *headT, char *nome, char *team1,char  *team2, int score1, int score2, int NL){
	Game *aux1=NULL;
	Game *newG=NULL;
	Team *aux=NULL;
	
	if(headT==NULL){
		fprintf(fpOut, "%d Equipa inexistente.\n", NL);
		exit(0);
	}
	else{

		for(aux=headT; GetNext_team(aux)!=NULL; aux=GetNext_team(aux)){
				if((strcmp(team1, Getteam_name(aux))==0)&&(strcmp(team2, Getteam_name(aux))==0)){
					/*equipas existem => sai do loop para avancar*/
					break;
				}
		}
		for(aux1=headG; GetNext_game(aux1)!=NULL; aux1=GetNext_game(aux1)){
				if(strcmp(nome, GetName(aux1))==0){
					fprintf(fpOut, "%d Jogo existente.\n", NL);
					exit(0);
				}
		}
		newG=InitGameNode();
		if (newG==NULL){
			printf("Erro alocacao novo node\n.");
			exit(0);
		}
		headG=SetGameNode(newG, headG, nome, team1, team2, score1, score2,  NL);
		Determinewins(headT, newG); /*atualizar vitorias porque ha novo jogo*/
		fprintf(fpOut, "\n");
	}

	free(aux);
	free(aux1);
		
}

void Funcaocaso_l(Game *headG, FILE *fpOut, int NL){
	Game *aux=NULL, *aux1=NULL;
	Game *tail=NULL;

	if (headG==NULL){
		fprintf(fpOut, "\n");
		exit(0);
	}
	else {

		/*percorrer lista para ter a tail temporaria e poder percorrer a lista e imprimir ao contrario por ordem de introducao*/
		for (aux=headG; GetNext_game(aux)!=NULL; aux=GetNext_game(aux)){
			tail=aux;
			tail=GetPrev_game(aux);
		}

		for (aux1=tail; GetPrev_game(aux1)!=NULL; aux1=GetPrev_game(aux1))
			fprintf(fpOut, "%d %s %s %s %d %d\n", NL, GetName(aux1), GetTeam1(aux1), GetTeam2(aux), Getscore1(aux1), Getscore2(aux1));
	}

	free(tail);
	free(aux);
	free(aux1);
}

void Funcaocaso_p(Game *headG, FILE *fpOut, char *nome, int NL){
	Game *aux=NULL;

	for (aux=headG; GetNext_game(aux)!=NULL; aux=GetNext_game(aux)){

		if (strcmp(GetName(aux), nome)==0)
			fprintf(fpOut, "%c %s %s %s %d %d\n", Getline(aux), GetName(aux), GetTeam1(aux), GetTeam2(aux), Getscore1(aux), Getscore2(aux));
		else fprintf(fpOut, "%d Jogo inexistente.\n", NL);
	}
	free(aux);
}

void Funcaocaso_r(char *nome, Game *headG, FILE *fpOut, int NL){
	Game *aux=NULL;

	if (headG==NULL)
		exit(0);
	else {
		for(aux=headG; GetNext_game(aux)!=NULL; aux=GetNext_game(aux)){
			if (strcmp(GetName(aux), nome)==0)
				DeleteGameNode(aux, headG);
				else {
					fprintf(fpOut, "%d Jogo Inexistente",NL);
					break;
				}
		}
	}

	free(aux);
}

void Funcaocaso_s(Team *headT, char *nome, int score1, int score2, Game *headG, FILE *fpOut, int NL){
	Game *aux=NULL;

	for (aux=headG; GetNext_game(aux)!=NULL; aux=GetNext_game(aux)){

		if (strcmp(GetName(aux), nome)==0){
			aux=muda_score(score1, score2, aux);
			Determinewins(headT, aux); /*atualizar vitotrias porque scores mudaram*/
			free(aux);
			exit(0);
		}
	
		}


	fprintf(fpOut, "%d Jogo inexistente", NL);
	free(aux);
}

void Funcaocaso_A(char *nome, FILE *fpOut, Team *headT, int NL){
	Team *aux=NULL;
	Team *new=NULL;

	if(headT==NULL){
		headT=SetTeamNode(new, headT, nome);
		if(headT==NULL)
			exit(0);
	}else {
		for(aux=headT; GetNext_team(aux)!=NULL; aux=GetNext_team(aux)){
			if(strcmp(Getteam_name(aux),nome)==0){
				fprintf(fpOut, "%d Equipa existente.\n", NL);

				exit(0);
			}

		}

		new=InitTeamNode();
		if(new==NULL)
			exit(0);

		headT=SetTeamNode(new, headT, nome);
			
	}
	free(aux);
}

void Funcaocaso_P(char *nome, Team *headT, FILE *fpOut, int NL){
	Team *aux=NULL;

	for (aux=headT; GetNext_team(aux)!=NULL; aux=GetNext_team(aux)){
		if (strcmp(Getteam_name(aux), nome)==0){
			fprintf(fpOut, "%d %s %d\n", NL, nome, GetWin(aux));
			free(aux);
			exit(0);
		}
	}
	fprintf(fpOut, "%d Equipa inexistente.\n", NL);
}

void Funcaocaso_g(Team *headT, FILE *fpOut, int NL){
	Team *aux=NULL;

	if (headT==NULL)
		exit(0);

	fprintf(fpOut, "%d Melhores %d\n", NL, GetWin(headT));

	for (aux=headT; GetWin(aux)==GetWin(GetNext_team(aux)); aux=GetNext_team(aux)){
		fprintf(fpOut, "%d * %s\n",NL ,Getteam_name(aux));
	}

	free(aux);
}
