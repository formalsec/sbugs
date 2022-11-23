#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "funcoes.h"


/* Recebe o nome de uma equipa e devolve a sua posicao na Hash Table ou -1 caso nao exista */
int procura_equipa(char *equipa_nome, PRINCIPAL p) {

   /* Faz o hashing */ 
   int i = hashCode(equipa_nome, p->cap_equipas);

   /* Itera sobre o vetor ate encontrar uma posicao vazia */
   while (p->hashEquipa[i] != NULL) {
      if (strcmp(p->hashEquipa[i]->nome, equipa_nome) == 0) {
         return i;
      }
         
      /* vai para a proxima celula */
      ++i;
      
      /* vai para o inicio do vetor caso chegue ao fim */
      i %= p->cap_equipas;
   }        
   
   return -1;        
}


/* Recebe o nome de uma equipa e adiciona uma vitoria caso exista */
void adiciona_vitoria(char *equipa_nome, PRINCIPAL p) {
   int i = procura_equipa(equipa_nome, p);
   if (i != -1) {
      p->hashEquipa[i]->vitorias++;
   }
}


/* Recebe o nome de uma equipa e remove uma vitoria caso exista */
void remove_vitoria(char *equipa_nome, PRINCIPAL p) {
   int i = procura_equipa(equipa_nome, p);
   if (i != -1) {
      p->hashEquipa[i]->vitorias--;
   }
}


/* Recebe uma string e nsere uma equipa com esse nome na Hash Table de equipas */
int insert_equipa(char* nome, PRINCIPAL p) {
   int i;
   
   /* Faz o hashing */
   if (p->tamanho_equipas >= p->cap_equipas * 0.7) {
      p->cap_equipas += VETOR_HASH_SZ;
      p->hashEquipa = (EQUIPA*) can_fail_realloc(p->hashEquipa, sizeof(EQUIPA)*(p->cap_equipas));
   }

   /* Faz o hashing */
   i = hashCode(nome, p->cap_equipas);

   /* itera ate encontrar uma posicao livre */
   while (p->hashEquipa[i] != NULL) {
      /* vai para a proxima celula */
      ++i;
      /* da a volta ao vetor caso chegue ao fim */
      i %= p->cap_equipas;
   }
   p->hashEquipa[i] = (EQUIPA) can_fail_malloc(sizeof(struct equipa));
   p->hashEquipa[i]->nome = strdup(nome); 
   p->hashEquipa[i]->vitorias = 0;
   p->lista_equipas[p->tamanho_equipas] = p->hashEquipa[i];
   p->tamanho_equipas++;
   return 0;
}


/* Recebe o nome de uma equipa e remove-a da Hash Table de equipas */
void delete_equipa(char *equipa_nome, PRINCIPAL p) {

   /* Faz o hashing */
   int i, j;
   i = procura_equipa(equipa_nome, p);
   if (i != -1)
      p->hashEquipa[i] = NULL; 
   /* procura a equipa */
   while (p->hashEquipa[i] != NULL) {
      if (strcmp(p->hashEquipa[i]->nome, equipa_nome) == 0) break;
      else i = (i+1) % p->cap_equipas;
   }

   /* Apaga o jogo */
   if (p->hashEquipa[i] == NULL) return;
   free(p->hashEquipa[i]->nome); free(p->hashEquipa[i]); p->hashEquipa[i] = NULL;

   /* Reinsere os elementos seguintes ate encontrr um NULL */
   for (j = (i+1) % p->cap_equipas; p->hashEquipa[j] != NULL; j = (j+1) % p->cap_equipas) {
      p->hashEquipa[j] = NULL;
      insert_equipa(p->hashEquipa[j]->nome, p);
   }
}


/* Lista as equipas de forma mais grafica (usada para debug) */
void display_equipa(PRINCIPAL p) {
   int i = 0;
   
   for(i = 0; i<p->cap_equipas; i++) {
      if(p->hashEquipa[i] != NULL) {
         printf("(%s, %d)\n",p->hashEquipa[i]->nome, p->hashEquipa[i]->vitorias);
      }
      else
         printf("~~\n");
   }
   
   printf("\n");
}