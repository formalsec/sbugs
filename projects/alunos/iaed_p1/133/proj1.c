#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_IDP 10000       /*quantidade maxima de produtos*/
#define MAX_IDE 500         /*quantidade maxima de encomendas*/
#define PESO_MAX 200        /*peso maximo de uma encomenda*/
#define EXISTE 1
#define NAO_EXISTE 0

typedef struct {
    char descricao[64];
    int preco;
    int peso;
    int stock;
    int idp;
} produto;

typedef struct {
    produto prod_encomenda[100];  /*tem os produtos da encomenda*/
    int peso;
    int ide;
    int num_prod;
} encomenda;


/*macros*/
#define key(A) (A)
#define less(A, B) (key(A) < key(B))


/*funcoes prototipo*/
void a(produto *a, int *n);
void q(produto arr[]);
void N(encomenda *a, int *n);
void A(produto arrp[], encomenda arre[]);
void r(produto arr[]);
void R(produto arrp[], encomenda arre[]);
void C(encomenda arr[]);
void p(produto arrp[], encomenda arre[], int n);
void E(produto arrp[], encomenda arre[]);
void m(produto arrp[], encomenda arre[], int n);
void l(produto arr[], int n);
void L(encomenda arr[]);


/*controla que funcao auxiliar e usada*/
int main()
{
    produto lista_produtos[MAX_IDP];        /*lista de produtos*/
    encomenda lista_encomendas[MAX_IDE];        /*lista de encomendas*/
    int num_prod = 0;       /*numero de produtos*/ 
    int num_enc = 0;        /*numero de encomendas*/
    int c;
    c = getchar();
    while (c != 'x') {      /*o input de x termina o programa*/
        if (c == 'a')
            a(&lista_produtos[num_prod], &num_prod);
        else if (c == 'q')
            q(lista_produtos);
        else if (c =='N')
            N(&lista_encomendas[num_enc], &num_enc);
        else if (c == 'A')
            A(lista_produtos, lista_encomendas);
        else if (c == 'r')
            r(lista_produtos);
        else if (c == 'R')
            R(lista_produtos, lista_encomendas);
        else if (c == 'C')
            C(lista_encomendas);
        else if (c == 'p')
            p(lista_produtos, lista_encomendas, num_enc);
        else if (c == 'E')
            E(lista_produtos, lista_encomendas);
        else if (c == 'm')
            m(lista_produtos, lista_encomendas, num_enc);
        else if (c == 'l')
            l(lista_produtos, num_prod);
        else if (c == 'L')
            L(lista_encomendas);
        c = getchar();
    }
    return 0;
}




/*funcao auxiliar do mergesort para inteiros*/
void merge1(produto a[], int left, int m, int right)
{
    produto aux[MAX_IDP];
    int i, j, k;

    for (i = m+1; i > left; i--)
        aux[i-1] = a[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = a[j+1];
    for (k = left; k <= right; k++) {
        if (less(aux[j].preco, aux[i].preco) || i > m || (aux[j].preco == aux[i].preco && aux[j].idp < aux[i].idp))
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
    }
}

/*funcao mergesort para inteiros*/
void mergesort1(produto a[], int left, int right)
{
    int m = (right+left)/2;

    if (right <= left)
        return;
    mergesort1(a, left, m);
    mergesort1(a, m+1, right);
    merge1(a, left, m, right);
}



/*funcao auxiliar do mergesort para strings*/
void merge2(produto a[], int left, int m, int right)
{
    produto aux[150];
    int i, j, k;

    for (i = m+1; i > left; i--)
        aux[i-1] = a[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = a[j+1];
    for (k = left; k <= right; k++) {
        if (strcmp(aux[j].descricao, aux[i].descricao) < 0 || i > m)
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
    }
}

/*funcao mergesort para strings*/
void mergesort2(produto a[], int left, int right)
{
    int m = (right+left)/2;

    if (right <= left)
        return;
    mergesort2(a, left, m);
    mergesort2(a, m+1, right);
    merge2(a, left, m, right);
}





/*cria um novo produto a partir dos valores lidos*/
void a(produto *a, int *n)
{
    int k = *n;
    scanf(" %[^:]:%d:%d:%d", a->descricao, &a->preco, &a->peso, &a->stock);
    a->idp = k;
    printf("Novo produto %d.\n", k);
    *n += 1;
}

/*adiciona stock a um certo produto*/
void q(produto arr[])
{
    int idp, qtd;

    scanf(" %d:%d", &idp, &qtd);
    if (arr[idp].idp != idp)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else
        arr[idp].stock += qtd;
}

/*cria uma nova encomenda*/
void N(encomenda *a, int *n)
{
    a->num_prod = 0;
    a->peso = 0;
    a->ide = *n;
    printf("Nova encomenda %d.\n", *n);
    *n += 1;
}

/*adciona um novo produto a uma encomenda e caso ele ja exista adiciona stock desse produto*/
void A(produto arrp[], encomenda arre[])
{
    int idp, ide, qtd, i, estado;
    estado = NAO_EXISTE;
    scanf(" %d:%d:%d", &ide, &idp, &qtd);
    if (arre[ide].ide == ide) {
        if (arrp[idp].idp == idp) {
            if (arrp[idp].stock >= qtd) {
                if (arre[ide].peso + (arrp[idp].peso * qtd) <= PESO_MAX) {
                    for (i = 0; i < arre[ide].num_prod; i++)
                        if (arre[ide].prod_encomenda[i].idp == idp && arre[ide].prod_encomenda[i].stock > 0) {
                            arre[ide].prod_encomenda[i].stock += qtd;
                            arre[ide].peso += (arrp[idp].peso * qtd);
                            estado = EXISTE;
                        }
                    if (estado == NAO_EXISTE) { /*este bloco so e executado se produto nao existir na encomenda*/
                        int j;

                        j = arre[ide].num_prod;

                        arre[ide].prod_encomenda[j].idp = arrp[idp].idp;
                        arre[ide].prod_encomenda[j].peso = arrp[idp].peso;
                        arre[ide].prod_encomenda[j].preco = arrp[idp].preco;
                        arre[ide].prod_encomenda[j].stock = qtd;
                        strcpy(arre[ide].prod_encomenda[j].descricao, arrp[idp].descricao);
                        arre[ide].num_prod += 1;
                        arre[ide].peso += (arrp[idp].peso * qtd);
                    }
                    arrp[idp].stock -= qtd;
                }
                else
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
            }
            else
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        }
        else
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/*remove stock de um produto*/
void r(produto arr[])
{
    int idp, qtd;

    scanf(" %d:%d", &idp, &qtd);
    if (arr[idp].idp == idp){
        if (arr[idp].stock - qtd >= 0)
            arr[idp].stock -= qtd;
        else
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
}

/*remove um produto de uma encomenda*/
void R(produto arrp[], encomenda arre[])
{
    int idp, ide, i;

    scanf(" %d:%d", &ide, &idp);
    if (arre[ide].ide == ide) {
        if (arrp[idp].idp == idp) {
            for (i = 0; i < arre[ide].num_prod; i++)
                if (arre[ide].prod_encomenda[i].idp == idp) {
                    arrp[idp].stock += arre[ide].prod_encomenda[i].stock;
                    arre[ide].peso -= (arre[ide].prod_encomenda[i].peso * arre[ide].prod_encomenda[i].stock);
                    arre[ide].prod_encomenda[i].stock = 0;
                    break;
                }
        }
        else
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/*calcula o custo de uma encomenda*/
void C(encomenda arr[])
{
    int ide, total = 0, i, preco, qtd;

    scanf(" %d", &ide);
    if (arr[ide].ide == ide) {   
        for (i = 0; i < arr[ide].num_prod; i++)
            if (arr[ide].prod_encomenda[i].stock > 0) {
                preco = arr[ide].prod_encomenda[i].preco;
                qtd = arr[ide].prod_encomenda[i].stock;
                total += (preco * qtd);
            }
        printf("Custo da encomenda %d %d.\n", ide, total);
    }
    else
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
}

/*altera o preco de um produto*/
void p(produto arrp[], encomenda arre[], int n)
{
    int idp, preco, i, j;

    scanf(" %d:%d", &idp, &preco);
    if (arrp[idp].idp == idp) {
        arrp[idp].preco = preco;
        for (i = 0; i < n; i++)
            for (j = 0; j < arre[i].num_prod; j++)
                if (arre[i].prod_encomenda[j].idp == idp) {
                    arre[i].prod_encomenda[j].preco = preco;
                    break;
                }
    }
    else
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}

/*lista o produto de uma encomenda e a sua quantidade*/
void E(produto arrp[], encomenda arre[])
{
    int idp, ide, i;

    scanf(" %d:%d", &ide, &idp);
    if (arre[ide].ide == ide) {
        if (arrp[idp].idp == idp) {
            for (i = 0; i < arre[ide].num_prod; i++)
                if (arre[ide].prod_encomenda[i].idp == idp) {
                    printf("%s %d.\n", arre[ide].prod_encomenda[i].descricao, arre[ide].prod_encomenda[i].stock);
                    break;
                }
        }
        else
            printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}

/*lista a encomenda com maior quantidade de um certo produto*/
void m(produto arrp[], encomenda arre[], int n)
{
    int idp, ide, i, j, num_max = 0;        /*num_max corresponde ao quantidade maxima de um certo produto encontrada numa qualquer encomenda*/

    scanf(" %d", &idp);
    if (arrp[idp].idp == idp) {
        for (i = 0; i < n; i++)
            for (j = 0; j < arre[ide].num_prod; j++)
                 if (arre[i].prod_encomenda[j].idp == idp) {
                    num_max = arre[i].prod_encomenda[j].stock;
                    ide = i;
                    break;
                }
        if (num_max > 0)
            printf("Maximo produto %d %d %d.\n", idp, ide, num_max);
        }
    else
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
}

/*ordena pelo preco e lista todos os produtos*/
void l(produto arr[], int n)
{
    int i;
    mergesort1(arr, 0, n - 1);
    printf("Produtos\n");
    for(i = 0; i < n; i++)
        printf("* %s %d %d\n", arr[i].descricao, arr[i].preco, arr[i].stock);  
}

/*ordena alfabeticamente e lista todos os produtos de uma encomenda*/
void L(encomenda arr[])
{
    int i, ide;

    scanf(" %d", &ide);

    if (arr[ide].ide == ide) {
        mergesort2(arr[ide].prod_encomenda, 0, arr[ide].num_prod - 1);
        printf("Encomenda %d\n", ide);
        for(i = 0; i < arr[ide].num_prod; i++)
            if (arr[ide].prod_encomenda[i].stock > 0)
                printf("* %s %d %d\n", arr[ide].prod_encomenda[i].descricao, arr[ide].prod_encomenda[i].preco, arr[ide].prod_encomenda[i].stock); 
    }
    else
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}