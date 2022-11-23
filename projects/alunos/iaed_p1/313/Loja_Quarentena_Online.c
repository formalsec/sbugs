#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define IDP_MAX 10000		/*Numero maximo de produtos*/
#define IDE_MAX 500			/*Numero maximo de encomendas*/
#define PESO_MAX 200		/*Peso maximo numa encomenda, (que coincide com valor maximo de produtos numa encomenda,*/
								/*pois o peso minimo de cada produto e 1 unidade)*/

#define DESCRICAO 64		/*Numero maximo de caracteres numa descricao*/

void cria_produto();			/*cria um produto novo, (com valor 'idp' como identificador), e adiciona-o ao sistema*/
void adiciona_stock();			/*adiciona stock, (uma quantidade), de um produto ao sistema*/
void retira_stock();			/*retira stock de um produto*/
void altera_preco();			/*altera o preco de um produto*/
void precos_ordem();			/*funcao que lista os precos por ordem crescente*/
void cria_encomenda();			/*cria uma encomenda nova, (com valor 'ide' como identificador), e adiciona-a ao sistema*/
void adiciona_produto();		/*adiciona um produto a uma encomenda*/
void retira_produto();			/*retira um produto de uma encomenda*/
void custo_encomenda();			/*calcula o preco que uma encomenda*/
void produto_em_encomenda();	/*Mostra a descricao e a quantidade de um produto numa encomenda*/
void produto_mais_vezes();		/*Mostra a encomenda em que um dado produto ocorre mais vezes*/
void descr_ordem();				/*Lista as decricoes ,dos produtos presentes numa encomenda, por ordem alfabetica*/
int particao_precos();			/*Faz a particao da funcao de ordenacao dos precos*/
void quicksort_precos();		/*Faz a recursiva da funcao de ordenacao dos precos*/
int particao_descr();			/*Faz a particao da funcao de ordenacao das decricoes*/
void quicksort_descr();			/*Faz a recursiva da funcao de ordenacao das descricoes*/
void restart_contagens();		/*fun??o extra que mete os pesos e numero de produtos de cada encomenda com valor 0*/





char descr [IDP_MAX][DESCRICAO];			/*tabela de produtos e das respetivas descricoes*/
int preco_prod [IDP_MAX][2];				/*tabela em que cada linha e um produto, e em que a 1? posicao e o preco do produto e a 2? e o idp do produto*/
int peso_prod [IDP_MAX];					/*array em que cada valor e o peso de cada unidade de um produto*/
int stock_prod [IDP_MAX];					/*array em que cada valor e o  stock de um produto no sistema*/
int encomenda[IDE_MAX][PESO_MAX];			/*tabela de encomendas, em que cada uma pode conter ate 200 produtos*/
int peso_enc [IDE_MAX];						/*array em que cada valor e o peso de uma encomenda*/
int stock_enc [IDE_MAX][PESO_MAX]; 			/*tabela de encomendas e dos respetivos stocks de cada produto dentro delas*/
int nmr_prod_enc [IDE_MAX];					/*array em que cada valor e o numero de produtos em cada encomenda*/
int idp = 0;								/*identificador dos produtos*/
int ide = 0;								/*identificador das encomendas*/
int ord [IDP_MAX][2];						/*array dos precos dos produtos ordenados*/
int idp_ord [IDP_MAX];						/*vetor 'extra', onde e alterada a ordem dos diferentes idps, de modo a nao alterar o original*/
int stock_enc_ord [PESO_MAX];				/*Vetor 'extra', onde a ordem dos diferentes stocks nas encomendas de diferentes produtos sao alterados*/

int main(){
	char n;
	restart_contagens();
	while ((scanf("%c", &n)) !='x'){
		switch(n){
			case ('a'):
			getchar(); /*retira o caracter ' '*/
			cria_produto();
			break;

			case('q'):
			getchar();
			adiciona_stock();
			break;

			case('N'):
			cria_encomenda();
			break;

			case('A'):
			getchar();
			adiciona_produto();
			break;

			case('r'):
			getchar();
			retira_stock();
			break;

			case('R'):
			getchar();
			retira_produto();
			break;

			case('C'):
			getchar();
			custo_encomenda();
			break;

			case('p'):
			getchar();
			altera_preco();
			break;

			case('E'):
			getchar();
			produto_em_encomenda();
			break;

			case('m'):
			getchar();
			produto_mais_vezes();
			break;


			case('l'):
			precos_ordem();
			break;

			case('L'):
			getchar();
			descr_ordem();
			break;


			case('x'):
			return 0;
			break;
		}
	}
return 0;
}


void cria_produto(){ /*(a)*/
	char c;
	int atual = 0;
	while (atual != 4){
		int j = 0, i = 0;
		switch(atual){
			/*Ao longo da funcao existe a separacao dos diversos
			elementos de cada produto nos arrays respetivos*/
			case (0):
				for (;((c = getchar())!= ':'); ++i)
					descr[idp][i] = c;
				++atual;
				break;

			case (1):
				while((c = getchar()) != ':')
					j = j * 10 + (c - 48);  /* -->   Como o getchar le characters e nao ints,*/
				preco_prod[idp][0] = j;			/*os numeros lidos nao equivalem ao seu valor int*/
				preco_prod[idp][1] = idp;
				++atual;						/*mas sim a (n + 48), sendo n o numero lido.*/
				break;							/*Isto acontece ao longo do programa*/					
			
			case(2):
				while ((c = getchar()) != ':')		
					j = j * 10 + (c - 48);			
				peso_prod[idp] = j;
				++atual;
				break;

			case(3):
				while ((c = getchar()) != '\n')
					j = j * 10 + (c - 48);
				stock_prod[idp] = j;
				++atual;
				break;
		}
	}			
	printf("Novo produto %d.\n", idp); 	/*De cada vez que se cria um produto, o valor global de idp aumenta*/
	++idp;								/*de modo a garantir diferentes identificadores para diferentes produtos*/
}


void adiciona_stock(){/*(q)*/
	char c;
	int prod = 0;
	int atual = 0;
	while (atual != 2){
		int j = 0;
		switch(atual){
			case(0):
				while((c = getchar()) != ':')
					prod = prod * 10 + (c - 48);
				++atual;
				break;
			case(1):
				if (prod >= idp){	/*se o idp dado nao for um valor ja guardado no sistema e considerado erro*/
					printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prod);
				}
				else{
						while((c = getchar()) != '\n')
						j = j * 10 + (c - 48);
					stock_prod[prod] += j;	/*adiciona o valor do stock dado ao stock existente do produto*/
				}
				++atual;
				break;
		}
	}
}

void cria_encomenda(){/*(N)*/
	printf("Nova encomenda %d.\n", ide);
	++ide;			/*Ao criar uma encomenda, o valor global aumena uma unidade, para gar
					para garantir que nao ha duas encomendas com o mesmo identificador*/
}

void adiciona_produto(){/*(A)*/
	char c, repetido = 'n';
	int prod = 0, enc = 0, atual = 0, qnt = 0, posicao_repetido = 0, i = 0;
	while (atual != 3){
		switch(atual){
			case(0):
				while((c = getchar()) != ':')
					enc = enc * 10 + (c - 48);
				++atual;
				break;

			case(1):
				while((c = getchar()) != ':')
					prod = prod * 10 + (c -48);

				if (enc >= ide){
					printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
					return;
				}
				else if (prod >= idp){
						printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
						return;
				}
				else
					++atual;
				break;

			case(2):
				while((c = getchar()) != '\n'){
					qnt = qnt * 10 + (c - 48);
				}

				if (qnt > stock_prod[prod])
					printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prod, enc);
				
				else if  (((peso_prod[prod] * qnt) + peso_enc[enc]) > 200)
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prod, enc);
				
				else{
					if (nmr_prod_enc[enc] > 0){			
						for (; i < nmr_prod_enc[enc]; ++i){
							if (prod == encomenda[enc][i]){	/*Verifica se o produto ja esta no sistema*/
								repetido = 'y';
								posicao_repetido = i;
							}
						}
					}
					if (repetido == 'y')
						stock_enc[enc][posicao_repetido] += qnt;
					
					else{
						encomenda[enc][nmr_prod_enc[enc]] = prod;
						stock_enc[enc][nmr_prod_enc[enc]] = qnt;
						nmr_prod_enc[enc] += 1;
					}
					peso_enc[enc] += (peso_prod[prod] * qnt);
					stock_prod[prod] -= qnt;
				}
				return;
		}
	}
}

void retira_stock(){/*(r)*/
	char c;
	int prod = 0;
	int atual = 0;
	while (atual != 2){
		int j = 0;
		switch(atual){
			case(0):
				while((c = getchar()) != ':')
					prod = prod * 10 + (c - 48);
				++atual;
				break;
			case(1):
				if (prod >= idp)
					printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod);
				
				else{
					while((c = getchar()) != '\n')
					j = j * 10 + (c - 48);
					if (j > stock_prod[prod])
						printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", j, prod);
					else
						stock_prod[prod] -= j;
				}
				++atual;
				break;
		}
	}
}

void retira_produto(){/*(R)*/
	char c, aux = 'n';
	int i = 0, prod = 0, atual = 0, enc = 0, posicao = 0;
	while (atual != 2){
		switch(atual){
			case(0):
				while((c = getchar()) != ':')
					enc = enc * 10 + (c - 48);
				++atual;
				break;

			case(1):
				while((c = getchar()) != '\n')
					prod = prod * 10 + (c - 48);
				
				if (enc >= ide)
					printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
				
				else if (prod >= idp)
					printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",prod, enc);
				
				else{
					while (i < nmr_prod_enc[enc]){
						if (encomenda[enc][i] == prod){
							posicao = i;
							aux = 'y';
						}
						++i;
					}
					if (aux == 'y'){
						stock_prod[prod] += stock_enc[enc][posicao];
						peso_enc[enc] -= stock_enc[enc][posicao] * peso_prod[prod];
						for (; posicao < nmr_prod_enc[enc]; ++posicao){					/*Retirar um produto da encomenda*/
							stock_enc[enc][posicao] = stock_enc[enc][posicao + 1];
							encomenda[enc][posicao] = encomenda[enc][posicao + 1];
						}
						--nmr_prod_enc[enc];
					}
				}	
				++atual;
				break;
		}
	}		
}

void custo_encomenda(){/*(C)*/
	int total = 0, enc = 0, i = 0;
	char c;
	while ((c = getchar()) != '\n')
		enc = enc * 10 + (c - 48);
	if (enc >= ide)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", enc);
	else{
		for (; i < nmr_prod_enc[enc]; ++i)
			total += (stock_enc[enc][i] * preco_prod[encomenda[enc][i]][0]);
		printf("Custo da encomenda %d %d.\n", enc, total);
	}
}

void altera_preco(){/*(p)*/
	char c;
	int prod = 0;
	int atual = 0;
	while (atual != 2){
		int j = 0;
		switch(atual){
			case(0):
				while((c = getchar()) != ':')
					prod = prod * 10 + (c - 48);
				++atual;
				break;
			case(1):
				if (prod >= idp)
					printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", prod);
				
				else{
					while((c = getchar()) != '\n')
						j = j * 10 + (c - 48);
					preco_prod[prod][0] = j;
				}
				++atual;
				break;
		}
	}
}

void produto_em_encomenda(){/*(E)*/
	char c, aux = 'n';
	int atual = 0, i = 0, enc = 0, prod = 0, j = 0, posicao = 0;
	while (atual != 2){
		switch(atual){
			case(0):
				while((c = getchar()) != ':')
					enc = enc * 10 + (c - 48);
				++atual;
				break;
			case(1):
				while((c = getchar()) != '\n')
					prod = prod * 10 + (c - 48);
				if (enc >= ide)
					printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
				else if (prod >= idp)
					printf("Impossivel listar produto %d. Produto inexistente.\n", prod);
				else{
					while(i < nmr_prod_enc[enc]){
						if (encomenda[enc][i] == prod){
							aux = 'y';
							posicao = i;
						}
						++i;

					}
					for (; descr[prod][j] != '\0'; ++j)
						printf("%c", descr[prod][j]);
					if (aux == 'y')
						printf(" %d.\n", stock_enc[enc][posicao]);

					else
						printf(" 0.\n");
				}
				return;
		}		
	}
}

void produto_mais_vezes(){/*(m)*/
	int i = 0, j, prod = 0, enc_max = 0, quant_max = 0;
	char c;
	while ((c = getchar()) != '\n')
		prod = prod * 10 + (c - 48);
	if (prod >= idp){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",prod);
		return;
	}
	for (; i < ide; ++i){
		for (j = 0; j < nmr_prod_enc[i]; ++j){
			if ((prod == encomenda[i][j]) && (stock_enc[i][j] > quant_max)){
				enc_max = i;
				quant_max = stock_enc[i][j];
			}
		}
	}
	if (quant_max != 0)
		printf("Maximo produto %d %d %d.\n", prod, enc_max, quant_max);
	return;
}

void precos_ordem(){/*(l)*/
	int i, j;
	char c;
	for (i = 0; i < idp; ++i){
		ord[i][0] = preco_prod[i][0];
		ord[i][1] = preco_prod[i][1];	/*'cria' copias para serem alteradas em vez dos originais*/
	}
	quicksort_precos(ord, 0, (idp - 1));
	printf("Produtos\n");
	for (i = 0; i < idp; ++i){
		printf("* ");
		for (j = 0; (c = descr[ord[i][1]][j]) != '\0'; ++j)
			printf("%c", c);

		printf(" %d", ord[i][0]);
		printf(" %d\n", stock_prod[ord[i][1]]);
	}

}

int particao_precos(int ord[][2], int menor, int maior){
	int j, i = (menor - 1), pivot = ord[maior][0], trocado_preco = 0, trocado_idp = 0;
	for (j = menor; j <= (maior - 1); j++){
		if ((ord[j][0] < pivot) || ((ord[j][0] == pivot) && (ord[maior][1] > ord[j][1]))){
			i++;
			trocado_preco = ord[i][0];
			trocado_idp = ord[i][1];	/*Alterar a posicao do preco e do idp*/
			ord[i][0] = ord[j][0];
			ord[i][1] = ord[j][1];
			ord[j][0] = trocado_preco;
			ord[j][1] = trocado_idp;
		}
	}
	trocado_preco = ord[i + 1][0];
	trocado_idp = ord[i + 1][1];
	ord[i + 1][0] = ord[maior][0];
	ord[i + 1][1] = ord[maior][1];
	ord[maior][0] = trocado_preco;
	ord[maior][1] = trocado_idp;
	return (i + 1);
}

void quicksort_precos(int ord[][2], int menor, int maior){
	int pivot;
	if (menor < maior){
		pivot  = particao_precos(ord, menor, maior);

		quicksort_precos(ord, menor, (pivot - 1));
		quicksort_precos(ord, (pivot + 1), maior);
	}
}


void descr_ordem(){/*(L)*/
	char c;
	int enc = 0, i, j;
	while ((c = getchar()) != '\n')
		enc = enc * 10 + (c - 48);
	if (enc >= ide){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
	return;
	}
	for (i = 0; i < nmr_prod_enc[enc]; ++i){
		idp_ord[i] = encomenda[enc][i];			/*'cria' copias para serem alteradas em vez dos originais*/
		stock_enc_ord[i] = stock_enc[enc][i];
	}

	quicksort_descr(idp_ord, stock_enc_ord, 0, (nmr_prod_enc[enc] - 1));
	printf("Encomenda %d\n", enc);

	for (i = 0; i < nmr_prod_enc[enc]; ++i){
		printf("* ");
		for (j = 0; (c = descr[idp_ord[i]][j]) != '\0'; ++j)
			printf("%c", c);

		printf(" %d", preco_prod[idp_ord[i]][0]);
		printf(" %d\n", stock_enc_ord[i]);
	}

}

int particao_descr(int ord[], int s_e[], int menor, int maior){
	int i = (menor - 1), pivot = idp_ord[maior], t = 0, j, s;

	for (j = menor; j <= (maior - 1); j++){
		if ((strcmp(descr[ord[j]], descr[pivot]) < 0) || ((strcmp(descr[ord[j]], descr[pivot]) == 0) && (pivot > ord[j]))){
			++i;
			t = ord[i];
			ord[i] = ord[j];
			ord[j] = t;

			s = s_e[i];
			s_e[i] = s_e[j];
			s_e[j] = s;
		}
	}
	t = ord[i + 1];
	ord[i + 1] = ord[maior];
	ord[maior] = t;

	s = s_e[i + 1];
	s_e[i + 1] = s_e[maior];
	s_e[maior] = s;
	return (i + 1);

}


void quicksort_descr(int ord[], int s_e[], int menor, int maior){
	int pivot;

	if (menor < maior){
		pivot = particao_descr(ord, s_e, menor, maior);

		quicksort_descr(ord, s_e, menor, (maior - 1));
		quicksort_descr(ord, s_e ,(pivot + 1), maior);
	}
}


void restart_contagens(){
	int i = 0;
	for (; i < 500; ++i){
		peso_enc[i] = 0;
		nmr_prod_enc[i] = 0;
	}
}
