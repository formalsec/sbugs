#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comandos_estruturas.h"

int main()
{
   jogos *htjogos[10073]; /* hash table dos jogos  */
   equipas *ht[10073]; /* hash table das equipas */
   int num=1; /* NL */
   jogos *head=NULL; /* crio uma lista para colocar os jogos */
   equipas *head_e=NULL; /* crio uma lista para colocar as equipas */
   char caracter=getchar();
   while(caracter!='x') /* enquanto o programa nao acabar */
   {
      switch(caracter)
      {
         case 'a': head=comando_a(htjogos, ht, num, head, head_e); num++; break;
         case 'A': head_e=comando_A(ht, num, head_e); num++; break;
         case 'l': comando_l(num, head); num++; break;
         case 'p': comando_p(htjogos, num); num++; break;
         case 'P': comando_P(ht, num); num++; break;
         case 'r': head=comando_r(htjogos, ht, num, head, head_e); num++; break;
         case 's': comando_s(htjogos, ht, num, head, head_e); num++; break;
         case 'g': comando_g(num, head_e); num++; break;
      }
      caracter=getchar();
   }
   dar_free_equipas(head_e); /* free da lista que contem equipas */
   dar_free_jogos(head); /* free da lista que contem jogos */
   procura_free(htjogos, ht); /* free da hash table */
   return 0;
}

/******************************************************************************/
/* -------------------------------- COMANDO a ------------------------------- */
/*                            Adiciona um novo jogo                           */
jogos *comando_a(jogos **htjogos, equipas **ht, int num, jogos *head, equipas *head_e)
{
   char nome[MAX_NOME], equipa1[MAX_NOME], equipa2[MAX_NOME];
   int score1, score2, i1, i2, final;
   jogos *jogo;
   scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);
   /* cria um no de um jogo */
   jogo = novo_jogo(nome, equipa1, equipa2, score1, score2);
   i1 = HTprocura(ht, equipa1);
   i2 = HTprocura(ht, equipa2);
   final = HTprocurajogo(htjogos, nome);
   if (final==0) /* Se o jogo existir */
   {  /* Se as equipas existirem */
      if(i1==1 && i2==1)
      {
         /* insere jogo na hash table */
         HTinserejogo(htjogos, jogo);
         /* insere jogo na lista de jogos */
         head=insere_fim_jogos(head, jogo);
         if (score1>score2)
         {
            /* adiciona 1 vitoria a equipa1 na hash table */
            HT_soma_vitoria(ht, equipa1);
            /* adiciona 1 vitoria a equipa1 na lista de equipas */
            soma_vitoria(head_e, equipa1);
            return head;
         }
         else if (score2>score1)
         {
            /* adiciona 1 vitoria a equipa2 na hash table */
            HT_soma_vitoria(ht, equipa2);
            /* adiciona 1 vitoria a equipa2 na lista de equipas */
            soma_vitoria(head_e, equipa2);
            return head;
         }
         else /* caso haja um empate */
         {
            return head;
         }
      }
      else
      {
         printf("%d Equipa inexistente.\n", num);
         free(jogo->nome);
         free(jogo->equipa1);
         free(jogo->equipa2);
         free(jogo);
      }
   }
   else
   {
      printf("%d Jogo existente.\n", num);
      free(jogo->nome);
      free(jogo->equipa1);
      free(jogo->equipa2);
      free(jogo);
   }
   return head;
}

/******************************************************************************/
/* -------------------------------- COMANDO A ------------------------------- */
/*                          Adiciona uma nova equipa                          */
equipas *comando_A(equipas **ht, int num, equipas *head_e)
{
   char nome[MAX_NOME];
   int i;
   equipas *eq;
   scanf(" %[^:\n]", nome);
   eq = nova_equipa(nome); /* cria um no de uma equipa */
   /* verifica se a equipa existe na hash table */
   i=HTprocura(ht, nome);
   if (i==1) /* se esta equipa ja existir na hash table retorna 1 */
   {
      printf("%d Equipa existente.\n", num);
      free(eq->nome_equipa);
      free(eq);
      return head_e;
   }
   else
   {  /* se i!=1 inserimos o no na hashtable e na lista de equipas */
      HTinsere_equipa(ht, eq);
      head_e=insere_fim_equipas(head_e, eq);
      return head_e;
   }
}

/******************************************************************************/
/* -------------------------------- COMANDO l ------------------------------- */
/*        Lista os jogos pela ordem que foram introduzidos no sistema         */
void comando_l(int num, jogos *head)
{
   jogos *t;
   for(t = head; t != NULL; t = t->next)
   { /* vai imprimir cada elemento da lista de equipas */
      printf("%d %s %s %s %d %d\n", num, t->nome, t->equipa1, t->equipa2, t->score1, t->score2);
   }
}

/******************************************************************************/
/* -------------------------------- COMANDO p ------------------------------- */
/*                        Procura um jogo na hash table                       */
void comando_p(jogos **htjogos, int num)
{
   char nome[MAX_NOME];
   scanf(" %[^:\n]", nome);
   HTprocura_p(htjogos, nome, num);
}

/******************************************************************************/
/* -------------------------------- COMANDO P ------------------------------- */
/*                              Procura uma equipa                            */
void comando_P(equipas **ht, int num)
{
   char nome[MAX_NOME];
   scanf(" %[^:\n]",nome);
   procura_equipa_P(ht, nome, num);
}

/******************************************************************************/
/* -------------------------------- COMANDO r ------------------------------- */
/*                               Elimina um jogo                              */
jogos *comando_r(jogos **htjogos, equipas **ht, int num, jogos *head, equipas *head_e)
{
   char nome[MAX_NOME];
   scanf(" %[^:\n]", nome);
   HT_elimina_jogo(htjogos, ht, nome, num);
   head=elimina_jogo_lista(head, nome, head_e);
   return head;
}

/******************************************************************************/
/* -------------------------------- COMANDO s ------------------------------- */
/*                           Altera o score de um jogo                        */
void comando_s(jogos **htjogos, equipas **ht, int num, jogos *head, equipas *head_e)
{
   int score1, score2;
   char nome[MAX_NOME];
   scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);
   HT_altera_score(htjogos, ht, nome, score1, score2, num, head, head_e);
}

/******************************************************************************/
/* -------------------------------- COMANDO g ------------------------------- */
/*        Lista os jogos pela ordem que foram introduzidos no sistema         */
void comando_g(int num, equipas *head_e)
{
   int num_equipas, max_vitorias, i;
   char **nome;
   char **aux;
   int *v= malloc(sizeof(int)*2);
   v=maior_numero_vitorias(head_e, v);
   num_equipas = v[0];
   max_vitorias = v[1];
   free(v);
   aux=malloc(sizeof(char*)*(num_equipas));
   if (num_equipas==0) /* caso nao haja equipas */
   {
      free(aux);
      return;
   }
   nome = maior_equipas(head_e, num_equipas, max_vitorias);
   mergesort(nome, aux, 0, num_equipas-1); /* ordeno pelo nome das equipas */
   free(aux);
   printf("%d Melhores %d\n", num, max_vitorias);
   for (i=0; i<num_equipas; i++)
   {  /* imprimo por ordem cada uma dessas equipas */
      printf("%d * %s\n", num, nome[i]);
   }
   free(nome);
}