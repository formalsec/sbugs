#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


int numeroProdutos = 0;
int numEncomendas = 0;

/*Comando a - Adiciona um novo produto ao sistema*/
void a(char* desc, int preco, int peso, int qtd){

	strcpy(vetorProdutos[numeroProdutos].desc, desc);
	vetorProdutos[numeroProdutos].preco = preco;
	vetorProdutos[numeroProdutos].peso = peso;
	vetorProdutos[numeroProdutos].stock = qtd;

	printf("Novo produto %d.\n", numeroProdutos);
	numeroProdutos++;
}

/*Comando q - Adiciona stock a um produto existente no sistema*/
void q(int idp, int qtd){
	if(idp > numeroProdutos -1){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
		return;
	}
	vetorProdutos[idp].stock+=qtd;
}

/*Comando N - Cria uma nova encomenda*/
void N(){
	int i;
	vetorEncomendas[numEncomendas].numProd = 0;
	vetorEncomendas[numEncomendas].peso = 0;
	
	for(i = 0 ; i < MAX_PRODENCOMENDAS; i++){
		vetorEncomendas[numEncomendas].produtos[i].id = -1;
	}
	printf("Nova encomenda %d.\n", numEncomendas);
	numEncomendas++;	
}

/*Comando A - Adiciona um produto a uma encomenda. Se o produto j? existir na encomenda, 
adiciona a nova quantidade ? quantidade existente.*/
void A(int ide, int idp, int qtd){
	int j = 0;
	int k = 0;

	if(ide > numEncomendas - 1 ){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return;	
	}
	if(idp > numeroProdutos - 1){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	}
	if(qtd > vetorProdutos[idp].stock){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		return;
	}
	if( qtd * vetorProdutos[idp].peso + vetorEncomendas[ide].peso > 200 ){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
		return;
	}
	while(j < vetorEncomendas[ide].numProd){
		if(vetorEncomendas[ide].produtos[k].id == idp){
			vetorEncomendas[ide].produtos[k].qtd += qtd;
			vetorProdutos[idp].stock -= qtd;
			vetorEncomendas[ide].peso += qtd * vetorProdutos[idp].peso; 
			return;		
		}
		if(vetorEncomendas[ide].produtos[k].id > -1){
			j++;
		}	
		k++;
	}

	for(j = 0; vetorEncomendas[ide].produtos[j].id != -1 ; j++);
	vetorEncomendas[ide].produtos[j].id = idp;
	vetorEncomendas[ide].produtos[j].qtd = qtd;
	vetorEncomendas[ide].peso += qtd * vetorProdutos[idp].peso; 
	vetorProdutos[idp].stock -= qtd;
	vetorEncomendas[ide].numProd++;
}

/*Comando r - Remove stock a um produto existente*/
void r(int idp, int qtd){	
	if(idp > numeroProdutos - 1){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
		return;
	}
	if(vetorProdutos[idp].stock - qtd < 0){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
	}else{
		vetorProdutos[idp].stock -= qtd;
	}
}

/*Comando R - Remove um produto de uma encomenda*/
void R(int ide, int idp){
	int i = 0;
	int k = 0;
	if(ide > numEncomendas - 1){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return;
	}
	if(idp > numeroProdutos - 1){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	}
	while(i < vetorEncomendas[ide].numProd){
		if(vetorEncomendas[ide].produtos[k].id == idp){
			vetorEncomendas[ide].produtos[k].id = -1;
			vetorProdutos[idp].stock += vetorEncomendas[ide].produtos[k].qtd;
			vetorEncomendas[ide].peso -= vetorEncomendas[ide].produtos[k].qtd * vetorProdutos[idp].peso; 	
			vetorEncomendas[ide].numProd--;
			vetorEncomendas[ide].produtos[k].qtd = -1;
		}
		if(vetorEncomendas[ide].produtos[k].id > -1){
			i++;
		}
		k++;
	}
}


/*Comando C - Calcula o custo de uma encomenda*/
void C(int ide){
	int i = 0;
	int k = 0;
	int total = 0;

	if(ide > numEncomendas - 1){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}
	while(i < vetorEncomendas[ide].numProd){
		if(vetorEncomendas[ide].produtos[k].id > -1){
			total += vetorEncomendas[ide].produtos[k].qtd * vetorProdutos[vetorEncomendas[ide].produtos[k].id].preco;
			i++;
		}
		k++;
	}
	printf("Custo da encomenda %d %d.\n", ide, total);
}

/*Comando p - Altera o preco de um produto existente no sistema*/
void p(int idp, int preco){
	if(idp > numeroProdutos - 1){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
		return;
	}else{
		vetorProdutos[idp].preco = preco;
	}
}

/*Comando E - Lista a descricao e a quantidade de um produto numa encomenda*/
void E(int ide, int idp){
	int i = 0;
	int k = 0;

	if(ide > numEncomendas - 1){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}
	/*caso de n?o existir nenhum produto criado com esse identificador*/
	if(idp > numeroProdutos - 1){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
		return;
	}
	while(i < vetorEncomendas[ide].numProd){
		if(vetorEncomendas[ide].produtos[k].id == idp){
			printf("%s %d.\n", vetorProdutos[idp].desc, vetorEncomendas[ide].produtos[k].qtd);
			return;
		}
		if(vetorEncomendas[ide].produtos[k].id > -1){
			i++;
		}
		k++;
	}
	printf("%s %d.\n", vetorProdutos[idp].desc, 0);
}

/*Comando m - Lista o identificador da encomenda em que o produto aparece mais vezes.
Se houver 2 ou mais encomendas nessa situa??o, dever? imprimir a encomenda de menor id.*/
void m(int idp){
	int i, j, k;
	int max = 0;
	int maxEncomenda;

	if(idp > numeroProdutos - 1){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
		return;
	}
	for(j = 0; j < numEncomendas; j++){
		i = 0;
		k = 0;
		while(i < vetorEncomendas[j].numProd){
			if(vetorEncomendas[j].produtos[k].id == idp && vetorEncomendas[j].produtos[k].qtd > max){
				max = vetorEncomendas[j].produtos[k].qtd;
				maxEncomenda = j;
			}
			if(vetorEncomendas[j].produtos[k].id > -1){
				i++;
			}
			k++;		
		}
	}
	if(max != 0){
		printf("Maximo produto %d %d %d.\n", idp, maxEncomenda, max);
	}	
}


/*Comando l - Lista todos os produtos existentes no sistema por ordem crescente de preco.
Se houver 2 ou mais produtos com o mesmo pre?o, dever? imprimir esses por ordem crescente de id de produto*/
void l(){
	int i,j,tmp;
	int p[MAX_PRODUTOS];

	for (i = 0; i < numeroProdutos; i++){
		p[i] = i;
	}
	for (i = 0; i < numeroProdutos - 1; i++){
		for (j = 0; j < numeroProdutos - i - 1; j++) {
			if(vetorProdutos[p[j]].preco > vetorProdutos[p[j+1]].preco){
			 	tmp = p[j+1];
				p[j+1] = p[j];
				p[j] = tmp;
				
			}
		}
	}
	printf("Produtos\n");
	for (i = 0; i < numeroProdutos; i++){
		printf("* %s %d %d\n", vetorProdutos[p[i]].desc, vetorProdutos[p[i]].preco, vetorProdutos[p[i]].stock);
	}
}



/*Comando L - Lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
void L(int ide){
	int i = 0;
	int j = 0;
	int tmp;
	int p[MAX_PRODENCOMENDAS];

	if(ide > numEncomendas - 1){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}
	while(i < vetorEncomendas[ide].numProd){
		if(vetorEncomendas[ide].produtos[j].id > -1){
			p[i] = j;
			i++;
		}
		j++;
	}
	for (i = 0; i < vetorEncomendas[ide].numProd - 1; i++){
		for (j = 0; j < vetorEncomendas[ide].numProd - i - 1; j++) {
			if(O(vetorProdutos[vetorEncomendas[ide].produtos[p[j]].id].desc, vetorProdutos[vetorEncomendas[ide].produtos[p[j+1]].id].desc)==1){
			 	tmp = p[j+1];
				p[j+1] = p[j];
				p[j] = tmp;	
			}
		}
	}
	printf("Encomenda %d\n", ide);
	for (i = 0; i < vetorEncomendas[ide].numProd; i++){
		printf("* %s %d %d\n", vetorProdutos[vetorEncomendas[ide].produtos[p[i]].id].desc, vetorProdutos[vetorEncomendas[ide].produtos[p[i]].id].preco, vetorEncomendas[ide].produtos[p[i]].qtd);
	}
}

/*Funcao auxiliar para ordenar strings. Usada para o comando L onde se ordena alfabeticamente os produtos.*/
int O(char *a, char *b){
	unsigned int i;

	for(i = 0; i < strlen(a); i++){
		if(i == strlen(b)){
			return 1;
		}
		if(a[i] < b[i]){
			return 0;
		}
		if(a[i] > b[i]){
			return 1;
		}
	}
	return 0;
}





