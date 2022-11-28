#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "p2.h"             /* Header file que contem as estruturas utilizadas no projeto e os comandos */
#include "auxiliares.h"     /* Header file que contem os defines relativos as funcoes auxiliares */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  


Lista_equipas *A(int NL, char s[], hashtable_equipas *ht_equipa, Lista_equipas *lista_equipa)
{
  Equipa *novo;
  Equipa *a = ht_equipas_verifica(ht_equipa, s);
  if (a != 0)
  {
    printf("%d Equipa existente.\n", NL);
    return lista_equipa;
  }
  else
  {
    
  }

  novo = malloc(sizeof(Equipa));
  novo->nome = malloc(strlen(s) + 1);
  strcpy(novo->nome, s);
  novo->vitorias = 0;
  novo->next = 0;
  novo->prev = lista_equipa->last;
  if (lista_equipa->head == 0)
  {
    lista_equipa->head = novo;
  }
  else
  {
    lista_equipa->last->next = novo;
  }

  lista_equipa->last = novo;
  ht_equipas_insere(ht_equipa, s);
  return lista_equipa;
}

void P(int NL, char s[], hashtable_equipas *ht_equipa)
{
  Equipa *a = ht_equipas_verifica(ht_equipa, s);
  if (a == 0)
  {
    printf("%d Equipa inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  printf("%d %s %d\n", NL, a->nome, a->vitorias);
  return;
}

void g(int NL, Lista_equipas *lista_equipa, hashtable_equipas *ht_equipa)
{
  char **e;
  int c = 0;
  int melhor = 0;
  int i;
  int j = 0;
  Equipa *a;
  Equipa *percorre = lista_equipa->head;
  Equipa *descobre = lista_equipa->head;
  e = malloc((sizeof(char *)) * 10003);
  if (lista_equipa->head == 0)
  {
    return;
  }
  else
  {
    
  }

  while (percorre != 0)
  {
    a = ht_equipas_verifica(ht_equipa, percorre->nome);
    c += 1;
    if (a->vitorias >= melhor)
    {
      melhor = a->vitorias;
    }
    else
    {
      
    }

    percorre = percorre->next;
  }

  while (descobre != 0)
  {
    a = ht_equipas_verifica(ht_equipa, descobre->nome);
    if (melhor == a->vitorias)
    {
      e[j++] = a->nome;
    }
    else
    {
      
    }

    descobre = descobre->next;
  }

  qsort(e, j, sizeof(char *), compara);
  printf("%d Melhores %d\n", NL, melhor);
  for (i = 0; i < j; i++)
  {
    printf("%d * %s\n", NL, e[i]);
  }

  free(e);
  return;
}
