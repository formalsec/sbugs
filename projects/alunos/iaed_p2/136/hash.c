#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>

#include "hash.h"

/* FONTE (hash): https://cp-algorithms.com/string/string-hashing.html */

/* NOTA 1: um elemento de uma fila e sempre um ponteiro para um no
   NOTA 2: um elemento de um no e sempre um ponteiro ou para outro no ou para
uma estrutura */

/* funcao de dispersao - a cada string (argumento) associa uma chave */
int hash(char * s)
{
    int hash; /* resultado: a chave a ser calculada */
    unsigned long int i; /* expoente de cada caracter */ 
    unsigned long int tamanho; /* tamanho da string inserida */

    tamanho = strlen(s); /* calculo do tamanho da string */

    hash = s[0]; /* comecando no primeiro caracter */

    /* para cada caracter calcula-se o resto da divisao pelo max (primo) */
    for (i = 1; i < tamanho; i++) /* em cada iteracao atualiza-se o valor */
    {
        /* atualizacao para cada caracter - depende da posicao e da letra */
        hash = (hash + s[i] * i) % MAX_DIM;
    }

    return hash; /* retorna-se a chave */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao de inicializacao - inicializa uma fila vazia */
void FILAinit(fila Lst)
{
    Lst->head = NULL; /* nao tem nada na cabeca */
    Lst->tail = NULL; /* nem nada na cauda */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao de limpeza/libertacao - liberta a memoria associada a uma fila */
void FILAclear(fila Lst)
{
    node aux, aux_next;
    
    if (!Lst) return; /* se nao houver fila nao faz nada */

    /* se nao, comeca na cabeca e vai ate ao fim libertando cada elemento */
    aux = Lst->head;
    while (aux) /* enquando se estiver a apontar para alguma coisa */
    {
        aux_next = aux->next; /* salvaguarda-se o elemento seguinte */
        free(aux); /* liberta-se o atual */
        aux = aux_next; /* passa-se para o seguinte */
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao de adicao - adiciona um elemento ao fim de uma fila */
void FILAadd(fila Lst, void * v)
{
    node aux; /* elemento a adicionar */

    /* adiciona o elemento a fila */

    aux = can_fail_malloc(sizeof(struct str_node)); /* 1o reserva a memoria */
    aux->elem = v; /* 2o atribui o valor */
    aux->next = NULL; /* 3o o elemento e adicionado ao fim => nao ha proximo */
    aux->prev = Lst->tail; /* 4o o anterior ao adicionado e o antigo ultimo */


    if (Lst->tail != NULL) /* se o ultimo elemento ja tiver sido inicializado */
        Lst->tail->next = aux; /* temos de dizer que o seguinte e o que estamos 
                                                                    a inserir */
    Lst->tail = aux; /* o ultimo elemento e o que foi inserido */

    if (Lst->head == NULL) /* se a fila nao tiver nenhum elemento, e  (...)*/
        Lst->head = aux;                          /* (...) esse o primeiro */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao de procura - procura um elemento numa fila */
void * FILAfind(fila Lst, void * v)
{
    node aux_b, aux_e; /* elementos avaliados - procura */

    if (!Lst->head || !Lst->tail) 
        return NULL; /* se nao houver que procurar nao se encontra */
    
    aux_b = Lst->head; /* comeca na cabeca -> andar para a frente */
    aux_e = Lst->tail; /* comeca na cauda -> andar para tras */

    while (aux_b && aux_e) /* enquanto ambos apontarem para alguma coisa */
    {
        if (aux_b->elem == v) /* se encontrar o elemento devolve-o */
            return aux_b;
        else if (aux_e->elem == v) /* se o encontrar mas indo pela cauda tambem devolve */
            return aux_e;
        /* se nao, anda para a frente com o aux_b e para tras com o aux_e */
        aux_b = aux_b->next;
        aux_e = aux_e->prev;
    }
    return NULL; /* se chegar aqui nao encontrou */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao de remocao - remove um elemento de uma fila */
void FILAremove(fila Lst, void * v)
{
    node aux; /* elemento a remover */

    if (!Lst->head) return; /* se nao houver elementos para eliminar (...)
                                                    (...)  nao faz nada */
    aux = FILAfind(Lst, v); /* encontra o elemento */

    /* e atualiza quem e afetado pela sua remocao -> os vizinhos */
    
    if (aux->prev) /* se ele tiver um elemento anterior */
        aux->prev->next = aux->next; /* ele passa a agarrar o proximo */
    else /* se nao houver --> o que removemos e a cabeca */
        Lst->head = aux->next; /* entao ela passa a ser o seguinte */
            
    if (aux->next) /* se ele tiver um elemento seguinte */
        aux->next->prev = aux->prev; /* ele passa a agarrar o anterior */
    else /* se nao houver --> o que removemos e a cauda */
        Lst->tail = aux->prev; /* entao ela passa a ser o anterior */

    /* no fim, liberta a memoria referente ao no */
            
    free(aux); 
    return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

