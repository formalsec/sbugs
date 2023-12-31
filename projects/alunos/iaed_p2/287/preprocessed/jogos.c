#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "jogos.h"


void apaga_jogo(Jogo a)
{
  free(a->nome);
  free(a->equipa1);
  free(a->equipa2);
  free(a);
}

Jogo novo_jogo(char *nome, char *e1, char *e2, int s1, int s2)
{
  Jogo new = (Jogo) malloc(sizeof(struct jogo));
  new->score_e1 = s1;
  new->score_e2 = s2;
  new->nome = malloc(strlen(nome) + 1);
  strcpy(new->nome, nome);
  new->equipa1 = malloc(strlen(e1) + 1);
  strcpy(new->equipa1, e1);
  new->equipa2 = malloc(strlen(e2) + 1);
  strcpy(new->equipa2, e2);
  return new;
}

link_jogo *init_tab_jogos()
{
  int i;
  int tamanho = 997;
  link_jogo *jogos;
  jogos = malloc(tamanho * (sizeof(link_jogo)));
  for (i = 0; i < tamanho; i++)
    jogos[i] = 0;

  return jogos;
}

void insere_tab_jogo(Jogo jogo, link_jogo *jogos)
{
  int tamanho = 997;
  int i = hash(jogo->nome, tamanho);
  jogos[i] = insere_jogo_cadeia(jogos[i], jogo);
}

link_jogo insere_jogo_cadeia(link_jogo equi_slot, Jogo jogo)
{
  link_jogo new = 0;
  new = malloc(sizeof(struct node_jogo));
  new->next = equi_slot;
  new->jogo = jogo;
  return new;
}

Jogo procura_tab_jogo(Key v, link_jogo *jogos)
{
  int tamanho = 997;
  int i = hash(v, tamanho);
  return procura_jogo_cadeia(jogos[i], v);
}

Jogo procura_jogo_cadeia(link_jogo equi_slot, Key v)
{
  while (equi_slot != 0)
  {
    if (strcmp(v, equi_slot->jogo->nome) == 0)
    {
      return equi_slot->jogo;
    }
    else
    {
      
    }

    equi_slot = equi_slot->next;
  }

  return 0;
}

void apaga_tab_jogo(link_jogo *jogos, Key nome)
{
  int i = hash(nome, 997);
  link_jogo temp;
  link_jogo anterior;
  temp = jogos[i];
  for (temp = jogos[i], anterior = 0; temp != 0; anterior = temp, temp = temp->next)
  {
    if (strcmp(temp->jogo->nome, nome) == 0)
    {
      if (temp == jogos[i])
      {
        jogos[i] = temp->next;
      }
      else
      {
        anterior->next = temp->next;
      }

      temp->jogo->nome = "APAGADO";
    }
    else
    {
      
    }

  }

}

Lista_jogos inicia_ls()
{
  Lista_jogos l = malloc(sizeof(struct lista_jogos));
  l->cabeca = (l->ultimo = 0);
  return l;
}

Lista_jogos adiciona_jogo_ls(Jogo jogo, Lista_jogos l)
{
  link_jogo_ls novo = malloc(sizeof(struct node_jogo_ls));
  novo->prev = l->ultimo;
  novo->next = 0;
  novo->jogo = jogo;
  if (l->ultimo)
  {
    l->ultimo->next = novo;
  }
  else
  {
    l->cabeca = novo;
  }

  l->ultimo = novo;
  return l;
}

void apaga_ls_jogos(Lista_jogos l)
{
  link_jogo_ls temp1;
  link_jogo_ls temp2;
  temp1 = l->cabeca;
  while (temp1 != 0)
  {
    temp2 = temp1;
    temp1 = temp1->next;
    free(temp2);
  }

  free(l);
}

void apaga_tab_jogos(link_jogo *jogos)
{
  int i;
  link_jogo temp1;
  link_jogo temp2;
  Jogo jogo_temp;
  for (i = 0; i < 997; i++)
  {
    if (jogos[i] != 0)
    {
      temp1 = jogos[i];
      while (temp1 != 0)
      {
        jogo_temp = temp1->jogo;
        temp2 = temp1;
        temp1 = temp1->next;
        apaga_jogo(jogo_temp);
        free(temp2);
      }

    }
    else
    {
      
    }

  }

  free(jogos);
}

