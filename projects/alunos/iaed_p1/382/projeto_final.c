#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Espa?o para declara?ao de constantes, variaveis e fun?oes que se vao usar no programa */

#define MAX_ENCOMENDAS 500
#define MAX_STOCK 10000
#define MAX_PROD_ENCOMENDA 200
#define exch(A,B) {produto t = A; A = B; B = t;}
#define bigger_ascii_value(A,B) (strcmp(A, B) > 0)


typedef struct {
	int identificador;
	char descricao[64];
	int preco;
	int peso;
	int quantidade;
	int criado;
} produto;


typedef struct {
	int num_produtos;
	int criada;
	int peso_encomenda;
	produto produtos[MAX_PROD_ENCOMENDA];
} encomenda;


produto stock[MAX_STOCK];
encomenda encomendas[MAX_ENCOMENDAS];


int idp = 0;
int num_encomendas = 0;
int num_produtos_encomenda = 0;


void novo_produto();

void adiciona_produto_stock();

void nova_encomenda();

void adiciona_produto_encomenda();
void add_produto_encomenda(int quantidade, int ide, int idp);
void guarda_novo_produto_encomenda(int idp, int ide, int quantidade);

void remove_stock_produto();

void remove_produto_encomenda();

void calcula_custo_encomenda();

void altera_preco_produto();

void mostra_produto_encomenda();

void produto_quantidade_max();

void lista_stock();
void guarda_produtos_em_stock(produto stock_produtos[MAX_STOCK]);
void mergesort_produtos(produto stock_produtos[MAX_STOCK], int l, int r);
void merge(produto stock_produtos[MAX_STOCK], int l, int m, int r);
void compara_e_junta_ordenado(produto stock_produtos[MAX_STOCK], produto v_aux[MAX_STOCK], int j, int l, int r, int i);
void mostra_produtos_em_stock(produto stock_produtos[MAX_STOCK]);

void lista_produtos_encomenda();
void guarda_produtos_encomenda(produto produtos_encomenda[MAX_PROD_ENCOMENDA], int ide);
void quicksort_encomenda(produto produtos_encomenda[MAX_PROD_ENCOMENDA], int l, int r);
int partition_encomendas(produto produtos_encomenda[MAX_PROD_ENCOMENDA], int l, int r);
void mostra_produtos_encomenda(produto produtos_encomenda[MAX_PROD_ENCOMENDA], int ide);

int existe_produto_encomenda(int ide, int idp);

/* Fim do espa?o para declara?ao de constantes, variaveis e fun?oes que se vao usar no programa */


/* MAIN */

int main(){

	char c;

	while ((c = getchar()) != 'x'){

		switch(c){

			case 'a':
				novo_produto();
				break;

			case 'q':
				adiciona_produto_stock();
				break;

			case 'N':
				nova_encomenda();
				break;

			case 'A':
				adiciona_produto_encomenda();
				break;

			case 'r':
				remove_stock_produto();
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
				mostra_produto_encomenda();
				break;

			case 'm':
				produto_quantidade_max();
				break;

			case 'l':
				lista_stock();
				break;

			case 'L':
				lista_produtos_encomenda();
				break;
		}
	}
	return 0;
}






/* IMPLEMENTACAO DAS FUNCOES QUE FAZEM O PROGRAMA FUNCIONAR */



/* Esta Fun?ao cria um novo produto aquando se recebe uma letra a no inicio do input.
	idp representa o indice do produto criado. */


void novo_produto(){
	stock[idp].identificador = idp;
	stock[idp].criado = 1;

	scanf(" %[^:]:%d:%d:%d", stock[idp].descricao, &stock[idp].preco, &stock[idp].peso, &stock[idp].quantidade);
	printf("Novo produto %d.\n", idp);

	idp = idp + 1;
}




/* Esta Fun?ao adiciona x de um produto aquando se recebe uma letra q no inicio do input.

  		Deve gerar erro somente no caso em que o produto a que se esta a tentar aceder,
   		ou que se le no input ainda nao foi adicionado ao sistema */


void adiciona_produto_stock(){
	int idp, quantidade;
	scanf("%d:%d", &idp, &quantidade);

	if (stock[idp].criado != 0)
		stock[idp].quantidade += quantidade;

	else printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}




/* Esta Funcao cria uma nova encomenda quando se recebe uma letra N no inicio do input.
	ide representa o indice da encomenda que se cria. */


void nova_encomenda(){
	encomendas[num_encomendas].criada = 1;

	printf("Nova encomenda %d.\n", num_encomendas);
	num_encomendas += 1;
}




/* Esta Funcao adiciona um produto a uma encomenda ja existente, quando le A no inicio do input.

	Deve levantar erros se:
	- a encomenda nao tiver sido ainda criada; - Encomenda inexistente.
	- o produto ainda nao tiver sido adicionado ao stock; - Produto inexistente.
	- a quantidade em stock nao menor do que a que se quer adicionar a encomenda; - Quantidade em stock insuficiente.
	- o peso da encomenda exceder os 200 aquando se tenta adicionar os produtos; - Peso da encomenda excede o maximo de 200.

 	Caso contrario nao deve imprimir nada, apenas adicionar o produto a encomenda */



void adiciona_produto_encomenda(){
	int ide, idp, quantidade;
	scanf("%d:%d:%d", &ide, &idp, &quantidade);

	if (encomendas[ide].criada == 0)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

	else if (stock[idp].criado == 0)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

	else if (stock[idp].quantidade < quantidade)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);

	else if (encomendas[ide].peso_encomenda + (stock[idp].peso * quantidade) > 200)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
				
	else add_produto_encomenda(quantidade, ide, idp);

}




void add_produto_encomenda(int quantidade, int ide, int idp){
	
	if (existe_produto_encomenda(ide, idp) == -1){

		guarda_novo_produto_encomenda(ide, idp, quantidade);
		encomendas[ide].num_produtos += 1;
	}
	else encomendas[ide].produtos[existe_produto_encomenda(ide,idp)].quantidade += quantidade;
	
	encomendas[ide].peso_encomenda += (stock[idp].peso * quantidade);
	stock[idp].quantidade -= quantidade;
}



void guarda_novo_produto_encomenda(int ide, int idp, int quantidade){
	int idp_e = encomendas[ide].num_produtos;

	encomendas[ide].produtos[idp_e].identificador = idp;
	encomendas[ide].produtos[idp_e].criado = 1;

	encomendas[ide].produtos[idp_e].preco = stock[idp].preco;
	encomendas[ide].produtos[idp_e].peso = stock[idp].peso;
	strcpy(encomendas[ide].produtos[idp_e].descricao, stock[idp].descricao);

	encomendas[ide].produtos[idp_e].quantidade += quantidade;
}




/* Esta Funcao remove stock a um produto existente, quando inicialmente le no input a letra r.
	Deve gerar erro no caso de:
	- nao existir nenhum produto criado com o identificador a que se tenta aceder.
	- nao existir quantidade suficiente em stock que queremos de la retirar.
	
	Caso contrario a funcao nao deve devolver nada, mas apenas retirar a quantidade no stock */


void remove_stock_produto(){
	int idp, quantidade;
	scanf("%d:%d", &idp, &quantidade);

	if (stock[idp].criado == 0)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);

	else if (stock[idp].quantidade < quantidade)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);

	else stock[idp].quantidade -= quantidade;
}




/*  Esta Funcao remove um produto (ou toda a quantidade dele) de uma encomenda quando le no inicio do input a letra R.
	Deve gerar erros apenas nos casos em que :
   - nao exista nenhuma encomenda com o identificador (ide) que se recebeu no input e a que se tenta aceder.
   - nao exista nenhum produto com esse identificador (idp) no stock.

   Caso contrario nao deve devolver nada, apenas retirar da encomenda e repor no stock. */


void remove_produto_encomenda(){
	int ide, idp, i_prod_enc;

	scanf("%d:%d", &ide, &idp);

	if (encomendas[ide].criada == 0)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

	else if (stock[idp].criado == 0)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

	else if ((i_prod_enc = existe_produto_encomenda(ide, idp)) != -1){

		stock[idp].quantidade += encomendas[ide].produtos[i_prod_enc].quantidade;

		encomendas[ide].peso_encomenda -= (encomendas[ide].produtos[i_prod_enc].quantidade * stock[idp].peso);

		encomendas[ide].produtos[i_prod_enc].quantidade = 0;
	}
}




/* Esta Funcao calcula o custo total de uma encomenda, quando le no inicio do input a letra C.
	Deve gerar erros apenas no caso em que:
   - A encomenda a que se est? a tentar aceder / ou se le no input nao tenha ainda sido criada.

   Caso contrario deve devolver o custo total da soma de todos os produtos na encomenda. */


void calcula_custo_encomenda(){
	int custo_total = 0, idp, ide;
	scanf("%d", &ide);

	if (encomendas[ide].criada != 0){

		for (idp = 0; idp < encomendas[ide].num_produtos; idp++){
			if (encomendas[ide].produtos[idp].criado != 0)
				custo_total += encomendas[ide].produtos[idp].quantidade * encomendas[ide].produtos[idp].preco;
		}

		printf("Custo da encomenda %d %d.\n", ide, custo_total);
	}
	else printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
}




/* Esta funcao deve alterar o preco de um produto existente no sistema
	Deve entao gerar erro apenas nos casos em que o produto a que se tenta aceder nao estiver registado em stock.

	Caso contrario nao deve devover nada, apenas fazer as mudan?as devidas no sistema. */
	

void altera_preco_produto(){
	int idp, novo_preco, i_enc, i_prod;
	scanf("%d:%d", &idp, &novo_preco);

	if (stock[idp].criado != 0){
		stock[idp].preco = novo_preco;

		for (i_enc = 0; i_enc < num_encomendas; i_enc++){

			if ((i_prod = existe_produto_encomenda(i_enc, idp)) != -1){
				encomendas[i_enc].produtos[i_prod].preco = novo_preco;
			}
		}
	}
	else printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}




/* Esta funcao mostra um certo produto que esta contido numa encomenda.

	Deve gerar erros nos casos em que:
   - ainda nao ha nenhuma encomenda criada com o identificador (ide) a que se tenta aceder.
   - nao exista nenhum produto registado no sistema com o identificador (idp) a qu se tenta aceder.

	Caso contrario:
	-Se o produto existir na encomenda: deve devolver o produto, mostrando a sua descricao e quantidade.
	-Se o produto nao existir na encomenda: nao deve devolver nada. */


void mostra_produto_encomenda(){
	int ide, idp, i_prod;
	scanf("%d:%d", &ide, &idp);

	if (encomendas[ide].criada == 0)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

	else if (stock[idp].criado == 0)
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);

	else if ((i_prod = existe_produto_encomenda(ide, idp)) != -1)
		printf("%s %d.\n", encomendas[ide].produtos[i_prod].descricao, encomendas[ide].produtos[i_prod].quantidade);

	else printf("%s 0.\n", stock[idp].descricao);
}





/* Esta Funcao ve qual o produto que ocorre mais vezes e em qual encomenda ocorre mais vezes.
	Deve gerar erro apenas no caso em que o produto ainda nao tenha sido registado no sistema.

	Caso contrario deve devolver o produto que ocorre mais vezes, em que encomenda ocorre, e a respetiva quantidade. */


void produto_quantidade_max(){
	int idp, i_enc, i_prod, quantidade_max = 0, ide_max = 0;
	scanf("%d", &idp);

	if (stock[idp].criado != 0){

		for (i_enc = 0; i_enc < num_encomendas; i_enc++){

			if ((i_prod = existe_produto_encomenda(i_enc, idp)) != -1){

				if (encomendas[i_enc].produtos[i_prod].quantidade > quantidade_max){

					quantidade_max = encomendas[i_enc].produtos[i_prod].quantidade;
					ide_max = i_enc;
				}
			}
		}
		if (quantidade_max != 0)
			printf("Maximo produto %d %d %d.\n", idp, ide_max, quantidade_max);
	}
	else printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
}





/* Esta funcao lista todos os produtos existentes no stock do sistema, por ordem crescente de pre?o.
	Nao recebe nenhum input nem deve gerar erros, e se nao houverem produtos em stock nao deve devolver nada. */


void lista_stock(){
	produto stock_produtos[MAX_STOCK];

	guarda_produtos_em_stock(stock_produtos);

	mergesort_produtos(stock_produtos, 0, idp-1);

	mostra_produtos_em_stock(stock_produtos);
}


void guarda_produtos_em_stock(produto stock_produtos[MAX_STOCK]){
	int i_prod;

	for (i_prod = 0; i_prod < idp; i_prod++)
		stock_produtos[i_prod] = stock[i_prod];
}


void mergesort_produtos(produto stock_produtos[MAX_STOCK], int l, int r){
	int m = (l + r) / 2;

	if (r <= l) return;

	mergesort_produtos(stock_produtos, l, m);
	mergesort_produtos(stock_produtos, m+1, r);

	merge(stock_produtos, l, m, r);
}


void merge(produto stock_produtos[MAX_STOCK], int l, int m, int r){
	
	int i, j;
	produto v_aux[MAX_STOCK];

	for (i = m+1; i > l; i--)
		v_aux[i-1] = stock_produtos[i-1];

	for (j = m; j < r; j++)
		v_aux[r+m-j] = stock_produtos[j+1];

	compara_e_junta_ordenado(stock_produtos, v_aux, j, l, r, i);
}


void compara_e_junta_ordenado(produto stock_produtos[MAX_STOCK], produto v_aux[MAX_STOCK], int j, int l, int r, int i){
	int k;

	for (k = l; k <= r; k++){

		if (v_aux[j].preco < v_aux[i].preco)
			stock_produtos[k] = v_aux[j--];

		else if(v_aux[j].preco == v_aux[i].preco){

			if (v_aux[j].identificador < v_aux[i].identificador)
				stock_produtos[k] = v_aux[j--];
			else stock_produtos[k] = v_aux[i++];
		}
		else stock_produtos[k] = v_aux[i++];
	}
}


void mostra_produtos_em_stock(produto stock_produtos[MAX_STOCK]){
	int i_prod;

	printf("Produtos\n");
	for (i_prod = 0; i_prod < idp; i_prod++)
		printf("* %s %d %d\n", stock_produtos[i_prod].descricao, stock_produtos[i_prod].preco, stock_produtos[i_prod].quantidade); 
}





/* Esta funcao lista os produtos todos de uma encomenda por ordem alfabetica.
	Levanta erros somente quando a encomenda a que estamos a tentar aceder ainda nao foi criada

	Caso contrario devolve todos os produtos contidos numa encomenda por ordem da tabela ASCII */


void lista_produtos_encomenda(){
	int ide;
	produto produtos_encomenda[MAX_PROD_ENCOMENDA];
	scanf("%d", &ide);

	if (encomendas[ide].criada != 0){

		guarda_produtos_encomenda(produtos_encomenda, ide);

		quicksort_encomenda(produtos_encomenda, 0, num_produtos_encomenda-1);

		mostra_produtos_encomenda(produtos_encomenda, ide);
	}

	else printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}



void guarda_produtos_encomenda(produto produtos_encomenda[MAX_PROD_ENCOMENDA], int ide){
	int idp, idp_e = 0;

	for (idp = 0; idp < encomendas[ide].num_produtos; idp++){

		if (encomendas[ide].produtos[idp].criado != 0 && encomendas[ide].produtos[idp].quantidade > 0)
			produtos_encomenda[idp_e++] = encomendas[ide].produtos[idp];
	}
	num_produtos_encomenda = idp_e;
}


void quicksort_encomenda(produto produtos_encomenda[MAX_PROD_ENCOMENDA], int l, int r){
	int i;

	if (r <= l) return;

	i = partition_encomendas(produtos_encomenda, l, r);

	quicksort_encomenda(produtos_encomenda, l, i-1);
	quicksort_encomenda(produtos_encomenda, i+1, r);
}


int partition_encomendas(produto produtos_encomenda[MAX_PROD_ENCOMENDA], int l, int r){
	int i = l-1;
	int j = r;
	produto pivot = produtos_encomenda[r];

	while (i < j){

		while(bigger_ascii_value(pivot.descricao, produtos_encomenda[++i].descricao));

		while(bigger_ascii_value(produtos_encomenda[--j].descricao, pivot.descricao)){
			if (j == l)
				break;
		}
		if (i < j)
			exch(produtos_encomenda[i], produtos_encomenda[j]);
	}
	exch(produtos_encomenda[i],produtos_encomenda[r]);

	return i;
}


void mostra_produtos_encomenda(produto produtos_encomenda[MAX_PROD_ENCOMENDA], int ide){
	int idp;

	printf("Encomenda %d\n", ide);
	for (idp = 0; idp < num_produtos_encomenda; idp++)
		printf("* %s %d %d\n", produtos_encomenda[idp].descricao, produtos_encomenda[idp].preco, produtos_encomenda[idp].quantidade);
}





/*FUNCOES AUXILIARES */


/* Esta ? a funcao que procura um certo produto numa encomenda.

 	Se existir entao devolve o seu indice, se nao devolve -1, pois ? algo que nunca sera o indice */

int existe_produto_encomenda(int ide, int idp){
	int i_prod;

	if (encomendas[ide].num_produtos > 0){

		for (i_prod = 0; i_prod < encomendas[ide].num_produtos; i_prod++){
			if (encomendas[ide].produtos[i_prod].identificador == idp)
				return i_prod;
		}
	}
	return -1;
}


/*FIM DE FUNCOES AUXILIARES */
