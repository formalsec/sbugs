#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 1024
#include "hashtable.h"
#include "estruturas.h"

/*Esta funcao determina a posicao de um elemento na hash*/
int hash(char* nome_jogo,int* M)
{
  int h, a=31415, b=27183;
  for(h=0;*nome_jogo!='\0';nome_jogo++ , a = a*b %((*M)-1))
  {
    h = (a*h + *nome_jogo)%(*M);
  }
  if (h < 0)
  {
    h = h * (-1);
  }
  return h;
}

/*Esta funcao inicializa a hashtable dos jogos a NULL*/
void Stinit (int* M, pjogo* st)
{
  int i;
  for (i=0;i<(*M);i++)
  {
    st[i]=NULL;
  }
}

/*Esta funcao insere um jogo dado na hashtable e depois na lista dos jogos*/
void Stinsert(char* nome_jogo,char* equipa1, char* equipa2, int score1, int score2,int* M,pjogo *st,link* head)
{
  int i =hash(nome_jogo,M);
  while (st[i]!=NULL)
  {
    i=(i+1)%(*M);
  }
  st[i]=(pjogo)malloc(sizeof(struct jogo));
  st[i]->score1 = score1;
  st[i]->score2 =score2;
  st[i]->nome_jogo =(char*)malloc(sizeof(char)*(strlen(nome_jogo)+1));
  strcpy(st[i]->nome_jogo,nome_jogo);
  st[i]->equipa1 =(char*)malloc(sizeof(char)*(strlen(equipa1)+1));
  strcpy(st[i]->equipa1,equipa1);
  st[i]->equipa2 =(char*)malloc(sizeof(char)*(strlen(equipa2)+1));
  strcpy(st[i]->equipa2,equipa2);
  *head = insertEnd(head,st[i]);
}

void reinsere_el(pjogo el, pjogo* st,int* M,char* nome_jogo)
{
  int i =hash(nome_jogo,M);
  while (st[i]!=NULL)
  {
    i=(i+1)%(*M);
  }
  st[i] = el;
}

/*Esta funcao apaga um elemento da hashtable e da lista, e depois reinsere os restantes elementos*/
link STdelete(char* nome_jogo,int* M,pjogo *st,link* head)
{

  int i = hash(nome_jogo,M) , j;
  link t, prev;
  while (st[i] != NULL)
  {
    if (strcmp(st[i]->nome_jogo,nome_jogo)==0)
    {
      break;
    }
    else
    {
      i = (i+1) % (*M);
    }
  }
  for(t=(*head), prev=NULL; t!=NULL; prev=t, t=t->next)
  {
    if (strcmp(t->jogo->nome_jogo,nome_jogo) == 0)
    {
      if (t==(*head))
      {
        (*head) = t->next;
        free(t->jogo->nome_jogo);
        free(t->jogo->equipa1);
        free(t->jogo->equipa2);
        free(t->jogo);
        free(t);
        st[i] = NULL;
        break;
      }
      else
      {
        prev->next = t->next;
        t->next = NULL;
        free(t->jogo->nome_jogo);
        free(t->jogo->equipa1);
        free(t->jogo->equipa2);
        free(t->jogo);
        free(t);
        st[i] = NULL;
        break;
      }
    }
  }
  for (j=(i+1)%(*M);st[j] != NULL ; j =(j+1)%(*M))
  {
    reinsere_el(st[j],st,M,st[j]->nome_jogo);
    st[j] = NULL;
  }
  return (*head);
}


pjogo search(char* nome_jogo,int* M,pjogo* st)
{
  int i = hash(nome_jogo,M);
  while (st[i] != NULL)
  {
    if (strcmp(st[i]->nome_jogo,nome_jogo)==0)
    {
      return st[i];
    }
    else
    {
      i = (i+1) % (*M);
    }
  }
  return NULL;
}

/*Esta funcao inicializa a hashtable das equipas a NULL*/
void Htinit (int *L,pequipa* ht)
{
  int i;
  for (i=0;i<(*L);i++)
  {
    ht[i] = NULL;
  }
}

/*Esta funcao insere um elemento na hashtable e na lista das equipas*/
void Htinsert(char* equipa,int vitorias,int* L,pequipa *ht,link* head_2)
{

  int i =hash(equipa,L);
  while (ht[i]!=NULL)
  {
    i=(i+1)%(*L);
  }
  ht[i]=(pequipa)malloc(sizeof(struct equipas));
  ht[i]->vitorias = vitorias;
  ht[i]->equipa =(char*)malloc(sizeof(char)*(strlen(equipa)+1));
  strcpy(ht[i]->equipa,equipa);
  *head_2 = insertEnd_equipas(head_2,ht[i]);
}

pequipa search_equipa(char* equipa,int* L,pequipa* ht)
{
  int i = hash(equipa,L);
  while (ht[i] != NULL)
  {
    if (strcmp(ht[i]->equipa,equipa)==0)
    {
      return ht[i];
    }
    else
    {
      i = (i+1) % (*L);
    }
  }
  return NULL;
}
