#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "all.h"
#include "constants.h"
#include "Sort.h"

#include <stdio.h>
#include <stdlib.h>

extern prod prod_list[];								/* lista com todos os produtos no sistema */
extern ord ord_list[];									/* lista com todas as encomendas */

int idp = 0, ide = 0;									/* contadores do numero de produtos(idp) e encomendas(ide)*/
int idp_list[MAX_PROD];									/* lista com os id dos produtos para ordenar os produtos */	


/*--------------------*\
 * Funcoes auxiliares *
\*--------------------*/

/* verifica se e qual o erro da funcao 'add_prod_ord' */
int get_error(int ide2, int idp2, long int qt) {

	if (ide2 >= ide)
		/* encomenda nao existe */
		return 1;

	else if (idp2 >= idp)
		/* produto nao existe */
		return 2;

	else if (qt > prod_list[idp2].qt)
		/* quantidade em stock insuficiente */
		return 3;

	else {
		long int weight = qt * prod_list[idp2].weight + ord_list[ide2].weight;			/* novo peso da encomenda */
		if (weight > MAX_WEIGHT)
			/* peso da encomenda excede o maximo permitido */
			return 4;

		else
			return 0;
	}
}

/* devolve a quantidade do produto numa encomenda */
long int get_prod_qt(int idp2, ord* order) {
	return order->prod_list[idp2];
}

/* calcula o custo de uma encomenda */
long int calc_cost(ord* order) {
	int i;
	long int cost = 0;

	for (i = 0; i < MAX_PROD; i++) {
		prod* p = &prod_list[i];

		cost += p->price * order->prod_list[i];
	}

	return cost;
}

/*--------------------*\
 * Funcoes principais *
\*--------------------*/

/* adiciona um produto ao sistema */
void add_prod_sys() {
	prod p;

	idp_list[idp] = idp;
	scanf(" %[^:]:%ld:%ld:%ld", p.desc, &p.price, &p.weight, &p.qt);
	prod_list[idp] = p;
	printf("Novo produto %d.\n", idp++);
}

/* adiciona stock a um produto */
void add_stock() {
	int idp2;
	long int qt;

	scanf("%d:%ld", &idp2, &qt);
	if (idp2 >= idp) /* verifica se o produto existe */
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp2);
	else
		prod_list[idp2].qt += qt;
}	

/* cria uma nova encomenda */
void add_order() {
	int i;
	ord o;

	o.len = 0;
	o.weight = 0;

	/* inicializa lista de produtos a 0 */
	for (i = 0; i < MAX_PROD; i++)
		o.prod_list[i] = 0;

	ord_list[ide] = o;

	printf("Nova encomenda %d.\n", ide++);
}

/* adiciona um produto a uma encomenda */
void add_prod_ord() {
	int ide2, idp2;
	long int qt;
	int error;

	scanf("%d:%d:%ld", &ide2, &idp2, &qt);
	error = get_error(ide2, idp2, qt);
	if (error) {
		printf("Impossivel adicionar produto %d a encomenda %d. ", idp2, ide2);
		switch (error) {
			case 1:
				printf("Encomenda inexistente.");
				break;

			case 2:
				printf("Produto inexistente.");
				break;

			case 3:
				printf("Quantidade em stock insuficiente.");
				break;

			case 4:
				printf("Peso da encomenda excede o maximo de 200.");
				break;
		}
		printf("\n");
	}
	else {
		/* o input e valido */
		ord* order = &ord_list[ide2];						/* encomenda a qual queremos adicionar */
		prod* product = &prod_list[idp2];					/* produto que queremos adicionar */

		if (order->prod_list[idp2] == 0)
			/* produto nao existe na encomenda */
			order->len++;

		/* adiciona a quantidade a encomenda e retira do stock */
		order->prod_list[idp2] += (int) qt;
		product->qt -= qt;

		/* atualiza o peso da encomenda */
		order->weight += (int) qt * product->weight;
	}
}

/* remove stock a um produto */
void remove_stock() {
	int idp2;
	long int qt;
	prod* p;

	scanf("%d:%ld", &idp2, &qt);
	p = &prod_list[idp2];

	if (idp2 >= idp)  /* verifica se o produto existe */
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp2);
	else if (qt > p->qt) /* verifica se ha quantidade em stock */
		printf("Impossivel remover %ld unidades do produto %d do stock. Quantidade insuficiente.\n", qt, idp2);
	else
		p->qt -= qt;
}

/* remove um produto de uma encomenda */
void remove_prod() {
	int ide2, idp2;
	ord* o;
	prod* p;

	scanf("%d:%d", &ide2, &idp2);

	if (ide2 >= ide)  /* verifica se a encomenda existe */
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp2, ide2);
	else if (idp2 >= idp)  /* verifica se o produto existe */
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp2, ide2);
	else {
		long int qt;
		o = &ord_list[ide2];						 /* encomenda */
		p = &prod_list[idp2];						 /* produto */

		if (o->prod_list[idp2] == 0)
			/* o produto nao esta na encomenda */
			return;

		/* o produto esta na encomenda */
			
		qt = get_prod_qt(idp2, o);
			
		/* remove o produto da encomenda e repoe o seu stock */
		p->qt += qt;
		o->prod_list[idp2] = 0;

		o->len--;

		o->weight -= qt * p->weight;
	}
}

/* devolve o custo da encomenda */
void order_cost() {
	int ide2;

	scanf("%d", &ide2);

	if (ide2 >= ide) /* verifica se a encomenda existe */
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.", ide2);
	else
		printf("Custo da encomenda %d %ld.", ide2, calc_cost(&ord_list[ide2]));

	printf("\n");
}

/* altera o preco de um produto */
void change_price() {
	int idp2;
	long int price;

	scanf("%d:%ld", &idp2, &price);
	if (idp2 >= idp) /* verifica se o produto existe */
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp2);
	else
		prod_list[idp2].price = price;
}

/* mostra o produto na encomenda */
void show_prod() {
	int ide2, idp2;
	scanf("%d:%d", &ide2, &idp2);

	if (ide2 >= ide) /* verifica se a encomenda existe */
		printf("Impossivel listar encomenda %d. Encomenda inexistente.", ide2);
	else if (idp2 >= idp) /* verifica se o produto existe */
		printf("Impossivel listar produto %d. Produto inexistente.", idp2);
	else {
		printf("%s %d.", prod_list[idp2].desc, ord_list[ide2].prod_list[idp2]);
	}
	printf("\n");
}

/* mostra o produto que ocorre mais vezes nas encomendas */
void most_wanted() {
	int idp2;

	scanf("%d", &idp2);

	/* verifica se o produto existe */
	if (idp2 >= idp) {
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp2);
		return;
	}

	/* verifica se a encomenda existe */
	if (ide) {
		int maior = 0;									/* id da encomenda com maior numero de ocorrencias */
		long int qt = ord_list[0].prod_list[idp2];		/* numero de ocorrencias */
		int i;

		for (i = 1; i < ide; i++) {

			if (get_prod_qt(idp2, &ord_list[i]) > qt) {
				/* encontrou uma encomenda com mais ocorrencias que a anterior */
				maior = i;
				qt = ord_list[i].prod_list[idp2];
			}
		}

		/* verifica se o produto existe em alguma das encomendas */
		if (qt > 0)
			printf("Maximo produto %d %d %ld.\n", idp2, maior, qt);
	}
}

/* lista os produtos existentes no sistema (por ordem crescente de preco) */
void list_prod_sys() {
	int i;

	printf("Produtos\n");

	/* sort */
	radixsort(idp_list, idp);

	for (i = 0; i < idp; i++) {
		prod* p = &prod_list[idp_list[i]];
		printf("* %s %ld %ld\n", p->desc, p->price, p->qt);
		
		/* repoe a lista com os id originais */
		idp_list[i] = i;
	}
}

/* lista os produtos existentes numa encomenda (por ordem alfabetica) */
void list_prod_ord() {
	int ide2, i, n = 0;
	int* out;
	ord* o;

	scanf("%d", &ide2);
	if (ide2 >= ide) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide2);
		return;
	}

	printf("Encomenda %d\n", ide2);

	o = &ord_list[ide2];
	if (o->len == 0) /* verifica se a encomenda tem pelo menos um produto */
		return;

	out = can_fail_malloc(MAX_PROD * sizeof(int));			/* lista com os id dos produtos por ordem alfabetica */
	
	/* guarda os produtos que tem quantidade maior que 0 na lista 'out' */
	for (i = 0; i < MAX_PROD; i++)
		if (o->prod_list[i])
			*(out + n++) = i;

	/* sort */
	heapsort(out, n-1);

	for (i = 0; i < n; i++) {
		printf("* %s %ld %d\n", prod_list[out[i]].desc, prod_list[out[i]].price, o->prod_list[out[i]]);
	}

	free(out);
}