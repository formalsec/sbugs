#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define products 10000
#define orders 500

int i, j, prod_in_order[products][orders];
char command; 
char descrition[products];
int price[products];
int weight[products];
int stock[products];
int idp, ide, quantity;
int price2;
int order[orders];
int new_prod();
int add_stock();
int new_order();
int add_prod();
int rem_stock();
int rem_prod();
int order_cost();
int change_price();
int list_prod();
int list_max_prod();
int list_by_price();
int list_by_descrition();

int main(){
	char input[200];
	char command;
	
	do{ 										
		scanf("%s",input);						/* read the input */
		command = input[0];						/* read the first character (command) */
		switch(command){						/* execute functions according to the command */
			case 'a':
				if (i < products){				/*it can only exist 10000 products */
				new_prod();
				}	
				i ++;							/*increment product counter */
				break;
			case 'q':
				add_stock();
				break;
			case 'N':
				if (j < orders){				/*it can only exist 500 orders */
				new_order();
				}
				j ++;							/*increment order counter */
				break;
			case 'A':
				add_prod();
				break;
			case 'r':
				rem_stock();
				break;
			case 'R':
				rem_prod();
				break;
			case 'C':
				order_cost();
				break;	
			case 'p':
				change_price();
				break;
			case 'E':
				list_prod();
				break;
			case 'm':
				list_max_prod();
				break;
			case 'l':
				list_by_price();
				break;
			case 'L':
				list_by_descrition();
				break;
			case 'x':							/*terminate program when command is 'x' */
				return 0;
		}
	} while (strcmp(&command, "x") != 0);		/*ask for new input while command isn?t 'x' */  
	return 0;
}
 
int new_prod(){
	scanf("%c %[^:]:%d:%d:%d", &command, &descrition[i], &price[i], &weight[i], &stock[i]);   /*save values in array */
	printf("Novo produto %d.\n", i);
	return 0;
}

int add_stock(){
	scanf("%c %d:%d", &command, &idp, &quantity);
	if (idp <= i - 1){							/*verify that the product exists */
		stock[idp] = stock[idp] + quantity;
	}
	else
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	return 0;
}

int new_order(){
	printf("Nova encomenda %d.\n", j);
	scanf("Nova encomenda %d", &order[j]);		/*save value in array */
	return 0;
}

int add_prod(){
	scanf("%c %d:%d:%d", &command, &ide, &idp, &quantity);
	if (ide <= j - 1){														/*verify that the order exists */
		if (idp <= i - 1){													/*verify that the product exists */
			if (quantity < stock[idp]){										/*verify that there is enough quantity in stock */ 
				if (quantity * weight[idp] < 200){							/*verify that it doesn't exceed the maximum weight per order */
					prod_in_order[i][j] = prod_in_order[idp][ide];			
				}
				else
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
			}
			else
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		}
		else
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	return 0;
}

int rem_stock(){
	scanf("%c %d:%d", &command, &idp, &quantity);
	if (idp <= i - 1){												/*verify that the product exists */
		if (stock[idp] - quantity < 0){								/*verify there is more in stock than the quantity you want to remove */
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantity, idp);
		}
		else
			stock[idp] = stock[idp] - quantity;
	}
	else
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	return 0;
}

int rem_prod(){
	scanf("%c %d:%d", &command, &ide, &idp);
	if (ide <= j - 1){												/*verify that the order exists */
		if (idp <= i - 1){											/*verify that the product exists */
			price[idp] = weight[idp] = stock[idp] = 0;				/*remove product from order */
		}
		else
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	return 0;
}

int order_cost(){
	scanf("%c %d", &command, &ide);
	if (ide > j - 1)												/*verify that the order exists */
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	return 0;
}

int change_price(){
	scanf("%c %d:%d", &command, &idp, &price2);
	if (idp <= i - 1)												/*verify that the product exists */
		price[idp] = price2;
	else
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	return 0;
}

int list_prod(){
	scanf("%c %d:%d", &command, &ide, &idp);
	if (ide > j - 1)												/*verify that the order exists */
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	if (idp > i - 1)												/*verify that the product exists */
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	return 0;
}

int list_max_prod(){
	scanf("%c %d", &command, &idp);
	if (idp > i - 1)												/*verify that the product exists */
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	return 0;
}

int list_by_price(){
	return 0;
}

int list_by_descrition(){
	scanf("%c %d", &command, &ide);
	if (ide > j - 1)												/*verify that the order exists */
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	return 0;
}
