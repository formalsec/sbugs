#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "tabdispercao.h"
#include <stdlib.h>
#include <string.h>


int hash(Chave v, int m)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (m - 1))
    h = ((a * h) + (*v)) % m;

  return h;
}

pTabEquipas inicia_te(int max)
{
  int i;
  int m = 2 * max;
  pTabEquipas tab_dispercao = malloc(sizeof(struct tab_equipas));
  tab_dispercao->equipas = malloc(m * (sizeof(pEquipa)));
  tab_dispercao->max = m;
  tab_dispercao->N = 0;
  for (i = 0; i < m; i++)
    tab_dispercao->equipas[i] = 0;

  return tab_dispercao;
}

pTabJogos inicia_tj(int max)
{
  int i;
  int m = 2 * max;
  pTabJogos tab_dispercao = malloc(sizeof(struct tab_jogos));
  tab_dispercao->jogos = malloc(m * (sizeof(pJogo)));
  tab_dispercao->max = m;
  tab_dispercao->N = 0;
  for (i = 0; i < m; i++)
    tab_dispercao->jogos[i] = 0;

  return tab_dispercao;
}

void insere_eq(pEquipa equipa, pTabEquipas tab_dispercao)
{
  int i = hash(equipa->nome, tab_dispercao->max);
  while (tab_dispercao->equipas[i] != 0)
    i = (i + 1) % tab_dispercao->max;

  tab_dispercao->equipas[i] = equipa;
  tab_dispercao->N++;
}

void insere_jg(pJogo jogo, pTabJogos tab_dispercao)
{
  int i = hash(jogo->nome, tab_dispercao->max);
  while (tab_dispercao->jogos[i] != 0)
    i = (i + 1) % tab_dispercao->max;

  tab_dispercao->jogos[i] = jogo;
  tab_dispercao->N++;
}

void aumenta_te(pTabEquipas tab_dispercao)
{
  int i;
  pEquipa *t = tab_dispercao->equipas;
  tab_dispercao = inicia_te(tab_dispercao->max + tab_dispercao->max);
  for (i = 0; i < (tab_dispercao->max / 2); i++)
    if (t[i]->nome != 0)
  {
    insere_eq(t[i], tab_dispercao);
  }
  else
  {
    
  }


  free(t);
}

void aumenta_tj(pTabJogos tab_dispercao)
{
  int i;
  pJogo *t = tab_dispercao->jogos;
  tab_dispercao = inicia_tj(tab_dispercao->max + tab_dispercao->max);
  for (i = 0; i < (tab_dispercao->max / 2); i++)
    if (t[i]->nome != 0)
  {
    insere_jg(t[i], tab_dispercao);
  }
  else
  {
    
  }


  free(t);
}

pEquipa procura_eq(Chave v, pTabEquipas tab_dispercao)
{
  int i = hash(v, tab_dispercao->max);
  while (tab_dispercao->equipas[i] != 0)
    if (strcmp(v, tab_dispercao->equipas[i]->nome) == 0)
  {
    return tab_dispercao->equipas[i];
  }
  else
  {
    i = (i + 1) % tab_dispercao->max;
  }


  return 0;
}

pJogo procura_jg(Chave v, pTabJogos tab_dispercao)
{
  int i = hash(v, tab_dispercao->max);
  while (tab_dispercao->jogos[i] != 0)
    if (strcmp(v, tab_dispercao->jogos[i]->nome) == 0)
  {
    return tab_dispercao->jogos[i];
  }
  else
  {
    i = (i + 1) % tab_dispercao->max;
  }


  return 0;
}

void apaga_jg(Chave v, pTabJogos tab_dispercao)
{
  int j;
  int i = hash(v, tab_dispercao->max);
  pJogo aux;
  while (tab_dispercao->jogos[i] != 0)
    if (strcmp(v, tab_dispercao->jogos[i]->nome) == 0)
  {
    break;
  }
  else
  {
    i = (i + 1) % tab_dispercao->max;
  }


  if (tab_dispercao->jogos[i] == 0)
  {
    return;
  }
  else
  {
    
  }

  liberta_jogo(tab_dispercao->jogos[i]);
  tab_dispercao->jogos[i] = 0;
  tab_dispercao->N--;
  for (j = (i + 1) % tab_dispercao->max; tab_dispercao->jogos[j] != 0; j = (j + 1) % tab_dispercao->max, tab_dispercao->N--)
  {
    aux = tab_dispercao->jogos[j];
    tab_dispercao->jogos[j] = 0;
    insere_jg(aux, tab_dispercao);
  }

}

void liberta_te(pTabEquipas tab_dispercao)
{
  int i = 0;
  for (; i < tab_dispercao->max; i++)
    if (tab_dispercao->equipas[i] != 0)
  {
    liberta_equipa(tab_dispercao->equipas[i]);
    tab_dispercao->equipas[i] = 0;
    tab_dispercao->N--;
  }
  else
  {
    
  }


  free(tab_dispercao->equipas);
  free(tab_dispercao);
}

void liberta_tj(pTabJogos tab_dispercao)
{
  int i = 0;
  for (; i < tab_dispercao->max; i++)
    if (tab_dispercao->jogos[i] != 0)
  {
    liberta_jogo(tab_dispercao->jogos[i]);
    tab_dispercao->jogos[i] = 0;
    tab_dispercao->N--;
  }
  else
  {
    
  }


  free(tab_dispercao->jogos);
  free(tab_dispercao);
}

