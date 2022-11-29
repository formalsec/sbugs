#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipa.h"
#include "jogo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Recebe a HashTable das equipas, a HashTable dos jogos, a lista ligada
dos jogos e o numero da linha do input. Le do utilizador os dados de um
jogo e caso seja um jogo valido, adiciona a base de dados. Caso contrario
printa um erro*/
void a(LinkE * ETable,Link * JTable,Lista lista,int Linha_Input)
{
  char nome_max[1024],equipa0[1024],equipa1[1024],*nome;
  int score[2],validade,index;
  Jogo * novo_jogo;
  Equipa * e_vencedora;

  scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome_max,equipa0,equipa1,&score[0],&score[1]);

  nome = (char *)( can_fail_malloc ( (strlen(nome_max)+1) * sizeof(char)) );
  strcpy(nome,nome_max);

  novo_jogo = (Jogo*)( can_fail_malloc( sizeof(Jogo)) );
  novo_jogo-> nome = nome;

  novo_jogo->score[0] = score[0];
  novo_jogo->score[1] = score[1];

  validade = jogo_invalido(JTable,ETable,nome,equipa0,equipa1);

  if (validade ==0)
  {
    index = hashEquipa(equipa0,HASH_E_SIZE);
    novo_jogo->equipa0 = search_lista_e(ETable[index],equipa0);
    index = hashEquipa(equipa1,HASH_E_SIZE);
    novo_jogo->equipa1 = search_lista_e(ETable[index],equipa1);

    lista->head = add_j_to_main_list(lista->head,novo_jogo);
    add_linkj_hash(JTable,lista->head,novo_jogo->nome);

    if (lista->tail==NULL)
      lista->tail=lista->head;

    e_vencedora = vencedor(novo_jogo);

    if (e_vencedora!=NULL)
      e_vencedora->wins++;

  }
  else
  {
    if ( validade==1 )
      printf("%d Jogo existente.\n",Linha_Input);

    else if ( validade==2 )
      printf("%d Equipa inexistente.\n",Linha_Input);

    free(novo_jogo->nome);
    free(novo_jogo);
  }
}

/*----------------------------------------------------------------------------*/

/* Recebe a hashtable das equipas e a linha do input. Le do utilizador
os dados de uma equipa a adicionar. Com argumentos validos, adiciona a HashTable
das equipas, caso contrario, printa um erro*/
void A(LinkE * ETable,int Linha_Input)
{
  char nome_max[1024],*nome;
  Equipa * nova_equipa;
  scanf(" %[^:\n]",nome_max);

  nome = (char *)( can_fail_malloc ( (strlen(nome_max)+1) * sizeof(char)) );
  strcpy(nome,nome_max);

  nova_equipa = (Equipa*)( can_fail_malloc ( sizeof(Equipa) ) );

  nova_equipa->nome = nome;
  nova_equipa->wins = 0;

  if ( add_e_to_hash(ETable,nova_equipa)==0 )
  {
    printf("%d Equipa existente.\n",Linha_Input);
    free(nova_equipa->nome);
    free(nova_equipa);
  }
}

/*----------------------------------------------------------------------------*/

/* Recebe como argumento a hashtable dos jogos e a linha do input. Le do utilizador
os dados de um jogo e um novo resultado para esse jogo. Com argumentos validos
modifica a base de dados de acordo com o novo jogo, caso contrario printa um erro */
void s(Link * JTable, int Linha_Input)
{
  char nome[1024];
  int score[2];
  Link link;
  Equipa * equipa;

  scanf(" %[^:\n]:%d:%d",nome,&score[0],&score[1]);

  link = search_j_Table(JTable,nome);

  if (link==NULL)
    printf("%d Jogo inexistente.\n",Linha_Input);

  else
  {
    equipa = vencedor(link->linkj->jogo);

    if (equipa!=NULL)
      equipa->wins -= 1;

    link->linkj->jogo->score[0] = score[0];
    link->linkj->jogo->score[1] = score[1];

    equipa = vencedor(link->linkj->jogo);

    if (equipa!=NULL)
      equipa->wins++;
  }
}

/*----------------------------------------------------------------------------*/

/* Recebe a hashtable dos jogos, a lista ligada dos jogos e a linha do input.
Le do utilizador o nome de um jogo a apagar. Caso o jogo exista, apaga da base
de dados. Caso contrario printa erro */
void r(Link * JTable,Lista lista, int Linha_Input)
{
  char nome[1024];

  scanf(" %[^:\n]",nome);

  if ( destroy(JTable,&(lista->head),&(lista->tail),nome) == 0 )
    printf("%d Jogo inexistente.\n",Linha_Input);
}

/*----------------------------------------------------------------------------*/

/* Recebe a hashtable dos jogos e a linha do input. Le do utilizador um jogo a procurar
e printa os dados desse jogo. Caso nao exista, printa erro */
void p(Link * JTable, int Linha_Input)
{
  char nome[1024];
  Link link;

  scanf(" %[^:\n]",nome);

  link = search_j_Table(JTable,nome);

  if (link==NULL)
    printf("%d Jogo inexistente.\n",Linha_Input);

  else
    printf("%d %s %s %s %d %d\n",Linha_Input,link->linkj->jogo->nome,link->linkj->jogo->equipa0->nome,
  link->linkj->jogo->equipa1->nome,link->linkj->jogo->score[0],link->linkj->jogo->score[1]);
}

/*----------------------------------------------------------------------------*/

/* Recebe a hashtable das equipas e a linha do input. Le do utilizador uma equipa
a procurar e printa os dados dessa equipa. Caso nao exista, printa erro */
void P(LinkE * ETable , int Linha_Input)
{
  char nome[1024];
  Equipa * equipa;

  scanf(" %[^:\n]",nome);

  equipa = search_lista_e( ETable[hashEquipa(nome,HASH_E_SIZE)] , nome );

  if (equipa==NULL)
    printf("%d Equipa inexistente.\n",Linha_Input);

  else
    printf("%d %s %d\n",Linha_Input,equipa->nome,equipa->wins);
}

/*----------------------------------------------------------------------------*/

/* Recebe a lista ligada de todos os jogos e a linha do input, e printa todos os
jogos guardados na base de dados, por ordem de introducao */
void l(Lista lista,int Linha_Input)
{
  LinkJ linkj= lista->tail;

  while (linkj!=NULL)
  {
    printf("%d %s %s %s %d %d\n",Linha_Input,linkj->jogo->nome,linkj->jogo->equipa0->nome,
    linkj->jogo->equipa1->nome,linkj->jogo->score[0],linkj->jogo->score[1]);
    linkj = linkj->prev;
  }
}

/*----------------------------------------------------------------------------*/

/* Recebe a hashtable das equipas e a linha do input, e printa a equipa que tiver
mais jogos ganhos, ou equipas (por ordem alfabetica), caso haja empates */
void g(LinkE * ETable , int Linha_Input)
{
  int contador,max_wins=0,array_size=0,array_size2,existem_equipas=0;
  LinkE linke=NULL;
  pEquipa * equipas=NULL;

  /* Agora vou procurar o maximo de wins */
  for (contador=0 ; contador<HASH_E_SIZE ; contador++ )
  {
    linke = ETable[contador];
    while (linke!=NULL)
    {
      existem_equipas = 1;
      if (linke->equipa->wins > max_wins)
      {
        max_wins = linke->equipa->wins;
        array_size = 1;
      }

      else if (linke->equipa->wins == max_wins)
        array_size++;

      linke = linke->next;
    }
  }

  equipas = can_fail_malloc( array_size * sizeof(pEquipa) );

  array_size2=array_size;

  /* Agora vou procurar as equipas com essas wins */
  for (contador=0 ; contador<HASH_E_SIZE ; contador++ )
  {
    linke = ETable[contador];
    while (linke!=NULL)
    {
      if (linke->equipa->wins == max_wins)
      {
        equipas[array_size2-1]= linke->equipa;
        array_size2 -= 1;
      }

      if (array_size2 == (-1))
        contador=HASH_E_SIZE;

      linke = linke->next;
    }
  }

  if (existem_equipas==1)
  {
    qsort(equipas,array_size,sizeof(pEquipa),cmpstr);
    printf("%d Melhores %d\n",Linha_Input,max_wins);
    for (contador=0 ; contador<array_size ; contador++)
      printf("%d * %s\n",Linha_Input,equipas[contador]->nome);
  }
  free(equipas);
}

/*----------------------------------------------------------------------------*/

/* Recebe a hashtable dos jogos, a hashtable das equipas, e a lista ligada dos jogos
e procede a eliminar todos as equipas e jogos associados a essas 3 */
void x(Link * JTable,LinkE * ETable,Lista lista)
{
  clear_j(JTable);
  clear_e(ETable);
  free(lista);
}

/*----------------------------------------------------------------------------*/

int main()
{
  LinkE ETable[HASH_E_SIZE];
  Link JTable[HASH_J_SIZE];
  Lista lista;
  int Linha_Input=1;
  char comando='O';

  lista = can_fail_malloc(sizeof(struct lista));

  lista->head = NULL;
  lista->tail = NULL;

  ETable_init(ETable);
  JTable_init(JTable);

  while ( comando !='x' )
    {
      comando = getchar();
      switch(comando)
      {
        case 'a':
          a(ETable, JTable, lista, Linha_Input);Linha_Input++;break;

        case 'A':
          A(ETable,Linha_Input);Linha_Input++;break;

        case 's':
          s(JTable, Linha_Input);Linha_Input++;break;

        case 'r':
          r(JTable,lista,Linha_Input);Linha_Input++;break;

        case 'p':
          p(JTable, Linha_Input);Linha_Input++;break;

        case 'P':
          P(ETable,Linha_Input);Linha_Input++;break;

        case 'l':
          l(lista,Linha_Input);Linha_Input++;break;

        case 'g':
          g(ETable,Linha_Input);Linha_Input++;break;

        case 'x':
          x(JTable,ETable,lista);Linha_Input++;break;
      }
    }

  return 0;
}
