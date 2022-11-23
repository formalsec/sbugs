#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funcoes.h"


char *strdup(const char *src) {
    char *dst = can_fail_malloc(strlen (src) + 1);  /* Espaco para o comprimento mais NULL */
    if (dst == NULL) return NULL;          /* Sem memoria disponivel */
      strcpy(dst, src);                    /* Copia os carateres */
    return dst;                            /* Retorna a nova string */
}


/* Recebe uma string e e faz o hashing somando todos os valores ascii de cada letra */
int hashCode(char *str, int tamanho) {
   int i, l, len=strlen(str), valor=0;
   for (i = 0; i < len; i++) {
      l = str[i];
      valor += l;
   }
   return valor % tamanho;
}


/* Recebe o nome de um jogo e devolve a sua posicao na Hash Table ou -1 caso nao exista */
int procura_jogo(char *jogo_nome, PRINCIPAL p) {
   /* Faz o hashing */ 
   int hashIndex = hashCode(jogo_nome, p->cap_jogos);
   
   /* Itera sobre o vetor ate encontrar uma posicao vazia */ 
   while (p->hashJogo[hashIndex] != NULL) {
      if (strcmp(p->hashJogo[hashIndex]->nome, jogo_nome) == 0) {
         return hashIndex;
      }
         
      /* vai para a proxima celula */
      ++hashIndex;
      
      /* vai para o inicio do vetor caso chegue ao fim */
      hashIndex %= p->cap_jogos;
   }        
   
   return -1;        
}


/* Insere um jogo na Hash Table dos jogos */
int insert_jogo(JOGO j, PRINCIPAL p) {
   int i;
   /* Faz o hashing */
   if (p->tamanho_jogos >= p->cap_jogos * 0.7) {
      p->cap_jogos += VETOR_HASH_SZ;
      p->hashJogo = (JOGO*) can_fail_realloc(p->hashJogo, sizeof(JOGO)*(p->cap_jogos));
   }
   /* Faz o hashing */
   i = hashCode(j->nome, p->cap_jogos);

   /* itera ate encontrar uma posicao livre */
   while (p->hashJogo[i] != NULL) {
      /* vai para a proxima celula */
      ++i;
      /* da a volta ao vetor caso chegue ao fim */
      i %= p->cap_jogos;
   }
   p->hashJogo[i] = (JOGO) can_fail_malloc(sizeof(struct jogo));
   p->hashJogo[i]->nome = strdup(j->nome);
   p->hashJogo[i]->equipa1 = strdup(j->equipa1);
   p->hashJogo[i]->equipa2 = strdup(j->equipa2);
   p->hashJogo[i]->score1 = j->score1;
   p->hashJogo[i]->score2 = j->score2;
   p->tamanho_jogos++;
   return 0;
}


/* Apaga um jogo da Hash Table dos jogos */
void delete_jogo(char *jogo_nome, PRINCIPAL p) {
   /* Faz o hashing */
   JOGO jogo;
   int i, j;
   i = hashCode(jogo_nome, p->cap_jogos);

   /* procura o jogo */
   while (p->hashJogo[i] != NULL) {
      if (strcmp(p->hashJogo[i]->nome, jogo_nome) == 0) break;
      else i = (i+1) % p->cap_jogos;
   }
   if (p->hashJogo[i] == NULL) return;
   
   /* Apaga o jogo */
   free(p->hashJogo[i]->nome); free(p->hashJogo[i]->equipa1); free(p->hashJogo[i]->equipa2); free(p->hashJogo[i]); p->hashJogo[i] = NULL;
   
   /* Reinsere os elementos seguintes ate encontrr um NULL */
   for (j = (i+1) % p->cap_jogos; p->hashJogo[j] != NULL; j = (j+1) % p->cap_jogos) {
      jogo = copia_jogo(jogo, p->hashJogo[j]);
      free_jogo(p->hashJogo[j]);
      p->hashJogo[j] = NULL;
      insert_jogo(jogo, p);
      free_jogo(jogo);
      p->tamanho_jogos--;
   }
   p->tamanho_jogos--;
}


/* Lista os jogos de forma mais grafica (usada para debug) */
void display_jogo(PRINCIPAL p) {
   int i = 0;
   
   for(i = 0; i<p->cap_jogos; i++) {
   
      if(p->hashJogo[i] != NULL)
         printf("(%s, %s, %s, %d, %d)\n",p->hashJogo[i]->nome, p->hashJogo[i]->equipa1, p->hashJogo[i]->equipa2, p->hashJogo[i]->score1, p->hashJogo[i]->score2);
      else
         printf("~~\n");
   }
   
   printf("\n");
}

/* A copia as caracteristicas de um jogo para outro */
JOGO copia_jogo(JOGO jogo1, JOGO jogo2) {
    jogo1 = (JOGO) can_fail_malloc(sizeof(struct jogo));
    jogo1->nome = strdup(jogo2->nome);
    jogo1->equipa1 = strdup(jogo2->equipa1);
    jogo1->equipa2 = strdup(jogo2->equipa2);
    jogo1->score1 = jogo2->score1;
    jogo1->score2 = jogo2->score2;
    return jogo1;
}

/* Liberta a memoria de um jogo */
void free_jogo(JOGO jogo) {
   free(jogo->nome);
   free(jogo->equipa1);
   free(jogo->equipa2);
   free(jogo);
   jogo = NULL;
}