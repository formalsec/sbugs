#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "funcoes_cases.h"

/*funcao que adiciona um novo jogo*/
link_j letra_a(int num_linhas, link_j *primeiros_j, 
                link_e *primeiras_e, link_j lista_jogos, link_j *fim_lista)
{
        ptr_jogo x;
        link_e e1, e2;
        link_j x1, x2;
        char j1[MAX], eq1[MAX], eq2[MAX];
        char *ptr_j1, *ptr_eq1, *ptr_eq2;
        int score1, score2;
        x = NULL;

        scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", j1, eq1, eq2, &score1, &score2);


        if (procura_jogo(primeiros_j, j1) != NULL)
        {
            printf("%d Jogo existente.\n", num_linhas);
            return lista_jogos;
        }
        if ((procura_equipa(primeiras_e, eq1)) == NULL)
        {
            printf("%d Equipa inexistente.\n", num_linhas);
            return lista_jogos;
        }
        if ((procura_equipa(primeiras_e, eq2)) == NULL )
        {   
            printf("%d Equipa inexistente.\n", num_linhas);
            return lista_jogos;
        }

        ptr_j1 = (char*)can_fail_malloc(sizeof(char)*(strlen(j1)+1));
        strcpy(ptr_j1, j1);

        ptr_eq1 = (char*)can_fail_malloc(sizeof(char)*(strlen(eq1)+1));
        strcpy(ptr_eq1, eq1);

        ptr_eq2 = (char*)can_fail_malloc(sizeof(char)*(strlen(eq2)+1));
        strcpy(ptr_eq2, eq2);

        if (score1 > score2)
        {
            e1 = procura_equipa(primeiras_e, eq1);
            e1->equipa->vitorias++;
        }
        if (score1 < score2)
        {
            e2 = procura_equipa(primeiras_e, eq2);
            e2->equipa->vitorias++;
        }

        x = novo_jogo(ptr_j1, ptr_eq1, ptr_eq2, score1, score2);
        x1 = (link_j)can_fail_malloc(sizeof(struct no_jogos));
        x2 = (link_j)can_fail_malloc(sizeof(struct no_jogos));

        x1->jogo= x;
        x1->proximo = NULL;
        
        x2->jogo = x;
        x2->proximo= NULL;
        *fim_lista = insere_fim_j(*fim_lista, x1);
        insere_jogo(primeiros_j, x2);
        if (lista_jogos == NULL)
            lista_jogos = *fim_lista;
        return lista_jogos;
}

/*funcao que adiciona uma nova equipa*/
link_e letra_A (int num_linhas, link_e *primeiras_e, link_e lista_equipas)
{
    char eq1[MAX];
    char *ptr_eq1;
    ptr_equipas y;
    link_e y1, y2;

    scanf(" %[^:\n]", eq1);

    if (procura_equipa(primeiras_e, eq1) != NULL)
    {   
        printf("%d Equipa existente.\n", num_linhas);
        return lista_equipas;
    }

    ptr_eq1 = (char*)can_fail_malloc(sizeof(char)*(strlen(eq1)+1));
    strcpy(ptr_eq1, eq1);
    
    y = nova_equipa(ptr_eq1, 0);
    y1 = (link_e)can_fail_malloc(sizeof(struct no_equipas));
    y2 = (link_e)can_fail_malloc(sizeof(struct no_equipas));

    y1->equipa = y;
    y1->proximo = NULL;

    y2->equipa = y;
    y2->proximo = NULL;

    lista_equipas = insere_alfabetica(lista_equipas, y1);
    insere_equipa(primeiras_e, y2);

    return lista_equipas;
}

/*funcao que imprime todos os jogos pela ordem em que foram introduzidos*/
int letra_l(int num_linhas, link_j lista_jogos)
{
    link_j x;
    if (lista_jogos != NULL)
    {
        for(x = lista_jogos; x != NULL; x = x->proximo)
            printf("%d %s %s %s %d %d\n", num_linhas, x->jogo->nome, 
                x->jogo->equipa1, x->jogo->equipa2, x->jogo->score1, x->jogo->score2);
    }
    return 0;
}

/*funcao que procura um jogo com o nome passado como input*/
int letra_p(int num_linhas, link_j *primeiros_j)
{
    char j1[MAX];
    link_j x;

    scanf(" %[^:\n]", j1);

    x = procura_jogo(primeiros_j, j1);
    if (x == NULL)
    {
        printf("%d Jogo inexistente.\n", num_linhas);
        return 0;
    }

    printf("%d %s %s %s %d %d\n", num_linhas, j1, 
        x->jogo->equipa1, x->jogo->equipa2, x->jogo->score1, x->jogo->score2);

    return 0;
}

/*funcao que procura uma equipa com o nome passado como input*/
int letra_P (int num_linhas, link_e *primeiras_e)
{
    char eq1[MAX];
    link_e e1;

    scanf(" %[^:\n]", eq1);

    if ((procura_equipa(primeiras_e, eq1)) == NULL)
    {
        printf("%d Equipa inexistente.\n", num_linhas);
        return 0;
    }

    e1 = procura_equipa(primeiras_e, eq1);
    printf("%d %s %d\n", num_linhas, e1->equipa->nome, e1->equipa->vitorias);

    return 0;
}

/*funcao que apaga o jogo cujo nume eh passado como input*/
link_j letra_r(int num_linhas, link_j *primeiros_j, link_e *primeiras_e, 
                    link_j lista_jogos, link_j *fim_lista)
{
    char j1[MAX];
    link_e e1, e2;
    link_j x;
    x = NULL;

    scanf(" %[^:\n]", j1);

    x = procura_jogo(primeiros_j, j1);

    if (x == NULL)
    {
        printf("%d Jogo inexistente.\n", num_linhas);
        return lista_jogos;
    }
    
    e1 = procura_equipa(primeiras_e, x->jogo->equipa1);
    e2 = procura_equipa(primeiras_e, x->jogo->equipa2);

    if (x->jogo->score1 > x->jogo->score2)
        e1->equipa->vitorias--;
    if (x->jogo->score1 < x->jogo->score2)
        e2->equipa->vitorias--;

    lista_jogos = apaga_j(primeiros_j, lista_jogos, j1, fim_lista);
    
    return lista_jogos;
}

/*funcao que altera o resultado de um jogo*/
int letra_s(int num_linhas, link_j *primeiros_j, link_e *primeiras_e)
{
    int score1, score2;
    char j1[MAX];
    link_j x;
    link_e e1, e2;
    x = NULL;

    scanf(" %[^:\n]:%d:%d", j1, &score1, &score2);

    x = procura_jogo(primeiros_j, j1);
    if (x == NULL)
    {
        printf("%d Jogo inexistente.\n", num_linhas);
        return 0;
    }

    e1 = procura_equipa(primeiras_e, x->jogo->equipa1);
    e2 = procura_equipa(primeiras_e, x->jogo->equipa2);

    if (x->jogo->score1 > x->jogo->score2)
    {
        if (score1 == score2)
            e1->equipa->vitorias--;
        if (score1 < score2)
        {
            e1->equipa->vitorias--;
            e2->equipa->vitorias++;
        }
    }

    if (x->jogo->score1 < x->jogo->score2)
    {
        if (score1 == score2)
            e2->equipa->vitorias--;
        if (score1 > score2)
        {
            e2->equipa->vitorias--;
            e1->equipa->vitorias++;
        }
    }
    if (x->jogo->score1 == x->jogo->score2)
    {
        if (score1 > score2)
            e1->equipa->vitorias++;
        if (score1 < score2)
            e2->equipa->vitorias++;
    }
    
    x->jogo->score1 = score1;
    x->jogo->score2 = score2;
    return 0;
}

/*funcao que imprime as equipas que venceram mais jogos*/
int letra_g(int num_linhas, link_e lista_equipas)
{
    int melhor_score;
    link_e e1;

    melhor_score = 0;

    if (lista_equipas == NULL)
        return 0;

    for(e1 = lista_equipas; e1 != NULL; e1 = e1->proximo)
    {
        if (e1->equipa->vitorias >= melhor_score)
            melhor_score = e1->equipa->vitorias;
    }

    printf("%d Melhores %d\n", num_linhas, melhor_score);

    for(e1 = lista_equipas; e1 != NULL; e1 = e1->proximo)
    {
        if (e1->equipa->vitorias == melhor_score)
            printf("%d * %s\n", num_linhas, e1->equipa->nome);
    }
    return 0;
}

int frees_projeto(link_j*primeiros_j, link_e*primeiras_e, link_j lista_jogos, link_e lista_equipas)
{
    int w;
    link_e m, anterior_e;
    link_j k, anterior_j;
    
    w = 0;
    m = NULL, anterior_e = NULL, k = NULL, anterior_j = NULL;

    if (lista_equipas != NULL) /*dar free ao nome das equipas e ao ponteiro*/
    {
        m = lista_equipas;
        while (m != NULL)
        {
            anterior_e = m;
            m = m->proximo;
            FreeNome_e(anterior_e);
            free(anterior_e);

        }
    }

    if (lista_jogos != NULL) /* dar free ao nome das equipas e ao ponteiro */
    {
        k = lista_jogos;
        while (k != NULL)
        {
            anterior_j = k;
            k = k->proximo;
            FreeNomes_j(anterior_j);
            free(anterior_j);
        }
    }

    for(w = 0; w < SIZE; w++) /*dar free a hashtable dos jogos e aos ponteiros respetivos*/
    {
        k = primeiros_j[w];
        while (k != NULL)
        {
            anterior_j = k;
            k = k->proximo;
            free(anterior_j); 
        }
    }

    free(primeiros_j);

    for(w = 0; w < SIZE; w++) /*dar free a hashtable das equipas e aos ponteiros respetivos*/
    {
        m = primeiras_e[w];
        while (m != NULL)
        {
            anterior_e = m;
            m = m->proximo;
            free(anterior_e); 
        }
    }

    free(primeiras_e);
    
    return 0;
}
