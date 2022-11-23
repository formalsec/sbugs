#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>

/*Declaracao de Varaveis*/
#define MAX_Identificador 9999 	/* Numero maximo do identificador*/
#define MAX_Descricao 63 		/* Numero maximo de caraceres da descricao*/
#define MAX_Produtos 10000 	/* Numero maximo de produtos*/
#define MAX_Encomendas 500 	/* Numero maximo de encomendas*/
#define MAX_Peso_Encomendas 200 /* Numero maximo do peso de encomendas*/

struct Detalhes_Produtos
{
	char descricao[MAX_Descricao];
	int preco;
	int peso;
	int quantidade_stock;
} produtos[MAX_Identificador];

struct Detalhes_Produtos;

int Encomendas[MAX_Encomendas][MAX_Produtos];

/*Funcao main*/
int main ()
{
	int Correr = 1, Produto = 0, Encomenda = -1 ;
	char Comando;
	while(Correr == 1)					/*Ciclo que permite correr o programa*/
	{
		Comando = getchar();			/*Captura o comando*/
		getchar();						/*Come o espaco*/

		/*a - Adiciona um novo produto ao sistema*/
		if (Comando == 'a')
		{
			scanf("%s:%d:%d:%d",produtos[Produto].descricao, &produtos[Produto].preco, &produtos[Produto].peso, &produtos[Produto].quantidade_stock); /*Eu sei que isto esta incorrecto mas nao sabia como fazer e para demonstrar o raciocinio fiz desta forma*/
			printf("Novo produto %d.\n", Produto);
			Produto++;
		}

		/*q - Adiciona stock a um produto existente no sistema*/
		if (Comando == 'q')
		{
			int produto , quantidade;
			scanf("%d:%d",&produto, &quantidade);
			if (Produto < produto)
			{
				printf("Impossivel adicionar produto %d ao stock.Produto inexistente.\n", produto);
			}
			else
			{
				produtos[produto].quantidade_stock = produtos[produto].quantidade_stock + quantidade;
			}
		}

		/*N - Cria uma nova encomenda*/
		if (Comando == 'N')
		{
			Encomenda++;
			printf("Nova encomenda %d.\n", Encomenda);
		}

		/*A - Adiciona um produto a uma encomenda. Se o produto ja existir na encomensa, adiciona a nova quantidade a quantidade existente*/
		if (Comando == 'A')
		{
			int ide, idp, qtd;
			scanf("%d:%d:%d", &ide, &idp, &qtd);
			if (Encomenda < ide)
			{
				printf("Impossivel adicionar produto %d a encomenda %d. Ecomenda inexistente.\n", idp, ide);
			}
			if (Produto < idp)
			{
				printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
			}
			if (produtos[idp].quantidade_stock < qtd)
			{
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
			}
			else
			{
				int prod = 0, peso = 0;
				while(prod <= Produto)
				{
					peso = peso + (produtos[prod].peso * Encomendas[ide][prod]);
				}
				peso = peso + (produtos[idp].peso * qtd);
				if (MAX_Peso_Encomendas < peso)
				{
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", idp, ide, MAX_Peso_Encomendas);
				}
				else
				{
					produtos[idp].quantidade_stock = produtos[idp].quantidade_stock - qtd;
					Encomendas[ide][idp]=Encomendas[ide][idp] + ide;

				}
			}
		}

		/*r - Remove stock a um produto existente*/
		if (Comando == 'r')
		{
			int produto , quantidade, qtd_final;
			scanf("%d:%d",&produto, &quantidade);
			if (Produto < produto)
			{
				printf("Impossivel remover stock do produto %d.Produto inexistente.\n", produto);
			}
			qtd_final = produtos[produto].quantidade_stock - quantidade;
			if (qtd_final <= 0)
			{
				printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insoficiente.\n", quantidade, produto);
			}
			else
			{
				produtos[produto].quantidade_stock = produtos[produto].quantidade_stock - quantidade;
			}
		}

		/*R - Remove um produto de uma encomenda*/
		if (Comando == 'R')
		{
			int ide, idp;
			scanf("%d:%d", &ide, &idp);
			if (Encomenda < ide)
			{
				printf("Impossivel adicionar produto %d a encomenda %d. Ecomenda inexistente.\n", idp, ide);
			}
			if (Produto < idp)
			{
				printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
			}
			else
			{
				produtos[idp].quantidade_stock = produtos[idp].quantidade_stock + Encomendas[ide][idp];
				Encomendas[ide][idp] = 0;
			}
		}

		/*C - Calcula o custo de uma encomenda*/
		if (Comando == 'C')
		{
			int ide, prod = 0, custo = 0;
			scanf("%d", &ide);
			if (Encomenda < ide)
			{
				printf("Impossivel calcular custo da encomenda %d. Ecomenda inexistente.\n", ide);
			}
			else
			{
				while(prod <= Produto)
				{
					custo = custo + (produtos[prod].preco * Encomendas[ide][prod]);
				}
				printf("Custo da encomenda %d %d.\n", ide, custo);
			} 
			
		}

		/*p - Altera o preco de um produto existente no sistema*/
		if (Comando == 'p')
		{
			int idp, preco;
			scanf("%d:%d", &idp, &preco);
			if (Produto < idp)
			{
				printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
			}
		}

		/*E - Lista a descricao e a quantidade de um produto numa encomenda*/
		if (Comando == 'E')
		{
			int ide, idp;
			scanf("%d:%d", &ide, &idp);
			if (Encomenda < ide)
			{
				printf("Impossivel listar encomenda %d. Ecomenda inexistente.", ide);
			}
			if (Produto < idp)
			{
				printf("Impossivel listar produto %d.Produto enexistente.", idp);
			}
			else
			{
				printf("%s %d\n", produtos[idp].descricao, Encomendas[ide][idp]);
			}
		}

		/*m - Lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas nessa situacao, devera imprimir a encomenda de menor id*/
		if (Comando == 'm')
		{
			int cont = 0, idp, total = 0, posicao = 0;
			scanf("%d", &idp);
			if (Produto < idp)
			{
				printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
			}
			while (cont != Encomenda)
			{
				if (total < Encomendas[cont][idp])
				{
					total = Encomendas[cont][idp];
					posicao = cont;
				}
				cont++;
			}
			printf("Maximo produto %d %d %d\n", idp, posicao, total);
		}

		/*l - Lista todos os produtos existentes no sistema por ordem crescente de preco. Se houver 2 ou mais produtos com o mesmo preco, devera imprimir esses por ordem decrescente de id de produto*/
		if (Comando == 'l')
		{
			/*int ciclo = 0, Minino_anterior = 0, Minimo_actual = 999999999, Lista[Produto], repeticao = 0, total = 0, id = 0;
			printf("Produtos\n");
			while (total <= Produto)
			{
				if (produtos[ciclo].preco < Minimo_actual && Minino_anterior < produtos[ciclo].preco)
				{
					Minimo_actual = produtos[ciclo].preco;
					id = ciclo;
					ciclo++;
				}
				if (ciclo == Produto && total != Produto)
				{
					ciclo = 0;
					total++;
					printf("*%s %d %d\n", produtos[id].descricao, produtos[id].preco, produtos[id].quantidade_stock);
				}
			}*/
		}

		/*L - Lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
		if (Comando == 'L')
		{
			
		}

		/*x - tremina o programa*/
		if (Comando == 'x')
		{
			Correr = 0; /*Tremina o ciclo*/
		}
	}
	return 0;
}
