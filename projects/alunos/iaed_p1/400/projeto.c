#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_DESCRIPTION 64
#define MAX_PRODUCTS 10000
#define MAX_ORDERS 500
#define MAX_PRODS_E 200

/*ESTRUTURAS*/

/*Estrutura Produto*/

typedef struct Produto
{
	int idp;
	int preco;
	int peso;
	int qtd;
	char descricao[MAX_DESCRIPTION];

}Produto;

/*Estrutura Stock_Encomenda cujo contem o numero identificador de cada produto e a sua respetiva quantidade numa dada encomenda*/

typedef struct Stock_Encomenda
{
	int prod;
	int qtd;

}Stock_Encomenda;

/*Estrutura Encomenda*/

typedef struct Encomenda
{	
	int ide;
	int peso;
	int n_prods;
	Stock_Encomenda prods_encomenda[MAX_PRODS_E];

}Encomenda;

/*PROTOTIPOS DAS FUNCOES*/

void cmd_a();
void cmd_q();
void cmd_N();
void cmd_A();
void cmd_r();
void cmd_R();
void cmd_C();
void cmd_p();
void cmd_E();
void cmd_m();
void cmd_l();
void cmd_L();
void quicksort(Produto a[], int l, int r);
void quicksort_str(Stock_Encomenda e[], int l, int r);

/*VARIAVEIS GLOBAIS*/

/*Representa o numero de produtos existentes no sistema*/
int id = 0;
/*Representa o numero de encomendas existentes no sistema*/
int id_e = 0;
/*Representa a lista com os produtos todos do sistema*/
Produto lista_p[MAX_PRODUCTS];
/*Representa a lista com as encomendas todas do sistema*/
Encomenda lista_e[MAX_ORDERS];

/*Funcao main*/

int main()
{
	int ativo = 1;
	char c;
	while(ativo)
	{
		switch (c = getchar())
		{
			case 'a':
				printf("Novo produto %d.\n", id);
				cmd_a();
				break;
		
			case 'q':
				cmd_q();
				break;

			case 'N':
				printf("Nova encomenda %d.\n", id_e);
				cmd_N();
				break;

			case 'A':
				cmd_A();
				break;

			case 'r':
				cmd_r();
				break;
			
			case 'R':
				cmd_R();
				break;
			
			case 'C':
				cmd_C();
				break;
			
			case 'p':
				cmd_p();
				break;
			
			case 'E':
				cmd_E();
				break;
			
			case 'm':
				cmd_m();
				break;
			
			case 'l':
				cmd_l();
				break;
			
			case 'L':
				cmd_L();
				break;
			/*Comando 'x' para terminar o programa*/
			case 'x':
				ativo = 0;
				break;
		}

	}
	return 0;
}

/*Comandos*/

/*COMANDO 'a'*/
/*Adiciona um novo produto ao sistema*/

void cmd_a()
{
	Produto p;
	scanf(" %64[^:]:%d:%d:%d", p.descricao, &p.preco, &p.peso, &p.qtd);
	p.idp = id;
	lista_p[id++] = p;
}

/*COMANDO 'q'*/
/*Adiciona stock a um produto existente no sistema*/

void cmd_q()
{	
	int idp_produto = 0, stock_add = 0;
	scanf("%d:%d", &idp_produto, &stock_add);

	if(idp_produto >= id)
	{
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_produto);
		return;
	}
	lista_p[idp_produto].qtd += stock_add;
}

/*COMANDO 'N'*/
/*Cria uma nova encomenda*/

void cmd_N()
{
	Encomenda e;
	e.ide = id_e;
	e.peso = 0;
	e.n_prods = 0;
	lista_e[id_e++] = e;
}

/*COMANDO 'A'*/
/*Adiciona um produto a uma encomenda*/

void cmd_A()
{	
	int e = 0, ide_produto = 0, qtd_produto = 0, idp_produto = 0;
	scanf("%d:%d:%d", &ide_produto, &idp_produto, &qtd_produto);

	if(ide_produto >= id_e)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_produto, ide_produto);
		return;
	}
	if(idp_produto >= id) 
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_produto, ide_produto);
		return;
	}
	if(qtd_produto > lista_p[idp_produto].qtd)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_produto, ide_produto);
		return;
	}
	if((lista_e[ide_produto].peso + (lista_p[idp_produto].peso * qtd_produto)) > 200)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_produto, ide_produto);
		return;
	}
	/*Ver se o produto dado ja existe na encomenda e se existir adiciona a quantidade dada e retira essa mesma do stock*/
	for (e = 0; e < lista_e[ide_produto].n_prods; e++)
	{
		if(lista_e[ide_produto].prods_encomenda[e].prod == idp_produto)
		{
			lista_p[idp_produto].qtd -= qtd_produto;
			lista_e[ide_produto].prods_encomenda[e].qtd += qtd_produto;
			lista_e[ide_produto].peso += (lista_p[idp_produto].peso * qtd_produto);
			return;
		}
	}
	/*Como o produto nao existe na encomenda vai adiciona lo e retirar tambem a quantidade adicionada ao stock*/
	lista_p[idp_produto].qtd -= qtd_produto;
	lista_e[ide_produto].prods_encomenda[lista_e[ide_produto].n_prods].prod = idp_produto;
	lista_e[ide_produto].prods_encomenda[lista_e[ide_produto].n_prods++].qtd = qtd_produto;
	lista_e[ide_produto].peso += (lista_p[idp_produto].peso * qtd_produto);
}	

/*COMANDO 'r'*/
/*Remove stock a um produto existente no sistema*/

void cmd_r()
{
	int idp_produto = 0, stock_remove = 0;
	scanf("%d:%d", &idp_produto, &stock_remove);

	if(idp_produto >= id)
	{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_produto);
		return;
	}
	else
	{
		if(lista_p[idp_produto].qtd >= stock_remove)
		{
			lista_p[idp_produto].qtd -= stock_remove;
			return;
		}
		else
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock_remove, lista_p[idp_produto].idp);
	}
}

/*COMANDO 'R'*/
/*Remove um produto de uma encomenda*/

void cmd_R()
{	
	int e, i, ide_produto = 0, idp_produto = 0;
	scanf("%d:%d", &ide_produto, &idp_produto);

	if(ide_produto >= id_e)
	{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_produto, ide_produto);
		return;
	}
	if(idp_produto >= id)
	{
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_produto, ide_produto);
		return;
	}
	for (e = 0; e < lista_e[ide_produto].n_prods; e++)
	{
		if (lista_e[ide_produto].prods_encomenda[e].prod == idp_produto)
		{
			lista_e[ide_produto].peso -=  lista_e[ide_produto].prods_encomenda[e].qtd * lista_p[lista_e[ide_produto].prods_encomenda[e].prod].peso;
			lista_p[idp_produto].qtd += lista_e[ide_produto].prods_encomenda[e].qtd;

			/*Todos os produtos posteriores ao que vai ser removido andam uma posicao para tras de modo a manter a ordem correcta e nao haver posicoes 'vazias'*/
			for (i = e; i < lista_e[ide_produto].n_prods - 1; i++)
			{
				lista_e[ide_produto].prods_encomenda[i] = lista_e[ide_produto].prods_encomenda[i + 1];
 			}
			lista_e[ide_produto].n_prods--;
			break;
		}		
	}
}

/*COMANDO 'C'*/
/*Calcula o custo de uma encomenda*/

void cmd_C()
{	
	int i,preco_total = 0, ide_produto = 0;
	scanf("%d", &ide_produto);

	if (ide_produto >= id_e)
	{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_produto);
		return;
	}
	for(i = 0; i<lista_e[ide_produto].n_prods; i++)
	{
		preco_total += lista_e[ide_produto].prods_encomenda[i].qtd * lista_p[lista_e[ide_produto].prods_encomenda[i].prod].preco;
	}
	printf("Custo da encomenda %d %d.\n", ide_produto, preco_total);
}

/*COMANDO 'p'*/
/*Altera o preco de um produto existente no sistema*/

void cmd_p()
{	
	int idp_produto = 0, preco_novo = 0;
	scanf("%d:%d", &idp_produto, &preco_novo);

	if (idp_produto >= id)
	{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_produto);
		return;
	}
	lista_p[idp_produto].preco = preco_novo;
}	

/*COMANDO 'E'*/
/*Retorna a descricao e a quantidade de um produto numa dada encomenda*/

void cmd_E()
{
	int e = 0, ide_produto = 0, idp_produto = 0;
	scanf("%d:%d", &ide_produto, &idp_produto);

	if(ide_produto >= id_e)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_produto);
		return;
	}
	if(idp_produto >= id)
	{
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp_produto);
		return;
	}
	/*Ver se o produto existe na encomenda e se existir retorna a sua descricao e a quantidade presente na encomenda desse mesmo*/
	for (e = 0; e < lista_e[ide_produto].n_prods; e++)
	{	
		if(lista_e[ide_produto].prods_encomenda[e].prod == idp_produto)
		{	
			printf("%s %d.\n", lista_p[lista_e[ide_produto].prods_encomenda[e].prod].descricao, lista_e[ide_produto].prods_encomenda[e].qtd);
			return;
		}
	}
	printf("%s 0.\n", lista_p[idp_produto].descricao);
	return;
}

/*COMANDO 'm'*/
/*Retorna o identificador da encomenda em que um dado produto ocorre mais vezes*/

void cmd_m()
{	
	int e, i, idp_produto = 0, qtd_produto = -1, indice_encomenda = 0, indice_produto = 0;
	scanf("%d", &idp_produto);

	if (idp_produto >= id)
	{
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_produto);
		return;
	}
	/*Ver qual e a encomenda em que o produto dado se encontra em maior quantidade*/
	for(i = 0; i<id_e; i++)
	{
		for(e = 0; e<lista_e[i].n_prods; e++)
		{
			if (lista_e[i].prods_encomenda[e].prod == idp_produto)
			{
				if (lista_e[i].prods_encomenda[e].qtd > qtd_produto)
				{
					qtd_produto = lista_e[i].prods_encomenda[e].qtd;
					indice_encomenda = i;
					indice_produto = e;
					break;
				}
			}
		}
	}
	if (qtd_produto != -1)
		printf("Maximo produto %d %d %d.\n", idp_produto, lista_e[indice_encomenda].ide, lista_e[indice_encomenda].prods_encomenda[indice_produto].qtd);
}

/*COMANDO 'l'*/
/*Lista os produtos do sistema por ordem crescente de preco*/

void cmd_l()
{
	int i;
	Produto lista_p_sorted[MAX_PRODUCTS];

	for (i = 0; i < id; i++)
	{
		lista_p_sorted[i] = lista_p[i];
	}
	/*Vai ordenar a 'lista_p_sorted', inicialmente igual a 'lista_p', por ordem crescente de preco*/
	quicksort(lista_p_sorted, 0, id-1);
	printf("Produtos\n");

	for(i = 0; i<id;i++){
		printf("* %s %d %d\n", lista_p_sorted[i].descricao, lista_p_sorted[i].preco, lista_p_sorted[i].qtd);
	}
}

/*COMANDO 'L'*/
/*Lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/

void cmd_L()
{
	Stock_Encomenda e[MAX_PRODS_E];
	int i, ide_produto = 0;
	scanf("%d", &ide_produto);

	if (ide_produto >= id_e)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_produto);
		return;
	}
	for (i = 0; i < lista_e[ide_produto].n_prods; i++)
	{
		e[i] = lista_e[ide_produto].prods_encomenda[i];
	}
	/*Vai ordenar 'e', inicialmente igual a 'lista_e', por ordem alfabetica da descricao*/
	quicksort_str(e, 0, lista_e[ide_produto].n_prods - 1);
	printf("Encomenda %d\n", ide_produto);

	for (i = 0; i < lista_e[ide_produto].n_prods; i++)
	{
		printf("* %s %d %d\n", lista_p[e[i].prod].descricao, lista_p[e[i].prod].preco, e[i].qtd);
	}
}

/*Funcoes auxiliares*/

/*Funcao com proposito de trocar o identificador de um produto com o de outro*/
void exchange(Produto a[], int i, int j)
{
	Produto aux;

	aux = a[i];
	a[i] = a[j];
	a[j] = aux;
}

/*Funcao com proposito de auxiliar a funcao quicksort()*/
int partition(Produto a[], int l, int r)
{
	int i = l-1;
	int j = r;
	Produto v = a[r];

	while (i < j)
	{
		while (a[++i].preco < v.preco || (a[i].preco == v.preco && a[i].idp < v.idp));
		while (v.preco < a[--j].preco || (v.preco == a[j].preco && v.idp < a[
			j].idp))
			if (j == l)
				break;
		if (i < j)
			exchange(a,i,j);
	}
	exchange(a,i,r);
	return i;
}

/*Funcao com proposito de ordenar a lista de produtos por ordem crescente de preco*/
void quicksort(Produto a[], int l, int r)
{
	int i;

	if (r <= l)
		return;
	i = partition(a, l, r);
	quicksort(a, l, i-1);
	quicksort(a, i+1, r);
}

/*Funcao com proposito de trocar a o identificador de um produto com o de outro*/
void exchange_str(Stock_Encomenda e[], int i, int j)
{
	Stock_Encomenda aux;

	aux = e[i];
	e[i] = e[j];
	e[j] = aux;
}

/*Funcao com proposito de auxiliar a funcao quicksort_str()*/
int partition_str(Stock_Encomenda e[], int l, int r)
{
	int i = l-1;
	int j = r;
	Stock_Encomenda v = e[r];

	while (i < j)
	{
		while ((strcmp(lista_p[e[++i].prod].descricao, lista_p[v.prod].descricao)) < 0);
		while ((strcmp(lista_p[v.prod].descricao, lista_p[e[--j].prod].descricao)) < 0){
			if (j == l)
				break;
		}
		if (i < j)
			exchange_str(e,i,j);
	}
	exchange_str(e, i, r);
	return i;
}

/*Funcao com proposito de ordenar uma lista de produtos por ordem alfabetica da descricao*/
void quicksort_str(Stock_Encomenda e[], int l, int r)
{
	int i;

	if (r <= l)
		return;
	i = partition_str(e, l, r);
	quicksort_str(e, l, i-1);
	quicksort_str(e, i+1, r);
}