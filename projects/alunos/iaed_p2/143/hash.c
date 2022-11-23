#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
 
#define TRUE 0

/* -------hash table Equipa-------- */

/* RESOLUCAO POR PROCURA LINEAR */

/* funcao hash das equipas */
int Equipa_hash(char *nome, int M){
    int h, a = 31415, b = 27183;

    for(h = 0; *nome != '\0'; nome++, a = (a * b) % (M - 1)){
        h = (a * h + *nome) % M;
    }
    return h;
}


/* funcao que inicializa o ponteiro das equipas */
equipa * Equipa_init(int m, unsigned int *M, equipa *Equipa){
    int i; 
    *M = m;
    Equipa = (equipa*) can_fail_malloc(m * sizeof(equipa));
    for(i = 0; i < m; i++){
        Equipa[i] = NULL;
    }
    return Equipa;
}


/* funcao que insere uma equipa*/
void Equipa_insert(int M, equipa *Equipa, equipa p){
    unsigned int i = Equipa_hash(p->nome, M);
    
    
    while(Equipa[i] != NULL){
        i = (i + 1) % M;
    }
    Equipa[i] = p;
}


/* funcao que procura uma equipa */
equipa Equipa_search(int M, char Nome[], equipa *Equipa){
    unsigned int i = Equipa_hash(Nome, M); 
    
    
    while (Equipa[i] != NULL){
        if (strcmp(Equipa[i]->nome, Nome) == TRUE){
            return Equipa[i];
        }
        else{
            i = (i + 1) % M;
        }
    }
    return NULL;
}


/* funcao que da free (liberta memoria) das equipas */
void Equipa_FREE(unsigned int M, equipa *Equipa){
    unsigned int j; 
    for (j = 0; j < M; j++){
        if (Equipa[j] != NULL){
            free(Equipa[j]->nome);
            free(Equipa[j]);
        }
    }
    free(Equipa);
}


/* funcao que expande a hash das equipas */
equipa *Equipa_expand(unsigned int *M, equipa *Equipa){
    unsigned int i;
    equipa *p = Equipa;

    Equipa = Equipa_init(*M + *M, M, Equipa);

    for(i = 0; i < (*M / 2); i++){
        if(p[i] != NULL){
            Equipa_insert(*M, Equipa, p[i]);
        }
    }
    free(p);
    return Equipa;   
}

/*------- hash table Jogos -------*/

/* RESOLUCAO POR PROCURA LINEAR */


/* funcao hash dos jogos */
int Jogo_hash(char *nome, int N){
    unsigned int h;
    int a = 31415, b = 27183;

    for(h = 0; *nome != '\0'; nome++, a = (a * b) % (N - 1)){
        h = (a * h + *nome) % N;
    }
    return h;
}


/* funcao que inicializa o ponteiro dos jogos */
jogo *Jogo_init(int m, unsigned int *N, jogo *Jogo){
    int i; 
    *N = m;
    Jogo = (jogo*) can_fail_malloc(m * sizeof(jogo));
    for(i = 0; i < m; i++){
        Jogo[i] = NULL;
    }
    return Jogo;
}


/* funcao que insere um jogo */
void Jogo_insert(int N, jogo *Jogo, jogo p){
    unsigned int i = Jogo_hash(p->nome, N);

    while(Jogo[i] != NULL){
        i = (i + 1) % N;
    }
    Jogo[i] = p;
}


/* funcao que procura um jogo */
jogo Jogo_search(int N, char Nome[], jogo *Jogo){
    unsigned int i = Jogo_hash(Nome, N);


    while (Jogo[i] != NULL){
        if (strcmp(Jogo[i]->nome, Nome) == TRUE){
            return Jogo[i];
        }
        else{
            i = (i + 1) % N;
        }
    }
    return NULL;
}


/* funcao que apaga um jogo */
void Jogo_delete(unsigned int N, char Nome[], jogo *Jogo){
    unsigned int j;
    unsigned int i = Jogo_hash(Nome, N);
    
    jogo p; 

    

    while(Jogo[i] != NULL){
        if(strcmp(Jogo[i]->nome, Nome) == TRUE){
        break;
        } 
        else{
            i = (i + 1) % N;
        }
    }
    if (Jogo[i] == NULL) return;

    
    free(Jogo[i]->nome); free(Jogo[i]); Jogo[i] = NULL;
    

    for(j = (i + 1) % N; Jogo[j] != NULL; j = (j + 1) % N){
        p = Jogo[j];
        Jogo[j] = NULL;
        Jogo_insert(N, Jogo, p);
    }
}


/* funcao que da free (liberta memoria) dos jogos */
void Jogo_FREE(unsigned int N, jogo *Jogo){
    unsigned int j; 
    for (j = 0; j < N; j++){
        if (Jogo[j] != NULL){
            free(Jogo[j]->nome);
            free(Jogo[j]);
        }
    }
    free(Jogo);
}


/* funcao que expande a hash dos jogos */
jogo *Jogo_expand(unsigned int *M, jogo *Jogo){
    unsigned int i;
    jogo *p = Jogo;

    Jogo = Jogo_init(*M + *M, M, Jogo);


    
    for(i = 0; i < (*M / 2); i++){
        if(p[i] != NULL){
            Jogo_insert(*M, Jogo, p[i]);
        }
    }
    free(p);
    return Jogo;
}

