#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "comandos.h"
#include "structs.h"


int existe_equipa(team_n **hash_teams, char *name)
{
  int i;
  int indice = hash_function(name);
  team_n *auxiliar = hash_teams[indice];
  while ((auxiliar != 0) && (strcmp(auxiliar->name, name) != 0))
  {
    auxiliar = auxiliar->next;
  }

  if (auxiliar == 0)
  {
    i = 0;
    return i;
  }
  else
  {
    i = 1;
    return i;
  }

}

void altera_numero_vitorias(team_n **hash_teams, char *equipa, bool valor)
{
  int id = hash_function(equipa);
  team_n *t = hash_teams[id];
  while ((t != 0) && (strcmp(t->name, equipa) != 0))
  {
    t = t->next;
  }

  if (valor == true)
  {
    t->wins = t->wins + 1;
  }
  else
  {
    if (valor == false)
    {
      t->wins = t->wins - 1;
    }
    else
    {
      
    }

  }

}

game_n *a_adiciona_jogo(game_n **hash_table, team_n **hash_teams, game_n *head, int nl)
{
  game_n *t = 0;
  game_n *auxiliar = 0;
  bool valor;
  int id = 0;
  int i1;
  int i2;
  int score1 = 0;
  int score2 = 0;
  char *nome = malloc((sizeof(char)) * (1023 + 1));
  char *equipa1 = malloc((sizeof(char)) * (1023 + 1));
  char *equipa2 = malloc((sizeof(char)) * (1023 + 1));
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
  t = (game_n *) malloc(sizeof(game_n));
  t->nome = (char *) malloc(((sizeof(char)) * strlen(nome)) + 1);
  strcpy(t->nome, nome);
  t->equipa1 = (char *) malloc(((sizeof(char)) * strlen(equipa1)) + 1);
  strcpy(t->equipa1, equipa1);
  t->equipa2 = (char *) malloc(((sizeof(char)) * strlen(equipa2)) + 1);
  strcpy(t->equipa2, equipa2);
  t->score1 = score1;
  t->score2 = score2;
  t->next = 0;
  t->lista = 0;
  id = hash_function(t->nome);
  auxiliar = hash_table[id];
  while (auxiliar != 0)
  {
    if (strcmp(auxiliar->nome, t->nome) == 0)
    {
      printf("%d Jogo existente.\n", nl);
      free_jogo(t);
      free(nome);
      free(equipa1);
      free(equipa2);
      return head;
    }
    else
    {
      
    }

    auxiliar = auxiliar->next;
  }

  i1 = existe_equipa(hash_teams, t->equipa1);
  if (i1 == 0)
  {
    free_jogo(t);
    free(nome);
    free(equipa1);
    free(equipa2);
    printf("%d Equipa inexistente.\n", nl);
    return head;
  }
  else
  {
    
  }

  i2 = existe_equipa(hash_teams, t->equipa2);
  if (i2 == 0)
  {
    free_jogo(t);
    free(nome);
    free(equipa1);
    free(equipa2);
    printf("%d Equipa inexistente.\n", nl);
    return head;
  }
  else
  {
    
  }

  valor = true;
  if (t->score1 > t->score2)
  {
    altera_numero_vitorias(hash_teams, t->equipa1, valor);
  }
  else
  {
    if (t->score2 > t->score1)
    {
      altera_numero_vitorias(hash_teams, t->equipa2, valor);
    }
    else
    {
      
    }

  }

  inserir_hash_table(hash_table, t);
  head = inserir_na_head(head, t);
  free(nome);
  free(equipa1);
  free(equipa2);
  return head;
}

team_n *A_adiciona_equipa(team_n **hash_teams, team_n *head_team, int nl)
{
  team_n *t;
  team_n *auxiliar = 0;
  int id;
  char *name = malloc((sizeof(char)) * (1023 + 1));
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  t = (team_n *) malloc(sizeof(team_n));
  t->name = (char *) malloc(((sizeof(char)) * strlen(name)) + 1);
  strcpy(t->name, name);
  t->wins = 0;
  t->next = 0;
  t->lista = 0;
  id = hash_function(t->name);
  auxiliar = hash_teams[id];
  while (auxiliar != 0)
  {
    if (strcmp(auxiliar->name, t->name) == 0)
    {
      printf("%d Equipa existente.\n", nl);
      free_equipa(t);
      free(name);
      return head_team;
    }
    else
    {
      
    }

    auxiliar = auxiliar->next;
  }

  inserir_hash_teams(hash_teams, t);
  head_team = inserir_na_head_teams(head_team, t);
  free(name);
  return head_team;
}

void l_lista_jogos(game_n *head, int nl)
{
  game_n *a = head;
  if (a == 0)
  {
    return;
  }
  else
  {
    
  }

  l_lista_jogos(a->lista, nl);
  printf("%d %s %s %s %d %d\n", nl, a->nome, a->equipa1, a->equipa2, a->score1, a->score2);
}

void p_procura_jogo(game_n **hash_table, int nl)
{
  game_n *t = 0;
  int id = 0;
  char *nome = malloc((sizeof(char)) * (1023 + 1));
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  id = hash_function(nome);
  t = hash_table[id];
  if (t == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
    free(nome);
    return;
  }
  else
  {
    while ((t != 0) && (strcmp(t->nome, nome) != 0))
    {
      t = t->next;
    }

    if (t == 0)
    {
      printf("%d Jogo inexistente.\n", nl);
      free(nome);
      return;
    }
    else
    {
      
    }

    if (strcmp(t->nome, nome) == 0)
    {
      printf("%d %s %s %s %d %d\n", nl, t->nome, t->equipa1, t->equipa2, t->score1, t->score2);
      free(nome);
      return;
    }
    else
    {
      
    }

  }

}

void P_procura_equipa(team_n **hash_teams, int nl)
{
  team_n *t = 0;
  int id = 0;
  char *name = malloc((sizeof(char)) * (1023 + 1));
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  id = hash_function(name);
  t = hash_teams[id];
  if (t == 0)
  {
    printf("%d Equipa inexistente.\n", nl);
    free(name);
    return;
  }
  else
  {
    while ((t != 0) && (strcmp(t->name, name) != 0))
    {
      t = t->next;
    }

    if (t == 0)
    {
      printf("%d Equipa inexistente.\n", nl);
      free(name);
      return;
    }
    else
    {
      
    }

    if (strcmp(t->name, name) == 0)
    {
      printf("%d %s %d\n", nl, t->name, t->wins);
      free(name);
      return;
    }
    else
    {
      
    }

  }

}

game_n *apaga(game_n *head, char *nome)
{
  game_n *t = head;
  game_n *anterior = 0;
  while (t != 0)
  {
    if (strcmp(t->nome, nome) == 0)
    {
      if (t == head)
      {
        head = t->lista;
      }
      else
      {
        anterior->lista = t->lista;
      }

      free_jogo(t);
      break;
    }
    else
    {
      
    }

    anterior = t;
    t = t->lista;
  }

  return head;
}

game_n *r_apaga_jogo(game_n **hash_table, team_n **hash_teams, game_n *head, int nl)
{
  game_n *t = 0;
  game_n *anterior = 0;
  bool valor;
  int id = 0;
  char *nome = malloc((sizeof(char)) * (1023 + 1));
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  id = hash_function(nome);
  t = hash_table[id];
  if (t == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
    free(nome);
    return head;
  }
  else
  {
    while ((t != 0) && (strcmp(t->nome, nome) != 0))
    {
      anterior = t;
      t = t->next;
    }

    if (t == 0)
    {
      printf("%d Jogo inexistente.\n", nl);
      free(nome);
      return head;
    }
    else
    {
      valor = false;
      if (t->score1 > t->score2)
      {
        altera_numero_vitorias(hash_teams, t->equipa1, valor);
      }
      else
      {
        if (t->score1 < t->score2)
        {
          altera_numero_vitorias(hash_teams, t->equipa2, valor);
        }
        else
        {
          
        }

      }

      if (anterior == 0)
      {
        hash_table[id] = t->next;
      }
      else
      {
        anterior->next = t->next;
      }

    }

  }

  head = apaga(head, nome);
  free(nome);
  return head;
}

void muda_scores(int antigoscore1, int antigoscore2, team_n **hash_teams, game_n *t, bool valor)
{
  if (antigoscore1 > antigoscore2)
  {
    if (t->score1 == t->score2)
    {
      valor = false;
      altera_numero_vitorias(hash_teams, t->equipa1, valor);
    }
    else
    {
      if (t->score1 < t->score2)
      {
        valor = false;
        altera_numero_vitorias(hash_teams, t->equipa1, valor);
        valor = true;
        altera_numero_vitorias(hash_teams, t->equipa2, valor);
      }
      else
      {
        
      }

    }

  }
  else
  {
    if (antigoscore1 == antigoscore2)
    {
      valor = true;
      if (t->score1 > t->score2)
      {
        altera_numero_vitorias(hash_teams, t->equipa1, valor);
      }
      else
      {
        if (t->score1 < t->score2)
        {
          altera_numero_vitorias(hash_teams, t->equipa2, valor);
        }
        else
        {
          
        }

      }

    }
    else
    {
      if (antigoscore1 < antigoscore2)
      {
        if (t->score1 == t->score2)
        {
          valor = false;
          altera_numero_vitorias(hash_teams, t->equipa2, valor);
        }
        else
        {
          if (t->score1 > t->score2)
          {
            valor = true;
            altera_numero_vitorias(hash_teams, t->equipa1, valor);
            valor = false;
            altera_numero_vitorias(hash_teams, t->equipa2, valor);
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

void s_altera_score(game_n **hash_table, team_n **hash_teams, int nl)
{
  game_n *t = 0;
  bool valor = false;
  int id = 0;
  int score1;
  int score2;
  int antigoscore1;
  int antigoscore2;
  char *nome = malloc((sizeof(char)) * (1023 + 1));
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  id = hash_function(nome);
  t = hash_table[id];
  if (t == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
    free(nome);
    return;
  }
  else
  {
    while ((t != 0) && (strcmp(t->nome, nome) != 0))
    {
      t = t->next;
    }

    if (t == 0)
    {
      printf("%d Jogo inexistente.\n", nl);
      free(nome);
      return;
    }
    else
    {
      
    }

    if (strcmp(t->nome, nome) == 0)
    {
      antigoscore1 = t->score1;
      antigoscore2 = t->score2;
      t->score1 = score1;
      t->score2 = score2;
    }
    else
    {
      
    }

  }

  muda_scores(antigoscore1, antigoscore2, hash_teams, t, valor);
  free(nome);
}

int encontrar_maximo(team_n *head_team)
{
  team_n *aux = head_team;
  int maximo = 0;
  while (aux != 0)
  {
    if (aux->wins > maximo)
    {
      maximo = aux->wins;
    }
    else
    {
      
    }

    aux = aux->lista;
  }

  return maximo;
}

int encontrar_numero_maximos(team_n *head_team, int maximo)
{
  team_n *aux = head_team;
  int n_maximos = 0;
  while (aux != 0)
  {
    if (aux->wins == maximo)
    {
      n_maximos++;
    }
    else
    {
      
    }

    aux = aux->lista;
  }

  return n_maximos;
}

int comparar_strings(const void *nome1, const void *nome2)
{
  return strcmp(*((char **) nome1), *((char **) nome2));
}

void g_equipas_vencedoras(team_n *head_team, int nl, int maximo, int n_maximos)
{
  team_n *aux = 0;
  int i = 0;
  int indice = 0;
  char **lista;
  lista = malloc((sizeof(char *)) * n_maximos);
  if ((maximo == 0) && (n_maximos == 0))
  {
    free(lista);
    return;
  }
  else
  {
    
  }

  aux = head_team;
  while (aux != 0)
  {
    if (aux->wins == maximo)
    {
      lista[indice] = aux->name;
      indice++;
    }
    else
    {
      
    }

    aux = aux->lista;
  }

  qsort(lista, n_maximos, sizeof(char *), comparar_strings);
  printf("%d Melhores %d\n", nl, maximo);
  for (i = 0; i < n_maximos; i++)
  {
    printf("%d * %s\n", nl, lista[i]);
  }

  free(lista);
  return;
}

