#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comandos.h"
#include "auxiliares.h"


void A(linkE *headEptr, hptr *h1)
{
  char *nome_equipa;
  linkE aux;
  nome_equipa = (char *) malloc((sizeof(char)) * 1093);
  for (int nome_equipa_index = 0; nome_equipa_index < 10; nome_equipa_index++)
  {
    nome_equipa[nome_equipa_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_equipa[10 - 1] = '\0';
  aux = encontra_E(*headEptr, nome_equipa);
  if (aux == 0)
  {
    insereInicio_E(headEptr, nome_equipa);
  }
  else
  {
    printf("%d Equipa existente.\n", (*h1)->cont);
  }

  free(nome_equipa);
}

void a(linkJ *headJptr, linkE headE, hptr *h1)
{
  char *jogo;
  char *e1;
  char *e2;
  int p1;
  int p2;
  jogo = (char *) malloc((sizeof(char)) * 1093);
  e1 = (char *) malloc((sizeof(char)) * 1093);
  e2 = (char *) malloc((sizeof(char)) * 1093);
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
  for (int e1_index = 0; e1_index < 10; e1_index++)
  {
    e1[e1_index] = new_sym_var(sizeof(char) * 8);
  }

  e1[10 - 1] = '\0';
  for (int e2_index = 0; e2_index < 10; e2_index++)
  {
    e2[e2_index] = new_sym_var(sizeof(char) * 8);
  }

  e2[10 - 1] = '\0';
  p1 = new_sym_var(sizeof(int) * 8);
  p2 = new_sym_var(sizeof(int) * 8);
  if (encontra_J(*headJptr, jogo) != 0)
  {
    printf("%d Jogo existente.\n", (*h1)->cont);
  }
  else
  {
    if ((encontra_E(headE, e1) == 0) || (encontra_E(headE, e2) == 0))
    {
      printf("%d Equipa inexistente.\n", (*h1)->cont);
    }
    else
    {
      insereInicio_J(headJptr, jogo, e1, e2, p1, p2);
      vitorias(headE, p1, p2, e1, e2, h1);
    }

  }

  free(jogo);
  free(e1);
  free(e2);
}

void p(linkJ *headJptr, hptr *h1)
{
  char *jogo;
  linkJ obj;
  int linha;
  int g1;
  int g2;
  linha = (*h1)->cont;
  jogo = (char *) malloc((sizeof(char)) * 1093);
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
  obj = encontra_J(*headJptr, jogo);
  if (obj == 0)
  {
    printf("%d Jogo inexistente.\n", linha);
  }
  else
  {
    g1 = obj->golos1;
    g2 = obj->golos2;
    printf("%d %s %s %s %d %d\n", linha, obj->nome_jogo, obj->equipa1, obj->equipa2, g1, g2);
  }

  free(jogo);
}

void P(linkE headE, hptr *h1)
{
  char *nome_e;
  linkE aux;
  nome_e = (char *) malloc((sizeof(char)) * 1093);
  for (int nome_e_index = 0; nome_e_index < 10; nome_e_index++)
  {
    nome_e[nome_e_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_e[10 - 1] = '\0';
  aux = encontra_E(headE, nome_e);
  if (aux == 0)
  {
    printf("%d Equipa inexistente.\n", (*h1)->cont);
  }
  else
  {
    printf("%d %s %d\n", (*h1)->cont, aux->nome_equipa, aux->vitorias);
  }

  free(nome_e);
}

void r(linkJ *headJptr, hptr *h1, linkE headE)
{
  char *jogo;
  linkJ aux;
  jogo = (char *) malloc((sizeof(char)) * 1093);
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
  aux = encontra_J(*headJptr, jogo);
  if (aux == 0)
  {
    printf("%d Jogo inexistente.\n", (*h1)->cont);
  }
  else
  {
    retira_pontos(aux, headE, h1);
    elimina_J(headJptr, jogo);
  }

  free(jogo);
}

void s(linkJ *headJptr, hptr *h1, linkE headE)
{
  int p1;
  int p2;
  char *jogo;
  linkJ aux;
  jogo = (char *) malloc((sizeof(char)) * 1093);
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
  p1 = new_sym_var(sizeof(int) * 8);
  p2 = new_sym_var(sizeof(int) * 8);
  aux = encontra_J(*headJptr, jogo);
  if (aux == 0)
  {
    printf("%d Jogo inexistente.\n", (*h1)->cont);
  }
  else
  {
    retira_pontos(aux, headE, h1);
    vitorias(headE, p1, p2, aux->equipa1, aux->equipa2, h1);
    aux->golos1 = p1;
    aux->golos2 = p2;
  }

  free(jogo);
}

void l(linkJ headJ, hptr *h1)
{
  linkJ t;
  int linha;
  int g1;
  int g2;
  linha = (*h1)->cont;
  if (headJ == 0)
  {
    return;
  }
  else
  {
    if (headJ->next == 0)
    {
      g1 = headJ->golos1;
      g2 = headJ->golos2;
      printf("%d %s %s %s %d %d\n", linha, headJ->nome_jogo, headJ->equipa1, headJ->equipa2, g1, g2);
    }
    else
    {
      for (t = headJ->prev; t != headJ; t = t->prev)
      {
        g1 = t->golos1;
        g2 = t->golos2;
        printf("%d %s %s %s %d %d\n", linha, t->nome_jogo, t->equipa1, t->equipa2, g1, g2);
      }

      g1 = headJ->golos1;
      g2 = headJ->golos2;
      printf("%d %s %s %s %d %d\n", linha, headJ->nome_jogo, headJ->equipa1, headJ->equipa2, g1, g2);
    }

  }

}

void g(linkE headE, hptr *h1)
{
  char **nomes;
  linkE aux;
  int i;
  int cont;
  cont = 0;
  nomes = (char **) malloc(1093 * (sizeof(char *)));
  if (headE == 0)
  {
    return;
  }
  else
  {
    
  }

  for (aux = headE, i = 0; aux != 0; aux = aux->next)
  {
    if (aux->vitorias == (*h1)->max_vit)
    {
      nomes[i] = aux->nome_equipa;
      i++;
      cont++;
    }
    else
    {
      
    }

  }

  SelectionSort(nomes, 0, cont);
  printf("%d Melhores %d\n", (*h1)->cont, (*h1)->max_vit);
  for (i = 0; i < cont; i++)
    printf("%d * %s\n", (*h1)->cont, nomes[i]);

}

