#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 63        /* Maximo de carateres de uma descrisao */
#define PESO_MAX 200  /* Peso maximo de uma encomenda */
#define M_ENCOM 500   /* Numero maximo de encomendas */
#define M_STOCK 10000 /* Numero maximo de produtos no sistem */


typedef struct produto{
	char descricao[MAX];
	int preco, peso, stock;
}produto;

typedef struct encomenda{
	int quantidade[M_STOCK], peso_tot; /* em cada posicao X esta a quantidade do produto de id X, peso total da encomenda */
}encomenda;

produto armazem[M_STOCK];              /* array que vai ter todos os produtos do sistema registados, onde cada posicao corresponde ao id do produto */
encomenda lis_encom[M_ENCOM];          /* array que tem todas as encomendas, onde cada posicao corresponde ao id da encomenda */
int id = 0, id_e = 0;				   /* variaveis globais que indicam o tamanho da array armazem e encomendas */

/* Funcoes: */

/* Adiciona um produto ao sistema */
int adicionar_prod(){     
	scanf(" %[^:]:%d:%d:%d", armazem[id].descricao, &armazem[id].preco, &armazem[id].peso, &armazem[id].stock);
	return printf("Novo produto %d.\n", id++);         
}

/* Adiciona stock de um produto no sistema */
void adicionar_stock(){    
	int idq, qtd; /* input do id do produto e quantidade a adicionar ao stock */
	scanf(" %d:%d", &idq, &qtd);
	if (idq >= id)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idq);
	else
		armazem[idq].stock += qtd;
}

/* Cria uma nova encomenda, inicializando uma array do tipo encomenda na array da lista de encomendas */
int nova_enc(){ 	
	int idp;      
	for (idp = 0; idp < M_STOCK; idp++)
		lis_encom[id_e].quantidade[idp] = 0;   /* inicializacao de array */
	lis_encom[id_e].peso_tot = 0;
	return printf("Nova encomenda %d.\n", id_e++);
}

/* Adiciona um produto a uma encomenda */
void ad_pro_enc(){
	int ide, idp, qnt;   /* input do id da encomenda, id do produto e quantidade a por na encomenda */
	scanf(" %d:%d:%d", &ide, &idp, &qnt);
	if (ide < id_e){
		if (idp < id){
			if (qnt <= armazem[idp].stock){ 
				if (lis_encom[ide].peso_tot + qnt * armazem[idp].peso <= PESO_MAX){   
				/* Retirar quantidade do stock, coloca-la na encomenda e aumentar peso total da encomenda */
					armazem[idp].stock -= qnt;
					lis_encom[ide].quantidade[idp] += qnt;
					lis_encom[ide].peso_tot += qnt * armazem[idp].peso;
				}
				else printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
			}
			else printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);	
		}
		else printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/* Remove quantidade de um produto ao stock (sistema) */
void remove_stock(){
	int idp, qnt;     /* input do id do produto e quantidade a retirar do stock */
	scanf(" %d:%d", &idp, &qnt);
	if (idp < id){
		if (armazem[idp].stock >= qnt)
			armazem[idp].stock -= qnt;
		else
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qnt, idp);
	}
	else
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
}

/* Remove um produto de uma encomenda pondo a quantidade desse produto a zero na respetiva encomenda */
void remove_pro_ecom(){
	int ide, idp;    /* input do id da encomenda e id do produto */
	scanf(" %d:%d", &ide, &idp);
	if (ide < id_e){
		if(idp < id){            
		/* Diminuir peso total, repor stock e retirar produto da encomenda */
			lis_encom[ide].peso_tot -= lis_encom[ide].quantidade[idp] * armazem[idp].peso;
			armazem[idp].stock += lis_encom[ide].quantidade[idp];
			lis_encom[ide].quantidade[idp] = 0;
		}
		else printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/* Calcula o custo de uma encomenda */
void custo_encom(){
	int ide, idp, custo = 0; /* input do id da encomenta, id do produto, custo total da encomenda */
	scanf(" %d", &ide);
	if (ide < id_e){
		for (idp = 0; idp < M_STOCK; idp++){
			if (lis_encom[ide].quantidade[idp] > 0) /* quantidade maior que 0 implica haver um produto numa encomenda */
				custo += lis_encom[ide].quantidade[idp] * armazem[idp].preco;
		}
		printf("Custo da encomenda %d %d.\n", ide, custo);
	}
	else 
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
}

/* Altera o preco de um produto no sistema */
void alterar_preco(){
	int idp, preco;  /* input do id do produto e novo preco */
	scanf(" %d:%d", &idp, &preco);
	if (idp < id)
		armazem[idp].preco = preco;     /* altera preco antigo pelo de input */
	else
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}

/* Lista a descrisao e quantidade de um produto */
void descricao_quantidade(){
	int ide, idp;                       /* input do id da encomenda e id do produto */
	scanf(" %d:%d", &ide, &idp);
	if (ide < id_e){
		if (idp < id)
			printf("%s %d.\n",armazem[idp].descricao, lis_encom[ide].quantidade[idp]);
		else
			printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	}
	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}

/* Lista o identificador da encomenda em que o produto dado ocorre mais vezes */
void max_produto(){
	int idp, ide, encom, max = 0;  /* input do id do produto, id da encomenda a percorrer na lista de encomendas, encomenda onde tem a maior quantidade, maximo de quantidade */
	scanf(" %d", &idp);
	if (idp < id){
			for (ide = 0; ide < id_e; ide++){
				if (lis_encom[ide].quantidade[idp] > max){    /* guarda o ide de uma encomenda caso a quantidade do produto seja maior que o maximo */
					max = lis_encom[ide].quantidade[idp];
					encom = ide;
				}
			}
			if (max != 0)
				printf("Maximo produto %d %d %d.\n", idp, encom, max);
	}
	else printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
}


/* Ve se o preco do id X e menor que o de Y, caso sejam iguais compara os ids */
int menor_preco(int X, int Y){
	int booleano = 0;
	if (armazem[X].preco < armazem[Y].preco || (armazem[X].preco == armazem[Y].preco && X < Y))
		booleano = 1;
	return booleano;
}

/* Ve se esta por oredem alfabetica as descrisoes dos ids X e Y */
int menor_desc(int X, int Y){
	int i, booleano = -1;
	for (i = 0; i < MAX && armazem[X].descricao[i] != '\n' && armazem[Y].descricao[i] != '\n' && booleano == -1; i++){ /* verifica a letra de maior relevancia enqunto for igual nas duas descricoes */
		if (armazem[X].descricao[i] > armazem[Y].descricao[i])  
			booleano = 0;
		else if (armazem[X].descricao[i] < armazem[Y].descricao[i])
			booleano = 1;
	}
	return booleano;
}

/* Junta duas particoes da array de forma ordenada */
void merge(int array[], int ini, int meio, int ult, int type){  /* type = 0 comparar preco e type = 1 comparar descrisao */
	int i, j, k, aux[M_STOCK];    /* i - iteravel que comeca no inicio da particao, j - iteravel que comeca no fim da particao, k - iteravel que percorre a array principal, aux - array auxiliar que tem como conteudo os valores das particoes */
	for (i = meio + 1; i > ini; i--)  /* primeira particao */
		aux[i - 1] = array[i - 1];
	for (j = meio; j < ult; j++)      /* segunda particao por ordem invertida */
		aux[ult + meio - j] = array[j + 1];
	for (k = ini; k <= ult; k ++){
		if (type == 0){	              /* trocas */
			if (menor_preco(aux[j], aux[i]))
				array[k] = aux[j--];
			else
				array[k] = aux[i++];
		}
		else {
			if (menor_desc(aux[j], aux[i]))
				array[k] = aux[j--];
			else
				array[k] = aux[i++];
		}
	}
}

/* Funcao que ordena os ids dos produtos segundo o seu preco (type = 0) ou segundo a sua descrisao (type = 1), separando a array em particoes e depois junta-las de forma ordenada */
void mergesort(int array[], int ini, int ult, int type){
	int meio = (ult + ini)/2;               /* meio da array */
	if (ult <= ini) return;
	mergesort(array, ini, meio, type);      /* particoes do lado direito */
	mergesort(array, meio + 1, ult, type);  /* particoes do lado esquerdo */
	merge(array, ini, meio, ult, type);     /* juntar particoes de forma ordenada*/
}

/* Inicializa uma array com os ids dos produtos do sistema que depois vao ser ordenados segundo o seu preco */
void ordenar_preco(){ 
	int ids[M_STOCK], p;     /* array com o tamanho igual ao numero de produtos no sistema, produto a percorrer */
	for (p = 0; p < id; p++) /* indice de todos os produtos na array */
		ids[p] = p;
	mergesort(ids, 0, id - 1, 0);
	printf("Produtos\n");
	for (p = 0; p < id; p++)
		printf("* %s %d %d\n", armazem[ids[p]].descricao, armazem[ids[p]].preco, armazem[ids[p]].stock);
}

/* Inicializa uma array com os ids dos produtos de uma encomenda que depois vao ser ordenados por ordem alfabetica segundo a descrisao */
void ordenar_desc(){ 
	int ids[M_STOCK], p, ide, i = 0, tamanho = 0; 
	scanf(" %d", &ide);
	if (ide < id_e){
		for (p = 0; p < id; p++){
			if (lis_encom[ide].quantidade[p] > 0){
				ids[i++] = p;
				tamanho++;
			}
		}
		mergesort(ids, 0, tamanho - 1, 1);
		printf("Encomenda %d\n", ide);
		for (i = 0; i < tamanho; i++)
			printf("* %s %d %d\n", armazem[ids[i]].descricao, armazem[ids[i]].preco, lis_encom[ide].quantidade[ids[i]]);
	}
	else printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}

/* Chama uma funcao segundo o comando de input */
void lis_comandos(char comando){
	switch(comando){
		case 'a': adicionar_prod() ; break;
		case 'q': adicionar_stock(); break;
		case 'N': nova_enc(); break;
		case 'A': ad_pro_enc(); break;
		case 'r': remove_stock(); break;
		case 'R': remove_pro_ecom(); break;
		case 'C': custo_encom(); break;
		case 'p': alterar_preco(); break;
		case 'E': descricao_quantidade(); break;
		case 'm': max_produto(); break;
		case 'l': ordenar_preco(); break;
		case 'L': ordenar_desc(); break;
	}
}

int main(){
	char c, comando; /* comando de input */
	while ((c = getchar()) != 'x' && c != EOF){
		comando = c; 
		lis_comandos(comando);
	}
	return 0;
}