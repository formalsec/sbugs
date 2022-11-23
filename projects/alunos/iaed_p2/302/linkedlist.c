#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "linkedlist.h"

/*funcao para fazer print de uma linkedlist de equipas*/
void printlist_equipa(int cont, int vitorias, node_equipa *head) {
   node_equipa *tmp = head;
   while(tmp != NULL && tmp->vitorias == vitorias) {
      printf("%d * %s\n", cont, tmp->nome);
      tmp = tmp->next;
   }
}

/*funcao para fazer print de uma linkedlist de jogos*/
void printlist_jogo(node_jogo *head, int cont){
   node_jogo *tmp = head;
   while(tmp != NULL){
      printf("%d %s %s %s %d %d\n", cont, tmp->nome, tmp->t1, tmp->t2, tmp->s1, tmp->s2);
      tmp = tmp->next_list;
   }
}

/*funcao para criar uma node de jogo*/
node_jogo *cria_node_jg(char *nome, char *t1, char *t2, int s1, int s2){
   node_jogo *resultado = can_fail_malloc(sizeof(node_jogo));
   resultado->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
   strcpy(resultado->nome, nome);
   resultado->t1 = can_fail_malloc(sizeof(char) * (strlen(t1) + 1));
   strcpy(resultado->t1, t1);
   resultado->t2 = can_fail_malloc(sizeof(char) * (strlen(t2) + 1));
   strcpy(resultado->t2, t2);
   resultado->s1 = s1;
   resultado->s2 = s2;
   resultado->next = NULL;
   resultado->next_list = NULL;
   resultado->prev_list = NULL;
   return resultado;
}

/*funcao para criar uma node de equipa*/
node_equipa *cria_node_eq(char *nome){
   node_equipa *resultado = can_fail_malloc(sizeof(node_equipa));
   resultado->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
   strcpy(resultado->nome, nome);
   resultado->vitorias = 0;
   resultado->next = NULL;
   return resultado;
}

/*funcao para inserir um jogo no fim de uma linkedlist*/
node_jogo *insere_jogo_lista(node_jogo *head, node_jogo *jogo){
   node_jogo *tmp = head;
   if(tmp == NULL) return head = jogo;
   while(tmp->next != NULL){
      tmp = tmp->next;
   }
   tmp->next = jogo;
   return head;
}

/*funcao para inserir um jogo no fim de uma double linked list*/
node_jogo *_insere_jogo_lista(node_jogo *head, node_jogo *jogo, node_jogo **last){
   if(head == NULL){
      *last = jogo;
      return head = jogo;
   }
   (*last)->next_list = jogo;
   jogo->prev_list = (*last);
   *last = jogo;
   return head;
}

/*funcao para inserir uma equipa no fim de uma linkedlist*/
node_equipa *insere_equipa_lista(node_equipa *head, node_equipa *equipa){
   node_equipa *tmp = head;
   if(tmp == NULL) return head = equipa;
   while(tmp->next != NULL){
      tmp = tmp->next;
   }
   tmp->next = equipa;
   return head;
}

/*funcao para encontrar uma node de equipa numa dada linkedlist*/
node_equipa *encontra_listnode_eq(node_equipa *head, char *nome){
   node_equipa *tmp = head;
   while(tmp != NULL){
      if(strcmp(tmp->nome, nome) == 0) return tmp;
      tmp = tmp->next;
   }
   return NULL;
}

/*funcao para encontrar uma node de jogo numa dada linkedlist*/
node_jogo *encontra_listnode_jg(node_jogo *head, char *nome){
   node_jogo *tmp = head;
   while(tmp != NULL){
      if(strcmp(tmp->nome, nome) == 0) return tmp;
      tmp = tmp->next;
   }
   return NULL;
}

/*funcao para libertar uma unica node de equipa*/
void free_node_eq(node_equipa *node){
   free(node->nome);
   free(node);
}

/*funcao para libertar uma unica node de jogo*/
void free_node_jg(node_jogo *node){
   free(node->nome);
   free(node->t1);
   free(node->t2);
   free(node);
}

/*funcao para apagar uma node de uma lista e da memoria*/
node_jogo *delete_node_list(node_jogo *head, char *nome){
   node_jogo *tmp = head, *prev;
   if(tmp != NULL && (strcmp(tmp->nome, nome) == 0)){ /*se for a cabeca da lista*/
      head = tmp->next;
      free_node_jg(tmp);
      return head;
   }
   while(tmp != NULL && (strcmp(tmp->nome, nome) != 0)){ /*procura a node certa*/
      prev = tmp;
      tmp = tmp->next;
   }
   if(tmp == NULL) return head;
   prev->next = tmp->next;
   free_node_jg(tmp);
   return head;
}

/*funcao que remove uma node da lista sem apagar da memoria*/
node_jogo *remove_node_list(node_jogo *head, node_jogo *jogo, node_jogo **last){
   node_jogo *tmp = head;

   if(*last == jogo) /*se for o ultimo da lista*/
      (*last) = jogo->prev_list; /*muda o ultimo da lista para o anterior*/

   if(tmp == jogo){ /*se for a cabeca da lista*/
      head = tmp->next_list;
   }
   if(jogo->next_list != NULL){ /*se nao for o ultimo da lista*/
      jogo->next_list->prev_list = jogo->prev_list;
   }
   if(jogo->prev_list != NULL){ /*se nao for o primeiro*/
      jogo->prev_list->next_list = jogo->next_list;
   }
   return head;
}

/*funcao para libertar uma linkedlist inteira de equipas*/
void destroy_list_eq(node_equipa *head){
   node_equipa *tmp;
   while(head != NULL){
      tmp = head;
      head = head->next;
      free_node_eq(tmp);
   }
   free(head);
}

/*funcao para libertar uma linkedlist inteira de jogos*/
void destroy_list_jg(node_jogo *head){
   node_jogo *tmp;
   while(head != NULL){
      tmp = head;
      head = head->next;
      free_node_jg(tmp);
   }
   free(head);
}

/*funcao de comparacao entre duas strings para o qsort*/
int compara(const void *a, const void *b) {
   const char **ia = (const char **)a;
   const char **ib = (const char **)b;
   return strcmp(*ia, *ib);
}
