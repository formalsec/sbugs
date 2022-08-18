#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipa.h"
#include "jogo.h"
#include "string_list.h"
#include "strdup.h"


/* Estruturas utilizadas: */
/* 	*duas hashtables para 2 structs diferentes usando external chaining */
/*	*Lista ligada para strings */

/* Variaveis Globais */
char str[1023], e1[1023], e2[1023];
int NL = 1; /* variavel que controla o numero da linha no output*/

void comm_A(HT_E Equipas, link *leaderboard)
/* Adicionar uma equipa */
{
  scanf(" %[^:\n]", str);
  if (searchEquipa(Equipas, str) != NULL)
  {
    printf("%d Equipa existente.\n", NL);
    return;
  }
  /* Adicionar a hashtable de equipas*/
  insertEquipa(Equipas, str);
  /* adicionar o nome da equipa, ordenadamente*/ 
  insertSorted(leaderboard, str);
}

void comm_P(HT_E Equipas)
{
/* Procurar uma equipa*/
  Equipa *ptr;
  scanf(" %[^:\n]", str);
  ptr = searchEquipa(Equipas, str);
  if (ptr == NULL)
  {
    printf("%d Equipa inexistente.\n", NL);
    return;
  }
  printf("%d %s %d\n", NL, ptr->name, ptr->wins);
}

void comm_a(HT_J Jogos, HT_E Equipas, link *inputJogos)
{
/* Adicionar um jogo */
  int s1, s2;
  Equipa *ptr_e1, *ptr_e2;
  Jogo *ptr;
  scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", str, e1, e2, &s1, &s2);
  ptr_e1 = searchEquipa(Equipas, e1);
  ptr_e2 = searchEquipa(Equipas, e2);
  if (ptr_e1 == NULL || ptr_e2 == NULL)
  {
    printf("%d Equipa inexistente.\n", NL); 
    return;
  }
  ptr = searchJogo(Jogos, str);
  if (ptr != NULL)
  {
    printf("%d Jogo existente.\n", NL);
    return;
  }
  /* Adicionar a hashtable de jogos*/
  insertJogo(Jogos, str, e1, e2, s1, s2);
  /* Adicionar a lista de jogos pela ordem introduzida*/
  append(inputJogos, str);
  /* incrementar uma vitoria ao vencedor*/
  if (s1 > s2) incWin(Equipas, e1, 1);
  else if (s1 < s2) incWin(Equipas, e2, 1);
}

void comm_p(HT_J Jogos)
{
  /* Procurar um jogo*/
  Jogo *ptr;
  scanf(" %[^:\n]", str);
  ptr = searchJogo(Jogos, str);
  if (ptr == NULL)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  printf("%d %s %s %s %d %d\n", NL, ptr->name, ptr->equipa1, ptr->equipa2, ptr->score1, ptr->score2);
}

void comm_l(HT_J Jogos, link *inputJogos)
{
/* Listar os jogos pela ordem que foram introduzidos*/
  link x;
  Jogo *ptr;
  for (x = *inputJogos; x != NULL; x = x->next)
  {
    ptr = searchJogo(Jogos, x->str);
    printf("%d %s %s %s %d %d\n", NL, ptr->name, ptr->equipa1, ptr->equipa2, ptr->score1, ptr->score2);
  }
}

void comm_r(HT_J Jogos, HT_E Equipas, link *inputJogos)
{
/* remover jogo*/
  Jogo *ptr;
  scanf(" %[^:\n]", str);
  ptr = searchJogo(Jogos, str);
  if (ptr == NULL)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  if (ptr->score1 > ptr->score2) incWin(Equipas, ptr->equipa1, 0);
  else if (ptr->score1 < ptr->score2) incWin(Equipas, ptr->equipa2, 0);
  /* remove da hashtable de jogos*/
  removeJogo(Jogos, str);
  /* remove da lista de jogos pela ordem introduzida*/
  removeStr(inputJogos, str);
}

void comm_s(HT_J Jogos, HT_E Equipas)
{
/* altera o score de um jogo*/
  int s1, s2;
  Jogo *ptr;
  scanf(" %[^:\n]:%d:%d", str, &s1, &s2);
  ptr = searchJogo(Jogos, str);
  if (ptr == NULL)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  /* decrementa uma vitoria ao vencedor antes de mudar*/
  if (ptr->score1 > ptr->score2) incWin(Equipas, ptr->equipa1, 0);
  else if (ptr->score1 < ptr->score2) incWin(Equipas, ptr->equipa2, 0);
  /* incrementa uma vitoria ao novo vencedor*/
  if (s1 > s2) incWin(Equipas, ptr->equipa1, 1);
  else if (s1 < s2) incWin(Equipas, ptr->equipa2, 1);
  ptr->score1 = s1; ptr->score2 = s2;
}

void comm_g(HT_E Equipas, link * leaderboard)
{
  /* encontra as equipas com mais vitorias*/
  int max = 0, i;
  link_e x;
  link y;
  Equipa *ptr;
  /* encontra o numero maximo de vitorias*/
  for (i = 0; i < Equipas->M; i++)
  {
    for(x = Equipas->L[i]; x != NULL; x = x->next)
    {
      if (x->e.wins > max) max = x->e.wins;
    }
  }
  printf("%d Melhores %d\n", NL, max);
  /* encontra as equipas com numero de vitorias igual ao maximo na lista cujo as equipas ja estao ordenadas lexicograficamente*/
  for (y = *leaderboard; y != NULL; y = y->next)
  {
    ptr = searchEquipa(Equipas, y->str);
    if (ptr->wins == max)
    {
      printf("%d * %s\n", NL, ptr->name);
    }
  }
}


int main(void)
{
  HT_J Jogos = initJogo(10);
  HT_E Equipas = initEquipa(10);
  link inputJogos = NULL, leaderboard = NULL;
  char c = getchar();
  while (c != 'x')
  {
    switch (c)
    {
      case 'a':
        comm_a(Jogos, Equipas, &inputJogos);
        NL++;
        break;

      case 'l':
        comm_l(Jogos, &inputJogos);
        NL++;
        break;
      
      case 'p':
        comm_p(Jogos);
        NL++;
        break;

      case 'r':
        comm_r(Jogos, Equipas, &inputJogos);
        NL++;
        break;

      case 's':
        comm_s(Jogos, Equipas);
        NL++;
        break;

      case 'A':
        comm_A(Equipas, &leaderboard);
        NL++;
        break;

      case 'P':
        comm_P(Equipas);
        NL++;
        break;

      case 'g':
        comm_g(Equipas, &leaderboard);
        NL++;
        break;
    }
    c = getchar();
  }
  return 0;
}

