/*File generated by PreProcessor.py*/


#include "backoffice.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void executa_a(int nL, fila jogos, fila equipas, fila jogos_ord)
{
  char a[1024];
  char b[1024];
  char c[1024];
  int s1;
  int s2;
  jogo j;
  jogo j1;
  equipa e1;
  equipa e2;
  for (int a_index = 0; a_index < 10; a_index++)
  {
    a[a_index] = new_sym_var(sizeof(char) * 8);
  }

  a[10 - 1] = '\0';
  for (int b_index = 0; b_index < 10; b_index++)
  {
    b[b_index] = new_sym_var(sizeof(char) * 8);
  }

  b[10 - 1] = '\0';
  for (int c_index = 0; c_index < 10; c_index++)
  {
    c[c_index] = new_sym_var(sizeof(char) * 8);
  }

  c[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  j1 = encontra_j_tab(jogos, a);
  if (j1)
  {
    escreve_erro(nL, -4);
    return;
  }
  else
  {
    
  }

  e1 = encontra_e_tab(equipas, b);
  if (!e1)
  {
    escreve_erro(nL, -1);
    return;
  }
  else
  {
    
  }

  e2 = encontra_e_tab(equipas, c);
  if (!e2)
  {
    escreve_erro(nL, -1);
    return;
  }
  else
  {
    
  }

  j = cria_jogo(a, e1, e2, s1, s2);
  junta_j(jogos, j, -8);
  junta_j(jogos_ord, j, -7);
}

void executa_A(int nL, fila equipas, fila equipas_ord)
{
  char a[1024];
  equipa e1;
  equipa e;
  for (int a_index = 0; a_index < 10; a_index++)
  {
    a[a_index] = new_sym_var(sizeof(char) * 8);
  }

  a[10 - 1] = '\0';
  e1 = encontra_e_tab(equipas, a);
  if (e1)
  {
    escreve_erro(nL, -2);
    return;
  }
  else
  {
    
  }

  e = cria_equipa(a);
  junta_e(equipas, e, -8);
  junta_e(equipas_ord, e, -7);
}

void executa_l(int nL, fila jogos_ord)
{
  escreve_j_lst(nL, jogos_ord);
}

void executa_p(int nL, fila jogos)
{
  char a[1024];
  jogo j;
  for (int a_index = 0; a_index < 10; a_index++)
  {
    a[a_index] = new_sym_var(sizeof(char) * 8);
  }

  a[10 - 1] = '\0';
  j = encontra_j_tab(jogos, a);
  if (!j)
  {
    escreve_erro(nL, -3);
  }
  else
  {
    escreve_jogo(nL, j);
  }

}

void executa_P(int nL, fila equipas)
{
  char a[1024];
  equipa e;
  for (int a_index = 0; a_index < 10; a_index++)
  {
    a[a_index] = new_sym_var(sizeof(char) * 8);
  }

  a[10 - 1] = '\0';
  e = encontra_e_tab(equipas, a);
  if (!e)
  {
    escreve_erro(nL, -1);
  }
  else
  {
    escreve_equipa(nL, e);
  }

}

void executa_r(int nL, fila jogos, fila jogos_ord)
{
  char a[1024];
  jogo j;
  for (int a_index = 0; a_index < 10; a_index++)
  {
    a[a_index] = new_sym_var(sizeof(char) * 8);
  }

  a[10 - 1] = '\0';
  j = encontra_j_tab(jogos, a);
  if (!j)
  {
    escreve_erro(nL, -3);
  }
  else
  {
    equipa vencedora;
    vencedora = obtem_vencedora(j);
    if (vencedora == j->e1)
    {
      muda_vitorias(j->e1, '-');
    }
    else
    {
      if (vencedora == j->e2)
      {
        muda_vitorias(j->e2, '-');
      }
      else
      {
        
      }

    }

    tira_j(jogos, j, -8);
    tira_j(jogos_ord, j, -7);
    apaga_jogo(j);
  }

}

void executa_s(int nL, fila jogos)
{
  char a[1024];
  int s1;
  int s2;
  jogo j;
  for (int a_index = 0; a_index < 10; a_index++)
  {
    a[a_index] = new_sym_var(sizeof(char) * 8);
  }

  a[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  j = encontra_j_tab(jogos, a);
  if (!j)
  {
    escreve_erro(nL, -3);
  }
  else
  {
    equipa vencedora;
    vencedora = obtem_vencedora(j);
    if (vencedora == j->e1)
    {
      muda_vitorias(j->e1, '-');
    }
    else
    {
      if (vencedora == j->e2)
      {
        muda_vitorias(j->e2, '-');
      }
      else
      {
        
      }

    }

    if (s1 > s2)
    {
      muda_vitorias(j->e1, '+');
    }
    else
    {
      if (s2 > s1)
      {
        muda_vitorias(j->e2, '+');
      }
      else
      {
        
      }

    }

    altera_score(j, s1, s2);
  }

}

void executa_g(int nL, fila equipas_ord)
{
  par_resultado max;
  int maximo;
  int num_venc;
  arvore *raiz = 0;
  max = maximo_vitorias(equipas_ord);
  maximo = max.maximo;
  num_venc = max.num_venc;
  if (maximo == (-9))
  {
    return;
  }
  else
  {
    
  }

  raiz = ARVbuild(raiz, equipas_ord, maximo, num_venc);
  printf("%d Melhores %d\n", nL, maximo);
  ARVprint(raiz, nL);
  ARVclear(raiz);
}

