#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Equipas.h"
#include "func_hash.h"
#define SIZE 1009
/*-------------------- funcoes para listas ligadas --------------------*/
ptr_equipas nova_equipa(char *nome, int vitorias)
{
    ptr_equipas novo = (ptr_equipas)can_fail_malloc(sizeof(struct equipas));
    novo->nome = nome;
    novo->vitorias = vitorias;
    return novo;
}

link_e insere_alfabetica(link_e primeiro, link_e y)
{
    link_e x, anterior;

    if ((primeiro == NULL) || (strcmp(y->equipa->nome, primeiro->equipa->nome) < 0))
    {
        y->proximo = primeiro;
        return y;
    }

    else
    {    
        anterior = primeiro;
        x = primeiro->proximo;
        while ((x != NULL) && ((strcmp(y->equipa->nome, x->equipa->nome) > 0)))
        {
            anterior = x;
            x = x->proximo;
        }
        y->proximo = x;
        anterior->proximo = y;
    }
    return primeiro;
}


link_e insere_inicio_e(link_e primeiro, link_e y)
{
    y->proximo = primeiro;
    return y;
}

link_e procura_e(link_e primeiro, char* nome)
{
    link_e x;
    for(x = primeiro; x != NULL; x = x->proximo)
        if (strcmp(x->equipa->nome, nome) == 0)
            return x;
    return NULL;
}

void FreeNode_e(link_e x)
{
    free(x->equipa);
    free(x);
}

void FreeNome_e(link_e x)
{
    free(x->equipa->nome);
    free(x->equipa);
}

/*-------------------- funcoes para a hashtable das equipas --------------------*/
link_e* inicializa_e(link_e *primeiros)
{
    int p;
    primeiros = (link_e*)can_fail_malloc(SIZE*sizeof(link_e));
    for(p = 0; p < SIZE; p++)
        primeiros[p] = NULL;
    return primeiros;
}

void insere_equipa(link_e *primeiros, link_e y)
{
    int i = func_hash(y->equipa->nome);
    primeiros[i] = insere_inicio_e(primeiros[i], y);
}

link_e procura_equipa(link_e *primeiros, char* nome)
{
    link_e p;
    int i = func_hash(nome);
    p =  procura_e(primeiros[i] , nome);
    return p;
}
