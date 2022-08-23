#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* inclusao dos header files necessarios */
#include "comandos.h"
#include "structs.h"


/*------------------------------------------------------------------------------
1 - comando a - adiciona um novo jogo
a_adiciona_jogo
------------------------------------------------------------------------------*/

/* auxiliar ao comando a que verifica a existencia de uma equipa */
int existe_equipa(team_n **hash_teams, char *name){
  int i;
  int indice = hash_function(name);
  team_n *auxiliar = hash_teams[indice];
  while (auxiliar != NULL && strcmp(auxiliar->name, name) != 0){
    auxiliar = auxiliar->next;
  }
  if (auxiliar == NULL){
    i = 0;
    return i;
  }
  else{
    i = 1;
    return i;
  }
}

/* auxiliar que aumenta/diminui o numero de vitorias de uma equipa na hash table dado um valor */
void altera_numero_vitorias(team_n **hash_teams, char *equipa, bool valor){
  int id = hash_function(equipa);
  team_n *t = hash_teams[id];

  /* sei que a equipa existe - quando a encontrar aumento as wins da mesma */
  while (t != NULL && strcmp(t->name, equipa) != 0){
    t = t->next;
  }
  if (valor == true){
    t->wins = t->wins + 1;
  }
  else if(valor == false){
    t->wins = t->wins - 1;
  }
}

/* funcao chamada na main */
game_n *a_adiciona_jogo(game_n **hash_table, team_n **hash_teams, game_n *head, int nl){
  game_n *t = NULL;
  game_n *auxiliar = NULL;
  bool valor;
  int id = 0;
  int i1;
  int i2;
  int score1 = 0;
  int score2 = 0;
  char *nome = malloc(sizeof(char) * (MAX_NAME + 1));
  char *equipa1 = malloc(sizeof(char) * (MAX_NAME + 1));
  char *equipa2 = malloc(sizeof(char) * (MAX_NAME + 1));

  scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);
  t = (game_n *)malloc(sizeof(game_n));

  /* alocacoes de memoria para strings */
  t->nome = (char *)malloc(sizeof(char) * strlen(nome) + 1);
  strcpy(t->nome, nome);
  t->equipa1 = (char *)malloc(sizeof(char) * strlen(equipa1) + 1);
  strcpy(t->equipa1, equipa1);
  t->equipa2 = (char *)malloc(sizeof(char) * strlen(equipa2) + 1);
  strcpy(t->equipa2, equipa2);

  t->score1 = score1;
  t->score2 = score2;
  t->next = NULL;
  t->lista = NULL;

  /* verificacao do primeiro erro - nome do jogo ja existente */
  id = hash_function(t->nome);
  auxiliar = hash_table[id];
  while (auxiliar != NULL){
    if (strcmp(auxiliar->nome, t->nome) == 0){
      printf("%d Jogo existente.\n", nl);
      free_jogo(t);
      free(nome);
      free(equipa1);
      free(equipa2);
      return head;
    }
    auxiliar = auxiliar->next;
  }

  /* verificacao do segundo erro - equipas inexistentes */
  i1 = existe_equipa(hash_teams, t->equipa1);
  if (i1 == 0){
    free_jogo(t);
    free(nome);
    free(equipa1);
    free(equipa2);
    printf("%d Equipa inexistente.\n", nl);
    return head;
  }
  i2 = existe_equipa(hash_teams, t->equipa2);
  if (i2 == 0){
    free_jogo(t);
    free(nome);
    free(equipa1);
    free(equipa2);
    printf("%d Equipa inexistente.\n", nl);
    return head;
  }

  /* aumentar as vitorias tanto na hash teams como na linked list das equipas */
  valor = true;
  /* aumentar o numero de vitorias */
  if (t->score1 > t->score2){
    /* aumento na hash table de equipas e na linked list das equipas */
    altera_numero_vitorias(hash_teams, t->equipa1, valor);
  }
  else if (t->score2 > t->score1){
    altera_numero_vitorias(hash_teams, t->equipa2, valor);
  }

  /* paramentros fornecidos com sucesso - coloco na hash table e na lista */
  inserir_hash_table(hash_table, t);
  head = inserir_na_head(head, t);

  free(nome);
  free(equipa1);
  free(equipa2);

  return head;
}




/*------------------------------------------------------------------------------
2- comando A - adiciona uma nova equipa
A_adiciona_equipa
------------------------------------------------------------------------------*/

/* funcao chamada na main */
team_n *A_adiciona_equipa(team_n **hash_teams, team_n *head_team, int nl){
  team_n *t;
  team_n *auxiliar = NULL;
  int id;
  char *name = malloc(sizeof(char) * (MAX_NAME + 1));

  scanf(" %[^:\n]", name);
  t = (team_n *)malloc(sizeof(team_n));
  /* alocacao de memoria pelo facto de ser uma string */
  t->name = (char *)malloc(sizeof(char) * strlen(name) + 1);
  strcpy(t->name, name);
  t->wins =0;
  t->next = NULL;
  t->lista = NULL;

  id = hash_function(t->name);
  auxiliar = hash_teams[id];

  /* verificacao do erro - caso a equipa ja exista */
  while (auxiliar != NULL){
    if (strcmp(auxiliar->name, t->name) == 0){
      printf("%d Equipa existente.\n", nl);
      free_equipa(t);
      free(name);
      return head_team;
    }
    auxiliar = auxiliar->next;
  }
  /* sucesso - inserir a equipa na hash table de equipas e na linked list de equipas */
  inserir_hash_teams(hash_teams, t);
  head_team = inserir_na_head_teams(head_team, t);
  free(name);
  return head_team;
}




/*------------------------------------------------------------------------------
3 - comando l - Lista todos os jogos pela ordem em que foram introduzidos
l_lista_jogos
------------------------------------------------------------------------------*/

/* funcao chamada na main - recursiva que imprime a lista dos jogos reversa */
void l_lista_jogos(game_n *head, int nl){
  game_n *a = head;
  if (a == NULL){
    return;
  }
  /* recursiva que retorna no ecra os jogos por odem inversa a colocada */
  l_lista_jogos(a->lista, nl);
  printf("%d %s %s %s %d %d\n", nl, a->nome, a->equipa1, a->equipa2, a->score1, a->score2);
}




/*------------------------------------------------------------------------------
4 - comando p - procura um jogo dado um nome
p_procura_jogo
------------------------------------------------------------------------------*/

/* funcao chamada na main */
void p_procura_jogo(game_n **hash_table, int nl){
  game_n *t = NULL;
  int id = 0;
  char *nome = malloc(sizeof(char) * (MAX_NAME + 1));
  /* solicitacao de um nome e respetivo id a partir da hash function */
  scanf(" %[^:\n]", nome);
  id = hash_function(nome);
  t = hash_table[id];

  /* se estiver vazio, nao tem qualquer jogo la */
  if (t == NULL){
    printf("%d Jogo inexistente.\n", nl);
    free(nome);
    return;
  }
  else{
    /* ciclo ate o t ser NULL ou ate encontrar o nome */
    while (t != NULL && strcmp(t->nome, nome) != 0){
      t = t->next;
    }
    /* se no fim o ponteiro ficar a NULL nao encontrei */
    if (t == NULL){
      printf("%d Jogo inexistente.\n", nl);
      free(nome);
      return;
    }
    /* encontro do nome */
    if (strcmp(t->nome, nome) == 0){
      printf("%d %s %s %s %d %d\n", nl, t->nome, t->equipa1, t->equipa2, t->score1, t->score2);
      free(nome);
      return;
    }
  }
}




/*------------------------------------------------------------------------------
5 - comando P - procura uma equipa dado um nome
P_procura_equipa
------------------------------------------------------------------------------*/

/* funcao chamda na main */
void P_procura_equipa(team_n **hash_teams, int nl){
  team_n *t = NULL;
  int id = 0;
  char *name = malloc(sizeof(char) * (MAX_NAME + 1));
  scanf(" %[^:\n]", name);
  id = hash_function(name);
  t = hash_teams[id];

  /* se estiver vazio nao tem qualquer equipa la */
  if (t == NULL){
    printf("%d Equipa inexistente.\n", nl);
    free(name);
    return;
  }
  else{
    /* ciclo ate t nao ser NULL ou encontrar o nome */
    while (t != NULL && strcmp(t->name, name) != 0){
      t = t->next;
    }
    if (t == NULL){
      printf("%d Equipa inexistente.\n", nl);
      free(name);
      return;
    }
    /* encontro o nome */
    if (strcmp(t->name, name) == 0){
      printf("%d %s %d\n", nl, t->name, t->wins);
      free(name);
      return;
    }
  }
}




/*------------------------------------------------------------------------------
6 - comando r - apaga um jogo
r_apaga_jogo
------------------------------------------------------------------------------*/

/* auxiliar que apaga o jogo da linked list dos jogos */
game_n *apaga (game_n *head, char *nome){
  game_n *t = head;
  game_n *anterior = NULL;

  while (t != NULL){
    if (strcmp(t->nome, nome) == 0){
      if (t == head){
        head = t->lista;
      }
      else{
        anterior->lista = t->lista;
      }
      free_jogo(t);
      break;
    }
    anterior = t;
    t = t->lista;
  }
  return head;
}

/* funcao chamada na main */
game_n *r_apaga_jogo(game_n **hash_table, team_n **hash_teams, game_n *head, int nl){
  game_n *t = NULL;
  game_n *anterior = NULL;
  bool valor;
  int id = 0;
  char *nome = malloc(sizeof(char) * (MAX_NAME + 1));
  scanf(" %[^:\n]", nome);
  id = hash_function(nome);
  t = hash_table[id];

  if (t == NULL){
    printf("%d Jogo inexistente.\n", nl);
    free(nome);
    return head;
  }
  else{
    while (t != NULL && strcmp(t->nome, nome) != 0){
      anterior = t;
      t = t->next;
    }
    /* se o t for NULL acaba - nao encontrei o jogo na entrada da hash table */
    if (t == NULL){
      printf("%d Jogo inexistente.\n", nl);
      free(nome);
      return head;
    }
    else{
      /* vou diminuir uma vitoria na hash teams e na linked list das equipas */
      valor = false;
      /* atualizacao de resultados caso o jogo exista */
      if (t->score1 > t->score2){
        /* a equipa 1 vai ter menos uma vitoria - atualizacao na hash teams e na linked list */
        altera_numero_vitorias(hash_teams, t->equipa1, valor);
      }
      else if (t->score1 < t->score2){
        /* tiro uma vitoria da equipa 2 na hash table de equipas e na lista */
        altera_numero_vitorias(hash_teams, t->equipa2, valor);
      }

      /* diferentes casos para apagar o jogo da hash table */
      /* se anterior e NULL quer dizer que o primeiro elemento era o jogo */
      if (anterior == NULL){
        hash_table[id] = t->next;
      }
      else{
        /* o jogo estava no meio */
        anterior->next = t->next;
      }
    }
  }
  /* apagar o jogo tambem da linked list dos jogos */
  head = apaga (head, nome);

  /*free do nome */
  free(nome);
  return head;
}




/*------------------------------------------------------------------------------
7 - comando s - altera o score de um jogo dado um nome
s_altera_score
------------------------------------------------------------------------------*/

/* auxiliar que atualiza as wins de cada equipa - por comparacao com os resultados antigos */
void muda_scores(int antigoscore1, int antigoscore2, team_n **hash_teams, game_n *t, bool valor){
  /* 1 caso */
  if (antigoscore1 > antigoscore2){
    if (t->score1 == t->score2){
      valor = false;
      /* atualizacao das vitorias da equipa1 na hash table */
      altera_numero_vitorias(hash_teams, t->equipa1, valor);
      /* atualizacao das vitorias da equipa1 na linked list */
    }
    else if (t->score1 < t->score2){
      /* valor false perde um jogo */
      valor = false;
      altera_numero_vitorias(hash_teams, t->equipa1, valor);
      /* valor true ganha um jogo */
      valor = true;
      altera_numero_vitorias(hash_teams, t->equipa2, valor);
    }
  }
  /* 2 caso */
  else if (antigoscore1 == antigoscore2){
    /* ganha um jogo */
    valor = true;
    if (t->score1 > t->score2){
      altera_numero_vitorias(hash_teams, t->equipa1, valor);
    }
    else if (t->score1 < t->score2){
      altera_numero_vitorias(hash_teams, t->equipa2, valor);
    }
  }
  /* 3 caso */
  else if (antigoscore1 < antigoscore2){
    if (t->score1 == t->score2){
      /* perde uma vitoria */
      valor = false;
      altera_numero_vitorias(hash_teams, t->equipa2, valor);
    }
    else if (t->score1 > t->score2){
      /* mais uma vitoria */
      valor = true;
      altera_numero_vitorias(hash_teams, t->equipa1, valor);
      /* menos uma vitoria */
      valor = false;
      altera_numero_vitorias(hash_teams, t->equipa2, valor);
    }
  }
}

/* funcao chamada na main */
void s_altera_score(game_n **hash_table, team_n **hash_teams, int nl){
  game_n *t = NULL;
  bool valor = false;
  int id = 0;
  int score1, score2;
  int antigoscore1, antigoscore2;
  char *nome = malloc(sizeof(char) * (MAX_NAME + 1));
  scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);
  id = hash_function(nome);
  t = hash_table[id];

  if (t == NULL){
    printf("%d Jogo inexistente.\n", nl);
    free(nome);
    return;
  }
  else{
    while (t != NULL && strcmp(t->nome, nome) != 0){
      t = t->next;
    }
    if (t == NULL){
      printf("%d Jogo inexistente.\n", nl);
      free(nome);
      return;
    }
    if (strcmp(t->nome, nome) == 0){
      /* encontrei o jogo vou alterar os valores antigos pelos novos */
      antigoscore1 = t->score1;
      antigoscore2 = t->score2;
      t->score1 = score1;
      t->score2 = score2;
    }
  }
  /* atualiza os scores de cada equipa tendo em conta a mudanca de resultado */
  muda_scores(antigoscore1, antigoscore2, hash_teams, t, valor);

  free(nome);
}




/*------------------------------------------------------------------------------
8 - comando g - lista equipas que ganharam mais jogos por ordem lexicografica
g_equipas_vencedoras
------------------------------------------------------------------------------*/

/* auxiliar que ve qual e o numero maximo de vitorias */
int encontrar_maximo(team_n *head_team){
  team_n *aux = head_team;
  int maximo = 0;
  while (aux != NULL){
    if (aux->wins > maximo){
      maximo = aux->wins;
    }
    aux = aux->lista;
  }
  return maximo;
}

/* auxiliar que ve quantas equipas tem o numero de maximo de vitorias */
int encontrar_numero_maximos(team_n *head_team, int maximo){
  team_n *aux = head_team;
  int n_maximos = 0;
  while (aux != NULL){
    if (aux->wins == maximo){
      n_maximos++;
    }
    aux = aux->lista;
  }
  return n_maximos;
}

/* auxiliar da funcao qsort de forma a ordenar as strings lexicograficamente */
int comparar_strings(const void *nome1, const void *nome2){
  return strcmp(*(char **)nome1, *(char **)nome2);
}

/* funcao chamada na main */
void g_equipas_vencedoras(team_n *head_team, int nl, int maximo, int n_maximos){
  team_n *aux = NULL;
  int i = 0;
  int indice = 0;
  char **lista;
  lista = malloc(sizeof(char *) * n_maximos);

  /* caso em que nao existe equipas para mostrar */
  if (maximo == 0 && n_maximos == 0){
    free(lista);
    return;
  }

  /* criar um array de strings de forma a colocar os nomes das equipas la */
  aux = head_team;
  while (aux != NULL){
    if (aux->wins == maximo){
      lista[indice] = aux->name;
      indice++;
    }
    aux = aux->lista;
  }

  /* ordenar o nome das equipas por ordem lexicografica */
  qsort(lista, n_maximos, sizeof(char *), comparar_strings);

  /* imprimir as equipas */
  printf("%d Melhores %d\n", nl, maximo);

  for (i = 0; i < n_maximos; i++){
    printf("%d * %s\n", nl, lista[i]);
  }

  free(lista);
  return;
}