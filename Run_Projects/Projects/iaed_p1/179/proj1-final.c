#include <stdio.h>
#include <string.h>

#define PRODUTOS_MAX 10000	/*Numero maximo de produtos na 'loja'.*/
#define ENCOMENDAS_MAX 500	/*Numero maximo de encomendas da 'loja'. */
#define PESO_MAX 200		/*Peso maximo de cada encomenda.*/
#define N_PRODUTOS_ENCOMENDA 200 /*Numero maximo de produtos por encomenda, uma vez que cada um tem no minimo 1kg.*/
#define STRING_MAX 63		/*Numero maximo de caracteres do nome de um produto.*/


/*Estrutura Produto, que representa um produto, sendo constituida pelo
nome do produto, o seu preco, o seu peso, a sua quantidade e o seu identificador.*/ 
typedef struct{

    char descricao[STRING_MAX];
    int preco;
    int peso;
    int quantidade;
    int idp;

}produto;


/*Estrutura Encomenda, que representa uma encomenda, sendo constituida por
um vetor de produtos que contem a quantidade de cada produto 'i'*/ 
typedef struct{

	/*Com o ide de produto, aceder a quantidade desse produto existente na encomenda*/
	int id_prod[PRODUTOS_MAX];	

}encomenda;


/*VARIAVEIS GLOBAIS*/

/*Vetor de produtos, contem todos os produtos da 'loja'.*/
produto catalogo[PRODUTOS_MAX];

/*Vetor de encomendas, contem todas as encomendas da 'loja'.*/
encomenda pedidos[ENCOMENDAS_MAX];

/* Identificador de produto, identificador de encomenda, quantidade de produto.*/
int idp, ide, qtd;

/*Variaveis 'p' e 'e' de controlo de quantos produtos e quantas encomendas
foram introduzidas ate certo momento, respetivamente.*/
int p;
int e;



/* 'a': Le uma palavra e tres inteiros e adiciona um novo produto
com esssas caracteristicas ao vetor catalogo.*/
void adiciona_produto(int p)
{
	printf("Novo produto %d.\n", p);

	catalogo[p].idp = p;

	scanf(" %[^:]:%d:%d:%d",
			catalogo[p].descricao,
			&catalogo[p].preco, 
			&catalogo[p].peso, 
			&catalogo[p].quantidade);
}


/* 'q': Le dois inteiros e adiciona stock(qtd) a um produto(idp) 
presente no vetor 'catalogo'.*/
void adiciona_stock(produto catalogo[], int p)
{
	scanf("%d:%d", &idp, &qtd);

	/* Se o idp escolhido pelo utilizador for superior ao numero de produtos
	existentes, erro.*/
	if (idp >= p)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);

	else
		catalogo[idp].quantidade += qtd;
}


/* 'A': Le tres inteiros e adiciona uma certa quantidade(qtd) de um produto(idp) a uma
encomenda(ide) no vetor 'pedidos', e remove a mesma quantidade desse produto
no vetor 'catalogo'.*/
void adiciona_produto_encomenda(encomenda pedidos[], produto catalogo[], int e, int p)
{

	/* peso_total serve para guardar o valor do peso total da encomenda ide.*/
	int peso_total, i;

	scanf("%d:%d:%d", &ide, &idp, &qtd);

	/* Se o ide escolhido pelo utilizador for superior ao numero de encomendas
	existentes, erro.*/
	if (ide >= e)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",
				idp, ide);

	else if (idp >= p)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",
				idp, ide);

	/*Se a quantidade escolhida for superior a quantidade existente, erro.*/
	else if (qtd > catalogo[idp].quantidade)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",
				idp, ide);

	else
	{
		for (i = 0, peso_total = 0; i < p; i++)
		{
			if (i == idp)
				peso_total += ((pedidos[ide].id_prod[idp] + qtd) * catalogo[idp].peso);
			else
				peso_total += ((pedidos[ide].id_prod[i]) * catalogo[i].peso);
		}
		
		/*Se , ao adicionar a quantidade de produto a encomenda, o peso da encomenda
		exceder o peso maximo de uma encomenda, erro.*/
		if (peso_total > PESO_MAX)
			printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",
					idp, ide);

		else
		{
			pedidos[ide].id_prod[idp] += qtd;
			catalogo[idp].quantidade -= qtd;
		}
	}	
}


/* 'r': Le dois inteiros e remove stock(qtd) a um determinado produto(idp)
no vetor 'catalogo'*/
void remove_stock(produto catalogo[], int p)
{
	scanf("%d:%d", &idp, &qtd);

	if (idp >= p)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n"
				, idp);
	
	/* Se a quantidade a remover tornar a quantidade existente em
	um numero negativo, erro.*/
	else if (catalogo[idp].quantidade - qtd < 0)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",
				qtd, idp);

	else
		catalogo[idp].quantidade -= qtd; 
}

/* 'R': Le dois inteiros e remove um produto(idp) de uma encomenda(ide) do vetor 'pedidos'.*/
void remove_produto(encomenda pedidos[], produto catalogo[], int e, int p)
{
	scanf("%d:%d", &ide, &idp);

	if (ide >= e)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",
				idp, ide);

	else if (idp >= p)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",
				idp, ide);

	else
	{
		catalogo[idp].quantidade += pedidos[ide].id_prod[idp];
		pedidos[ide].id_prod[idp] = 0; 
	}
}


/* 'C': Le um inteiro referente a uma encomenda(ide), e calcula o custo total dessa encomenda.*/
void calcula_custo(encomenda pedidos[], produto catalogo[], int e, int p)
{

	scanf("%d", &ide);

	if (ide >= e)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",
				ide);

	else
	{
		int i, custo;

		/*Multiplicar a quantidade de cada produto existente na encomenda pelo
		seu respetivo preco. */
		for (i = 0, custo = 0; i < p; i++)
			custo += (pedidos[ide].id_prod[i] * catalogo[i].preco);

		printf("Custo da encomenda %d %d.\n", ide, custo);
	}
}

/* 'p': Le dois inteiros, um referente a um produto do vetor 'catalogo' e
outro referente a um preco, altera o preco desse produto para o preco introduzido.*/
void altera_preco(produto catalogo[], int p)
{
	int novo_preco;

	scanf("%d:%d", &idp, &novo_preco);

	if (idp >= p)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",
				idp);

	else catalogo[idp].preco = novo_preco;
}


/* 'E': Le dois inteiros referentes a uma encomenda(ide) e a um produto(idp), e lista a
a descricao e a quantidade de produto(idp) na respetiva encomenda(ide). */
void lista_produto(encomenda pedidos[], produto catalogo[], int e, int p)
{
	scanf("%d:%d", &ide, &idp);

	if (ide >= e)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",
				ide);

	else if (idp >= p)
		printf("Impossivel listar produto %d. Produto inexistente.\n",
				idp);

	else
		printf("%s %d.\n", catalogo[idp].descricao, pedidos[ide].id_prod[idp]);
}


/* 'm': Le um inteiro referente a um produto(idp) e retorna a encomenda(ide) em
que esse produto exista em maior quantidade.*/
void lista_maximo_produto(encomenda pedidos[], int e, int p)
{
	int ide, max_enco, qtd_max;

	scanf("%d", &idp);

	if (idp >= p)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",
				idp);

	else
	{
		for (ide = 0, max_enco = 0, qtd_max = 0; ide < e; ide++)

			/*So altera os dados se a quantidade for MAIOR que
				a maior registada at? a?, se for igual,
				nao vai contabilizar porque ja contabilizou a encomenda com menor
				ide e com a mesma quantidade. */
			if (qtd_max < pedidos[ide].id_prod[idp])
			{
				qtd_max = pedidos[ide].id_prod[idp];
				max_enco = ide;
			}

		if (qtd_max != 0)
			printf("Maximo produto %d %d %d.\n", idp, max_enco, qtd_max);
	}
}


/* 'l'(2): Merge de listas que tem como resultado a lista ordenada por preco de todos os produtos.*/
void merge_produtos(produto lista[], int left, int m, int right)
{	
	produto aux[PRODUTOS_MAX];
	int i, j, k;

	/* i e o iterador que comeca no inicio da lista.*/
	for (i = m+1; i > left; i--)
		aux[i-1] = lista[i-1];

	/* j e o iterador que comeca no fim da lista.*/
	for (j = m; j < right; j++)
		aux[right+m-j] = lista[j+1];

	/*Ordenar a lista de produtos, do inicio para o fim.*/
	for (k = left; k <= right; k++)
	{
		/*Se o preco de aux[j] for menor que aux[i], coloca-se aux[j] em lista[k].*/
		if (aux[j].preco < aux[i].preco)
			lista[k] = aux[j--];

		/*Se o preco de aux[j] for igual ao preco de aux[i]...*/
		else if (aux[j].preco == aux[i].preco)
		{
			/*Se o identificador (idp) de aux[i] for menor, coloca-se aux[i] em lista[k]. */
			if(aux[i].idp < aux[j].idp)
				lista[k] = aux[i++];

			/*Caso contrario, coloca-se aux[j] em lista[k].*/
			else
				lista[k] = aux[j--];
		}

		/*Se o preco de aux[j] for maior que aux[i], coloca-se aux[i] em lista[k].*/
		else
			lista[k] = aux[i++];
	}
}

/* 'l'(1): Merge sort do vetor 'catalogo' em relacao ao preco dos produtos.*/
void merge_sort_produtos(produto lista[], int left, int right)
{
	int m = (right+left)/2;

	if (right<=left)return;
	
	merge_sort_produtos(lista, left, m);
	merge_sort_produtos(lista, m+1, right);
	
	merge_produtos(lista, left, m, right);
}


/* 'l': Tem como resultado a lista ordenada pelo preco dos produtos do vetor 'catalogo'.*/
void lista_ordenada_produtos(produto catalogo[], int p)
{	
	produto lista[PRODUTOS_MAX];
	int i;

	for (i = 0; i < p; i++)
		lista[i] = catalogo[i];

	/*Merge Sort dos precos dos produtos*/
	merge_sort_produtos(lista, 0, p-1);

	printf("Produtos\n");

	for (i = 0; i < p; i++)
		printf("* %s %d %d\n", lista[i].descricao, lista[i].preco, lista[i].quantidade);
}


/* 'L'(2): Merge de listas que tem como resultado a lista ordenada alfabeticamente
dos produtos existentes numa encomenda.*/
void merge_encomenda(produto lista[], int left, int m, int right)
{
	produto aux[N_PRODUTOS_ENCOMENDA];
	int i, j, k;

	/* i e o iterador que comeca no inicio da lista.*/
	for (i = m+1; i > left; i--)
		aux[i-1] = lista[i-1];
	
	/* j e o iterador que comeca no fim da lista.*/
	for (j = m; j < right; j++)
		aux[right+m-j] = lista[j+1];
	
	/*Ordenar a lista do inicio ao fim, alfabeticamente. */
	for (k = left; k <= right; k++)

		if (strcmp(aux[j].descricao, aux[i].descricao) < 0)
			lista[k] = aux[j--];

		else
			lista[k] = aux[i++];
}

/* 'L'(1): Merge sort dos produtos de uma encomenda.*/
void merge_sort_encomenda(produto lista[], int left, int right)
{
	int m = (right+left)/2;

	if (right <= left) return;
	
	merge_sort_encomenda(lista, left, m);
	merge_sort_encomenda(lista, m+1, right);
	
	merge_encomenda(lista, left, m, right);
}


/* 'L': Le um inteiro referente a uma encomenda(ide), e tem como resultado a lista ordenada alfabeticamente
dos produtos dessa encomenda. */
void lista_ordenada_encomenda(encomenda pedidos[], produto catalogo[], int e, int p)
{
	int i, j = 0;
	int n_total_produtos;
	produto lista[N_PRODUTOS_ENCOMENDA];

	scanf("%d", &ide);

	if (ide >= e)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",
				ide);

	else
	{
		for(i = 0, j = 0; i < p; i++)

			/*Se a quantidade de 'i' produto da encomenda 'ide' for nulo,
			nao entra para a lista, caso contrario entra.*/
			if (pedidos[ide].id_prod[i] != 0)
			{
				lista[j] = catalogo[i];
				lista[j++].quantidade = pedidos[ide].id_prod[i];
			}

		/*Numero total de produtos com quantidade maior que zero da encomenda.*/
		n_total_produtos = j;

		/* Merge sort da lista de produtos da encomenda(ide).*/
		merge_sort_encomenda(lista, 0, j - 1);

		printf("Encomenda %d\n", ide);

		for (i = 0; i < n_total_produtos; i++)
			printf("* %s %d %d\n",
					lista[i].descricao, lista[i].preco, lista[i].quantidade);		
	}

}


/*Le os carcteres correspondentes aos comandos e realiza as respetivas operacoes.*/
int main()
{
	char car;
	
	car = getchar();

	while(car != 'x')
	{	
		switch (car)
		{
			case 'a':
				adiciona_produto(p);
				p++;
				break;

			case 'q':
				adiciona_stock(catalogo, p);
				break;

			case 'N':
				printf("Nova encomenda %d.\n", e);
				e++;
				break;

			case 'A':
				adiciona_produto_encomenda(pedidos, catalogo, e, p);
				break;

			case 'r':
				remove_stock(catalogo, p);
				break;

			case 'R':
				remove_produto(pedidos, catalogo, e, p);
				break;

			case 'C':
				calcula_custo(pedidos, catalogo, e, p);
				break;

			case 'p':
				altera_preco(catalogo, p);
				break;

			case 'E':
				lista_produto(pedidos, catalogo, e, p);
				break;


			case 'm':
				lista_maximo_produto(pedidos, e, p);
				break;

			case 'l':
				lista_ordenada_produtos(catalogo, p);
				break;

			case 'L':
				lista_ordenada_encomenda(pedidos, catalogo, e, p); 
				break;
		}

		car = getchar();
	}

	return 0;
}


