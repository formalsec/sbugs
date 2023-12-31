#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIMIT 1000
#define MAX_PRODUCTS 10000
#define MAX_ORDERS 500
#define MAX_PROD_IN_ORDER 500
#define WORDS 10
#define Len 100
#define DESCRIPTION_LENGTH 63
#define MAXIMUM_ORDER_WEIGHT 200

/*Create a product structure */
typedef struct
{
	int id, price, weight, stock;
	char description[DESCRIPTION_LENGTH];
} Product;

/*Create an order structure */
typedef struct
{
	Product products[MAX_PROD_IN_ORDER];
	int productCounter, totalOrderWeight;
} Order;

/*Create an array of products*/
Product products[MAX_PRODUCTS];
/*Create an array of orders*/
Order orders[MAX_ORDERS];

/*Declare global variables*/
int productCounter = 0;
int orderCounter = 0;
int prodInPacksCounter = 0;

/*make an array to save the input tokens*/
char tokArray[WORDS][Len];

/* Function that separates the stdin words*/
void sepWords()
{
	int i;
	char *token;
	char str[MAX_LIMIT];
	fgets(str, MAX_LIMIT, stdin);
	/* Returns first token */
	token = strtok(str, " ");
	/* Keep printing tokens while one of the */
	/* delimiters present in str[]. */
	for (i = 0; token != NULL; i++)
	{
		strcpy(tokArray[i], token);
		token = strtok(NULL, ":");
	}
}

/*Function that adds products to an array */
void addProduct(char d[], int p, int w, int s)
{
	/* Validates all the given arguments */
	if (d == NULL || p <= 0 || w <= 0 || s <= 0)
	{
		printf("Argumentos nao sao validos\n");
	}

	/* Insert product's attributes on the products array */
	strcpy(products[productCounter].description, d);
	products[productCounter].price = p;
	products[productCounter].weight = w;
	products[productCounter].stock = s;
	/* The ID is automatically generated by order of insertion */
	products[productCounter].id = productCounter;
	printf("Novo produto %d.\n", productCounter);
	/* Increments the product counter (number of products) */
	productCounter++;
}

/*Function that adds stock from the product */
void addStock(int idp, int s)
{
	/* Verify if the product exists */
	if (idp >= productCounter)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	/* Add stock to the existing product */
	products[idp].stock += s;
}
/*Creates as Order*/
void createOrder()
{
	printf("Nova encomenda %d.\n", orderCounter);
	/*Increments the order counter (number of existing orders)*/
	orderCounter++;
}

/*Function that adds a product to an Order*/
void addToOrder(int idOrder, int idProduct, int quantity)
{
	int i;
	/* Validate order id */
	if (idOrder >= orderCounter)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idProduct, idOrder);
		return;
	}

	/* Validate product id */
	if (idProduct >= productCounter)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idProduct, idOrder);
		return;
	}

	/* Check if we have enough products in stock */
	if (products[idProduct].stock < quantity || products[idProduct].stock < 0)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idProduct, idOrder);
		return;
	}

	/* Check if the order does not exceed it's maximum weight capacity */
	if (orders[idOrder].totalOrderWeight + (products[idProduct].weight * quantity) > 200)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idProduct, idOrder);
		return;
	}

	/* If this is the first product */
	if (orders[idOrder].productCounter == 0)
	{
		/* Insert the order attributes on the orders array */
		strcpy(orders[idOrder].products[orders[idOrder].productCounter].description, products[idProduct].description);
		orders[idOrder].products[orders[idOrder].productCounter].price = products[idProduct].price;
		orders[idOrder].products[orders[idOrder].productCounter].weight = products[idProduct].weight;
		orders[idOrder].products[orders[idOrder].productCounter].stock = quantity;
		/* The ID is automatically generated by order of insertion */
		orders[idOrder].products[orders[idOrder].productCounter].id = products[idProduct].id;
		/* Increments the totalOrderWeight attribute of an order*/
		orders[idOrder].totalOrderWeight += products[idProduct].weight * quantity;
		/* Decrements the stock availible in the products array */
		products[idProduct].stock -= quantity;
		/* Increments the number of existing products inside the order */
		orders[idOrder].productCounter++;
		return;
	}

	/* Check all order products */
	for (i = 0; i < orders[idOrder].productCounter; i++)
	{
		/* If this product already exists in the order */
		if (orders[idOrder].products[i].id == idProduct)
		{
			/* Remove product quantity from stock */
			products[idProduct].stock -= quantity;
			/* Add product's quantity to order */
			orders[idOrder].products[i].stock += quantity;
			/* Calculate new weight */
			orders[idOrder].totalOrderWeight += products[idProduct].weight * quantity;
			return;
		}
	}

	/* If this product doesn't exist in the order, add it.
	   Insert the order attributes on the orders array */
	strcpy(orders[idOrder].products[orders[idOrder].productCounter].description, products[idProduct].description);
	orders[idOrder].products[orders[idOrder].productCounter].price = products[idProduct].price;
	orders[idOrder].products[orders[idOrder].productCounter].weight = products[idProduct].weight;
	orders[idOrder].products[orders[idOrder].productCounter].stock = quantity;
	/* The ID is automatically generated by order of insertion */
	orders[idOrder].products[orders[idOrder].productCounter].id = products[idProduct].id;
	/* Increments the totalOrderWeight attribute of an order*/
	orders[idOrder].totalOrderWeight += products[idProduct].weight * quantity;
	/* Decrements the stock availible in the products array */
	products[idProduct].stock -= quantity;
	/* Increments the number of existing products inside the order */
	orders[idOrder].productCounter++;
	return;
}

/*Function that removes stock from the product */
void rmStock(int idProduct, int s)
{
	/* Validate product id */
	if (idProduct >= productCounter)
	{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idProduct);
		return;
	}

	/* Check if we have enough products in stock */
	if (products[idProduct].stock - s < 0)
	{
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", s, idProduct);
		return;
	}
	/* Remove stock (s), from the product */
	products[idProduct].stock -= s;
}

/*Function that removes a product's stock from an order */
void rmProduct(int idOrder, int idProduct)
{
	int i;
	/* Validate order id */
	if (idOrder >= orderCounter)
	{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idProduct, idOrder);
		return;
	}
	/* Validate product id */
	if (idProduct >= productCounter)
	{
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idProduct, idOrder);
		return;
	}

	/* Find product in order */
	for (i = 0; i < orders[idOrder].productCounter && orders[idOrder].products[i].id != idProduct; i++)
		;
	/* If it exists the value of 'i' should be diferent and inferior to the product counter */
	if (i < orders[idOrder].productCounter)
	{
		/* Restock */
		products[idProduct].stock += orders[idOrder].products[i].stock;
		/* Update order's weight */
		orders[idOrder].totalOrderWeight -= products[idProduct].weight * orders[idOrder].products[i].stock;
		/* Set this order's product's quantity to 0 */
		orders[idOrder].products[i].stock = 0;
	}
}

/*Function that gives us the total cost of an order */
void orderCost(int idOrder)
{
	int i;
	int cost = 0;
	/* Validate order id */
	if (idOrder >= orderCounter)
	{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idOrder);
		return;
	}
	/* Check all the products inside an order */
	for (i = 0; i < orders[idOrder].productCounter; i++)
	{
		/* Add the cost of each individual product to the cost of the order */
		cost += (orders[idOrder].products[i].price * orders[idOrder].products[i].stock);
	}
	printf("Custo da encomenda %d %d.\n", idOrder, cost);
}

/*Function that changes the price of a product */
void changePrice(int idProduct, int newPrice)
{
	int i, n;
	/* Validate product id */
	if (idProduct >= productCounter)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idProduct);

	/* Change product's price */
	products[idProduct].price = newPrice;

	/* Check all the orders to find the one(s) that
	have the product we want, in order to change the price */
	for (i = 0; i < orderCounter; i++)
	{
		/* Check all the products inside an order
		 to find the one that matches */
		for (n = 0; n < orders[i].productCounter; n++)
		{
			/* If the id we're looking for exists */
			if (orders[i].products[n].id == idProduct)
			{
				/* Update order's product price*/
				orders[i].products[n].price = newPrice;
			}
		}
	}
}

/*Function that lists a product inside a specific order */
void listOrder(int idOrder, int idProduct)
{
	int i;
	/* Validate order id */
	if (idOrder >= orderCounter)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idOrder);
		return;
	}
	/* Validate product id */
	if (idProduct >= productCounter)
	{
		printf("Impossivel listar produto %d. Produto inexistente.\n", idProduct);
		return;
	}
	/* Check all the products inside an order
		to find the one that matches */
	for (i = 0; i < orders[idOrder].productCounter; i++)
	{
		/* If the id we're looking for exists */
		if (orders[idOrder].products[i].id == idProduct)
		{
			/* Show order's product */
			printf("%s %d.\n", orders[idOrder].products[i].description, orders[idOrder].products[i].stock);
			return;
		}
	}
	printf("%s %d.\n", products[idProduct].description, 0);
	return;
}

/*Function that gives us the most occurences of a product's stock */
void orderWithMoreProducts(int idProduct)
{
	int i, n;
	int orderWithMoreProducts = -1;
	int maxProducts = 0;

	/* Validates order id */
	if (idProduct >= productCounter)
	{
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idProduct);
		return;
	}

	/* Iterate all orders in reverse */
	for (i = orderCounter - 1; i >= 0; i--) /*It iterates in reverse to respect the rule:
											In case of equal occurence of a product the one
											with a lower id should be returned */
	{
		for (n = 0; n < orders[i].productCounter; n++)
		{
			/* If this order has the product we're looking for and the number of products is higher */
			if (orders[i].products[n].id == idProduct && orders[i].products[n].stock > 0 && orders[i].products[n].stock >= maxProducts)
			{ /* Update the maximum stock of the product as well as the index
				'orderWithMoreProducts' it occurs in */
				maxProducts = orders[i].products[n].stock;
				orderWithMoreProducts = i;
			}
		}
	}

	/* If we found at least one order with the product we were looking for */
	if (orderWithMoreProducts != -1)
	{
		printf("Maximo produto %d %d %d.\n", idProduct, orderWithMoreProducts, maxProducts);
	}
}

/* I have created two different merges for ordering price and alphabetically */
/* mergeSortPrice orders the products by price (ascending) */
void mergePrice(Product arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	Product L[MAX_PRODUCTS / 2], R[MAX_PRODUCTS / 2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
	{
		L[i].id = arr[l + i].id;
		L[i].price = arr[l + i].price;
		L[i].weight = arr[l + i].weight;
		L[i].stock = arr[l + i].stock;
		strcpy(L[i].description, arr[l + i].description);
	}
	for (j = 0; j < n2; j++)
	{
		R[j].id = arr[m + 1 + j].id;
		R[j].price = arr[m + 1 + j].price;
		R[j].weight = arr[m + 1 + j].weight;
		R[j].stock = arr[m + 1 + j].stock;
		strcpy(R[j].description, arr[m + 1 + j].description);
	}

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; /* Initial index of first subarray */
	j = 0; /* Initial index of second subarray */
	k = l; /* Initial index of merged subarray */
	while (i < n1 && j < n2)
	{
		if (L[i].price <= R[j].price)
		{
			arr[k].id = L[i].id;
			arr[k].price = L[i].price;
			arr[k].weight = L[i].weight;
			arr[k].stock = L[i].stock;
			strcpy(arr[k].description, L[i].description);
			i++;
		}
		else
		{
			arr[k].id = R[j].id;
			arr[k].price = R[j].price;
			arr[k].weight = R[j].weight;
			arr[k].stock = R[j].stock;
			strcpy(arr[k].description, R[j].description);
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1)
	{
		arr[k].id = L[i].id;
		arr[k].price = L[i].price;
		arr[k].weight = L[i].weight;
		arr[k].stock = L[i].stock;
		strcpy(arr[k].description, L[i].description);
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2)
	{
		arr[k].id = R[j].id;
		arr[k].price = R[j].price;
		arr[k].weight = R[j].weight;
		arr[k].stock = R[j].stock;
		strcpy(arr[k].description, R[j].description);
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the sub-array of arr to be sorted */
void mergeSortPrice(Product arr[], int l, int r)
{
	if (l < r)
	{
		/* Same as (l+r)/2, but avoids overflow for large l and h */
		int m = l + (r - l) / 2;

		/* Sort first and second halves */
		mergeSortPrice(arr, l, m);
		mergeSortPrice(arr, m + 1, r);

		mergePrice(arr, l, m, r);
	}
}

/* Prints products by price */
void listProductsByPrice()
{
	int i;

	Product productsSorted[MAX_PRODUCTS];
	memcpy(productsSorted, products, sizeof(Product) * productCounter);

	mergeSortPrice(productsSorted, 0, productCounter - 1);

	printf("Produtos\n");
	for (i = 0; i < productCounter; i++)
	{
		printf("* %s %d %d\n", productsSorted[i].description, productsSorted[i].price, productsSorted[i].stock);
	}
}
/* mergeSortDescription orders the products alphabetically (by description) */
void mergeDescription(Product arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	Product L[MAX_PRODUCTS / 2], R[MAX_PRODUCTS / 2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
	{
		L[i].id = arr[l + i].id;
		L[i].price = arr[l + i].price;
		L[i].weight = arr[l + i].weight;
		L[i].stock = arr[l + i].stock;
		strcpy(L[i].description, arr[l + i].description);
	}
	for (j = 0; j < n2; j++)
	{
		R[j].id = arr[m + 1 + j].id;
		R[j].price = arr[m + 1 + j].price;
		R[j].weight = arr[m + 1 + j].weight;
		R[j].stock = arr[m + 1 + j].stock;
		strcpy(R[j].description, arr[m + 1 + j].description);
	}

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; /* Initial index of first subarray */
	j = 0; /* Initial index of second subarray */
	k = l; /* Initial index of merged subarray */
	while (i < n1 && j < n2)
	{
		if (strcmp(L[i].description, R[j].description) < 0)
		{
			arr[k].id = L[i].id;
			arr[k].price = L[i].price;
			arr[k].weight = L[i].weight;
			arr[k].stock = L[i].stock;
			strcpy(arr[k].description, L[i].description);
			i++;
		}
		else
		{
			arr[k].id = R[j].id;
			arr[k].price = R[j].price;
			arr[k].weight = R[j].weight;
			arr[k].stock = R[j].stock;
			strcpy(arr[k].description, R[j].description);
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1)
	{
		arr[k].id = L[i].id;
		arr[k].price = L[i].price;
		arr[k].weight = L[i].weight;
		arr[k].stock = L[i].stock;
		strcpy(arr[k].description, L[i].description);
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2)
	{
		arr[k].id = R[j].id;
		arr[k].price = R[j].price;
		arr[k].weight = R[j].weight;
		arr[k].stock = R[j].stock;
		strcpy(arr[k].description, R[j].description);
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the sub-array of arr to be sorted */
void mergeSortDescription(Product arr[], int l, int r)
{
	if (l < r)
	{
		/* Same as (l+r)/2, but avoids overflow for large l and h */
		int m = l + (r - l) / 2;

		/* Sort first and second halves */
		mergeSortDescription(arr, l, m);
		mergeSortDescription(arr, m + 1, r);

		mergeDescription(arr, l, m, r);
	}
}

/* Prints this order's products alphabetically */
void listOrderProducts(int idOrder)
{
	int i;
	Product productsOrdered[MAX_PROD_IN_ORDER];

	if (idOrder >= orderCounter)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idOrder);
		return;
	}

	memcpy(productsOrdered, orders[idOrder].products, sizeof(Product) * orders[idOrder].productCounter);

	for (i = 0; i < orders[idOrder].productCounter; i++)
	{
		mergeSortDescription(productsOrdered, 0, orders[idOrder].productCounter - 1);
	}

	printf("Encomenda %d\n", idOrder);
	for (i = 0; i < orders[idOrder].productCounter; i++)
	{
		if (productsOrdered[i].stock != 0)
		{
			printf("* %s %d %d\n", productsOrdered[i].description, productsOrdered[i].price, productsOrdered[i].stock);
		}
	}
}

/* Switch Case function */
int main()
{
	/* Infinite loop */
	while (1)
	{
		char *x = can_fail_malloc(sizeof(char));
		/* Insert the user's input into a global variable to be used in every function */
		sepWords();
		strcpy(x, tokArray[0]);

		/* Switch Case */
		switch (*x)
		{
		case 'a':
			addProduct(tokArray[1], atoi(tokArray[2]), atoi(tokArray[3]), atoi(tokArray[4]));
			break;
		case 'q':
			addStock(atoi(tokArray[1]), atoi(tokArray[2]));
			break;
		case 'N':
			createOrder();
			break;
		case 'A':
			addToOrder(atoi(tokArray[1]), atoi(tokArray[2]), atoi(tokArray[3]));
			break;
		case 'r':
			rmStock(atoi(tokArray[1]), atoi(tokArray[2]));
			break;
		case 'R':
			rmProduct(atoi(tokArray[1]), atoi(tokArray[2]));
			break;
		case 'C':
			orderCost(atoi(tokArray[1]));
			break;
		case 'p':
			changePrice(atoi(tokArray[1]), atoi(tokArray[2]));
			break;
		case 'E':
			listOrder(atoi(tokArray[1]), atoi(tokArray[2]));
			break;
		case 'm':
			orderWithMoreProducts(atoi(tokArray[1]));
			break;
		case 'l':
			listProductsByPrice();
			break;
		case 'L':
			listOrderProducts(atoi(tokArray[1]));
			break;
		case 'x':
			exit(0);
		}
	}
	return 0;
}
