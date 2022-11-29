#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "lista_jogos.h"


/* inicializa uma lista de jogos devolve o ponteiro para a lista ------------------------------- */
lista* inicializa_lista_jogos()
{
    /* aloca memoria para a estrutura lista */
    lista* lista_jogos = (lista*)can_fail_malloc(sizeof(lista));
    
    
    lista_jogos -> cabeca = NULL;
    lista_jogos -> ultimo = NULL;

    return lista_jogos;
}


/* adiciona um jogo no fim da lista ------------------------------------------------------------ */
void adiciona_jogo_lista(lista* lista_jogos, pJogo jogo)
{
    /* aloca memoria para um novo node */
    link_jogo link_novo = (link_jogo)can_fail_malloc(sizeof(struct node_jogo));
    
    /* faz com que o node aponte para o jogo */
    link_novo -> jogo = jogo;
    link_novo -> next = NULL;

    /* se a lista estiver vazia, a cabeca passa a ser o node novo */
    if (lista_jogos -> cabeca == NULL)
    {
        lista_jogos -> cabeca = link_novo;
        lista_jogos -> ultimo = link_novo;
    }
    /* se nao estiver vazia adiciona no fim */
    else 
    {
        lista_jogos -> ultimo -> next = link_novo;
        lista_jogos -> ultimo = link_novo;
    }
}


/* remove um jogo da lista e devolve o ponteiro para esse jogo --------------------------------- */
pJogo remove_jogo_lista(lista* lista_jogos, char* nome)
{
    pJogo jogo;
    link_jogo aux;
    link_jogo iterador = lista_jogos -> cabeca;
    
    
    /* verifica se o jogo eh o primeiro da lista */
    if (strcmp(obtem_nome_jogo(iterador -> jogo), nome) == 0)
    {
        /* a cabeca da lista pass a ser o segundo node */
        lista_jogos -> cabeca = iterador -> next;

        /* atribui 'a variavel jogo o ponteiro do jogo a ser removido */
        jogo = iterador -> jogo; 
        
        /* verifica se a lista tem apenas um elemento, 
        se tiver atualiza tambem o ultimo node da lista */
        if (lista_jogos -> ultimo -> jogo == jogo)
            lista_jogos -> ultimo = lista_jogos -> cabeca;

        /* liberta a memoria alocada 'a cabeca antiga */
        free(iterador);
    }
    else
    {
        /* percorre a lista ate' encontrar o node que aponta para o jogo, ou ate chegar ao fim */
        /* aux eh o node que esta' a seguir do iterador */
        for(aux = iterador -> next; iterador -> next!= NULL; iterador = aux, aux = iterador ->next)
        {
            /* compara o jogo do aux com o jogo a remover */
            if (strcmp(obtem_nome_jogo(aux -> jogo), nome) == 0)
            {
                
                /* se o jogo for o ultimo, atualiza o a variavel ultimo da lista */
                if (lista_jogos -> ultimo == aux)
                    lista_jogos -> ultimo = iterador;

                /* atribui 'a variavel jogo o ponteiro do jogo a ser removido */
                jogo = aux -> jogo;

                /* liga o node iterador com o que esta' depois do aux */ 
                iterador -> next = aux -> next;

                /* liberta a memoria alocada ao node que continha o jogo */ 
                free(aux);
                break;
            }
        }
    }

    /* devolve o jogo que foi removido */
    return jogo; 
}


/* escreve a informacao de todos os jogos da lista --------------------------------------------- */
void print_lista_jogos(lista *lista_jogos, unsigned int Num_Linha)
{
    link_jogo iterador; 

    /* percorre a lista e escreve a informacao de cada jogo */
    for (iterador = lista_jogos -> cabeca; iterador != NULL; iterador = iterador -> next)
    {
        print_jogo(iterador -> jogo, Num_Linha);        
    }

    return;
}

/* liberta a memoria da lista e dos jogos ------------------------------------------------------ */
void destroi_lista_jogos(lista *lista_jogos)
{
    link_jogo iterador;
    link_jogo aux;

    /* percorre a lista e liberta a memoria aloca aos jogos e aos nodes */
    for (iterador = lista_jogos -> cabeca; iterador != NULL; iterador = aux)
    {
        aux = iterador -> next;

        /* liberta a memoria alocada ao jogo */
        free_jogo(iterador -> jogo);

        /* liberta a memoria alocada ao node */
        free(iterador);
    }
    
    /* liberta a memoria alocada 'a estrutura lista */
    free(lista_jogos);
    
    return;
}