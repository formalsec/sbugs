#include <stdio.h>

int cont = 0;
int idp = 0;
int ide = 0;
int cont_produtos = 0;  
int cont_encomendas = 0;

typedef struct produto {
	int idp;
	char descricao[63];
	int preco;
	int peso;
	int qtd;
} Produto;

typedef struct encomenda {
	int ide;
	int cont_produtos;
	int preco;
	Produto produtos_na_encomenda[200];
	int peso;
} Encomenda;

Produto inventario[10000];

Encomenda todas_encomendas[500];



void adiciona_produto() {
	int preco, peso, qtd;
	Produto a;
	scanf("%[^:]:%d:%d:%d", a.descricao, &preco, &peso, &qtd);
	a.idp = idp;
	idp++;
	a.preco = preco;
	a.peso = peso;
	a.qtd = qtd;
	inventario[a.idp] = a;
	printf("Novo produto %d.\n", a.idp);
}



void adiciona_stock() {
	int ESTADO = 0;
	int i;
	Produto ex;
	scanf("%d:%d", &ex.idp, &ex.qtd);
	for (i = 0; i < cont; i++) {
		if (inventario[i].idp == ex.idp) {
			ESTADO = 1;
			inventario[i].qtd += ex.qtd;
		}
		
	}
	if (ESTADO == 0) printf("Impossivel adicionar produto %d ao stock. Produto nao existente.\n", ex.idp);
}



void nova_encomenda() {
	Encomenda b;
	b.ide = ide;
	ide++;
	b.peso = 0;
	todas_encomendas[b.ide] = b;
	printf("Nova encomenda %d.\n", b.ide);
}



void adiciona_produto_encomenda() {
	int ESTADO = 0;
	int i;
	Produto p;
	Encomenda q;
	scanf("%d:%d:%d", &q.ide, &p.idp, &p.qtd);	
	if (q.ide > (cont_encomendas - 1)) printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", p.idp, q.ide);
	else if (p.idp > (cont - 1)) printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.", p.idp, q.ide);
	else if (inventario[p.idp].qtd < p.qtd) printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", p.idp, q.ide);
	else if ((todas_encomendas[q.ide].peso + (inventario[p.idp].peso * p.qtd)) > 200) printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", p.idp, q.ide);
	
	else {
		for (i = 0; i < todas_encomendas[q.ide].cont_produtos; i++) {
			if (todas_encomendas[q.ide].produtos_na_encomenda[i].idp == p.idp) {
				ESTADO = 1;
				todas_encomendas[q.ide].produtos_na_encomenda[i].qtd += p.qtd;
				todas_encomendas[q.ide].peso += (inventario[p.idp].peso * p.qtd);
				todas_encomendas[q.ide].preco += (inventario[p.idp].preco * p.qtd);
				inventario[p.idp].qtd -= p.qtd;
			}
		}
		if (ESTADO == 0) {
			todas_encomendas[q.ide].produtos_na_encomenda[i] = inventario[p.idp];
			todas_encomendas[q.ide].peso += (inventario[p.idp].peso * p.qtd);
			todas_encomendas[q.ide].preco += (inventario[p.idp].preco * p.qtd);	
			inventario[p.idp].qtd -= p.qtd; 
			todas_encomendas[q.ide].cont_produtos++;
		}
	}
}



void remove_da_encomenda() {
	int ESTADO = 0;
	int ESTADO2 = 0;
	int i, j;
	Encomenda b;
	Produto a;
	scanf("%d:%d", &b.ide, &a.idp);
	for (i = 0; i < cont_encomendas; i++) {
		if (todas_encomendas[i].ide == b.ide) {
			ESTADO = 1;
			for (j = 0; j < cont; j++) {
				if (inventario[j].idp == a.idp) {
					ESTADO2 = 1;
					todas_encomendas[b.ide].preco -= (inventario[j].preco * todas_encomendas[b.ide].produtos_na_encomenda[a.idp].qtd);
					todas_encomendas[b.ide].peso -= (inventario[j].peso * todas_encomendas[b.ide].produtos_na_encomenda[a.idp].qtd);
					inventario[j].qtd += todas_encomendas[b.ide].produtos_na_encomenda[a.idp].qtd;
					todas_encomendas[b.ide].produtos_na_encomenda[a.idp].idp = 0;
					todas_encomendas[b.ide].cont_produtos--;
				}	
			}		
			if (ESTADO2 == 0) printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", a.idp, b.ide);
		}
	}
	if (ESTADO == 0) printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", a.idp, b.ide);
} 



void remove_stock() {
	int ESTADO = 0;
	int ESTADO2 = 0;
	int i;
	Produto a;
	scanf("%d:%d", &a.idp, &a.qtd);
	for (i = 0; i < cont; i++) {
		if (inventario[i].idp == a.idp) {
			ESTADO = 1;
			if (inventario[i].qtd > a.qtd) {
				ESTADO2 = 1;
				inventario[i].qtd = inventario[i].qtd - a.qtd;
			}
		}
	}
	if (ESTADO == 0) printf("Impossivel remover stock do produto %d. Produto inexistente.\n", a.idp);
	if (ESTADO2 == 0) printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", a.qtd, a.idp);
}



void custo() {
	int ESTADO = 0;
	int i;
	Encomenda b;
	scanf("%d", &b.ide);
	for (i = 0; i < cont_encomendas; i++) {
		if (todas_encomendas[i].ide == b.ide) {
			ESTADO = 1;
			printf("Custo da encomenda %d %d.\n", b.ide, todas_encomendas[i].preco);
		}
	}
	if (ESTADO == 0) printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", b.ide);
}



void altera_preco() {
	int i;
	Produto a;
	scanf("%d:%d", &a.idp, &a.preco);
	for (i = 0; i <= cont; i++) {
		if (i == cont) printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", a.idp);
		else if (inventario[i].idp == a.idp) inventario[i].preco = a.preco;
	}
}



int main() {
	char command;
	while(1) {
		command = getchar();
		switch(command) {
			case 'a':
				cont++;
				adiciona_produto();
				break;

			case 'q':
				adiciona_stock();  /*nao esta a funcionar*/
				break;

			case 'N':
				cont_encomendas++;
				nova_encomenda();
				break;

			case 'A':
				adiciona_produto_encomenda();
				break;

			case 'r':
				remove_stock();
				break;

			case 'R':
				remove_da_encomenda();
				break;

			case 'C':
				custo();
				break;

			case 'p':
				altera_preco();
				break;

			case 'E':
				break;

			case 'm':
				/* Chama a funcao responsavel pela execucao do comando m */

				break;

			case 'l':
				/* Chama a funcao responsavel pela execucao do comando l */

				break;

			case 'L':
				/* Chama a funcao responsavel pela execucao do comando L */

				break;

			case 'x':
				return 0;

			default:
				printf("ERRO: Comando desconhecido\n");
		}

		getchar(); /* le o '\n' introduzido pelo utilizador */
	}


	return -1; /* se chegou aqui algo correu mal*/ 
}
