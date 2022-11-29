#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUTO 10000
#define MAX_ENCOMENDA 500
#define MAX_PROD_ENC 200
#define CARACTERES 63

/******************************************************
*----------------------ESTRUTURAS---------------------*
******************************************************/

typedef struct prod{
	int idp; /*Identificador do produto*/
	char desc[CARACTERES]; /*Descricao do produto*/
	int preco, peso;
	int qnt; /*Quantidade em stock do produto idp quando acedido atraves de todos_produtos[idp].qnt e quantidade do produto idp na encomenda ide quando acedido atraves de todas_encomendas[ide].produtos[idp].qnt*/
} Produto;

typedef struct enc{
	int ide; /*Identificador da encomenda*/
	Produto produtos[MAX_PROD_ENC]; /*Todos os produtos da encomenda*/
	int peso_total_enc;
	int contador_prod_enc; /*Quantos produtos constituem a encomenda*/
} Encomenda;


/******************************************************
*-------------------VARIAVEIS GERAIS------------------*
******************************************************/

int idp = 0; /*Identificador do produto inicializado a 0*/
Produto todos_produtos[MAX_PRODUTO]; /*Este vetor contem todos os produtos existentes no sistema*/

int ide = 0; /*Identificador da encomenda inicializado a 0*/
Encomenda todas_encomendas[MAX_ENCOMENDA]; /*Este vetor contem todas as encomendas existentes no sistema*/

Produto aux_preco[MAX_PRODUTO]; /*Vetor de apoio ao algoritmo de ordenacao dos produtos atraves do preco*/
Produto aux_desc[MAX_ENCOMENDA]; /*Vetor de apoio ao algoritmo de ordenacao dos produtos de uma dada encomenda atraves da descricao*/

int contador_prod = 0; /*Contador de produtos no sistema*/
int contador_enc = 0; /*Contador de encomendas no sistema*/

/******************************************************
*----------------------DECLARACAO---------------------*
*----------------das funcoes auxiliares---------------*
******************************************************/

void novo_prod(); 
void adiciona_stock(); 
void nova_enc(); 
void adic_prod_enc(); 
void remove_stock(); 
void rem_prod_enc(); 
void calcula_custo_enc(); 
void altera_preco_prod(); 
void desc_qnt_prod_enc(); 
void enc_mais_prod(); 
void lista_produtos(); 
void lista_prod_encomenda(); 

/******************************************************
*-------------------FUNCAO PRINCIPAL------------------*
******************************************************/

int main(){

	char comando;

	while ((comando = getchar()) != 'x'){
		
		switch(comando){

		default:
			break;

		case 'a' :
			/*Funcao responsavel pela execucao do comando: a*/
			novo_prod();
			contador_prod++;
			break;

		case 'q' :
			/*Funcao responsavel pela execucao do comando: q*/
			adiciona_stock();
			break;

		case 'N' :
			/*Funcao responsavel pela execucao do comando: N*/
			nova_enc();
			contador_enc++;
			break;

		case 'A' :
			/*Funcao responsavel pela execucao do comando: A*/
			adic_prod_enc();
			break;

		case 'r' :
			/*Funcao responsavel pela execucao do comando: r*/
			remove_stock();
			break;

		case 'R' :
			/*Funcao responsavel pela execucao do comando: R*/
			rem_prod_enc();

			break;

		case 'C' :
			/*Funcao responsavel pela execucao do comando: C*/
			calcula_custo_enc();
			break;

		case 'p' :
			/*Funcao responsavel pela execucao do comando: p*/
			altera_preco_prod();
			break;

		case 'E' :
			/*Funcao responsavel pela execucao do comando: E*/
			desc_qnt_prod_enc();
			break;

		case 'm' :
			/*Funcao responsavel pela execucao do comando: m*/
			enc_mais_prod();
			break;

		case 'l' :
			/*Funcao responsavel pela execucao do comando: l*/
			lista_produtos();
			break;

		case 'L' :
			/*Funcao responsavel pela execucao do comando: L*/
			lista_prod_encomenda();
			break;
		}
	}
	
	return 0;
}

/******************************************************
*---------------ALGORITMOS DE ORDENACAO---------------*
******************************************************/

int compara_preco(Produto i ,Produto j){

    if(i.preco != j.preco)
        return i.preco < j.preco;
    /*Se houver 2 ou mais produtos com o mesmo pre?o, dever? entrar neste else para os ordenar por ordem crescente de id de produto*/
    else
        return i.idp < j.idp;
}

void merge_preco(Produto a[], int l, int m, int r){ 

    int i, j, k; 
    
    for (i = m + 1; i > l; i--) 
    	aux_preco[i - 1] = a[i - 1]; 

    for (j = m; j < r; j++) 
        aux_preco[r + m - j] = a[j + 1];

    for (k = l; k <= r; k++){

    	if (compara_preco(aux_preco[j], aux_preco[i]) || i > m)
    		a[k] = aux_preco[j--];

    	else
    		a[k] = aux_preco[i++]; 
    }
} 
  
/*l  --> Indice inicial,  r  --> Indice final*/
void mergeSort_preco(Produto arr[], int l, int r){ 

    if (l < r){ 
        
        int m = l+(r-l)/2; 
       
        mergeSort_preco(arr, l, m); 
        mergeSort_preco(arr, m+1, r); 
  
        merge_preco(arr, l, m, r); 
    } 
} 

int compara_descricao(Produto a,Produto b){

    return strcmp(a.desc,b.desc) < 0;
}

void merge_desc(Produto a[], int l, int m, int r){ 

    int i, j, k; 
    
    for (i = m + 1; i > l; i--) 
    	aux_desc[i - 1] = a[i - 1]; 

    for (j = m; j < r; j++) 
        aux_desc[r + m - j] = a[j + 1];

    for (k = l; k <= r; k++){

    	if (compara_descricao(aux_desc[j], aux_desc[i]) || i > m)
    		a[k] = aux_desc[j--];

    	else
    		a[k] = aux_desc[i++]; 
    }
} 
  
/*l  --> Indice inicial,  r  --> Indice final*/
void mergeSort_desc(Produto arr[], int l, int r){ 

    if (l < r){ 
  
        int m = l+(r-l)/2; 
        
        mergeSort_desc(arr, l, m); 
        mergeSort_desc(arr, m+1, r); 
  
        merge_desc(arr, l, m, r); 
    } 
} 

/******************************************************
*------------------FUNCOES AUXILIARES-----------------*
******************************************************/

/*Verifica se o produto atribuido existe na encomenda designada e devolve o indice do produto quer estes ja exista na encomenda (indice existente) quer nao (esse indice estara vazio, logo sera onde adicionamos o novo produto da encomenda)*/
int prod_existe_enc(int idp, int ide){

	int i;

	for (i = 0; i < todas_encomendas[ide].contador_prod_enc; i++){
		if (todas_encomendas[ide].produtos[i].idp == idp)
			return i;
	}

	return i;
}

/*----------------------COMANDOS---------------------*/

/* a */
/*Adiciona um novo produto ao sistema*/
void novo_prod(){

	Produto a;

	a.idp = idp;
	idp++;

	scanf(" %[^:]:%d:%d:%d\n", a.desc, &a.preco, &a.peso, &a.qnt);

	todos_produtos[a.idp] = a;

	printf("Novo produto %d.\n", a.idp);
}

/* q */
/*Adiciona stock a um produto existente no sistema*/
void adiciona_stock(){

	Produto p;
	int stock;

	scanf(" %d:%d", &p.idp, &stock);
	
	if (p.idp >= contador_prod)

		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", p.idp);
	
	else
		todos_produtos[p.idp].qnt += stock;	
}

/* N */
/*Cria uma nova encomenda*/
void nova_enc(){

	Encomenda e;

	e.ide = ide;
	ide++;

	e.peso_total_enc = 0;
	e.contador_prod_enc = 0;

	todas_encomendas[e.ide] = e;

	printf("Nova encomenda %d.\n", e.ide);
}

/* A */
/*Adiciona um produto a uma encomenda*/
void adic_prod_enc(){

	Encomenda e;
	Produto p;
	int qnt_prod, i;

	scanf(" %d:%d:%d", &e.ide, &p.idp, &qnt_prod);

	if (e.ide >= contador_enc)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", p.idp, e.ide);

	else if (p.idp >= contador_prod)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", p.idp, e.ide);

	else if (todos_produtos[p.idp].qnt < qnt_prod)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", p.idp, e.ide);

	else if (((todos_produtos[p.idp].peso * qnt_prod) + todas_encomendas[e.ide].peso_total_enc) > MAX_PROD_ENC)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", p.idp, e.ide);

	else {

		i = prod_existe_enc(p.idp, e.ide);

		if (i < todas_encomendas[e.ide].contador_prod_enc){

			todas_encomendas[e.ide].peso_total_enc += (todos_produtos[p.idp].peso * qnt_prod);

			todas_encomendas[e.ide].produtos[i].qnt += qnt_prod;

			/*Como estou a adicionar um produto (numa certa quantidade) proveniente do stock a encomenda, necessito de retirar esse mesmo valor ao stock*/
			todos_produtos[p.idp].qnt -= qnt_prod;
		}

		/*Caso o produto ainda nao exista na encomenda*/
		else {

			todas_encomendas[e.ide].peso_total_enc += (todos_produtos[p.idp].peso * qnt_prod);

			/*Adiciar produto a encomenda*/
			todas_encomendas[e.ide].produtos[i] = todos_produtos[p.idp];

			/*E neste passo que se associam os vetores "produtos" e "qnt_prod_enc"*/
			todas_encomendas[e.ide].produtos[i].qnt = qnt_prod;

			todas_encomendas[e.ide].contador_prod_enc++;

			/*Como se esta a adicionar um produto (numa certa quantidade) proveniente do stock a encomenda, necessita-se de retirar esse mesmo valor ao stock*/
			todos_produtos[p.idp].qnt -= qnt_prod;
		}
	}
}

/* r */
/*Remove stock a um produto existente*/
void remove_stock(){

	Produto p;
	int stock_retirar;

	scanf(" %d:%d", &p.idp, &stock_retirar);
	
	if (p.idp >= contador_prod)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", p.idp);

	else if (todos_produtos[p.idp].qnt < stock_retirar)
		 printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock_retirar, p.idp);

	else
		 todos_produtos[p.idp].qnt -= stock_retirar;
}

/* R */
/*Remove um produto de uma encomenda*/
void rem_prod_enc(){

	Encomenda e;
	Produto p;
	int i, j;

	scanf(" %d:%d", &e.ide, &p.idp);

	if (e.ide >= contador_enc)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", p.idp, e.ide);

	else if (p.idp >= contador_prod)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", p.idp, e.ide);
		
	else {

		i = prod_existe_enc(p.idp, e.ide);

		if (i < todas_encomendas[e.ide].contador_prod_enc){

		 	/*Como se esta a remover um produto da encomenda e necessario repor-se a quantidade deste no stock*/
			todos_produtos[p.idp].qnt += todas_encomendas[e.ide].produtos[i].qnt;

			/*Atualizar o peso total da encomenda*/
			todas_encomendas[e.ide].peso_total_enc -= (todos_produtos[p.idp].peso * todas_encomendas[e.ide].produtos[i].qnt);

			/*Remocao do produto da encomenda*/
			for (j = i; j < todas_encomendas[e.ide].contador_prod_enc - 1; j++)
				todas_encomendas[e.ide].produtos[j] = todas_encomendas[e.ide].produtos[j + 1];

			/*Como foi retirado um produto tem que se retirar um elemento ao contador*/
			todas_encomendas[e.ide].contador_prod_enc--;
			}
	}
}

/* C */
/*Calcula o custo de uma encomenda*/
void calcula_custo_enc(){

	Encomenda e;
	int preco_total = 0, i;

	scanf(" %d", &e.ide);

	if (e.ide >= contador_enc)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", e.ide);

	else {

		for (i = 0; i < todas_encomendas[e.ide].contador_prod_enc; i++)
			preco_total += (todos_produtos[todas_encomendas[e.ide].produtos[i].idp].preco * todas_encomendas[e.ide].produtos[i].qnt);

		printf("Custo da encomenda %d %d.\n", e.ide, preco_total);
	}
}

/* p */
/*Altera o preco de um produto existente no sistema*/
void altera_preco_prod(){

	Produto p;
	int preco_novo;

	scanf(" %d:%d", &p.idp, &preco_novo);

	if (p.idp >= contador_prod)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", p.idp);

	else
		todos_produtos[p.idp].preco = preco_novo;
}

/* E */
/*Retorna a descricao e a quantidade de um produto numa dada encomenda*/
void desc_qnt_prod_enc(){

	Encomenda e;
	Produto p;
	int i;

	scanf(" %d:%d", &e.ide, &p.idp);

	if (e.ide >= contador_enc)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", e.ide);

	else if (p.idp >= contador_prod)
		printf("Impossivel listar produto %d. Produto inexistente.\n", p.idp);
	
	/*Caso o produto exista na encomenda*/
	else {

		i = prod_existe_enc(p.idp, e.ide);

		if (i < todas_encomendas[e.ide].contador_prod_enc)
			printf("%s %d.\n", todas_encomendas[e.ide].produtos[i].desc, todas_encomendas[e.ide].produtos[i].qnt);	
		/*Caso o produto nao exista na encomenda*/
		else
			printf("%s %d.\n", todos_produtos[p.idp].desc, 0);
	}
}

/* m */
/*Retorna o identificador da encomenda em que um dado produto ocorre mais vezes*/
void enc_mais_prod(){

	Produto p;
	int j, i, qnt_mais_alta = 0; 
	int indice_qnt_mais_alta = -1; /*Comeca a -1 para nao interferir com os casos em que o indice vai permanecer no 0 (caso valido)*/

	scanf(" %d", &p.idp);

	if (p.idp >= contador_prod)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", p.idp);

	else {

		for (j = 0; j < contador_enc; j++){
			
			i = prod_existe_enc(p.idp, j);

			if ((i < todas_encomendas[j].contador_prod_enc) && (todas_encomendas[j].produtos[i].qnt > qnt_mais_alta)){

				qnt_mais_alta = todas_encomendas[j].produtos[i].qnt;
				indice_qnt_mais_alta = j; /*Guardar o indice da encomenda em que o produto ocorre mais vezes*/
			}
		}

		if (indice_qnt_mais_alta != -1)
			printf("Maximo produto %d %d %d.\n", p.idp, indice_qnt_mais_alta, qnt_mais_alta);
	}
}

/* l */
/*Lista todos os produtos existentes no sistema por ordem crescente de preco*/
void lista_produtos(){
	
	int i;
	Produto copia_lista_prod[MAX_PRODUTO];

	printf("Produtos\n");

	/*Efetua-se uma copia do vetor para quando for ordenado e impresso nao desordenar o vetor inicial*/
	for (i = 0; i < contador_prod; i++)
		copia_lista_prod[i] = todos_produtos[i];

	/*Listar todos os produtos existentes no sistema por ordem crescente de pre?o. Se houver 2 ou mais produtos com o mesmo pre?o, dever? imprimir esses por ordem crescente de identificador de produto*/
	mergeSort_preco(copia_lista_prod, 0, contador_prod - 1);

	for (i = 0; i < contador_prod; i++)
		printf("* %s %d %d\n", copia_lista_prod[i].desc, copia_lista_prod[i].preco, copia_lista_prod[i].qnt);
}

/* L */
/*Lista todos os produtos de uma encomenda por ordem alfabetica de descricao*/
void lista_prod_encomenda(){

	int i;
	Encomenda e;
	Produto copia_prod_enc[MAX_ENCOMENDA];

	scanf(" %d", &e.ide);

	if (e.ide >= contador_enc)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", e.ide);

	else {

		printf("Encomenda %d\n", e.ide);

		/*Efetua-se uma copia de cada um dos vetores para quando forem ordenados e impressos nao se desordenar os vetores iniciais*/
		for (i = 0; i < todas_encomendas[e.ide].contador_prod_enc; i++)
			copia_prod_enc[i] = todas_encomendas[e.ide].produtos[i];

		/*Listar todos os produtos de uma encomenda por ordem alfab?tica da descri??o e o vetor das quantidades (segundo a ordem do primeiro)*/
		mergeSort_desc(copia_prod_enc, 0, todas_encomendas[e.ide].contador_prod_enc - 1);

		for (i = 0; i < todas_encomendas[e.ide].contador_prod_enc; i++)
			printf("* %s %d %d\n", copia_prod_enc[i].desc, todos_produtos[copia_prod_enc[i].idp].preco, copia_prod_enc[i].qnt);
	}
}

/*-------------------FIM DE CODIGO-------------------*/