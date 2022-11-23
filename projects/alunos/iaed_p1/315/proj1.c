#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define Descricao 64 /*Uma string n?o vazia com um m?ximo de 63 caracteres.*/
#define MAX_PRODUTOS 10000 /*Maximo produtos diferentes. Os produtos sao numerados de 0 a 9 999 e sequencialmente pela sua ordem de introducao*/
#define MAX_ENCOMENDAS 500 /*Maximo encomendas. As encomendas sao numeradas de 0 a 499 e sequencialmente pela sua ordem de introducao.*/
#define MAX_UNIDADES 200 /*Cada encomenda podera pesar no maximo 200 unidades de peso.*/
#define MAX_COUNT 127 /* Maximo da tabela de ASCII*/

/*
* Estrutura do produto.
*/
struct Prodt {

	int id;
	char descr[Descricao];
	int preco;
	int peso;
	int qtd;

} prodt;

/*
* Estrutura da encomenda.
*/
struct Encomenda {

	struct Prodt produto[MAX_UNIDADES];
	int n_unidades;
	int idp;
	
} encomenda;

struct Prodt produtos[MAX_PRODUTOS];
struct Encomenda encomendas[MAX_ENCOMENDAS];



/**********************  FUNCOES PRINCIPAIS  **********************/

/*Adiciona um novo produto ao sistema.*/
int a(char descr[Descricao], int preco, int peso, int qtd, int idp){ 

	struct Prodt prod;
	strcpy(prod.descr, descr);
	prod.id = idp;
	prod.preco = preco;
	prod.peso = peso;
	prod.qtd = qtd;	
	produtos[idp] = prod;

	printf("Novo produto %i.\n", idp); /* idp e o identificador do produto criado.*/
	return ++idp;

}


/*Adiciona stock a um produto existente no sistema.*/
void q(int idp, int new_idp, int qtd){

	if(new_idp >= idp)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", new_idp);

	else
		produtos[new_idp].qtd += qtd;
}


/*Cria uma nova encomenda.*/
int N(int ide){

	struct Encomenda enc;
	enc.n_unidades = 0;
	enc.idp = 0;
	encomendas[ide] = enc;
	printf("Nova encomenda %i.\n", ide);

	return ++ide; /*ide e o identificador da encomenda criada*/
}


/*Adiciona um produto a uma encomenda. Se o produto ja existir na encomenda, adiciona a nova quantidade a quantidade existente*/
void A(int idp, int new_idp, int ide, int new_ide, int qtd){

	int new_peso = 0;
	int prodNotFound = 1;

	if(new_ide >= ide)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", new_idp, new_ide); /*no caso de nao existir nenhuma encomenda criada com esse identificador*/

	else if(new_idp >= idp )
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", new_idp, new_ide); /*no caso de nao existir nenhum produto criado com esse identificador*/

	else if(produtos[new_idp].qtd < qtd)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", new_idp, new_ide); /*no caso de nao existir stock suficiente desse produto para satisfazer a encomenda*/

	else if((encomendas[new_ide].n_unidades + qtd * produtos[new_idp].peso) > 200)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", new_idp, new_ide); /*no caso de a adi??o desse produto exceder o peso maximo permitido por encomenda*/

	else{

		int i;
		struct Prodt prod = produtos[new_idp];
		int prod_idp = encomendas[new_ide].idp;

		new_peso = qtd * produtos[new_idp].peso;
		encomendas[new_ide].n_unidades += new_peso;
		produtos[new_idp].qtd -= qtd;

		for(i = 0; i < prod_idp; i++){

			struct Prodt new_prod = encomendas[new_ide].produto[i];

			if(new_prod.id == prod.id){
				encomendas[new_ide].produto[i].qtd += qtd;
				prodNotFound = 0;
				break;
			}
		}

		if(prodNotFound){
			encomendas[new_ide].produto[prod_idp] = produtos[new_idp];
			encomendas[new_ide].produto[prod_idp].qtd = qtd;
			encomendas[new_ide].idp++;
		}
	}					
}


/*remove stock a um produto existente*/
void r(int idp, int new_idp, int qtd){

	if(new_idp >= idp){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", new_idp); /*no caso de nao existir nenhum produto criado com esse identificador*/
		return;
	}

	if(produtos[new_idp].qtd < qtd){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, new_idp); /*no caso de a quantidade de stock restante apos a remocao ser negativa*/
		return;
	}

	produtos[new_idp].qtd -= qtd;
}


/*remove um produto de uma encomenda*/
void R(int ide, int idp, int new_ide, int new_idp){

	if(new_ide >= ide)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", new_idp, new_ide); /*no caso de nao existir nenhuma encomenda criada com esse identificador*/

	else if(new_idp >= idp)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", new_idp, new_ide); /*no caso de nao existir nenhum produto criado com esse identificador*/

	else{

		int i, rem_unidades;
		int prod_idp = encomendas[new_ide].idp;
		int prodNotFound = 1;
		struct Prodt prod = produtos[new_idp];

		for(i = 0; i < prod_idp; i++) {

			struct Prodt new_prod = encomendas[new_ide].produto[i];

			if(new_prod.id == prod.id){
				rem_unidades = encomendas[new_ide].produto[i].qtd * encomendas[new_ide].produto[i].peso;
				encomendas[new_ide].n_unidades -= rem_unidades;
				produtos[new_idp].qtd += encomendas[new_ide].produto[i].qtd;
				prodNotFound = 0;
				break;
			}
		}

		if(!prodNotFound) { /* produto nao encontrado */

			for(; i < prod_idp; i++)
				encomendas[new_ide].produto[i] = encomendas[new_ide].produto[i+1];

			encomendas[new_ide].idp--;
		}
	}
}


/*calcula o custo de uma encomenda*/
void C(int ide, int new_ide){
	int i, preco = 0;
	struct Encomenda enc = encomendas[new_ide];

	if(new_ide >= ide)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", new_ide); /*no caso de nao existir nenhuma encomenda criada com esse identificador*/

	else{

		for(i = 0; i < enc.idp; i++)
			preco += enc.produto[i].preco * enc.produto[i].qtd;

		printf("Custo da encomenda %i %i.\n", new_ide, preco); /*preco e o valor total da encomenda ide*/
	}
} 


/*altera o pre?o de um produto existente no sistema*/
void p(int idp, int ide, int preco, int new_idp){

	int i, j;

	if(new_idp >= idp)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", new_idp); /*no caso de nao existir nenhum produto criado com esse identificador*/
	
	else{

		produtos[new_idp].preco = preco;

		for(i = 0; i < ide; i++) {
			for(j = 0; j < encomendas[i].idp; j++) {
				if(encomendas[i].produto[j].id == produtos[new_idp].id)
					encomendas[i].produto[j].preco = preco;
			}
		}
	}
} 


/*lista a descri??o e a quantidade de um produto numa encomenda*/
void E(int new_idp, int new_ide, int idp, int ide){
	
	int i, prod_idp, qtd = 0;

	if(new_ide >= ide)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", new_ide); /*no caso de nao existir nenhuma encomenda criada com esse identificador*/

	else if(new_idp >= idp)
		printf("Impossivel listar produto %d. Produto inexistente.\n", new_idp); /*no caso de nao existir nenhum produto criado com esse identificador*/

	else{

		prod_idp = encomendas[new_ide].idp;

		for(i = 0; i < prod_idp; i++){
			if(encomendas[new_ide].produto[i].id == produtos[new_idp].id){
				qtd = encomendas[new_ide].produto[i].qtd;
				break;
			}
		}

		printf("%s %d.\n", produtos[new_idp].descr, qtd); /*descr e a descri??o do produto idp e qtd ? a quantidade desse produto na encomenda ide*/
	}
}	


/*lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas nessa situa??o, dever? imprimir a encomenda de menor id*/
void m(int new_idp, int idp, int ide){

	int i, j, max = 0, enc = 0;

	if( new_idp >= idp)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", new_idp); /*no caso de nao existir nenhum produto criado com esse identificador*/

	else{

		for(i = 0; i < ide; i++) {
			for(j = 0; j < encomendas[i].idp; j++) {
				if(encomendas[i].produto[j].id == produtos[new_idp].id) {
					if(encomendas[i].produto[j].qtd > max) {
						max = encomendas[i].produto[j].qtd;
						enc = i;
					}
					break;
				}
			}
		}

		if(max)
			printf("Maximo produto %d %d %d.\n", new_idp, enc, max);
	}
}


/**********************  FUNCOES AUXILIARES  **********************/
/* Permite juntar tudo no "final" do merge, faz parte da funcao Merge Sort*/
void k2(struct Prodt prod[], int l_Lim, int m, int r_Lim){

	int i, j, k;
	struct Prodt aux[MAX_PRODUTOS];

	for(i = m+1; i > l_Lim; i--)
		aux[i-1] = prod[i-1];

	for(j = m; j < r_Lim; j++)
		aux[r_Lim+m-j] = prod[j+1];

	for(k = l_Lim; k <= r_Lim; k++) {

		if(aux[j].preco < aux[i].preco)
			prod[k] = aux[j--];

		else if(aux[j].preco == aux[i].preco){
			if(aux[j].id > aux[i].id)
				prod[k] = aux[i++];

			else
				prod[k] = aux[j--];
		}

		else
			prod[k] = aux[i++];
	}
}


/* Merge Sort*/
void k1(struct Prodt prod[], int l_Lim, int r_Lim) {

	int m;

	m = (r_Lim + l_Lim) / 2;

	if(r_Lim <= l_Lim)
		return;

	k1(prod, l_Lim, m);
	k1(prod, m+1, r_Lim);
	k2(prod, l_Lim, m, r_Lim);
}


/*lista todos os produtos existentes no sistema por ordem crescente de pre?o. Se houver 2 ou mais produtos com o mesmo preco, devera imprimir esses por ordem crescente de id de produto*/
void l(int l_Lim, int r_Lim) {

	int i;

	struct Prodt prod[MAX_PRODUTOS];

	for(i = l_Lim; i <= r_Lim; i++)
		prod[i] = produtos[i];

	k1(prod, l_Lim, r_Lim);

	printf("Produtos\n");

	for(i = l_Lim; i <= r_Lim; i++)
		printf("* %s %d %d\n", prod[i].descr, prod[i].preco, prod[i].qtd);
}


/**********************  FUNCOES AUXILIARES  **********************/
/*Counting sort. As chaves podem tomar valores entre 0 e M-1. Se existirem k0 chaves com valor 0, entao ocupam as primeiras k0 posi??es do vetor final: de 0 a k0-1. */
void k3(struct Prodt output[], int pos, int idp) {

	int i, cnt[MAX_COUNT+1] = {0};
	struct Prodt new_output[MAX_UNIDADES];

	for(i = 0; i < idp; i++) {
		if((int)strlen(output[i].descr) > pos)
			cnt[(int)output[i].descr[pos]]++;

		else 
			cnt[0]++;
	}


	for(i = 1; i <= MAX_COUNT; i++)
		cnt[i] += cnt[i-1];

	for(i = idp-1; i >= 0; i--) {  /* ele comeca pelo ultimo elemento para garantir a estabilidade do algoritmo*/ 
		if((int)strlen(output[i].descr) > pos) {
			new_output[cnt[(int)output[i].descr[pos]]-1] = output[i];
			cnt[(int)output[i].descr[pos]]--;
		}

		else {
			new_output[cnt[0]-1] = output[i];
			cnt[0]--;
		}
	}

	for(i = 0; i < idp; i++){
		output[i] = new_output[i];
	}
}


/*lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o*/
/*usa o Radix Sort, e uma tecnica de classificacao que classifica os elementos primeiro agrupando os digitos individuais do mesmo valor de local*/
void L(int new_ide, int ide){

	int i, max = 0;
	struct Prodt output[MAX_UNIDADES];
	struct Encomenda enc = encomendas[new_ide];
	int idp = enc.idp;

	if(new_ide >= ide)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", new_ide);
	
	else{

		for(i = 0; i < idp; i++){
			output[i] = enc.produto[i];
			if((int)strlen(output[i].descr) > max)
				max = strlen(output[i].descr);
		}

		for(i = max-1; i >= 0; i--)
			k3(output, i, idp);

		printf("Encomenda %d\n", new_ide);

		for(i = 0; i < idp; i++)
			printf("* %s %d %d\n", output[i].descr, output[i].preco, output[i].qtd);
	}
}


/*
* Entrada de dados.
*/
int main() {
	char comando, descr[Descricao];
	int preco, peso, qtd;
	int idp = 0, new_idp, ide = 0, new_ide;


	while(1) {
		scanf("%c", &comando);
		switch(comando) {
	 		case 'a':
	 			scanf(" %[^:]:%d:%d:%d", descr, &preco, &peso, &qtd);
	 			idp = a(descr, preco, peso, qtd, idp);
	 			break;
	 		case 'q':
	 			scanf(" %d:%d", &new_idp, &qtd);
	 			q(idp, new_idp, qtd);
	 			break;
	 		case 'N':
	 			ide = N(ide);
	 			break;
	 		case 'A':
	 			scanf(" %d:%d:%d", &new_ide, &new_idp, &qtd);
	 			A(idp, new_idp, ide, new_ide, qtd);
	 			break;
	 		case 'r':
	 			scanf(" %d:%d", &new_idp, &qtd);
	 			r(idp, new_idp, qtd);
	 			break;
	 		case 'R':
	 			scanf(" %d:%d", &new_ide, &new_idp);
	 			R(ide, idp, new_ide, new_idp);
	 			break;
	 		case 'C':
	 			scanf(" %d", &new_ide);
	 			C(ide, new_ide);
	 			break;
	 		case 'p':
	 			scanf(" %d:%d", &new_idp, &preco);
	 			p(idp, ide, preco, new_idp);
	 			break;
	 		case 'E':
	 			scanf(" %d:%d", &new_ide, &new_idp);
	 			E(new_idp, new_ide, idp, ide);
	 			break;
	 		case 'm':
	 			scanf(" %d", &new_idp);
	 			m(new_idp, idp, ide);
	 			break;
	 		case 'l':
	 			l(0, idp-1);
	 			break;
	 		case 'L':
	 			scanf(" %d", &new_ide);
	 			L(new_ide, ide);
	 			break;
	 		case 'x':
	 			return 0;
	 			break;
	 		}
		}	 

	return 0;
}