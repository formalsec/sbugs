#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include<string.h>
/*Inicializacoes
Estrutura de produtos que guarda os seus nomes, precos, pesos, quantidades e indices de cada uns */
struct produto
	{
		char nome[63];
		int preco;
		int peso;
		int qtd;
		int idp;
	};

/*Estrutura de encomendas que guarda o preco e o peso total da encomenda, tambem como a quantidade de cada produto na encomenda*/
struct encomenda
{
	int idp[10000]; /*idp[10] = 11 produto de indice 10 tem 11 de quantidade*/
	int peso;
	int preco;
};
struct encomenda encomendas[500]; /* Lista de estruturas onde se guardam as encomendas*/
int aux[10000]; /*Lista auxiliar para indices ordenados*/

/*Funcoes Auxiliares*/

void inicia_produtos(struct produto identificadores[10000])
{
	int i;
	/*Inicializar proodutos a zeros*/
	for(i = 0; i < 10000; i++)
	{
		identificadores[i].nome[0] = '+'; 
		identificadores[i].preco = 0;
		identificadores[i].peso = 0;
		identificadores[i].qtd = 0;
		identificadores[i].idp = i;
	}
}

void adiciona_prod(char nome[63], int preco, int peso,int qtd,struct produto identificadores[10000],int id_incr)
{
	struct produto prod;

	strcpy(prod.nome, nome);
	prod.idp = id_incr;
	prod.preco = preco;
	prod.peso = peso;
	prod.qtd = qtd;
	identificadores[id_incr] = prod;
}

void cria_encomenda(int n_encom, struct encomenda encomendas[500])
{
	struct encomenda enc;
	int i = 0;
	/*Inicializar encomenda a zeros*/
	while(i < 10000)
	{
		enc.idp[i] = 0;
		i++;
	}
	enc.peso = 0;
	enc.preco = 0;
	encomendas[n_encom] = enc;
}

void remove_stock(int idp, int qtd, struct produto identificadores[10000])
{
	identificadores[idp].qtd -= qtd;
}

void adiciona_a_encomenda(int ide, int idp, int qtd, struct produto identificadores[])
{
	encomendas[ide].idp[idp] += qtd;
	encomendas[ide].peso += identificadores[idp].peso * qtd;
	encomendas[ide].preco += identificadores[idp].preco * qtd;
	remove_stock(idp, qtd, identificadores);
}

void adiciona_stock(int idp, int qtd, struct produto identificadores[10000])
{
	identificadores[idp].qtd += qtd;
}

void remove_de_encomenda(int ide, int idp, struct produto identificadores[])
{
	adiciona_stock(idp, encomendas[ide].idp[idp], identificadores);
	encomendas[ide].preco -= identificadores[idp].preco * encomendas[ide].idp[idp];
	encomendas[ide].peso -= identificadores[idp].peso * encomendas[ide].idp[idp];
	encomendas[ide].idp[idp] = 0;
}

void corre_encomenda(int idp, struct encomenda encomendas[500])
{
	int e = 0;
	int max_ocur = 0, max_ide = 0;
	
	while(e < 500)
	{
		/*Quatidade de produto idp na encomenda e for maior que o maximo ate entao*/
		if(encomendas[e].idp[idp] > max_ocur)
		{
			max_ocur = encomendas[e].idp[idp];
			max_ide = e;
		}
		e++;
	}
		if(max_ocur > 0)
		printf("Maximo produto %d %d %d.\n", idp, max_ide, max_ocur);
}

void atualiza_preco(int idp, int preco, struct produto identificadores[], struct encomenda encomendas[], int n_encom)
{
	int preco_antigo, e = 0;
	preco_antigo = identificadores[idp].preco;
	identificadores[idp].preco = preco;

	/*Verificar se esse produto se encontra nalguma encomenda e substituir o preco*/
	while(e < n_encom)
	{
		if(encomendas[e].idp[idp] > 0)
		{
			encomendas[e].preco -= preco_antigo * encomendas[e].idp[idp];
			encomendas[e].preco += preco * encomendas[e].idp[idp];
		}
		e++;
	}
}

void merge_aux(struct produto identificadores[], int left, int m, int right)
{
	int i, j, k;
	
	for (i = m+1; i >left; i--) /*Encher a primeira metade do aux com identificadores*/
		aux[i-1] = identificadores[i-1].idp;
	for(j = m; j < right; j++)  /*Encher a segunda metade do aux com identificadores*/
		aux[right+m-j] = identificadores[j+1].idp;
	for(k = left; k <= right; k++) /*Ordena os identificadores que estavam em aux por ordem de preco*/
	{
		if(identificadores[aux[j]].preco < identificadores[aux[i]].preco ||
		 (identificadores[aux[j]].preco == identificadores[aux[i]].preco && 
		 	aux[j] < aux[i]))
			identificadores[k].idp = aux[j--]; 
		else
			identificadores[k].idp = aux[i++];
	}
}

/*Funcao recursiva que realiza o merge sort, divindo a lista que lhe e dada e ordenando pela ordem de precos*/
void merge_sort(struct produto identificadores[], int left, int right)
{
	int m;
	
	if(left < right)
	{
		m = left+(right-left)/2;
		merge_sort(identificadores, left, m);
		merge_sort(identificadores, m+1, right);
		merge_aux(identificadores, left, m, right);
	}
}

void sort_preco(struct produto identificadores[])
{
	struct produto idaux[10000];
	int i = 0, j = 0;
	/*Inicializa uma lista auxiliar a zeros*/
	for(i = 0; i < 10000;i++)
	{
		aux[i] = 0;
	}
	i = 0;
	printf("Produtos\n");
	while(i < 10000 && identificadores[i].qtd >= 0 && identificadores[i].nome[0] != '+')
	{
		strcpy(idaux[i].nome, identificadores[i].nome);
		idaux[i].qtd = identificadores[i].qtd;
		idaux[i].preco = identificadores[i].preco;
		idaux[i].idp = identificadores[i].idp;
		i++;
	}
	merge_sort(idaux, 0, i-1);
	while(j < i)
	{
		if(identificadores[idaux[j].idp].qtd >= 0)
		{
			printf("* %s %d %d\n", identificadores[idaux[j].idp].nome, identificadores[idaux[j].idp].preco, identificadores[idaux[j].idp].qtd);
		}
		j++;
	}
}

void merge_aux_2(struct produto identificadores[], int left, int m, int right)
{
	int i, j, k;
	
	for (i = m+1; i >left;i--)
		aux[i-1] =identificadores[i-1].idp;
	for(j = m; j < right; j++)
		aux[right+m-j] = identificadores[j+1].idp;
	for(k = left; k <= right; k++) /*Ordena os identificadores que estavam em aux por ordem alfabetica*/
	{
		if(strcmp(identificadores[aux[j]].nome, identificadores[aux[i]].nome) < 0 ||
		  (strcmp(identificadores[aux[j]].nome, identificadores[aux[i]].nome) == 0 && 
		  aux[j] < aux[i]))
			identificadores[k].idp = aux[j--];
		else
			identificadores[k].idp = aux[i++];
	}
	
}
/*Funcao recursiva que realiza o merge sort, divindo a lista que lhe e dada e ordenando pela ordem alfabetica*/
void merge_sort_2(struct produto identificadores[], int left, int right)
{
	int m;
	if(left < right)
	{
		m = left+(right-left)/2;
		merge_sort_2(identificadores, left, m);
		merge_sort_2(identificadores, m+1, right);
		merge_aux_2(identificadores, left, m, right);
	}
}

void sorte_nome(struct produto identificadores[], int ide)
{
	struct produto idaux[10000];
	int i = 0, j;
	for(i = 0; i < 10000;i++)
	{
		aux[i] = 0;
	}

	i = 0;
		while(i < 10000 && identificadores[i].nome[0] != '+')
	{
		strcpy(idaux[i].nome, identificadores[i].nome);
		idaux[i].qtd = encomendas[ide].idp[i];
		idaux[i].preco = encomendas[ide].preco;
		idaux[i].idp = identificadores[i].idp;
		i++;
	}
	merge_sort_2(idaux, 0, i-1);
	printf("Encomenda %d\n", ide);
	for(j = 0; j < i; j++)
	{
		if(encomendas[ide].idp[idaux[j].idp] > 0)
		{
			printf("* %s %d %d\n", identificadores[idaux[j].idp].nome, identificadores[idaux[j].idp].preco, encomendas[ide].idp[idaux[j].idp]);
		}
	}	
}

/*Funcao principal*/

int main()
{
	int preco, peso, qtd, id_incr = 0, idp, n_encom = 0, ide;
	char c, nome[63];
	struct produto identificadores[10000]; /*Lista de estruturas onde se guardam os produtos*/
	inicia_produtos(identificadores);
	while((c=getchar()) != EOF)
	{
		switch(c)
		{
			case 'a':
				c = getchar();
				scanf("%[^:]:%d:%d:%d",nome, &preco, &peso, &qtd);
				adiciona_prod(nome,preco,peso,qtd,identificadores,id_incr);
				printf("Novo produto %d.\n", id_incr);
				id_incr++;
				break;

			case 'q':
				scanf("%d:%d", &idp, &qtd);
				if(idp >= id_incr)
				{
					printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
				}
				else
					adiciona_stock(idp, qtd, identificadores);
				break;

			case 'N':
				cria_encomenda(n_encom, encomendas);
				printf("Nova encomenda %d.\n", n_encom);
				n_encom++;
				break;

			case 'A':
				scanf("%d:%d:%d", &ide, &idp, &qtd);
				if(ide >= n_encom){
					printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
				}
				else if(idp >= id_incr)
				{
					printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
				}
				else if (identificadores[idp].qtd < qtd)
				{
					printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide );
				}
				else if(ide >= n_encom){
					printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
				}
				else if(identificadores[idp].peso * qtd + encomendas[ide].peso > 200)
				{
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
				}
				else{
					adiciona_a_encomenda(ide, idp, qtd, identificadores);
				}
				break;

			case 'r':
				scanf("%d:%d", &idp, &qtd);
				if(idp >= id_incr)
				{
					printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
				}
				else if(identificadores[idp].qtd - qtd < 0)
				{
					printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
				}
				else 
					remove_stock(idp, qtd, identificadores);
				break;

			case 'R':
				scanf("%d:%d", &ide, &idp);
				if(ide >= n_encom){
					printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
				}
				else if(idp >= id_incr)
				{
					printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
				}
				else
				{
					remove_de_encomenda(ide, idp, identificadores);
				}
				break;

			case 'C':
				scanf("%d", &ide);
				if(ide >= n_encom)
				{
					printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
				}
				else 
					printf("Custo da encomenda %d %d.\n",ide, encomendas[ide].preco);
				break;

			case 'p':
				scanf("%d:%d", &idp, &preco);
				if(idp >= id_incr)
				{
					printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
				}
				else
				{
					atualiza_preco(idp,preco,identificadores,encomendas,n_encom);
				}
				break;

			case 'E':
				scanf("%d:%d", &ide, &idp);
				if(ide >= n_encom)
				{
					printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
				}
				else if(idp >= id_incr)
				{
					printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
				}
				else
					printf("%s %d.\n",identificadores[idp].nome, encomendas[ide].idp[idp]);
				break;

			case 'm':
				scanf("%d", &idp);
				if(idp >= id_incr)
				{
					printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
				}
				else
					corre_encomenda(idp,encomendas);
				break;

			case 'l':
				sort_preco(identificadores);
				break;

			case 'L':
				scanf("%d", &ide);
				if(ide >= n_encom)
				{
					printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
				}
				else
					sorte_nome(identificadores, ide);
				break;

			case 'x':
				break;


		}
	}
	return 0;
}
