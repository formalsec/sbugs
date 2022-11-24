#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include "messages.h"

#define MAX_PRODUCTS 10000 /* Maximum products that can be cratead */
#define MAX_PACKAGE_WEIGTH 200 /* Maximum total weigth per package*/

/* Struct that represents the products. Contains: 
 * 	Id: Products identifier,
 * 	Description: Products description,
 * 	price: Products price,
 * 	weight: Products weight,
 * 	stock: Products avaliable stock.
 */
typedef struct product{
	int id;
	char description[63];
	int price;
	int weight;
	int stock;
} Product;

/* Struct that represents the packages. Contains: 
 * 	Id: Packages identifier,
 * 	Products: A list of the productos that the package contains,
 * 	totalPackageProducts: Total ammount of products in the package,
 * 	totalweight: total weight of the package.
 */
typedef struct package{
	int id;
	Product products[MAX_PACKAGE_WEIGTH];
	int totalPackageProducts;
	int totalWeight;
} Package;

/* Struct that represents the packages. Contains: 
 * 	label: Command identifier,
 * 	Description: Used for the descrition argument when avaliable,
 * 	Args: other integer arguments,
 * 	
 * 	usage: Auxiliary struct for better handling the commands processing. 
 */
typedef struct command{
	char label;
	char description[63];
	int args[3];

} Command;

Product products[MAX_PRODUCTS]; /* Existing products in the program */
Package packages[500]; /* Existing packages in the program */
int productsQuantity = 0; /* Total of products */
int packagesQuantity = 0; /* Total of packages */

/**
 * Auxiliary function the check if exists a product with the requested id
 */
int isProductValid(int id){
	return id < productsQuantity;
}

/**
 * Auxiliary function the check if exists a package with the requested id
 */
int isPackageValid(int id){
	return id < packagesQuantity;
}

/**
 * Function that creates a new product and adds it to the products lits
 * Requiers a command to define the inicital price, weigth and stock.
 */
void createProduct(Command command){
	Product product;
	product.id = productsQuantity;
	productsQuantity++;
	strcpy(product.description, command.description);
	product.price = command.args[0];
	product.weight = command.args[1];
	product.stock = command.args[2];
	products[product.id] = product;
	printf(NEW_PRODUCT_MESSAGE, product.id);
}

/**
 * Restocks the requested product by id.
 */
void restock(int pId, int stock){
	if(isProductValid(pId) == 0){
		printf(INVALID_RESTOCK_PRODUCT, pId);
		return;
	}	
	products[pId].stock += stock;
}

/**
 * Removes the desired ammount of stock to the requested product by id.
 */
void removeStock(int pId, int stockToRemove){
	if(isProductValid(pId) == 0){
		printf(INVALID_REMOVE_STOCK_PRODUCT, pId);
		return;
	} else if(products[pId].stock < stockToRemove){
		printf(INVALID_REMOVE_STOCK_AMOUNT, stockToRemove ,pId);
		return;
	}

	products[pId].stock -= stockToRemove;
}

/**
 * Function that creates a new package and adds it to the package lits
 */
void createPackage(){
	Package package;
	package.id = packagesQuantity;
	package.totalPackageProducts = 0;
	package.totalWeight = 0;
	packagesQuantity++;
	packages[package.id] = package;
	printf(NEW_PACKAGE_MESSAGE, package.id);
}

/**
 * Auxiliary function the check if the requested package contains the package in question. 
 * Both requiered by id.
 */
int packageContainsProduct(int pkId, int ptId){
	int i;
	for(i = 0; i < packages[pkId].totalPackageProducts; i++){
		if(packages[pkId].products[i].id == ptId){
			return i;
		}
	}
	return -1;
}

/**
 * Adds the requested product with a certain ammount to the asked package. 
 * Bouth requested by id.
 */
void addProduct(int pkId, int ptId, int quantity){
	Product product;
	int index;
	if(isPackageValid(pkId) == 0){
		printf(INVALID_ADD_PRODUCT_PACKAGE, ptId, pkId);
		return;
	} else if(isProductValid(ptId) == 0){
		printf(INVALID_ADD_PRODUCT_PRODUCT, ptId, pkId);
		return;
	} else if(products[ptId].stock < quantity){
		printf(INVALID_ADD_PRODUCT_STOCK, ptId, pkId);
		return;
	} else if((products[ptId].weight * quantity + packages[pkId].totalWeight) > MAX_PACKAGE_WEIGTH){
		printf(INVALID_ADD_PRODUCT_OVERWEIGHT, ptId, pkId);
		return;
	}
	index = packageContainsProduct(pkId, ptId); 

	/*
	 *	If the package have the product it will simpley add the stock otherwise adds the product.
	 */
	if(index == -1){
		product = products[ptId];
		product.stock = quantity;
		packages[pkId].products[packages[pkId].totalPackageProducts] = product;
		packages[pkId].totalPackageProducts++;
	} else {
		packages[pkId].products[index].stock += quantity;
	}
	packages[pkId].totalWeight += products[ptId].weight * quantity;
	products[ptId].stock -= quantity;
}

/**
 * Auxiliary fuction that removes a product from the products array in the packages. Bouth requested by id.
 */
void removeFromProductsArray(int pkId, int index){
	int i;
	for(i = index; i < packages[pkId].totalPackageProducts - 1; i++){
		packages[pkId].products[i] = packages[pkId].products[i + 1];
	}
	packages[pkId].totalPackageProducts--;	
}

/**
 * Removes a product from the packages. Bouth requested by id.
 */
void removeProduct(int pkId, int ptId){
	int i;
	if(isPackageValid(pkId) == 0){
		printf(INVALID_REMOVE_PRODUCT_PACKAGE, ptId, pkId);
		return;
	} else if(isProductValid(ptId) == 0){
		printf(INVALID_REMOVE_PRODUCT_PRODUCT, ptId, pkId);
		return;
	}

	i = packageContainsProduct(pkId, ptId);

	if(i == -1){
		return;
	}

	products[ptId].stock += packages[pkId].products[i].stock;
	packages[pkId].totalWeight -= products[ptId].weight * packages[pkId].products[i].stock;
	removeFromProductsArray(pkId, i);
}

/**
 * Calculate the price of the package requested by Id.
 */
void packagePrice(int pkId){
	int i, price = 0;
	if(isPackageValid(pkId) == 0){
		printf(INVALID_PACKAGE_PRICE_PACKAGE, pkId);
		return;
	}

	for(i = 0; i < packages[pkId].totalPackageProducts; i++){
		price += packages[pkId].products[i].price * packages[pkId].products[i].stock; 
	}

	printf(PACKAGE_PRICE, pkId, price);
}

/**
 * Changes the requested product by id price globally.
 */
void setProductPrice(int ptId, int price){
	int i, j;
	if(isProductValid(ptId) == 0){
		printf(INVALID_SET_PRODUCT_PRICE_PRODUCT, ptId);
	}
	products[ptId].price = price;
	for(i = 0; i < packagesQuantity; i++){
		j = packageContainsProduct(i, ptId);
		if(j != -1){
			packages[i].products[j].price = price;
		}
	}
}
/**
 * Prints the informage of the product in the package.
 * If the package doesn't have product it will print the stock "0" other the stock that is in the package.
 * Both requested by id.
 */
void productInfo(int pkId, int ptId){
	int i;
	if(isPackageValid(pkId) == 0){
		printf(INVALID_PRODUCT_INFO_PACKAGE, pkId);
		return;
	} else if(isProductValid(ptId) == 0){
		printf(INVALID_PRODUCT_INFO_PRODUCT, ptId);
		return;
	}

	i = packageContainsProduct(pkId, ptId);

	if(i == -1){
		printf(PRODUCT_INFO, products[ptId].description, 0);
	} else {
		printf(PRODUCT_INFO, packages[pkId].products[i].description, packages[pkId].products[i].stock);
	}
}

/**
 * Prints the package that contains the biggest ammount of the product requested by id.
 * 
 */
void mostValuablePackage(int ptId){
	int i, j, mvpk = -1, currentStock = 0;
	if(isProductValid(ptId) == 0){
		printf(INVALID_MOST_VALUABLE_PACKAGE_PRODUCT, ptId);
	}

	for(i = 0; i < packagesQuantity; i++){
		j = packageContainsProduct(i, ptId);
		if(j != -1 && packages[i].products[j].stock > currentStock){
			currentStock = packages[i].products[j].stock;
			mvpk = i;
		}
	}
	if(mvpk != -1){
		printf(MVP, ptId, mvpk, currentStock);
	}
}

/**
 * Auxiliary function to compare two products by description alphabetically.
 */
char compareByDesc(Product a, Product b){
	return strcmp(a.description, b.description) < 0;
}

/**
 * Auxiliary function to compare two products by price and if equal by id.
 */
char compareByPrice(Product a, Product b){
	if(a.price == b.price){
		return a.id < b.id;
	} else {
		return a.price < b.price;
	}
}

/**
 * Auxiliary function to compare two products by id.
 */
char compareById(Product a, Product b){
	return a.id < b.id;
}

/**
 * Auxiliary function for the merge sort. 
 */
void merge(Product a[], int left, int m, int right, char(*compareFunction)(Product, Product)){
	int i, j, k;
	Product aux[MAX_PRODUCTS];
	for (i = m+1; i > left; i--){
		aux[i-1] = a[i-1];
	}
	
	for (j = m; j < right; j++){
		aux[right+m-j] = a[j+1];
	}
	
	for (k = left; k <= right; k++){
		if ((*compareFunction)(aux[j], aux[i])){
			a[k] = aux[j--];
		} else {
			a[k] = aux[i++];
		}
	}
}

/**
 * Organization function using the merge sort algorithm that sort the products array starting and ending at 
 * any position with the criteria of the compareFunction.
 */
void mergeSort(Product a[], int left, int right, char(*compareFuction)(Product, Product)){
	int m = (right + left)/2;

	if(right <= left){
		return;
	}

	mergeSort(a, left, m, compareFuction);
	mergeSort(a, m+1, right, compareFuction);
	merge(a, left, m, right, compareFuction);
}

/**
 * Prints the products of the packages requested by description.
 */
void listProductsByDescription(int pkId){
	int i = 0;
	if(isPackageValid(pkId) == 0){
		printf(INVALID_LIST_PRODUCTS_BY_DESC, pkId);
		return;
	}

	mergeSort(packages[pkId].products, 0, packages[pkId].totalPackageProducts - 1, &compareByDesc);
	printf(LIST_PRODUCTS_BY_DESC_HEADER, pkId);
	for(i = 0; i < packages[pkId].totalPackageProducts; i++){
		printf(LIST_PRODUCTS_PRODUCT, packages[pkId].products[i].description, packages[pkId].products[i].price, packages[pkId].products[i].stock);
	}
	mergeSort(packages[pkId].products, 0, packages[pkId].totalPackageProducts - 1, &compareById);
}

/**
 * Prints all the products by price.
 */
void listProductsByPrice(){
	int i = 0;
	
	mergeSort(products, 0, productsQuantity - 1, &compareByPrice);
	printf(LIST_PRODUCTS_BY_PRICE_HEADER);
	for(i = 0; i < productsQuantity; i++){
		printf(LIST_PRODUCTS_PRODUCT, products[i].description, products[i].price, products[i].stock);
	}
	mergeSort(products, 0, productsQuantity - 1, &compareById);
}

/**
 * Auxiliary function to read and excute the command from the used.
 */
Command readCommand(){
	Command command;
	scanf("%c",&command.label);
	switch(command.label){
		case 'a':
			scanf(" %[^:]:%d:%d:%d",command.description, &command.args[0], &command.args[1], &command.args[2]);
			createProduct(command);
			break;
		case 'q':
			scanf(" %d:%d", &command.args[0], &command.args[1]);
			restock(command.args[0], command.args[1]);
			break;
		case 'N':
			createPackage();
			break;
		case 'A':
			scanf(" %d:%d:%d", &command.args[0], &command.args[1], &command.args[2]);
			addProduct(command.args[0], command.args[1], command.args[2]);
			break;
		case 'r':
			scanf(" %d:%d", &command.args[0], &command.args[1]);
			removeStock(command.args[0], command.args[1]);
			break;
		case 'R':
			scanf(" %d:%d", &command.args[0], &command.args[1]);
			removeProduct(command.args[0], command.args[1]);
			break;
		case 'C':
			scanf(" %d", &command.args[0]);
			packagePrice(command.args[0]);
			break;
		case 'p':
			scanf( "%d:%d", &command.args[0], &command.args[1]);
			setProductPrice(command.args[0], command.args[1]);
			break;
		case 'E':
			scanf(" %d:%d", &command.args[0], &command.args[1]);
			productInfo(command.args[0], command.args[1]);
			break;
		case 'm':
			scanf(" %d", &command.args[0]);
			mostValuablePackage(command.args[0]);
			break;
		case 'l':
			listProductsByPrice();
			break;
		case 'L':
			scanf(" %d", &command.args[0]);
			listProductsByDescription(command.args[0]);
			break;
	}
	return command;
}

int main(){
	Command command;
	do{
		command = readCommand();
	} while(command.label != 'x');
	return 0;
}
