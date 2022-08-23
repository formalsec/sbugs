#include "hashtable.h"

/*funcao que determina uma hash par auma dada string*/
size_t hash(const char *s, size_t capacidade){
   int i, valor = 0, len = strlen(s);
   for(i = 0; i < len; i++){
      valor = valor * 29 + s[i];
   }
   return valor % capacidade;
}

/*funcao que cria uma hashtable para jogos*/
hash_table_jogo *mk_hash_table_jg(int capacidade){
   hash_table_jogo *rv = malloc(sizeof(hash_table_jogo));
   rv->capacidade = capacidade;
   rv->tb = calloc(rv->capacidade, sizeof(node_jogo*));
   rv->last = NULL;
   return rv;
}

/*funcao que cria uma hashtable para equipas*/
hash_table_equipa *mk_hash_table_eq(int capacidade){
   hash_table_equipa *rv = malloc(sizeof(hash_table_jogo));
   rv->capacidade = capacidade;
   rv->tb = calloc(rv->capacidade, sizeof(node_equipa*));
   return rv;
}

/*funcao que insere um dado jogo numa dada hashtable*/
void insere_jogo_hash(hash_table_jogo *table, node_jogo *jogo){
   size_t i = hash(jogo->nome, table->capacidade);
   if(jogo == NULL) return;
   table->tb[i] = insere_jogo_lista(table->tb[i], jogo);
}

/*funcao que insere uma dada equipa numa dada hashtable*/
void insere_eq_hash(hash_table_equipa *table, node_equipa *equipa){
   size_t i = hash(equipa->nome, table->capacidade);
   if(equipa == NULL) return;
   table->tb[i] = insere_equipa_lista(table->tb[i], equipa);
}

/*funcao que encontra um jogo correspondente a um dado nome numa hashtable
inserida*/
node_jogo *encontra_hash_jg(hash_table_jogo *table, char *nome){
   size_t i = hash(nome, table->capacidade);
   node_jogo *tmp;
   if(table->tb[i] != NULL){
      tmp = encontra_listnode_jg(table->tb[i], nome);
      if(tmp != NULL) return tmp;
   }
   return NULL;
}

/*funcao que encontra uma equipa correspondente a um dado nome numa hashtable
inserida*/
node_equipa *encontra_hash_eq(hash_table_equipa *table, char *nome){
   size_t i = hash(nome, table->capacidade);
   node_equipa *tmp;
   if(table->tb[i] != NULL){
      tmp = encontra_listnode_eq(table->tb[i], nome);
      if(tmp != NULL) return tmp;
   }
   return NULL;
}

/*funcao que remove um jogo de uma hastable correspondente a um nome inserido*/
void remove_jogo_hash(hash_table_jogo *table, char *nome){
   size_t i = hash(nome, table->capacidade);
   int cont = 0;
   node_jogo *tmp;
   if(table->tb[i] != NULL){ /*se esse nome ja foi inserido*/
      tmp = table->tb[i];
      while(tmp != NULL){ /*enquanto a linkedlist nao estiver no fim*/
         if(cont == 1){
            table->tb[i] = delete_node_list(table->tb[i], nome);
            return;
         }
         tmp = tmp->next;
         cont++;
      }
      tmp = encontra_listnode_jg(table->tb[i], nome);
      if(tmp != NULL){ /*se a node existir*/
         table->tb[i] = delete_node_list(table->tb[i], nome);
         table->tb[i] = NULL;
      }
   }
}

/*funcao que liberta memoria de uma hash_table de jogos*/
void free_hashtable_jg(hash_table_jogo *table){
   size_t i;
   for(i = 0; i < table->capacidade; i++){
      destroy_list_jg(table->tb[i]); /*liberta a linkedlist no indice i*/
   }
   free(table->tb);
   free(table);
}

/*funcao que liberta memoria de uma hash_table de equipas*/
void free_hashtable_eq(hash_table_equipa *table){
   size_t i;
   for(i = 0; i < table->capacidade; i++){
      destroy_list_eq(table->tb[i]); /*liberta a linkedlist no indice i*/
   }
   free(table->tb);
   free(table);
}

/*funcao que recebe uma node de uma equipa numa hashtable e outra numa linkedlist
e diminui as vitorias de ambas*/
void diminui_vitorias(node_equipa *hash_eq){
   hash_eq->vitorias--;
}

/*funcao que recebe uma node de uma equipa numa hashtable e outra numa linkedlist
e aumenta as vitorias de ambas*/
void aumenta_vitorias(node_equipa *hash_eq){
   hash_eq->vitorias++;
}
