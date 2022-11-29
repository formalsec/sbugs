#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxProdutos 	10000		/* Maximo nr de produtos */
#define MaxEncomendas 	500			/* Maximo nr de encomendas */
#define MaxPeso			200			/* Peso maximo de encomenda */
#define MaxLenDescr		63			/* Tamanho maximo da descricao de produto */

#define NaoHa			-1			/* Indicacao de que o produto/item/encomenda nao existe */



/*
	Estrutura Produto (produto do stock)id, descricao, preco, peso, quantidade em stock, 
localizacao numa dada encomenda (de 0 a 499, -1 se nao existir na encomenda)
*/
typedef struct produto {

	int idp;							/* id do produto ([0, 9999]) */
	char descricao[MaxLenDescr+1];		/* Descricao do produto */
	int preco;							/* Preco do Produto */
	int peso;							/* Peso do Produto */
	int qtd;							/* Quantidade em Stock*/
	int Local_Enc[MaxEncomendas];		/* Lista da localizacao nas encomendas */ 
	
} Produto;


/*
	Estrutura Prdt_Enc (produto numa encomenda)
 */
typedef struct prdt_em_enc {

	int idp;						/*id do produto ([0, 9999])*/
	char descricao[MaxLenDescr+1];	/* Descricao do produto */
	int preco;						/* Preco do produto */
	int peso;						/* Peso do produto */
	int qtd_e;						/* Quantidade na encomenda */
	
} Prdt_Enc;


/*
	Estrutura Encomenda: id, nr atual de itens diferentes/id do 
proximo item a existir, lista de itens
*/
typedef struct encomenda {

	int ide;					/* id da encomenda */
	int next_item;				/* Proximo item a existir */
	Prdt_Enc Itens[MaxPeso];	/* Lista de itens da encomenda*/

} Encomenda;



/*
	Stock: Lista de todos os produtos existentes
	next_produto: nr de produtos atual/id do proximo produto a existir
*/
Produto Stock[MaxProdutos];
int next_produto = 0;


/*
	Pedidos: Lista de todas as encomendas existentes
	next_encomenda: nr de encomendas atual/id da proxima encomenda a existir
*/
Encomenda Pedidos[MaxEncomendas];
int next_encomenda = 0;



/* vetor auxiliar da funcao l_merge */
Produto aux[MaxProdutos]; 


/*
	item_nulo: devolve um item placeholder, nao existente
*/
Prdt_Enc item_nulo() {
	Prdt_Enc p;

	p.idp = NaoHa;
	p.descricao[0] = '\0';
	p.preco = 0;
	p.peso = 0;
	p.qtd_e = 0;

	return p;
}


/*
	produto_nulo: devolve um produto placeholder, nao existente
*/
Produto produto_nulo(){
	Produto p;
	int i;

	p.idp = NaoHa;
	p.descricao[0] = '\0';
	p.preco = 0;
	p.peso = 0;
	p.qtd = 0;

	for (i = 0; i < MaxEncomendas; i++)
		p.Local_Enc[i] = NaoHa;

	return p;
}


/* 
	encomenda_nula: devolve uma encomenda nula, nao existente
*/
Encomenda encomenda_nula() {
	Encomenda e;
	Prdt_Enc p;
	int i;

	e.ide = NaoHa;
	e.next_item = NaoHa;

	p = item_nulo();
	for (i = 0; i < MaxPeso; i++)
		e.Itens[i] = p;

	return e;
}



/*
	Inicializar: inicializa os Pedidos e Stock do sistema
*/
void Inicializar() {
	int i;
	Encomenda e;
	Produto p;

	e = encomenda_nula();
	p = produto_nulo();

	for (i = 0; i < MaxProdutos; i++)
		Stock[i] = p;

	for (i = 0; i < MaxEncomendas; i++)
		Pedidos[i] = e;

	return;
}


/*
	a_NovoProduto: adiciona um novo produto ao sistema
*/
void a_NovoProduto() {
	Produto p;
	int i;

	scanf(" %[^:]:%d:%d:%d", p.descricao, &p.preco, &p.peso, &p.qtd);

	p.idp = next_produto;
	p.descricao[MaxLenDescr] = '\0';

	for (i = 0; i < MaxEncomendas; i++)					/* Nao existem encomendas as quais o produto tenha sido adicionado*/
		p.Local_Enc[i] = NaoHa;

	Stock[next_produto] = p;							/* Adicionar o produto ao Stock */

	printf("Novo produto %d.\n", p.idp);
	next_produto++;										

	return;
}



/*
	q_MaisStock: adiciona stock a um produto existente no sistema
*/
void q_MaisStock() {
	int idp, a_adicionar;

	scanf(" %d:%d", &idp, &a_adicionar);

	if (idp >= next_produto)			 /* O produto nao existe se o seu id for maior do que o nr de produtos atual*/				
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	else
		Stock[idp].qtd += a_adicionar;

	return;
}



/*
	N_NovaEncomenda: cria uma nova encomenda
*/
void N_NovaEncomenda(){
	int i;
	Encomenda e;
	Prdt_Enc p;

	e.ide = next_encomenda;
	e.next_item = 0;

	p = item_nulo();

	for (i = 0; i < MaxPeso; i++)			/* Uma nova encomenda nao tem ainda produtos adicionados; sao todos nulos/invalidos */
		e.Itens[i] = p;

	Pedidos[next_encomenda] = e;			/* Adicionar encomenda a lista de pedidos */

	printf("Nova encomenda %d.\n", e.ide);
	next_encomenda++;

	return;
}



/* 
	A_MaisProdutoEnc: Adiciona um produto a uma encomenda
*/
void A_MaisProdutoEnc() {
	int i;
	int ide, idp;
	int local;								/* local: localizacao do produto na encomenda de id ide*/
	int qtd_a_adicionar; int size_d;
	int peso_e = 0;
	Encomenda e;
	Produto p;
	Prdt_Enc item;

	scanf(" %d:%d:%d", &ide, &idp, &qtd_a_adicionar);

	if (ide >= next_encomenda)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

	else if (idp >= next_produto)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

	else if (Stock[idp].qtd < qtd_a_adicionar)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);

	else
	{
		p = Stock[idp];
		e = Pedidos[ide];

		for (i = 0; i < e.next_item; i++)
			peso_e += e.Itens[i].peso * e.Itens[i].qtd_e;

		peso_e += p.peso*qtd_a_adicionar;

		if (peso_e > MaxPeso)
			printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);

		else
		{
			local = p.Local_Enc[ide];

			if (local != NaoHa)
				e.Itens[local].qtd_e += qtd_a_adicionar; 		

			else
			{
				item = e.Itens[e.next_item];

				size_d = strlen(p.descricao);

				for (i = 0; i < size_d; i++)
					item.descricao[i] = p.descricao[i];

				item.idp = p.idp;
				item.descricao[size_d] = '\0';
				item.preco = p.preco;
				item.peso = p.peso;
				item.qtd_e = qtd_a_adicionar;

				e.Itens[e.next_item] = item;

				p.Local_Enc[ide] = e.next_item;
				Stock[idp] = p;

				e.next_item++;
			}

			Stock[idp].qtd -= qtd_a_adicionar;
			Pedidos[ide] = e;
		}
	}

	return;
}



/*
	r_MenosStock: remove stock a um produto existente
*/
void r_MenosStock() {
	int idp, a_remover;

	scanf(" %d:%d", &idp, &a_remover);

	if (idp >= next_produto)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);

	else if (Stock[idp].qtd < a_remover)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", a_remover, idp);

	else
		Stock[idp].qtd -= a_remover;

	return;
}



void R_MenosProdutoEnc() {
	Encomenda e;
	Prdt_Enc item;
	int ide, idp;
	int i, local, max;

	scanf(" %d:%d", &ide, &idp);

	if (ide >= next_encomenda)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

	else if (idp >= next_produto)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

	else
	{
		local = Stock[idp].Local_Enc[ide];

		if (local != NaoHa)
		{
			Stock[idp].qtd += Pedidos[ide].Itens[local].qtd_e;		/* Adicionar ao Stock a quantidade removida */

			e = Pedidos[ide];

			if (e.next_item == 1)				/* Se o item a remover for o unico, basta tornar o item 0 um item nulo */
			{
				item = e.Itens[0];
				Stock[item.idp].Local_Enc[ide] = NaoHa;
				e.Itens[0] = item_nulo();
			}		
			
			else if (local < (e.next_item - 1) )
			{
				max = e.next_item - 1;
				
				for (i = local; i < max; i++)			/* Cada item se move uma posicao para traz na encomenda */
				{
					e.Itens[i] = e.Itens[i+1];

					item = e.Itens[i];
					Stock[item.idp].Local_Enc[ide] -= 1;
				}
				e.Itens[max] = item_nulo();
			}
			e.next_item--;
			Pedidos[ide] = e;
		}
	}
	return;
}



/*
	C_CustoEncomenda: calcula o custo de uma encomenda
*/
void C_CustoEncomenda() {
	int i;
	int ide;
	int custo = 0;
	Encomenda e;
	Prdt_Enc item;

	scanf(" %d", &ide);

	if (ide >= next_encomenda)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);

	else
	{
		e = Pedidos[ide];

		for (i = 0; i < e.next_item; i++)
		{			
			item = e.Itens[i];
			custo += item.qtd_e * item.preco;
		}

		printf("Custo da encomenda %d %d.\n", ide, custo);
	}

	return;
}



/*
	p_AlterarPrecoPrdt: altera o preco de um produto existente no sistema
*/
void p_AlterarPrecoPrdt() {
	int i;
	int idp, local;
	int preco_novo;
	Produto p;
	Encomenda e;

	scanf(" %d:%d", &idp, &preco_novo);

	if (idp >= next_produto)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);

	else
	{
		Stock[idp].preco = preco_novo;
		p = Stock[idp];

		for (i = 0; i < MaxEncomendas; i++)
			if (p.Local_Enc[i] != NaoHa)
			{
				e = Pedidos[i];
				local = p.Local_Enc[i];
				e.Itens[local].preco = p.preco;
				Pedidos[i] = e;
			}
	}
	return;
}



/*
	E_ProdutoInfoEnc: retorna a descricao e quantidade de
um produto numa encomenda
*/
void E_ProdutoInfoEnc() {
	int idp, ide;
	int ammnt, local;
	Produto stock_p;
	Prdt_Enc p_e;

	scanf(" %d:%d", &ide, &idp);

	if (ide >= next_encomenda)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

	else if (idp >= next_produto)
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);

	else
	{
		stock_p = Stock[idp];
		local = stock_p.Local_Enc[ide];

		if (local == NaoHa)
			ammnt = 0;

		else
		{
			p_e = Pedidos[ide].Itens[local];
			ammnt = p_e.qtd_e;
		}

		printf("%s %d.\n", Stock[idp].descricao, ammnt);
	}

	return;
}



/*
	m_IdMaiorPedidoPrdt: lista o identificador da encomenda em
que o produto ocorre mais vezes, com prioridade ao de maior id.
*/
void m_IdMaiorPedidoPrdt() {
	int idp, ide;
	int max = NaoHa;
	int nr_occorencias, local;
	int i;
	Produto p;
	Encomenda e;

	scanf(" %d", &idp);

	if (idp >= next_produto)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);

	else
	{
		p = Stock[idp];

		for (i = 0; i < next_encomenda; i++)
		{
			local = p.Local_Enc[i];

			if (local != NaoHa)
			{
				e = Pedidos[i];
				nr_occorencias = e.Itens[local].qtd_e;

				if (nr_occorencias > max)
				{
					ide = i;
					max = nr_occorencias;
				}

			}	
		}

		if (max != NaoHa)
			printf("Maximo produto %d %d %d.\n", idp, ide, max);
	}
	return;
}



/*
	l_merge: ordena uma lista de produtos acordo com o seu preco
*/ 
void l_merge(Produto arr[], int left, int m, int right) { 
  int i, j, k;

  for (i = m+1; i > left; i--)
    aux[i-1] = arr[i-1];

  for (j = m; j < right; j++)
    aux[right+m-j] = arr[j+1];

  for (k = left; k <= right; k++)
    if ((aux[j].preco < aux[i].preco) || i > m)
      arr[k] = aux[j--];
    else
      arr[k] = aux[i++];

	return;
}


/*
	l_mergesort: divide uma lista de produtos em listas menores a
ordenar, unindo-as depois numa lista ordenada por preco
*/
void l_mergesort(Produto arr[], int left, int right) {
	int m = (right + left)/2;

	if (right <= left)
		return;

	l_mergesort(arr, left, m);
	l_mergesort(arr, m+1, right);
	l_merge(arr, left, m, right);
}



/*
	l_ListaPrdtPreco: lista todos os produtos do sistema por ordem
crescente de preco, de acordo com o id do produto
*/
void l_ListaPrdtPreco() {
	Produto lista[MaxProdutos];
	int i;

	for (i = 0; i < MaxProdutos; i++)
		lista[i] = Stock[i];

	l_mergesort(lista, 0, next_produto - 1);

	printf("Produtos\n");

	for (i = 0; i < next_produto; i++)
		printf(" %s %d %d\n", lista[i].descricao, lista[i].preco, lista[i].qtd);

	return;
}


/*
	L_ListaPrdtAlfabeto: lista os itens de uma encomenda por ordem alfabetica
*/
void L_ListaPrdtAlfabeto() {
	int ide;

	scanf(" %d", &ide);

	if (ide >= next_encomenda)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

	else
		return;
}

/*
	main: Le uma serie de comandos relacionados com o sistema
e age de acordo com cada um
*/
int main () {
	char comando;

	scanf("%c", &comando);
	Inicializar();				/* Inicializar o Stock e Pedidos */

	while (comando != 'x')
	{
		switch (comando)
		{	
			case 'a':
				a_NovoProduto();
				break;

			case 'q':
				q_MaisStock();
				break;

			case 'N':
				N_NovaEncomenda();
				break;

			case 'A':
				A_MaisProdutoEnc();
				break;

			case 'r':
				r_MenosStock();
				break;

			case 'R':
				R_MenosProdutoEnc();
				break;

			case 'C':
				C_CustoEncomenda();
				break;

			case 'p':
				p_AlterarPrecoPrdt();
				break;

			case 'E':
				E_ProdutoInfoEnc();
				break;

			case 'm':
				m_IdMaiorPedidoPrdt();
				break;

			case 'l':
				l_ListaPrdtPreco();
				break;

			case 'L':
				L_ListaPrdtAlfabeto();
				break;
		}
		scanf("\n%c", &comando);
	}
	return 0;
}