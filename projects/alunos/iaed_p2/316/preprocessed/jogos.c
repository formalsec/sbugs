#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "jogos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Jogos *init_jogos()
{
  Jogos *jogos = malloc(sizeof(Jogos));
  jogos->head = (jogos->last = 0);
  return jogos;
}

void free_jogo(node_jogos *jogo)
{
  free(jogo->nome);
  free(jogo);
}

void destroy_jogos(Jogos *jogos)
{
  node_jogos *jogo = 0;
  while (jogos->head)
  {
    jogo = jogos->head->next;
    free_jogo(jogos->head);
    jogos->head = jogo;
  }

  free(jogos);
}

node_jogos *cria_jogo(char *n, node_equipas *e1, node_equipas *e2, int s1, int s2)
{
  node_jogos *jogo = malloc(sizeof(node_jogos));
  jogo->nome = malloc((strlen(n) + 1) * (sizeof(char)));
  strcpy(jogo->nome, n);
  jogo->equipa1 = e1;
  jogo->equipa2 = e2;
  jogo->score1 = s1;
  jogo->score2 = s2;
  jogo->next = (jogo->previous = 0);
  if (s1 > s2)
  {
    equipa_vencedora(e1);
  }
  else
  {
    if (s2 > s1)
    {
      equipa_vencedora(e2);
    }
    else
    {
      
    }

  }

  return jogo;
}

void add_jogo(Jogos *jogos, node_jogos *jogo)
{
  jogo->previous = jogos->last;
  if (jogos->last)
  {
    jogos->last->next = jogo;
    jogos->last = jogo;
  }
  else
  {
    jogos->head = jogo;
    jogos->last = jogo;
  }

}

void remove_node_jogos(Jogos *jogos, node_jogos *jogo)
{
  if (jogo->previous == 0)
  {
    jogos->head = jogo->next;
  }
  else
  {
    jogo->previous->next = jogo->next;
  }

  if (jogo->next == 0)
  {
    jogos->last = jogo->previous;
  }
  else
  {
    jogo->next->previous = jogo->previous;
  }

  free_jogo(jogo);
}

void atualiza_scores_jogo(node_jogos *jogo, int s1, int s2)
{
  if ((jogo->score1 > jogo->score2) && (s1 <= s2))
  {
    equipa_diminui_jogos_ganhos(jogo->equipa1);
  }
  else
  {
    if ((jogo->score1 < jogo->score2) && (s1 >= s2))
    {
      equipa_diminui_jogos_ganhos(jogo->equipa2);
    }
    else
    {
      
    }

  }

  if ((s1 > s2) && (jogo->score1 <= jogo->score2))
  {
    equipa_vencedora(jogo->equipa1);
  }
  else
  {
    if ((s1 < s2) && (jogo->score1 >= jogo->score2))
    {
      equipa_vencedora(jogo->equipa2);
    }
    else
    {
      
    }

  }

  jogo->score1 = s1;
  jogo->score2 = s2;
}
