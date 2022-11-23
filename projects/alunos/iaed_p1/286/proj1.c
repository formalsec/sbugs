#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_IDENTIFICADOR 10000	 				/* O maximo de produtos diferentes. */
#define MAX_DESCRICAO 64						/* O maximo de caracteres que a descricao podera ter (+ \0). */
#define MAX_ENCOMENDAS 500						/* O maximo de encomendas. */
#define MAX_PESO 200 							/* O peso maximo que uma encomenda suporta. */



/* Definicao da estrutura produto. */
typedef struct 
{
	int identificador;
	char descricao[MAX_DESCRICAO];
	int preco;
	int peso;
	int quant;

} produto;

/* Definicao da estrutura encomenda, onde cada encomenda tem uma array de produtos. */
typedef struct 
{
	int peso;
	int ide;
	int numerop;
	produto lista_produtos[MAX_IDENTIFICADOR];
	
} encomenda;



											/* VARIAVEIS GLOBAIS */

											/* Variavel i corresponde ao identificador dos produtos. */	
int i=0, e=0;								/* Variavel e corresponde ao identificador das encomendas. */
produto sistema[MAX_IDENTIFICADOR];			/* Array de produtos - sistema que guarda todos os produtos e informacoes em stock. */
encomenda lista_encomendas[MAX_ENCOMENDAS]; /* Array de encomendas - a lista de todas as encomendas criadas. */



/* Cria um produto atribuindo-lhe um id e recebendo uma descricao, preco, peso e quantidade. *  
 * Todas as informacoes sao guardadas no sistema. 											 */
/* (Comando a) */	
void adicionaProduto()
{
	if (i <= MAX_IDENTIFICADOR)
	{
		sistema[i].identificador = i;

		scanf("%[^:]:%d:%d:%d", sistema[i].descricao, &sistema[i].preco, &sistema[i].peso, &sistema[i].quant);

		printf("Novo produto %d.\n", i);
	}
}

/* Adiciona quantidade ao produto (idp) ja existente no sistema. Se o produto nao tiver sido criado, gera erro. */
/* (Comando q) */	
void adicionaStock()
{
	int idp, add_qtd;

	scanf("%d:%d", &idp, &add_qtd);

	if (strcmp(sistema[idp].descricao,"") == 0)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp); 

	sistema[idp].quant += add_qtd;
}

/* Cria uma encomenda atribuindo-lhe um id unico. */
/* (Comando N) */
void criaEncomenda()
{
	lista_encomendas[e].ide = e;
	lista_encomendas[e].numerop = 0; /* Encomendas novas comecam com 0 produtos. A variavel numerop faz a contagem dos produtos. */
	printf("Nova encomenda %d.\n", e);
}


/* Adiciona o produto (idtp) 'a encomenda (idte). Se o produto ja' existir na encomenda, adiciona a nova quantidade 'a quantidade existente */
/* (Comando A) */
void adiciona_pEncomenda()
{
	int idte, idtp, in_qtd, n;	

	scanf("%d:%d:%d", &idte, &idtp, &in_qtd);


	if (idte >= e)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idtp, idte);
		return;
	}
	if (strcmp(sistema[idtp].descricao , "") == 0)
	{	
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idtp, idte);
		return;
	}
	if (sistema[idtp].quant < in_qtd)
	{	
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idtp, idte);
		return;
	}

	if (lista_encomendas[idte].peso + (sistema[idtp].peso * in_qtd) > MAX_PESO) 
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idtp, idte);
		return;
	}

	sistema[idtp].quant -= in_qtd; 								/* A quantidade inserida na encomenda e' retirada do sistema. */
	lista_encomendas[idte].peso += sistema[idtp].peso * in_qtd;	/* A introducao de (mais) produto e proporcional com o aumento do peso. */
	for (n=0; n < lista_encomendas[idte].numerop; n++)
		if (lista_encomendas[idte].lista_produtos[n].identificador == idtp)
		{
			lista_encomendas[idte].lista_produtos[n].quant += in_qtd;
			return;
		} 
	n = lista_encomendas[idte].numerop;		/* Como o produto nao esta na encomenda, atribui os parametros a posicao seguinte da lista de produtos. */
	strcpy(lista_encomendas[idte].lista_produtos[n].descricao,sistema[idtp].descricao);
	lista_encomendas[idte].lista_produtos[n].identificador = idtp;
	lista_encomendas[idte].lista_produtos[n].quant = in_qtd; 
	lista_encomendas[idte].numerop += 1;

}

/* Remove stock ao produto existente (idp) e com quantidade suficiente. */
/* (Comando r) */
void removeStock()
{
	int idp, remove_qtd;

	scanf("%d:%d", &idp, &remove_qtd);

	if(strcmp(sistema[idp].descricao,"")==0)
	{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
		return;
	}
	if(sistema[idp].quant < remove_qtd )
	{
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", remove_qtd, idp);
		return;
	}
	sistema[idp].quant -= remove_qtd;	
}

/* Remove o produto (idtp) de uma encomenda (idte). */
/* (Comando R) */
void remove_pEncomenda()
{
	int idte, idtp, n;

	scanf("%d:%d", &idte, &idtp);

	if(idte >= e)
	{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idtp, idte);
		return;
	}
	if(strcmp(sistema[idtp].descricao,"")==0)
	{
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idtp, idte);
		return;
	}
	for (n=0; n < lista_encomendas[idte].numerop; n++)
		if(lista_encomendas[idte].lista_produtos[n].identificador == idtp)
		{	
			/* Com remocao de produto a encomenda perde peso e o sistema recebe a quantidade anteriormente retirada. */
			lista_encomendas[idte].peso -= (lista_encomendas[idte].lista_produtos[n].quant * sistema[idtp].peso); 
			sistema[idtp].quant += lista_encomendas[idte].lista_produtos[n].quant;
			lista_encomendas[idte].lista_produtos[n].quant = 0;
			return;
		}
}

/* Calcula o custo da encomenda (idte). */
/* (Comando C) */
void custoEncomenda()
{
	int idte, contador, preco_total=0;

	scanf("%d", &idte);

	if(idte >= e)
	{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idte);
		return;
	}
	for (contador=0; contador < lista_encomendas[idte].numerop; contador++)
		preco_total += (sistema[lista_encomendas[idte].lista_produtos[contador].identificador].preco * lista_encomendas[idte].lista_produtos[contador].quant);
	printf("Custo da encomenda %d %d.\n", idte, preco_total);
}

/* Altera o preco do produto (idtp) existente no sistema.*/
/* (Comando p) */
void alteraPreco()
{
	int idtp, novo_preco;

	scanf("%d:%d", &idtp, &novo_preco);
	if (idtp >= i)
	{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idtp);
		return;
	}
	sistema[idtp].preco = novo_preco;
}

/* Lista a descricao e a quantidade do produto (idtp) na encomenda (idte). */
/* (Comando E) */
void lista_DescriQtd()
{
	int idte, idtp, n;

	scanf("%d:%d", &idte, &idtp);
	if(idte >= e)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idte);
		return;
	}
	if(idtp >= i)
	{
		printf("Impossivel listar produto %d. Produto inexistente.\n", idtp);
		return;
	}
	for (n=0; n < lista_encomendas[idte].numerop; n++) 	/* Utiliza a descricao do produto para encontrar o indice (n) na encomenda.*/
		if (strcmp(lista_encomendas[idte].lista_produtos[n].descricao, sistema[idtp].descricao)==0)
		{
			printf("%s %d.\n", sistema[idtp].descricao, lista_encomendas[idte].lista_produtos[n].quant);
			return;
		}
	printf("%s 0.\n", sistema[idtp].descricao);        /* Caso nao esteja na encomenda lista quantidade 0. */
}

/* Lista o identificador da encomenda em que o produto (idtp) ocorre mais vezes. 		   *
 * Se houver 2 ou mais encomendas nessa situacao, devera imprimir a encomenda de menor id. */
/* (Comando m) */
void listaMaxProduto()
{
	int idtp, n, p, maximo_p = -1, encomenda_n;
	scanf("%d", &idtp);

	if(idtp>=i)
	{
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idtp);
		return;
	}
	for (n=0; n < e; n++)
	{
		for (p=0; p < lista_encomendas[n].numerop; p++)
		{
			if(lista_encomendas[n].lista_produtos[p].identificador == idtp)
			{		/* A quantidade tera que ser maior que 0 e maior que o maximo_p (que guarda a quantidade maxima ate ali encontrada) */
				if (lista_encomendas[n].peso != 0 && maximo_p < lista_encomendas[n].lista_produtos[p].quant && lista_encomendas[n].lista_produtos[p].quant > 0)
				{
					maximo_p = lista_encomendas[n].lista_produtos[p].quant;
					encomenda_n = n;
				}
			}
		}
	}
	if (maximo_p < 1)    /* Se o maximo nao for maior que 0 significa que nao esta em nenhuma encomenda. */
		return;
	else 
		printf("Maximo produto %d %d %d.\n", idtp, encomenda_n, maximo_p);

}

/* Algoritmo de ordenacao merge.                                                                     *
 * l corresponde ao inicio, m 'a metade da lista e r ao final.                                       *
 * Separa a lista_crescente em duas sub-listas -> lista_crescente[l...m] e lista_crescente[m+1...r]  *
 * Ordena-a por ordem crescente do preco de cada produto.                                            */
void merge(produto lista_crescente[], int l, int m, int r) 
{ 
	int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* Listas temporarias E[l...m] | D[m+1...r] */
    produto E[MAX_IDENTIFICADOR], D[MAX_IDENTIFICADOR]; 
  
    /* Copia os produtos para as listas de produtos temporarias */
    for (i = 0; i < n1; i++) 
        E[i] = lista_crescente[l + i]; 
    for (j = 0; j < n2; j++) 
        D[j] = lista_crescente[m + 1+ j]; 
  
    
    i = 0;
    j = 0; 
    k = l;
    /* Compara cada posicao pelo preco e volta a juntar as sub-listas. */
    while (i < n1 && j < n2) 
    { 
        if (E[i].preco <= D[j].preco) 
        { 
            lista_crescente[k] = E[i]; 
            i++; 
        } 
        else
        { 
            lista_crescente[k] = D[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Se ainda existir produtos na sub-lista E adiciona-os. */
    while (i < n1) 
    { 
        lista_crescente[k] = E[i]; 
        i++; 
        k++; 
    } 
  
    /* Se ainda existir produtos na sub-lista D adiciona-os. */
    while (j < n2) 
    { 
        lista_crescente[k] = D[j]; 
        j++; 
        k++; 
    } 
} 
 
/* Parte sucessivamente ao meio a lista de produtos ate obter listas com apenas um produto.                             *
 * Aplica sucessivamente o procedimento de Merge, para ordenar a lista de produtos a partir de dois produtos ordenados. */
void mergeSort(produto lista_crescente[], int l, int r) 
{ 
    if (l < r)     /* Verifica se a lista ainda tem varios produtos */
    { 
        int m = l+(r-l)/2; 
     
    	/* Parte em duas sub-listas a lista_crescente */
        mergeSort(lista_crescente, l, m); 
        mergeSort(lista_crescente, m+1, r); 
  
        merge(lista_crescente, l, m, r); 
    } 
} 



/* Lista todos os produtos existentes no sistema por ordem crescente de preco.                      *
 * Se houver 2 ou mais produtos com o mesmo preco, e' impresso por ordem crescente de id de produto. */
/* (Comando l) */
void listaPcrescente()
{
	int n;
	produto lista_crescente[MAX_IDENTIFICADOR];

	printf("Produtos\n");
	if (i > 0)
	{
		/* lista_crescente e' uma copia do sistema utilizada para fazer as alteracoes sem mudar as posicoes no sistema. */
		memcpy(&lista_crescente, &sistema, sizeof(sistema));
		mergeSort(lista_crescente, 0, i-1);
		for(n=0; n < i; n++)
			printf("* %s %d %d\n", lista_crescente[n].descricao, lista_crescente[n].preco, lista_crescente[n].quant);
	}
}

			
/* Lista todos os produtos da encomenda (idte) por ordem alfabetica da descricao relativamente a tabela ASCII. *
 * E' utilizado um algoritmo (quick sort) para a ordenacao.                                                    */
/* (Comando L) */
void lista_alfabeticamente()
{
	int idte, n, u, j, numero_produtos;

	/* Variaveis utilizadas para guardar os valores durante a execucao da funcao. */
	char encomenda_ordenada_abc[MAX_IDENTIFICADOR][MAX_DESCRICAO], guarda_descricao[MAX_DESCRICAO];
	int encomenda_ordenada_id[MAX_IDENTIFICADOR], guarda_id;
	

	scanf("%d", &idte);
	if (idte >= e)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idte);
		return;
	}
	numero_produtos = lista_encomendas[idte].numerop;
	
	/* Guarda os ids e as descricoes para ordenar alfabeticamente e nao perder os ids correspondentes. */ 
	for (u=0; u < numero_produtos; u++)
		{
			strcpy(encomenda_ordenada_abc[u], lista_encomendas[idte].lista_produtos[u].descricao);
			encomenda_ordenada_id[u] = lista_encomendas[idte].lista_produtos[u].identificador;
		}


	for(n=0; n< numero_produtos - 1; n++)
	{
    	for(j=n+1; j< numero_produtos;j++)
    	{
        	if(strcmp(encomenda_ordenada_abc[n], encomenda_ordenada_abc[j])>0)
        	{
        		/* Sempre que altera a lista das descricoes, faz o mesmo com a lista de ids. */
	            strcpy(guarda_descricao, encomenda_ordenada_abc[n]);	
	            guarda_id = encomenda_ordenada_id[n];
	            strcpy(encomenda_ordenada_abc[n], encomenda_ordenada_abc[j]);
	            encomenda_ordenada_id[n] = encomenda_ordenada_id[j];
	            strcpy(encomenda_ordenada_abc[j], guarda_descricao);
	            encomenda_ordenada_id[j] = guarda_id;
        	}
    	}
	}
	printf("Encomenda %d\n", idte);
    u=0;
	for (u=0; u < numero_produtos; u++)
	{
		for(j=0; j < numero_produtos; j++)
			/* Verifica se esta na encomenda (quantidade superior a 0) e qual a sua posicao na lista de produtos. */
			if(encomenda_ordenada_id[u] == lista_encomendas[idte].lista_produtos[j].identificador && lista_encomendas[idte].lista_produtos[j].quant > 0)
			{
				printf("* %s %d %d\n", encomenda_ordenada_abc[u], sistema[encomenda_ordenada_id[u]].preco, lista_encomendas[idte].lista_produtos[j].quant);
			}
	}

}


/* Le um caracter (comando) do stdin e executa cada funcao a ele designada. */
/* Acaba o programa se o comando 'x' for inserido.                          */

int main()
{
	char comando=' ';
	
	while (comando != EOF && comando != 'x')
	{ 	
		scanf("%c", &comando);
		switch(comando)
		{
			case 'a':
				getchar();
				adicionaProduto();
				i++;
				break;

			case 'q':
				getchar();
				adicionaStock();
				break;

			case 'N':
				criaEncomenda();	
				e++;
				break;

			case 'A':
				getchar();
				adiciona_pEncomenda();
				break;

			case 'r':
				getchar();
				removeStock();
				break;

			case 'R':
				getchar();
				remove_pEncomenda();
				break;

			case 'C':
				getchar();
				custoEncomenda();
				break;

			case 'p':
				getchar();
				alteraPreco();
				break;

			case 'E':
				getchar();
				lista_DescriQtd();
				break;

			case 'm':
				getchar();
				listaMaxProduto();
				break;

			case 'l':
				getchar();
				listaPcrescente();
				break;

			case 'L':
				getchar();
				lista_alfabeticamente();
				break;
		}
	}	
	return 0;
}