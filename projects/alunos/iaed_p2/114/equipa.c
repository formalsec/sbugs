#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipa.h"
#include <stdio.h>
#include <string.h>

/* Recebe um ponteiro para uma hash table de equipas e inicializa os indices a
NULL */
void ETable_init(LinkE * Table)
{
  int contador;
  for (contador=0 ; contador < HASH_E_SIZE ; contador++)
    Table[contador] = NULL;
}

/*----------------------------------------------------------------------------*/

/* Recebe como input o head de uma lista da hashtable, e adiciona a equipa a essa
lista, retornando a nova lista */
LinkE add_e_to_list(LinkE head, Equipa * equipa)
{
  LinkE new;
  new = (LinkE) (can_fail_malloc (sizeof(NodeE)) );
  new->equipa = equipa;
  new->next = head;
  return new;
}

/*----------------------------------------------------------------------------*/

/* Recebe como input o nome de uma equipa e o tamanho da hash table, e devolve
o index que devera ser ocupado pela equipa */
int hashEquipa(char *v, int M)
{
  int h, a = 31415, b = 27183;
  for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
  h = (a*h + *v) % M;
  return h;
}

/*----------------------------------------------------------------------------*/

/* Recebe como input uma lista da hashtable e o nome de uma equipa, e devolve
o ponteiro para essa equipa caso encontre, caso nao encontre devolve NULL */
Equipa * search_lista_e(LinkE head, char * nome)
{
  while (head!=NULL)
  {
    if (  strcmp(head->equipa->nome,nome)==0  )
    {
      return head->equipa;}
    else
      head = head->next;
  }
  return NULL;
}

/*----------------------------------------------------------------------------*/

/* Recebe como input a hashtable e uma equipa, e adiciona essa equipa a HashTable,
retornando 1, caso essa equipa ja exista retorna 0*/
int add_e_to_hash(LinkE * Table, Equipa * equipa)
{
  int index = hashEquipa(equipa->nome , HASH_E_SIZE) ;

  if ( search_lista_e( Table[index] , equipa->nome )==NULL )
  {
    Table[ index ] = add_e_to_list( Table[ index ] , equipa );
    return 1;
  }

  else
    return 0;
}

/*----------------------------------------------------------------------------*/

/* Recebe como input a Hashtable das equipas e apaga todas as equipas da base
de dados */
void clear_e(LinkE * Table)
{
  int contador;
  LinkE linke,next;

  for (contador=0 ; contador<HASH_E_SIZE ; contador++ )
  {
    linke = Table[contador];
    while (linke!=NULL)
    {
      free(linke->equipa->nome);
      free(linke->equipa);
      next = linke->next;

      free(linke);

      linke = next;
    }
    Table[contador] = NULL;
  }
}

/*----------------------------------------------------------------------------*/

/* Funcao similar ao strcmp, mas que recebe como input equipas, e compara os seus nomes*/
int cmpstr(void const *a, void const *b)
{
    Equipa * aa = *(Equipa **)a;
    Equipa * bb = *(Equipa **)b;

    return strcmp(aa->nome, bb->nome);
}
