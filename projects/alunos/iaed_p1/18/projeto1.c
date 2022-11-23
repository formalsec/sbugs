#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>

/* tamanho maximo de uma string lida pelo programa atraves do comando 'a' */
#define MAXDESC 64
/* numero maximo de produtos no sistema */
#define MAXPROD 10000
/* numero maximo de encomendas no sistema */
#define MAXENCOMENDAS 500
/* peso maximo de uma encomenda */
#define PESOMAX 200
#define RUN 1
#define STOP 0


/* Estruturas */

typedef struct produto
{
	int idp;
	int preco, peso, qtd, pedidos;
	char desc[MAXDESC];
}produto;

typedef struct infoProduto
{
	int idp;
	int qtd;
}infoProduto;

typedef struct encomenda
{
	infoProduto produtos[PESOMAX];
	int peso;
	int n_produtos;
	int ide;
}encomenda;

/* Vetores e Variaveis Globais */

produto bdProdutos[MAXPROD];			/* vetor com todos os produtos criados */
encomenda bdEncomendas[MAXENCOMENDAS];	/* vetor com todos as encomendas criadas */
int IDProduto = 0;						/* numero de produtos no sistema */
int IDEncomenda = 0;					/* numero de encomendas no sistema */

/* Funcoes */

/* auxiliares */
void copiaString(char origem[], char destino[]);
int comparaString(char str1[], char str2[]);
int converteParaMinusculas(int a);

/* comando a */
void criaProduto(char desc[], int preco, int peso, int qtd);
produto aux_criaProduto(char desc[], int preco, int peso, int qtd);

/* comando q */
void adicionaStock(int idp, int qtd);

/* comando N */
void criaEncomenda();
encomenda aux_criaEncomenda();

/* comando A */
void adicionaProdutoEncomenda(int ide, int idp, int qtd);

/* comando r */
void removeStock(int idp, int qtd);

/* comando R */
void removeProdutoEncomenda(int ide, int idp);
void aux_removeProduto(int ide, int idp);

/* comando C */
void custoEncomenda(int ide);

/* comando P */
void alteraPreco(int idp, int preco);

/* comando E */
void infoProdutoEncomenda(int ide, int idp);

/* comando m */
void maiorEncomendaProduto(int idp);

/* comando l */
void ordProdutosPreco();
void mergesortProdutos(produto num[], int l, int r);
void aux_mergesortProdutos(produto num[], int l, int m ,int r);
void reordenaProdutos(produto lista[], int end);


/* comando L */
void ordEncomendaDesc(int ide);
void mergesortEncomendas(infoProduto list[], int l, int r);
void aux_mergesortEncomendas(infoProduto list[], int l, int m, int r);

int main()
{
	char s[MAXDESC];
	int estado = RUN, c;
	int a, b;

	while (estado)
	{		
		switch (c = getchar())
		{			
			case 'a':
				scanf(" %[^:]:%d:%d:%d", s, &a, &b, &c);
				criaProduto(s, a, b, c);
				break;
			case 'q':
				scanf("%d:%d", &a, &b);
				adicionaStock(a, b);
				break;
			case 'N':
				criaEncomenda();
				break;				
			case 'A':
				scanf("%d:%d:%d", &a, &b, &c);
				adicionaProdutoEncomenda(a, b, c);
				break;
			case 'r':
				scanf("%d:%d", &a, &b);
				removeStock(a, b);
				break;
			case 'R':
				scanf("%d:%d", &a, &b);
				removeProdutoEncomenda(a, b);
				break;
			case 'C':
				scanf("%d", &a);
				custoEncomenda(a);
				break;
			case 'p':
				scanf("%d:%d", &a, &b);
				alteraPreco(a, b);
				break;
			case 'E':
				scanf("%d:%d", &a, &b);
				infoProdutoEncomenda(a, b);
				break;
			case 'm':
				scanf("%d", &a);
				maiorEncomendaProduto(a);
				break;
			case 'l':
				ordProdutosPreco();
				break;
			case 'L':
				scanf("%d", &a);
				ordEncomendaDesc(a);
				break;
			case 'x':
				estado = STOP;
			default:
				break;
		}
	}
	return 0;
}

/* Cria um novo produto no vetor bdProdutos */
void criaProduto(char desc[], int preco, int peso, int qtd)
{
	bdProdutos[IDProduto] = aux_criaProduto(desc, preco, peso, qtd);
	printf("Novo produto %d.\n", IDProduto);
	IDProduto++;
}

/* Cria um novo produto */
produto aux_criaProduto(char desc[], int preco, int peso, int qtd)
{
	produto res;
	res.preco = preco;
	res.peso = peso;
	res.qtd = qtd;
	res.pedidos = 0;
	res.idp = IDProduto;
	copiaString(desc, res.desc);
	return res;
}

/* Adiciona quantidade em stock a um produto. */
void adicionaStock(int idp, int qtd)
{
	if (idp >= IDProduto)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	else
		bdProdutos[idp].qtd += qtd;
}

/* Cria uma nova encomenda no vetor bdEncomendas */
void criaEncomenda()
{
	bdEncomendas[IDEncomenda] = aux_criaEncomenda();
	printf("Nova encomenda %d.\n", IDEncomenda);
	IDEncomenda++;
}

/* Cria uma nova encomenda */
encomenda aux_criaEncomenda()
{
	encomenda res;
	res.n_produtos = 0;
	res.peso = 0;
	res.ide = IDEncomenda;
	return res;
}

/* Adiciona um produto a uma encomenda, ou quantidade de produto se o produto ja existir na encomenda */
void adicionaProdutoEncomenda(int ide, int idp, int qtd)
{
	int i, produtoExiste;
	if (ide >= IDEncomenda)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if (idp >= IDProduto)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else if (bdProdutos[idp].qtd - qtd < bdProdutos[idp].pedidos)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	else if (bdEncomendas[ide].peso + bdProdutos[idp].peso * qtd > PESOMAX)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
	else
	{
		produtoExiste = 0;

		for (i = 0; i < bdEncomendas[ide].n_produtos; i++)	/*percorre lista de produtos na encomenda at? encontrar o produto especificado*/
			if (idp == bdEncomendas[ide].produtos[i].idp)	/*se encontra o id do produto, adiciona quantidade especificada*/
			{
				produtoExiste++;
				bdEncomendas[ide].produtos[i].qtd += qtd;				
				bdEncomendas[ide].peso += qtd * bdProdutos[idp].peso;
				bdProdutos[idp].pedidos += qtd;
				return;
			}
		if(!produtoExiste)	/*se nao encontrou o produto -> produto nao existe na encomenda, adiciona info do produto a encomenda*/
		{		
			produtoExiste = bdEncomendas[ide].n_produtos++;
			bdEncomendas[ide].produtos[produtoExiste].idp = idp;
			bdEncomendas[ide].produtos[produtoExiste].qtd = qtd;			
			bdEncomendas[ide].peso += qtd * bdProdutos[idp].peso;
			bdProdutos[idp].pedidos += qtd;
		}	/*peso da encomenda e nr de encomendas do produto sao atualizados
		bdEncomendas[ide].peso += qtd * bdProdutos[idp].peso;
		bdProdutos[idp].pedidos += qtd;*/
	}
}

/* Remove quantidade em stock de um produto existente, se houver stock suficiente */
void removeStock(int idp, int qtd)
{
	if (idp >= IDProduto)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	else if (bdProdutos[idp].qtd - qtd < bdProdutos[idp].pedidos)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
	else
		bdProdutos[idp].qtd -= qtd;
}


/* Remove um produto de uma encomenda */
void removeProdutoEncomenda(int ide, int idp)
{
	int peso, qtd, i;

	if (ide >= IDEncomenda)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if (idp >= IDProduto)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else
	{
		for (i = 0; i < bdEncomendas[ide].n_produtos; i++)	 /*percorre lista de produtos na encomenda at? encontrar o produto especificado */
		{
			if (idp == bdEncomendas[ide].produtos[i].idp)	
			{
				peso = bdProdutos[idp].peso;				/*peso = do produto que vai ser removido*/
				qtd = bdEncomendas[ide].produtos[i].qtd;	/*qtd = quantidade de produto na encomenda*/
				bdEncomendas[ide].peso -= qtd * peso;
				bdProdutos[idp].pedidos -= qtd;
				aux_removeProduto(ide, i);
				break;
			}
		}
	}
}

/* Remove um produto existente de uma encomenda, ajustando as posicoes dos restantes produtos */
void aux_removeProduto(int ide, int idp)
{
	int n;
	n = bdEncomendas[ide].n_produtos - 1;
	bdEncomendas[ide].produtos[idp] = bdEncomendas[ide].produtos[n];
	bdEncomendas[ide].n_produtos--;
}

/* Calcula o custo de uma encomenda existente no vetor bdEncomendas */
void custoEncomenda(int ide)
{
	int res, idp, qtd, i;
	if (ide >= IDEncomenda)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	else
	{
		res = 0;
		for (i = 0; i < bdEncomendas[ide].n_produtos; i++)	/* percorre produtos da encomenda, adiciona preco * quantidade ao total*/
		{
			qtd = bdEncomendas[ide].produtos[i].qtd;
			idp = bdEncomendas[ide].produtos[i].idp;
			res += bdProdutos[idp].preco * qtd;
		}
		printf("Custo da encomenda %d %d.\n", ide, res);
	}
}


/* Altera o preco de um produto existente no vetor bdProdutos */
void alteraPreco(int idp, int preco)
{
	if (idp >= IDProduto)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	else
		bdProdutos[idp].preco = preco;
}

/* Imprime descricao do produto e quantidade de produto na encomenda */
void infoProdutoEncomenda(int ide, int idp)
{
	int i, produtoEncomendado;
	if (ide >= IDEncomenda)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else if (idp >= IDProduto)
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	else
	{
		produtoEncomendado = 0;

		for (i = 0; i < bdEncomendas[ide].n_produtos; i++)	/* percorre produtos da encomenda ate encontrar o produto especificado*/
			if (idp == bdEncomendas[ide].produtos[i].idp)
			{
				produtoEncomendado++;
				printf("%s %d.\n", bdProdutos[idp].desc, bdEncomendas[ide].produtos[i].qtd);
			}
		if (!produtoEncomendado)	/* quando nao encontra o produto na encomenda, imprime descricao e quantidade 0 */
			printf("%s 0.\n", bdProdutos[idp].desc);
	}
}

/* Imprime ID do produto, ID da encomenda com maior quantidade do produto e a propria quantidade */
void maiorEncomendaProduto(int idp)
{
	int i, j, ide, qtd;
	if (idp >= IDProduto)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	else if (IDEncomenda > 0 && bdProdutos[idp].pedidos > 0)
	{
		qtd = 0;

		for (i = 0; i < IDEncomenda; i++)	/* percorre vetor bdEncomendas */
			for (j = 0; j < bdEncomendas[i].n_produtos; j++)	/* percorre vetor produtos de cada encomenda */
				if (idp == bdEncomendas[i].produtos[j].idp && bdEncomendas[i].produtos[j].qtd > qtd)
				{
					qtd = bdEncomendas[i].produtos[j].qtd;
					ide = i;
				}
		printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
	}
}

/* Ordena produtos do vetor bdProdutos por preco*/
void ordProdutosPreco()
{
	int i;

	mergesortProdutos(bdProdutos, 0, IDProduto-1);
	printf("Produtos\n");

	for (i = 0; i < IDProduto; i++)	/* percorre o vetor bdProdutos */
		printf("* %s %d %d\n", bdProdutos[i].desc, bdProdutos[i].preco, bdProdutos[i].qtd - bdProdutos[i].pedidos);

	reordenaProdutos(bdProdutos, IDProduto-1);
}

/* primeira parte do merge sort usado para ordenar os produtos por preco */
void mergesortProdutos(produto vetor[], int l, int r)
{
	if (l < r)
	{
		int m = (l + r) / 2;
		/* chama a funcao recursivamente para a primeira e segunda metades do vetor */
		mergesortProdutos(vetor, l, m);
		mergesortProdutos(vetor, m + 1, r);
		/* ordena e junta os elementos de ambas as metades */
		aux_mergesortProdutos(vetor, l, m, r);
	}
}

/* segunda parte do merge sort - ordena e junta os produtos de duas metades assumindo que cada metade esta ordenada */
void aux_mergesortProdutos(produto vetor[], int l, int m, int r)
{
	int i, j, k;
	produto aux[MAXPROD];

	for (i = l; i <= r; i++)	/* copia produtos do vetor principal para o auxiliar*/
		aux[i] = vetor[i];


	i = l;
	j = m + 1;
	k = l;

	while (i <= m && j <= r)
	{	/* percorre as duas metades no vetor auxiliar, escolhe ordenadamente produtos de cada metade e copia-os para o vetor principal */
		if (aux[i].preco <= aux[j].preco)
			vetor[k++] = aux[i++];
		else
			vetor[k++] = aux[j++];
	}

	while (i <= m)
		vetor[k++] = aux[i++];
}

/* Ordena produtos de um vetor por idp. Usado apos merge sort do vetor bdProdutos para colocar os produto na sua posicao original. */
void reordenaProdutos(produto vetor[], int end)
{
	int i = 0, idp;
	produto aux;
	while (i < end)
	{	/* percorre o vetor, compara posicao do produto com o seu idp, coloca-o na posicao certa */
		if (vetor[i].idp != i)
		{
			idp = vetor[i].idp;
			aux = vetor[idp];
			vetor[idp] = vetor[i];
			vetor[i] = aux;
		}
		else i++;
	}
}

/* parte principal do merge sort usado para ordenar produtos de uma encomenda por descricao */
void mergesortEncomendas(infoProduto vetor[], int l, int r)
{
	if (l < r)
	{
		int m;
		m = (l + r) / 2;
		mergesortEncomendas(vetor, l, m);
		mergesortEncomendas(vetor, m + 1, r);
		aux_mergesortEncomendas(vetor, l, m, r);
	}
}

/* segunda parte do merge sort - ordena e junta os produtos de duas metades assumindo que cada metade esta ordenada */
void aux_mergesortEncomendas(infoProduto vetor[], int l, int m, int r)
{
	int i, j, k, idp1, idp2;
	infoProduto aux[PESOMAX];

	/* copia produtos do vetor principal para o vetor auxiliar*/
	for (i = l; i <= r; i++)
		aux[i] = vetor[i];

	i = l;
	j = m + 1;
	k = l;

	while (i <= m && j <= r)
	{	/* percorre as duas metades no vetor auxiliar, escolhe ordenadamente produtos de cada metade e copia-os para o vetor principal */
		idp1 = aux[i].idp;
		idp2 = aux[j].idp;
		if (comparaString(bdProdutos[idp1].desc, bdProdutos[idp2].desc) <= 0)
			vetor[k++] = aux[i++];
		else
			vetor[k++] = aux[j++];
	}

	/* copia produtos restantes */
	while (i <= m)
		vetor[k++] = aux[i++];
}

/*funcao ordEncomendaDesc: recebe o numero de uma encomenda, imprime dos detalhes dos produtos da encomenda se esta existir*/
void ordEncomendaDesc(int ide)
{
	int i, idp, qtd;
	if (ide >= IDEncomenda)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else
	{
		mergesortEncomendas(bdEncomendas[ide].produtos, 0, bdEncomendas[ide].n_produtos-1);

		printf("Encomenda %d\n", ide);
		for (i = 0; i < bdEncomendas[ide].n_produtos; i++)
		{	
			idp = bdEncomendas[ide].produtos[i].idp;
			qtd = bdEncomendas[ide].produtos[i].qtd;
			printf("* %s %d %d\n", bdProdutos[idp].desc, bdProdutos[idp].preco, qtd);
		}
	}
	
}

/* Copia o conteudo de uma string origem para uma string destino */
void copiaString(char origem[], char destino[])
{
	int c, i;
	i = 0;

	while((c = origem[i]) /*!= EOF && c */!= '\0'/* && c != '\n'*/)
		destino[i++] = c;
	destino[i] = '\0';
}

/* Converte uma letra maiuscula para a sua minuscula */
int converteParaMinusculas(int a)
{
	if (a >= 'A' && a <= 'Z')
		a += 'a' - 'A';
	return a;
}

/* Recebe duas strings, devolve a diferenca entre as duas */
int comparaString(char str1[], char str2[])
{
	int a, b, i, res;
	i = 0;
	res = 0;
	
	while(!res && (a = str1[i]) /*!= EOF && a */!= '\0' /*&& a != '\n' */&& (b = str2[i]) /*!= EOF && b */!= '\0' /*&& b != '\n'*/)
	{
		res = converteParaMinusculas(a) - converteParaMinusculas(b);
		i++;
	}
	return res;
}