#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "equipa.h"
#include "jogo.h"
#include <stdio.h>
#include <string.h>


/* Recebe um ponteiro para uma hash table e inicializa a hash table com ponteiros
para vetores nulos */
void JTable_init(Link * Table)
{

  int contador;
  for (contador=0 ; contador < HASH_J_SIZE ; contador++)
    Table[contador] = NULL;
}

/*----------------------------------------------------------------------------*/

/* Recebe como input uma string e o tamanho do array e retorna o index indicado para
a table */
int hashJogo(char *v, int M)
{
  int h, a = 31415, b = 27183;
  for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
  h = (a*h + *v) % M;
  return h;
}

/*----------------------------------------------------------------------------*/

/* Recebe como input a head da lista ligada dentro da hashtable, e retorna o link
que contem o jogo em procura, ou NULL caso o jogo nao exista na lista */
Link search_j_lista_Table(Link head, char * nome)
{
  while (head!=NULL)
  {
    if ( strcmp(head->linkj->jogo->nome , nome ) == 0 )
      return head;

    else
      head = head->next;
  }
  return NULL;
}

/*----------------------------------------------------------------------------*/

/* Recebe como input uma hashtable e um nome de um jogo e retorna o ponteiro para
o link desse jogo na hash table caso exista. Caso nao exista devolve NULL*/
Link search_j_Table(Link * Table, char * nome)
{
  int index = hashJogo (nome, HASH_J_SIZE);
  return search_j_lista_Table( Table[index] , nome );
}

/*----------------------------------------------------------------------------*/

/* Recebe como input a Hashtable dos jogos, a HashTable das equipas e os argumentos
de um jogo, e verifica se esse jogo cumpre os requesitos: Nao existir um jogo com esse
nome, e as equipas existirem na base de dados. Devolve 0 se jogo valido, devolve 1 ou
2 caso seja invalido, por motivos diferentes */
int jogo_invalido(Link * JHTable , LinkE * EHTable , char * jogo_nome , 
char * equipa0_nome , char * equipa1_nome)
{
  int indexj;

  indexj = hashJogo(jogo_nome,HASH_J_SIZE) ;
  if ( search_j_lista_Table( JHTable[indexj],jogo_nome )!=NULL )
    return 1;
  else if (search_lista_e(EHTable[hashEquipa(equipa0_nome,HASH_E_SIZE)],equipa0_nome)==NULL||
  search_lista_e( EHTable[hashEquipa(equipa1_nome,HASH_E_SIZE)],equipa1_nome )==NULL)
    return 2;
  return 0;
}

/*----------------------------------------------------------------------------*/

/* Recebe como input a head da lista e um jogo, e retorna a head da nova lista, que
contem este jogo como head e o resto da lista*/
LinkJ add_j_to_main_list (LinkJ head, Jogo * jogo)
{
  LinkJ new;
  new = (LinkJ) (can_fail_malloc (sizeof(NodeJ)));
  new->jogo = jogo;
  new->prev = NULL;
  new->next = head;

  if (head!=NULL)
    head->prev = new;

  return new;
}

/*----------------------------------------------------------------------------*/

/* Recebe como input a head da lista dentro da hashtable, e adiciona o node do jogo
a essa lista, retornando a nova lista */
Link add_linkj_to_list(Link head, LinkJ linkj)
{
  Link new;
  new = (Link) (can_fail_malloc (sizeof(Node)));
  new->prev = NULL;
  new->linkj = linkj;
  new->next = head;

  if (head!=NULL)
    head->prev = new;

  return new;
}

/*----------------------------------------------------------------------------*/

/* Recebe como input a hashtable e adiciona o node do jogo a hashtable */
void add_linkj_hash(Link * Table, LinkJ linkj, char * nome)
{
  int index = hashJogo( nome, HASH_J_SIZE );
  Table[index] = add_linkj_to_list( Table[index] , linkj );
}

/*----------------------------------------------------------------------------*/

/* Recebe um jogo e devolve o ponteiro para a equipa vencedora */
Equipa * vencedor(Jogo * jogo)
{
  if (jogo->score[0] > jogo->score[1])
    return jogo->equipa0;

  else if (jogo->score[0] < jogo->score[1])
    return jogo->equipa1;

  return NULL;
}

/*----------------------------------------------------------------------------*/

/* Recebe a hashtable dos jogos, a head e a tail da lista ligada dos jogos e o
nome do jogo, e remove esse jogo da base de dados. */
int destroy(Link * Table , LinkJ * MainList, LinkJ * Tail , char * nome)
{
  Equipa * e_vencedora;
  Link link = search_j_Table(Table, nome);
  int index = hashJogo(nome,HASH_J_SIZE) ;

  if (link!=NULL)
  {
    e_vencedora = vencedor(link->linkj->jogo);
    if (e_vencedora!=NULL)
      e_vencedora->wins -= 1;

    free(link->linkj->jogo->nome);
    free(link->linkj->jogo);

    /* Esta serie de ifs e elses vai remover o jogo da lista ligada principal */
    if (link->linkj->prev!=NULL)
      link->linkj->prev->next = link->linkj->next;

    else
      *(MainList) = link->linkj->next;


    if (link->linkj->next!=NULL)
      link->linkj->next->prev = link->linkj->prev;

    else
      *(Tail) = link->linkj->prev;


    free(link->linkj);

    /* Esta serie de ifs e elses vai remover o jogo da hashtable */
    if (link->prev==NULL && link->next==NULL)
      Table[index]=NULL;

    else if (link->prev!=NULL && link->next==NULL)
      link->prev->next = NULL;

    else if (link->prev==NULL && link->next!=NULL)
    {
      Table[index]=link->next;
      link->next->prev = NULL;
    }

    else
      {
        link->prev->next = link->next;
        link->next->prev = link->prev;
      }

    free(link);

    return 1;
  }
  return 0;
}

/*----------------------------------------------------------------------------*/

/* Recebe a Hashtable dos jogos e a partir dai vai remover todos os jogos da base
de dados, inclusivamente da lista ligada */
void clear_j(Link*Table)
{
  int contador;
  Link link,next;

  for (contador=0 ; contador<HASH_J_SIZE ; contador++ )
  {
    link = Table[contador];
    while (link!=NULL)
    {
      free(link->linkj->jogo->nome);
      free(link->linkj->jogo);
      free(link->linkj);
      next = link->next;
      free(link);
      link = next;
    }
    Table[contador] = NULL;
  }
}
