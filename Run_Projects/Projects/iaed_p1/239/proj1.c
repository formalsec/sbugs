#include <stdio.h>
#include <string.h>

/* Tamanho maximo da descricao de um produto */
#define MAXDESC 63	

/* Numero maximo de produtos no sistema */
#define MAXPRODS 10000			

/* Numero maximo de encomendas */
#define MAXENC 500

/* Peso maximo de cada encomenda */
#define PESO_MAX 200


/* Estrutura de um produto */
typedef struct {
	int id;
	char desc[MAXDESC];
	int preco;
	int peso;
	int qtd;
} produto; 


/* Estrutura de uma encomenda 
Contem numero de produtos na encomenda e produtos */
typedef struct {
	int numprods;				
	produto produtos[PESO_MAX];
} encomenda;


/* Array de produtos no sistema */
produto prods[MAXPRODS];

/* Numero de produtos no sistema */
int num_p;

/* Array de encomendas */
encomenda encomendas[MAXENC];

/* Numero de encomendas */
int num_e;

/* Auxiliares nas funcoes de ordenacao mergesort_n e mergesort_p */
produto a[MAXPRODS];
produto aux[MAXPRODS];


/* Comando 'a'
 Adiciona novo produto ao sistema atraves de inputs do terminal */
void add_prod() {
	scanf(" %63[^:]:%d:%d:%d", prods[num_p].desc, &prods[num_p].preco, &prods[num_p].peso, &prods[num_p].qtd);
	printf("Novo produto %d.\n", (prods[num_p].id = num_p));
	num_p++;
}


/* Comando 'q'
 Adiciona stock a um produto atraves de inputs do terminal  */
void add_stock() {
	int idp, qtd;
	scanf(" %d:%d", &idp, &qtd);

	/* Adiciona stock */
	if (idp < num_p) 
		prods[idp].qtd += qtd; 
	
	/* Erro */		
	else
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}


/* Comando 'N'
 Adiciona nova encomenda */
void add_enc() {

	/* Encomenda nao tem produtos */
	encomendas[num_e].numprods = 0;

	printf("Nova encomenda %d.\n", num_e++);
}


/* Calcula peso de uma encomenda */
int peso(encomenda enc) {
	int i, val = 0;

	/* Percorre produtos da encomenda e adiciona peso de cada um */
	for (i = 0; i < enc.numprods; i++)
		val += enc.produtos[i].peso * enc.produtos[i].qtd;

	return val;
}


/* Descobre indice do produto com id idp 
na encomenda com id ide */
int ind(int idp, int ide) {
	int i;

	/* Percorre produtos da encomenda e devolve o indice se o seu id corresponde ao idp procurado */
	for (i = 0; i < encomendas[ide].numprods; i++) {
		if (encomendas[ide].produtos[i].id == idp)
			return i;
	}

	/* Produto nao esta na encomenda */
	return -1;
}


/* Adiciona novo produto a uma encomenda 
Devolve indice do produto na encomenda */
int novo_prod_enc(int idp, int ide) {
	int n = encomendas[ide].numprods;

	encomendas[ide].produtos[n] = prods[idp];
	encomendas[ide].produtos[n].qtd = 0;

	return encomendas[ide].numprods++;
}


/* Comando 'A'
 Adiciona produto a encomenda */
void add_prod_enc() {
	int ide, idp, qtd;
	scanf(" %d:%d:%d", &ide, &idp, &qtd);

	/* Erros */
	if (ide >= num_e)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if (idp >= num_p)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else if (prods[idp].qtd < qtd)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	else if (peso(encomendas[ide]) + prods[idp].peso * qtd > PESO_MAX)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);

	/* Adiciona produto a encomenda e remove do stock*/
	else {
		/* Indice do produto na encomenda */
		int i = ind(idp, ide);

		/* Produto nao esta na encomenda, adicionar a encomenda */
		if (i == -1)
			i = novo_prod_enc(idp, ide);

		/* Adicionar stock a encomenda e retirar do sistema*/
		encomendas[ide].produtos[i].qtd += qtd;
		prods[idp].qtd -= qtd;
	}
}


/* Comando 'r'
 Remove stock a um produto existente */
void rm_stock() {
	int idp, qtd;
	scanf(" %d:%d", &idp, &qtd);

	/* Erros */
	if (idp >= num_p)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	else if (prods[idp].qtd < qtd)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);

	/* Remove stock ao produto */
	else
		prods[idp].qtd -= qtd;
}


/* Comando 'R'
 Remove produto de uma encomenda */
void rm_prod_enc() {
	int ide, idp;
	scanf(" %d:%d", &ide, &idp);

	/* Erros */
	if (ide >= num_e)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if (idp >= num_p)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

	/* Remove produto da encomenda e repoe stock no sistema */
	else {
		int i = ind(idp, ide);

		/* Se o produto esta na encomenda, remove-o e adiciona ao sistema */
		if (i != -1) {
			prods[idp].qtd += encomendas[ide].produtos[i].qtd;
			encomendas[ide].produtos[i].qtd = 0;
		}
	}
}


/* Comando 'C'
 Calcula custo de uma encomenda a escolha */
void cost() {
	int ide;
	scanf(" %d", &ide);
	
	/* Erro */
	if (ide >= num_e) 
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);

	/* Calcula e imprime custo da encomenda */
	else {
		int i, val = 0;

		/* Percorre encomenda e adiciona valor (quantidade*preco) de cada produto ao preco */
		for (i = 0; i < encomendas[ide].numprods; i++)
			val += encomendas[ide].produtos[i].qtd * encomendas[ide].produtos[i].preco;
		
	printf("Custo da encomenda %d %d.\n", ide, val);
	}
}


/* Atualiza preco de um produto nas encomendas */
void update_preco(int idp) {
	int i;
	int npreco = prods[idp].preco;

	/* Percorre encomendas e, se o produto pertence a encomenda, atualiza preco */
	for (i = 0; i < num_e; i++) {
		int j = ind(idp, i);
		/* Se produto pertence a encomenda, altera preco */
		if (j != -1)
			encomendas[i].produtos[j].preco = npreco;
	}
}


/* Comando 'p'
 Altera preco do produto para o preco escolhido */
void alt_preco() {
	int idp, preco;
	scanf(" %d:%d", &idp, &preco);
	
	/* Erro */
	if (idp >= num_p)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);

	/* Muda preco no sistema e nas encomendas */
	else {
		prods[idp].preco = preco;
		update_preco(idp);
	}
}


/* Comando 'E'
 Imprime a descri??o e quantidade do produto escolhido */
void prod_info() {
	int ide, idp;
	scanf(" %d:%d", &ide, &idp);

	/* Erros */
	if (ide >= num_e)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else if (idp >= num_p)
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);

	/* Imprime informacoes */
	else {
		int i = ind(idp, ide);

		/* Produto nao esta na encomenda */
		if (i == -1)
			printf("%s %d.\n", prods[idp].desc, 0);

		/* Produto esta na encomenda */
		else
			printf("%s %d.\n", encomendas[ide].produtos[i].desc, encomendas[ide].produtos[i].qtd);
	}
}


/* Comando 'm'
 Imprime o identificador da encomenda em que o produto ocorre mais vezes */
void max_prod() {
	int idp;
	scanf(" %d", &idp);

	/* Erro */
	if (idp >= num_p)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);

	/* Encontra encomenda em que o produto ocorre mais vezes */
	else {
		int i, ide = 0, high = 0;

		/* Percorre encomendas para descobrir em qual delas existe maior quantidade do produto */
		for (i = 0; i < num_e; i++) {
			int j = ind(idp, i);
			if (j >= 0 && encomendas[i].produtos[j].qtd > high) {
				ide = i;
				high = encomendas[i].produtos[j].qtd;
			}
		}
		
		if (high > 0)
			printf("Maximo produto %d %d %d.\n", idp, ide, high);
	}
}


/* Junta os subarrays do mergesort_p */
void merge_p(int l, int m, int r) {
	int i, j, k;

	/* Constroi o vetor auxiliar */
	for (i = m+1; i > l; i--)
		aux[i-1] = a[i-1];
	for (j = m; j < r; j++)
		aux[r+m-j] = a[j+1];

	/* Junta arrays */
	for (k = l; k <= r; k++) {
		if (aux[j].preco < aux[i].preco || i > m)
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
	}
}


/* Funcao que ordena produtos por ordem de precos */
void mergesort_p(int l, int r) {
	int m = (r + l)/2;

	if (r <= l)
		return;

	/* Ordena as duas metades */
	mergesort_p(l, m);
	mergesort_p(m+1, r);

	/* Junta as duas metades */
	merge_p(l, m, r);
}


/* Copia array de produtos */
void cpyprods(produto to[], produto from[], int lim) {
	int i;

	for (i = 0; i <= lim; i++)
		to[i] = from[i];
}


/* Comando 'l'
 Imprime produtos do sistema pela ordem do pre?o */
void sort_price() {
	int l = 0, r = num_p - 1;

	/* Copia produtos para array auxiliar */
	cpyprods(a, prods, r);
	
	/* Ordena produtos atraves do algoritmo Merge Sort */
	mergesort_p(l, r); 

	/* Imprime produtos ordenados */
	printf("Produtos\n");
	for (l = 0; l < num_p; l++)
		printf("* %s %d %d\n", a[l].desc, a[l].preco, a[l].qtd);
}


/* Junta os subarrays do mergesort_n */
void merge_n(int l, int m, int r) {
	int i, j, k;

	/* Constroi o vetor auxiliar */
	for (i = m+1; i > l; i--)
		aux[i-1] = a[i-1];
	for (j = m; j < r; j++)
		aux[r+m-j] = a[j+1];

	/* Junta arrays */
	for (k = l; k <= r; k++) {
		if (strcmp(aux[j].desc, aux[i].desc) < 0 || i > m)
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
	}
}


/* Ordena produtos por ordem alfabetica da descricao */
void mergesort_n(int l, int r) {
	int m = (r + l)/2;

	if (r <= l)
		return;

	/* Ordena as duas metades */
	mergesort_n(l, m);
	mergesort_n(m+1, r);

	/* Junta as duas metades */
	merge_n(l, m, r);
}


/* Comando 'L'
 Imprime produtos de uma encomenda pela ordem alfabetica da descricao */
void sort_name() {
	int ide, l, r;
	scanf(" %d", &ide);

	/* Limites do array */
	l = 0; r = encomendas[ide].numprods - 1;

	/* Erro */
	if (ide >= num_e)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

	else {
		/* Copia produtos da encomenda para array auxiliar */
		cpyprods(a, encomendas[ide].produtos, r);

		/* Ordena elementos alfabeticamente */
		mergesort_n(l, r);

		/* Imprime produtos por ordem */
		printf("Encomenda %d\n", ide);
		for (l = 0; l <= r; l++) {

			/* Produto esta na encomenda */
			if (a[l].qtd > 0)
				printf("* %s %d %d\n", a[l].desc, a[l].preco, a[l].qtd);
		}
	}
}


/* Lida com o comando recebido e realiza as operacoes adequadas */
void comand(char c) {

	/* Valor da tecla premida */
	switch(c) {

		/* Adiciona novo produto ao sistema */
		case 'a':
			add_prod();
			break;

		/* Adiciona stock a um produto existente */
		case 'q':
			add_stock();
			break;

		/* Adiciona uma nova encomenda */
		case 'N':
			add_enc();
			break;

		/* Adiciona produto a encomenda ou, se ja existir, adiciona quantidade a quantidade existente */
		case 'A':
			add_prod_enc();
			break;

		/* Remove stock a um produto existente */
		case 'r':
			rm_stock();
			break;

		/* Remove produto de uma encomenda */
		case 'R':
			rm_prod_enc();
			break;

		/* Calcula o custo de uma encomenda */
		case 'C':
			cost();
			break;

		/* Altera o pre?o de um produto existente no sistema */
		case 'p':
			alt_preco();
			break;

		/* Lista a descri??o e a quantidade de um produto numa encomenda */
		case 'E':
			prod_info();
			break;

		/* Lista o identificador da encomenda em que o produto dado ocorre mais vezes */
		case 'm':
			max_prod();
			break;

		/* Lista todos os produtos existentes no sistema por ordem crescente de preco */
		case 'l':
			sort_price();
			break;

		/* Lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
		case 'L':
			sort_name();
			break;
	}
}


/* Recebe comando do terminal e efetua acao correspondente */
int main() {
	char c;

	/* Lida com inputs sucessivos do terminal 
	Termina com o carater 'x' */
	while ((c = getchar()) != 'x')
		comand(c);

	return 0;
}
