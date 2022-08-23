#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define N_MAX 9999
#define D_MAX 63
#define P_MAX 10000
#define E_MAX 500
#define W_MAX 200
#define less(A,B)  (A < B)==true

int pConta = 0; /*contador para os produtos*/
int eConta = 0; /*contador para as encomendas*/


/*------------------------------------------------------------------------|
| Estrutura __produto__ 												  |
|																		  |
| caracterizada por:													  |
| 	.id          |identificador(um numero inteiro no intervalo [0, 9 999])|
| 	.description |uma descricaoo(uma string nao vazia com um maximo de 63c|
| 	.price   	 |pre?o (um numero inteiro maior que 0)					  |		 
|	.weight      |peso (um numero inteiro maior que 0)					  |
|	.qtd         |quantidade em stock (um numero inteiro maior ou igual a0|
|	.exists      |o produto existe na encomenda se =1 ou nao se = 0       |
--------------------------------------------------------------------------*/
typedef struct {
	int id;
	char description[D_MAX+1];
	int price;
	int weight;
	int qtd;
	int exists;/*exists diz me se o produto existe na encomenda ou nao*/
}__produto__;

/*inicializacao da tabela de produtos*/
__produto__ produtos[P_MAX] = {{0}};


/*------------------------------------------------------------------------|
| Estrutura __encomenda__ 												  |
|																		  |
| caracterizada por:													  |
| 	.id          |identificador(um numero inteiro no intervalo [0, 9 999])|
| 	.price   	 |pre?o (um numero inteiro maior que 0)					  |		 
|	.weight      |peso (um numero inteiro maior que e menor que 200)	  |				  |
|	.qtd         |quantidade em stock (numero inteiro maior que 0         |
|	__produto__  |lista de produtos que compoem a encomenda               |
--------------------------------------------------------------------------*/
typedef struct {
	int id;
	int weight;
	int qtd;
	int price;
	__produto__ p[P_MAX];
}__encomenda__;

/*inicializacao da tabela de encomendas*/
__encomenda__ encomendas[E_MAX]= {{0}};

/*cria-se produto*/
__produto__ cria_produto(){
	return produtos[pConta];
}

/*funcao auxiliar que poe a zeros o produto - elimina o produto*/
__produto__ elimina_produto(int idp){
	int i, aux;
	__produto__ p_aux[P_MAX];
	for (i=0; i<pConta; i++){
		if(produtos[i].id == idp){
			p_aux[i] = produtos[i];
			aux = i;
			p_aux[i].exists = 0;
			p_aux[i].price=0;
			p_aux[i].weight=0;
			p_aux[i].qtd=0;
		}
	}
	return p_aux[aux];
}

/*----------------------------------------------------------|
| Function: __a__ 											|
|															|
| Description: adiciona um novo produto ao sistema     		|									    |                  |
|  -> recebe...descricao,preco,peso,quantide                |
|  -> devolve...id do produto criado                        |
------------------------------------------------------------*/
void __a__(char description[D_MAX+1], int price, int weight, int qtd){
	__produto__ new;
	/*se o preco, o peso e a quantidade introduzidos > 0, adiciono o produto*/
	if((price >0 ) && (weight > 0) && (qtd > 0)){
		new = cria_produto();
		strcpy(new.description, description);
		new.price = price;
		new.weight = weight;
		new.qtd = qtd;
		new.id = pConta;
		new.exists = 0;
		/*por definicao, ao criar o produto ele nao existe em nenhuma encomenda*/
		produtos[pConta] = new;
		/*adicionei o novo produto criado - new, na lista de produtos*/
		printf("Novo produto %d.\n", pConta);
		pConta++;
		/*incremento os produtos existentesno sistema*/
	}
}

/*----------------------------------------------------------|
| Function: __k__ 											|
|															|
| Description: auxiliar que lsita os produtos no sistema    |									    |                  |
|  -> recebe..............................................  |
|  -> devolve...produtos existentes no sistema              |
------------------------------------------------------------*/
void __k__(){
	int i;
	for(i=0; i<pConta; i++){
		printf("idp %d\n", produtos[i].id);
		printf("%s\t", produtos[i].description);
		printf("preco %d\t", produtos[i].price);
		printf("peso %d\t", produtos[i].weight);
		printf("qtd %d\n", produtos[i].qtd);
	}
}


/*----------------------------------------------------------|
| Function: __l__ 											|
|															|
| Description: lista todos produtos no sistema,  			|
			    ordem crescente preco                       |									    |                  |
|  -> recebe..............................................  |
|  -> devolve...produtos listados ordem crescente de preco  |
|               se houver produtos com o mesmo preco lista  |
|				o maior id, como criterio de desmpate       |
------------------------------------------------------------*/
void __l__(){
	int i,k=0,j, index=0, aux=0;
	__produto__ paux[P_MAX], a[P_MAX];
	for(i=0; i<pConta; i++){
		/*copio os produtos para o vetor aux*/
		paux[i] = produtos[i];
		a[i] = paux[i];
	}
	/*selection sort para ordenar produtos*/
 	for(i=0; i < (pConta-1); i++){
 		index = i;
 		for(j = i+1; j < pConta; j++){
 			if(paux[index].price > paux[j].price){
 				index = j;
 			}
 			if(paux[index].price == paux[j].price){
 				if(paux[index].id > paux[j].id){
 					index = j;
 				}
 			}
 		}
 		if(index != j){
			aux = paux[i].price;
			a[i].price = aux;
			a[i] = paux[i];
			paux[i] = paux[index];
			paux[index] = a[i];
			}
 		}

	printf("Produtos\n");
	for(k=0; k < pConta; k++){
		/*copio os produtos para o vetor aux*/
		printf("* %s ", paux[k].description);
		printf("%d ", paux[k].price);
		printf("%d\n", paux[k].qtd);
		i++;
	}
}

/*----------------------------------------------------------|
| Function: not_encomenda_exists 							|
|															|
| Description: auxiliar que verifica se encomenda existe    |									    |                  |
|  -> recebe....id da encomenda                             |
|  -> devolve...true se nao existe, false se existe         |
------------------------------------------------------------*/
bool not_encomenda_exists(int ide){
	if(ide > eConta-1)
		return true;
	else
		return false;
}

/*----------------------------------------------------------|
| Function: not_product_exists 							    |
|															|
| Description: auxiliar que verifica se produto existe      |									    |                  |
|  -> recebe....id do produto                               |
|  -> devolve...true se nao existe, false se existe         |
------------------------------------------------------------*/
bool not_product_exists(int idp){
	if(idp > pConta-1)
		return true;
	else
		return false;
}

/*----------------------------------------------------------|
| Function: __q__         	 							    |
|															|
| Description: adiciona stock a um produto existente sistema|									    |                  |
|  -> recebe....id do produto, stock                        |
|  -> devolve...erro se o produto nao existe                |
------------------------------------------------------------*/
void __q__(int idp, int qtd){
	int i;
	if(not_product_exists(idp)){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	}
	else{
		for (i=0; i < pConta; i++){
			/*aumento a quantidade de produto*/
			if(idp == i){
				produtos[idp].qtd += qtd;
				break;
			}
		}
	}
}

/*cria-se encomenda*/
__encomenda__ cria_Encomenda(){
	return encomendas[eConta];
}

/*----------------------------------------------------------|
| Function: weight_exceeds     	 							|
|															|
| Description: auxiliar que verifica se peso da encomenda   |
|			   excede max 200							    |                  
|  -> recebe....id da encomenda e produto,quantidade-produto|                             |
|  -> devolve...true se excede, false se nao excede 200     |
------------------------------------------------------------*/
bool weight_exceeds(int ide, int idp, int qtd){
	int i, j, p_total=0;
	for (i=0; i< pConta; i++){
		if(produtos[i].id == idp){
			/*multiplico o peso de cada produto pela sua quantidade*/
			p_total = (produtos[idp].weight) * (qtd);
			if (p_total > W_MAX){
				return true;
			}
		}
		for(j=0; j< eConta; j++){
			if(encomendas[j].id == ide){
				/*verifico se excede a quantidade maxima permitida*/
				if (encomendas[ide].weight + p_total > W_MAX){
					return true;
				}
			}
		}
	}
	return false;
}

/*----------------------------------------------------------|
| Function: not_enough_stock   	 							|
|															|
| Description: auxiliar que verifica se stock de produto    |
|			   satisfaz o pedido de  encomenda		        |                  
|  -> recebe....id do produto,quantidade a adicionar        |                             |
|  -> devolve...true se nao ha stock suficiente             |
|				false caso haja stock                       |
------------------------------------------------------------*/
bool not_enough_stock(int idp, int qtd){
	int i;
	for(i=0; i< pConta; i++){
		if(produtos[i].id == idp){	
			if(produtos[idp].qtd < qtd)
				return true;
		}
	}
	return false;
}

/*----------------------------------------------------------|
| Function: __N__ 											|
|															|
| Description: cria uma nova encomenda              		|									    |                  |
|  -> recebe..............................................  |
|  -> devolve...id da encomenda criada                      |
------------------------------------------------------------*/
void __N__(){
	/*crio uma nova encomenda
	.id atribuido pela ordem de introducao
	.peso por definicao 0 (encomenda ainda vazia) */
	__encomenda__ new;
	new = cria_Encomenda();
	new.id = eConta;
	new.weight = 0;
	/*atualizo as encomendas com a que acabei de criar*/
	encomendas[eConta] = new;
	printf("Nova encomenda %d.\n", eConta);
	eConta++;
	/*incremento N total encomendas*/
}

/*----------------------------------------------------------|
| Function: __A__ 											|
|															|
| Description: adiciona um produto a uma encomenda     		|									    |                  |
|  -> recebe...id da encomenda,produto e quantide           |
|  -> devolve...erro se nao passar as verificacoes          |
------------------------------------------------------------*/
void __A__(int ide, int idp, int qtd){
	/*adiciono um produto a uma encomenda*/
	int i,j,peso=0, aux=0;
	/*verifico se a encomenda existe*/
	if(not_encomenda_exists(ide)){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
	/*verifico se o produto existe*/
	else if(not_product_exists(idp)){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	/*verifico se o stock existente satisfaz o pedido de encomenda*/
	else if(not_enough_stock(idp,qtd)){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	}
	/*verifico se o peso da encomenda > 200*/
	else if(weight_exceeds(ide,idp, qtd)){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
	}
	
	else{
		for(i=0; i<(pConta); i++){
			if (produtos[i].id == idp){
				peso = produtos[i].weight;
				peso = peso*qtd;
			}
		}
		/*verifico se excede a quantidade maxima permitida*/
		aux = encomendas[ide].weight + peso;
		if(aux > W_MAX){
			printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
		}
		else{
			for(j=0; j<(eConta);j++){		
				/*existe o id produto na lista de id encomendas
				--> aumento a quantidade do produto
				--> aumento o peso da encomenda*/	
				if(encomendas[j].id==ide){
				/*adiciono produto a encomenda
				--> atualizo o peso da encomenda
				--> anexo produto a encomenda
				--> atualiza as quantidades em stock*/
					/*se o produto ja existe na encomenda*/
					/*caso seja a primeira vez que adiciono o produto a encomenda*/
					encomendas[j].p[idp].weight = produtos[idp].weight;
					strcpy(encomendas[j].p[idp].description, produtos[idp].description);
					encomendas[j].p[idp].id = idp;
					encomendas[j].p[idp].exists = 1;
					/*altero a flag Exists para 1
					pois este produto existe nesta encomenda*/
					encomendas[j].p[idp].price = produtos[idp].price;
					encomendas[j].price += produtos[idp].price * qtd;
					encomendas[j].weight += peso;
					encomendas[j].qtd += qtd;
					produtos[idp].qtd -= qtd;
					if (encomendas[j].qtd == qtd){
						encomendas[j].p[idp].qtd = qtd;
					}
					else{
						encomendas[j].p[idp].qtd += qtd;
					}
				}
			}
		}
	}
}

/*----------------------------------------------------------|
| Function: __C__ 											|
|															|
| Description: calcula o custo de uma encomenda     		|									    |                  |
|  -> recebe...id da encomenda,produto e quantide           |
|  -> devolve...custo total da encomenda 					|
|				erro se encomenda nao existe                |
------------------------------------------------------------*/
void __C__(int ide){
	int j;
	if(not_encomenda_exists(ide)){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	}
	else{
		for(j=0; j < eConta; j++){
			if(encomendas[j].id == ide){
				printf("Custo da encomenda %d %d.\n", ide, encomendas[ide].price);
				break;
			}
		}
	}
}

/*----------------------------------------------------------|
| Function: __r__ 											|
|															|
| Description: remove stock a um produto existente      	|									    |                  |
|  -> recebe...id da encomenda, quantide a remover          |
|  -> devolve...erro se produto nao existe 					|
|				erro se apos remocao nao existe stock       |
------------------------------------------------------------*/
void __r__(int idp, int qtd){
	int i;
	if(not_product_exists(idp)){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	}
	/*verifico se o stock existente satisfaz o pedido de encomenda*/
	else if(not_enough_stock(idp,qtd)){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
	}
	else{
		for (i = 0; i < pConta; i++){
			if(i ==idp)
				produtos[idp].qtd -= qtd;
		}
	}
}

/*----------------------------------------------------------|
| Function: __R__ 											|
|															|
| Description: remove um produto de uma encomenda       	|									    |                  |
|  -> recebe...id da encomenda, id produto a remover        |
|  -> devolve...erro se produto nao existe 					|
|				erro se encomenda nao existe                |
------------------------------------------------------------*/
void __R__(int ide, int idp){
	int i,j, qtd_idp_encomenda=0, price_del=0, weight_del=0;
	if(not_encomenda_exists(ide)){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
	/*verifico se o produto existe*/
	else if(not_product_exists(idp)){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else{
		for(i=0; i< eConta; i++){
			for(j=0; j< pConta; j++){
				if((i == ide)&&(j==idp)){
					qtd_idp_encomenda = encomendas[i].p[j].qtd;
					price_del = encomendas[i].p[j].price;
					weight_del = encomendas[i].p[j].weight;
					encomendas[i].p[j] = elimina_produto(idp);
					price_del = qtd_idp_encomenda * price_del;
					weight_del = qtd_idp_encomenda * weight_del;
					encomendas[i].price -= price_del;
					encomendas[i].weight -= weight_del;
					encomendas[i].qtd -= qtd_idp_encomenda;
					produtos[idp].qtd += qtd_idp_encomenda;

				}
			}
		}
	}
}

/*----------------------------------------------------------|
| Function: __K__   	 							        |
|															|
| Description: auxiliar lista produtos existente encomenda  |                 
|  -> recebe....id da encomenda       						| 
|  -> devolve...lista dos produtos na encomenda             |
------------------------------------------------------------*/
void __K__(int ide){
	int j,i=0;
	/*percorro encomendas*/
	printf("Encomenda %d\n", ide);
	/*percorro produtos*/
	while(i < pConta){
		for(j = 0; j < eConta; j++){
			if (encomendas[ide].id == j){
				if (encomendas[ide].p[i].price > 0){
					printf("%s\n", encomendas[j].p[i].description);
					printf("custa %d\t", encomendas[j].p[i].price);
					printf("existe %d\t", encomendas[j].p[i].qtd);
					printf("pesa %d\n", encomendas[j].p[i].weight);
				}	
				i++;
			}
		}
	}
}

/*----------------------------------------------------------|
| Function: __E__   	 							        |
|															|
| Description: lista descricao e quantidade de produtos     |
|				existentes numa  encomenda  				|                 
|  -> recebe....id da encomenda, id do produto     			| 
|  -> devolve...lista dos produtos na encomenda             |
|				<descricao> <quantidade>					|
|				erro caso encomenda ou produto nao existam	|
------------------------------------------------------------*/
void __E__(int ide, int idp){
	int i, j;
	if (not_product_exists(idp)){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	}
	else if(not_encomenda_exists(ide)){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	else{
		for(i=0; i<pConta; i++){
			for(j=0; j < eConta; j++){
				if(i == idp){
					if(j == ide){
						printf("%s %d.\n", produtos[idp].description, encomendas[ide].p[idp].qtd);
						break;
					}
				}
			}
		}
	}
}

/*----------------------------------------------------------|
| Function: __p__   	 							        |
|															|
| Description: altera o preco de um produto existente		|                 
|  -> recebe....id do produto, preco     		        	| 
|  -> devolve...erro caso produto nao existam   			|
------------------------------------------------------------*/
void __p__(int idp, int price){
	int i, j, new_total_price=0, old_total_price=0;
	if (not_product_exists(idp)){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	}
	else{
		for(i=0;i < pConta; i++){
			if (produtos[i].id == idp){
				produtos[i].price = price;
			}
			for(j = 0; j < eConta; j++){
				if (encomendas[j].p[i].id == idp){
					old_total_price = (encomendas[j].p[i].price * encomendas[j].p[i].qtd);
					new_total_price = (price * encomendas[j].p[i].qtd);
					encomendas[j].p[i].price = price;
					encomendas[j].price -= old_total_price;
					encomendas[j].price += new_total_price;
				}	
			}
		}
	}
}


/*----------------------------------------------------------|
| Function: __m__   	 							        |
|															|
| Description: lista o identificador da encomenda           |
|  				em que o produto dado ocorre mais vezes		|                 
|  -> recebe....id do produto    		        			| 
|  -> devolve...ide da encomenda onde o produto existe em   |
|				maior quantidade   			                |
|				erro caso o produto nao exista              |
------------------------------------------------------------*/
void __m__(int idp){
	int i=0, max=0, j=0, id_e=0, flag=0, aux[E_MAX]={-1};
	if (not_product_exists(idp)){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	}
	else{
		while(i < pConta){
			for(j = 0; j < eConta; j++){
				if ((encomendas[j].p[i].id == idp) && (encomendas[j].p[idp].exists==1) && (encomendas[j].p[i].qtd > 0)){
					aux[j] = encomendas[j].p[i].qtd;
					flag = 1;
				}
			}
			i++;
		}
		if (flag ==1){
			for(i = 0; i < E_MAX; i++){
				if (aux[i]>0){
					if(aux[i] > max){
						max = aux[i];
						id_e=i;
					}
				}
			}
			printf("Maximo produto %d ", idp);
			printf("%d ", id_e);
			printf("%d.\n", max);	
		}
	}
}

/*----------------------------------------------------------|
| Function: countP_in_id   	 							    |
|															|
| Description: auxiliar que devolve numero de produtos 		|
|              diferentes numa encomenda					|                 
|  -> recebe....id da encomenda    		        			| 
|  -> devolve...numero total de produtos diferentes nesse id|
------------------------------------------------------------*/
int countP_in_ide(int ide){
	int i,j,conta=0;
	for(j=0; j < eConta; j++){
		if( j == ide){
			for(i=0; i < pConta; i++){
				if (encomendas[j].p[i].exists == 1){
				conta++;
				}
			}	
		}
	}
	return conta;	
}

/*----------------------------------------------------------|
| Function: L   	 							    		|
|															|
| Description: lista todos os produtos de uma encomenda     |
|  				por ordem alfabetica da descrica			|                 
|  -> recebe....id da encomenda    		        			| 
|  -> devolve...lista ordenada dos produtos   				|
------------------------------------------------------------*/
void __L__(int ide){
	int i=0,j,k,conta=0;
	__produto__ paux[P_MAX]={0};
	__produto__ aux[P_MAX]={0};
	if(not_encomenda_exists(ide)){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	else{
		printf("Encomenda %d\n", ide);
		conta = countP_in_ide(ide);
		for(i=0;i<pConta; i++){
			if (encomendas[ide].p[i].exists == 1){
				paux[i] = encomendas[ide].p[i];
				aux[i] = paux[i];
			}/*copio os produtos para um vetor paux*/
		}	
		if (conta > 1){
			for(k=0; k< (pConta-1); k++){
				for(j = k+1; j < pConta; j++){
					/*se o caracter seguinte for maior que o atual, troco as
					suas posicoes no vetor*/
					if(strcmp(paux[k].description, paux[j].description)>0){
						aux[k] = paux[k];
						paux[k] = paux[j];
						paux[j] = aux[k];
					}
				}
			}
		}
		for(k = 0; k < pConta; k++){
			if(paux[k].qtd>0){
				printf("* %s ", paux[k].description);
				printf("%d ", paux[k].price);
				printf("%d\n", paux[k].qtd);
			}	
		}
	}
}


int main(){

	char description[D_MAX+1];
	int price;
	int weight;
	int qtd;
	int idp;/*identidficador do produto*/
	int ide;/*identidficador da encomenda*/
	char command;

	while (1){
		command = getchar();
		switch (command) {
		case 'a':
			/*adiciona um novo produto ao sistema*/
			scanf(" %[^:]:%d:%d:%d", description, &price, &weight, &qtd);
			__a__(description, price, weight, qtd);
			break;
		case 'k':
			/*comando auxiliar que lista os produtos existentes no sistema*/
			__k__();
			break;
		case 'K':
			/*comando auxiliar que lista os produtos existentes numa encomenda*/
			scanf(" %d", &ide);
			__K__(ide);
			break;
		case 'q':
			/*adiciona stock a um produto existente no sistema*/
			scanf(" %d:%d", &idp, &qtd);
			__q__(idp, qtd);
			break;
		case 'N':
			/*cria uma nova encomenda*/
			__N__();
			break;
		case 'A':
			/*adiciona um produto a uma encomenda*/
			scanf(" %d:%d:%d", &ide, &idp, &qtd);
			__A__(ide, idp, qtd);
			break;
		case 'r':
			/*remove stock a um produto existente*/
			scanf(" %d:%d", &idp, &qtd);
			__r__(idp, qtd);
			break;
		case 'R':
			/*remove um produto de uma encomenda*/
			scanf(" %d:%d", &ide, &idp);
			__R__(ide, idp);
			break;
		case 'C':
			/*calcula o custo de uma encomenda*/
			scanf("%d", &ide);
			__C__(ide);
			break;
		case 'p':
			/*altera o pre?o de um produto existente no sistema*/
			scanf(" %d:%d", &idp, &price);
			__p__(idp, price);
			break;
		case 'E':
			/*retorna a descri??o e a quantidade de um produto numa dada encomenda*/
			scanf(" %d:%d", &ide, &idp);
			__E__(ide, idp);
			break;
		case 'm':
			/*retorna o identificador da encomenda em que um dado produto ocorre mais vezes*/
			scanf(" %d", &idp);
			__m__(idp);
			break;
		case 'l':
			/*lista todos os produtos existentes no sistema por ordem crescente de pre?o*/
			__l__();
			break;
		case 'L':
			/*lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o*/
			scanf(" %d", &ide);
			__L__(ide);
			break;
		case 'x':
			/*termina o programa*/
			return EXIT_SUCCESS;
		default:
			printf("ERRO: comando desconhecido\n");
		}
		getchar();
	}
	return 0;
}





