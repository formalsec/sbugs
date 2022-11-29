#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* ---------------------------------------------- DEFINICAO DE CONSTANTES ----------------------------------------------- */

#define MAXPRODUTOS 10000 /* Numero total de produtos */
#define MAXENCOMENDAS 500 /* Numero total de encomendas */
#define MAXPESO 200 /* Peso maximo de uma encomenda */
#define MAXDESC 63 /* Numero maximo de caracteres para a descricao */

/* ------------------------------------------ DEFINICAO DE PRODUTO (ESTRUTURA) ------------------------------------------ */

typedef struct{
	int idp; /* Identificador do produto (um numero inteiro no intervalo [0, 9999]) */
	char desc[MAXDESC]; /* Descricao do produto (uma string nao vazia com um maximo de 63 caracteres) */
	int preco; /* Preco de uma unidade de produto (um numero inteiro maior que 0) */
	int peso; /* Peso de uma unidade de produto (um numero inteiro maior que 0) */
	int qtd; /* Quantidade de produto (um inteiro maior ou igual a 0) */
} Produto;

Produto Encomendas[MAXENCOMENDAS][MAXPESO]; /* Vetor bidimensional de produtos, representa as encomendas */
/* Matriz onde sao guardados os identificadores das encomendas(linhas) e os produtos de cada encomenda(colunas) */
Produto Stock[MAXPRODUTOS]; /* Vetor unidimensional de produtos, representa todos os produtos existentes */
static int produtoscount; /* Identificador de produto */
static int encomendascount; /* Identificador de encomenda */

/* ----------------------------------------------------- PROTOTIPOS ---------------------------------------------------- */

/* ----- FUNCOES AUXILIARES ----- */

int calcula_preco(int ide, int idp); /* Calcula o preco de um produto */
int calcula_pesoE(int ide); /* Calcula o preso de uma encomenda */
void mostra_produto(int idp); /* Imprime um determinado produto */
void mostra_encomenda(int ide, int i); /* Imprime um determinado produto numa encomenda */
void bubble_idp(Produto a[], int l, int r); /* Ordenar os produtos por ordem crescente de idp */
void bubble_preco(Produto a[], int l, int r); /* Ordenar os produtos por ordem crescente de preco */
void bubble_desc(Produto a[], int l, int r); /* Ordenar os produtos de uma encomenda por ordem alfabetica */
int total_produtos(int ide); /* Numero de produtos numa encomenda */
void inicializar(int ide, int idp); /* Coloca o produto a zeros */
int procura_produto(int idp); /* Procura o produto idp no vetor de produtos(Stock) */

/* ----- FUNCOES (COMANDOS) ----- */

void novo_produto(); /* Comando a */
void adiciona_stock(int idp, int qtd); /* Comando q */
void nova_encomenda(); /* Comando N */
void adiciona_produto(int ide, int idp, int qtd); /* Comando A */
void remove_stock(int idp, int qtd); /* Comando r */
void remove_produto(int ide, int idp); /* Comando R */
void custo_encomenda(int ide); /* Comando C */
void alterar_preco(int idp, int preco); /* Comando p */
void listar_produto(int ide, int idp); /* Comando m */
void listar_maisvezes(int idp); /* Comando E */
void listar_produtos(); /* Comando l */
void listar_produtos_encomenda(int ide); /* Comando L */

/* ------------------------------------------------------- CODIGO ------------------------------------------------------ */

int
main()
{
  int idp, ide, qtd, preco, comando;
  int i, j, p; 

/* Inicializar o stock a zero */

  for (p = 0; p < MAXPRODUTOS; p++)
  {
  	Stock[p].idp = 0;
	strcpy(Stock[p].desc,"NULL");
	Stock[p].preco = 0;
	Stock[p].peso = 0;
	Stock[p].qtd = 0;	
  }

/* Inicializar as encomendas a zero */

  for(i=0; i < MAXENCOMENDAS; i++)
	 {
	 	for (j = 0; j < MAXPESO; j++)
	 	{
	 		inicializar(i,j);
	 	}
	 }

  while ((comando = getchar()) != 'x'){ 
    switch (comando) {
      case 'a':
        novo_produto();
        break;
      case 'q':
      	scanf("%d:%d", &idp, &qtd);
        adiciona_stock(idp, qtd);
        break;
      case 'N':
        nova_encomenda();
        break;
      case 'A':
      	scanf("%d:%d:%d", &ide, &idp, &qtd);
        adiciona_produto(ide, idp, qtd);
        break;
      case 'r':
      	scanf("%d:%d", &idp, &qtd);
        remove_stock(idp, qtd);
        break;
      case 'R':
      	scanf("%d:%d", &ide, &idp);
        remove_produto(ide, idp);
        break;
      case 'C':
      	scanf("%d", &ide);
        custo_encomenda(ide);
        break;
      case 'p':
      	scanf("%d:%d", &idp, &preco);
        alterar_preco(idp, preco);
        break;
      case 'E':
      	scanf("%d:%d", &ide, &idp);
      	listar_produto(ide, idp);
        break;
      case 'm':
      	scanf("%d", &idp);
      	listar_maisvezes(idp);
      	break;
      case 'l':
      	listar_produtos();
      	break;
      case 'L':
      	scanf("%d", &ide);
      	listar_produtos_encomenda(ide);
      	break;
      default:
      	break;
    }
  }
  return 0;
}


/* ----- FUNCOES COMANDOS ----- */


void novo_produto()
/* comando a - adiciona um novo produto ao sistema */
/* Esta funcao faz a leitura da desc, preco, peso e qtd */
/* Devolve o Novo Produto idp, onde idp corresponde ao valor do produtoscount */
{
	int preco, peso, qtd;
	char desc[MAXDESC];
	scanf(" %[^:]:%d:%d:%d", desc, &preco, &peso, &qtd);
	if (produtoscount < MAXPRODUTOS)
	{
		Stock[produtoscount].idp = produtoscount;
		strcpy(Stock[produtoscount].desc, desc);
		Stock[produtoscount].preco = preco;
		Stock[produtoscount].peso = peso;
		Stock[produtoscount].qtd = qtd;
		printf("Novo produto %d.\n", produtoscount);
		produtoscount ++;
	}
}


void adiciona_stock(int idp, int qtd)
/* comando q - adiciona stock a um produto existente no sistema */
/* Esta funcao recebe 2 inteiros, idp e qtd, soma a quantidade existente no stock, */
/* correspondente ao produto idp a quantidade passada como argumeto */
/* Caso nao o produto idp nao exista a funcao devolve um erro */
{
	if (idp < produtoscount)
	{
		int p;
		p = procura_produto(idp);
		Stock[p].qtd += qtd;
	}
		else
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}


void nova_encomenda()
/* comando N - cria uma nova encomenda */
/* Esta funcao devolve Nova Encomenda ide, onde ide corresponde ao valor do encomendascount */
{
	if (encomendascount < MAXENCOMENDAS)
	{
		printf("Nova encomenda %d.\n", encomendascount);
		encomendascount ++;
	}
}


void adiciona_produto(int ide, int idp, int qtd)
/* comando A - adiciona um produto a uma encomenda. */
/* Se o produto ja existir na encomenda, adiciona a nova quantidade a quantidade existente */
/* Esta funcao recebe 3 inteiros, ide(identificador de encomenda), idp(identificador do produto), qtd(quantidade) */
/* No caso de a encomenda nao existir, no caso do produto nao existir, no caso de nao existir stock suficiente desse produto */
/* para satisfazer a encomenda e no caso da adicao do produto exceder o peso maximo permitido por encmenda, a funcao devolve um erro */
{
	int i, p, t;
	p = procura_produto(idp); /* corresponde a posicao no vetor Stock do produto idp. */
	t = total_produtos(ide); /* corresponde ao numero de produtos na encomenda ide. */
	if (ide >= encomendascount)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if (idp >= produtoscount)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else if (qtd > Stock[p].qtd)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	else if ((calcula_pesoE(ide) + (Stock[p].peso * qtd)) > MAXPESO)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", idp, ide, MAXPESO);	
	else
		{
			for (i = 0; i < produtoscount; i ++)
			{
				 if (i == t || (Encomendas[ide][i].idp == idp && Encomendas[ide][i].preco != 0))
				/* caso o produto nao exista na encomenda igualamos a posicao correta do vetor ao produto */

					{
						Encomendas[ide][i].idp = Stock[p].idp ;
						strcpy(Encomendas[ide][i].desc, Stock[p].desc);
						Encomendas[ide][i].preco = Stock[p].preco;
						Encomendas[ide][i].peso = Stock[p].peso;
						Encomendas[ide][i].qtd += qtd;
						
						break;
					}
			}
			remove_stock(idp, qtd);
		}
}


void remove_stock(int idp, int qtd)
/* comando r -  remove stock a um produto existente */ 
/* Esta funcao recebe 2 inteiros, idp e qtd, e retira ao stock do produto a qtd dada. */
/* Caso o produto nao exista, ou a qtd for maior que a qtd em stock, devolve erro*/
{	
	int p;
	p = procura_produto(idp);
	if (idp < produtoscount)
	{
		if (Stock[p].qtd >= qtd)
			Stock[p].qtd = Stock[p].qtd - qtd;
		else
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
	}
	else
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
}


void remove_produto(int ide, int idp)
/* comando R - remove um produto de uma encomenda */
/* Esta funcao recebe 2 inteiros, ide e idp, vai remover o produto idp da encomenda ide, caso exista. */
/* Remover significa neste caso que o identificador do produto na encomenda passa a ser -1, o preco, a qtd e o peso passam a ser 0. */
/* Caso a encomenda ou o produto nao existam devolve erro*/
{
	int i;
	if (ide < encomendascount)
	{
		if (idp < produtoscount)
		{
			for(i=0; i < total_produtos(ide); i++)
			{  
				if (Encomendas[ide][i].idp == idp && Encomendas[ide][i].peso != 0) 
				/* Como inicialmente o vetor foi inicializado a zeros, quando o idp e igua a zero tem de comfirmar que ele pertence mesmo a encomenda*/
				{	
					/* adicionar a quantidade do produto removido da encomenda a quantidade em stock do produto correspondente */
					adiciona_stock(idp,Encomendas[ide][i].qtd);

					Encomendas[ide][i].idp = -1; 
					Encomendas[ide][i].preco = 0;
					Encomendas[ide][i].peso = 0;
					Encomendas[ide][i].qtd = 0;
					
					break;
				}
				else
					continue;
			}
		}
		else
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);	
}


void custo_encomenda(int ide)
/* comando C - calcula o custo de uma encomenda */
/* Esta funcao recebe 1 inteiro, ide, e calcula o preco da encomenda ide. Se a encomenda nao exitir devolve erro*/
{
	int i;
	int custo = 0;
	if (ide < encomendascount)
	{
		for (i = 0; i < total_produtos(ide); i++) /* chama a funcao que calcula o numero total de produtos numa encomenda */
		{
			custo = custo + calcula_preco(ide, i); /* chama a funcao que calcula o preco de um produto */
		}
		printf("Custo da encomenda %d %d.\n", ide, custo);
	}
	else
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
}


void alterar_preco(int idp, int preco)
/* comando p - altera o preco de um produto existente no sistema */
/* Esta funcao recebe 2 inteiros, idp e preco, e vai alterar o preco do porduto idp para o preco dado*/
{
	int i,j,p;
	p = procura_produto(idp);
	if (idp < produtoscount)
	{
		Stock[p].preco = preco;

		for (i=0; i < encomendascount; i++)
		{
			for (j=0; j < total_produtos(i); j++) /* altera o preco do produto na encomenda caso ele exista na mesma */
			{
				if (Encomendas[i][j].idp == idp && Encomendas[i][j].peso != 0)
					Encomendas[i][j].preco = preco;
			}
		}
	}
	else
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}


void listar_produto(int ide, int idp)
/* comando E - lista a descricao e a qunatidade de um produto numa encomenda */
/* Esta funcao recebe 2 inteiros, ide e idp, e devolve a descricao do produto idp e a qtd do produto idp na encomenda ide. */
/* Da forma: <desc> <qtd>. onde <desc> e a descricao do produto <idp> e <qtd> e a quantidade desse produto na encomenda <ide>. */
/* Caso o produto ou a encomenda nao existam devolve erro */
{
	int i,t=0;
	int p = 0;
	p = procura_produto(idp);
	if (ide < encomendascount)
	{
		if (idp < produtoscount)
		{
			for(i = 0; i < total_produtos(ide); i++)
			{
				if (Encomendas[ide][i].idp == idp && Encomendas[ide][i].preco != 0) /* caso o produto exista na encomenda */
					{
						printf("%s %d.\n",Encomendas[ide][i].desc, Encomendas[ide][i].qtd);
						t ++;
						break;
					}
					
			}
			if (t == 0)
				printf("%s %d.\n",Stock[p].desc, 0);

		}
		else 
			printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	}
	else 
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}


void listar_maisvezes(int idp)
/* comando m - lista o identificador da encomenda em que o produto dado ocorre mais vezes. */
/* Se houver 2 ou mais encomendas nessa situacao, devera imprimir a encomenda de menor id. */ 
/* Esta funcao recebe um intiero, idp, devolve a encomenda em que a quantidade do produto idp e maior, a qtd do produto idp correspondente naquela encomenda. */
/* Da forma: Maximo produto <idp> <ide> <qtd>. */ 
/* Caso o produto ou a encomenda nao existam devolve erro */
{
	int i,j;
	int t = 0;
	int max = 0;
	int ide = 0;
	if (idp < produtoscount)
	{
		for (i = 0; i < encomendascount; i++)
		{
			for (j = 0; j < total_produtos(i); j++)
			{
				if (Encomendas[i][j].idp == idp && Encomendas[i][j].peso !=0)
				{		
					/* a variavel t ve se existe algum produto idp nuuma encomenda, se t = 0, nao existe o prouto idp em nenhuma das encomendas*/
					if (Encomendas[i][j].qtd > max)
					{	
						t++;
						max = Encomendas[i][j].qtd; /* ver qual e a qtd maxima do produto*/
						ide = i;
						/* ide corresponde ao ide na encomenda onde o produto idp aparece mais vezes */
					}
					else if (i == ide)
						max = max + Encomendas[i][j].qtd;
				}
			}
		} 
		if (t >= 1)
			printf("Maximo produto %d %d %d.\n", idp, ide, max);
	}
	else
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
}


void listar_produtos()
/* comando l - lista todos os produtos existentes no sistema por ordem crescente de preco. */
/* Se houver 2 ou mais produtos com o mesmo preco, devera imprimir imprimir esses por ordem crscente de preco. */
{
	int i;
	bubble_idp(Stock, 0, (produtoscount));
	bubble_preco(Stock, 0, (produtoscount));
	printf("Produtos\n");
  	for (i = 0; i < produtoscount; i++) 
  	{
    	mostra_produto(i); /* chama a funcao auxiliar que imprime o produto */
    }
}


void listar_produtos_encomenda(int ide)
/* comando L - lista todos os produtos de uma encomenda por ordem alfabetica de descricao. */ 
/* Esta funcao recebe 1 inteiro, ide, corresponde ao identificador da lista que iremos listar */
/* Se a encomenda nao tiver produtos imprime apenas Encomenda ide,corresponde ao numero da encomenda*/
/* Caso a encomenda nao exista devolve erro. */
{
	int i,t;
	t = total_produtos(ide);
	if (ide < encomendascount)
	{
		if (t > 0)
		{	
			bubble_desc(Encomendas[ide], 0, t);
			printf("Encomenda %d\n", ide);
  			for (i = 0; i < t; i++) 
  			{
  				if (Encomendas[ide][i].peso != 0) /* verificar se os proutos existem mesmo na encomenda*/
    				mostra_encomenda(ide, i); /* chama a funcao auxiliar que imprime o produto */
    			else
    				continue;
  			}
  		}
  		else 
  			printf("Encomenda %d\n", ide);
  	}
  	else
  		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide );
}


/* ----- FUNCOES AUXILIARES ----- */


int calcula_pesoE(int ide)
/* calcula o peso de uma encomenda. */
/* Esta funcao recebe 1 inteiro, ide, correspondente ao numero de encomenda. */
{
	int i;
	int peso = 0;
	for (i=0; i < total_produtos(ide); i++ )
	{
		peso = peso + (Encomendas[ide][i].peso * Encomendas[ide][i].qtd);
	}
	return peso;
}

int total_produtos(int ide)
/* Esta funcao recebe 1 inteiro, ide, correspondente ao numero de encomenda. */
/* Devolve o numero de produtos nessa encomenda. */
{
	int i, total = 0;
	for (i = 0; i < produtoscount; i++)
	{
		if (Encomendas[ide][i].preco != 0 || Encomendas[ide][i].idp == -1 )
			total ++;
	}
	return total;
}


void inicializar(int ide, int idp)
/* Esta funcao recebe 2 inteiros, ide, correspondente ao numero de encomenda e idp, corresponde ao numero do produto. */
/* coloca um produto do vetor encomendas a 0. */
{
			Encomendas[ide][idp].idp = 0;
	 		strcpy(Encomendas[ide][idp].desc, "NULL");
	 		Encomendas[ide][idp].preco = 0;
	 		Encomendas[ide][idp].peso = 0;
	 		Encomendas[ide][idp].qtd = 0;
}


int procura_produto(int idp)
/* Esta funcao recebe 1 inteiro, idp, correspondente ao numero de produto. */
/* Devolve a posicao do vetor Stock, correspondente ao produto idp. */
{
	int i, j = 0;
	for(i = 0; i < produtoscount; ++i)
	{
		if (Stock[i].idp == idp)
			j = i;
	}
	return j;
}


int calcula_preco(int ide, int idp)
/* Esta funcao recebe 2 inteiros, ide e idp, e calcula o preco do poduto idp na encomenda ide. */
{
	int preco = 0;
	preco = Encomendas[ide][idp].preco * Encomendas[ide][idp].qtd;

	return preco;
}


void mostra_produto(int idp)
/* Esta funcao recebe 1 inteiro, idp, e imprime o produto idp. */
/* Da forma: * <desc> <preco> <qtd em stock> */
{
	if (idp >= 0 && idp < produtoscount)
	{
		printf("* %s %d %d\n", Stock[idp].desc, Stock[idp].preco, Stock[idp].qtd);
	}
	
}


void mostra_encomenda(int ide, int i)
/* Esta funcao recebe 2 inteiro, ide e i, e imprime o produto correspondente a posicao i da encomenda ide. */
/* Da forma: * <desc> <preco> <qtd na encomenda ide> */
{
	if (i >= 0 && i < produtoscount)
	{
    	printf("* %s %d %d\n", Encomendas[ide][i].desc, Encomendas[ide][i].preco, Encomendas[ide][i].qtd);	
	}
}


void bubble_idp(Produto a[], int l, int r)
/* Esta funcao recebe 1 vetor de produtos e 2 inteiros, l e r, limites do vetor de produtos */ 
/* Ordena um vetor de produtos pela ordem crescente idp. */
/* Genero de bubble sort. */
{ 
	int i, j;
	Produto pro;
	for (i = l; i < r; i++){
		for (j = l; j < r + (l - 1); j++) 
			if (a[j].idp > a[j + 1].idp){  
				pro = a[j];
				a[j] = a[j+1];
				a[j+1] = pro;
			}
	}
}


void bubble_preco(Produto a[], int l, int r)
/* Esta funcao recebe 1 vetor de produtos e 2 inteiros, l e r, limites do vetor de produtos */ 
/* Ordena um vetor de produtos pela ordem crescente preco. */
/* Genero de bubble sort. */
{ 
	int i, j;
	Produto pro;
	for (i = l; i < r; i++){
		for (j = l; j < r + (l - 1); j++) 
			if (a[j].preco > a[j + 1].preco){  
				pro = a[j];
				a[j] = a[j+1];
				a[j+1] = pro;
			}
	}
}


void bubble_desc(Produto a[], int l, int r)
/* Esta funcao recebe 1 vetor de produtos e 2 inteiros, l e r, limites do vetor de produtos */ 
/* Ordena um vetor de produtos por ordem alfabetica de descricao */
/* Genero de bubble sort. */
{ 
	int i, j;
	Produto pro;
	for (i = l; i < r; i++){
		for (j = l; j < r + (l - 1); j++) 
			if (strcmp(a[j].desc,a[j+1].desc) > 0){  
				pro = a[j];
				a[j] = a[j+1];
				a[j+1] = pro;
			}
	}
}