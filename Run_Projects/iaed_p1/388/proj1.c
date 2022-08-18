#include <stdio.h>

#define MPROD 10000
#define MDES 63
#define MENCO 500
#define MPESO 200

/* Estruturas utilizadas (produtos e encomendas) */
typedef struct produto{
	char des[MDES];
	int preco, kg, qtd, id;
} prod;


typedef struct encomenda{ 
	int produtos, peso;
	int idprod[MPROD], qtprod[MPROD];
} enco;

/* Variaveis globais */
enco lenco[MENCO], nenco;

/* Serve para encontrar o indice de um item numa lista (devolve o indice do elemento se encontrar, se nao devolve -1) */
int ifinder(int item, int size, int *lista){
	int i;
	for (i = 0; i < size; i++){
		if (item == lista[i])
			return i;
	}
	return -1;
}

/* Funcao que troca dois produtos de indice i e j numa lista */
void trcprod(int i, int j, prod *clprod){
	prod cprod;
	cprod = clprod[i];
	clprod[i] = clprod[j];
	clprod[j] = cprod;
}

/* Verifica se os precos sao iguais para manter a rdem dos ids, caso sejam */
int prcig(prod prod1, prod prod2){
	if (prod1.preco == prod2.preco)
		return prod1.id < prod2.id;
	return prod1.preco < prod2.preco;
}

/* Funcao auxiliar responsavel por fazer a particao da lista de produtos na funcao quicksort */
int divprod(prod *clprod, int e, int d){
	int i = e - 1;
	int j = d;
	prod p = clprod[d];
	while (i < j){
		while (prcig(clprod[++i], p));
		while (prcig(p, clprod[--j]))
			if (j == e)
				break;
		if (i < j)
			trcprod(i, j, clprod);
	}
 	trcprod(i, d, clprod);
	return i;
}

/* Funcao auxiliar responsavel por fazer a particao da lista de produtos de uma encomenda na funcao quicksort */
int divenco(prod *clprod, int e, int d){
	int i = e - 1;
	int j = d;
	int ind;
	char cdes[MDES];
	for (ind = 0; ind < MDES; ind++)
		cdes[ind] = clprod[d].des[ind];
	while (i < j){
		while (strcmp(clprod[++i].des, cdes) < 0);
		while (strcmp(cdes, clprod[--j].des) < 0)
			if (j == e)
				break;
		if (i < j)
			trcprod(i, j, clprod);
	}
	trcprod(i, d, clprod);
	return i;
}


/* Funcao que faz o sort de uma lista de produtos (estado serve para verificar se trata de uma encomenda (L) ou produto (l)) */
void quicksort(prod *clprod, int e, int d, int estado){
	int i;
	if (d <= e)
		return;
	if (estado == 1){
		i = divprod(clprod, e, d);
		quicksort(clprod, e, i - 1, 1);
		quicksort(clprod, i + 1, d, 1);
	}
	else{
		i = divenco(clprod, e, d);
		quicksort(clprod, e, i - 1, 0);
		quicksort(clprod, i + 1, d, 0);
	}
}

/* Funcoes que tratam dos comandos introduzidos pelo utilizador */

void acommand(int idp, prod *lprod){
	prod nprod;
	getchar();
	scanf("%[^:]:%d:%d:%d", nprod.des, &nprod.preco, &nprod.kg, &nprod.qtd);
	printf("Novo produto %d.\n", idp);
	nprod.id = idp;
	lprod[idp] = nprod;
}

void qcommand(int idp, prod *lprod){
	int idpa, qtda;
	getchar();
	scanf("%d:%d", &idpa, &qtda);
	if (idp <= idpa)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idpa);
	else
		lprod[idpa].qtd += qtda;
}

void Ncommand(int ide, enco *lenco){
	printf("Nova encomenda %d.\n", ide);
	nenco.peso = 0;
	nenco.produtos = 0;
	nenco.qtprod[0] = 0;
	lenco[ide] = nenco;
}

void Acommand(int idp, int ide, prod *lprod, enco *lenco){
	int idea, idpa, qtda, fres;
	getchar();
	scanf("%d:%d:%d", &idea, &idpa, &qtda);
	if (ide <= idea)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idpa, idea);
	else if (idp <= idpa)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idpa, idea);
	else if (lprod[idpa].qtd < qtda)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idpa, idea);
	else if (lenco[idea].peso + (lprod[idpa].kg * qtda) > MPESO)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", idpa, idea, MPESO);
	else{ 
		/* Procura se o produto existe na lista de produtos. Caso exista, adiciona a quantidade da encomenda, 
		caso contrario adiciona o novo produto a encomenda */
		fres = ifinder(idpa, lenco[idea].produtos, lenco[idea].idprod);
		if (fres == -1){
			lenco[idea].idprod[lenco[idea].produtos] = lprod[idpa].id;
			lenco[idea].qtprod[lenco[idea].produtos] += qtda;
			lenco[idea].produtos++;
		}
		else
			lenco[idea].qtprod[fres] += qtda;
		lenco[idea].peso += (lprod[idpa].kg * qtda);
		lprod[idpa].qtd -= qtda;
	}
}

void rcommand(int idp, prod *lprod){
	int idpa, qtda;
	getchar();
	scanf("%d:%d", &idpa, &qtda);
	if (idp <= idpa)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idpa);
	else if (lprod[idpa].qtd < qtda)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtda, idpa);
	else
		lprod[idpa].qtd -= qtda;
}

void Rcommand(int idp, int ide, prod *lprod, enco *lenco){
	int idpa, idea, fres;
	getchar();
	scanf("%d:%d", &idea, &idpa);
	if (ide > idea){
		if (idp <= idpa)
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idpa, idea);
		else{
			fres = ifinder(idpa, lenco[idea].produtos, lenco[idea].idprod);
			/* Se encontrar o produto na encomenda, remove-o, caso contrario, nada acontece */
			if (fres != -1){
				lenco[idea].produtos--;
				lenco[idea].peso -= (lprod[idpa].kg * lenco[idea].qtprod[fres]);
				lprod[idpa].qtd += lenco[idea].qtprod[fres];
				lenco[idea].idprod[fres] = lenco[idea].idprod[lenco[idea].produtos];
				lenco[idea].qtprod[fres] = lenco[idea].qtprod[lenco[idea].produtos];
				lenco[idea].idprod[lenco[idea].produtos] = 0;
				lenco[idea].qtprod[lenco[idea].produtos] = 0;
			}
		}
	}
	else
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idpa, idea);
}

void Ccommand(int ide, prod *lprod, enco *lenco){
	int idea, i, res = 0;
	getchar();
	scanf("%d", &idea);
	if (idea < ide){
		/* Loop que calcula o custo da encomenda */
		for (i = 0; i < lenco[idea].produtos; i++){
			res += (lprod[lenco[idea].idprod[i]].preco * lenco[idea].qtprod[i]);
		}
		printf("Custo da encomenda %d %d.\n", idea, res);
	}
	else
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idea);
}

void pcommand(int idp, prod *lprod){
	int idpa, pa;
	getchar();
	scanf("%d:%d", &idpa, &pa);
	if (idpa < idp)
		lprod[idpa].preco = pa;
	else
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idpa);
}

void Ecommand(int idp, int ide, prod *lprod, enco *lenco){
	int idpa, idea, i;
	getchar();
	scanf("%d:%d", &idea, &idpa);
	if (ide <= idea)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idea);
	else if (idp <= idpa)
		printf("Impossivel listar produto %d. Produto inexistente.\n", idpa);
	else{
		i = ifinder(idpa, lenco[idea].produtos, lenco[idea].idprod);
		printf("%s %d.\n", lprod[idpa].des, lenco[idea].qtprod[i]);
	}
}

void mcommand(int idp, int ide, enco *lenco){
	int i, max = 0, idea, idpa, j;
	getchar();
	scanf("%d", &idpa);
	if (idp <= idpa)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idpa);
	else{
		for (i = 0; i < ide; i++){
			j = ifinder(idpa, lenco[i].produtos, lenco[i].idprod);
			/* Caso o produto nao exista na encomenda, passa para a proxima encomenda */
			if (j == -1)
				continue;
			/* Atualiza o maximo e o id da encomenda atual, se o maximo aumentar */
			if (max < lenco[i].qtprod[j]){
				max = lenco[i].qtprod[j];
				idea = i;
			}
		}
		/* Caso o maximo seja zero, nao devolve nada */
		if (max != 0)
			printf("Maximo produto %d %d %d.\n", idpa, idea, max);
	}
}

void lcommand(int idp, prod *lprod){
	int i;
	prod clprod[MPROD];
	/* Loop que copia a lista de produtos, para ser organizada */
	for (i = 0; i < idp; i++)
		clprod[i] = lprod[i];
	if (idp > 0)
		quicksort(clprod, 0, idp - 1, 1);
	printf("Produtos\n");
	/* Loop que lista os produtos por ordem */
	for (i = 0; i < idp; i++)
		printf("* %s %d %d\n", clprod[i].des, clprod[i].preco, clprod[i].qtd);
}

void Lcommand(int ide, prod *lprod, enco *lenco){
	int i, idea;
	prod clprod[MPROD];
	getchar();
	scanf("%d", &idea);
	if (idea < ide){
		/* Loop que copia os produtos e a sua quantidade numa encomenda para serem organizados */
		for (i = 0; i < lenco[idea].produtos; i++){
			clprod[i] = lprod[lenco[idea].idprod[i]];
			clprod[i].qtd = lenco[idea].qtprod[i];
		}
		quicksort(clprod, 0, lenco[idea].produtos - 1, 0);
		printf("Encomenda %d\n", idea);
		/* Loop que lista os produtos por ordem */
		for (i = 0; i < lenco[idea].produtos; i++)
			printf("* %s %d %d\n", clprod[i].des, clprod[i].preco, clprod[i].qtd);
	}
	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idea);
}

/* Funcao main que corre o programa */
int main(){
	prod lprod[MPROD];
	char c;
	int idp = 0, ide = 0;
	/* Ciclo reponsavel por manter o programa a correr */
	while (1){
		/* Recebe o comando e escolhe a entrada apropriada */
		c = getchar();
		switch (c){
			case 'a':
				acommand(idp, lprod);
				idp++;
				break;
			case 'q':
				qcommand(idp, lprod);
				break;
			case 'N':
				Ncommand(ide, lenco);
				ide++;
				break;
			case 'A':
				Acommand(idp, ide, lprod, lenco);
				break;
			case 'r':
				rcommand(idp, lprod);
				break;
			case 'R':
				Rcommand(idp, ide, lprod, lenco);
				break;
			case 'C':
				Ccommand(ide, lprod, lenco);
				break;
			case 'p':
				pcommand(idp, lprod);
				break;
			case'E':
				Ecommand(idp, ide, lprod, lenco);
				break;
			case 'm':
				mcommand(idp, ide, lenco);
				break;
			case 'l':
				lcommand(idp, lprod);
				break;
			case 'L':
				Lcommand(ide, lprod, lenco);
				break;
			case 'x':
				return 0;
		}
	}
}