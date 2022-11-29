#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define DESC_LENGHT 63
#define MAX_PROD 10000
#define MAX_ENCS 500
#define MAX_PESO_ENC 200

typedef struct produto
{
    char desc[DESC_LENGHT + 1];
    int preco;
    int peso;
    int qtd;
} produto;

typedef struct encomenda
{
    int prodc;
    int peso;
    int idp[MAX_PESO_ENC]; /* Porque no minimo um produto tem 1 unidade de peso */
    int qtd[MAX_PESO_ENC]; /* Porque no minimo um produto tem 1 unidade de peso */
} encomenda;

/* Variaveis para a escrita dos argumentos passados pelo user */
char comando, desc[DESC_LENGHT + 1];
int arg1, arg2, arg3;

int prodc = 0;              /* Contador de produtos */
produto produtos[MAX_PROD]; /* Array principal, que guarda os produtos e a sua quantidade em stock */

/* Array de idps ordenados por ordem crescente dos precos dos produtos,
so e ordenado cada vez que o utilizador usa o comando l */
int produtos_sorted_preco[MAX_PROD];

int sorted_preco_count; /* produtos_sorted_preco[] tem sempre os sorted_preco_count primeiros idps ordenados */

/* Array de idps ordenados pela descricao dos produtos, esta sempre 
ordenado e e atualizado sempre que um novo produto e adicionado ao sistema, uma vez que essa ordem nunca muda, so podem ser acrescentados mais produtos */
int produtos_sorted_desc[MAX_PROD];

encomenda encomendas[MAX_ENCS]; /* Array que guarda todas as encomendas */
int encc = 0;                   /* Contador de encomendas */

/* Comandos */
void adiciona_prod(char *desc, int preco, int peso, int qtd); /* a */
void altera_qtd_prd(int idp, int qtd);                        /* q e r */
void nova_encomenda();                                        /* N */
void adiciona_prod_enc(int ide, int idp, int qtd);            /* A */
void remove_prod_enc(int ide, int idp);                       /* R */
void obter_custo_enc(int ide);                                /* C */
void altera_preco_prd(int idp, int preco);                    /* p */
void list_prd_enc(int ide, int idp);                          /* E */
void maximo_produto(int idp);                                 /* m */
void list_produtos();                                         /* l */
void list_encomenda(int ide);                                 /* L */

/* Funcoes Auxiliares */
int linear_search(int arr[], int left, int right, int x);
void merge_prd_preco(int arr[], int l, int m, int r);
void mergeSort_prd_preco(int arr[], int l, int r);
int binarySearch(int arr[], int left, int right, int x);
int qtd_prd_enc(int ide, int idp);

int main()
{
    while (1)
    {
        comando = getchar();
        switch (comando)
        {
        case 'a':
            /* a descricao:preco:peso:qtd */
            scanf(" %[^:]:%d:%d:%d", desc, &arg1, &arg2, &arg3);
            adiciona_prod(desc, arg1, arg2, arg3);
            break;
        case 'q':
            /* q idp:qtd */
            scanf(" %d:%d", &arg1, &arg2);
            altera_qtd_prd(arg1, arg2);
            break;
        case 'N':
            /* N */
            nova_encomenda();
            break;
        case 'A':
            /* A ide:idp:qtd */
            scanf(" %d:%d:%d", &arg1, &arg2, &arg3);
            adiciona_prod_enc(arg1, arg2, arg3);
            break;
        case 'r':
            /* r idp:qtd */
            scanf(" %d:%d", &arg1, &arg2);
            altera_qtd_prd(arg1, -arg2);
            break;
        case 'R':
            /* R ide:idp */
            scanf(" %d:%d", &arg1, &arg2);
            remove_prod_enc(arg1, arg2);
            break;
        case 'C':
            /* C ide */
            scanf(" %d", &arg1);
            obter_custo_enc(arg1);
            break;
        case 'p':
            /* p idp:preco */
            scanf(" %d:%d", &arg1, &arg2);
            altera_preco_prd(arg1, arg2);
            break;
        case 'E':
            /* E ide:idp */
            scanf(" %d:%d", &arg1, &arg2);
            list_prd_enc(arg1, arg2);
            break;
        case 'm':
            /* m idp */
            scanf(" %d", &arg1);
            maximo_produto(arg1);
            break;
        case 'l':
            /* l */
            list_produtos();
            break;
        case 'L':
            /* L <ide> */
            scanf(" %d", &arg1);
            list_encomenda(arg1);
            break;
        case 'x':
            return 0;
        }
    }
}

/* Funcoes Principais */

/* Adiciona um novo produto ao sistema */
void adiciona_prod(char *desc, int preco, int peso, int qtd)
{
    int i = prodc;
    /* Inicializar o produto */
    strcpy(produtos[prodc].desc, desc);
    produtos[prodc].preco = preco;
    produtos[prodc].peso = peso;
    produtos[prodc].qtd = qtd;

    /* Adicionar nova entrada no final da tabela de idps ordenada por preco */
    produtos_sorted_preco[prodc] = prodc;

    /* Insertion na posicao certa da tabela de idps ordenada alfabeticamente */
    while (strcmp(desc, produtos[produtos_sorted_desc[i - 1]].desc) < 0 && i > 0)
    {
        produtos_sorted_desc[i] = produtos_sorted_desc[i - 1];
        i--;
    }
    produtos_sorted_desc[i] = prodc;

    printf("Novo produto %d.\n", prodc);
    prodc++;
    return;
}

/* Altera a quantidade de um produto no sistema */
void altera_qtd_prd(int idp, int qtd)
{
    /* Validacao de argumentos */
    if (idp >= prodc)
    {
        if (qtd > 0)
        {
            /* Caso idp invalido do comando q */
            printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        }
        else
        {
            /* Caso idp invalido do comando r */
            printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
            return;
        }
    }

    /* Caso de quantidade em stock insuficiente do comando r */
    if (qtd < 0 && -qtd > produtos[idp].qtd)
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", -qtd, idp);
        return;
    }

    produtos[idp].qtd += qtd;
    return;
}

/* Funcao que adiciona uma nova encomenda ao sistema */
void nova_encomenda()
{
    /* Inicializar os valores de peso de contagem de produtos a 0 */
    encomendas[encc].prodc = 0;
    encomendas[encc].peso = 0;

    printf("Nova encomenda %d.\n", encc);

    encc++;
    return;
}

/* Remove a quantidade de um produto ao sistema e adiciona-o a uma encomenda */
void adiciona_prod_enc(int ide, int idp, int qtd)
{
    int i;

    /* Validacao de argumentos */
    if (ide >= encc)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    else if (idp >= prodc)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    else if (produtos[idp].qtd < qtd)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }
    else if (encomendas[ide].peso + (qtd * produtos[idp].peso) > MAX_PESO_ENC)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %i.\n", idp, ide, MAX_PESO_ENC);
        return;
    }

    /* Procurar o produto dentro do array da encomenda */
    i = binarySearch(encomendas[ide].idp, 0, encomendas[ide].prodc - 1, idp);

    /* Remover a quantidade necessaria ao produto */
    altera_qtd_prd(idp, -qtd);

    /* Incrementar o peso total da encomenda */
    encomendas[ide].peso += qtd * produtos[idp].peso;

    /* No caso do produto ainda nao estar na encomenda */
    if (i == -1)
    {
        /* Adicionar nova entrada na tabela de produtos de encomenda */
        encomendas[ide].idp[encomendas[ide].prodc] = idp;
        encomendas[ide].qtd[encomendas[ide].prodc] = qtd;

        /* Insertion na posicao correta da tabela da encomenda ordenada pelo idp */
        i = encomendas[ide].prodc;
        while ((encomendas[ide].idp[i - 1] > idp) && i > 0)
        {
            encomendas[ide].idp[i] = encomendas[ide].idp[i - 1];
            encomendas[ide].qtd[i] = encomendas[ide].qtd[i - 1];
            i--;
        }
        encomendas[ide].idp[i] = idp;
        encomendas[ide].qtd[i] = qtd;

        /* Incrementar o contador de produtos da encomenda */
        encomendas[ide].prodc++;
        return;
    }
    encomendas[ide].qtd[i] += qtd;
    return;
}

/* Remove um produto a uma encomenda */
void remove_prod_enc(int ide, int idp)
{
    int i, j;

    /* Validacao de argumentos */
    if (ide >= encc)
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    else if (idp >= prodc)
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }

    /* Procurar o indice desse produto dentro da encomenda */
    i = binarySearch(encomendas[ide].idp, 0, encomendas[ide].prodc - 1, idp);

    /* Caso a encomenda nao contenha esse produto */
    if (i != -1)
    {
        altera_qtd_prd(idp, encomendas[ide].qtd[i]);
        encomendas[ide].peso -= (encomendas[ide].qtd[i] * produtos[idp].peso);
        /* No caso em que o produto que queremos remover nao esta em ultimo lugar do array */
        /* Remover o produto da encomenda */
        for (j = i; j < encomendas[ide].prodc; j++)
        {
            encomendas[ide].idp[j] = encomendas[ide].idp[j + 1];
            encomendas[ide].qtd[j] = encomendas[ide].qtd[j + 1];
        }
        encomendas[ide].prodc--;
    }
    return;
}

/* Calcula o custo total de todos os produtos contidos numa encomenda */
void obter_custo_enc(int ide)
{
    int i, total = 0;

    /* Validacao dos argumentos */
    if (ide >= encc)
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    for (i = 0; i < encomendas[ide].prodc; i++)
    {
        total += (produtos[encomendas[ide].idp[i]].preco * encomendas[ide].qtd[i]);
    }

    printf("Custo da encomenda %d %d.\n", ide, total);
    return;
}

/* Altera o preco de um produto */
void altera_preco_prd(int idp, int preco)
{
    int i;

    /* Validacao dos argumentos */
    if (idp >= prodc)
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }

    /* Verificar se o produto esta na parte ordenada do array de idps ordenados por preco */
    i = linear_search(produtos_sorted_preco, 0, sorted_preco_count - 1, idp);

    if (i != -1)
    {
        /* Se estiver, temos que o tirar para fora da parte ordenada do array */
        while (i < sorted_preco_count)
        {
            produtos_sorted_preco[i] = produtos_sorted_preco[i + 1];
            i++;
        }
        sorted_preco_count--;
        /* Inserir o idp na primeira posicao nao ordenada do array */
        produtos_sorted_preco[sorted_preco_count] = idp;
    }

    produtos[idp].preco = preco;
    return;
}

/* Lista a descri??o e a quantidade de um produto numa encomenda */
void list_prd_enc(int ide, int idp)
{
    /* Validacao dos argumentos */
    if (ide >= encc)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    else if (idp >= prodc)
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }

    printf("%s %d.\n", produtos[idp].desc, qtd_prd_enc(ide, idp));
    return;
}

/* Lista o identificador da encomenda em que o produto dado ocorre mais vezes e essa quantidade */
void maximo_produto(int idp)
{
    int i, qtd, max_qtd = 0, max_ide;

    /* Validacao dos argumentos */
    if (idp >= prodc)
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }

    /* Passar por todas as encomendas, procurar o indice do produto e ir registando a maior qtd e o ide respetivo */
    for (i = 0; i < encc; i++)
    {
        qtd = qtd_prd_enc(i, idp);
        if (qtd > max_qtd)
        {
            max_qtd = qtd;
            max_ide = i;
        }
    }

    /* So da print se houver pelo menos uma encomenda que contenha o produto */
    if (max_qtd != 0)
    {
        printf("Maximo produto %d %d %d.\n", idp, max_ide, max_qtd);
    }

    return;
}

/* Lista todos os produtos no sistema por ordem crescente do preco */
void list_produtos()
{
    int i;
    /* Fazer sort da parte nao ordenada do vetor de idps ordenados por preco */
    mergeSort_prd_preco(produtos_sorted_preco, sorted_preco_count, prodc - 1);
    /* Fazer merge sort das partes ordenadas do vetor */
    merge_prd_preco(produtos_sorted_preco, 0, sorted_preco_count - 1, prodc - 1);
    /* O vetor agora esta todo ordenado */
    sorted_preco_count = prodc;
    printf("Produtos\n");
    for (i = 0; i < prodc; i++)
    {
        printf("* %s %d %d\n", produtos[produtos_sorted_preco[i]].desc, produtos[produtos_sorted_preco[i]].preco, produtos[produtos_sorted_preco[i]].qtd);
    }
    return;
}

/* Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
void list_encomenda(int ide)
{
    int i, printed_count = 0;

    /* Validacao dos argumentos */
    if (ide >= encc)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    printf("Encomenda %d\n", ide);

    for (i = 0; i < prodc && printed_count < encomendas[ide].prodc; i++)
    {
        if (binarySearch(encomendas[ide].idp, 0, encomendas[ide].prodc, produtos_sorted_desc[i]) != -1)
        {
            printf("* %s %d %d\n", produtos[produtos_sorted_desc[i]].desc, produtos[produtos_sorted_desc[i]].preco, qtd_prd_enc(ide, produtos_sorted_desc[i]));
            printed_count++;
        }
    }
    return;
}

/* -- Funcoes auxiliares  -- */

/* Procura linear de um elemento dentro de um array [left, ..., right] */
int linear_search(int arr[], int left, int right, int x)
{
    int i;
    for (i = left; i <= right; i++)
    {
        if (arr[i] == x)
        {
            return i;
        }
    }
    return -1;
}

/* Funcao para fazer merge de duas parted ordenadas do vetor idps, por ordem decrescente do preco que corresponde a cada idp */
void merge_prd_preco(int arr[], int left, int m, int right)
{
    int aux[MAX_PROD];
    int i, j, k;

    /* Copiar o lado esquerdo [l, ..., m] */
    for (i = m + 1; i > left; i--)
    {
        aux[i - 1] = arr[i - 1];
    }

    /* Copiar o lado esquerdo [m + 1, ..., r], mas ao contrario */
    for (j = m; j < right; j++)
    {
        aux[right + m - j] = arr[j + 1];
    }

    /* Ir comparando as duas pontas do array auxiliar e colocar em arr */
    for (k = left; k <= right; k++)
    {
        if (produtos[aux[j]].preco < produtos[aux[i]].preco)
        {
            arr[k] = aux[j--];
        }

        else if (produtos[aux[j]].preco > produtos[aux[i]].preco)
        {
            arr[k] = aux[i++];
        }

        /* Caso tenham o mesmo preco, ordenamos pelo menor idp */
        else if (aux[i] < aux[j])
        {
            arr[k] = aux[i++];
        }

        else
        {
            arr[k] = aux[j--];
        }
    }
    return;
}

/* Funcao para fazer merge sort de um array de idps por ordem decrescente do preco que corresponde a cada idp */
void mergeSort_prd_preco(int arr[], int left, int right)
{
    if (left < right)
    {
        int m = left + (right - left) / 2;
        /* Sort das duas metades */
        mergeSort_prd_preco(arr, left, m);
        mergeSort_prd_preco(arr, m + 1, right);
        /* Merge das duas metades para o mesmo vetor */
        merge_prd_preco(arr, left, m, right);
    }
    return;
}

/* Funcao para fazer procura binraria num array [left, ..., right],  */
int binarySearch(int arr[], int left, int right, int x)
{
    if (right >= left)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] < x)
            return binarySearch(arr, mid + 1, right, x);

        return binarySearch(arr, left, mid - 1, x);
    }
    /* Caso o elemento nao esteja no array */
    return -1;
}

/* Retorna a quantidade de produto dentro de uma encomenda */
int qtd_prd_enc(int ide, int idp)
{
    int i = binarySearch(encomendas[ide].idp, 0, encomendas[ide].prodc - 1, idp);
    if (i != -1)
    {
        return encomendas[ide].qtd[i];
    }
    return 0;
}