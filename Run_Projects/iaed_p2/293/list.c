#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

struct _game{
	int NL;
	char *name;
	char *team1;
	char *team2;
	int points1;
	int points2;
	struct _game *previous;
	struct _game *next;
};

struct _team{
	char *name;
	int wins;
	struct _team *next;
};
/*esta funcao serve apenas para alocar a memoria para 1 node da lista e inicializar as variaveis a 0*/
Game *InitGameNode(){
	
	/*memory allocation for new array of structures*/
	Game *new=(Game *)malloc(sizeof(Game));
	/*inicialization of variables*/
	new->NL=0;
	new->name='\0';
	new->team1='\0';
	new->team2='\0';
	new->points1=0;
	new->points2=0;
	new->previous=NULL;
	new->next=NULL;
	
	return new;
}

/*Nesta funcao estas a atribuir valores As variaveis e a inserir o node no fim da lista atraves dos ponteiros*/
Game *SetGameNode(Game *new, Game *headG, char *fname, char *fteam1, char *fteam2, int fscore1, int fscore2, int nl) {
	Game *aux1=NULL;
	Game *aux=headG;
	int ln=0;
	int l1=0;
	int l2=0;
	
	/*variaveis*/
	new->points1=fscore1;
	new->points2 =fscore2;
	new->NL=nl;
	
	ln=strlen(fname);
	new->name=(char *)malloc(sizeof(char)*(ln)+1);
	strcpy(new->name, fname);
	
	l1=strlen(fteam1);
	new->team1=(char *)malloc(sizeof(char)*(l1)+1);
	strcpy(new->team1, fteam1);
	
	l2=strlen(fteam2);
	new->team2=(char *)malloc(sizeof(char)*(l2)+1);
	strcpy(new->team2, fteam2);
	
	/*inserir na lista*/
	if(aux==NULL){
		headG=new;
	} else {
		
		aux1=aux;
		/*encontrar o ultimo nome*/
		while(aux1->next!=NULL){
			aux1=aux1->next;
		}
		aux1->next=new;
		new->previous=aux1;
		new->next=NULL;
	}
	return headG;
}
Game *DeleteGameNode(Game *delete, Game *headG){
	Game *aux=NULL;
	Game *aux1=NULL;
	
	aux=headG;
	if(delete!=headG){
		
		while(aux->next!=delete)
			aux=aux->next;
		
		aux->next=delete->next;
		aux1=delete->next;
		aux1->previous=aux;
		
		
	}else {
		printf("Estas a tenter apagar a head.");
		headG=delete->next;
	}
	
		delete->previous=NULL;
		delete->next=NULL;
		
		free(delete->name);
		free(delete->team1);
		free(delete->team2);
		free(delete);
		return headG;	
}

char *GetName(Game *current){
	return current->name;
}

char *GetTeam1(Game *current){
	return current->team1;
}
char *GetTeam2(Game *current){
	return current->team2;
}

int Getscore1(Game *current){
	return current->points1;
}

int Getscore2(Game *current){
	return current->points2;
}

int Getline(Game *current){
	return current->NL;
}


Game *GetNext_game(Game *current){
	return current->next;
}
Game *GetPrev_game(Game *current){
	return current->previous;
}

Team *GetNext_team(Team *current){
	return current->next;
}
void FreeAll (Game *headG){
	Game *aux=NULL;
	
	for(aux=headG; aux->next!=NULL; aux=aux->next){
		free(aux->name);
		free(aux->team1);
		free(aux->team2);
	}
	
	free(headG);
}

Game *muda_score(int score1, int score2, Game *elemento){
	elemento->points1=score1;
	elemento->points2=score2;
	return elemento;
}

/*esta funcao serve apenas para alocar a memoria para 1 node da lista e inicializar as variaveis a 0*/
Team *InitTeamNode(){
	
	/*memory allocation for new array of structures*/
	Team *new=(Team *)malloc(sizeof(Team));
	/*inicialization of variables*/
	new->name='\0';
	new->wins=0;
	new->next=NULL;
	
	return new;
}

/*Nesta funcao estas a atribuir valores As variaveis e a inserir o node em ordem descendente e alfabetica*/
Team *SetTeamNode(Team *new, Team *headT, char *fname){
	Team *aux=NULL;
	Team *aux1=NULL;
	int ln=0;
	/*Init*/
	if(new==NULL){
		new=InitTeamNode();
		
		ln=strlen(fname);
		new->name=(char *)malloc(sizeof(char)*(ln)+1);
		strcpy(new->name, fname);
	}
	/*inserir na lista*/
	if(headT==NULL){
		headT=new;
	} else {

		if(new->wins>headT->wins){
			new->next=headT;
			headT=new;
		}
		else {
			aux=headT;
			/*ordenar*/
			while(new->wins<=aux->wins){

				if(new->wins==aux->wins){
					/*ordem alfabetica*/
					if(strcmp(new->name, aux->name)==0){
						 /*nomes iguais, nao deve acontecer porque o nome da equipa so acontece uma vez*/
						/*mas caso aconteca, da-se exit*/
						exit(0);
					}
					else if(strcmp(new->name, aux->name)<0){
						/*new menor que aux logo aux vem primeiro no alfabeto e por isso primeiro na lista*/
						new->next=aux->next;
						aux=new;
						break;
					} 
					else if(strcmp(new->name, aux->name)>0){
						/*aux menor que new logo new vem primeiro no alfabeto e por isso primeiro na lista*/
						aux->next=new;
						aux1=aux;
						aux1=aux1->next;
						new->next=aux1->next;
						break;
					} 

				}
				aux=aux->next;
			}
		}
	}
	return headT;
}

char *Getteam_name(Team *current){
	return current->name;
}

int GetWin(Team *current){
	return current->wins;
}

void FreeT (Team *headT){
	Team *aux=NULL;
	
	for(aux=headT; aux->next!=NULL; aux=aux->next){
		free(aux->name);
	}
	
	free(headT);
}

void Determinewins(Team *headT, Game *current){
	Team *aux=NULL;
	Team *wanted=NULL;
	

	if(current->points1>current->points2) /*ganha equipa 1*/
		wanted->name=current->team1;
	else if (current->points1<current->points2) /*ganha equipa 2*/
		wanted->name=current->team2;
	else if (current->points1==current->points2) /*empate por isso nao ha atualizacao de vitorias*/
		exit(0);

	for(aux=headT; aux->next!=NULL; aux=aux->next){
		if(strcmp(wanted->name, aux->name)==0)
			aux->wins=aux->wins+1;
	}

	free(wanted);
	free(aux);
}
