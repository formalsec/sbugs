#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/**
 * File:  main.c
 * Author:  Afonso Custodio 
 * Created on:  17mar2020
 * Description: Adaptacao de Algoritmo BFS
 * para calculo de notas atraves de um grafo orientado
 **/
#include <stdio.h>
#include <stdlib.h>

typedef enum bool
{
    NAO,
    SIM
} Bool;

typedef struct amizade
{
    int id_aluno;
    struct amizade *proxima_amizade; /*apontador para uma estrutura amizade*/
} Amizade;

typedef struct aluno
{
    int n_aluno;
    int nota_inicial;
    int nota_final;
    Amizade *primeira_amizade; /*apontador para estrutura que sera a primeira amizade do aluno*/
    Amizade *ultima_amizade;   /*apontador para estrutura que sera a ultima amizade do aluno*/
    /*Apontadores para manipulacao da Fila utilizada no algoritmo de calculo de notas*/
    Amizade *primeira_relacao;       /*apontador para estrutura que sera a primeira relacao do aluno*/
    Amizade *ultima_relacao;         /*apontador para estrutura que sera a ultima relacao do aluno */
    Amizade *prox_relacao_processar; /*apontador para estrutura amizade que tera a informacao do proximo vertice do grafo a processar*/
} Aluno;

typedef struct turma
{
    Aluno *alunos; /*apontador para vetor de estruturas de aluno que representa */
    int num_alunos;
} Turma;

/**
 *Cria e adiciona uma estrutura amizade a um aluno
 * @param id_amizade id do aluno
 * @param al aluno onde se insere a amizade
 **/
void addAmizade(Turma *t, int id_aluno, int id_amizade)
{
    Aluno *al = t->alunos + id_aluno;
    Amizade *am = (Amizade *)can_fail_malloc(sizeof(Amizade));
    am->proxima_amizade = NULL;
    am->id_aluno = id_amizade;
    if (al->primeira_amizade == NULL)
    {
        al->primeira_amizade = am;
    }
    else
    {
        al->ultima_amizade->proxima_amizade = am;
    }
    al->ultima_amizade = am;
}

/**
 *Liberta a memoria de uma estrutura amizade
 * @param am estrutura amizade a qual se vai libertar a memoria
 **/
void freeAmizade(Amizade *am)
{
    free(am);
}

/**
 *Cria e adiciona uma estrutura aluno a uma turma
 * @param nota nota do aluno
 * @param t estrutura turma a qual o aluno pertence
 **/
void addAluno(int nota, int id, Turma *t)
{
    Aluno *al = t->alunos + id;
    al->primeira_amizade = NULL;
    al->ultima_amizade = NULL;
    al->primeira_relacao = NULL;
    al->ultima_relacao = NULL;
    al->prox_relacao_processar = NULL;
    al->n_aluno = id;
    al->nota_inicial = nota;
    al->nota_final = nota;
}

/**
 *Liberta a memoria de um aluno
 * @param al aluno ao qual se liberta a memoria
 **/
void freeAluno(Aluno *al)
{
    Amizade *aux, *aux2;
    aux = al->primeira_amizade;
    /*Percorre lista de amizades*/
    while (aux)
    {
        aux2 = aux;
        aux = aux2->proxima_amizade;
        freeAmizade(aux2);
    }
    /*Percorre lista de relacoes*/
    aux = al->primeira_relacao;
    while (aux)
    {
        aux2 = aux;
        aux = aux2->proxima_amizade;
        freeAmizade(aux2);
    }
}

/**
 *Cria uma turma
 * @return Apontador para a estrututra turma criada
 **/
Turma *newTurma(int num_alunos)
{
    Turma *t = (Turma *)can_fail_malloc(sizeof(Turma));
    t->num_alunos = num_alunos;
    t->alunos = can_fail_malloc(num_alunos * sizeof(Aluno));
    return t;
}

/**
 *Liberta a memoria de uma estrutura turma
 * @param t estrutura cuja memoria ira ser libertada
 **/
void freeTurma(Turma *t)
{
    int i;

    for (i = 0; i < t->num_alunos; i++)
    {
        freeAluno(t->alunos + i);
    }
    free(t->alunos);
    free(t);
}

/**
 *Imprime a nota de um aluno
 * @param al aluno do qual se vai imprimir a nota
 **/
void printAluno(Aluno *al)
{
    printf("%d\n", al->nota_final);
}

/**
 *Imprime a nota de todos os alunos de uma turma
 * @param t turma da qual se vao imprimir as notas
 **/
void printTurma(Turma *t)
{
    int i;
    for (i = 0; i < t->num_alunos; i++)
    {
        printAluno(t->alunos+i);
    }
}

/**
 * Devolve se relacao ja existe na fila de relacoes de um aluno
 * @param al Aluno
 * @param id da relacao a procurar
 * @return SIM/NAO
 **/
Bool existeRelacao(Aluno *al, int id)
{
    Amizade *am;
    /*Se for ele proprio*/
    if (al->n_aluno == id)
        return SIM;
    /*Verifica na Fila Relacoes*/
    am = al->primeira_relacao;
    while (am)
    {
        if (am->id_aluno == id)
            return SIM;
        am = am->proxima_amizade;
    }
    return NAO;
}

/**
 * Adiciona uma relacao a fila de relacoes de um aluno
 * @param al aluno
 * @param id da relacao a inserir
 **/
void addRelacao(Aluno *al, int id)
{
    /*aloca memoria e set de valores da relacao*/
    Amizade *r = can_fail_malloc(sizeof(Amizade));
    r->id_aluno = id;
    r->proxima_amizade = NULL;

    /*Insere a relacao*/
    if (!al->primeira_relacao)
    { /* caso ainda nao haja relacoes*/
        al->primeira_relacao = r;
        al->ultima_relacao = r;
        al->prox_relacao_processar = r;
        return;
    }

    /*caso não seja a primeira relacao*/
    al->ultima_relacao->proxima_amizade = r;
    al->ultima_relacao = r;

    /*Caso proxima relação a processar seja NULL apontar para a inserida*/
    if (!al->prox_relacao_processar)
        al->prox_relacao_processar = r;
}

/**
 * Devolve a proxima relacao (amizade) de um aluno a processar
 * @param al aluno
 * @return estrutura amizade ou NUL se todas processadas
 **/
Amizade *getNextRelacaoProcessar(Aluno *al)
{
    Amizade *r;
    /*Caso todas tenham sido processadas*/
    if (!al->prox_relacao_processar)
        return NULL;
    /*caso haja a processar*/
    r = al->prox_relacao_processar;
    al->prox_relacao_processar = r->proxima_amizade;
    return r;
}

/**
 * Agoritmo para calculo de notas baseado no algoritmo BFS
 * Iteracao na turma para a cada aluno calcular nota final
 * @param t turma
 **/
void calculaNotas(Turma *t)
{
    int i;
    Aluno *al, *al_rel;
    Amizade *am, *r;

    for (i = 0; i < t->num_alunos; i++) /*para cada aluno aplica o algoritmo... */
    {
        al = t->alunos + i;
        /* inserir como relacao as amizades diretas */
        am = al->primeira_amizade;
        while (am) /*para cada amizade do aluno */
        {
            addRelacao(al, am->id_aluno);/* adiciona amizade como relacao*/
            am = am->proxima_amizade;
        }
        /*processa iterativamente fila de relacoes e insere novas */
        while ((r = getNextRelacaoProcessar(al)))
        {
            /*carrega o aluno em relacao (al_rel)*/
            al_rel = t->alunos + r->id_aluno;

            /*caso nota inicial do aluno em relacao seja maior que a nota final do aluno a calcular*/
            if (al_rel->nota_inicial > al->nota_final)
                al->nota_final = al_rel->nota_inicial;

            /*Insere como relacoes as amizades do aluno relacao em processamento*/
            am = al_rel->primeira_amizade;
            while (am) /*para cada amizade do aluno*/
            {
                if (existeRelacao(al, am->id_aluno) == NAO)
                    addRelacao(al, am->id_aluno);
                am = am->proxima_amizade;
            }
        }
    }
}

/**
 * #######################################################
 * Funcao main
 * Le dados de entrada
 * Adiciona os alunos
 * Adiciona as amizades dos alunos
 * Calcula notas
 * Manda imprimir notas finais
 * Liberta memoria
 **/
int main()
{
    Turma *t;   
    int num_alunos, num_amizades;
    int i, tmp1, tmp2;

    /*Le primeira linha*/
    scanf("%d,%d\n", &num_alunos, &num_amizades);

    /*Cria turma*/
    t = newTurma(num_alunos);

    /*Le alunos e carrega*/
    for (i = 0; i < num_alunos; i++)
    {
        scanf("%d", &tmp1);
        addAluno(tmp1, i, t);
            
    }

    /*Le amizades e carrega*/
    for (i = 0; i < num_amizades; i++)
    {
        scanf("%d %d", &tmp1, &tmp2);
        addAmizade(t,tmp1-1, tmp2-1);
    }
    
    calculaNotas(t);
    printTurma(t);
    freeTurma(t);
    return EXIT_SUCCESS;
}