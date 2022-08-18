#include <stdio.h>
#include <string.h>


#define DESCRIPTION_MAX 64   /* Limite dimensao descricao produtos */
#define ORDER_PRODUCT_MAX 200 /* Maximo de produtos por encomenda */
#define ORDER_WEIGHT_MAX 200  /* Maximo peso por encomenda */
#define ORDERS_MAX 500        /* Nr maximo de encomendas */
#define PRODUCE_MAX 10000     /* Nr maximo de produtos */
#define END 'x'              /* Comando encerrar programa */
#define ADD_PRODCT 'a'       /* Comando adicionar produto */
#define ADD_STOCK 'q'        /* Comando adicionar stock a produto */
#define ORDER 'N'            /* Comando adicionar encomenda */
#define ADD_2_ORD 'A'        /* Comando adicionar produto a encomenda */
#define RMOVE_STK 'r'        /* Comando remover stock a produto */
#define RMV_FROM_ORD 'R'     /* Comando remover produto de encomenda */
#define COST 'C'             /* Comando obter custo de encomenda */
#define CHNG_PRICE 'p'       /* Comando alterar preco produto */
#define PRODCT_IN_ORD 'E'    /* Comando obter descricao e qtd de produto em encomenda */
#define ORDER_WITH_MOST 'm'  /* Comando obter encomenda com mais qtd de um produto */
#define LIST_PRODUCE 'l'     /* Comando listar todos os produtos por preco */
#define LIST_ORDER 'L'       /* Comando obter produtos de encomenda por ordem alfabetica */



/* STRUCTURES */

/* Estrutura 'Product', inclui toda informacao necessaria (preco, id, descricao, peso, stock) */
typedef struct{
    int identifier;
    char description[DESCRIPTION_MAX];
    int price;
    int weight;
    int stock;
}Product;

/* Estrutura Product_resumido, == a Product mas sem peso para poupar memoria no vetor products em baixo */
typedef struct{
    int identifier;
    int order_stock;
    int price;
    char description[DESCRIPTION_MAX];
}Product_resumido;

/* Estrutura 'Order', inclui vetor de Product_resumido da encomenda e restante informacao(id, peso total, preco total, nr de produtoss) */
typedef struct{
    Product_resumido products[ORDER_PRODUCT_MAX];
    int total_weight;
    int total_price;
    int identifier;
    int nr_of_prod;
}Order;


/* PROTOTYPES */

void add_prod(char descrp[], int p, int w, int s);
void add_stock(int prd_id, int qtd);
void new_order();
void add_to_order(int ord_id, int prd_id, int qtd);
void remove_prd(int prd_id, int qtd);
void remove_from_ord(int ord_id, int prd_id);
void order_price(int ord_id);
void change_price(int prd_id, int price);
void list_prd(int ord_id, int prd_id);
void most_order(int prd_id);
void list_all();
void list_order(int ord_id);
void quicksort(Product_resumido list[], int left, int right, char mode);
int partition_l(Product_resumido list[], int left, int right);
int partition_L(Product_resumido list[], int left, int right);
void troca_produto(Product_resumido list_change[], int p1, int p2);

/* GLOBAL VARIABLES */

Product all_produce[PRODUCE_MAX]; /* Vetor que contem todos os produtos */
Order all_orders[ORDERS_MAX]; /* Vetor que contem todas as encomendas */
int product_nr = 0; /* Variavel - numero total de produtos registados no sistema */
int order_nr = 0; /* Variavel - numero total de encomendas registadas no sistema */


/* MAIN PROGRAM */

/* Le os comandos e recorre as funcoes correspondentes para os executar */
int main(){
    int order_id, prdct_id, quantity, weight, price; /* Variaveis int usadas como argumentos nas funcoes(comandos) */
    char command, description[DESCRIPTION_MAX]; /* Variaveis char usadas como argumentos nas funcoes(comandos) */

    scanf("%c", &command);  /* Primeiro, receber comando */
    while (command != END){
        switch (command){
            /* obter restantes parametros e executar respetiva funcao */ 
            case ADD_PRODCT:
                scanf(" %63[^:]:%d:%d:%d", description, &price, &weight, &quantity);
                add_prod(description, price, weight, quantity);
                break;
            case ADD_STOCK:
                scanf("%d:%d", &prdct_id, &quantity);
                add_stock(prdct_id, quantity);
                break;
            case ORDER:
                new_order();
                break;
            case ADD_2_ORD:
                scanf("%d:%d:%d", &order_id, &prdct_id, &quantity);
                add_to_order(order_id, prdct_id, quantity);
                break;
            case RMOVE_STK:
                scanf("%d:%d", &prdct_id, &quantity);
                remove_prd(prdct_id, quantity);
                break;
            case RMV_FROM_ORD:
                scanf("%d:%d", &order_id, &prdct_id);
                remove_from_ord(order_id, prdct_id);
                break;
            case COST:
                scanf("%d", &order_id);
                order_price(order_id);
                break;
            case CHNG_PRICE:
                scanf("%d:%d", &prdct_id, &price);
                change_price(prdct_id, price);
                break;
            case PRODCT_IN_ORD:
                scanf("%d:%d", &order_id, &prdct_id);
                list_prd(order_id, prdct_id);
                break;
            case ORDER_WITH_MOST:
                scanf("%d", &prdct_id);
                most_order(prdct_id);
                break;
            case LIST_PRODUCE:
                list_all();
                break;
            case LIST_ORDER:
                scanf("%d", &order_id);
                list_order(order_id);
                break;
        }
        scanf("%c", &command);
    }
    return 0;
}


/* FUNCTIONS (PERFORM THE COMMANDS) */

/* Funcao add_prod adiciona um produto novo e as suas caracteristicas(recebidas como argumentos) ao vetor all_produce */
void add_prod(char descrp[], int p, int w, int s){
    Product new_product;

    /* atrbuir caracteristicas ao novo produto */
    new_product.identifier = product_nr; 
    new_product.price = p;  
    new_product.weight = w; 
    new_product.stock = s;  
    strcpy(new_product.description, descrp); 
    
    all_produce[product_nr]=new_product;  /* Depois de atribuicoes, colocar o produto no vetor 'all_products */
    product_nr++; /* Atualizar o nr de produtos no sistema */
    printf("Novo produto %d.\n", new_product.identifier);
}

/* Funcao add_stock verifica se produto(prd_id) existe, se sim adiciona stock(qtd) ao mesmo */
void add_stock(int prd_id, int qtd){
     /* Se nr de produtos no sistema igual ou menor ao id do produto (tambem visto como indice) este nao existe */
    if (product_nr <= prd_id) printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prd_id);
    else all_produce[prd_id].stock += qtd;
}

/* Funcao cria uma nova encomenda, faz as atribuicoes necessarias, e coloca-a no vetor 'all_orders' */
void new_order(){
    Order new_order;

    new_order.nr_of_prod = 0; /* Numero inicial de produtos na encomenda*/
    new_order.total_weight = 0; 
    new_order.total_price = 0; 
    new_order.identifier = order_nr; /* Atribuir identificador da encomenda*/

    all_orders[order_nr] = new_order; /* Colocar encomenda no vetor 'all_orders' */
    order_nr ++; /* Atualizar o nr de encomendas no sistema */

    printf("Nova encomenda %d.\n", new_order.identifier);
}

/* Funcao verifica se podemos adicionar a quantidade(qtd) do produto(prd_id) ah encomenda(ord_id), se sim adiciona*/
void add_to_order(int ord_id, int prd_id, int qtd){
    int in_order = 0; /* flag para saber se produto ja existe dentro da encomenda em questao */
    int i = 0; 
    
    /* Verificar se existem impedimentos (existencia de ecomenda,produto, stock e espaco em peso) */
    if (order_nr <= ord_id)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prd_id, ord_id);
    else if (product_nr <= prd_id)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prd_id, ord_id); 
    else if (all_produce[prd_id].stock < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prd_id, ord_id);
    else if ((all_orders[ord_id].total_weight + all_produce[prd_id].weight * qtd) > ORDER_WEIGHT_MAX)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prd_id, ord_id);
    /* Caso em que nao existe impedimentos */
    else{
        /* ciclo verifica se o produto dado existe dentro da encomenta atualizando a flag correspondente */
        while( i < all_orders[ord_id].nr_of_prod){
            if (all_orders[ord_id].products[i].identifier == prd_id){  /* comparacao do prd_id com os produtos contidos na encomenda */
                in_order = 1; /* Produto ja existe na encomenda*/
                break;
            }
            i++;
        }
        /* se produto ja existir apenas acrescentar a qtd desejada ah encomenda */     
        if (in_order) all_orders[ord_id].products[i].order_stock += qtd;
        /* se nao existir acrescentar produto ah encomenda (vetor 'products' presente nesta) */
        else { 
            all_orders[ord_id].products[i].identifier = prd_id; /* identifica o produto acrescentado ao vetor 'products' dentro da encomenda */
            all_orders[ord_id].products[i].order_stock = qtd; /*  adiciona o stock ao produto no vetor 'products' */
            all_orders[ord_id].products[i].price = all_produce[prd_id].price; /* informacao de preco */
            strcpy(all_orders[ord_id].products[i].description, all_produce[prd_id].description); /* adiciona a descricao do produto */
            
            all_orders[ord_id].nr_of_prod += 1; /* atualiza nr de produtos na encomenda */
        }

        /* atualizacao do peso e preco da encomenda */
        all_orders[ord_id].total_price += (all_produce[prd_id].price * qtd);
        all_orders[ord_id].total_weight += (all_produce[prd_id].weight * qtd); 

        remove_prd(prd_id, qtd); /* remover, do stock disponivel no vetor 'all_produce', o stock acrescentado ah encomenda */
    } 
}

/* Funcao remove stock(qtd) ao produto dado(prd_id) do sistema */
void remove_prd(int prd_id, int qtd){
    /* verificar se produto existe */
    if (product_nr <= prd_id)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prd_id);
    /* verificar se produto tem stock suficiente */
    else if (all_produce[prd_id].stock < qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, prd_id);
    /* remover o stock(qtd) dado */
    else 
        all_produce[prd_id].stock -= qtd;
}

/* Funcao remove produto(prd_id) de encomenda(ord_id), alertando caso nao seja possivel */
void remove_from_ord(int ord_id, int prd_id){
    int i=0;
    /* Verificar se existe encomenda */
    if (order_nr <= ord_id) printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prd_id, ord_id);
    /* Verificar se existe produto */
    else if (product_nr <= prd_id) printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prd_id, ord_id);
    else{
        /* ciclo para encontrar produto dado na encomenda */
        while (i < all_orders[ord_id].nr_of_prod){
           /* Verificar se o produto esta na encomenda */
            if (all_orders[ord_id].products[i].identifier == prd_id){
                int qtnty = all_orders[ord_id].products[i].order_stock; /* variavel(quantidade na encomenda) criada para tornar codigo mais legivel */
                
                all_orders[ord_id].total_price -= (all_produce[prd_id].price * qtnty);  /* retirar peso do produto da encomenda */
                all_orders[ord_id].total_weight -= (all_produce[prd_id].weight * qtnty); /* retirar custo do produto da encomenda */
                add_stock(prd_id, qtnty); /* repor stock do produto que estava reservado no sistema */
                all_orders[ord_id].products[i].order_stock = 0; /* atualizar quantidade do produto na encomenda */
                break;
            }
            i++;
        }
    }
}

/* Funcao retorna o custo da encomenda dada (ord_id) */
void order_price(int ord_id){
    if (order_nr <= ord_id) printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ord_id);
    else{
       printf("Custo da encomenda %d %d.\n", ord_id, all_orders[ord_id].total_price);
    }
}

/* Funcao altera o preco(price) do produto(prd_id) e faz os ajustes dentro das encomendas que conteem esse prdt */
void change_price(int prd_id, int price){
    int i, j;
    int b4_price, after_price = price; /* variaveis preco antes e preco depois */
    /* Verificar se produto existe */
    if (product_nr <= prd_id) printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", prd_id);
    else{
        b4_price = all_produce[prd_id].price; /* guardar preco que vai ser substituido */
        all_produce[prd_id].price = price;
        /* ciclo vai a todas as encomendas verificar se conteem o produto */
        for(i = 0; i < order_nr; i++){
            /* se encomenda nao for vazia confirmar os produtos */
            if (all_orders[i].total_weight > 0){
                /* procurar o produto na encomenda i */
                for(j = 0; j < all_orders[i].nr_of_prod; j++){
                    if (all_orders[i].products[j].identifier == prd_id){
                        /* se produto na encomenda, alterar preco do produto e preco total da encomenda */
                        all_orders[i].products[j].price = price;
                        all_orders[i].total_price += (after_price-b4_price) * all_orders[i].products[j].order_stock;
                    }
                }
            }
        }
    }
}

/* Funcao recebe um produto(prd_id) e uma encomenda(ord_id) e lista a descricao e quantidade desse prd na encomenda */
void list_prd(int ord_id, int prd_id){
    /* verificar fisabilidade do comando */
    if (order_nr <= ord_id) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ord_id);
    else if (product_nr <= prd_id) printf("Impossivel listar produto %d. Produto inexistente.\n", prd_id);
    else{
        int i=0;
        /* ciclo de procura do produto prd_id na encomenda ord_id */
        while (i < all_orders[ord_id].nr_of_prod){
            if (all_orders[ord_id].products[i].identifier == prd_id){
                /* se existir expor a sua descricao e stock */
                printf("%s %d.\n", all_produce[prd_id].description, all_orders[ord_id].products[i].order_stock);
                break;
            }
            i++;
        }
        /* se produto nao existe na encomenda expor a sua descricao e o seu stock(que eh 0) */
        if (i == all_orders[ord_id].nr_of_prod) printf("%s 0.\n", all_produce[prd_id].description);
    }
}

/* Funcao procura a encomenda que contem maior quantidade de um produto(prd_id) e expoe essa informacao */
void most_order(int prd_id){
    if (product_nr <= prd_id) printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prd_id);
    else{
        int  i, j;
        int max = 0, max_id; /* variaveis guardam a qtd maxima e a encomenda onde max ocorre */
        for (i=0; i < order_nr; i++){
            /* ao percorrer as encomendas verificar se existem produtos nelas */
            if (all_orders[i].total_weight > 0){
                /* caso existam produtos, percorrer ah procura do prd_id dado */
                for (j = 0; j < all_orders[i].nr_of_prod; j++){
                    if (all_orders[i].products[j].identifier == prd_id && all_orders[i].products[j].order_stock > max){
                        /* se encontrar o prd_id e este existir em quantidade superior ao maximo anteriror, atualziar max e max_id */
                        max = all_orders[i].products[j].order_stock;
                        max_id = i;
                        break; /* parar de percorrer encomenda */
                    }  
                }
            }
        }
        /* no fim da procura expor a informacao obtida */
        if (max > 0) printf("Maximo produto %d %d %d.\n", prd_id, max_id, max);
    }
}

/* Funcao que ordena todos os produtos existentes por ordem crescente de preco (comando l) */
void list_all(){
    int i;
    Product_resumido aux_list[PRODUCE_MAX]; /* lista auxiliar de todos os produtos lista que vai ser ordenada */
    
    /* copia dos produtos para a lista auxiliar */
    for(i=0; i < product_nr; i++){
        aux_list[i].order_stock = all_produce[i].stock; /* aqui order_stock == stock */
        aux_list[i].identifier = all_produce[i].identifier;
        aux_list[i].price = all_produce[i].price;
        strcpy(aux_list[i].description, all_produce[i].description);
    }

    quicksort(aux_list, 0, product_nr - 1, 'l'); /* recorrer ao quicksort para organizar especificando o comando a executar */

    /* outuput da lista organizada */
    printf("Produtos\n");
    for(i=0; i < product_nr; i++){
        printf("* %s %d %d\n", aux_list[i].description, aux_list[i].price , aux_list[i].order_stock);  
    }
}

/* Funcao recebe encomenda(ord_id) e ordena-a por ordem alfabetica dos produtos nela presente */
void list_order(int ord_id){
    if (order_nr <= ord_id) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ord_id);
    else{
        int i = 0;
        /* chamada do quicksort no modo apropriado ao comando */
        quicksort(all_orders[ord_id].products, 0, all_orders[ord_id].nr_of_prod - 1, 'L');
        /* Output da encomenda ordenada */
        printf("Encomenda %d\n", ord_id);
        while (i < all_orders[ord_id].nr_of_prod){
            /* apenas produtos com stock superior a 0 dentro da encomenda sao dados no output */
            if (all_orders[ord_id].products[i].order_stock > 0){
                printf("* %s %d %d\n", all_orders[ord_id].products[i].description,  all_orders[ord_id].products[i].price, all_orders[ord_id].products[i].order_stock);
            }
            i++;
        }
    }
}

/* Funcao quicksort, recebe a lista a organizar, o limite esquerdo, direito, e o modo('l' ou 'L' conforme o comando) */
void quicksort(Product_resumido list[], int left, int right, char mode){
    int i;
    /* caso de paragem */
    if (right <= left){
        return;
    }
    /* obter posicao onde dividir o vetor a organizar de acordo com o comando*/
    if(mode == 'l') i = partition_l(list, left, right);
    else if(mode == 'L') i = partition_L(list, left, right);

    /* chamada recursiva */
    quicksort(list, left, i - 1, mode);
    quicksort(list, i + 1, right, mode);
}

/* Funcao recebe uma list os limites esq e drt  e retorna o indice da posicao onde dividir a lista para o quicksort */
int partition_l(Product_resumido list[],int left, int right){
    int i = left, j = right;
    
    while(i  < j){
        /* avancar o indice i enquanto preco menor q pivot ou, se preco igual, o id for menor */
        while (list[i].price < list[right].price || (list[i].price == list[right].price && list[i].identifier < list[right].identifier)){
            i++;
        }
        /* reduzir o indice j enquanto preco mair q pivot ou, se preco igual, o id for maior */
        while((list[--j].price > list[right].price || (list[j].price == list[right].price && list[j].identifier > list[right].identifier)) && j>=left );
        if (i < j){ 
            /* se i e j ainda nao se tiverem cruzado trocar produtos da posicao i com j */
            troca_produto(list, i, j);
            i++;
        }
    }
    /* troca do pivot com o produto na posicao i */
    troca_produto(list, i, right);
    return i;
}

/* Funcao semelhante a partition_l mas para comando 'L', a funcao partition foi dividida em duas para nao ficar uma demasiado grande e complexa */
int partition_L(Product_resumido list[], int left, int right){
    int i = left, j = right;

    while(i  < j){
        /* avancar o indice i enquanto alfabeticamente menor q pivot ou, se igual, o id for menor */
        while (strcmp(list[i].description, list[right].description) < 0 || (strcmp(list[i].description, list[right].description) == 0 && list[i].identifier < list[right].identifier)){
             i++;
        }
        /* reduzir o indice j enquanto alfabeticamenta maior q pivot ou, se alfabeticamente igual, o id for maior */
        while((strcmp(list[--j].description, list[right].description) > 0 || (strcmp(list[j].description, list[right].description) == 0 && list[j].identifier > list[right].identifier)) && j>=left);
        if (i < j){ 
            /* se i e j ainda nao se tiverem cruzado trocar produtos da posicao i com j */
            troca_produto(list, i, j);
            i++;
        }
    }
    /* troca do pivot com o produto na posicao i */
    troca_produto(list, i, right);
    return i;
}

/* Funcao troca 2 produtos de uma lista(list_change) nas posicoes(p1 e p2) entre si */
void troca_produto(Product_resumido list_change[], int p1, int p2){
    Product_resumido pos_aux; /* variavel auxiliar para a troca de posicoes */

    pos_aux = list_change[p1];
    list_change[p1]=list_change[p2];
    list_change[p2]=pos_aux;
}