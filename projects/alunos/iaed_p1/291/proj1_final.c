#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define MAX_STR 63  /* tamanho maximo da descricao do produtom */
#define MAX_PROD 10000  /* numero maximo de produtos no sistema */
#define MAX_PESO 200 /* peso maximo de uma encomenda */
#define MAX_ENCOMENDA 500 /* numero maximo de encomendas no sistema */
#define IDENT_PROD 0 /* usado somente para ir buscar o idp de um produto na encomenda */
#define QUANT 1 /* usado somente para ir buscar a qtd de um produto na encomenda */


typedef struct produto{
	int ident, preco, peso, qtd;
	char descricao[MAX_STR];
} Produto;

typedef struct encomenda{
	int qtd_prod[MAX_PESO][2];	/* array com id's e quantidades de produtos na encomenda */
	int peso;					/* inteiro que representa o peso da encomenda */
	int n_prod_enc;				/* inteiro que representa o n de produtos adicionados a encomenda (nao diminui se um produto for removido) */
} Encomenda;

/* Seja e uma encomenda, e[3][IDENT_PROD] ? o idp do produto que est? na posicao 3 da encomenda e.
   e[3][QUANT] ? a quantidade desse produto na encomenda e. */



int __a__(int n_prod, Produto l_prod[MAX_PROD]){
	scanf(" %[^:]:", l_prod[n_prod].descricao);
	scanf("%d", &l_prod[n_prod].preco);
	scanf(":%d", &l_prod[n_prod].peso);
	scanf(":%d", &l_prod[n_prod].qtd);
	l_prod[n_prod].ident = n_prod;
	printf("Novo produto %d.\n", n_prod++); 
	return n_prod;
}


void __q__(int n_prod, Produto l_prod[MAX_PROD]){
	int idp, quant;
	scanf(" %d:%d", &idp, &quant);
	if (idp < n_prod)
		l_prod[idp].qtd += quant;
	else
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}


void __A__(int n_prod, int n_enc, Produto l_prod[MAX_PROD], Encomenda l_enc[MAX_ENCOMENDA]){
	int ide, idp, quant, i;
	scanf(" %d:%d:%d", &ide, &idp, &quant);
	if (ide >= n_enc)									/* ERROS */
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if (idp >= n_prod)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else if (quant > l_prod[idp].qtd)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	else if (l_enc[ide].peso + quant * l_prod[idp].peso > 200)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
	else{
		l_enc[ide].peso += quant * l_prod[idp].peso;
		l_prod[idp].qtd -= quant;
		for (i = 0; i < l_enc[ide].n_prod_enc; i++){
			if (l_enc[ide].qtd_prod[i][IDENT_PROD] == idp){		/* verificar se o produto ja esta na encomenda */
				l_enc[ide].qtd_prod[i][QUANT] += quant;			/* e adicionar apenas a qtd a que ja existia */
				return;
			}
		}
		if (l_enc[ide].n_prod_enc < MAX_PESO){							/* se o array ainda nao esta "cheio" */
			l_enc[ide].qtd_prod[l_enc[ide].n_prod_enc][QUANT] = quant;	/*adiciona produto e qtd a encomenda */
			l_enc[ide].qtd_prod[(l_enc[ide].n_prod_enc)++][IDENT_PROD] = idp;
		}
		else{
			for (i = 0; i < MAX_PESO; i++){						/* se o array ja esta cheio, verificar se algum produto foi removido (qtd = 0) */
				if (l_enc[ide].qtd_prod[i][QUANT] == 0){		/* e colocar o novo produto nessa posicao do array */
					l_enc[ide].qtd_prod[i][IDENT_PROD] = idp;
					l_enc[ide].qtd_prod[i][QUANT] = quant;
				}
			}
		}
	}
}


void __r__(int n_prod, Produto l_prod[MAX_PROD]){
	int idp, quant;
	scanf(" %d:%d", &idp, &quant);
	if (idp >= n_prod)									/* ERROS */
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	else if (l_prod[idp].qtd - quant < 0)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quant, idp);
	else
		l_prod[idp].qtd -= quant;
}


void __R__(int n_prod, int n_enc, Produto l_prod[MAX_PROD], Encomenda l_enc[MAX_ENCOMENDA]){
	int ide, idp, i;
	scanf(" %d:%d", &ide, &idp);
	if (ide >= n_enc)									/* ERROS */
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if (idp >= n_prod)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else{

		for (i = 0; i < l_enc[ide].n_prod_enc; i++){
			if (l_enc[ide].qtd_prod[i][IDENT_PROD] == idp){								/* procura produto */
				l_enc[ide].peso -= (l_enc[ide].qtd_prod[i][QUANT] * l_prod[idp].peso);	/* retira peso (qtd na encomenda * peso do produto) a encomenda */
				l_prod[idp].qtd += l_enc[ide].qtd_prod[i][QUANT];
				l_enc[ide].qtd_prod[i][QUANT] = 0;										/* coloca quantidade a 0 na encomenda */
			}
		}
	}	
}


void __C__(int n_enc, Produto l_prod[MAX_PROD], Encomenda l_enc[MAX_ENCOMENDA]){
	int ide;
	scanf(" %d", &ide);
	if (ide >= n_enc)									/* ERROS */
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	else{
		int i, custo = 0;
		for (i = 0; i < l_enc[ide].n_prod_enc; i++)
			custo += (l_enc[ide].qtd_prod[i][QUANT] * l_prod[l_enc[ide].qtd_prod[i][IDENT_PROD]].preco);
		printf("Custo da encomenda %d %d.\n", ide, custo);
	}
}


void __p__(int n_prod, Produto l_prod[MAX_PROD]){
	int idp, pr;
	scanf(" %d:%d", &idp, &pr);
	if (idp < n_prod)
		l_prod[idp].preco = pr;
	else
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}


void __E__(int n_prod, int n_enc, Produto l_prod[MAX_PROD], Encomenda l_enc[MAX_ENCOMENDA]){
	int ide, idp, i;
	scanf(" %d:%d", &ide, &idp);
	if (ide >= n_enc)									/* ERROS */
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else if (idp >= n_prod)
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	else{
		for (i = 0; i < l_enc[ide].n_prod_enc; i++){
			if (l_enc[ide].qtd_prod[i][IDENT_PROD] == idp){	/* procora produto */
				printf("%s %d.\n", l_prod[idp].descricao, l_enc[ide].qtd_prod[i][QUANT]);
				return;
			}
		}
		printf("%s 0.\n", l_prod[idp].descricao); /* printa 0 se o produto nao foi adicionado a encomenda */
	}
}


void __m__(int n_prod, int n_enc, Encomenda l_enc[MAX_ENCOMENDA]){
	int idp;
	scanf(" %d", &idp);
	if (idp >= n_prod)									/* ERROS */
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	else{
		int max_qtd = 0, max_ide = 0, i, j;
		for (i = 0; i < n_enc; i++){							/* itera pelas encomendas */
			for (j = 0; j < l_enc[i].n_prod_enc; j++){			/* itera pelos produtodos da encomenda */
				if (l_enc[i].qtd_prod[j][IDENT_PROD] == idp){	/* verifica se e o produto desejado */
					if (l_enc[i].qtd_prod[j][QUANT] > max_qtd){	/* se for a maior quantidade guarda qtd e id */
						max_qtd = l_enc[i].qtd_prod[j][QUANT];	  
						max_ide = i;							 
					}
				}
			}
		}
		if (max_qtd != 0)
			printf("Maximo produto %d %d %d.\n", idp, max_ide, max_qtd);
	}
}

/*_______________________________________________________ Funcoes para ordenacao_______________________________________________________ */


/* funcao que troca dois produtas numa encomenda */
void troca_prod_enc(int v[MAX_PESO][2], int i, int j){
	int a[2];
	a[0] = v[i][0];
	a[1] = v[i][1];
	v[i][0] = v[j][0];
	v[i][1] = v[j][1];
	v[j][0] = a[0];
	v[j][1] = a[1];
}


int partition_desc(int v[MAX_PESO][2], int e, int d, Produto l_prod[MAX_PROD]){
	int i = e - 1, j = d + 1;
	while (i < j){
		while (strcmp(l_prod[v[++i][IDENT_PROD]].descricao, l_prod[v[d][IDENT_PROD]].descricao) < 0); /* compara strings */
		while (strcmp(l_prod[v[d][IDENT_PROD]].descricao, l_prod[v[--j][IDENT_PROD]].descricao) < 0){
			if (j == e)
				break;
		}
		if (i < j)
			troca_prod_enc(v, i, j);
	}
	troca_prod_enc(v, i, d);
	return i;
}


void quicksort_desc(int v[MAX_PESO][2], int e, int d, Produto l_prod[MAX_PROD]){
	int i;
	if (d <= e)
		return;
	i = partition_desc(v, e, d, l_prod);
	quicksort_desc(v, e, i - 1, l_prod);
	quicksort_desc(v, i + 1, d, l_prod);
}

/* funcao que copia o conteudo de um vetor de prod (a) para outro (v_aux) */
void copia(int n_prod, Produto v_aux[MAX_PROD], Produto a[MAX_PROD]){
	int i;
	for (i = 0; i < n_prod; i++){		
		v_aux[i].ident = a[i].ident;
		v_aux[i].peso = a[i].peso;
		v_aux[i].preco = a[i].preco;
		v_aux[i].qtd = a[i].qtd;
		strcpy(v_aux[i].descricao, a[i].descricao);
	}
}

/* funcao que troca dois produtos num array de produtos */
void troca_prod(Produto v[], int i, int j){
	Produto a;
	a = v[i];
	v[i] = v[j];
	v[j] = a;
}

int partition_preco(Produto v[MAX_PROD], int e, int d){
	int i = e - 1, j = d + 1;	
	while (i < j){
		while (v[++i].preco < v[d].preco || ((v[i].preco == v[d].preco) && v[i].ident < v[d].ident));
		while (v[d].preco < v[--j].preco || ((v[d].preco == v[j].preco) && v[d].ident < v[j].ident)){
			if (j == e){
				break;
			}
		}
		if (i < j){
			troca_prod(v, i, j);
		}
	}
	troca_prod(v, i, d);
	return i;
}

void quicksort_preco(Produto v[MAX_PROD], int e, int d){
	int i;
	if (d <= e)
		return;
	i = partition_preco(v, e, d);
	quicksort_preco(v, e, i - 1);
	quicksort_preco(v, i + 1, d);
}

/*__________________________________________________________/ FIM ORDENACAO /__________________________________________________________*/


void __l__(int n_prod, Produto l_prod[MAX_PROD]){
	int i;
	Produto v_aux[MAX_PROD]; /* array auxiliar para nao desordenar o array de produtos principal */
	copia(n_prod, v_aux, l_prod);
	quicksort_preco(v_aux, 0, n_prod - 1); /* ordenar v_aux pelo preco dos produtos */
	printf("Produtos\n");
	for (i = 0; i < n_prod; i++){
		printf("* %s %d %d\n", v_aux[i].descricao, v_aux[i].preco, v_aux[i].qtd);
	}
}


void __L__(int n_enc, Produto l_prod[MAX_PROD], Encomenda l_enc[MAX_ENCOMENDA]){
	int ide;
	scanf(" %d", &ide);
	if (ide >= n_enc)									/* ERROS */
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);	
	else{
		int i;
		quicksort_desc(l_enc[ide].qtd_prod, 0, l_enc[ide].n_prod_enc - 1, l_prod); /* ordenar uma encomenda pela descricao dos seus produtos */
		printf("Encomenda %d\n", ide);
		for (i = 0; i < l_enc[ide].n_prod_enc; i++){
			if (l_enc[ide].qtd_prod[i][QUANT] != 0) /* se a qtd do produto na encomenda nao for zero, faz print */
				printf("* %s %d %d\n", l_prod[l_enc[ide].qtd_prod[i][IDENT_PROD]].descricao, l_prod[l_enc[ide].qtd_prod[i][IDENT_PROD]].preco, l_enc[ide].qtd_prod[i][QUANT]);
		}
		return;
	}
}

/* le os comandos do terminal e executa as funcoes correspondentes */
int main(){
	char c;
	Encomenda l_enc[MAX_ENCOMENDA] = {0}; 	/* array com todas as encomendas criadas */
	Produto l_prod[MAX_PROD] = {0};			/* array com todos os produtos criados */
	int n_prod = 0, n_enc = 0;				/* variaveis que representam, respetivamente, o numero de produtos e encomendas criadas */
	while ((c = getchar()) != EOF){
		if (c == 'a')
			n_prod = __a__(n_prod, l_prod);
		else if (c == 'q')
			__q__(n_prod, l_prod);
		else if (c == 'x')					/* termina o programa */
			break;
		else if (c == 'N')
			printf("Nova encomenda %d.\n", n_enc++); /* cria nova encomeda, aumentado em 1 o numero de encomendas */
		else if (c == 'A')
			__A__(n_prod, n_enc, l_prod, l_enc);
		else if (c == 'r')
			__r__(n_prod, l_prod);
		else if (c == 'R')
			__R__(n_prod, n_enc, l_prod, l_enc);
		else if (c == 'C')
			__C__(n_enc, l_prod, l_enc);
		else if (c == 'p')
			__p__(n_prod, l_prod);
		else if (c == 'E')
			__E__(n_prod, n_enc, l_prod, l_enc);
		else if (c == 'm')
			__m__(n_prod, n_enc, l_enc);
		else if (c == 'l')
			__l__(n_prod, l_prod);
		else if (c == 'L')
			__L__(n_enc, l_prod, l_enc);
	}
	return 0;
}