#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define IDP_MAX 10000  /* Numero maximo de produtos que podem existir */
#define STRING_MAX 63  /* Tamanho maximo permitido para strings */
#define IDE_MAX 500    /* Numero maximo de encomendas que podem existir */
#define PESO_MAX 200   /* Peso maximo de cada encomenda */


/* Estou a criar uma estrutura produto com os campos necessarios para guardar informacoes sobre um determinado produto */
struct produto{
	int idp; /* Identificador de produto */
	char descricao[STRING_MAX];
	int preco;
	int peso;
	int qtd;  /* Quantidade de produto */
};

/* Vetor de estruturas (produto) */
struct produto produtos[IDP_MAX];
/* Variavel global que que guarda o indice atual de cada produto */
int indice_produto_atual;

/* Estou a criar uma estrutura encomenda com os campos necessarios para guardar informacoes sobre uma determinada encomenda */
struct encomenda{
	int ide;   /* Identificador de encomenda */
	struct produto prod;  /*  Dentro da estrutura encomenda ha a estrutura produto pois uma encomenda eh um conjunto de produtos */
};

/* Tabela bidimensional de estruturas (encomenda) */
struct encomenda encomendas[IDE_MAX][PESO_MAX];
/* Variavel global que que guarda o indice atual de cada encomenda */
int indice_encomenda_atual;

/* Aqui estou a pre definir os identificadores de todas as encomendas a -5 para indicar que ainda nao foram inicializadas */
void inicializar_encomendas(){
	int a,b;							
	for (a = 0; a < 500; a++){
		for (b = 0; b < 200; b++){
			encomendas[a][b].ide = -5;
		}
	}

}

void comando_a(){

	scanf("%[^:]:%d:%d:%d", produtos[indice_produto_atual].descricao, &produtos[indice_produto_atual].preco, &produtos[indice_produto_atual].peso, &produtos[indice_produto_atual].qtd);
	printf("Novo produto %d.\n", indice_produto_atual);
	indice_produto_atual++;
}

void comando_q(){
	int indice_aux;
	int qtd;
	scanf("%d:%d", &indice_aux, &qtd);
	if (strcmp(produtos[indice_aux].descricao, "") == 0)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", indice_aux);
	else
		produtos[indice_aux].qtd += qtd;
}

void comando_N(){
	int i;
	for (i = 0; i < 200; i++){
		encomendas[indice_encomenda_atual][i].ide = indice_encomenda_atual;
	}
	printf("Nova encomenda %d.\n", indice_encomenda_atual);
	indice_encomenda_atual++;

}

void comando_A(){
	int ide, idp, qtd;
	scanf("%d:%d:%d", &ide, &idp, &qtd);
	if (encomendas[ide][0].ide == -5)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if (strcmp(produtos[idp].descricao, "") == 0)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else if (qtd > produtos[idp].qtd)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
}


void comando_r(){
	int idp, qtd;
	scanf("%d:%d", &idp, &qtd);
	if (strcmp(produtos[idp].descricao, "") == 0)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	else if (qtd > produtos[idp].qtd)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, qtd);
	produtos[idp].qtd -= qtd;


}

void comando_R(){
	int ide, idp;
	scanf("%d:%d", &ide, &idp);
	if (encomendas[ide][0].ide == -5)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if (strcmp(produtos[idp].descricao, "") == 0)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
}

void comando_C(){
	int ide, i, custo = 0 ;
	scanf("%d", &ide);
	if (encomendas[ide][0].ide == -5)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	for (i = 0; i < 200; i++){
		custo += encomendas[ide][i].prod.preco * encomendas[ide][i].prod.qtd;
	}
	printf("Custo da encomenda %d %d.\n", ide, custo);

}

void comando_p(){
	int idp, preco;
	scanf("%d:%d", &idp, &preco);
	if (strcmp(produtos[idp].descricao, "") == 0)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	produtos[idp].preco = preco;

}

void comando_E(){
	int ide, idp;
	scanf("%d:%d", &ide, &idp);
	if (encomendas[ide][0].ide == -5)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else if (strcmp(produtos[idp].descricao, "") == 0)
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
}

void comando_m(){
	int idp;
	scanf("%d", &idp);
	if (strcmp(produtos[idp].descricao, "") == 0)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
}

void comando_l(){

}

void comando_L(){


}



/* Le os comandos do utilizador e chama funcoes mediante o comando fornecido */
int main(){
	int c;

	inicializar_encomendas();

	c = getchar();
	while (c != EOF){
		switch(c){
			case 'a':
				comando_a();
				break;

			case 'q':
				comando_q();
				break;

			case 'N':
				comando_N();
				break;

			case 'A':
				comando_A();
				break;

			case 'r':
				comando_r();
				break;

			case 'R':
				comando_R();
				break;

			case 'C':
				comando_C();
				break;

			case 'p':
				comando_p();
				break;

			case 'E':
				comando_E();
				break;

			case 'm':
			 	comando_m();
			 	break;

			case 'l':
				comando_l();
				break;

			case 'L':
				comando_L();
				break;

			case 'x':
				exit(0);




		}
		c = getchar();
	}



	return 0;
}