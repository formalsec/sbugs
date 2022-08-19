/*File generated by PreProcessor.py*/


#include "jogos.h"


void adiciona_fim(limites_lista *lista, Jogo *jogo)
{
  link_lista n = malloc(sizeof(struct lista_jogos));
  n->jogo = jogo;
  n->next = 0;
  n->prev = lista->last;
  if (lista->head == 0)
  {
    {
      lista->head = n;
      lista->last = n;
    }
  }
  else
  {
    {
      lista->last->next = n;
      lista->last = n;
    }
  }

}

limites_lista *nova_lista()
{
  limites_lista *lista = malloc(sizeof(limites_lista));
  lista->head = 0;
  lista->last = 0;
  return lista;
}

link_jogo *inicializa_hash_jogo(int m)
{
  int i;
  link_jogo *heads_jogos;
  heads_jogos = (link_jogo *) malloc(m * (sizeof(link_jogo)));
  for (i = 0; i < m; i++)
    heads_jogos[i] = 0;

  return heads_jogos;
}

link_jogo novo_jogo(link *heads, char *buffer, char *equipa1, char *equipa2, int score1, int score2)
{
  int i;
  link_jogo x = (link_jogo) malloc(sizeof(struct no));
  x->jogo = malloc(sizeof(struct jogo));
  x->jogo->nome = (char *) malloc((sizeof(char)) * (strlen(buffer) + 1));
  i = hash(equipa1, 977);
  x->jogo->equipa1 = encontra_equipa(heads[i], equipa1);
  i = hash(equipa2, 977);
  x->jogo->equipa2 = encontra_equipa(heads[i], equipa2);
  strcpy(x->jogo->nome, buffer);
  x->jogo->score1 = score1;
  x->jogo->score2 = score2;
  if (score1 > score2)
  {
    x->jogo->equipa1->jogos_ganhos += 1;
  }
  else
  {
    if (score2 > score1)
    {
      x->jogo->equipa2->jogos_ganhos += 1;
    }
    else
    {
      
    }

  }

  x->next = 0;
  return x;
}

link_jogo insere_jogo(limites_lista *lista, link *heads, link_jogo head, char *buffer, char *equipa1, char *equipa2, int score1, int score2)
{
  link_jogo x = novo_jogo(heads, buffer, equipa1, equipa2, score1, score2);
  x->next = head;
  adiciona_fim(lista, x->jogo);
  return x;
}

void insere_jogo_hash(limites_lista *lista, link *heads, link_jogo *heads_jogo, char *nome, char *equipa1, char *equipa2, int score1, int score2)
{
  int i = hash(nome, 977);
  heads_jogo[i] = insere_jogo(lista, heads, heads_jogo[i], nome, equipa1, equipa2, score1, score2);
}

int existe_jogo(link_jogo *heads_jogos, char *nome)
{
  link_jogo aux;
  int i = hash(nome, 977);
  for (aux = heads_jogos[i]; aux != 0; aux = aux->next)
  {
    if (strcmp(aux->jogo->nome, nome) == 0)
    {
      return 1;
    }
    else
    {
      
    }

  }

  return 0;
}

Jogo *encontra_jogo(link_jogo head, char *nome)
{
  link_jogo aux;
  for (aux = head; aux != 0; aux = aux->next)
  {
    if (strcmp(aux->jogo->nome, nome) == 0)
    {
      return aux->jogo;
    }
    else
    {
      
    }

  }

  return 0;
}

Jogo *procura_jogo(link_jogo *heads, char *nome)
{
  int i = hash(nome, 977);
  return encontra_jogo(heads[i], nome);
}

void destroi_lista_jogos(limites_lista *lista)
{
  link_lista head = lista->head;
  while (head != 0)
  {
    lista->head = lista->head->next;
    free(head->jogo->nome);
    free(head->jogo);
    free(head);
    head = lista->head;
  }

  lista->head = 0;
  lista->last = 0;
  free(lista);
}

void destroi_hash_jogos(link_jogo *heads_jogos, int M)
{
  int i;
  link_jogo head;
  for (i = 0; i < M; i++)
  {
    head = heads_jogos[i];
    while (head != 0)
    {
      heads_jogos[i] = heads_jogos[i]->next;
      free(head);
      head = heads_jogos[i];
    }

    free(heads_jogos[i]);
  }

  free(head);
  free(heads_jogos);
}

void apaga_jogo_hash(link_jogo *heads, char *nome)
{
  link_jogo aux;
  link_jogo t;
  int i = hash(nome, 977);
  aux = heads[i];
  if (strcmp(aux->jogo->nome, nome) == 0)
  {
    {
      t = aux;
      heads[i] = aux->next;
    }
  }
  else
  {
    {
      while (strcmp(aux->next->jogo->nome, nome) != 0)
      {
        aux = aux->next;
      }

      t = aux->next;
      aux->next = t->next;
    }
  }

  free(t);
}

void apaga_jogo_lista(limites_lista *lista, char *nome)
{
  link_lista t;
  link_lista aux = lista->head;
  if (strcmp(aux->jogo->nome, nome) == 0)
  {
    {
      t = aux;
      if (lista->head == lista->last)
      {
        {
          lista->head = 0;
          lista->last = 0;
        }
      }
      else
      {
        {
          lista->head = aux->next;
          lista->head->prev = lista->last;
          lista->last->next = 0;
        }
      }

    }
  }
  else
  {
    {
      while (strcmp(aux->jogo->nome, nome) != 0)
      {
        aux = aux->next;
      }

      t = aux;
      if (aux->next != 0)
      {
        aux->next->prev = t->prev;
      }
      else
      {
        {
          lista->last = aux->prev;
        }
      }

      aux->prev->next = t->next;
    }
  }

  free(t);
}
