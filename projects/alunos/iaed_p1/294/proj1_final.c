#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define linhas_encomendas 500
#define colunas_encomendas 201
#define n_produtos 10000
#define string_produto 64
#define maxpeso 200

/* Estrutura do tipo produto. */
typedef struct{ 
		/* identificador do produto do tipo inteiro. */
    	int identificador;
    	/* descricao do produto do tipo string (vector de caracteres). */  
    	char descricao[string_produto];    	
    	/* preco do produto do tipo inteiro. */
    	int preco;	
    	/* peso do produto do tipo inteiro. */
    	int peso;
    	/* quantidade do produto existente no sistema do tipo inteiro. */
    	int quantidade_stock;
    	/* vector com dimensao maxima das linhas das encomendas onde guarda o valor 
    	da quantidade que e inserida numa encomenda. */
    	int quantidade_encomenda[linhas_encomendas];
} Product;

/* Cria um vetor de 10000 produtos. */	
Product produto[n_produtos];

/* Tabela bidimensional com dimensao de 500*201 onde na coluna 0 esta o ide da 
encomenda e a frente estao os idps dos produtos que fazem parte da encomenda. */ 
int encomendas[linhas_encomendas][colunas_encomendas];

/* Variavel global que conta quantos produtos foram introduzidos no programa. */
int idp_a;
/* Variavel global que conta quantas encomendas foram introduzidas no programa. */
int ide_N;

/* Vetor auxiliar a ser usada no mergeSort. */
Product aux_comando_l[n_produtos];

Product produtos_comando_l[n_produtos];

/* Funcao que adiciona um novo produto ao sistema. */ 
void comando_a(){
	char descricao[string_produto];
	int preco,peso,qtd;

	scanf(" %[^:]:%d:%d:%d",descricao,&preco,&peso,&qtd);
    
   	produto[idp_a].identificador = idp_a;
	strcpy(produto[idp_a].descricao , descricao);
	produto[idp_a].preco = preco;
	produto[idp_a].peso = peso;
	produto[idp_a].quantidade_stock = qtd;

	printf("Novo produto %d.\n", produto[idp_a].identificador);
	idp_a++;
}

/* Funcao que adiciona stock a um produto existente. */
void comando_q(){
	int idp,qtd;

	scanf(" %d:%d",&idp,&qtd);

	/* Verifica se algum produto ja foi adiciona ao sistema. */
	if(idp < idp_a){
		produto[idp].quantidade_stock += qtd;
	}

	else{
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	}
}

/* Funcao que cria um nova encomenda. */
void comando_N(){

	encomendas[ide_N][0] = ide_N;
	printf("Nova encomenda %d.\n", encomendas[ide_N][0]);
	ide_N++;
}

/* Funcao que adiciona um produto a uma encomenda. Se o produto ja existir na 
encomenda, adiciona a nova quantidade a quantidade existente. */
void comando_A(){
	int iden,idprod,quant;
	int peso_encomenda = 0;
	int i;
	int p;


	scanf(" %d:%d:%d",&iden,&idprod,&quant);
	/* Verifica se alguma encomenda ja foi adicionada ao sistema. */
	if (iden < ide_N){
		/* Verifica se algum produto ja foi adicionado ao sistema. */
		if (idprod < idp_a){
			/* Verifica se a quantidade de um produto inserida pelo usuario 
			e menor ou igual a  sua quantidade existente em stock. */
			if (quant <= produto[idprod].quantidade_stock){
				for (i = 1; i < colunas_encomendas; i++) {
					/* Verifica se existe algum idp que nao seja zero 
					na linha da encomenda ide. */
					if (encomendas[iden][i] != 0) {
						peso_encomenda += produto[encomendas[iden][i]].peso * produto[encomendas[iden][i]].quantidade_encomenda[iden];
					}
				}
				/* Verifica se existe o produto de idp zero na encomenda ide. */
				if (produto[0].quantidade_encomenda[iden] != 0) {
					peso_encomenda += produto[0].quantidade_encomenda[iden] * produto[0].peso;
				}
				/* Verifica se o peso da encomenda com o novo produto excede 
				o maximo do peso aceite. */
				if (peso_encomenda + produto[idprod].peso * quant <= maxpeso){
					/* Verifica se a quantidade do produto idp na encomenda ide 
					e zero. */
					if (produto[idprod].quantidade_encomenda[iden] == 0) {
						for (p = 1; p < colunas_encomendas; p++){
							if (encomendas[iden][p] == 0) {
								encomendas[iden][p] = produto[idprod].identificador;
								break;
							} 
						}
					}
					/* Atualizacao da quantidade de stock e da encomenda 
					do produto */
					produto[idprod].quantidade_stock -= quant;
					produto[idprod].quantidade_encomenda[iden] += quant;
				}
				else{
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idprod,iden);
				}
			}
			else{
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idprod,iden);
			}				
		}
		else{
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idprod,iden);
		}
	}
	else{
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idprod,iden);
	}
}

/* Funcao que remove stock a um produto existente. */
void comando_r(){
	int idp;
	int qtd;

	scanf(" %d:%d",&idp,&qtd);
	/* Verifica se algum produto ja foi adicionado ao sistema. */
	if (idp < idp_a){
		/* Verifica se a quantidade de um produto inserida pelo usuario 
			e menor ou igual a  sua quantidade existente em stock. */
		if (qtd <= produto[idp].quantidade_stock){
			/* Remove a quantidade do produto inserida pelo usuario a 
			existente no sistema. */
			produto[idp].quantidade_stock -= qtd;		
		}
		else{
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd,idp);
		}
	}
	else{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	}
}

/* Funcao que remove um produto de uma encomenda. */
void comando_R(){
	int ide,idp,i,j;
	int colunas_encomendas_R = 201;

	scanf(" %d:%d", &ide,&idp);
	/* Verifica se alguma encomenda ja foi adicionada ao sistema. */
	if (ide < ide_N){
		/* Verifica se algum produto ja foi adicionado ao sistema. */
		if (idp < idp_a){
			for (i = 1; i <= colunas_encomendas_R; i++)
				/* Verifica se o idp do produto inserido pelo usuario esta presente 
				na linha da encomenda ide. */
				if (idp == encomendas[ide][i])
					break;
			if (i < colunas_encomendas_R){
			 	colunas_encomendas_R -= 1;
			 	for (j = i; j < colunas_encomendas_R; j++){
			 		encomendas[ide][j] = encomendas[ide][j+1];
				}
				encomendas[ide][j] = 0;
				produto[idp].quantidade_stock += produto[idp].quantidade_encomenda[ide];
				produto[idp].quantidade_encomenda[ide] = 0;
			}
		}	 		 	
		else{
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp,ide);
		}
	}
	else{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp,ide);
	}
}

/* Funcao que calcula o custo de uma encomenda. */
void comando_C(){
	int ide;
	int preco_encomenda = 0;
	int i;
	

	scanf(" %d",&ide);
	/* Verifica se alguma encomenda ja foi adicionada ao sistema. */
	if (ide < ide_N){
		for (i = 1; i < colunas_encomendas; i++){
			/* Verifica se existe algum idp que nao seja zero 
			na linha da encomenda ide. */
			if (encomendas[ide][i] != 0){
				preco_encomenda += produto[encomendas[ide][i]].preco * produto[encomendas[ide][i]].quantidade_encomenda[ide];
			}
		}
		/* Verifica se existe o produto de idp zero na encomenda ide. */
		if (produto[0].quantidade_encomenda[ide] != 0){
			preco_encomenda += produto[0].preco * produto[0].quantidade_encomenda[ide];
		}
		printf("Custo da encomenda %d %d.\n", ide,preco_encomenda);
	}
	else{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	}	
}

/* Funcao que altera o preco de um produto existente no sistema. */
void comando_p(){
	int idp,novo_preco;

	scanf(" %d:%d",&idp,&novo_preco);
	/* Verifica se algum produto ja foi adicionado ao sistema. */
	if (idp < idp_a){
		/* Atualiza o preco do produto de identificador idp introduzido pelo usuario 
		pelo preco que e lido no terminal. */
		produto[idp].preco = novo_preco;	
	}
	else{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	}
}

/* Funcao que lista a descricao e a quantidade de um produto numa encomenda. */
void comando_E(){
	int ide,idp,i;

	scanf(" %d:%d",&ide,&idp);
	/* Verifica se alguma encomenda ja foi adicionada ao sistema. */
	if (ide < ide_N){
		/* Verifica se algum produto ja foi adicionado ao sistema. */
		if (idp <idp_a){
			for (i = 1; i <= colunas_encomendas; i++){
				/* Percorre a linha da encomenda ide ate encontrar o idp 
				correspondente ao inserido pelo usuario. Quando isso acontecer faz 
				break e printf for do ciclo for. */
				if (idp == encomendas[ide][i]){
					break;				
				}
			}
			printf("%s %d.\n", produto[idp].descricao,produto[idp].quantidade_encomenda[ide]);
		}
		else{
			printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
		}
	}
	else{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
}

/* Funcao que lista o identificador da encomenda em que o produto dado ocorre mais 
vezes. Se houver 2 ou mais encomendas nessa situacao, devera imprimir a encomenda 
de menor ide. */
void comando_m(){
	int idp,i;
	int maior = 0;
	int controlo_m = -1;
	int ind_encomenda = 0;

	scanf(" %d",&idp);
	/* Verifica se algum produto ja foi adicionado ao sistema. */
	if (idp < idp_a){
		/* Verifica se existe alguma encomenda no sistema. */
		if (ide_N != 0){
			for (i = 0; i < linhas_encomendas; i++){
				/* Percorre o vetor ate encontrar uma quantidade do 
				produto idp no indice i que nao seja zero. E assim muda a variavel 
				local para 0 para detetar que a condicao verificou-se. */
				if (produto[idp].quantidade_encomenda[i] != 0){
					controlo_m = 0;
					/* Verifica se a variavel local maior e menor que a quantidade 
					do produto idp da encomenda i. */
					if (maior < produto[idp].quantidade_encomenda[i]){
			    		maior = produto[idp].quantidade_encomenda[i];
			    		ind_encomenda = i;
		    		}
    			}
    		}
			if (controlo_m != -1){
				printf("Maximo produto %d %d %d.\n", idp,ind_encomenda,maior);
			}     
		}
	}	
	else{
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	}
}

/* Funcao para ordenar um vetor usando merge sort */
/* Mescla os dois subvetores de vet[]. */ 
/* Primeiro subvetor e vet[l..m] */
/* Segundo subvetor e vet[m+1..r] */
void merge(Product aux_comando_l[], Product vet[], int l, int m, int r){ 
    int i, j, k; 
  
    /* Copiar data para o vetor temporario */
    for (i = m + 1; i > l; i--){ 
        aux_comando_l[i - 1] = vet[i - 1]; 
    }
    for (j = m; j < r; j++){
        aux_comando_l[r + m - j] = vet[j + 1]; 
    }
    for (k = l; k <= r; k++){
    	if (aux_comando_l[j].preco < aux_comando_l[i].preco || i > m){
    		vet[k] = aux_comando_l[j--];
    	}
    	else{
    		vet[k] = aux_comando_l[i++];
    	}
    } 
} 
  
  
 /* l e para o indice esquerdo e r e para o indice direito do 
   subvetor do vetor a ser ordenado */
void mergeSort(Product aux_comando_l[], Product arr[], int l, int r){
	
	/* O mesmo para (l+r)/2, mas evita overflow for */
    /* large l e h */
    int m = (r + l) / 2;

    if (r <= l){
    	return;
    } 
        
    /* Ordena primeira e segunda metades */
    mergeSort(aux_comando_l, arr, l, m); 
    mergeSort(aux_comando_l, arr, m + 1, r); 

    merge(aux_comando_l, arr, l, m, r); 
    
} 

/* Funcao que lista todos os produtos existentes no sistema por ordem crescente de
preco. Se houver 2 ou mais produtos com o mesmo preco, devera imprimir esses por ordem 
crescente de id de produto. */

void comando_l(){
	int p,e;

		printf("Produtos\n");

		for (p = 0; p < idp_a ; p++){
			produtos_comando_l[p].identificador = produto[p].identificador;
			produtos_comando_l[p].preco = produto[p].preco;
			strcpy(produtos_comando_l[p].descricao, produto[p].descricao);
			produtos_comando_l[p].quantidade_stock = produto[p].quantidade_stock;
		} 

		mergeSort(aux_comando_l, produtos_comando_l,0, idp_a - 1);

		for (e = 0; e < idp_a ; e++){
			printf("* %s %d %d\n", produtos_comando_l[e].descricao, produtos_comando_l[e].preco, produtos_comando_l[e].quantidade_stock);
		}
}


/* Menu do sistema. */
int main(){
	char letra;
	while(1){
		scanf("%c",&letra);
    	switch (letra){
			case 'N':
				comando_N();
				break;
			case 'A':
				comando_A();
				break;
			case 'R':
				comando_R();
				break;
			case 'C':
				comando_C();
				break;	
			case 'E':
				comando_E();
				break;
			/* case 'L':
				comando_L();
				break; */
			case 'a':
				comando_a();    
				break;
			case 'q':
				comando_q();
				break;
			case 'r':
				comando_r();
				break;
			case 'p':
				comando_p();
				break;
			case 'm':
				comando_m();
				break;
			case 'l':
				comando_l();
				break;
			case 'x':
				return 0;
			default:
				break;
    	}
	    scanf("\n");
	}
}
