/*
 * File:  proj1.c
 * Author: 92443 Daniela Carvalho
 *         93718 Guilherme Barata
 * Description: Um programa que permite prever notas de alunos.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct adj{
    int i_amigo;
    struct adj * next;
} * Adj;

typedef struct aluno{
    int nota_prevista;
    Adj sou_amigo;
    int visitado;
} * Aluno;

Aluno alunos;

/* FUNCOES */
void preencher_aluno(int N);
void preencher_amigos(int M);
void ver_alunos(int N, int M);
void propagar_notas(int vertice);
void print_resultados(int N);

int main(){

    int N, M;
    
    scanf("%d,%d", &N, &M);
    if (N<2) return EXIT_FAILURE;
    if (M<1) return EXIT_FAILURE;

    preencher_aluno(N);
    preencher_amigos(M);
    ver_alunos(N, M);
    print_resultados(N);
    return 0;
}

/* ALUNO */
/* Trata inputs do aluno */
void preencher_aluno(int N){
    int i;

    alunos = (Aluno) malloc(N * sizeof(struct aluno));

    for (i=0; i<N; i++){
        int nota;
        scanf("%d", &nota);
        
        alunos[i].visitado = 0;
        alunos[i].nota_prevista = nota;
        alunos[i].sou_amigo = NULL;
    }
}

/* AMIGOS */
/* Trata dos inputs de relacoes de amizade */
void preencher_amigos(int M){
    int i;

    for (i=0; i<M; i++){

        int u, v;
        scanf("%d %d", &u, &v);

        Adj amigo = (Adj) malloc(sizeof(struct adj));
        amigo->i_amigo = u-1;

        if (alunos[v-1].sou_amigo == NULL){
            amigo->next = NULL;
        }
        else{
            amigo->next = alunos[v-1].sou_amigo;
        }
        alunos[v-1].sou_amigo = amigo;
    }
}

/* RECALCULA NOTAS */

void ver_alunos(int N, int M) {
    int i;

    for (i=0; i<N; i++){

        if (!alunos[i].visitado){
            alunos[i].visitado = 1;
            propagar_notas(i);
        }
    }
}

void propagar_notas(int vertice){
    int nota = alunos[vertice].nota_prevista;
    Adj amigo_aux;

    for (amigo_aux = alunos[vertice].sou_amigo; amigo_aux != NULL; amigo_aux = amigo_aux->next){
          
        int vertice_amigo = amigo_aux->i_amigo;

        if (nota > alunos[vertice_amigo].nota_prevista){
            alunos[vertice_amigo].visitado = 1;
            alunos[vertice_amigo].nota_prevista = nota;
            propagar_notas(vertice_amigo);   
        }
    }
}

/* RESULTADOS - output e frees */
void print_resultados(int N){
    int i;
    Adj amigo, amigo_aux;

    for (i=0; i<N; i++){
        printf("%d\n", alunos[i].nota_prevista);

        amigo = alunos[i].sou_amigo;

        while(amigo != NULL){
            amigo_aux = amigo;
            free(amigo_aux);
            amigo = amigo->next;
        }
    }
    free(alunos);
}