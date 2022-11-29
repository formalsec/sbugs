#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "estruturas_info.h"  

game* NEWGAME(char* name_game, char* team1, char* team2, int score1, int score2, int order){
  game *newgame = can_fail_malloc(sizeof(game)); /* guardar memoria para o node do jogo */
  newgame->name_game = can_fail_malloc(sizeof(char) * (strlen(name_game)+1)); /* guardar memoria para os caracteres das equipas e do nome do jogo */
  newgame->team1 = can_fail_malloc(sizeof(char) * (strlen(team1)+1));
  newgame->team2 = can_fail_malloc(sizeof(char) * (strlen(team2)+1));
  newgame->name_game = strcpy(newgame->name_game, name_game); /* copiar o nome do jogo do input para o nome do jogo do node */
  newgame->team1 = strcpy(newgame->team1, team1); /* copiar os nomes das equipas do input para as equipas do node do jogo */
  newgame->team2 = strcpy(newgame->team2, team2);
  newgame->score1 = score1;/* por os scores do input para o nodo do jogo */
  newgame->score2 = score2; 
  newgame->order = order;
  newgame->next = NULL; /* por o proximo node a NULL */
  return newgame; /* retorna o novo jogo com as novas informacoes do input */            
}

team* NEWTEAM(char* name_team){ /* mesmo raciocinio que o NEWGAME */
  team *newteam = can_fail_malloc(sizeof(team));
  newteam->name_team = can_fail_malloc(sizeof(char) * (strlen(name_team)+1));
  newteam->name_team = strcpy(newteam->name_team, name_team);
  newteam->wins = 0; /* inicializar as vitorias a 0 */
  newteam->next = NULL;
  return newteam;
 }

game* PutsAsHeadListGame(game* head, char* name_game, char* team1, char* team2, int score1, int score2, int order){
  game* newgame = NEWGAME(name_game, team1, team2, score1, score2, order);
  newgame->next = head; /* poe o jogo recebido do NEWGAME como cabeca da linked list */
  return newgame;
 }

team* PutsAsHeadListTeam(team* head, char* name_team){
  team *newteam = NEWTEAM(name_team);  /* poe a equipa recebida do NEWTEAM como cabeca da linked list */
  newteam->next = head;
  return newteam;
 }

int ReturnsHashGameIndex(char *name_game){ /* convertem os caracteres do nome do jogo num numero (que vai ser um indice) */
  int h = 0, a = 127;
 	for (; *name_game != '\0'; name_game++)
 		h = (a*h + *name_game) % SIZE;
 	return h;
} 

int ReturnsHashTeamIndex(char* name_team){ /* convertem os caracteres do nome da equipa num numero (que vai ser um indice) */
 	int h = 0, a = 127;
 	for (; *name_team != '\0'; name_team++)
 		h = (a*h + *name_team) % SIZE;
 	return h;
}

game* LooksUpInGameHash(game** hashtablegame, char* name_game){
  int index = ReturnsHashGameIndex(name_game);
  game *aux; /* aux e do tipo da struct game */
  aux = hashtablegame[index]; /* aux passa a estar numa posicao random da hashtable, usando o indice obtido na funccao em cima (hash()) */
  while (aux != NULL){ /* percorre a linked list correspondente a posicao da hashtable obtida em cima */
    	if(strcmp(aux->name_game, name_game) == 0){
  		  return aux; /* se algum nome dos nodes de jogos da linked list percorrida for igual ao input, da return a esse node */
      }
  aux = aux->next; /* se nao for igual, passa para o proximo */ 
  }
  return aux;
}

void FreeGameInfo(game* t){  /* faz free de todas as componentes do node do jogo, e do node em si no fim */
  free(t->name_game);
  free(t->team1);
  free(t->team2);
  free(t); 
}

game* DeleteGame(game* head, char* name_game){ /* faz delete do node do jogo e retorna a nova cabeca dessa linked list ja sem esse node */
  game* t; 
  game* prev;
  for (t = head, prev = NULL; t != NULL; prev = t, t = t->next){
    if (strcmp(t->name_game, name_game) == 0){
      if (t == head){
        head = t->next;
      }
      else{
        prev->next = t->next;
      }
      FreeGameInfo(t);         
      return head;
    }
  }
  return head;
}

team* LooksUpInTeamHash(team** hashtableteam, char* name_team){ /* o mesmo raciocinio que "LooksUpInGameHash" */
  int index = ReturnsHashTeamIndex(name_team);
  team *aux;
  aux = hashtableteam[index];
  while(aux != NULL){
  	if(strcmp(aux->name_team, name_team) == 0){
  		return aux;
    }
  aux = aux->next;
  }
  return aux;
 }

void InitializesHashTableGame(game** hashtablegame){ /* Inicializa todos os indices da hashtable a NULL */
  int i;
  for (i = 0; i < SIZE; i++) hashtablegame[i] = NULL;
}

 void InitializesHashTableTeam(team** hashtableteam){ /* Inicializa todos os indices da hashtable a NULL */
 	int i;
 	for (i = 0; i < SIZE; i++) hashtableteam[i] = NULL;
 }

/* ********************* FUNCOES PRINCIPAIS ****************** */

void AddsGame(char* name_game, char* team1, char* team2, int score1, int score2, game** hashtablegame, team** hashtableteam, int NL, int order){
	int index;
	team *aux;
	game *auxgame;
	if (LooksUpInGameHash(hashtablegame, name_game) != NULL){ /* se o node do jogo encontrado pelo nome do jogo do input nao for NUL... */
		printf("%d Jogo existente.\n", NL);
    }
    else if (LooksUpInTeamHash(hashtableteam, team1) == NULL){ /* se o node da equipa encontrada pelo nome da equipa 1 do input for NULL... */
    	printf("%d Equipa inexistente.\n", NL);
    }
    else if (LooksUpInTeamHash(hashtableteam, team2) == NULL){ /* se o node da equipa encontrada pelo nome da equipa 2 do input for NULL... */
    	printf("%d Equipa inexistente.\n", NL);
    }
    else{
         index = ReturnsHashGameIndex(name_game); /* converter o nome do input num indice */
         hashtablegame[index] = PutsAsHeadListGame(hashtablegame[index], name_game, team1, team2, score1, score2, order); /* o jogo do input passa a ser o head da linked list pertencente ao index da hashtable */
         auxgame = LooksUpInGameHash(hashtablegame, name_game); /* retorna o node do jogo correspondente ao nome do jogo do input */

        if (auxgame->score1 > auxgame->score2){ /* se o score1 do jogo for maior que o score2, acede as vitorias do node da equipa 1 e incrementa-as em 1 */
             aux = LooksUpInTeamHash(hashtableteam, team1);
             aux->wins += 1; 
        }
        else if(auxgame->score1 < auxgame->score2){ /* se o score2 do jogo for maior que o score1, acede as vitorias do node da equipa 2 e incrementa-as em 1 */
       	     aux = LooksUpInTeamHash(hashtableteam, team2);
       	     aux->wins += 1;
        }
    }
}

void AddsTeam(char* name_team, team** hashtableteam, int NL){ 
	int index;
	if (LooksUpInTeamHash(hashtableteam, name_team) != NULL){ /* se o node da equipa encontrada pelo nome dda equipa do input for diferente de NULL... */
		printf("%d Equipa existente.\n", NL);
	}
	else{
		index = ReturnsHashTeamIndex(name_team);
		hashtableteam[index] = PutsAsHeadListTeam(hashtableteam[index], name_team);
	} /* ponho a equipa recebida como cabeca da linked list pertencente ao index da hashtable */
}

void PrintsGame(char* name_game, game** hashtablegame, int NL){
     game *auxgame;
     if (LooksUpInGameHash(hashtablegame, name_game) == NULL){
     	printf("%d Jogo inexistente.\n", NL); /* se o node do jogo encontrado pelo nome do jogo do input nao for NUL... */ 
     }
     else{
     	auxgame = LooksUpInGameHash(hashtablegame, name_game); /* obtem o node do jogo cujo nome dele e igual ao do input */
     	printf("%d %s %s %s %d %d\n", NL, auxgame->name_game, auxgame->team1, auxgame->team2, auxgame->score1, auxgame->score2);
     } /* printa toda a informacao do node do jogo */

}

void PrintsTeam(char* name_team, team** hashtableteam, int NL){
	team *aux;
	if (LooksUpInTeamHash(hashtableteam, name_team) == NULL){
		printf("%d Equipa inexistente.\n", NL); /* se o node da equipa encontrada pelo nome da equipa do input for NULL... */
	}
	else{
		aux = LooksUpInTeamHash(hashtableteam, name_team); /* obtem o node da equipa cujo nome dela e igual ao do input */
		printf("%d %s %d\n", NL, aux->name_team, aux->wins); /* da print as duas componentes do node da euqipa */
	}
}

void ChangesScore(char* name_game, int score1, int score2, game** hashtablegame, team** hashtableteam, int NL){
    game* oldgame;
    team* aux;
    team* aux1;
    team* aux2;
    oldgame = LooksUpInGameHash(hashtablegame, name_game); /* obtem o node do jogo cujo nome dele e o do input, sem mudancas de score */
    if (oldgame == NULL){ /* se for NULL... */
      printf("%d Jogo inexistente.\n", NL);
    } /* existem 3 grandes possiveis resultados, e dentro deles e necessario fazerem-se alteracoes as vitorias em dois casos de tres possiveis, num total de 9 resultados possiveis (fazendo-se altercoes em 6 apenas) */
    else{ /* depois de se obter o node do jogo, acede-se ao nome da equipa necessaria nesse node de jogo, e encontra-se o node de equipa correspondente */
      if (oldgame->score1 > oldgame->score2){ 
        if (score1 == score2){ 
          aux = LooksUpInTeamHash(hashtableteam, oldgame->team1); /*  */
          aux->wins -= 1; /* fazem-se as alteracoes necessarias as vitorias dependendo dos scores do jogo */
        } 
        else if(score1 < score2){
          aux1 = LooksUpInTeamHash(hashtableteam, oldgame->team1);
          aux2 = LooksUpInTeamHash(hashtableteam, oldgame->team2);
          aux1->wins -= 1;
          aux2->wins += 1;
        }
      }
      else if (oldgame->score1 == oldgame->score2){
        if (score1 > score2){
          aux = LooksUpInTeamHash(hashtableteam, oldgame->team1);
          aux->wins += 1;
        }
        else if(score1 < score2){
          aux = LooksUpInTeamHash(hashtableteam, oldgame->team2);
          aux->wins += 1;
        }
      }
      else if (oldgame->score1 < oldgame->score2){
        if (score1 > score2){
          aux1 = LooksUpInTeamHash(hashtableteam, oldgame->team1);
          aux2 = LooksUpInTeamHash(hashtableteam, oldgame->team2);
          aux1->wins += 1;
          aux2->wins -= 1;
        }
        else if (score1 == score2){
          aux = LooksUpInTeamHash(hashtableteam, oldgame->team2);
          aux->wins -= 1;
        }
      }
    oldgame->score1 = score1; /* por fim altera-se o score do jogo antigo para o score do novo jogo dado no input */
    oldgame->score2 = score2;
    }
}


void ListsGames(game** hashtablegame, int order, int NL){
  game* aux;
  int i, e;
  for(e = 0; e < order; e++){ /* order faz parte do node do jogo, sendo um numero unico para cada um. Relaciona a ordem em que cada um foi criado. E incrementado depois de criar um jogo (na main) */
    for(i = 0; i < MAX_HASH; i++){ 
      aux = hashtablegame[i];
      while(aux != NULL){
        if(aux->order == e){ /* se existir na hashtable um jogo com esse order da print de toda a informacao do jogo */
          printf("%d %s %s %s %d %d\n", NL, aux->name_game, aux->team1, aux->team2, aux->score1, aux->score2);
          break;
        }
        aux = aux->next;
      }
    }
  }
}

void ErasesGame(char* name_game, game** hashtablegame, team** hashtableteam, int NL){
  game* erasinggame;
  team* aux;
  int index = ReturnsHashGameIndex(name_game); /* da um indice aleatorio para ser utilizado na hashtable */
  erasinggame = LooksUpInGameHash(hashtablegame, name_game); /* obtem-se o jogo a apagar atraves do nome do jogo do input */

  if (erasinggame == NULL){ /* se o node do jogo encontrado pelo nome do jogo do input nao for NUL... */ 
      printf("%d Jogo inexistente.\n", NL);
  }
  else if (erasinggame->score1 > erasinggame->score2){ /* mesmo raciocinio que na "ChangesScore" mas agora ha apenas duas alteracoes a fazer porque o score nao muda */
    aux = LooksUpInTeamHash(hashtableteam, erasinggame->team1);
    aux->wins -= 1; /* reduz as vitorias a equipa que era vitoriosa no jogo a apagar */
  }
  else if (erasinggame->score1 < erasinggame->score2){
    aux = LooksUpInTeamHash(hashtableteam, erasinggame->team2);
    aux->wins -= 1;
  }
  hashtablegame[index] = DeleteGame(hashtablegame[index], name_game); 
} /* atualiza a linked list para estar ja sem o node do jogo que se quer apagar */

int main(){
	int NL = 1;
    int running = 1;
    int c;
    int score1 = 0; /* declarar as variaveis do input */
    int score2 = 0;
    int order = 0;
    char name_team[MAX_TITLE]; 
    char name_game[MAX_TITLE];
    char team1[MAX_TEAM];
    char team2[MAX_TEAM];
    team *hashtableteam[SIZE]; /* criacao da hashtable das equipas */
    game *hashtablegame[SIZE]; /* criacao da hashtable dos jogos */
  	InitializesHashTableTeam(hashtableteam); /* inicializar todos os indices da hashtableteam a NULL */
  	InitializesHashTableGame(hashtablegame); /* inicializar todos os indices da hashtablegame a NULL */
	while (running == 1){
		switch(c = getchar()){

			case 'A':
			  getchar();
			  scanf("%[^:\n]", name_team);
			  AddsTeam(name_team, hashtableteam, NL);
			  NL++;
			  break;

			case 'P':
			  getchar();
			  scanf("%[^:\n]", name_team);
			  PrintsTeam(name_team, hashtableteam, NL);
		    NL++;
			  break;

			case 'a':
			  getchar();
			  scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name_game, team1, team2, &score1, &score2);
			  AddsGame(name_game, team1, team2, score1, score2, hashtablegame, hashtableteam, NL, order);
			  NL++;
        order++; /* o order e sempre incrementado depois de cada chamada desta funcao, desta forma, associa cada jogo a um numero pela ordem em que foi criado */
			  break;

			case 'p':
			  getchar();
			  scanf("%[^:\n]", name_game);
			  PrintsGame(name_game, hashtablegame, NL);
		    NL++;
			  break;

      case 's':
        getchar();
        scanf("%[^:\n]:%d:%d", name_game, &score1, &score2);
        ChangesScore(name_game, score1, score2, hashtablegame, hashtableteam, NL);
        NL++;
        break;

      case 'l':
        getchar();
        ListsGames(hashtablegame, order, NL);
        NL++;
        break;

      case 'r':
        getchar();
        scanf("%[^:\n]", name_game);
        ErasesGame(name_game, hashtablegame, hashtableteam, NL);
        NL++;
        break;

			case 'x':
			  running = 0;
			  break;
		}
	}
  return 0;
}

