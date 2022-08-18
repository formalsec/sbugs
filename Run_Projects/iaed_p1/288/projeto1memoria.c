#include <stdio.h>
#include <string.h>

/*Numero maximo de produtos*/
#define PMAX 10000
/*Numero maximo de encomendas*/
#define EMAX 500
/*Peso maximo por encomenda*/
#define PESOMAX 200
/*Numero de carateres maximo da descricao de um produto*/
#define DESCRICAOMAX 64


typedef struct 
{
	int idp, preco, peso, qtd;
	char descricao[DESCRICAOMAX];
} PRODUTO;

typedef struct
{
	int ide, preco, peso;
	int produtos[PMAX];
} ENCOMENDA;


/*Prototipos de funcoes*/
void cria_produto();
void adiciona_qtd();
void cria_encomenda();
void adiciona_prod();
void remove_stock();
void remove_prod();
void custo_encomenda();
void altera_preco();
void des_qtd_enc();
void prod_mais_qtd();
void ordem_precos();
void ordem_prod_enc();

void mergesort_l(PRODUTO a[], int l, int r);
void merge_l(PRODUTO a[], int l, int m, int r);
void mergesort_L(PRODUTO a[], int l, int r);
void merge_L(PRODUTO a[], int l, int m, int r);


/*Vetor com todos os produtos por ordem de idp*/
PRODUTO sistema[PMAX];
/*Vetor com todas as encomendas por ordem de ide*/
ENCOMENDA sistema_encomendas[EMAX];
/*Contador de idps: idp do proximo produto a criar/indice do proximo produto no vetor sistema*/
int idps_sistema = 0;
/* Contador de ides: ide da proxima encomenda a criar/indice da proxima encomenda no vetor de encomendas*/
int ides_encomendas = 0;


/************
 * PROGRAMA *
 ************/

int main(){
	char c;

	while (1){

		c = getchar();
		switch (c)
		{
			case 'a': cria_produto(); break;
			case 'q': adiciona_qtd(); break;
			case 'N': cria_encomenda(); break;
			case 'A': adiciona_prod(); break;
			case 'r': remove_stock(); break;
			case 'R': remove_prod(); break;
			case 'C': custo_encomenda(); break;
			case 'p': altera_preco(); break;
			case 'E': des_qtd_enc(); break;
			case 'm': prod_mais_qtd(); break;
			case 'l': ordem_precos(); break;
			case 'L': ordem_prod_enc(); break;
			case 'x': return 0;
		}
	}
	return 0;
}

/* a - Adiciona um novo produto ao sistema.*/
void cria_produto(){
	int pr, ps, q;
	char d[DESCRICAOMAX];
	PRODUTO novo;

	scanf(" %[^:]:%d:%d:%d", d, &pr, &ps, &q);

	novo.idp = idps_sistema;
	idps_sistema += 1;

	strcpy(novo.descricao, d);
	novo.preco = pr;
	novo.peso = ps;
	novo.qtd = q;

	sistema[novo.idp] = novo;

	printf("Novo produto %d.\n", novo.idp);
}

/* q - Adiciona stock (quantidade) a um produto no sistema.*/
void adiciona_qtd(){
	int id, q;

	scanf(" %d:%d", &id, &q);

	if (id >= idps_sistema)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
	else
		sistema[id].qtd += q;
}

/* N - Cria uma nova encomenda.*/
void cria_encomenda(){
	int i;
	ENCOMENDA nova;

	nova.ide = ides_encomendas;
	ides_encomendas += 1;

	nova.preco = 0;
	nova.peso = 0;

	for (i = 0; i < PMAX ; i++)
		nova.produtos[i] = 0;

	sistema_encomendas[nova.ide] = nova;

	printf("Nova encomenda %d.\n", nova.ide);
}

/* A - Adiciona um produto a uma encomenda/adiciona quantidade de um produto ja existente.*/
void adiciona_prod(){
	int e, p, q;

	scanf(" %d:%d:%d", &e, &p, &q);

	if (e >= ides_encomendas)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", p, e);
		return;
	}
	if (p >= idps_sistema)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", p, e);
		return;
	}
	if (sistema[p].qtd < q)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", p, e);
		return;
	}
	if ((sistema_encomendas[e].peso + sistema[p].peso*q) > PESOMAX)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", p, e);
		return;
	}	
	/*altera o preco e o peso*/
	sistema_encomendas[e].preco += sistema[p].preco * q;
	sistema_encomendas[e].peso += sistema[p].peso * q;
	/*adiciona quantidade*/
	sistema_encomendas[e].produtos[p] += q;
	/*remove qtd do sistema*/
	sistema[p].qtd -= q;
}

/* r - Remove stock a um produto existente no sistema.*/
void remove_stock(){
	int p, q;

	scanf(" %d:%d", &p, &q);

	if (p >= idps_sistema)
	{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", p);
		return;
	}
	if ((sistema[p].qtd - q) < 0)
	{
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", q, p);
		return;
	}

	sistema[p].qtd -= q;
}

/* R - Remove um produto a uma encomenda.*/
void remove_prod(){
	int e, p;

	scanf(" %d:%d", &e, &p);

	if (e >= ides_encomendas)
	{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", p, e);
		return;
	}
	if (p >= idps_sistema)
	{
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", p, e);
		return;
	}

	/*remover produto da encomenda*/
	/*altera o preco e o peso*/
	sistema_encomendas[e].preco -= sistema[p].preco * sistema_encomendas[e].produtos[p];
	sistema_encomendas[e].peso -= sistema[p].peso * sistema_encomendas[e].produtos[p];
	/*devolve a qtd ao sistema*/
	sistema[p].qtd += sistema_encomendas[e].produtos[p];
	/*qtd do produto na encomenda a 0*/
	sistema_encomendas[e].produtos[p] = 0;
}

/* C - Calcula o custo de uma encomenda.*/
void custo_encomenda(){
	int e;

	scanf(" %d", &e);

	if (e >= ides_encomendas)
	{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", e);
		return;
	}

	printf("Custo da encomenda %d %d.\n", e, sistema_encomendas[e].preco);
}

/* p - Altera o preco de um produto existente no sistema.*/
void altera_preco(){
	int p, novo_preco, i;

	scanf(" %d:%d", &p, &novo_preco);

	if (p >= idps_sistema)
	{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", p);
		return;
	}

	for (i = 0; i < ides_encomendas; i++)
	{
		if (sistema_encomendas[i].produtos[p] != 0)
			sistema_encomendas[i].preco += (novo_preco - sistema[p].preco) * sistema_encomendas[i].produtos[p];
	}

	sistema[p].preco = novo_preco;
}

/* E - Lista a descricao e a quantidade de um produto numa encomenda.*/
void des_qtd_enc(){
	int e, p;

	scanf(" %d:%d", &e, &p);

	if (e >= ides_encomendas)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", e);
		return;
	}
	if (p >= idps_sistema)
	{
		printf("Impossivel listar produto %d. Produto inexistente.\n", p);
		return;
	}

	printf("%s %d.\n", sistema[p].descricao, sistema_encomendas[e].produtos[p]);
}

/* m - Lista o identificador da encomenda em que o produto dado ocorre mais vezes.*/
void prod_mais_qtd(){
	int p, i, max = 0, ecom;

	scanf(" %d", &p);

	if (p >= idps_sistema)
	{
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", p);
		return;
	}
	/*se nao ha encomendas*/
	if (ides_encomendas == 0)
		return;

	for (i = 0; i < ides_encomendas; i++)
	{
		if (sistema_encomendas[i].produtos[p] > max)
		{
			max = sistema_encomendas[i].produtos[p];
			ecom = i;
		}
	}
	/*se produto nao esta em nenhuma encomenda*/
	if (max == 0)
		return;

	printf("Maximo produto %d %d %d.\n", p, ecom, max);
}

/* l - Lista todos os produtos existentes no sistema por ordem crescente de preco.*/
void ordem_precos(){
	int i, l = 0, r = idps_sistema-1;
	PRODUTO copia_sistema[PMAX];

	for (i = 0; i < idps_sistema; i++)
	{
		copia_sistema[i] = sistema[i];
	}
	/*ordena produtos na copia_sistema*/
	mergesort_l(copia_sistema, l, r);

	printf("Produtos\n");
	for (i = 0; i < idps_sistema; i++)
	{
		printf("* %s %d %d\n", copia_sistema[i].descricao, copia_sistema[i].preco, copia_sistema[i].qtd);
	}
}

/* l - Merge Sort para a funcao ordem_precos.*/
void merge_l(PRODUTO a[], int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1;
	int n2 =  r - m;
	PRODUTO L[PMAX], R[PMAX];

	for (i = 0; i < n1; i++)
		L[i] = a[l + i];
	for (j = 0; j < n2; j++)
		R[j] = a[m + 1+ j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].preco <= R[j].preco)
			a[k] = L[i++];
		else
			a[k] = R[j++];
		k++;
	}

	while (i < n1)
	{
		a[k] = L[i++];
		k++;
	}
	while (j < n2)
	{
		a[k] = R[j++];
		k++;
	}
}

void mergesort_l(PRODUTO a[], int l, int r){
	if (l < r)
	{
		int m = l+(r-l)/2;
		mergesort_l(a, l, m);
		mergesort_l(a, m+1, r);
		merge_l(a, l, m, r);
	}
}


/* L - Lista todos os produtos de uma encomenda por ordem alfabetica da descricao.*/
void ordem_prod_enc(){
	int e, i, contador_prod = 0;
	PRODUTO copia_encomenda[PMAX];

	scanf(" %d", &e);

	if (e >= ides_encomendas)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", e);
		return;
	}

	printf("Encomenda %d\n", e);

	/*cria um novo vetor de produtos, com os produtos que estao na encomenda*/
	for (i = 0; i < idps_sistema; i++)
	{
		if (sistema_encomendas[e].produtos[i] != 0)
		{
			copia_encomenda[contador_prod] = sistema[i];
			copia_encomenda[contador_prod].qtd = sistema_encomendas[e].produtos[i];
			contador_prod += 1;
		}
	}

	mergesort_L(copia_encomenda, 0, contador_prod-1);

	for (i = 0; i < contador_prod; i++)
		printf("* %s %d %d\n", copia_encomenda[i].descricao, copia_encomenda[i].preco, copia_encomenda[i].qtd);
}


/* L - Merge Sort para a funcao ordem_prod_enc.*/
void merge_L(PRODUTO a[], int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1;
	int n2 =  r - m; 
	PRODUTO L[PMAX], R[PMAX];

	for (i = 0; i < n1; i++)
		L[i] = a[l + i];
	for (j = 0; j < n2; j++)
		R[j] = a[m + 1+ j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (strcmp(L[i].descricao, R[j].descricao) < 0)
			a[k] = L[i++];
		else
			a[k] = R[j++];
		k++;
	}

	while (i < n1)
	{
		a[k] = L[i++];
		k++;
	}
	while (j < n2)
	{
		a[k] = R[j++];
		k++;
	}
}

void mergesort_L(PRODUTO a[], int l, int r){
	if (l < r)
	{
		int m = l+(r-l)/2;
		mergesort_L(a, l, m);
		mergesort_L(a, m+1, r);
		merge_L(a, l, m, r);
	}
}

/*Fim do programa*/