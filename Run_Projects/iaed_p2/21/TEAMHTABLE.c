#include "TEAMHTABLE.h"
#include "TEAM.h"

/*Funcao de dispersao para guardar as equipas
  Guarda as equipas por ordem alfabetica, ou seja, guarda as equipas com a mesma
  inicial no mesmo teamNode*/
int hashT(char* v){
  int h = v[0]%MAXTEAM;
  return h;
}
/*Inicializa a hash table*/
void teamInit(){
  int i;
  teamHeads = (teamNode*)malloc(MAXTEAM*sizeof(teamNode));
  for (i = 0; i < MAXTEAM; i++){
    teamHeads[i] = NULL;
  }
}

/*Insere a equipa team na linked list do node da hashtable, correspondente, por ordem alfabetica.
  Calcula, atraves da funcao de dispersao hashT, utilizando o nome da equipa,
  o indice da hash table onde colocar a nova equipa.
  Posteriormente, percorre a lista ate encontrar o local onde a colocar (ordem alfabetica).*/
void teamInsert(Team team){
  int i = hashT(team->name);
  if(teamHeads[i] == NULL){
    teamHeads[i] = (teamNode)malloc(sizeof(struct teamnode));
    teamHeads[i]->team = team;
    teamHeads[i]->next = NULL;
  }
  else{
    teamNode newNode = (teamNode)malloc(sizeof(struct teamnode));
    teamNode t, prev;
    newNode->team = team;

    for(t = teamHeads[i], prev = NULL; t!=NULL; prev = t, t = t->next){
      if(strcmp(t->team->name, team->name)>0){
        if(t == teamHeads[i]){
          newNode->next = teamHeads[i];
          teamHeads[i]=newNode;
          break;
        }
        else{
          newNode->next = t;
          prev->next = newNode;
          break;
        }
      }
      else{
        if(t->next == NULL){
          newNode->next = NULL;
          t->next = newNode;
          break;
        }
      }
    }
  }
}

/*Remove a equipa team da hash table*/
void teamDelete(Team team){
  int i = hashT(team->name);
  teamNode t, prev;
  for(t = teamHeads[i], prev = NULL; t!=NULL; prev = t, t = t->next){
    if(strcmp(t->team->name, team->name)==0){
      if(t == teamHeads[i]){
        teamHeads[i] = t->next;
      }
      else if(t->next == NULL){
				prev->next = NULL;
			}
			else{
				prev->next = t->next;
			}
			free(t->team);
			free(t);
			break;
    }
  }
}

/*Devolve o node onde a equipa, de nome name, se encontra. Primeiro calcula, atraves da funcao
  de dispersao, hashT, a posicao na hashtable e depois percorre a linked list ate encontrar
  a equipa com o nome introduzido como argumento da funcao*/
teamNode teamSearch(char* name){
  int i = hashT(name);
  teamNode aux;
  for(aux = teamHeads[i]; aux!=NULL; aux=aux->next){
    if(strcmp(aux->team->name, name)==0){
      return aux;
    }
  }
  return NULL;
}

/*Funcao auxiliar da teamHashFREE, que elimina cada linked list da hashtable*/
void teamHashListFREE(teamNode t){
  if (t!=NULL){
    freeTeam(t->team);
    teamHashListFREE(t->next);
    free(t);
  }
}

/*Apaga a hashtable*/
void teamHashFREE(){
  int i;
  for(i=0; i<MAXTEAM; i++){
    teamHashListFREE(teamHeads[i]);
  }
}

/*Inicilizacao da linked list que guarda as equipas com mais vitorias*/
void TlistInit(){
  THeadList = NULL;
}

/*Cria um novo node com a equipa t e ponteiro, next, para o node seguinte*/
teamNode newTeamNode(Team t, teamNode next){
	teamNode x = (teamNode) malloc(sizeof(struct teamnode));
  x->team = t;
  x->next = next;
  return x;
}

/*Cria o node para a equipa t e adiciona-o no fim da lista THeadList
  (na primeira posicao se a lista estiver vazia)*/
void addTeamNodeList(Team t){
  if (THeadList == NULL) {
		THeadList = newTeamNode(t, THeadList);
	}
	else {
		teamNode aux;
		aux = THeadList;
		while(aux->next != NULL){
			aux = aux->next;
		}
	  aux->next = newTeamNode(t, NULL);
	}
}

/*Elimina a linked list THeadList*/
void TfreeHead(teamNode node){
  if(node!=NULL){
    TfreeHead(node->next);
    free(node);
  }
}
