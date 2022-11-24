#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAXORDERS 500
#define MAXPRODUCTS 10000
#define MAXPERORDER 200
#define MAXCARACTERES 64
#define FALSE 0
#define TRUE 1

/*indica sempre o valor maximo de produtos/encomendas em sistema para evitar ler garbage values*/
int total_prods = 0;
int total_orders = 0;

/*representacao interna de cada produto no sistema/stock*/
typedef struct{
    int id;
    char description[64];
    int price;
    int weight;
    int quantity;
} Product;

/*representacao interna de cada produto por encomenda*/
typedef struct{
    int idp;
    int qtt;
} Order;

/*estrutura auxiliar para ordenacao no comando l*/
typedef struct {
        int idp;
        int price;
    } sort_prod;

/*estrutura auxiliar para ordenacao no comando L*/
typedef struct {
    int idp;
    int quantity;
    char description[MAXCARACTERES];
} sort_order;

/*Array de produtos no sistema/stock. O indice corresponde mutuamente
ao id do produto*/
Product list_of_prods[MAXPRODUCTS];

/*Array para os produtos em cada encomenda.
Primeiro indice representa ide. O segundo corresponde ha ordem 
por que se adicionaram produtos na encomenda respetiva*/
Order list_of_orders[MAXORDERS][MAXPERORDER];



void new_product(void); /*A*/
void inc_stock(void); /*q*/
void new_order(void); /*N*/
void add_prod_order(void); /*A*/
void rem_units(void); /*r*/
void rem_prod_order(void); /*R*/
void price_order(void); /*C*/
void change_price(void); /*p*/
void print_details_order(void); /*E*/
void identifier(void); /*m*/
void list_prod(void); /*l*/
void list_prod_order(void); /*L*/
void increment_stock(int, int);
int conditionsR_check(int, int);
void rm_prod(int, int);
int conditionsA_check(int, int, int);
void add(int, int, int);
int conditionsr_check(int, int);
void rem(int, int);
void sort_array(sort_prod [], int, int);
int partition(sort_prod [], int, int);
void print_details_prods(sort_prod []);
void exchange(sort_prod *, sort_prod *);
void sort_array_alpha(sort_order [], int, int);
int partition_alpha(sort_order [], int, int);
void exchange_alpha(sort_order *, sort_order *);
void print_details_prods_order(sort_order [], int, int);
int ordered_quantity(int, int);



int main(){
    /*recebe input e consoante o char inserido corre o comando correspondente
    Chama a funcao apropriada*/

    char command;
    while(1){
        command = getchar();

        switch(command){

            case 'a':
                new_product();
                break;
            
            case 'q':
                inc_stock();
                break;
            
            case 'N':
                new_order();
                break;

            case 'A':
                add_prod_order();
                break;
            
            case 'r':
                rem_units();
                break;
            
            case 'R':
                rem_prod_order();
                break;
            
            case 'C':
                price_order();
                break;
            
            case 'p':
                change_price();
                break;
            
            case 'E':
                print_details_order();
                break;
            
            case 'm':
                identifier();
                break;
            
            case 'l':
                list_prod();
                break;
            
            case 'L':
                list_prod_order();
                break;
            
            case 'x':
                return 0;

        }

    }

    return 0;
}


/*---------------------------commands-----------------------------*/



/*--------------------a--------------------*/
void new_product(void){
    /*Adiciona um novo produto em stock a posicao em memoria
    seguinte do array*/
    
    scanf(" %[^:]:%d:%d:%d", list_of_prods[total_prods].description, &list_of_prods[total_prods].price, 
        &list_of_prods[total_prods].weight, &list_of_prods[total_prods].quantity);

    list_of_prods[total_prods].id = total_prods;

    printf("Novo produto %d.\n", total_prods);
    total_prods++;
}



/*------------------q---------------------*/
void inc_stock(void){
    /*Aumenta a quantidade em stock de um produto*/

    int idp, qtt;
    scanf("%d:%d", &idp, &qtt);
    if(idp >= total_prods){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }else{
        increment_stock(idp, qtt);
    }    
}




/*-----------------------N------------------------*/
void new_order(void){
    /*Disponibiliza uma nova encomenda. Limpa possiveis garbage values la existentes.
    O -1 permite nas encomendas saber quando ja se leu todos os produtos*/

    int i;

    /*Inicializacao da nova encomenda. limpa os possiveis valores anteriores
    e coloca todos a -1, ja que nenhum produto tem esse id*/
    for(i = 0; i < MAXPERORDER; i++){
        list_of_orders[total_orders][i].idp = -1;
        list_of_orders[total_orders][i].qtt = -1;
    }

    printf("Nova encomenda %d.\n", total_orders);
    total_orders++;
}




/*-----------------------A---------------------*/
void add_prod_order(void){
    /*Adiciona um produto a uma encomenda dando overwrite do valor 'nulo'
    que segundo esta representacao interna eh -1. O produto eh adicionado
    na posicoa do array imediatamente a seguir*/

    int ide, prod_idp, new_qtt;
    scanf("%d:%d:%d", &ide, &prod_idp, &new_qtt);

    /*verifica se ha erros e se nao houver cumpre a funcao de A*/
    switch(conditionsA_check(ide, prod_idp, new_qtt)){

        case 0:
            /*adicona o produto a encomenda*/
            add(ide, prod_idp, new_qtt);

            /*remove de stock a quantidade adicionada a encomenda*/
            rem(prod_idp, new_qtt);
            break;

        case 1:
            printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prod_idp, ide);
            break;

        case 2:
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prod_idp, ide);
            break;

        case 3:
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prod_idp, ide);
            break;
        
        case 4:
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prod_idp, ide);
            break;

    }
    
}

/*auxiliares*/

int conditionsA_check(int ide, int prod_idp, int new_qtt){
/*Se nao houver erros a funcao retorna 0, caso contrario
devolve um int que gera um prompt de erro na funcao add_prod_order()*/
    int i = 0, total_weight = 0, prod_weight, prod_quantity, index;

    if(ide >= total_orders){
        return 1;
    }else if(prod_idp >= total_prods){
        return 2;
    }else if(new_qtt > list_of_prods[prod_idp].quantity){
        return 3;
    }

    while((index = list_of_orders[ide][i].idp) != -1 && i < MAXPERORDER){

        prod_weight = list_of_prods[list_of_orders[ide][i].idp].weight;
        prod_quantity = list_of_orders[ide][i].qtt;

        total_weight += prod_quantity * prod_weight;
        i++;
    }
    total_weight += list_of_prods[prod_idp].weight * new_qtt;

    if(total_weight > 200){
        return 4;
    }else{
        return 0;
    }

}


void add(int ide, int prod_idp, int new_qtt){
    /*Adiciona quantidade ao produto prod_idp na encomenda ide
    caso ele ja exista la. Senao adiciona o com a quantidade new_qtt*/

    int ind, i = 0, exist = FALSE;

    while((ind = list_of_orders[ide][i].idp)!= -1){
        if(ind == prod_idp){
            list_of_orders[ide][i].qtt += new_qtt;
            exist = TRUE;
            break;
        }
        i++;
    }
    if(!exist){
        list_of_orders[ide][i].idp = prod_idp;
        list_of_orders[ide][i].qtt = new_qtt;
    }
}



/*------------------------r---------------------------*/
void rem_units(void){
    /*Remove unidades de um produto em stock, nunca permitindo
    que o valor em stock se torne negativo*/

    int prod_idp, prod_qtd;
    scanf("%d:%d", &prod_idp, &prod_qtd);
    switch(conditionsr_check(prod_idp, prod_qtd)){

        case 0:
            /*Efetiva a remocao do produto do stock*/
            rem(prod_idp, prod_qtd);
            break;

        case 1:
            printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod_idp);
            break;
        
        case 2:
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", prod_qtd, prod_idp);
            break;

    }
}

/*auxiliar*/
int conditionsr_check(int prod_idp, int prod_qtd){
/*Testa as condicoes do comando r e permite que um stock seja 
removido caso nao haja erros. Influencia o case corrido na
funcao rem_units()*/

    if(prod_idp >= total_prods){
        return 1;
    }else if(prod_qtd > list_of_prods[prod_idp].quantity){
        return 2;
    }else{
        return 0;
    }

}



/*------------------------R---------------------------*/
void rem_prod_order(void){
    int ide, idp;
    scanf("%d:%d", &ide, &idp);
    switch(conditionsR_check(ide, idp)){

        case 0:
            /*remove o produto da encomenda*/
            rm_prod(ide, idp);
            break;
        
        case 1:
            printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
            break;
        
        case 2:
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
            break;

        case 3:
            /*caso em que o produto existe no sistema, e a encomenda existe. No entanto a encomenda em questao nao contem o produto*/
            break;
    
    }
}

/*auxiliares*/
int conditionsR_check(int ide, int idp){
    /*retorna para a funcao rem_prod_order() um int que decidira
    que acao sera realizada ou se se da prompt de um erro*/

    int value, i = 0, exist = FALSE;
    if(ide >= total_orders){
        return 1;
    }else if(idp >= total_prods){
        return 2;
    }else{

        while(((value = list_of_orders[ide][i].idp) != -1) && i < MAXPERORDER){
            if(value == idp){
                exist = TRUE;
            }
        i++;
        }
        if(exist){
            return 0;
        }else{
            return 3;
        } 

    }
}

void rm_prod(int ide, int idp){
    /*desloca todos os produtos da encomenda a partir do a eliminar 
    para uma posicao anterior do array dando overwrite 
    do produto que deve ser removido. Deste modo as encomendas nao ficam 
    cheias com produtos a zeros*/

    int value, quantity, i = 0, deleting = FALSE;
    quantity = ordered_quantity(ide, idp);
    increment_stock(idp, quantity);
    
    while(((value = list_of_orders[ide][i].idp)!=-1) && i < MAXPERORDER){

        if((value==idp) && (!deleting)){
            deleting = TRUE;
        }else if(deleting){
            list_of_orders[ide][i-1].idp = list_of_orders[ide][i].idp;
            list_of_orders[ide][i-1].qtt = list_of_orders[ide][i].qtt; 
        }
        i++;

    }
    /*situacao em que se sai do while antes da ultima posicao ser apagada/deslocada*/
    list_of_orders[ide][i-1].idp = -1;
    list_of_orders[ide][i-1].qtt = -1;

}



/*-----------------------C------------------------*/
void price_order(void){
    /*Calcula o preco de uma encomenda consultando os precos
    dos produtos em sistema. Assim a funcionalidade nao eh afetada
    quando se altera o preco dos produtos em stock*/

    int i = 0, index, ide, total_cost = 0;
    scanf("%d", &ide);

    if(ide >= total_orders){

        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);

    }else{

        while((index = list_of_orders[ide][i].idp) != -1 && i < MAXPERORDER){

            total_cost += list_of_prods[index].price * list_of_orders[ide][i].qtt;
            i++;

        }
        printf("Custo da encomenda %d %d.\n", ide, total_cost);

    }

}



/*-------------------------p------------------------*/
void change_price(void){
    /*altera o preco de um produto no sistema*/

    int idp, new_price;
    scanf("%d:%d", &idp, &new_price);

    if(idp >= total_prods){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }else{
        list_of_prods[idp].price = new_price;
    }

}



/*-----------------------E-------------------------*/
void print_details_order(void){
    /*Print da descricao de um produto e da sua quantidade numa encomenda ide*/

    int order_ide, prod_idp, quantity;
    scanf("%d:%d", &order_ide, &prod_idp);

    if(order_ide >= total_orders){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", order_ide);
    }else if(prod_idp >= total_prods){
        printf("Impossivel listar produto %d. Produto inexistente.\n", prod_idp);
    }else{
        quantity = ordered_quantity(order_ide, prod_idp);
        printf("%s %d.\n", list_of_prods[prod_idp].description, quantity); 
    }

}




/*----------------------------m----------------------------*/
void identifier(void){
    /*Percorre iterativamente o array bidimensional de encomendas/produtos 
    para encontrar a encomenda em que um produto se encontra em maior quantidade.
    Imprime esse valor no terminal*/

    int idp, i, index = 0, ide, max_qtt = -1, exist = FALSE;
    scanf("%d", &idp);

    if(idp >= total_prods){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }else{

        for(i = 0; i < total_orders; i++){
            for(index = 0; index < MAXPERORDER; index++){

                if((list_of_orders[i][index].idp == idp) && (list_of_orders[i][index].qtt > max_qtt)){
                    max_qtt = list_of_orders[i][index].qtt;
                    ide = i;
                    exist = TRUE;
                }

            }
        }
        if(exist){
            printf("Maximo produto %d %d %d.\n", idp, ide, max_qtt);
        }
        
    }
    
}




/*--------------------------Sorting functions----------------------------*/


/*------------------------------'l'------------------------------*/

void list_prod(void){
    /*Imprime no temrinal os produtos em sistema por preco crescente.
    Para isto recorre a um array auxiliar para nao alterar 
    a ordem em memoria dos produtos*/

    sort_prod new_array[MAXPRODUCTS];
    int i;

    for(i = 0; i < total_prods; i++){

        new_array[i].idp = i;
        new_array[i].price = list_of_prods[i].price;
    
    }
    
    sort_array(new_array, 0, total_prods - 1);
    print_details_prods(new_array);

}


/*-----Auxiliares 'l'-----*/

/*Funcoes que imprimem por ordem de preco os
produtos existentes no sistema. Em caso de produtos com precos iguais
imprime primeiro os de menor id*/


void sort_array(sort_prod new_array[], int start, int end){
    /*Funcao principal de ordenacao l segundo o algoritmo quicksort*/
    int mid;
    if(start < end){

        /*qual na posicao certa (entre maiores e menores) o pivot*/
        mid = partition(new_array, start, end);

        /*chamada recursiva em arvore que ordena as duas metades
        obtidas no passo anterior*/
        sort_array(new_array, start, mid - 1);
        sort_array(new_array, mid + 1, end);

    }
}


int partition(sort_prod new_array[], int start, int end){
    /*Troca a posicao dos elementos de modo que o array fique subdividido
    em menores e maiores(em relacao ao pivot). De seguida troca o pivot com a
    primeira posicao em memoria do elementos maiores.
    Retorna o valor do indice do pivot*/
    int l = start;
    int r = end - 1;
    sort_prod pivot = new_array[end];
    while(l < r){

        while(new_array[l].price < pivot.price || 
        ((new_array[l].price == pivot.price) && (new_array[l].idp < pivot.idp))){
            l++;
        }
        while(new_array[r].price > pivot.price ||
        ((new_array[r].price == pivot.price) && (new_array[r].idp > pivot.idp))){
            if(r == l)
                break;
            r--;
        }
        if(l < r){
            exchange(&new_array[l], &new_array[r]);
        }

    }

    if(new_array[l].price > pivot.price ||
    ((new_array[l].price == pivot.price) && (new_array[l].idp > pivot.idp)))
        exchange(&new_array[l], &new_array[end]);
    
    return l;

}


void exchange(sort_prod * left, sort_prod * right){
    /*Efetua a troca dos elementos com recurso a uma variavel auxiliar*/

    sort_prod temp;
    temp.idp = left->idp;
    temp.price = left->price;
    left->idp = right->idp;
    left->price = right->price;
    right->idp = temp.idp;
    right->price = temp.price;

}


void print_details_prods(sort_prod sorted_prods[]){
    /*Imprime no terminal os valores dos produtos em sistema ja ordenados*/
    int i, idp;
    printf("Produtos\n");
    for(i = 0; i < total_prods; i++){
        idp = sorted_prods[i].idp;
        printf("* %s %d %d\n", list_of_prods[idp].description, 
                              list_of_prods[idp].price,
                              list_of_prods[idp].quantity);
    }
}
 



/*------------------------------'L'------------------------------*/

void list_prod_order(void){
    /*Imprime no temrinal os produtos de uma encomenda designada
    por ordem alfabetica de descricao. Recorre tal como em l a um 
    array auxiliar*/

    sort_order new_array[MAXORDERS];
    int i = 0, index = 0, ide, value, quant, total = 0;
    scanf("%d", &ide);

    if(ide >= total_orders){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;  
    }

    /*Copia para o array de estruturas auxiliar os valores relevantes a esta funcao*/
    while((value = list_of_orders[ide][i].idp) != -1 && i < MAXPERORDER){

        if((quant = list_of_orders[ide][i].qtt) > 0){

            new_array[index].idp = list_of_prods[value].id;
            strcpy(new_array[index].description, list_of_prods[value].description);
            new_array[index].quantity = quant;
            index++;
            total++;

        }
        i++;
    }

        sort_array_alpha(new_array, 0, total-1);
        print_details_prods_order(new_array, ide, total);
    
}



/*-----Auxiliares 'L'-----*/
/*Funcoes que ordenam alfabeticamente e imprimem  os produtos
de uma encomenda indicada*/


void sort_array_alpha(sort_order new_array[], int start, int end){
    /*Algoritmo quicksort que ordena os produtos de uma encomenda segundo
    ordem alfabetica da sua descricao*/
    int mid;
    if(start < end){

        /*divide o array inicial em dois excluindo o pivot, que ja 
        esta na posicao correta*/
        mid = partition_alpha(new_array, start, end);

        /*chamada recursiva em arvore para ordenar as consecutivas
        metades restantes obtidas*/
        sort_array_alpha(new_array, start, mid - 1);
        sort_array_alpha(new_array, mid + 1, end);

    }
}


int partition_alpha(sort_order new_array[], int start, int end){
    /*Organiza os elementos fora da posicao de modo que no final retorna
    a posicao do pivot. De modo que a sua esquerda so se encontram valores menores
    e a direita valores maiores*/

    int l = start;
    int r = end - 1;
    sort_order pivot = new_array[end];

    /*Desloca primeiro o indice da esquerda ate encontrar elementos fora de posicao.
    Repete o processo para o indice da esuqerda e entao efetua a troca dos elementos.
    Isto ate os indices se cruzarem*/
    while(l < r){

        while(strcmp(new_array[l].description, pivot.description) < 0 ||
        ((strcmp(new_array[l].description, pivot.description)==0) && (new_array[l].idp < pivot.idp))){
            l++;
        }
        while(strcmp(new_array[r].description, pivot.description) > 0 ||
        ((strcmp(new_array[r].description, pivot.description)==0) && (new_array[r].idp > pivot.idp))){
            if(r == l)
                break;
            r--;
        }
        if(l < r){
            exchange_alpha(&new_array[l], &new_array[r]);
        }
    }

    if(strcmp(new_array[l].description, pivot.description) > 0 ||
    ((strcmp(new_array[l].description, pivot.description)==0) && (new_array[l].idp > pivot.idp)))
        exchange_alpha(&new_array[l], &new_array[end]);
    
    return l;

}


void exchange_alpha(sort_order * left, sort_order * right){
    /*Efetua a troca da posicao dos elementos do array
    recebidos como argumentos*/

    sort_order temp;
    strcpy(temp.description, left -> description);
    temp.idp = left-> idp;
    temp.quantity = left -> quantity;
    strcpy(left -> description, right -> description);
    left -> idp = right -> idp;
    left -> quantity = right -> quantity;
    strcpy(right -> description, temp.description);
    right -> idp = temp.idp;
    right -> quantity = temp.quantity; 

}


void print_details_prods_order(sort_order sorted_prods[], int ide, int total){
    /*imprime no terminal os produtos da encomenda indicada
    por ordem alfabetica das suas descricoes*/
    
    int i, id, price;
    printf("Encomenda %d\n", ide);
    for(i = 0; i < total; i++){
        id = sorted_prods[i].idp;
        price = list_of_prods[id].price;
        printf("* %s %d %d\n", sorted_prods[i].description, price, sorted_prods[i].quantity);
    }

}



/*-----------------------------------------------------------*/

int ordered_quantity(int ide, int idp){
/*Devolve a quantidade de um produto (idp) numa encomenda (ide)
Se o produto nao estiver presente devolve 0*/
    int i = 0, index, qtt;
    while(((index = list_of_orders[ide][i].idp)!= -1) && i < MAXPERORDER){
        if(index == idp){
            qtt = list_of_orders[ide][i].qtt;
            return qtt;
        }
        i++;
    }
    return 0;

}


/*Funcoes auxiliares apenas para permitir maior abstracao em 
relacao aos movimentos de stock*/

void increment_stock(int idp, int qtt){
    /*aumenta a quantidade em stock de um produto*/
    list_of_prods[idp].quantity += qtt;

}

void rem(int prod_idp, int prod_qtd){
    /*Remove uma certa quantidade de produto de stock
    nunca permitindo que o stock se torne negativo*/

    if((list_of_prods[prod_idp].quantity - prod_qtd) < 0){
        list_of_prods[prod_idp].quantity = 0;
    }else{
        list_of_prods[prod_idp].quantity -= prod_qtd;    
    }
    
}
