#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESC 64
#define MAX 10000
#define MAX_TAMANHO 200
#define MAX_ORDERS 500
#define MAX_ORDER_WEIGHT 200

int id = 0; /*total produtos*/
int order_id = 0;/*total encomendas*/

/*estrutura dos produtos*/
typedef struct
{
    char description[MAX_DESC];
    int price;
    int weight;
    int stock;
} Product;

/*estrutura de encomenda*/
typedef struct 
{
    int order_weight;
    Product product[MAX];
} Order;

Product myProduct[MAX];

Order myOrders[MAX_ORDERS];

/* TODO meter em funcoes*/
void custoEncomenda(int order_identifier);/*funcao auxiliar de 'C'*/
void orderMostProduct(int identifier);/*funcao auxiliar de 'm'*/

int main() {


    char cmd[MAX_TAMANHO + 1];
    int identifier, stock, order_identifier, price;

    while (fgets(cmd, MAX_TAMANHO, stdin) != NULL) {

        switch (cmd[0])
        {
            case 'a': /*cria produto*/
                sscanf(cmd, "a %[^:]:%d:%d:%d\n", myProduct[id].description, &myProduct[id].price , &myProduct[id].weight, &myProduct[id].stock);
                printf("Novo produto %d.\n", id);
                id++;
                break;
            case 'q': /*adiciona stock a produto*/
                sscanf(cmd, "q %d:%d",&identifier,&stock);
                if (identifier >= id){
                    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", identifier);
                }
                else
                {
                    myProduct[identifier].stock += stock;
                    
                }
                break;
            case 'N': /*cria encomenda*/
                sscanf(cmd, "N");
                printf("Nova encomenda %d.\n", order_id);
                order_id++;
                break;
            case 'A':/*adiciona stock a enconmenda*/
                sscanf(cmd, "A %d:%d:%d", &order_identifier, &identifier, &stock);
                if (order_identifier >= order_id){
                    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", identifier, order_identifier);
                    break;
                }
                if (identifier >= id){
                    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", identifier, order_identifier);
                    break;
                }
                if (myProduct[identifier].stock < stock){
                    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", identifier, order_identifier);
                    break;
                }
                if ((myOrders[order_identifier].order_weight + (stock * myProduct[identifier].weight ))> 200){
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", identifier, order_identifier);
                    break;
                }
                else
                {   
                    myOrders[order_identifier].product[identifier].stock = myOrders[order_identifier].product[identifier].stock + stock;
                    myOrders[order_identifier].order_weight = myOrders[order_identifier].order_weight + stock * myProduct[identifier].weight;
                    myProduct[identifier].stock = myProduct[identifier].stock - stock;

                    break;
                }
                break;
            case 'r':/*remove stock de produto*/
                sscanf(cmd, "r %d:%d", &identifier, &stock);
                if(identifier >= id){
                    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", identifier);
                    break;
                }
                if (myProduct[identifier].stock < stock){
                    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock, identifier);
                    break;
                }
                else
                {
                    myProduct[identifier].stock = myProduct[identifier].stock - stock;
                    printf("novo stock:%d", myProduct[identifier].stock);
                    break;
                }
                break;
            case 'R':/*remove produto de encomenda*/
                sscanf(cmd, "R %d:%d", &order_identifier, &identifier);
                if (order_identifier >= order_id) {
                    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",identifier, order_identifier);
                    break;
                }
                if (identifier >= id){
                    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",identifier, order_identifier);
                    break;
                }
                else{
                    myProduct[identifier].stock = myProduct[identifier].stock + myOrders[order_identifier].product[identifier].stock;
                    myOrders[order_identifier].order_weight -= myProduct[identifier].weight *  myOrders[order_identifier].product[identifier].stock;
                    myOrders[order_identifier].product[identifier].stock = 0;
                    break;
                }
                break;
            case 'C':/*Custo da encomenda*/
                sscanf(cmd, "C %d", &order_identifier);
                if (order_identifier >= order_id){
                    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", order_identifier);
                    break;
                }
                else
                {
                    custoEncomenda(order_identifier);
                    break;       
                }
                break;
            case 'p':/*Alterar pre?o produto*/
                sscanf(cmd, "p %d:%d", &identifier, &price);
                if (identifier >= id){
                    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", identifier);
                    break;
                }
                else
                {
                    myProduct[identifier].price = price;
                    break;
                }
                break;
            case 'E':/* lista a descri??o e a quantidade de um produto numa encomenda*/
                sscanf(cmd, "E %d:%d", &order_identifier, &identifier);
                if (order_identifier >= order_id){
                    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", order_identifier);
                    break;
                }
                if (identifier >= id){
                    printf("Impossivel listar produto %d. Produto inexistente.\n", identifier);
                    break;
                }
                else
                {
                    printf("%s %d.\n", myProduct[identifier].description, myOrders[order_identifier].product[identifier].stock);
                    break;
                }
                break;
            case 'm':/*lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas nessa situa??o, dever? imprimir a encomenda de menor id*/
                sscanf(cmd, "m %d", &identifier);
                if (identifier >= id){
                    printf("Impossivel listar maximo do produto %d. Produto inexistente.", identifier);
                    break;
                }
                else
                {
                    orderMostProduct(identifier);
                    break;
                }
            case 'l':/*ordem crescente de precos de produtos*/
                sscanf(cmd, "l");
                printf("Produtos\n");
                break;
            case 'x':
                return 0;
        }
    }
    return 0;
}

/*vai a cada produto da encomenda e multiplica o seu nr de stock pelo preco do produto e faz um sumatorio*/
void custoEncomenda(int order_identifier){
    int i, order_price = 0;
    for (i = 0; i <= id; i++){        
        order_price = order_price + myProduct[i].price * myOrders[order_identifier].product[i].stock;
    }
    printf("Custo da encomenda %d %d.\n", order_identifier, order_price);
}

/* funcao que verifica qual encomenda em que o produto se encontra mais vezes*/
/*tem max que guarda valor max de stock na encomenda e vai verificando para as restantes encomendas*/
void orderMostProduct(int identifier){
    int i, order, max = 0;
    
    for(i = 0; i < order_id; i++){
        if (max < myOrders[i].product[identifier].stock){
            max = myOrders[i].product[identifier].stock;
            order = i;
        }
    }
    printf("Maximo produto %d %d %d.", identifier, order, max);
}
