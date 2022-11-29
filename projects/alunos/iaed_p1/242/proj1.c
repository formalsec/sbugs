#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Inicializacao das contantes usadas ao longo do programa. 
*/

#define PRODID 10000
#define DESC 64
#define ORDERS 500
#define SUC 0
#define ERROR 1

/*
Definicao das estruturas produto e encomenda.
Criacao variaveis globais (contadores, vetores produtos,
vetores encomendas e vetores auxiliares).
*/

typedef struct product {

	int pid;
	char desc[DESC];
	int exists;
	int price;
	int weight;
	int stock;

} product;

typedef struct order {

	int oid;
	int total_w;
	int price_t;
	int in_order;
	int max_s;
	int exists;
	product p_ord[PRODID];

} order;


int count_orders = 0;
int total_prod = 0;
order orders[ORDERS];
product products[PRODID];
product pcopy[PRODID];
product swap[PRODID];
product aux[PRODID];

void createProd(){

/* Nesta fucao sao lidos os valores de descricao, preco, peso e quantidade em stock.
   Assinala-se a existencia do produto e imprime-se o numero do produto e
   por fim incrementa-se o contador de produtos.
*/

	int p, w, s;
	char desc[DESC];

	scanf(" %[^:]:%d:%d:%d", desc, &p, &w, &s);

	products[total_prod].pid = total_prod;
	strcpy(products[total_prod].desc, desc);
	products[total_prod].exists = 1;
	products[total_prod].price = p;
	products[total_prod].weight = w;
	products[total_prod].stock = s;

	printf("Novo produto %d.\n", total_prod);
	total_prod++;
	
}


int addStock(){

/* Nesta fucao sao lidos os valores de id de produto e quantidade a adicionar ao produto p_id.
   Se o produto nao existir, levanta-se o erro, mas em caso contrario,
   incrementa-se a quantidade indicada.
*/	

	int p_id, a_qty;
	
	scanf(" %d:%d", &p_id, &a_qty);

	if(p_id > total_prod || products[p_id].exists != 1){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", p_id);
		return ERROR;
	}
	
	else{
		products[p_id].stock += a_qty;
		return SUC;
	}
}


void newOrder(){

/* Nesta fucao e inicializada um encomenda colocando os seus valores a zero.
   Assinala-se a existencia da encomenda e imprime-se o numero da mesma e
   por fim incrementa-se o contador de encomendas.
*/

	orders[count_orders].oid = count_orders;
	orders[count_orders].total_w = 0;
	orders[count_orders].price_t = 0;
	orders[count_orders].in_order = 0;
	orders[count_orders].max_s = 0;
	orders[count_orders].exists = 1;
	
	printf("Nova encomenda %d.\n", count_orders);
	count_orders++;	
}


int addProd(){

/* Nesta fucao sao lidos os valores de id de encomenda, id de produto e 
   a quantidade a adicionar a encomenda o_id.
   Se o produto ja existe, apenas se incrementa o peso total da encomenda, o preco total
   e a quantidade pretendida, reduzido a quantidade do produto no vetor products.
   incrementa-se a quantidade indicada. Caso contrario, inicializa-se o produto no vetor produtos
   p_ord dentro da respetiva encomenda.
*/

	int o_id, p_id, qty;

	scanf(" %d:%d:%d", &o_id, &p_id, &qty);

	if(o_id > count_orders || orders[o_id].exists != 1){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", p_id, o_id);
		return ERROR;
	}

	else if(p_id > total_prod || products[p_id].exists != 1){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", p_id, o_id);
		return ERROR;
	}

	else if((products[p_id].stock - qty) < 0){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", p_id, o_id);
		return ERROR;
	}

	else if((orders[o_id].total_w + (qty * products[p_id].weight)) > 200){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", p_id, o_id);
		return ERROR;
	}

	else if(orders[o_id].p_ord[p_id].exists == 1){
		orders[o_id].total_w += (qty * products[p_id].weight);
		orders[o_id].price_t += (qty * products[p_id].price);
		orders[o_id].p_ord[p_id].stock += qty;

		products[p_id].stock -= qty;
		return SUC;
	}

	else{
		orders[o_id].total_w += (qty * products[p_id].weight);
		orders[o_id].price_t += (qty * products[p_id].price);
		orders[o_id].p_ord[p_id].pid = p_id;
		strcpy(orders[o_id].p_ord[p_id].desc, products[p_id].desc);
		orders[o_id].p_ord[p_id].exists = 1;
		orders[o_id].p_ord[p_id].price = products[p_id].price;
		orders[o_id].p_ord[p_id].weight = products[p_id].weight;
		orders[o_id].p_ord[p_id].stock = qty;
		orders[o_id].in_order += 1;
		products[p_id].stock -= qty;
		return SUC;	
	}
}


int removeStock(){

/* Nesta fucao sao lidos os valores de id de produto e quantidade a remover ao produto p_id.
   Se o produto nao existir ou a quantidade a remover levar a stock negativo, levanta-se o erro, 
   mas em caso contrario, decrementa-se a quantidade indicada.
*/

	int p_id, rm_qty;
	
	scanf(" %d:%d", &p_id, &rm_qty);

	if(p_id > total_prod || products[p_id].exists != 1){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", p_id);
		return ERROR;
	}

	else if(products[p_id].stock - rm_qty < 0){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", rm_qty, p_id);
		return ERROR;
	}

	else{
		products[p_id].stock -= rm_qty;
		return SUC;
	}
}


int removeProd(){

/* Nesta fucao sao lidos os valores de id de encomenda, id de produto.
   Se o produto ja nao existe, retorna sucesso.
   Caso contrario, remove-se o produto da encomenda deixando os seus valores a 0.
*/

	int o_id, p_id;

	scanf(" %d:%d", &o_id, &p_id);

	if(o_id > count_orders || orders[o_id].exists != 1){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", p_id, o_id);
		return ERROR;
	}

	else if(p_id > total_prod || products[p_id].exists != 1){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", p_id, o_id);
		return ERROR;
	}

	else if(orders[o_id].p_ord[p_id].exists == 0){
		return SUC;
	}

	else{
		products[p_id].stock += orders[o_id].p_ord[p_id].stock;
		orders[o_id].total_w -= (orders[o_id].p_ord[p_id].stock * products[p_id].weight);
		orders[o_id].price_t -= (orders[o_id].p_ord[p_id].stock * products[p_id].price);
		orders[o_id].max_s = 0;
		orders[o_id].in_order--;

		orders[o_id].p_ord[p_id].exists = 0;
		orders[o_id].p_ord[p_id].price = 0;
		orders[o_id].p_ord[p_id].weight = 0;
		orders[o_id].p_ord[p_id].stock = 0;
		return SUC;	
	}	
}


int calcCost(){

/* Nesta fucao e lido o id de encomenda.
   Se a encomenda nao existir, levanta erro.
   Imprime apenas o preco total (price_t) da encomenda o_id.
*/

	int o_id;

	scanf(" %d", &o_id);

	if(o_id > count_orders || orders[o_id].exists != 1){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", o_id);
		return ERROR;
	}

	printf("Custo da encomenda %d %d.\n", o_id, orders[o_id].price_t);
	return SUC;

}


int changePrice(){

/* Esta fucao le o id do produto e o novo preco desse produto.
   Se o produto nao existir, levanta erro.
   Procura dentro de todas as encomendas que tenham esse produto e altera o preco total
   e respetivo preco do produto.
*/

	int p_id, n_price, i, s;
	
	scanf(" %d:%d", &p_id, &n_price);

	if(p_id > total_prod || products[p_id].exists != 1){ 
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", p_id);
		return ERROR;
	}

	for(i = 0; i < count_orders; i++){
		if(orders[i].p_ord[p_id].exists == 1){
			s = orders[i].p_ord[p_id].stock;
			orders[i].price_t += (s * n_price) - (s * orders[i].p_ord[p_id].price);
			orders[i].p_ord[p_id].price = n_price;
		}
	}
		
	products[p_id].price = n_price;
	return SUC;
}


int getInfo(){

/* Nesta fucao e lido o id de encomenda e o id de produto.
   Se o produto ou a encomenda nao existirem, levanta erro.
   Inicia todos as encomendas com o respetivo id de produto e descricao.
   Imprime, por fim, a descricao e quantidade de p_id em orders.
*/

	int o_id, p_id, i, j;

	scanf(" %d:%d", &o_id, &p_id);

	if(o_id > count_orders || orders[o_id].exists != 1){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);
		return ERROR;
	}

	else if(p_id > total_prod || products[p_id].exists != 1){
		printf("Impossivel listar produto %d. Produto inexistente.\n", p_id);
		return ERROR;
	}

	for(i = 0; i < count_orders; i++){
		for(j = 0; j < total_prod; j++){
			orders[i].p_ord[j].pid = j;
			strcpy(orders[i].p_ord[j].desc, products[j].desc);	
		}
	}

	printf("%s %d.\n", orders[o_id].p_ord[p_id].desc, orders[o_id].p_ord[p_id].stock);
	return SUC;
}

int getID(){

/* Nesta fucao e lido o id de produto.
   Se o produto nao existir, levanta erro.
   Itera sobre todas as encomendas para saber qua a encomenda com maior quantidade
   de produto p_id e imprime o produto na encomenda e a sua respetiva quantidade.
*/

	int p_id, i, total = 0, ord = 0;

	scanf(" %d", &p_id);

	if(p_id > total_prod || products[p_id].exists != 1){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", p_id);
		return ERROR;
	}

	for(i = 0; i < count_orders; i++){
		if(orders[i].p_ord[p_id].exists == 1){
			orders[i].max_s = orders[i].p_ord[p_id].stock;
			if(total < orders[i].max_s){
				total = orders[i].max_s;
				ord = i;
			}
			total = orders[ord].max_s;
		}
	}

	if(orders[ord].p_ord[p_id].exists == 1){
		printf("Maximo produto %d %d %d.\n", p_id, ord, total);
	}

	return SUC;
}

void mergePrice(product p[PRODID], int l, int m, int r){ /* Funcao auxiliar ao mergeSort*/

	int i, j, k;

	for (i = m+1; i > l; i--){
    	aux[i-1] = p[i-1];
	}

  	for (j = m; j < r; j++){
   		aux[r+m-j] = p[j+1];
  	}

  	for (k = l; k <= r; k++){
    	if ((aux[j].price < aux[i].price) || i > m){
    	  p[k] = aux[j--];
    	}
   		
   		else{
    	  p[k] = aux[i++];
   		}
    }
}


void listProd(product p[PRODID], int l, int r){ /*Funcao mergeSort para ordenar vetor de produtos*/
	
	int m = (l+r)/2;

	if(r <= l) return;

	listProd(p, l, m);
	listProd(p, m+1, r);
	mergePrice(p, l, m, r);
}

void printProd(){

/* Nesta fucao nao e lido nada, pois apeas se pretende ordenar produtos pelo preco ascendente.
   Realiza uma copia para vetor auxiliar e chama funcao que ordena vetor.
   Imprime a descricao, preco e quantidade de todos os produtos no sistema.
*/

	int i;

	for(i = 0; i < total_prod; i++){
		pcopy[i] = products[i];
	}

	listProd(pcopy, 0, total_prod-1);

	printf("Produtos\n");
	for(i = 0; i < total_prod; i++){
		if(pcopy[i].exists == 1)
			printf("* %s %d %d\n", pcopy[i].desc, pcopy[i].price, pcopy[i].stock);
	}	
}


void mergeDesc(product p[PRODID], int l, int m, int r){ /* Funcao auxiliar ao mergeSort*/

	int i, j, k;

	for(i = m+1; i > l; i--){
    	aux[i-1] = p[i-1];
	}

  	for(j = m; j < r; j++){
   		aux[r+m-j] = p[j+1];
  	}

  	for(k = l; k <= r; k++){
    	if((strcmp(aux[j].desc, aux[i].desc) < 0) || i > m){
    	  p[k] = aux[j--];
    	}
   		
   		else{
    	  p[k] = aux[i++];
   		}
    }
}

void listOrd(product p[PRODID], int l, int r){ /*Funcao mergeSort para ordenar vetor de produtos alfabeticamente*/
	
	int m = (l+r)/2;

	if(r <= l) return;

	listOrd(p, l, m);
	listOrd(p, m+1, r);
	mergeDesc(p, l, m, r);
}

int orderProds(){

/* Nesta fucao e lido o id de encomenda.
   A funcao vai ordenar a descricao dos produtos dentro da encomenda o_id alfabeticamente.
   Imprime descricao, preco e quantidade de todos os produtos dessa encomenda.
*/

	int o_id, i;

	scanf(" %d", &o_id);

	if(o_id > count_orders || orders[o_id].exists != 1){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);
		return ERROR;
	}

	for(i = 0; i < total_prod; i++){
		swap[i] = orders[o_id].p_ord[i];
	}

	listOrd(swap, 0, total_prod-1);

	printf("Encomenda %d\n", o_id);
	for(i = 0; i < total_prod; i++){
		if(swap[i].exists == 1)
			printf("* %s %d %d\n", swap[i].desc, swap[i].price, swap[i].stock);
	}
	return SUC;
}

int main(){

	char cmd = '\0';

	while(cmd != 'x'){
        cmd = getchar();

        switch(cmd){
			case 'a':
				createProd();
				break;

			case 'q':
				addStock();
				break;

			case 'N':
				newOrder();
				break;

			case 'A':
				addProd();
				break;

			case 'r':
				removeStock();
				break;

			case 'R':
				removeProd();
				break;

			case 'C':
				calcCost();
				break;

			case 'p':
				changePrice();
				break;

			case 'E':
				getInfo();
				break;

			case 'm':
				getID();
				break;

			case 'l':
				printProd();
				break;

			case 'L':
				orderProds();
				break;
		}

	}

	return 0;
}