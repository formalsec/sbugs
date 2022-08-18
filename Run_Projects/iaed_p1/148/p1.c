#include <stdio.h>
#include <string.h>

/************ Constantes e macros ***********/
#define MAX_STRING 64
#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define MAX_PESO 200
#define VERDADEIRO 1
#define FALSO 0
#define PRECO 'p'
#define DESC 'd'


/*********** Estruturas ***********/
typedef struct Produto{
	int id;
	char desc[MAX_STRING];
	int preco;
	int peso;
	int stock;
} Produto;

typedef struct Encomenda{
	int id;
	int peso ;
	int preco;
	Produto produto[MAX_PRODUTOS];
	int n_de_prods;
} Encomenda;

/*********** Vari?veis globais ***********/
Produto sistema[MAX_PRODUTOS];			/* Array contendo os produtos atualmente no sistema */
int n_sis = 0; 							/* N de produtos atualmente no sistema (comprimento do vetor) */
Encomenda encomenda[MAX_ENCOMENDAS];	/* Array contendo todas as encomendas */
int n_encoms = 0; 						/* N de encomendas atualmente no vetor (comprimento do vetor) */

/*********** Fun??es ***********/

/* Adiciona um novo produto ao vetor sistema. Corresponde ao comando 'a' */

void adicionaProduto(){
	char descricao[MAX_STRING];
	int preco, peso, quantidade;

	scanf(" %[^:]:%d:%d:%d", descricao, &preco, &peso, &quantidade);

	strcpy(sistema[n_sis].desc, descricao);
	sistema[n_sis].preco = preco;
	sistema[n_sis].peso = peso;
	sistema[n_sis].stock = quantidade;
	sistema[n_sis].id = n_sis;

	printf("Novo produto %d.\n", sistema[n_sis].id);
	n_sis++;
}

/* Adiciona stock a um produto no vetor sistema (se existir). Corresponde ao
comando 'q' */
void adicionaStock(){
	int quantidade, id;

	scanf(" %d:%d", &id, &quantidade);

	if(id > n_sis - 1)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
	else
		sistema[id].stock += quantidade;
}

/* Cria uma nova encomenda no vetor encomenda e inicializa as suas variaveis.
Corresponde ao comando 'N' */
void criaEncomenda(){
	encomenda[n_encoms].id = n_encoms;
	encomenda[n_encoms].peso = 0;
	encomenda[n_encoms].preco = 0;
	encomenda[n_encoms].n_de_prods = 0;

	printf("Nova encomenda %d.\n", encomenda[n_encoms].id);
	n_encoms++;
}

/* Adiciona um produto (ou stock a esse produto) a uma encomenda especifica.
Corresponde ao comando 'A' */
void adicionaProdEncomenda(){
	int id_encom, id_prod, quantidade, i, ja_existe, posic_do_prod;
	ja_existe = FALSO;


	scanf(" %d:%d:%d", &id_encom, &id_prod, &quantidade);
	if(id_encom > n_encoms - 1)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_prod, id_encom);
	else if(id_prod > n_sis - 1)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_prod, id_encom);
	else if(quantidade > sistema[id_prod].stock)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_prod, id_encom);
	else if((encomenda[id_encom].peso + sistema[id_prod].peso * quantidade) > MAX_PESO)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", id_prod, id_encom, MAX_PESO);
	else{
		for(i = 0; i < encomenda[id_encom].n_de_prods; i++)
			if(id_prod == encomenda[id_encom].produto[i].id){
				ja_existe = VERDADEIRO;
				posic_do_prod = i;
				break;
			}

		if(ja_existe == VERDADEIRO){
			encomenda[id_encom].produto[posic_do_prod].stock += quantidade;
		} else{	/* Se nao existir na encomenda, adicionamos como novo produto */
			strcpy(encomenda[id_encom].produto[encomenda[id_encom].n_de_prods].desc, sistema[id_prod].desc);
			encomenda[id_encom].produto[encomenda[id_encom].n_de_prods].id    = id_prod;
			encomenda[id_encom].produto[encomenda[id_encom].n_de_prods].peso  = sistema[id_prod].peso;
			encomenda[id_encom].produto[encomenda[id_encom].n_de_prods].preco = sistema[id_prod].preco;
			encomenda[id_encom].produto[encomenda[id_encom].n_de_prods].stock = quantidade;
			encomenda[id_encom].n_de_prods++;
		}

		/* Em ambos os casos precisamos de atualizar o sistema e o peso e preco da encomenda */
		sistema[id_prod].stock -= quantidade;
		encomenda[id_encom].peso += quantidade * sistema[id_prod].peso;
		encomenda[id_encom].preco += quantidade * sistema[id_prod].preco;

	}
}


/* Remove stock a um produto no vetor sistema (se for possivel).
Corresponde ao comando 'r' */
void removeStockProd(){
	int id_prod, quantidade;

	scanf(" %d:%d", &id_prod, &quantidade);

	if(id_prod > n_sis - 1)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_prod);
	else if(quantidade > sistema[id_prod].stock)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, id_prod);
	else
		sistema[id_prod].stock -= quantidade;
}

/* Remove um produto de uma encomenda e atualiza o preco e peso desta.
Corresponde ao comando 'R' */
void removeProdEncomenda(){
	int id_encom, id_prod;
	int i;

	scanf(" %d:%d", &id_encom, &id_prod);

	if(id_encom > n_encoms - 1)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_prod, id_encom);
	else if(id_prod > n_sis - 1)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_prod, id_encom);
	else
		for(i = 0; i < encomenda[id_encom].n_de_prods; i++)
			if(encomenda[id_encom].produto[i].id == id_prod){
				encomenda[id_encom].peso  -= sistema[id_prod].peso * encomenda[id_encom].produto[i].stock;
				encomenda[id_encom].preco -= sistema[id_prod].preco * encomenda[id_encom].produto[i].stock;
				sistema[id_prod].stock    += encomenda[id_encom].produto[i].stock;
				encomenda[id_encom].produto[i].stock = 0;
				break;
			}
}

/* Calcula o valor total de uma encomenda.
Corresponde ao comando 'C' */
void calculaCustoEncomenda(){
	int id_encom, i, custo;
	custo = 0;

	scanf(" %d", &id_encom);

	if(id_encom >= n_encoms)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_encom);
	else{
		for(i = 0; i < encomenda[id_encom].n_de_prods; i++)
			custo += encomenda[id_encom].produto[i].preco * encomenda[id_encom].produto[i].stock;

		printf("Custo da encomenda %d %d.\n", id_encom, custo);
	}
}

/* Altera o preco de um produto no sistema.
Corresponde ao comando 'p' */
void alteraPreco(){
	int id_prod, novo_preco, i, j;

	scanf(" %d:%d", &id_prod, &novo_preco);

	if(id_prod > n_sis - 1){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_prod);
		return;
	}

	sistema[id_prod].preco = novo_preco;

	for(i = 0; i < n_encoms; i++)
		for(j = 0; j < encomenda[i].n_de_prods; j++)
			if(encomenda[i].produto[j].id == id_prod){
				encomenda[i].preco += (novo_preco - encomenda[i].produto[j].preco) * encomenda[i].produto[j].stock;
				encomenda[i].produto[j].preco = novo_preco;
			}
}

/* Lista a descri??o e a quantidade de um produto numa encomenda.
Corresponde ao comando 'E' */
void listaProduto(){
	int id_encom, id_prod, i, esta_na_enc;
	esta_na_enc = FALSO;
	scanf(" %d:%d", &id_encom, &id_prod);

	if(id_encom > n_encoms - 1)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_encom);
	else if(id_prod > n_sis - 1)
		printf("Impossivel listar produto %d. Produto inexistente.\n", id_prod);
	else{
		for(i = 0; i < encomenda[id_encom].n_de_prods; i++)
			if(encomenda[id_encom].produto[i].id == id_prod){
				printf("%s %d.\n", encomenda[id_encom].produto[i].desc, encomenda[id_encom].produto[i].stock);
				esta_na_enc = VERDADEIRO;
				break;
			}

		if(esta_na_enc == FALSO)
			printf("%s %d.\n", sistema[id_prod].desc, 0);
	}
}

/* Mostra o identificador da encomenda em que um produto ocorre mais vezes (com o menor id)
Corresponde ao comando 'm' */
void encomendaMaisProduto(){
	int id_prod, maior_n_ocorr, id_enc_maior;
	int i, j;

	maior_n_ocorr = 0;

	scanf(" %d", &id_prod);

	if(id_prod > n_sis - 1){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_prod);
		return;
	}

	for(i = 0; i < n_encoms; i++)
		for(j = 0; j < encomenda[i].n_de_prods; j++)
			if((encomenda[i].produto[j].id == id_prod) && (encomenda[i].produto[j].stock > maior_n_ocorr)){
				maior_n_ocorr = encomenda[i].produto[j].stock;
				id_enc_maior = encomenda[i].id;
			} /* Nao precisamos de fazer outro if pq a primeira encomenda assignada tem o menor id */

	if(maior_n_ocorr > 0)
		printf("Maximo produto %d %d %d.\n", id_prod, id_enc_maior, maior_n_ocorr);
}

/* Ordena um vetor produto por um criterio c (preco e id ou alfabeticamente).
Corresponde a uma funcao auxiliar para os comandos 'l' e 'L' e a funcao mergesort() */
void merge(Produto v[], int e, int d, int m, char c){
	int i_e, i_d, i_t, i;
	Produto temp[MAX_PRODUTOS];
	i_e = e;					/* Array esquerdo */
	i_d = m + 1;				/* Array direito */
	i_t = e;					/* Array tempor?rio*/

	while((i_e <= m) && (i_d <= d))	/* Se c for PRECO, ordena por preco e id como 2do criterio, se nao, alfabeticamente */
		if((c == PRECO) ? (v[i_d].preco < v[i_e].preco) : (strcmp(v[i_e].desc, v[i_d].desc) >= 0)){
			temp[i_t] = v[i_d];
			i_t++;
			i_d++;
		} else if((c == PRECO) ? (v[i_d].preco > v[i_e].preco) : (strcmp(v[i_e].desc, v[i_d].desc) < 0)){
			temp[i_t] = v[i_e];
			i_t++;
			i_e++;
		} else{		/* Se c n?o for 'p' n?o entra*/
			if(v[i_d].id <= v[i_e].id){
				temp[i_t] = v[i_d];
				i_t++;
				i_d++;
			} else{
				temp[i_t] = v[i_e];
				i_t++;
				i_e++;
			}
		}

	while(i_e <= m){			/* Se falhou a primeira condi??o no && */
		temp[i_t] = v[i_e];
		i_t++;
		i_e++;
	}

	while(i_d <= d){			/* Se falhou a segunda condi??o no && */
		temp[i_t] = v[i_d];
		i_t++;
		i_d++;
	}

	for(i = e; i <= d; i++)
		v[i] = temp[i];
}

/* Divide em metades um vetor ate ficar com vetores de comprimento 1, para serem ordenados por merge()
Corresponde a uma funcao auxiliar para os comandos 'l' e 'L' */
void mergesort(Produto v[], int esq, int dir, char crit){
	int m;
	if(esq < dir){
		m = (esq + dir) / 2;
		mergesort(v, esq, m, crit);
		mergesort(v, m + 1, dir, crit);
		merge(v, esq, dir, m, crit);
	}

}

/* Imprime uma copia dos produtos do array sistema, por ordem crescente de preco (e de id se tiverem precos iguais).
Corresponde ao comando 'l' */
void listaProdutosPreco(){
	Produto res[MAX_PRODUTOS];
	int i;

	for(i = 0; i < n_sis; i++)
		res[i] = sistema[i];

	mergesort(res, 0, n_sis - 1, PRECO);

	printf("Produtos\n");
	for(i = 0; i < n_sis; i++)
		printf("* %s %d %d\n", res[i].desc, res[i].preco, res[i].stock);
}

/* Imprime uma copia dos produtos de uma encomenda (uma posicao do vetor encomenda) por ordem alfabetico da descricao.
Corresponde ao comando 'L' */
void listaProdutosDesc(){
	Produto res[MAX_PRODUTOS];
	int i, id_encom;

	scanf(" %d", &id_encom);

	if(id_encom > n_encoms - 1){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_encom);
		return;
	}

	for(i = 0; i < encomenda[id_encom].n_de_prods; i++)
		res[i] = encomenda[id_encom].produto[i];

	mergesort(res, 0, encomenda[id_encom].n_de_prods - 1, DESC);

	printf("Encomenda %d\n", id_encom);
	for(i = 0; i < encomenda[id_encom].n_de_prods; i++)
		if(res[i].stock > 0)
			printf("* %s %d %d\n", res[i].desc, res[i].preco, res[i].stock);
}

/*********** Programa principal ***********/
/* Faz a leitura de cada comando e invoca a funcao correspondente */
int main(){
	char comando;

	scanf("%c", &comando);
	while (comando != 'x'){
		switch (comando){
		case 'a':
			adicionaProduto();
			break;

		case 'q':
			adicionaStock();
			break;

		case 'N':
			criaEncomenda();
			break;

		case 'A':
			adicionaProdEncomenda();
			break;

		case 'r':
			removeStockProd();
			break;

		case 'R':
			removeProdEncomenda();
			break;

		case 'C':
			calculaCustoEncomenda();
			break;

		case 'p':
			alteraPreco();
			break;

		case 'E':
			listaProduto();
			break;

		case 'm':
			encomendaMaisProduto();
			break;

		case 'l':
			listaProdutosPreco();
			break;
		case 'L':
			listaProdutosDesc();
			break;

		default:
			break;
		}
		scanf(" %c", &comando);
	}

	return 0;
}
