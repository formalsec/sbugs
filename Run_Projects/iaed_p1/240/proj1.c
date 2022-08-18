#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Definir as constantes e os seus valores. */
#define MAX_INPUT 200
#define MAX_STR 63
#define MAX_PRODUCTS 10000
#define MAX_ORDERS 500
#define MAX_WEIGHT 200
#define MAX_PRODUCTS_ORDERS 200

/* Criar estrutura para Produto. */
typedef struct {
    
    int identifier;
    char description[MAX_STR];
    int price;
    int p_weight;
    int total_stock;

} Product;

/* Criar estrutura para as Encomendas. */
typedef struct {

    Product productsOrderList[MAX_PRODUCTS_ORDERS];
    int order_weight;
    int order_number;
    int products_counter;

} Order;

int numProducts;     /*   counter Produtos no sistema    */
int numOrders;       /*   counter Encomendas no sistema  */
int IDP = 0;         /*   idp dos produtos no sistema           */
int IDE = 0;         /*   ide das encomendas no sistema         */


Product productsList[MAX_PRODUCTS];  /* lista de Produtos global no sistema   */
Order ordersList[MAX_ORDERS];        /* lista de Encomendas global no sistema */


void addProduct();   /* criar produto  */
void createsOrder(); /* crar encomenda */

void addToOrder();   /* funcoes para adicionar produto a encomenda */
void addProductToOrder();

void changeProduct(); /* menu de opcoes */
void addStock();
void remStock();
void changePrice();
void calculatesOrderPrice();
void showDetails();
void moreTimesProduct();
void remProductFromOrder();

void printOrderProductsList(); /* funcoes necessarias para L e algoritmo quickSort */
void quickSort();
void swap();
int partition();
int comparePrice();
int less();

void printProductsList(); /* funcoes necessarias para l */
void sortProductsOrder(); 


int findIDP();  /* funcoes auxiliares de procura*/
int findIDE();
int findProductAtOrder();



/* 
    A funcao "main":
    
    - Vai pedindo e executando comandos, ate que seja pedido para parar.
    - Usa um switch para saber qual a instrucao pretendida.

 */

int main() {

    int c;

    while(1) {

        c = getchar(); 
        switch (c) {

            case 'a':               /*  a = Adiciona um novo produto ao sistema.  */
                addProduct();
                break;

            case 'q':               /*  q = Adiciona stock a um produto existente no sistema.  */
                changeProduct(1);      
                break;

            case 'N':               /*  N = Cria uma nova encomenda.  */
                createsOrder();   
                break;

            case 'A':               /*  A = Adiciona um produto a uma encomenda.  */
                addToOrder();
                break;
            
            case 'r':               /*  r = Remove stock a um produto existente.  */
                changeProduct(2);
                break;

            case 'R':               /*  R = Remove um produto de uma encomenda.  */
                changeProduct(5);   
                break;

            case 'C':               /*  C = Calcula o custo de uma encomenda.  */
                changeProduct(7);
                break;
            
            case 'p':               /*  p = Altera o preco de um produto existente no sistema.  */
                changeProduct(3);
                break;
            
            case 'E':               /*  E = Retorna a descricao e a quantidade de um produto numa dada encomenda.  */
                changeProduct(4);
                break;

            case 'm':               /*  m = Retorna o identificador da encomenda em que um dado produto ocorre mais vezes.  */
                changeProduct(6);
                break;

            case 'l':               /*  l = Lista todos os produtos existentes no sistema por ordem crescente de preco.  */
                printProductsList(productsList);
                break;

            case 'L':               /*  L = Lista todos os produtos de uma encomenda por ordem alfabetica da descricao.  */
                printOrderProductsList(ordersList);
                break;

            case 'x':               /*  x = Fecha/termina o programa.  */
                return 0;

            default:
                break;

        }
        while(c != '\n')
            c = getchar();
    }

    return 0;
}

/*  
    A funcao "addProduct":

        - Recebe como argumento uma linha com todas as caracteristicas especificas de um determinado producto, dividindo-a 
        para dentro da estrutura Product e adicionando-o a lista global de produtos.
        - Nao retorna nenhuma mensagem de erro.
        - Retorna print de mensagem de sucesso com o idp do produto criado.
*/

void addProduct() { /* a */

    Product product;
    char input[MAX_INPUT];
    char *delimiter = ":";
    char *token;
    int i;
    
    scanf(" %[^\n]", input);

    token = strtok(input, delimiter);
    i = 0;
    while (token != NULL) {

        if (i == 0)
            strcpy(product.description, token);
        
        else if (i == 1) 
            product.price = atoi(token);

        else if (i == 2)
            product.p_weight = atoi(token);

        else if (i == 3)
            product.total_stock = atoi(token);

        token = strtok(NULL, delimiter);
        i++;
    }

    product.identifier = IDP++;
    productsList[numProducts++] = product;
    printf("Novo produto %d.\n", product.identifier);
}

/*  
    A funcao "createsOrder":

        - Cria uma encomenda, atribuindo-lhe um ide e adicionando-a a lista global de encomendas no sistema,
        para alem de dar set de alguns atributos a 0.
        - Nao retorna nenhuma mensagem de erro.
        - Retorna print de mensagem de sucesso com o ide da encomenda criada.
*/

void createsOrder() { /* N */

    Order order;

    order.order_weight = 0;
    order.order_number = IDE++;
    order.products_counter = 0;
    ordersList[numOrders++] = order;

    printf("Nova encomenda %d.\n", order.order_number);
}


/* 
    A funcao "changeProduct":

    - Recebe como argumento um numero inteiro que especifica a opcao e consequentemente a funcao a utilizar:

        1 = Adicionar Stock do Produto.
        2 = Remover Stock do Produto.
        3 = Alterar Preco do Produto.
        4 = Ver a descricao e total stock de um Produto numa Encomenda.
        5 = Remover Produto de uma Encomenda.
        6 = Devolver o ide da encomenda e o total stock do produto onde este ultimo ocorre mais vezes.
        7 = Calcular o preco total de uma encomenda.

    - Utiliza cada uma das suas funcoes auxiliares para poder realizar a opcao escolhida.
*/

void changeProduct(int n){ 

    char input[MAX_STR];
    char *delimiter, *idp, *qtd, *ide;
    scanf(" %[^\n]", input);
    delimiter = ":";
    
    if (n == 4){

        ide = strtok(input, delimiter);
        idp = strtok(NULL, delimiter);

        showDetails(atoi(ide), atoi(idp));   /* E */
    }

    else if( n == 5){

        ide = strtok(input, delimiter);
        idp = strtok(NULL, delimiter);

        remProductFromOrder(atoi(ide), atoi(idp));  /* R */
    }

    else if( n == 6){

        moreTimesProduct(atoi(input));   /* m */
    }

    else if( n == 7){

        calculatesOrderPrice(atoi(input));      /* C */
    }

    else {

        idp = strtok(input, delimiter);
        qtd = strtok(NULL, delimiter);

        if( n == 1)
            addStock(atoi(idp), atoi(qtd));     /* q */

        if (n == 2)
            remStock(atoi(idp), atoi(qtd));     /* r */

        if (n == 3)
            changePrice(atoi(idp), atoi(qtd));  /* p */
    }

}


/*
   A funcao "addStock":

    - Adiciona uma quantidade ao stock do produto na lista de produtos.
    - Recebe como argumentos o idp do produto e a quantidade de produto para adicionar.
    - Tem como funcao auxiliar a "findIDP" para saber se o produto recebido se encontra no sistema.
    - Retorna mensagem de erro quando o produto nao existe.

*/
void addStock(int idp, int qtd){ /* q */

    int foundIDP = findIDP(idp);

    if (foundIDP == -2){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        return;
    }

    else{
        productsList[foundIDP].total_stock += qtd;
        return;
    }
}


/*
   A funcao "remStock":

    - Remove uma quantidade ao stock do produto na lista de produtos.
    - Recebe como argumentos o idp do produto e a quantidade de produto para remover.
    - Tem como funcao auxiliar a "findIDP" para saber se o produto recebido se encontra no sistema.
    - Retorna mensagem de erro quando:
        - O produto nao existe.
        - Nao e possivel remover a quantidade recebida, 
        dado ao stock existente ser menor que a quantidade a retirar.

*/
void remStock(int idp, int qtd){ /* r */

    int foundIDP = findIDP(idp);

    if (foundIDP == -2)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);

    else{
        
        if(productsList[foundIDP].total_stock >= qtd){
            productsList[foundIDP].total_stock -= qtd;
            return;
        }
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return; 
    }   
}


/*
   A funcao "changePrice":

    - Altera o preco do produto na lista de produtos e dentro das encomendas.
    - Recebe como argumentos o idp do produto e o preco de alteracao.
    - Tem como funcao auxiliar a "findIDP" para saber se o produto recebido se encontra no sistema.
    - Retorna mensagem de erro quando o produto nao existe.

*/
void changePrice(int idp, int qtd){ /* p */

    int foundIDP = findIDP(idp), i, j;

    if (foundIDP == -2)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);

    else{

        for (i = 0 ; i < numOrders ; i++ ){
            for ( j = 0; j < ordersList[i].products_counter; j++){
                if(ordersList[i].productsOrderList[j].identifier == idp){
                    ordersList[i].productsOrderList[j].price = qtd;
                }
            }
        }
        productsList[idp].price = qtd;
        return; 
    }

}

/* 
    A funcao "showDetails":

    - Recebe como argumentos o ide especifico de uma determinada encomenda e um idp de um produto. 
    - Se esse produto existir dentro da encomenda, printa os detalhes esperados (descricao e total stock).
    - Se esse produto nao existir apenas dentro da encomenda, printa a sua descricao mas o total stock nulo.
    - Retorna mensagem de erro quando:
        - A encomenda e/ou produto nao existirem.

*/

void showDetails(int ide, int idp){ /* E */

    int foundIDE = findIDE(ide); 
    int foundIDP = findIDP(idp);
    int exists, total, none = 0;


    Order o = ordersList[ide];
    exists = findProductAtOrder(o, foundIDP);

    if (foundIDE == -1)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

    else if (foundIDP == -2)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);

    else if(exists == -3)
        printf("%s %d.\n", productsList[idp].description, none);
        
    else {

        total = o.productsOrderList[exists].total_stock;
        ordersList[foundIDE] = o;
        printf("%s %d.\n", productsList[idp].description, total);
        return;
    }

}


/* 
    A funcao "calculatesOrderPrice":

    - Retorna o custo total de uma determinada encomenda e o seu ide.
    - Recebe como argumento o ide especifico de uma encomenda. 
    - Retorna mensagem de erro quando:
        - A encomenda nao existe no sistema.
*/

void calculatesOrderPrice(int ide){ /* C */

    int foundIDE = findIDE(ide), i, total = 0;

    if(foundIDE == -1)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);

    else{

        for (i = 0; i < ordersList[ide].products_counter; i++){
			total += ordersList[ide].productsOrderList[i].price * ordersList[ide].productsOrderList[i].total_stock;
		}
		printf("Custo da encomenda %d %d.\n", ide, total);
        return;
    }

}

/*  
    A funcao "addToOrder":
        - Recebe como argumento uma linha que contem o ide da encomenda e o idp e quantidade de produto 
        que se pretende adicionar a essa encomenda.
        - Tem como funcao auxiliar a "auxChangeOrder";
*/

void addToOrder(){ /* A */

    char input[MAX_STR];
    char *delimiter = ":", *token;
    int ide, idp, qtd, i = 0;
    
    scanf(" %[^\n]", input);
    token = strtok(input, delimiter);

    while (token != NULL) {

        if (i == 0)
            ide = atoi(token);
        
        else if (i == 1) 
            idp = atoi(token);

        else if (i == 2)
            qtd = atoi(token);

        token = strtok(NULL, delimiter);
        i++;
    }
    addProductToOrder(ide, idp, qtd);

}


/*  
    A funcao "addProductToOrder":

        - Recebe como argumento da funcao "addToOrder" o ide da encomenda e o idp e a quantidade do produto 
        que se pretende adicionar a essa encomenda.
        - Tem como funcoes auxiliares a "findIDP", a "findIDE" e a "findProductAtOrder", 
        para saber se o idp e/ou ide existem e se o produto se encontra na encomenda ou nao.
        - Retorna mensagem de erro quando:
            - O produto nao existe no sistema.
            - A encomenda nao existe no sistema.
            - Se a quantidade a adicionar pretendidda de produto for maior que a quantidade existente deste no sistema.
            - Se ao adicionar a quantidade pretendida de produto a encomenda ultrapassar o limite de peso de 200kg.
        - Se passar nestas condicoes, nao retorna nada e completa o seu objetivo.
        - Nao devolve nada, para alem de mensagem de erro.

*/

void addProductToOrder(int ide, int idp, int qtd){ 

    int exists, k;
    int foundIDP = findIDP(idp);
    int foundIDE = findIDE(ide);

    if (foundIDE == -1)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

    else if (foundIDP == -2)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

    else if (productsList[foundIDP].total_stock < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
   

    else if ((productsList[foundIDP].p_weight * qtd + ordersList[foundIDE].order_weight) > MAX_WEIGHT )
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    
    else{

        Order o = ordersList[foundIDE];
        Product p = productsList[foundIDP];

        exists = findProductAtOrder(o, foundIDP);

        if (exists == -3){

            k = o.products_counter;

            o.productsOrderList[k] = p;
            o.productsOrderList[k].total_stock = qtd;

            o.products_counter++;
            
            o.order_weight += p.p_weight * qtd;
            ordersList[foundIDE] = o;

            p.total_stock -= qtd;
            productsList[foundIDP] = p;

            return;
        }

        else{

            o.productsOrderList[exists].total_stock += qtd;
            o.order_weight += p.p_weight * qtd;
            p.total_stock -= qtd;

            ordersList[foundIDE] = o;
            productsList[foundIDP] = p;

            return;
        }
    }
}  


/*  
    A funcao "remProductFromOrder":
    
        - Recebe como argumento da funcao "changeProduct" o ide da encomenda e o idp do produto que se pretende remover a essa encomenda.
        - Tem como funcoes auxiliares a "findIDP", a "findIDE" e a "findProductAtOrder", para saber se o idp e/ou ide existem e se o produto se encontra na encomenda ou nao.
        - Retorna mensagem de erro quando:
            - O produto nao existe no sistema.
            - A encomenda nao existe no sistema.
        - Se o produto nao existir na encomenda, nao realiza nada.
        - Se o produto existir na encomenda e removido e o seu stock na encomenda e acrescentado ao stock do produto na lista de produtos global.
        - Nao devolve nada, para alem de mensagem de erro.

*/

void remProductFromOrder(int ide, int idp){

    int exists, qtd = 0, i;
    int foundIDE = findIDE(ide);
    int foundIDP = findIDP(idp);

    Order o = ordersList[ide];
    exists = findProductAtOrder(o, foundIDP);

    if (foundIDE == -1)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

    else if (foundIDP == -2)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

    else if (exists == -3) 
        return;
    
    else{

        qtd = o.productsOrderList[exists].total_stock;
        productsList[foundIDP].total_stock += qtd;
            
        o.order_weight -= productsList[foundIDP].p_weight * qtd; 

        for( i = exists ; i < o.products_counter; i++){
            o.productsOrderList[i] = o.productsOrderList[i + 1];
        }

        o.products_counter--;
        ordersList[foundIDE] = o;
    }

}  


/*  
    A funcao "moreTimesProduct":
        - Recebe como argumento o idp de um produto do qual se pretende saber em qual encomenda se encontra em maior quantidade.
        - Retorna mensagem de erro se o produto nao existir.
        - Retorna mensagem de sucesso com o  maior total stock (quantidade do produto), o ide da encomenda e o idp do produto.

*/

void moreTimesProduct(int idp){ /* m */

    int foundIDP = findIDP(idp);
    int i, j, max = 0, lastmax = 0, foundIDE = -1;
    
    if (foundIDP == -2)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    
    for ( i = 0; i < numOrders; i++){
        for ( j = 0 ; j < ordersList[i].products_counter; j++){
            if(ordersList[i].productsOrderList[j].identifier == idp){
                if(ordersList[i].productsOrderList[j].total_stock > max){
                    max = ordersList[i].productsOrderList[j].total_stock;
                    if (max > lastmax){
                        lastmax = max;
                        foundIDE = ordersList[i].order_number;
                    }
                }
            }
        }
    }
    if (foundIDE != -1)
        printf("Maximo produto %d %d %d.\n", idp, foundIDE, lastmax);
}


/*--------------------   FUNCOES AUXILIARES DE PROCURA  --------------     */

/*
    A funcao "findIDE":
        - Recebe como argumento o ide de uma encomenda e verifica se ela existe na lista global de encomendas.
        - Retorna o ide se encontrar.
        - Retorna -1 se a encomenda nao existir.

*/

int findIDE(int ide){

    int i;
   
    for( i = 0; i < numOrders; i++){
        if(ordersList[i].order_number == ide){
            return ide;
        }
    }
    return -1;
}

/*
    A funcao "findIDP":
        - Recebe como argumento o idp de um produto e verifica se ele existe na lista global de produtos.
        - Retorna o idp se encontrar
        - Retorna -2 se o produto nao existir.

*/

int findIDP(int idp){

    int i;

    for( i = 0; i < numProducts; i++){
        if(productsList[i].identifier == idp){
            return idp;
        }
    }
    return -2;
}

/*  
    A funcao "findProductAtOrder":
        - Recebe como argumentos uma encomenda especifica e o idp de um produto e 
        verifica se ele existe na lista de produtos dessa mesma encomenda.
        - Retorna o indice onde o produto se encontra na encomenda recebida.
        - Retorna -3 se o produto nao existir na encomenda.

*/

int findProductAtOrder(Order o, int idp){
    
    int i;

    for (i = 0; i < o.products_counter; i++ ){
        if (o.productsOrderList[i].identifier == idp)
            return i; 
    }
    return -3;
}

/* --------------------------------------------------------------------     */



/* 
    A funcao "printProductsList":

    - Imprime a lista de todos os produtos existentes no sistema do menor para o maior preco e do menor para maior id, como pedido.
    - Utiliza a funcao auxiliar quickSort para realizar essa ordenacao a lista de produtos.

*/

void printProductsList(Product* list) { /* l */

    Product productsListAux[MAX_PRODUCTS];
    int i;

    printf("Produtos\n");

    for (i = 0; i < numProducts; i++){
        productsListAux[i] = list[i];
    }

    quickSort(productsListAux, 0, numProducts - 1);

    for (i = 0; i < numProducts; i++)
        printf("* %s %d %d\n", 
        productsListAux[i].description,
        productsListAux[i].price,
        productsListAux[i].total_stock
        );    
}


/* ---------Algoritmo de Ordenacao por Preco e IDP || QuickSort -------     */

int partition(Product* list, int low, int high) {

    Product pivot = list[high];
    int i = (low -1), j = high;

    while (i < j){
        while(comparePrice(list[++i], pivot) == 1);
        while(comparePrice(pivot, list[--j]) == 1)
            if ( j == low )
                break;
        if (i < j)
            swap(&list[i], &list[j]);
    }  
    swap(&list[i], &list[high]); 
    return i; 

}

void swap(Product* a, Product* b) 
{ 
    Product t = *a; 
    *a = *b; 
    *b = t; 
}

void quickSort(Product* list, int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(list, low, high); 
  
        quickSort(list, low, pi - 1); 
        quickSort(list, pi + 1, high); 
    } 
} 

/* compara preco de produtos e o seu idp*/
int comparePrice(Product old, Product new) {

    if (old.price < new.price)
        return 1;

    else if (old.price > new.price)
        return 0;

    else {
        if ((old.price) == (new.price))
            if (old.identifier < new.identifier)
                return 1;
        return 0;
    }

}

/* -------------------------------------------------------------------      */

/* 
    A funcao "printOrderProductsList":

    - Imprime a lista de todos os produtos existentes, por ordem alfabetica, na encomenda com o determinado ide recebido. 
    - Utiliza a funcao auxiliar sortProductsOrder para realizar essa ordenacao a lista de produtos.
    
*/

void printOrderProductsList(Order* ordersList) { /* L */

    Product auxOrderProductsList[MAX_PRODUCTS];
    int foundIDE, i;
    char input[MAX_STR];
    int ide;
    scanf(" %[^\n]", input);

    ide = atoi(input);
    foundIDE = findIDE(ide);

    if(foundIDE == -1){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    
    for(i = 0; i < ordersList[ide].products_counter; i++){
        auxOrderProductsList[i] = ordersList[ide].productsOrderList[i];
    }

    sortProductsOrder(auxOrderProductsList, ordersList[ide].products_counter);

    printf("Encomenda %d\n", ordersList[foundIDE].order_number);
    for(i = 0; i < ordersList[foundIDE].products_counter; i++){
        printf("* %s %d %d\n",
        auxOrderProductsList[i].description,
        auxOrderProductsList[i].price,
        auxOrderProductsList[i].total_stock);
    }   
    
} 


/* --------------Algoritmo de Ordenacao Alfabeticamente---------------      */

void sortProductsOrder(Product* list, int n){
    int i,j;
    Product temp;

    for (i = 0 ; i < n ; i++) {
        for ( j = i + 1 ; j < n ; j++) {
            if (strcmp(list[i].description,list[j].description) > 0) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
   
}
/* -------------------------------------------------------------------      */
