#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_PRODUCTS 9999
#define MAX_ORDERS 499
#define DESC_LENGTH 64


#define ADD_PRODUCT 'a'
#define CHANGE_QUANTITY 'q'
#define NEW_ORDERID 'N'
#define NEW_ORDER 'A'
#define REMOVE_STOCK 'r'
#define REMOVE_ORDER 'R'
#define ORDER_COST 'C'
#define ALTER_PRICE 'p'
#define DISCRIPT_ORDER 'E'
#define MOST_ORDERED 'm'
#define LIST_PRODUCTS 'l'
#define ALPHA_ORDER 'L'
#define LEAVE 'x'


void add_product(char args[]);
void add_to_quantity(char args[]);
void new_orderid();
void new_order(char args[]);
void remove_stock(char args[]);
void remove_order(char args[]);
void order_cost(char args[]);
void alter_price(char args[]);
void discript_order(char args[]);
void most_ordered(char args[]);
void list_products();
void alpha_order(char args[]);


struct product {
    int id;
    char desc[DESC_LENGTH];
    int price;
    int weight;
    int quantity;
};


struct order {
    int number_product;
    int peso;
    struct product product_toorder[200];
};


struct product products[MAX_PRODUCTS];
/* counter representa o numero de produtos na array de produtos */
int counter = 0;
struct order orders[MAX_ORDERS];
/* order_counter representa o numero de encomendas na array de encomendas */
int order_counter = 0;

/* a main avalia o primeiro char (funcao a executar) e atravez de um switch corre a funcao */
int main() {
    char function;
    char args[100];
    int stop = 0;
    while (function != 'x' && stop == 0) {
        scanf(" %c", &function);
        switch (function) {
            case ADD_PRODUCT:
                scanf(" %s", args);
                add_product(args);
                break;

            case CHANGE_QUANTITY:
                scanf(" %s", args);
                add_to_quantity(args);
                break;

            case NEW_ORDERID:
                new_orderid();
                break;

            case NEW_ORDER:
                scanf("%s", args);
                new_order(args);
                break;

            case REMOVE_STOCK:
                scanf("%s", args);
                remove_stock(args);
                break;

            case REMOVE_ORDER:
                scanf("%s", args);
                remove_order(args);
                break;

            case ORDER_COST:
                scanf("%s", args);
                order_cost(args);
                break;

            case ALTER_PRICE:
                scanf("%s", args);
                alter_price(args);
                break;

            case DISCRIPT_ORDER:
                scanf("%s", args);
                discript_order(args);
                break;

            case MOST_ORDERED:
                scanf("%s", args);
                most_ordered(args);
                break;

            case LIST_PRODUCTS:
                list_products();
                break;

            case ALPHA_ORDER:
                alpha_order(args);
                break;

            case LEAVE:
                stop = 1;
                break;
        }
    }
    return 0;
}

/* a funcao cria um novo produto atravez da estrutura definida anteriormente */
void add_product(char args[]) {
    struct product new_product;
    /* atribui os dados ao produto */
    strcpy(new_product.desc, strtok(args, ":"));
    new_product.price = atoi(strtok(NULL, ":"));
    new_product.weight = atoi(strtok(NULL, ":"));
    new_product.quantity = atoi(strtok(NULL, ":"));
    new_product.id = counter;
    /* adiciona o produto a array de produtos */
    products[counter] = new_product;
    /* cada vez que se cria um novo produto, incrementa o counter que representa o numero de produtos. */
    counter++;

    /* retorna o id do produto */
    printf("Novo produto %d.\n", products[counter - 1].id);
}


/* adiciona uma quantidade ao produto */
void add_to_quantity(char args[]) {
    int i = atoi(strtok(args, ":"));
    /* verifica os argumentos */
    if (i >= counter) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", i);
        return;
    }
    /* se os argumentos sao validos, adiciona a quantidade ao id desejado */
    else {
        products[i].quantity += atoi(strtok(NULL, ":"));
    }
}

/* cria uma nova encomenda */
void new_orderid() {
    struct order new__order;
    new__order.peso = 0;
    new__order.number_product = 0;
    /* adiciona a encomenda a array de encomendas */
    orders[order_counter] = new__order;
    /* retorna o id da encomenda */
    printf("Nova encomenda %d.\n", order_counter);
    order_counter++;
}

/* adiciona um produto a uma encomenda existente */
void new_order(char args[]) {
    int i = 0;
    int e;
    /* retira dados para a funcao */
    int id_order = atoi(strtok(args, ":"));
    int id_prod = atoi(strtok(NULL, ":"));
    int qtd = atoi(strtok(NULL, ":"));
    /* verifica se a encomenda existe na array de encomendas*/
    if (id_order >= order_counter) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_prod, id_order);
        return;
    }
    /* verifica se o produto existe na array de encomendas*/
    else if (id_prod >= counter) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_prod, id_order);
        return;
    }
    /* verifica se existe quantidade suficiente no stock do produto para fazer a encomenda */
    else if (qtd > products[id_prod].quantity) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_prod, id_order);
        return;
    }
    /* verifica se ultrapssa o limite de peso */
    else if (products[id_prod].weight * qtd > 200) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_prod, id_order);
        return;
    }
    /* verifica se o produto ja existe na encomenda e se sim adiciona quantidade */
    for (e = 0; e <= orders[id_order].number_product; e++) {
        if (strcmp(orders[id_order].product_toorder[e].desc, products[id_prod].desc) == 0) {
            /* verifica de a soma do peso da encomenda com o peso novo passa o limite */
            if (orders[id_order].peso + products[id_prod].weight * qtd > 200) {
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_prod, id_order);
                return;
            }
            orders[id_order].product_toorder[e].quantity += qtd;
            i += 1;
            break;
        }
    }
    /* se o produto nao existe na encomenda, adiciona produto */
    if (i == 0) {
        if (orders[id_order].peso + products[id_prod].weight * qtd > 200) {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_prod, id_order);
            return;
        }
        orders[id_order].product_toorder[orders[id_order].number_product].quantity = qtd;
        strcpy(orders[id_order].product_toorder[orders[id_order].number_product].desc, products[id_prod].desc);
        orders[id_order].product_toorder[orders[id_order].number_product].id = id_prod;
        orders[id_order].product_toorder[orders[id_order].number_product].weight = products[id_prod].weight;
        orders[id_order].product_toorder[orders[id_order].number_product].price = products[id_prod].price;
        /* e aumenta o numero de produtos da encomenda na sua estrutura */
        orders[id_order].number_product += 1;
    }
    /* aumenta o peso da encomenda */
    orders[id_order].peso += products[id_prod].weight * qtd;
    /* retira o stock adicionado a encomenda ao stock do produto */
    products[id_prod].quantity -= qtd;
}


/* retira stock a encomenda */
void remove_stock(char args[]) {
    /* retira dados para a funcao */
    int id_prod = atoi(strtok(args, ":"));
    int qtd = atoi(strtok(NULL, ":"));
    /* verifica se o id do produto e valido */
    if (id_prod >= counter) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_prod);
        return;
    }
    /* verifica se o stock retirado e maior do que o stock existente */
    else if (products[id_prod].quantity - qtd < 0) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd, id_prod);
        return;
    }
    /* retira stock */
    products[id_prod].quantity -= qtd;
}


/* retira um produto da encomenda */
void remove_order(char args[]) {
    /* retira dados para a funcao */
    int id_order = atoi(strtok(args, ":"));
    int id_product = atoi(strtok(NULL, ":"));
    int e, i;
    /* verifica se o id da encomenda e valido */
    if (id_order >= order_counter) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_product, id_order);
        return;
    }
    /* verifica se o id do produto e valido */
    else if (id_product >= counter) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_product, id_order);
        return;
    }
    /* procura o produto que se pretende apagar dentro da encomenda */
    for (e = 0; e < orders[id_order].number_product; e++) {
        if (id_product == orders[id_order].product_toorder[e].id) {
            /* se entra neste ciclo significa que encontrou o produto, logo retira o peso do produto na encomenda e adiciona a stock a sua quantidade */
            orders[id_order].peso -= orders[id_order].product_toorder[e].quantity * orders[id_order].product_toorder[e].weight;
            products[id_product].quantity += orders[id_order].product_toorder[e].quantity;
            /* a partir do index do produto que se pretende apagar (exclusive) move todos os produtos seguintes para o index anterior */
            for (i = e; i <= orders[id_order].number_product; i++) {
                orders[id_order].product_toorder[i] = orders[id_order].product_toorder[i + 1];
            }
            /* retira um ao numero de produtos dentro da encomenda */
            orders[id_order].number_product -= 1;
            break;
        }
    }
}

/* devolve o custo a encomenda desejada */
void order_cost(char args[]) {
    /* retira dados para a funcao */
    int id_order = atoi(args);
    int e;
    /* define um int que vai representar o preco total da encomenda */
    int price = 0;
    /* verifica se o id da encomenda e valido */
    if (id_order >= order_counter) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_order);
        return;
    }
    /* percorre todos os produtos da encomenda e soma ao price */
    for (e = 0; e < orders[id_order].number_product; e++) {
        price += orders[id_order].product_toorder[e].quantity * orders[id_order].product_toorder[e].price;
    }
    /* devolve o custo da encomenda */
    printf("Custo da encomenda %d %d.\n", id_order, price);
}

/* altera o preco de um produto */
void alter_price(char args[]) {
    /* retira dados para a funcao */
    int id_product = atoi(strtok(args, ":"));
    int price = atoi(strtok(NULL, ":"));
    int e, i;
    /* verifica se o id do produto e valido */
    if (id_product >= counter) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_product);
        return;
    }
    /* altera o preco do produto na lista de produtos */
    products[id_product].price = price;
    /* percorre todas as encomendas e altera o preco do produto se este pertencer a encomenda */
    for (e = 0; e < order_counter; e++) {
        for (i = 0; i < orders[e].number_product; i++) {
            if (id_product == orders[e].product_toorder[i].id) {
                orders[e].product_toorder[i].price = price;
                break;
            }
        }
    }
}


/* devolve a quantidade de um produto pretendido na encomenda pretendida */
void discript_order(char args[]) {
    /* retira dados para a funcao */
    int id_order = atoi(strtok(args, ":"));
    int id_product = atoi(strtok(NULL, ":"));
    int e;
    /* verifica se o id da encomenda e valido */
    if (id_order >= order_counter) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_order);
        return;
    }
    /* verifica se o id do produto e valido */
    else if (id_product >= counter) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", id_product);
        return;
    }
    /* percorre a encomenda  ate encontrar o id do produto */
    for (e = 0; e < orders[id_order].number_product; e++) {
        /* quando econtra o id, devolve a sua quantidade */
        if (id_product == orders[id_order].product_toorder[e].id) {
            printf("%s %d.\n", orders[id_order].product_toorder[e].desc, orders[id_order].product_toorder[e].quantity);
        }
            /* caso nao tenham encomendado o produto na encomenda devolve a quantidade que e 0 */
        else {
            printf("%s %d.\n", orders[id_order].product_toorder[e].desc, 0);
        }
    }
}


/* lista o identificador da encomenda em que o produto dado ocorre mais vezes  */
void most_ordered(char args[]) {
    /* retira dados para a funcao */
    int id_product = atoi(args);
    int e;
    int i;
    /* cria uma array em que o seu primeiro termo corresponde ao id da encomenda e o segundo a quantidade que foi nesta pedido do produto pretendido */
    int max[2] = {-1, -1};
    int existe = 0;
    /* verifica se o id do produto e valido */
    if (id_product >= counter) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_product);
        return;
    }
    /* percorre todas as encomendas */
    for (e = 0; e < order_counter; e++) {
        for (i = 0; i < orders[e].number_product; i++) {
            /* se o produto e o produto pretendido e a sua quantidade e maior do que a sua quantidade anterior, atualiza o novo maximo com a sua respetiva encomenda */
            if (orders[e].product_toorder[i].id == id_product && max[1] < orders[e].product_toorder[i].quantity) {
                max[0] = e;
                max[1] = orders[e].product_toorder[i].quantity;
                /* atualiza o int existe que garante que o produto foi encomendado pelo menos uma vez */
                existe += 1;
                break;
            }
        }
    }
    /* apos percorrer todas as encomendas e nao encontrar nenhuma encomenda do produto, retorna NADA */
    if (existe == 0) {
        return;
    }
    /* caso existir maximo, retorna o id do produto, o id da encomenda e a sua quandidade encomendada nesta */
    else {
        printf("Maximo produto %d %d %d.\n", id_product, max[0], max[1]);
    }
}


/* retorna uma lista de todos os produtos em ordem crescente de preco */
void list_products() {
    int e;
    int min;
    int tobreak = 0;
    printf("Produtos\n");
    /* percorrer todos os produtos e comparar com o minimo, se for igual devolve a sua informacao, caso contrario incrementa o minimo */
    /* caso ja fez printf de todos os elementos a funcao acaba */
    for (min = 0; tobreak != counter; min++)
        for (e = 0; e < counter; e++) {
            if (products[e].price == min) {
                printf("* %s %d %d\n", products[e].desc, products[e].price, products[e].quantity);
                tobreak++;
            }
        }
}


/* devolve o nome de todos os produtos de uma encomenda por ordem alfabetica */
void alpha_order(char args[]) {
    /* retira dados para a funcao */
    /* cria uma lista auxiliar para facilitar as trocas de posicao */
    char aux[64];
    int id_order = atoi(args);
    int i, e;
    /* cria uma lista auxiliar onde se vai colocar todas a descricoes dos produtos */
    char all[200][9999];
    /* verifica se o id da encomenda e valido */
    if (id_order >= order_counter) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_order);
        return;
    }
    printf("Encomenda %d\n", id_order);
    /* coloca todas os nomes das encomendas numa array */
    for (i = 0; i < orders[id_order].number_product; i++) {
        strcpy(all[i], orders[id_order].product_toorder[i].desc);
    }
    /* percorre todos os nomes e compara, trocando os com a array aux */
    for (i = 0; i <= orders[id_order].number_product; i++) {
        for (e = i + 1; e <= orders[id_order].number_product; e++) {
            if (strcmp(all[i], all[e]) > 0) {
                strcpy(aux, all[i]);
                strcpy(all[i], all[e]);
                strcpy(all[e], aux);
            }
        }
    }
    /* devolve todos os produtos por ordem alfabetica */
    for (i = 0; i < orders[id_order].number_product; i++) {
        for (e = 0; e < orders[id_order].number_product; e++) {
            if (strcmp(all[i], orders[id_order].product_toorder[e].desc)) {
                printf("* %s %d %d\n", all[i], orders[id_order].product_toorder[e].price,
                       orders[id_order].product_toorder[e].quantity);
                break;
            }
        }
    }
}