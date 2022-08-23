#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXDESC 64  /*Maximum number of characters for a product description*/
#define MAXPRODS 10000  /*Maximum number of products*/
#define MAXORDERS 500  /*Maximum number of orders*/
#define MAXORDERWEIGHT 200  /*Maximum weight of an order*/
#define MAXINPUT 112  /*Maximum size of input*/

#define exch(A, B){Product C = (A); (A) = (B); (B) = C;}

int PRODUCTID = -1;
int NUMBEROFPRODUCTS = 0;

int ORDERID = -1;
int NUMBEROFORDERS=0;

typedef struct {
	/*Product information:identification,price,weight,quantity*/
	int id,price,weight,quant;
	/*Product description*/
	char desc[MAXDESC];
}Product;
/*A vector of Product , where all the products in the system are stored*/
Product products[MAXPRODS];

typedef struct {
	/*Order information:identification,weight,number of products*/
	int id,weight,numOfProds;
	/*A vector of Product , where the products associated with the order are stored*/ 
	Product products[MAXPRODS];
}Order;
/*A vector of Order , where all the orders in the system are kept*/
Order orders[MAXORDERS];

/*-------------------------------------AUX FUNCTIONS--------------------------------------*/

/* Function "leLinha" from the slides;reads from stdin until \n and writes in input[]*/
void readLine(char input[]) { 
	int c,i=0;
	getchar();
	while((c = getchar()) != '\n')
		input[i++] = c;
	input[i] = '\0';
}

/* Cuts,when the sep[](':') is found,the string given in first argument in the number of strings required for the specific command*/
void stringCut(char input[],char *str[],int n_args,char sep[]) {
	int i = 0;
	str[i]=strtok(input,sep);

	for (i = 1; i < n_args; i++)
		str[i]=strtok(NULL,sep);	
}

/* Accesses the vector of products and returns the product with the given pid in argument*/
Product getProduct(int idp) {
	return products[idp];
}

/* partitions the vector of products given*/
int partition(Product v[], int l, int r) {
	int i = l - 1, j = r;
	int pivot = v[r].price;

	while (i < j) {
		while (v[++i].price < pivot);
		while (pivot < v[--j].price && j != l);
		if(i < j)
			exch(v[i],v[j]);
	}
	exch(v[i],v[r]);
	return i;
}

/* sorts the given Product vector using quicksort*/
void quicksort(Product v[], int l, int r) {
	if (r > l) {
		int i = partition(v, l, r);
		quicksort(v, l, i-1);
		quicksort(v, i+1, r);
	}
}


/* Returns 'true' if the product with idp is in the order ide,if the product isn't there the function returns 'false'*/
bool productInOrder(int idp,int ide) {
	int i;

	for (i = 0; i < orders[ide].numOfProds; i++)
		if (orders[ide].products[i].id == idp) return true;
	return false;
}

/*-------------------------------------MAIN FUNCTIONS-------------------------------------*/
/*Initializes a Product with the attributes given in str[]*/
Product createProduct(char *str[]) {
	Product p;
	PRODUCTID++;

	p.id = PRODUCTID;
	strcpy(p.desc,str[0]);
	p.price = atoi(str[1]);
	p.weight = atoi(str[2]);
	p.quant = atoi(str[3]);
	NUMBEROFPRODUCTS++;
	return p;

}

/*Inserts a Product in the Product vector*/
void addProduct(Product p) { /*a*/
	if (p.id<MAXPRODS) products[p.id] = p;
	printf("Novo produto %d.\n", p.id);
}

/* Increments the stock of given Product with the given quantity*/ 
void addStock(char *str[]) { /*q*/
	int idp = atoi(str[0]),quant = atoi(str[1]);

	if (idp <= PRODUCTID) products[idp].quant += quant;
	else printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
}


/*Initializes a new Order and places it in the order vector*/
void newOrder() { /*N*/
	Order o;
	ORDERID++;

	if(ORDERID<MAXORDERS) {
		o.id=ORDERID;
		o.weight = 0;
		o.numOfProds = 0;
		orders[ORDERID] = o;
		NUMBEROFORDERS++;
		printf("Nova encomenda %d.\n",o.id);
	}
}

/*Adds a given Product to a given Order*/
void addProductToOrder(char *str[]) { /*A*/
	int ide = atoi(str[0]),idp = atoi(str[1]),qtd = atoi(str[2]),i;
	Product p = getProduct(idp);
	
	if (ide>ORDERID) printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
	else if(idp>PRODUCTID) printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
	else if(qtd>p.quant) printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
	else if((orders[ide].weight + (qtd*p.weight))>200) printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
	else {
		if(!productInOrder(idp,ide)){
			strcpy(orders[ide].products[orders[ide].numOfProds].desc,p.desc);
			orders[ide].products[orders[ide].numOfProds].id = p.id;
			orders[ide].products[orders[ide].numOfProds].price = p.price;
			orders[ide].products[orders[ide].numOfProds].weight = p.weight;
			orders[ide].products[orders[ide].numOfProds].quant = qtd;
			products[p.id].quant -= qtd;
			orders[ide].weight += (qtd*p.weight);
			orders[ide].numOfProds++;
		} 
		else{
			for (i = 0; i < orders[ide].numOfProds; i++) {
				if(orders[ide].products[i].id==idp) {
					orders[ide].products[i].quant += qtd;
					products[p.id].quant -= qtd;
					orders[ide].weight += (qtd*p.weight);
				}
			}
		}
	}
}

/*Removes the given quantity to the stock of the given Product*/
void removeStock(char *str[]) { /*r*/
	int idp = atoi(str[0]),qtd = atoi(str[1]);

	if(idp>PRODUCTID) printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
	else if(products[idp].quant<qtd) printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
	else products[idp].quant -= qtd;
}


/*Removes a Product from an Order*/
void removeFromOrder(char *str[]) { /*R*/
	int ide = atoi(str[0]),idp= atoi(str[1]),i,flag =0;

	if(ide>ORDERID) printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
	else if(idp>PRODUCTID) printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
	else{
		if(productInOrder(idp,ide)) {
			for (i = 0; i < orders[ide].numOfProds; ++i)
			{
				if(orders[ide].products[i].id == idp || flag==1) {
					if (flag == 0) {
						orders[ide].weight -= (products[idp].weight*orders[ide].products[i].quant);
						products[idp].quant += orders[ide].products[i].quant;
					}
					orders[ide].products[i] = orders[ide].products[(i+1)];
					flag=1;
				}
			}

			orders[ide].numOfProds--;
		}
	}
}

/*returns the sum of prices of Products in an Order*/
void getCost(char input[]) { /*C*/
	int ide = atoi(input),i,cost=0;

	if(ide>ORDERID) printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
	else{
		for (i = 0; i < orders[ide].numOfProds; ++i)
			if(orders[ide].products[i].quant>0 && orders[ide].products[i].price>0) cost += (orders[ide].products[i].price*orders[ide].products[i].quant);
		printf("Custo da encomenda %d %d.\n",ide,cost);
	}
}

/*Changes the price of a Product in the whole system(products & orders)*/
void changePrice(char *str[]) { /*p*/
	int idp = atoi(str[0]),price = atoi(str[1]),i,j;

	if(idp > PRODUCTID) printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
	else {
		products[idp].price = price;
		for(i = 0;i < NUMBEROFORDERS;i++)
			for(j = 0;j < orders[i].numOfProds;j++) 
				if(orders[i].products[j].id == idp) orders[i].products[j].price = price;			 
	}
}

/*Prints the description and quantity of a given product in a given order*/
void listProductInOrder(char *str[]) { /*E*/
	int ide = atoi(str[0]),idp = atoi(str[1]),i;
	Product p = products[idp];

	if(ide>ORDERID) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
	else if(idp>PRODUCTID) printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
	else if(!productInOrder(idp,ide)) printf("%s 0.\n",p.desc);
	else{
		for (i = 0; i < orders[ide].numOfProds; i++)
			if(orders[ide].products[i].id==idp) {
				printf("%s %d.\n",p.desc,orders[ide].products[i].quant);
				break;
			}
		} 
}

/*Searches "orders" to find the one with the most quantity of the given Product*/
void orderWithMostProduct(char *str[]) { /*m*/
	int idp = atoi(str[0]),ide,i,j,mostQuant=0;

	if(products[idp].id!=idp) printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
	else {
		for (i = 0; i < NUMBEROFORDERS; i++)
			for (j = 0; j < orders[i].numOfProds; j++)
				if(orders[i].products[j].id == idp && orders[i].products[j].quant > mostQuant) {
				 ide = i , mostQuant = orders[i].products[j].quant;
				}
		if(mostQuant>0) printf("Maximo produto %d %d %d.\n",idp,ide,mostQuant);
	}
}

/*Lists products per price,starting in the least expensive*/
void listPerPrice() { /*l*/
	int i,k=0,j;
	Product arr_temp[MAXPRODS];

	for (i = 0; i < NUMBEROFPRODUCTS ; i++)
		arr_temp[k++] = products[i];
	quicksort(arr_temp,0,k-1);
	
	for(i=0;i<NUMBEROFPRODUCTS;i++) {
		for(j=i+1;j<NUMBEROFPRODUCTS;j++)	
			if(arr_temp[j].price==arr_temp[i].price && arr_temp[j].id < arr_temp[i].id) exch(arr_temp[j],arr_temp[i]);
	}
	printf("Produtos\n");
	for (i = 0; i < k; i++)
		printf("* %s %d %d\n",arr_temp[i].desc,arr_temp[i].price,arr_temp[i].quant);
}

/*Lists products in an Order Alphabetically*/
void listAlphabetically(char input[]) { /*L*/
	int ide = atoi(input),i,j,numOfProds;
	Product array_temp[MAXPRODS];

	if(ide>ORDERID) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
	else {
		numOfProds = orders[ide].numOfProds;
		for (i = 0; i < numOfProds; ++i)
			array_temp[i] = orders[ide].products[i];
		for (i = 0; i < numOfProds; ++i)
			for (j = 0; j < numOfProds; ++j)
				if (strcmp(array_temp[j].desc,array_temp[i].desc)>0) exch(array_temp[j],array_temp[i]);
      	printf("Encomenda %d\n",ide); 
      	for (i = 0; i < numOfProds; i++)
      		printf("* %s %d %d\n",array_temp[i].desc,array_temp[i].price,array_temp[i].quant);
	}
}


int main() {
	char c,input[MAXINPUT], *str[MAXINPUT],sep[2]=":";

	while(1) {
		c = getchar();
		switch(c) {
			case 'a':
				readLine(input);
				stringCut(input,str,4,sep);
				addProduct(createProduct(str));
				break;
			case 'q':
				readLine(input);
				stringCut(input,str,2,sep);
				addStock(str);
				break;
			case 'N':
				newOrder();
				break;
			case 'A':
				readLine(input);
				stringCut(input,str,3,sep);
				addProductToOrder(str);
				break;
			case 'r':
				readLine(input);
				stringCut(input,str,2,sep);
				removeStock(str);
				break;
			case 'R':
				readLine(input);
				stringCut(input,str,2,sep);
				removeFromOrder(str);
				break;
			case 'C':
				readLine(input);
				getCost(input);
				break;
			case 'p':
				readLine(input);
				stringCut(input,str,2,sep);
				changePrice(str);
				break;
			case 'E':
				readLine(input);
				stringCut(input,str,2,sep);
				listProductInOrder(str);
				break;
			case 'm':
				readLine(input);
				stringCut(input,str,1,sep);
				orderWithMostProduct(str);
				break;
			case 'l':
				listPerPrice();
				break;
			case 'L':
				readLine(input);
				listAlphabetically(input);
				break;
			case 'x':
				exit(0);
			default:
				break;

		}
	}
	return 0;
}
