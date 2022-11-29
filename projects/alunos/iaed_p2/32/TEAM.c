#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "TEAM.h"

/*
Recebe o nome da equipa a adicionar
Verifica se existe e adiciona na hashtable das equipas*/
void NewTeam(int line){
  int i;
  link l;
  char* name = can_fail_malloc(sizeof(char)*MAX_STR);
  scanf(" %[^:\n]",name);
  getchar();


  i = hash_team(name);
  l = searchHashTeam(name, t_heads[i]);

  if(!l){
    t_heads[i] = insertHashTeam(name, t_heads[i]);
    freeTeamList(teams_list);
    TeamListInit();
  }
  else{
    printf("%d Equipa existente.\n", line);
  }
  free(name);
}

/*
Recebe o nome da equipa a procurar
Chama a funcao auxiliar da hashtable*/
void SearchTeam(int line){
  char* name = can_fail_malloc(sizeof(char)*MAX_STR);
  link l;
  int i;

  scanf(" %[^:\n]",name);
  getchar();

  i = hash_team(name);
  l = searchHashTeam(name, t_heads[i]);
  if(l !=NULL){
    printf("%d %s %d\n", line, name, l->team->wins);
  }
  else{
    printf("%d Equipa inexistente.\n", line);
  }
  free(name);
}

/*
Verifica se a lista auxiliar esta vazia
Se estiver, percorre a hashtable para determinar as equipas com mais vitorias
Caso contrario, faz logo print das da lista ligada
NOTA: Se nao estiver nula quer dizer que nao ocorreu nenhuma alteracao desde
  a ultima chamada a funcao g logo podemos fazer logo print da lista*/
void MaxWins(int line){
  int i;
  int max = -1;
  link l, index;
  TeamsList gl;

  getchar();

  if(teams_list == NULL){
    for(i = 0; i<M; i++){
      for(index = t_heads[i]; index != NULL; index = index->next){
        if(index->team->wins > max){
          if(teams_list != NULL){
            freeTeamList(teams_list);
            TeamListInit();
          }
          max = index->team->wins;
          insertTeamList(index->team);
        }
        else if(index->team->wins == max){
          insertTeamList(index->team);
        }
      }
    }
  }

  if(teams_list != NULL){
    i = hash_team(teams_list->team->name);
    l = searchHashTeam(teams_list->team->name, t_heads[i]);

    printf("%d Melhores %d\n", line, l->team->wins);

    for(gl = teams_list; gl != NULL; gl = gl->next){
      printf("%d * %s\n", line, gl->team->name);
    }
  }
}


/*:::::::::::::::::::::AUXILIARES:::::::::::::::::::::*/

void increaseWins(char* name){
  int i = hash_team(name);
  link l = searchHashTeam(name, t_heads[i]);
  l->team->wins++;
}

void decreaseWins(char* name){
  int i = hash_team(name);
  link l = searchHashTeam(name, t_heads[i]);
  l->team->wins--;
}

/*:::::::::::::::::::::AUXILIARES HASHTABLE:::::::::::::::::::::*/

/*
Receb o nome da equipa
Guarda espaco para um link e guarda o nome da equipa
Retorna o novo link*/
link newTeamLink(char* name){
  size_t size;
  link l = can_fail_malloc(sizeof(struct node));
  l->team = can_fail_malloc(sizeof(struct team));

  size = strlen(name) + 1;
  l->team->name = can_fail_malloc(sizeof(char)*size);
  strncpy(l->team->name, name, size);
  l->team->wins = 0;
  l->next = NULL;

  return l;
}

/*funcao hash para as equiipas*/
int hash_team(char* name){
  return name[0]%M;
}

/*inicializacao da hashtable das equipas*/
void TeamInit(){
  int i;
  teams_list = NULL;
  teams_list_tail = NULL;

  t_heads = (link*)can_fail_malloc(sizeof(link)*M);
  for (i = 0; i < M; i++)
    t_heads[i] = NULL;
}

/*
Recebe o nome da equipa a adicionar e a posicao da hashtable correspondente
*/
link insertHashTeam(char* name, link head){
  link aux, prev;

  if(head == NULL){
    head = newTeamLink(name);
  }
  else{
    for(aux = head, prev = NULL; aux != NULL; prev = aux,aux = aux->next){
      if(strcmp(aux->team->name, name)<0){
        if(aux->next == NULL){
          aux->next = newTeamLink(name);
          break;
        }
      }
      else{
        if(aux==head){
          head = newTeamLink(name);
          head->next = aux;
          break;
        }
        else{
          prev->next = newTeamLink(name);
          (prev->next)->next = aux;
          break;
        }
      }
    }
  }
  return head;
}

/*
Recebe o nome da equipa e a posicao da hashtable correspondente
previamente calculada*/
link searchHashTeam(char* name, link head){
  link aux;
  for (aux = head; aux != NULL; aux = aux -> next) {
		if (strcmp(aux->team->name, name)==0)
			return aux;
  }
  return NULL;
}

/*
funcao auxiliar para dar free a hashtable*/
void free_list(link head){
  if(head != NULL){
    free(head->team->name);
    free(head->team);
    free_list(head->next);
    free(head);
  }
}

/*
free da hashtable*/
void freeTeamHash(){
  int i;
  for(i=0;i<M;i++){
    free_list(t_heads[i]);
  }
}


/*:::::::::::::::::::::AUXILIARES ESTRUTURA NOMES EQUIPAS:::::::::::::::::::*/

/*
free da lista ligada*/
void freeTeamList(TeamsList t){
  if(t != NULL){
    freeTeamList(t->next);
    free(t);
  }
}

/*
free da lista ligada*/
void TeamListInit(){
  teams_list = NULL;
  teams_list_tail = NULL;
}

/*
Recebe uma equipa e adiciona a lista ligada auxiliar*/
void insertTeamList(Team team) {
  if(teams_list ==NULL){
    teams_list = teams_list_tail = newTeamIndex(team);

  }
  else{
    teams_list_tail->next = newTeamIndex(team);
    teams_list_tail = teams_list_tail->next;
  }
}

/*
Recebe um equipa
Cria um novo TeamsList com a equipa guardada*/
TeamsList newTeamIndex(Team team){
  TeamsList node = can_fail_malloc(sizeof(struct team_name));
  node->team = team;
  node->next = NULL;
  return node;
}
