#include "MATCHHTABLE.h"
#include "TEAM.h"
#include "MATCH.h"

/*Funcao de dispersao para guardar os jogos na hash table.*/
int hashM(char* v, int m){
  int h = 0, a = 127;
  for (; *v != '\0'; v++)
    h = (a*h + *v) % m;
  return h;
return h;
}

/*Inicializa a hash table*/
void matchInit(){
  int i;
  matchHeads = (matchNode*)malloc(MAX*sizeof(matchNode));
  for (i = 0; i < MAX; i++){
    matchHeads[i] = NULL;
  }
}

/*Insere o jogo match na linked list do node da hashtable, correspondente.
  Calcula, atraves da funcao de dispersao hashM, utilizando o nome do jogo,
  o indice da hash table onde colocar o novo jogo.
  Posteriormente, percorre a lista ate ao fim, onde a coloca o novo jogo.*/
void matchInsert(Match match){
  int i = hashM(match->name, MAX);
  if (matchHeads[i] == NULL){
    matchHeads[i] = (matchNode)malloc(sizeof(struct matchnode));
    matchHeads[i]->match = match;
    matchHeads[i]->next = NULL;
  }
  else{
    matchNode t, prev;
    matchNode newNode = (matchNode)malloc(sizeof(struct matchnode));
    newNode->match = match;
    newNode->next = NULL;
    for(t = matchHeads[i], prev = NULL; t!=NULL; prev = t, t = t->next){}
      prev->next = newNode;
  }
  addMatchNodeList(match);
}

/*"Elimina" o jogo match da hash table. Muda o nome do jogo para ':', visto que
  o nome dos jogos nunca e ':', ficando o jogo, assim, inutilizado. Os jogos
  propriamente ditos sao apenas eliminados no final.*/
void matchDelete(Match match){
  matchNode t, prev;
  int i = hashM(match->name, MAX);
  for(t = matchHeads[i], prev = NULL; t!=NULL; prev = t, t = t->next){
    if(strcmp(t->match->name, match->name)==0){
      if(t == matchHeads[i]){
        matchHeads[i] = t->next;
      }
			else{
				prev->next = t->next;
			}
      strcpy(t->match->name,":");

			free(t);
			break;
    }
  }
}

/*Devolve o node onde o jogo, de nome name, se encontra. Primeiro calcula, atraves da funcao
  de dispersao, hashM, a posicao na hashtable e depois percorre a linked list ate encontrar
  a equipa com o nome introduzido como argumento da funcao*/
matchNode matchSearch(char* name){
  int i = hashM(name, MAX);
  matchNode aux;
  for(aux = matchHeads[i]; aux!=NULL; aux=aux->next){
    if(strcmp(aux->match->name, name)==0){
      return aux;
    }
  }
  return NULL;
}

/*Funcao auxiliar da matchHashFREE, que elimina cada linked list da hashtable*/
void matchHashListFREE(matchNode m){
  if (m!=NULL){
    matchHashListFREE(m->next);
    free(m);
  }
}

/*Apaga a hashtable*/
void matchHashFREE(){
  int i;
  for(i=0; i<MAX; i++){
    matchHashListFREE(matchHeads[i]);
  }
}

/*Inicilizacao da linked list que guarda os jogos por ordem de introducao*/
void MlistInit(){
  head = NULL;
	tail = NULL;
}

/*Cria um novo node com o jogo match e o ponteiro, next, para o node seguinte*/
matchNode newMatchNode(Match match, matchNode next){
	matchNode x = (matchNode) malloc(sizeof(struct matchnode));
	x->match = match;
  x->next = next;
  return x;
}

/*Cria o node para o jogo match e adiciona-o no fim da linked list
  (na primeira posicao, head, se a lista estiver vazia)*/
void addMatchNodeList(Match match){
  if (head == NULL) {
		head = tail = newMatchNode(match, head);
	}
	else {
	  tail->next = newMatchNode(match, tail->next);
	  tail = tail->next;
	}
}

/*Elimina a linked list cujo primeiro node e head e o ultimo a tail*/
void MfreeHead(matchNode node){
  if(node!=NULL){
		freeMatch(node->match);
    MfreeHead(node->next);
    free(node);
  }
}
