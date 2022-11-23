#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAXORDERWEIGHT 200    	
#define MAXPRODUCTS 10000		
#define MAXORDERS 500			
#define MAXDESCRIPTION 63		
#define IDANDQTY 2				
#define QTY 1					
#define ID 0					


typedef struct product
{
	int id, price, weight, stock;
	char desc[MAXDESCRIPTION];	
} Product;

typedef struct order
{
	int id, cost, weight, orderProdId;
	int orderProd[MAXORDERWEIGHT][IDANDQTY];
} Order;

Product products[MAXPRODUCTS]; 	/* Array to store products */
Order orders[MAXORDERS];		/* Array to store orders */

int productsId, ordersId; 		/* Counters to keep track of products[] and orders[] size */


/* MAIN FUNCTIONS */
void addProduct();	 			
void addStock(); 				
void removeStock(); 			
void newOrder(); 				
void addProductToOrder(); 		
void removeProductFromOrder(); 	
void orderCost(); 				
void changePrice(); 			
void listOrderDescQtd(); 		
void listMostOrderId();			
void listProductsByPrice();		
void listOrderByDesc();			

/* SECONDARY FUNCTIONS */
void init(); 														
void updateValuesAddProductToOrder(int, int, int, int, int);		
void quickSortByPrice(Product products[], int, int);				
int quickSortPartitionByPrice(Product products[], int, int);				
void quickSortByDesc(int prod[][IDANDQTY], int, int); 				
int quickSortPartitionByDesc(int prod[][IDANDQTY], int, int);	
void swapProd(Product prod[], int, int);							
void swapProdDesc(int prod[][IDANDQTY], int, int);					


int main(){

	int progRun = 1;
	char command;

	init();

	while(progRun){

		switch(command = getchar()){
			case 'a':
				getchar();
				addProduct();
				break;

			case 'q':
				addStock();
				break;

			case 'r':
				removeStock();
				break;

			case 'N':
				newOrder();
				break;

			case 'A':
				addProductToOrder();
				break;

			case 'R':
				removeProductFromOrder();
				break;

			case 'C':
				orderCost();
				break;

			case 'p':
				changePrice();
				break;

			case 'E':
				listOrderDescQtd();
				break;

			case 'm':
				listMostOrderId();
				break;	

			case 'l':
				listProductsByPrice();
				break;

			case 'L':
				listOrderByDesc();
				break;

			case 'x': 
				progRun = 0;
				break;
		} getchar();
	}

	return 0;

}

/* MAIN FUNCTIONS */

/* Adds new product to products[] */
void addProduct(){
	scanf("%[^:]:%d:%d:%d", products[productsId].desc, &products[productsId].price, &products[productsId].weight, &products[productsId].stock);
	products[productsId].id = productsId;
	printf("Novo produto %d.\n", productsId);
	productsId++;
}


/* Adds stock to a product in products[] */
void addStock(){
	int idp, stock;
	scanf("%d:%d", &idp, &stock);
	
	if(products[idp].id != -1)
		products[idp].stock += stock;	
	else 
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}


/* Removes stock from a product in products[] */
void removeStock(){
	int idp, stock;
	scanf("%d:%d", &idp, &stock);
	
	if(products[idp].id != -1){
		if((products[idp].stock - stock) >= 0){
			products[idp].stock -= stock;
		}else 
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock, idp);
	}else 
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
}


/* Adds new order to orders[] */
void newOrder(){
	orders[ordersId].id = ordersId;
	printf("Nova encomenda %d.\n", ordersId);
	ordersId++;
}


/* Adds a product to an order in orders[].orderProd[] and quantity to orders[].orderProdQtd[] */
void addProductToOrder(){
	int ide, idp, qty, i;
	scanf("%d:%d:%d", &ide, &idp, &qty);

	/*
		Checks if Product <idp> can be added to Order <ide>
	*/
	if(orders[ide].id != -1){
		if(products[idp].id != -1){
			if((products[idp].stock - qty) >= 0){
				if((orders[ide].weight + (qty * products[idp].weight)) <= MAXORDERWEIGHT){

					/*
						Adds product <idp> to Order <ide>
						Updates Order's <ide> weight and cost
					*/
					for(i = 0; i < orders[ide].orderProdId; i++){
						if(orders[ide].orderProd[i][ID] == idp){
							updateValuesAddProductToOrder(ide, idp, i, qty, 1);
							return;
						}
					}

					/*
						Verifies if orderProd[] in Order is full (200)
					  	Looks up an empty Product in the Order to replace it
					*/
					if(orders[ide].orderProdId == MAXORDERWEIGHT){
						for(i = 0; i < orders[ide].orderProdId; i++){
							if(orders[ide].orderProd[i][QTY] == 0){
								updateValuesAddProductToOrder(ide, idp, i, qty, 0);
								return;
							}
						}
					} else {
						updateValuesAddProductToOrder(ide, idp, orders[ide].orderProdId, qty, 0);
						orders[ide].orderProdId++;
					}
										
				} else
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
			} else
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);			
		} else
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	} else 
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}


/* Removes product from an order in orders[].orderProd[] */
void removeProductFromOrder(){
	int ide, idp, i;
	scanf("%d:%d", &ide, &idp);

	if(orders[ide].id != -1){
		if(products[idp].id != -1){			
			for(i = 0; i < orders[ide].orderProdId; i++){
				if(orders[ide].orderProd[i][ID] == idp){
					orders[ide].cost -= (orders[ide].orderProd[i][QTY] * products[orders[ide].orderProd[i][ID]].price);			
					orders[ide].weight -= (orders[ide].orderProd[i][QTY] * products[orders[ide].orderProd[i][ID]].weight);
					products[idp].stock += orders[ide].orderProd[i][QTY];
					orders[ide].orderProd[i][QTY] = 0;					
				}
			}			
		} else
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	} else 
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}


/* Returns total cost of an order */
void orderCost(){
	int ide;
	scanf("%d", &ide);

	if(orders[ide].id != -1){
		printf("Custo da encomenda %d %d.\n", ide, orders[ide].cost);
	} else
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
}


/* Updates a product's price in products[] */
void changePrice(){
	int idp, price, i, j, prevPrice = 0;
	scanf("%d:%d", &idp, &price);

	if(products[idp].id != -1){
		prevPrice = products[idp].price;
		products[idp].price = price;

		for(i = 0; i < ordersId; i++){
			for(j = 0; j < orders[i].orderProdId; j++){
				
				if(orders[i].orderProd[j][ID] == idp){
					orders[i].cost += ((price - prevPrice) * orders[i].orderProd[j][QTY]);
					break;
				}
			}
		}
	} else
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}


/* Lists description and quantity of a product in an order in orders[] */
void listOrderDescQtd(){
	int ide, idp, i;
	scanf("%d:%d", &ide, &idp);

	if(orders[ide].id != -1){
		if(products[idp].id != -1){			
			
			for(i = 0; i < orders[ide].orderProdId; i++){
				if(orders[ide].orderProd[i][ID] == idp){
					printf("%s %d.\n", products[orders[ide].orderProd[i][ID]].desc, orders[ide].orderProd[i][QTY]);
					return;				
				}
			}	
					printf("%s 0.\n", products[idp].desc);		
						
		} else
			printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	} else 
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}


/* Lists order id in orders[] where a specific product appears the most */
void listMostOrderId(){
	int idp, i, j, maxId = 0, maxProdId = 0, tempQty = 0;
	scanf("%d", &idp);

	if(products[idp].id != -1){

		if(ordersId == 0) return;

		for(i = 0; i < ordersId; i++){
			for(j = 0; j < orders[i].orderProdId; j++){
				if(orders[i].orderProd[j][ID] == idp && tempQty < orders[i].orderProd[j][QTY]){
					tempQty = orders[i].orderProd[j][QTY];
					maxId = i;
					maxProdId = j;
					break;
				}
			}
		}

		if(tempQty > 0)
			printf("Maximo produto %d %d %d.\n", idp, maxId, orders[maxId].orderProd[maxProdId][QTY]);

	} else
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
}


/* Lists all products by price in ascending order */
void listProductsByPrice(){
	
	int i;
	Product tempProducts[MAXPRODUCTS];

	for(i = 0; i < productsId; i++){
		tempProducts[i] = products[i];
	}

	quickSortByPrice(tempProducts, 0, productsId-1);

	printf("Produtos\n");
	for(i = 0; i < productsId; i++){
		printf("* %s %d %d\n", tempProducts[i].desc, tempProducts[i].price, tempProducts[i].stock);
	}
}


/* Lists all products in an order alphabetically */
void listOrderByDesc(){
	
	int i, ide;
	int tempOrderProd[MAXORDERWEIGHT][IDANDQTY];

	scanf("%d", &ide);

	if(orders[ide].id != -1){
		for(i = 0; i < orders[ide].orderProdId; i++){
			tempOrderProd[i][ID] = orders[ide].orderProd[i][ID];
			tempOrderProd[i][QTY] = orders[ide].orderProd[i][QTY];
		}

		quickSortByDesc(tempOrderProd, 0, orders[ide].orderProdId - 1);
	

		printf("Encomenda %d\n", ide);
		for(i = 0; i < orders[ide].orderProdId; i++){
			if(tempOrderProd[i][QTY] != 0)
				printf("* %s %d %d\n", products[tempOrderProd[i][ID]].desc, products[tempOrderProd[i][ID]].price, tempOrderProd[i][QTY]);
		}

	}else 
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}

/* SECONDARY FUNCTIONS */


/* Initializes products[] and orders[] id to -1 */
void init(){
	int i;

	for(i = 0; i < MAXPRODUCTS; i++){
		products[i].id = -1;
	}

	for(i = 0; i < MAXORDERS; i++){
		orders[i].id = -1;
	}
}


/* Updates Order's weight/cost, Product's stock and an order product's values */
void updateValuesAddProductToOrder(int tempIde, int tempIdp, int prodIndex, int tempQtd, int exists){
	if(!exists)
		orders[tempIde].orderProd[prodIndex][ID] = products[tempIdp].id;

	orders[tempIde].orderProd[prodIndex][QTY] += tempQtd;
	products[tempIdp].stock -= tempQtd;
	orders[tempIde].weight += tempQtd * products[tempIdp].weight;
	orders[tempIde].cost += tempQtd * products[tempIdp].price;
}


/* QuickSort used for listProductsByPrice() function */
void quickSortByPrice(Product prod[], int l, int h){
	int i;

	if(h <= l)
		return;

	i = quickSortPartitionByPrice(prod, l, h);

	quickSortByPrice(prod, l, i-1);
	quickSortByPrice(prod, i+1, h);
}

int quickSortPartitionByPrice(Product prod[], int l, int h){
	int i, j;

	i = l - 1;
	j = h;
	
	
	while(i < j){
		while(prod[++i].price < prod[h].price || ((prod[i].price == prod[h].price) && (prod[i].id < prod[h].id)));
		while(prod[--j].price > prod[h].price || ((prod[j].price == prod[h].price) && (prod[j].id > prod[h].id))){
			if(j == l)
				break;
		}
		if(i < j){
			swapProd(prod, i, j);		
		}
	}

	swapProd(prod, i, h);

	return i;
}


/* QuickSort used for listOrderByDesc() function */
void quickSortByDesc(int prod[][IDANDQTY], int l, int h){
	int i;

	if(h <= l)
		return;

	i = quickSortPartitionByDesc(prod, l, h);

	quickSortByDesc(prod, l, i-1);
	quickSortByDesc(prod, i+1, h);
}

int quickSortPartitionByDesc(int prod[][IDANDQTY], int l, int h){
	int i, j;

	i = l - 1;
	j = h;	
	
	while(i < j){
		while(strcmp(products[prod[++i][ID]].desc, products[prod[h][ID]].desc) < 0);
		while(strcmp(products[prod[--j][ID]].desc, products[prod[h][ID]].desc) > 0){
			if(j == l)
				break;
		}
		if(i < j){
			swapProdDesc(prod, i, j);	
		}
	}

	swapProdDesc(prod, i, h);

	return i;
}


/* Swaps products for sort by price function */
void swapProd(Product prod[], int i, int j){
	
	Product temp;

	temp = prod[i];
	prod[i] = prod[j];
	prod[j] = temp;
}


/* Swaps products for sort by description function*/
void swapProdDesc(int prod[][IDANDQTY], int i, int j){
	
	int temp;

	temp = prod[i][ID];
	prod[i][ID] = prod[j][ID];
	prod[j][ID] = temp;

	temp = prod[i][QTY];
	prod[i][QTY] = prod[j][QTY];
	prod[j][QTY] = temp;
}
