#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

             /* constantes */

#define MAX 63                /* numero maximo de carateres para descricao recebido na funcao */  
#define MAX_PRODUTOS 10000    /* numero maximo de produtos que o sistema recebe */
#define MAX_ENCOMENDAS 500    /* numero maximo de encomendas que o sistema recebe */
#define MAX_PESO 200          /* numero maximo de peso que cada encomenda aguenta */
#define MAX_PRODUTOS_ENCOMENDA 200   /* numero maximo de produtos de uma encomenda */
#define MAX_CARACTERISTICAS 4        /* numero maximo de caracteristicas que e dado num input */
#define MAX_INFO_ENCOMENDA 2         /* numero maximo de informcao guardada numa tabela dentro da estrutura da encomenda */

/*estrutura para os produtos*/
typedef struct produto
{
	int identificacao_produto;
	char NOME_PRODUTO[MAX];
	int preco;
	int peso;
	int qtd;
}produto;

/*estrutura para as encomendas*/
typedef struct encomenda
{
	int identificacao_encomenda;
	int peso_encomenda;
	int info_encomenda[MAX_PESO][MAX_INFO_ENCOMENDA];  /* dentro fo max_info_encomenda estara guardado o indice e a quantidade do produto nessa encomenda*/
}encomenda;

produto STOCK_LOJA[MAX_PRODUTOS];
encomenda ENCOMENDAS[MAX_ENCOMENDAS];

/*******************   FUNOCES AUXILIARES   *******************/

/**** Funcao que le e guarda cada linha do input ate encontrar um '\n' ****/
int LerLinha(char LINHA[])
{
	char c;
	int i = 0;
	while ((c = getchar()) != '\n')
	{
		LINHA[i] = c; /*enquanto nao encontrar '\n' mete o caracter na tabela LINHA*/
		i++;
	}
	LINHA[i] = '\0';
	return 0;
}
/**** Funcao que separa, a cada ':', as informacoes de cada linha introduziada e guarda as no vetor armazem_dados ****/ 
int SepararDados(char LINHA[], char ARMAZEM_DADOS[][MAX])
{
	int i,p=0,a=0, b = 0;
	for (i = 0; i < MAX_CARACTERISTICAS; i++)
	{
		strncpy(ARMAZEM_DADOS[i], "", MAX); /*a cada indice do vetor armazem dados introduz 63 "" que e o maximo de caracteres que sao permitidos por caracteristica do produto*/
	}
	while(LINHA[p] != '\0')
	{
		if(LINHA[p] == ':')
		{
			ARMAZEM_DADOS[a][b] = '\0';  /*ao encontrar os ':' muda de indice para ser guardada a proxima informacao toda*/
			b = 0;
			a++;
		}
		else
		{
			ARMAZEM_DADOS[a][b] = LINHA[p]; /*caso nao encontre os ':' continua a guardar os caracteres no mesmo indice a*/
			b++;
		}
		p++;
	}
	return a;
}

/*Funcao merge para o comando L que ira ordenar alfabeticamente os produtos*/
void merge_L(int tabelaF[], int baixo, int cima, int mid, int encomenda)
{
	int k, i, j, tabela_aux[MAX_PRODUTOS];
	for(i = mid + 1; i > baixo; i--)    /* contrucao do vetor auxiliar*/
		tabela_aux[i -1] = tabelaF[i-1];
	for(j = mid; j < cima; j++)   /* contrucao do vetor auxiliar*/
		tabela_aux[cima + mid - j] = tabelaF[j +1];
	for(k =baixo; k <= cima; k++)
	{
		if(strcmp(STOCK_LOJA[ENCOMENDAS[encomenda].info_encomenda[tabela_aux[j]][0]].NOME_PRODUTO,
			STOCK_LOJA[ENCOMENDAS[encomenda].info_encomenda[tabela_aux[i]][0]].NOME_PRODUTO) < 0) /*compara as strings para as ordenar por ordem alfabetica*/
			tabelaF[k] = tabela_aux[j--];                                                         /* e introduz o respetivo indice por ordem na tabela final*/
		else
			tabelaF[k] = tabela_aux[i++];
	}
}

/*Funcao merge para o comando l que ira ordenar em relacao a numeros inteiros que neste caso sao os precos dos produtos*/
void merge_l(int tabelaF[], int baixo, int cima, int mid)
{
	int k, i, j, tabela_aux[MAX_PRODUTOS];
	for(i = mid + 1; i > baixo; i--) /* contrucao do vetor auxiliar*/
		tabela_aux[i -1] = tabelaF[i-1];
	for(j = mid; j < cima; j++)  /* contrucao do vetor auxiliar*/
		tabela_aux[cima + mid - j] = tabelaF[j +1];
	for(k =baixo; k <= cima; k++)
	{
		if((STOCK_LOJA[tabela_aux[j]].preco < STOCK_LOJA[tabela_aux[i]].preco))  /*aqui comeca a ser feita a comparacao dos precos e a respetiva ordena?ao na tabela final*/
			tabelaF[k] = tabela_aux[j--];
		else if (STOCK_LOJA[tabela_aux[j]].preco == STOCK_LOJA[tabela_aux[i]].preco && 
			STOCK_LOJA[tabela_aux[j]].identificacao_produto < STOCK_LOJA[tabela_aux[i]].identificacao_produto) /*comparacao feita no caso dos precos serem iguais mas*/
		{                                                                                                      /*os idndices diferentes*/
			tabelaF[k] = tabela_aux[j--];
		}
		else
			tabelaF[k] = tabela_aux[i++];
	}
}

/*funcao que inicia a ordenao tanto alfabetica como por ordem de precos*/
void merge_sort(int baixo, int cima, int tabelaF[], int string, int encomenda)
{
	int mid = ((cima + baixo) / 2); 

	if(cima <= baixo) /*condicao que nos indica quando temos vetores apenas com um valor*/
	{
		return;
	}

	merge_sort(baixo, mid, tabelaF,string,encomenda);   /* Partir sucessivamente o vetor dado ao meio ate que fiquemos apenas com vetores que contem apenas um elemento*/
	merge_sort(mid + 1, cima, tabelaF, string,encomenda);
	if(string)
		merge_L(tabelaF, baixo, cima, mid, encomenda); /*aqui distingue-se se estamos a fazer a funcao 'l' ou 'L'*/
	else
		merge_l(tabelaF, baixo, cima, mid);
}

/*******************  FUNCOES PRINCIPAIS   *****************/
/*Esta funcao adiciona um novo produto a encomenda*/
void adiciona_produto()
{
	int i,p = 0;
	char LINHA[MAX], ARMAZEM_DADOS[MAX_CARACTERISTICAS][MAX];
	getchar();/* usado para retirar o espaco depois de letra do comando */
	LerLinha(LINHA);
	SepararDados(LINHA, ARMAZEM_DADOS);
	for (i = 0; i < MAX_PRODUTOS; i++)
	{
		if(STOCK_LOJA[i].identificacao_produto != -1) /* procura um indice 'vazio' para o atribuir a identificaao do produto*/
			p++;
		else{
			break;
		}
	}
	STOCK_LOJA[p].identificacao_produto = p;
	strcpy(STOCK_LOJA[p].NOME_PRODUTO, ARMAZEM_DADOS[0]);
	STOCK_LOJA[p].preco = atoi(ARMAZEM_DADOS[1]);          /* guarda os dados nos respetivos sitios */
	STOCK_LOJA[p].peso = atoi(ARMAZEM_DADOS[2]);
	STOCK_LOJA[p].qtd = atoi(ARMAZEM_DADOS[3]);
	printf("Novo produto %d.\n",p);
}

/*Funcao que adiciona stock a um determinado produto*/
void adiciona_stock()
{
	char LINHA[MAX], ARMAZEM_DADOS[MAX_CARACTERISTICAS][MAX];
	getchar();
	LerLinha(LINHA);
	SepararDados(LINHA, ARMAZEM_DADOS);
	if (STOCK_LOJA[atoi(ARMAZEM_DADOS[0])].identificacao_produto != -1) /*verificacao da existencia do produto*/
	{
		STOCK_LOJA[atoi(ARMAZEM_DADOS[0])].qtd += atoi(ARMAZEM_DADOS[1]); /*stock e aqui adicionado*/
	}
	else
	{
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", atoi(ARMAZEM_DADOS[0]));
	}
}

/*Nesta funcao ira ser criada uma nova encomenda*/
void cria_encomenda()
{
	int i, p = 0;
	for (i = 0; i < MAX_ENCOMENDAS; i++)
	{
		if(ENCOMENDAS[i].identificacao_encomenda != -1) /* procura um indice 'vazio' para o atribuir a identificaao da encomenda*/
			p++;
	}
	ENCOMENDAS[p].identificacao_encomenda = p;
	printf("Nova encomenda %d.\n", p);
}

/*Nesta funcao e adicionado um produto a encomenda*/
void adiciona_encomenda()
{
	int i, permissao;
	char LINHA[MAX], ARMAZEM_DADOS[MAX_CARACTERISTICAS][MAX];
	getchar();
	LerLinha(LINHA);
	SepararDados(LINHA, ARMAZEM_DADOS);
	permissao = 1;
	if (ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].identificacao_encomenda != -1)/*verificacao da existencia da encomenda*/
	{
		if (STOCK_LOJA[atoi(ARMAZEM_DADOS[1])].identificacao_produto != -1) 
		{
			if(STOCK_LOJA[atoi(ARMAZEM_DADOS[1])].qtd >= atoi(ARMAZEM_DADOS[2]))  /* verifica se existe existe stock suficiente para adicionar o produto a encomenda */
			{
				ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].peso_encomenda += atoi(ARMAZEM_DADOS[2]) * STOCK_LOJA[atoi(ARMAZEM_DADOS[1])].peso;   /*calculo do peso total*/
				if(ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].peso_encomenda > MAX_PESO)
				{
					ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].peso_encomenda -= atoi(ARMAZEM_DADOS[2]) * STOCK_LOJA[atoi(ARMAZEM_DADOS[1])].peso;   /* retirar agora o que foi adicionado pois e invalido o peso atual*/
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",atoi(ARMAZEM_DADOS[1]),atoi(ARMAZEM_DADOS[0])); 
				}
				else /* encomenda nao ultrupassa o peso 200*/
				{
					STOCK_LOJA[atoi(ARMAZEM_DADOS[1])].qtd -= atoi(ARMAZEM_DADOS[2]);
					for (i = 0; i < MAX_PESO; ++i)
					{
						if (ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][0] == atoi(ARMAZEM_DADOS[1]))  /* o produto ja se encontra na encomenda */
						{
							ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][1] += atoi(ARMAZEM_DADOS[2]);
							i = MAX_PESO;
							permissao = 0;
						}
					}
					if(permissao) /* o produto ainda nao se encontra na encomenda */
					{
						for (i = 0; i < MAX_PESO; ++i)
						{
							if (ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][0] == -1) 
							{
								ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][0] = atoi(ARMAZEM_DADOS[1]); /* guardar a idt do produto */
								ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][1] = atoi(ARMAZEM_DADOS[2]); /* guardar a qtd do produto */
								break;
							}
						}
					}
				}
			}
			else
			{
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",atoi(ARMAZEM_DADOS[1]),atoi(ARMAZEM_DADOS[0])); 
			}
		}
		else
		{
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",atoi(ARMAZEM_DADOS[1]),atoi(ARMAZEM_DADOS[0])); 
		}   
	}
	else{
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",atoi(ARMAZEM_DADOS[1]),atoi(ARMAZEM_DADOS[0])); 
	}
}

/*Esta funcao remove stock a um produto do stock da loja*/
void remove_stock()
{
	char LINHA[MAX], ARMAZEM_DADOS[MAX_CARACTERISTICAS][MAX];
	getchar();
	LerLinha(LINHA);
	SepararDados(LINHA, ARMAZEM_DADOS);
	if (STOCK_LOJA[atoi(ARMAZEM_DADOS[0])].identificacao_produto != -1)   /* verificacao da existencia do produto */
	{
		if(STOCK_LOJA[atoi(ARMAZEM_DADOS[0])].qtd - atoi(ARMAZEM_DADOS[1])  >= 0)   /* verificar se ao retiramos menos ou tanta quantidade que a existente*/
		{
			STOCK_LOJA[atoi(ARMAZEM_DADOS[0])].qtd -= atoi(ARMAZEM_DADOS[1]);   
		}
		else
		{
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",atoi(ARMAZEM_DADOS[1]), atoi(ARMAZEM_DADOS[0]));
		}
	}
	else
	{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", atoi(ARMAZEM_DADOS[0]));
	}
}

/*Funcao que ira remover um determinado produto a certa encomenda*/
void remove_produto_encomenda()
{
	int i;
	char LINHA[MAX], ARMAZEM_DADOS[MAX_CARACTERISTICAS][MAX];
	getchar();
	LerLinha(LINHA);
	SepararDados(LINHA, ARMAZEM_DADOS);
	if (ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].identificacao_encomenda != -1)
	{
		if (STOCK_LOJA[atoi(ARMAZEM_DADOS[1])].identificacao_produto != -1)
		{
			for (i = 0; i < MAX_PESO; i++)
			{
				if (ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][0] == atoi(ARMAZEM_DADOS[1])) /* encontrar o indice do prduto que se quer remover*/
				{
					ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].peso_encomenda -= STOCK_LOJA[atoi(ARMAZEM_DADOS[1])].peso * ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][1]; /* retirar o peso ao peso total da encomenda*/
					STOCK_LOJA[atoi(ARMAZEM_DADOS[1])].qtd += ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][1]; /*repor no stock a qtd retirada a encomenda */
					ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][1] = 0; /* o peso desse produto na encomenda e posto a 0 pois o produto foi retirado*/
					break;
				}
			}
		}
		else
		{
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", atoi(ARMAZEM_DADOS[1]),atoi(ARMAZEM_DADOS[0])) ;
		}	
	}
	else
	{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", atoi(ARMAZEM_DADOS[1]),atoi(ARMAZEM_DADOS[0]));
	}
}

/*Funcao que calcula o custa da encomenda pedida*/
void calcula_custa_encomenda()
{
	int i, preco = 0;
	char LINHA[MAX], ARMAZEM_DADOS[MAX_CARACTERISTICAS][MAX];
	getchar();
	LerLinha(LINHA);
	SepararDados(LINHA, ARMAZEM_DADOS);
	if (ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].identificacao_encomenda == atoi(ARMAZEM_DADOS[0]))
	{
		for (i = 0; i < MAX_PESO; i++)
		{
			if (ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][0] != -1)
			{
				preco += STOCK_LOJA[ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][0]].preco * ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][1]; /*conta que calcula o custo*/
			}
		}
		printf("Custo da encomenda %d %d.\n", atoi(ARMAZEM_DADOS[0]), preco);
	}
	else
	{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", atoi(ARMAZEM_DADOS[0]));
	}
}

/*Nesta funcao ira ser alterado o preco do produto pretendido*/
void altera_preco()
{
	char LINHA[MAX], ARMAZEM_DADOS[MAX_CARACTERISTICAS][MAX];
	getchar();
	LerLinha(LINHA);
	SepararDados(LINHA, ARMAZEM_DADOS);
	if (STOCK_LOJA[atoi(ARMAZEM_DADOS[0])].identificacao_produto != -1) 
	{
		STOCK_LOJA[atoi(ARMAZEM_DADOS[0])].preco = atoi(ARMAZEM_DADOS[1]); /* o preco e alterado aqui substituindo o valor antigo pelo novo*/
	}
	else
	{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",atoi(ARMAZEM_DADOS[0]));
	}
}

/*Funcao que lista a descricao e a quantidade de um produto na encomenda*/
void lista_descricao_qtd()
{
	int i, ativo = 0;
	char LINHA[MAX], ARMAZEM_DADOS[MAX_CARACTERISTICAS][MAX];
	getchar();
	LerLinha(LINHA);
	SepararDados(LINHA, ARMAZEM_DADOS);
	if (ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].identificacao_encomenda != -1) 
	{
		if (STOCK_LOJA[atoi(ARMAZEM_DADOS[1])].identificacao_produto != -1)  
		{
			for (i = 0; i < MAX_PESO; i++)
			{
				if(ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][0] == atoi(ARMAZEM_DADOS[1]))/*encontrar, dentro da encomenda dada, o indice do porduto que se quer listar*/
				{
					ativo = 1; 
					break;
				}
			}
			if (ativo) /* usado para saber que o produto ja se enctra na encomenda e a quantidade nao e zero */
				printf("%s %d.\n", STOCK_LOJA[atoi(ARMAZEM_DADOS[1])].NOME_PRODUTO,ENCOMENDAS[atoi(ARMAZEM_DADOS[0])].info_encomenda[i][1]);
			else
				printf("%s %d.\n", STOCK_LOJA[atoi(ARMAZEM_DADOS[1])].NOME_PRODUTO, 0);
		}
		else
		{
			printf("Impossivel listar produto %d. Produto inexistente.\n",atoi(ARMAZEM_DADOS[1]));
		}
	}
	else
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",atoi(ARMAZEM_DADOS[0]));
	}
}

/*Funcao que indica a encomenda onde o produto se encontra em maior quantidade*/
void maior_qtd_encomenda()
{
	int i,p,contagem = 0, guarda_encomenda = 0, autorizacao = 1;
	char LINHA[MAX], ARMAZEM_DADOS[MAX_CARACTERISTICAS][MAX];
	getchar();
	LerLinha(LINHA);
	SepararDados(LINHA, ARMAZEM_DADOS);
	if (STOCK_LOJA[atoi(ARMAZEM_DADOS[0])].identificacao_produto != -1)
	{
		for (i = 0; i < MAX_ENCOMENDAS; i++)
		{
			for(p = 0; p < MAX_PESO; p++)
			{
				if (ENCOMENDAS[i].info_encomenda[p][0] != -1 && ENCOMENDAS[i].info_encomenda[p][0] == atoi(ARMAZEM_DADOS[0]))
				{
					if (ENCOMENDAS[i].info_encomenda[p][1] > contagem){     
						contagem = ENCOMENDAS[i].info_encomenda[p][1]; /*se a nova quantidade na encomenda for maior que na encomenda anterior */
						guarda_encomenda = i;                          /*fica guardado, na variabel guarda_encomenda o indice dessa mesma encomenda*/
					}
				}
			}
		}
		if(ENCOMENDAS[0].identificacao_encomenda == -1 || contagem == 0) /* verifica se nao existe esse produto em nenhuma encomenda ou se a sua quantidade e zero*/
			autorizacao = 0;
		if(autorizacao)
			printf("Maximo produto %d %d %d.\n",atoi(ARMAZEM_DADOS[0]),guarda_encomenda,contagem);
	}
	else
	{
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",atoi(ARMAZEM_DADOS[0]));
	}
}

/*Funcao que ordena os produtos do sistema por ordem crescente de preco*/
void produtos_ordenados_preco()
{
	int i, tabelaF[MAX_PRODUTOS],conta = 0, cima, baixo = 0;
	for (i = 0; i < MAX_PRODUTOS; i++)
	{
		if (STOCK_LOJA[i].identificacao_produto != -1)
		{
			conta++;  /* numero de produtos existentes no sistema*/
		}
		else
			break;
	}
	cima = conta;
	for (i = 0; i < cima; i++)
		tabelaF[i] = STOCK_LOJA[i].identificacao_produto; /*passar os indices para uma tabela que ira ser usada no merge_sort*/
	merge_sort(baixo,cima - 1,tabelaF,0,0); /*o valor 0 indica que vamos comparar precos que sao numeros inteiros e nao strings(na funcao L toma o valor 1)*/
	printf("Produtos\n");
	for (i = 0; i < conta ; i++)
	{
		printf("* %s %d %d\n", STOCK_LOJA[tabelaF[i]].NOME_PRODUTO, STOCK_LOJA[tabelaF[i]].preco, STOCK_LOJA[tabelaF[i]].qtd);
	}
}

/*Funcao que cria uma lista com os produtos de uma encomenda ordenados por ordem alfabetica*/
void lista_produtos_encomenda()
{
	int i,conta = 0, baixo = 0, cima = 0, tabelaF[MAX_PRODUTOS], encomenda;
	char LINHA[MAX_CARACTERISTICAS];
	getchar();
	LerLinha(LINHA);
	encomenda = atoi(LINHA);
	if (ENCOMENDAS[atoi(LINHA)].identificacao_encomenda != -1)
	{
		for (i = 0; i < MAX_PESO; ++i)
		{
			if (ENCOMENDAS[atoi(LINHA)].info_encomenda[i][0] != -1) 
			{
				tabelaF[cima] = i; /* passa esses indices para uma tabela que vai ser usada no merge_sort*/
				cima++;
				conta++; /* conta os produtos existentes nessa encomenda*/
			}
			else
				break;
		}
		merge_sort(baixo,cima - 1,tabelaF,1, encomenda);/*variavel encomenda toma o valor da encomenda que se pretende listar com os produtos ordenados alfabeticamente*/
		printf("Encomenda %d\n",encomenda);
		for (i = 0; i < conta; i++)
			if (ENCOMENDAS[encomenda].info_encomenda[tabelaF[i]][1] > 0) /* aqui so entram os produtos cuja quantidade seja superior a zero para poder ser feito o seu print*/
				printf("* %s %d %d\n", STOCK_LOJA[ENCOMENDAS[encomenda].info_encomenda[tabelaF[i]][0]].NOME_PRODUTO, 
					STOCK_LOJA[ENCOMENDAS[encomenda].info_encomenda[tabelaF[i]][0]].preco,
					ENCOMENDAS[encomenda].info_encomenda[tabelaF[i]][1]);
	}
	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(LINHA));

}

int main()
{
	int i,p,c,continua=1;
	/* inicia todos os produtos a -1 para saber que nao tenho produtos no sotck */
	for (i = 0; i < MAX_PRODUTOS; i++)
	{
		STOCK_LOJA[i].identificacao_produto = -1;
	}

   /*inicia o peso de todas as encomendas a 0 e inicia todas as encomendas a -1 para saber as que estao 'ativas' */
	for (i = 0; i < MAX_ENCOMENDAS; i++)
	{
		ENCOMENDAS[i].peso_encomenda = 0;
		ENCOMENDAS[i].identificacao_encomenda = -1;
	}

	/* inicia os produtos e a qtd dos menos na encomenda a 0 para ver facil de gravar as informacoes */
	for(i=0; i < MAX_ENCOMENDAS; i++)
	{
		for(p = 0; p < MAX_PESO; p++)
		{
			ENCOMENDAS[i].info_encomenda[p][0] = -1;		
		}
	}
	/* Procura e ecolhe a funcao dependendo da primeira letra de cada linha*/
	while(continua) /* ao encontrar o comando 'x' o continua passa a valer 0 e nao entra no ciclo*/
	{
		switch(c = getchar()) /*aqui e decidido, dependendo da primeira letra do input, para que funcao o programa ira*/
		{
			case 'a':
				adiciona_produto();
				break;
			case 'q':
				adiciona_stock();
				break;
			case 'N':
				cria_encomenda();
				break;
			case 'A':
				adiciona_encomenda();
				break;
			case 'r':
				remove_stock();
				break;
			case 'R':
				remove_produto_encomenda();
				break;
			case 'C':
				calcula_custa_encomenda();
				break;
			case 'p':
				altera_preco();
				break;
			case 'E':
				lista_descricao_qtd();
				break;
			case 'm':
				maior_qtd_encomenda();
				break;
			case 'l':
				produtos_ordenados_preco();
				break;
			case 'L':
				lista_produtos_encomenda();
				break;
			case 'x':
				continua = 0;
		}
	}
	return 0; /*fim do programa*/
}