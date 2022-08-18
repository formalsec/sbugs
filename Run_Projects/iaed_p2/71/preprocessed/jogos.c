/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jog_ligados.h"
#include "jogos.h"


jlink *init_jogos()
{
  int i;
  jlink *hash_jogos = (jlink *) malloc((sizeof(jlink)) * 1657);
  for (i = 0; i < 1657; i++)
  {
    hash_jogos[i] = 0;
  }

  return hash_jogos;
}

jlink novo_jlink(Jogo jogo, jlink cabeca)
{
  jlink link = malloc(sizeof(struct node_jogos));
  link->jogo = jogo;
  link->proximo = cabeca;
  return link;
}

jlink push_jogo(jlink cabeca, Jogo jogo)
{
  jlink nova_cabeca = novo_jlink(jogo, cabeca);
  return nova_cabeca;
}

void adiciona_jogo(jlink *hash_jogos, Lista_Jogos lista, Jogo jogo)
{
  int chave = hash(jogo->nome);
  acrescenta_jogo(lista, jogo);
  hash_jogos[chave] = push_jogo(hash_jogos[chave], jogo);
}

jlink rem_aux2(jlink cabeca, Jogo jogo)
{
  jlink atual;
  jlink anterior = 0;
  for (atual = cabeca; atual != 0; atual = atual->proximo)
  {
    if (atual->jogo == jogo)
    {
      {
        if (atual == cabeca)
        {
          cabeca = atual->proximo;
        }
        else
        {
          anterior->proximo = atual->proximo;
        }

        FREEjlink(atual);
        return cabeca;
      }
    }
    else
    {
      anterior = atual;
    }

  }

  return cabeca;
}

void remove_jogo(jlink *hash_jogos, Lista_Jogos lista, Jogo jogo)
{
  int chave = hash(jogo->nome);
  rem_aux1(lista, jogo);
  hash_jogos[chave] = rem_aux2(hash_jogos[chave], jogo);
}

int existe_jogo_aux(jlink cabeca, char *nome)
{
  jlink x;
  for (x = cabeca; x != 0; x = x->proximo)
  {
    if (strcmp(x->jogo->nome, nome) == 0)
    {
      {
        return 1;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

int existe_jogo(jlink *hash_jogos, char *nome)
{
  int chave = hash(nome);
  return existe_jogo_aux(hash_jogos[chave], nome);
}

Jogo procura_jogo_aux(jlink cabeca, char *nome)
{
  jlink x;
  for (x = cabeca; x != 0; x = x->proximo)
  {
    if (strcmp(x->jogo->nome, nome) == 0)
    {
      return x->jogo;
    }
    else
    {
      
    }

  }

  return 0;
}

Jogo procura_jogo(jlink *hash_jogos, char *nome)
{
  int chave = hash(nome);
  return procura_jogo_aux(hash_jogos[chave], nome);
}

jlink limpa_lista_jogos(jlink cabeca)
{
  jlink atual;
  jlink aux;
  if (cabeca == 0)
  {
    {
      free(cabeca);
      return cabeca;
    }
  }
  else
  {
    if (cabeca->proximo == 0)
    {
      {
        FREEjlink(cabeca);
        return 0;
      }
    }
    else
    {
      {
        atual = cabeca->proximo;
        while (atual != 0)
        {
          aux = cabeca->proximo;
          cabeca->proximo = aux->proximo;
          FREEjlink(aux);
          atual = cabeca->proximo;
        }

        FREEjlink(cabeca);
        return 0;
      }
    }

  }

}

void limpa_hash_jogos(jlink *hash_jogos)
{
  int i;
  for (i = 0; i < 1657; i++)
  {
    hash_jogos[i] = limpa_lista_jogos(hash_jogos[i]);
  }

  free(hash_jogos);
}

