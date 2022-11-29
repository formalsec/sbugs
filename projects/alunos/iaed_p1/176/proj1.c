#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Creates a type of data called produtos to store all the created products. Each product has a descirpition,id,weight,price and stock.*/
struct Produtos{
    int id;
    char descricao[63];
    int preco;
    int peso;
    int stock;
}produtos[10000];

/* Creates a type of data called encomendas to store all the created orders. Each order has an id and weight also has a counter initialize that keeps track of the amount of products in an order.*/

struct Encomendas{
    int id;
    int counter;
    int peso;
    struct Produtos produtosEncomenda[10000];
}encomendas[500];

/* Two variables initialized that one is added everytime a produtct/order is created. */

int idP = 0;
int idE = 0;

/* Function a() creates a product with a description, weight, price, stock and an id starting at 0 that is incremented as new product are created */

void a(){
    int i;
    char descricao[63];
    int preco, peso, qtd;
    scanf(" %[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);

    produtos[idP].id = idP;
    strcpy(produtos[idP].descricao, descricao);
    produtos[idP].preco = preco;
    produtos[idP].peso = peso;
    produtos[idP].stock = qtd;

    for (i = 0; i < 500; i++){
        if (i < idE){
            encomendas[i].produtosEncomenda[encomendas[i].counter] = produtos[idP];
            encomendas[i].produtosEncomenda[encomendas[i].counter].stock = 0;
            encomendas[i].counter++;
        }
        else if (idP == 0){
            encomendas[i].counter = 0;
            encomendas[i].produtosEncomenda[encomendas[i].counter] = produtos[idP];
            encomendas[i].produtosEncomenda[encomendas[i].counter].stock = 0;
            encomendas[i].counter++;
        }
        else{
            encomendas[i].produtosEncomenda[encomendas[i].counter] = produtos[idP];
            encomendas[i].produtosEncomenda[encomendas[i].counter].stock = 0;
            encomendas[i].counter++;
        }
    }
    printf("Novo produto %d.\n", produtos[idP].id);
}

/* Function q() adds stock to a product. */

void q(){
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    if (idp >= idP){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        return;
    }
    produtos[idp].stock += qtd;
}

/* Function N() creates a new order. */

void N(){

    encomendas[idE].id = idE;
    encomendas[idE].peso = 0;
    if (idP == 0){
        encomendas[idE].counter = 0;
    }
    printf("Nova encomenda %d.\n", encomendas[idE].id);
}

/* Function A() adds a product to an order. */

void A(){
    int ide, idp, qtd;
    int i, pesoProduto;
    scanf("%d:%d:%d", &ide, &idp, &qtd);
    if (ide >= idE){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if (idp >= idP){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    if (produtos[idp].stock < qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }

    pesoProduto = produtos[idp].peso * qtd;

    if (encomendas[ide].peso + pesoProduto > 200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }

    for (i = 0; i < encomendas[ide].counter; i++){
        if (encomendas[ide].produtosEncomenda[i].id == idp){
            encomendas[ide].produtosEncomenda[i].stock += qtd;
            encomendas[ide].peso += pesoProduto;
            produtos[idp].stock -= qtd;
            return;
        }
    }
}

/* Function r() removes stock from a product. */

void r(){
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    if (idp >= idP){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }
    if (produtos[idp].stock - qtd < 0){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
    }
    produtos[idp].stock -= qtd;
}

/* Function R() removes a product from an error. */

void R(){
    int i;
    int ide, idp;
    scanf("%d:%d", &ide, &idp);
    if (ide >= idE){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if (idp >= idP){
        printf("Impossivel remover produto %d a encomenda%d. Produto inexistente.\n", idp, ide);
        return;
    }

    for (i = 0; i < encomendas[ide].counter; i++){
        if (encomendas[ide].produtosEncomenda[i].id == idp){
            produtos[idp].stock += encomendas[ide].produtosEncomenda[i].stock;
            encomendas[ide].produtosEncomenda[i].stock = 0;
            return;
        }
    }
}

/* Function C returns the total cost of an order. */

void C(){
    int ide;
    int i, total = 0;
    scanf("%d", &ide);
    if (ide >= idE){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    for(i = 0; i < encomendas[ide].counter; i++){
        total += encomendas[ide].produtosEncomenda[i].preco * encomendas[ide].produtosEncomenda[i].stock;
    }
    printf("Custo da encomenda %d %d.\n", ide, total);
}

/* Function p() changes a product's price */

void p(){
    int idp, preco;
    int i, j;
    scanf("%d:%d", &idp, &preco);
    if (idp >= idP){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }

    produtos[idp].preco = preco;

    for (i = 0; i < idE; i++){
        for (j = 0; j < encomendas[i].counter; j++){
            if (encomendas[i].produtosEncomenda[j].id == idp){
                encomendas[i].produtosEncomenda[j].preco = preco;
            }
        }
    }
}

/* Function E() lists a product and returns its description and quantity in an order. */

void E(){
    int ide, idp;
    int i;
    scanf("%d:%d", &ide, &idp);
    if (ide >= idE){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    if (idp >= idP){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }
    for (i = 0; i < encomendas[ide].counter; i++){
        if (encomendas[ide].produtosEncomenda[i].id == idp){
            printf("%s %d.\n", encomendas[ide].produtosEncomenda[i].descricao, encomendas[ide].produtosEncomenda[i].stock);
            return;
        }
    }
}

/* Function m() returns the order where a prodcut has it's most amount. */

void m(){
    int idp;
    int maiorQuantidade = 0, idEncomenda = 0, i, j, f= 0;
    scanf("%d", &idp);
    if (idp >= idP){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }
    for (i = 0; i < 500; i++){
        for (j = 0; j <= encomendas[i].counter; j++){
            if (encomendas[i].produtosEncomenda[j].id == idp){
                f = 1;
                if (encomendas[i].produtosEncomenda[j].stock > maiorQuantidade){
                    maiorQuantidade = encomendas[i].produtosEncomenda[j].stock;
                    idEncomenda = i;
                }
            }
        }
    }
    if (f == 0){
        return;
    }
    else{
        printf("Maximo produto %d %d %d.\n", idp, idEncomenda, maiorQuantidade);
    }
}

/* Function l() lists all products in ascending order of price. */

void l(){
    int i, j, a;
    struct Produtos *nProdutos = can_fail_malloc(sizeof(produtos)); /* Erro */
    struct Produtos tmp;
    for (a = 0; a < idP; a++){
        nProdutos[a] = produtos[a];
    }
    for (i = 0; i < idP; i++){
        for (j = 0; j < idP; j++){
            if (nProdutos[i].preco < nProdutos[j].preco){
                tmp = nProdutos[i];
                nProdutos[i] = nProdutos[j];
                nProdutos[j] =tmp;
            }
        }
    }
    printf("Produtos\n");
    for (i = 0; i < idP; i++){
        printf("* %s %d %d\n", nProdutos[i].descricao, nProdutos[i].preco, nProdutos[i].stock);
    }
}

/* Function L() lists products in an order also by order. */

void L(){
    int i, j, a;
    int ide;
    struct Produtos *nProdEncomenda = can_fail_malloc(sizeof(encomendas[ide].produtosEncomenda));  /* Erro */
    struct Produtos tmp;
    scanf("%d", &ide);
    for (a = 0; a < encomendas[ide].counter; a++){
        nProdEncomenda[a] = encomendas[ide].produtosEncomenda[a];
    }
    if (ide >= idE){
        printf("Impossivel listar  encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    for (i = 0; i < encomendas[ide].counter; i++){
        for (j = 0; j < encomendas[ide].counter; j++){
            if (strcmp(nProdEncomenda[i].descricao, nProdEncomenda[j].descricao) < 0){
                tmp = nProdEncomenda[i];
                nProdEncomenda[i] = nProdEncomenda[j];
                nProdEncomenda[j] = tmp;
            }
        }
    }

    printf("Encomenda %d.\n", ide);

    for (i = 0; i < encomendas[ide].counter; i++){
        printf("* %s %d %d\n", nProdEncomenda[i].descricao, nProdEncomenda[i].preco, nProdEncomenda[i].stock);
    }
}

/* Fucntion x() ends the program. */

void x(){
    exit(0);
}

/* Function main() reads the first character of the input and with that information runs each function accordingly. */

int main(){
    char c;
    do{
        scanf(" %c", &c);
        if (c == 'a'){
            a();
            idP++;
        }
        else if (c == 'q'){
            q();
        }
        else if (c == 'N'){
            N();
            idE++;
        }
        else if (c == 'A'){
            A();
        }
        else if (c == 'r'){
            r();
        }
        else if (c == 'R'){
            R();
        }
        else if (c == 'C'){
            C();
        }
        else if (c == 'p'){
            p();
        }
        else if (c == 'E'){
            E();
        }
        else if (c == 'm'){
            m();
        }
        else if (c == 'l'){
            l();
        }
        else if (c == 'L'){
            L();
        }
        else if (c == 'x'){
            x();
        }
    }while (1);
}






















