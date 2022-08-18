#include <stdio.h>
#include <string.h>

#define MAX_N_PROD 10000		/* Numero maximo de produtos no sistema */
#define MAX_N_E 500				/* Numero maximo de encomendas no sistema */
#define MAX_PESO_E 200			/* Peso maximo por encomenda */
#define MAX_PROD_E 200			/* Numero maximo de produtos por encomenda */
#define MAX_COMP_DESC 64		/* Maximo comprimento da descricao de um produto */
#define ATIVO 1


/* ***************************************************************************** */
/* --------------------------- 	 ESTRUTURAS  ----------------------------------- */
/* ***************************************************************************** */


/* Define a estrutura 'struct produto', e o seu alias 'produto' */
typedef struct produto 

{
	int idp, preco, peso, qtd;
	char descricao[MAX_COMP_DESC];

} produto;


/* Define a estrutura 'struct produto_em_encomenda', e o seu alias 'produto_em_e'.
Esta difere da 'struct produto' porque os elementos sao definidos unicamente pelo 
seu idp e qtd em encomenda */
typedef struct produto_em_encomenda

{
	int idp, qtd;
	
} produto_em_e;


/* Define a estrutura 'struct encomenda', e o seu alias 'encomenda' */
typedef struct encomenda

{
	int ide, peso_e, n_produtos;
	produto_em_e prods[MAX_PROD_E];

} encomenda;


/* ***************************************************************************** */
/* --------------------------- 	 VAR GLOBAIS  ---------------------------------- */
/* ***************************************************************************** */


/* Arrays que guardam os produtos e as encomendas todas do sistema,respetivamente. */
produto lista_prod[MAX_N_PROD];
encomenda lista_e[MAX_N_E];

/* ***************************************************************************** */
/* ----------------------------   PROTOTIPOS  ---------------------------------- */
/* ***************************************************************************** */

void criaProduto(int idp);
void adicionaStock(int idp);
void novaEncomenda(int ide);
void adicionapEncomenda(int idp, int ide);
void removeStock(int idp);
void removeProdEncomenda(int idp, int ide);
void custoEncomenda(int ide);
void alteraPreco(int idp);
void descQtdProdInEncomenda(int idp, int ide);
void encomendaMaisOcorr(int idp, int ide);
int indiceProdEmEncomenda(int idp_dado, int ide_dado);
void reOrdVetorProds(int ide_dado, int indice);
void listaProdutospPreco(int idp);
void listaPEncomendaAlfabet(int ide);
void quicksort(produto a[], int l, int r, char sort_metodo);
int partition(produto a[], int l, int r, char sort_metodo);
void troca(produto a[], int i, int j);
int menor(produto x, produto y, char sort_metodo);

int main() {

	/* As variaveis 'idp' e 'ide' sao contadores para os produtos e encomendas, respetivamente */
	int terminar = 0, idp = -1, ide = -1;
	char c;		

	/* Enquanto a flag 'terminar' nao estiver ativa, continua a executar o programa. */
	while (terminar != ATIVO) {

		/* Le um carater do stdin e executa o respetivo comando. */ 
		switch(c = getchar()) {

			case 'a':

				criaProduto(++idp);
				break;

			case 'q':

				adicionaStock(idp);
				break;

			case 'N':

				novaEncomenda(++ide);
				break;

			case 'A':

				adicionapEncomenda(idp, ide);
				break;

			case 'r':

				removeStock(idp);
				break;

			case 'R':

				removeProdEncomenda(idp, ide);
				break;

			case 'C':

				custoEncomenda(ide);
				break;

			case 'p':

				alteraPreco(idp);
				break;

			case 'E':

				descQtdProdInEncomenda(idp, ide);
				break;

			case 'm':

				encomendaMaisOcorr(idp, ide);
				break;

			case 'l':

				listaProdutospPreco(idp);
				break;

			case 'L':

				listaPEncomendaAlfabet(ide);
				break;

			case 'x':

				terminar = ATIVO;	
				break;
		}
	}

	return 0;
}

/* Cria um novo produto no sistema. */
void criaProduto(int idp) {

	produto p;

	/* Todas as funcoes associadas a comandos vao ler do stdin certos valores atraves da funcao scanf */
	scanf(" %64[^:]:%d:%d:%d", p.descricao, &p.preco, &p.peso, &p.qtd);

	p.idp = idp;
	lista_prod[idp] = p;

	printf("Novo produto %d.\n", p.idp);
}


/* Adiciona Stock a um produto ja existente no sistema. */
void adicionaStock(int idp) {
	
	int idp_dado, qtd_add;

	scanf("%d:%d", &idp_dado, &qtd_add);

	if (idp_dado <= idp)

		lista_prod[idp_dado].qtd += qtd_add;

	else 

		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_dado);
}


/* Cria um nova encomenda no sistema e coloca-a no array de encomendas 'lista_e' */
void novaEncomenda(int ide) {

	encomenda e = {0};

	e.ide = ide;
	lista_e[ide] = e;

	printf("Nova encomenda %d.\n", e.ide);
}


/* Adiciona um produto a uma encomenda */
void adicionapEncomenda(int idp, int ide) {

	int idp_dado, ide_dado, qtd_add, indice;
	
	scanf("%d:%d:%d", &ide_dado, &idp_dado, &qtd_add);

	/* Verifica se a encomenda ja foi criada */
	if (ide_dado <= ide) 
	{	
		/* Verifica se o produto ja foi criado */
		if (idp_dado <= idp) 
		{
			/*Verifica se o produto existe em stock em qtd suficiente para ser adicionado */
			if (lista_prod[idp_dado].qtd >= qtd_add) 
			{	
				/*Verifica se a encomenda, com o novo produto, nao excede o peso maximo */
				if (lista_e[ide_dado].peso_e <= MAX_PESO_E - lista_prod[idp_dado].peso * qtd_add) 
				{
					/* Adiciona o peso a encomenda */
					lista_e[ide_dado].peso_e += lista_prod[idp_dado].peso * qtd_add;

					/* Variavel indice toma o valor do indice do produto de idp 'idp_dado'
					dentro do array 'prods' da encomenda. Se este nao existir, passa a ter o indice onde ele vai ser criado */
					indice = indiceProdEmEncomenda(idp_dado, ide_dado);

					/* Se o produto ainda nao existir, ou seja, se a variavel 'indice' tiver o valor do 1 indice vazio
					do array 'prods', cria o produto(_em_e) e coloca-o nesse indice do array. */
					if (indice == lista_e[ide_dado].n_produtos)

						{	
							/* Incrementa o 'n_produtos' */
							lista_e[ide_dado].n_produtos += 1;
							lista_e[ide_dado].prods[indice].idp = idp_dado;
						}

					/* Adiciona a encomenda o produto na a qtd pedida */
					lista_e[ide_dado].prods[indice].qtd += qtd_add;

					/* Retira a quantidade que foi adicionada ao stock do produto respetivo */
					lista_prod[idp_dado].qtd -= qtd_add;	
				}
				else printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_dado, ide_dado);
			}
			else printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_dado, ide_dado);
		}
		else printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_dado, ide_dado);
	}
	else printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_dado, ide_dado);
}


/* Remove determinada quantidade do stock de um produto */
void removeStock(int idp) {

	int idp_dado, qtd_rem;

	scanf("%d:%d", &idp_dado, &qtd_rem);

	/* Verifica se o produto existe */
	if (idp_dado <= idp)
	{
		/* Verifica se existe em stock a qtd a remover */
		if (qtd_rem <= lista_prod[idp_dado].qtd)

			lista_prod[idp_dado].qtd -= qtd_rem;

		else printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd_rem, idp_dado);
	}

	else printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_dado);

}


/* Remove um produto de uma encomenda */
void removeProdEncomenda(int idp, int ide) {

	int indice, idp_dado, ide_dado;

	scanf("%d:%d", &ide_dado, &idp_dado);

	/* Verifica se a encomenda existe */
	if (ide_dado <= ide)
	{	
		/* Verifica se o produto existe */
		if (idp_dado <= idp)
		{
			/* Variavel 'indice' toma o valor do indice do produto(_em_e) de idp 'idp_dado'
			dentro do array 'prods' da encomenda, se existir */
			indice = indiceProdEmEncomenda(idp_dado, ide_dado);

			/* Se o produto(_em_e) nao existir na encomenda, isto e, se 'indice' tiver o primeiro indice 
			vazio do array 'prods', retorna */
			if (indice == lista_e[ide_dado].n_produtos)
				return;

			/* Devolve ao stock a quantidade que o produto(_em_e) tinha */
			lista_prod[idp_dado].qtd += lista_e[ide_dado].prods[indice].qtd;

			/* Retira o peso da encomenda */
			lista_e[ide_dado].peso_e -= lista_prod[idp_dado].peso * lista_e[ide_dado].prods[indice].qtd;

			/* Reordena o array 'prods' da encomenda, por forma a apagar o que foi removido */
			reOrdVetorProds(ide_dado, indice);

			/* Decrementa a variavel 'n_produtos' */
			lista_e[ide_dado].n_produtos -= 1;
		}
		else printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_dado, ide_dado);
	}
	else printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_dado, ide_dado);

}


/* Calcula e imprime, caso nao emita erros, o custo de uma encomenda */
void custoEncomenda(int ide) {

	int i, ide_dado, custo = 0, idp_a_consultar;

	scanf("%d", &ide_dado);

	/* Verifica se a encomenda existe */
	if (ide_dado <= ide)
	{
		for (i = 0; i < lista_e[ide_dado].n_produtos; i++)
		{	
			/* Guarda na variavel 'idp_a_consultar' o indice do array 'lista_prod' a que vai aceder */
			idp_a_consultar = lista_e[ide_dado].prods[i].idp;

			/* Acede ao array 'lista_prod' para consultar o preco e adiciona-o (*qtd do produto_em_e) ao custo */
			custo += lista_e[ide_dado].prods[i].qtd * lista_prod[idp_a_consultar].preco;
		}
		printf("Custo da encomenda %d %d.\n", ide_dado, custo);
	}
	else printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_dado);

}	


/* Altera o preco de um produto */
void alteraPreco(int idp) {

	int idp_dado, novo_preco;

	scanf("%d:%d", &idp_dado, &novo_preco);

	/* Verifica se o produto existe */
	if (idp_dado <= idp)

		/* Altera a sua componente 'preco' */
		lista_prod[idp_dado].preco = novo_preco;

	else printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_dado);
}	


/* Imprime, caso nao emita erros, a descricao e a quantidade de um produto numa determinada encomenda */
void descQtdProdInEncomenda(int idp, int ide) {

	int idp_dado, ide_dado, indice;

	scanf("%d:%d", &ide_dado, &idp_dado);

	/* Verifica se a encomenda existe */
	if (ide_dado <= ide)
	{
		/* Verifica se o produto existe */
		if (idp_dado <= idp)
		{
			/* Indice toma o valor do indice do produto(_em_e) dentro do array 'prods' da encomenda.
			Se nao existir, toma o valor do primeiro indice vazio do array */
			indice = indiceProdEmEncomenda(idp_dado, ide_dado);

			/* A descricao vai-se buscar ao array 'lista_prod' e a qtd ao ind 'indice' no array 'lista_e'.
			Se nao existir, a qtd esta inicializada a zero. */
			printf("%s %d.\n", lista_prod[idp_dado].descricao, lista_e[ide_dado].prods[indice].qtd);
		}
		else printf("Impossivel listar produto %d. Produto inexistente.\n", idp_dado);
	}
	else printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_dado);

}


void encomendaMaisOcorr(int idp, int ide) {

	int i, indice, idp_dado, e_max_occ, max_occ = 0;

	scanf("%d", &idp_dado);

	/* Verifica se o produto existe */
	if (idp_dado <= idp)
	{	
		for (i = 0; i <= ide; i++)
		{	
			/* Toma o valor do indice do array 'lista_e' em que o produto(_em_e) se encontra, se existir */
			indice = indiceProdEmEncomenda(idp_dado, i);

			/* Se o produto(_em_e) existir na encomenda em > qtd do que o max ate agora, passa a ser o max */
			if (indice != lista_e[i].n_produtos && lista_e[i].prods[indice].qtd > max_occ)
			{
				e_max_occ = i;
				max_occ = lista_e[i].prods[indice].qtd;
			}
		}	

		/* Se 'max_occ' e != do valor a que foi inicializado quer dizer que o produto esta em alguma encomenda */ 
		if (max_occ != 0) 

			printf("Maximo produto %d %d %d.\n", idp_dado, e_max_occ, max_occ);
	}
	else printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_dado);

}


void listaProdutospPreco(int idp) {

	int i;
	produto prods_ordenar[MAX_N_PROD] = {0};

	/* Cria uma copia do array 'lista_prod', de modo a que o array original esteja ordenado por idp*/
	for (i = 0; i <= idp; i++) 
		prods_ordenar[i] = lista_prod[i];

	/* Chama o metodo QuickSort, que ordena o array copia 'prods_ordenar' inteiro, por preco ('p') */
	quicksort(prods_ordenar, 0, idp, 'p');

	printf("Produtos\n");

	for (i = 0; i <= idp; i++)

		printf("* %s %d %d\n", prods_ordenar[i].descricao, prods_ordenar[i].preco, prods_ordenar[i].qtd);
}


void listaPEncomendaAlfabet(int ide) {

	int i, ide_dado, idp_a_consultar;
	produto prods_ordenar[MAX_PROD_E] = {0};

	scanf("%d", &ide_dado);

	/* Verifica se a encomenda existe */
	if (ide_dado <= ide)
	{
		/* Cria uma copia do array 'lista_prod', de modo a que o array original esteja ordenado por idp*/
		for (i = 0; i < lista_e[ide_dado].n_produtos; i++) 
		{	
			/* Todas as componentes do produto sao copiadas do array 'lista_prod' */ 
			idp_a_consultar = lista_e[ide_dado].prods[i].idp;
			prods_ordenar[i] = lista_prod[idp_a_consultar];

			/* A qtd e depois alterada para a do produto(_em_e) dentro da encomenda */
			prods_ordenar[i].qtd = lista_e[ide_dado].prods[i].qtd;
		}

		/* Chama o metodo QuickSort, que ordena o array copia 'prods_ordenar' inteiro, alfabeticamente ('a') */
		quicksort(prods_ordenar, 0, lista_e[ide_dado].n_produtos - 1, 'a');	/* sort alfabeticamente */

		printf("Encomenda %d\n", ide_dado);

		/* Imprime a descricao, o preco e a qtd dos produtos do array ordenado */
		for (i = 0; i < lista_e[ide_dado].n_produtos; i++)

			printf("* %s %d %d\n", prods_ordenar[i].descricao, prods_ordenar[i].preco, prods_ordenar[i].qtd);
	}
	else printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_dado);
		
}


/* Retorna, se existir, o indice de um produto(_em_e) no array 'prods' de uma encomenda. 
Caso nao exista, retorna o primeiro indice "vazio"(a zeros) do array. */
int indiceProdEmEncomenda(int idp_dado, int ide_dado) {

	int i;

	for (i = 0; i < lista_e[ide_dado].n_produtos; i++)
	{	
		if (lista_e[ide_dado].prods[i].idp == idp_dado)
			return i;
	}

	return i;
}


/* Reordena o vetor 'prods', vetor de produtos(_em_e) dentro de uma encomenda, apos um elemento ter sido removido */
void reOrdVetorProds(int ide_dado, int indice) {

	int i;

	for (i = indice; i < lista_e[ide_dado].n_produtos; i++)

		lista_e[ide_dado].prods[i] = lista_e[ide_dado].prods[i + 1];
}


/* Algoritmo de Ordenacao QuickSort, que ordena consoante o parametro 'sort_metodo' */
void quicksort(produto a[], int min, int max, char sort_metodo) {	

	int i;

	if (max <= min)
		return;

	/* O algoritmo chama-se a si proprio, recursivamente, sendo que cada vez que e chamado parte o array 'a'
	em 2 e ordena ambas as partes */
	i = partition(a, min, max, sort_metodo);

	quicksort(a, min, i - 1, sort_metodo);

	quicksort(a, i + 1, max, sort_metodo);
}


/* Toma o ultimo elemento do array 'a' como pivot, e coloca todos os elementos 
menores do que o pivot a sua esquerda e todos os maiores a sua direita. Coloca o pivot na sua posicao correta */
int partition(produto a[], int min, int max, char sort_metodo) {

	int i = min - 1;
	int j = max;
	produto v = a[max];

	while (i < j)
	{
		while (menor(a[++i], v, sort_metodo));

		while (menor(v, a[--j], sort_metodo))
		{
			if (j == min)

				break;
		}

		if (i < j)

			troca(a, i, j);	
	}

		troca(a, i, max);

		return i;
}


/* Troca de posicao dois elementos de indices i e j, de um array 'a' */
void troca(produto a[], int i, int j) {

	produto p = a[i];
	
	a[i] = a[j];

	a[j] = p;

}


/* Retorna 1 se o produto x for menor do que o y e 0 caso contrario */
int menor(produto x, produto y, char sort_metodo) {

	int res;

	/* Compara tendo em conta o criterio de comparacao (parametro sort_metodo) */
	if (sort_metodo == 'p')

		res = x.preco - y.preco;

	else
		res = strcmp(x.descricao, y.descricao);

	/* Se, os produtos forem iguais quando comparados com o 'sort_metodo', entao comparamos o seu idp */
	if (res == 0) 

		return (x.idp < y.idp);

	return (res < 0);

}


