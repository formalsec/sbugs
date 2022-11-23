#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>

/* O numero maximo de produtos (numerados de 0 a 9999). */
#define MAX_ID_PRODUCT 9999

/* O numero maximo de encomendas (numeradas de 0 a 499). */
#define MAX_ID_DELIVERY 499

/* O peso maximo de uma encomenda individual. */
#define MAX_WEIGHT 200

/* O numero maximo de produtos numa encomenda. */
#define MAX_N_PRODUCTS 189

/* O numero maximo de carateres na descricao de um produto. */
#define MAX_DESCRIPTION 63

int i = -1; /* Variavel global associada ao identificador de produtos. */

int j = -1; /* Variavel global associada ao identificador de encomendas. */

int k = 0; /* Variavel global associada ao numero de vezes que se cria uma nova encomenda. */

/* Estrutura associada ao objeto Produto. */
typedef struct product {
    int pid;
    char description[MAX_DESCRIPTION];
    int price;
    int weight;
    int stock;
} Product;

/* Estrutura associada ao objeto Encomenda. */
typedef struct delivery {
    Product list[MAX_N_PRODUCTS];
    int did;
    int total_weight;
} Delivery;

/* Cria um novo produto e incrementa a variavel global i, (Comando a). */
void createProduct(Product p[MAX_ID_PRODUCT + 1]) {
    Product a;
    scanf(" %[^:]:%d:%d:%d", a.description, &a.price, &a.weight, &a.stock);
    i++;
    if (i <= MAX_ID_PRODUCT) {
        a.pid = i;
        p[i] = a;
        printf("Novo produto %d.\n", a.pid);
    }
}

/* Incrementa o stock de um determinado produto (pid) por uma quantidade (qtd), (Comando q). */
void addStock(Product p[MAX_ID_PRODUCT + 1], int pid, int qtd) {
    if (pid > i) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", pid);
    }
    else {
        p[pid].stock = p[pid].stock + qtd;
    }
}

/* Cria uma nova encomenda e incrementa a variavel global j, (Comando N). */
void createDelivery(Delivery d[MAX_ID_DELIVERY + 1]) {
    Delivery b;
    j++;
    if (j <= MAX_ID_DELIVERY) {
        b.did = j;
        d[j] = b;
        d[j].total_weight = 0;
        printf("Nova encomenda %d.\n", d[j].did);
    }
}

/* Adiciona um produto (pid) a uma encomenda (eid) ou incrementa o stock de um produto existente, (Comando A). */
void addStockToDelivery(Delivery d[MAX_ID_DELIVERY + 1], Product p[MAX_ID_PRODUCT + 1], int eid, int pid, int qtd) {
    if (eid > j) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", pid, eid);
    }
    else if (pid > i) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", pid, eid);
    }
    else {        
        if (p[pid].stock - qtd < 0) {
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", pid, eid);
        }
        else if ((d[eid].total_weight + (qtd*p[pid].weight)) > MAX_WEIGHT) {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", pid, eid);
        }
        else {
            p[pid].stock -= qtd;
            d[eid].total_weight += (p[pid].weight*qtd);
            d[eid].list[pid].stock += qtd;
            d[eid].list[pid].price = p[pid].price;
            k++;
        }
    }
}

/* Subtrai o stock de um determinado produto (pid) por uma quantidade (qtd), (Comando r). */
void removeStock(Product p[MAX_ID_PRODUCT + 1], int pid, int qtd) {
    if (pid > i) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", pid);
    }
    else {
        int a = p[pid].stock - qtd;
        if (a < 0) {
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, pid);
        }
        else {
            p[pid].stock = a;
        }
    }
}

/* Remove um produto (pid) de uma encomenda (eid), (Comando R). */
void removeProductFromDelivery(Product p[MAX_ID_PRODUCT + 1], Delivery d[MAX_ID_DELIVERY + 1], int eid, int pid){
    if (eid > j) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", pid, eid);
    }
    else if (pid > i) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", pid, eid);
    }
    else {
        d[eid].total_weight -= (d[eid].list[pid].stock * p[pid].weight);
        p[pid].stock += d[eid].list[pid].stock;
        d[eid].list[pid].stock = 0;      
    }
}

/* Calcula o valor total de uma encomenda (eid), (Comando C). */
void calculateDeliveryPrice(Delivery d[MAX_ID_DELIVERY + 1], int eid) {
    int x;
    int total_p = 0;
    if (eid > j){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", eid);
    }
    else {
        for (x = 0; x <= i; x++){
            total_p += (d[eid].list[x].price * d[eid].list[x].stock);
        }
        printf("Custo da encomenda %d %d.\n", eid, total_p);
    }
}

/* Altera o valor de um produto (pid), (Comando p). */
void changePrice(Product p[MAX_ID_PRODUCT + 1], Delivery d[MAX_ID_DELIVERY + 1], int pid, int new_price) {
    int x;
    if (pid > i) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", pid);
    }
    else {
        p[pid].price = new_price;
        for (x = 0; x <= j; x++){
            d[x].list[pid].price = new_price;
        }
    }
}

/* Lista a descri??o e a quantidade de um dado produto (pid) numa dada encomenda (did), (Comando E). */
void returnDescriptionAndStock(Product p[MAX_ID_PRODUCT + 1], Delivery d[MAX_ID_DELIVERY + 1], int pid, int eid) {
    if (eid > j) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", eid);
    }
    else if (pid > i) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", pid);
    }
    else {
        printf("%s %d.\n", p[pid].description, d[eid].list[pid].stock);
    }
}

/* Lista o identificador da encomenda em que um produto (pid) tem maior stock presente, (Comando m). */
void findHighestProductStock(Delivery d[MAX_ID_DELIVERY + 1], int pid) {
    int x;
    int did, qtt;
    int h_stock = 0;
    if (pid > i) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", pid);
    }
    else if (j >= 0 && k > 0) {     
        for (x = 0; x <= j; x++) {
            if (h_stock < d[x].list[pid].stock) {
                h_stock = d[x].list[pid].stock;
                did = x;
                qtt = d[x].list[pid].stock;
            } 
            else {
                continue;
            }
        }
        if (h_stock != 0) {
            printf("Maximo produto %d %d %d.\n", pid, did, qtt);
        }
    }
}

/* Realiza uma ordenacao crescente dos precos dos produtos, (Comando l). */
void listProducts(Product p[MAX_ID_PRODUCT + 1]) {
    
    int x;
    int y = 0;
    int price = 1;
    
    printf("Produtos\n");  
    while (y <= i) {
        for (x = 0; x <= i; x++) {
            if (p[x].price == price) {
                printf("* %s %d %d\n", p[x].description, p[x].price, p[x].stock);
                y++;
            }
            else {
                continue;
            }
        }
        price++;
    }
}

/* Realiza uma ordenacao alfabetica dos produtos de uma dada encomenda (eid), (Comando L). */
void listProductsInDelivery(Product p[MAX_ID_PRODUCT + 1], Delivery d[MAX_ID_DELIVERY + 1], int eid) {
    
    char a = 'a';
    int x;

    if (eid > j) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", eid);
    }
    else {
        printf("Encomenda %d\n", eid);
        while (a <= 'z') {
            for (x = 0; x <= i; x++) {
                if (p[x].description[0] == a && d[eid].list[x].stock != 0) {
                    printf("* %s %d %d\n", p[x].description, d[eid].list[x].price, d[eid].list[x].stock);
                }
                else {
                    continue;
                }
            }
            a++;
        }
    }
}

/* Processa comandos e realiza diferentes funcoes, consoante o comando. Se o comando for x, o programa encerra. */
int main() {
    
    Product products[MAX_ID_PRODUCT];
    Delivery deliveries[MAX_ID_DELIVERY];
    
    char c;
    int eid, pid, p, qtd;
    
    scanf("%c", &c);
    
    while (c != 'x') {        
        switch (c) {
            case 'a':
                createProduct(products);
                break;
            case 'q':
                scanf("%d:%d", &pid, &qtd);
                addStock(products, pid, qtd);
                break;
            case 'N':
                createDelivery(deliveries);
                break;
            case 'A':
                scanf("%d:%d:%d", &eid, &pid, &qtd);
                addStockToDelivery(deliveries, products, eid, pid, qtd);
                break;
            case 'r':
                scanf("%d:%d", &pid, &qtd);
                removeStock(products, pid, qtd);
                break;
            case 'R':
                scanf("%d:%d", &eid, &pid);
                removeProductFromDelivery(products, deliveries, eid, pid);
                break;
            case 'C':
                scanf("%d", &eid);
                calculateDeliveryPrice(deliveries, eid);
                break;
            case 'p':
                scanf("%d:%d", &pid, &p);
                changePrice(products, deliveries, pid, p);
                break;
            case 'E':
                scanf("%d:%d", &eid, &pid);
                returnDescriptionAndStock(products, deliveries, pid, eid);
                break;
            case 'm':
                scanf("%d", &pid);
                findHighestProductStock(deliveries, pid);
                break;
            case 'l':
                listProducts(products);
                break;
            case 'L':
                scanf("%d", &eid);
                listProductsInDelivery(products, deliveries, eid);
                break;
        }
        scanf("%c", &c);
    }
    return 0;
}