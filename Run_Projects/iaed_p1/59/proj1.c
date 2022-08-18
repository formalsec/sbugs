#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* A capacidade maxima de produtos no sistema*/
#define MAXSISTEMA 10000
/* O numero maximo de encomendas que o sistema suporta*/
#define MAXENCOM 500

/* O comprimento maximo da descricao de um produto*/
#define MAXDESC 63

/* O numero maximo de produtos que uma encomenda pode ter*/
#define MAXPROD	200

/* O estado de uma encomenda com um produto procurado*/
#define PRODUTO_IN 1
/* O estado de uma encomenda sem um produto procurado*/
#define PRODUTO_OUT -1

/* O conjunto de dados de um produto*/
typedef struct produto {
	char desc[MAXDESC];
	int custo;
	int peso;
	int quantidade;
} Produto;

/* O conjunto de dados de uma encomenda*/
typedef struct encomenda {
	int idp_produtos[MAXPROD];
	int quantidade_produtos[MAXPROD];
	int peso;
} Encomenda;

/* Vector de Produtos que guarda cada produto adicionado no sistema*/
Produto produtos[MAXSISTEMA];
/* Vector de Encomendas que guarda cada encomenda adicionada no sistema*/
Encomenda encomendas[MAXENCOM];
/* Variaveis que delimitam o numero de produtos e encomendas actual
respectivamente*/
int idp, ide;

/* Define a funcao auxiliar que inicia o registo de encomendas*/
void inicia_registo_encomendas();
/* Define o comando '__a__'*/
void adiciona_produto();
/* Define o comando '__q__'*/
void adiciona_stock();
/* Define o comando '__N__'*/
void cria_encomenda();
/* Define o comando '__A__'*/
void fornece_encomenda();
/* Define o comando '__r__'*/
void remove_stock();
/* Define o comando '__R__'*/
void remove_produto_encomenda();
/* Define o comando '__C__'*/
void calcula_custo_encomenda();
/* Define o comando '__p__'*/
void altera_preco_produto();
/* Define o comando '__E__'*/
void lista_quantidade_produto();
/* Define o comando '__m__'*/
void lista_produto_mais_referenciado();
/* Define o comando '__l__'*/
void lista_produtos_sistema();
/* Define a funcao auxiliar de ordenamento Quick sort*/
void quick_sort(int custo_produtos[], int idp_produtos[], int esquerda, 
	int direita);
/* Define a funcao particao que divide o vector a ordenar (faz parte do Quick
sort)*/
int particao(int custo_produtos[], int idp_produtos[], int esquerda, 
	int direita);
/* Define a funcao auxiliar de ordenamento Selection sort*/
void selection_sort(int custo_produtos[], int idp_produtos[], int indice_1, int indice_2);
/* Define o comando '__L__'*/
void lista_produtos_encomenda();

/* Regula o fluxo de instrucoes ao longo do programa*/
int main() {
	int comando;
	
	inicia_registo_encomendas();

	while ((comando = getchar())) {
		switch (comando) {
			case 'a':
				adiciona_produto();
				break;
			case 'q':
				adiciona_stock();
				break;
			case 'N':
				cria_encomenda();
				break;
			case 'A':
				fornece_encomenda();
				break;
			case 'r':
				remove_stock();
				break;
			case 'R':
				remove_produto_encomenda();
				break;
			case 'C':
				calcula_custo_encomenda();
				break;
			case 'p':
				altera_preco_produto();
				break;
			case 'E':
				lista_quantidade_produto();
				break;
			case 'm':
				lista_produto_mais_referenciado();
				break;
			case 'l':
				lista_produtos_sistema();
				break;
			case 'L':
				lista_produtos_encomenda();
				break;
			case 'x':
				return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

/* Inicia o registo de encomendas limpo*/
void inicia_registo_encomendas() {
	int indice_encomenda, indice_produto;

	for (indice_encomenda = 0; indice_encomenda < MAXENCOM; ++indice_encomenda)
		for (indice_produto = 0; indice_produto < MAXPROD; ++indice_produto)
			encomendas[indice_encomenda].idp_produtos[indice_produto] = PRODUTO_OUT;
} 

/* Adiciona um produto ao sistema com uma identificacao*/
void adiciona_produto() {

	scanf(" %[^:]:%d:%d:%d", produtos[idp].desc, &produtos[idp].custo,
	&produtos[idp].peso, &produtos[idp].quantidade);
	printf("Novo produto %d.\n", idp);
	++idp;
}

/* Adiciona stock a um produto existente no sistema*/
void adiciona_stock() {
	int idp_instrucao, quantidade;

	scanf(" %d:%d", &idp_instrucao, &quantidade);
	if (idp_instrucao < idp)
		produtos[idp_instrucao].quantidade += quantidade;
	else
		printf("Impossivel adicionar produto %d ao stock. "
			"Produto inexistente.\n", idp_instrucao);
}

/* Cria uma nova encomenda com uma identificacao*/
void cria_encomenda() {
	
	printf("Nova encomenda %d.\n", ide);
	++ide;
}

/* Fornece uma encomenda com produtos*/
void fornece_encomenda() {
	int ide_instrucao, idp_instrucao;
	int quantidade;
	int estado_produto;
	int indice_produto;

	scanf(" %d:%d:%d", &ide_instrucao, &idp_instrucao, &quantidade);

	if (ide_instrucao < ide && idp_instrucao < idp &&
		quantidade <= produtos[idp_instrucao].quantidade && 
		encomendas[ide_instrucao].peso + quantidade * produtos[idp_instrucao].peso 
		<= MAXPROD) {
		estado_produto = PRODUTO_OUT;
		for (indice_produto = 0; indice_produto < MAXPROD; ++indice_produto)
			if (encomendas[ide_instrucao].idp_produtos[indice_produto] == idp_instrucao) {
				estado_produto = PRODUTO_IN;
				encomendas[ide_instrucao].peso += quantidade * 
				produtos[idp_instrucao].peso;
				encomendas[ide_instrucao].quantidade_produtos[indice_produto] +=
				quantidade;
				produtos[idp_instrucao].quantidade -= quantidade;
				indice_produto = MAXPROD;
			}
		if (estado_produto == PRODUTO_OUT) {
			for (indice_produto = 0; indice_produto < MAXPROD && 
				encomendas[ide_instrucao].idp_produtos[indice_produto] != PRODUTO_OUT;
				++indice_produto);
			encomendas[ide_instrucao].idp_produtos[indice_produto] = idp_instrucao;
			encomendas[ide_instrucao].peso += quantidade * produtos[idp_instrucao].peso;
			encomendas[ide_instrucao].quantidade_produtos[indice_produto] = quantidade;
			produtos[idp_instrucao].quantidade -= quantidade;
		}
	}
	else
		if (ide_instrucao >= ide)
			printf("Impossivel adicionar produto %d a encomenda %d. "
				"Encomenda inexistente.\n", idp_instrucao, ide_instrucao);
		else if (idp_instrucao >= idp)
				printf("Impossivel adicionar produto %d a encomenda %d. "
					"Produto inexistente.\n", idp_instrucao, ide_instrucao);
		else if (quantidade > produtos[idp_instrucao].quantidade)
			printf("Impossivel adicionar produto %d a encomenda %d. "
				"Quantidade em stock insuficiente.\n", idp_instrucao, 
				ide_instrucao);
		else
			printf("Impossivel adicionar produto %d a encomenda %d. "
						"Peso da encomenda excede o maximo de 200.\n", idp_instrucao, 
						ide_instrucao);
}

/* Remove stock a um produto numa certa quantidade*/
void remove_stock() {
	int idp_instrucao, quantidade;

	scanf(" %d:%d", &idp_instrucao, &quantidade);
	if (idp_instrucao < idp)
		if (quantidade <= produtos[idp_instrucao].quantidade)
			produtos[idp_instrucao].quantidade -= quantidade;
		else
			printf("Impossivel remover %d unidades do produto %d "
				"do stock. Quantidade insuficiente.\n", quantidade, idp_instrucao);
	else
		printf("Impossivel remover stock do produto %d. "
			"Produto inexistente.\n", idp_instrucao);
}

/* Remove totalmente um produto duma encomenda no sistema*/
void remove_produto_encomenda() {
	int ide_instrucao, idp_instrucao;
	int indice_produto;

	scanf(" %d:%d", &ide_instrucao, &idp_instrucao);

	if (ide_instrucao < ide) {
		if (idp_instrucao < idp) {
			for (indice_produto = 0; indice_produto < MAXPROD; ++indice_produto)
				if (encomendas[ide_instrucao].idp_produtos[indice_produto] == idp_instrucao) {
					produtos[idp_instrucao].quantidade += 
					encomendas[ide_instrucao].quantidade_produtos[indice_produto];
					encomendas[ide_instrucao].peso -= 
					encomendas[ide_instrucao].quantidade_produtos[indice_produto] * 
					produtos[idp_instrucao].peso;
					encomendas[ide_instrucao].quantidade_produtos[indice_produto] = 0;
					encomendas[ide_instrucao].idp_produtos[indice_produto] = PRODUTO_OUT;
					indice_produto = MAXPROD;
				}
		}
		else
			printf("Impossivel remover produto %d a encomenda %d. "
			"Produto inexistente.\n", idp_instrucao, ide_instrucao);
	}
	else
		printf("Impossivel remover produto %d a encomenda %d. "
			"Encomenda inexistente.\n", idp_instrucao, ide_instrucao);
}
	
/* Calcula o custo de uma encomenda*/
void calcula_custo_encomenda() {
	int ide_instrucao;
	int custo = 0;
	int indice_produto;

	scanf(" %d", &ide_instrucao);

	if (ide_instrucao < ide) {
		for (indice_produto = 0; indice_produto < MAXPROD; ++indice_produto)
			custo += produtos[encomendas[ide_instrucao].idp_produtos[indice_produto]].custo * 
		encomendas[ide_instrucao].quantidade_produtos[indice_produto];
		printf("Custo da encomenda %d %d.\n", ide_instrucao, custo);
	}
	else
		printf("Impossivel calcular custo da encomenda %d. "
			"Encomenda inexistente.\n", ide_instrucao);
}

/* Altera o preco de um produto existente no sistema*/
void altera_preco_produto() {
	int idp_instrucao, custo_instrucao;

	scanf(" %d:%d", &idp_instrucao, &custo_instrucao);
	if (idp_instrucao < idp)
		produtos[idp_instrucao].custo = custo_instrucao;
	else
		printf("Impossivel alterar preco do produto %d. "
			"Produto inexistente.\n", idp_instrucao);
}

/* Lista a descricao e a quantidade de um dado produto numa encomenda*/
void lista_quantidade_produto() {
	int ide_instrucao, idp_instrucao;
	int indice_produto;

	scanf(" %d:%d", &ide_instrucao, &idp_instrucao);

	if (ide_instrucao < ide)
		if (idp_instrucao < idp) {
			for (indice_produto = 0; 
				encomendas[ide_instrucao].idp_produtos[indice_produto] 
				!= idp_instrucao && indice_produto < MAXPROD;
				++indice_produto);
			if (indice_produto != MAXPROD)
				printf("%s %d.\n", produtos[idp_instrucao].desc, 
					encomendas[ide_instrucao].quantidade_produtos[indice_produto]);
			else
				printf("%s 0.\n", produtos[idp_instrucao].desc);
		}
		else
			printf("Impossivel listar produto %d. "
				"Produto inexistente.\n", idp_instrucao);
	else
		printf("Impossivel listar encomenda %d. "
				"Encomenda inexistente.\n", ide_instrucao);
}

/* Lista a encomenda com o produto procurado em maior quantidade*/
void lista_produto_mais_referenciado() {
	int idp_instrucao;
	int indice_encomenda, indice_produto;
	int estado_produto;
	int max_referencia = 0;
	int ide_referencia = 0, idp_referencia = 0;

	scanf(" %d", &idp_instrucao);

	if (idp_instrucao < idp) {
		estado_produto = PRODUTO_OUT;
		for (indice_encomenda = 0; indice_encomenda < MAXENCOM; ++indice_encomenda) {
			for (indice_produto = 0; indice_produto < MAXPROD; ++indice_produto)
				if (encomendas[indice_encomenda].idp_produtos[indice_produto] == idp_instrucao)
					if (encomendas[indice_encomenda].quantidade_produtos[indice_produto] > max_referencia || 
						(encomendas[indice_encomenda].quantidade_produtos[indice_produto] == max_referencia && 
							indice_encomenda < ide_referencia)) {
					max_referencia = 
					encomendas[indice_encomenda].quantidade_produtos[indice_produto];
					ide_referencia = indice_encomenda;
					idp_referencia = indice_produto;
					indice_produto = MAXPROD;
					estado_produto = PRODUTO_IN;
					}
		}
		if (estado_produto == PRODUTO_IN)
			printf("Maximo produto %d %d %d.\n", idp_instrucao, ide_referencia, 
				encomendas[ide_referencia].quantidade_produtos[idp_referencia]);
	}
	else
		printf("Impossivel listar maximo do produto %d. "
			"Produto inexistente.\n", idp_instrucao);
}

/* Lista todos os produtos contidos no sistema por ordem crescente de preco*/
void lista_produtos_sistema() {
	int custo_produtos[MAXSISTEMA], idp_produtos[MAXSISTEMA];
	int indice_produto;
	int indice_1, indice_2;

	for (indice_produto = 0; indice_produto < idp; ++indice_produto) {
		idp_produtos[indice_produto] = indice_produto;
		custo_produtos[indice_produto] = produtos[indice_produto].custo;
	}

	quick_sort(custo_produtos, idp_produtos, 0, idp - 1);
	/* Devido a instabilidade do Quick_sort e necessario nova ordenacao.
	   Neste caso apenas interessam chaves adjacentes com custo igual*/
	for (indice_1 = 0; indice_1 < idp - 1; ++indice_1)
		for (indice_2 = indice_1 + 1; indice_2 < idp; ++indice_2)
			if (custo_produtos[indice_1] == custo_produtos[indice_2]) {
				for (; custo_produtos[indice_1] == custo_produtos[indice_2 + 1] && indice_2 < idp; ++indice_2);
				/* Aplica o Selection_sort ao conjunto restrito de chaves adjacentes
				   com custo igual*/
				selection_sort(custo_produtos, idp_produtos, indice_1, indice_2);
				indice_1 = indice_2;
				break;
			}

	printf("Produtos\n");
	for (indice_produto = 0; indice_produto < idp; ++indice_produto)
		printf("* %s %d %d\n", produtos[idp_produtos[indice_produto]].desc, 
			produtos[idp_produtos[indice_produto]].custo,
			produtos[idp_produtos[indice_produto]].quantidade);
}

/* Ordena os produtos no sistema de logistica por custo em ordem ascendente*/
void quick_sort(int custo_produtos[], int idp_produtos[], int esquerda, 
	int direita) {

	int indice;

	if (direita <= esquerda)
		return;
	indice = particao(custo_produtos, idp_produtos, esquerda, direita);
	quick_sort(custo_produtos, idp_produtos, esquerda, indice - 1);
	quick_sort(custo_produtos, idp_produtos, indice + 1, direita) ;
}

int particao(int custo_produtos[], int idp_produtos[], int esquerda, 
	int direita) {

	int indice_e = esquerda - 1, indice_d = direita;
	int v = custo_produtos[direita];
	int auxiliar_custo, auxiliar_idp;

	while (indice_e < indice_d) {
		while (custo_produtos[++indice_e] < v);
		while (v < custo_produtos[--indice_d])
			if (indice_d == esquerda)
				break;
		if (indice_e < indice_d) {
			auxiliar_custo = custo_produtos[indice_e];
			auxiliar_idp = idp_produtos[indice_e];
			custo_produtos[indice_e] = custo_produtos[indice_d];
			idp_produtos[indice_e] = idp_produtos[indice_d];
			custo_produtos[indice_d] = auxiliar_custo;
			idp_produtos[indice_d] = auxiliar_idp;
		}
	}
	auxiliar_custo = custo_produtos[indice_e];
	auxiliar_idp = idp_produtos[indice_e];
	custo_produtos[indice_e] = custo_produtos[direita];
	idp_produtos[indice_e] = idp_produtos[direita];
	custo_produtos[direita] = auxiliar_custo;
	idp_produtos[direita] = auxiliar_idp;

	return indice_e;
}

/* Ordena os produtos no sistema de logistica por custo em ordem ascendente*/
void selection_sort(int custo_produtos[], int idp_produtos[], int indice_1, int indice_2) {
	int indice_e, indice_d;
	int auxiliar_custo, auxiliar_idp, min;

	for (indice_e = indice_1; indice_e <= indice_2 - 1; indice_e++) {
		min = indice_e;
		for (indice_d = indice_e + 1; indice_d <= indice_2; indice_d++) {
			/* Depois da ordenacao efectuada pelo Quick_sort, resta encontrar
			   chaves com o mesmo custo mas com idp desordenados*/
			if (custo_produtos[indice_d] == custo_produtos[min] && 
				idp_produtos[indice_d] < idp_produtos[min])
				min = indice_d;
			/* Caso encontre uma chave com custo diferente do procurado
			   cessa a procura dentro do vector de custos*/
			if (custo_produtos[indice_d] != custo_produtos[min])
				indice_d = idp;
		}

		auxiliar_custo = custo_produtos[indice_e];
		auxiliar_idp = idp_produtos[indice_e];
		custo_produtos[indice_e] = custo_produtos[min];
		idp_produtos[indice_e] = idp_produtos[min];
		custo_produtos[min] = auxiliar_custo;
		idp_produtos[min] = auxiliar_idp;
	}
}

/* Lista todos os produtos contidos numa encomenda por ordem alfabetica*/
void lista_produtos_encomenda() {
	int ide_instrucao;
	int indice_e, indice_d;
	int indice_produto;
	int min, auxiliar_idp, auxiliar_quantidade;

	scanf(" %d", &ide_instrucao);

	/* Aplica uma versao alterada do Selection_sort em que chaves com valor -1 (PRODUTO_OUT)
	   sao ignoradas. A comparacao e efectuada entre strings de descricao*/
	if (ide_instrucao < ide) {
		for (indice_e = 0; indice_e < MAXPROD - 1; indice_e++) {
			min = indice_e;
			for (indice_d = indice_e + 1; indice_d < MAXPROD; indice_d++) {
				if (encomendas[ide_instrucao].idp_produtos[indice_e] != PRODUTO_OUT && 
					encomendas[ide_instrucao].idp_produtos[indice_d] != PRODUTO_OUT)
						if (strcmp(
							produtos[encomendas[ide_instrucao].idp_produtos[indice_d]].desc, 
							produtos[encomendas[ide_instrucao].idp_produtos[min]].desc) < 0)
							min = indice_d;
			}
			auxiliar_idp = encomendas[ide_instrucao].idp_produtos[indice_e];
			auxiliar_quantidade = encomendas[ide_instrucao].quantidade_produtos[indice_e];
			encomendas[ide_instrucao].idp_produtos[indice_e] =
			encomendas[ide_instrucao].idp_produtos[min];
			encomendas[ide_instrucao].quantidade_produtos[indice_e] = 
			encomendas[ide_instrucao].quantidade_produtos[min];
			encomendas[ide_instrucao].idp_produtos[min] = auxiliar_idp;
			encomendas[ide_instrucao].quantidade_produtos[min] = auxiliar_quantidade;
		}

		printf("Encomenda %d\n", ide_instrucao);
		for (indice_produto = 0; indice_produto < MAXPROD; ++indice_produto)
			if (encomendas[ide_instrucao].idp_produtos[indice_produto] != -1)
				printf("* %s %d %d\n", 
					produtos[encomendas[ide_instrucao].idp_produtos[indice_produto]].desc, 
					produtos[encomendas[ide_instrucao].idp_produtos[indice_produto]].custo,
					encomendas[ide_instrucao].quantidade_produtos[indice_produto]);
	}
	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_instrucao);
}