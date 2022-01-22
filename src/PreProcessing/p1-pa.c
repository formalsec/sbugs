#include <stdio.h>
#include <string.h>

#define MAXPRODS 1000
#define MAXENCOMENDAS 50
#define MAXPESO 200
#define MAXDESC 64

#define LESS(A, B) { (prods[A].preco) < (prods[B].preco) }
#define EXCH(A, B) { int t = A; A = B; B = t; }

/*Hardcode API functions to create sym vars*/
void* new_sym_var(unsigned int length){
    return NULL;
}


typedef struct produto{
    int preco, peso, qtd;
    char desc[MAXDESC];
}PRODUTO;

PRODUTO prods[MAXPRODS];
int prods_ordenados_preco[MAXPRODS];
int prods_ordenados_descricao[MAXPRODS];
int ordered = 1;
int n_prods = 0;
int encomendas[MAXENCOMENDAS][MAXPRODS];
int n_encomendas = 0;

void init(){
    int i,j;
    for(i = 0; i < n_prods; i++){
        prods[i].desc[0] = 0;
        prods[i].preco = 0;
        prods[i].peso = 0;
        prods[i].qtd = 0;
    }
    for(i=0; i < n_encomendas; i++)
        for(j=0; j < n_prods; j++)
            encomendas[i][j] = 0;
}

void print_prod(char desc[], int preco, int qtd){
    printf("* %s %d %d\n", desc, preco, qtd);
}

void my_sort(int a[], int l, int r, int (*f)(PRODUTO, PRODUTO, int, int))
{ 
    int i, j, done;
    for (i = l; i < r; i++){
        done=1;
        for (j = r; j > i; j--) 
            /* if ( LESS(a[j], a[j-1]) ){ */
            if ( f(prods[a[j]] , prods[a[j-1]], a[j], a[j-1]) ){  
                EXCH(a[j-1], a[j]);
                done=0;
            }
        if (done) break;
    }
}

int compara_precos(PRODUTO a, PRODUTO b, int ia, int ib){
    return (a.preco) < (b.preco) ||
            ((a.preco) == (b.preco) && (ia < ib));
}

int compara_descricoes(PRODUTO a, PRODUTO b, int ia, int ib){
    ia = 0;
    ib = ia;
    ia = ib;
    return strcmp(b.desc, a.desc) > 0;
}

int encomendas_produto(int idp){
    int ie, qtd = 0;
    for (ie = 0; ie < n_encomendas; ie++)
        qtd += encomendas[ie][idp];
    return qtd;
}

int peso_encomenda(int ide){
    int ip, peso = 0;
    for (ip = 0; ip < MAXPRODS; ip++)
        peso += encomendas[ide][ip] * prods[ip].peso;
    return peso;
}

long custo_encomenda(int ide){
    int ip;
    long custo = 0;

    for (ip = 0; ip < MAXPRODS; ip++)
        custo += encomendas[ide][ip] * prods[ip].preco;
    return custo;
}

void comando_a(){
    if (n_prods > 9999){
            puts("************* ERRO: passou os 10000 *************");
            /*return -1*/;
        }
    else{
        getchar();
        scanf(" %[^:]:%d:%d:%d", prods[n_prods].desc, &prods[n_prods].preco, &prods[n_prods].peso, &prods[n_prods].qtd);
        prods_ordenados_preco[n_prods] = n_prods;
        prods_ordenados_descricao[n_prods] = n_prods;
        ordered = 0;
        printf("Novo produto %d.\n", n_prods);
        n_prods++;
    }
}

void comando_q(){
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);
    if (idp >= n_prods)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else
        prods[idp].qtd += qtd;
}

void comando_N(){
/*
* __N__ - cria uma nova encomenda __@ToDo: associamos encomendas a pessoas?__
  * Formato de entrada: `N`
  * Formato de saída: `ide` representando o identificador da encomenda criada.
*/
    if (n_encomendas >= 500)
        puts("************* ERRO: passou os 500 *************");
    else{
        printf("Nova encomenda %d.\n", n_encomendas);
        n_encomendas++;
    }
    
}

void comando_A(){
/* * __A__ - adiciona um produto a uma encomenda. Se o produto já existir na encomenda, adiciona a nova quantidade à quantidade existente
  * Formato de entrada: `A ide:idp:qtd`
  * Formato de saída: NADA (excepto erro)
  * Erros:
    * `Impossivel adicionar produto <idp> a encomenda <ide>. Encomenda inexistente.` no caso de não existir uma encomenda criada com esse identificador
    * `Impossivel adicionar produto <idp> a encomenda <ide>. Produto inexistente.` no caso de não existir um produto em stock com esse identificador
    * `Impossivel adicionar produto <idp> a encomenda <ide>. Quantidade em stock insuficiente.` no caso de não existir stock suficiente desse produto para satisfazer a encomenda
    * `Impossivel adicionar produto <idp> a encomenda <ide>. Peso da encomenda excede o maximo de 200.` no caso de a adição desse produto exceder o peso máximo permitido por encomenda 
*/
    int ide, idp, qtd;
    scanf(" %d:%d:%d", &ide, &idp, &qtd);
    if (ide >= n_encomendas)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp >= n_prods)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if(encomendas_produto(idp) + qtd > prods[idp].qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if(peso_encomenda(ide) + qtd * prods[idp].peso > 200)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else
        encomendas[ide][idp] += qtd;
}

void comando_r(){
/* * __r__ - remove stock a um produto existente
  * Formato de entrada: `r idp:qtd`
  * Formato de saída: NADA (excepto erro)
  * Erros:
    * `Impossivel remover stock do produto <idp> do stock. Produto inexistente.` no caso de não existir um produto em stock com esse identificador
    * `Impossivel remover <qtd> unidades do produto <idp> do stock. Quantidade insuficiente.` no caso de a quantidade de stock restante após a remoção ser negativa ou ser insuficiente para satisfazer as encomendas existentes 
*/
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);
    if (idp >= n_prods)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if(encomendas_produto(idp) > prods[idp].qtd - qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    else
        prods[idp].qtd -= qtd;
}


void comando_R(){
/* * __R__ - remove um produto de uma encomenda
  * Formato de entrada: `A ide:idp`
  * Formato de saída: NADA (excepto erro)
  * Erros:
    * `Impossivel remover produto <idp> a encomenda <ide>. Encomenda inexistente.` no caso de não existir uma encomenda criada com esse identificador
    * `Impossivel remover o produto <idp> a encomenda <ide>. Produto inexistente.` se não existir o produto na encomenda
*/
    int ide, idp;
    scanf(" %d:%d", &ide, &idp);
    if (ide >= n_encomendas)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp >= n_prods)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else
        encomendas[ide][idp] = 0;
}


void comando_C(){
/* * __C__ - calcula o custo de uma encomenda
  * Formato de entrada: `C ide`
  * Formato de saída: `ide total` onde `total` é o valor total da encomenda
  * Erros:
    * `Impossivel calcular custo da encomenda <ide>. Encomenda inexistente.` no caso de não existir uma encomenda criada com esse identificador
*/
    int ide;
    scanf(" %d", &ide);
    if (ide >= n_encomendas)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else
        printf("Custo da encomenda %d %ld.\n", ide, custo_encomenda(ide));    
}


void comando_p(){
    int idp, preco;
    scanf(" %d:%d", &idp, &preco);
    if (idp >= n_prods)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else{
        prods[idp].preco = preco;
        ordered = 0;
    }
}

void comando_E(){
/*
* __E__ - lista a descrição e a quantidade de um produto numa encomenda
  * Formato de entrada: `E ide:idp`
  * Formato de saída: `<desc> <qtd>` onde `<desc>` é a descrição do produto `<idp>` e `<qtd>` é a quantidade desse produto na encomenda `<ide>`
  * Erros:
    * `Impossivel listar encomenda <ide>. Encomenda inexistente.` no caso de não existir nenhuma encomenda criada com esse identificador
    * `Impossivel listar produto <idp>. Produto inexistente.` no caso de não existir nenhum produto criado com esse identificador

*/
    int ide, idp;
    scanf(" %d:%d", &ide, &idp);

    if (ide >= n_encomendas)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if (idp >= n_prods)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else
        printf("%s %d.\n", prods[idp].desc, encomendas[ide][idp]);
}

void comando_m(){
/*
* __m__ - lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas nessa situação, deverá imprimir a encomenda de menor `id`.
  * Formato de entrada: `m idp`
  * Formato de saída:
    * `Maximo produto <idp> <ide> <qtd>.` onde `<ide>` é o número da encomenda em que `<idp>` ocorre mais vezes, sendo essa quantidade `<qtd>`
    * Não deverá listar nada caso o produto `<idp>` não ocorra em nenhuma encomenda, ou caso não haja encomendas
  * Erros:
    * `Impossivel listar maximo do produto <idp>. Produto inexistente.` no caso de não existir nenhum produto criado com esse identificador

*/
    int maxe = 0, ie, idp;
    scanf(" %d", &idp);

    if (idp >= n_prods)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else{
        for(ie = 0; ie < n_encomendas; ie++)
            if(encomendas[ie][idp] > encomendas[maxe][idp])
                maxe = ie;
        if (n_encomendas != 0 && encomendas[maxe][idp] > 0)
            printf("Maximo produto %d %d %d.\n", idp, maxe, encomendas[maxe][idp]);
    }
}

void comando_l(int a[]){
    int ni;
    if (!ordered)
        my_sort(a, 0, n_prods - 1, compara_precos);
    printf("Produtos\n");
    for(ni = 0; ni < n_prods; ni++)
        print_prod(prods[a[ni]].desc, prods[a[ni]].preco, prods[a[ni]].qtd - encomendas_produto(a[ni]));
}

void comando_L(int a[]){
    int ide, ni;
    scanf(" %d", &ide);
    if (ide >= n_encomendas)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else{
        if (!ordered)
            my_sort(a, 0, n_prods - 1, compara_descricoes);
        printf("Encomenda %d\n", ide);
        for(ni = 0; ni < n_prods; ni++)
            if (encomendas[ide][a[ni]] > 0)
                print_prod(prods[a[ni]].desc, prods[a[ni]].preco, encomendas[ide][a[ni]]);
        /* printf("* Total: %d\n", custo_encomenda(ide)); */
    }
}



int main(){
    int c;
    /* int idp, preco, peso, qtd;
    char desc[MAXDESC]; */

    init();

    while((c = getchar()) != EOF){
        switch (c)
        {
        case 'a':
            comando_a();
            break;
        case 'q':
            comando_q();
            break;
        case 'N':
            comando_N();
            break;
        case 'A':
            comando_A();
            break;
        case 'r':
            comando_r();
            break;
        case 'R':
            comando_R();
            break;
        case 'C':
            comando_C();
            break;
        case 'p':
            comando_p();
            break;
        case 'E':
            comando_E();
            break;
        case 'm':
            comando_m();
            break;
        /*
        case 'L':
            comando_L(prods_ordenados_descricao);
            break;
        case 'l':
            comando_l(prods_ordenados_preco);
            break;
        case 'z':
            comando_l(prods_ordenados_preco);
            break;*/
        case 'x':
            return 0;
        default:
            printf("Invalid command: %c", c);
            break;
        }
        getchar();
        break;
    }
    return 0;
}
