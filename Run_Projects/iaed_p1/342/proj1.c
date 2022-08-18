#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*############################# Constantes: #############################*/

#define MAX_IDP 10000
#define MAX_IDE 500
#define MAX_DESC 63
#define MAX_PESO_ENC 200

/*############################# Esrtuturas: #############################*/

/*Estrutura usada por cada produto.*/
typedef struct
{
	int idp;
	char desc[MAX_DESC];
	int preco_prdt;
	int peso_prdt;
	int qtd_stock;
	int qtd_enc[MAX_IDE]; /*Esta componente guarda as quantidades de um produto num array cujos indices equivalem aos ide's das encomendas.*/
} prdt;

/*Estrutura usada por cada encomenda.*/
typedef struct
{
	int ide;
	int nxt_prdt;
	int peso_enc;
	int produtos[MAX_PESO_ENC]; /*Esta componente guarda os idp's correspondentes aos produtos existentes na encomenda em causa.*/
} enc;

/*############################# Vari?veis globais: #############################*/

prdt stock[MAX_IDP]; /*Array que guarda todos os produtos criadas.*/
enc encomendas[MAX_IDE]; /*Array que guarda todas as encomendas criadas.*/
int  nxt_idp = 0, nxt_ide = 0; /*N?meros inteiros que apontam para o idp do pr?ximo e da pr?xima encomenda, respetivamente.*/

/*############################# Fun??es: #############################*/

/*Esta fun??o adiciona um produto ao sistema. Guarda os dados inseridos nas respetivas componentes do produto adicionado.*/
void add_prd_stock(char dados[])
{
	strcpy(stock[nxt_idp].desc, strtok(dados, ":"));
	stock[nxt_idp].preco_prdt = atoi(strtok(NULL, ":"));
	stock[nxt_idp].peso_prdt = atoi(strtok(NULL, ":"));
	stock[nxt_idp].qtd_stock = atoi(strtok(NULL, ":"));
	stock[nxt_idp].idp = nxt_idp;

	printf("Novo produto %d.\n", stock[nxt_idp].idp);

	nxt_idp += 1;
}

/*Esta fun??o adiciona quantidade a um produto exisente no sistema. Acede ao respetivo indice do array de produtos e incrementa a componente 'qtd_stk'.*/
void add_qtd_stock(char dados[])
{
	int idp_in, qtd_in;

	idp_in = atoi(strtok(dados, ":"));
    qtd_in = atoi(strtok(NULL, ":"));

	if (idp_in >= nxt_idp)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_in);
	else
		stock[idp_in].qtd_stock += qtd_in;
}

/*Esta fun??o cria uma encomenda. Incrementa o apontador da pr?xima encomenda po um e inicializa as componentes da encomenda criada.*/
void cria_enc()
{
	encomendas[nxt_ide].ide = nxt_ide;
	encomendas[nxt_ide].nxt_prdt = 0;
	encomendas[nxt_ide].peso_enc = 0;

	printf("Nova encomenda %d.\n", encomendas[nxt_ide].ide);

	nxt_ide += 1;
}

/*Esta fun??o adiciona um produto a uma encomenda. Se o produto a adicionar for encontrado na itera??o dos produtos da encomenda em quest?o, 
atualiza as componentes necess?rias da encomenda e do produto, caso contr?rio insere o produto na encomenda atualizando tamb?m as componentes necess?rias.*/
void add_prd_enc(char dados[])   
{
	int ide_in, idp_in, qtd_in, i, flag_n_exst = 1;

	ide_in = atoi(strtok(dados, ":"));
	idp_in = atoi(strtok(NULL, ":"));
	qtd_in = atoi(strtok(NULL, ":"));

	if (ide_in >= nxt_ide)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_in, ide_in);

	else if (idp_in >= nxt_idp)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_in, ide_in);

	else if (stock[idp_in].qtd_stock < qtd_in)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_in, ide_in);

	else if (encomendas[ide_in].peso_enc + qtd_in * stock[idp_in].peso_prdt > MAX_PESO_ENC)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_in, ide_in);

	else
	{
		for (i = 0; i < encomendas[ide_in].nxt_prdt; i++)
		{
			if (encomendas[ide_in].produtos[i] == idp_in)
			{
				stock[idp_in].qtd_enc[ide_in] += qtd_in;
				encomendas[ide_in].peso_enc += qtd_in * stock[idp_in].peso_prdt;
				stock[idp_in].qtd_stock -= qtd_in;
				flag_n_exst = 0;
			}
		}
		if (flag_n_exst)
		{
			encomendas[ide_in].produtos[encomendas[ide_in].nxt_prdt] = idp_in;
			stock[idp_in].qtd_enc[ide_in] = qtd_in;
			encomendas[ide_in].peso_enc += qtd_in * stock[idp_in].peso_prdt;
			stock[idp_in].qtd_stock -= qtd_in;
			encomendas[ide_in].nxt_prdt += 1;    
		}
	}
}

/*Esta fun??o remove quantidade de um produto no sistema.*/ 
void rmv_qtd_stock(char dados[])
{
	int idp_in, qtd_in;

	idp_in = atoi(strtok(dados, ":"));
	qtd_in = atoi(strtok(NULL, ":"));

	if (idp_in >= nxt_idp)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_in);

	else if (qtd_in > stock[idp_in].qtd_stock)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd_in, idp_in);

	else
		stock[idp_in].qtd_stock -= qtd_in;
}

/*Esta fun??o remove um produto de uma encomanda. Isto ? feito iterando a encomenda em causa, quando o produto em causa for encontrado todos os seguintes fazem um "shift-left"*/
void rmv_prdt_enc(char dados[])  
{
	int ide_in, idp_in, i, prdt_a_rmv_encontrd = 0;

	ide_in = atoi(strtok(dados, ":"));
	idp_in = atoi(strtok(NULL, ":"));

	if (ide_in >= nxt_ide)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_in, ide_in);

	else if (idp_in >= nxt_idp)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_in, ide_in);

	else
	{
		for (i = 0; i < encomendas[ide_in].nxt_prdt; i++)
		{
			if (encomendas[ide_in].produtos[i] == idp_in)
			{
				prdt_a_rmv_encontrd = 1;
				encomendas[ide_in].peso_enc -= stock[idp_in].qtd_enc[ide_in] * stock[idp_in].peso_prdt;
				stock[idp_in].qtd_stock += stock[idp_in].qtd_enc[ide_in];
				stock[idp_in].qtd_enc[ide_in] = 0;
			}
			if (prdt_a_rmv_encontrd)
				encomendas[ide_in].produtos[i] = encomendas[ide_in].produtos[i + 1];
		}
		if (prdt_a_rmv_encontrd)
			encomendas[ide_in].nxt_prdt -= 1;
	}
}

/*Esta fun??o calcula o pre?o de uma encomenda. Isto ? feito iterando a encomenda em causa, em cada produto soma-se a uma vari?vel a quantidade do produto na encomenda vezes o pre?o
	do produto em quest?o.*/
void get_preco_enc(char dados[])
{
	int ide_in, i, preco_enc = 0;

	ide_in = atoi(strtok(dados, ":"));

	if (ide_in >= nxt_ide)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_in);

	else
	{
		for (i = 0; i < encomendas[ide_in].nxt_prdt; i++)
			preco_enc += stock[encomendas[ide_in].produtos[i]].qtd_enc[ide_in] * stock[encomendas[ide_in].produtos[i]].preco_prdt;
		printf("Custo da encomenda %d %d.\n", ide_in, preco_enc);
	}
}

/*Esta fun??o altera o pre?o de um produto acedendo ? respetiva componente do produto em causa.*/
void alt_preco_prdt(char dados[]) 
{
	int idp_in, preco_in;

	idp_in = atoi(strtok(dados, ":"));
	preco_in = atoi(strtok(NULL, ":"));

	if (idp_in >= nxt_idp)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_in);

	else
		stock[idp_in].preco_prdt = preco_in;
}

/*Esta fun??o mostra a descri??o e a quantidade de um produto numa encomenda.*/
void get_desc_qtd_prdt_enc(char dados[])
{
	int ide_in, idp_in, i, prdt_inxst = 1;

	ide_in = atoi(strtok(dados, ":"));
	idp_in = atoi(strtok(NULL, ":"));

	if (ide_in >= nxt_ide)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_in);

	else if (idp_in >= nxt_idp)
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp_in);

	else
	{
		for (i = 0; i < encomendas[ide_in].nxt_prdt; i++)
		{
			if (encomendas[ide_in].produtos[i] == idp_in)
			{
		        printf("%s %d.\n", stock[idp_in].desc, stock[idp_in].qtd_enc[ide_in]);
		        prdt_inxst = 0;
			}
	    }
	    if (prdt_inxst)
	    	printf("%s %d.\n", stock[idp_in].desc, 0);
	}
}

/*Esta fun??o encontra a encomenda em que um certo produto existe em maior quntidade. Isto ? feito iterando a componente 'qtd_enc' do produto em causa.*/
void get_enc_max_prdt(char dados[])
{
	int idp_in, i, flag_prdt_exst = 0, max_qtd_enc = 0, ide_max_qtd;

	idp_in = atoi(strtok(dados, ":"));

	if (idp_in >= nxt_idp)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_in);

	for (i = 0; i < nxt_ide; i++)
	{
		if (stock[idp_in].qtd_enc[i] > max_qtd_enc)
		{
			max_qtd_enc = stock[idp_in].qtd_enc[i];
			ide_max_qtd = i;
			flag_prdt_exst = 1;
		}
	}
	if (flag_prdt_exst && nxt_ide != 0)
		printf("Maximo produto %d %d %d.\n", idp_in, ide_max_qtd, max_qtd_enc);	
}

/*Esta fun??o "junta" dois arrays ordenados num s?, por sua vez tamb?m ordenado. Isto ? feito retirando das extermidades dos dois arrays o menor elemento.
	(A fun??o ? utilizada pelo comando 'l' e 'L' por isso ? que recebe o argumento "mode").*/
void merge(int arr[], int i_l, int i_r, int i_m, char mode)
{
	int l, r, i;
	int aux[MAX_IDP];

	for (l = i_m + 1; l > i_l; l--)
		aux[l - 1] = arr[l - 1];
	for (r = i_m; r < i_r; r++)
		aux[i_r + i_m - r] = arr[r + 1];

	for (i = i_l; i <= i_r; i++)
	{
		if (mode == 'l')
		{
			if (stock[aux[l]].preco_prdt == stock[aux[r]].preco_prdt)
			{
				if (aux[l] > aux[r])
					arr[i] = aux[r--];
				else 
					arr[i] = aux[l++];
			}
			else if (stock[aux[l]].preco_prdt > stock[aux[r]].preco_prdt)
				arr[i] = aux[r--];
			else
				arr[i] = aux[l++];
		}
		else
		{
			if (strcmp(stock[aux[l]].desc, stock[aux[r]].desc) == 0)
			{
				if (stock[aux[l]].idp > stock[aux[r]].idp)
					arr[i] = aux[r--];
				else 
					arr[i] = aux[l++];
			}
			else if (strcmp(stock[aux[l]].desc, stock[aux[r]].desc) > 0)
				arr[i] = aux[r--];
			else
				arr[i] = aux[l++];
		}
	}
}

/*Esta fun??o separa um array em arrays de um s? elemento que s?o depois ordenados pela fun??o "merge".*/
void mrg_srt(int arr[], int lim_l, int lim_r, char mode)
{
	int lim_m = (lim_l + lim_r) / 2;

	if (lim_l >= lim_r)
		return;

	mrg_srt(arr, lim_l, lim_m, mode);
	mrg_srt(arr, lim_m + 1, lim_r, mode);
	merge(arr, lim_l, lim_r, lim_m, mode);
}

/*Esta fun??o mostra todos os produtos existentes no sistema ordenados  por ordem crescente de pre?o. Isto ? eito fazendo uma c?pia do array que cont?m os 
	produtos do sistema (apenas dos idp's deles) e passando esta c?pia ? fun??o "mrg_srt".*/
void get_prdts_stock_ord_preco()
{
	int i;
	int prdts_ord[MAX_IDP];

	for (i = 0; i < nxt_idp; i++)
		prdts_ord[i] = i;

	mrg_srt(prdts_ord, 0, nxt_idp - 1, 'l');

	printf("Produtos\n");
	for (i = 0; i < nxt_idp; i++)
		printf("* %s %d %d\n", stock[prdts_ord[i]].desc, stock[prdts_ord[i]].preco_prdt, stock[prdts_ord[i]].qtd_stock);
}

/*Esta fun??o mostra todos os produtos existentes numa dada encomenda por ordem alfab?tica. Isto ? feito fazendo uma c?pia d array que cont?m os produtos da 
	encomenda em causa e passando esta c?pia ? fun??o "mrg_srt".*/
void get_prdts_enc_ord_alph(char dados[])
{
	int i, ide_in;
	int prdts_ord[MAX_IDP];

	ide_in = atoi(strtok(dados, ":"));

	if (ide_in >= nxt_ide)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_in);

	else
	{
		for (i = 0; i < encomendas[ide_in].nxt_prdt; i++)
			prdts_ord[i] = encomendas[ide_in].produtos[i];

		mrg_srt(prdts_ord, 0, encomendas[ide_in].nxt_prdt - 1, 'L');

		printf("Encomenda %d\n", ide_in);
		for (i = 0; i < encomendas[ide_in].nxt_prdt; i++)
			printf("* %s %d %d\n", stock[prdts_ord[i]].desc, stock[prdts_ord[i]].preco_prdt, stock[prdts_ord[i]].qtd_enc[ide_in]);
	}
}

/*Fun??o main. Encarregue de esperar inputs. Est? sempre num ciclo while at? que o comando 'x' seja efetuado terminando o programa.*/
int main()
{
	char instr[1024];

	while (1)
	{
		fgets(instr, 1024, stdin);

		switch (instr[0])
		{
			case 'a':
				add_prd_stock(&instr[2]);	
				break;

			case 'q': 				
				add_qtd_stock(&instr[2]);		
				break;

			case 'N':
				cria_enc();	
				break;

			case 'A':
				add_prd_enc(&instr[2]);		
				break;

			case 'r':
				rmv_qtd_stock(&instr[2]);	
				break;

			case 'R': 				
				rmv_prdt_enc(&instr[2]);
				break;

			case 'C':
				get_preco_enc(&instr[2]);
				break;

			case 'p':
				alt_preco_prdt(&instr[2]);
				break;

			case 'E':
				get_desc_qtd_prdt_enc(&instr[2]);
				break;

			case 'm': 				
				get_enc_max_prdt(&instr[2]);
				break;

			case 'l':
				get_prdts_stock_ord_preco();
				break;

			case 'L':
				get_prdts_enc_ord_alph(&instr[2]);
				break;

			case 'x':
				exit(0);
		}
	}
	return 0;
}