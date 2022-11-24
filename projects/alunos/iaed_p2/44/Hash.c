#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"


static int M;

/*Funcao que determina o slot da Hash Table para um jogo ou equipa*/
int hash(char *v, int M)
{
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
        h = (a*h + *v) % M;
    return h;
}

/***************************************************
****************************************************
Codigo para os jogos
****************************************************
***************************************************/

/*Nova estrutura que contem um apontador para um jogo*/
link JnewNode(link next, jogo j){
    link l = (link)can_fail_malloc(sizeof(struct node));
    l->j = j;
    l->next = next;
    return l;
}

/*Procura um jogo numa cabeca da HashTable*/
jogo JsearchList(link head, Key v){
    link aux;
    for (aux = head; aux; aux = aux->next) {
		if (strcmp(v, key(aux->j))==0) {
            return aux->j;
        }
	}
	return NULL;
}

/*Encontra um jogo na HashTable e remove-o da mesma*/
link removeJ(link head, Key k){
	link aux, aux2;
	for (aux = head, aux2 = NULL; aux; aux2 = aux, aux = aux->next) {
		if (strcmp(k, key(aux->j))==0){
			if (aux == head) {
                head = aux->next;
            }
            else{
                aux2->next = aux->next;
            }
            if(aux->j->score1 > aux->j->score2){
                aux->j->equipa1->wins--;
            } 
            if(aux->j->score1 < aux->j->score2){
                aux->j->equipa2->wins--;
            } 
/*Liberta a memoria previamente alocada*/
			freeJogo(aux->j);
            free(aux);
			return head;
		}
	}
	return head;
}


/*Liberta a memoria de uma cabeca da Hash*/
void JfreeHash(link head){
	link aux1, aux2;
    if (!head) return;
	
	for (aux1 = head, aux2 = head->next; aux1; aux2 = aux1->next, aux1 = aux2){
        freeJogo(aux1->j);
        free(aux1);
    }
}

/*Cria e inicializa a HashTable*/
link* Jinit(int m){
    link *heads;
    int i;
    M=m;
    heads=(link*)can_fail_malloc(M*sizeof(link));
    for(i=0;i<M;i++){
        heads[i]=NULL;
    }
    return heads;
}

/*Insere um jogo na HashTable*/
void Jinsert(link *heads,jogo j){
    int i = hash(key(j), M);
    heads[i] = JnewNode(heads[i], j);
}

/*Procura um jogo na HashTable*/
jogo Jsearch(link *heads,Key v){
    int i = hash(v, M);
    return JsearchList(heads[i], v);
}

/*Apaga um jogo da HashTable*/
void Jdelete(link *heads,Key v){
    int i = hash(v, M);
    heads[i] = removeJ(heads[i],v);
}

/*Destroi a HashTable*/
void JdestroyHash(link* heads){
	int i;
	for (i = 0; i < M; i++) {
		JfreeHash(heads[i]);
	}
/*Liberta a memoria alocada para as cabecas da HashTable*/ 
	free(heads);
}

/***************************************************
****************************************************
Codigo para as equipas
****************************************************
***************************************************/

/*Obtem o numero de vitorias de uma equipa*/
int getWins(Elink* tops,char team[1024]){
    equipa eq;

    eq = Esearch(tops,team);

    return (eq->wins);
}

/*Ordena um array de equipas por ordem alfabetica*/
int TeamOrder(const void *x,const void *y){
    const equipa a = *(const equipa*)x;
    const equipa b = *(const equipa*)y;

    return strcmp((a)->nome,(b)->nome);
}

/*Obtem o maior numero de vitorias alcancado e as equipas que o obtiveram*/
void getMostWins(Elink* tops, int count){
	int i,j,k,maxWins;
    Elink aux;
    equipa *Array;

/*Obtem o maximo de vitorias*/
	for (i = 0 ,maxWins = -1; i < M; i++) {
        for (aux = tops[i]; aux; aux = aux->next) {
            j=0;
		    j=aux->e->wins;
            if(j>maxWins){
                maxWins=j;
            }
	    }
        
	}
    if(maxWins==-1)return;

/*Obtem o numero de equipas que conseguiram o maximo numero de vitorias*/
    k=0;
    for(i=0;i < M;i++){
        for(aux = tops[i]; aux; aux = aux->next){
            if(aux->e->wins==maxWins){
                k++;
            }
        }
    }
    

    Array = can_fail_malloc(sizeof(equipa)*k);
    i=0;
/*Obtem as equipas que conseguiram o maximo numero de vitorias*/
    while(i<k){
        for(j=0;j < M;j++){
            for(aux = tops[j]; aux; aux = aux->next){
                if(aux->e->wins==maxWins){
                    Array[i]=aux->e;
                    i++;
                }
            }
        }
    }
/*Ordena as equipas por ordem alfabetica*/ 
    qsort(Array, k, sizeof(equipa), TeamOrder);
    printf("%d Melhores %d\n",count,maxWins);
    for(i=0;i<k;i++){
        printf("%d * %s\n",count,Array[i]->nome);
    }

    free(Array);
  
    
}


/*Nova estrutura que contem um apontador para uma equipa*/
Elink EnewNode(Elink next, equipa e){
    Elink l = (Elink)can_fail_malloc(sizeof(struct Enode));
    l->e = e;
    l->next = next;
    return l;
}

/*Procura uma equipa numa cabeca da HashTable*/
equipa EsearchList(Elink top, Point v){
    Elink aux;
    for (aux = top; aux; aux = aux->next) {
		if (strcmp(v, point(aux->e))==0) {
            return aux->e;
        }
	}
	return NULL;
}


/*Liberta a memoria de uma cabeca da Hash*/
void EfreeHash(Elink top){
	Elink aux1, aux2;
    if (!top) return;
	
	for (aux1 = top, aux2 = top->next; aux1; aux2 = aux1->next, aux1 = aux2){
        freeEquipa(aux1->e);
        free(aux1);
    }
}

/*Cria e inicializa a HashTable das equipas*/
Elink* Einit(int m){
    Elink *tops;
    int i;
    M=m;
    tops=(Elink*)can_fail_malloc(M*sizeof(Elink));
    for(i=0;i<M;i++){
        tops[i]=NULL;
    }
    return tops;
}

/*Insere uma equipa na HashTable*/
void Einsert(Elink *tops,equipa e){
    int i = hash(point(e), M);
    tops[i] = EnewNode(tops[i], e);
}

/*Procura uma equipa na HashTable e devolve-a caso exista*/
equipa Esearch(Elink *tops,Point v){
    int i = hash(v, M);
    return EsearchList(tops[i], v);
}

/*Destroi a HashTable das equipas*/
void EdestroyHash(Elink* tops){
	int i;
	for (i = 0; i < M; i++) {
		EfreeHash(tops[i]);
	}
/*Liberta a memoria das cabecas*/
	free(tops);
}

