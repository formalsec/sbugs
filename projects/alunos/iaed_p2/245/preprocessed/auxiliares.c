#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "p2.h"             /* Header file que contem as estruturas utilizadas no projeto e os comandos */
#include "auxiliares.h"     /* Header file que contem os defines relativos as funcoes auxiliares */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Lista_equipas *criar_lista()
{
  Lista_equipas *lista = malloc(sizeof(Lista_equipas));
  lista->head = 0;
  lista->last = 0;
  return lista;
}

void liberta_lista_equipas(Lista_equipas *lista_equipa)
{
  while (lista_equipa->head != 0)
  {
    Equipa *a = lista_equipa->head->next;
    free(lista_equipa->head->nome);
    free(lista_equipa->head);
    lista_equipa->head = a;
  }

  free(lista_equipa);
}

unsigned int hash(char *key)
{
  unsigned long int value = 0;
  unsigned int i = 0;
  unsigned int key_len = strlen(key);
  for (; i < key_len; ++i)
  {
    value = (value * 37) + key[i];
  }

  value = value % 10003;
  return value;
}

hashtable_equipas *criar_equipas()
{
  int i;
  hashtable_equipas *hashtable = malloc((sizeof(hashtable_equipas)) * 1);
  hashtable->entradas = malloc((sizeof(Equipa)) * 10003);
  for (i = 0; i < 10003; ++i)
  {
    hashtable->entradas[i] = 0;
  }

  return hashtable;
}

void libertar_equipas(hashtable_equipas *hashtable)
{
  int i;
  Equipa *atual;
  Equipa *next;
  for (i = 0; i < 10003; i++)
  {
    atual = hashtable->entradas[i];
    while (atual != 0)
    {
      next = atual->next;
      free(atual->nome);
      free(atual);
      atual = next;
    }

  }

  free(hashtable->entradas);
  free(hashtable);
}

Equipa *ht_equipas_aloca(char *key)
{
  Equipa *p_equipa = malloc(sizeof(Equipa));
  p_equipa->nome = malloc(strlen(key) + 1);
  p_equipa->next = 0;
  p_equipa->prev = 0;
  strcpy(p_equipa->nome, key);
  p_equipa->vitorias = 0;
  return p_equipa;
}

void ht_equipas_insere(hashtable_equipas *hashtable, char *key)
{
  Equipa *prev;
  unsigned int slot = hash(key);
  Equipa *equipa = hashtable->entradas[slot];
  if (equipa == 0)
  {
    hashtable->entradas[slot] = ht_equipas_aloca(key);
    return;
  }
  else
  {
    
  }

  while (equipa != 0)
  {
    if (strcmp(equipa->nome, key) == 0)
    {
      equipa = ht_equipas_aloca(key);
      return;
    }
    else
    {
      
    }

    prev = equipa;
    equipa = prev->next;
  }

  prev->next = ht_equipas_aloca(key);
}

Equipa *ht_equipas_verifica(hashtable_equipas *hashtable, char *key)
{
  unsigned int slot = hash(key);
  Equipa *equipa = hashtable->entradas[slot];
  if (equipa == 0)
  {
    return 0;
  }
  else
  {
    
  }

  while (equipa != 0)
  {
    if (strcmp(equipa->nome, key) == 0)
    {
      return equipa;
    }
    else
    {
      
    }

    equipa = equipa->next;
  }

  return 0;
}

Lista_jogos *criar_lista_j()
{
  Lista_jogos *lista = malloc((sizeof(Lista_jogos)) * 1);
  lista->head = 0;
  lista->last = 0;
  return lista;
}

void liberta_lista(Lista_jogos *lista_jogo)
{
  Jogo *proximo;
  while (lista_jogo->head != 0)
  {
    proximo = lista_jogo->head->next;
    free(lista_jogo->head->nome);
    free(lista_jogo->head->equipa2);
    free(lista_jogo->head);
    lista_jogo->head = proximo;
  }

  free(lista_jogo);
  return;
}

hashtable_jogos *criar_jogos()
{
  int i;
  hashtable_jogos *hashtable_j = malloc(sizeof(hashtable_jogos));
  hashtable_j->entradas = malloc((sizeof(Jogo)) * 10003);
  for (i = 0; i < 10003; ++i)
  {
    hashtable_j->entradas[i] = 0;
  }

  return hashtable_j;
}

void ht_jogos_apaga(hashtable_jogos *ht_jogos, char *key)
{
  Jogo *prev;
  int id = 0;
  unsigned int b = hash(key);
  Jogo *jogo = ht_jogos->entradas[b];
  if (jogo == 0)
  {
    return;
  }
  else
  {
    
  }

  while (jogo != 0)
  {
    if (strcmp(jogo->nome, key) == 0)
    {
      if ((jogo->next == 0) && (id == 0))
      {
        ht_jogos->entradas[b] = 0;
      }
      else
      {
        
      }

      if ((jogo->next == 0) && (id != 0))
      {
        prev->next = 0;
      }
      else
      {
        
      }

      if ((jogo->next != 0) && (id != 0))
      {
        prev->next = jogo->next;
      }
      else
      {
        
      }

      free(jogo->nome);
      free(jogo->equipa1->nome);
      free(jogo->equipa1);
      free(jogo->equipa2->nome);
      free(jogo->equipa2);
      free(jogo);
      return;
    }
    else
    {
      
    }

    prev = jogo;
    jogo = prev->next;
    ++id;
  }

  free(ht_jogos);
}

Jogo *ht_jogos_verifica(hashtable_jogos *hashtable_j, char *key)
{
  unsigned int slot = hash(key);
  Jogo *jogo = hashtable_j->entradas[slot];
  if (jogo == 0)
  {
    return 0;
  }
  else
  {
    
  }

  while (jogo != 0)
  {
    if (strcmp(jogo->nome, key) == 0)
    {
      return jogo;
    }
    else
    {
      
    }

    jogo = jogo->next;
  }

  return 0;
}

int compara(const void *ptr1, const void *ptr2)
{
  char *s1 = *((char **) ptr1);
  char *s2 = *((char **) ptr2);
  return strcmp(s1, s2);
}

