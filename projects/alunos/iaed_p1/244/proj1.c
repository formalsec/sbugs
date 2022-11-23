#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#define MaxProducts 10000 	/* Maximum allowed number of different products*/
#define MaxPackages 500	 	/* Maximum allowed number of packages */
#define LEN 64			/* Maximum length of a received string */

/* Product struct */
struct Product
{
	int id;
	char description[LEN];
	int price;
	int weight;
	int stock;
} Product;

/* Package struct */
struct Package
{
	struct Product contents[MaxProducts];
	int contentsCount;
	int id;
	int weight;
} Package;

/* Arrays and counters to hold and count all the products and packages */
struct Product allProducts[MaxProducts];
int ProductCounter;
struct Package allPackages[MaxPackages];
int PackageCounter;

/* 
This function adds a new product into the allProducts array
	input: 	description of product
			price of product
			weight of product
			stock of product
	output: void
*/
void addProduct(char command[LEN])
{
	char delim[2] = ":";
	struct Product temp;
	char *token;
	token = strtok(command, delim);
	/*id*/
	temp.id = ProductCounter;
	/*description*/
	strcpy(temp.description, token);
	/*price*/
	token = strtok(NULL, delim);
	temp.price = strtol(token, NULL, 10);
	/*weight*/
	token = strtok(NULL, delim);
	temp.weight = strtol(token, NULL, 10);
	/*stock*/
	token = strtok(NULL, delim);
	temp.stock = strtol(token, NULL, 10);
	/*adds to array*/
	allProducts[ProductCounter] = temp;
	printf("%s%d%s\n", "Novo produto ", temp.id, ".");
	/*counter increased*/
	ProductCounter = ProductCounter + 1;
}

/*
This function adds stock to an existing product
	input: 	idp of product
			quantity of stock being added
	output: void
*/
void addStock(char command[LEN])
{
	int idp;
	int i;
	int found = 0; /*int will be changed to 1 if there is a product with the id provided*/
	int qtd;
	char delim[2] = ":";
	char *token;
	/*id num*/
	token = strtok(command, delim);
	idp = strtol(token, NULL, 10);
	/*quantity to be added*/
	token = strtok(NULL, delim);
	qtd = strtol(token, NULL, 10);
	/*searching for id of product and adding stock*/
	for (i = 0; i < ProductCounter; ++i)
	{
		if (allProducts[i].id == idp)
		{
			/*this is where it adds the stock*/
			allProducts[i].stock = allProducts[i].stock + qtd;
			found = 1;
		}
	}
	/*shows error if no matching id is found*/
	if (found == 0)
	{
		printf("%s%d%s\n", "Impossivel adicionar produto ", idp, " ao stock. Produto inexistente." );
	}
}

/*
This function creates a new package in the package array
	input: 	none
	output: void
*/
void newPackage()
{
	/*declares and initialized a new package and then adds it to the array*/
	struct Package temp;
	temp.id = PackageCounter;
	/* weight and contents count are assumed to be at 0 by default in other functions so they have to be initialized at the creation of the package */
	temp.weight = 0;
	temp.contentsCount = 0;
	allPackages[PackageCounter] = temp;
	PackageCounter = PackageCounter + 1;
	printf("%s%d%s\n", "Nova encomenda ", temp.id, ".");
}

/*
This function adds a product to a package
	input: 	idp of product to be added
			ide of package product is being added to
			quantity of product being added to the package
	output: void
*/
void addToPackage(char command[LEN])
{
	int idp;
	int ide;
	int qtd;
	int inConNum;
	char *token;
	int packageNum = -1;
	int productNum = -1;
	char delim[2] = ":";
	int i;
	int exists = 0;
	/*ide*/
	token = strtok(command, delim);
	ide = strtol(token, NULL, 10);
	/*idp*/
	token = strtok(NULL, delim);
	idp = strtol(token, NULL, 10);
	/*qtd*/
	token = strtok(NULL, delim);
	qtd = strtol(token, NULL, 10);
	/*to find the package id*/
	for (i = 0; i < PackageCounter; ++i)
	{
		if (ide == allPackages[i].id)
		{
			packageNum = i;
		}
	}
	/*to find the product*/
	for (i = 0; i < ProductCounter; ++i)
	{
		if (idp == allProducts[i].id)
		{
			productNum = i;
		}
	}
	/*checks for errors*/
	if (packageNum == -1)
	{
		printf("%s%d%s%d%s\n", "Impossivel adicionar produto ", idp, " a encomenda ", ide, ". Encomenda inexistente.");
	} 
	else if (productNum == -1) 
	{
		printf("%s%d%s%d%s\n", "Impossivel adicionar produto ", idp, " a encomenda ", ide, ". Produto inexistente.");
	} 
	else if (allProducts[productNum].stock < qtd) 
	{
		printf("%s%d%s%d%s\n", "Impossivel adicionar produto ", idp, " a encomenda ", ide, ". Quantidade em stock insuficiente.");
	}
	else if (allPackages[packageNum].weight + (allProducts[productNum].weight)*qtd > 200)
	{
		printf("%s%d%s%d%s\n", "Impossivel adicionar produto ", idp, " a encomenda ", ide, ". Peso da encomenda excede o maximo de 200.");
	}
	else /*if it gets through to this else then no error had a  chance to occur and the package can be updated*/
	{	
		/* loops through the contents of the package in order to check if a new product is being added or if the quantity of an existing product is being adjusted*/
		for (i = 0; i < allPackages[packageNum].contentsCount; ++i)
		{
			/* checks whether product id in contents array matches new product id. If so, 'exists's value is changed */
			if(allPackages[packageNum].contents[i].id == allProducts[productNum].id)
			{
				inConNum = i;
				exists = 1; /* the variable 'exists' is changed to 1 if there is already an instance of the product in the package */
			}
		}
		if (exists == 0)
		{
			/* no instances of the product are present so it is added from scratch */
			allPackages[packageNum].contents[allPackages[packageNum].contentsCount] = allProducts[productNum];
			allPackages[packageNum].contents[allPackages[packageNum].contentsCount].stock = qtd;
			allPackages[packageNum].weight = allPackages[packageNum].weight + (allProducts[productNum].weight)*qtd;
			allPackages[packageNum].contentsCount = allPackages[packageNum].contentsCount + 1;
			allProducts[productNum].stock = allProducts[productNum].stock - qtd;
			/* in order, this section:
				added the product into the contents array of the package
				set the quantity of product in the contents array
				calculated and set the new weight of the package
				increased the counter for how many different products are in the contents array
				calculated and set the new stock of the product in the allProducts array
			*/
		}
		else
		{
			/* here there is already an instance of the product so we need to adjust the quantity of it as well as the weight of the package */
			allPackages[packageNum].contents[inConNum].stock = allPackages[packageNum].contents[inConNum].stock + qtd;
			allPackages[packageNum].weight = allPackages[packageNum].weight + (allProducts[productNum].weight)*qtd;
			allProducts[productNum].stock = allProducts[productNum].stock - qtd;
			/* in order, this section:
				added stock to the product in the contents array
				calculated and set the new package weight
				calculated and set the new stock in the allProducts array
			*/
		}
	}
}

/*
This function removes stock of a product in the allProducts array
	input: 	idp of product
			quantity to be removed from stock
*/
void removeStock(char command[LEN])
{
	int idp;
	int qtd;
	char *token;
	char delim[2] = ":";
	int i;
	int productNum = -1;
	/*idp*/
	token = strtok(command, delim);
	idp = strtol(token, NULL, 10);
	/*qtd*/
	token = strtok(NULL, delim);
	qtd = strtol(token, NULL, 10);
	/*to find the product*/
	for (i = 0; i < ProductCounter; ++i)
	{
		if (idp == allProducts[i].id)
		{
			productNum = i;
		}
	}
	if (productNum == -1)
	{
		printf("%s%d%s\n", "Impossivel remover stock do produto ", idp, ". Produto inexistente.");
	}
	else if (allProducts[productNum].stock < qtd)
	{
		printf("%s%d%s%d%s\n", "Impossivel remover ", qtd, " unidades do produto ", idp, " do stock. Quantidade insuficiente.");
	}
	else /*if it makes it here then all conditions are cleared*/
	{
		/* removes the stock */
		allProducts[productNum].stock = allProducts[productNum].stock - qtd;
	}
}

/*
This function removes a product from a package
	input: 	ide of package
			idp of product
	output: void
*/
void removeFromPackage(char command[LEN])
{
	int ide;
	int idp;
	char *token;
	int packageNum = -1;
	int productNum = -1;
	char delim[2] = ":";
	int i;
	int inPackNum;
	/*ide*/
	token = strtok(command, delim);
	ide = strtol(token, NULL, 10);
	/*idp*/
	token = strtok(NULL, delim);
	idp = strtol(token, NULL, 10);
	/*to find the package id*/
	for (i = 0; i < PackageCounter; ++i)
	{
		if (ide == allPackages[i].id)
		{
			packageNum = i;
		}
	}
	/*to find the product*/
	for (i = 0; i < ProductCounter; ++i)
	{
		if (idp == allProducts[i].id)
		{
			productNum = i;
		}
	}
	if (packageNum == -1)
	{
		printf("%s%d%s%d%s\n", "Impossivel remover produto ", idp, " a encomenda ", ide, ". Encomenda inexistente.");
	} 
	else if (productNum == -1) 
	{
		printf("%s%d%s%d%s\n", "Impossivel remover produto ", idp, " a encomenda ", ide, ". Produto inexistente.");
	}
	else
	{
		/* loops through the contents of the package */
		for (i = 0; i < allPackages[packageNum].contentsCount; ++i)
		{
			/* checks if the right product has been found and records the array index for later deletion */
			if (allPackages[packageNum].contents[i].id == idp)
			{
				inPackNum = i;
			}
		}
		/* new package weight is calculated and stock is updated in the product array*/
		allPackages[packageNum].weight = allPackages[packageNum].weight - (allPackages[packageNum].contents[inPackNum].weight)*(allPackages[packageNum].contents[inPackNum].stock);
		allProducts[productNum].stock = allProducts[productNum].stock + allPackages[packageNum].contents[inPackNum].stock;
		for (i = inPackNum; i < allPackages[packageNum].contentsCount; ++i)
		{
			/* the product above the one to be deleted is moved into the now open spot. All products above it are also moved down one spot */
			allPackages[packageNum].contents[i] = allPackages[packageNum].contents[i+1];
		}
		/* contentsCount has to be decreased to reflect the deletion fo a product */
		allPackages[packageNum].contentsCount = allPackages[packageNum].contentsCount - 1;
	}
}

/*
This function calculates the cost of a package
	input: 	ide of package
	output: void
*/
void calcCost(int ide)
{
	int i;
	int packageNum = -1;
	int total = 0;
	/*to find the package id*/
	for (i = 0; i < PackageCounter; ++i)
	{
		if (ide == allPackages[i].id)
		{
			packageNum = i;
		}
	}
	if (packageNum == -1)
	{
		printf("%s%d%s\n", "Impossivel calcular custo da encomenda ", ide, ". Encomenda inexistente.");
	}
	else
	{
		/* loops through contents and sums up costs of products*/
		for (i = 0; i < allPackages[packageNum].contentsCount; ++i)
		{
			total = total + (allPackages[packageNum].contents[i].price)*(allPackages[packageNum].contents[i].stock);
		}
		printf("%s%d%s%d%s\n", "Custo da encomenda ", ide, " ", total, ".");
	}
}

/*
This function changes the price of a product specified by its idp
	input: 	idp of product whose price needs changing
			new price of product
	output: void
*/
void changePrice(char command[LEN])
{
	int idp;
	int Nprice;
	char *token;
	char delim[2] = ":";
	int i;
	int q;
	int productNum = -1;
	/*idp*/
	token = strtok(command, delim);
	idp = strtol(token, NULL, 10);
	/*Nprice*/
	token = strtok(NULL, delim);
	Nprice = strtol(token, NULL, 10);
	/*to find product id*/
	for (i = 0; i < ProductCounter; ++i)
	{
		if (idp == allProducts[i].id)
		{
			productNum = i;
		}
	}
	if (productNum == -1)
	{
		printf("%s%d%s\n", "Impossivel alterar preco do produto ", idp, ". Produto inexistente.");
	}
	else
	{
		/* price is changed in the product array */
		allProducts[productNum].price = Nprice;
		/* loops through the package array */
		for (i = 0; i < PackageCounter; ++i)
		{
			/* loops through the contents of the packages */
			for (q = 0; q < allPackages[i].contentsCount; ++q)
			{
				/* checks if the product beeing viewed has the same idp as the one specified and makes chanegs to price if it is so*/
				if (allPackages[i].contents[q].id == allProducts[productNum].id)
				{
					allPackages[i].contents[q].price = Nprice;
				}
			}
		}
	}
}

/*
This function prints the details of a specific product present in a package
	input: 	idp of the product the function is supposed to look for
			ide of the package the product is in
	output: void
*/
void inPackProdInfo(char command[LEN])
{
	int idp;
	int ide;
	char *token;
	char delim[2] = ":";
	int i;
	int productNum = -1;
	int packageNum = -1;
	/*ide*/
	token = strtok(command, delim);
	ide = strtol(token, NULL, 10);
	/*idp*/
	token = strtok(NULL, delim);
	idp = strtol(token, NULL, 10);
	/*to find the package id*/
	for (i = 0; i < PackageCounter; ++i)
	{
		if (ide == allPackages[i].id)
		{
			packageNum = i;
		}
	}
	/*to find the product id*/
	for (i = 0; i < ProductCounter; ++i)
	{
		if (idp == allProducts[i].id)
		{
			productNum = i;
		}
	}
	/*conditions to be cleared*/
	if (packageNum == -1)
	{
		printf("%s%d%s\n", "Impossivel listar encomenda ", ide, ". Encomenda inexistente.");
	}
	else if (productNum == -1)
	{
		printf("%s%d%s\n", "Impossivel listar produto ", idp, ". Produto inexistente.");
	}
	else /*if it reaches here, then all conditions have been cleared*/
	{
		/* loops through the contents of the package specidfied by the received ide */
		for (i = 0; i < allPackages[packageNum].contentsCount; ++i)
		{
			/* this if statement checks for when the selected product has the same idp as the one specified. If no such product is found then nothing is printed */
			if (allPackages[packageNum].contents[i].id == idp)
			{
				printf("%s%s%d%s\n", allPackages[packageNum].contents[i].description, " ", allPackages[packageNum].contents[i].stock, ".");
			}
		}
	}
}

/*
This function looks for and prints the details of a product in package that contains the most instances of it
	input: idp of product
	output: void 
*/
void findMode(int idp)
{
	int i;
	int q;
	int productNum = -1;
	/*details of package with most occurences of a product*/
	int packageNum = -1;
	int pInStock = 0;
	/*to find the product id*/
	for (i = 0; i < ProductCounter; ++i)
	{
		if (idp == allProducts[i].id)
		{
			productNum = i;
		}
	}
	if (productNum == -1)
	{
		printf("%s%d%s\n", "Impossivel listar maximo do produto ", idp, ". Produto inexistente.");
	}
	else
	{
		/* loops through all packages */
		for (i = 0; i < PackageCounter; ++i)
		{
			/* loops through the contents of the packages */
			for (q = 0; q < allPackages[i].contentsCount; ++q)
			{
				/* here it sees if the product being seen has the same id as the idp received */
				if (allPackages[i].contents[q].id == idp)
				{
					/* here it checks if the quantity of this product is higher than the modal value recorded */
					if(allPackages[i].contents[q].stock > pInStock)
					{
						packageNum = i;
						pInStock = allPackages[i].contents[q].stock;
					}
				}
			}
		}
		if (packageNum == -1)
		{
			/* no instances of the product were found in any package so no output is required */
		}
		else
		{
			printf("%s%d%s%d%s%d%s\n", "Maximo produto ", idp, " ", allPackages[packageNum].id, " ", pInStock, ".");
		}
	}
}

/*
This function lists all existing products in increasing order of price
	input: 	array of all existing products
	output: void
A copy of the array is passed to the function so that the original array is not placed out of order
*/
void listPrice(struct Product listt[MaxProducts])
{
	int i;
	int q;
	struct Product tempy;
	/*bubble sort*/
	for (i = 0; i < ProductCounter-1; ++i)
	{
		for (q = 0; q < ProductCounter-i-1; ++q)
		{
			if (listt[q].price > listt[q+1].price)
			{
				/*swaps both items*/
				tempy = listt[q];
				listt[q] = listt[q+1];
				listt[q+1] = tempy;
			}
		}
	}
	printf("%s\n", "Produtos");
	for (i = 0; i < ProductCounter; ++i)
	{
		printf("%s%s%s%d%s%d\n", "* ", listt[i].description, " ", listt[i].price, " ", listt[i].stock);
	}
}

/*
This function lists the contents of a package in alphabetical order of description
	input: 	ide of package
			array of all packages
	output: void
*/
void alphaList(int ide, struct Package listt[MaxProducts])
{
	int i;
	int q;
	int packageNum = -1;
	struct Product tempy;
	/*to find the package id*/
	for (i = 0; i < PackageCounter; ++i)
	{
		if (ide == allPackages[i].id)
		{
			packageNum = i;
		}
	}
	if (packageNum == -1)
	{
		printf("%s%d%s\n", "Impossivel listar encomenda ", ide, ". Encomenda inexistente.");
	}
	else
	{
		/*bubble sort*/
		for (i = 0; i < listt[packageNum].contentsCount-1; ++i)
		{
			for (q = 0; q < listt[packageNum].contentsCount-i-1; ++q)
			{
				if (strcmp(listt[packageNum].contents[q].description, listt[packageNum].contents[q+1].description) > 0)
				{
					/*swaps both items*/
					tempy = listt[packageNum].contents[q];
					listt[packageNum].contents[q] = listt[packageNum].contents[q+1];
					listt[packageNum].contents[q+1] = tempy;
				}
			}
		}
		printf("%s%d\n", "Encomenda ", ide);
		for (i = 0; i < listt[packageNum].contentsCount; ++i)
		{
			printf("%s%s%s%d%s%d\n", "* ", listt[packageNum].contents[i].description, " ", listt[packageNum].contents[i].price, " ", listt[packageNum].contents[i].stock);
		}
	}
}

/* This is the main function; it serves to read in commands and pass the correct arguements to the functions called in */
int main()
{
	char arg[LEN];
	char mander = ' ';
	int grail;
	PackageCounter = 0;
	ProductCounter = 0;
	/* A while loop containing a switch keeps the program running untill the command to stop it, 'x', is called */
	while(mander!='x')
	{
		/* gets selected command */
		mander = getchar();
		switch(mander)
		{
			case 'a':
				getchar();
				scanf("%[^\n]s", arg);
				addProduct(arg);
				break;
			case 'q':
				getchar();
				scanf("%[^\n]s", arg);
				addStock(arg);
				break;
			case 'N':
				newPackage();
				break;
			case 'A':
				getchar();
				scanf("%[^\n]s", arg);
				addToPackage(arg);
				break;
			case 'r':
				getchar();
				scanf("%[^\n]s", arg);
				removeStock(arg);
				break;
			case 'R':
				getchar();
				scanf("%[^\n]s", arg);
				removeFromPackage(arg);
				break;
			case 'C':
				getchar();
				scanf("%d", &grail);
				calcCost(grail);
				break;
			case 'p':
				getchar();
				scanf("%[^\n]s", arg);
				changePrice(arg);
				break;
			case 'E':
				getchar();
				scanf("%[^\n]s", arg);
				inPackProdInfo(arg);
				break;
			case 'm': 
				getchar();
				scanf("%d", &grail);
				findMode(grail);
				break;
			case 'l':
				listPrice(allProducts);
				break;
			case 'L':
				getchar();
				scanf("%d", &grail);
				alphaList(grail, allPackages);
				break;
		}
	}
	return 0;
}