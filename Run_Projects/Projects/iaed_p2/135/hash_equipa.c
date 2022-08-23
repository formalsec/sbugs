#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_equipa.h"

/* Funcao auxiliar de insercao da equipa na hash das equipas
 * Insere a estrutura equipa na lista
 */
link_equipa insereLista_equipa(link_equipa head, pEquipa e){
    link_equipa old_head=head;

    head = malloc(sizeof(node_equipa));
    head->next = old_head;
    head->e = e;
    return head;
}

/* Funcao auxiliar de procura da equipa na hash  das equipas
 * Procura a equipa com o nome s na lista
*/
pEquipa procuraLista_equipa(link_equipa head, char *s){
    link_equipa temp = head;
    
    if(!head) return NULL;

    for(temp = head; temp; temp = temp->next){
        if(!strcmp(temp->e->nome,s)) return temp->e;
    }
    return NULL;
}

/* Cria uma hash de equipas nova vazia */
hashtable_equipa* cria_hash_equipa(int m){
    int i;
    hashtable_equipa* ht = (hashtable_equipa*) malloc(sizeof(hashtable_equipa));
    ht->M = m;
    ht->heads = (link_equipa*) malloc(ht->M*sizeof(link_equipa));

    for (i = 0; i < ht->M; i++){
        ht->heads[i] = NULL;
    }
    return ht;
}

/* Funcao de insercao da equipa na hash das equipas */
void insereHash_equipa(hashtable_equipa* ht, pEquipa e){
    int i = hash(e->nome, ht->M);
    ht->heads[i] = insereLista_equipa(ht->heads[i], e);
}

/* Funcao de procura da equipa na hash das equipas */
pEquipa procuraHash_equipa(hashtable_equipa* ht, char *v){
    int i = hash(v, ht->M);
    return procuraLista_equipa(ht->heads[i], v);
}

/* Liberta toda a memoria associada a um elemento da hash das equipas*/
void FREEnode_equipa(link_equipa t){
    free(t->e->nome);
    free(t->e);
    free(t);
}

/* Liberta toda a memoria associada a hash das equipas */
void FREEhash_equipa(hashtable_equipa* ht){
    int i;
    link_equipa x, head;

    for(i=0; i < ht -> M; i++){
     	head = ht->heads[i];
        while(head){
            x = head;
            head = head -> next;
        	FREEnode_equipa(x);
        }
    }
    free(ht->heads);
    free(ht);
}

/* Descobre o maior numero de ganhos da equipa e quantas equipas tem esse mesmo numero */
void maior_ganhos(hashtable_equipa* ht, int* maior_n_ganhos, int* n_equipas){
    int i;
    link_equipa head;

    for(i = 0; i < ht -> M; i++){
        head = ht->heads[i];
        while(head){
            if(head->e->n_ganhos > *maior_n_ganhos){
                *maior_n_ganhos = head->e->n_ganhos;
                *n_equipas = 1;
            }else if(head->e->n_ganhos == *maior_n_ganhos){
                (*n_equipas)++;
            }
            head = head -> next;
        }
    }
}

/* Funcao auxiliar (que e utilizada na ordenacao)que compara duas strings */
int compara_string(const void * px, const void * py){
    char **n1 = (char**)px;
    char **n2 = (char**)py;
    return strcmp(*n1, *n2);
}

/* Imprime o nome das equipas com maior numero de ganhos */
void nome_equipas_maior_ganhos(hashtable_equipa* ht, 
                            const int maior_n_ganhos, 
                            const int n_equipas, 
                            const int n_comando){
    int i, j = 0;
    char** equipas;
    link_equipa head;

    equipas = (char**) malloc(sizeof(char*)*n_equipas);

    for(i=0; i < ht -> M && j < n_equipas; i++){
        head = ht->heads[i];
        while(head && j < n_equipas){
            if(head->e->n_ganhos == maior_n_ganhos){
                equipas[j] = strdup(head->e->nome);
                j++;
            }
            head = head -> next;
        }
    }
    qsort(equipas, n_equipas, sizeof(char*), compara_string);
    printf("%d Melhores %d\n", n_comando, maior_n_ganhos);
    for(j = 0; j < n_equipas; j++){
        printf("%d * %s\n", n_comando, equipas[j]);
        free(equipas[j]);
    }
    free(equipas);
}

