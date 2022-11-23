#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include "proj1.h"

int main(void)
{
	PRODUTO produtos[PRODUTOS_MAX];
	ENCOMENDA encomendas[ENCOMENDAS_MAX];
	char descricao[63];
	int numero_produtos = 0;
	int peso, preco, qtd;
	int idp = 0,ide = 0;
	char comando;
	int flag = 0;
	int i, j;
	int numero_encomendas = 0;

	

	for(i = 0; i < PRODUTOS_MAX; i++)
		produtos[i].idp = -1;
	for(i = 0; i < ENCOMENDAS_MAX; i++)
		encomendas[i].ide = -1;
	while(1)
	{
		comando = getchar();
		switch(comando)

		/*
		o switch separa os comandos
		*/

		{
			case 'a': /*done*/
				getchar();
				scanf("%[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);
				produtos[numero_produtos] = add_produto(descricao, preco, peso, qtd, numero_produtos);
				numero_produtos++;

				break;


			case 'q': /*done*/
				getchar();
				scanf("%d:%d", &idp, &qtd);

				if (produtos[idp].idp == -1)

					printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);

				else
					produtos[idp] = add_stock(produtos[idp], qtd);

				break;


			case 'N': /*done*/
				getchar();
				encomendas[numero_encomendas] = create_encomenda(numero_encomendas);
				numero_encomendas++;

				break;


			case 'A': /*done*/
				getchar();
				scanf("%d:%d:%d", &ide, &idp, &qtd);

				if ((produtos[idp].idp == -1) || (encomendas[ide].ide == -1))
				{
					if (encomendas[ide].ide == -1)

						printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
					else

						printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp,  ide);

					flag=1;
				}

				else
					encomendas[ide] = add_encomenda(encomendas[ide], qtd, produtos[idp], &flag, &j);

				if (flag == 0)
					produtos[idp] = remove_stock(produtos[idp], qtd);
				flag = 0;

				break;


			case 'r': /*done*/
				getchar();
				scanf("%d:%d", &idp, &qtd);

				if (produtos[idp].idp == -1)
 
					printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
				else
					produtos[idp] = remove_stock(produtos[idp], qtd);

				break;


			case 'R': /*done*/
				getchar();
				scanf("%d:%d", &ide, &idp);

				if ((produtos[idp].idp == -1) || (encomendas[ide].ide == -1))
				{
					if (encomendas[ide].ide == -1)

						printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
					else

						printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
					flag = 1;
				}

				else
					encomendas[ide] = retira_produto(encomendas[ide], produtos[idp], &flag, &qtd);

				if (flag == 0)
					produtos[idp] = add_stock(produtos[idp], qtd);
				flag = 0;

				break;

			case 'C': /*done*/
				getchar();
				scanf("%d",&ide);

				if (encomendas[ide].ide == -1)
					printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
				else
					calcula_custo(encomendas[ide],produtos);
				break;

			case 'p': /*done*/
				getchar();
				scanf("%d:%d",&idp,&preco);

				if (produtos[idp].idp == -1)
					printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
				else
					produtos[idp]=altera_preco(produtos[idp],preco);

				break;

			case 'E':
				getchar();
				scanf("%d:%d", &ide, &idp);

				if ((produtos[idp].idp == -1)||(encomendas[ide].ide == -1))
				{
					if (encomendas[ide].ide == -1)

						printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
					else

						printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
				}

				else{
					for(j=0; j < 200||encomendas[ide].produto[j] != idp; j++);
					if(encomendas[ide].produto[j] == idp)
						listar_encomenda(encomendas[ide],j,produtos);
				}
				break;

			case 'm':
				getchar();
				scanf("%d", &idp);

				if (produtos[idp].idp == -1)
					printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
				else
						encomenda_maior_produto(encomendas,idp);
				break;

			case 'x': /*done*/

				return 0;

				break;
		}
	}
	return 0;
}

/*
ARGUMENTOS: uma descricao para o produto com o maximo de 63 caracteres, um preco maior que zero,
um peso mior que zero, a quantidade em stock que sera maior ou igual a zero, e um numero para identificar o produto

OBJETIVO: adicionar um novo produto ao sistema
*/

PRODUTO add_produto(char descricao[63], int preco, int peso, int qtd, int numero_produto)
{
	PRODUTO item;
	strcpy (item.descricao, descricao);
	item.preco = preco;
	item.peso = peso;
	item.qtd = qtd;
	item.idp = numero_produto;

	printf("Novo produto %d.\n", numero_produto);

	return item;
}

/*
ARGUMENTOS: o identificador do produto e a quantidade que pretende adicionar
OBJETIVO: adicionar stock a um produto  existente no sistema se existir algum produto com esse identificador
*/

PRODUTO add_stock(PRODUTO item, int stock)
{
	item.qtd = item.qtd + stock;

	return item;
}
/*
OBJETIVO: criar uma nova encomenda com um ide (um identificador da encomenda)

sendo que uma encomenda e um conjuntoo de produtos

vao existir no maximo 500 encomendas numeradas de 0 a 499

em cada encomend existem no maximo 200 unidades de peso
*/

ENCOMENDA create_encomenda(int numero_encomenda)
{
	ENCOMENDA encomenda;
	int i;
	encomenda.ide = numero_encomenda;
	encomenda.peso = 0;
	for(i = 0; i < 200; i++)
	{
		encomenda.qtd[i] = 0;
		encomenda.produto[i] = -1;
	}

	printf("Nova encomenda %d.\n", encomenda.ide);

	return encomenda;
}

/*
ARGUMENTOS: o identificador da encomenda (ide), o identificador do produto (idp) e a quantidade do produto que se pretende adicionar na encomenda
OBEJTIVOS: adicionar um produto a uma encomenda e se o produto ja existir adiciona-se uma quantidade a quantidade ja existente

So adiciona um produto a uma encomenda se existir quantidade suficiente em stock 
e se o peso da encomend nao exceder as 200 unidades de peso

So adiciona um produto  uma encomenda se o identificdor (ide) da encomenda existir 
e o identificador (idp) do produto a adicionr tambem existir

*/

ENCOMENDA add_encomenda(ENCOMENDA encomenda, int qtd, PRODUTO produto, int* flag, int *i)
{
	if(produto.qtd < qtd)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",produto.idp, encomenda.ide);
		*flag = 1;
	}
	else if((encomenda.peso+((produto.peso)*qtd)) > 200)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",produto.idp, encomenda.ide);
		*flag = 1;
	}
	else{
		for(*i = 0; *i < 200; *i += 1){
			if((encomenda.produto[*i] == -1)||(encomenda.produto[*i]==produto.idp))
			{
				encomenda.produto[*i] = produto.idp;
				encomenda.qtd[*i] += qtd;
				encomenda.peso += (qtd*produto.peso);
				break;
			}
		}
	}

	return encomenda;
}

/*
ARGUMENTOS: o idp (identificador) do produto ao que se que remover stock e a quantidade de stock que se pretende retirar a esse produto

OBJETIVO: remover stock a um produto existente

so ira remover stock ao produto se esse produto existir, se o idp do produto existir
e se houver quantidade em stock desse produto suficiente para se remover o que se pretender remover
*/


PRODUTO remove_stock(PRODUTO item, int stock)
{
	if (item.qtd < stock)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock,item.idp);
	else
		item.qtd -= stock;

	return item;
}

/*
ARGUMENTOS: o identificador quer do produto que se pretende retirar quer da especifica encomenda da qual se pretende retirar o produto em questao
idp e ide respetivamente

OBJETIVO: remover produto de uma encomenda caso esse produto e essa encomenda existirem, caso ambos os identificadores quer do produto quer da encomenda existam

*/

ENCOMENDA retira_produto(ENCOMENDA encomenda, PRODUTO produto, int* flag, int *qtd)
{
	int i;

	for(i = 0; (i < 200); i++)
		if(encomenda.produto[i]==produto.idp)
		{
			encomenda.produto[i] = -1;
			encomenda.peso -= (encomenda.qtd[i] * produto.peso);
			*qtd = encomenda.qtd[i];
			encomenda.qtd[i] = 0;

			return encomenda;
		}
	*flag = 1;

	return encomenda;
}

/*
OBJETIVO: Calcular o custo total de uma encomenda introduzindo so o identifcador da encomenda que se pretende calcular o custo 

so e calculado o custo das encomendas que existirem

*/


void calcula_custo(ENCOMENDA encomenda, PRODUTO produtos[PRODUTOS_MAX])
{
	int preco = 0;
	int i;
	for(i = 0; i < 200; i++)
	{
		preco = preco + (encomenda.qtd[i] * produtos[encomenda.produto[i]].preco);
	}
	printf("Custo da encomenda %d %d.\n", encomenda.ide, preco);

	return;
}

/*
ARGUMENTOS: o identificador do produto e o preco

OBJETIVO: alterar o preco de um produto que ja exista no sistema

so da para alterar o preco a um produto que ja exista no sistema
*/


PRODUTO altera_preco(PRODUTO item, int novo_preco)
{
	item.preco = novo_preco;

	return item;
}


/*
ARGUMENTOS: os identificadores da encomenda e do produto

OBJETIVO: lista a descricao e a quantidade de um produto numa encomenda
*/


void listar_encomenda(ENCOMENDA encomenda, int idp, PRODUTO produtos[PRODUTOS_MAX])
{
	printf("%s %d.\n", produtos[encomenda.produto[idp]].descricao,encomenda.qtd[idp] );

	return;

}

/* 
dando o identificador (argumento) do produto devera cumprir o objetivo

 OBJETIVO: listar o identificador da encomenda em que o produto dado ocorre mais vezes 
caso existam 2 ou mais encomendas com o determinado produto exatamente na mesma quantidade, 
devera imprimir a encomenda de menor de menor id (numero de identificacao)

*/

void encomenda_maior_produto(ENCOMENDA encomendas[ENCOMENDAS_MAX], int idp)
{
	int i, j;
	int ide, qtd = 0;

	for(i=0; i < ENCOMENDAS_MAX; i++)
	{
		for(j = 0; j < 200; j++)
		{
			if(encomendas[i].produto[j] == idp)
			{
				if(encomendas[i].qtd[j] > qtd)
				{
					qtd=encomendas[i].qtd[j];
					ide = i;
				}
				break;
			}
		}
	}

	printf("Maximo produto %d %d %d.\n", idp, ide, qtd);

	return;
}
