/*File generated by PreProcessor.py*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "jogos.h"


int hash_function_jogos(char *string, int tamanho_max)
{
  int hash;
  int a = 31415;
  int b = 27183;
  for (hash = 0; (*string) != '\0'; string++, a = (a * b) % (tamanho_max - 1))
    hash = ((a * hash) + (*string)) % tamanho_max;

  return hash;
}

hashtable_jogos *inicializa_jogos(int tamanho_maximo)
{
  int hash;
  hashtable_jogos *tabela_jogos;
  tabela_jogos = (hashtable_jogos *) malloc(sizeof(hashtable_jogos));
  tabela_jogos->tamanho_maximo = tamanho_maximo;
  tabela_jogos->vetor_hashes = (link_hashtable_jogos *) malloc(tamanho_maximo * (sizeof(link_hashtable_jogos)));
  for (hash = 0; hash < tamanho_maximo; hash++)
    tabela_jogos->vetor_hashes[hash].next = 0;

  return tabela_jogos;
}

lista_ord_jogos *inicializa_jogos_lista()
{
  lista_ord_jogos *lista_jogos;
  lista_jogos = (lista_ord_jogos *) malloc(sizeof(lista_ord_jogos));
  lista_jogos->head = 0;
  lista_jogos->tail = 0;
  return lista_jogos;
}

void inserir_jogo(char *nome_jogo, link_equipa *equipa1, link_equipa *equipa2, int score1, int score2, hashtable_jogos *tabela_jogos, lista_ord_jogos *lista_jogos)
{
  char *novo_nome_jogo;
  int hash;
  jogo *novo_jogo;
  link_jogo *no_novo_jogo;
  novo_nome_jogo = (char *) malloc((strlen(nome_jogo) + 1) * (sizeof(char)));
  strcpy(novo_nome_jogo, nome_jogo);
  novo_jogo = (jogo *) malloc(sizeof(jogo));
  novo_jogo->nome_jogo = novo_nome_jogo;
  novo_jogo->pequipa1 = equipa1;
  novo_jogo->pequipa2 = equipa2;
  novo_jogo->pontos1 = score1;
  novo_jogo->pontos2 = score2;
  no_novo_jogo = (link_jogo *) malloc(sizeof(link_jogo));
  no_novo_jogo->pointer_jogo = novo_jogo;
  hash = hash_function_jogos(nome_jogo, tabela_jogos->tamanho_maximo);
  if (tabela_jogos->vetor_hashes[hash].next == 0)
  {
    no_novo_jogo->jogo_next_hashtable = 0;
    tabela_jogos->vetor_hashes[hash].next = no_novo_jogo;
  }
  else
  {
    no_novo_jogo->jogo_next_hashtable = tabela_jogos->vetor_hashes[hash].next;
    tabela_jogos->vetor_hashes[hash].next = no_novo_jogo;
  }

  if (lista_jogos->head == 0)
  {
    lista_jogos->head = no_novo_jogo;
    lista_jogos->tail = no_novo_jogo;
    no_novo_jogo->jogo_anterior_lista = 0;
    no_novo_jogo->jogo_next_lista = 0;
  }
  else
  {
    lista_jogos->tail->jogo_next_lista = no_novo_jogo;
    no_novo_jogo->jogo_anterior_lista = lista_jogos->tail;
    no_novo_jogo->jogo_next_lista = 0;
    lista_jogos->tail = no_novo_jogo;
  }

  if (score1 > score2)
  {
    equipa1->numero_vitorias++;
  }
  else
  {
    if (score1 < score2)
    {
      equipa2->numero_vitorias++;
    }
    else
    {
      
    }

  }

}

void listar_todos_jogos(int linha_input, lista_ord_jogos *lista_jogos)
{
  link_jogo *pjogo_atual;
  jogo *jogo_atual;
  pjogo_atual = lista_jogos->head;
  while (pjogo_atual != 0)
  {
    jogo_atual = pjogo_atual->pointer_jogo;
    printf("%d %s %s %s %d %d\n", linha_input, jogo_atual->nome_jogo, jogo_atual->pequipa1->nome_equipa, jogo_atual->pequipa2->nome_equipa, jogo_atual->pontos1, jogo_atual->pontos2);
    pjogo_atual = pjogo_atual->jogo_next_lista;
  }

}

link_jogo *procurar_jogo(char *nome_jogo, hashtable_jogos *tabela_jogos)
{
  int hash;
  link_jogo *link_atual;
  hash = hash_function_jogos(nome_jogo, tabela_jogos->tamanho_maximo);
  if (tabela_jogos->vetor_hashes[hash].next == 0)
  {
    return 0;
  }
  else
  {
    link_atual = tabela_jogos->vetor_hashes[hash].next;
    while (link_atual != 0)
    {
      if (!strcmp(link_atual->pointer_jogo->nome_jogo, nome_jogo))
      {
        return link_atual;
      }
      else
      {
        link_atual = link_atual->jogo_next_hashtable;
      }

    }

    return 0;
  }

}

void apagar_jogo(char *nome_jogo, hashtable_jogos *tabela_jogos, lista_ord_jogos *lista_jogos)
{
  int hash;
  link_jogo *jogo_anterior;
  link_jogo *jogo_alvo;
  link_jogo *jogo_next;
  hash = hash_function_jogos(nome_jogo, tabela_jogos->tamanho_maximo);
  if (strcmp(nome_jogo, tabela_jogos->vetor_hashes[hash].next->pointer_jogo->nome_jogo) == 0)
  {
    jogo_alvo = tabela_jogos->vetor_hashes[hash].next;
    jogo_next = jogo_alvo->jogo_next_hashtable;
    tabela_jogos->vetor_hashes[hash].next = jogo_next;
  }
  else
  {
    jogo_anterior = tabela_jogos->vetor_hashes[hash].next;
    while (1)
    {
      if (strcmp(jogo_anterior->jogo_next_hashtable->pointer_jogo->nome_jogo, nome_jogo) == 0)
      {
        jogo_alvo = jogo_anterior->jogo_next_hashtable;
        jogo_next = jogo_alvo->jogo_next_hashtable;
        jogo_anterior->jogo_next_hashtable = jogo_next;
        break;
      }
      else
      {
        jogo_anterior = jogo_anterior->jogo_next_hashtable;
      }

    }

  }

  if ((jogo_alvo->jogo_anterior_lista == 0) && (jogo_alvo->jogo_next_lista == 0))
  {
    lista_jogos->head = 0;
    lista_jogos->tail = 0;
  }
  else
  {
    if (jogo_alvo->jogo_anterior_lista == 0)
    {
      jogo_next = jogo_alvo->jogo_next_lista;
      lista_jogos->head = jogo_next;
      jogo_next->jogo_anterior_lista = 0;
    }
    else
    {
      if (jogo_alvo->jogo_next_lista == 0)
      {
        jogo_anterior = jogo_alvo->jogo_anterior_lista;
        lista_jogos->tail = jogo_anterior;
        jogo_anterior->jogo_next_lista = 0;
      }
      else
      {
        jogo_next = jogo_alvo->jogo_next_lista;
        jogo_anterior = jogo_alvo->jogo_anterior_lista;
        jogo_anterior->jogo_next_lista = jogo_next;
        jogo_next->jogo_anterior_lista = jogo_anterior;
      }

    }

  }

  if (jogo_alvo->pointer_jogo->pontos1 > jogo_alvo->pointer_jogo->pontos2)
  {
    jogo_alvo->pointer_jogo->pequipa1->numero_vitorias--;
  }
  else
  {
    if (jogo_alvo->pointer_jogo->pontos1 < jogo_alvo->pointer_jogo->pontos2)
    {
      jogo_alvo->pointer_jogo->pequipa2->numero_vitorias--;
    }
    else
    {
      
    }

  }

  free(jogo_alvo->pointer_jogo->nome_jogo);
  free(jogo_alvo->pointer_jogo);
  free(jogo_alvo);
}

void alterar_jogo(link_jogo *jogo, int score1, int score2)
{
  int score1temp;
  int score2temp;
  score1temp = jogo->pointer_jogo->pontos1;
  score2temp = jogo->pointer_jogo->pontos2;
  if (score1temp > score2temp)
  {
    jogo->pointer_jogo->pequipa1->numero_vitorias--;
  }
  else
  {
    if (score1temp < score2temp)
    {
      jogo->pointer_jogo->pequipa2->numero_vitorias--;
    }
    else
    {
      
    }

  }

  jogo->pointer_jogo->pontos1 = score1;
  jogo->pointer_jogo->pontos2 = score2;
  if (score1 > score2)
  {
    jogo->pointer_jogo->pequipa1->numero_vitorias++;
  }
  else
  {
    if (score1 < score2)
    {
      jogo->pointer_jogo->pequipa2->numero_vitorias++;
    }
    else
    {
      
    }

  }

}

void destruir_jogos(hashtable_jogos *tabela_jogos)
{
  int hash;
  link_jogo *jogo_atual;
  link_jogo *jogo_temporario;
  for (hash = 0; hash < tabela_jogos->tamanho_maximo; hash++)
  {
    jogo_atual = tabela_jogos->vetor_hashes[hash].next;
    while (jogo_atual != 0)
    {
      jogo_temporario = jogo_atual->jogo_next_hashtable;
      free(jogo_atual->pointer_jogo->nome_jogo);
      free(jogo_atual->pointer_jogo);
      free(jogo_atual);
      jogo_atual = jogo_temporario;
    }

  }

  free(tabela_jogos->vetor_hashes);
  free(tabela_jogos);
}

void destruir_lista(lista_ord_jogos *lista_jogos)
{
  free(lista_jogos);
}
