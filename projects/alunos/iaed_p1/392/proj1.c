#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 10000
#define MAX_DESC 64
#define MAX_ENCOMENDAS 500
#define MAX_PESO 200


struct produto {
	int id;
	char descricao[MAX_DESC];
	int preco;
	int peso;
	int stock;
};
struct produto prod[MAX_PRODUTOS];

/* estrutura de encomenda, contendo a estrutura do produto como variavel*/
struct encomenda {
	int id;
	struct produto prod[MAX_PESO];
};
struct encomenda enc[MAX_ENCOMENDAS];

/* Muda o valor do id de todas as variaveis de produto e encomenda para -1 */
void init() {
	int i, idx;
	for (i = 0; i < MAX_PRODUTOS; i++) {
		prod[i].id = -1;
	}
	for (i = 0; i < MAX_ENCOMENDAS; i++) {
		enc[i].id = -1;
		for (idx = 0; idx < MAX_PESO; idx++) {
			enc[i].prod[idx].id = -1;
		}
	}
}

/* cria um produto novo*/
void run_a(char descricao[], int preco, int peso, int qtd) {
	int i;

	/* verifica a proxima posicao vazia (id = -1) e insere os dados */
	for (i = 0; i < MAX_PRODUTOS; i++) {
		if (prod[i].id == -1) {
			prod[i].id = i;
			strcpy(prod[i].descricao, descricao);
			prod[i].preco = preco;
			prod[i].peso = peso;
			prod[i].stock = qtd;
			printf("Novo produto %d.\n", prod[i].id);

			break;
		}
	}
}


/*	adiciona stock a um produto*/
void run_q(int idp, int qtd) {
	/* verifica a existencia do produto atraves do id (se id=-1 o produto nao existe) */
	if (prod[idp].id == -1) {
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
		return;
	}
	prod[idp].stock += qtd;
}


/*	cria uma nova encomenda*/
void run_N() {
	int i;

	/* verifica qual a proxima posicao vazia (id=-1) para criar a nova encomenda */
	for (i = 0; i < MAX_ENCOMENDAS; i++) {
		if (enc[i].id == -1) {
			enc[i].id = i;
			printf("Nova encomenda %d.\n", i);
			break;
		}
	}
}


/*	adiciona produto a uma encomenda, com quantidade introduzida pelo utilizador*/
void run_A(int ide, int idp, int qtd) {
	int i, peso = 0;
	/*Calcula o peso da encomenda*/
	for (i = 0; i < MAX_PESO; i++) {
		if (enc[ide].prod[i].id != -1) {
			peso += (enc[ide].prod[i].peso * enc[ide].prod[i].stock);
		}
	}

	/*valida os varios parametros introduzidos */
	if (enc[ide].id != ide) {
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return;
	}
	if (prod[idp].id != idp) {
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	}
	if (prod[idp].stock < qtd) {
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		return;
	}
	if (prod[idp].peso * qtd + peso > 200) {
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
		return;
	}

	/* procura pelo id do produto na encomenda, caso exista, adiciona stock, se nao, cria um produto novo na encomenda */
	for (i = 0; i < MAX_PESO; i++) {
		if (enc[ide].prod[i].id == prod[idp].id) {
			enc[ide].prod[i].stock += qtd;
			prod[idp].stock -= qtd;
			return;
		}
		if (enc[ide].prod[i].id == -1){
			enc[ide].prod[i].id = idp;
			strcpy (enc[ide].prod[i].descricao, prod[idp].descricao);
			enc[ide].prod[i].preco = prod[idp].preco;
			enc[ide].prod[i].peso = prod[idp].peso;
			enc[ide].prod[i].stock = qtd;
			prod[idp].stock -= qtd;
			
			break;
		}
	}
}


/*	remove stock a um produto */
void run_r(int idp, int qtd) {
	/* verifica a existencia do produto e a sua quantidade atual */
	if (prod[idp].id == -1) {
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
		return;
	}
	if (prod[idp].stock < qtd) {
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
		return;
	}

	prod[idp].stock -= qtd;
}


/*	Remove um produto da encomenda*/
void run_R(int ide, int idp) {
	int i, idx;

	/* verifica a validade do parametros introduzidos */
	if (enc[ide].id == -1) {
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return;
	}

	if (prod[idp].id == -1) {
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	}

	/* procura na encomenda o produto com o mesmo ID introduzido pelo utilizador e remove-o */
	for (i = 0; i < MAX_PESO; i++) {
		if (enc[ide].prod[i].id == idp) {
			/* devolve o stock da encomenda ao produto global */
			prod[idp].stock += enc[ide].prod[i].stock;

			/* move os produtos que est?o ? direita do produto removido para a esquerda */
			for (idx = i; idx < MAX_PESO; idx++) {
				enc[ide].prod[idx].id = enc[ide].prod[idx+1].id;
				strcpy(enc[ide].prod[idx].descricao, enc[ide].prod[idx+1].descricao);
				enc[ide].prod[idx].preco = enc[ide].prod[idx+1].preco;
				enc[ide].prod[idx].peso = enc[ide].prod[idx+1].peso;
				enc[ide].prod[idx].stock = enc[ide].prod[idx+1].stock;
			}

			/* cria uma posicao vazia na ultima posicao dos produtos */
			enc[ide].prod[MAX_PESO-1].id = -1;
			strcpy(enc[ide].prod[MAX_PESO-1].descricao, "");
			enc[ide].prod[MAX_PESO-1].preco = 0;
			enc[ide].prod[MAX_PESO-1].peso = 0;
			enc[ide].prod[MAX_PESO-1].stock = 0;

			break;
		}
	}	
}


/*	conta o valor total do preco da encomenda*/
void run_C(int ide) {
	int i, total = 0;

	/* verifica a validade da encomenda */
	if (enc[ide].id == -1) {
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}

	for (i = 0; i < MAX_PESO; i++) {
		total += (enc[ide].prod[i].preco * enc[ide].prod[i].stock);
	}
	printf("Custo da encomenda %d %d.\n", ide, total);
}


/*	altera o preco de um produto*/
void run_p (int idp, int preco) {
	int i, idx;

	/* verifica a existencia do produto */
	if (prod[idp].id == -1) {
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
		return;
	}

	/* altera o preco do produta na variavel global e em qualquer encomenda que o produto esteja */
	prod[idp].preco = preco;
	for (i = 0; i < MAX_ENCOMENDAS; i++) {
		for (idx = 0; idx < MAX_PESO; idx++) {
			if (enc[i].prod[idx].id == prod[idp].id) {
				enc[i].prod[idx].preco = preco;
				break;
			}
		}
	}
}


/*	lista a descricao e o stock de um produta na encomenda pedida*/
void run_E (int ide, int idp) {
	int i;

	/* verifica a existencia da encomenda e do produto */
	if (enc[ide].id == -1) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}
	if (prod[idp].id == -1) {
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
		return;
	}

	/* procura pelo produto pedido na encomenda */
	for (i = 0; i < MAX_PESO; i++) {
		if (enc[ide].prod[i].id == prod[idp].id) {
			printf("%s %d.\n", prod[idp].descricao, enc[ide].prod[i].stock);
			break;
		}
	}
}


/*	verifica qual a encomenda que contem a maior quantidade do produto*/
void run_m (int idp) {
	int i, idx, ide, maior = 0;

	/* verifica a sua existencia */
	if (prod[idp].id == -1) {
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
		return;
	}

	/* verifica qual a encomenda com o maior stock do produto e guarda o seu valor */
	for (i = 0; i < MAX_ENCOMENDAS; i++) {
		for (idx = 0; idx < MAX_PESO; idx++) {
			if (enc[i].prod[idx].id == prod[idp].id) {
				if (enc[i].prod[idx].stock > maior) {
					maior = enc[i].prod[idx].stock;
					ide = enc[i].id;
				}
			}
		}
	}

	if (maior == 0) {
		return;
	}
	printf("Maximo produto %d %d %d.\n", idp, ide, maior);
}

/*	cria uma lista dos produtos existentes numa lista ordenada de forma crescente*/
void run_l () {
	int i, idx;
	
	/* cria varias variaveis auxiliares para permitir a troca de elementos sem perda de dados */
	char descrAux[MAX_DESC];
	int idAux, precoAux, qtdAux;

	/* cria uma estrutura local identica ? lista dos produtos existentes */	
	struct produto ord[MAX_PRODUTOS];
	for (i = 0; i < MAX_PRODUTOS; i++) {
		ord[i].id = prod[i].id;
		strcpy(ord[i].descricao, prod[i].descricao);
		ord[i].preco = prod[i].preco;
		ord[i].stock = prod[i].stock;
	}


	/* utiliza o insertion sort para ordenar os produtos existentes */
	for (i = 1; i < MAX_PRODUTOS; i++) {
		idAux = ord[i].id;
		strcpy (descrAux, ord[i].descricao);
		precoAux = ord[i].preco;
		qtdAux = ord[i].stock;

		/* considera as posi?oes vazias (id=-1) como sendo maiores, alterando assim a sua ordem */
		for (idx = i-1; idx >= 0; idx--) {
			if (precoAux >= ord[idx].preco && ord[idx].id != -1) {
				break;
			}
			ord[idx+1].id = ord[idx].id;
			strcpy(ord[idx+1].descricao, ord[idx].descricao);
			ord[idx+1].preco = ord[idx].preco;
			ord[idx+1].stock = ord[idx].stock;
		}

		ord[idx+1].id = idAux;
		strcpy (ord[idx+1].descricao, descrAux);
		ord[idx+1].preco = precoAux;
		ord[idx+1].stock = qtdAux;

	}
	
	/* lista os produtos ate a uma posicao vazia */
	printf("Produtos\n");
	for (i = 0; i < MAX_PRODUTOS; i++) {
		if (ord[i].id != -1) {
			printf("* %s %d %d\n", ord[i].descricao, ord[i].preco, ord[i].stock);
		}
	}
}


/*	cria uma lista dos produtos numa encomenda por ordem alfabetica*/
void run_L (int ide) {
	int i, idx;
	/* cria uma estrutura local identica ? encomenda atual para ordenar os produtos*/
	struct produto ord[MAX_PRODUTOS];
	
	/* cria variaveis auxiliares para permitar a troca de elementos sem perda de dados */
	char descrAux[MAX_DESC];
	int precoAux, qtdAux;

	/* valida a existencia da encomenda */
	if (enc[ide].id == -1) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}

	/* copia os valores dos produtos da encomenda para a estrura de ordena??o local */
	for (i = 0; i < MAX_PESO; i++) {
		ord[i].id = enc[ide].prod[i].id;
		strcpy(ord[i].descricao, enc[ide].prod[i].descricao);
		ord[i].preco = enc[ide].prod[i].preco;
		ord[i].stock = enc[ide].prod[i].stock;
	}

	/* utiliza bubble sorte para ordenar os produtos de ordem alfabetica */
	for (i = 0; i < MAX_PESO; i++) {
		/* se encontrar uma posicao vazia (id=-1) entao nao ha mais produtos */
		if (ord[i].id == -1) {
			break;
		}
		for (idx = 0; idx < MAX_PESO; idx++) {
			/* se encontrar um lugar vazio (id=-1) entao nao ha mais produtos para ordenar */
			if (ord[i].id == -1) {
			break;
		}
			
			/* compara a descricao dos produtos selecionados e verifica qual a que deve aparecer primeiro na ordena??o */
			if (strcmp(ord[i].descricao, ord[idx].descricao) < 0) {
				
				strcpy(descrAux, ord[i].descricao);
				precoAux = ord[i].preco;
				qtdAux = ord[i].stock;

				strcpy(ord[i].descricao, ord[idx].descricao);
				ord[i].preco = ord[idx].preco;
				ord[i].stock = ord[idx].stock;

				strcpy(ord[idx].descricao, descrAux);
				ord[idx].preco = precoAux;
				ord[idx].stock = qtdAux;
			}
		}
	}

	/* lista os produtos at? encontrar um lugar vazio (id=-1)*/
	printf("Encomenda %d\n", ide);
	for (i = 0; i < MAX_PESO; i++) {
		if (ord[i].id != -1) {
			printf("* %s %d %d\n", ord[i].descricao, ord[i].preco, ord[i].stock);
		}
	}

}


int main() {

/*	loop infinito com os respetivos comandos*/
	char command;
	char descricao[MAX_DESC];
	int ide, idp, preco, peso, qtd;
	/*inicializa as variaveis de ID para default*/
	init();
	/*espera pela linha de comando com os respetivos parametros*/
	while (1) {
		command = getchar();
		switch (command) {
			case 'a':
				scanf(" %[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);
				run_a(descricao, preco, peso, qtd);
				break;
			case 'q':
				scanf(" %d:%d", &idp, &qtd);
				run_q(idp, qtd);
				break;
			case 'N':
				run_N();
				break;
			case 'A':
				scanf(" %d:%d:%d", &ide, &idp, &qtd);
				run_A(ide, idp, qtd);
				break;
			case 'r':
				scanf(" %d:%d", &idp, &qtd);
				run_r(idp, qtd);
				break;
			case 'R':
				scanf(" %d:%d", &ide, &idp);
				run_R(ide, idp);
				break;
			case 'C':
				scanf(" %d", &ide);
				run_C(ide);
				break;
			case 'p':
				scanf(" %d:%d", &idp, &preco);
				run_p(idp, preco);
				break;
			case 'E':
				scanf(" %d:%d", &ide, &idp);
				run_E(ide, idp);
				break;
			case 'm':
				scanf(" %d", &idp);
				run_m(idp);
				break;
			case 'l':
				run_l();
				break;
			case 'L':
				scanf(" %d", &ide);
				run_L(ide);
				break;
			case 'x':
				return 0;
		}

	}

	return -1;
}