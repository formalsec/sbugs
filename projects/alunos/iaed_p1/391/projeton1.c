#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* Constants */
#define max_input_size 4000
#define max_stock_size 10000
#define max_delivery_size 200
#define max_listD_size 500
#define max_input 63
#define max_weight 200

/*
** PRODUCT STRUCT
*/
typedef struct 
{
 int identifier;
 int price;
 int weight;
 int amount;
 char description[max_input];
}product;


/*
** PRODUCTS IN DELIVERY STRUCT
*/
typedef struct 
{
  int p_id;
  int quantity;  
}products_in_delivery;

/*
** DELIVERY STRUCT
*/
typedef struct 
{
 int identifier;
 int weight;
 int product_count;
 /* Each delivery has a list with products. each product is composed by an id and quantity in the delivery*/
 products_in_delivery list_products[max_delivery_size];
}delivery;




/*   GLOBAL VARIABLES   */
product stock[max_stock_size];/*stock where all the products are*/
delivery list_deliverys[max_listD_size]; /* array where all the deliveries are*/
int idp = 0, ide = 0; /* idp its the id of the last product in the stock, +1 and ide is the id of the last delivery in the deliveries aray, +1*/

/* *******************************************************
ADD_PRODUCT_STOCK - function that adds a product to the
stock of products.
each products has a description a price a weight and a amount in stock
 ****************************************************** */


void addproduct_stock(char description[], int price, int weight, int amount)
{
 /* creates a new product*/
    product prod;
    if (idp < max_stock_size)
    {
    strcpy(prod.description, description); 
    prod.price = price;
    prod.weight = weight;
    prod.amount = amount;
        prod.identifier = idp;
   
    stock[idp] = prod;

    printf("Novo produto %d.\n", idp);

    idp++;  
    }
}


/* *******************************************************
ADD_PRODUCT_AMOUNT- function that adds a certain quantity of a product
(chosen by the user) to the amount that it already has in stock
 ****************************************************** */
void add_product_amount(int identifier, int amount)
{
    
    if (identifier < idp)
    {
        stock[identifier].amount += amount;
            
    }

    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", identifier);



}


/* *******************************************************
NEW_DELIVERY- function that Creates a new delivery.
 each delivery is deffined by and id, weight, number of products in it 
 and the products
 ****************************************************** */
void new_delivery()
{
    delivery new_d;

    new_d.identifier = ide;
    new_d.weight = 0;
    new_d.product_count =0;
    list_deliverys[ide] = new_d;
    printf("Nova encomenda %d.\n", ide);
    ide++;


}


/* *******************************************************
ADD_PRODUCT_TO_DELIVERY- function that adds products to a delivery (all chosen by the user)
 if the product already exist it increases its amount in the delivery 
 ****************************************************** */
void add_product_to_delivery(int id_delivery, int id_product, int amount)
{
   
    int item, new_weight,flag=0;

/*verifies if the delivery exists*/
    if (id_delivery < ide)
    {
    /*verifies if the products exist*/
        if (id_product < idp)
        {
        /* verifies if the amount of the product to add  in the delivery is not bigger than the amount that exists in stock*/
            if (amount <= stock[id_product].amount)
            {

                new_weight = list_deliverys[id_delivery].weight + stock[id_product].weight*amount;

            /*verifies if, after adding the procuct to the delivery it doesnt exceed the weight limit*/
                if (new_weight <= max_weight)
                    {
                        /*checking if the product already exists in the delivery*/
                        for(item= 0; item< list_deliverys[id_delivery].product_count; item++)
                        {
                            if (list_deliverys[id_delivery].list_products[item].p_id == id_product)
                                /* if the product exists in the delivery*/
                            {
                                /*increases the amount of the product in the delivery*/
                                list_deliverys[id_delivery].list_products[item].quantity += amount;
                                /*gives the delivery its new weight*/
                                list_deliverys[id_delivery].weight = new_weight;
                                /* subtracts the amount addded to the delivery to the amount in stock*/
                                stock[id_product].amount-=amount;
                                /* changes the flag value, this way we know that the product was in the delivery*/
                                flag++;
                            }
                        }
                        /*if the product wasnt in the delivery*/
                        if (flag == 0)
                             {
                                /*creates a new product in delivery*/
                                products_in_delivery new_product;
                                /* gives it its id*/
                                new_product.p_id = stock[id_product].identifier;
                                /* gives it its amount*/
                                new_product.quantity = amount;
                                /* adds the new product to the list of products of the delivery*/
                                list_deliverys[id_delivery].list_products[list_deliverys[id_delivery].product_count]= new_product;
                                /* increases the number of products of the delivery*/
                                list_deliverys[id_delivery].product_count++;
                                /* subtracts the amount addded to the delivery to the amount in stock*/
                                stock[id_product].amount-=amount;
                                /*gives the delivery its new weight*/
                                list_deliverys[id_delivery].weight = new_weight;

                             }

                    }
                    else
                        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",id_product, id_delivery);

            }
            else 
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_product, id_delivery);
        }
        else
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",id_product, id_delivery);
    }

    else
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",id_product, id_delivery);

}


/* *******************************************************
REMOVE_PRODUCT_STOCK- function that removes amount quantity of a product 
 in the stock
 ****************************************************** */
void remove_product_stock(int identifier, int amount)
{
    /* verifies if the product exists*/
    if (identifier < idp)
    {   
        /* verifies if the amount that we want to remove is bigger that what exists, if it isnt, removes*/
        if (amount <= stock[identifier].amount)stock[identifier].amount -= amount;

        else
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n" ,amount, identifier);
    }

    else
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", identifier);

}

void TESTE_encomenda(int id_delivery)
{
    int i=0;
    for(i = 0; i< list_deliverys[id_delivery].product_count; i++)
        printf("%d", list_deliverys[id_delivery].list_products[i].p_id);
}

/* *******************************************************
REMOVE_PROD_DELIVERY- function that removes the product of a delivery by 
deliting it
 ****************************************************** */
void remove_prod_delivery(int id_delivery, int id_product)
{
    int position, i, ii;
  
  
    if (id_delivery < ide) 
    {
        if (id_product < idp)
        {
            for(i = 0; i< list_deliverys[id_delivery].product_count; i++)

            {
                /* finding the product in the delivery*/
                if (list_deliverys[id_delivery].list_products[i].p_id == id_product)
                {
                    /*saves the position of the product in the delivery*/
                    position = i;
                    /*replaces the quantities in the stock, the wight in the delivery, the price etc...*/
                    stock[id_product].amount += list_deliverys[id_delivery].list_products[i].quantity;
                    list_deliverys[id_delivery].weight -= stock[id_product].weight *  list_deliverys[id_delivery].list_products[i].quantity;
                    list_deliverys[id_delivery].list_products[i].quantity = 0;

                    /*removes the product from the delivery by shfting to the left all the products of the delivery starting in... the position*/
                    for (ii = position; ii <list_deliverys[id_delivery].product_count-1; ii++)
                    list_deliverys[id_delivery].list_products[ii] = list_deliverys[id_delivery].list_products[ii+1];
                    list_deliverys[id_delivery].product_count--;

                }
                
            }
            
        }
        else 
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n" ,id_product, id_delivery);
    }
    else
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",id_product, id_delivery);
        
}

/* *******************************************************
DELIVERY_COST - function that calculates the price of a delivery
 ****************************************************** */
void delivery_cost(int id_delivery)
{
    int total_price = 0, i = 0;

    
    if (id_delivery < ide)
    {
        total_price = 0;
        for (i= 0; i < list_deliverys[id_delivery].product_count; i++)
        {
            /* for each product of the delivery sum its price times its quantity*/
           total_price += stock[list_deliverys[id_delivery].list_products[i].p_id].price * list_deliverys[id_delivery].list_products[i].quantity;
          
        }
        printf("Custo da encomenda %d %d.\n",id_delivery, total_price);
        
    }
    else
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_delivery);
    
}

/* *******************************************************
CHANGE_PRODUCT_PRICE- function that changes the price of a product
 ****************************************************** */
void change_product_price(int id_product, int new_price)
{
    if (id_product < idp) stock[id_product].price = new_price;
    else
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_product);
   
}

/* *******************************************************
print_product- function that prints the product of a delivery- description, quantity
 ****************************************************** */
void print_product(int id_delivery, int id_product)
{
    int i, flag=0;

    if (id_delivery < ide)
    {
        if(id_product < idp)
        {
            for(i = 0; i < list_deliverys[id_delivery].product_count; i++)
            {
                /*finding the product in the delivery*/
                if (id_product == list_deliverys[id_delivery].list_products[i].p_id)
                {
                    /*prints it when it finds it*/
                    printf("%s %d.\n", stock[id_product].description, list_deliverys[id_delivery].list_products[i].quantity);
                    /* marks that the product was in the delivery*/
                    flag ++;
                }
            }

            /* if it wasnt in the delivery  only prints the desciption of the product*/
            if (flag ==0)printf("%s 0.\n",stock[id_product].description);
        }  
        else
            printf("Impossivel listar produto %d. Produto inexistente.\n", id_product);
    }
    else
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_delivery);
    
}

/* *******************************************************
largest_order_by_product- function that prints the delivery where a product
 appears the most and its ammount - (id of the product, id of the delivery, ammount)
 ****************************************************** */
void largest_order_by_product(int id_product)
{
    int iddelivery_maxprod=0, max_amount=0, i=0, ii=0, flag =0;

    if (id_product < idp)
    {
        /*iterates trough all the deliveries*/
        for(i=0; i<ide; i++)
        {
            /*iterates all the products in a delivry*/
            for(ii=0; ii<list_deliverys[i].product_count; ii++)
            {
                /*everytime it finds the product in question*/
                if (list_deliverys[i].list_products[ii].p_id == id_product)
                {
                    if (flag == 0) flag++;
                    /* checks if the amount of the product in that delivery is bigger than the max ammount, if it is the max_amount is now the amount of he product in that delivery*/
                    if (list_deliverys[i].list_products[ii].quantity > max_amount)
                    {
                        max_amount = list_deliverys[i].list_products[ii].quantity;
                        iddelivery_maxprod = i;
                    }

                }
            }
        }
        if (flag !=0) printf("Maximo produto %d %d %d.\n", id_product, iddelivery_maxprod, max_amount);
        else
            /* if the product doesnt exist in any delivery doesent do anything*/
            return;
    }
    else
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_product);
    }
}

/*
FOR DEVELOPMENT ONLY
void print_test(char where[], int stock_p[])
{
    int ii;
    printf ("%s:",where);
    for (ii=0; ii<4; ii++)
            printf("%s%d",(ii > 0  ? "," : ""),stock[stock_p[ii]].identifier);
    printf ("\r\n");
}
*/

/* *******************************************************
INITIALIZE_STOCK_PRICE_INDEX- this function creates a new array
 with only the index of all the products in the stock
 ****************************************************** */
void initialize_stock_price_index(int stock_price_index[])
{
    int i;
    for(i=0; i< idp; i++)
        stock_price_index[i] = i;
}

/* *******************************************************
quicksort_partition-price- sorts an array of id of products in a way that all the id with a correspondent price in the 
 left of a number (pivot) are smaller than the price correspondet to the pivot and the prices of the idps in the right are bigger
 and returns the position of the pivot
 ****************************************************** */
int quicksort_partition_price(int stock_pri[] , int l, int r)
{
    int pivot = r /* by default is the number in the right of the array*/, left = l-1, right = r, save_num;

    while(left < right)
    {
        /* starts to iterate from the left*/
        while(stock[stock_pri[++left]].price < stock[stock_pri[pivot]].price);
        /* when it finds a number bigger than the pivot stops and starts to iterate from the right*/
        while(left != right && stock[stock_pri[--right]].price> stock[stock_pri[pivot]].price);
        /* when it finds a number smaller than the pivot stops*/
        if (left<right)
        {
            /*exchanges those numbers*/
        save_num= stock_pri[left];
        stock_pri[left] = stock_pri[right];
        stock_pri[right] = save_num;

        }
   
    }
    /*exchanges the pivot with the first number bigger than it counting from the right*/
    save_num = stock_pri[left];
    stock_pri[left] = stock_pri[pivot];
    stock_pri[pivot] = save_num;
    /*returns the position of the pivot in the array*/
    return left;



}

/* *******************************************************
QUICKSORT_PRICE- function that has an algorythm implemented that sorts 
in this case, an array of id s in acording with its correspondent price 
 ****************************************************** */
void quicksort_price(int stock_p[], int left, int right)
{
    int i;
    if (right <= left )
        return;
    i = quicksort_partition_price(stock_p, left, right);
    /*apllies the function quicksort recusrively sorting half after half after half.. of the array until its sorted*/ 
    quicksort_price(stock_p, left,i-1);
    quicksort_price(stock_p, i+1, right);
}






/* *******************************************************
quicksort_partition-idp- sorts an array of id of products with the same price in a way that all the id in the 
 left of a number (pivot) are smaller than the  pivot and the idps in the right are bigger
 and returns the position of the pivot
 ****************************************************** */
int quicksort_partition_idp(int stock_pri[] , int l, int r)
{
    int pivot = r, left = l-1, right = r, save_num;

    while(left < right)
    {
        while(stock[stock_pri[++left]].identifier < stock[stock_pri[pivot]].identifier);
        while(left != right && stock[stock_pri[--right]].identifier> stock[stock_pri[pivot]].identifier);
        if (left<right)
        {
        save_num= stock_pri[left];
        stock_pri[left] = stock_pri[right];
        stock_pri[right] = save_num;

        }
   
    }
    save_num = stock_pri[left];
    stock_pri[left] = stock_pri[pivot];
    stock_pri[pivot] = save_num;
    return left;



}

/* *******************************************************
quicksort_idp- sorts the idps of products with the same price when all the idps are already sorted by price
 ****************************************************** */
void quicksort_idp(int stock_p[], int left, int right)
{
    int i;
    if (right <= left )
        return;
    i = quicksort_partition_idp(stock_p, left, right);
    quicksort_idp(stock_p, left,i-1);
    quicksort_idp(stock_p, i+1, right);
} 


/* *******************************************************
/PRINT_STOCK_PRODUCT_BY_PRICE- prints all the products of the stock but sorted by price
 and the elements with the same price sorted by idp
 ****************************************************** */
void print_stock_product_by_price()
{
    int stock_price_index[max_stock_size], i,l,i1=0, r=0, flag;
    int left=0, right = idp-1;

    initialize_stock_price_index(stock_price_index);
    /*sorts the array of ids according with their correspondent price*/
    quicksort_price(stock_price_index, left, right);
    /* sorts the idps with the same price from the smaller to the greatest*/
    while(i1<idp-1)
    {
        flag =0;
        /*if it finds 2 consecutive ids with the same price*/
        if (stock[stock_price_index[i1]].price == stock[stock_price_index[i1+1]].price)   
        {
            flag++;
            r=i1;
            l=i1;
            /*saves the positions where all the idps have the same price*/
            while(r < idp-1 &&(stock[stock_price_index[r]].price == stock[stock_price_index[r+1]].price) )
                r++;
            /* sorts them from the smallest id to the biggest*/
            quicksort_idp(stock_price_index,l,r);
        }
        if (flag ==0)
        i1++;
        else
            i1 =r;
    }

    printf("Produtos\n");
    for (i=0; i<idp; i++)
            printf("* %s %d %d\n", stock[stock_price_index[i]].description, stock[stock_price_index[i]].price, stock[stock_price_index[i]].amount);
}





/* *******************************************************
INITIALIZE_DELIVERY_PRODUCTS_INDEX- initializes a array with the index of the products in the delivery
****************************************************** */
void initialize_delivery_products_index(int delivery_products_index[], int id_delivery)
{
    int i;
    for (i=0; i<list_deliverys[id_delivery].product_count; i++)
    {
        delivery_products_index[i] = list_deliverys[id_delivery].list_products[i].p_id;
    }

}




int quicksort_partition_alphabetical(int delivery_products_index[] , int l, int r)
{
    int pivot = r, left = l-1, right = r, save_num;
    
    
    
    
    while(left < right)
    {
        
        while(strcmp(stock[delivery_products_index[++left]].description, stock[delivery_products_index[pivot]].description)<0);
        /* when it finds a description with bigger acii than the pivot in the same amount of letters stops and starts to iterate from the right*/
        while(left != right && strcmp(stock[delivery_products_index[--right]].description, stock[delivery_products_index[pivot]].description)>0);
       /* when it finds a description with smaller ascii in tha same amount of letters than the pivot stops*/
        if (left<right && strcmp(stock[delivery_products_index[left]].description, stock[delivery_products_index[right]].description)>0)
        {
            /*exchanges those to ids */
           save_num= delivery_products_index[left];
            delivery_products_index[left] = delivery_products_index[right];
            delivery_products_index[right] = save_num;
        }
    }
  
      /*exchanges the pivot with the first id that has a description bigger than the pivot corresponding description counting from the right*/  
    save_num = delivery_products_index[left];
    delivery_products_index[left] = delivery_products_index[pivot];

    delivery_products_index[pivot] = save_num;
    
   /*returns the position of the pivot in the array*/
    return left;
}

/* *******************************************************
quicksort_alphabetical- sorts the idps of products in a delivery acordint with their description
 ****************************************************** */
void quicksort_alphabetical(int stock_p[], int left, int right)
{
    int i;
   
    if (right <= left )
        return;

    i = quicksort_partition_alphabetical(stock_p, left, right);
    quicksort_alphabetical(stock_p, left,i-1);
    quicksort_alphabetical(stock_p, i+1, right);
}


void print_delivery_products_alphabetically(int id_delivery)
    {
    int delivery_products_index[max_delivery_size], i=0, delivery_products_quantities[max_delivery_size];
    int left  = 0, right = list_deliverys[id_delivery].product_count-1, x, w;
    if (id_delivery < ide)
    {
        initialize_delivery_products_index(delivery_products_index, id_delivery);
        quicksort_alphabetical(delivery_products_index, left, right);
        /*after sorting  by description every idp of the products in the delivery*/
        printf("Encomenda %d\n", id_delivery);


        if (list_deliverys[id_delivery].product_count >0)
        {
        /*creates a new array with the quantities of each product in the delivery*/
        for (x=0; x<list_deliverys[id_delivery].product_count; x++)
        {
            for(w=0; w<list_deliverys[id_delivery].product_count; w++)
            {
                if (list_deliverys[id_delivery].list_products[w].p_id == delivery_products_index[x])
                    delivery_products_quantities[x]= list_deliverys[id_delivery].list_products[w].quantity;
            }
        }
        /* prints the products obtaining its description putting each index of the delivery_products_index array as a index of the stock, and then going to the delivery_products_quantities so see its
        corresponding quantitie*/
        for (i=0; i<list_deliverys[id_delivery].product_count; i++)
                printf("* %s %d %d\n", stock[delivery_products_index[i]].description, stock[delivery_products_index[i]].price, delivery_products_quantities[i]);
        } 
    }
    else
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_delivery );
    }

/*********************************************************************
** PARSE COMMAND- Receives the user command, parses it and executes the required function
**********************************************************************/
bool parse_command(char input[])
{
    int identifier=0, price=0, weight=0, amount=0, id_delivery=0, id_product=0, new_price =0;
    char description[63];
    char command[1], parameters[255];
    
    /* get the command and the parameters */
    sscanf(input, "%s %s",command, parameters);

    /* execute the command */
    
        switch(command[0])
        {
            case 'a': 
            {
                    sscanf(parameters, "%[^:]:%d:%d:%d",description, &price, &weight, &amount);
                    addproduct_stock(description, price, weight, amount);
                    break;
            }
            case 'q':

                    sscanf(parameters, "%d:%d",&identifier, &amount);
                    add_product_amount(identifier,amount);
                    break;
            case 'N':
                    new_delivery();
                    break;
            case 'A':

                    sscanf(parameters, "%d:%d:%d",&id_delivery, &id_product, &amount);
                    add_product_to_delivery(id_delivery, id_product, amount);
                    break;
            case 'r':
                    sscanf(parameters, "%d:%d",&identifier, &amount);
                    remove_product_stock(identifier, amount);
                    break;
            case 'R':       
                    sscanf(parameters, "%d:%d",&id_delivery, &id_product);     
                    remove_prod_delivery(id_delivery, id_product);
                    break;
            case 'C':
            
                    sscanf(parameters, "%d",&id_delivery);
                    delivery_cost(id_delivery);
                    break;
            case 'p':
                    sscanf(parameters, "%d:%d",&id_product, &new_price);
                    change_product_price(id_product, new_price);
                    break;
            case 'E':
            {
                    
                    sscanf(parameters, "%d:%d",&id_delivery, &id_product);
                    print_product(id_delivery, id_product);
    
                    break;
            }
            case 'm':
            {
                    sscanf(parameters,"%d", &id_product);
                    largest_order_by_product(id_product);
    
                    break;
            }
            case 'l':
                    print_stock_product_by_price();
                    break;
            case 'L':
                    sscanf(parameters, "%d",&id_delivery);
                    print_delivery_products_alphabetically(id_delivery);            
                    break;
            case 'x':
                    /* no more inputs, exit */
                    return false;            
        }

    return true;
}

/*********************************************************************
**read_and_parse_commands- gets the input from the user and executes the corresponding command
**********************************************************************/ 
void read_and_parse_commands()
{
    char input[max_input_size];

    do 
    {

        /* get commands from the user */
        fgets(input, max_input_size, stdin);
    } while (parse_command(input));  
}



int main()
{
   
    /* My tests - FOR DEVELOPMENT TESTS ONLY!!!*/
    /* simulate user commands */
    /*
    char commands[][20] = {"a aXXa:10:2:3","a uaaa:50:1:1","a portatil:100:1:1","a lapis:2:2:2","a borracha:5:1:1","N","A 0:1:1","A 0:0:2","I","A 0:2:1","A 0:3:1", ""};
    int i = 0;
    for (i = 0; strlen(commands[i]) > 0; i++)
    {
        parse_command(commands[i]);
    }
    */

      read_and_parse_commands();
    return 0;
}


