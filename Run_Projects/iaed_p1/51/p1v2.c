#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Constants*/

/*The maximum amount of prducts stored*/
#define MAX_PRODUCTS 10000

/*The maximum amount of orders stored*/
#define MAX_ORDERS 500

/*The maximum amount of products per order*/
#define MAX_PER_ORDER 200

/*The maximum weight of an order*/
#define MAX_WEIGHT 200

/*The maxumin length of a product description*/
#define DESCRIPTION_LEN 64


/*Structures*/
typedef int Integer;
typedef char Character;

typedef struct product
{
    Integer id;
    Character description[DESCRIPTION_LEN];
    Integer price;
    Integer weight;
    Integer stock;
}Product;

typedef struct order
{
    Integer id;
    Integer selected_products[MAX_PER_ORDER];
    Integer chosen_counter;
    Integer quantity[MAX_PER_ORDER];
    Integer weight;
}Order;


/*Main functions*/
void create_product();

void add_stock(Integer idP, Integer new_stock);

void create_order();

void add_product(Integer idO, Integer idP, Integer quantity);

void remove_stock(Integer idP, Integer removed_stock);

void remove_product(Integer idO, Integer idP);

void order_cost(Integer idO);

void change_price(Integer idP, Integer price);

void product_amount(Integer idO, Integer idP);

void max_amount(Integer idP);

void sort_products();

void sort_order(Integer idO);


/*Auxiliary functions*/

Integer get_quantity(Integer idO, Integer index);

Integer get_price(Integer idP);

void print_Product(Product * product);

void print_Order(Integer idO);


Integer get_price(Integer id);

Integer get_weight_product(Integer id);

Integer get_stock(Integer id);

void set_product_id(Integer id);

void set_price(Integer id, Integer price);

void set_sorted_price(Integer idP, Integer price);

void set_weight_product(Integer id, Integer weight);

void set_stock(Integer id, Integer stock);

void set_sorted_stock(Integer idP, Integer stock);


Integer get_chosenPrd_id(Integer id, Integer index);

Integer get_chosenPrd_count(Integer idO);

Integer get_quantity(Integer id, Integer index);

Integer get_weight_order(Integer id);

void set_order_id(Integer id);

void set_weight_order(Integer id, Integer weight);

void chosen_increment(Integer idO);

void chosen_decrement(Integer idO);


void execute_command(Character selector);

int * get_command();


Integer create_idP();

Integer create_idO();


Integer check_weight(Integer idO, Integer idP, Integer quantity);

void add_weight(Integer idO, Integer idP, Integer quantity);

void remove_weight(Integer idO, Integer idP, Integer quantinty);


Integer check_stock(Integer idP, Integer requested_stock);


void update_quantity(Integer idO, Integer idP, Integer quantity);


Integer valid_product(Integer idP);

Integer valid_order(Integer idO);


void print_Product(Product * product);

void print_Order(Integer idO);


Integer in_order(Integer idO, Integer idP);

Integer find_product(Integer idO, Integer idP);

Integer find_sorted_product(Integer idP);



/*Global arrays & variables*/

/*Array of products*/
Product global_products[MAX_PRODUCTS];
/*Array of orders*/
Order global_orders[MAX_ORDERS];

/*Counter for product ids*/
Integer global_idP = 0;
/*Counter for order ids*/
Integer global_idO = 0;

/*Sorted array of products*/
Product global_products_sorted[MAX_PRODUCTS];
/*Delimits what part of the array is sorted*/
Integer global_sort = 0;


/*Main*/
int main()
{
    Character selector;

    while (selector != 'x')
    {
        selector = getchar();
        execute_command(selector);
    }

    return 0;
}



/*MAIN FUNCTIONS*/
/*a*/

/*Creates and adds a new unique product to a product array*/
void create_product()
{
    Product new_product;
    Character l_description[DESCRIPTION_LEN];
    Integer l_price = 0;
    Integer l_weight = 0;
    Integer l_stock = 0;

    scanf(" %[^:]:%d:%d:%d", l_description, &l_price, &l_weight, &l_stock);
    
    new_product.id = create_idP();
    strcpy(new_product.description, l_description);
    new_product.price = l_price;
    new_product.weight = l_weight;
    new_product.stock = l_stock;

    /*Stores new product on Global product array*/
    global_products[new_product.id] = new_product;

    printf("%s %d%s\n", "Novo produto", new_product.id, ".");
}

/*q*/

/*Adds a given ammount of stock to the respective product*/
void add_stock(Integer idP, Integer new_stock)
{
    Integer updated_stock;

    updated_stock = global_products[idP].stock + new_stock;

    if(valid_product(idP) == 0)
    {
        set_stock(idP, updated_stock);
        set_sorted_stock(idP, updated_stock);
    }   
        else
        {
            printf("%s %d %s\n","Impossivel adicionar produto", idP, "ao stock. Produto inexistente.");
        }
}

/*N*/

/*Creates a new unique empty order*/
void create_order()
{
    Order new_order;
    
    new_order.id = create_idO();

    new_order.weight = 0;
    new_order.chosen_counter = 0;

    /*Stores new order on Global order array*/
    global_orders[new_order.id] = new_order;

    printf("%s %d%s\n", "Nova encomenda", new_order.id, ".");
}

/*A*/

/*Adds a given product to the respective order*/
void add_product(Integer idO, Integer idP, Integer quantity)
{
    if (valid_order(idO) == 0 && valid_product(idP) == 0 && check_stock(idP, quantity) == 0 && check_weight(idO, idP, quantity) == 0)
    {
        if (in_order(idO, idP) != 0)
        {
            add_weight(idO, idP, quantity);
            global_orders[idO].selected_products[get_chosenPrd_count(idO)] = global_products[idP].id;
            global_orders[idO].quantity[get_chosenPrd_count(idO)] = quantity;
            remove_stock(idP, quantity);
            chosen_increment(idO);
        }
            else
            {
                update_quantity(idO, idP, quantity);
            }
    }   else if (valid_order(idO) == 1)
        {
            printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idP, "a encomenda", idO, ". Encomenda inexistente.");
        }
            else if (valid_product(idP) == 1)
            {
                printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idP, "a encomenda", idO, ". Produto inexistente.");
            }
                else if (check_stock(idP, quantity) == 1)
                {
                    printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idP, "a encomenda", idO, ". Quantidade em stock insuficiente.");
                }
                    else if (check_weight(idO, idP, quantity) == 1)
                    {
                        printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idP, "a encomenda", idO, ". Peso da encomenda excede o maximo de 200.");
                    }
}

/*r*/

/*Removes a given ammount of stock from the respective product*/
void remove_stock(Integer idP, Integer removed_stock)
{
    Integer updated_stock;

    updated_stock  = global_products[idP].stock - removed_stock;

    if (valid_product(idP) == 0 && updated_stock >= 0)
    {
        set_stock(idP, updated_stock);
        set_sorted_stock(idP, updated_stock);
    }   else if (valid_product(idP) == 1)
        {
            printf("%s %d%s\n","Impossivel remover stock do produto", idP, ". Produto inexistente.");
        }
            else if (updated_stock < 0)
            {
                printf("%s %d %s %d %s\n","Impossivel remover", removed_stock, "unidades do produto", idP, "do stock. Quantidade insuficiente.");            
            }
}

/*R*/

/*Removes as a given prodect from the respective order*/
void remove_product(Integer idO, Integer idP)
{
    Integer i, position, quantity;

    if (valid_order(idO) == 0 && valid_product(idP) == 0 && in_order(idO, idP) == 1)
    {
        
    }   else if (valid_order(idO) == 0 && valid_product(idP) == 0 && in_order(idO, idP) == 0)
        {
            position = find_product(idO, idP);
            quantity = get_quantity(idO, position);
            add_stock(idP, quantity);
            remove_weight(idO , idP, quantity);

            for (i = position ; i < get_chosenPrd_count(idO); i++)
            {
                global_orders[idO].selected_products[i] = global_orders[idO].selected_products[i + 1];
                global_orders[idO].quantity[i] = global_orders[idO].quantity[i + 1];
            }
            
            chosen_decrement(idO);        
        }   
            else if (valid_order(idO) == 1)
            {
                printf("%s %d %s %d%s\n", "Impossivel remover produto" ,idP ,"a encomenda", idO,". Encomenda inexistente.");
            }   
                else if (valid_product(idP) == 1)
                {
                    printf("%s %d %s %d%s\n", "Impossivel remover produto" ,idP ,"a encomenda", idO,". Produto inexistente.");
                }
}

/*C*/

/*Determines the total cost of a given order*/
void order_cost(Integer idO)
{
    Integer i, total;

    total = 0;

    if(valid_order(idO) == 0)
    {
        for (i = 0; i < get_chosenPrd_count(idO); i++)
        {
            total = total + (get_price(get_chosenPrd_id(idO, i)) * (get_quantity(idO, i)));
        } 

        printf("%s %d %d%s\n", "Custo da encomenda" ,idO , total, "."); 
    }   
        else
        {
            printf("%s %d%s\n", "Impossivel calcular custo da encomenda", idO,". Encomenda inexistente.");
        }   
}

/*p*/

/*Changes price of a given product*/
void change_price(Integer idP, Integer price)
{
    if (valid_product(idP) == 0)
    {
        set_price(idP, price);
        set_sorted_price(idP, price);
    }   
        else
        {
            printf("%s %d%s\n", "Impossivel alterar preco do produto", idP,". Produto inexistente.");
        }
    
}

/*E*/

/*Lists the description and amount of a product in a given order*/
void product_amount(Integer idO, Integer idP)
{
    if (valid_order(idO) == 0 && valid_product(idP) == 0)
    {
        if(in_order(idO, idP) == 0)
        {
            printf("%s %d%s\n", global_products[idP].description, get_quantity(idO, find_product(idO, idP)), ".");

        }   
            else
            {
                printf("%s %d%s\n", global_products[idP].description, 0, ".");
            }
        
    }   
        else if (valid_order(idO) == 1)
        {
            printf("%s %d%s\n", "Impossivel listar encomenda", idO,". Encomenda inexistente.");

        }   
            else if (valid_product(idP) == 1)
            {
                printf("%s %d%s\n", "Impossivel listar produto", idP,". Produto inexistente.");
            }
}

/*m*/

/*Find the order with the largest amount of a given product*/
void max_amount(Integer idP)
{
    Integer i, j, id, l_id, l_ammount;

    l_ammount = 0;

    if(valid_product(idP) == 0)
    {
        for (i = 0; i < global_idO; i++)
        {
            
            id = global_orders[i].id;
            j = find_product(id, idP);

            if(j != -1)
            {
                if (l_ammount < get_quantity(id, j))
                {
                    l_ammount = get_quantity(id, j);
                    l_id = id;
                }   
                    else if (l_ammount == get_quantity(id, j))
                    {
                        if(id < l_id)
                            l_id = id;
                    }
            }
        }
        if(l_ammount != 0)
            printf("%s %d %d %d%s\n", "Maximo produto", idP, l_id, l_ammount, ".");

    }   
        else
        {
            printf("%s %d%s\n", "Impossivel listar maximo do produto", idP,". Produto inexistente.");
        }
    
}

/*l*/

/*Sorts product array in acending order based on price*/
void sort_products()
{
    Integer i, j;
    Product temp_product;

    if (sizeof(global_products) > 1)
    {
        /*Create a copy of global products array*/
        while (global_sort < global_idP)
        {
            global_products_sorted[global_sort] = global_products[global_sort];
            global_sort++;
        }

        /*Sorting algorithm*/
        for (i = 0; i < global_idP; i++)
        {
            for (j = 0; j < global_idP; j++)
            {
                if(global_products_sorted[j].price > global_products_sorted[i].price)
                {
                    temp_product = global_products_sorted[i];
                    global_products_sorted[i] = global_products_sorted[j];
                    global_products_sorted[j] = temp_product;
                }
                    else if (global_products_sorted[j].price == global_products_sorted[i].price)
                    {
                        if (global_products_sorted[j].id > global_products_sorted[i].id)
                        {
                            temp_product = global_products_sorted[i];
                            global_products_sorted[i] = global_products_sorted[j];
                            global_products_sorted[j] = temp_product;
                        }
                    }
            }
        }
        /*Print sorted array*/
        print_Product(global_products_sorted);
    }
        else
        {
            /*Print array with only 1 object*/
            print_Product(global_products);
        }
}

/*L*/

/*Sorts a given order alphabetically based on the products description*/
void sort_order(Integer idO)
{
    Integer i, j, temp_id, temp_quantity;
    
    if (valid_order(idO) == 0)
    {
        /*Sorting algorithm*/
        for (i = 0; i < get_chosenPrd_count(idO); i++)
        {
            for (j = 0; j < get_chosenPrd_count(idO); j++)
            {
                if(global_products[get_chosenPrd_id(idO, j)].description[0] > global_products[get_chosenPrd_id(idO, i)].description[0])
                {
                    temp_id = global_orders[idO].selected_products[i];
                    temp_quantity = global_orders[idO].quantity[i];
                    global_orders[idO].selected_products[i] = global_orders[idO].selected_products[j];
                    global_orders[idO].selected_products[j] = temp_id;
                    global_orders[idO].quantity[i] = global_orders[idO].quantity[j];
                    global_orders[idO].quantity[j] = temp_quantity;
                }
                    else if (global_products[get_chosenPrd_id(idO, j)].description[0] == global_products[get_chosenPrd_id(idO, i)].description[0])
                    {
                        if (global_products[get_chosenPrd_id(idO, j)].description[1] > global_products[get_chosenPrd_id(idO, i)].description[1])
                        {
                            temp_id = global_orders[idO].selected_products[i];
                            temp_quantity = global_orders[idO].quantity[i];
                            global_orders[idO].selected_products[i] = global_orders[idO].selected_products[j];
                            global_orders[idO].selected_products[j] = temp_id;
                            global_orders[idO].quantity[i] = global_orders[idO].quantity[j];
                            global_orders[idO].quantity[j] = temp_quantity;
                        }
                    }
            }
        }
        /*Print sorted order*/
        print_Order(idO);
    } 
        else
        {
            printf("%s %d%s\n", "Impossivel listar encomenda", idO,". Encomenda inexistente.");
        }
    
}



/*AUXILIAR FUNCTIONS*/

/*Product*/
/*Getters*/
Integer get_price(Integer id)
{
    return global_products[id].price;
}

Integer get_weight_product(Integer id)
{
    return global_products[id].weight;
}

Integer get_stock(Integer id)
{
    return global_products[id].stock;
}

/*Setters*/
void set_product_id(Integer id)
{
    global_products[id].id = id;
}

void set_price(Integer id, Integer price)
{
    global_products[id].price = price;
}

void set_sorted_price(Integer idP, Integer price)
{
    Integer index;
    
    index = find_sorted_product(idP);

    if(global_sort > 0 && index != -1)
        global_products_sorted[index].price = price;
}

void set_weight_product(Integer id, Integer weight)
{
    global_products[id].weight = weight;
}

void set_stock(Integer id, Integer stock)
{
    global_products[id].stock = stock;
}

void set_sorted_stock(Integer idP, Integer stock)
{
    Integer index;
    
    index = find_sorted_product(idP);

    if(global_sort > 0 && index != -1)
        global_products_sorted[index].stock = stock;
}



/*Order*/
/*Getters*/
Integer get_chosenPrd_id(Integer id, Integer index)
{
    return global_orders[id].selected_products[index];
}

Integer get_chosenPrd_count(Integer idO){
    return global_orders[idO].chosen_counter;
}

Integer get_quantity(Integer id, Integer index)
{
    return global_orders[id].quantity[index];
}

Integer get_weight_order(Integer id)
{
    return global_orders[id].weight;
}

/*Setters*/
void set_order_id(Integer id)
{
    global_orders[id].id = id;
}

void set_weight_order(Integer id, Integer weight)
{
    global_orders[id].weight = weight;
}



/*Input*/

/*Choses what command to execute based on user input*/
void execute_command(Character selector)
{
    Integer * command;

    switch (selector)
        {
        case 'a':
            create_product();

            break;

        case 'q':
            command = get_command();
            add_stock(command[0], command[1]);

            break;
        
        case 'N':
            create_order();
            
            break;

        case 'A':
            command = get_command();
            add_product(command[0], command[1], command[2]);
            break;

        case 'r':
            command = get_command();
            remove_stock(command[0], command[1]);
            break;

        case 'R':
            command = get_command();
            remove_product(command[0], command[1]);
            break;

        case 'C':
            command = get_command();
            order_cost(command[0]);
            break;

        case 'p':
            command = get_command();
            change_price(command[0], command[1]);
            break;
        
        case 'E':
            command = get_command();
            product_amount(command[0], command[1]);
            break;

        case 'm':
            command = get_command();
            max_amount(command[0]);
            break;

        case 'l':
            sort_products();
            break;

        case 'L':
            command = get_command();
            sort_order(command[0]);
            break;

        case 'x':
            /*Close the program*/
            exit(0);
            break;

        default:
            break;
        }
}

/*Reads user input and returns an integer array of the split user input*/
Integer * get_command()
{
    Character command[100];
    Character delim[2] = ":";
    Character * token;
    static Integer split[3];
    Integer i = 0;

    scanf(" %s", command);
    token = strtok(command, delim);

    while (token != NULL)
    {
        split[i++] = atoi(token);
        token = strtok(NULL, delim);
    }

    return split;
}



/*IDs*/

/*Creates and returns unique products id*/
Integer create_idP()
{
    Integer new_id;

        new_id = global_idP;
        global_idP++;

    return new_id;
}

/*Creates and returns unique orders id*/
Integer create_idO()
{
    Integer new_id;

    new_id = global_idO;
    global_idO++;

    return new_id;
}



/*Weight*/

/*Checks if order weight is within limits and returns integer value based on that*/
Integer check_weight(Integer idO, Integer idP, Integer quantity)
{
    Integer product_w, current_w, new_w;

    product_w = get_weight_product(idP);
    current_w = get_weight_order(idO);

    new_w = current_w + product_w * quantity;
    if (new_w <= MAX_WEIGHT)
    {
        return 0;
    }

    return 1;
}

/*Adds weight to given order based on product and quantity*/
void add_weight(Integer idO, Integer idP, Integer quantity)
{
    Integer product_w, current_w, new_w;

    product_w = get_weight_product(idP);
    current_w = get_weight_order(idO);

    new_w = current_w + product_w * quantity;
    set_weight_order(idO, new_w);
}

/*Removes weight of given order based on product and quantity*/
void remove_weight(Integer idO, Integer idP, Integer quantity)
{
    Integer product_w, current_w, new_w;

    product_w = get_weight_product(idP);
    current_w = get_weight_order(idO);

    new_w = current_w - product_w * quantity;
    set_weight_order(idO, new_w);
}



/*Stock*/

/*Checks if there is enough stock of a given product to fulfill the stock rerquest and returns an integer value based on availability*/
Integer check_stock(Integer idP, Integer requested_stock)
{
    Integer stock;

    stock = get_stock(idP);

    if(stock >= requested_stock)
    {
        return 0;
    }

    return 1;
}



/*Quantity*/

/*Updates the quantity of a certain product on a given order*/
void update_quantity(Integer idO, Integer idP, Integer quantity)
{
    Integer index, updated_quantity;

    index = find_product(idO, idP);
    
    updated_quantity = global_orders[idO].quantity[index] + quantity;

    global_orders[idO].quantity[index] = updated_quantity;

    add_weight(idO, idP, quantity);

    remove_stock(idP, quantity);
}



/*Validity check*/

/*Checks if a given product exists and returns an integer value based on the validity*/
Integer valid_product(Integer idP)
{
    Integer i;

    for (i = 0; i < global_idP; i++)
    {
        if (idP == global_products[i].id)
        {
            return 0;
            break;
        }
    }
    return 1;
}

/*Checks if a given order exists and returns an integer value based on the validity*/
Integer valid_order(Integer idO)
{
    Integer i;
    
    for (i = 0; i < global_idO; i++)
    {
        if (idO == global_orders[i].id)
        {
            return 0;
            break;
        }
    }
    return 1;
}



/*Prints*/

/*Prints a given products array*/
void print_Product(Product * product)
{
    Integer i;

    printf("%s\n", "Produtos");

        for (i = 0; i < global_idP; i++)
        {
            printf("%s %s %d %d\n", "*", product[i].description, product[i].price, product[i].stock);
        }
}

/*Prints a given order*/
void print_Order(Integer idO)
{
    Integer i;
    Order order;

    order = global_orders[idO];

    printf("%s %d\n", "Encomenda", order.id);
    if (get_chosenPrd_count(idO) != 0)
    {
        for (i = 0; i < get_chosenPrd_count(idO); i++)
        {
            printf("%s %s %d %d\n", "*", global_products[get_chosenPrd_id(order.id, i)].description, global_products[get_chosenPrd_id(order.id, i)].price, order.quantity[i]);
        }
    }
}



/*Miscellaneous*/

void chosen_increment(Integer idO)
{
    global_orders[idO].chosen_counter++;
}


void chosen_decrement(Integer idO)
{
    global_orders[idO].chosen_counter--;
}

/*Checks if a given product is in a given order and returns an integer value based on that*/
Integer in_order(Integer idO, Integer idP)
{
    if (find_product(idO, idP) == -1)
    {
        return 1;
    }
    return 0;
}

/*Finds the index of a given prduct in a given order and returns the integer value corresponding if product is present */
Integer find_product(Integer idO, Integer idP)
{
    Integer i;

    i = 0;
    while (i < get_chosenPrd_count(idO))
    {
        if (global_orders[idO].selected_products[i] == idP)
        {
            return i;
            break;
        }
        i++;
    }
    return -1;
}

/*Finds the index of a given prduct in the sorted products array and returns the integer value corresponding if product is present */
Integer find_sorted_product(Integer idP)
{
    Integer i;

    for (i = 0; i < global_idP; i++)
    {
        if (global_products_sorted[i].id == idP)
        {
            return i;
            break;
        }
    }
    return -1;
    
}

