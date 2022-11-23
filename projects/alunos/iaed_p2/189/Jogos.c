#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Jogos.h"
#include "func_hash.h"
#define SIZE 1009

/*------------------- funcoes de listas ligadas -------------------*/
ptr_jogo novo_jogo(char *nome, char *eq1, char *eq2, int score1, int score2)
{
    ptr_jogo novo = (ptr_jogo)can_fail_malloc(sizeof(struct jogo));
    novo->nome = nome;
    novo->equipa1 = eq1;
    novo->equipa2 = eq2;
    novo->score1 = score1;
    novo->score2 = score2;
    return novo;
}

link_j insere_fim_j(link_j ultimo_jogo, link_j j1)
{
    if(ultimo_jogo == NULL)
        return j1;

    ultimo_jogo->proximo = j1;
    j1->proximo = NULL;
    return j1;
}


link_j procura_j(link_j primeiro_jogo, char* nome)
{
    link_j x;
    for(x = primeiro_jogo; x != NULL; x = x->proximo)
        if (strcmp(x->jogo->nome, nome) == 0)
            return x;
    return NULL;
}

void FreeNomes_j (link_j x)
{
    free(x->jogo->nome);
    free(x->jogo->equipa1);
    free(x->jogo->equipa2); 
    free(x->jogo);
}

void FreeNode_j(link_j x)
{
    free(x->jogo);
    free(x);
}

link_j apaga_j(link_j *primeiros_j, link_j primeiro_jogo, char* nome, link_j *fim_lista)
{
    link_j x, y, anterior;

    for(x = primeiro_jogo, anterior = NULL; x != NULL; anterior = x, x = x->proximo)
    {
        if(strcmp(x->jogo->nome, nome) == 0)
        {
            if(x == primeiro_jogo)
            {
                primeiro_jogo = x->proximo;
                if ((*fim_lista) == x)
                    (*fim_lista) = x->proximo;
            }
            else
            {
                anterior->proximo = x->proximo;
                if(*(fim_lista) == x)
                    *fim_lista = anterior;
                
            }

            y = apaga_jogo(primeiros_j, nome);
            free(x->jogo->nome);
            free(x->jogo->equipa1);
            free(x->jogo->equipa2);
            FreeNode_j(x);
            free(y);
            return primeiro_jogo;
        }
    }
    return primeiro_jogo;
}

/*-------------------- funcoes para a hashtable dos jogos --------------------*/
link_j* inicializa_j(link_j *primeiros_j)
{
    int k;
    primeiros_j = (link_j*)can_fail_malloc(SIZE*sizeof(link_j));
    for(k = 0; k < SIZE; k++)
        primeiros_j[k] = NULL;
    return primeiros_j;
}


void insere_jogo(link_j *primeiros_j, link_j j1)
{
    int i = func_hash(j1->jogo->nome);
    primeiros_j[i] = 
        insere_inicio_j(primeiros_j[i], j1);
}

link_j insere_inicio_j(link_j inicio, link_j j1)
{
    j1->proximo = inicio;
    return j1;
}


link_j procura_jogo(link_j *primeiros_j, char* nome)
{
    link_j k;
    int i = func_hash(nome);
    k = procura_j(primeiros_j[i] , nome);
    return k;
}


link_j apaga_jogo(link_j *primeiros_j,char *nome)
{
    link_j primeiro_jogo, anterior, x;
    int i = func_hash(nome);
    primeiro_jogo = primeiros_j[i];
    for(x = primeiro_jogo, anterior = NULL; x != NULL; anterior = x, x = x->proximo)
    {
        if (strcmp(x->jogo->nome, nome) == 0)
        {
            if(x == primeiro_jogo)
                primeiros_j[i] = x->proximo;
                    
            else
                anterior->proximo = x->proximo;
            break;
        }
    }
    return x;
}

