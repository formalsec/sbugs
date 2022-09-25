/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos_equipas.h"


long tabEq_size = 8;
long tabEq_ocup;
pEquipa *tabela_Equi;
long tabJo_size = 8;
long tabJo_ocup;
pJogo *tabela_Jo;
pJogo head;
pJogo tail;
void inicializar_estruturas()
{
  tabela_Equi = cria_tabela_equi();
  tabela_Jo = cria_tabela_jogo();
}

void freeEstruturas()
{
  freeTabEq();
  freeTabJo();
}

void a(long line)
{
  int sc1;
  int sc2;
  long i;
  long j;
  char nomes[3][1024];
  pJogo novo_jogo;
  for (int nomes_index = 0; nomes_index < 10; nomes_index++)
  {
    nomes[0][nomes_index] = new_sym_var(sizeof(char) * 8);
  }

  nomes[0][10 - 1] = '\0';
  for (int nomes_index = 0; nomes_index < 10; nomes_index++)
  {
    nomes[1][nomes_index] = new_sym_var(sizeof(char) * 8);
  }

  nomes[1][10 - 1] = '\0';
  for (int nomes_index = 0; nomes_index < 10; nomes_index++)
  {
    nomes[2][nomes_index] = new_sym_var(sizeof(char) * 8);
  }

  nomes[2][10 - 1] = '\0';
  sc1 = new_sym_var(sizeof(int) * 8);
  sc2 = new_sym_var(sizeof(int) * 8);
  if (search_Jo(nomes[0]) != (-1))
  {
    printf("%ld Jogo existente.\n", line);
  }
  else
  {
    if (((i = search_Eq(nomes[1])) == (-1)) || ((j = search_Eq(nomes[2])) == (-1)))
    {
      printf("%ld Equipa inexistente.\n", line);
    }
    else
    {
      novo_jogo = cria_jogo(nomes[0], tabela_Equi[i], tabela_Equi[j], sc1, sc2);
      insert_Jo(novo_jogo);
    }

  }

}

void A(long line)
{
  char str[1024];
  pEquipa nova_equipa;
  for (int str_index = 0; str_index < 10; str_index++)
  {
    str[str_index] = new_sym_var(sizeof(char) * 8);
  }

  str[10 - 1] = '\0';
  if (search_Eq(str) != (-1))
  {
    printf("%ld Equipa existente.\n", line);
  }
  else
  {
    nova_equipa = cria_equipa(str);
    insert_Eq(nova_equipa);
  }

}

void l(long line)
{
  pJogo pAux = head;
  while (pAux != 0)
  {
    printf("%ld %s %s %s %d %d\n", line, pAux->nome, pAux->e1->nome, pAux->e2->nome, pAux->sc1, pAux->sc2);
    pAux = pAux->next;
  }

}

void p(long line)
{
  long i;
  char str[1024];
  for (int str_index = 0; str_index < 10; str_index++)
  {
    str[str_index] = new_sym_var(sizeof(char) * 8);
  }

  str[10 - 1] = '\0';
  if ((i = search_Jo(str)) == (-1))
  {
    printf("%ld Jogo inexistente.\n", line);
  }
  else
  {
    printf("%ld %s %s %s %d %d\n", line, tabela_Jo[i]->nome, tabela_Jo[i]->e1->nome, tabela_Jo[i]->e2->nome, tabela_Jo[i]->sc1, tabela_Jo[i]->sc2);
  }

}

void P(long line)
{
  long i;
  char str[1024];
  for (int str_index = 0; str_index < 10; str_index++)
  {
    str[str_index] = new_sym_var(sizeof(char) * 8);
  }

  str[10 - 1] = '\0';
  if ((i = search_Eq(str)) == (-1))
  {
    printf("%ld Equipa inexistente.\n", line);
  }
  else
  {
    printf("%ld %s %d\n", line, tabela_Equi[i]->nome, tabela_Equi[i]->vit);
  }

}

void r(long line)
{
  char str[1024];
  for (int str_index = 0; str_index < 10; str_index++)
  {
    str[str_index] = new_sym_var(sizeof(char) * 8);
  }

  str[10 - 1] = '\0';
  if (remove_Jo(str) != 0)
  {
    printf("%ld Jogo inexistente.\n", line);
  }
  else
  {
    
  }

}

void s(long line)
{
  int sc1;
  int sc2;
  int ant_venc;
  int novo_venc;
  long i;
  char str[1024];
  for (int str_index = 0; str_index < 10; str_index++)
  {
    str[str_index] = new_sym_var(sizeof(char) * 8);
  }

  str[10 - 1] = '\0';
  sc1 = new_sym_var(sizeof(int) * 8);
  sc2 = new_sym_var(sizeof(int) * 8);
  if ((i = search_Jo(str)) == (-1))
  {
    printf("%ld Jogo inexistente.\n", line);
  }
  else
  {
    ant_venc = vencedor(tabela_Jo[i]->sc1, tabela_Jo[i]->sc2);
    novo_venc = vencedor(sc1, sc2);
    tabela_Jo[i]->sc1 = sc1;
    tabela_Jo[i]->sc2 = sc2;
    atualiza_vencedores(ant_venc, novo_venc, tabela_Jo[i]->e1, tabela_Jo[i]->e2);
  }

}

void g(long line)
{
  int max = 0;
  long i = 0;
  long j = 0;
  pEquipa *campeoes;
  if (tabEq_ocup == 0)
  {
    return;
  }
  else
  {
    
  }

  campeoes = (pEquipa *) malloc((sizeof(pEquipa)) * tabEq_ocup);
  for (i = 0; i < tabEq_size; ++i)
    if (tabela_Equi[i] != 0)
  {
    if (tabela_Equi[i]->vit == max)
    {
      campeoes[j] = tabela_Equi[i];
      ++j;
    }
    else
    {
      if (tabela_Equi[i]->vit > max)
      {
        j = 0;
        max = tabela_Equi[i]->vit;
        campeoes[j] = tabela_Equi[i];
        ++j;
      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }


  mergesort(campeoes, 0, j - 1);
  printf("%ld Melhores %d\n", line, max);
  for (i = 0; i < j; ++i)
  {
    printf("%ld * %s\n", line, campeoes[i]->nome);
  }

  free(campeoes);
}

int main()
{
  long line = 0;
  char c;
  inicializar_estruturas();
  while ((c = getchar()) != 'x')
  {
    line++;
    switch (c)
    {
      case 'a':
        getchar();
        a(line);
        break;

      case 'A':
        getchar();
        A(line);
        break;

      case 'l':
        l(line);
        break;

      case 'p':
        getchar();
        p(line);
        break;

      case 'P':
        getchar();
        P(line);
        break;

      case 'r':
        getchar();
        r(line);
        break;

      case 's':
        getchar();
        s(line);
        break;

      case 'g':
        g(line);
        break;

    }

    getchar();
  }

  freeEstruturas();
  return 0;
}

