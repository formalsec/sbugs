#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char storage_Array0[65];
int storage_Array_id[10000];
int storage_Array_price[10000];
int current_id = 0;
int current_order_id = 0;

struct product {
    int id;
    char description[65];
    int price;
    int weight;
    int amount;
};

struct product stock[10000];

struct order {
    int order_id;
    struct product all_items[200];
    int total_weight;
    int total_price;
};

struct order all_orders[500];

void store_info(){                      /* func que quarda inform?ao ate encontra ':' ou '\n'*/
    char rest = '0';
    int i = 0;

    while( rest != ':' && rest != '\n'){
        rest = getchar();
        storage_Array0[i] = rest;
        i++;
    }

    storage_Array0[i-1] = '\n';
    storage_Array0[i] = '\0';
}

void set_order_weigth(int ide){        /* func para defenir peso de uma encomenda */
    int i = 0;
    int weight = 0;
    
    for(; i < 200; i++){
        if( all_orders[ide].all_items[i].weight > 0){
            weight = weight + (all_orders[ide].all_items[i].weight * all_orders[ide].all_items[i].amount);
        }
    }

    all_orders[ide].total_weight = weight;
}

void set_order_price(int ide){          /* func para defenir pre?o de uma encomenda */
    int i = 0;
    int price = 0;
    
    for(; i < 200; i++){
        if( stock[all_orders[ide].all_items[i].id].price > 0 ){
            price = price  + (stock[all_orders[ide].all_items[i].id].price * all_orders[ide].all_items[i].amount);
        }
    }

    all_orders[ide].total_price = price;
}

int check_error(int e, int idp, int ide, int qtd){        /* func para verificar todos os possiveis erros */
    if(e == 1){
        if(current_id <= idp){       /* erro 1 produto nao existente*/
            return 0;
        }
    } else if(e == 2){               /* erro 2 encomenda nao existente*/
        if(current_order_id <= ide){
            return 0;
        }
    } else if(e == 3){               /* erro 3 quantidade de stock*/
        if(stock[idp].amount < qtd){
            return 0;
        }
    } else if(e == 4){              /* erro 4 peso maximo excedido*/
        set_order_weigth(ide);
        if((all_orders[ide].total_weight + (stock[idp].weight * qtd)) > 200){
            return 0;
        }
    }
    return 1;
}

void add_stock(int idp, int qtd){          /* func para aumentar stock de um produto*/
    stock[idp].amount = stock[idp].amount + qtd;
}

void add_to_order(int ide, int idp, int qtd){       /* func para adicionar produto a uma encomenda*/
    int i;

    for(i = 0; i < 200; i++){
        if(all_orders[ide].all_items[i].id == idp && all_orders[ide].all_items[i].amount != 0){
            all_orders[ide].all_items[i].amount = all_orders[ide].all_items[i].amount + qtd;
            stock[idp].amount = stock[idp].amount - qtd;
            set_order_weigth(ide);
            set_order_price(ide);
            return;
        }
    }

    for(i = 0; i < 200; i++){
        if(all_orders[ide].all_items[i].amount == 0){
            all_orders[ide].all_items[i] = stock[idp];
            all_orders[ide].all_items[i].amount = qtd;
            stock[idp].amount = stock[idp].amount - qtd;
            set_order_weigth(ide);
            set_order_price(ide);
            return;
        }
    }
}

void remove_product(int idp, int ide){          /* func para remover um produto de uma encomenda*/
    int i = 0;

    for(; i < 200; i++){
        if(all_orders[ide].all_items[i].id == idp){
            stock[idp].amount = stock[idp].amount + all_orders[ide].all_items[i].amount;
            all_orders[ide].all_items[i].amount = 0;
            return;
        }
    }
}

int get_number(int idp, int ide){               /* dado uma encomenda e um pedido indica a quantidade de um certo produto na encomenda, usado em 'E' */
    int i = 0;

    for(; i < 200; i++){
        if(all_orders[ide].all_items[i].id == stock[idp].id){
            return all_orders[ide].all_items[i].amount;
        }
    }
    return 0;
}

int get_order(int idp){                        /* func para encontrar a encomenda que contem mais de um produto*/
    int i, j, ide;
    int max = 0;

    for(i = 0; i < current_order_id; i++){
        for(j = 0; j < 200; j++){
            if(all_orders[i].all_items[j].id == idp){
                if(max < all_orders[i].all_items[j].amount){
                    max = all_orders[i].all_items[j].amount;
                    ide = i;
                }
            }
        }
    }
    return ide;
}

/*void mini_sort(int index, int lenght){    o algoritmo nao ordena os ids no caso do pre?o ser igual, este seria o proposito deste algoritmo
    int i, j, temp;
    char *token;
    for(i = index; i < lenght - 1 + index; i++){
        for(j = i + 1; lenght + index; j++){
            if(storage_Array_id[i] > storage_Array_id[j]){
                temp = storage_Array_id[i];
                storage_Array_id[i] = storage_Array_id[j];
                storage_Array_id[j] = temp;
            }
        }
    }
    for(i = index; i < lenght; i++){
        token = strtok(stock[storage_Array_id[i]].description, "\n");
        printf("* %s %d %d\n", token, stock[storage_Array_id[i]].price,  stock[storage_Array_id[i]].amount);
    }
}*/

void shell_sort_price(int lenght){          /* func para imprimir todos os produtos por ordem crescente de pre?o*/
    int gap = lenght / 2;
    int i, j;
    int temp[2];
    char *token;

    for(i = 0; i < lenght; i++){
        storage_Array_id[i] = i;
        storage_Array_price[i] = stock[i].price;
    }

    while(gap > 0){
        j = 0;
        i = gap;

        for(;i < lenght; i++){
            temp[0] = storage_Array_id[i];
            temp[1] = storage_Array_price[i];
            j = i;
            for(; j >= gap && storage_Array_price[j-gap] >= temp[1] ; j -= gap){
                storage_Array_id[j] = storage_Array_id[j - gap];
                storage_Array_price[j] = storage_Array_price[j - gap];
            }
            storage_Array_id[j] = temp[0];
            storage_Array_price[j] = temp[1];
        }
        gap = gap / 2;
    }

    /*j = 0;              o algoritmo nao ordena os ids no caso do pre?o ser igual
    for(i = 0; i < lenght; i++){
        if(storage_Array_price[i] == storage_Array_price[i+1]){
            while(storage_Array_price[i] == storage_Array_price[i + j]){
                j++;
            }
            mini_sort(i, j + 1);
            i = i + j;
            j = 0;
        } else {
            token = strtok(stock[storage_Array_id[i]].description, "\n");
            printf("* %s %d %d\n", token, stock[storage_Array_id[i]].price,  stock[storage_Array_id[i]].amount);            
        }
    }*/

    for(i = 0; i < lenght; i++){
        token = strtok(stock[storage_Array_id[i]].description, "\n");
        printf("* %s %d %d\n", token, stock[storage_Array_id[i]].price,  stock[storage_Array_id[i]].amount);
    }
}

void sort_order(int ide){
    char desc[200][65];
    int ids[200];
    int qtd[200];
    char temp[65];
    char *token;
    int temp_id, temp_qtd;
    int i, j, a, b;

    j = 0;
    for(i = 0; i < 200; i++){
        if(all_orders[ide].all_items[i].amount != 0){
            strcpy(desc[j], all_orders[ide].all_items[i].description);
            ids[j] = all_orders[ide].all_items[i].id;
            qtd[j] = all_orders[ide].all_items[i].amount;
            j++;
        }
    }

    a = j - 1;
    b = j;
    j = 0;

    for(i = 0; i < a; i++){
        for(j = i + 1; j < b; j++){
            if(strcmp(desc[i], desc[j]) > 0){
                strcpy(temp, desc[i]);
                temp_id = ids[i];
                temp_qtd = qtd[i];
                strcpy(desc[i], desc[j]);
                ids[i] = ids[j];
                qtd[i] = qtd[j];
                strcpy(desc[j], temp);
                ids[j] = temp_id;
                qtd[j] = temp_qtd;
            }
        }
    }
    
    for(i = 0; i < b; i++){
        token = strtok(desc[i], "\n");
        printf("* %s %d %d\n", token, stock[ids[i]].price, qtd[i]);
    }
}

int main(){
    char choice = '0';
    char *token;
    int j = 0;
    int idp, qtd, ide, price;

    while(choice != 'x'){
        choice = getchar();

        if(choice == 'x'){ break;}

        if(choice == 'a'){                                              /* botao a */
            getchar();
    
            stock[current_id].id = current_id;

            store_info();
            for(j = 0; j < 65; j++){
                stock[current_id].description[j] = storage_Array0[j];
                if(storage_Array0[j] == '\0'){break;}
            }
            j = 0;

            store_info();
            stock[current_id].price = atoi(storage_Array0);

            store_info();
            stock[current_id].weight = atoi(storage_Array0);

            store_info();
            stock[current_id].amount = atoi(storage_Array0);

            printf("Novo produto %d.\n", current_id);
            current_id++;

        } else if(choice == 'q'){                                      /* botao q */
            getchar();  
            store_info();
            idp = atoi(storage_Array0);

            store_info();
            qtd = atoi(storage_Array0);

            if(check_error(1, idp, 0, 0) == 0){
                printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
            } else{ 
                add_stock(idp, qtd);
            }

        } else if(choice == 'N'){                                      /* botao N */ 
            all_orders[current_order_id].order_id = current_order_id;
            printf("Nova encomenda %d.\n", current_order_id);
            current_order_id++;

        } else if(choice == 'A'){                                      /* botao A */
            getchar();  
            store_info();
            ide = atoi(storage_Array0);
            store_info();
            idp = atoi(storage_Array0);
            store_info();
            qtd = atoi(storage_Array0);

            if(check_error(2, idp, ide, qtd) == 0){
                printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
            } else if(check_error(1, idp, ide, qtd) == 0){
                printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
            } else if(check_error(3, idp, ide,qtd) == 0){
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
            } else if(check_error(4, idp, ide, qtd) == 0){
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
            } else{
                add_to_order(ide, idp, qtd);
            }

        } else if(choice == 'r'){                                      /* botao r */
            getchar();
            store_info();
            idp = atoi(storage_Array0);
            store_info();
            qtd = atoi(storage_Array0);

            if(check_error(1, idp, 0, qtd) == 0){
               printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp); 
            } else if(stock[idp].amount < qtd){
                printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
            } else {
                add_stock(idp, -qtd);
            }
        } else if(choice == 'R'){                                     /* botao R */
            getchar(); 
            store_info();
            ide = atoi(storage_Array0);
            store_info();
            idp = atoi(storage_Array0);

            if(check_error(2, idp, ide, 0) == 0){
                printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
            } else if(check_error(1, idp, ide,0) == 0){
                printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
            } else{
                remove_product(idp, ide);
            }
        } else if(choice == 'C'){                                      /* botao C */
            getchar();
            store_info();
            ide = atoi(storage_Array0);

            if(check_error(2, 0, ide, 0) == 0){
                printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
            } else {
                set_order_price(ide);
                printf("Custo da encomenda %d %d.\n", ide, all_orders[ide].total_price);
            }
        } else if(choice == 'p'){                                       /* botao p */
            getchar();
            store_info();
            idp = atoi(storage_Array0);
            store_info();
            price = atoi(storage_Array0);

            if(check_error(1, idp, 0, 0) == 0){
                printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
            } else {
                stock[idp].price = price;
            }

        } else if(choice == 'E'){                                       /* botao E */
            getchar();
            store_info();
            ide = atoi(storage_Array0);
            store_info();
            idp = atoi(storage_Array0);

            if(check_error(2, idp, ide, 0) == 0){
                printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
            } else if(check_error(1, idp, ide, 0) == 0){
                printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
            } else{
                token = strtok(stock[idp].description, "\n");
                printf("%s %d.\n", token, get_number(idp, ide));
            }
        } else if(choice == 'm'){                                      /* botao m */
            getchar();
            store_info();
            idp = atoi(storage_Array0);

            if(check_error(1, idp, 0, 0) == 0){
                printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
            } else{
                ide = get_order(idp);
                qtd = get_number(idp, ide);
                if(qtd != 0){
                    printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
                }
            }
        } else if(choice == 'l'){                                   /* botao l */
            printf("Produtos\n");
            shell_sort_price(current_id);
            
        } else if(choice == 'L'){                                   /* botao L */
            getchar();
            store_info();
            ide = atoi(storage_Array0);

            if(check_error(2, 0, ide, 0) == 0){
                printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
            } else {
                printf("Encomenda %d\n", ide);
                sort_order(ide);
            }
        }
    }
    return 0;
}