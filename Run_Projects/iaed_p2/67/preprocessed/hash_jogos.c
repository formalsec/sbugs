/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_jogos.h"


link_jogo *init_jogo(int m)
{
  int i;
  link_jogo *tabela_jogos;
  tabela_jogos = (link_jogo *) malloc(m * (sizeof(link_jogo)));
  for (i = 0; i < m; i++)
  {
    tabela_jogos[i] = 0;
  }

  return tabela_jogos;
}

link_jogo novo_jogo(char *nome, char *equipa1, char *equipa2, int score1, int score2)
{
  link_jogo x = (link_jogo) malloc(sizeof(struct node_jogos));
  x->jogo = (pJogo) malloc(sizeof(struct jogo));
  x->jogo->nome = (char *) malloc((strlen(nome) + 1) * (sizeof(char)));
  strcpy(x->jogo->nome, nome);
  x->jogo->equipa1 = (char *) malloc((strlen(equipa1) + 1) * (sizeof(char)));
  strcpy(x->jogo->equipa1, equipa1);
  x->jogo->equipa2 = (char *) malloc((strlen(equipa2) + 1) * (sizeof(char)));
  strcpy(x->jogo->equipa2, equipa2);
  x->jogo->score1 = score1;
  x->jogo->score2 = score2;
  x->next = 0;
  return x;
}

link_jogo procura_lista_jogo(link_jogo head, char *nome)
{
  link_jogo t;
  for (t = head; t != 0; t = t->next)
  {
    if (strcmp(t->jogo->nome, nome) == 0)
    {
      {
        return t;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

link_jogo insere_lista_jogo(link_jogo head, link_jogo jogo)
{
  link_jogo x = novo_jogo(jogo->jogo->nome, jogo->jogo->equipa1, jogo->jogo->equipa2, jogo->jogo->score1, jogo->jogo->score2);
  x->next = head;
  return x;
}

link_jogo remove_jogo_lista(link_jogo head, char *nome)
{
  if (head == 0)
  {
    return 0;
  }
  else
  {
    
  }

  if (strcmp(head->jogo->nome, nome) == 0)
  {
    {
      link_jogo t;
      t = head->next;
      free(head->jogo->nome);
      free(head->jogo->equipa1);
      free(head->jogo->equipa2);
      free(head->jogo);
      free(head);
      return t;
    }
  }
  else
  {
    
  }

  head->next = remove_jogo_lista(head->next, nome);
  return head;
}

link_jogo remove_lista(link_jogo head)
{
  if (head == 0)
  {
    return 0;
  }
  else
  {
    {
      link_jogo t;
      t = head->next;
      free(head->jogo->nome);
      free(head->jogo->equipa1);
      free(head->jogo->equipa2);
      free(head->jogo);
      free(head);
      return t;
    }
  }

  head->next = remove_lista(head->next);
  return head;
}

int hash_string(char *v, int M)
{
  int h = 0;
  int a = 127;
  for (; (*v) != '\0'; v++)
  {
    h = ((a * h) + (*v)) % M;
  }

  return h;
}

link_jogo procura_jogo(char *nome, link_jogo *tabela_jogos)
{
  int i;
  i = hash_string(nome, 1069);
  return procura_lista_jogo(tabela_jogos[i], nome);
}

link_jogo *insere_jogo(link_jogo jogo, link_jogo *tabela_jogos)
{
  int i = hash_string(jogo->jogo->nome, 1069);
  tabela_jogos[i] = insere_lista_jogo(tabela_jogos[i], jogo);
  return tabela_jogos;
}

link_jogo *apaga_jogo(char *nome, link_jogo *tabela_jogos)
{
  int i = hash_string(nome, 1069);
  tabela_jogos[i] = remove_jogo_lista(tabela_jogos[i], nome);
  return tabela_jogos;
}

link_jogo apaga_jogo_2(char *nome, link_jogo lista_jogos)
{
  lista_jogos = remove_jogo_lista(lista_jogos, nome);
  return lista_jogos;
}

link_jogo insere_jogo_2(link_jogo jogo, link_jogo lista_jogos)
{
  lista_jogos = insere_lista_jogo(lista_jogos, jogo);
  return lista_jogos;
}

link_jogo insere_lista_jogo_2(link_jogo head, link_jogo jogo)
{
  link_jogo x;
  if (head == 0)
  {
    {
      return novo_jogo(jogo->jogo->nome, jogo->jogo->equipa1, jogo->jogo->equipa2, jogo->jogo->score1, jogo->jogo->score2);
    }
  }
  else
  {
    
  }

  for (x = head; x->next != 0; x = x->next)
    ;

  x->next = novo_jogo(jogo->jogo->nome, jogo->jogo->equipa1, jogo->jogo->equipa2, jogo->jogo->score1, jogo->jogo->score2);
  return head;
}

void print_jogos(link_jogo head, int linha)
{
  link_jogo t;
  for (t = head; t != 0; t = t->next)
  {
    printf("%d %s %s %s %d %d\n", linha, t->jogo->nome, t->jogo->equipa1, t->jogo->equipa2, t->jogo->score1, t->jogo->score2);
  }

}

void altera_jogo(link_jogo jogo, int score1, int score2)
{
  jogo->jogo->score1 = score1;
  jogo->jogo->score2 = score2;
}

link_jogo altera_jogo_2(char *nome, int score1, int score2, link_jogo lista_jogos)
{
  link_jogo x;
  x = procura_lista_jogo(lista_jogos, nome);
  x->jogo->score1 = score1;
  x->jogo->score2 = score2;
  return lista_jogos;
}

link_jogo *liberta_jogos(link_jogo *tabela_jogos)
{
  int i;
  for (i = 0; i < 1069; i++)
  {
    tabela_jogos[i] = remove_lista(tabela_jogos[i]);
  }

  return tabela_jogos;
}

