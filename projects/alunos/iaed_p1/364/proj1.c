#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define exch(A, B){prod t=A; A=B; B=t;}
#define PRODUTOS 10000
#define ENCOMENDAS 500
#define PRODUTOS_POR_ENCOMENDA 200
#define CARACTERES 64

void add_prod(int idp);
void add_stock(int idp);
void new_enc(int ide);
void add_prod_enc(int idp, int ide);
void remove_stock(int idp);
void remove_prod_enc(int idp, int ide);
void preco_enc(int ide);
void change_preco( int idp);
void desc_qtd_enc(int ide, int idp);
void enc_max_prod(int idp);
void ordem_preco();
void ordem_alfabetica_enc();

char descricao[CARACTERES];
int preco, peso, quantidade;

/**********************************************************/
/*********************** ESTRUTURAS ***********************/
/**********************************************************/

typedef struct produto
{
	int idp, preco, peso, qtd;
	char desc[CARACTERES];


} prod;

typedef struct encomenda
{
	int nr_prod_enc; /* Contador */
	int nr_enc, peso_enc, qtd_enc[PRODUTOS_POR_ENCOMENDA];

	prod prod_enc[PRODUTOS_POR_ENCOMENDA];

} enc;

/**********************************************************/
/******** FUNCOES DE ORDENACAO || E AUXILIARES ************/
/**********************************************************/

void quicksort(prod copia[], int first, int last, int FLAG);
int partition(prod copia[], int first, int last);
void selectionsort(prod copia[], int first, int last);
int peso_total_enc(enc a);

/**********************************************************/
/********************** FUNCAO MAIN  **********************/
/**********************************************************/

prod total_prod[PRODUTOS];
enc total_enc[ENCOMENDAS];

int idp = 0;
int ide = 0;

int main()
{
	char comando;

	while ((comando = getchar())!='x'){			/* At? a tecla 'x' nao ser precionada, manter o programa em execucao.*/ 
	switch (comando) 
	{
		case 'a':								/* Tecla 'a' executa a funcao add_prod. */
			add_prod(idp++); break;
		case 'q':								/* Tecla 'q' executa a funcao add_stock. */
			add_stock(idp); break;
		case 'N':								/* Tecla 'N' executa a funcao new_enc. */
			new_enc(ide++); break;
		case 'A':								/* Tecla 'A' executa a funcao add_prod_enc. */
			add_prod_enc(idp,ide); break; 
		case 'r':								/* Tecla 'r' executa a funcao remove_stock. */
			remove_stock(idp); break;
		case 'R':								/* Tecla 'R' executa a funcao remove_prod_enc. */
			remove_prod_enc(idp,ide); break;
		case 'C':								/* Tecla 'c' executa a funcao preco_enc. */
			preco_enc(ide); break;
		case 'p':								/* Tecla 'p' executa a funcao change_preco. */
			change_preco(idp); break;
		case 'E':								/* Tecla 'E' executa a funcao desc_qtd_enc. */
			desc_qtd_enc(ide,idp); break;
		case 'm':								/* Tecla 'm' executa a funcao enc_max_prod. */
			enc_max_prod(ide); break;
		case 'l':								/* Tecla 'l' executa a funcao ordem_preco. */
			ordem_preco(); break;
		case 'L':								/* Tecla 'L' executa a funcao ordem_alfabetica_enc. */
			ordem_alfabetica_enc(); break;
		default: break;	
	}
	
	}
	return 0;
}

/**********************************************************/
/******** FUNCOES DOS COMANDOS || E AUXILIARES ************/
/**********************************************************/


void add_prod(int idp)	/* 'a' */
{
	prod n;

	scanf(" %[^:]:%d:%d:%d", n.desc, &n.preco, &n.peso, &n.qtd);

	n.idp = idp;
	idp++;														

	total_prod[n.idp] = n;

	printf("Novo produto %d.\n", n.idp);
}


void add_stock(int idp)	/* 'q' */
{
	prod n;

	scanf("%d:%d", &n.idp, &quantidade);

	if (n.idp >= idp)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", n.idp);
	else
		total_prod[n.idp].qtd += quantidade; 
}


void new_enc(int ide)	/* 'N' */
{
	enc n;

	n.nr_enc = ide;
	total_enc[ide] = n;

	printf("Nova encomenda %d.\n", n.nr_enc);

}

int peso_total_enc(enc a)
{
	int i;
	for ( i = 0; i < a.nr_prod_enc; i++)			
		a.peso_enc += (a.prod_enc[i].qtd * a.prod_enc[i].peso); 					 																/* Adicionar o peso total de cada produto que j? estava inserido na encomenda */
	return a.peso_enc;

}
void add_prod_enc(int idp, int ide) /* 'A' */
{
	enc a;
	prod p;
	int i;
	int DENTRO = 0;
	scanf("%d:%d:%d", &a.nr_enc, &p.idp, &quantidade);

	if (a.nr_enc >= ide) 																															/* Verificacao da encomenda */
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", p.idp, a.nr_enc); 

	else if (p.idp >= idp) 																															/* Verificacao do produto */
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", p.idp, a.nr_enc);

	else if (total_prod[p.idp].qtd < quantidade)																									/* Verificacao da quantidade do produto no stock total */
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", p.idp, a.nr_enc); 

	else if ((peso_total_enc(total_enc[a.nr_enc])+(quantidade * total_prod[p.idp].peso))> 200) 														/* Verificacao do peso da encomenda */
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", p.idp, a.nr_enc);

	else {

			for ( i = 0; i < total_enc[a.nr_enc].nr_prod_enc; i++)																					/* Percorre os produtos da encomenda */
			{	
				if  (total_enc[a.nr_enc].prod_enc[i].idp == p.idp)																					/* Se j? existir o produto na encomenda */
				{
					DENTRO = 1;
					total_enc[a.nr_enc].prod_enc[i].qtd += quantidade; 																				/* Adiciona a quantidade de produto a encomenda*/
					total_prod[p.idp].qtd -= quantidade;
					break; 																															/* Retira ao Stock total a quantidade do produto adicionada ? encomenda */
				}
			}	
			if (DENTRO==0)																															/* Se nao existir na encomenda */
				{ 
					total_enc[a.nr_enc].prod_enc[i] = total_prod[p.idp];
					total_enc[a.nr_enc].prod_enc[i].qtd = quantidade;																				/* Adiciona a quantidade de produto a encomenda*/
					total_enc[a.nr_enc].nr_prod_enc++;																								/* Incrementa o contador de produtos na encomenda */
					total_prod[p.idp].qtd -= quantidade; 																							/* Retirar ao Stock total a quantidade do produto adicionada a encomenda */
				}
	}	
} 


void remove_stock(int idp)	/* 'r' */
{	
	prod n;
	scanf("%d:%d", &n.idp, &quantidade);

	if (n.idp >= idp) 																																/* Verificacao do produto */
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", n.idp);
	else if (total_prod[n.idp].qtd < quantidade)																									/* Verificacao da quantidade de stock existente */
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, n.idp);
	else 
		total_prod[n.idp].qtd -= quantidade;
}


void remove_prod_enc(int idp, int ide)	/* 'R' */
{
	prod n;
	enc a;
	int i;

	scanf("%d:%d", &a.nr_enc, &n.idp);
	if (a.nr_enc >= ide) 																															/* Verificacao da encomenda */
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", n.idp, a.nr_enc); 
	else if (n.idp >= idp) 																															/* Verificacao do produto */
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", n.idp, a.nr_enc);

	else 
	{	
		for (i=0; i < total_enc[a.nr_enc].nr_prod_enc;i++){																							/* Percorre os produtos da encomenda */
			if (total_enc[a.nr_enc].prod_enc[i].idp == n.idp){																						/* Verifica se o produto se encontra na encomenda */
				total_prod[n.idp].qtd += total_enc[a.nr_enc].prod_enc[i].qtd;																		/* Retirar ao Stock total a quantidade do produto adicionada a encomenda. */	
				total_enc[a.nr_enc].prod_enc[i].qtd = 0;																							/* Igualar a quantidade de produto na encomenda a zero */
			}	
		}
	}
}


void preco_enc(int ide)	/* 'C' */
{
	enc a;
	int total = 0, i;

	scanf("%d", &a.nr_enc);

	if (a.nr_enc >= ide) 																															/* Verificacao da encomenda. */
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", a.nr_enc); 
	else
	{
		for ( i = 0; i < total_enc[a.nr_enc].nr_prod_enc; i++)																						/* Percorre os produtos da encomenda. */
		{	 					 																		
			total += (total_enc[a.nr_enc].prod_enc[i].preco * total_enc[a.nr_enc].prod_enc[i].qtd);													/* Soma os precos dos produtos da encomenda. */
		}	
		printf("Custo da encomenda %d %d.\n",a.nr_enc, total);
	}
}

void change_preco(int idp)	/* 'p' */
{
	prod n;
	int i, j;

	scanf("%d:%d", &n.idp, &preco);

	if (n.idp >= idp) 																																/* Verificacao do produto. */
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", n.idp);
	else {
		total_prod[n.idp].preco = preco;																											/* Altera o preco dos produtos do sistema exteco os que estao nas encomendas. */

		for ( i = 0; i < ide; i++)																													/* Percorre todas as encomendas do sistema. */
		{
			for (j = 0; j < total_enc[i].nr_prod_enc; j++)																							/* Percorre os produtos de cada encomenda. */
			{
				if  (total_enc[i].prod_enc[j].idp == n.idp)																							/* Verifica se o produto se encontra na encomenda. */
					total_enc[i].prod_enc[j].preco = preco; 																						/* Altera o preco de produto na encomenda. */																						/* Retirar ao Stock total a quantidade do produto adicionada ? encomenda */
			}	
		}	
		}	
}

void desc_qtd_enc(int ide, int idp) /* 'E' */
{
	prod n;
	enc a;
	int i;
	int DEFINE = 0;

	scanf("%d:%d", &a.nr_enc, &n.idp);

	if (a.nr_enc >= ide) 																															/* Verificacao da encomenda */
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", a.nr_enc); 
	else if (n.idp >= idp) 																															/* Verificacao do produto */
		printf("Impossivel listar produto %d. Produto inexistente.\n", n.idp);
	else {
		for ( i = 0; i < total_enc[a.nr_enc].nr_prod_enc; i++)																						/* Percorre todas os produtos da encomenda do sistema. */
		{
			if  (total_enc[a.nr_enc].prod_enc[i].idp == n.idp)																						/* Verifica se o produto se encontra na encomenda. */
			{
				DEFINE = 1;
				printf("%s %d.\n", total_enc[a.nr_enc].prod_enc[i].desc, total_enc[a.nr_enc].prod_enc[i].qtd); 
			}
		}	
	if ( DEFINE == 0 )																																/* Caso o produto nao esteja na encomenda */
		printf("%s %d.\n", total_prod[n.idp].desc,0);
	}
}

void enc_max_prod(int ide)	/* 'm' */
{	
	prod n;
	int maior = 0;
	int guarda, i, j;
	scanf("%d", &n.idp);
	if (n.idp >= idp) 																																/* Verificacao do produto */
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", n.idp);
	else
	{
		for ( i = 0; i < ide; i++)																													/* Percorre todas as encomendas do sistema */
		{
			for ( j = 0; j < total_enc[i].nr_prod_enc; j++)
			{
				if (total_enc[i].prod_enc[j].idp == n.idp)																							/* Verifica se o produto se encontra na encomenda */
				{
					if  (total_enc[i].prod_enc[j].qtd > maior)																						/* Caso a a encomenda em analise contenha mais produto que a encomenda guardada ateriormente */
					{ 						
						maior = total_enc[i].prod_enc[j].qtd;																						/* Atualiza quantidade de produto */
						guarda = i;																													/* Atualiza a encomenda */
					}
				}
			}
		}
	if (maior > 0)																																	
		printf("Maximo produto %d %d %d.\n", n.idp, guarda, maior);
	}	
}

void ordem_preco() /* 'l' */
{	
	int i, j;
	prod copia[10000];
	for (j = 0; j < idp; j++)
	{
		copia[j] = total_prod[j];																													/* Criar uma copia do vetor total_prod para nao projudicar futuras acoes*/
	}
	quicksort(copia, 0, idp-1,1);																													/* Ordenar por pre?o */
	printf("Produtos\n");
	for (i = 0; i < idp; i++)	
	{
		printf("* %s %d %d\n", copia[i].desc, copia[i].preco, copia[i].qtd);
	}
	
}

void ordem_alfabetica_enc()	/* 'L' */
{
	enc a;
	prod copia[10000];
	int j,i;
	scanf("%d", &a.nr_enc);

	if (a.nr_enc >= ide) 																															/* Verificacao da encomenda */
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", a.nr_enc); 
	else
	{
		for (j = 0; j < total_enc[a.nr_enc].nr_prod_enc; j++)
		{
			copia[j] = total_enc[a.nr_enc].prod_enc[j];																								/* Criar uma copia do vetor total_prod para nao projudicar futuras acoes*/
		}

		selectionsort(copia,0,total_enc[a.nr_enc].nr_prod_enc - 1);																					/* Ordenar por ordem alfabetica os produtos da encomenda */
		
		printf("Encomenda %d\n", a.nr_enc);								
		for (i = 0; i < (total_enc[a.nr_enc].nr_prod_enc); i++)			
		{	
			if (copia[i].qtd != 0)
				printf("* %s %d %d\n", copia[i].desc, copia[i].preco, copia[i].qtd);
		}
	}
}

/****************************************************************************/
/********** FUNCOES ** DE ** ORDENACAO ** E ** SUAS ** AUXILIARES ***********/
/****************************************************************************/

void quicksort(prod copia[], int first, int last, int FLAG)	/* ALGORITMO EFICIENTE DE ORDENACAO - ORDENAR POR PRECO */
{
	int i;

	if (FLAG == 1){	/* Ordena por pre?o */
		if (last <= first)
			return;
		i = partition(copia,first,last);
		quicksort(copia,first,i-1,1);
		quicksort(copia,i+1,last,1);
		}
}

int partition(prod copia[], int first, int last) 	/* AUX PARA ORDENAR POR PRECO */
{
	prod pivot = copia[last];
	int i = (first - 1);
	int j = first;

	for (;j <= last-1; j++){
		if (copia[j].preco < pivot.preco)																											/* No caso do preco do elemento for menos do que o do elemento(pivot) */
		{						
			i++;																																	/* Incrementar o indice (<) */
			exch(copia[i],copia[j]);																												/* Trocar a ordem dos produtos */
		}
		else if (copia[j].preco == pivot.preco)																										/* No caso do preco do elemento for igual ao do elemento(pivot) */
		{
			if (copia[j].idp < pivot.idp)
			{
				i++;																																/* Incrementar o indice (<) */
				exch(copia[i],copia[j]);																											/* Trocar a ordem dos produtos */
			}
		}
	}
	exch(copia[i+1],copia[last]);
	return (i+1);
}

void selectionsort(prod copia[], int first, int last) /* ALGORITMO ELEMENTAR DE ORDENACAO - ORDENAR ALFABETICAMENTE */
{
	int i, j;
	for (i = first; i < last; i++)
	{
		prod aux;
		int min = i;
		for (j = i+1; j <= last; j++)
			if (strcmp(copia[j].desc, copia[min].desc) < 0)
				min = j;

		aux = copia[i]; copia[i] = copia[min]; copia[min] = aux;
	}
}


