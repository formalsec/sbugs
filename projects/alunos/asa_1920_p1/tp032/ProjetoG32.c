#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

struct amigos {
    int aluno;
    int amigo;
};

int *alunos;
struct amigos *amizades;
int mudanca = 1;

void aplicaAlgoritmo(int M) {
    int a, idAluno, idAmigo;
    for(a = 0; a < M; a++){
        idAluno = amizades[a].aluno - 1;
        idAmigo = amizades[a].amigo - 1;
        if(alunos[idAmigo] > alunos[idAluno]){
            alunos[idAluno] = alunos[idAmigo];
            mudanca = 1;
        }
    }
}

void display(int N) {
    int i;
    for(i = 0; i < N; i++) {
        printf("%d\n", alunos[i]);
    }
}

int main() {
    int N, M, i, j;

    scanf("%d,%d", &N, &M);
    alunos = (int*)can_fail_malloc(N * sizeof(int));
    amizades = (struct amigos*)can_fail_malloc(M * sizeof(struct amigos));

    for (i = 0; i < N; i++) {
        scanf("%d", &alunos[i]);
    }
    
    for (j = 0; j < M; j++) {
        scanf("%d %d", &amizades[j].aluno, &amizades[j].amigo);
    }

    while(mudanca != 0){
        mudanca = 0;
        aplicaAlgoritmo(M);
    }

    display(N);
    free(alunos);
    return 0;
}