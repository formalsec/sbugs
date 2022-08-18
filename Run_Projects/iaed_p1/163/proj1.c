#include <stdio.h>
#include <string.h>

/* constantes */
#define DESCRICAO 63
#define MAXPRODUTOS 10000
#define MAXENCOMENDAS 500
#define MAXWEIGHT 200

/* verificadores */
#define produto_inexistente(P) (idp <= P)
#define encomenda_inexistente(E) (ide <= E)
#define quantidade_insuficiente(P, QT) (produtos[P].s < QT)
#define peso_excedido(A) (A > MAXWEIGHT)

/* Auxiliares de ordenacao */
#define encomenda_sorted(E) (encomendas[E].p_ordenado)
#define key_int(A) (produtos[A].price)
#define less_price(A, B) (key_int(A) < key_int(B))
#define equal(A,B) (key_int(A) == key_int(B))
#define key_str(A) (produtos[A].d)
#define less_abc(A, B) (strcmp(key_str(A), key_str(B)) < 0)

/* Abstracao */
#define descricao(P) (produtos[P].d)
#define preco(P) (produtos[P].price)
#define peso(P) (produtos[P].w)
#define quantidade(P) (produtos[P].s)
#define peso_encomenda(E) (encomendas[E].peso)
#define num_produtos(E) (encomendas[E].num_p)
#define encomenda_ordenada(E) (encomendas[E].ordenado)
#define encomenda_porordem(E) (encomendas[E].p_ordenado)
#define encomenda_produtos(E,P) (encomendas[E].produtos[P])
#define jaesteve_encomenda(E,P) (encomendas[E].jaesteve[P])

/* estruturas */
typedef struct produto
{
    char d[DESCRICAO]; /* Descricao do produto */
    int price; /* preco do produto */
    int w; /* peso do produto */
    int s; /* stock do produto */
} produto;

typedef struct encomenda
{
    int peso; /* peso da encomenda */
    int num_p; /* numero de produtos */
    int ordenado; /* se estiver a um, nao ha necessidade de ordenar */
    int p_ordenado[MAXPRODUTOS]; /* lista dos indices ordendados dos produtos */
    int produtos[MAXPRODUTOS]; /* indice de produto -> quantidade na encomenda */
    int jaesteve[MAXPRODUTOS]; /* caso o indice esteja a 1, o produto esta ou ja esteve na encomenda */
} encomenda;


/* ---variaveis globais--- */
int idp = 0; /* indice do ultimo produto adicionado +1 */
int ide = 0; /* indice da ultima encomenda adicionada +1 */
produto produtos[MAXPRODUTOS]; /* lista de produtos */
encomenda encomendas[MAXENCOMENDAS]; /* lista de encomendas */
int pricesorted[MAXPRODUTOS] = {-1}; /* precos ordenados */
int aux[MAXPRODUTOS];  /* Auxiliar do merge */

/* variaveis de controlo */
int prod_alterado; /* se estiver a 1 e necessario ordenar os produtos */
int sorted; /* ultimo produto a ser ordenado */
int preco_alterado; /* se estiver a 1 o preco mudou */

/* ao longo do projeto sao utilizadas as seguintes variaveis genericas para input*/
/* ip -> indice de produto */
/* ie -> indice da encomenda */
/* qtd -> quantidade */

/* i -> utilizado para iteracoes */

/* ---funcoes---  */
/* operacoes de produtos */
void add_produto(); /* adiciona um produto ao sistema */
void add_stock(); /* adiciona uma quantidade de um produto ao stock */
void remove_stock(); /* remove stock a um produto */
void muda_preco(); /* muda o preco de um produto */
void lista_produtos(); /* lista os produtos por ordem de preco */

/* operacoes de encomendas */
void adiciona_p_encomenda(); /* adiciona um produto a uma encomenda */
void remove_p_encomenda(); /* remove um produto a uma encomenda */
void calcula_preco(); /* calcula o preco de uma encomenda */
void produto_encomenda(); /* retorna a descricao e quantidade de um produto numa encomenda */
void produto_mais_repetido(); /* retorna o produto mais repetido numa encomenda */
void lista_produtos_encomenda(); /* lista os produtos de uma encomenda por ordem alfabetica */

/* ordenacao */
void merge(int array[], int inicio, int meio, int fim, int (*compare)(int,int));
void mergesort(int a[], int left, int right, int (*compare)(int,int));
int compara_preco(int i1, int i2); /* avalia se o produto de indice i1 vem antes do i2 ao ordenar por preco */
int compara_str(int i1, int i2); /* verifica se o produto de indice i1 vem antes do i2 ao ordenar em ordem alfabetica */


/* -main- */
int main()
{
    char c;

    while ((c = getchar()) != 'x') /* recebe um char respetivo a um comando, enviando o programa para a funcao respetiva */
    {
        switch (c)
        {
            case 'a':
                add_produto();
                break;
            
            case 'q':
                add_stock();
                break;
            case 'N':
                printf("Nova encomenda %d.\n", ide);
                ide++;
                break;
            
            case 'A':
                adiciona_p_encomenda();
                break;

            case 'r':
                remove_stock();
                break;

            case 'R':
                remove_p_encomenda();
                break;

            case 'C':
                calcula_preco();
                break;

            case 'p':
                muda_preco();
                break;

            case 'E':
                produto_encomenda();
                break;

            case 'm':
                produto_mais_repetido();
                break;

            case 'l':
                lista_produtos();
                break;

            case 'L':
                lista_produtos_encomenda();
                break;

            default:
            break;
        }
    }
    return 0;
}


void add_produto()
{
    scanf(" %[^:]:%d:%d:%d",descricao(idp) ,&preco(idp), &peso(idp), &quantidade(idp));
    printf("Novo produto %d.\n", idp);
    pricesorted[idp] = idp; /* acrescenta a lista de ordenados*/
    prod_alterado = 1; /* necessario ordenar */
    idp ++;
}

void add_stock()
{
    int ip;
    int qtd;
    scanf("%d:%d",&ip, &qtd);
    if (produto_inexistente(ip))
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", ip);
    }
    else
    {
        quantidade(ip) += qtd;
    }
}

void remove_stock()
{
    int ip, qt;
    scanf(" %d:%d", &ip, &qt);
    if (produto_inexistente(ip))
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", ip);
    }
    else if (quantidade_insuficiente(ip,qt))
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qt, ip);
    }
    else
    {
        quantidade(ip) -= qt;
    }
}

void muda_preco()
{
    int ip, preco;
    scanf(" %d:%d", &ip, &preco);
    if (produto_inexistente(ip))
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", ip);
    }
    else
    {
        prod_alterado = 1;
        preco_alterado = 1;
        preco(ip) = preco;
    }
}

void lista_produtos()
{
    int i;
    if (prod_alterado) /* se houver alteracao nos protudos, ordena-os */
    {
        if (!sorted) /* se nunca tiver sido ordenado, faz mergesort completo */
        {
            mergesort(pricesorted, 0, idp-1, compara_preco);
            sorted = idp;
        }
        else if (preco_alterado) /* se houver alteracao de preco, faz mergesort completo */
        {
            mergesort(pricesorted,0, idp-1,compara_preco);
            sorted = idp;
        }
        else /* faz mergesort apenas dos novos produtos e faz merge dos novos com os antigos */
        {
            mergesort(pricesorted, sorted, idp-1 ,compara_preco);
            merge(pricesorted,0,sorted-1,idp-1, compara_preco);
            sorted = idp;
        }
        prod_alterado = 0;
        preco_alterado = 0;
    }
    printf("Produtos\n");
    for (i = 0; i!= idp; i++)
    {
        printf("* %s %d %d\n", descricao(pricesorted[i]), preco(pricesorted[i]), quantidade(pricesorted[i]));
    }
}


void adiciona_p_encomenda()
{
    int ie, ip, qtd;
    scanf(" %d:%d:%d",&ie, &ip, &qtd);
    if (encomenda_inexistente(ie))
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", ip, ie);
    }
    else if (produto_inexistente(ip))
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", ip, ie);
    }
    else if (quantidade_insuficiente(ip, qtd))
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", ip, ie);
    }
    else if (peso_excedido(peso_encomenda(ie) + peso(ip) * qtd))
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", ip, ie);
    }
    else
    {
        if (!jaesteve_encomenda(ie,ip)) /* se for a primeira vez que um produto esta numa encomenda, acrescenta-o a lista de ordenacao */
        {
            encomenda_porordem(ie)[num_produtos(ie)] = ip;
            encomenda_ordenada(ie) = 0;
            num_produtos(ie) += 1;
            jaesteve_encomenda(ie,ip) = 1;
        }
        encomenda_produtos(ie,ip) += qtd;
        peso_encomenda(ie) += (peso(ip) * qtd);
        quantidade(ip) -= qtd;
    }
}

void remove_p_encomenda()
{
    int ie, ip;
    scanf(" %d:%d", &ie, &ip);
    if (encomenda_inexistente(ie))
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", ip, ie);
    }
    else if (produto_inexistente(ip))
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", ip, ie);
    }
    else
    {
        peso_encomenda(ie) -= (encomenda_produtos(ie,ip) * peso(ip));
        quantidade(ip) += encomenda_produtos(ie,ip);
        encomenda_produtos(ie,ip) = 0;
    }
}

void calcula_preco()
{
    int ie;
    int i;
    int preco = 0;
    scanf(" %d", &ie);
    if (encomenda_inexistente(ie))
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ie);
    }
    else
    {
        for (i = 0; i != num_produtos(ie); i++)
        {
            preco += (encomenda_produtos(ie,encomenda_sorted(ie)[i]) * preco(encomenda_sorted(ie)[i]));
        }
        printf("Custo da encomenda %d %d.\n", ie, preco);
    }
}

void produto_encomenda()
{
    int ie, ip;
    scanf(" %d:%d", &ie, &ip);
    if (encomenda_inexistente(ie))
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ie);
    }
    else if (produto_inexistente(ip))
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", ip);
    }
    else
    {
        printf("%s %d.\n", descricao(ip), encomenda_produtos(ie, ip));
    }
}

void produto_mais_repetido()
{
    int ip;
    int ie;
    int iemaior;
    int mais = 0;
    scanf(" %d", &ip);
    if (produto_inexistente(ip))
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", ip);
    }
    else
    {
        for (ie = 0; ie != ide; ie++)
        {
            if (encomenda_produtos(ie, ip) > mais)
            {
                mais = encomenda_produtos(ie, ip);
                iemaior = ie;
            }
        }
        if (mais > 0)
        {
            printf("Maximo produto %d %d %d.\n", ip, iemaior, mais);
        }
    }
}

void lista_produtos_encomenda()
{
    int ie, i;
    scanf(" %d", &ie);
    if (encomenda_inexistente(ie))
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ie);
    }
    else
    {
        mergesort(encomenda_porordem(ie),0,num_produtos(ie)-1, compara_str); /* mergesort dos produtos da encomenda */
        encomenda_ordenada(ie) = 1; /* produtos dessa encomenda passam a estar organizados */
        printf("Encomenda %d\n", ie);
        for(i = 0; i!= num_produtos(ie); i++)
        {
            if (encomenda_produtos(ie,encomenda_porordem(ie)[i]) != 0) /* caso tenham stock, lista produtos ordenados */
            {
                printf("* %s %d %d\n",
                    descricao(encomenda_porordem(ie)[i]),
                    preco(encomenda_porordem(ie)[i]),
                    encomenda_produtos(ie,encomenda_porordem(ie)[i]));
            }
        }
    }   
}

void merge(int array[], int inicio, int meio, int fim, int (*compare)(int,int))
{
    int i, j, k;
    for (i = meio+1; i > inicio; i--)
    {
        aux[i-1] = array[i-1];
    }
    for (j = meio; j< fim; j++)
    {
        aux[fim+meio-j] = array[j+1];
    }
    for (k = inicio; k <= fim; k++)
    {
        if (compare(aux[j],aux[i]))
        {
            array[k] = aux[j--];
        }
        else
        {
            array[k] = aux[i++];
        }
    }
}

void mergesort(int a[], int left, int right, int (*compare)(int,int))
{
    int m = (right+left)/2;
    if (right <= left) return;
    mergesort(a, left, m, compare);
    mergesort(a, m+1, right, compare);
    merge(a, left, m, right, compare);
}

int compara_preco(int i1, int i2)
{
    return (less_price(i1,i2) || (equal(i1,i2) && i1 < i2));
}
int compara_str(int i1, int i2)
{
    return (less_abc(i1,i2));
}