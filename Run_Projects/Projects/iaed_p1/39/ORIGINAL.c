#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* definicao de constantes */

#define MAX_deliveries 500
#define MAX_PRODUCTS 10000
#define MAX_INPUT 220

/*numero total de produtos e encomendas*/

int products = 0; 
int deliveries = 0;

/*estrutura de um produto*/

typedef struct{
    int ID;
    char description[64];
    int price;
    int weight;
    int amount;
}Product;

/* estrutura de uma encomenda */

typedef struct{
    Product products[MAX_PRODUCTS];
    int delivery_weight;
    int delivery_ID;
    int different_products;
}Delivery;

/* vetores com todos os produtos/ encomendas/ produtos ordenados */

Product all_products[MAX_PRODUCTS];
Delivery company[MAX_deliveries];
Product all_products_sort[MAX_PRODUCTS];
Product temporary;

/* funcoao auxiliar que verifica a existencia de um produto */

int Exists_Product(int product_ID){
    if (product_ID >= products)
        return 0;
    return 1;
}

/* funcoao auxiliar que verifica a existencia de uma encomenda */

int Exists_Delivery(int delivery_ID){
    if (delivery_ID >= deliveries)
        return 0;
    return 1;
}

/* adicona um produto ao vetor de produtos */

void add_product(){
    char input[MAX_INPUT];
    fgets(input,MAX_INPUT,stdin);
    sscanf(input, "%[^:]:%d:%d:%d", all_products[products].description, &all_products[products].price, &all_products[products].weight, &all_products[products].amount);
    all_products[products].ID = products;
    printf("Novo produto %d.\n", products);
    products ++;;

}

/* aumenta o amount de uma determnado produto */

void add_amount(){
    char input[MAX_INPUT];

    int product_ID;
    int _amount;

    fgets(input,MAX_INPUT,stdin);
    sscanf(input, "%d:%d", &product_ID, &_amount);

    if (Exists_Product(product_ID) == 0){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", product_ID);
        return;
    } 
    all_products[product_ID].amount += _amount;
}

/* adiciona uma encomenda ao vetor de encomendas */

void add_delivery(){
    company[deliveries].delivery_ID = deliveries;
    company[deliveries].delivery_weight = 0;
    company[deliveries].different_products = 0;
    printf("Nova encomenda %d.\n", deliveries);
    deliveries ++;

}

/* adicona um produto a uma encomenda, sendo esse vetor adicionado por ordem de posicao crescente, ou seja, na poscao diferent_products da struct de uma encomenda */

void add_product_to_delivery(){
    int delivery_ID;
    int product_ID;
    int k;
    int _amount;

    char input[MAX_INPUT];
    fgets(input,MAX_INPUT,stdin);
    sscanf(input, "%d:%d:%d",&delivery_ID ,&product_ID, &_amount);


    if (Exists_Delivery(delivery_ID) == 0){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", product_ID, delivery_ID);
        return;
    }
    if (Exists_Product(product_ID) == 0){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", product_ID, delivery_ID);
        return;
    }
    if (all_products[product_ID].amount  < _amount){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", product_ID, delivery_ID);
        return;
    }
    if ((company[delivery_ID].delivery_weight + (all_products[product_ID].weight * _amount)) > 200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",product_ID, delivery_ID);
        return;
    }    
                
    for (k=0;k<company[delivery_ID].different_products; k++){
        if(company[delivery_ID].products[k].ID == product_ID){
            company[delivery_ID].products[k].amount += _amount;
            all_products[product_ID].amount =  all_products[product_ID].amount - _amount;
            company[delivery_ID].delivery_weight += (all_products[product_ID].weight * _amount);
            return;
            }
        }                              
        company[delivery_ID].delivery_weight += (all_products[product_ID].weight * _amount);
        all_products[product_ID].amount =  all_products[product_ID].amount - _amount;
        company[delivery_ID].products[company[delivery_ID].different_products] = all_products[product_ID];
        company[delivery_ID].products[company[delivery_ID].different_products].amount = _amount;
        company[delivery_ID].different_products ++;
        return;
    }

/* remove uma determnada quantidade do stock de um produto no vetor de produtos */

void remove_product_stock(){
    int _amount;
    int product_ID;
    char input[MAX_INPUT];
    fgets(input,MAX_INPUT,stdin);
    sscanf(input, "%d:%d",&product_ID,&_amount);

    if (Exists_Product(product_ID) == 0){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",product_ID);
        return;
    }
    if (all_products[product_ID].amount < _amount){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", _amount ,product_ID);
        return;
    }

    all_products[product_ID].amount -=_amount;
}

/* remove um produto do vetor de produtos de uma encomenda */

void remove_delivery_product(){
    int delivery_ID;
    int product_ID;
    int i;
    char input[MAX_INPUT];
    fgets(input,MAX_INPUT,stdin);
    sscanf(input, "%d:%d",&delivery_ID ,&product_ID);

     if (Exists_Delivery(delivery_ID) == 0){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", product_ID, delivery_ID);
        return;
    }
    if (Exists_Product(product_ID) == 0){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", product_ID, delivery_ID);
        return;
    }

    /* ao inves de remover um produto, troco o ultimo produto com o produtoq ue quero remover e removo uma unidade a variavel different products para quando voltar a adicionar um produto ele escrever por cima daquele que supostamente seria apagado */

    for(i =0 ; i<company[delivery_ID].different_products; i++){
        if(company[delivery_ID].products[i].ID == product_ID){ 
            company[delivery_ID].delivery_weight -= company[delivery_ID].products[i].weight * company[delivery_ID].products[i].amount;
            all_products[product_ID].amount += company[delivery_ID].products[i].amount;     
            temporary = company[delivery_ID].products[company[delivery_ID].different_products-1];
            company[delivery_ID].products[company[delivery_ID].different_products-1] = company[delivery_ID].products[i];
            company[delivery_ID].products[i] = temporary;
            company[delivery_ID].different_products--;
            return;
        }
    }
}

/* calcula o valor de uma encomenda percorrendo todas as respetiivas quantidades e precos de cada produto, somando tudo e dando um full price */

void price_generator(){
    char input[MAX_INPUT];
    int delivery_ID;
    int i;
    int full_price = 0;
    fgets(input,MAX_INPUT,stdin);
    sscanf(input, "%d",&delivery_ID);

    if (Exists_Delivery(delivery_ID) == 0){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", delivery_ID);
        return;
    }
    for (i = 0; i<company[delivery_ID].different_products; i++){       
        full_price += company[delivery_ID].products[i].price * company[delivery_ID].products[i].amount;
    }
    printf("Custo da encomenda %d %d.\n",delivery_ID, full_price);  
}

/* altera o preco de uma produto e tambem em todos os produtos que estao em encomendas */

void price_change(){
    char input[MAX_INPUT];
    int product_ID;
    int price;
    int k,j;
    fgets(input,MAX_INPUT,stdin);
    sscanf(input, "%d:%d",&product_ID, &price);

    if(Exists_Product(product_ID) == 0){ 
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", product_ID );
        return;
        }

    all_products[product_ID].price = price;
    for(k=0; k<deliveries; k++){
        for (j =0; j< company[k].different_products; j++){
            if (company[k].products[j].ID == product_ID){
                company[k].products[j].price = price;
            }
        }   
    }         
}

/* procura um produto numa encomenda */

void look_product(){
    char input[MAX_INPUT];
    int product_ID;
    int delivery_ID;
    int i;
    fgets(input,MAX_INPUT,stdin);
    sscanf(input, "%d:%d",&delivery_ID ,&product_ID);

    if (Exists_Delivery(delivery_ID) == 0){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",delivery_ID);
        return;
    }

    if(Exists_Product(product_ID) == 0){
        printf("Impossivel listar produto %d. Produto inexistente.\n", product_ID);
        return;
    }
    
    for (i=0; i<company[delivery_ID].different_products; i++){
        if(company[delivery_ID].products[i].ID == product_ID){
            printf("%s %d.\n", company[delivery_ID].products[i].description, company[delivery_ID].products[i].amount);
            return;
        }            
    }
    printf("%s %d.\n", all_products[product_ID].description, 0);
}

/* funcao que percorre todas as encomendas, cujo objetivo e encontrar a encomenda em que esse determinado produto tem o maior amount, acaso haja o mesmo amount, escolhe a encomenda com ID menor */

void product_ocurrences(){
    char input[MAX_INPUT];
    int product_ID;
    int j;
    int k;
    int max = 0;
    int max_ID;
    fgets(input,MAX_INPUT,stdin);
    sscanf(input, "%d",&product_ID);

    if(Exists_Product(product_ID) == 0){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", product_ID);
        return;
    }

    /* se encontrar um valor max maior ele atualzia, caso seja igual atualiza se o ID for mais baixo */

    for (j = 0; j< deliveries; j++){
        for (k =0; k < company[j].different_products;k++){
            if(company[j].products[k].ID == product_ID){
                if(company[j].products[k].amount > max){
                    max = company[j].products[k].amount;
                    max_ID = company[j].delivery_ID;
                }
                else{
                    if (company[j].products[k].amount == max){
                        if(company[j].delivery_ID < max_ID){
                            max_ID = company[j].products[k].ID;                           
                        }
                    }
                }
            }
        }
    }
    if (max != 0)
        printf("Maximo produto %d %d %d.\n", product_ID, max_ID, max); 
}

/* aplicacao do algortmo mergesort para ordenar o vetor sort por letra */

void merge_letter(int left, int m, int right){
    Product aux[MAX_PRODUCTS];
    int i, j, k;
    for (i = m+1; i > left; i--)
        aux[i-1] = all_products_sort[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = all_products_sort[j+1];
    for (k = left; k <= right; k++)
        if (strcmp(aux[j].description,aux[i].description) < 0){
            all_products_sort[k] = aux[j--];
            }               
        else
            all_products_sort[k] = aux[i++];
}

void mergesort_letter(int left, int right) {
    int m = (right+left)/2;
    if (right <= left)
        return;
    mergesort_letter(left, m);
    mergesort_letter(m+1, right);
    merge_letter(left, m, right);
}

/* aplicacao do algortmo mergesort para ordenar o vetor sort por preco */

void merge_price(int left, int m, int right){
    Product aux[MAX_PRODUCTS];
    int i, j, k;
    for (i = m+1; i > left; i--)
        aux[i-1] = all_products_sort[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = all_products_sort[j+1];
    for (k = left; k <= right; k++)
        if (aux[j].price < aux[i].price)
            all_products_sort[k] = aux[j--];
        else if (aux[j].price == aux[i].price && aux[j].ID < aux[i].ID){
                all_products_sort[k] = aux[j--];
            }
        else
            all_products_sort[k] = aux[i++];
}

void mergesort_price(int left, int right) {
    int m = (right+left)/2;
    if (right <= left)
        return;
    mergesort_price(left, m);
    mergesort_price(m+1, right);
    merge_price(left, m, right);
}

/* e utiilizada a funcao mergesort num vetor para ordenar e depois da print dos produtos desse vetor por ordem */

void price_list(){
    int i;

    for (i = 0; i<products; i++){
        all_products_sort[i] = all_products[i];
    }

    mergesort_price(0,products-1);
    
    printf("Produtos\n");
    for (i = 0; i<products; i++){
        printf("* %s %d %d\n", all_products_sort[i].description, all_products_sort[i].price, all_products_sort[i].amount);
    }
    for (i = 0; i<products; i++){
        all_products_sort[i].amount = 0;
    }
}

/* e utiilizada a funcao mergesort num vetor para ordenar e depois da print dos produtos desse vetor por ordem */

void letter_order(){
    char input[MAX_INPUT];
    int i;
    int delivery_ID;
    fgets(input,MAX_INPUT,stdin);
    sscanf(input, "%d",&delivery_ID);

    if (Exists_Delivery(delivery_ID) == 0){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", delivery_ID);
        return;
    } 
    if (company[delivery_ID].different_products == 0){
        printf("Encomenda %d\n", delivery_ID);
        return;
    }

    for (i = 0; i<company[delivery_ID].different_products; i++){
        all_products_sort[i] = company[delivery_ID].products[i];
    }
    
    mergesort_letter(0,company[delivery_ID].different_products-1);

    printf("Encomenda %d\n", delivery_ID);
    for (i = 0; i<company[delivery_ID].different_products; i++){
        if (all_products_sort[i].amount != 0)
            printf("* %s %d %d\n", all_products_sort[i].description, all_products_sort[i].price, all_products_sort[i].amount);
    }
    for (i = 0; i<company[delivery_ID].different_products; i++){
        all_products_sort[i].amount = 0;
    }
}

/* switchcase que determna qual a funcao que sera utilizada */

int main(){
    char function;
    do{
        function = getchar();
        getchar();
        switch (function){
        case 'a':
            add_product();
            break;
        case 'q':
            add_amount();
            break;
        case 'N':
            add_delivery();
            break;
        case 'A':
            add_product_to_delivery();
            break;
        case 'r':
            remove_product_stock();
            break;
        case 'R':
            remove_delivery_product();
            break;
        case 'C':
            price_generator();
            break;
        case 'p':
            price_change();
            break;
        case 'E':
            look_product();
            break;
        case 'm':
            product_ocurrences();
            break;
        case 'l':
            price_list();
            break;
        case 'L':
            letter_order();
            break;
        }
    }while (function != 'x');
    return 0;
}

