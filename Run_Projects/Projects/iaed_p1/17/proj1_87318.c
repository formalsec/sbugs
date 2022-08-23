#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************************
 +         Definicao de constantes globais          +
 ****************************************************/

#define MAX 2048            /* - maximo da string inicial        */
#define MAX_ID 9999         /* - maximo de produtos armazenados  */
#define MAX_STRING 63       /* - maximo para string de descricao */
#define MAX_ENC 499         /* - maximo encomendas 500           */
#define MAX_PESO 200        /* - peso maximo encomenda 200       */

/*********************************************************************************************
 +         Estruturas de organizacao para cada Produto e Encomenda, respetivamente           +
 *********************************************************************************************/

typedef struct produtos
{
	int idp, preco, peso, qtd; 
	char descricao[MAX_STRING];
} produtos;

   /*****************************************/

typedef struct encomendas
{
	int ide, num_prods, prod[MAX_ID], qtds[MAX_ID]; /* organizado por ordem de adicao */
} encomendas;

/********************************************************
 +         Definicao das variaveis estaticas            +
 ********************************************************/

static struct produtos Produto[MAX_ID];      /* restringe numero maximo de produtos                */

static struct encomendas Encomenda[MAX_ENC]; /* restringe numero maximo de encomendas              */

static int n_produtos = -1;                  /* inicializa contagem do numero de produtos em stock */

static int n_encomendas = -1;                /* inicializa contagem do numero de encomendas        */

/****************************************
 +          Funcoes principais          +
 ****************************************/

/*
 + Funcao: Funcao_a (correspondente o "case 'a'" na Funcao Main)
 + Recebe: char argum[] (string inicial 'a descricao:preco:peso:qtd')
 + Retorna: -NADA-; Formato de saida - 'Novo produto <idp>'
 + Objetivo: Adiciona a struct do conjunto de produtos em stock um novo produto com especificoes
 +           de descricao, preco, peso e quantidade. Assume-se que input respeitara tipos
 +           indicados.
 +
 ***********************************************************************************************/

void Funcao_a(char argum[])
{
	const char separador[2] = ":";
	char *var_aux, desc[MAX_STRING];
	int price, weight, qt;

	var_aux = strtok(argum, separador);
	strcpy(desc, var_aux);

	var_aux = strtok(NULL, separador);
	price = atoi(var_aux);

	var_aux = strtok(NULL, separador);
	weight = atoi(var_aux);

	var_aux = strtok(NULL, separador);
	qt = atoi(var_aux);

	n_produtos++;

	Produto[n_produtos].idp = n_produtos;
	strcpy(Produto[n_produtos].descricao, desc);
	Produto[n_produtos].preco = price;
	Produto[n_produtos].peso = weight;
	Produto[n_produtos].qtd = qt;

	printf("Novo produto %d.\n", Produto[n_produtos].idp);
}

/*
 + Funcao: Funcao_q (correspondente o "case 'q'" na Funcao Main)
 + Recebe: char argum[] (string inicial 'q idp:qtd')
 + Retorna: 0 quando adiciona stock; 1 se nao passar a averiguacao;
 +          Formato de saida - NADA (exceto erro)
 + Objetivo: Adiciona a stock a um produto ja existente. Faz averiguacao da existencia do
 +           produto recebido como argumento.
 +
 ***********************************************************************************************/

int Funcao_q(char argum[])
{
	const char separador[2] = ":";
	char *var_aux;
	int id, qt, i;

	var_aux = strtok(argum, separador);
	id = atoi(var_aux);

	var_aux = strtok(NULL, separador);
	qt = atoi(var_aux);

	for(i = 0; i <= n_produtos; i++)
	{
		if(Produto[i].idp == id)
		{
			Produto[i].qtd = Produto[i].qtd + qt;

			return 0;
		}
	}

	printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
	
	return 1;
}

/*
 + Funcao: Funcao_N (correspondente o "case 'N'" na Funcao Main)
 + Recebe: -NADA- (string inicial 'N')
 + Retorna: -NADA-; Formato de saida - 'Nova encomenda <ide>'
 + Objetivo: Cria uma nova encomenda no sistema.
 +
 ***********************************************************************************************/

void Funcao_N()
{
	n_encomendas++;

	Encomenda[n_encomendas].ide = n_encomendas;
	Encomenda[n_encomendas].num_prods = 0;

	printf("Nova encomenda %d.\n", Encomenda[n_encomendas].ide);
}

/*
 + Funcao: Funcao_r (correspondente o "case 'r'" na Funcao Main)
 + Recebe: inteiro 'id' referente a identificacao do produto, inteiro 'qt' referente a quantidade.
 + Retorna: 2 para produto inexistente, 1 para encomenda inexistente, 0 se remover; 
 +          Formato de saida - NADA (exceto erro)
 + Objetivo: remove stock a um produto existente.
 +
 ***********************************************************************************************/

int Funcao_r(int id, int qt)
{
	int i;

	for(i = 0; i <= n_produtos; i++)
	{
		if(Produto[i].idp == id)
		{
			if(Produto[i].qtd >= qt)
			{
				Produto[i].qtd = Produto[i].qtd - qt;

				return 0; 
			}
			else
			{
				printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qt, id);

				return 1;
			}
		}
	}

	printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);

	return 2;
}

/*
 + Funcao: Funcao_A (correspondente o "case 'A'" na Funcao Main)
 + Recebe: char argum[] (string inicial 'A ide:idp:qtd')
 + Retorna: 3 para produto inexistente, 4 para encomenda inexistente, 0 se adicionar,
 +          2 se quantidade em stock for insuficiente, 1 se passar o peso maximo; 
 +          Formato de saida - NADA (exceto erro)
 + Objetivo: Adicona um produto a uma encomenda, averiguando se este ja esta contido nela e em
 +           caso afirmativo adiciona a quantida em questao a quantidade contida.
 +
 ***********************************************************************************************/

int Funcao_A(char argum[])
{
	const char separador[2] = ":";
	char *var_aux;
	int id_e, id_p, qt, i, j, k, l, peso_total = 0;

	var_aux = strtok(argum, separador);
	id_e = atoi(var_aux);

	var_aux = strtok(NULL, separador);
	id_p = atoi(var_aux);

	var_aux = strtok(NULL, separador);
	qt = atoi(var_aux);

	for(i = 0; i <= n_encomendas; i++)
	{
		if(Encomenda[i].ide == id_e && id_e >= 0)
		{
			for(j = 0; j <= n_produtos; j++)
			{
				if(Produto[j].idp == id_p && id_p >= 0)
				{
					if(Encomenda[i].num_prods == 0)
					{
						if(Produto[j].qtd >= qt)
						{
							if((qt * Produto[j].peso) <= MAX_PESO) /* adiciona a encomenda se esta nao tiver produtos */
							{
								Encomenda[i].prod[0] = id_p;
								Encomenda[i].qtds[0] = qt;

								Encomenda[i].num_prods++;

								Funcao_r(id_p, qt); /* retira quantidade colocada na encomenda */

								return 0;
							}
							else
							{
								printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_p, id_e);

								return 1;
							}
						}
						else
						{
							printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_p, id_e);

							return 2;
						}
					}
					else if(Encomenda[i].num_prods > 0)
					{
						for(l = 0; l < Encomenda[i].num_prods; l++)
						{
							peso_total = peso_total + Encomenda[i].qtds[l]*Produto[Encomenda[i].prod[l]].peso;
						}

						for(k = 0; k < Encomenda[i].num_prods; k++)
						{
							if(Encomenda[i].prod[k] == id_p) /* adiciona a encomenda se esta tiver o produto questao */
							{
								if(qt <= Produto[j].qtd)
								{
									if(peso_total + (qt * Produto[j].peso) <= MAX_PESO)
									{

										Encomenda[i].qtds[k] = Encomenda[i].qtds[k] + qt;

										Funcao_r(id_p, qt);

										return 0;
									}
									else
									{
										printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_p, id_e);

										return 1;
									}
								}
								else
								{
									printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_p, id_e);

									return 2;
								}
							}
						}

						if(Produto[j].qtd >= qt) /* adiciona a encomenda se esta tiver produtos mas nao tiver o produto em questao */
						{
							if(peso_total + (qt * Produto[j].peso) <= MAX_PESO)
							{
								Encomenda[i].prod[Encomenda[i].num_prods] = id_p;
								Encomenda[i].qtds[Encomenda[i].num_prods] = qt;

								Encomenda[i].num_prods++;

								Funcao_r(id_p, qt);

								return 0;
							}
							else
							{
								printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_p, id_e);

								return 1;
							}
						}
						else
						{
							printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_p, id_e);

							return 2;
						}						
					}
				}
			}

			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_p, id_e);

			return 3;
		}
	}

	printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_p, id_e);

	return 4;
}

/*
 + Funcao: Funcao_R (correspondente o "case 'R'" na Funcao Main)
 + Recebe: char argum[] (string inicial 'R ide:idp')
 + Retorna: 2 para encomenda inexistente, 1 para produto inexistente, 0 se remover; 
 +          Formato de saida - NADA (exceto erro)
 + Objetivo: remove um produto de uma encomenda.
 +
 ***********************************************************************************************/

int Funcao_R(char argum[])
{
	const char separador[2] = ":";
	char *var_aux;
	int id_e, id_p, i, j, k, posi, qt_prod;

	var_aux = strtok(argum, separador);
	id_e = atoi(var_aux);

	var_aux = strtok(NULL, separador);
	id_p = atoi(var_aux);

	for(i = 0; i <= n_encomendas; i++)
	{
		if(Encomenda[i].ide == id_e)
		{
			for(j = 0; j <= n_produtos; j++)
			{
				if(Produto[j].idp == id_p)
				{
					for(k = 0; k < Encomenda[i].num_prods; k++)
					{
						if(Encomenda[i].prod[k] == id_p)
						{
							qt_prod = Encomenda[i].qtds[k];
							posi = k;
							Encomenda[i].num_prods = Encomenda[i].num_prods - 1;
						}
					}

					for(k = posi; k < Encomenda[i].num_prods; k++)
					{
						Encomenda[i].prod[k] = Encomenda[i].prod[k + 1];
						Encomenda[i].qtds[k] = Encomenda[i].qtds[k + 1];
					}

					Produto[j].qtd = Produto[j].qtd + qt_prod;

					return 0;
				}
			}

			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_p, id_e);

			return 1;				
		}
	}

	printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_p, id_e);

	return 2;
}

/*
 + Funcao: Funcao_C (correspondente o "case 'C'" na Funcao Main)
 + Recebe: char argum[] (string inicial 'c ide')
 + Retorna: 1 para encomenda inexistente, 0 se calcular custo; 
 +          Formato de saida - 'custo da encomenda <ide> <total>.' OU erro
 + Objetivo: calcula o custo total da encomenda.
 +
 ***********************************************************************************************/

int Funcao_C(char argum[])
{
	int id_e, i, j, preco_total = 0;

	id_e = atoi(argum);

	for(i = 0; i <= n_encomendas; i++)
	{
		if(Encomenda[i].ide == id_e)
		{
			for(j = 0; j < Encomenda[i].num_prods; j++)
			{
				preco_total = preco_total + Encomenda[i].qtds[j]*Produto[Encomenda[i].prod[j]].preco;
			}

			printf("Custo da encomenda %d %d.\n", id_e, preco_total);

			return 0;
		}
	}

	printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_e);

	return 1;
}

/*
 + Funcao: Funcao_p (correspondente o "case 'p'" na Funcao Main)
 + Recebe: char argum[] (string inicial 'p idp:preco')
 + Retorna: 1 para produto inexistente, 0 se alterar preco; 
 +          Formato de saida - NADA (exceto erro)
 + Objetivo: altera preco de um produto caso este exista no sistema.
 +
 ***********************************************************************************************/

int Funcao_p(char argum[])
{
	const char separador[2] = ":";
	char *var_aux;
	int id, price, i;

	var_aux = strtok(argum, separador);
	id = atoi(var_aux);

	var_aux = strtok(NULL, separador);
	price = atoi(var_aux);

	for(i = 0; i <= n_produtos; i++)
	{
		if(Produto[i].idp == id)
		{
			Produto[i].preco = price;

			return 0;
		}
	}

	printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);

	return 1;
}

/*
 + Funcao: Funcao_E (correspondente o "case 'E'" na Funcao Main)
 + Recebe: char argum[] (string inicial 'E ide:idp')
 + Retorna: 2 para encomenda inexistente, 1 para produto inexistente, 0 se o produto estiver na encomenda e esta existir; 
 +          Formato de saida - '<desc> <qtd>.' OU erro
 + Objetivo: lista a descricao e a quantidade de um produto numa encomenda.
 +
 ***********************************************************************************************/

int Funcao_E(char argum[])
{
	const char separador[2] = ":";
	char *var_aux;
	int id_e, id_p, i, j, k, qtd = 0;

	var_aux = strtok(argum, separador);
	id_e = atoi(var_aux);

	var_aux = strtok(NULL, separador);
	id_p = atoi(var_aux);

	for(i = 0; i <= n_encomendas; i++)
	{
		if(Encomenda[i].ide == id_e)
		{
			for(j = 0; j <= n_produtos; j++)
			{
				if(Produto[j].idp == id_p)
				{
					for(k = 0; k < Encomenda[i].num_prods; k++)
					{
						if(Encomenda[i].prod[k] == id_p)
						{
							qtd = Encomenda[i].qtds[k]; 
						}
					}

					printf("%s %d.\n", Produto[j].descricao, qtd);

					return 0;
				}
			}

			printf("Impossivel listar produto %d. Produto inexistente.\n", id_p);

			return 1;
		}
	}

	printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_e);

	return 2;
}

/*
 + Funcao: Funcao_m (correspondente o "case 'm'" na Funcao Main)
 + Recebe: char argum[] (string inicial 'm idp')
 + Retorna: 1 para produto inexistente, 0 se o produto exisitir no sistema; 
 +          Formato de saida - 'Maximo produto <idp> <ide> <qtd>.' OU NADA caso nao esteja
 +          em nenhuma encomenda OU erro
 + Objetivo: lista o identificador da encomenda em que o produto dado ocorre mais vezes; se
 +           houver 2 ou mais encomendas nessa situacao, imprime a de menor 'id'.
 +
 ***********************************************************************************************/

int Funcao_m(char argum[])
{
	int id_p, i, j, k, id_e = 0, maior = 0;

	int flag = 0;  /* variaveis de flag/controlo */

	id_p = atoi(argum);

	for(i = 0; i <= n_produtos; i++)
	{
		if(Produto[i].idp == id_p)
		{
			if(n_encomendas < 0)    /* verifica se ha encomendas */
			{
				return 0;
			}
			else
			{
				for(j = 0; j <= n_encomendas; j++)
				{
					for(k = 0; k < Encomenda[j].num_prods; k++)
					{
						if(Encomenda[j].prod[k] == id_p)
						{
							if(Encomenda[j].qtds[k] > maior)
							{
								id_e =j;
								maior = Encomenda[j].qtds[k];

								flag = 1; /* ha produto em pelo menos uma das encomendas */
							}
						}
					}
				}

				if(flag == 1)
				{
					printf("Maximo produto %d %d %d.\n", id_p, id_e, maior);

					return 0;
				}
				else
				{
					return 0;
				}
			}
		}
	}

	printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_p);

	return 1;
}

/*
 + Funcao: Funcao_L (correspondente o "case 'L'" na Funcao Main; INACABADA)
 + Recebe: char argum[] (string inicial 'L ide')
 + Retorna: 1 para encomenda inexistente, 0 se o encomenda exisitir no sistema; 
 +          Formato de saida - INACABADO (apenas imprime a mensagem de erro para tal caso)
 + Objetivo: lista todos os produtos de uma encomenda por ordem alfabetica da descricao.
 +
 ***********************************************************************************************/

int Funcao_L(char argum[])
{
	int id, i;

	id = atoi(argum);

	for(i = 0; i <= n_encomendas; i++)
	{
		if(Encomenda[i].ide == id)
			return 0;
	}

	printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id);

	return 1;
}

/********************************
 +          Funcao Main         +
 ********************************/

/*
 + -> Funcao Main contem apenas 2 variaveis declaradas (c, que refere qual o case do switch;
 + argum[MAX] que ira conter a string toda obtida do input); utilizacao da operacao 'getchar'
 + para obter o char 'c' que ditara cada case do switch, seguido de um 'getchar()' vazio
 + propositado para retirar o espaco entre a operacao e as instrucoes da operacao; obtencao
 + da restante string a partir de 'fgets'; cada case depende da primeira instrucao dada na
 + string do input inicial; operacao 'x' termina o programa com sucesso; caso o input seja
 + invalido, termina o programa apresentado um output de erro correspondente: para o caso 'r'
 + realiza automaticamente na Main a separacao da string para facilitar o uso desta funcao noutra
 + funcao (Funcao_A), declarando variaveis 'separador' que delimita o separador de cada argumento,
 + ponteiro 'var_aux' que auxilia no uso da funcao embutida 'strtok', inteiros 'id' e 'qt' que
 + serao passados em argumento para a funcao propriamente dita.
 +
 ***********************************************************************************************/

int main()
{
	char c, argum[MAX];

	while((c = getchar()) != EOF)
	{
		getchar();

		switch(c)
		{
			case 'a':
			{
				fgets(argum, MAX, stdin);

				Funcao_a(argum);

				break;
			}
			case 'q':
			{
				fgets(argum, MAX, stdin);

				Funcao_q(argum);

				break;
			}
			case 'N':
			{
				Funcao_N();

				break;
			}
			case 'A':
			{
				fgets(argum, MAX, stdin);

				Funcao_A(argum);

				break;
			}
			case 'r':
			{
				const char separador[2] = ":";
				char *var_aux;
				int id, qt;

				fgets(argum, MAX, stdin);

				var_aux = strtok(argum, separador);
				id = atoi(var_aux);

				var_aux = strtok(NULL, separador);
				qt = atoi(var_aux);

				Funcao_r(id, qt);

				break;
			}
			case 'R':
			{
				fgets(argum, MAX, stdin);

				Funcao_R(argum);

				break;
			}
			case 'C':
			{
				fgets(argum, MAX, stdin);

				Funcao_C(argum);

				break;	
			}
			case 'p':
			{
				fgets(argum, MAX, stdin);

				Funcao_p(argum);

				break;
			}
			case 'E':
			{
				fgets(argum, MAX, stdin);

				Funcao_E(argum);

				break;
			}
			case 'm':
			{
				fgets(argum, MAX, stdin);

				Funcao_m(argum);

				break;
			}
			case 'L':
			{
				fgets(argum, MAX, stdin);

				Funcao_L(argum);

				break;
			}
			case 'x':
			{
				return EXIT_SUCCESS;
			}
			default:
			{
				fprintf(stderr, "Erro: operacao invalida!\n");

				return EXIT_FAILURE;
			}
		}
	}

	return 0;
}