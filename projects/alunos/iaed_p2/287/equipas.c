#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "equipas.h"

/* liberta espaco na memoria de uma equipa */
void apaga_Equipa(Equipa a){
    free(a->nome);
    free(a);
}


/* cria uma nova equipa */
Equipa nova_Equipa(char* nome){
    Equipa new = (Equipa)can_fail_malloc(sizeof(struct equipa));
    new->vitorias = 0;
    new->nome = can_fail_malloc(strlen(nome)+1);
    strcpy(new->nome, nome);
    return new;
}

/* funcao aux do qsort compara duas equipas pelo nome */
int compara_equipas(const void * a, const void * b){

  char** equipaA = (char** )a;
  char** equipaB = (char** )b;

  return strcmp( *equipaA,*equipaB );
}


/* gera um numero ligado com o o nome do input entre 0
    e o tamamho */
int hashU(char *v,int tamanho){
    int h, a = 31415, b = 27183;

    for(h = 0; *v != '\0';v++, a = a*b % (tamanho-1))
        h = (a*h + *v) % tamanho;
    
    return h;
}

/*  utiliza a abtracao Key */
int hash(Key nome, int tamanho){
    int h = hashU(nome,tamanho);
    return h;
}

/* inica a Hashtable das equipas */
link_equi* inicia_tab_equi(int tamanho){
    int i;
    link_equi *equipas;
    equipas = can_fail_malloc(tamanho*sizeof(link_equi));
    
    for(i = 0; i < tamanho; i++)
        equipas[i] = NULL;
    return equipas;
}

/* insere uma equipa na Hashtable das equipas */
void insere_tab_equi(Equipa equipa,link_equi *equipas,int tamanho) {
    int i = hash(key(equipa),tamanho);
    equipas[i] = insere_cadeia_equi(equipas[i], equipa);
}

/* procura uma equipa na hashtable das equipas */
Equipa procura_tab_equi(Key v,link_equi *equipas, int tamanho) {
    int i = hash(v,tamanho);
    return procura_cadeia_equi(equipas[i], v);
}

/* insere na cadeia da hashtable(externalchaining), tratando assim das colisoes */
link_equi insere_cadeia_equi(link_equi equi_slot,Equipa equipa){
    link_equi new = NULL;
    new = (link_equi)can_fail_malloc(sizeof(struct node));
    new->next = equi_slot;
    new->equipa = equipa;
    return new;
}


/* procura na cadeia da hashtable(externalchaining) */
Equipa procura_cadeia_equi(link_equi equi_slot,Key v){
    while(equi_slot != NULL){
        if(strcmp(v,key(equi_slot->equipa)) ==0 )
            return equi_slot->equipa;
        equi_slot = equi_slot->next;
    }
    return NULL;
}

/* apaga a hashtable das equipas */
void apaga_tab_equi(link_equi*equipas){
    int i;
    link_equi temp1,temp2;
    Equipa equi_temp;
    for(i=0; i<TAM_HASHTABLE_EQUI; i++){
        if(equipas[i] != NULL){
            temp1 = equipas[i];
            while(temp1 != NULL){
                equi_temp = temp1->equipa;
                temp2 = temp1;
                temp1 = temp1->next;
                apaga_Equipa(equi_temp);
                free(temp2);
            }
        }
    }
    free(equipas);
}









