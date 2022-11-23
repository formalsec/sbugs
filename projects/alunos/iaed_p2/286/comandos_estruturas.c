#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comandos_estruturas.h"
/*
 * Ficheiro contem:
 * - Comandos Auxiliares a cada comando principal
 * - Outros: 
 *    1- HASH
 *    2- INSERE EM LISTAS
 *    3- OUTROS PROCESSOS ENVOLVENDO HASH TABLE E LISTAS
 *    4- FREES 
*/
/***************************************************************************************/
/*                                 COMANDOS AUXILIARES                                 */
/***************************************************************************************/

/*                                   Auxiliares de a                                   */
/* novo_jogo: cria um no de um jogo  */
jogos *novo_jogo(char *nome, char *equipa1, char *equipa2, int score1, int score2)
{
   jogos *x = can_fail_malloc(sizeof(jogos));
   x->nome = can_fail_malloc((strlen(nome)+1)*sizeof(char));
   strcpy(x->nome, nome);
   x->equipa1 = can_fail_malloc((strlen(equipa1)+1)*sizeof(char));
   strcpy(x->equipa1, equipa1);
   x->equipa2 = can_fail_malloc((strlen(equipa2)+1)*sizeof(char));
   strcpy(x->equipa2, equipa2);
   x->score1=score1;
   x->score2=score2;
   x->next = NULL;
   return x;
}

/* HTinserejogo: insere a lista de jogos num determinado indice da hash table */
void HTinserejogo(jogos **htjogos, jogos *jogo)
{
   int indice = hash(jogo->nome);
   htjogos[indice] = insere_inicio_jogo(htjogos[indice], jogo);
}
/* insere_inicio_jogo: insere um no de um jogo no inicio da lista */
jogos *insere_inicio_jogo(jogos *headj, jogos *jogo)
{
   jogo->next = headj;
   return jogo;
}

/*                                   Auxiliares de A                                   */
/* nova_equipa: cria um novo no para uma equipa */
equipas *nova_equipa(char *nome)
{
   equipas *x = can_fail_malloc(sizeof(equipas));
   x->nome_equipa = can_fail_malloc((strlen(nome)+1)*sizeof(char));
   strcpy(x->nome_equipa, nome);
   x->vitoria=0; /* inicializa as vitorias de um equipa a 0 */
   x->next = NULL;
   return x;
}

/* HTinsere_equipa: insere a lista de equipas num tal indice da hash table */
void HTinsere_equipa(equipas **ht, equipas *eq)
{
   int indice = hash(eq->nome_equipa);
   ht[indice] = insere_inicio(ht[indice], eq);
}

/* insere_inicio: insere um no no inicio de uma lista de equipas */
equipas *insere_inicio(equipas *head, equipas *eq)
{
   eq->next = head;
   return eq;
}

/*                                   Auxiliares de p                                   */
/* procura_jogo_p: procura jogo na hash table */
void HTprocura_p(jogos **htjogos, char *nome, int num)
{
   int indice = hash(nome);
   procura_jogo_p(htjogos[indice], nome, num);
}

/* procura_jogo_p: procura um jogo na lista que se encontra no tal indice da hash table */
int procura_jogo_p(jogos *headj, char *nome, int num)
{
   jogos *t = headj;
   while(t != NULL)
   {
      if(strcmp(t->nome, nome) == 0) 
      {
         printf("%d %s %s %s %d %d\n", num, nome, t->equipa1, t->equipa2, t->score1, t->score2);
         return 0;
      }
      t = t->next;
   }
   printf("%d Jogo inexistente.\n", num);
   return 0;
}

/*                                   Auxiliares de P                                   */
/* procura_equipa_P: procura uma equipa na hash table */
void procura_equipa_P(equipas **ht, char *nome, int num)
{
   int indice = hash(nome);
   lista_equipa_P(ht[indice], nome, num);

}

/* lista_equipa_P: procura uma equipa na lista que se encontra num determinado indice da 
   hash table */
void lista_equipa_P(equipas *head, char *nome, int num)
{
   equipas *t=head;
   while(t!=NULL)
   {
      if(strcmp(t->nome_equipa, nome) == 0)
      {
         printf("%d %s %d\n", num, nome, t->vitoria);
         return;
      }
      t=t->next;
   }
   printf("%d Equipa inexistente.\n", num);
}

/*                                   Auxiliares de r                                   */
/* HT_elimina_jogo: vai eliminar um jogo com um tal nome da hash table */
void HT_elimina_jogo(jogos **htjogos, equipas **ht, char *nome, int num)
{
   int indice = hash(nome);
   htjogos[indice]=elimina_jogo_r(ht, htjogos[indice], nome, num);
}

/* elimina_jogo_r: elimina um elemento de uma lista que se encontra numa 
   determinada posicao da hash table  */
jogos *elimina_jogo_r(equipas **ht, jogos *headj, char*nome, int num)
{
   jogos *t, *anterior;
   int i=0; /* variavel que serve para saber se aquele jogo existe ou nao em sistema */
   for(t = headj, anterior = NULL; t != NULL; anterior = t, t = t->next)
   {
      if(strcmp(t->nome, nome) == 0)
      {
         i=1; /* esse jogo existe no sistema, entao i passa a ser 1 */
         if(t == headj)
         {  /* se uma equipa ganhou o jogo entao e retirada na hash table uma 
               vitoria a essa equipa */
            if ((t->score1)>(t->score2))
            {  
               HT_tira_vitoria(ht, t->equipa1); 
            }
            else if ((t->score2)>(t->score1))
            {  
               HT_tira_vitoria(ht, t->equipa2);
            }
            headj = t->next;
         }
         else
         {  /* se uma equipa ganhou o jogo entao e retirada na hash table uma 
               vitoria a essa equipa */
            if ((t->score1)>(t->score2))
            {  
               HT_tira_vitoria(ht, t->equipa1);
            }
            else if ((t->score2)>(t->score1))
            {  
               HT_tira_vitoria(ht, t->equipa2);
            }
            anterior->next = t->next;
         }
         free(t->nome);
         free(t->equipa1);
         free(t->equipa2);
         free(t);
         break;
      }
   }
   verifica(i, num); /* verifica se i == 0 entao esse jogo nao existe em sistema */
   return headj;
}

/* verifica: verifica se i==0 entao o jogo nao existe em sistema */
void verifica(int i, int num)
{
   if (i==0){printf("%d Jogo inexistente.\n", num);}
}

/* elimina_jogo_lista: elimina um jogo com um dado nome da lista de equipas */
jogos *elimina_jogo_lista(jogos *head, char *nome, equipas *head_e)
{
   jogos *t, *anterior;
   for(t = head, anterior = NULL; t != NULL; anterior = t, t = t->next)
   {
      if(strcmp(t->nome,nome) == 0)
      {
         if(t == head)
         {  /* se uma equipa ganhou o jogo entao e retirada na lista de equipas uma 
               vitoria a essa equipa */
            if ((t->score1)>(t->score2)) 
            {  
               tirar_vitoria_lista(head_e, t->equipa1);
            }
            else if ((t->score2)>(t->score1))
            {  
               tirar_vitoria_lista(head_e,t->equipa2);
            }
            head = t->next;
         }
         else
         {  /* se uma equipa ganhou o jogo entao e retirada na lista de equipas uma 
               vitoria a essa equipa */
            if ((t->score1)>(t->score2))
            {
               tirar_vitoria_lista(head_e, t->equipa1);
            }
            else if ((t->score2)>(t->score1))
            {
               tirar_vitoria_lista(head_e,t->equipa2);
            }
            anterior->next = t->next;
         }
         free(t->nome);
         free(t->equipa1);
         free(t->equipa2);
         free(t);
         break;
      }
   }
   return head;
}

/*                                   Auxiliares de s                                   */
/*HT_altera_score: altera o score na hash table */
void HT_altera_score(jogos **htjogos, equipas **ht, char *nome, int score1, int score2, int num, jogos *head, equipas *head_e)
{
   int indice = hash(nome);
   altera_score_lista(ht, htjogos[indice], nome, score1, score2, num, head, head_e);
}

/* altera_score_lista: altera o score numa determinada lista da hash table e 
   na lista de equipas */
int altera_score_lista(equipas **ht, jogos *headj, char *nome, int score1, int score2, int num, jogos *head, equipas *head_e)
{
   jogos *t = headj;
   int i1, i2;
   while(t != NULL)
   {
      if(strcmp(t->nome, nome) == 0 ) /* encontro o jogo */
      {
         if(t->score1 > t->score2) /* ve quem ganhou o jogo anteriormente */
         {  /* tirar a vitoria a respetiva equipa na hashtable e na lista de equipas */
            HT_tira_vitoria(ht, t->equipa1); 
            tirar_vitoria_lista(head_e, t->equipa1); 
         }
         /* raciocinio semelhante as linhas anteriores, mas no caso em que a equipa2 
            ganha */
         if(t->score2 > t->score1)
         {  
            HT_tira_vitoria(ht, t->equipa2);
            tirar_vitoria_lista(head_e, t->equipa2);
         }
         t->score1=score1; /*alteramos o score */
         t->score2=score2;
         i1 = HTprocura(ht, t->equipa1);
         i2 = HTprocura(ht, t->equipa2);
         if (i1==1 && i2==1 && score1 > score2)
         {  /* se as equipas existirem(i1==1 e i2==1), adicionamos vitoria a equipa1 */
            HT_soma_vitoria(ht, t->equipa1); /* na hash table */
            soma_vitoria(head_e, t->equipa1); /* na lista de equipas */
         }
         else if (i1==1 && i2==1 && score2 > score1)
         {  /* se as equipas existirem, adicionamos vitoria a equipa2 */
            HT_soma_vitoria(ht, t->equipa2); /* na hash table */
            soma_vitoria(head_e, t->equipa2); /* na lista de equipas */
         }
         break;
      }
      t = t->next;
   }
   if (t==NULL) {printf("%d Jogo inexistente.\n", num);} /* caso o jogo nao exista */
   while(head!=NULL)
   {
      if (strcmp(head->nome, nome)==0) 
      {  /* Altera o score na lista de equipas */
         head->score1=score1;
         head->score2=score2;
         break;
      }
      head=head->next;
   }
   return 0;
}

/*                                   Auxiliares de g                                   */
/* maior_numero_vitorias: devolve o maior numero de vitorias */
int *maior_numero_vitorias(equipas *head_e, int *v)
{
   equipas *i;
   v[0]=0; /* numero de equipas com o numero de vitorias maximo */
   v[1]=0; /* numero de vitorias maximo */
   for(i=head_e; i!=NULL; i=i->next)
   {
      if(i->vitoria>v[1])
      {  
         v[0]=0; /* quando o max muda, o numero de equipas fica a 0 */
         v[1] = i->vitoria; /* atualiza o numero max de vitorias */
         v[0]=v[0]+1; /* incrementa o numero de equipas com max vitorias */
      }
      else if(i->vitoria==v[1])
      {  /* caso o valor max se mantenha vamos incrementando numero de 
            equipas com max vitorias */
         v[0]=v[0]+1; 
      }
   }
   return v;
}

/* maior_equipas: devolve um vetor com o nome das equipas que tem o 
   maximo de vitorias */
char **maior_equipas(equipas *head_e, int num_equipas, int max_vitorias)
{
   int cont=0;
   equipas *i=head_e;
   char **nome = can_fail_malloc(sizeof(char*)*num_equipas);
   while(i!=NULL)
   {
      if(i->vitoria==max_vitorias) 
      {  /* adiciono o nome da equipa num vetor */
         nome[cont] = i->nome_equipa;
         cont++;
      }
      i=i->next;
   }
   return nome;
}

/* mergesort e merge: servem para ordenar o nome das equipas por ordem lexicografica */
void mergesort(char **nome, char **aux, int left, int right)
{
  int m = (right+left)/2;
  if (right<=left)
   {
      return;
   }
  mergesort(nome, aux, left, m);
  mergesort(nome, aux, m+1, right);
  merge(nome, aux, left, m, right);
}

void merge(char **nome, char **aux, int left, int m, int right)
{
  int i, j, k;
  for(i=m+1; i>left; i--)
    aux[i-1] = nome[i-1];
  for (j=m; j<right; j++)
    aux[right+m-j] = nome[j+1];
  for(k= left; k<= right; k++)
  {
    if (strcmp(aux[j], aux[i])<0)
      nome[k] = aux[j--];
    else
      nome[k]=aux[i++];
  }
}

/*************************************************************************************************/
/*                                            OUTROS                                             */
/* ***********************************************************************************************/

/* 1 */
/* HASH */
/***************************************************************************************/
/* Funcao hash funcao que devolve o indice em que a equipa
   vai ficar (serve para jogos tambem) */
unsigned int hash (char *nome)
{
   unsigned int valor=0;
   int tamanho=strlen(nome);
   int i=0;
   while(i<tamanho)
   {
      valor = valor*tamanho;
      valor = valor + nome[i];
      i++;
   }
   return valor%1024; /* indice em que ficou guardado o nome */
}


/* 2 */
/* INSERE EM LISTAS */
/***************************************************************************************/
/*                       Inserem equipas/jogos na lista                       */
/* insere_fim_jogos: insere na lista de jogos um no de um jogo */
jogos *insere_fim_jogos(jogos *head, jogos *jogo)
{
   jogos *x;
   if(head == NULL)
      return novo_jogo(jogo->nome, jogo->equipa1, jogo->equipa2, jogo->score1, jogo->score2);
   for(x = head; x->next != NULL; x = x->next)
      ;
   x->next = novo_jogo(jogo->nome, jogo->equipa1, jogo->equipa2, jogo->score1, jogo->score2);
   return head;
}

/* insere_fim_equipas: insere numa lista de equipas um no de uma equipa */
equipas *insere_fim_equipas(equipas *head_e, equipas *equipa){
   equipas *x;
   if (head_e == NULL)
      return nova_equipa(equipa->nome_equipa);
   for(x = head_e; x->next != NULL; x = x->next){
      ;
   }
   x->next = nova_equipa(equipa->nome_equipa);
   return head_e;
}


/* 3 */
/* OUTROS PROCESSOS ENVOLVENDO HASH TABLE E LISTAS */
/****************************************************************************************/
/*               Procuram um jogo na hashtable e em listas(jogos/equipas)               */

/* HTprocura_jogo: verifica se o jogo existe na hash table */
int HTprocurajogo(jogos **htjogos, char *nome)
{
   int indice = hash(nome);
   int i=procura_jogo(htjogos[indice], nome);
   return i;
}

/* procura_jogo: verifica se o jogo existe na lista */
int procura_jogo(jogos *headj, char *nome)
{
   jogos *t = headj;
   while(t != NULL)
   {
      if(strcmp(t->nome, nome) == 0)
      {
         return 1;  /* se o jogo ja existir retorna 1 */
      }
      t = t->next;
   }
   return 0;
}

/* HTprocura: verifica se uma equipa com um tal nome existe na hash table */
int HTprocura(equipas **ht, char *nome)
{
   int indice = hash(nome);
   int i=procura_equipa(ht[indice], nome);
   /* se i==1 existe essa equipa na hash table */
   return i;
}

/* procura_equipa: verifica se uma equipa com um tal nome existe na lista */
int procura_equipa(equipas *head, char *nome)
{
   equipas *t = head;
   while(t != NULL)
   {
      if(strcmp(t->nome_equipa, nome) == 0)
      {
         return 1; /* se retornar 1, existe essa equipa na lista */
      }
      t = t->next;
   }
   return 0;
}

/******************************************************************************/
/*                 Tiram uma vitoria na lista e na hash table                 */

/* HT_tira_vitoria: tiram uma vitoria a uma equipa na hash table */
void HT_tira_vitoria(equipas **ht, char *nome)
{
   int indice=hash(nome);
   tirar_vitoria_lista(ht[indice], nome);
}

/* tirar_vitoria_lista: tiram uma vitoria a uma equipa na lista */
void tirar_vitoria_lista(equipas *head, char *equipa_vitoria)
{
   equipas *t = head;
   while(t != NULL)
   {
      if(strcmp(t->nome_equipa, equipa_vitoria)==0)
      {
         t->vitoria=t->vitoria-1;
         break;
      }
      t = t->next;
   }
}

/******************************************************************************/
/*                 Somam uma vitoria na lista e na hash table                 */

/* HT_soma_vitoria: adiciona uma vitoria a uma equipa na hash table */
void HT_soma_vitoria(equipas **ht, char *equipa_vitoria)
{
   int indice = hash(equipa_vitoria);
   soma_vitoria(ht[indice], equipa_vitoria);
}

/* soma_vitoria: adiciona uma vitoria a uma equipa na lista */
void soma_vitoria(equipas *head_e, char *equipa_vitoria)
{
   equipas *t = head_e;
   while(t != NULL)
   {
      if(strcmp(t->nome_equipa, equipa_vitoria)==0)
      {
         t->vitoria=t->vitoria+1;
      }
      t = t->next;
   }
}


/* 4 */
/* FREES */
/***************************************************************************************/
/* procura_free: percorre cada indice da hash table */
void procura_free(jogos **htjogos, equipas **ht)
{
   int i=0;
   while(i!=1025)
   {
      dar_free_equipas(ht[i]);
      dar_free_jogos(htjogos[i]);
      i++;
   }
}

/* dar_free_equipas: percorre toda a lista e liberta o espaco ocupado
   por cada elemento e pela lista em si, no caso de uma lista do tipo
   equipas *eq */
void dar_free_equipas(equipas *eq)
{
   equipas *t = eq;
   equipas *novo_t;
   while(t != NULL)
   {
      novo_t=t;
      free(novo_t->nome_equipa);
      t=novo_t->next;
      free(novo_t);
   }
}

/* dar_free_equipas: percorre toda a lista e liberta o espaco ocupado
   por cada elemento e pela lista em si, no caso de uma lista do tipo
   jogos *jogo */
void dar_free_jogos(jogos *jogo)
{
   jogos *t = jogo;
   jogos *novo_t;
   while(t != NULL)
   {
      novo_t=t;
      free(novo_t->nome);
      free(novo_t->equipa1);
      free(novo_t->equipa2);
      t=novo_t->next;
      free(novo_t);
   }
}