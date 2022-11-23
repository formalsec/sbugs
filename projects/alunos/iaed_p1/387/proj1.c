#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* -------- CONSTANTES -------- */

/* Definicao de maximos de tamanho para a descricao, quantidade de produtos, encomendas e peso de encomenda, respetivamente. */
#define MAX_STRING				63
#define MAX_PRODUTOS			10000
#define MAX_ENCOMENDAS			500
#define MAX_PESO_ENCOMENDA		200

/* Constantes de estado. */
#define OPT_PRECO				0
#define OPT_DESC				1

#define exch(A, B) { Produto t = A; A = B; B = t; }	/* Funcao auxiliar usada no quicksort para trocar a posicao de dois produtos. */


/* -------- STRUCTS -------- */


typedef struct {	/* Estrutura de um produto com as suas respetivas caracteristicas. */
	int idp;
	char des[MAX_STRING];
	int preco;
	int peso;
	int stock;
} Produto;

typedef struct {	/* Estrutura de uma encomenda (conjunto de produtos). */
	int qnt_prod;
	Produto lista[MAX_PRODUTOS];
} Encomenda;


/* -------- VARIAVEIS GLOBAIS -------- */

Produto prod_exis[MAX_PRODUTOS];		/* Conjunto de produtos existentes no sistema. */
Encomenda enc_exis[MAX_ENCOMENDAS];		/* Conjuntos de encomedas existentes. */

int idp_atual = 0, ide_atual = 0;		/* Variaveis que sinalizam o proximo valor de id do produto e da encomenda. */

int opcao;								/* Caracteristica pela qual ordenar os produtos. */


/* -------- FUNCOES AUXILIARES -------- */

/* Verifica a existencia de uma encomenda. */
int existe_enc(int id) {
	return id < ide_atual;
}

/* Verifica a existencia do produto na lista passada e retorna o seu id, retorna -1 se nao existir.
   E passado como parametro um limite que corresponde ao numero de elementos da lista. */
int existe_prod_lista(int idp, Produto list[], int limite) {
	int i;
	for (i = 0; i < limite; i++)
		if (list[i].idp == idp)
			return i;
	return -1;
}


/* -------- FUNCOES SECUNDARIAS -------- */

/* Adiciona um novo produto ao sistema. */
void ad_prod() {
	Produto p;
	scanf(" %[^:]:%d:%d:%d", p.des, &p.preco, &p.peso, &p.stock);
	p.idp = idp_atual;
	prod_exis[idp_atual] = p;
	printf("Novo produto %d.\n", (idp_atual++));
}

/* Cria uma nova encomenda */
void ad_encomenda() {
	printf("Nova encomenda %d.\n", ide_atual++);
}

/* Adiciona stock a um produto existente no sistema. */
void ad_stock() {
	int idp, stock;
	scanf("%d:%d", &idp, &stock);
	if (existe_prod_lista(idp, prod_exis, idp_atual) > -1)		/* Se o produto existir no sistema. */
		prod_exis[idp].stock += stock;
	else
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

/* Adiciona produto ? encomenda. */
void ad_prod_enc() {
	int ide, idp, stock, idp_enc, id_qtd_encomendas;
	int i, peso_total = 0;
	scanf("%d:%d:%d", &ide, &idp, &stock);
	if (!(existe_enc(ide)))
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if (((existe_prod_lista(idp, prod_exis, idp_atual) == -1)))
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else if ((prod_exis[idp].stock) < stock)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	else {
		id_qtd_encomendas = enc_exis[ide].qnt_prod;
		for (i = 0; i < id_qtd_encomendas; i++) {												/* Calculo do peso da encomenda. */
			peso_total += enc_exis[ide].lista[i].stock * enc_exis[ide].lista[i].peso;
		}
		if ((peso_total + stock * prod_exis[idp].peso) > MAX_PESO_ENCOMENDA)					/* Calculo do peso total com o novo produto. */
			printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
		else if ((existe_prod_lista(idp, enc_exis[ide].lista, enc_exis[ide].qnt_prod) == -1)) {	/* Se o produto ainda nao existir na encomenda: */
			enc_exis[ide].lista[id_qtd_encomendas] = prod_exis[idp];							/* Adiciona-se o produto do id correspondente com o stock pedido, reduzindo o mesmo no sistema */
			enc_exis[ide].lista[id_qtd_encomendas].stock = stock;
			enc_exis[ide].qnt_prod++;															/* Aumento da quantidade de produtos na encomenda, agora correspondente ao id do proximo produto.s */
			prod_exis[idp].stock -= stock;
		}
		else {																					/* Se o produto ja existir: */
			idp_enc = existe_prod_lista(idp, enc_exis[ide].lista, enc_exis[ide].qnt_prod);		/* Aumenta-se o seu stock na encomenda e diminui-se respetivamente no sistema. */
			enc_exis[ide].lista[idp_enc].stock += stock;
			prod_exis[idp].stock -= stock;
		}
	}
}

/* Remove stock a um produto existente no sistema. */
void remove_stock() {
	int id_p, qtd;
	scanf("%d:%d", &id_p, &qtd);
	if (existe_prod_lista(id_p, prod_exis, idp_atual) == -1)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_p);
	else if ((prod_exis[id_p].stock - qtd) < 0)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id_p);
	else
		prod_exis[id_p].stock -= qtd;
}

/* Remove um produto de uma encomenda. */
void remove_prod_enc() {
	int ide, idp, idprod_enc;
	scanf("%d:%d", &ide, &idp);
	if (!existe_enc(ide))
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if (existe_prod_lista(idp, prod_exis, idp_atual) == -1)								/* Verifica a existencia do produto no sistema. */
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else {
		idprod_enc = existe_prod_lista(idp, enc_exis[ide].lista, enc_exis[ide].qnt_prod);
		if (idprod_enc > -1) {																	/* Se o produto existir na encomenda a sua quantidade eh colocada a zero e o seu stock eh reposto no sistema. */
			prod_exis[idp].stock += enc_exis[ide].lista[idprod_enc].stock;
			enc_exis[ide].lista[idprod_enc].stock = 0;
		}
	}
}

/* Calcula o custo de uma encomenda. */
void custo_enc() {
	int i, ide, total = 0;
	scanf("%d", &ide);
	if (!existe_enc(ide))
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	else {												
		/* Soma os precos calculados para cada pruduto dentro da encomenda */
		for (i = 0; i < enc_exis[ide].qnt_prod; i++)
			total += enc_exis[ide].lista[i].stock * enc_exis[ide].lista[i].preco;
		printf("Custo da encomenda %d %d.\n", ide, total);
	}
}

/* Altera o preco de um produto existente no sistema. */
void altera_preco() {
	int i, idp, novo_preco, idprod_enc;
	scanf("%d:%d", &idp, &novo_preco);
	if (existe_prod_lista(idp, prod_exis, idp_atual) == -1)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	else {											/* Alteracao do preco do produto em todas as suas ocorrencias, sistema e encomendas. */
		prod_exis[idp].preco = novo_preco;
		for (i = 0; i < ide_atual; i++) {
			idprod_enc = existe_prod_lista(idp, enc_exis[i].lista, enc_exis[i].qnt_prod);			
			if (idprod_enc != -1)					/* Se o produto existir numa das encomendas, vai ao seu id na encomenda e altera o seu preco. */
				enc_exis[i].lista[idprod_enc].preco = novo_preco;
		}
	}
}

/* Retorna a descricao e a quantidade de um produto numa dada encomenda. */
void desc_qtd_prod_enc() {
	int ide, idp, idprod_enc;
	scanf("%d:%d", &ide, &idp);
	if (!existe_enc(ide))
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else if (existe_prod_lista(idp, prod_exis, idp_atual) == -1)
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	else {
		idprod_enc = existe_prod_lista(idp, enc_exis[ide].lista, enc_exis[ide].qnt_prod);	/* Verifica se o produto existe na encomenda*/
		if (idprod_enc > -1)
			printf("%s %d.\n", prod_exis[idp].des, enc_exis[ide].lista[idprod_enc].stock);
		else
			printf("%s 0.\n", prod_exis[idp].des);											/* Se nao existir produto dentro da encomenda a sua quantidade eh printada a zero. */
	}
}

/* Retorna o identificador da encomenda em que um dado produto ocorre mais vezes. */
void max_prod() {
	int i, idp, idprod_enc, qtd_max = -1, ide_max = -1;
	scanf("%d", &idp);
	if (existe_prod_lista(idp, prod_exis, idp_atual) == -1)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	else {
		for (i = 0; i < ide_atual; i++) {
			idprod_enc = existe_prod_lista(idp, enc_exis[i].lista, enc_exis[i].qnt_prod);	/* Eh verificada a existencia do produto em cada encomenda. Se existir o seu idp correspondente na encomenda eh retornado. */
			if (idprod_enc != -1)																
				if (enc_exis[i].lista[idprod_enc].stock > qtd_max) {
					qtd_max = enc_exis[i].lista[idprod_enc].stock;							/* Atualiza-se a quantidade maxima verificada e guarda-se o id da encomenda correspondente. */
					ide_max = i;
				}
		}
		if (qtd_max > 0)																	/* Apenas retorna o produto caso exista stock do mesmo. */
			printf("Maximo produto %d %d %d.\n", idp, ide_max, qtd_max);
	}
}

/* Com base na caracteristica a ordenar (preco ou descricao) compara os produtos. */
int compara_prod(Produto a, Produto v) {
	if (opcao == OPT_PRECO) {
		if (a.preco == v.preco)						/* Se os precos forem igual compara-os de acordo com o seu idp. */
			return (a.idp < v.idp);
		else
			return (a.preco < v.preco);
	}
	else
		return (strcmp(a.des, v.des) < 0);		/* A funcao strcmp retorna um num negativo se o primeiro parametro for menor que o segundo. */
}

/* Funcao que ordena produtos de uma lista. */
void quicksort(Produto a[], int l, int r) {
	int i, j;
	Produto v;
	if (r <= l) return;		/* Verificacao dos parametros passados. */

	i = l - 1;
	j = r;
	v = a[r];	/* Pivot - ultimo elemento da lista passada, separara os elementos de acordo com o criterio,
				           menores a sua esquerda e maiores a direita. */

	/* Rearranja os elementos do vector conforme o criterio de ordenacao. */
	while (i < j) {		/* Enquanto o iterador da esquerda (i) for menor que o da direita (j). */
		while (compara_prod(a[++i], v));
		while (compara_prod(v, a[--j])) {
			if (j == l)
				break;
		}
		if (i < j)					
			exch(a[i], a[j]);		/* Troca de elementos. */
	}
	exch(a[i], a[r]);				/* Coloca o elemento correspondente ao pivot na sua posicao final. */

	/* Aplicacao recursiva do algoritmo aos dois subconjuntos de dados dai resultantes. */
	quicksort(a, l, i - 1);
	quicksort(a, i + 1, r);
}

/* Lista todos os produtos existentes no sistema por ordem crescente de preco. */
void ordena_prod_exis() {
	int i;
	Produto copia[MAX_PRODUTOS];

	for (i = 0; i < idp_atual; i++) {		/* Criamos uma copia da lista de produtos do sistema para que a possamos ordenar posteriormente sem alterar a original. */
		copia[i] = prod_exis[i];
	}

	/* Ordenacao da nova lista criada de acordo com a caracteristica (opcao). */
	opcao = OPT_PRECO;
	quicksort(copia, 0, idp_atual - 1);

	printf("Produtos\n");
	for (i = 0; i < idp_atual; i++) {
		printf("* %s %d %d\n", copia[i].des, copia[i].preco, copia[i].stock);
	}
}

/* Lista todos os produtos de uma encomenda por ordem alfabetica da descricao. */
void ordena_encomenda() {
	int i, qtd, ide;

	scanf("%d", &ide);
	if (!existe_enc(ide))
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else {
		
		qtd = enc_exis[ide].qnt_prod;
		/* Neste caso nao eh preciso criar copia porque na verificacao de existencia de produto numa lista (existe_prod_lista),
		   neste caso especifico na lista de produtos de uma certa encomenda, eh retornado o id no qual o produto correspondente
		   se encontra, fazendo com que a ordenacao da lista nao cause nenhum efeito na procura do produto. */

		/* Ordenacao da lista de produtos de uma certa encomenda de acordo com a caracteristica (opcao). */
		opcao = OPT_DESC;
		quicksort(enc_exis[ide].lista, 0, qtd - 1);

		printf("Encomenda %d\n", ide);
		for (i = 0; i < qtd; i++) {
			if (enc_exis[ide].lista[i].stock > 0)				/* Se o stock de um produto for nulo ? considerado inexistente na encomenda. */
				printf("* %s %d %d\n", enc_exis[ide].lista[i].des, enc_exis[ide].lista[i].preco, enc_exis[ide].lista[i].stock);
		}
	}
}


/* --------- FUNCAO MAIN --------- */

int main() {
	char c;
	
	while (((scanf("%c", &c)) != EOF) && (c != 'x')) {	/* Caso o comando seja 'x' ou o input termine, o programa termina. */
		
		/* Conforme o comando passado, uma funcao correspondente eh chamada. */
		switch (c) {
		case'a':
			ad_prod();
			break;

		case 'q':
			ad_stock();
			break;

		case 'N':
			ad_encomenda();
			break;

		case 'A':
			ad_prod_enc();
			break;

		case 'r':
			remove_stock();
			break;

		case 'R':
			remove_prod_enc();
			break;

		case 'C':
			custo_enc();
			break;

		case 'p':
			altera_preco();
			break;

		case 'E':
			desc_qtd_prod_enc();
			break;

		case 'm':
			max_prod();
			break;

		case 'l':
			ordena_prod_exis();
			break;

		case 'L':
			ordena_encomenda();
			break;
		}
	}
	return 0;
}