#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_jogo.h"
#include "lista_jogo.h"
#include "auxiliar.h"

/* Liberta toda a memoria associada a um elemento da hash dos jogos */
void FREEnode_jogo(link_jogo t){
    FREEel_lista(t->el);
    free(t);
}

/* Funcao auxiliar de insercao do jogo na hash dos jogos
 * Insere um elemento da lista duplamente ligada 
 * (que contem a estrutura jogo) na lista
 */
link_jogo insereLista_jogo(link_jogo head, el_lista_jogo* el){
    link_jogo old_head=head;
    
    head = can_fail_malloc(sizeof(node_jogo));
    head->next = old_head;
    head->el = el;
    return head;
}

/* Funcao auxiliar de procura da jogo na hash dos jogos 
 * Procura o elemento da lista duplamente ligada 
 * (que contem o jogo com o nome s) na lista
*/
el_lista_jogo* procuraLista_jogo(link_jogo head, char *s){
    link_jogo temp;

    if(!head) return NULL;

    for(temp = head; temp; temp = temp->next){
        if(!strcmp(temp->el->j->nome,s)) return temp->el;
    }
    return NULL;
}

/* Funcao auxiliar de remocao do jogo na hash dos jogos 
 * Remove o elemento da lista duplamente ligada
 * (que contem o jogo com o nome v) n lista
*/
link_jogo removeJogoLista(link_jogo head, char *v){
    link_jogo t, prev;

    if(!head) return NULL;

    for(t = head, prev = NULL; t; prev = t, t = t->next){
        if(!strcmp(t->el->j->nome, v)){
            if(t == head){
                head = t->next;
            }else{
                prev->next = t->next;
            }
            FREEnode_jogo(t);
            break;
        }
    }
    return head;
}

/* Cria uma hash de jogos nova vazia  */
hashtable_jogo* cria_hash_jogo(int m){
    int i;
    hashtable_jogo* ht = (hashtable_jogo*) can_fail_malloc(sizeof(hashtable_jogo));
    ht->M = m;
    ht->heads = (link_jogo*) can_fail_malloc(ht->M*sizeof(link_jogo));

    for (i = 0; i < ht->M; i++){
        ht->heads[i] = NULL;
    }
    return ht;
}

/* Funcao de insercao do jogo na hash dos jogos */
void insereHash_jogo(hashtable_jogo* ht, el_lista_jogo* el){
    int i = hash(el->j->nome, ht->M);
    ht->heads[i] = insereLista_jogo(ht->heads[i], el);
}

/* Funcao de procura do jogo na hash dos jogos */
el_lista_jogo* procuraHash_jogo(hashtable_jogo* ht, char *v) {
    int i = hash(v, ht->M);
    return procuraLista_jogo(ht->heads[i], v);
}

/* Funcao de remocao do jogo na hash dos jogos */
void apagaHash_jogo(hashtable_jogo* ht, char *v){
    int i = hash(v, ht->M);
    ht->heads[i] = removeJogoLista(ht->heads[i], v);
}

/* Liberta toda a memoria associada a hash dos jogos */
void FREEhash_jogo(hashtable_jogo* ht){
    int i;
    link_jogo head, x;

    for(i = 0; i < ht -> M; i++){
        head = ht->heads[i];
        while(head){
        	x = head;
            head = head->next;
        	FREEnode_jogo(x);
        }
    }
    free(ht->heads);
    free(ht);
}

