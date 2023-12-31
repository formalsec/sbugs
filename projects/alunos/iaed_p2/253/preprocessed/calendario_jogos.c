#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "TABELA_HASH_E.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void free_Jogo(Jogo *n)
{
  free(n->nome);
  free(n->eqcasa);
  free(n->eqfora);
  free(n);
}

void free_listJ(listJogos *l)
{
  while (l->primeiro)
  {
    Jogo *temp = l->primeiro->proximo;
    free_Jogo(l->primeiro);
    l->primeiro = temp;
  }

  free(l);
}

int verifica_j(Tabela_hash *calendario, const char *nome)
{
  const size_t i = hash(nome, calendario->capacidade);
  No_hash *no;
  for (no = calendario->topos[i]; no != 0; no = no->proximo)
    if (strcmp(no->pont_jogo->nome, nome) == 0)
  {
    return 0;
  }
  else
  {
    
  }


  return 1;
}

listJogos *cria_listJogos()
{
  listJogos *jogos = malloc(sizeof(listJogos));
  jogos->primeiro = 0;
  jogos->ultimo = 0;
  return jogos;
}

void cria_Jogo(listJogos *jogos, const char *nome, const char *casa, const char *fora, int g_casa, int g_fora, Tabela_hash *calendario)
{
  const size_t i = hash(nome, calendario->capacidade);
  Jogo *novo = malloc(sizeof(Jogo));
  novo->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
  strcpy(novo->nome, nome);
  novo->eqcasa = malloc((sizeof(char)) * (strlen(casa) + 1));
  strcpy(novo->eqcasa, casa);
  novo->eqfora = malloc((sizeof(char)) * (strlen(fora) + 1));
  strcpy(novo->eqfora, fora);
  novo->golos_casa = g_casa;
  novo->golos_fora = g_fora;
  novo->anterior = jogos->ultimo;
  novo->proximo = 0;
  if (jogos->ultimo)
  {
    jogos->ultimo->proximo = novo;
  }
  else
  {
    jogos->primeiro = novo;
  }

  jogos->ultimo = novo;
  calendario->topos[i] = cria_Jogo_hash(calendario->topos[i], novo);
}

No_hash *cria_Jogo_hash(No_hash *ultimo, Jogo *novo_J)
{
  No_hash *nn = malloc(sizeof(No_hash));
  nn->pont_jogo = novo_J;
  nn->proximo = ultimo;
  return nn;
}

void rm_jogo(listJogos *lista_jogos, Jogo *jogo)
{
  if (jogo->anterior == 0)
  {
    lista_jogos->primeiro = jogo->proximo;
  }
  else
  {
    jogo->anterior->proximo = jogo->proximo;
  }

  if (jogo->proximo == 0)
  {
    lista_jogos->ultimo = jogo->anterior;
  }
  else
  {
    jogo->proximo->anterior = jogo->anterior;
  }

  free_Jogo(jogo);
}

void adiciona_jogo(listJogos *lista_jogos, Tabela_hash *calendario, Tabela_hash *tabela, int contador)
{
  char nome[1024];
  char casa[1024];
  char fora[1024];
  int g_casa;
  int g_fora;
  getchar();
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  for (int casa_index = 0; casa_index < 10; casa_index++)
  {
    casa[casa_index] = new_sym_var(sizeof(char) * 8);
  }

  casa[10 - 1] = '\0';
  for (int fora_index = 0; fora_index < 10; fora_index++)
  {
    fora[fora_index] = new_sym_var(sizeof(char) * 8);
  }

  fora[10 - 1] = '\0';
  g_casa = new_sym_var(sizeof(int) * 8);
  g_fora = new_sym_var(sizeof(int) * 8);
  if (verifica_j(calendario, nome) == 0)
  {
    printf("%d Jogo existente.\n", contador);
    return;
  }
  else
  {
    
  }

  if ((verifica_e(tabela, casa) == 1) || (verifica_e(tabela, fora) == 1))
  {
    printf("%d Equipa inexistente.\n", contador);
    return;
  }
  else
  {
    
  }

  cria_Jogo(lista_jogos, nome, casa, fora, g_casa, g_fora, calendario);
  if (g_casa > g_fora)
  {
    aumenta_pontos(tabela, casa);
  }
  else
  {
    
  }

  if (g_casa < g_fora)
  {
    aumenta_pontos(tabela, fora);
  }
  else
  {
    
  }

}

void lista_todos_jogos(listJogos *lista_jogos, int contador)
{
  Jogo *jogo;
  if (lista_jogos->primeiro == 0)
  {
    return;
  }
  else
  {
    
  }

  for (jogo = lista_jogos->primeiro; jogo != 0; jogo = jogo->proximo)
    printf("%d %s %s %s %d %d\n", contador, jogo->nome, jogo->eqcasa, jogo->eqfora, jogo->golos_casa, jogo->golos_fora);

}

void procura_jogo(Tabela_hash *calendario, int contador)
{
  char nome[1024];
  No_hash *no;
  getchar();
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (verifica_j(calendario, nome) == 1)
  {
    printf("%d Jogo inexistente.\n", contador);
  }
  else
  {
    const size_t i = hash(nome, calendario->capacidade);
    for (no = calendario->topos[i]; no != 0; no = no->proximo)
      if (strcmp(no->pont_jogo->nome, nome) == 0)
    {
      printf("%d %s %s %s %d %d\n", contador, no->pont_jogo->nome, no->pont_jogo->eqcasa, no->pont_jogo->eqfora, no->pont_jogo->golos_casa, no->pont_jogo->golos_fora);
      return;
    }
    else
    {
      
    }


  }

}

void apaga_jogo(Tabela_hash *calendario, Tabela_hash *tabela, listJogos *lista_jogos, int contador)
{
  char nome[1024];
  No_hash *jogo;
  No_hash *ant;
  long int i;
  getchar();
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  i = hash(nome, calendario->capacidade);
  jogo = calendario->topos[i];
  if (verifica_j(calendario, nome) == 1)
  {
    printf("%d Jogo inexistente.\n", contador);
    return;
  }
  else
  {
    
  }

  if ((jogo != 0) && (strcmp(jogo->pont_jogo->nome, nome) == 0))
  {
    if (jogo->pont_jogo->golos_casa > jogo->pont_jogo->golos_fora)
    {
      retira_pontos(tabela, jogo->pont_jogo->eqcasa);
    }
    else
    {
      
    }

    if (jogo->pont_jogo->golos_casa < jogo->pont_jogo->golos_fora)
    {
      retira_pontos(tabela, jogo->pont_jogo->eqfora);
    }
    else
    {
      
    }

    rm_jogo(lista_jogos, jogo->pont_jogo);
    calendario->topos[i] = jogo->proximo;
    free(jogo);
    return;
  }
  else
  {
    while ((jogo != 0) && ((!strcmp(jogo->pont_jogo->nome, nome)) == 0))
    {
      ant = jogo;
      jogo = jogo->proximo;
    }

  }

  if (jogo->pont_jogo->golos_casa > jogo->pont_jogo->golos_fora)
  {
    retira_pontos(tabela, jogo->pont_jogo->eqcasa);
  }
  else
  {
    
  }

  if (jogo->pont_jogo->golos_casa < jogo->pont_jogo->golos_fora)
  {
    retira_pontos(tabela, jogo->pont_jogo->eqfora);
  }
  else
  {
    
  }

  rm_jogo(lista_jogos, jogo->pont_jogo);
  ant->proximo = jogo->proximo;
  free(jogo);
}

void altera_resultado(Tabela_hash *calendario, Tabela_hash *tabela, int contador)
{
  char nome[1024];
  No_hash *jogo;
  int score_casa;
  int score_fora;
  getchar();
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score_casa = new_sym_var(sizeof(int) * 8);
  score_fora = new_sym_var(sizeof(int) * 8);
  if (verifica_j(calendario, nome) == 1)
  {
    printf("%d Jogo inexistente.\n", contador);
  }
  else
  {
    const size_t i = hash(nome, calendario->capacidade);
    for (jogo = calendario->topos[i]; jogo != 0; jogo = jogo->proximo)
      if (strcmp(jogo->pont_jogo->nome, nome) == 0)
    {
      altera_pontos(tabela, jogo, score_casa, score_fora);
      jogo->pont_jogo->golos_casa = score_casa;
      jogo->pont_jogo->golos_fora = score_fora;
    }
    else
    {
      
    }


  }

}

void altera_pontos(Tabela_hash *tabela, No_hash *jogo, int score_casa, int score_fora)
{
  if (jogo->pont_jogo->golos_casa > jogo->pont_jogo->golos_fora)
  {
    if (score_casa < score_fora)
    {
      retira_pontos(tabela, jogo->pont_jogo->eqcasa);
      aumenta_pontos(tabela, jogo->pont_jogo->eqfora);
    }
    else
    {
      if (score_casa == score_fora)
      {
        retira_pontos(tabela, jogo->pont_jogo->eqcasa);
      }
      else
      {
        
      }

    }

  }
  else
  {
    if (jogo->pont_jogo->golos_casa < jogo->pont_jogo->golos_fora)
    {
      if (score_casa > score_fora)
      {
        aumenta_pontos(tabela, jogo->pont_jogo->eqcasa);
        retira_pontos(tabela, jogo->pont_jogo->eqfora);
      }
      else
      {
        if (score_casa == score_fora)
        {
          retira_pontos(tabela, jogo->pont_jogo->eqfora);
        }
        else
        {
          
        }

      }

    }
    else
    {
      if (jogo->pont_jogo->golos_casa == jogo->pont_jogo->golos_fora)
      {
        if (score_casa > score_fora)
        {
          aumenta_pontos(tabela, jogo->pont_jogo->eqcasa);
        }
        else
        {
          if (score_casa < score_fora)
          {
            aumenta_pontos(tabela, jogo->pont_jogo->eqfora);
          }
          else
          {
            
          }

        }

      }
      else
      {
        
      }

    }

  }

}

