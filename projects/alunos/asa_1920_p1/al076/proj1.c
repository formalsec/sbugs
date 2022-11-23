#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"

/*
Projeto 1 de ASA segundo semestre primeiro ano
Grupo 76 Alameda
Guilherme Areias    89451
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* relacao entre o aluno1 e aluno 2 */
typedef struct {
	int al1;
	int al2;
} Vector;

/* Varivaies
n_alunos: numero de alunos inseridos
n_relacoes: numero de relacoes de amizade entre alunos
max_rel : numero maximo de relacoes de um aluno
amizades: lista de vetores com as relacoes de amizade
current_index: indicador do index atual */
int n_alunos = 0;
int n_relacoes = 0;
int max_rel = 0;
Vector* amizades;
int current_index = 0;

/* Funcoes */
/*void initialize(int relacoes[n_alunos+1][max_rel]);*/
void influencia(int i, int al, int relacoes[n_alunos][max_rel], int notas[n_alunos+1][3]);

int main(){

   /* s_aux : string auxiliar que guarda os valores N ou M antes de passarem a inteiros */
   int k = 0, i = 0, e = 0, aluno1 = 0, aluno2 = 0;
   char y, input[100], s_aux[100];

   /* 1) scan dos parametros N e M */
   while ((y = getchar()) != '\n' && y != EOF){
       input[k] = y;
       k++;
   }
   input[k] = '\0';
   k = 0;
   while (input[i] != ','){
       s_aux[i] = input[i];
       i++;
   }
   s_aux[i] = '\0';
   n_alunos = atoi(s_aux);
   memset(s_aux, '\0', sizeof(s_aux));
   i++;
   while (input[i] != '\0'){
       s_aux[k] = input[i];
       i++;
       k++;
   }
   s_aux[k] = '\0';
   n_relacoes = atoi(s_aux);
   memset(s_aux, '\0', sizeof(s_aux));

   /* 2) scan das notas dos N alunos*/
   /* notas : lista com as notas e id e estado de cada aluno */
   /* notas[][2] : quando o estado != 0 o aluno influenciou todos os alunos que tinha a influenciar */
   int notas[n_alunos+1][3];
   /* numero maximo de relacoes de um aluno */
   max_rel = (n_relacoes / 2) + 2;
   /* relacoes : tem o numero de relacoes de cada aluno 'relacoes[][0]' e as relacoes do aluno.
    os valores das relacoes que sao:
        < 0 ele nao e necessariamente amigo
        > 0 ele e amigo */ 
   int relacoes[n_alunos+1][max_rel];
   amizades = can_fail_malloc(sizeof(Vector)*n_relacoes);
   for (i = 1; i <= n_alunos; i++){
       if (scanf("%d", &notas[i][1])){
           /* inicializa a lista relacoes */
           notas[i][0] = i;
           notas[i][2] = 0;
           relacoes[i][0] = 0;
       }
   }

   /* 3) scan das M relacoes alunos*/
   for (i = 0; i < n_relacoes; i++){
       if (scanf("%d %d", &aluno1, &aluno2)){
           /* verifica se a relacao ja existe */
           e = 1;
           k = 1;
           if (relacoes[aluno1][0] != 0){
               while (e <= relacoes[aluno1][0]){
                   if (relacoes[aluno1][e] == aluno2){
                       k = 0;
                    }
                    e++;
                }
           }
           /* adiciona a relacao de amizade */
           if (k == 1){
            amizades[i].al1 = aluno1;
            amizades[i].al2 = aluno2;
            k = relacoes[aluno1][0] + 1; 
            relacoes[aluno1][k]= aluno2;
            k = relacoes[aluno2][0] + 1; 
            relacoes[aluno2][k]= -aluno1;
            relacoes[aluno1][0]++;
            relacoes[aluno2][0]++;
           }
       }
   }

   /* 4) ordena a lista com as notas de maior para menor */
   while(1){
       /* enquanto for 0 a lista ainda nao esta ordenada */
       k = 0;
        for (i = 1; i <= n_alunos - 1; i++){
            if (notas[i][1] < notas[i+1][1]){
                /* aqui as variaveis aluno1 e aluno2 servem so para ajudar */
                aluno1 = notas[i][0];
                aluno2 = notas[i][1];
                notas[i][0] = notas[i+1][0];
                notas[i][1] = notas[i+1][1];
                notas[i+1][0] = aluno1;
                notas[i+1][1] = aluno2;
                k = 1;
            }
        }
        if (k == 0){
            break;
        }
   }

   /* 5) percorrer a lista notas[][] e alterar as notas que sejam precisas */
   for (i = 1; i <= n_alunos; i++){
       aluno1 = notas[i][0]; /* id do aluno */
       if (notas[aluno1][2] == 0){
           if (relacoes[aluno1][0] > 0){
               influencia(i, aluno1, relacoes, notas);
           }
           notas[aluno1][2] = 1;
       }
   }

   /* 6) output do programa */
   for (i = 1; i <= n_alunos; i++){
       for (k = 1; k <= n_alunos; k++){
           if (i == notas[k][0]){
               printf("%d\n", notas[k][1]);
           }
       }
   }

   free(amizades);

   return 0;
}

/* Percorre todas as relacoes de um aluno em que este pode influenciar a nota de outro aluno */
void influencia(int i, int al, int relacoes[n_alunos][max_rel], int notas[n_alunos+1][3]){
    int k = relacoes[al][0];
    int al2, n1, n2, e, aux = 0;
    /* enquanto o numero de relacoes do aluno al for diferente de zero */
    while (k != 0){
        /* caso al influencie a nota do aluno k */
        if (relacoes[al][k] < 0){
            al2 = abs(relacoes[al][k]);
            n1 = notas[i][1];
            for (e = 1; e <= n_alunos; e++){
                if (al2 == notas[e][0]){
                    aux = e;
                    e = n_alunos;
                }
            }
            n2 = notas[aux][1];
            /* caso o aluno 2 va subir a nota */
            if (n1 > n2){
                notas[aux][1] = n1;
                influencia(aux, al2, relacoes, notas);
            }
        }
        k--;
    }
    /* o aluno al ja influenciou todos os alunos que podia influenciar */
    notas[al][2] = 1;
}

/* Fim */