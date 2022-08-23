#include <stdio.h>
#include <string.h>

/* maximo de produtos permitido no sistema */
#define MAX_PRODUTO 10000
/* maximo de encomendas permitidas pelo sistema */
#define MAX_ENCOMENDA 500
/* valor maximo do peso por encomenda */
#define MAX_PESO 200
/* tamanho maximo da descricao de um produto */
#define MAX_DESCRICAO 64

/* estrutura dos produtos */
typedef struct produto {
		int idp;
		char descricao[MAX_DESCRICAO];
		int preco;
		int peso;
		int qtd;
} produto;
/* "armazem" de todos os produtos */
produto geral[MAX_PRODUTO];
/* identificador do proximo produto a ser adicionado */
int next_idp = 0;
/* estrutura das encomendas */
typedef struct encomenda {
		int ide;
		produto conteudo[MAX_PESO];
		int preco;
		int peso;
		int next_prod;
} encomenda;
/* conjunto de todas as encomendas */
encomenda pedidos[MAX_ENCOMENDA];
/* identificador da proxima encomenda a ser adicionada */
int next_ide = 0;
/* listas auxiliares para organizar por custo na funcao l */
int aux[MAX_PRODUTO], a[MAX_PRODUTO];
/* listas auxiliares para organizar por ordem alfabetica na funcao L */
char nomes[MAX_ENCOMENDA][MAX_DESCRICAO], copia[MAX_DESCRICAO];
/* instrucao a ser recebida pelo utilizador */
char comando;



/* adiciona um novo produto ao sistema */
produto adiciona_sistema() {

	produto novo;
	char desc[MAX_DESCRICAO];
	int price, weight, quant, i;
	scanf(" %[^:]:%d:%d:%d", desc, &price, &weight, &quant);
	novo.idp = next_idp;
	for (i = 0; desc[i] != '\0'; i++) {
	    novo.descricao[i] = desc[i];
	}
	novo.descricao[i] = '\0';
	novo.preco = price;
	novo.peso = weight;
	novo.qtd = quant;
	return novo;
}

/* adiciona stock a um produto existente */
void adiciona_stock() {
	int prod, somar;
	scanf(" %d:%d", &prod, &somar);
	if (prod < next_idp) {
		geral[prod].qtd += somar;
	}
	else {
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prod);
	}
}

/* funcao auxiliar para enumerar todos os produtos do sistema por ordem de id */
void lista_auxiliar() {
	int i;
	printf("Produtos\n");
	for (i = 0; i < next_idp; i++) {
		printf("* %s id%d %d %d em stock\n", geral[i].descricao, geral[i].idp, geral[i].preco, geral[i].qtd);
	}

}

/* cria uma nova encomenda */
void cria_encomenda() {
	encomenda nova;
	nova.ide = next_ide;
	nova.preco = 0;
	nova.peso = 0;
	nova.next_prod = 0;
	pedidos[next_ide] = nova;
	printf("Nova encomenda %d.\n", next_ide);
}

/* adiciona determinada quantidade de um produto a uma encomenda existente */
void adiciona_prod_encomenda() {
	int enc, prod, quant, i, verif = 0, repetido = 0;
	produto acrescentar;
	scanf(" %d:%d:%d", &enc, &prod, &quant);
	if (enc >= next_ide) {
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
	}
	else if (prod >= next_idp) {
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
	}
	else if (geral[prod].qtd < quant) {
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prod, enc);
	}
	else if (pedidos[enc].peso + (quant * geral[prod].peso) > MAX_PESO) {
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prod, enc);
	}
	else {
		if (pedidos[enc].next_prod != 0) {
			for (i = 0; i < pedidos[enc].next_prod; i++) {
				if (pedidos[enc].conteudo[i].idp == prod) {
					verif += i;
					repetido = 1;
				}
			}
			if (verif == 0 && repetido != 0) {
				pedidos[enc].conteudo[verif].qtd += quant;
			}
		}
		if (verif == 0 && repetido == 0) {
			acrescentar = geral[prod];
			acrescentar.qtd = quant;
			pedidos[enc].conteudo[pedidos[enc].next_prod] = acrescentar;
			pedidos[enc].next_prod += 1;
		}
		else if (verif != 0 && repetido != 0 ) {
			pedidos[enc].conteudo[verif].qtd += quant;
		}
		geral[prod].qtd -= quant;
		pedidos[enc].preco += (geral[prod].preco * quant);
		pedidos[enc].peso += (geral[prod].peso * quant);
	}
}

/* funcao auxiliar para enumerar todos os produtos numa encomenda selecionada pela ordem em que foram acrescentados */
void encomenda_auxiliar() {
	int i, id;
	scanf(" %d", &id);
	if (id >= next_ide) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id);
	}
	else {
		printf("Encomenda %d\n", id);
		for (i = 0; i < pedidos[id].next_prod; i++) {
			printf("* %s %d %d na %d\n", pedidos[id].conteudo[i].descricao, pedidos[id].conteudo[i].preco, pedidos[id].conteudo[i].qtd, id);
		}
	}
}

/* remove stock de um produto existente */
void remove_stock() {
	int prod, quant;
	scanf(" %d:%d", &prod, &quant);
	if (prod >= next_idp) {
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod);
	}
	else if (quant > geral[prod].qtd) {
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quant, prod);
	}
	else {
		geral[prod].qtd -= quant;
	}
}

/* remove um produto selecionado de uma encomenda */
void remove_prod_encomenda() {
	int enc, prod, i;
	scanf(" %d:%d", &enc, &prod);
	if (enc >= next_ide) {
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
	}
	else if (prod >= next_idp) {
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
	}
	else {
		for (i = 0; i < pedidos[enc].next_prod; i++) {
			if (pedidos[enc].conteudo[i].idp == prod) {
				pedidos[enc].preco -= (pedidos[enc].conteudo[i].preco * pedidos[enc].conteudo[i].qtd);
				pedidos[enc].peso -= (pedidos[enc].conteudo[i].peso * pedidos[enc].conteudo[i].qtd);
				geral[prod].qtd += pedidos[enc].conteudo[i].qtd;
				pedidos[enc].conteudo[i].qtd = 0;
			}
		}
	}
}

/* calcula o custo de uma encomenda */
void calcula_custo() {
	int enc;
	scanf(" %d", &enc);
	if (enc >= next_ide) {
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", enc);
	}
	else {
		printf("Custo da encomenda %d %d.\n", enc, pedidos[enc].preco);
	}
}

/* altera o custo de um produto existente no sistema */
void altera_custo() {
	int prod, custo, i, j;
	scanf(" %d:%d", &prod, &custo);
	if (prod >= next_idp) {
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", prod);
	}
	else {
		geral[prod].preco = custo;
		for (i = 0; i < next_ide; i++) {
			for (j = 0; j < pedidos[i].next_prod; j++) {
				if (pedidos[i].conteudo[j].idp == prod) {
					pedidos[i].preco -= (pedidos[i].conteudo[j].preco * pedidos[i].conteudo[j].qtd);
					pedidos[i].conteudo[j].preco = custo;
					pedidos[i].preco += (pedidos[i].conteudo[j].preco * pedidos[i].conteudo[j].qtd);
				}
			}
		}
	}
}

/* indica a descricao de um produto e a quantidade do mesmo numa encomenda selecionada */
void lista_prod_encomenda() {
	int enc, prod, i, verif = 0, existe = 0;
	scanf(" %d:%d", &enc, &prod);
	if (enc >= next_ide) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
	}
	else if (prod >= next_idp) {
		printf("Impossivel listar produto %d. Produto inexistente.\n", prod);
	}
	else {
		for (i = 0; i < pedidos[enc].next_prod; i++) {
			if (pedidos[enc].conteudo[i].idp == prod) {
				verif += i;
				existe = 1;
			}
		}
		if (verif == 0 && existe == 0) {
			printf("%s %d.\n", geral[prod].descricao, verif);
		}
		else {
			printf("%s %d.\n", geral[prod].descricao, pedidos[enc].conteudo[verif].qtd);
		}
	}
}

/* indica a encomenda em que determinado produto surge mais vezes, juntamente com essa quantidade */
void lista_maior_quantidade() {
	int prod, i, j, maior_enc, maior = 0;
	scanf(" %d", &prod);
	if (prod >= next_idp) {
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prod);
	}
	else {
		for (i = 0; i < next_ide; i++) {
			for (j = 0; j < pedidos[i].next_prod; j++) {
				if (pedidos[i].conteudo[j].idp == prod && pedidos[i].conteudo[j].qtd > maior) {
					maior = pedidos[i].conteudo[j].qtd;
					maior_enc = i;
				}
			}
		}
		if (maior != 0) {
			printf("Maximo produto %d %d %d.\n", prod, maior_enc, maior);
		}
	}
}

/* prototipos das funcoes mergesort e merge */
void mergesort(int a[], int l, int r);
void merge(int a[], int l, int m, int r);

/* lista todos os produtos existentes no sistema por ordem crescente de preco */
void lista_ordem_sistema() {
	int i, j;
	for (i = 0; i < next_idp; i++) {
		a[i] = geral[i].preco;
	}
	mergesort(a, 0, next_idp - 1);
	printf("Produtos\n");
	for (i = 0; i < next_idp; i++) {
		if (a[i] != a[i-1]) {
			for (j = 0; j < next_idp; j++) {
				if (a[i] == geral[j].preco) {
					printf("* %s %d %d\n", geral[j].descricao, geral[j].preco, geral[j].qtd);
				}
			}
		}
	}
}

/* lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
void lista_ordem_encomenda() {
	int enc, i, j;
	scanf(" %d", &enc);
	if (enc >= next_ide) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
	}
	else {
		for (i = 0; i < pedidos[enc].next_prod; i++) {
			strcpy(nomes[i], pedidos[enc].conteudo[i].descricao);
		}
		for (i = 0; i < pedidos[enc].next_prod; i++) {
			for (j = i+1; j < pedidos[enc].next_prod; j++) {
				if (strcmp(nomes[i], nomes[j]) > 0) {
					strcpy(copia, nomes[i]);
					strcpy(nomes[i], nomes[j]);
					strcpy(nomes[j], copia);
				}
			}
		}
		printf("Encomenda %d\n", enc);
		for (i = 0; i < pedidos[enc].next_prod; i++) {
			for (j = 0; j < pedidos[enc].next_prod; j++) {
				if (strcmp(nomes[i], pedidos[enc].conteudo[j].descricao) == 0 && pedidos[enc].conteudo[j].qtd > 0) {
					printf("* %s %d %d\n", pedidos[enc].conteudo[j].descricao, pedidos[enc].conteudo[j].preco, pedidos[enc].conteudo[j].qtd);
					break;
				}
			}
		}
	}
}



/* funcoes merge e mergesort */
void mergesort(int a[], int l, int r) {
	int m = (r + l)/2;
	if (r <= l) {
		return;
	}
	mergesort(a, l, m);
	mergesort(a, m+1, r);
	merge(a, l, m, r);
}

void merge(int a[], int l, int m, int r) {
	int i, j, k;
	for (i = m+1; i > l; i--) {
		aux[i-1] = a[i-1];
	}
	for (j = m; j < r; j++) {
		aux[r+m-j] = a[j+1];
	}
	for (k = l; k <= r; k++) {
		if (aux[j] < aux[i] || i > m) {
			a[k] = aux[j--];
		}
		else {
			a[k] = aux[i++];
		}
	}
}



/* identifica os diferentes comandos e chama a funcao correspondente a cada um */
int main() {

	while ((comando = getchar()) != 'x') {
		switch(comando) {
		 case 'a':
		 	/* adiciona um novo produto ao sistema */
		 	geral[next_idp] = adiciona_sistema();
		 	printf("Novo produto %d.\n", next_idp);
		 	next_idp += 1;
		 	break;
		 case 'q':
		 	/* adiciona stock a um produto existente no sistema */
		 	adiciona_stock();
		 	break;
		 case 'N':
		 	/* cria uma nova encomenda */
		 	cria_encomenda();
		 	next_ide += 1;
		 	break;
		 case 'A':
		 	/* adiciona um produto a uma encomenda */
		 	adiciona_prod_encomenda();
		 	break;
		 case 'r':
		 	/* remove stock a um produto existente */
		 	remove_stock();
		 	break;
		 case 'R':
		 	/* remove um produto de uma encomenda */
		 	remove_prod_encomenda();
		 	break;
		 case 'C':
		 	/* calcula o custo de uma encomenda */
		 	calcula_custo();
		 	break;
		 case 'p':
		 	/* altera o pre?o de um produto existente no sistema */
		 	altera_custo();
		 	break;
		 case 'E':
		 	/* retorna a descri??o e a quantidade de um produto numa dada encomenda */
		 	lista_prod_encomenda();
		 	break;
		 case 'm':
		 	/* retorna o identificador da encomenda em que um dado produto ocorre mais vezes */
		 	lista_maior_quantidade();
		 	break;
		 case 'l':
		 	/* lista todos os produtos existentes no sistema por ordem crescente de pre?o */
		 	lista_ordem_sistema();
		 	break;
		 case 'L':
		 	/* lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
		 	lista_ordem_encomenda();
		 	break;
		 case 'k':
		 	/* lista todos os produtos existentes no sistema por ordem crescente de id */
		 	lista_auxiliar();
		 	break;
		 case 'K':
		 	/* lista todos os produtos numa encomenda pela ordem em que foram adicionados */
		 	encomenda_auxiliar();
		 	break;
		}
		getchar(); 	
	}
	return 0;
}
