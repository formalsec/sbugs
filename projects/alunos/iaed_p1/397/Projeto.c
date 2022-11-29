#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define DIMN 9999  /* N?mero m?ximo de produtos */
#define DIMA 3      /* N?mero de atributos (3 a contar com o 0) */

/* Declara??o das Fun??es */
void a(char *dc, float pr, float ps, int qtd);    /* Adiciona um novo produto ao sistema */
void q(int idp, int qtd);                         /* Adiciona stock a um produto existente no sistema */
char N();                                         /* Cria uma nova encomenda */
void A(int ide, int idp, int qtd);                /* Adiciona um produto a uma encomenda */
void r(int idp, int qtd);                         /* Remove stock a um produto existente */
void R(int ide, int idp);                         /* Remove um produto de uma encomenda */
int C(int ide);                                   /* Calcula o custo de uma encomenda */
void p(int idp, float preco);                     /* Altera o pre?o de um produto existente no sistema */
char E(int ide, int idp);                         /* Lista a descri??o e a quantidade de um produto numa encomenda */
int m(int idp);                                   /* Lista o identificador da encomenda em que o produto dado ocorre mais vezes */
char l();                                         /* Lista todos os produtos existentes no sistema por ordem crescente de pre?o */
char L(int ide);                                  /* Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
void x();                                         /* Termina o programa */

/* Inicializa??o dos vetores */
void inicprod(int v[DIMN][DIMA])
{
	int i, j;
	for(i=0 ; i<DIMN ; i++)
	  for(j=0 ; j<DIMA ; j++)
		v[i][j]=0;
}

/* FUN??ES */
/* Adiciona um novo produto ao sistema */
void a(char *desc, float preco, float peso, int qtd)
{
	int i=0; /* Identificador ?nico */
	scanf(" %[^:]:%f:%f:%d", desc, &preco, &peso, &qtd);
	printf("Novo Produto %d.\n", i++);
}

/*  Adiciona stock a um produto existente no sistema */
void q(int idp, int qtd)
{
	int i, q;
	scanf(" %d:%d", &i, &q);
	printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", i);
	
}

/* Adiciona um produto a uma encomenda */
void A(int ide, int idp, int qtd)
{
	int i, q, e;
	scanf(" %d:%d:%d", &i, &q, &e);
	printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", i, e);
	printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", i, e);
	printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", i, e);
	printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", i, e);
}

/* Remove stock a um produto existente */
void r(int idp, int qtd)
{
	int i, q;
	scanf(" %d:%d", &i, &q);
	printf("Impossivel remover stock do produto %d. Produto inexistente.\n", i);
	printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", q, i);
}

/* Remove um produto de uma encomenda */
void R(int ide, int idp)
{
	int e, i;
	scanf(" %d:%d", &e, &i);
	printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", i, e);
	printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", i, e);
}

/* Calcula o custo de uma encomenda */
int C(int ide)
{
	int e;
	scanf(" %d", &e);
	printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", e);
	return (0);
}

/* Altera o pre?o de um produto existente no sistema */
void p(int idp, float preco)
{
	int i;
	float p;
	scanf(" %d:%f", &i, &p);
	printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", i);
}

/* Lista a descri??o e a quantidade de um produto numa encomenda */
char E(int ide, int idp)
{
	int e, i;
	scanf(" %d:%d", &e, &i);
	printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", e);
	printf("Impossivel listar produto %d. Produto inexistente.\n", i);
	return (0);
}

/* Lista o identificador da encomenda em que o produto dado ocorre mais vezes */
int m(int idp)
{
	int i;
	scanf(" %d", &i);
	printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", i);
	return (0);
}

/* Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
char L(int ide)
{
	int e;
	scanf(" %d", &e);
	printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", e);
	return (0);
}

int main(int argc, char *argv[])
{
	int o[DIMN][DIMA];
	char desc, operator;
	float preco, peso;
	int qtd, idp, ide, i;
	
	inicprod(o);
	
	scanf("%c", &operator);
	
	  switch(operator)
	    {
		  case 'a':
			  a(&desc, preco, peso, qtd);
			  break;
			
		  case 'q':
			  q(idp, qtd);
			  break;
						
		  case 'N':
			  break;
			
		  case 'A':
			  A(ide, idp, qtd);
			  break;
			
		  case 'r':
			  r(idp, qtd);
			  break;
			
		  case 'R':
			  R(ide, idp);
			  break;

		  case 'C':
			  C(ide); 
			  break; 

		  case 'p':
			  p(idp, preco);
			  break;
	
		  case 'E':
			  E(ide, idp);
			  break;

		  case 'm':
			  m(idp);
			  break;

		  case 'l':
			  break;
	
		  case 'L':
			  L(ide);
			  break;
			
		  case 'x':
			  break;
	    }
}
