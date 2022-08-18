#include <stdio.h>
#include <string.h>
/*Maximum number of different products.*/ 
#define MAXPRD 10000
/*Maximum number of differnt orders.*/
#define MAXORD 500
/*Maximum number of products in an order (maximum weight = 200 --> each product weighs at least 1).*/
#define MAXPRD_ORD 200
/*Maximum weight of an order.*/
#define MAXWGHT 200
/*Maximum number of characters in a description of a product + "\0".*/
#define MAXDEF 64
/*Control value to know when to merge by price.*/
#define mergeP 1
/*Control value to know when to merge alphabetically.*/
#define mergeA 2

/*Structures*/

/*Structure to codify a product.*/
typedef struct product{
    /*Product identifier.*/
    int idp;
    char description[MAXDEF];
    int price;
    int weight;
    int stock;
}product;

/*Structure to codify an order (group of products).*/
typedef struct order{
    /*Order identifier.*/
    int ido;
    int weight;
    /*Number of products in an order.*/
    int number_prod;
    product prods[MAXPRD_ORD];
}order;

/*Functions prototypes.*/

void addProduct(char str[MAXDEF], int p, int w, int qt);
void addStock(int idp, int qtd);
void createOrder();
void addProdOrder(int ido, int idp, int qt);
void removeStock(int idp, int qt);
void removeProdOrder(int ido, int idp);
void costOrder(int ido);
void changePrice(int ide, int p);
void productOrder(int ido, int ide);
void mostProdOrder(int idp);
void getAllProds();
void listOrder(int ido);
void readString(char desc[MAXDEF]);
void copyString(char str1[MAXDEF], char str2[MAXDEF]);
void mergeSort(product arr[MAXPRD], int ido, int inf, int sup, int control);
void mergePrice(product arr[MAXPRD], int inf, int middle, int sup);
void mergeAlph(product arr[MAXPRD], int ido, int inf, int middle, int sup);
void swapProduct(product arr[MAXPRD], int i, int j);
void outputProduct(char str[MAXDEF], int p, int qt);

/*Global variables.*/

/*N? of existent products.*/
int product_counter;
/*N? of existent orders.*/
int order_counter;
product products[MAXPRD]; 
order orders[MAXORD];

/*Main function.*/
int main(){
    char ch;int price, weight, qt;
    int ido;
    int idp;
    char description[MAXDEF] = {0};
    /*Variable to save if an 'x' if found.*/
    int not_finished = 1;

    while(not_finished){
        /*Note: getchar() --> Get the "\n".*/
        switch(ch = getchar()){
            case 'a':
                readString(description);
                scanf("%d:%d:%d", &price, &weight, &qt);
                getchar();
                addProduct(description, price, weight, qt);
                break;
            
            case 'q':
                scanf("%d:%d", &idp, &qt);
                getchar();
                addStock(idp, qt);
                break;

            case 'N':
                createOrder();
                getchar();
                break;

            case 'A':
                scanf("%d:%d:%d", &ido, &idp, &qt);
                getchar();
                addProdOrder(ido, idp, qt);
                break;
            
            case 'r':
                scanf("%d:%d", &idp, &qt);
                getchar();
                removeStock(idp, qt);
                break;
            
            case 'R':
                scanf("%d:%d", &ido, &idp);
                getchar();
                removeProdOrder(ido, idp);
                break;

            case 'C':
                scanf("%d", &ido);
                getchar();
                costOrder(ido);
                break;
            
            case 'p':
                scanf("%d:%d", &idp, &price);
                getchar();
                changePrice(idp, price);
                break;
            
            case 'E':
                scanf("%d:%d", &ido, &idp);
                getchar();
                productOrder(ido, idp);
                break;
            
            case 'm':
                scanf("%d", &idp);
                getchar();
                mostProdOrder(idp);
                break;

            case 'l':
                getAllProds();
                getchar();
                break;
            
            case 'L':
                scanf("%d", &ido);
                getchar();
                listOrder(ido);
                break;
            
            /*ch == x*/
            default:
                not_finished = 0;
                break;
        }     
    }

    return 0;
}

/*Adds a new product to the list of products.*/
void addProduct(char str[MAXDEF], int p, int w, int qt){
    copyString(products[product_counter].description, str);
    products[product_counter].idp = product_counter;
    products[product_counter].price = p;
    products[product_counter].weight = w;
    products[product_counter].stock = qt;
    printf("Novo produto %d.\n", product_counter);
    product_counter++;
}

/*Adds stock to an existent product.*/
void addStock(int idp, int qt){
    if(idp >= product_counter)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    
    else{
        int i;
    
        for(i = 0; i < product_counter; i++){
            if(products[i].idp == idp){
                products[i].stock += qt;
                break;
            }
        }
    }
}

/*Creates a new order.*/
void createOrder(){
    orders[order_counter].ido = order_counter;
    printf("Nova encomenda %d.\n", order_counter);
    order_counter++;
}

/*Adds a new product to an order or, if its already in it, adds stock to it (in the order).*/
void addProdOrder(int ido, int idp, int qt){
    if(ido >= order_counter)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ido);
    
    else if(idp >= product_counter)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ido);

    else{
        int i;
        /*Position of the product.*/
        int pos;

        /*Getting the position of the product*/
        for(i = 0; i < MAXPRD; i++){
            if(products[i].idp == idp){
                pos = i;
                break;
            }
        }

        if(qt > products[pos].stock)
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ido);
    
        else if(qt*products[pos].weight + orders[ido].weight > MAXWGHT)
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ido);

        else{
            /*Control variable to know if the product is already in the order.*/
            int product_in = 0;

            /*Checks if the product is inside the order*/
            for(i = 0; i < orders[ido].number_prod; i++){
                if(orders[ido].prods[i].idp == idp){
                    orders[ido].prods[i].stock += qt;
                    product_in = 1;
                    break;
                }
            }

            if(!product_in){
                /*Adds a new proudct inside the order*/
                orders[ido].prods[orders[ido].number_prod] = products[pos];
                /*Fix the idp and quantity*/
                orders[ido].prods[orders[ido].number_prod].idp = idp;
                orders[ido].prods[orders[ido].number_prod].stock = qt;
                orders[ido].number_prod++;
            }

            orders[ido].weight += qt*products[pos].weight;
            removeStock(idp, qt);
        }
    }
}

/*Removes stock to a product in the system.*/
void removeStock(int idp, int qt){
    if(idp >= product_counter)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);

    else{
         int i;

        /*Searching for the product and verifying if it was enough stock*/
        for(i = 0; i < product_counter; i++){
            if(products[i].idp == idp){
                if(qt > products[i].stock)
                    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qt, idp);

                else
                    products[i].stock -= qt;

                break;
            }
        }
    }
}

/*Removes a product from an order.*/
void removeProdOrder(int ido, int idp){
    if(ido >= order_counter)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ido);

    else if(idp >= product_counter)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ido);
    
    else{
        int i;

        /*Verifies if the product exists inside the order*/
        for(i = 0; i < orders[ido].number_prod; i++){
            if(orders[ido].prods[i].idp == idp){
                orders[ido].weight -= orders[ido].prods[i].stock*orders[ido].prods[i].weight;
                addStock(idp, orders[ido].prods[i].stock);
                orders[ido].prods[i].stock = 0;
                break;
            } 
        }
    }
}

/*Calculates the cost of an order.*/
void costOrder(int ido){
    if(ido >= order_counter)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ido);

    else{
        int value = 0;
        int i;

        for(i = 0; i < orders[ido].number_prod; i++)
            value += orders[ido].prods[i].stock*orders[ido].prods[i].price;
    
        printf("Custo da encomenda %d %d.\n", ido, value);
    }
}

/*Changes the price of a product, everywhere.*/
void changePrice(int idp, int p){
    if(idp >= product_counter)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);

    else{
        int i, j;

        /*Changing the price in "products"*/
        for(i = 0; i < product_counter; i++){
            if(products[i].idp == idp){
                products[i].price = p;
                break;
            }
        }

        /*Changing the price in every order*/
        for(i = 0; i < order_counter; i++){
            for(j = 0; j < orders[i].number_prod; j++){
                if(orders[i].prods[j].idp == idp){
                    orders[i].prods[j].price = p;
                    break;
                }
            }
        }
    }
}

/*Outputs the description of a product as well as its quantity in an order.*/
void productOrder(int ido, int idp){
    if(ido >= order_counter)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ido);

    else if(idp >= product_counter)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);

    else{
        int i;
        int quantity = 0;
        
        /*Getting the quantity of the product*/
        for(i = 0; i < orders[ido].number_prod; i++){
            if(orders[ido].prods[i].idp == idp){
                quantity = orders[ido].prods[i].stock;
                break;
            }
        }

        /*Getting the description of the product*/
        for(i = 0; i < product_counter; i++){
            if(products[i].idp == idp){
                printf("%s", products[i].description);
                printf(" %d.\n", quantity);
                break;
            }
        }
    }
}

/*Outputs the order where a certain product exists the most, its idp and quantity.*/
void mostProdOrder(int idp){
    if(idp >= product_counter)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);

    /*Ignores if there is no orders*/
    else if(order_counter == 0);
    
    else{
        int i, j;
        int prod_exists = 0;
        /*Maximum quantity yet.*/
        int max = 0;
        /*Ido of the order where it occurs.*/
        int max_order = 0;

        /*Seek for the maximum quantity of the product idp*/
        for(i = 0; i < order_counter; i++){
            for(j = 0; j < orders[i].number_prod; j++){
                if(orders[i].prods[j].idp == idp){
                    if(orders[i].prods[j].stock > max){
                        prod_exists = 1;
                        max = orders[i].prods[j].stock;
                        max_order = i;
                    }
                    break;
                }
            }
        }

        if(prod_exists)
            printf("Maximo produto %d %d %d.\n", idp, max_order, max);
    }
}

/*Outputs every product in the system sorted by their price (lowest --> highest).*/
void getAllProds(){
    int i;
    product aux[MAXPRD];

    /*If there is only one product in the order, theres no need to sort it*/
    if(product_counter > 1)
        mergeSort(aux, 0, 0, product_counter-1, 1);

    printf("Produtos\n");
    for(i = 0; i < product_counter; i++){
        putchar('*');
        putchar(' ');
        outputProduct(products[i].description, products[i].price, products[i].stock);
    }
}

/*Outputs every product in an order sorted by alphabetical order.*/
void listOrder(int ido){
    if(ido >= order_counter)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ido);
    
    else if(order_counter == 0)
        printf("Encomenda %d\n", ido);

    else{
        int i;
        product aux[MAXPRD];

        /*If there is only one product in the order, theres no need to sort it*/
        if(orders[ido].number_prod > 1)
            mergeSort(aux, ido, 0, orders[ido].number_prod-1, 2);

        printf("Encomenda %d\n", ido);
        for(i = 0; i < orders[ido].number_prod; i++){
            if(orders[ido].prods[i].stock != 0){
                putchar('*');
                putchar(' ');
                outputProduct(orders[ido].prods[i].description, orders[ido].prods[i].price, orders[ido].prods[i].stock);
            }
        }
    }
}

/*Reads an input and saves it.*/
void readString(char desc[MAXDEF]){
    int i, ch;
    /*Gets the space remaining in the input*/
    getchar();

    for(i = 0; (ch = getchar()) != ':'; i++)
        desc[i] = ch;
    
    desc[i] = '\0';
}

/*Copies a string.*/
void copyString(char str1[MAXDEF], char str2[MAXDEF]){
    int j;

    for(j = 0; str2[j] != '\0'; j++)
        str1[j] = str2[j];
    
    str1[j] = '\0';
}

/*Sorts a list of products from the lowest price to the highest.*/
void mergeSort(product arr[MAXPRD], int ido, int inf, int sup, int control){
    int middle = (inf+sup)/2;

    if(sup <= inf)
        return;

    mergeSort(arr, ido, inf, middle, control);
    mergeSort(arr, ido, middle+1, sup, control);

    if(control == 1)
        /*No need for the ido*/
        mergePrice(arr, inf, middle, sup);
    else if(control == 2)
        mergeAlph(arr, ido, inf, middle, sup);
}

/*Merges two lists of products according to the price (inf:sup).*/
void mergePrice(product arr[MAXPRD], int inf, int middle, int sup){
    int i, j, k;

    /*Copies the list of products*/
    for(i = middle+1; i > inf; i--)
        arr[i-1] = products[i-1];
    
    for(j = middle; j < sup; j++)
        arr[sup+middle-j] = products[j+1];
    
    /*Compares the first and second half of the list*/
    for(k = inf; k <= sup; k++){
        if(arr[j].price < arr[i].price || i > middle)
            products[k] = arr[j--];

        /*Making the algorithm stable*/
        else if(arr[j].price == arr[i].price){
            if(arr[j].idp < arr[i].idp)
                products[k] = arr[j--];
            
            else
                products[k] = arr[i++];
        }

        else
            products[k] = arr[i++];
    }
}

/*Merges two lists of products alphabetically.*/
void mergeAlph(product arr[MAXPRD], int ido, int inf, int middle, int sup){
    int i, j, k;

    /*Copies the list of products*/
    for(i = middle+1; i > inf; i--)
        arr[i-1] = orders[ido].prods[i-1];
    
    for(j = middle; j < sup; j++)
        arr[sup+middle-j] = orders[ido].prods[j+1];
    
    /*Compares the first and second half of the list*/
    for(k = inf; k <= sup; k++){
        if(strcmp(arr[j].description, arr[i].description) < 0 || i > middle)
            orders[ido].prods[k] = arr[j--];

        else
            orders[ido].prods[k] = arr[i++];
    }
}

/*Swaps two products.*/
void swapProduct(product arr[MAXPRD], int i, int j){
    product temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

/*Outputs the description, price and stock of a product.*/
void outputProduct(char str[MAXDEF], int p, int qt){
    printf("%s %d %d\n", str, p, qt);
}
