#include <stdio.h>

#define MAX_PRODUCTS 10000 /* The maximum number of products stored. */
#define MAX_DESC 64	/* The maximum number of characters stored. */
#define MAX_ORDER 500 /*The maximum number of orders*/
#define MAX_WEIGHT 200 /*The maximum weight of an order*/
#define TRUE 1
#define FALSE 0

/****************************************************************************/
typedef struct {
	char description[MAX_DESC];	
	unsigned int price;
	unsigned int weight;
	unsigned int ordernumber;	/*Number of timer orded*/
	int stock;					
	int ordersList[MAX_ORDER];	/*orderes that have the product*/
} product;

/*Adds or removes a value to the selected product*/
int StockOperation (product v[], int id, int qtd) {
	int aux;
	aux = v[id].stock + qtd;
	return aux;
}
/****************************************************************************/
typedef struct {
	unsigned int NumberOfProducts;
	int list[MAX_PRODUCTS];
	int idpQty[MAX_PRODUCTS];
} order;

/****************************************************************************/

/*Global Variables*/
unsigned int numberProducts;    /*Number of products stored*/
unsigned int numberOrders;     /*Number of open orders*/
order ido[MAX_ORDER];		   	/*Array of Orders*/
product idp[MAX_PRODUCTS];	   /*Array of Products*/
enum option { WEIGHT, PRICE, ALPHABETICAL}; 
int x [MAX_PRODUCTS];		/*aux to the funcion MergeSort*/

/****************************************************************************/
void merge(int a[], int start , int end, int option){
    int mid = (start + end)/2;
    
    int i = start;
    int j = mid+1;
    int k = start;
    
    int aux[MAX_PRODUCTS];

	if (option == ALPHABETICAL){		/*flag to choose the sort type*/
		
		int c = 0;
		while(i <= mid && j <= end){
			if(idp[a[i]].description[c] < idp[a[j]].description[c]){
				aux[k++] = a[i++];
				c = 0;
			}
			else if (idp[a[i]].description[c] > idp[a[j]].description[c]){
				aux[k++] = a[j++];
				c = 0;
			}
			else {
				c++;
			}

		}
	}

	else if (option == PRICE){			/*flag to choose the sort type*/
		while(i <= mid && j <= end){
			if(idp[a[i]].price < idp[a[j]].price){
				aux[k++] = a[i++];
			}
			else if (idp[a[i]].price > idp[a[j]].price){
				aux[k++] = a[j++];
			}
			else {
				if (a[i] < a[j]){
					aux[k++] = a[i++];
				}
				else{
					aux[k++] = a[j++];
				}
			}
		}
	}
    while(i <= mid){
        aux[k++] = a[i++];
    }
    while(j <= end){
        aux[k++]  = a[j++];
    }
    for(i = start; i <= end; i++){
        a[i] = aux [i];
    } 
}



void mergeSort(int a[], int start, int end, int option){
	int mid = (start + end)/2;
	
    if(start < end){
		
    

    mergeSort(a, start, mid, option);
	
    mergeSort(a, mid+1, end, option);
    
    merge(a, start, end, option);
	}
}
/* Confirms if an ID is valid */
int NotValidID (unsigned short id, unsigned short MaxIdUsed) {
	int result = FALSE;
	if (id >= MaxIdUsed){
		result = TRUE;
	}
	return result;
}
/* Confirms if a product is in an order */
int PorductInOrder (unsigned short idorder, unsigned short idproduct){
	unsigned short result = FALSE, i;
	for(i = 0; i < ido[idorder].NumberOfProducts; i++){
		if (ido[idorder].list[i] == idproduct){
			result = TRUE;
		}
	}
	return result;
}
/*Adds a new product to the database*/
void CreatNewProduct (product idp[]) {
	if ( numberProducts < MAX_PRODUCTS ) {
		scanf(" %64[^:]:%u:%u:%d", idp[numberProducts].description, &idp[numberProducts].price, &idp[numberProducts].weight, &idp[numberProducts].stock);
		printf("Novo produto %u.\n", numberProducts);
		x[numberProducts] = numberProducts;
		numberProducts++;
	}
}
/**/
int QtyAlreadyOrded(int idproduct) {
	unsigned int i;
	int Qty = 0;
	for (i=0 ; i < idp[idproduct].ordernumber ; i++) {
		Qty += ido[idp[idproduct].ordersList[i]].idpQty[idproduct];			/*Vai somar a quantidade encomnedada por encomenda*/
	}
	return Qty;
}
/*the output is the sum of all the quantities ordered for the input value */
void RemoveStock (product idp[]) {
	unsigned int id = 0;
	int qtd = 0;
	scanf("%u:%d", &id, &qtd);
	if (NotValidID(id, numberProducts)) {
		printf("Impossivel remover stock do produto %u. Produto inexistente.\n", id);
	}
	else if ((StockOperation(idp, id , -qtd)- QtyAlreadyOrded(id)) < 0){
		printf("Impossivel remover %d unidades do produto %u do stock. Quantidade insuficiente.\n", qtd, id);
	}
	else {
		idp[id].stock = StockOperation(idp, id, -qtd);
	}
}
/*Confirms if it is a valid ID and adds stock to it*/
void AddStock (product idp[]) {
	unsigned int id = 0;
	int qtd = 0;
	scanf("%u:%d", &id, &qtd);
	
	if (NotValidID(id, numberProducts)) {
		
		printf("Impossivel adicionar produto %u ao stock. Produto inexistente.\n", id);
	}
	else {
		idp[id].stock = StockOperation(idp, id, qtd);
	}
}
/*Confirms if it is possible to creat a new Order and adds one to the order counter*/
void CreatNewOrder() {
	if ( numberOrders < MAX_ORDER) {
		printf("Nova encomenda %u.\n", numberOrders);
		numberOrders++;
	}
}
/*Receives an order ID and returns its weight or Price*/
int WPCalculation (int idorder, int option) {
	unsigned int i, result = 0;
	if (option == WEIGHT){					/*flag to choose the calculation type*/
		for( i=0 ; i < ido[idorder].NumberOfProducts; i++) {
			result += ido[idorder].idpQty[ido[idorder].list[i]] * idp[ido[idorder].list[i]].weight;
		}
	}
	else if (option == PRICE){				/*flag to choose the calculation type*/
		for( i=0 ; i < ido[idorder].NumberOfProducts; i++) {
			result += ido[idorder].idpQty[ido[idorder].list[i]] * idp[ido[idorder].list[i]].price;
		}
	}
	return result;
}
/*Remove a product from an order*/
void RemoveProduct () {
	unsigned int i, remove = FALSE;
	int idorder, idproduct;
	scanf("%d:%d",&idorder, &idproduct);
	if (NotValidID(idorder, numberOrders)){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idproduct, idorder);
	}
	else if (NotValidID(idproduct, numberProducts)){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idproduct, idorder);
	}
	else if (PorductInOrder (idorder, idproduct)){
		for (i = 0; i <ido[idorder].NumberOfProducts; i++) {
			if (idproduct == ido[idorder].list[i]){
				ido[idorder].idpQty[ido[idorder].list[i]] = 0; 	 /*Switch the quantity of that idp in the order to zero*/
				ido[idorder].list[i] = 0;						/*Remove the idp form the list of idps in the order*/
				remove = TRUE;								   /*Flag to indicate that the change has already occurred*/
			}
			else if (remove == TRUE) {
				ido[idorder].list[i-1] = ido[idorder].list[i]; /*Change all the next values*/
			}
		}
		remove = FALSE;
		for (i = 0; i < idp[idproduct].ordernumber; i++) {
			if (idp[idproduct].ordersList[i] == idorder) {
				idp[idproduct].ordersList[i] = 0;				/*delete ido from the list of orders*/
				remove = TRUE;									/*Flag to indicate that the change has already occurred*/
			}
			else if (remove == TRUE){
			idp[idproduct].ordersList[i-1] = idp[idproduct].ordersList[i];
			}
		}
		ido[idorder].NumberOfProducts--;						/*Corrects the number of products */
		idp[idproduct].ordernumber--;								/*Corrects the number of times a product is ordered*/
	}
}
/*Confirms if it is possible to a quantity of a product to be ordered and adds the quantity to the order */
void OrderaProduct(){
	int idproduct, idorder, qty;
	scanf("%d:%d:%d", &idorder, &idproduct, &qty);
	if (NotValidID(idorder, numberOrders)){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idproduct, idorder);
	}
	else if (NotValidID(idproduct, numberProducts)){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idproduct, idorder);
	}
	else if ((qty + QtyAlreadyOrded(idproduct) ) > idp[idproduct].stock){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idproduct, idorder);
	}
	else if ((WPCalculation(idorder, WEIGHT) + qty * idp[idproduct].weight) > MAX_WEIGHT){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idproduct, idorder);
	}
	else if (ido[idorder].idpQty[idproduct] > 0){
		ido[idorder].idpQty[idproduct] += qty;
	}
	else if (qty >0) {
		ido[idorder].list[ido[idorder].NumberOfProducts] = idproduct;
		ido[idorder].idpQty[idproduct] += qty;
		ido[idorder].NumberOfProducts++;
		idp[idproduct].ordersList[idp[idproduct].ordernumber] = idorder;  /*Saber que um produto foi mencionado na encomenda x*/
		idp[idproduct].ordernumber ++;									/*contador de vezes que foi mencionado*/
	}
}
/*The sum of the price times the quantity of all products in a list*/
void PriceCalculator() {
	int idorder;
	scanf("%d", &idorder);
	if (NotValidID(idorder, numberOrders)){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idorder);
	}
	else {
		printf("Custo da encomenda %d %d.\n",idorder, WPCalculation(idorder, PRICE));
	}
}
/*Changes the price of a product*/
void ChangePrice () {
	int idproduct, Price;
	scanf("%d:%d", &idproduct, &Price);
	if (NotValidID(idproduct, numberProducts)) {
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idproduct);
	}
	else {
		idp[idproduct].price = Price ;
	}
}
/*QTY of a product in one order*/
void ProductQtyOrder (){
	int idorder, idproduct;
	scanf("%d:%d", &idorder, &idproduct);
	if (NotValidID(idorder, numberOrders)){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idorder);
	}
	else if (NotValidID(idproduct, numberProducts)){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idproduct);
	}
	else {
		printf("%s %d.\n",idp[idproduct].description , ido[idorder].idpQty[idproduct]);
	}
}
/*output is the highest order quantity of a product*/
void MaxProduct() {
	unsigned int idproduct = 0, i = 0 , aux = 0;
	scanf("%u", &idproduct);
	if (NotValidID(idproduct, numberProducts)){
		printf("Impossivel listar maximo do produto %u. Produto inexistente.\n", idproduct);
	}
	if (idp[idproduct].ordernumber != 0) {
		for(i = 0; i < idp[idproduct].ordernumber; i++){
			if (ido[idp[idproduct].ordersList[i]].idpQty[idproduct] > ido[idp[idproduct].ordersList[aux]].idpQty[idproduct]){
				aux = i;
			}
			else if (ido[idp[idproduct].ordersList[i]].idpQty[idproduct] == ido[idp[idproduct].ordersList[aux]].idpQty[idproduct] && idp[idproduct].ordersList[i] < idp[idproduct].ordersList[aux] ){
				aux = i;
			}
		}	
		printf("Maximo produto %u %d %d.\n", idproduct, idp[idproduct].ordersList[aux], ido[idp[idproduct].ordersList[aux]].idpQty[idproduct]);
	}
}
/*Sort products by price*/
void PriceOrder(){
	unsigned int loop;
	mergeSort(x, 0, numberProducts-1, PRICE);
	printf("Produtos\n");
	for(loop = 0; loop < numberProducts; loop++)
      printf("* %s %u %d\n", idp[x[loop]].description, idp[x[loop]].price, idp[x[loop]].stock - QtyAlreadyOrded(x[loop]));
	
}
/*Sorts products within an order by alphabetical order*/
void AlphabeticalOrder (){
	unsigned short idorder, loop;
	scanf("%hu", &idorder);

	mergeSort(ido[idorder].list, 0 , ido[idorder].NumberOfProducts-1, ALPHABETICAL);
	
	if (NotValidID(idorder, numberOrders)){
		printf("Impossivel listar encomenda %hu. Encomenda inexistente.\n", idorder);
	}
	else{
		printf("Encomenda %u\n",idorder);
		if (ido[idorder].NumberOfProducts > 0){
			for(loop = 0; loop < ido[idorder].NumberOfProducts; loop++){
				
				printf("* %s %u %d\n",idp[ido[idorder].list[loop]].description, idp[ido[idorder].list[loop]].price, ido[idorder].idpQty[ido[idorder].list[loop]]);
			}
		}
	}
}
/*Commandline - Main loop that waits for a command until the x is press*/
int main() {
	char command;

	while ((command = getchar()) != 'x') {
		switch (command) {
		case 'a':
			CreatNewProduct(idp);
			break;
		case 'q':
			AddStock(idp);
			break;
		case 'N':
			CreatNewOrder();
			break;
		case 'A':
			OrderaProduct();
			break;
		case 'r':
			RemoveStock(idp);
			break;
		case 'R':
			RemoveProduct();
			break;
		case 'C':
			PriceCalculator();
			break;
		case 'p':
			ChangePrice();
			break;
		case 'E':
			ProductQtyOrder ();
			break;
		case 'm':
			MaxProduct();
			break;
		case 'l':
			PriceOrder();
			break;
		case 'L':
			AlphabeticalOrder();
			break;
		}		
		getchar();
	}
	return 0;
}
