#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAXPRODUTOS 10000 
#define MAXENCOMENDAS 500
#define MAXPESO 200

/*Estruturas*/ 

typedef struct {
	int idp;
	char descr[63];
	int preco;
	int peso;
	int qtd;	
} Produto;

typedef struct {
	Produto stock ;
	int ide;
} Encomenda;

/*Variaveis globais para guardar os produtos*/

static Produto stock[MAXPRODUTOS];
static Encomenda encomenda[MAXENCOMENDAS][MAXPESO];
static int PesoEncomenda[MAXENCOMENDAS];	/*Peso de cada encomenda*/
static int CustoEncomenda[MAXENCOMENDAS];	/*Custo total de cada encomenda*/
static int prodcont;						/*contador para o numero de produtos*/
static int enccont;							/*contador para o numero de encomendas*/


/*
 * ****Gerir Stocks**** 
 * a - adiciona um novo produto ao sistema
 * q - adiciona stock a um produto existente no sistema 
 * N - cria uma nova encomenda 
 * A - adiciona um produto a uma encomenda 
 * r - remove stock a um produto existente 
 * R - remove um produto de uma encomenda 
 * C - calcula o custo de uma encomenda
 * p - altera o preco de um produto existente no sistema
 * E - retorna a descricao e a quantidade de um produto numa dada encomenda
 * m - retorna o identificador da encomenda em que um dado produto ocorre mais vezes
 * l - lista todos os produtos existentes no sistema por ordem crescente de preco
 * L - lista todos os produtos de uma encomenda por ordem alfabetica da descricao
 * x - termina o programa
 * ************************* 
 */
 
 
/*Prototipos das Funcoes*/ 

void cria_produto();
void adiciona_stock();
void cria_encomenda();
void adiciona_prod_enc();
void remove_stock_prod();
void remove_prod_enc();
void calcula_custo();
void altera_preco();
void lista_prod_enc();
void max_produto();
void listar_alfa();

void um_produto(int j);

/*Inicio do codigo*/ 

int main() 
{
  
	char opcao;
	
	do{
		scanf("%c", &opcao);
		switch (opcao){
			case 'a':
				cria_produto();
				break;
			case 'q':
				adiciona_stock();
				break;
			case 'N':
				cria_encomenda();
				break;
			case 'A':
				adiciona_prod_enc();
				break;
			case 'r':
				remove_stock_prod();
				break;
			case 'R':
				remove_prod_enc();
				break;
			case 'C':
				calcula_custo();
				break;
			case 'p':
				altera_preco();
				break;
			case 'E':
				lista_prod_enc();
				break;
			case 'm':
				max_produto();
				break;
			case 'l':
				printf("Opcao l");
				break;
			case 'L':
				listar_alfa();
				break;
			case 'x':
				break; 
 
        }
 
    }while(opcao != 'x');
 
   return 0;
 
}

/*
* Opcao 'a' - Funcao para criar novos produtos no sistema
* Aumenta o contador de produtos existentes 
*/

void cria_produto(){
	
	if (prodcont < MAXPRODUTOS){

		scanf(" %[^:]:%d:%d:%d", stock[prodcont].descr, &stock[prodcont].preco, &stock[prodcont].peso, &stock[prodcont].qtd);
	
		stock[prodcont].idp = prodcont;			/*O identificador de produto vai ser igual a posicao onde o produto se encontra na array*/
	
		printf("Novo produto %d.\n", stock[prodcont].idp);

		prodcont ++;							/*Aumenta o numero de produtos existentes*/
	
	}
}

/*
* Opcao 'q' - Funcao para adicionar stock a um produto existente
* Se o produto existir
* Adiciona a quantidade nova ao parametro 'qtd' da estrutura Produto 
*/

void adiciona_stock(){
	
	int k, quantidade;
	
	scanf("%d:%d", &stock[prodcont].idp, &quantidade);
	k = stock[prodcont].idp;
	
	if (k < prodcont){
		stock[k].qtd = stock[k].qtd + quantidade;
		
	}else{
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", k);
  }
}

/*
* Opcao 'N' - Funcao para criar uma nova encomenda
* Aumenta o contador de encomendas existentes
* Coloca o peso de cada encomenda a 0
*/

void cria_encomenda(){
	
	if (enccont < MAXENCOMENDAS){
	  
		encomenda[enccont][prodcont].ide = enccont;		/*O identificador da encomenda vai ser igual a posicao onde a encomenda se encontra na array*/
		PesoEncomenda[enccont] = 0;
		printf("Nova encomenda %d.\n", encomenda[enccont][prodcont].ide);
	
		enccont ++;										/*Aumenta o numero de encomendas existentes*/
	}
}

/*
* Opcao 'A' - Funcao para adicionar um produto a uma encomenda
* Nao da erro
* Se o produto e a encomenda existirem
* Se a quantidade pedida existir em stock
* Se o peso da encomenda for menor do que 200
*/

void adiciona_prod_enc(){
	
	int i, j, quantidade;
	
	scanf("%d:%d:%d", &encomenda[enccont][prodcont].ide, &stock[prodcont].idp, &quantidade);
	i = encomenda[enccont][prodcont].ide;
	j = stock[prodcont].idp;

	if (i < enccont){
		if (j < prodcont){
			if (quantidade <= stock[j].qtd){			
				if (PesoEncomenda[i] + (stock[j].peso * quantidade) <= MAXPESO){	
					PesoEncomenda[i] = PesoEncomenda[i] + (stock[j].peso * quantidade);			/*O peso da encomenda vai ser igual ao peso dos produtos * as suas quantidades*/
					CustoEncomenda[i] = CustoEncomenda[i] + (stock[j].preco * quantidade);		/*O custo da encomenda vai ser igual ao preco dos produtos * as suas quantidades*/
					strcpy(encomenda[i][j].stock.descr, stock[j].descr);						/*A descricao do produto fica igual na encomenda*/
					encomenda[i][j].stock.preco = stock[j].preco;								/*O preco do produto fica igual na encomenda*/
					encomenda[i][j].stock.qtd = encomenda[i][j].stock.qtd + quantidade;			/*A quantidade do produto na encomenda vai aumentar*/
					stock[j].qtd = stock[j].qtd - quantidade;									/*A quantidade do produto no stock vai diminuir*/

				}else{
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", j, i);}
			}else{
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", j, i);}
		}else{
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", j, i);}
	}else{
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", j, i);}
}

/*
* Opcao 'r' - Funcao para remover stock de um produto
* Se o produto existir
* Remove a quantidade ao parametro 'qtd' da estrutura Produto
*/

void remove_stock_prod(){
		
	int k, quantidade;
	
	scanf("%d:%d", &stock[prodcont].idp, &quantidade);
	k = stock[prodcont].idp;
	
	if (k < prodcont){
		if (quantidade <= stock[k].qtd){
			stock[k].qtd = stock[k].qtd - quantidade;
		
		}else{
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, k);}
	}else{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", k);}
}


/*
* Opcao 'R' - Funcao para remover um produto a uma encomenda
* Coloca a quantidade do produto j a 0 na encomenda i
*/

void remove_prod_enc(){
	
	int i, j;
	
	scanf("%d:%d", &encomenda[enccont][prodcont].ide, &stock[prodcont].idp);
	i = encomenda[enccont][prodcont].ide;
	j = stock[prodcont].idp;

	if (i < enccont){
		if (j < prodcont){
			PesoEncomenda[i] = PesoEncomenda[i] - (stock[j].peso * encomenda[i][j].stock.qtd);			/*O peso da encomenda vai diminuir ao remover-se o produto*/
			CustoEncomenda[i] = CustoEncomenda[i] - (stock[j].preco * encomenda[i][j].stock.qtd);		/*O custo da encomenda vai diminuir ao remover-se o produto*/
			strcpy(encomenda[i][j].stock.descr, stock[j].descr);
			encomenda[i][j].stock.preco = stock[j].preco;
			stock[j].qtd = stock[j].qtd + encomenda[i][j].stock.qtd;									/*O stock do produto removido a encomenda vai aumentar*/
			encomenda[i][j].stock.qtd = 0;																/*A quantidade do produto na encomenda vai passar a 0*/
		}else{
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", j, i);}
	}else{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", j, i);}
}

/*
* Opcao 'C' - Funcao para calcular o custo de uma encomenda
*/

void calcula_custo(){
	
	int i;
	
	scanf("%d", &encomenda[enccont][prodcont].ide);
	i = encomenda[enccont][prodcont].ide;
	
	if (i < enccont){
		printf("Custo da encomenda %d %d.\n", i, CustoEncomenda[i]);
	}else{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", i);}
}

/*
* Opcao 'p' - Funcao para alterar o preco de um dado produto existente no sistema
*/

void altera_preco(){
	
	int j, i, novopreco;
	
	scanf("%d:%d", &stock[prodcont].idp, &novopreco);
	j = stock[prodcont].idp;
	i = encomenda[enccont][prodcont].ide; 
	
	if (j < prodcont){
		CustoEncomenda[i] = CustoEncomenda[i] - stock[j].preco * encomenda[i][j].stock.qtd;
		stock[j].preco = novopreco;
		CustoEncomenda[i] = CustoEncomenda[i] +  stock[j].preco * encomenda[i][j].stock.qtd;
	}else{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", j);}
}

/*
* Opcao 'E' - Funcao para indicar o produto dado numa dada encomenda
* Procura o produto na encomenda e faz print da sua descricao e quantidade na encomenda
*/

void lista_prod_enc(){
	
	int i, j;
	
	scanf("%d:%d", &encomenda[enccont][prodcont].ide, &stock[prodcont].idp);
	i = encomenda[enccont][prodcont].ide;
	j = stock[prodcont].idp;

	if (i < enccont){
		if (j < prodcont){
			printf("%s %d.\n", encomenda[i][j].stock.descr, encomenda[i][j].stock.qtd);
		}else{
			printf("Impossivel listar produto %d. Produto inexistente.\n",  j);}
	}else{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", i);}
}

/*
* Opcao 'm' - Funcao para indicar em qual encomenda um dado produto aparece mais vezes
* So imprime se a quantidade maior for diferente de 0
*/

void max_produto(){
	
	int i, j, max, k;
	
	scanf("%d", &stock[prodcont].idp);
	i = encomenda[enccont][prodcont].ide;
	j = stock[prodcont].idp;
	max = 0;
	k = 0;

	if (j >= prodcont){
	printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",  j);
	
	}else{		
		for (i = 0; i < enccont; i++){												/*Vai correr por todas as encomendas*/
			if (encomenda[i][j].stock.qtd > max){
				max = encomenda[i][j].stock.qtd;									/*Guarda o valor maximo*/
				k = i;}}															/*Guarda o identificar da encomenda onde se encontra o maximo do produto*/
		if (encomenda[k][j].stock.qtd != 0){
			printf("Maximo produto %d %d %d.\n", j, k, max);}
	
	}
}

/*
* Opcao 'L' - Funcao para listar os produtos de uma dada encomenda alfabeticamente
* Incompleto - So funciona o erro e nao imprimir quando a quantidade for 0
*/

void listar_alfa(){
	
	int i, j;
	
	scanf("%d", &encomenda[enccont][prodcont].ide);
	j = stock[prodcont].idp;
	i = encomenda[enccont][prodcont].ide;

	if (i < enccont){
		
		printf("Encomenda %d\n", i);
		if (encomenda[i][j].stock.qtd != 0){
			for (j = 0; j < prodcont; j++){
				um_produto(j);
				printf("\n");
			}
		}		

	}else{		
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",  i);}				
}

/*
* Funcao auxiliar
* Imprime so um produto para ser usada depois nas funcoes de listagem
*/

void um_produto(int j){
	
	int i;
	i = encomenda[enccont][prodcont].ide;
	
	if (j >= 0 && j < prodcont){
		printf("* %s %d %d",
		encomenda[i][j].stock.descr,
		encomenda[i][j].stock.preco,
		encomenda[i][j].stock.qtd);}
}