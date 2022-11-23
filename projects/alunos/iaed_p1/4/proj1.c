#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 10000
#define MAX_ORDERS 500
#define MAX_DESCRIPTION 63

typedef struct product{
   char description[MAX_DESCRIPTION];
   int price;
   int weight;
   int quantity;
}Product;

typedef struct order_item{
    struct order_item* next;
    int product_id;
    int quantity;
}Item;

void add_product(Product products[], Product new_product, int current);
void add_stock(Product products[], int idp, int qtd);
void remove_stock(Product products[], int idp, int qtd);
void add_product_to_order(int ide, int idp, int qtd, Product products[], Item *order);
Item* new_order_item(int idp, int qtd);
int remove_product_from_order(int idp, Item *order);
int order_cost(Item* order, Product products[]);
void change_product_price(Product products[], int idp, int price);
int get_order_item_quantity(int idp, Item* order);
void find_order_with_max_idp(Item* orders[], int idp);
int item_weight(int idp, int qtd, Product products[]);
int order_weight(Item* order, Product products[]);
void sort_print_products(Product original[], int size);
void sort_products_by_price(Product products[], int n);
void sort_print_order(Item* order, Product products[], int ide);


int main() {
    char comando;

    Product products[MAX_PRODUCTS];
    Item* orders[MAX_ORDERS] = { NULL };
    int current_product = 0;
    int current_order = 0;

    while (1)
    {
        Product a;
        int idp, qtd;
        int ide;
        int price, cost;
        comando = getchar();

        switch (comando) {
            case 'a':
                
                scanf(" %[^:]:%i:%i:%i", a.description, &a.price, &a.weight, &a.quantity);

                add_product(products, a, current_product);
                printf("Novo produto %i.\n", current_product);
                current_product += 1;

                break;
            case 'q':
                
                scanf(" %i:%i", &idp, &qtd);
                if (idp < current_product)
                {
                    add_stock(products, idp, qtd);
                } else
                {
                    printf("Impossivel adicionar produto %i ao stock. Produto inexistente.\n", idp);
                }
                break;
            case 'N':
                orders[current_order] = new_order_item(-1, 0);
                printf("Nova encomenda %i.\n", current_order);
                current_order++;
                break;
            case 'A':
                
                scanf(" %i:%i:%i", &ide, &idp, &qtd);
                if (ide >= current_order)
                {
                    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
                } else if (idp >= current_product)
                {
                    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
                } else if (products[idp].quantity < qtd)
                {
                    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
                } else if ((item_weight(idp, qtd, products) + order_weight(orders[ide], products)) > 200)
                {
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
                } else if (orders[ide] == NULL)
                {
                    orders[ide] = new_order_item(idp, qtd);
                    remove_stock(products, idp, qtd);
                } else
                {
                    add_product_to_order(ide, idp, qtd, products, orders[ide]);
                    remove_stock(products, idp, qtd);
                }
                break;

            case 'r':
                
                scanf(" %i:%i", &idp, &qtd);
                if (idp >= current_product)
                {
                    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
                } else if (products[idp].quantity < qtd)
                {
                    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
                } else
                {
                    remove_stock(products, idp, qtd);
                }
                break;
            
            case 'R':
                
                scanf(" %i:%i", &ide, &idp);
                if (ide >= current_order)
                {
                    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
                } else if (idp >= current_product)
                {
                    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
                } else
                {
                    qtd = remove_product_from_order(idp, orders[ide]);
                    add_stock(products, idp, qtd);
                }
                
                break;

            case 'C':
                
                scanf(" %d", &ide);
                if (ide >= current_order)
                {
                    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
                } else
                {
                    cost = order_cost(orders[ide], products);
                    printf("Custo da encomenda %d %d.\n", ide, cost);
                }
                
                break;

            case 'p':
                
                scanf(" %d:%d", &idp, &price);
                if (idp >= current_product)
                {
                    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
                } else
                {
                    change_product_price(products, idp, price);
                }
                
                break;
            
            case 'E':
                
                scanf(" %d:%d", &ide, &idp);
                if (ide >= current_order)
                {
                    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
                } else if (idp >= current_product)
                {
                    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
                } else
                {
                    int quantity = get_order_item_quantity(idp, orders[ide]);
                    printf("%s %d.\n", products[idp].description, quantity);
                }
                break;

            case 'm':

                scanf(" %d", &idp);
                if (idp >= current_product)
                {
                    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
                } else if (current_order == 0)
                {
                  break;  
                } else
                {
                    find_order_with_max_idp(orders, idp);
                }
                break;

            case 'l': 
                sort_print_products(products, current_product);
                break;

            case 'L':
                scanf(" %d", &ide);
                if (ide >= current_order)
                {
                    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
                } else
                {
                    sort_print_order(orders[ide], products, ide);
                }
                
                
                break;
                
            case 'x':
                return EXIT_SUCCESS;
        
            default:
                printf("ERRO: Comando desconhecido\n");
                break;
        }
        getchar();
    }
    

    return EXIT_FAILURE;
}

void add_product(Product *products, Product new_product, int current) {
    products[current] = new_product;
}

void add_stock(Product *products, int idp, int qtd) {
    products[idp].quantity += qtd;
}

void remove_stock(Product *products, int idp, int qtd) {
    products[idp].quantity -= qtd;
}

void add_product_to_order(int ide, int idp, int qtd, Product products[], Item *order) {
    Item *new;

    if (order->product_id == idp)
    {
        order->quantity += qtd;
    } else if (order->next == NULL)
    {
        new = new_order_item(idp, qtd);
        order->next = new;
    } else
    {
        add_product_to_order(ide, idp, qtd, products, order->next);
    }
}

Item* new_order_item(int idp, int qtd) {
    Item* new;
    new = (Item *)can_fail_malloc(sizeof(Item));
    new->product_id = idp;
    new->quantity = qtd;
    new->next = NULL;

    return new;
}

int remove_product_from_order(int idp, Item *order) {
    Item* temp = order, *prev;
    int qtd = 0;

/*     if (temp != NULL && temp->product_id == idp)
    {
        *order = temp->next;
        free(temp);
        return;
    } */

    while (temp->next != NULL && temp->product_id != idp)
    {
        prev = temp;
        temp = prev->next;
    }

    if (temp == NULL) return 0;

    if (temp->product_id == idp)
    {
        qtd = temp->quantity;
        if (temp->next == NULL) {
            prev->next = NULL;
        } else {
            prev->next = temp->next;
        }
        free(temp);
    }

    return qtd;
}

int order_cost(Item* order, Product products[]) {
    int total = 0;
    Item* temp;

    if (order->product_id < 0) temp = order->next;

    while (temp != NULL)
    {
        int idp = temp->product_id;
        int qtd = temp->quantity;
        int price = products[idp].price;
        
        total += (qtd * price);
        temp = temp->next;
    }
    
    return total;
}

void change_product_price(Product *products, int idp, int price) {
    products[idp].price = price;
}

int get_order_item_quantity(int idp, Item* order) {
    Item* temp = order;
    int quantity = 0;

    while (temp->next != NULL && temp->product_id != idp)
    {
        temp = temp->next;
    }
    if (temp->product_id == idp) quantity = temp->quantity;

    return quantity;
}

void find_order_with_max_idp(Item* orders[], int idp) {
    int i = 0;
    int max_order = 0;
    int max_qtd = 0;

    while (orders[i] != NULL)
    {
        int qtd = get_order_item_quantity(idp, orders[i]);
        if (qtd > max_qtd)
        {
            max_qtd = qtd;
            max_order = i;
        }
        i++;
    }
    if (max_qtd == 0)
    {
        return;
    } else
    {
        printf("Maximo produto %d %d %d.\n", idp, max_order, max_qtd);
    }  
}

int item_weight(int idp, int qtd, Product products[]) {
    int weight = products[idp].weight * qtd;

    return weight;
}

int order_weight(Item* order, Product products[]) {
    int total = 0;
    Item* temp = order;

    while (temp != NULL)
    {
        int idp = temp->product_id;
        int qtd = temp->quantity;
        
        total += item_weight(idp, qtd, products);
        temp = temp->next;
    }
    
    return total;
}

void sort_print_products(Product original[], int size) {
    Product sorted[MAX_PRODUCTS];
    int i;
    for (i = 0; i < size; i++)
    {
        sorted[i] = original[i];
    }
/*     for (i = 0; i < size; i++)
    {
        printf("* %s %d %d\n", original[i].description, original[i].price, original[i].quantity);
    }
    for (i = 0; i < size; i++)
    {
        printf("* %s %d %d\n", sorted[i].description, sorted[i].price, sorted[i].quantity);
    } */
    sort_products_by_price(sorted, size);
/*     printf("Produtos\n");
    while (i < size)
    {
        printf("* %s %d %d\n", sorted[i].description, sorted[i].price, sorted[i].quantity);
        i++;
    } */ 
}

void swap(Product *xp, Product *yp) { 
    Product temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void sort_products_by_price(Product products[], int size) 
{ 
    int i, j, min_idx; 
   
    for (i = 0; i < size-1; i++) 
    {
        min_idx = i; 
        for (j = i+1; j < size; j++) 
          if (products[j].price < products[min_idx].price) 
            min_idx = j; 

        swap(&products[min_idx], &products[i]); 
    }
    printf("Produtos\n");
    for (i = 0; i < size; i++)
    {
        printf("* %s %d %d\n", products[i].description, products[i].price, products[i].quantity);
    }
}

void sort_print_order(Item* order, Product products[], int ide) {
    Item* temp;

    if (order->product_id < 0) temp = order->next;

    printf("Encomenda %d\n", ide);
    while (temp != NULL)
    {
        int price = products[temp->product_id].price;
        printf("* %s %d %d\n", products[temp->product_id].description, price, temp->quantity);
        temp = temp->next;
    }
}