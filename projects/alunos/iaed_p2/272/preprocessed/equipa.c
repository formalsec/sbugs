#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "equipa.h"
#include <stdio.h>
#include "hash.h"
#include <string.h>
#include <stdlib.h>


void adiciona_equipa(struct Equipas *equipas, int comandos_total)
{
  char nome[1024];
  int hash;
  struct Equipa *equipa;
  struct Equipa *nova_equipa;
  int nome_length;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  hash = hash_str(nome);
  equipa = equipas->gavetas[hash % 1024];
  while (equipa != 0)
  {
    if (strcmp(nome, equipa->nome) == 0)
    {
      printf("%d Equipa existente.\n", comandos_total);
      return;
    }
    else
    {
      
    }

    if (equipa->next_equipa == 0)
    {
      break;
    }
    else
    {
      
    }

    equipa = equipa->next_equipa;
  }

  nome_length = strlen(nome);
  nome_length = strlen(nome);
  nova_equipa = malloc(sizeof(struct Equipa));
  nome_length = strlen(nome);
  nova_equipa->nome = malloc((sizeof(char)) * (nome_length + 1));
  strcpy(nova_equipa->nome, nome);
  nova_equipa->wins = 0;
  nova_equipa->next_equipa = 0;
  equipas->ordem = realloc(equipas->ordem, (equipas->nequipas + 1) * (sizeof(struct Equipa)));
  equipas->ordem[equipas->nequipas] = nova_equipa;
  equipas->nequipas += 1;
  if (equipa != 0)
  {
    equipa->next_equipa = nova_equipa;
  }
  else
  {
    equipas->gavetas[hash % 1024] = nova_equipa;
  }

}

void procura_equipa(struct Equipas *equipas, int comandos_total)
{
  char nome[1024];
  int hash;
  struct Equipa *equipa;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  hash = hash_str(nome);
  equipa = equipas->gavetas[hash % 1024];
  while (equipa != 0)
  {
    if (strcmp(nome, equipa->nome) == 0)
    {
      printf("%d %s %d\n", comandos_total, equipa->nome, equipa->wins);
      return;
    }
    else
    {
      
    }

    equipa = equipa->next_equipa;
  }

  printf("%d Equipa inexistente.\n", comandos_total);
}

int comparar_equipas(const void *equipa1, const void *equipa2)
{
  if ((*((const struct Equipa **) equipa1))->wins < (*((const struct Equipa **) equipa2))->wins)
  {
    return 1;
  }
  else
  {
    
  }

  if ((*((const struct Equipa **) equipa1))->wins > (*((const struct Equipa **) equipa2))->wins)
  {
    return -1;
  }
  else
  {
    
  }

  return strcmp((*((const struct Equipa **) equipa1))->nome, (*((const struct Equipa **) equipa2))->nome);
}

void melhores_equipas(struct Equipas *equipas, int comandos_total)
{
  int wins;
  int n;
  if (equipas->ordem == 0)
  {
    return;
  }
  else
  {
    
  }

  qsort(equipas->ordem, equipas->nequipas, sizeof(struct Equipa *), comparar_equipas);
  wins = equipas->ordem[0]->wins;
  printf("%d Melhores %d\n", comandos_total, wins);
  for (n = 0; n < equipas->nequipas; n++)
  {
    if (equipas->ordem[n]->wins < wins)
    {
      return;
    }
    else
    {
      
    }

    printf("%d * %s\n", comandos_total, equipas->ordem[n]->nome);
  }

}

