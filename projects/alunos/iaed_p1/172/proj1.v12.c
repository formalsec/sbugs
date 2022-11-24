#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>

#define VERDADEIRO 1
#define MAX_STR 62
#define MAX_PESO 200
#define DIM_P 9999
#define DIM_E 499
#define MSG_ERRO ""

/* tipo produto */
typedef struct
{
    char desc [MAX_STR];
    int preco, peso, stock;
} produto;


/* tipo encomenda */
typedef struct
{
    int produtos[MAX_PESO], quantidade[MAX_PESO], peso, contador;
} encomenda;

/* Funcoes==============================================================================================*/


/* junta duas partes ordenadas de um vetor--------------------------------------------------------------*/
void merge(const produto lista_p[DIM_P], int vetor_id[DIM_P], int l_inf, int m, int l_sup)
{
    int i, j, k;
    int aux[DIM_P]; /* vetor auxiliar para a ordenacao*/

    /* copia o id dos produtos para o vetor auxiliar */
    for (i = m+1; i > l_inf; i--)
    {
        aux[i - 1] = vetor_id[i - 1];
    }

    for (j = m; j < l_sup; j++)
    {
        aux[l_sup + m - j] = vetor_id[j + 1];
    }


    /* ordena o o vetor entre os limites */
    for (k = l_inf; k <= l_sup; k++)
    {
        if (lista_p[aux[j]].preco < lista_p[aux[i]].preco || i > m)
            vetor_id[k] = aux[j--];
        
        else
            vetor_id[k] = aux[i++];
    }

    return;
}

/* ordena produtos pelo preco usando mergesort ---------------------------------------------------------*/
void mergesort(const produto lista_p[DIM_P], int vetor_id[DIM_P], int l_inf, int l_sup)
{
    int meio; /* indice do meio a particao de um vetor */
    
    meio = (l_inf + l_sup)/2;

    if (l_sup <= l_inf)
        return;

    mergesort(lista_p, vetor_id, l_inf, meio);
    mergesort(lista_p, vetor_id, meio + 1, l_sup);

    merge (lista_p, vetor_id, l_inf, meio, l_sup);

    return;
}


/* troca dois inteiros de um vetor de posicao ----------------------------------------------------------*/
void troca_int(int vetor[], int i, int j)
{
    int aux; /* inteiro auxiliar */
  
    aux = vetor[j];
    vetor[j] = vetor[i];
    vetor[i] = aux;

    return;
}

/* particiona um vetor de produtos e devolve o indice que separa as particoes ---------------------------------------*/
int particao(const produto lista_p[DIM_P], encomenda lista_e[DIM_E], int ide, int l_inf, int l_sup)
{
    int i, j;
    
    i = l_inf - 1;
    j = l_sup;
    
    /* separa os produtos em dois grupos, */
    while (i < j)
    {
        /* compara as descricoes dos produto e do produto pivot */
        while (strcmp(lista_p[lista_e[ide].produtos[++i]].desc, lista_p[lista_e[ide].produtos[l_sup]].desc) < 0);
        while (strcmp(lista_p[lista_e[ide].produtos[l_sup]].desc, lista_p[lista_e[ide].produtos[--j]].desc) < 0)
        {
            if (j == l_inf)
                break;
        }

    
        if (i < j)
        {  
            troca_int(lista_e[ide].quantidade, i, j);
            troca_int(lista_e[ide].produtos, i, j);
        }
        
    }    

    troca_int(lista_e[ide].quantidade, i, l_sup);
    troca_int(lista_e[ide].produtos, i, l_sup);
        
    return i;
}

/* ordena os produtos de uma encomenda atraves de quicksort --------------------------------------------*/
void quicksort(const produto lista_p[DIM_P], encomenda lista_e[DIM_E], int ide, int l_inf, int  l_sup)
{
    int indice; /* indice do elemento que separa as particoes */

    if (l_sup <= l_inf)
        return;

    indice = particao(lista_p, lista_e, ide, l_inf, l_sup);

    quicksort(lista_p, lista_e, ide, l_inf, indice - 1);
    quicksort(lista_p, lista_e, ide, indice + 1, l_sup);

    return;
}


/* adiciona um novo produto ao sistema -----------------------------------------------------------------*/
void a_adiciona_produto(produto lista[DIM_P], int id)
{    
    /* le e atribui as caracteristicas de um produto */ 
    scanf(" %[^:]:%d:%d:%d", lista[id].desc, &lista[id].preco, &lista[id].peso, &lista[id].stock);

    printf("Novo produto %d.\n", id);

    return;
}

/* adiciona um produto a uma encomenda -----------------------------------------------------------------*/
void A_adiciona_encomenda(produto lista_p[DIM_P], encomenda lista_e[DIM_E], int num_p, int num_e)
{
    int i, ide, idp, qtd; /* ide/idp: identificadores de encomenda/produto; qtd: quantidade */
    
    scanf(" %d:%d:%d", &ide, &idp, &qtd);

    /* verifica possiveis erros */
    if (ide >= num_e)
    {
        /* MSG_ERRO = mensagem de erro comum a todos os erros */

        printf(MSG_ERRO);                       
        printf("Encomenda inexistente.\n");

        return;
    }
    else if (idp >= num_p)
    {
        printf(MSG_ERRO);
        printf("Produto inexistente.\n");

        return;
    }
    else if (lista_p[idp].stock < qtd )
    {
        printf(MSG_ERRO);
        printf("Quantidade em stock insuficiente.\n");

        return;
    }
    else if (lista_e[ide].peso + qtd * lista_p[idp].peso > MAX_PESO)
    {
        printf(MSG_ERRO);
        printf("Peso da encomenda excede o maximo de 200.\n");

        return;
    }
    
    /* atualiza o peso da encomenda e o stock do produto */
    lista_e[ide].peso += qtd * lista_p[idp].peso;
    lista_p[idp].stock -= qtd;

    /* se o produto estiver na encomenda aumenta a sua quantidade */
    for (i = 0; i < lista_e[ide].contador; i++)
    {
        if (lista_e[ide].produtos[i] == idp)
        {
            lista_e[ide].quantidade[i] += qtd;
            return;
        }
    }
    
    /* adiciona o produto 'a encomenda */
    lista_e[ide].produtos[i] = idp;
    lista_e[ide].contador++;
    lista_e[ide].quantidade[i] = qtd;

    return;
}

/* calcula o custo de uma encomenda --------------------------------------------------------------------*/
void C_custo(const produto lista_p[DIM_P], const encomenda lista_e[DIM_E], int num_e)
{
    int i, ide, custo; /* custo: custo a ser calculado da encomenda */

    custo = 0;

    scanf(" %d", &ide);

    /* verifica se a encomenda existe */
    if (ide >= num_e )
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    /* soma o custo de todos os produtos */
    for (i = 0; i < lista_e[ide].contador; i++)
    {
        custo += lista_e[ide].quantidade[i] * lista_p[lista_e[ide].produtos[i]].preco;
    }
    
    printf("Custo da encomenda %d %d.\n", ide, custo);

    return;
}

/* lista a descricao e quantidade de um produto numa encomenda -----------------------------------------*/
void E_lista_prod_enc(const produto lista_p[DIM_P], const encomenda lista_e[DIM_E], int num_p, int num_e)
{
    int i, idp, ide;

    scanf(" %d:%d", &ide, &idp);

    /* verifica se a encomenda e o produto existem */
    if (ide >= num_e)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }
    else if (idp >= num_p)
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
        return;
    }

    /* escreve a descricao do protudo */
    printf("%s ", lista_p[idp].desc);
    
    /* escreve a quantidade do produto na encomenda */
    for (i = 0; i < lista_e[ide].contador; i++)
    {
        if (lista_e[ide].produtos[i] == idp)
        {
            printf("%d.\n", lista_e[ide].quantidade[i]);
            return;
        }
    }
    printf("0.\n");

    return;
}

/* lista todos os produtos -----------------------------------------------------------------------------*/
void lista_produtos(const produto lista_p[DIM_P], const int vetor_id[DIM_P], int limite)
{
    int i;

    printf("Produtos\n");
    for (i = 0; i < limite; i++)
    {
        printf("* %s %d %d\n", lista_p[vetor_id[i]].desc, lista_p[vetor_id[i]].preco,
                               lista_p[vetor_id[i]].stock);
    }
    return;
}

/* lista todos os produtos de uma encomenda ------------------------------------------------------------*/
void lista_encomenda(const produto lista_p[DIM_P], const encomenda enc, int ide)
{
    int i;

    printf("Encomenda %d\n", ide);
    for (i = 0; i < enc.contador; i++)
    {          
        printf("* %s %d %d\n", lista_p[enc.produtos[i]].desc,
            lista_p[enc.produtos[i]].preco, enc.quantidade[i]);
    }

    return;
}

/*lista todos os produtos ordenados por preco ----------------------------------------------------------*/
void l_lista_produtos_ordenados(const produto lista_p[DIM_P], int limite)
{
    int  vetor_id[DIM_P]; /* vetor com os id's dos produtos */
    int i;

    /* copia e id de cada produto para o vetor */
    for (i = 0; i < limite; i++){
        vetor_id[i] = i;
    }

    mergesort(lista_p, vetor_id, 0, limite - 1);

    lista_produtos(lista_p, vetor_id, limite);
    return;
}

/* lista os produtos de uma encomenda por ordem alfabetica ---------------------------------------------*/
void L_lista_encomenda_ordenada(const produto lista_p[DIM_P], encomenda lista_e[DIM_E], int num_e)
{
    int ide;

    scanf(" %d", &ide);

    /* verifica se a encomenda existe */
    if (ide >= num_e)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
        
    quicksort(lista_p, lista_e, ide, 0, lista_e[ide].contador - 1);

    lista_encomenda(lista_p, lista_e[ide], ide);

    return;
}

/* lista o identificador da encomenda onde o produto ocorre mais vezes -------------------------------*/
void m_maximo(const encomenda lista_e[DIM_E], int num_p, int num_e)
{
    int i, j, idp;
    int id_max; /* id da encomenda onde o produto ocorre mais vezes */
    int max; /* quantidade do produto na encomenda onde ocorre mais vezes */

    max = 0;

    scanf(" %d", &idp);

    /* verifica se o produto existe */
    if (idp >= num_p)
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
        return;
    }

    /* percorre todas as encomendas, localiza o produto e compara com o maximo anterior */ 
    for (i = 0; i < num_e; i++)
    {
        for (j = 0; j < lista_e[i].contador; j++)
        {
            if (lista_e[i].produtos[j] == idp)
            {
                if (lista_e[i].quantidade[j] > max)
                {
                    max = lista_e[i].quantidade[j];
                    id_max = i;
                }
                break;
            }
        }
    }

    if (max != 0)
    {
        printf("Maximo produto %d %d %d.\n", idp, id_max, max);
    }

    return;
}

/* cria uma nova encomenda -----------------------------------------------------------------------------*/
void N_cria_encomenda(int  id)
{
    printf("Nova encomenda %d.\n",id);
    return;
}

/* altera preco de um produto --------------------------------------------------------------------------*/
void p_altera_preco(produto lista_p[DIM_P], int num_p)
{
    int idp;
    int novo_preco; /* novo preco do produto */

    scanf(" %d:%d", &idp, &novo_preco);

    /* verifica se o produto existe */
    if (idp >= num_p)
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
        return;
    }

    lista_p[idp].preco = novo_preco;
    
    return;
}

/* adiciona stock a um produto existente ---------------------------------------------------------------*/
void q_adiciona_stock(produto lista[DIM_P], int num_p)
{
    int idp, qtd;

    scanf(" %d:%d", &idp, &qtd);
    
    /* verifica se o produto existe */
    if (idp >= num_p)
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        return;
    }

    lista[idp].stock += qtd;

    return;
}

/*  remove stock a um produto existente ----------------------------------------------------------------*/
void r_remove_stock(produto lista_p[DIM_P], int num_p)
{
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);

    /* verifica se o produto existe em quantidade suficiente */
    if (idp >= num_p)
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }
    else if (qtd > lista_p[idp].stock)
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", 
                qtd, idp);
        return;
    }

    lista_p[idp].stock -= qtd;
    return;
}

/* remove um elemento de um vetor mantendo a ordem -----------------------------------------------------*/
void remove_elemento(int index,int vetor[],int limite)
{
    /* move todos os elementos apos o index para tras */
    for (; index < limite; index++)
    {
        vetor[index] = vetor[index + 1];
    }

    return;
}

/* remove um produto de uma encomenda ------------------------------------------------------------------*/
void R_remove_produto(produto lista_p[DIM_P], encomenda lista_e[DIM_E], int num_p,int num_e)
{
    int i, ide, idp;

    scanf(" %d:%d",&ide,&idp);

    /* verifica se a encomenda e o produto existem */
    if (ide >= num_e)
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if (idp >= num_p)
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }

    for (i = 0; i < lista_e[ide].contador;i++)
    {
        
        if (lista_e[ide].produtos[i] == idp)
        {
            /* aumenta o stock disponivel do produto */
            lista_p[idp].stock += lista_e[ide].quantidade[i];
            /* diminui o peso da encomenda */
            lista_e[ide].peso -= lista_e[ide].quantidade[i] * lista_p[idp].peso;

            /* remove o poduto */
            remove_elemento(i,lista_e[ide].produtos,--lista_e[ide].contador);
            remove_elemento(i,lista_e[ide].quantidade,lista_e[ide].contador);

            return;
        }
    }
    return;
}


/*                                  -------------------------------------- */
int main() 
{
    int contador_p; /* numero de produtos criados */
    int contador_e; /* numero de encomendas criadas */

    produto lista_p[DIM_P] = {0}; /* vetor de produtos */
    encomenda lista_e[DIM_E] = {0}; /* vetor de encomendas */

    char c; /* comando a ler */
    
    contador_p = 0;
    contador_e = 0;


    while (VERDADEIRO)
        switch (c = getchar())
        {
            case 'a': /* a descricao:preco:peso:qtd */
                a_adiciona_produto(lista_p, contador_p++); 
                break;
            case 'A': /* A ide:idp:qtd */
                A_adiciona_encomenda(lista_p, lista_e, contador_p, contador_e);
                break;
            case 'C': /* C ide */
                C_custo(lista_p, lista_e, contador_e);
                break;
            case 'E': /* E ide:idp */
                E_lista_prod_enc(lista_p, lista_e, contador_p, contador_e);
                break;
            case 'l': /* l */
                l_lista_produtos_ordenados(lista_p, contador_p);
                break;
            case 'L': /* L ide */
                L_lista_encomenda_ordenada(lista_p, lista_e, contador_e);
                break;
            case 'm': /* m idp */
                m_maximo(lista_e, contador_p, contador_e);
                break;
            case 'N': /* N */
                N_cria_encomenda(contador_e++);
                break;
            case 'p': /* p idp:preco */
                p_altera_preco(lista_p, contador_p);
                break;
            case 'q': /* q idp:qtd */
                q_adiciona_stock(lista_p, contador_p);
                break;
            case 'r': /* r idp:qtd */
                r_remove_stock(lista_p, contador_p);
                break;
            case 'R': /* R ide:idp */
                R_remove_produto(lista_p, lista_e, contador_p, contador_e);
                break;
            case 'x': /* x */
                return 0;
        }
    
}
