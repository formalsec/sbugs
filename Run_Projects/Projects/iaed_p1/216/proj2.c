#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define DESCRIPTION 63 /*numero maximo caracters da descricao de Produtos*/
#define BUFFER 1800 /*tamanho buffer*/
#define PRODMAX 10000 /*numero maximo Produtos*/
#define ENCMAX 500 /*numero maximo Encomendas*/
#define ENCPESOMAX 200 /*peso maximo Encomenda*/


typedef struct produto{
 	int idp; /*id Produto*/
 	char desc[DESCRIPTION]; /*descricao*/
 	long preco;
 	long peso;
 	long quant; /*quantidade*/

 }Produto;



typedef struct encomenda{
	int ide; /*id Encomenda*/
	/*Produto prodE[ENCPESOMAX]; lista de Produtos da encomeda*/
	/*long q[ENCPESOMAX]; lista da quantidade em stock de cada Produto*/
	long quant[PRODMAX];
	int proE; /*numero de Produtos na Encomenda*/
	long pesoE;

}Encomenda;
Encomenda enc[ENCMAX]; /*lista de todas as Encomendas*/
Produto prod[PRODMAX]; /* lista de todos os Produtos*/



char buf[BUFFER]; /*buffer*/
char tok[2] = ":"; /*token para divis?o*/
int idpcount = 0; /*contador Produto*/
int idecount = 0; /*contador Encomenda*/

/* AUX FUNCTIONS*/

/*function to print Product List*/

void printProd(Produto prods[], int count){ /*print list of products*/
	int i; /*aux*/
	for(i=0; i<count; ++i){ /*iterate over list*/
		printf("* %s %ld %ld\n", prods[i].desc, prods[i].preco, prods[i].quant);
	}

}






/*MAIN FUNCTIONS*/

/*function to add packages*/
void addEnc(){ 
	enc[idecount].ide = idecount; /*sets id of order*/
	enc[idecount].pesoE = 0; /*set weigh*/
	enc[idecount].proE = 0; /*set*/





	
	
}

/*Function to list Products*/
void listProd(){

	int i, j, k; /*aux variables - for*/
	Produto temp; /*temporary product to switch and sort*/
	Produto prodaux[ENCPESOMAX]; /*aux list to print*/
	for(k=0; k<idpcount; ++k){/*fill aux list*/
		prodaux[k]=prod[k];
	}
	printf("Produtos\n");
	for(i=0; i<idpcount; ++i){ /*iterate over list*/
		for (j = i + 1; j < idpcount; ++j){ 
			if(prodaux[i].preco > prodaux[j].preco){ /*if price of second product is lower switch the products*/
				temp = prodaux[i];
            	prodaux[i] = prodaux[j];
            	prodaux[j] = temp;

			}
			else if(prodaux[i].preco == prodaux[j].preco){ /*if price is equal*/
				if(prodaux[i].idp > prodaux[j].idp){ /*switch if ID of first product is higher than the second*/
					temp = prodaux[i];
            		prodaux[i] = prodaux[j];
            		prodaux[j] = temp;
				}

			}
		}
	}
	printProd(prodaux, idpcount); /*print the list*/
}

/*function to add products*/
void addProd(){ 
	char *t, *ptr; /*aux chars to read from stdin*/
	prod[idpcount].idp = idpcount; /*sets the id of product*/
	fgets(buf, BUFFER, stdin); /*scans from stdin*/
	strtok(buf, "\n"); /*separate 1 line*/
	t = strtok (buf, tok); /*divides buffer with token :*/
	strcpy(prod[idpcount].desc, t); /*add description*/
	t = strtok (NULL, tok); /*divides once again*/
	prod[idpcount].preco = strtol(t, &ptr, 10); /*convert to long and add price*/
	t = strtok (NULL, tok); 
	prod[idpcount].peso = strtol(t, &ptr, 10); /*add weight*/
	t = strtok (NULL, tok); 
	prod[idpcount].quant = strtol(t, &ptr, 10); /*add quantity*/

	 
	
	
}

/*function to add stock to product*/
void addStock(){
	long id, q; /*aux for id of product and quantity*/
	char *t, *ptr; /*aux to read from stdin*/
	fgets(buf, BUFFER, stdin); /*scans from stdin*/
	strtok(buf, "\n"); /*separate 1 line*/
	t = strtok (buf, tok); /*divides buffer with token :*/
	id = strtol(t, &ptr, 10); /*convert to long*/
	if(id >= idpcount){ /*if id of product doesn't exist*/
		printf("Impossivel adicionar produto %ld ao stock. Produto inexistente.\n", id);
	}
	else{
		t = strtok (NULL, tok); /*divides once again*/
		q = strtol(t, &ptr, 10); /*convert to long*/
		prod[id].quant += q; /*add quantity to product*/
	}
	 
	
}

/*Function to add Product to Order*/

void addToEnc(){
	long e, ip, q, npeso; /*auxiliar variables for order, product, quantity and new order weight*/
	char *t, *ptr; /*aux to read from stdin*/
	
	fgets(buf, BUFFER, stdin); /*scans from stdin*/
	strtok(buf, "\n"); /*separate 1 line*/
	t = strtok (buf, tok); /*divides buffer with token :*/
	e = strtol(t, &ptr, 10); /*convert to long*/
	t = strtok (NULL, tok); /*divides once again*/
	ip = strtol(t, &ptr, 10);
	t = strtok (NULL, tok); /*divides once again*/
	q = strtol(t, &ptr, 10); 
	npeso = enc[e].pesoE + (q * prod[ip].peso); /*calculate new weight of order*/
	
	if(e>=idecount){ /*if order doesn't exist*/
		printf("Impossivel adicionar produto %ld a encomenda %ld. Encomenda inexistente.\n", ip, e);
		return;
	}

	else if(ip>=idpcount){ /*if product doesn't exist*/
		printf("Impossivel adicionar produto %ld a encomenda %ld. Produto inexistente.\n", ip, e);
		return;
	}
	

	else if(q > prod[ip].quant){ /*If product has run out of stock*/
		printf("Impossivel adicionar produto %ld a encomenda %ld. Quantidade em stock insuficiente.\n", ip, e);
		return;
	}

	else if(npeso>ENCPESOMAX){ /*if order is too heavy*/
		printf("Impossivel adicionar produto %ld a encomenda %ld. Peso da encomenda excede o maximo de 200.\n", ip, e);
	}
	else{
		prod[ip].quant -= q; /*remove given quantity from stock*/
		enc[e].quant[ip] += q; /*add product quantity to order*/
		enc[e].proE++; /*increase number of products in order*/
		enc[e].pesoE = npeso; /*define new weight of order*/




	}
	 
	

}

/*Function to remove stock from product*/

void remStock(){ 
	long id, q; /*aux for id of product and quantity*/
	char *t, *ptr; /*aux to read from stdin*/
	fgets(buf, BUFFER, stdin); /*scans from stdin*/
	strtok(buf, "\n"); /*separate 1 line*/
	t = strtok (buf, tok); /*divides buffer with token :*/
	id = strtol(t, &ptr, 10);
	t = strtok (NULL, tok); /*divides once again*/
	q = strtol(t, &ptr, 10); /*convert to long*/
	if(id >= idpcount){ /*if id of product doesn't exist*/
		printf("Impossivel remover stock do produto %ld. Produto inexistente.\n", id);
		return;
	}
	else if(q>prod[id].quant){ /*if given quantity isn't available on stock*/
		printf("Impossivel remover %ld unidades do produto %ld do stock. Quantidade insuficiente.\n", q, id);
		
	}
	else{
		prod[id].quant -= q; /*remove quantity from product*/

	}
	 
	
}
/*Remove Product from order*/

void remProd(){
	long e, ip, quanti; /*auxiliar variables for order and product*/
	char *t, *ptr; /*aux to read from stdin*/
	fgets(buf, BUFFER, stdin); /*scans from stdin*/
	strtok(buf, "\n"); /*separate 1 line*/
	t = strtok (buf, tok); /*divides buffer with token :*/
	e = strtol(t, &ptr, 10); /*convert to long*/
	t = strtok (NULL, tok); /*divides once again*/
	ip = strtol(t, &ptr, 10);
	if(e>=idecount){ /*if order doesn't exist*/
		printf("Impossivel remover produto %ld a encomenda %ld. Encomenda inexistente.\n", ip, e);
		return;
	}

	else if(ip>=idpcount){/*if product doesn't exist*/
		printf("Impossivel remover produto %ld a encomenda %ld. Produto inexistente.\n", ip, e);
		return;
	}
	else{
		quanti = enc[e].quant[ip]; /*save quantity*/
		enc[e].quant[ip] =0; /*set quantity of product in order to 0*/
		enc[e].proE--; /*decrease product counter*/
		enc[e].pesoE-= (quanti * prod[ip].peso); /*decrease weight of order*/
		prod[ip].quant += quanti; /*add quantity back to product stock*/
		

	}


}

/*Function to calculate cost of Order*/
void calcCusto(){
	long id, total, q, p; /*aux for id of oder, total cost, quantity and price*/
	char *t, *ptr; /*aux to read from stdin*/
	int i; /*aux for for cycle*/
	fgets(buf, BUFFER, stdin); /*scans from stdin*/
	strtok(buf, "\n"); /*separate 1 line*/
	t = strtok (buf, tok); /*divides buffer with token :*/
	id = strtol(t, &ptr, 10);
	if(id >= idecount){ /*if id of product doesn't exist*/
		printf("Impossivel calcular custo da encomenda %ld. Encomenda inexistente.\n", id);
	}
	else{
		total = 0;
		for(i=0; i<idpcount; ++i){ /*iterate products*/
			q = enc[id].quant[i]; /*quantity of product i in order*/
			if(q >0){ /*if it exists*/
				p = prod[i].preco; /*set individual price*/
				total+= (p*q); /*calculate price and add to total*/

			}
		}

		
		printf("Custo da encomenda %ld %ld.\n", id, total);
		
	}
	 
	
}

/*Function to change price*/

void chPri(){ 
	long id, p; /*aux for id of product and quantity*/
	char *t, *ptr; /*aux to read from stdin*/
	fgets(buf, BUFFER, stdin); /*scans from stdin*/
	strtok(buf, "\n"); /*separate 1 line*/
	t = strtok (buf, tok); /*divides buffer with token :*/
	id = strtol(t, &ptr, 10);
	if(id >= idpcount){ /*if id of product doesn't exist*/
		printf("Impossivel alterar preco do produto %ld. Produto inexistente.\n", id);
	}
	else {
		t = strtok (NULL, tok); /*divides once again*/
		p = strtol(t, &ptr, 10); /*convert to long*/
		prod[id].preco = p; /*set price*/
	}
	 
	
}

/*Function to print description and quantity of Product in given Order */

void listProdOrd(){
	long e, ip, q; /*auxiliar variables for order product, and quantity of product in order*/
	char *t, *ptr, *d; /*aux to read from stdin and aux for description*/
	fgets(buf, BUFFER, stdin); /*scans from stdin*/
	strtok(buf, "\n"); /*separate 1 line*/
	t = strtok (buf, tok); /*divides buffer with token :*/
	e = strtol(t, &ptr, 10); /*convert to long*/
	t = strtok (NULL, tok); /*divides once again*/
	ip = strtol(t, &ptr, 10);
	if(e>=idecount){ /*if order doesn't exist*/
		printf("Impossivel listar encomenda %ld. Encomenda inexistente.\n", e);
		return;
	}

	else if(ip>=idpcount){/*if product doesn't exist*/
		printf("Impossivel listar produto %ld. Produto inexistente.\n", ip);
		return;
	}
	else{
		
		d = malloc(strlen(prod[ip].desc)+1); /*allocate memory*/
		strcpy(d, prod[ip].desc); /*copy memory to aux variable*/
		q = enc[e].quant[ip];	/*get quantity*/
		
		printf("%s %ld.\n", d, q);
		
		
		free(d); /*free memory once it's no longer needed*/
	}	
}

/*Function to find which order has more of a given product */

void listMaxProd(){
	long id, ide, quant, quantaux; /*aux for id of product and order and quantity*/
	int e; /*aux to iterate orders*/
	char *t, *ptr; /*aux to read from stdin*/
	fgets(buf, BUFFER, stdin); /*scans from stdin*/
	strtok(buf, "\n");
	t = strtok (buf, tok); /*divides buffer with token :*/
	id = strtol(t, &ptr, 10);
	quant = 0;
	ide = 0;
	if(id >= idpcount){ /*if id of product doesn't exist*/
		printf("Impossivel listar maximo do produto %ld. Produto inexistente.\n", id);
	}
	else if(idecount!=0){ /*if there is at least one order */
		for(e = 0; e<idecount; ++e){ /*iterate orders*/
			quantaux = enc[e].quant[id]; /*set new quantity*/
			if(quantaux>quant){ /*if new quantity is higher than previous quantity*/
				quant = quantaux; /*set new quantity as highest*/
				ide = e; /*set id of order with highest quantity*/
			}
		
		

		}
		if(quant>0){ /*if product exists in at least one order*/
			printf("Maximo produto %ld %ld %ld.\n", id, ide, quant);
		}
	}
	 
	
}
/*Function to print all products in an order by alphabetical order*/

void listProdEnc(){
	long id, q; /*aux for id of order and quantity*/
	int p, i, j, k; /*aux for product count and cycles*/
	Produto temp; /*Aux to switch and sort*/
	char *t, *ptr; /*aux to read from stdin*/
	Produto prodaux[ENCPESOMAX]; /*aux product list for print*/
	fgets(buf, BUFFER, stdin); /*scans from stdin*/
	strtok(buf, "\n");
	t = strtok (buf, tok); /*divides buffer with token :*/
	id = strtol(t, &ptr, 10);
	q = 0;
	p = 0;
	if(id >= idecount){ /*if id of product doesn't exist*/
		printf("Impossivel listar encomenda %ld. Encomenda inexistente.\n", id);
	}
	else{
		printf("Encomenda %ld\n", id);
		for(i=0; i<idpcount; ++i){/*go through products*/
			q = enc[id].quant[i]; /*quantity of product in given order*/
			if(q>0){ /*if product exists in order*/
				prodaux[p]=prod[i]; /*add to aux list for print*/
				prodaux[p].quant = q; /*set product quantity in given order instead of in stock*/
				p++; /*increase product counter*/
				
			}
		}
		
	 	for(k=0;k<p;++k){
	      	for(j=k+1;j<p;++j){
		        if(strcmp(prodaux[k].desc,prodaux[j].desc)>0){ /*if first member comes after second one alphabeticaly switch them*/
		          	temp = prodaux[k]; 
	            	prodaux[k] = prodaux[j];
	            	prodaux[j] = temp;
	         	}
	      	}
	    }
			
		printProd(prodaux, p); /*print aux list*/
	}
	
	
}


int main() {
	
	
	while(1)
	{	
		char c = getchar(); /*read command from stdin*/
		switch(c){
			/*exit*/
			case'x': 
			 	exit(EXIT_SUCCESS);	
			/*new order*/
			case'N':
				addEnc();
				printf("Nova encomenda %d.\n", idecount++);
				break;
			/*list products*/
			case'l':
				listProd();
				break;

			
			/*add products*/
			case'a': /*add Product*/
				getchar(); /*read extra space from stdin*/
				addProd();
				printf("Novo produto %d.\n", idpcount++);
				break;
			/*add stock to product*/
			case'q':
				getchar(); /*read extra space from stdin*/
				addStock();
				break;
				
			
			/*add product to order*/	
			case'A':
				getchar(); /*read extra space from stdin*/
				addToEnc();
				break;
				
			/*decrease stock of product*/
			case'r':
				getchar(); /*read extra space from stdin*/
				remStock();
				break;
			
			/*remove product from order*/
			case'R':
				getchar(); /*read extra space from stdin*/
				remProd();
				break;
			/*calculate order cost*/
			case'C':
				getchar(); /*read extra space from stdin*/
				calcCusto();
				break;	
			/*change product price*/
			case'p':
				getchar(); /*read extra space from stdin*/
				chPri();
				break;
			/*list description and quantity of product in given order*/
			case'E':
				getchar(); /*read extra space from stdin*/
				listProdOrd();
				break;	
			/*list order with higher quantity of a given product*/
			case'm':
				getchar(); /*read extra space from stdin*/
				listMaxProd();
				break;	
			
			/*List all products in an order alphabetically*/
			case'L':
				getchar(); /*read extra space from stdin*/
				listProdEnc();
				break;	
			
		}
	}
	return 0;
}
