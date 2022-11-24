#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "estruturas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*Funcao responsavel por inicializar a hash table dos jogos*/
void init_HTJ(jogo * HTjogo){
    int i;
    for(i = 0; i < TABLE_SIZE; i++){
        HTjogo[i] = NULL;
    }
}
/*Funcao responsavel por alocar a memoria necessaria para criar um novo jogo dentro da hash table*/
jogo newjogo(char * nome, char * eq1, char * eq2, int sc1, int sc2, int id){
    jogo aux = can_fail_malloc(sizeof(struct str_jogo));
    aux->nome = can_fail_malloc(sizeof(char)*(strlen(nome)+1));
    aux->eq1 = can_fail_malloc(sizeof(char)*(strlen(eq1)+1));
    aux->eq2 = can_fail_malloc(sizeof(char)*(strlen(eq2)+1));
    aux->sc1 = sc1;
    aux->sc2 = sc2;
    aux->id = id;
    strcpy(aux->nome, nome);
    strcpy(aux->eq1, eq1);
    strcpy(aux->eq2, eq2);
    aux->nextJ = NULL;
    return aux;
}

/*Funcao responsavel por inserir o novo jogo no inicio de cada indice da hash table*/
jogo InsertBeginingJogo(jogo head, char * nome, char * eq1, char * eq2, int sc1, int sc2, int id){
    jogo aux = newjogo(nome, eq1, eq2, sc1, sc2, id);
    aux->nextJ = head;
    return aux;
}

/*Funcao responsavel por obter o indice em que o novo jogo vai ser inserida*/
void InsertJogo(char * nome, char * eq1, char * eq2, int sc1, int sc2, jogo * HTjogo, int id){
    int x = Hash(nome ,TABLE_SIZE);
    HTjogo[x] = InsertBeginingJogo(HTjogo[x], nome, eq1, eq2, sc1, sc2, id);
}

/*Funcao responsavel por procurar um jogo dentro da hash table*/
jogo SearchJogo(char * nome, jogo * HTjogo){
    int i = Hash(nome, TABLE_SIZE);
    jogo aux;
    for(aux = HTjogo[i]; aux != NULL; aux = aux->nextJ){
        if(strcmp(aux->nome,nome) == 0) return aux;
    }return NULL;
}

/*Funcao responsavel por remover o jogo da hash table libertando a memoria usada e acertando a ordem dos elementos da hash table*/
jogo RemoveJogo(jogo head, char * nome){
    jogo t,prev;
    for(t = head, prev = NULL; t != NULL; prev = t, t = t-> nextJ){
        if(strcmp(t->nome, nome) == 0){
            if (t == head) head = t->nextJ;
            else prev->nextJ = t->nextJ;
            FreeJogo(t);
            return head;
        }
    }return head;
}

/*Funcao responsavel para libertar a memoria usada pela hash table dos jogos*/
void FreeHTjogo(jogo * HTjogo){
    int i;
    jogo aux;
    for(i = 0; i<TABLE_SIZE;i++ ){
        while(HTjogo[i]){
            aux = HTjogo[i]->nextJ;  
            FreeJogo(HTjogo[i]);
            HTjogo[i] = aux;
        }
    }
}

/*Funcao responsavel para libertar a memoria usada para criar cada parametro do jogo*/
void FreeJogo(jogo aux){
    free(aux->nome);
    free(aux->eq1);
    free(aux->eq2);
    free(aux);
}