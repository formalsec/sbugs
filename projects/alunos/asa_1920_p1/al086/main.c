#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFO 2

typedef struct conexoes
{
    int id;
    struct conexoes *next;
} conexoes;


typedef struct aluno
{
    int nota;
    struct conexoes *amigo; 
    struct conexoes *ultimoAmigo;
    int totalConexoes;
    int visitado;
} aluno;

/*
guarda as informacoes:  
o numero de alunos inscritos na disciplina 
o numero de relacoes de amizade
*/

/*
guarda os alunos e suas notas
*/
void getAlunos(int numDeAlunos, aluno *alunos)
{
    int i;
    for(i=0; i < numDeAlunos; i++)
    {
        if(scanf("%d", &alunos[i].nota) != EOF)
        {
            alunos[i].amigo = (conexoes*)can_fail_malloc(sizeof(conexoes));  
            alunos[i].amigo->id = -1;
            alunos[i].amigo->next = NULL;
            alunos[i].ultimoAmigo = alunos[i].amigo;
            alunos[i].totalConexoes = 0;
            alunos[i].visitado = -1;
        } else {
            exit(1);
        }
    }
}

/*
Separa a string recebida para assim obter:
 - o aluno
 - o seu amigo/conexao
*/
void getFriend(int estudante, int amigo, aluno *alunos)
{

    alunos[estudante].ultimoAmigo->id = amigo;

    alunos[estudante].ultimoAmigo->next = (conexoes *)can_fail_malloc(sizeof(conexoes));
    alunos[estudante].ultimoAmigo->next->id = -1;
    alunos[estudante].ultimoAmigo->next->next = NULL;
    alunos[estudante].ultimoAmigo = alunos[estudante].ultimoAmigo->next;

    alunos[estudante].totalConexoes++;
}

/*
Cria as conexoes de amizade entre os alunos
*/
void getConnections(int numDeConexoes, aluno *alunos)
{
    int i, estudante, amigo;
    for(i=0; i < numDeConexoes; i++)
    {
        if(scanf("%d %d", &estudante, &amigo) != EOF)
        {
            getFriend(estudante - 1, amigo - 1, alunos);
        } 
        else {
            exit(1);
        }
    }
}

/*
Percorre todas as ligacoes de um aluno, obtendo assim a maior nota entre suas conexoes
*/

int visitarAlunos(int idDoAluno, aluno *alunos, int numDaInteracao)
{
    int i;
    int temp = 0;
    int resultado = 0;
    conexoes *auxilar;

    if(alunos[idDoAluno].visitado != numDaInteracao){
        alunos[idDoAluno].visitado = numDaInteracao;
        temp = alunos[idDoAluno].nota;
        auxilar=alunos[idDoAluno].amigo;
        for(i=0; i<alunos[idDoAluno].totalConexoes; i++)
        {
            resultado = visitarAlunos(auxilar->id, alunos, numDaInteracao);
            auxilar=auxilar->next;
            if (temp < resultado)
            {
                temp = resultado;
                alunos[idDoAluno].nota = temp;
            }
        }
        return temp;
    } else {
        return alunos[idDoAluno].nota;
    }



}

void calcularNotas(aluno *alunos, int numDeAlunos){
    int i = 0;

    for(i = 0; i<numDeAlunos; i++){
        visitarAlunos(i, alunos, i);
    }

}

/*
Percorre todos os alunos assim imprimindo suas notas
*/
void imprimirNotas(aluno *alunos, int numDeAlunos)
{
    int i;
    for(i = 0; i<numDeAlunos; i++)
    {
        printf("%d\n", alunos[i].nota);
    }
}

void fim(aluno *alunos, int numDeAlunos)
{
    int i, j;
    /*corrigir frees*/
    conexoes *auxiliar;
    for(i=0; i<numDeAlunos; i++){
        for(j=0; j<alunos[i].totalConexoes; j++){
            auxiliar = alunos[i].amigo;
            alunos[i].amigo = alunos[i].amigo->next;
            free(auxiliar);
        }
        free(alunos[i].ultimoAmigo);
        
    }
    free(alunos);
}

int main (void)
{
    char comma;
    int informacoes[INFO];

    if(scanf("%d%c%d", &informacoes[0], &comma, &informacoes[1]) != EOF){

        aluno *alunos = can_fail_malloc(informacoes[0]*sizeof(aluno));

        getAlunos(informacoes[0], alunos);

        getConnections(informacoes[1], alunos);

        calcularNotas(alunos, informacoes[0]);

        imprimirNotas(alunos, informacoes[0]);

        fim(alunos, informacoes[0]);

    }

    return 0;

}