#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>

#define MAX_IDP 10000
#define MAX_IDE 500
#define MAX_WEIGHT 200

typedef struct{
    char descricao[63];
    long preco;
    long peso;
    long stock;
    int idp;
} product;

typedef struct{
    char descricao[63];
    long preco;
    long peso;
    long stock;
    int idp;
} order;


product vector[MAX_IDP];  /* Vector of structures that saves the database of the products */
product orders [MAX_IDE][MAX_IDP];
order orderes [MAX_IDE][MAX_IDP];
char new_str[MAX_IDP];   /* String used to save the new product input in other format */
int sort[MAX_IDP];
int aux[MAX_IDP];
int ide_count;

int select_letter();
void formats_input();
void add_product(product v[]);
void add_stock(product v[]);
int create_order(int ide_count);
void add_prod2order(product o[MAX_IDE][MAX_IDP], product v[], int ide_count);
void rem_stock(product v[]);
void rem_prodorder(product o[MAX_IDE][MAX_IDP], product v[], int ide_count);
void order_cost(product o[MAX_IDE][MAX_IDP], product v[], int ide_count);
void change_price(product v[]);
void prod_order(product v[], product o[MAX_IDE][MAX_IDP], int ide_count);
void max_prod(product o[MAX_IDE][MAX_IDP], product v[], int ide_count);
void merge_sort(int sort[], int l, int r);
void merge(int sort[], int left, int m, int right);
void merge_prices(product v[]);
void merge_description(product o[MAX_IDE][MAX_IDP], product v[], int ide_count);

int main(){

    while(select_letter());   /* Searches for a new letter */

    return 0;
}

/* Selects the command for each letter given */
int select_letter(){
    char command;

    command = getchar();
    switch (command){
        case 'a': add_product(vector); return 1;  /* Adds a new product to the system */

        case 'q': add_stock(vector); return 1;         /* Adds stock to an existing product */

        case 'N': ide_count = create_order(ide_count); return 1;  /* Creates a new order */

        case 'A': add_prod2order(orders, vector, ide_count); return 1;  /* Adds a new product to a order */

        case 'r': rem_stock(vector); return 1;  /* Removes stock from an existing product */

        case 'R': rem_prodorder(orders, vector, ide_count); return 1;  /* Removes a product form an order */

        case 'C': order_cost(orders, vector, ide_count); return 1;  /* Calculates the cost of an order */

        case 'p': change_price(vector); return 1;  /* Changes the price of a product in the system */

        case 'E': prod_order(vector, orders, ide_count); return 1;  /* Returns the caracteristics of a product in an order */

        case 'm': max_prod(orders, vector, ide_count); return 1;  /* Returns the idp of an order where a product is more frequent */

        case 'l': merge_prices(vector); return 1;  /* Lists all the products existent in the system by price order */

        case 'L': merge_description(orders, vector, ide_count); return 1;  /* List all the products existent in an order by alphabetic order of the description */

        case 'x': return 0;  /* Ends the program */

        default: return 1;
    }
}

void formats_input(){
    int i2=0, c;
    while ((c = getchar()) != '\n')
    {
        if (c == ':'){
            c = ' ';
            new_str[i2] = c;
            i2++;
        }
        else
        {
            new_str[i2] = c;
            i2++;
        }
    }
   new_str[i2] = '\0';     
}

void add_product(product v[]){
    int i = 0;

    while (v[i].peso != 0){
        i++;
    }
    v[i].idp = i;
        
    formats_input();
    sscanf(new_str, "%s%ld%ld%ld", v[i].descricao, &v[i].preco, &v[i].peso, &v[i].stock);
    printf("Novo produto %d.\n", v[i].idp);
}

void add_stock(product v[]){
    int idp_comp;
    long qtd_add;

    formats_input();
    sscanf(new_str, "%d%ld", &idp_comp, &qtd_add);
    
    if (v[idp_comp].preco != 0){
        v[idp_comp].stock += qtd_add;
    } 
    else
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_comp);
    }
    
}

int create_order(int ide_count){

    printf("Nova encomenda %d.\n", ide_count);
    ide_count++;
    return ide_count;
}

void add_prod2order(product o[MAX_IDE][MAX_IDP], product v[], int ide_count){
    int ide, idp, qtd, peso_total = 0;
    int i = 0;
    
    formats_input();
    sscanf(new_str, "%d%d%d", &ide, &idp, &qtd);
    if (ide >= ide_count){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    else if (v[idp].peso == 0){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    else if (v[idp].stock < qtd) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }

    o[ide][idp].stock += qtd;
    v[idp].stock -= qtd; 
    
    for(i=0; i < MAX_IDP; i++){
        if(o[ide][i].stock > 0){
            peso_total += o[ide][i].stock * v[i].peso;
        }
    }
    

    if (peso_total > 200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        o[ide][idp].stock -= qtd;
        v[idp].stock += qtd; 
    }
}

void rem_stock(product v[]){
    int idp, qtd;
    int i = 0;

    formats_input();
    sscanf(new_str, "%d%d", &idp, &qtd);

    while (v[i].peso > 0)
    {
        i++;
    }
        
    if (idp >= i)
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }
    v[idp].stock -= qtd;

    if (v[idp].stock < 0)
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        v[idp].stock += qtd;
        return;
    }
    
}

void rem_prodorder(product o[MAX_IDE][MAX_IDP], product v[], int ide_count){
    int idp, ide;
    int i = 0;

    formats_input();
    sscanf(new_str, "%d%d", &ide, &idp);
    

    if (ide >= ide_count)
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }

    while(v[i].peso > 0){
        i++;
    }

    if (idp >= i)
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }

    v[idp].stock += o[ide][idp].stock;
    o[ide][idp].stock = 0;
}

void order_cost(product o[MAX_IDE][MAX_IDP], product v[], int ide_count){
    int ide;
    int total_cost = 0;
    int i = 0;

    scanf("%d", &ide);

    if (ide >= ide_count)
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    for(i= 0; i < MAX_IDP; i++){
        total_cost += v[i].preco * o[ide][i].stock;
    }
    printf("Custo da encomenda %d %d.\n", ide, total_cost);
    
}

void change_price(product v[]){
    int i = 0;
    int idp, price = 0;

    formats_input();
    sscanf(new_str, "%d%d", &idp, &price);

    while (v[i].peso > 0)
    {
        i++;
    }
    if (i <= idp){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }
    v[idp].preco = price;
}

void prod_order(product v[], product o[MAX_IDE][MAX_IDP], int ide_count){
    
    int idp, ide;
    int i = 0;

    formats_input();
    sscanf(new_str, "%d%d", &ide, &idp);
    

    if (ide >= ide_count)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    while(v[i].peso > 0){
        i++;
    }

    if (idp >= i)
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }

    printf("%s %ld.\n", v[idp].descricao, o[ide][idp].stock);
}

void max_prod(product o[MAX_IDE][MAX_IDP], product v[], int ide_count){
    int idp, ide;
    int i = 0, i2 = 0;
    int maior = 0;

    scanf("%d", &idp);

    while(v[i].peso > 0){
        i++;
    }

    if (idp >= i)
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }

    for(i2 = 0; i2 <= ide_count; i2++){
        if (o[i2][idp].stock > maior){
            maior = o[i2][idp].stock;
            ide = i2;
        }
    }
    if(maior > 0){
        printf("Maximo produto %d %d %d.\n", idp, ide, maior);
    }
} 

void merge_sort(int sort[], int l, int r){
    int m = (r+l)/2;
    if (r <= l) return;
    merge_sort(sort, l, m);
    merge_sort(sort, m+1, r);
    merge(sort, l, m, r);
}

void merge(int sort[], int left, int m, int right)
{ 
  int i, j, k;
  for (i = m+1; i > left; i--) 
    aux[i-1] = sort[i-1];
  for (j = m; j < right; j++)
    aux[right+m-j] = sort[j+1];
  for (k = left; k <= right; k++)
    if (aux[j]< aux[i] || i > m)
      sort[k] = aux[j--];
    else
      sort[k] = aux[i++];
}

void merge_prices(product v[]){
    int i = 0;
    int prices[MAX_IDP];
    int i2 = 0, i3 = 0;

    while (v[i].preco > 0)
    {
        prices[i] = v[i].preco;
        i++;
    }

    merge_sort(prices, 0, i - 1);


    printf("Produtos\n");
    for(i2= 0; i2 <= i; i2++){
        for(i3 = 0; i3 < i; i3++){
            if(v[i3].preco == prices[i2] && v[i3].preco != prices[i2 -1]){
            printf("* %s %ld %ld\n", v[i3].descricao, v[i3].preco, v[i3].stock);
            }
        }
    }
}

void merge_description(product o[MAX_IDE][MAX_IDP], product v[], int ide_count){
    int ide;
    int products[MAX_IDP];
    int i, i2 = 1, i3; 

    scanf("%d", &ide);

    if (ide >= ide_count){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.", ide);
    }

    for (i = 0; i < MAX_IDP; i++){
        if(o[ide][i].stock > 0){
            products[i] = v[i].descricao[0];
        }
    }
    while (o[ide][i2].stock > 0)
    {
        i2++;
    }
    
    merge_sort(products, 0, i2);
    i2 = 0;
    while (o[ide][i2].stock > 0)
    {
        i2++;
    }
    printf("Encomenda %d.\n", ide);
    for (i3 = 0; i3 < i2 - 1; i3++){
        if (products[i3] != 0){
            printf("%s %ld %ld na %d\n", v[i3].descricao, v[i3].preco, o[ide][i3].stock, ide);
        }
    }
}
