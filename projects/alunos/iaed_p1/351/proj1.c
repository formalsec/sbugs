#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/*
-desmax:
+1 espaco do que e pedido para o stopper da string '\0'

-epmax:
numero maximo de produtos numa encomenda 
(minimo de peso de um produto = 1 
e maximo de peso de encomenda = 200 
por isso a encomenda tem no maximo 200 produtos simultaneamente) 
*/
#define pmax 10000
#define desmax 64 
#define emax 500
#define epmax 200 


/* 
apesar da maior parte das funcoes 
usarem o indice do array "produtos" como id,
adicionei a variavel id a estrutura para estabilizar 
o algoritmo de ordenacao atribuido a 'l' 
*/
struct produto{
	char descricao[desmax];
	int preco, peso, qtd, id;
};


/* 
um indice no array id representa o mesmo produto 
que tenha o mesmo indice no array quantidades 
*/
struct encomenda{
	int id[epmax], quantidades[epmax], id_atual;
};


/*
o array "a2" servira como array auxiliar para ordenacao,
os outros servirao para guardar os produtos e encomendas, respetivamente
*/
struct produto a2[pmax];

struct produto produtos[pmax];

struct encomenda encomendas[emax];


/* inicializa um novo produto, a partir do input do utilizador */
void novo_produto(int id){
	char d[desmax];
	int preco, peso, qtd;

	scanf(" %[^:]:%d:%d:%d", d, &preco, &peso, &qtd);

	strcpy(produtos[id].descricao, d);
	produtos[id].preco = preco;
	produtos[id].peso = peso;
	produtos[id].qtd = qtd;
	produtos[id].id = id;

	printf("Novo produto %d.\n", id);
}


/* adiciona stock a um produto, consoante o input */
void adc_stock(int id_atual){
	int id, qtd;
	scanf("%d:%d", &id, &qtd);

	if(id_atual >= id)
		produtos[id].qtd += qtd;
	else
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
}


/* inicializa uma nova encomenda */
void cria_encomenda(int id){
	encomendas[id].id_atual = -1;
	printf("Nova encomenda %d.\n", id);
}


/* adiciona um produto a uma encomenda ou adiciona stock se o produto ja existir */
void adc_prod_encomenda(int id_atual_p, int id_atual_e){
	int i, ide, idp, qtd, peso = 0, existe = -1;
	scanf("%d:%d:%d", &ide, &idp, &qtd);

	if(ide > id_atual_e){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return;
	}
	else if(idp > id_atual_p){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	}
	else if(qtd > produtos[idp].qtd){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		return;
	}

	/* ciclo 2 em 1: calcula o peso e verifica se o produto ja existe, guardando o indice */
	for(i = 0; i < encomendas[ide].id_atual + 1; i++){
		peso += produtos[encomendas[ide].id[i]].peso * encomendas[ide].quantidades[i];
		if(idp == encomendas[ide].id[i]){
			existe = i;
		}
	}

	/* complementa o ciclo anterior: adiciona o peso do produto em questao */
	peso += produtos[idp].peso * qtd;

	if(peso > 200)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
	else if(existe != -1){
		/* adiciona stock a encomenda e remove essa quantidade ao stock normal do produto */
		produtos[idp].qtd -= qtd;
		encomendas[ide].quantidades[existe] += qtd;
	}
	else{
		/* o mesmo que o anterior, mas inicializa o produto na encomenda */
		produtos[idp].qtd -= qtd;
		encomendas[ide].id_atual++;
		encomendas[ide].id[encomendas[ide].id_atual] = idp;
		encomendas[ide].quantidades[encomendas[ide].id_atual] = qtd;
	}
}


/* remove stock a um produto, consoante o input */
void remove_stock(int id_atual){
	int id, qtd;
	scanf("%d:%d", &id, &qtd);

	if(id_atual < id)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
	else if(produtos[id].qtd < qtd)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id);
	else
		produtos[id].qtd -= qtd;
}


/* remove um produto de uma encomenda */
void remove_produto(int id_atual_e, int id_atual_p){
	int i, ide, idp, estado = 0, k;
	scanf("%d:%d", &ide, &idp);

	if(ide > id_atual_e){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	} else if(idp > id_atual_p){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	} else{
		/* procura o produto na encomenda e ativa a flag "estado" se existir */
		for(i = 0; i < encomendas[ide].id_atual + 1; i++){
			if(encomendas[ide].id[i] == idp){
				estado = 1;
				k = i;
			}
		}

		if(estado == 1){
			/* devolve o stock ao produto */
			produtos[idp].qtd += encomendas[ide].quantidades[k];

			/* move todos os produtos nos arrays das encomendas 1 indice para tras, 
			a partir do produto removido. o espaco da encomenda nao da para todos 
			os produtos que possam existir e assim liberta-se espaco */
			for(i = k; i < encomendas[ide].id_atual; i++){
				encomendas[ide].id[i] = encomendas[ide].id[i+1];
				encomendas[ide].quantidades[i] = encomendas[ide].quantidades[i+1];
			}
			encomendas[ide].id_atual--;
		}
	}
}


/* calcula o custo total de uma encomenda dada */
void custo_encomenda(int id_atual_e){
	int ide, i, preco = 0;
	scanf("%d", &ide);

	if(ide > id_atual_e)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	else{
		/* ciclo que calcula o preco, dependendo do custo e quantidade de cada produto */
		for(i = 0; i < encomendas[ide].id_atual + 1; i++){
			preco += produtos[encomendas[ide].id[i]].preco * encomendas[ide].quantidades[i];
		}
		printf("Custo da encomenda %d %d.\n", ide, preco);
	}
}


/* altera o preco de um produto (em todo o sistema) */
void altera_preco(int id_atual_p){
	int idp, preco;
	scanf("%d:%d", &idp, &preco);

	if(idp > id_atual_p)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	else
		produtos[idp].preco = preco;
}


/* procura um produto numa encomeda e lista a sua descricao e quantidade nela */
void prod_na_enc(int id_atual_e, int id_atual_p){
	int ide, idp, i, tracker = -1;
	scanf("%d:%d", &ide, &idp);

	if(ide > id_atual_e){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	} else if(idp > id_atual_p){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	} else{
		/* encontra o produto e regista o id em "tracker" */
		for(i = 0; i < encomendas[ide].id_atual + 1; i++){
			if(idp == encomendas[ide].id[i])
				tracker = i;
		}
		printf("%s %d.\n", produtos[idp].descricao, encomendas[ide].quantidades[tracker]);
	}
}


/* procura qual e a encomenda em que certo produto tem maior stock */
void max_ocorrencia_produto(int id_atual_p, int id_atual_e){
	int idp, max = -1, idemax, i, j;
	scanf("%d", &idp);

	if(idp > id_atual_p)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	else{
		/* nested for loops para percorrer todos os produtos de todas as encomendas */
		for(i = 0; i < id_atual_e + 1; i++){
			for(j = 0; j < encomendas[i].id_atual + 1; j++){
				if(encomendas[i].id[j] == idp && encomendas[i].quantidades[j] > max){
					max = encomendas[i].quantidades[j];
					idemax = i;
				}
			}
		}
		if(max != -1)
			printf("Maximo produto %d %d %d.\n", idp, idemax, max);
	}
}


/* as 2 funcoes a seguir servem para implementar o algoritmo 
merge sort que organiza os produtos todos por ordem crescente do preco */
void merge_preco(struct produto a[], int l, int m, int r){
	int i, j, k;

	for(i = m+1; i > l; i--)
		a2[i-1] = a[i-1];

	for(j = m; j < r; j++)
		a2[r+m-j] = a[j+1];

	for(k = l; k <= r; k++)
		if(a2[j].preco < a2[i].preco)
			a[k] = a2[j--];

		/* a unica parte que difere do codigo utilizado nas aulas, para establilizar o algoritmo */
		else if(a2[j].preco == a2[i].preco && a2[j].id < a2[i].id)
			a[k] = a2[j--];

		else
			a[k] = a2[i++];
}

void mergesort_preco(struct produto prod[], int l, int r){
	int m = (r+l)/2;
	if (r <= l) 
		return;
	mergesort_preco(prod, l, m);
	mergesort_preco(prod, m+1, r);
	merge_preco(prod, l, m, r);
}


/* utiliza o algoritmo merge sort implementado previamente para organizar todos os produtos */
void lista_todos(int id_atual_p){
	int i;
	struct produto p[pmax];

	/* cria uma copia para "p" para nao "desorganizar" o original */
	for(i = 0; i < id_atual_p + 1; i++){
			p[i] = produtos[i];
	}

	mergesort_preco(p, 0, id_atual_p);

	printf("Produtos\n");

	for(i = 0; i < id_atual_p + 1; i++){
		printf("* %s %d %d\n", p[i].descricao, p[i].preco, p[i].qtd);
	}
}


/* organiza todos os produtos de uma encomenda, usando bubble sort, pois o array a organizar e relativamente pequeno*/
void lista_encomenda(int id_atual_e){
	int ide, i, j;
	struct produto aux, p[epmax];

	scanf("%d", &ide);

	if(ide > id_atual_e)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else{
		/* cria copia, usando as quantidades da encomenda na estrutura do produto */
		for(i = 0; i < encomendas[ide].id_atual + 1; i++){
			p[i] = produtos[encomendas[ide].id[i]];
			p[i].qtd = encomendas[ide].quantidades[i];
		}

		/* implemntacao do algoritmo bubble sort, mais uma vez, nao se justifica um algoritmo complexo */
		for(i = 0; i < encomendas[ide].id_atual; i++){
			for(j = 0; j < encomendas[ide].id_atual - i; j++){
				if(strcmp(p[j].descricao, p[j+1].descricao) > 0){
					aux = p[j];
					p[j] = p[j+1];
					p[j+1] = aux;
				}
			}
		}

		printf("Encomenda %d\n", ide);

		for(i = 0; i < encomendas[ide].id_atual + 1; i++){
			printf("* %s %d %d\n", p[i].descricao, p[i].preco, p[i].qtd);
		}
	}
}


int main(){
	char c;
	int id_p = -1, id_e = -1;

	while(c != 'x'){
		c = getchar();

		switch(c){
			case 'a':
				id_p++;
				novo_produto(id_p);
				break;

			case 'q':
				adc_stock(id_p);
				break;

			case 'N':
				id_e++;
				cria_encomenda(id_e);
				break;

			case 'A':
				adc_prod_encomenda(id_p, id_e);
				break;

			case 'r':
				remove_stock(id_p);
				break;

			case 'R':
				remove_produto(id_e, id_p);
				break;

			case 'C':
				custo_encomenda(id_e);
				break;

			case 'p':
				altera_preco(id_p);
				break;

			case 'E':
				prod_na_enc(id_e, id_p);
				break;

			case 'm':
				max_ocorrencia_produto(id_p, id_e);
				break;

			case 'l':
				lista_todos(id_p);
				break;

			case 'L':
				lista_encomenda(id_e);
				break;
		}

	}
	return 0;
}