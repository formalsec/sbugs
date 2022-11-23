#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 1024
#include "hashtable.h"
#include "estruturas.h"


int cmp(const void* a, const void* b)
{
  char** a1, **a2;
  a1 = (char**) a;
  a2 = (char**) b;
  return  strcmp(*a1,*a2);
}


/*Esta funcao insere um jogo na hashtable e na lista,verificando tambem os possiveis erros*/
void cria_jogo(int* NL,int* M,pjogo* st,int* L,pequipa* ht,link* head)
{
  int score1,score2;
  char nome_jogo[MAX_CHAR],equipa1[MAX_CHAR],equipa2[MAX_CHAR];
  pjogo* ponteiro;
  pequipa* ponteiro_equipa1;
  pequipa* ponteiro_equipa2;
  scanf(" %[^:]:%[^:]:%[^:]:%d:%d",nome_jogo,equipa1,equipa2,&score1,&score2);
  ponteiro = can_fail_malloc(sizeof(pjogo));
  ponteiro_equipa1 = can_fail_malloc(sizeof(pequipa));
  ponteiro_equipa2 = can_fail_malloc(sizeof(pequipa));
  (*NL)++;
  *ponteiro = search(nome_jogo,M,st);
  *ponteiro_equipa1 = search_equipa(equipa1,L,ht);
  *ponteiro_equipa2 = search_equipa(equipa2,L,ht);
  if ((*ponteiro) != NULL)
  {
    printf("%d Jogo existente.\n", *NL);
  }
  else if ((*ponteiro_equipa1) == NULL)
  {
    printf("%d Equipa inexistente.\n",*NL);
  }
  else if ((*ponteiro_equipa2) == NULL)
  {
    printf("%d Equipa inexistente.\n",*NL);
  }
  else
  {
    Stinsert(nome_jogo,equipa1,equipa2,score1,score2,M,st,head);
    if (score1 > score2)
    {
      (*ponteiro_equipa1)->vitorias +=1;
    }
    else if (score1 < score2)
    {
      (*ponteiro_equipa2)->vitorias +=1;
    }
  }
  free(ponteiro);
  free(ponteiro_equipa1);
  free(ponteiro_equipa2);
}

/*Esta funcao percorre a lista e da print a informacao de cade jogo inserido,
  caso a lista esteja vazia nao da print a nada*/
void lista_jogos(int* NL,link* head)
{
  link t;
  (*NL)++;
  for(t=(*head); t != NULL ; t = t->next)
  {
    printf("%d %s %s %s %d %d\n",*NL,t->jogo->nome_jogo,t->jogo->equipa1,t->jogo->equipa2,t->jogo->score1,t->jogo->score2);
  }
}

/*Esta funcao procura um jogo na hashtable*/
void procura_jogo(int* NL,int* M,pjogo* st)
{
  char nome_jogo[MAX_CHAR];
  pjogo* ponteiro;
  ponteiro = can_fail_malloc(sizeof(pjogo));
  scanf(" %[^:\n]",nome_jogo);
  (*NL)++;
  *ponteiro = search(nome_jogo,M,st);
  if ((*ponteiro) == NULL)
  {
    printf("%d Jogo inexistente.\n", *NL);
  }
  else
  {
    printf("%d %s %s %s %d %d\n",*NL,(*ponteiro)->nome_jogo,(*ponteiro)->equipa1,(*ponteiro)->equipa2,(*ponteiro)->score1,(*ponteiro)->score2);
  }
  free(ponteiro);
}

/*Esta funcao apaga um jogo da lista e da hashtable, e retirando
  assim a vitoria a equipa vencedora*/
void apaga_jogo(int* NL,int* M,pjogo* st, int* L,pequipa* ht,link* head)
{
  char nome_jogo[MAX_CHAR];
  pjogo* ponteiro;
  pequipa* ponteiro_equipa1;
  pequipa* ponteiro_equipa2;
  ponteiro_equipa1 = can_fail_malloc(sizeof(pequipa));
  ponteiro_equipa2 = can_fail_malloc(sizeof(pequipa));
  ponteiro = can_fail_malloc(sizeof(pjogo));
  scanf(" %[^:\n]",nome_jogo);
  (*NL)++;
  (*ponteiro) = search(nome_jogo,M,st);
  if ((*ponteiro) == NULL)
  {
    printf("%d Jogo inexistente.\n",*NL);
  }
  else if((*ponteiro)->score1 > (*ponteiro)->score2)
  {
    *ponteiro_equipa1 = search_equipa((*ponteiro)->equipa1,L,ht);
    (*ponteiro_equipa1)->vitorias -=1;
    STdelete(nome_jogo,M,st,head);
  }
  else if((*ponteiro)->score1 < (*ponteiro)->score2)
  {
    *ponteiro_equipa2 = search_equipa((*ponteiro)->equipa2,L,ht);
    (*ponteiro_equipa2)->vitorias -=1;
    STdelete(nome_jogo,M,st,head);
  }
  else
  {
    STdelete(nome_jogo,M,st,head);
  }
  free(ponteiro);
  free(ponteiro_equipa1);
  free(ponteiro_equipa2);
}

/*Esta funcao altera o resultado de um jogo.
  Primeiro verifica quem ganhou o primeiro jogo retirado lhe a vitoria,
  depois verifica no novo resutado inserido quem ganhou e adiciona a vitoria*/
void altera_resultado(int* NL,int* M,pjogo* st,int* L,pequipa* ht)
{
  int score1,score2;
  char nome_jogo[MAX_CHAR];
  pjogo* ponteiro;
  pequipa* ponteiro_equipa1;
  pequipa* ponteiro_equipa2;
  ponteiro = can_fail_malloc(sizeof(pjogo));
  ponteiro_equipa1 = can_fail_malloc(sizeof(pequipa));
  ponteiro_equipa2 = can_fail_malloc(sizeof(pequipa));
  scanf(" %[^:]:%d:%d",nome_jogo,&score1,&score2);
  (*NL)++;
  *ponteiro = search(nome_jogo,M,st);
  if ((*ponteiro) == NULL)
  {
    printf("%d Jogo inexistente.\n",*NL);
  }
  else
  {
    if((*ponteiro)->score1 > (*ponteiro)->score2)
    {
      *ponteiro_equipa1 = search_equipa((*ponteiro)->equipa1,L,ht);
      (*ponteiro_equipa1)->vitorias -=1;
    }
    else if((*ponteiro)->score1 < (*ponteiro)->score2)
    {
      *ponteiro_equipa2 = search_equipa((*ponteiro)->equipa2,L,ht);
      (*ponteiro_equipa2)->vitorias -=1;
    }
    (*ponteiro)->score1 = score1;
    (*ponteiro)->score2 = score2;
    if (score1 > score2)
    {
      *ponteiro_equipa1 = search_equipa((*ponteiro)->equipa1,L,ht);
      (*ponteiro_equipa1)->vitorias +=1;

    }
    else if (score1 < score2)
    {
      *ponteiro_equipa2 = search_equipa((*ponteiro)->equipa2,L,ht);
      (*ponteiro_equipa2)->vitorias +=1;
    }
  }
  free(ponteiro);
  free(ponteiro_equipa1);
  free(ponteiro_equipa2);
}

/*Esta funcao insere a equipa introduzida pelo utilizador na hashtable e na lista*/
void adiciona_equipa(int* NL, int* L, pequipa* ht, link* head_2)
{
  char equipa[MAX_CHAR];
  pequipa* ponteiro_equipa;
  ponteiro_equipa = (pequipa*)can_fail_malloc(sizeof(pequipa));
  scanf(" %[^:\n]",equipa);
  (*NL)++;
  (*ponteiro_equipa) = search_equipa(equipa,L,ht);
  if ((*ponteiro_equipa) == NULL)
  {
    Htinsert(equipa,0,L,ht,head_2);
  }
  else
  {
    printf("%d Equipa existente.\n", *NL);
  }
  free(ponteiro_equipa);
}

/*Esta funcao procura uma equipa na hashtable*/
void procura_equipa(int* NL, int* L, pequipa* ht)
{
  char equipa[MAX_CHAR];
  pequipa* ponteiro_equipa;
  ponteiro_equipa = can_fail_malloc(sizeof(pequipa));
  scanf(" %[^:\n]",equipa);
  (*NL)++;
  (*ponteiro_equipa) = search_equipa(equipa,L,ht);
  if ((*ponteiro_equipa) == NULL)
  {
    printf("%d Equipa inexistente.\n",*NL);
  }
  else
  {
    printf("%d %s %d\n",*NL,(*ponteiro_equipa)->equipa,(*ponteiro_equipa)->vitorias );
  }
  free(ponteiro_equipa);
}

/*Esta funcao percore lista e da print, por ordem lexicografica,
  as equipas com um maior numero de vitorias.
  Para isso a funcao percorre a lista para determinar o maior numero de vitorias existente
  e o numero de equipas que o tem,
  depois a lista e outra vez percorrida e adiciona as equipas com maior numero de vitorias
  a um vetor, esse vetor e ordenado e depois printado*/
void lista_equipa(int* NL,link* head_2)
{
  link t;
  int i,contador = 0,maximo = 0;
  char** guarda;
  pequipa* ponteiro_equipa;
  ponteiro_equipa = can_fail_malloc(sizeof(pequipa));
  (*NL)++;
  for(t=(*head_2); t != NULL ; t = t->next)
  {
    if (t->equipa->vitorias > maximo)
    {
      maximo = t->equipa->vitorias;
      contador = 1;
    }
    else if (t->equipa->vitorias == maximo)
    {
      contador++;
    }
  }
  guarda = (char**)can_fail_malloc(sizeof(char*)*(contador));
  for(t=(*head_2); t != NULL ; t = t->next)
  {
    if (t->equipa->vitorias == maximo)
    {
      *guarda = t->equipa->equipa;
      guarda++;
    }
  }
  if (contador != 0)
  {
    for(i=0; i<contador; i++)
    {
      guarda--;
    }
    qsort(guarda,contador,sizeof(char*),cmp);
    printf("%d Melhores %d\n",(*NL),maximo);
    for(i=0; i<contador; i++)
    {
      printf("%d * %s\n",(*NL),(*guarda));
      guarda++;
    }
  }
  for(i=0; i<contador; i++)
  {
    guarda--;
  }
  free(guarda);
  free(ponteiro_equipa);
}


int main()
{
  pjogo * st;
  pequipa* ht;
  link* head;
  link *head_2;
  int L = 49000, M=49000 , NL = 0;
  char letra;
  head = can_fail_malloc(sizeof(link));
  *head = NULL;
  head_2 = (link*)can_fail_malloc(sizeof(link));
  *head_2 = NULL;
  st = can_fail_malloc((M)*sizeof(struct jogo));
  Stinit(&M,st);/*Inicializa a hashtable dos jogos*/
  ht = can_fail_malloc((L)*sizeof(struct equipas));
  Htinit(&L,ht);/*Inicializa a hashtable das equipas*/
  /*Este ciclo while recebe os comandos inseridos pelo utilizador*/
  while ((letra=getchar()) != 'x')
  {
    switch(letra)
    {
      case 'a':
        cria_jogo(&NL,&M,st,&L,ht,head);
        break;
      case 'l':
        lista_jogos(&NL,head);
        break;
      case 'p':
        procura_jogo(&NL,&M,st);
        break;
      case 'r':
        apaga_jogo(&NL,&M,st,&L,ht,head);
        break;
      case 's':
        altera_resultado(&NL,&M,st,&L,ht);
        break;
      case 'A':
        adiciona_equipa(&NL,&L,ht,head_2);
        break;
      case 'P':
        procura_equipa(&NL,&L,ht);
        break;
      case 'g':
        lista_equipa(&NL,head_2);
        break;
      }
    }
    da_free_st(head);
    da_free_ht(head_2);
    free(head);
    free(head_2);
    free(st);
    free(ht);
    return 0;
}
