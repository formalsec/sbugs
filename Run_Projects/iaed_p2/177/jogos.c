#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"


/*lista onde guardo os jogos pela ordem de insercao*/

/*Inicializa a lista onde vou guardar os jogos.*/
lista *inicializa_lista() {
	lista* tmp = (lista*) malloc(sizeof(lista));
	tmp->head = NULL;
	tmp->last = NULL;
	return tmp;
}

/*Faz print dos jogos desde a head (inicio) ate ao last (ultimo elemento da lista).*/
void print(lista *l, int nl){
    pPerson x=l->head;
    for (; x!=NULL; x=x->next){
        /*caso o jogo ainda nao tenha sido eliminado*/
        if (x->eliminado==0){
            printf("%d %s %s %s %d %d\n",nl,  x->nome, x->equipa1, x->equipa2, x->score1, x->score2);
        }
    }
    return ;
}

/*hash table onde guardo os jogos*/

/*Funcao esta nos slides*/
int hash(char *v, int M)
{
    int h = 0, a = 127;
    for (; *v != '\0'; v++){
        h = (a*h + *v) % M;
    }
    return h;
}

/*Inicializa a hash table de procura linear onde vou inserir os jogos.*/
jogo inicializa_jogo(jogo st1, int m) {
    int i; 
    st1 = (jogo)malloc(m*sizeof(struct perso));
    st1->tamanho=m;
    st1->elementos=0;
    st1->v = (pPerson*)malloc(m*sizeof(pPerson));
    /*inicializo tudo a NULL*/
    for (i = 0; i < m; i++){
        st1->v[i] = NULL; 
    }
    return st1;
}

/*Liberta toda a memoria ocupada pela hash table.*/
jogo destroi_jogo(jogo st){
    int i;
    /*percorre toda a hash table*/
    for (i=0; i<st->tamanho; i++){
        if (st->v[i]!=NULL){
            free(st->v[i]->nome);
            free(st->v[i]->equipa1);
            free(st->v[i]->equipa2);
            free(st->v[i]);
        }
    }
    free(st->v);
    free(st);
    return st;
}

/*Funcao auxiliar da funcao re_hash_jogo.*/
jogo insere(jogo st, pPerson v, char *nome){
    int i;
    i=hash(nome, st->tamanho);
    while (st->v[i]!=NULL){
        i = (i+1) % st->tamanho;
    }
    st->v[i] = v;
    return st;
}

/*Fucao auxiliar da funcao insere_jogo. Insere todos os elementos
da hash antiga numa nova mas com o dobro do tamanho.*/
jogo re_hash_jogo(jogo st){
    jogo st1=NULL;
    int i;
    /*a nova hash table e inicializada com o dobro do tamanho*/
    st1=inicializa_jogo(st1, st->tamanho*2);
    st1->elementos=st->elementos;
    /*os elemenotos da hash antiga sao inseridos na nova*/
    for (i=0; i<st->tamanho; i++){
        if (st->v[i]!=NULL){
            st1=insere(st1, st->v[i], st->v[i]->nome);
        }
    }
    free(st->v);
    free(st);
    return st1;
}

/*Insere o jogo nome na hash table e no fim da lista e caso 
o numero de elementos seja metade do tamanho da hash aumenta
o seu tamanho para o dobro*/
jogo insere_jogo(jogo st, lista *l, char*nome, char *equipa1, char *equipa2, int score1, int score2) {
    int i;
    st->elementos+=1;
    if (2*st->elementos>=st->tamanho){
        st=re_hash_jogo(st);
    }
    i=hash(nome, st->tamanho);
    while (st->v[i]!=NULL){
        i = (i+1) % st->tamanho;
    }
    st->v[i] = (pPerson)malloc(sizeof(struct person));
    st->v[i]->score1 = score1;
    st->v[i]->score2 = score2;
    st->v[i]->eliminado = 0;
    st->v[i]->nome =(char*)malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(st->v[i]->nome, nome);
    st->v[i]->equipa1 =(char*)malloc(sizeof(char)*(strlen(equipa1)+1));
    strcpy(st->v[i]->equipa1, equipa1);
    st->v[i]->equipa2 =(char*)malloc(sizeof(char)*(strlen(equipa2)+1));
    strcpy(st->v[i]->equipa2, equipa2);
    st->v[i]->next=NULL;
    /*o novo jogo e inserido no fim da lista*/
    if (l->head == NULL) {
		l->head = st->v[i];
		l->last = st->v[i];
	} else {
		pPerson prev_last = l->last;
		prev_last->next = st->v[i];
		l->last = st->v[i];
	}
    return st;
}

/*Averigua se existe algum jogo com o nome nome na hash table.
Caso exista retorna 1 e caso contrario retorna 0.*/
int pertence_jogo(jogo st1, char *nome){
    int i;
    i=hash(nome, st1->tamanho);
    while (st1->v[i] != NULL){
        if (strcmp(st1->v[i]->nome, nome)==0 && st1->v[i]->eliminado==0){
            return 1;
        }
        else{
            i = (i+1) % st1->tamanho;
        }
    }
    return 0;
}

/*Faz print do jogo nome*/
void print_jogo(jogo st1, char *nome, int nl){
    int i;
    i=hash(nome, st1->tamanho);
    while (st1->v[i] != NULL){
        /*caso o jogo nao tenha sido eliminado*/
        if (strcmp(st1->v[i]->nome, nome)==0 && st1->v[i]->eliminado==0){
            printf("%d %s %s %s %d %d\n", nl, st1->v[i]->nome, st1->v[i]->equipa1, st1->v[i]->equipa2, st1->v[i]->score1, st1->v[i]->score2);
            return;
        }
        else{
            i = (i+1) % st1->tamanho;
        }
    }
}

/*Atualiza o score do jogo nome para os novos scores: score1 e score2.*/
jogo altera_score(jogo st1, char *nome, int novo_score1, int novo_score2){
    int i;
    i=hash(nome, st1->tamanho);
    while (st1->v[i] != NULL){
        if (strcmp(st1->v[i]->nome, nome)==0 && st1->v[i]->eliminado==0){
            st1->v[i]->score1=novo_score1;
            st1->v[i]->score2=novo_score2;
            return st1;
        }
        else{
            i = (i+1) % st1->tamanho;
        }
    }
    return st1;
}

/*Elimina um jogo, ou seja, altera a componente eliminado da 
estrutura jogo anteriormente a 0 para 1.*/
jogo elimina_jogo(jogo st, char *nome) {
    int i;
    i=hash(nome, st->tamanho);
    while (st->v[i]!=NULL){
        if (strcmp(st->v[i]->nome, nome)==0 && st->v[i]->eliminado==0) {
            break;
        }
        else i = (i+1) % st->tamanho;
    }
    st->v[i]->eliminado=1;
    return st;
}