#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define IDP 10000
#define IDE 500
#define MAXDSCR 63
#define PESO 200
#define exch(A,B) {int t;t=A;A=B;B=t;}

/*	Estruturas globais: produto e encomenda	*/
typedef struct
{
	int indexprod;
	int preco;
	int peso;
	int qtd;
	char dscr[MAXDSCR];
}produto;

typedef struct
{
	produto prodenc[PESO];                   /* A Encomenda tem 200 de peso max, cada produto tem 1 de peso min, logo a encomenda tem 200 produtos max*/
	int pesoenc;
	int precoenc;
	int numeroprod;
}encomenda;

/*	Variaveis globais */
int idp=0,ide=0;
produto prod[IDP];
encomenda enc[IDE];

/*	Funcao auxiliar,
	Retorna o peso de uma encomenda. */
int peso_da_encomenda(int n)
{
	int i=0;
	enc[n].pesoenc=0;
	while (i<enc[n].numeroprod)
	{
		enc[n].pesoenc+=(enc[n].prodenc[i].peso)*(enc[n].prodenc[i].qtd);
		i++;
	}
	return enc[n].pesoenc;
}

/*	Comando 'a',
	Adiciona um produto ao sistema
	junto com a sua descricao,
	preco e peso por unidade. */

void adiciona_produto()
{
	scanf(" %[^:]:%d:%d:%d",prod[idp].dscr ,&prod[idp].preco,&prod[idp].peso,&prod[idp].qtd);
	printf("Novo produto %d.\n",idp);
	idp++;
}

/*	Comando 'q'
	Adiciona quantidade de produto
	relativa ao produto indicado. */

void adiciona_stock()
{
	int idptemp,qtd;
	scanf(" %d:%d", &idptemp,&qtd);
	if (idptemp>idp-1)
	{
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idptemp);
	}
	else
	{
		prod[idptemp].qtd+=qtd;
	}
}

/*	Comando 'N',
	Cria uma encomenda. */

void cria_encomenda()
{
	printf("Nova encomenda %d.\n",ide);
	enc[ide].numeroprod=0;
	ide++;
}

/*	Comando 'A',
	Adiciona um dado produto a uma
	encomenda indicada, especificando
	a quantidade do produto. */

void adiciona_produto_a_encomenda()
{
	int idetemp,i,idptemp,qtd;
	scanf(" %d:%d:%d",&idetemp,&idptemp,&qtd);
	if (idetemp>ide-1)
	{	
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idptemp,idetemp);
	}
	else if (idptemp>idp-1)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idptemp,idetemp);
	}
	else if (qtd>(prod[idptemp].qtd))
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idptemp,idetemp);
	}
	else if (((peso_da_encomenda(idetemp))+(qtd*prod[idptemp].peso))>200)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idptemp,idetemp);
	}
	else
	{
		for (i=0;i<enc[idetemp].numeroprod;i++)
		{
			if(enc[idetemp].prodenc[i].indexprod==idptemp)                       /* Quando eh um produto ja existente */
			{
				enc[idetemp].prodenc[i].qtd+=qtd;
				enc[idetemp].prodenc[i].preco=prod[idptemp].preco;
				enc[idetemp].prodenc[i].peso=prod[idptemp].peso;
				strcpy(enc[idetemp].prodenc[i].dscr,prod[idptemp].dscr);
				prod[idptemp].qtd-=qtd;
				return;
			}
		}	

		enc[idetemp].prodenc[enc[idetemp].numeroprod].indexprod=idptemp;		/* Quando eh um produto novo */
		enc[idetemp].prodenc[enc[idetemp].numeroprod].qtd+=qtd;
		enc[idetemp].prodenc[enc[idetemp].numeroprod].preco=prod[idptemp].preco;
		enc[idetemp].prodenc[enc[idetemp].numeroprod].peso=prod[idptemp].peso;
		strcpy(enc[idetemp].prodenc[enc[idetemp].numeroprod].dscr,prod[idptemp].dscr);
		prod[idptemp].qtd-=qtd;
		enc[idetemp].numeroprod++;

	}
}

/*	Comando 'r',
	Remove quantidade de um produto
	especifico. */

void remove_stock()
{
	int idptemp,qtd;
	scanf(" %d:%d",&idptemp,&qtd);
	if (idptemp>idp-1)
	{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idptemp);
	}
	else if (prod[idptemp].qtd-qtd<0)
	{
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idptemp);
	}
	else
	{
		prod[idptemp].qtd-=qtd;
	}
}

/*	Comando 'R',
	Remove um dado produto de uma
	encomenda indicada. */

void remove_produto_a_encomenda()
{
	int idetemp,i,idptemp;
	scanf(" %d:%d",&idetemp,&idptemp);
	if (idetemp>ide-1)
	{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idptemp,idetemp);
	}
	else if(idptemp>idp-1)
	{
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idptemp,idetemp);
	}
	else
	{
		for (i=0;i<enc[idetemp].numeroprod;i++)									/* Verifica os produtos na encomenda */		
		{
			if(enc[idetemp].prodenc[i].indexprod==idptemp)
			{
				prod[idptemp].qtd+=enc[idetemp].prodenc[i].qtd;					/* Devolve ao stock a quantidade retirada a encomeda */
				enc[idetemp].prodenc[i].qtd=0;									/* Retira o produto da encomenda */
			}
		}
	}
}

/*	Comando 'C',
	Calcula o custo de uma
	dada encomeda. */

void custo_encomenda()
{
	int idetemp,i;
	scanf(" %d",&idetemp);
	if(idetemp>ide-1)
	{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",idetemp);
	}
	else
	{
		enc[idetemp].precoenc=0;
		for (i=0;i<enc[idetemp].numeroprod;i++)
		{
			enc[idetemp].precoenc+=(enc[idetemp].prodenc[i].preco)*(enc[idetemp].prodenc[i].qtd);
		}
		printf("Custo da encomenda %d %d.\n",idetemp,enc[idetemp].precoenc);
	}
}

/*	Comando 'p',
	Modifica o preco de um
	dado produto. */

void altera_preco()
{
	int idptemp,i,j;
	int precotemp;
	scanf(" %d:%d",&idptemp,&precotemp);
	if(idptemp>idp-1)
	{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idptemp);
	}
	else
	{
		for (i=0;i<ide;i++)														/* Verifica todas as encomendas */
		{
			for(j=0;j<enc[i].numeroprod;j++)
			{
				if(enc[i].prodenc[j].indexprod==idptemp)
					enc[i].prodenc[j].preco=precotemp;							/* Altera o preco dos produtos nas encomendas */
			}
		}
		prod[idptemp].preco=precotemp;											/* Altera o preco dos produtos no stock */
	}

}

/*	Comando 'E',
	Apresenta a lista de produtos
	que pertencem a uma dada
	encomenda. */

void lista_produtos_enc()
{
	int idetemp,i,idptemp;
	scanf(" %d:%d",&idetemp,&idptemp);
	if(idetemp>ide-1)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",idetemp);
	}
	else if(idptemp>idp-1)
	{
		printf("Impossivel listar produto %d. Produto inexistente.\n",idptemp);
	}
	else
	{
		for(i=0;i<enc[idetemp].numeroprod;i++)									/* Verifica os produtos na encomenda */
		{
			if(enc[idetemp].prodenc[i].indexprod==idptemp)
			{
				printf("%s %d.\n",enc[idetemp].prodenc[i].dscr,enc[idetemp].prodenc[i].qtd);
				return;
			}

		}
		printf("%s %d.\n",prod[idptemp].dscr,0);
	}
}

/*	Comando 'm',
	Lista a encomenda em que um
	dado produto se encontra em
	maior quantidade. */

void lista_prod_mais_vezes()
{
	int idptemp,i,j,a=0,b=0,max=0;
	scanf(" %d",&idptemp);
	if (idptemp>idp-1)
	{
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idptemp);
	}
	else
	{
		for(i=0;i<ide;i++)
		{
			for(j=0;j<enc[i].numeroprod;j++)									/* Verifica todas as encomendas */
			{
				if(enc[i].prodenc[j].indexprod==idptemp && enc[i].prodenc[j].qtd>max)		/* Verifica qual a encomenda que contem mais unidades do produto */
				{
					max=enc[i].prodenc[j].qtd;									/* Atualiza o maximo de qtd de produto */
					a=i;
					b=j;

				}
			}
		}
		if (max>0)
		{
			printf("Maximo produto %d %d %d.\n",idptemp,a,enc[a].prodenc[b].qtd);
		}
	}
}
/*	Quicksort,
	Usado para ordenar os
	produtos por ordem 
	crescente de preco */

/*	Funcao parition,
	Usada para ordenar as
	particoes */

int partition(int prodord[IDP],int l,int r)
{
	int i= l-1,j=r;
	int aux=prodord[r];
	while(i<j)
	{
		while(prod[prodord[++i]].preco<prod[aux].preco || (prod[prodord[i]].preco==prod[aux].preco && prodord[i]<aux));	/* Compara o preco de dois elementos e os seus indices*/
		while(prod[aux].preco<prod[prodord[--j]].preco || (prod[aux].preco==prod[prodord[j]].preco && aux<prodord[j]))
			if(j==l)
				break;

		if(i<j)
			exch(prodord[i],prodord[j]);										/* Troca os indices dos produtos */
	}
	exch(prodord[i],prodord[r]);												/* Troca os indices dos produtos */
	return i;
}

/*	Funcao quicksort,
	Parte principal do
	quicksort que chama
	a funcao partition */

void quicksort(int prodord[IDP],int l,int r)
{
	int i;

	if(r<=l)
		return;

	i=partition(prodord,l,r);
	quicksort(prodord,l,i-1);
	quicksort(prodord,i+1,r);
}
/*	Comando 'l',
	Lista por ordem crescente de
	preco os produtos do sistema. */

void lista_por_preco()
{
	int i,l=0,n,r=idp-1,prodord[IDP];
	for (i=0;i<idp;i++)
	{
		prodord[i]=i;
	}
	quicksort(prodord,l,r);
	printf("Produtos\n");
	for (n=0;n<idp;n++)
	{
		printf("* %s %d %d\n",prod[prodord[n]].dscr,prod[prodord[n]].preco,prod[prodord[n]].qtd);
	}

}

/*	Comando 'L',
	Lista por ordem alfabetica
	de descricao os produtos
	de uma encomenda. */

void lista_por_ordem_alfa()
{
	int idetemp,j,k,n,min;
	produto temp;
	scanf(" %d",&idetemp);
	if (idetemp>ide-1)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",idetemp);
	}
	else
	{
		for(j=0;j<enc[idetemp].numeroprod-1;j++)								/* Algoritmo de ordenacao com base no Selectionsort */
		{
			min=j;
			for(k=j+1;k<enc[idetemp].numeroprod;k++)							/* Percorre o numero de produtos na encomenda */
			{
				if (strcmp(enc[idetemp].prodenc[min].dscr,enc[idetemp].prodenc[k].dscr)>0)
				{
					min=k;
				}
			}
			temp=enc[idetemp].prodenc[min];										/* Ocorre a troca de elementos */
			enc[idetemp].prodenc[min]=enc[idetemp].prodenc[j];
			enc[idetemp].prodenc[j]=temp;
		}
		printf("Encomenda %d\n",idetemp);
		for (n=0;n<enc[idetemp].numeroprod;n++)
		{
			if (enc[idetemp].prodenc[n].qtd>0)
			{
			printf("* %s %d %d\n",enc[idetemp].prodenc[n].dscr,enc[idetemp].prodenc[n].preco,enc[idetemp].prodenc[n].qtd);
			}
		}
	}
}


int main()
{
	char c;
	for(;;)																		/* Ciclo infinito */
	{
	
		scanf("%c",&c);
		switch(c)
		{
		 	case 'a': adiciona_produto(); break;

		 	case 'q': adiciona_stock(); break;

		    case 'N': cria_encomenda(); break;

		    case 'A': adiciona_produto_a_encomenda(); break;

			case 'r': remove_stock(); break;

			case 'R': remove_produto_a_encomenda(); break;

			case 'C': custo_encomenda(); break;

			case 'p': altera_preco(); break;

			case 'E': lista_produtos_enc(); break;

			case 'm': lista_prod_mais_vezes(); break;

			case 'l': lista_por_preco(); break;

			case 'L': lista_por_ordem_alfa(); break;

			case 'x': return 0; break;											/* Condicao de termino */

			default: break;
		}
    }
 	
 	return 0;
}