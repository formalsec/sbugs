#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STOCK_MAX 10000    /*Numero maximo possivel de produtos em stock*/
#define ENCOMENDAS_MAX 500 /*Numero maximo possivel de encomendas*/
#define PESO_MAX 200       /*Peso maximo de uma encomenda*/

typedef struct Produto
{
    int id_produto;     /*ID da encomenda (numero no Stock)*/
    char descricao[63]; /*Nome do produto*/
    int preco;          /*Preco do produto em Stock*/
    int peso;           /*Peso por unidade do produto*/
    int quantidade;     /*Unidades do produto em Stock*/

} Produto;

typedef struct encomenda
{
    Produto prod[200]; /*Produtos na encomenda*/
    int id_encomenda;  /*ID da encomenda (numero na lista)*/
    int n_produtos;    /*Numero de produtos existentes atualmente na encomenda*/
    int peso;          /*Peso total da encomenda*/

} encomenda;
/*Funcao que cria uma nova encomenda sem nenhum produto*/
encomenda criaEncomenda(int id_encomenda)
{
    encomenda a;
    a.id_encomenda = id_encomenda;
    a.n_produtos = 0;
    a.peso = 0;
    printf("Nova encomenda %d.\n", id_encomenda);
    return a;
}
/*Funcao que adiciona uma certa quantidade de um produto a uma encomenda criada anteriormente*/
void adicionaEncomenda(Produto Stock[STOCK_MAX], encomenda Lista[ENCOMENDAS_MAX], int id_encomenda, int id_produto)
{
    int ide = 0, idp = 0, qtd = 0;
    int i, len, add = 0;
    Produto a;

    scanf("%d:%d:%d", &ide, &idp, &qtd);
    /*Diferentes casos em nao ? possivel adicionar o produto*/
    if (ide >= id_encomenda)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp >= id_produto)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (Stock[idp].quantidade < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if (Stock[idp].peso * qtd + Lista[ide].peso > PESO_MAX)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else
    {
        len = Lista[ide].n_produtos;
        /*Verifica se o produto ja esta na encomenda,
        se estiver apenas adiciona mais quantidade ao mesmo*/
        for (i = 0; i < len; i++)
        {
            a = Lista[ide].prod[i];
            if (a.id_produto == idp)
            {
                Lista[ide].prod[i].quantidade += qtd;
                Lista[ide].peso += Stock[idp].peso * qtd;
                Stock[idp].quantidade -= qtd;
                add = 1;
            }
        }
        /*Adiciona um novo produto a encomenda*/
        if (add == 0)
        {
            Lista[ide].prod[len] = Stock[idp];
            Lista[ide].prod[len].quantidade = qtd;
            Stock[idp].quantidade -= qtd;
            Lista[ide].peso += Stock[idp].peso * qtd;
            Lista[ide].n_produtos += 1;
        }
    }
}

/*Funcao que remove um certo produto de uma encomenda*/
void removeEncomenda(Produto Stock[STOCK_MAX], encomenda Lista[ENCOMENDAS_MAX], int id_encomenda, int id_produto)
{
    int ide, idp, i;
    Produto a, temp;

    scanf("%d:%d", &ide, &idp);

    if (ide >= id_encomenda)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp >= id_produto)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else
    {
        /*Quando encontra o produto para remover na encomenda, este ? trocado com o ultimo da lista ficando este no seu lugar*/
        /*De seguida decrementa-se o n_produtos em um de forma a este ultimo (o removido) nao ser contabilizado*/
        for (i = 0; i < Lista[ide].n_produtos; i++)
        {
            a = Lista[ide].prod[i];
            if (a.id_produto == idp)
            {
                Lista[ide].peso -= Lista[ide].prod[i].quantidade * Lista[ide].prod[i].peso;
                Stock[idp].quantidade += Lista[ide].prod[i].quantidade;
                temp = Lista[ide].prod[i];
                Lista[ide].prod[i] = Lista[ide].prod[Lista[ide].n_produtos - 1];
                Lista[ide].prod[Lista[ide].n_produtos - 1] = temp;
                Lista[ide].n_produtos -= 1;
            }
        }
    }
}
/* Funcao que vai introduzir um novo produto no sistema*/
Produto leProduto(int id_produto)
{
    Produto a;
    /*Meter todos os valores a zero de forma a evitar conflitos de memoria*/
    memset(a.descricao, 0, 63);
    a.preco = 0;
    a.peso = 0;
    a.quantidade = 0;
    a.id_produto = id_produto;

    scanf(" %[^:]s:", a.descricao);
    scanf(":%d:%d:%d", &a.preco, &a.peso, &a.quantidade);

    printf("Novo produto %d.\n", a.id_produto);

    return a;
}
/*Funcao que vai adicionar uma certa quantidade de um produto ja existente ao stock*/
void addStock(Produto Stock[STOCK_MAX], int id_produto)
{
    int idp = 0, qtd = 0; /*Id do produto e quantidade respetivamente*/

    scanf("%d:%d", &idp, &qtd);

    if (idp < id_produto)
        Stock[idp].quantidade += qtd;
    else
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
}
/*Funcao que remove stock de um produto existende*/
void removeStock(Produto Stock[STOCK_MAX], int id_produto)
{
    int idp, qtd;

    scanf("%d:%d", &idp, &qtd);

    if (idp >= id_produto)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if (Stock[idp].quantidade < qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    else
    {
        Stock[idp].quantidade -= qtd;
    }
}
/*Funcao que verifica o custo total de uma encomenda*/
void custoEncomenda(encomenda Lista[ENCOMENDAS_MAX], int id_encomenda)
{
    int i, custo = 0, ide;

    scanf("%d", &ide);

    if (ide >= id_encomenda)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else
    {
        for (i = 0; i < Lista[ide].n_produtos; i++)
        {
            custo += Lista[ide].prod[i].preco * Lista[ide].prod[i].quantidade;
        }
        printf("Custo da encomenda %d %d.\n", ide, custo);
    }
}
/*Funcao que permite alterar o preco de um produto em todo o sistema*/
void alteraPreco(Produto Stock[STOCK_MAX], encomenda Lista[ENCOMENDAS_MAX], int id_encomenda, int id_produto)
{
    int idp, novoPreco, i, e;

    scanf("%d:%d", &idp, &novoPreco);

    if (idp >= id_produto)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else
    {
        /*Alterar os precos dos produtos em Stock*/
        Stock[idp].preco = novoPreco;

        /*Alterar os precos dos produtos nas encomendas*/
        for (i = 0; i < id_encomenda; i++)
        {
            for (e = 0; e < Lista[i].n_produtos; e++)
            {
                if (Lista[i].prod[e].id_produto == idp)
                {
                    Lista[i].prod[e].preco = novoPreco;
                }
            }
        }
    }
}
/*Funcao que verifica a quantidade de um produto existente em uma encomenda*/
void produtoEncomenda(Produto Stock[STOCK_MAX], encomenda Lista[ENCOMENDAS_MAX], int id_encomenda, int id_produto)
{
    int ide, idp, i, encontrou = 0;

    scanf("%d:%d", &ide, &idp);

    if (ide >= id_encomenda)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if (idp >= id_produto)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else
    {
        for (i = 0; i < Lista[ide].n_produtos; i++)
        {
            if (Lista[ide].prod[i].id_produto == idp)
            {
                printf("%s %d.\n", Lista[ide].prod[i].descricao, Lista[ide].prod[i].quantidade);
                encontrou = 1;
            }
        }
        if (encontrou == 0)
        {
            printf("%s 0.\n", Stock[idp].descricao);
        }
    }
}
/*lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
void ocorreProduto(encomenda Lista[ENCOMENDAS_MAX], int id_encomenda, int id_produto)
{
    int idp, i, e, maior_ide = -1, qtd = 0;
    scanf("%d", &idp);
    if (idp >= id_produto)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else
    {
        for (i = 0; i < id_encomenda; i++)
        {
            for (e = 0; e < Lista[i].n_produtos; e++)
            {
                if (Lista[i].prod[e].id_produto == idp && Lista[i].prod[e].quantidade > qtd)
                {
                    qtd = Lista[i].prod[e].quantidade;
                    maior_ide = Lista[i].id_encomenda;
                }
            }
        }
        if (maior_ide >= 0)
            printf("Maximo produto %d %d %d.\n", idp, maior_ide, qtd);
    }
}
/*Algoritmo Merge Sort feito para ordenar uma lista de Produtos 
    por ordem de precos*/
void mergeStock(Produto arr[STOCK_MAX], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* Cria arrays temporarios */
    Produto L[STOCK_MAX], R[STOCK_MAX];

    /* Copia a informacao para os arrays temporarios L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Junta os diferentes arrays de volta em arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].preco <= R[j].preco)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copia os restantes elementos de L[], se existirem */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copia os restantes elementos de R[], se existirem */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l --> indice da esquerda r--> indice da direita */
void mergeSortStock(Produto arr[STOCK_MAX], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSortStock(arr, l, m);
        mergeSortStock(arr, m + 1, r);

        mergeStock(arr, l, m, r);
    }
}

/*Funcao que lista todos os produtos existentes em stock de forma ordenada pelo preco*/
void listStock(Produto Stock[STOCK_MAX], int id_produto)
{
    int i;
    Produto org[STOCK_MAX];
    /* Cria uma copia do Stock de forma a nao alterar o original */
    for (i = 0; i < id_produto; i++)
        org[i] = Stock[i];

    mergeSortStock(org, 0, id_produto - 1);

    printf("Produtos\n");
    for (i = 0; i < id_produto; i++)
    {
        printf("* ");
        printf("%s ", org[i].descricao);
        printf("%d ", org[i].preco);
        printf("%d\n", org[i].quantidade);
    }
}
/*Funcao que recebe duas strings e retorna 1 se a primeira for maior e 2 caso a segunda seja maior (tabela ASCII)*/
int maior(char um[20], char dois[20])
{
    int i, len, maior = 2; /*Inicializado a 2 para nao haver conflitos de memoria e para manter a ordem nos algoritmos de ordenacao*/

    if (strlen(um) > strlen(dois))
        len = strlen(dois);
    else
        len = strlen(um);

    for (i = 0; i < len; i++)
    {
        if (um[i] > dois[i])
        {
            maior = 1;
            break;
        }
        else if (um[i] < dois[i])
        {
            maior = 2;
            break;
        }
    }
    return maior;
}
/*Algoritmo Merge Sort feito para ordenar uma lista de Produtos 
    por odem alfab?tica*/
void mergeEncomenda(Produto arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* Cria arrays temporarios */
    Produto L[PESO_MAX], R[PESO_MAX];

    /* Copia a informacao para os arrays temporarios L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Junta os diferentes arrays de volta em arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (maior(L[i].descricao, R[j].descricao) == 2)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copia os restantes elementos de L[], se existirem */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copia os restantes elementos de R[], se existirem */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l --> indice da esquerda r--> indice da direita */
void mergeSortEncomenda(Produto arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSortEncomenda(arr, l, m);
        mergeSortEncomenda(arr, m + 1, r);

        mergeEncomenda(arr, l, m, r);
    }
}

/*Funcao que lista todos os produtos adicionados numa encomenda de forma alfabetica segundo a descricao*/
void listEncomenda(encomenda Lista[ENCOMENDAS_MAX], int id_encomenda)
{

    int ide, i;
    encomenda enc;
    scanf("%d", &ide);
    if (ide >= id_encomenda)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else
    {
        /* Cria uma copia da encomenda de forma a nao alterar a original */

        enc = Lista[ide]; /*enc -- encomenda para listar*/
        /*Ciclo que percorre os produtos da encomenda e ordena os mesmos usando Bubble Sort*/

        mergeSortEncomenda(enc.prod, 0, enc.n_produtos - 1);
        printf("Encomenda %d\n", ide);
        for (i = 0; i < enc.n_produtos; i++)
        {
            printf("* %s %d %d\n", enc.prod[i].descricao, enc.prod[i].preco, enc.prod[i].quantidade);
        }
    }
}
/* Func?o que ir? decidir o que fazer com a informa??o introduzida*/
/* Funciona como um menu*/
int menu(Produto Stock[STOCK_MAX], encomenda Lista[ENCOMENDAS_MAX], int id_produto, int id_encomenda)
{
    char opcao = ' ';

    while (opcao != 'x')
    {
        scanf("%c", &opcao); /*Sai do programa quando um 'x' for introduzido*/

        if (opcao == 'a') /*Adiciona novo produto ao stock*/
        {
            Stock[id_produto] = leProduto(id_produto);
            id_produto++;
        }
        else if (opcao == 'l') /*lista todos os produtos existentes no sistema por ordem crescente de pre?o*/
        {
            listStock(Stock, id_produto);
        }
        else if (opcao == 'q') /*Adiciona um certo numero de um produto ao stock*/
        {
            addStock(Stock, id_produto);
        }
        else if (opcao == 'N') /*Cria nova encomenda*/
        {
            Lista[id_encomenda] = criaEncomenda(id_encomenda);
            id_encomenda++;
        }
        else if (opcao == 'A') /*Adiciona um produto a uma encomenda*/
        {
            adicionaEncomenda(Stock, Lista, id_encomenda, id_produto);
        }
        else if (opcao == 'r') /*Remove uma certa quantia de stock de um produto*/
        {
            removeStock(Stock, id_produto);
        }
        else if (opcao == 'R') /*Remove um produto de uma encomenda*/
        {
            removeEncomenda(Stock, Lista, id_encomenda, id_produto);
        }
        else if (opcao == 'L') /*Lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
        {
            listEncomenda(Lista, id_encomenda);
        }
        else if (opcao == 'C') /*Calcula o preco total da encomenda*/
        {
            custoEncomenda(Lista, id_encomenda);
        }
        else if (opcao == 'p') /*Altera o pre?o de um produto no sistema*/
        {
            alteraPreco(Stock, Lista, id_encomenda, id_produto);
        }
        else if (opcao == 'E') /*lista a descricao e a quantidade de um produto em uma encomenda*/
        {
            produtoEncomenda(Stock, Lista, id_encomenda, id_produto);
        }
        else if (opcao == 'm') /*lista a descricao e a quantidade de um produto em uma encomenda*/
        {
            ocorreProduto(Lista, id_encomenda, id_produto);
        }
    }

    return 0;
}
/*Funcao inicial que apenas inicializa algumas variaveis e tabelas
que sao necessarias no decorrer do programa*/
int main()
{
    static Produto Stock[STOCK_MAX] = {0};
    static encomenda Lista[ENCOMENDAS_MAX] = {0};
    int id_produto = 0;
    int id_encomenda = 0;

    menu(Stock, Lista, id_produto, id_encomenda);
    return 0;
}