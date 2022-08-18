#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "radix.h"

/*Valores maximos de produtos, encomendas e peso de uma encomenda*/
#define MAX_PROD 10000 
#define MAX_ENC 500
#define MAX_WEIGHT 200


/*estrutura para um produto*/
typedef struct Produto
{
	char descricao[63];
	int preco, peso, qtd, idp;
} Produto;


/*estrutura para uma encomenda*/
typedef struct Encomenda
{
	int counterPE;
	int ide, peso_total;
	int estado;						/*variavel que indica se uma encomenda esta ativa*/
	int qtds[MAX_WEIGHT], idps[MAX_WEIGHT];

} Encomenda;

/*Arrays onde irao ser guardados cada produto e cada encomenda*/
Produto produtos[MAX_PROD];
Encomenda encomendas[MAX_ENC];

/*counterP- numero de produtos existentes
  counterE- numero de encomendas existentes*/
int counterP = 0, counterE = 0;

/*
	funcao (int) find_prod:
	-Argumentos: identificador da encomenda e identificador do produto da encomenda
	-itera por todos os produtos dentro da encomenda e verifica se o id dado existe
	-Retorna o indice do produto dentro da lista de idps da encomenda, caso nao exista 
	retorna a constante MAX_WEIGHT
*/
int find_prod(int ide, int idp)
{
	int i;
	for(i=0; i < encomendas[ide].counterPE +1; i++)
	{
		if(!encomendas[ide].counterPE)
			return MAX_WEIGHT;
		else if(i == encomendas[ide].counterPE)
			return MAX_WEIGHT;
		else if(encomendas[ide].idps[i] == idp)
			break;
	}
	return i;
}

/*
	funcao (void) a:
	-Argumentos: descricao, preco, peso e quantidade do produto
	-Adiciona valores das caracteristicas dum produto ao proximo produto a ser adicionado
	-Retorna para o standard output "Novo produto " seguido do numero do produto
*/
void a(char descricao[], int preco, int peso, int qtd)
{	
	strcpy(produtos[counterP].descricao, descricao);
	produtos[counterP].preco = preco;
	produtos[counterP].peso = peso;
	produtos[counterP].qtd = qtd;
	produtos[counterP].idp = counterP; 	
	printf("Novo produto %d.\n", counterP);
	counterP++;
}

/*
	funcao (void) q:
	-Argumentos: identificador e quantidade a adicionar do produto
	-Incrementa uma dada quantidade dum produto ao stock existente desse produto
	-Retorna erro se:
		-O produto nao existir
*/
void q(int idp, int qtd)
{
	if(produtos[idp].descricao[0] == '\0')
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	else
		produtos[idp].qtd += qtd;	 
}

/*
	funcao (void) N:
	-Argumentos: 
	-Adiciona valores das caracteristicas duma encomenda a proxima encom,encomenda a ser adicionada
	-Retorna para o standard output "Novo encomenda " seguido do numero da encomenda
*/
void N()
{

	encomendas[counterE].counterPE = 0;
	encomendas[counterE].estado = 1;   /*variavel de estado passa para o valor 1 que indica tautologicamente True*/
	encomendas[counterE].peso_total = 0;
	encomendas[counterE].ide = counterE;
	printf("Nova encomenda %d.\n", counterE);
	counterE++;
}

/*
	funcao (void) A:
	-Argumentos: identificador da encomenda (ide), indetificador do produto dentro da encomenda (idp),
	quantidade do produto a meter na encomenda (qtd)
	- funcoes auxiliares: find_prod
	-Incrementa o peso da encomenda, adiciona o idp e qtd a lista de idps e de qtds respetivamente
	-Retorna erro se:
		-a encomenda nao exisitir
		-o produto nao exisitir
		-nao existir stock suficiente do produto
		-com o peso adicionado exceder o peso maximo duma encomenda
*/
void A(int ide, int idp, int qtd)
{
	int i;
	/*Verificacoes*/
	if(!encomendas[ide].estado)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if(produtos[idp].descricao[0] == '\0')
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else if(produtos[idp].qtd < qtd)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	else if((encomendas[ide].peso_total + produtos[idp].peso * qtd) > MAX_WEIGHT)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);

	/*Adicionar produto caso ele nao exista na encomenda*/
	else if(find_prod(ide, idp) == MAX_WEIGHT)
	{
		encomendas[ide].peso_total += produtos[idp].peso * qtd;
		encomendas[ide].idps[encomendas[ide].counterPE] = idp;
		encomendas[ide].qtds[encomendas[ide].counterPE] = qtd;
		encomendas[ide].counterPE++;
		produtos[idp].qtd -= qtd;
	}

	/*adicionar produto caso ele exista na encomenda*/
	else
	{
		i = find_prod(ide, idp);
		encomendas[ide].qtds[i] += qtd;
		encomendas[ide].peso_total += produtos[idp].peso * qtd;
		produtos[idp].qtd -= qtd;
	}
	
}

/*
	funcao (void) r:
	-Argumentos: identificador do produto, quantidade do produto a retirar
	-Decrementa uma da quantidade do stock desse produto
	-Retorna erro se:
		-o produto nao exisitir
		-nao existir stock suficiente do produto para remover
*/
void r(int idp, int qtd)
{
	/*Verificacoes*/
	if(produtos[idp].descricao[0] == '\0')
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	else if(produtos[idp].qtd < qtd)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
	else
		produtos[idp].qtd -= qtd;
}

/*
	funcao (void) R:
	-Argumentos: identificador da encomenda (ide), identificador do produto (idp)
	-Funcoes auxiliares: find_prod
	-Retira o produto idp da encomenda ide
	-Retorna erro se:
		-a encomenda nao existir
		-o produto nao exisitir
*/
void R(int ide, int idp)
{
	int posicao, i;

	if(!encomendas[ide].estado)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

	
	else if(produtos[idp].descricao[0] == '\0')
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	
	else if(find_prod(ide, idp) != MAX_WEIGHT)
	{
		i = find_prod(ide, idp);

		produtos[idp].qtd += encomendas[ide].qtds[i];
		encomendas[ide].peso_total -= produtos[idp].peso * encomendas[ide].qtds[i]; 
		for(posicao = i; posicao < MAX_WEIGHT; posicao++){                                                
			encomendas[ide].idps[posicao] = encomendas[ide].idps[posicao+1];
			encomendas[ide].qtds[posicao] = encomendas[ide].qtds[posicao+1];
			
		}
		encomendas[ide].counterPE--;
	}
}

/*
	funcao (void) C:
	-Argumentos: identificador da encomenda (ide)
	-Calcula o custo total de uma encomenda
	-Retorna para o standard output "Custo da encomenda" seguido do ide e do custo total
	-Retorna erro se:
		-a encomenda nao existir
*/
void C(int ide)
{
	int custo_total=0, i;
	if(!encomendas[ide].estado)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	else
	{
		for(i=0; i<encomendas[ide].counterPE; i++)
			custo_total += produtos[encomendas[ide].idps[i]].preco * encomendas[ide].qtds[i];

		printf("Custo da encomenda %d %d.\n", ide, custo_total);

	}	
}

/*
	funcao (void) p:
	-Argumentos: identificador do produto, valor de preco a alterar
	-Altera o preco de um dado produto
	-Retorna erro se:
		-o produto nao exisitir
*/
void p(int idp, int preco)
{
	if(produtos[idp].descricao[0] == '\0')
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	else
		produtos[idp].preco = preco;
}

/*
	funcao (void) E:
	-Argumentos: identificador da encomenda (ide), identificador do produto (idp)
	-Funcoes auxiliares: find_prod
	-Encontrar descricao e quantidade de um dado produto na encomenda
	-Retorna para o standard output a descricao e qauntidade na encomenda ide do produto idp
	-Retorna erro se:
		-a encomenda nao exisitir
		-o produto nao exisitir
*/
void E(int ide, int idp)
{
	int i, q;

	if(!encomendas[ide].estado)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

	else if(produtos[idp].descricao[0] == '\0')
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);

	else
	{
		i = find_prod(ide, idp);
		if(i == MAX_WEIGHT)
			q=0;
		else
			q = encomendas[ide].qtds[i];
		
		printf("%s %d.\n", produtos[idp].descricao, q);
	}
}

/*
	funcao (void) m:
	-Argumentos: identificador do produto (idp)
	-Funcoes auxiliares: find_prod
	-Encontra a encomenda em que existe uma maior quantidade do produto idp
	-Retorna para o standard output "Maximo produto " seguido do idp, o indice da encomenda  e a quantidade maxima 
	-Retorna erro se:
		-o produto nao exisitir
*/
void m(int idp)
{
	int i, max_qtd = 0, max_index=-1, find;

	/*verificacoes*/
	if(produtos[idp].descricao[0] == '\0')
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);

	/*listagem do produto*/
	else{
		for(i = 0; i<MAX_ENC; i++)
		{
			find = find_prod(i, idp);
			if(find != MAX_WEIGHT && max_qtd < encomendas[i].qtds[find])
			{
					max_qtd = encomendas[i].qtds[find_prod(i, idp)];
					max_index = i;
			}
		}
		if(max_index != -1){
			printf("Maximo produto %d %d %d.\n", idp, max_index, max_qtd);
		}
	}
}

/*
	funcao (void) l:
	-Argumentos:
	-Funcoes auxiliares: radix_sort
	-lista todos os produtos por ordem crescente de preco desenpatando pela ordem crescente de identificador
	-Retorna para o standard output "Produtos" seguido de uma lista de "* "  com a descricao, preco e quantidade 
*/
void l()
{
	int precos[MAX_PROD][2], i;
	for(i=0; i < counterP; i++)
	{
		precos[i][0] = i;
		precos[i][1] = produtos[i].preco;
	}
	radixSort(precos, counterP);
	printf("Produtos\n");
	for(i=0; i < counterP; i++)
		printf("* %s %d %d\n", produtos[precos[i][0]].descricao, produtos[precos[i][0]].preco, produtos[precos[i][0]].qtd);
}

/*
	funcao (void) L:
	-Argumentos: identificador da encomenda (ide)
	-lista todos os produtos da encomenda ide por ordem alfabetica segundo as descricoes
	-Retorna para o standard output "Encomenda " do ide e de uma lista de "* "  com a descricao, preco
	e quantidade do produto na encomenda ide
*/
void L(int ide)
{
	int i, j;
	Produto aux;
	Produto produtos_aux[MAX_WEIGHT];
	
	if(!encomendas[ide].estado)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else
	{
		printf("Encomenda %d\n",ide);
		for(i=0; i<encomendas[ide].counterPE; i++){
			produtos_aux[i] = produtos[encomendas[ide].idps[i]];
			produtos_aux[i].qtd = encomendas[ide].qtds[i];
			strcpy(produtos_aux[i].descricao, produtos[encomendas[ide].idps[i]].descricao);
		}
		
		for(i=0;i<encomendas[ide].counterPE;i++)
        	for(j=i+1;j<encomendas[ide].counterPE;j++)
			{
        		if(strcmp(produtos_aux[i].descricao,produtos_aux[j].descricao)>0)
				{
            		aux = produtos_aux[i];
            		produtos_aux[i] = produtos_aux[j];
            		produtos_aux[j] = aux;
         		}
      		}
		for(i=0; i< encomendas[ide].counterPE; i++)
			printf("* %s %d %d\n", produtos_aux[i].descricao, produtos_aux[i].preco, produtos_aux[i].qtd);
	}	
}

int main()
{
	char command, desc[63];
	int i, execucao=1, preco, weight, qtd, idp, ide;

	while(execucao)
	{
		command = getchar();
		for(i=0; i < 120; i++)
		{
			switch(command)
			{
				case 'a':
					getchar();
					scanf("%[^:]:%d:%d:%d]", desc, &preco, &weight, &qtd);
					a(desc, preco, weight, qtd);
					break;

				case 'q':
					getchar();
					scanf("%d:%d", &idp, &qtd);
					q(idp, qtd);
					break;

				case 'N':
					N();
					break;

				case 'A':
					getchar();
					scanf("%d:%d:%d", &ide, &idp, &qtd);
					A(ide, idp, qtd);
					break;

				case 'r':
					getchar();
					scanf("%d:%d", &idp, &qtd);
					r(idp, qtd);
					break;

				case 'R':
					getchar();
					scanf("%d:%d", &ide, &idp);
					R(ide, idp);
					break;

				case 'C':
					getchar();
					scanf("%d", &ide);
					C(ide);
					break;

				case 'p':
					getchar();
					scanf("%d:%d", &idp, &preco);
					p(idp, preco);
					break;

				case 'E':
					getchar();
					scanf("%d:%d", &ide, &idp);
					E(ide, idp);
					break;

				case 'm':
					getchar();
					scanf("%d", &idp);
					m(idp);
					break;

				case 'l':
					l();
					break;

				case 'L':
					getchar();
					scanf("%d", &ide);
					L(ide);
					break;

				case 'x':
					return 0;
			}
			break;
		}
	}
	return 0;	
}