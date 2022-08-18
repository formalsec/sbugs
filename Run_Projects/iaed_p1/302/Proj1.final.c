#include <stdio.h>
#include <string.h>
#define MAX_IDENT 10000
#define MAX_ENC 500
#define MAX_CHAR 63
#define MAX_PESO 200
int ident_p = 0; /* Contador dos produtos*/
int ident_e = 0; /*Contador das encomendas*/
int ide, idp;

typedef struct {
	char descricao[MAX_CHAR];
	int preco;
	int peso;
	int quantidade;
	int identificador;
} produto;

typedef struct {
	int identificador; /*e necessario para saberes em que encomenda estas */
	int peso;
	int numero_de_produtos; /* numero de produtos que ha numa encomenda */
	produto produtos [150];
} encomenda;

encomenda conj_encomendas[MAX_ENC];
produto conj_produtos[MAX_IDENT];

/* adiciona um novo produto ao sistema */
void funcao_a() {
	scanf(" %[^:]:%d:%d:%d", conj_produtos[ident_p].descricao, &conj_produtos[ident_p].preco,
    &conj_produtos[ident_p].peso, &conj_produtos[ident_p].quantidade);
	printf("Novo produto %d.\n", ident_p);
	conj_produtos[ident_p].identificador = ident_p;
	ident_p++;
}

/* adiciona stock a um produto existente no sistema */
void funcao_q() {
	int stock;
	scanf("%d:%d",&idp, &stock);
	if (ident_p <= idp)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	else
		conj_produtos[idp].quantidade += stock;
}

/* cria uma nova encomenda */
void funcao_N() {
	printf("Nova encomenda %d.\n", ident_e);
	ident_e++;
}

/* adiciona um produto a uma encomenda */
void funcao_A() {
	int quantidade,i;
	scanf("%d:%d:%d",&ide, &idp, &quantidade);
	if (idp >= ident_p){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	}
	else if (ide >= ident_e){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp, ide);
		return;

	}
	else if (conj_produtos[idp].quantidade < quantidade){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		return;

	}
	else if (conj_encomendas[ide].peso + (conj_produtos[idp].peso * quantidade) > MAX_PESO){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
		return;
	}
	else{
		/*Caso o produto ja esteja na encomenda, adicionamos a quantidade*/
		for(i = 0; i < conj_encomendas[ide].numero_de_produtos; i++){
			if(conj_encomendas[ide].produtos[i].identificador == idp){
				conj_encomendas[ide].produtos[i].quantidade += quantidade;
				conj_produtos[idp].quantidade -= quantidade;
				conj_encomendas[ide].peso += (conj_produtos[idp].peso * quantidade);
				return;
			}
		}
		conj_encomendas[ide].peso += (conj_produtos[idp].peso * quantidade);
		conj_encomendas[ide].produtos[conj_encomendas[ide].numero_de_produtos] = conj_produtos[idp]; /* Vetor de todos os produtos de cada encomenda*/
		conj_encomendas[ide].produtos[conj_encomendas[ide].numero_de_produtos].quantidade = quantidade;
		conj_encomendas[ide].numero_de_produtos++;
		conj_produtos[idp].quantidade -= quantidade;
	}
}

/* remove stock a um produto existente */
void funcao_r() {
	int quantidade;
	scanf("%d:%d",&idp, &quantidade);
	if (ident_p <= idp)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
	else if (conj_produtos[idp].quantidade < quantidade)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",quantidade,idp);
	else
		conj_produtos[idp].quantidade -= quantidade;
}

/* remove um produto de uma encomenda */
void funcao_R() {
	int i;
	scanf("%d:%d", &ide, &idp);
	if(ident_e <= ide)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
	else if(ident_p <= idp)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
	else{
		/*vai ter de remover o produto de uma encomenda, que neste caso ? colocar a quantidade na encomenda a zero*/
		for(i = 0; i < conj_encomendas[ide].numero_de_produtos; i++){
			if(conj_encomendas[ide].produtos[i].identificador == idp){ /* Para verificar se o produto esta dentro da encomenda */
				/*se tiramos da encomenda, a quantidade do stock aumenta*/
				conj_produtos[idp].quantidade += conj_encomendas[ide].produtos[i].quantidade;
				conj_encomendas[ide].peso -= conj_encomendas[ide].produtos[i].quantidade * conj_produtos[idp].peso;
				conj_encomendas[ide].produtos[i].quantidade = 0;

				return;
			}
		}
	}
}

/* calcula o custo de uma encomenda */
void funcao_C(){
	int i, somatorio, idProduto;
	scanf("%d", &ide);
		if(ident_e <= ide){
			printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
			return;
		}
		else{
			somatorio = 0;
			for(i = 0; i < conj_encomendas[ide].numero_de_produtos; i++){
				idProduto = conj_encomendas[ide].produtos[i].identificador;
				somatorio = somatorio + (conj_encomendas[ide].produtos[i].quantidade * conj_produtos[idProduto].preco); /*Vai buscar o preco atual do produto*/
			}
		}
		printf("Custo da encomenda %d %d.\n", ide, somatorio);
}

/* Altera o preco de um produto existente no sistema */
void funcao_p(){
	int preco_novo = 0;
	scanf("%d:%d", &idp, &preco_novo);
	if(ident_p <= idp){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	}
	else{
		conj_produtos[idp].preco = preco_novo;
	}
}

/* lista a descri??o e a quantidade de um produto numa encomenda */
void funcao_E(){
	int i;
	scanf("%d:%d", &ide, &idp);
	if(ident_e <= ide){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	else if(ident_p <= idp){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	}
	else{
		for(i=0; i < conj_encomendas[ide].numero_de_produtos; i++){
			if(conj_encomendas[ide].produtos[i].identificador == idp){ /* Para verificar se o produto esta dentro da encomenda */
				printf("%s %d.\n", conj_produtos[idp].descricao, conj_encomendas[ide].produtos[i].quantidade);
				return;
			}
		}
		printf("%s %d.\n", conj_produtos[idp].descricao,0);
	}
}

/*lista o identificador da encomenda em que o produto dado ocorre mais vezes */
void funcao_m(){
	int i, n, maximo= 0, EncomendaIdMax= -1;
	scanf("%d", &idp);
	if(ident_p <= idp){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	}
	else{
		for(i=0; i < ident_e; i++){
			for(n=0; n < conj_encomendas[i].numero_de_produtos; n++){ /* percorre os produtos dentro de uma encomenda */
				if(conj_encomendas[i].produtos[n].identificador == idp &&
					maximo < conj_encomendas[i].produtos[n].quantidade){
					maximo = conj_encomendas[i].produtos[n].quantidade;
					EncomendaIdMax = i;
				}
			}
		}
		if( maximo == 0 || EncomendaIdMax == -1)
		return;
		printf("Maximo produto %d %d %d.\n", idp, EncomendaIdMax, maximo);
	}
}

void funcao_l(){
}

/* Ordena alfabeticamente as descricoes dos produotos nas encomendas */
void funcao_L(){
	int i, n, r;
	produto produto_aux;
	scanf("%d", &ide);
	if(ident_e <= ide){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	else{
		for(i=0; i < conj_encomendas[ide].numero_de_produtos; i++){
			for(n = 0; n < conj_encomendas[ide].numero_de_produtos ; n++){
				r = strcmp(conj_encomendas[ide].produtos[n].descricao,conj_encomendas[ide].produtos[i].descricao);
				if(r > 0){
					produto_aux = conj_encomendas[ide].produtos[i];
					conj_encomendas[ide].produtos[i] = conj_encomendas[ide].produtos[n];
					conj_encomendas[ide].produtos[n] = produto_aux;
				}
			}
		}
		printf("Encomenda %d\n",ide);
		for(i = 0; i < conj_encomendas[ide].numero_de_produtos; i++){
			if(conj_encomendas[ide].produtos[i].quantidade != 0){
				n = conj_encomendas[ide].produtos[i].identificador;
				printf("* %s %d %d\n", conj_encomendas[ide].produtos[i].descricao,conj_produtos[n].preco,conj_encomendas[ide].produtos[i].quantidade);
			}
		}
	}
}

/* Para dar print de todos os produtos */
/* Funcao auxiliar */
void funcao_k(){
	int i;
	for( i = 0; i < ident_p; i++){
		printf("ProdId:%d Pre?o:%d Peso:%d Quantidade:%d\n",conj_produtos[i].identificador,conj_produtos[i].preco,conj_produtos[i].peso,conj_produtos[i].quantidade);
	}
}
/* utilizar o switch para que se realize apenas um comando*/
int main(){
	char comando;
	while ((comando = getchar()) != 'x'){
			switch(comando) {
				case 'a': funcao_a();
				/* adiciona um novo produto ao sistema */
					break;
				case 'q': funcao_q();
				/* adiciona stock a um produto existente no sistema */
					break;
				case 'N': funcao_N();
				/* cria uma nova encomenda */
					break;
				case 'A': funcao_A();
				/* adiciona um produto a uma encomenda */
					break;
				case 'r': funcao_r();
				/* remove stock a um produto existente */
					break;
				case 'R': funcao_R();
				/* remove um produto de uma encomenda */
					break;
				case 'C': funcao_C();
				/* calcula o custo de uma encomenda */
					break;
				case 'p': funcao_p();
					break;
				case 'E': funcao_E();
					break;
				case 'm': funcao_m();
					break;
				case 'l': funcao_l();
					break;
				case 'L': funcao_L();
					break;
				case 'k': funcao_k();
					break;
			}
	}
	return 0;
}
