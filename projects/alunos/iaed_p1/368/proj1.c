#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define MAX_STR 64
#define MAX_PESO 200

#define NAO_ENCONTRADO -1

struct produto {
	char desc[MAX_STR];
	int preco, peso, qtd;
};

struct encomenda {
	int idp[MAX_PESO], qtd[MAX_PESO];
	int dim;
};

/* Lista de produtos. */
struct produto p[MAX_PRODUTOS];
/* Lista de encomendas. */
struct encomenda e[MAX_ENCOMENDAS];
/* Numero de produtos. */
int num_p = 0;
/* Numero de encomendas.*/
int num_e = 0;

/* Verifica se o produto existe no sistema. */
int existe_produto(int idp) {
	return idp < num_p;
}

/* Verifica se a encomenda existe no sistema. */
int existe_encomenda(int ide) {
	return ide < num_e;
}

/* Devolve a posicao de um produto dentro de uma encomenda.
   Se nao for encontrado, a funcao devolve NAO_ENCONTRADO. */
int pos_produto(int ide, int idp) {
	int res = NAO_ENCONTRADO, i;

	for (i = 0; i < e[ide].dim; i++)
		if (e[ide].idp[i] == idp)
			res = i;

	return res;
}

/* Devolve o peso total de uma encomenda. */
int peso_encomenda(int ide) {
	int peso = 0, idp, i;

	for (i = 0; i < e[ide].dim; i++) {
		idp = e[ide].idp[i];
		peso += e[ide].qtd[i] * p[idp].peso;
	}

	return peso;
}

/* Remove um produto de uma encomenda. */
void remove_p_de_e(int ide, int i) {
	int j = e[ide].dim - 1;

	/* Copia o produto na ultima posicao
	   para a posicao do produto removido. */

	e[ide].idp[i] = e[ide].idp[j];
	e[ide].qtd[i] = e[ide].qtd[j];

	e[ide].dim --;
	return;
}

/* Devolve se o preco de um produto eh menor do que outro. */
int menor_preco(int id1, int id2) {
	return p[id1].preco < p[id2].preco;
}

/* Compara as descricoes de dois produtos numa encomenda. */
int cmp_desc(int ide, int i, int j) {
	int id1 = e[ide].idp[i];
	int id2 = e[ide].idp[j];
	return strcmp(p[id1].desc, p[id2].desc) < 0;
}

/* Devolve a quandidade de um produto dentro de uma encomenda. */
int qtd_em_encomenda(int ide, int idp) {
	int i;
	i = pos_produto(ide, idp);
	if (i == NAO_ENCONTRADO)
		return 0;
	else
		return e[ide].qtd[i];
}

/* Executa o comando k. (Mostra lista de produtos no sistema) */
void comando_k() {
	int idp;

	printf("Produtos\n");
	for (idp = 0; idp < num_p; idp++) {
		printf("* %s %d %d\n", p[idp].desc, p[idp].preco, p[idp].qtd);
	}

	return;
}

/* Executa o comando a. (Adiciona um produto novo ao sistema) */
void comando_a() {
	scanf(" %[^:]:%d:%d:%d", p[num_p].desc, &p[num_p].preco, &p[num_p].peso, &p[num_p].qtd);
	printf("Novo produto %d.\n", num_p);
	num_p++;

	return;
}

/* Executa o comando q. (Adiciona stock a um produto existente) */
void comando_q() {
	int idp, qtd;

	scanf(" %d:%d", &idp, &qtd);
	if (!existe_produto(idp)) {
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
		return;
	}

	p[idp].qtd += qtd;
	return;
}

/* Executa o comando K. (Mostra lista de produtos numa encomenda) */
void comando_K() {
	int ide, idp, i;

	scanf(" %d", &ide);
	printf("Encomenda %d\n", ide);
	for (i = 0; i < e[ide].dim; i++) {
		idp = e[ide].idp[i];
		printf("* %s %d %d\n", p[idp].desc, p[idp].preco, e[ide].qtd[i]);
	}
	return;
}

/* Executa o comando N. (Cria uma nova encomenda) */
void comando_N() {
	e[num_e].dim = 0;
	printf("Nova encomenda %d.\n", num_e);
	num_e++;
	return;
}

/* Executa o comando A. (Adiciona um produto a uma encomenda) */
void comando_A() {
	int ide, idp, qtd, i;

	scanf(" %d:%d:%d", &ide, &idp, &qtd);

	if (!existe_encomenda(ide)) {
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return;
	}
	if (!existe_produto(idp)) {
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	}
	if (qtd > p[idp].qtd) {
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		return;
	}
	if (peso_encomenda(ide) + qtd * p[idp].peso > MAX_PESO) {
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", idp, ide, MAX_PESO);
		return;
	}

	i = pos_produto(ide, idp);

	/* Adiciona um novo produto ? encomenda se ele nao existir la. */
	if (i == NAO_ENCONTRADO) {
		i = e[ide].dim;
		e[ide].idp[i] = idp;
		e[ide].qtd[i] = 0;
		e[ide].dim ++;
	}

	/* Altera a quantidade do produto no sistema e na encomenda */
	p[idp].qtd -= qtd;
	e[ide].qtd[i] += qtd;
	return;
}

/* Executa o comando r. (Remove stock a um produto existente) */
void comando_r() {
	int idp, qtd;

	scanf(" %d:%d", &idp, &qtd);
	if (!existe_produto(idp)) {
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
		return;
	}
	if (qtd > p[idp].qtd) {
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
		return;
	}

	p[idp].qtd -= qtd;
	return;
}

/* Executa o comando R. (Remove um produto de uma encomenda) */
void comando_R() {
	int ide, idp, i;

	scanf(" %d:%d", &ide, &idp);
	if (!existe_encomenda(ide)) {
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return;
	}
	if (!existe_produto(idp)) {
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	}

	i = pos_produto(ide, idp);
	if (i != NAO_ENCONTRADO) {
		p[idp].qtd += e[ide].qtd[i];
		remove_p_de_e(ide, i);
	}

	return;
}

/* Executa o comando C. (Calcula o custo de uma encomenda) */
void comando_C() {
	int ide, idp, i, total = 0;

	scanf(" %d", &ide);
	if (!existe_encomenda(ide)) {
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}

	for (i = 0; i < e[ide].dim; i++) {
		idp = e[ide].idp[i];
		total += e[ide].qtd[i] * p[idp].preco;
	}
	printf("Custo da encomenda %d %d.\n", ide, total);

	return;
}

/* Executa o comando p. (Altera o preco de um produto existente no sistema) */
void comando_p() {
	int idp, preco;

	scanf(" %d:%d", &idp, &preco);
	if (!existe_produto(idp)) {
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
		return;
	}

	p[idp].preco = preco;
	return;
}

/* Executa o comando E.
  (Retorna a descricao e a quantidade de um produto numa dada encomenda) */
void comando_E() {
	int ide, idp, qtd;

	scanf(" %d:%d", &ide, &idp);
	if (!existe_encomenda(ide)) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}
	if (!existe_produto(idp)) {
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
		return;
	}

	qtd = qtd_em_encomenda(ide, idp);
	printf("%s %d.\n", p[idp].desc, qtd);
	return;
}

/* Executa o comando m.
   (Retorna o identificador da encomenda
   em que um dado produto ocorre mais vezes) */
void comando_m() {
	int ide, idp, qtd, max = 0, max_qtd = 0;

	scanf(" %d", &idp);

	if (!existe_produto(idp)) {
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
		return;
	}

	for (ide = 0; ide < num_e; ide++) {
		qtd = qtd_em_encomenda(ide, idp);
		if (qtd > max_qtd) {
			max_qtd = qtd;
			max = ide;
		}
	}
	if (max_qtd > 0)
		printf("Maximo produto %d %d %d.\n", idp, max, max_qtd);

	return;
}

/* Executa o comando l.
   (Lista todos os produtos existentes no sistema
   por ordem crescente de preco) */
void comando_l() {
	int ordem[MAX_PRODUTOS], idp, i, j, v;

	for (i = 0; i < num_p; i++)
		ordem[i] = i;

	for (i = 1; i < num_p; i++) {
		v = ordem[i];
		j = i-1;
		while (j >= 0 && menor_preco(v, ordem[j])) {
				ordem[j+1] = ordem[j];
				j--;
		}
		ordem[j+1] = v;
	}

	printf("Produtos\n");
	for (i = 0; i < num_p; i++) {
		idp = ordem[i];
		printf("* %s %d %d\n", p[idp].desc, p[idp].preco, p[idp].qtd);
	}

	return;
}

/* Executa o comando l.
   (Lista todos os produtos de uma encomenda
   por ordem alfabetica da descricao) */
void comando_L() {
	int ordem[MAX_PESO], ide, idp, i, j, v;

	scanf(" %d", &ide);

	if (!existe_encomenda(ide)) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}

	for (i = 0; i < e[ide].dim; i++)
		ordem[i] = i;

	for (i = 1; i < e[ide].dim; i++) {
		v = ordem[i];
		j = i-1;
		while (j >= 0 && cmp_desc(ide, v, ordem[j])) {
				ordem[j+1] = ordem[j];
				j--;
		}
		ordem[j+1] = v;
	}

	printf("Encomenda %d\n", ide);
	for (j = 0; j < e[ide].dim; j++) {
		i = ordem[j];
		idp = e[ide].idp[i];
		printf("* %s %d %d\n", p[idp].desc, p[idp].preco, e[ide].qtd[i]);
	}
	return;
}

int main() {
	char comando;

	while ((comando = getchar()) != 'x') {
		switch (comando) {
			case 'k':
				comando_k();
				break;

			case 'a':
				comando_a();
				break;

			case 'q':
				comando_q();
				break;

			case 'K':
				comando_K();
				break;

			case 'N':
				comando_N();
				break;

			case 'A':
				comando_A();
				break;

			case 'r':
				comando_r();
				break;

			case 'R':
				comando_R();
				break;

			case 'C':
				comando_C();
				break;

			case 'p':
				comando_p();
				break;

			case 'E':
				comando_E();
				break;

			case 'm':
				comando_m();
				break;

			case 'l':
				comando_l();
				break;

			case 'L':
				comando_L();
				break;
		}
	}

	return 0;
}