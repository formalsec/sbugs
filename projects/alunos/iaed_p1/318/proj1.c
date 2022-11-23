#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*-------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------CONSTANTS--------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/

/*The maximum number of characters that the input can receive.*/
#define max_input 5000
/*The maximum number of different products that the system can support.*/
#define max_products 10000
/*The maximum number of orders accepted.*/
#define max_orders 500
/*The maximum number of characters that a description of a product can have.*/
#define max_description 63
/*The maximum weight units that an order can have.*/
#define max_weight 200

/*-------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------STRUCTURES-------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/

/*The struct "product" is used to define the products that are in the system.*/
typedef struct
{
	char description[max_description];
	int identifier_product;
	int price;
	int weight;
	int stock;
}product;

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*The struct "order" is used to define the orders that are in the list of orders.*/
typedef struct 
{
	/*Array of product quantities. The lenght is max_products so the quantity of each product in the order is in the <idp of the product> index.*/
	int lista_quantities[max_products];
	/*Array of the idps of the products in the order*/
	int list_of_idps[max_weight];
	int identifier_order;
	/*The sum of the weight of each product in the order multiplied by their quantity.*/
	int total_weight;
	/*Number of different products in the order.*/
	int num_of_products;
}order;

/*-------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------GLOBAL VARIABLES----------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Array of products.*/
product sistema[max_products];
/*Counts the number of different products in the system.*/
int idp_counter=0;

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Array of orders.*/
order list_of_orders[max_orders];
/*Counts the number of orders in the list_of_orders.*/
int ide_counter=0;

/*-------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------AUXILIARY FUNCTIONS------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Calculates or changes the total_weight of an order after adding or removing a product.*/
int calculates_or_changes_order_weight(char option[], int ide, int idp, int quantity, char sign)
{
	/*Variable that will contain the weight of the order after the change.*/
	int weight_atual=0;

	/*If we're adding products to the order the sign will be '+'.\
		If we're removing products from the order the sign will be '-'.\
		The weight_atual is calculated summing/subtracting the total_weight of the order <ide> with the product <idp> weight multiplied by the quantity.*/
	if (sign == '+') weight_atual = list_of_orders[ide].total_weight + (sistema[idp].weight)*quantity;
		else weight_atual = list_of_orders[ide].total_weight - (sistema[idp].weight)*quantity;

	/*If we want to actually change the order's weight the option will be "change".*/
	if (strncmp(option,"change", 6) == 0)
	{
		list_of_orders[ide].total_weight = weight_atual;
		return 0;
	}
	/*If we just want to calculate the order's weight the option will be "calculate".*/
	else return weight_atual;
}


/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Removes a certain idp from the list_of_idps of a certain order.*/
void remove_idp_from_list_of_idps(int idp, int ide)
{
	int i, ii;

	for (i=0; i < list_of_orders[ide].num_of_products; i++)
		{	/*Finds the index where the idp wanted is.*/
			if (list_of_orders[ide].list_of_idps[i] == idp)
			{	/*Iterates every index from the one that has the idp wanted to the last one in the order.*/
				for (ii=i; ii < list_of_orders[ide].num_of_products; ii++)
				{	/*Puts in the index ii the idp from the next index, eliminating the idp wanted.*/
					list_of_orders[ide].list_of_idps[ii] = list_of_orders[ide].list_of_idps[ii+1];
				}
				break;
			}
		}
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Compares two prices, idps, or descriptions, depending on the option.
	Returns a negative number if the object in the index 'b' is bigger than the one in 'a'.
	Returns a positive number in the opposite case.
	Returns '0' if they're equal.*/
int compare(char option[], int list_to_ordenate[], int a, int b)
{
	if (strncmp(option,"price", 5) == 0)
		return (sistema[list_to_ordenate[a]].price-sistema[list_to_ordenate[b]].price);

	if (strncmp(option,"identifier", 10) == 0)
		return (list_to_ordenate[a]-list_to_ordenate[b]);

	else return (strcmp(sistema[list_to_ordenate[a]].description, sistema[list_to_ordenate[b]].description));
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Exchanges the element in the index 'a' with the one in 'b'.*/
void exch(int list_to_ordenate[], int a, int b)
{
	int x = list_to_ordenate[a];

	list_to_ordenate[a] = list_to_ordenate[b];
	list_to_ordenate[b] = x;
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Calculates the new pivot used in quicksort_by_price_or_idp_or_alpha and exchanges elements in the list in order to ordenate it by the chosen option.*/
int partition(char option[], int list_to_ordenate[], int l, int r)
{
	int i = l-1;
	int j = r;
	
	while (i < j)
	{	/*Finds the index where the object is bigger than the object in the pivot ('r') index.*/
		while (compare(option, list_to_ordenate, ++i, r) < 0);
		/*Finds the index where the object is smaller than the object in the pivot ('r') index.*/
		while (compare(option, list_to_ordenate, r, --j) < 0)
		{
			if (j == l) break;
		}
		/*Exchanges the idps from the indexs found before.*/
		if (i < j) exch(list_to_ordenate, i, j);
	}
	/*Exchanges the idps from the indexs 'i' and 'r'.*/
	exch(list_to_ordenate, i, r);
	/*Returns new pivot.*/
	return i;
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Recursive function that ordenates a list of idps based on the price, description or actual idp (depending on the option) from the index 'l' to 'r'.*/
void quicksort_by_price_or_idp_or_alpha(char option[], int list_to_ordenate[], int l, int r)
{
	int i;
	/*If r<=l it reached the final.*/
	if (r <= l) return;
	/*Contains the new pivot used in the next calls of the function.*/
	i = partition(option, list_to_ordenate, l, r);
	quicksort_by_price_or_idp_or_alpha(option, list_to_ordenate, l, i-1);
	quicksort_by_price_or_idp_or_alpha(option, list_to_ordenate, i+1, r);
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Ordenates the idps of the products with the same price.*/
void ordenate_idps(int list_to_ordenate[])
{
	int left=0, right=1, save_r, flag=0;

	while (left<idp_counter-1)
	{	/*Finds the products with the same price.*/
		if (sistema[list_to_ordenate[left]].price == sistema[list_to_ordenate[right]].price)
		{
			/*The products with the same price will be from the index "left" to "right".*/
			while (sistema[list_to_ordenate[left]].price == sistema[list_to_ordenate[right]].price)
			{	/*It only iterates until the last element.*/
				if (right<idp_counter) right++;
				else break;
			}
			save_r=right;
			/*It will ordenate by idp the elements of the list from index "left" to "right".*/
			quicksort_by_price_or_idp_or_alpha("identifier", list_to_ordenate, left, right-1);
			flag++;
		}
		/*If flag==0 the products in "left" and "right" have different prices so we want to analyse the next elements.*/
		if (flag==0)
		{
			left++;
			right++;
		}
		/*If flag!=0 the products from "left" to "save_r" were already ordenated so we want to restart analysing the prices from index "save_r".*/
		if (flag!=0) 
		{
			left=save_r;
			right=save_r+1;
			flag = 0;
		}	
	}
}

/*-------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------FUNCTIONS ABOUT THE SYSTEM------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Adds a new product to the system*/
void new_product_in_system(char description[], int price, int weight, int stock)
{
	product new_p;

	new_p.identifier_product = idp_counter;
	strcpy(new_p.description, description);
	new_p.price = price;
	new_p.weight = weight;
	new_p.stock = stock;

	sistema[idp_counter] = new_p;

	printf("Novo produto %d.\n", idp_counter);
	idp_counter++;
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Adds a certain stock to a product that already exists in the system.*/
void add_stock_product(int idp, int quantity)
{	/*Verifies if the product exists.*/
	if (idp < idp_counter) sistema[idp].stock += quantity;
	else printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Removes a certain stock from a product in the system.*/
void remove_stock_product(int idp, int quantity)
{	/*Verifies if the product exists.*/
	if (idp < idp_counter)
		{	/*Verifies if the quantity to remove exists.*/
			if (sistema[idp].stock >= quantity) sistema[idp].stock -= quantity;
			else printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantity, idp);
		}
	else printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Changes the price of a product.*/
void change_product_price(int idp, int new_price)
{	/*Verifies if the product exists.*/
	if (idp < idp_counter) sistema[idp].price = new_price;
	else printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Prints all the products in the system by their price. In case of products with the same price, they're ascending ordenated by their idp.*/
void print_system_by_price()
{
	int i;
	/*Contains the idp of the product to print.*/
	int idp_to_print;
	/*List that's going to be ordenated.*/
	int list_to_ordenate[max_products];

	/*Copies the original list to the new one.*/
	for (i=0; i<idp_counter; i++)
	{
		list_to_ordenate[i] = i;
	}
	/*Ordenates the idps of the products by their price.*/
	quicksort_by_price_or_idp_or_alpha("price", list_to_ordenate, 0, idp_counter-1);
	/*Ordenates the products with the same price by their idps.*/
	ordenate_idps(list_to_ordenate);

	printf("Produtos\n");
	/*Iterates the ordenated list to print every product.*/
	for (i=0; i<idp_counter; i++)
	{
		idp_to_print = list_to_ordenate[i];
		printf("* %s %d %d\n", sistema[idp_to_print].description, sistema[idp_to_print].price, sistema[idp_to_print].stock);
	}
}

/*-------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------FUNCTIONS ABOUT THE ORDERS--------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Creates a new order and puts it in the list_of_orders.*/
void new_order()
{
	int i;
	order new_order;
	new_order.identifier_order = ide_counter;
	new_order.total_weight = 0;
	new_order.num_of_products = 0;
	for (i=0;i<max_products;i++)
	{
		new_order.lista_quantities[i]=0;
	}

	list_of_orders[ide_counter] = new_order;

	printf("Nova encomenda %d.\n", ide_counter);
	ide_counter++;
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Adds a certain product to a certain order.*/
void add_product_to_order(int ide, int idp, int quantity)
{	/*Verifies if the order exists.*/
	if (ide < ide_counter)
	{	/*Verifies if the product exists.*/
		if (idp < idp_counter)
		{	/*Verifies if the quantity of the product wanted to add exists in stock.*/
			if (sistema[idp].stock >= quantity)
			{	/*Verifies if by adding this quantity of this product the total_weight of the orders doesn't exceed the maximum.*/
				if (calculates_or_changes_order_weight("calculate", ide, idp, quantity, '+') <= max_weight)
				{	/*Verifies if product doesn't exist in the order.*/
					if (list_of_orders[ide].lista_quantities[idp] == 0)
					{	/*Adds the idp of the new product to the list_of_idps of the order.*/
						list_of_orders[ide].list_of_idps[list_of_orders[ide].num_of_products] = idp;
						/*Increases the number of different products in the order.*/
						list_of_orders[ide].num_of_products++;
					}
					/*Adds the quantity of the product to the index <idp>.*/
					list_of_orders[ide].lista_quantities[idp] += quantity;
					/*Changes the total_weight of the order after the addition.*/
					calculates_or_changes_order_weight("change", ide, idp, quantity, '+');
					/*Removes the quantity added to the order from the product stock.*/
					remove_stock_product(idp, quantity);
				}
				else printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
			}
			else printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		}
		else printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Removes a certain product from a certain order.*/
void remove_product_from_order(int ide, int idp)
{	/*Verifies if the order exists.*/
	if (ide < ide_counter)
	{	/*Verifies if the product exists.*/
		if (idp < idp_counter)
		{	/*Verifies if the product exists in the order.*/
			if (list_of_orders[ide].lista_quantities[idp] > 0 ) 
			{	/*Restores in stock the quantity of the product in the order.*/
				add_stock_product(idp, list_of_orders[ide].lista_quantities[idp]);
				/*Changes the total_weight of the order after the removal.*/
				calculates_or_changes_order_weight("change", ide, idp, list_of_orders[ide].lista_quantities[idp], '-');
				/*Puts the quantity of the product in the order to 0.*/
				list_of_orders[ide].lista_quantities[idp] = 0;
				/*Removes the idp of the product from the list_of_idps of the order.*/
				remove_idp_from_list_of_idps(idp, ide);
				/*Decreases the number of different products in the order.*/
				list_of_orders[ide].num_of_products--;
			}
		}
		else printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Prints the cost of a certain order.*/
void cost_of_order(int ide)
{	
	int i;
	/*It will contain the cost of the order.*/
	int cost = 0;
	/*It will contain the idp of the different products in the order.*/
	int idp;

	/*Verifies if the order exists.*/
	if (ide < ide_counter)
	{	/*Iterates the list_of_idps of the order.*/
		for (i=0; i < list_of_orders[ide].num_of_products; i++)
		{	/*Puts the idp from the index 'i' in the variable.*/
			idp = list_of_orders[ide].list_of_idps[i];
			/*Adds the price of the product <idp> multiplied by its quantity in the order to the variable cost.*/
			cost += (sistema[idp].price)*(list_of_orders[ide].lista_quantities[idp]);
		}
		printf("Custo da encomenda %d %d.\n", ide, cost);
	}
	else printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Prints the quantity of a certain product in a certain order.*/
void quantity_of_product_in_order(int ide, int idp)
{
	/*Verifies if the order exists.*/
	if (ide < ide_counter)
	{	/*Verifies if the product exists.*/
		if (idp < idp_counter)
		{	/*Prints the description and the quantity of the product that is in the order.*/
			printf("%s %d.\n", sistema[idp].description, list_of_orders[ide].lista_quantities[idp]);
		}
		else printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	}
	else printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Prints the order that has the largest amount of a certain product and its quantity.*/
void order_w_more_qnt_product(int idp)
{	
 	int i;
	/*It will contain the ide of the order that has the largest amount of the product.*/
	int ide_w_more_qnt = 0;
	/*It will contain the quantity of the product in the order <ide_w_more_qnt>.*/
	int max_quantity = 0;

	/*Verifies if the product exists.*/
	if (idp < idp_counter)
	{	/*Iterates the list_of_orders.*/
		for (i=0; i<ide_counter; i++)
		{	/*Compares the quantity of the product in the order from the index 'i' with the max_quantity found so far.*/
			if (list_of_orders[i].lista_quantities[idp] > max_quantity)
			{	/*Updates the order and the quantity.*/
				max_quantity = list_of_orders[i].lista_quantities[idp];
				ide_w_more_qnt = i;
			}
		}
		/*It only prints if the product exists in any order.*/
		if (max_quantity != 0) printf("Maximo produto %d %d %d.\n", idp, ide_w_more_qnt, max_quantity);
	}
	else printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*Prints the products of a certain order alphabetically.*/
void print_order_by_alpha(int ide)
{
	int i;
	/*Contains the idp of the product to print.*/
	int idp_to_print;
	/*List that's going to be ordenated.*/
	int list_to_ordenate[max_weight];

	/*Verifies if the order exists.*/
	if (ide<ide_counter)
	{	/*Copies the original list to the new one.*/
		for (i=0; i < list_of_orders[ide].num_of_products; i++)
		{
			list_to_ordenate[i] = list_of_orders[ide].list_of_idps[i];
		}
		/*Ordenates the idps of the list according to the respective description.*/
		quicksort_by_price_or_idp_or_alpha("description", list_to_ordenate, 0, list_of_orders[ide].num_of_products-1);
		printf("Encomenda %d\n",ide);
		/*Iterates the ordenated list to print every product.*/
		for (i=0; i < list_of_orders[ide].num_of_products; i++)
		{
			idp_to_print = list_to_ordenate[i];
			printf("* %s %d %d\n", sistema[idp_to_print].description, sistema[idp_to_print].price, list_of_orders[ide].lista_quantities[idp_to_print]);
		}
	}
	else printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}

/*-------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------CICLO MAIN-----------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/

int main()
{	/*Contains the input.*/
    char input[max_input];
    /*Arguments used in the functions called by the commands.*/
    int ide, idp, price, weight, stock, quantity, new_price;
    char description[max_description];

    while(1)
    {	/*Gets input from the user.*/
    	fgets(input, max_input, stdin);
    	/*Links each command to its function.*/
        switch(input[0])
        {
            case 'a':
            		sscanf(&input[2], "%[^:]:%d:%d:%d", description, &price, &weight, &stock);
            		new_product_in_system(description, price, weight, stock);
            		break;

         	case 'q':
         			sscanf(&input[2],"%d:%d", &idp, &quantity);
         			add_stock_product(idp, quantity);
         			break;

         	case 'N':
         			new_order();
         			break;

         	case 'A':
         			sscanf(&input[2],"%d:%d:%d", &ide, &idp, &quantity);
         			add_product_to_order(ide, idp, quantity);
         			break;

         	case 'r':
					sscanf(&input[2],"%d:%d", &idp, &quantity);
         			remove_stock_product(idp, quantity);        			
         			break;

         	case 'R':
         			sscanf(&input[2],"%d:%d", &ide, &idp);
         			remove_product_from_order(ide, idp);
         			break;

 			case 'C':
 					sscanf(&input[2],"%d", &ide);
 					cost_of_order(ide);
 					break;

         	case 'p':
         			sscanf(&input[2],"%d:%d", &idp, &new_price);
         			change_product_price(idp, new_price);
         			break;

         	case 'E':
         			sscanf(&input[2],"%d:%d", &ide, &idp);
         			quantity_of_product_in_order(ide, idp);
         			break;

         	case 'm':
         			sscanf(&input[2],"%d", &idp);
         			order_w_more_qnt_product(idp);
         			break;

         	case 'l':
         			print_system_by_price();
         			break;

			case 'L':
					sscanf(&input[2],"%d", &ide);
					print_order_by_alpha(ide);
					break;

 			case 'x':return 0;
        }
    }
    return 0;
}


