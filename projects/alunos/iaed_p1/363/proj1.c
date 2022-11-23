#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IN 1024
#define MAX_PROD 10001
#define MAX_ENC 501
#define MAX_PESO 200
#define MAX_DESC 64


/**************/
/* Estruturas */
/**************/

typedef struct produto{    /* Estrutura dos produtos */

	char desc[MAX_DESC];
	int preco, peso, qtd, id;

} Produto;


typedef struct encomenda{    /* Estrutura das encomendas */

	int preco, peso, id, conj_prod[MAX_PROD], conj_qtds[MAX_PROD];

} Encomenda;


/*********************/
/* Vari?veis Globais */
/*********************/

Produto prods[MAX_PROD];   /* Stock de produtos */
Encomenda encom[MAX_ENC];  /* Lista de encomendas */

int idp;                   /* Vari?vel respons?vel pela identifica??o dos produtos */
int ide;                   /* Vari?vel respons?vel pela identifica??o das encomendas */
int qtd_prod[MAX_PESO];    /* Array que toma como valores a quantidade de produtos por encomenda */
int flag;                  /* Flag usada para saber qual das ordena??es a executar */


/**********************/
/* Fun??es Auxiliares */
/**********************/

/* Fun??o que ordena o array inserido */

void merge(int arr[], int l, int m, int r){
	int i, j, k, aux[MAX_PROD];

	for (i = m + 1; i > l; i--)
		aux[i - 1] = arr[i - 1];       
		/* Dois ciclos que preenchem o vetor auxiliar a partir do array inserido */

	for (j = m; j < r; j++)
		aux[r + m - j] = arr[j + 1];
	if (flag == 0){
		for (k = l; k <= r; k++){
			if (prods[aux[j]].preco < prods[aux[i]].preco || i > m)  
			/* Verifica qual o produto com o menor pre?o */
				arr[k] = aux[j--];
			else
				arr[k] = aux[i++];
		}	
	}
	else{
		for (k = l; k <= r; k++){
			if (strcmp(prods[aux[j]].desc, prods[aux[i]].desc) < 0 || i > m) 
			/* Verifica qual o produto com a descri??o que vem em primeiro na ordem alfab?tica */
				arr[k] = aux[j--];
			else
				arr[k] = aux[i++];
		}	
	}
}


/* Fun??o recursiva de ordena??o */

void merge_sort(int arr[], int l, int r){

	int m = (r + l) / 2;
	if (r <= l)
		return;
	merge_sort(arr, l, m);
	merge_sort(arr, m + 1, r);
	merge(arr, l, m, r);
}


/***********/
/* Fun??es */
/***********/

/* Comando 'a' */
/* Fun??o que adiciona um produto ao sistema */

void add_prod(char input[MAX_IN]){
	Produto p;

	strcpy(p.desc, strtok(input, ":"));
	p.preco = atoi(strtok(NULL, ":"));
	p.peso = atoi(strtok(NULL, ":"));
	p.qtd = atoi(strtok(NULL, ":"));
	p.id = idp;
	/* S?o preenchidas as componentes do Produto inserido no stock */ 

	printf("Novo produto %d.\n", idp);
	prods[idp] = p;
	idp++;
	/* ? adicionado o produto ? lista de produtos (prods) e ? incrementado o valor do idp para
	o pr?ximo produto */
}

/* Comando 'q' */
/* Fun??o que adiciona stock a um produto do sistema */

void add_stock(char input[MAX_IN]){
	int id_p, quant;

	id_p = atoi(strtok(input, ":"));
	quant = atoi(strtok(NULL, ":"));

	if (id_p >= idp)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id_p);
	else
		prods[id_p].qtd += quant;
		/* Adiciona stock ao produto em causa */
}

/* Comando 'N' */
/* Fun??o que adiciona uma encomenda ao sistema */

void add_enc(){
	Encomenda e;

	e.preco = 0;
	e.peso = 0;
	e.id = ide;
	/* S?o preenchidas as componetes da Encomenda criada */

	printf("Nova encomenda %d.\n", ide);
	encom[ide] = e;
	ide++;
	/* ? adicionada a encomenda ? lista de encomendas (encom) e ? incrementado o valor do ide para
	a pr?xima encomenda */
}

/* Comando 'A' */
/* Fun??o que adiciona um produto a uma ecomenda do sistema */

void add_prod_enc(char input[MAX_IN]){
	int id_e, id_p, quant, i, j = 0;
	Produto p;
	Encomenda e;

	id_e = atoi(strtok(input, ":"));
	id_p = atoi(strtok(NULL, ":"));
	quant = atoi(strtok(NULL, ":"));
	p = prods[id_p];
	e = encom[id_e];

	if(id_e > ide - 1)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_p, id_e);
	else if (id_p > idp - 1)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_p, id_e);
	else if (quant > p.qtd)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_p, id_e);
	else if ((e.peso + p.peso * quant) > MAX_PESO)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_p, id_e);
	else{
		for (i = 0; i < qtd_prod[id_e] && j == 0; i++){
			/* Ciclo que itera a lista de produtos da encomenda */

			if (id_p == e.conj_prod[i]){
				/* Condi??o que verifica se o produto a adicionar j? se encontra na encomenda */
			   e.conj_qtds[i] += quant;
			   j++;
			   /* Adiciona a quantidade ao produto caso a condi??o se verifique e adiciona "1"
			   ? vari?vel "j" para verificar a condi??o seguinte */
			}  
		}
		if (j == 0){	
			/* Caso j seja 0, ou seja, o produto n?o se encontra na encomenda, adiciona-o */

			e.conj_prod[qtd_prod[id_e]] = id_p;
			e.conj_qtds[qtd_prod[id_e]] = quant;
			qtd_prod[id_e]++;
			/* Adiciona o id ao conjunto de produtos relativo ? encomenda, a quantidade pretendida
			ao conjunto de quantidades relativo aos produtos dessa encomenda e aumenta "1" na
			quantidade de produtos relativa ? encomenda */
		}
		e.preco += p.preco * quant; 
	    e.peso += p.peso * quant;
		e.id = id_e;	
		prods[id_p].qtd -= quant;
		/* S?o atualizadas as componentes da encomenda e a quantidade do produto em stock
		que lhe foi adicionado */
	}
	encom[id_e] = e;
}

/* Comando 'r' */
/* Fun??o que remove stock de um produto do sistema */

void remove_stock(char input[MAX_IN]){
	int id_p, quant;

	id_p = atoi(strtok(input, ":"));
	quant = atoi(strtok(NULL, ":"));

	if (id_p > idp - 1)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_p);
	else if (prods[id_p].qtd < quant)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quant, id_p);
	else
		prods[id_p].qtd -= quant;
		/* Remove stock do produto em causa */
}

/* Comando 'R' */
/* Fun??o que remove um produto de uma encomenda do sistema */

void remove_produto_enc(char input[MAX_IN]){
	int id_e, id_p, i = 0, j;
	Encomenda e;

	id_e = atoi(strtok(input, ":"));
	id_p = atoi(strtok(NULL, ":"));
	e = encom[id_e];

	if(id_e > ide - 1)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_p, id_e);
	else if (id_p > idp - 1)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_p, id_e);
	else{
		while(e.conj_prod[i] != id_p && i < qtd_prod[id_e])
			i++;
			/* Ciclo que verifica se o produto em causa est? na encomenda */

		if (i != qtd_prod[id_e]){
			e.preco -= prods[id_p].preco * e.conj_qtds[i];
			e.peso -= prods[id_p].peso * e.conj_qtds[i];
			prods[id_p].qtd += e.conj_qtds[i];
			/* Caso esteja, atualiza as componentes da encomenda e adiciona a quantidade
			que estava na encomenda, de volta ao stock */

			for (j = i; j < qtd_prod[id_e]; j++){
				/* Ciclo que faz com que o produto seja retirado da encomenda */
				e.conj_prod[j] = e.conj_prod[j + 1];
				e.conj_qtds[j] = e.conj_qtds[j + 1];
			}	
			qtd_prod[id_e]--;
			/* Retira "1" ? quantidade de produtos relativa ? encomenda */
		}
	}
	encom[id_e] = e;
}

/* Comando 'C' */
/* Fun??o que calcula o pre?o de uma encomenda do sistema */

void custo_enc(char input[MAX_IN]){
 	int id_e;
 	Encomenda e;

 	id_e = atoi(strtok(input, ":"));
 	e = encom[id_e];
 	
 	if(id_e > ide - 1)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_e);
	else
		printf("Custo da encomenda %d %d.\n", id_e, e.preco);
		/* Caso nenhum erro se verifique, ? devolvido ide e o custo da encomenda */
}

/* Comando 'p' */
/* Fun??o que altera o pre?o de um produto do sistema */

void altera_preco(char input[MAX_IN]){
 	int id_p, preco_novo, i, j, preco_antigo;
 	Encomenda e;

 	id_p = atoi(strtok(input, ":"));
 	preco_novo = atoi(strtok(NULL, ":"));
 	preco_antigo = prods[id_p].preco;

 	if (id_p > idp - 1)
 		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_p);
 	else{
 		prods[id_p].preco = preco_novo;
 		/* Altera o pre?o do produto no stock */
 		for (i = 0; i < ide; i++){
 			/* Ciclo que itera a lista de encomendas do sistema */
 			e = encom[i];
 			for (j = 0; j < qtd_prod[i]; j++){
 				/* Ciclo que itera a lista de produtos da encomenda */

 				if (id_p == e.conj_prod[j]){
 					e.preco -= preco_antigo * e.conj_qtds[j];
 					e.preco += preco_novo * e.conj_qtds[j];
 					/* Caso o produto se encontre na encomenda, atualiza o pre?o da mesma */
 				}
 			}
 			encom[i] = e;
 		}
 	}	
}

/* Comando 'E' */
/* Fun??o que lista a descri??o e a quantidade de um produto duma encomenda do sistema */

void desc_qtd_enc(char input[MAX_IN]){
 	int id_e, id_p, i, j = 0;
 	Encomenda e;

 	id_e = atoi(strtok(input, ":"));
 	id_p = atoi(strtok(NULL, ":"));
 	e = encom[id_e];

 	if (id_e > ide - 1)
 		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_e);
 	else if (id_p > idp - 1)
 		printf("Impossivel listar produto %d. Produto inexistente.\n", id_p);
 	else{
 		for (i = 0; i < qtd_prod[id_e]; i++){
 			/* Ciclo que itera a lista de produtos da encomenda */

 			if (e.conj_prod[i] == id_p){
 				printf("%s %d.\n", prods[id_p].desc, e.conj_qtds[i]);
 				/* Caso o produto esteja na encomenda, imprime a sua descri??o e quantidade */
 				j++;
 			}	
 		}
 		if (j == 0)
 			printf("%s %d.\n", prods[id_p].desc, 0);
 			/* Caso n?o esteja na encomenda, imprime a sua descri??o e a quantidade a "0" */
 	}
}

/* Comando 'm' */
/* Fun??o que indica a encomenda que cont?m mais quantidade do produto em causa */

void prod_ocorre_enc(char input[MAX_IN]){
	int id_p, id_e, medidor = 0, maior = 0, i, j;
	Encomenda e;

	id_p = atoi(strtok(input, ":"));

	if (id_p > idp - 1)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_p);
	for (i = 0; i < ide; i++){
		/* Ciclo que itera a lista de encomendas do sistema */
		e = encom[i];

		for (j = 0; j < qtd_prod[i]; j++){
			/* Ciclo que itera a lista de produtos da encomenda */

			if (e.conj_prod[j] == id_p)
				medidor = e.conj_qtds[j];
				/* Vari?vel que toma como valores as quantidades dos produtos da encomenda */
		}
		if (medidor > maior){
			maior = medidor;
		    id_e = i;
		    /* Caso a quantidade do produto nessa encomenda seja superior ? quantidade do mesmo
		    produto de outra encomenda, a vari?vel "maior" toma o valor dessa quantidade e o
		    id_e (vari?vel que toma os valores dos ide's das encomendas) toma o valor dessa encomenda */
		}
	}
	if (medidor != 0)
		printf("Maximo produto %d %d %d.\n", id_p, id_e, maior);	
}

/* Comando 'l' */
/* Fun??o que ordena todos o produtos do sistema por ordem de pre?o */

void ordena_prod_preco(){
	int i, j, lista_aux[MAX_PROD];
	flag = 0;

	for (i = 0; i < idp; i++)
		/* Ciclo que itera o stock de produtos */
		lista_aux[i] = prods[i].id;

	merge_sort(lista_aux, 0, idp - 1);
	/* Organiza a lista auxiliar que cont?m os id's dos produtos do stock */
	printf("Produtos\n");
	for (j = 0; j < idp; j++)
		/* Ciclo que itera a lista organizada por ordem de pre?o e imprime a descri??o, 
		o pre?o e a quantidade dos produtos */
		printf("* %s %d %d\n", prods[lista_aux[j]].desc, prods[lista_aux[j]].preco, prods[lista_aux[j]].qtd);
}

/* Comando 'L' */
/* Fun??o que ordena todos o produtos de uma encomenda do sistema por ordem alfab?tica */

void ordena_enc_alf(char input[MAX_IN]){
	int id_e, i, k, aux1[MAX_PROD], aux2[MAX_PROD];
	Encomenda e;
	flag = 1;

	id_e = atoi(strtok(input, ":"));
	e = encom[id_e];

	if (id_e > ide - 1)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_e);
	else{
		for (i = 0; i < qtd_prod[id_e]; i++){
			/* Ciclo que ? usado para criar uma c?pia da lista de produtos da encomenda em
			quast?o e uma lista de quantidades desses produtos colocadas no ?ndice que
			corresponde ao id de cada produto */
			aux1[i] = e.conj_prod[i];
			aux2[e.conj_prod[i]] = e.conj_qtds[i];
		}	
		merge_sort(aux1, 0, qtd_prod[id_e] - 1);
		/* Organiza a lista auxiliar "1" que cont?m os id's dos produtos da encomenda */
		printf("Encomenda %d\n", id_e);
		for (k = 0; k < qtd_prod[id_e]; k++)
			/* Ciclo que imprime os produtos organizados por ordem alfab?tica, isto ?, 
			a sua descri??o, o seu pre?o e a sua quantidade */
			printf("* %s %d %d\n", prods[aux1[k]].desc, prods[aux1[k]].preco, aux2[aux1[k]]);
	}	
}


/***************/
/* Fun??o main */
/***************/

int main(){
	char input[MAX_IN];
	
	while(fgets(input, MAX_IN, stdin)){
		/* Ciclo que aguarda o input do utilizador */

		switch(input[0]){
			/* Comando switch que cont?m todas as op??es poss?veis de intera??o do programa */

			case 'a':
				add_prod(&input[2]);
				break;

			case 'q':
				add_stock(&input[2]);
				break;
				
			case 'N':
				add_enc();
				break;

			case 'A':
				add_prod_enc(&input[2]);
				break;

			case 'r':
				remove_stock(&input[2]);
				break;

			case 'R':
				remove_produto_enc(&input[2]);
				break;

			case 'C':
				custo_enc(&input[2]);
				break;

			case 'p':
				altera_preco(&input[2]);
				break;

			case 'E':
				desc_qtd_enc(&input[2]);
				break;

			case 'm':
				prod_ocorre_enc(&input[2]);
				break;

			case 'l':
				ordena_prod_preco();
				break;

			case 'L':
				ordena_enc_alf(&input[2]);
				break;

			case 'x':
				return 0;

			default:
				break;
		}		
	}
	return 0;												
}
