#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Valor maximo de produtos guardados. */
#define MAX_PRODUTOS 10000
/* Valor maximo de encomendas guardadas. */
#define MAX_ENCOMENDAS 500
/* Valor maximo de produtos numa encomenda. */
#define MAX_PRODUTOS_ENCOMENDA 200
/* Tamanho maximo de uma string. */
#define DES_MAX 63


/* 
 *	Estrutura de produtos 
 *  idp identificador
 *  des descricao
 *  preco preco
 *  qtd quantidade
*/
struct produtos
{
	int idp;
	char des[DES_MAX];
	int preco;
	int peso;
	int qtd;
};

/* 
 *	Estrutura de encomendas 
 *  ide identificador
 *  peso peso (somat?rio da quantidade a multiplicar pelo peso dos produtos)
 *  cpe contador de produtos na encomenda
 *  preco preco (somat?rio da quantidade a multiplicar pelo precp dos produtos)
 *  listagem array de uma estrutura de produtos
*/
struct encomendas
{
	int ide;
	int peso;
	int cpe;
	int preco;
	struct produtos listagem[MAX_PRODUTOS_ENCOMENDA];
};

/*
 * i Variavel para guardar o getchar.
 * cide cidp Contador de encomendas e contador de produtos respetivamente.
*/
int i, cide = 0, cidp = 0;
/* Array de encomendas. */
struct encomendas encomenda[MAX_ENCOMENDAS];
/* Array de produtos. */
struct produtos produto[MAX_PRODUTOS];
/* 
 * Array de produtos utilizado para fazer 
 * uma copia para o print de produtos ordenados por preco.
*/
struct produtos auxproduto[MAX_PRODUTOS];
/* Arrays auxiliares para o merge sort. */
struct produtos aux[MAX_PRODUTOS];
struct encomendas aux2[MAX_ENCOMENDAS];


/* Funcoes para merge sort tal como lecionado nas aulas. */
void mergep(struct produtos a[], int left, int m, int right)
{ 
  	int i, j, k;
  	for (i = m+1; i > left; i--) 
    	aux[i-1] = a[i-1];
  	for (j = m; j < right; j++)
    	aux[right+m-j] = a[j+1];
  	for (k = left; k <= right; k++)
    	if (aux[j].preco < aux[i].preco || i > m)
      		a[k] = aux[j--];
    	else
      		a[k] = aux[i++];
}

void mergesortp(struct produtos a[], int left, int right)
{
	int m = (right+left)/2;

	if(right <= left)
		return;

  	mergesortp(a, left, m);
  	mergesortp(a, m+1, right);
  	mergep(a, left, m, right);
}

void merges(struct encomendas a[], int id, int left, int m, int right)
{ 
    int i, j, k;
  	for (i = m+1; i > left; i--)
    	aux2[id].listagem[i-1] = a[id].listagem[i-1];
    for (j = m; j < right; j++)
      	aux2[id].listagem[right+m-j] = a[id].listagem[j+1];
    for (k = left; k <= right; k++)
    	if (strcmp(aux2[id].listagem[j].des, aux2[id].listagem[i].des) < 0  || i > m)
        	a[id].listagem[k] = aux2[id].listagem[j--];
      	else
        	a[id].listagem[k] = aux2[id].listagem[i++];
}

void mergesorts(struct encomendas a[], int id, int left, int right)
{
  	int m = (right+left)/2;

  	if(right <= left)
    	return;

  	mergesorts(a, id, left, m);
 	mergesorts(a, id, m+1, right);
  	merges(a, id, left, m, right);
}


/* 
 * Funcao criaProduto.
 * Cria um produto com ID igual ao contador de IDs.
 * Obtem e guarda inputs do comando na estrutura de dados.
 */
void criaProduto()
{
	scanf(" %[^:]:%d:%d:%d", produto[cidp].des, &produto[cidp].preco, &produto[cidp].peso, &produto[cidp].qtd);
	produto[cidp].idp = cidp; 
	printf("Novo produto %d.\n", produto[cidp].idp);
	cidp++;
}

/* 
 * Funcao adicionaQuantidade.
 * Adiciona quantidade a um produto na estrutura
 * se passar em todas as verificacoes.
*/
void adiconaQuantidade()
{
    int idpt;
    int addqtd;
    scanf("%d:%d", &idpt, &addqtd);
    if(idpt < cidp)
    	produto[idpt].qtd += addqtd;
    else
    	printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idpt);
}

/* 
 * Funcao criaEncomenda.
 * Inicializa os parametros de uma nova encomenda
 * na posicao do contador de encomendas.
*/
void criaEncomenda()
{
	encomenda[cide].ide = 0;
    encomenda[cide].peso = 0;
    encomenda[cide].cpe = 0;
    encomenda[cide].preco = 0;
    printf("Nova encomenda %d.\n", cide);
    cide++;
}

/* 
 * Funcao adicionaProdutoEncomenda().
 * Adiciona um produto a uma encomenda se
 * passar todas as verificacoes.
*/
void adicionaProdutoEncomenda()
{
    int j;
    /* 
	 * idet Identificador de encomenda onde adicionar.
	 * idpt Identificador de produto a adicionar.
	 * qtdt Quantidade de produto a adicionar.
    */
    int idet;
    int idpt;
    int qtdt;
    /* modo 
     * Se o modo continuar igual a 0, significa que nao houve
	 * erro ou que o produto nao existe em stock.
    */
    int modo = 0;
    scanf("%d:%d:%d", &idet, &idpt, &qtdt);
    if(idet < cide)
    {
    	if(idpt < cidp)
        {
        	/* Verifica se ha stock. */
        	if((produto[idpt].qtd - qtdt) >= 0)
        	{
        		/* for que percorre os produtos. */
            	for(j = 0;j < encomenda[idet].cpe;j++)
            	{
            		/* Verifica se ja ha esse produto na encomenda. */
            		if(encomenda[idet].listagem[j].idp == idpt)
            		{
            			/* Verifica se o peso esta dentro dos limites. */
            			if(((encomenda[idet].peso + (qtdt * encomenda[idet].listagem[j].peso)) > MAX_PRODUTOS_ENCOMENDA))
            			{
                			modo = 1;
                			printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idpt, idet);
                			break;
                		}
                		/* Se nao der erro adicona a quantidade na encomenda
						 * no produto ja existente dentro da mesma, remove do stock
						 * e adiciona ao peso.
                		*/
                		else
                		{
                			encomenda[idet].listagem[j].qtd += qtdt;
                  			produto[idpt].qtd -= qtdt;
         	         		encomenda[idet].peso += (qtdt * produto[idpt].peso);
            	      		modo = 1;
                	  		break;
                		}
              		}
            	}

            	if(modo == 0)
            	{
            		/* Se o peso ultrapassar os 200 da erro, 
            		 * caso contrario adiciona novo produto na encomenda.
            		*/
             		if((encomenda[idet].peso + (qtdt * produto[idpt].peso)) > MAX_PRODUTOS_ENCOMENDA)
                		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idpt, idet);
              		/* Se nao der erro cria um novo produto na encomenda,
					 * remove do stock, aumenta o contador de produtos 
					 * na encomenda e aumenta o peso.
                	*/
              		else
              		{
                		encomenda[idet].listagem[encomenda[idet].cpe] = produto[idpt];
           			    encomenda[idet].listagem[encomenda[idet].cpe].qtd = qtdt;
                		encomenda[idet].peso += (qtdt * produto[idpt].peso);
	                	encomenda[idet].cpe++;
    	            	produto[idpt].qtd -= qtdt;
         	    	}
            	}
        	}
        	else
          		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idpt, idet);
    	}
       	else
       		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idpt, idet);
    }
    else
    	printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idpt, idet);
}


/*
 * Funcao removeQuantidade.
 * Remove quantidade do stock se passar
 * todas as verificacoes.
*/
void removeQuantidade()
{
	/*
	 * idpt ID do produto a remover quantidade.
	 * rqtd Quantidade a remover.
	*/
	int idpt;
    int rqtd;
    scanf("%d:%d", &idpt, &rqtd);
    if(idpt < cidp)
    {	
    	if((produto[idpt].qtd - rqtd) >= 0)
        	produto[idpt].qtd -= rqtd;
        else
        	printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", rqtd, idpt);
    }
    else
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idpt);
}


/*
 * Funcao removeProdutoEncomenda.
 * Remove um produto de uma encomenda se
 * a funcao passar todas as verificacoes.
*/
void removeProdutoEncomenda()
{
	/*
	 * Se o modo for 0 ainda nao encontrou esse produto na encomenda.
	 * Se o modo for 1 o ciclo puxa os produtos na encomenda uma casa para tras.
	 * Se o modo for 1 e a iteracao do ciclo for a ultima
	 * diminui o contador de produtos na encomenda
	 * de maneira a ocultar o mesmo em ciclos futuros. 
	*/
    int modo = 0;
    int j;
    /*
	 * idet Identificador da encomenda onde deve ser removido o produto.
	 * idpt Identificador do produto a remover. 
    */
    int idet;
    int idpt;
    scanf("%d:%d", &idet, &idpt);
    /* Verifica se a encomenda com esse ID ja foi criada. */
    if(idet < cide)
    {
    	/* Verifica se o produto com esse ID ja foi criado. */
    	if(idpt < cidp)
        {
        	for(j = 0;j < encomenda[idet].cpe;j++)
          	{
            	if(modo == 0 && encomenda[idet].listagem[j].idp == idpt)
            	{
              		produto[idpt].qtd += encomenda[idet].listagem[j].qtd;
              		encomenda[idet].peso -= (encomenda[idet].listagem[j].qtd * encomenda[idet].listagem[j].peso);
              		modo = 1;
            	}
            	else if (modo == 1)
              		encomenda[idet].listagem[j-1] = encomenda[idet].listagem[j];
            	if (modo == 1 && encomenda[idet].cpe == j + 1)
              		encomenda[idet].cpe--;
          	}
        }
        else
        	printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idpt, idet);
    }
    else
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idpt, idet);
}

/*
 * Funcao listaProdutoPreco.
 * Imprime os produtos ordenados por
 * ordem crescente de peso.
*/
void listaProdutoPreco()
{
	int j;
	/* Cria uma copia dos produtos de maneira
	 * a nao alterar a ordem inicial.
	*/
    for (j=0; j < cidp; j++)
        auxproduto[j] = produto[j];
    /* Organiza a copia (cidp -1 como right pois as posicoes
	 * sao sempre cidp-1.
    */
    mergesortp(auxproduto, 0, cidp-1);
    printf("Produtos\n");
    for(j = 0; j < cidp ; j++)
    	printf("* %s %d %d\n", auxproduto[j].des, auxproduto[j].preco, auxproduto[j].qtd);
}

/*
 * Funcao listaDescricaoQuantidade.
 * Lista a descricao e a quantidade
 * de um X produto escolhido pelo user
 * numa Y encomenda escolhida pelo user.
*/
void listaDescricaoQuantidade()
{
	int j;
	/*
	 * idet Identificador da encomenda onde se procura o produto.
	 * idpt Identificador do produto a listar. 
    */
    int idet;
    int idpt;
    /*
	 * Se o modo continuar igual a 0 nao foi encontrado o produto na encomenda
	 * e lista a descricao e a quantidade na encomenda que eh 0.
    */
    int modo = 0;
    scanf("%d:%d", &idet, &idpt);
    /* Verifica se o ID da encomenda existe. */
    if(idet < cide)
    {
    	/* Verifica se o ID do produto existe. */
        if(idpt < cidp)
        {
        	/* Procura pelo ID na lista dos produtos da encomenda*/
        	for(j = 0;j < encomenda[idet].cpe;j++)
        	{
        		if(encomenda[idet].listagem[j].idp == idpt)
            	{
              		printf("%s %d.\n", encomenda[idet].listagem[j].des, encomenda[idet].listagem[j].qtd);
              		modo = 1;
              		break;
            	}
          	}
          	if (modo == 0)
            	printf("%s 0.\n", produto[idpt].des);
        }
        else
        	printf("Impossivel listar produto %d. Produto inexistente.\n", idpt);
    }
    else
    	printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idet);
}

/*
 * Funcao alteraPreco.
 * Altera o preco de um produto no
 * array dos produtos.
*/
void alteraPreco()
{
	/*
	 * precot Novo preco do produto.
	 * idpt ID do produto a alterar o preco. 
	*/
	int precot;
    int idpt;
    scanf("%d:%d", &idpt, &precot);
    /* Verifica se o ID do produto existe. */
    if(idpt < cidp)
    	produto[idpt].preco = precot;
    else
    	printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idpt);
}

/*
 * Funcao encomendaMaiorQuantidade.
 * Lista a encomenda com a maior quantidade
 * de um denominado produto a escolher pelo user.
*/
void encomendaMaiorQuantidade()
{
	int j;
    int k;
    /* 
	 * idpt ID do produto a procurar.
	 * idep Variavel que guarda o ID da encomenda com maior quantidade.
	 * max Variavel que guarda o valor maximo.
    */
    int idpt;
    int idep;
    int max;
    /*
	 * Se o modo for igual a 0 e for encontrado o produto numa encomenda
	 * eh definido o maximo e guarda o ID da encomenda.
	 * Se o modo for igual a 1 quer dizer que ja ocorreu esse produto em
	 * pelo menos uma encomenda e a partir dai compara o maximo com a quantidade
	 * na encomenda atual e guarda os novos valores se a qtd > max.  
    */
    int modo = 0;
    scanf("%d", &idpt);
    /* Verifica se o ID do produto existe. */
    if(idpt < cidp)
    {
    	/* Percorre todas as encomendas. */
    	for(j=0;j < cide;j++)
       	{
       		/* Percorre os produtos numa encomenda j. */
        	for(k=0;k < encomenda[j].cpe;k++)
          	{
            	if(encomenda[j].listagem[k].idp == idpt && modo == 0)
            	{
              		max = encomenda[j].listagem[k].qtd; 
              		idep = j;
              		modo = 1;
              		break;
            	}
            	else if(encomenda[j].listagem[k].idp == idpt && modo == 1 && encomenda[j].listagem[k].qtd > max)
            	{
              		max = encomenda[j].listagem[k].qtd;
              		idep = j; 
              		break;
            	}
          	}
        }
        /* Se encontrou pelo menos um produto, imprime. */
        if (modo == 1)
          printf("Maximo produto %d %d %d.\n", idpt, idep, max);  
      }
      else
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idpt);
}

/*
 * Funcao ordenaEncomendaDescricao.
 * Organiza os produtos numa encomenda pela
 * ordem alfabetica da descricao dos produtos na encomenda.
*/
void ordenaEncomendaDescricao()
{
	int j;
	/* Encomenda a ordenar. */
    int idet;
    scanf("%d", &idet);
    /* Organiza a encomenda por ordem alfabetica
     * da descricao dos produtos na encomenda.
     * encomenda[idet].cpe-1 pois os IDs sao sempre
     * menos um que o contador.
    */
    mergesorts(encomenda, idet, 0, encomenda[idet].cpe-1);
    /* Verifica se existe o ID da encomenda. */
    if(idet < cide)
   	{
    	printf("Encomenda %d\n", idet);
    	for(j = 0; j < encomenda[idet].cpe; j++)
    		printf("* %s %d %d\n", encomenda[idet].listagem[j].des, produto[encomenda[idet].listagem[j].idp].preco, encomenda[idet].listagem[j].qtd);
	}
	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idet);
}


/*
 * calculaPreco.
 * Calcula o preco de uma encomenda.
*/
void calculaPreco()
{
	int j;
	/* ID da encomenda cujo preco se quer calcular. */
    int idet;
    scanf("%d", &idet);
    /* Verifica se existe encomenda. */
    if(idet < cide)
    {
    	/* Apaga o preco anterior. */
    	encomenda[idet].preco = 0;
    	/* Percorre todos os produtos dentro da encomenda
		 * e vai adicionando o custa da quantidade de um x
		 * produto na encomenda.
    	*/
        for(j = 0;j < encomenda[idet].cpe;j++)
        	encomenda[idet].preco += (encomenda[idet].listagem[j].qtd * produto[encomenda[idet].listagem[j].idp].preco);
        printf("Custo da encomenda %d %d.\n", idet, encomenda[idet].preco);
    }
    else
    	printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idet);
}

/* 
 * Funcao main.
 * Le os comandos do user input
 * que sao introduzidos num switch
 * que executa os respetivos casos escolhidos.
 */
int main()
{
	while((i=getchar())!=EOF && i != 'x')
	{
		switch(i)
		{
			case ('a'):
			criaProduto();
			break;

			case ('q'):
     		adiconaQuantidade();
    		break;

    		case ('N'):
    		criaEncomenda();
    		break;

    		case ('A'):
    		adicionaProdutoEncomenda();
    		break;

    		case ('r'):
    		removeQuantidade();
    		break;

    		case ('R'):
    		removeProdutoEncomenda();
    		break;

    		case ('C'):
    		calculaPreco();
    		break;

    		case ('p'):
    		alteraPreco();
    		break;

    		case ('E'):
    		listaDescricaoQuantidade();
    		break;

    		case('m'):
    		encomendaMaiorQuantidade();
    		break;

    		case ('l'):
    		listaProdutoPreco();
    		break;

    		case ('L'):
    		ordenaEncomendaDescricao();
    		break;
		}
	}
	return 0;
}