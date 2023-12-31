#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p2.h"


int hash(char v[1023], int M)
{
  int h = 0;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (M - 1))
  {
    h = ((a * h) + (*v)) % M;
  }

  return h;
}

void ini_hash_eq(link_equipa **eq, int M)
{
  int j;
  eq[0] = (link_equipa *) malloc(M * (sizeof(link_equipa)));
  for (j = 0; j < M; j++)
  {
    eq[0][j] = 0;
  }

  return;
}

link_equipa nova_equipa(char nome[1023])
{
  link_equipa aux = (link_equipa) malloc(sizeof(struct node2));
  strcpy(aux->eq.nome_equipa, nome);
  aux->eq.numero_vit = 0;
  aux->seguinte = 0;
  return aux;
}

void inserir_hash_eqp(link_equipa *eq, int M, char nome[1023])
{
  link_equipa a;
  int i = hash(nome, M);
  if (eq[i] == 0)
  {
    eq[i] = nova_equipa(nome);
    return;
  }
  else
  {
    
  }

  a = nova_equipa(nome);
  a->seguinte = eq[i];
  eq[i] = a;
}

link_equipa procura_hash_equipas(link_equipa *t_eq, char *nome, int M)
{
  int i = hash(nome, M);
  link_equipa aux = 0;
  for (aux = t_eq[i]; aux != 0; aux = aux->seguinte)
  {
    if (strcmp(aux->eq.nome_equipa, nome) == 0)
    {
      return aux;
    }
    else
    {
      
    }

  }

  return 0;
}

void apaga_node_eq(link_equipa nod)
{
  free(nod);
}

void apaga_hash_equipas(link_equipa *eq, int M)
{
  int i;
  link_equipa auxiliar;
  link_equipa anterior;
  for (i = 0; i < M; i++)
  {
    for (auxiliar = eq[i], anterior = 0; auxiliar != 0;)
    {
      anterior = auxiliar;
      auxiliar = auxiliar->seguinte;
      apaga_node_eq(anterior);
    }

  }

}

void inserir_hash_jogo(link_jogo *tab, int M, char nome[1023], char equipa1[1023], char equipa2[1023], int score1, int score2)
{
  link_jogo aux;
  int i = hash(nome, M);
  if (tab[i] == 0)
  {
    tab[i] = novo_jogo(nome, equipa1, equipa2, score1, score2);
  }
  else
  {
    aux = novo_jogo(nome, equipa1, equipa2, score1, score2);
    aux->seguinte = tab[i];
    tab[i] = aux;
  }

}

link_jogo procura_hash(link_jogo *tab, char nome[1023], int M)
{
  int i = hash(nome, M);
  link_jogo aux;
  for (aux = tab[i]; aux != 0; aux = aux->seguinte)
  {
    if (strcmp(aux->jogos.nome, nome) == 0)
    {
      return aux;
    }
    else
    {
      
    }

  }

  return 0;
}

void apaga_node(link_jogo nod)
{
  free(nod);
}

void apaga_hash(link_jogo *tab, int M)
{
  int i;
  link_jogo auxiliar;
  link_jogo anterior;
  for (i = 0; i < M; i++)
  {
    for (auxiliar = tab[i], anterior = 0; auxiliar != 0;)
    {
      anterior = auxiliar;
      auxiliar = auxiliar->seguinte;
      apaga_node(anterior);
    }

  }

}

void remove_hash_el(link_jogo *tab, char *nome, int M)
{
  int i;
  link_jogo auxiliar;
  link_jogo anterior;
  for (i = 0; i < M; i++)
  {
    for (auxiliar = tab[i], anterior = 0; auxiliar != 0;)
    {
      if (strcmp(auxiliar->jogos.nome, nome) == 0)
      {
        if (auxiliar == tab[i])
        {
          tab[i] = auxiliar->seguinte;
          apaga_node(auxiliar);
          break;
        }
        else
        {
          anterior->seguinte = auxiliar->seguinte;
          apaga_node(auxiliar);
          break;
        }

      }
      else
      {
        
      }

      anterior = auxiliar;
      auxiliar = auxiliar->seguinte;
    }

  }

}

link_jogo novo_jogo(char nome[1023], char equipa1[1023], char equipa2[1023], int score1, int score2)
{
  link_jogo aux = (link_jogo) malloc(sizeof(struct node1));
  strcpy(aux->jogos.nome, nome);
  strcpy(aux->jogos.equipa1.nome_equipa, equipa1);
  strcpy(aux->jogos.equipa2.nome_equipa, equipa2);
  aux->jogos.score1 = score1;
  aux->jogos.score2 = score2;
  aux->seguinte = 0;
  return aux;
}

void adiciona_jogo(link_jogo *tab, link_equipa *tab_eq, int M, int M2, int NL)
{
  char nome[1023];
  char equipa1[1023];
  char equipa2[1023];
  int score1;
  int score2;
  int h;
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
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (procura_hash(tab, nome, M) == 0)
  {
    if ((procura_hash_equipas(tab_eq, equipa1, M2) != 0) || (procura_hash_equipas(tab_eq, equipa2, M2) != 0))
    {
      inserir_hash_jogo(tab, M, nome, equipa1, equipa2, score1, score2);
      if (score1 > score2)
      {
        h = hash(equipa1, M2);
        tab_eq[h]->eq.numero_vit = tab_eq[h]->eq.numero_vit + 1;
      }
      else
      {
        h = hash(equipa2, M2);
        tab_eq[h]->eq.numero_vit = tab_eq[h]->eq.numero_vit + 1;
      }

    }
    else
    {
      printf("%d Equipa inexistente.\n", NL);
    }

  }
  else
  {
    printf("%d Jogo existente.", NL);
  }

}

void imprime_jogo(link_jogo tab, int NL)
{
  printf("%d %s ", NL, tab->jogos.nome);
  printf("%s %s ", tab->jogos.equipa1.nome_equipa, tab->jogos.equipa2.nome_equipa);
  printf("%02d %02d.\n", tab->jogos.score1, tab->jogos.score2);
}

void lista_jogos(link_jogo *tab, int NL, int M)
{
  link_jogo auxiliar;
  int i;
  for (i = 0; i < M; i++)
  {
    for (auxiliar = tab[i]; auxiliar != 0; auxiliar = auxiliar->seguinte)
    {
      imprime_jogo(auxiliar, NL);
    }

  }

}

void procura_jogo(link_jogo *tab, int M, int NL)
{
  char nome[1023];
  link_jogo tab1;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (procura_hash(tab, nome, M) != 0)
  {
    tab1 = procura_hash(tab, nome, M);
    imprime_jogo(tab1, NL);
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void remove_jogo(link_jogo *tab, int M, int NL)
{
  char nome[1023];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (procura_hash(tab, nome, M) != 0)
  {
    remove_hash_el(tab, nome, M);
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void altera_score(link_jogo *tab, int M, int NL)
{
  char nome[1023];
  int score1;
  int score2;
  int h;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (procura_hash(tab, nome, M) != 0)
  {
    h = hash(nome, M);
    tab[h]->jogos.score1 = score1;
    tab[h]->jogos.score2 = score2;
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void adiciona_equipa(link_equipa *tab_eq, int M, int NL)
{
  char nome[1023];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (procura_hash_equipas(tab_eq, nome, M) == 0)
  {
    inserir_hash_eqp(tab_eq, M, nome);
  }
  else
  {
    printf("%d Equipa existente.\n", NL);
  }

}

int main()
{
  char comando;
  int i;
  int NL = 0;
  link_jogo *tab_jogo = 0;
  link_equipa *tab_equipa = 0;
  int M = 1033;
  int M2 = 1933;
  tab_jogo = (link_jogo *) malloc(M * (sizeof(link_jogo)));
  for (i = 0; i < M; i++)
  {
    tab_jogo[i] = 0;
  }

  ini_hash_eq(&tab_equipa, M2);
  do
  {
    switch (comando = getchar())
    {
      case 'a':
        getchar();
        NL++;
        adiciona_jogo(tab_jogo, tab_equipa, M, M2, NL);
        break;

      case 'l':
        NL++;
        lista_jogos(tab_jogo, NL, M);
        break;

      case 'p':
        getchar();
        NL++;
        procura_jogo(tab_jogo, M, NL);
        break;

      case 'r':
        getchar();
        NL++;
        remove_jogo(tab_jogo, M, NL);
        break;

      case 's':
        getchar();
        NL++;
        altera_score(tab_jogo, M, NL);
        break;

      case 'A':
        getchar();
        NL++;
        adiciona_equipa(tab_equipa, M2, NL);
        break;

    }

  }
  while (comando != 'x');
  apaga_hash(tab_jogo, M);
  free(tab_jogo);
  apaga_hash_equipas(tab_equipa, M);
  free(tab_equipa);
  return 0;
}

