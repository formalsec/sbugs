/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"


void __a__(int NL, Hashtable hash_j, Hashtable hash_e, link *head)
{
  char n_s[1024];
  char e1_s[1024];
  char e2_s[1024];
  char *n;
  char *e1;
  char *e2;
  int s1;
  int s2;
  Item j;
  Item v;
  for (int n_s_index = 0; n_s_index < 10; n_s_index++)
  {
    n_s[n_s_index] = new_sym_var(sizeof(char) * 8);
  }

  n_s[10 - 1] = '\0';
  for (int e1_s_index = 0; e1_s_index < 10; e1_s_index++)
  {
    e1_s[e1_s_index] = new_sym_var(sizeof(char) * 8);
  }

  e1_s[10 - 1] = '\0';
  for (int e2_s_index = 0; e2_s_index < 10; e2_s_index++)
  {
    e2_s[e2_s_index] = new_sym_var(sizeof(char) * 8);
  }

  e2_s[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  n = cria_pchar(n_s);
  e1 = cria_pchar(e1_s);
  e2 = cria_pchar(e2_s);
  j = cria_item(n, e1, e2, s1, s2);
  if (procura_hash(n, hash_j) != 0)
  {
    {
      printf("%d Jogo existente.\n", NL);
      free_item(j);
      return;
    }
  }
  else
  {
    
  }

  if ((procura_hash(e1, hash_e) == 0) || (procura_hash(e2, hash_e) == 0))
  {
    {
      printf("%d Equipa inexistente.\n", NL);
      free_item(j);
      return;
    }
  }
  else
  {
    
  }

  insere_hash(j, hash_j);
  insere_lista(j, head);
  if ((v = vencedor(e1, e2, s1, s2, hash_e)) != 0)
  {
    v->vitorias++;
  }
  else
  {
    
  }

}

void __A__(int NL, Hashtable hasht)
{
  char n_s[1024];
  char *n;
  Item e;
  for (int n_s_index = 0; n_s_index < 10; n_s_index++)
  {
    n_s[n_s_index] = new_sym_var(sizeof(char) * 8);
  }

  n_s[10 - 1] = '\0';
  n = cria_pchar(n_s);
  if (procura_hash(n, hasht) != 0)
  {
    {
      printf("%d Equipa existente.\n", NL);
      free(n);
      return;
    }
  }
  else
  {
    
  }

  e = cria_item(n, 0, 0, 0, 0);
  insere_hash(e, hasht);
}

void __l__(int NL, link head)
{
  if (head != 0)
  {
    imprime_lista(NL, head);
  }
  else
  {
    
  }

}

void __p__(int NL, Hashtable hasht)
{
  char n[1024];
  Item j;
  for (int n_index = 0; n_index < 10; n_index++)
  {
    n[n_index] = new_sym_var(sizeof(char) * 8);
  }

  n[10 - 1] = '\0';
  j = procura_hash(n, hasht);
  if (j == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  imprime_jogo(j, NL);
}

void __P__(int NL, Hashtable hasht)
{
  char n[1024];
  Item e;
  for (int n_index = 0; n_index < 10; n_index++)
  {
    n[n_index] = new_sym_var(sizeof(char) * 8);
  }

  n[10 - 1] = '\0';
  e = procura_hash(n, hasht);
  if (e == 0)
  {
    {
      printf("%d Equipa inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  printf("%d %s %d\n", NL, n, e->vitorias);
}

void __r__(int NL, Hashtable hash_j, Hashtable hash_e, link *head)
{
  char n[1024];
  Item j;
  Item v;
  for (int n_index = 0; n_index < 10; n_index++)
  {
    n[n_index] = new_sym_var(sizeof(char) * 8);
  }

  n[10 - 1] = '\0';
  j = apaga_hash(n, hash_j);
  if (j == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  apaga_lista(j, head);
  v = vencedor(j->e1, j->e2, j->s1, j->s2, hash_e);
  if (v != 0)
  {
    v->vitorias--;
  }
  else
  {
    
  }

  free_item(j);
}

void __s__(int NL, Hashtable hash_j, Hashtable hash_e)
{
  char n[1024];
  int s1;
  int s2;
  Item j;
  Item aux;
  Item v;
  for (int n_index = 0; n_index < 10; n_index++)
  {
    n[n_index] = new_sym_var(sizeof(char) * 8);
  }

  n[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  j = procura_hash(n, hash_j);
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  if (j == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  aux = vencedor(j->e1, j->e2, j->s1, j->s2, hash_e);
  j->s1 = s1;
  j->s2 = s2;
  v = vencedor(j->e1, j->e2, j->s1, j->s2, hash_e);
  if (aux == v)
  {
    return;
  }
  else
  {
    
  }

  if (aux == 0)
  {
    {
      v->vitorias++;
      return;
    }
  }
  else
  {
    
  }

  if (v == 0)
  {
    {
      aux->vitorias--;
      return;
    }
  }
  else
  {
    
  }

  v->vitorias++;
  aux->vitorias--;
}

void __g__(int NL, Hashtable hasht)
{
  Item *endereco = hasht->endereco;
  int M = hasht->M;
  int i;
  int j = 0;
  int V = 0;
  int equipas = 0;
  char **lista;
  if (hasht->N == 0)
  {
    return;
  }
  else
  {
    
  }

  for (i = 0; i < M; i++)
    if (endereco[i] != 0)
  {
    {
      if (endereco[i]->vitorias == V)
      {
        equipas++;
      }
      else
      {
        
      }

      if (endereco[i]->vitorias > V)
      {
        {
          V = endereco[i]->vitorias;
          equipas = 1;
        }
      }
      else
      {
        
      }

    }
  }
  else
  {
    
  }


  lista = (char **) malloc((sizeof(char *)) * equipas);
  for (i = 0; i < M; i++)
    if (endereco[i] != 0)
  {
    {
      if (endereco[i]->vitorias == V)
      {
        {
          lista[j] = endereco[i]->nome;
          j++;
        }
      }
      else
      {
        
      }

    }
  }
  else
  {
    
  }


  qsort(lista, equipas, sizeof(char *), compara);
  printf("%d Melhores %d\n", NL, V);
  for (i = 0; i < equipas; i++)
    printf("%d * %s\n", NL, lista[i]);

  free(lista);
}

