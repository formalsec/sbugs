#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Abstracoes */
#define MAX_produto 10000
#define MAX_encomenda 500
#define MAX_char 63
#define MAX_peso 200
#define key(X) (P[X].price)
#define less(X, Y) (key(X) < key(Y))
#define KEY(X) (P[X].desc)
#define LESS(X, Y) (strcmp(KEY(X), KEY(Y)) < 0)
#define exch(X, Y) { int t = X; X = Y; Y = t;}

/* Estruturas */
typedef struct produto
    {
        char desc[MAX_char];    
        int price;
        int weight;
        int stock;
    } produto;                          

typedef struct encomenda
    {
        int stock[MAX_produto];     /* Vetor em que o indice corresponde ao id de um produto,
                                       e o seu valor ao stock presente na encomenda*/
        int weight;
        int verificap[MAX_produto]; /* Verifica se um produto ja se encontra na encomenda */
        int sortL[MAX_produto];     /* Vetor organizado no comando L */
        int contap;                 /* Contador para o vetor sortL */
    } encomenda;

/* Variaveis */
char c;                     /* Obtem o comando a ser realizado */
int ip = 0, ie = 0;         /* Conta produtos e conta encomendas, respetivamente */
int idp, ide, qtd;          /* Variaveis para produtos, encomendas e stock, respetivamente */
int price;                  /* Auxiliar para o comando p */
int total = 0;              /* Auxiliar para o comando C */
int maior = 0;                  /* Auxiliar para o comando m */
int i;                      /* Variavel utilizada nos ciclos for */
int sortl[MAX_produto];     /* Vetor organizado no comando l */
int aux[MAX_produto];       /* Vetor auxiliar do merge sort */

produto P[MAX_produto];     /* Vetor de produtos */
encomenda E[MAX_encomenda]; /* Vetor de encomendas */

/* Funcao auxiliar utilizada pelo mergesort para o comando l */
int ordena_l(int l, int r)
{
/* Verifica se os precos sao iguais */
    if (key(l) == key(r))
        return (l < r);      /* Devolve o que tiver o menor id */
    else
        return (less(l, r)); /* Senao, devolve o que tiver o menor preco */
}

/* Funcao auxiliar utilizada pelo mergesort para o comando L */
int ordena_L(int l, int r)
{
    return LESS(l, r);
}

/* Funcao do algoritmo de ordenacao mergesort
   que faz as comparacoes e ordena o vetor recebido*/
void merge(int a[], int l, int m, int r, int (*choose)(int, int))
{
    int i, j, k;
    for (i = m+1; i > l; i--)
        aux[i-1] = a[i-1];
    for (j = m; j < r; j++)
        aux[r+m-j] = a[j+1];
    for (k = l; k <= r; k++)
    /* A funcao auxiliar chamada por choose depende do comando utilizado */
        if (choose(aux[j], aux[i])) 
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
}

/* Funcao do algoritmo mergesort, que recebe o vetor a ordenar, os limites,
   e uma funcao auxiliar para ordenar segundo o comando l ou L
   aplica o metodo de dividir para conquistar dividindo o vetor em metades,
   e as metades nas suas metades, e assim sucessivamente */
void mergesort(int a[], int l, int r, int(*choose)(int, int)) 
{
    int m = (r+l)/2;
    if (r <= l)
        return;
    mergesort(a, l, m, choose);
    mergesort(a, m+1, r, choose);
    merge(a, l, m, r, choose);
}

/* Adiciona um novo produto ao sistema */
void a()
{
    scanf(" %[^:]:%d:%d:%d", P[ip].desc,
    &P[ip].price, &P[ip].weight, &P[ip].stock);
    printf("Novo produto %d.\n", ip);
    sortl[ip] = ip;
    ip++;
}

/* Adiciona stock a um produto no sistema */
void q()
{
    scanf("%d:%d", &idp, &qtd);
    if (idp < ip)
        P[idp].stock += qtd;
    else
        printf("Impossivel adicionar produto %d ao stock."
        " Produto inexistente.\n", idp);
}

/* Cria uma nova encomenda */
void N()
{
    printf("Nova encomenda %d.\n", ie);
    ie++;
}

/* Adiciona um produto a uma encomenda. Caso este ja exista
   adiciona stock a quantidade existente */
void A()
{
    scanf("%d:%d:%d", &ide, &idp, &qtd);
    if (ide < ie)
    {
        if (idp < ip)
        {
            if (qtd <= P[idp].stock)
            {
                if (E[ide].weight + qtd*P[idp].weight <= MAX_peso)
                {
                /* Verifica se o produto esta a ser adicionado pela primeira vez */
                    if (E[ide].verificap[idp] != 1)
                    {
                        E[ide].sortL[E[ide].contap] = idp;
                        E[ide].contap += 1;
                        E[ide].verificap[idp] = 1;
                    }
                    E[ide].stock[idp] += qtd;
                    E[ide].weight += qtd*P[idp].weight;
                    P[idp].stock -= qtd;
                }
                else
                    printf("Impossivel adicionar produto %d a encomenda %d."
                    " Peso da encomenda excede o maximo de 200.\n", idp, ide);
            }
            else
                printf("Impossivel adicionar produto %d a encomenda %d."
                " Quantidade em stock insuficiente.\n", idp, ide);
        }
        else
            printf("Impossivel adicionar produto %d a encomenda %d."
            " Produto inexistente.\n", idp, ide);
    }
    else
        printf("Impossivel adicionar produto %d a encomenda %d."
        " Encomenda inexistente.\n", idp, ide);
}

/* Remove stock a um produto no sistema */
void r()
{
    scanf("%d:%d", &idp, &qtd);
    if (idp < ip)
    {
        if (qtd <= P[idp].stock)
            P[idp].stock -= qtd;
        else
            printf("Impossivel remover %d unidades do produto %d do stock."
            " Quantidade insuficiente.\n", qtd, idp);
    }
    else
        printf("Impossivel remover stock do produto %d."
        " Produto inexistente.\n", idp);
}

/* Remove um produto de uma encomenda */
void R()
{
    scanf("%d:%d", &ide, &idp);
    if (ide < ie)
    {
        if (idp < ip)
        {
            P[idp].stock += E[ide].stock[idp];
            E[ide].weight -= E[ide].stock[idp]*P[idp].weight;
            E[ide].stock[idp] = 0;
        }
        else
            printf("Impossivel remover produto %d a encomenda %d."
            " Produto inexistente.\n", idp, ide);
    }
    else
        printf("Impossivel remover produto %d a encomenda %d."
        " Encomenda inexistente.\n", idp, ide);
}

/* Calcula o custo de uma encomenda */
void C()
{
    scanf("%d", &ide);
    if (ide < ie)
    {
    for (idp = 0; idp < ip; idp++)
        total += E[ide].stock[idp]*P[idp].price;
    printf("Custo da encomenda %d %d.\n", ide, total);
    total = 0;
    }   
    else
        printf("Impossivel calcular custo da encomenda %d."
        " Encomenda inexistente.\n", ide);
    
}

/* Altera o preco de um produto */
void p()
{
    scanf("%d:%d", &idp, &price);
    if (idp < ip)
        P[idp].price = price;
    else
        printf("Impossivel alterar preco do produto %d."
        " Produto inexistente.\n", idp);
}

/* Lista a descricao e a quantidade de um produto numa encomenda */
void e()
{
    scanf("%d:%d", &ide, &idp);
    if (ide < ie)
    {
        if (idp < ip)
            printf("%s %d.\n", P[idp].desc, E[ide].stock[idp]);
        else
            printf("Impossivel listar produto %d."
            " Produto inexistente.\n", idp);
    }
    else
        printf("Impossivel listar encomenda %d."
        " Encomenda inexistente.\n", ide);
}

/* Recebe um produto e lista o id da encomenda em que existe mais quantidade
   Caso haja duas ou mais encomendas, lista a encomenda de menor id */
void m()
{
    scanf("%d", &idp);
    if (idp < ip)
    {        
        maior = 0;
        for (i = 0; i < MAX_encomenda; i++)
        {
        /* Se alguma encomenda tiver mais stock que o valor de "maior" */
            if (E[i].stock[idp] > maior)
            {
                maior = E[i].stock[idp];    /* O valor e alterado */
                ide = i;                    /* A encomenda e guardada*/
            }
        }
        if (maior != 0)
            printf("Maximo produto %d %d %d.\n", idp, ide, maior);
    }
    else
        printf("Impossivel listar maximo do produto %d."
        " Produto inexistente.\n", idp);
}

/* Lista todos os produtos existentes por ordem crescente de preco
   Caso haja dois ou mais produtos com o mesmo preco, lista o de menor id primeiro */
void l()
{
/* Chama o algoritmo mergesort para organizar o vetor com o auxilio da funcao ordena_l */
    mergesort(sortl, 0, ip - 1, ordena_l);
    printf("Produtos\n");
    for (i = 0; i < ip; i++)
        printf("* %s %d %d\n", P[sortl[i]].desc,
        P[sortl[i]].price, P[sortl[i]].stock);
}

/* Lista todos os produtos de uma encomenda por ordem alfabetica */
void L()
{
    scanf("%d", &ide);
    if (ide < ie)
    {
    /* Chama o algoritmo mergesort para organizar o vetor com o auxilio da funcao ordena_L*/
        mergesort(E[ide].sortL, 0, E[ide].contap - 1, ordena_L);
        printf("Encomenda %d\n", ide);
        for (i = 0; i < E[ide].contap; i++)
        {
        /* Verifica se o produto ainda se encontra na encomenda */
            if (E[ide].stock[E[ide].sortL[i]] != 0)
                printf("* %s %d %d\n", P[E[ide].sortL[i]].desc,
                P[E[ide].sortL[i]].price, E[ide].stock[E[ide].sortL[i]]);
        }
    }
    else
        printf("Impossivel listar encomenda %d."
        " Encomenda inexistente.\n", ide);
}

/* Funcao main, fundamental em todos os programas em C */
int main()
{
/* Ciclo do... while... que recebe o comando, e encaminha para a funcao
   chamada, ate receber o comando x que termina o programa */
    do
    {
        c = getchar();
        switch (c)
        {
            case 'a':
                a();
                break;
            case 'q':
                q();
                break;
            case 'N':
                N();
                break;
            case 'A':
                A();
                break;
            case 'r':
                r();
                break;
            case 'R':
                R();
                break;
            case 'C':
                C();
                break;
            case 'p':
                p();
                break;
            case 'E':
                e();
                break;
            case 'm':
                m();
                break;
            case 'l':
                l();
                break;
            case 'L':
                L();
                break;
        }
    }   while (c != 'x');
    return 0;
}