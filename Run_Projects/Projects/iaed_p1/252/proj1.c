#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
definem se os limites
*/
#define MAX_INPUT 1024
#define MAX_DESCRICAO 63
#define MAX_ID 9999
#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define MAX_PESO_ENCOMENDA 200


/*
e criada uma estrutura produto
*/
typedef struct{
	int id;
	char descricao_prod[MAX_DESCRICAO];
	int preco_prod;
	int peso_prod;
	int quantidade_prod;
}produto;


/*
e criada uma estrutura encomenda
*/
typedef struct{
	int peso_encomenda;
	int preco_encomenda;
	int ie;
	int contador_produtos;
	produto lista_produtos_encomenda[MAX_PRODUTOS];
}encomenda;


/*
sao criadas duas variaveis globais para o id de um produto e id de encomenda
que vao aumentando sempre que se cria um produto e uma encomenda respetivamente
*/
int idp = 0;
int ide = 0;


/*
e criado um vetor de produtos que vai guardar todos os produtos cirados
*/
produto aux[MAX_PRODUTOS];
produto aux2[MAX_PRODUTOS];
produto lista_produtos[MAX_PRODUTOS];


/*
e criado um vetor de encomendas que vai guardar todas as encomendas
*/
encomenda lista_encomendas[MAX_ENCOMENDAS];


/*
funcao que adiciona um produto ao sistema
e usado o strtok para separar o input no que e pedido
descricao:preco:peso:quantidade
o idp aumenta em um pois o produto foi criado com sucesso
produto adicionado ao vetor de produtos
*/
void adiciona_produto(char in[MAX_INPUT]){

	produto novo_produto;
	strcpy(novo_produto.descricao_prod, strtok(in, ":"));
	novo_produto.preco_prod = atoi(strtok(NULL, ":"));
	novo_produto.peso_prod = atoi(strtok(NULL, ":"));
	novo_produto.quantidade_prod = atoi(strtok(NULL, ":"));
	novo_produto.id = idp;
	lista_produtos[idp] = novo_produto;
	printf("Novo produto %d.\n", idp);
	idp++;

}


/*
funcao que adiciona uma quantidade dada no input a quantidade ja existente
de um produto no sistema, caso seja possivel. caso contrario da erro.
*/
void adiciona_stock_produto(char in[MAX_INPUT]){

	int i = atoi(strtok(in, ":"));
	int qtd = atoi(strtok(NULL, ":"));

	if (i > idp - 1){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", i);
	}

	else {
		lista_produtos[i].quantidade_prod += qtd;
	}

}


/*
funcao que adiciona uma encomenda ao sistema
o ide aumenta em um pois a encomenda foi criada com sucesso
encomenda adicionada ao vetor de encomendas
*/
void cria_encomenda(){

	encomenda nova_encomenda;
	nova_encomenda.peso_encomenda = 0;
	nova_encomenda.preco_encomenda = 0;
	nova_encomenda.contador_produtos = 0;
	nova_encomenda.ie = ide;
	lista_encomendas[ide] = nova_encomenda;
	printf("Nova encomenda %d.\n", ide);
	ide++;

}


/*
funcao que adiciona um produto existente no vetor de produtos a uma encomenda que exista no vetor de encomendas
e feita a verificacao da existencia desse produto na encomenda.
caso o produto nao exista na encomenda e feita a adicao desse produto na encomenda
caso ele ja exista na encomenda, apenas e aumentada a sua quantidade peso e preco
quando e adicionado um produto a uma encomenda, a quantidade adicionada a encomenda tem de ser retirada
do vetor de Produtos
*/
void adiciona_produto_encomenda(char in[MAX_INPUT]){

	int id_encomenda = atoi(strtok(in, ":"));
	int id_produto = atoi(strtok(NULL, ":"));
	int qtd = atoi(strtok(NULL, ":"));
	int i;
	int flag = -1;
	encomenda a = lista_encomendas[id_encomenda];


	if (id_encomenda >= ide){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_produto, id_encomenda);
	}
	else if (id_produto >= idp){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_produto, id_encomenda);
	}
	else if (lista_produtos[id_produto].quantidade_prod < qtd){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_produto, id_encomenda);
	}
	else if ((a.peso_encomenda + (lista_produtos[id_produto].peso_prod * qtd)) > MAX_PESO_ENCOMENDA){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_produto, id_encomenda);
	}

	else {

			for (i = 0; i < a.contador_produtos; i++){

				if (a.lista_produtos_encomenda[i].id == id_produto){
					flag = i;
				}
			}

			if (flag <= -1) {

				a.lista_produtos_encomenda[a.contador_produtos].preco_prod = lista_produtos[id_produto].preco_prod;
				a.lista_produtos_encomenda[a.contador_produtos].peso_prod = lista_produtos[id_produto].peso_prod;
				strcpy(a.lista_produtos_encomenda[a.contador_produtos].descricao_prod, lista_produtos[id_produto].descricao_prod);
				a.lista_produtos_encomenda[a.contador_produtos].id = id_produto;
				a.peso_encomenda += lista_produtos[id_produto].peso_prod * qtd;
				a.preco_encomenda += lista_produtos[id_produto].preco_prod * qtd;
				a.lista_produtos_encomenda[a.contador_produtos].quantidade_prod = qtd;
				a.contador_produtos++;
				flag = -1;

			}

			else {

				a.peso_encomenda += lista_produtos[id_produto].peso_prod * qtd;
				a.preco_encomenda += lista_produtos[id_produto].preco_prod * qtd;
				a.lista_produtos_encomenda[a.contador_produtos].quantidade_prod += qtd;
				flag = -1;

		}
		lista_produtos[id_produto].quantidade_prod -= qtd;
		lista_encomendas[id_encomenda] = a;
	}
}


/*
funcao que remove stock de um produto existente no vetor de produtos, caso seja possivel
*/
void remove_stock_produto(char in[MAX_INPUT]){

	int ip = atoi(strtok(in, ":"));
	int qtd = atoi(strtok(NULL, ":"));

	if (ip > idp - 1){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", ip);
	}
	else if ((lista_produtos[ip].quantidade_prod - qtd) < 0){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, ip);
	}
	else {

		lista_produtos[ip].quantidade_prod -= qtd;

	}
}


/*
funcao que remove um produto existente numa encomenda, fazendo a verificacao da existencia do mesmo
antes de remove lo
*/
void remove_produto_encomenda(char in[MAX_INPUT]){

	int ie = atoi(strtok(in, ":"));
	int ip = atoi(strtok(NULL, ":"));
	int i, j;
	encomenda a = lista_encomendas[ie];
	int flag = -1;

	if (ie > ide - 1){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", ip, ie);
	}

	else if (ip > idp - 1){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", ip, ie);
	}

	else {

		for(i = 0; i < a.contador_produtos; i++){

			if (a.lista_produtos_encomenda[i].id == ip) {
				flag = i;
			}

		}

		if (flag != -1) {

			a.peso_encomenda -= (a.lista_produtos_encomenda[ip].peso_prod * a.lista_produtos_encomenda[ip].quantidade_prod);
			a.preco_encomenda -= (a.lista_produtos_encomenda[ip].preco_prod * a.lista_produtos_encomenda[ip].quantidade_prod);
			lista_produtos[ip].quantidade_prod += a.lista_produtos_encomenda[ip].quantidade_prod;
			for(j = flag; j < a.contador_produtos; j++){
				a.lista_produtos_encomenda[j] = a.lista_produtos_encomenda[j + 1];
			}
			a.contador_produtos--;
			flag = -1;
			lista_encomendas[ie] = a;

		}
	}
}


/*
funcao que calcula o custo de uma encomenda
*/
void calcula_custo_encomenda(char in[MAX_INPUT]){

	int id_encomenda = atoi(in);

	if (id_encomenda > ide - 1){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_encomenda);
	}

	else {

		printf("Custo da encomenda %d %d.\n", id_encomenda, lista_encomendas[id_encomenda].preco_encomenda);

	}
}


/*
funcao que altera o preco de um produto no vetor de Produtos para o preco dado no input
e caso esse produto exista numa encomenda, o preco do mesmo tambem e alterado para o preco dado no input
*/
void altera_preco_produto(char in[MAX_INPUT]){

	int ip = atoi(strtok(in, ":"));
	int preco = atoi(strtok(NULL, ":"));
	int i, e;

	if (ip > idp - 1){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", ip);
	}
	else {
		lista_produtos[ip].preco_prod = preco;
		for(i = 0; i < ide; i++){
			for(e = 0; e < lista_encomendas[i].contador_produtos; e++){
				if(lista_encomendas[i].lista_produtos_encomenda[e].id == ip){
					lista_encomendas[i].lista_produtos_encomenda[e].preco_prod = preco;
					break;
				}
			}
		}
	}
}


/*
funcao que lista a descricao e a quantidade de um produto existente numa encomenda, ambos dados no input
*/
void lista_desc_quant(char in[MAX_INPUT]){

	int ie = atoi(strtok(in, ":"));
	int ip = atoi(strtok(NULL, ":"));

	if (ie > ide - 1){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ie);
	}
	else if (ip > idp - 1){
		printf("Impossivel listar produto %d. Produto inexistente.\n", ip);
	}
	else {
		printf("%s %d.\n", lista_encomendas[ie].lista_produtos_encomenda[ip].descricao_prod, lista_encomendas[ie].lista_produtos_encomenda[ip].quantidade_prod);
	}
}


/*
funcao que percorre todas as encomendas e verifica em qual encomenda o produto dado no input tem maior quantidade
apos a verificacao o resultado da funcao e exatamente dizer em que encomenda aparece o produto dado e a sua quantidade
*/
void lista_ide_prod_max(char in[MAX_INPUT]){

	int ip = atoi(in);
	int i, e;
	int ie = 0;
	int maior = 0;

	if(ip > idp - 1){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", ip);
	}
	else {

			for(i = 0; i < ide; i++){

				for(e = 0; e < lista_encomendas[i].contador_produtos; e++){

					if (ip == lista_encomendas[i].lista_produtos_encomenda[e].id){

						if(lista_encomendas[i].lista_produtos_encomenda[e].quantidade_prod > maior){

							maior = lista_encomendas[i].lista_produtos_encomenda[e].quantidade_prod;

							if(maior == lista_encomendas[i].lista_produtos_encomenda[e].quantidade_prod){

								ie = i;

							}

						}
					}
				}
			}
	if (ip == lista_encomendas[ie].lista_produtos_encomenda[ip].id){
		printf("Maximo produto %d %d %d.\n", ip, ie, maior);
	}
	}
}


/*
e usado o algoritmo merge sort dado nas aulas teoricas nas proximas dua funcoes
para organizar os produtos da forma pedida
*/
void merge(produto a[], int l, int m, int r){

	int i, j, k;

	for(i = m + 1; i > l; i--)
		aux[i - 1] = a[i - 1];

	for(j = m; j < r; j++)
		aux[r + m - j] = a[j + 1];

	for(k = l; k <= r; k++)

		if(aux[j].preco_prod < aux[i].preco_prod || i > m)
			a[k] = aux[j--];

		else
			a[k] = aux[i++];

}


void mergesort(produto a[], int l, int r){

	int m = (r + l) / 2;

	if(r <= l)
		return;

	mergesort(a, l, m);
	mergesort(a, m + 1, r);

	merge(a, l, m, r);

}


/*
funcao que chama o algortimo merge sort para organizar os produtos
de forma crescente do preco
*/
void ordena_produtos_preco(){

	int i, e;
	produto lista_auxiliar[MAX_PRODUTOS];

	for(i = 0; i<idp; i++){
		lista_auxiliar[i] = lista_produtos[i];
	}

	mergesort(lista_auxiliar, 0, idp - 1);

	printf("Produtos\n");
	for (e = 0; e < idp; e++){
		printf("* %s %d %d\n", lista_auxiliar[e].descricao_prod, lista_auxiliar[e].preco_prod, lista_auxiliar[e].quantidade_prod);
	}
}


void merge2(produto a[], int l, int m, int r){

	int i, j, k;

	for(i = m + 1; i > l; i--)
		aux2[i - 1] = a[i - 1];

	for(j = m; j < r; j++)
		aux2[r + m - j] = a[j + 1];

	for(k = l; k <= r; k++)

		if(strcmp(aux2[j].descricao_prod, aux2[i].descricao_prod) < 0 || i > m)
			a[k] = aux2[j--];

		else
			a[k] = aux2[i++];

}


void mergesort2(produto a[], int l, int r){

	int m = (r + l) / 2;

	if(r <= l)
		return;

	mergesort2(a, l, m);
	mergesort2(a, m + 1, r);

	merge2(a, l, m, r);


}


/*
funcao que chama o algoritmo mergsort para organizar os produtos numa encomenda dada no input
de forma a organiza los por ordem alfabetica usando o strcmp
*/
void ordena_enc_alfa(char in[MAX_INPUT]){

	int ie = atoi(in);
	int i, e;
	produto lista_string[MAX_PRODUTOS];

	if(ie >= ide){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ie);
	}

	else{

		for(i = 0; i < idp; i++){
		lista_string[i] = lista_encomendas[ie].lista_produtos_encomenda[i];
		}

		mergesort2(lista_string, 0, idp - 1);

		printf("Encomenda %d\n", ie);
		for(e = 0; e < idp; e++){
			if(lista_string[e].preco_prod != 0){
				printf("* %s %d %d\n", lista_string[e].descricao_prod, lista_string[e].preco_prod, lista_string[e].quantidade_prod);
			}
		}
	}
}


/*
na funcao principal e usado o switch para alternar entre os varios comandos
e assim interagir com o sitems de logistica criado
*/
int main(){

	char in[MAX_INPUT];

	while(fgets(in, MAX_INPUT, stdin)){

		switch(in[0]){

			case 'a':
				adiciona_produto(&in[2]);
				break;
			case 'q':
				adiciona_stock_produto(&in[2]);
				break;
			case 'N':
				cria_encomenda();
				break;
			case 'A':
				adiciona_produto_encomenda(&in[2]);
				break;
			case 'r':
				remove_stock_produto(&in[2]);
				break;
			case 'R':
				remove_produto_encomenda(&in[2]);
				break;
			case 'C':
				calcula_custo_encomenda(&in[2]);
				break;
			case 'p':
				altera_preco_produto(&in[2]);
				break;
			case 'E':
				lista_desc_quant(&in[2]);
				break;
			case 'm':
				lista_ide_prod_max(&in[2]);
				break;
			case 'l':
				ordena_produtos_preco();
				break;
			case 'L':
				ordena_enc_alfa(&in[2]);
				break;
			case 'x':
				return 0;
		}
	}
	return 0;
}
