/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_equipa.h"
#include "hash_jogo.h"
#include "lista_jogos.h"


int hash(char *key, int M)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*key) != '\0'; key++)
  {
    h = ((a * h) + (*key)) % M;
    a = (a * b) % (M - 1);
  }

  return h;
}

void retira_vitoria(int M, pJogo jogo, linkE *equipas)
{
  int i;
  pEquipa equipa;
  if (jogo->score1 > jogo->score2)
  {
    {
      i = hash(jogo->equipa1, M);
      equipa = SearchEquipa(jogo->equipa1, equipas[i]);
      --equipa->vitorias;
    }
  }
  else
  {
    if (jogo->score1 < jogo->score2)
    {
      {
        i = hash(jogo->equipa2, M);
        equipa = SearchEquipa(jogo->equipa2, equipas[i]);
        --equipa->vitorias;
      }
    }
    else
    {
      
    }

  }

}

void atribui_vitoria(int M, pJogo jogo, linkE *equipas)
{
  int i;
  pEquipa equipa;
  if (jogo->score1 > jogo->score2)
  {
    {
      i = hash(jogo->equipa1, M);
      equipa = SearchEquipa(jogo->equipa1, equipas[i]);
      ++equipa->vitorias;
    }
  }
  else
  {
    if (jogo->score1 < jogo->score2)
    {
      {
        i = hash(jogo->equipa2, M);
        equipa = SearchEquipa(jogo->equipa2, equipas[i]);
        ++equipa->vitorias;
      }
    }
    else
    {
      
    }

  }

}

int comando_a(int nl, int M, linkJ *jogos, linkE *equipas, lista *jogosCron)
{
  char nome[1024];
  char equipa1[1024];
  char equipa2[1024];
  int s1;
  int s2;
  int i;
  pJogo j;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  for (int equipa1_index = 0; equipa1_index < 10; equipa1_index++)
  {
    equipa1[equipa1_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa1[10 - 1] = '\0';
  for (int equipa2_index = 0; equipa2_index < 10; equipa2_index++)
  {
    equipa2[equipa2_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa2[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  i = hash(nome, M);
  if (SearchJogo(nome, jogos[i]) != 0)
  {
    printf("%d Jogo existente.\n", nl);
  }
  else
  {
    if ((SearchEquipa(equipa1, equipas[hash(equipa1, M)]) == 0) || (SearchEquipa(equipa2, equipas[hash(equipa2, M)]) == 0))
    {
      printf("%d Equipa inexistente.\n", nl);
    }
    else
    {
      {
        j = newJogo(nome, equipa1, equipa2, s1, s2);
        jogos[i] = InsertJogo(j, jogos[i]);
        atribui_vitoria(M, j, equipas);
        jogosCron = InsertEndLista(j, jogosCron);
      }
    }

  }

  return ++nl;
}

int comando_A(int nl, int M, linkE *equipas)
{
  char nome[1024];
  int i;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  i = hash(nome, M);
  if (SearchEquipa(nome, equipas[i]) != 0)
  {
    printf("%d Equipa existente.\n", nl);
  }
  else
  {
    equipas[i] = InsertEquipa(nome, equipas[i]);
  }

  return ++nl;
}

int comando_l(lista *jogosCron, int nl)
{
  printLista(jogosCron, nl);
  return ++nl;
}

int comando_p(int nl, int M, linkJ *jogos)
{
  char nome[1024];
  int i;
  linkJ j;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  i = hash(nome, M);
  j = SearchJogo(nome, jogos[i]);
  printf("%d ", nl);
  if (j == 0)
  {
    printf("Jogo inexistente.\n");
  }
  else
  {
    printJogo(j->jogo);
  }

  return ++nl;
}

int comando_P(int nl, int M, linkE *equipas)
{
  char nome[1024];
  int i;
  pEquipa e;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  i = hash(nome, M);
  e = SearchEquipa(nome, equipas[i]);
  printf("%d ", nl);
  if (e == 0)
  {
    printf("Equipa inexistente.\n");
  }
  else
  {
    printEquipa(e);
  }

  return ++nl;
}

int comando_r(int nl, int M, linkJ *jogos, lista *jogosCron, linkE *equipas)
{
  char nome[1024];
  int i;
  linkJ j;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  i = hash(nome, M);
  j = SearchJogo(nome, jogos[i]);
  if (j == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
  }
  else
  {
    {
      retira_vitoria(M, j->jogo, equipas);
      jogosCron = DeleteLista(nome, jogosCron);
      jogos[i] = DeleteJogo(j, jogos[i]);
    }
  }

  return ++nl;
}

int comando_s(int nl, int M, linkJ *jogos, linkE *equipas)
{
  char nome[1024];
  int i;
  int s1;
  int s2;
  linkJ j;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  i = hash(nome, M);
  j = SearchJogo(nome, jogos[i]);
  if (j == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
  }
  else
  {
    {
      retira_vitoria(M, j->jogo, equipas);
      j->jogo->score1 = s1;
      j->jogo->score2 = s2;
      atribui_vitoria(M, j->jogo, equipas);
    }
  }

  return ++nl;
}

int cmp_func(const void *p1, const void *p2)
{
  return strcmp(*((char * const *) p1), *((char * const *) p2));
}

int comando_g(int nl, int M, linkE *equipas)
{
  int i;
  int j = 0;
  int maior = 0;
  int n = 0;
  linkE x;
  char **lista;
  for (i = 0; i < M; i++)
  {
    for (x = equipas[i]; x != 0; x = x->next)
    {
      if (x->equipa->vitorias > maior)
      {
        {
          maior = x->equipa->vitorias;
          n = 1;
        }
      }
      else
      {
        if (x->equipa->vitorias == maior)
        {
          n++;
        }
        else
        {
          
        }

      }

    }

  }

  if (n != 0)
  {
    {
      lista = (char **) malloc(n * (sizeof(char *)));
      for (i = 0; i < M; i++)
        for (x = equipas[i]; x != 0; x = x->next)
        if (x->equipa->vitorias == maior)
      {
        lista[j++] = x->equipa->nome;
      }
      else
      {
        
      }



      qsort(lista, n, sizeof(char *), cmp_func);
      printf("%d Melhores %d\n", nl, maior);
      for (i = 0; i < n; i++)
        printf("%d * %s\n", nl, lista[i]);

      free(lista);
    }
  }
  else
  {
    
  }

  return ++nl;
}

int main()
{
  int nl = 1;
  int M = 367;
  char c;
  linkE *equipas = InitEquipa(M);
  linkJ *jogos = InitJogo(M);
  lista *jogosCron = InitLista();
  while ((c = getchar()) != 'x')
  {
    switch (c)
    {
      case 'a':
        getchar();
        nl = comando_a(nl, M, jogos, equipas, jogosCron);
        break;

      case 'A':
        getchar();
        nl = comando_A(nl, M, equipas);
        break;

      case 'l':
        nl = comando_l(jogosCron, nl);
        break;

      case 'p':
        getchar();
        nl = comando_p(nl, M, jogos);
        break;

      case 'P':
        getchar();
        nl = comando_P(nl, M, equipas);
        break;

      case 'r':
        getchar();
        nl = comando_r(nl, M, jogos, jogosCron, equipas);
        break;

      case 's':
        getchar();
        nl = comando_s(nl, M, jogos, equipas);
        break;

      case 'g':
        nl = comando_g(nl, M, equipas);
        break;

    }

  }

  FreeHashEquipa(M, equipas);
  free(equipas);
  FreeHashJogo(M, jogos);
  free(jogos);
  freeLista(jogosCron);
  free(jogosCron);
  return 0;
}

