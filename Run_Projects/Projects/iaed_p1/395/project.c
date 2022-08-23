#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Valores maximos para cada parametro*/
#define MAX_id_prod 10000
#define MAX_desc 63
#define MAX_id_enco 500
#define MAX_peso 200

/*Estruturas*/
typedef struct
{
	char desc[MAX_desc];
	int idp;
	int preco;
	int peso;
	int stock;
	int quantidade;
} Produto;

typedef struct
{
	int ide;
	int qtd_p;
	int qtd_p_total;
} Encomenda;

/*Variaveis globais*/
int idprod = 0;								/*variavel que controla os ids dos produtos*/
int idenco = 0;								/*variavel que controla os ids das encomendas*/
Produto tab_produtos[MAX_id_prod];			/*array responsavel por guardar os produtos*/
Encomenda tab_encomendas[MAX_id_enco];		/*array responsavel por guardar as encomendas*/


void add_novo_produto()
{
	char nome[MAX_desc];
	Produto new_prod;
	scanf(" %[^:]:%d:%d:%d", nome, &new_prod.preco, &new_prod.peso, &new_prod.stock);
	strcpy(new_prod.desc, nome);
	if(idprod < MAX_id_prod)
	{
		printf("Novo produto %d.\n", idprod);
		new_prod.idp = idprod;
	}
	tab_produtos[idprod] = new_prod;
	idprod++;
}

void add_stock()
{
	int id_p, stock_p;
	scanf(" %d:%d", &id_p, &stock_p);
	if(id_p != tab_produtos[id_p].idp)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id_p);
	tab_produtos[id_p].stock += stock_p;
}

void cria_nova_enco()
{
	Encomenda new_enco;
	if(idenco < MAX_id_enco)
	{
		printf("Nova encomenda %d.\n", idenco);
		new_enco.ide = idenco;
	}
	tab_encomendas[idenco] = new_enco;
	idenco++;
}

void add_prod_enco()
{
	int id_e, id_p, qtd, stock_aux, peso_aux;
	scanf(" %d:%d:%d", &id_e, &id_p, &qtd);
	stock_aux = tab_produtos[id_p].stock;
	peso_aux = tab_produtos[id_p].peso * qtd;
	if(id_e != tab_encomendas[id_e].ide)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_p, id_e);
	}
	if(id_p != tab_produtos[id_p].idp)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_p, id_e);
	}
	if(id_e == tab_encomendas[id_e].ide && id_p == tab_produtos[id_p].idp)
	{
		if(stock_aux < qtd && peso_aux > MAX_peso)
		{
			printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_p, id_e);
		}
		if(peso_aux > MAX_peso && stock_aux < qtd)
		{
			printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", id_p, id_e, MAX_peso);
		}
	
	tab_produtos[id_p].quantidade = qtd;
	tab_produtos[id_p].stock -= qtd;
	}
}

void remove_stock()
{
	int id_p, qtd_p;
	scanf(" %d:%d", &id_p, &qtd_p);
	if(id_p != tab_produtos[id_p].idp)
	{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_p);
	}
	else
	{
		tab_produtos[id_p].stock -= qtd_p;
		if(tab_produtos[id_p].stock < 0)
		{
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd_p, id_p);
		}
		if(tab_produtos[id_p].stock == 0)
			tab_produtos[id_p].stock = 0;
	}
}

void remove_prod_enco()
{
	int id_e, id_p;
	scanf(" %d:%d", &id_e, &id_p);
	if(tab_encomendas[id_e].ide == id_e && tab_produtos[id_p].idp == id_p)
	{
		tab_produtos[id_p].idp -= id_p;
	}
	if(tab_encomendas[id_e].ide != id_e)
	{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_p, id_e);
	}
	if(tab_produtos[id_p].idp != id_p)
	{
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_p, id_e);
	}
}

void calcula_custo_enco()
{
	int id_e, i;
	int custo = 0;
	scanf(" %d", &id_e);
	if (tab_encomendas[id_e].ide != id_e)
	{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_e);
	}
	else
	{
		for(i = 0; i <= idprod; i++)
			custo += tab_produtos[i].preco * tab_encomendas[i].qtd_p_total;
		printf("Custo da encomenda %d %d\n", id_e, custo);
	}
}

void altera_preco()
{
	int id_p, new_preco;
	scanf(" %d:%d", &id_p, &new_preco);
	if(id_p != tab_produtos[id_p].idp)
	{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_p);
	}
	else
	{
		tab_produtos[id_p].preco = new_preco;
	}
}

void lista_desc_qtd_prod()
{
	int id_e, id_p;
	scanf(" %d:%d", &id_e, &id_p);
	if(tab_encomendas[id_e].ide == id_e && tab_produtos[id_p].idp == id_p)
	{
		printf("%s %d\n", tab_produtos[id_p].desc, tab_produtos[id_p].quantidade);
	}
	if(tab_encomendas[id_e].ide != id_e)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_e);
	}
	if(tab_produtos[id_p].idp != id_p)
	{
		printf("Impossivel listar produto %d. Produto inexistente.\n", id_p);
	}
}

void lista_ide_max()
{

}

void lista_prod_ex()
{

}

void lista_prod_alfa()
{

}

void selection_sort()
{

}

/*Executa os comandos fornecidos pelo utilizador*/
int main()
{
	char comando;
	while((comando = getchar()) != 'x')
	{
		switch(comando)
		{
			case 'a':
				add_novo_produto();
				break;
			case 'q':
				add_stock();
				break;
			case 'N':
				cria_nova_enco();
				break;
			case 'A':
				add_prod_enco();
				break;
			case 'r':
				remove_stock();
				break;
			case 'R':
				remove_prod_enco();
				break;
			case 'C':
				calcula_custo_enco();
				break;
			case 'p':
				altera_preco();
				break;
			case 'E':
				lista_desc_qtd_prod();
				break;
			case 'm':
				lista_ide_max();
				break;
			case 'l':
				lista_prod_ex();
				break;
			case 'L':
				lista_prod_alfa();
				break;
		}
	}
	return 0;
}