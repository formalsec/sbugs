#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * ***********************************************************
 * Implementação de uma fila com memória dinâmica
 * (FIFO) para armazenar inteiros
 * - Utilizada para algoritmo de busca BFS
 * ************************************************************
 **/
#define FILA_EMPTY -1
#define FILA_NOT_EMPTY 0

typedef struct fila_element
{
    int value;
    struct fila_element *next;
} Fila_Element;

typedef struct fila
{
    Fila_Element *first;
    Fila_Element *last;
} Fila;

Fila *new_fila()
{
    Fila *f = can_fail_malloc(sizeof(Fila));
    f->first = NULL;
    f->last = NULL;
    return f;
}

void free_fila_element(Fila_Element *fe)
{
    free(fe);
}

void free_fila(Fila *f)
{
    Fila_Element *fe, *aux;
    fe = f->first;
    while (fe)
    {
        aux = fe;
        fe = fe->next;
        free_fila_element(aux);
    }
    free(f);
}

int is_fila_empty(Fila *f)
{
    if (f->first)
        return FILA_NOT_EMPTY;
    else
        return FILA_EMPTY;
}

void enqueue_fila(Fila *f, int value)
{
    Fila_Element *fe = can_fail_malloc(sizeof(Fila_Element));
    fe->value = value;
    /*Primeiro a inserir*/
    if (!f->first)
        f->first = fe;
    else
        f->last->next = fe;
    fe->next = NULL;
    f->last = fe;
}

int dequeue_fila(Fila *f)
{
    Fila_Element *fe = f->first;
    int value;
    if (!fe) /*Fila vazia*/
        return FILA_EMPTY;
    if (!fe->next)
    { /* ultimo elemento da Fila*/
        f->last = NULL;
        f->first = NULL;
    }
    else
    { /* Mais que um elemento na fila*/
        f->first = fe->next;
    }
    value = fe->value;
    free_fila_element(fe);

    return value;
}

/**
 * **************************************************************************
 * Implementação de um grafo dirigido através de uma linkedList
 * Cada vértice implementado uma estrutura do tipo LinkedListDestinationNode
 * através do atributo id. Além do id a mesma estrutura guarda o limite da capacidade do vértice e o fluxo
 * utilizado no cálculo do fluxo máximo
 * *************************************************************************
 **/

typedef struct linked_list_destination_node
{
    int id;
    int limite;
    int fluxo;
    struct linked_list_destination_node *next;
} LinkedListDestinationNode;

typedef struct linked_list_base_node
{
    LinkedListDestinationNode *first;
} LinkedListBaseNode;

typedef struct grafo
{
    int dimension;
    LinkedListBaseNode *baseNodes;
} Grafo;

Grafo *new_grafo(int dimension)
{
    Grafo *g = can_fail_malloc(sizeof(Grafo));
    LinkedListBaseNode *bn;
    int i;
    g->dimension = dimension;
    g->baseNodes = can_fail_malloc(g->dimension * sizeof(LinkedListBaseNode));

    /*Inicia BaseNodes*/
    bn = g->baseNodes;

    for (i = 0; i < g->dimension; i++)
        (bn+i)->first = NULL;

    return g;
    
}

void free_grafo(Grafo *g)
{
    int i;
    LinkedListBaseNode *bn;
    LinkedListDestinationNode *dn, *tmp;
    bn = g->baseNodes;
    for (i = 0; i < g->dimension; i++)
    {
        dn = (bn + i)->first;
        while (dn)
        {
            tmp = dn;
            dn = tmp->next;
            free(tmp);
        }
    }
    free(g->baseNodes);
    free(g);
}

void add_node_grafo(Grafo *g, int from, int to, int limite)
{
    LinkedListDestinationNode *dn, *tmp, *prev;
    LinkedListBaseNode *bn = g->baseNodes;

    prev = NULL;
    tmp = (bn+from)->first;
    while (tmp)
    {
        if (tmp->id == to) /* já existe*/
            return;
        prev = tmp;
        tmp = tmp->next;
    }
    /*Não existe -> insere*/
    dn = can_fail_malloc(sizeof(LinkedListDestinationNode));
    dn->id = to;
    dn->limite = limite;
    dn->fluxo = 0; /* Os valores de fluxo iniciam a zero*/
    dn->next = NULL;
    if(prev)
        prev->next = dn;
    else
        (bn+from)->first=dn;
}

int get_fluxo_residual(Grafo *g, int from, int to)
{
    LinkedListBaseNode *bn = (g->baseNodes + from);
    LinkedListDestinationNode *dn = bn->first;
    while (dn)
    {
        if (dn->id == to)
            return dn->limite - dn->fluxo;
    }

    /*** Adicionar define do ERRO não existe nó ****/
    return -1;
}


/* Incrementa fluxo. Caso o nó não exista cria com Capacidade=fluxo=0 e depois incrementa*/
void node_increment_fluxo(Grafo *g, int from, int to, int incr)
{
    LinkedListBaseNode *bn = (g->baseNodes + from);
    LinkedListDestinationNode *dn = bn->first;
    while (dn)
    {
        if (dn->id == to)
        {
            dn->fluxo += incr;
            return;
        }
      
        dn=dn->next;
    }
}

LinkedListDestinationNode* get_first_destination_node(Grafo* g,int from){
    LinkedListBaseNode *bn = (g->baseNodes + from);
    return bn->first;
}

/*função criada para efeitos de testes e debug*/
void print_grafo(Grafo *g)
{
    int i;
    LinkedListBaseNode *bn = g->baseNodes;
    LinkedListDestinationNode *dn;
    printf("\n ******* PRINT GRAFO *******");
    for (i = 0; i < g->dimension; i++)
    {
        printf("\n[%d]  ",i);
        dn = (bn + i)->first;
        while (dn)
        {
            printf(" ->  {ID=%d | L= %d | F=%d} ", dn->id, dn->limite, dn->fluxo);
            dn = dn->next;
        }
    }
    printf("\n ******* FIM PRINT GRAFO *******\n");
}

/**********************************************************************************
 * Implementação da estrutura mapa, e respetivas funções, de acordo com o enunciado
 * do projeto.
 **********************************************************************************
 **/

typedef struct mapa
{
    int avenidas;
    int ruas;
    Grafo *representacao;
} Mapa;

/*Calcular Num. vertice a partir do num da rua e avenida*/
#define CRUZAMENTO_TO_VERTICE_IN(tot_av, av, r) av + tot_av *(r - 1);
#define CRUZAMENTO_TO_VERTICE_OUT(tot_av, tot_r, av, r) av + tot_av *(r - 1) + tot_av *tot_r;

Mapa *new_mapa(int avenidas, int ruas)
{
    Mapa *m = can_fail_malloc(sizeof(Mapa));
    m->avenidas = avenidas;
    m->ruas = ruas;
    /**
     *  Num Vertices engloba duplicação dos cruzamentos
     *  para inserir capacidade máxima em cada e mais dois
     *  vertices para SuperOrigem e SuperDestino
     **/
    m->representacao = new_grafo(2 * avenidas * ruas + 2);
    return m;
}

/**
 * Preenche mapa irá inserir as capacidade de fluxo na Matriz de Adjacência
 * - Primeiro faz o set de todas as ligações de e para os diversos cruzamentos (Vertices de 1 a N)
 * - Estabelece o fluxo entre o Super destino (Vértice N+1) 
 * - estabelece o fluxo entre a Super Fonte (vértice 0) com a casa dos cidadãos;
 * 
 **/
void preenche_mapa(Mapa *mapa, int s, int c)
{
    /*variáveis auxiliares*/
    int i, j, av, rua, from, to, in, out;

    /*esc - Posição escuadoro*/
    int esc = mapa->representacao->dimension - 1;
    /* fnt - Posição da fonte (Super Origem)*/
    int fnt = 0;

    /** 
     * Set inicial da matriz de adjancência:
     * - Estabelece as ligações entre cruzamentos distintos
     * - Estabelece um limite na capacidade de cada vertices
     **/

    for (i = 1; i <= mapa->avenidas; i++)
    {
        for (j = 1; j <= mapa->ruas; j++)
        {
            /* Set da capacidade do vértice*/
            out = from = CRUZAMENTO_TO_VERTICE_OUT(mapa->avenidas, mapa->ruas, i, j);
            in = CRUZAMENTO_TO_VERTICE_IN(mapa->avenidas, i, j);
            add_node_grafo(mapa->representacao, in, out, 1);
            add_node_grafo(mapa->representacao, out, in, 0);

            /*Ligações entre cruzamentos. É tb adicionado */
            /*Liga ao da esquerda*/
            if (i - 1 > 0)
            {
                to = CRUZAMENTO_TO_VERTICE_IN(mapa->avenidas, i - 1, j);
                add_node_grafo(mapa->representacao, from, to, 1);
                add_node_grafo(mapa->representacao, to, from, 0);
            }

            /* liga ao da direita*/
            if (i + 1 <= mapa->avenidas)
            {
                to = CRUZAMENTO_TO_VERTICE_IN(mapa->avenidas, i + 1, j);
                add_node_grafo(mapa->representacao, from, to, 1);
                add_node_grafo(mapa->representacao, to, from, 0);
            }

            /*Liga ao de cima*/
            if (j - 1 > 0)
            {
                to = CRUZAMENTO_TO_VERTICE_IN(mapa->avenidas, i, j - 1);
                add_node_grafo(mapa->representacao, from, to, 1);
                add_node_grafo(mapa->representacao, to, from, 0);
            }

            /*Liga ao de baixo*/
            if (j + 1 <= mapa->ruas)
            {
                to = CRUZAMENTO_TO_VERTICE_IN(mapa->avenidas, i, j + 1);
                add_node_grafo(mapa->representacao, from, to, 1);
                add_node_grafo(mapa->representacao, to, from, 0);
            }
        }
    }

    /* Lê posição de cada supermercado e cria um super Escuadoro*/
    for (i = 0; i < s; i++)
    {

        scanf("%d %d", &av, &rua);
        from = CRUZAMENTO_TO_VERTICE_OUT(mapa->avenidas, mapa->ruas, av, rua);
        add_node_grafo(mapa->representacao, from, esc, 1);
        add_node_grafo(mapa->representacao, esc, from, 0);
    }

    /* Lê posição de cada cidadão e cria uma super Origem*/
    for (i = 0; i < c; i++)
    {
        scanf("%d %d", &av, &rua);
        to = CRUZAMENTO_TO_VERTICE_IN(mapa->avenidas, av, rua);
        add_node_grafo(mapa->representacao, fnt, to, 1);
        add_node_grafo(mapa->representacao, to, fnt, 0);
    }
}

void free_mapa(Mapa *mapa)
{
    free_grafo(mapa->representacao);
    free(mapa);
}

/**
 * Algoritmo para cálculo de Fluxo máximo e funções auxiliares
 * 
 * 
 **/

/*
Implementação de um algoritmo bfs para pesquisa de um caminho 
aumentador de fluxo
*/
#define WHITE 0
#define GRAY 1
#define BLACK 2
/* Retorno da Função BFS*/
#define PATH_NOT_FOUND 0
#define PATH_FOUND 1
/*variaveis apoio bfs*/
Fila *fila;
int *visitados;
int bfs(Mapa *mapa, int *caminho, int from, int to)
{
    /*variáveis auxiliares*/
    int actual_node;
    LinkedListDestinationNode* dn=NULL;
    /* Inicializa array visitados*/
    memset(visitados, 0, mapa->representacao->dimension * sizeof(*visitados));
    /*for (i = 0; i < mapa->representacao->dimension; i++)
        visitados[i] = WHITE;*/

    /*enqueue origem*/
    enqueue_fila(fila, from);
    caminho[from] = -1;
    visitados[from] = GRAY;

    while (is_fila_empty(fila) == FILA_NOT_EMPTY)
    {
        actual_node = dequeue_fila(fila);
        visitados[actual_node] = BLACK;
        dn=get_first_destination_node(mapa->representacao,actual_node);
        
        while (dn)
        {
            if (visitados[dn->id] == WHITE && dn->limite - dn->fluxo > 0)
                {
                    enqueue_fila(fila, dn->id);
                    visitados[dn->id] = GRAY;
                    caminho[dn->id] = actual_node;
                }
            dn=dn->next;
        }
    }
    if (visitados[to] == BLACK)
        return PATH_FOUND;
    else
        return PATH_NOT_FOUND;
}

/**
 *  Implementação do Algoritmo de Ford-Fulkerson
 * 
 * 
 **/

int fluxo_maximo(Mapa *mapa)
{
    /*Iniciar array para guardar caminho*/
    int *caminho = can_fail_malloc(mapa->representacao->dimension * sizeof(int));
    int pos;
    int fluxo = 0;

    /*Enquanto houver um caminho aumentador*/
    while (bfs(mapa, caminho, 0, mapa->representacao->dimension - 1))
    {
        /*incrementa na matriz de fluxo o máximo fluxo possivel do caminho
        Neste caso será 1. Prejudicando a abstração (mas simplificando) aplica-se diretamente esse valor
        em vez de calcular o valor mínimo do fluxo (arestas) do caminho
        */
        fluxo++;
        pos = mapa->representacao->dimension - 1;
        do
        {
            node_increment_fluxo(mapa->representacao,caminho[pos],pos,1);
            node_increment_fluxo(mapa->representacao,pos,caminho[pos],-1);
            pos = caminho[pos];

        } while (pos != 0);
    }

    free(caminho);
    /* Não existem mais caminhos aumentadores de fluxo*/
    return fluxo;
}

/**
 * função main 
 * 
 **/
int main()
{
    Mapa *mapa;
    int avenidas, ruas;
    int s, c; /*c=cidadãos s=supermercados*/
    /*A ser usado na BFS*/
    fila = new_fila();

    /*Le num de avenidas e ruas e inicia o mapa*/
    scanf("%d %d\n", &avenidas, &ruas);
    mapa = new_mapa(avenidas, ruas);

    visitados = (int *)can_fail_malloc(mapa->representacao->dimension * sizeof(int));
    /*Lê numero de supermercados e cidadãos existentes no mapa*/
    scanf("%d %d\n", &s, &c);

    preenche_mapa(mapa, s, c);

    /*print_grafo(mapa->representacao);*/
    
    printf("%d\n", fluxo_maximo(mapa));
    free_fila(fila);
    free(visitados);
    free_mapa(mapa);
    return EXIT_SUCCESS;
}