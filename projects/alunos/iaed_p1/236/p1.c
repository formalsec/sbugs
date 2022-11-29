#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Constantes a usar no programa*/
#define MAX_C 64
#define MAX_PRODUTO 10000
#define MAX_ENCOMENDA 500
#define MAX_PESO 200
#define MAX_INPUT 1024


/*Estrutura do produto, com a descricao inicializada a VAZIO*/
typedef struct {
	int idProd;
	char descricao[MAX_C];	
	int preco;
	int peso;
	int quantidade;
} Produto;

/*Estrutura da encomenda*/
typedef struct{
	int idEnc;
	int peso;
	Produto product[MAX_PRODUTO];	
} Encomenda;


/* Prototipos */
void add_produto(char[], Produto[MAX_PRODUTO]);
void add_qtd(char[], Produto[MAX_PRODUTO]);
void new_encomenda(Encomenda[MAX_ENCOMENDA]);
void add_encomenda(char[], Encomenda[MAX_ENCOMENDA], Produto[MAX_PRODUTO]);
void remove_qtd(char[], Produto[MAX_PRODUTO]);
void remove_produto(char[], Encomenda[MAX_ENCOMENDA], Produto[MAX_PRODUTO]);
void calc_custo(char[], Encomenda[MAX_ENCOMENDA]);
void altera_preco(char[], Produto[MAX_PRODUTO]);
void lista_descricao(char[], Encomenda[MAX_ENCOMENDA], Produto[MAX_PRODUTO]);
void listar_produto(Produto[MAX_PRODUTO]);




/* Funcoes Auxiliares */
int check_idProd(int, Produto[MAX_PRODUTO], int);
int check_idEnc(int, Encomenda[MAX_ENCOMENDA], int);
int check_peso(int, int);
void produto_vazio(Produto[MAX_PRODUTO]);
void ordena_produto(Produto[MAX_INPUT], int);
void print_infoP(Produto[MAX_INPUT], int);



int main(){
	int running = 1;
	char command = '0', input[MAX_INPUT];

	Produto prod[MAX_PRODUTO];
	Encomenda enc[MAX_ENCOMENDA];

	produto_vazio(prod);

	while(running == 1){
		fgets(input, MAX_INPUT, stdin);

		command = input[0];

		switch(command){
			case 'a': add_produto(input, prod);	
				break;
			
			case 'q': add_qtd(input, prod);
				break;
			
			case 'N': new_encomenda(enc);
				break;
			
			case 'A': add_encomenda(input, enc, prod);
				break;

			case 'r': remove_qtd(input, prod);
				break;

			case 'R': remove_produto(input, enc, prod);
				break;

			case 'C': calc_custo(input, enc);
				break;

			case 'p': altera_preco(input, prod);
				break;

			case 'E': lista_descricao(input, enc, prod);
				break;

			case 'l': listar_produto(prod);
				break;

			case 'x': running = 0;
				break;

			default: printf("Invalid command\n");
		}
	}
	return 0;
}


/* Funcao auxiliar responsavel pela verificacao do id do produto*/
int check_idProd(int idProd, Produto prod[MAX_PRODUTO], int sinal){
	int i;
	for(i = 0; i < MAX_PRODUTO; i++){
		if(idProd == prod[i].idProd){
			return sinal = 1;
		}	
	}	
  return sinal = 0;
}

/* Funcao auxiliar responsavel pela verificacao do id da encomenda*/
int check_idEnc(int idEnc, Encomenda enc[MAX_ENCOMENDA], int sinal){
	int i;
	for(i = 0; i < MAX_ENCOMENDA; i++){
		if(idEnc == enc[i].idEnc){
			return sinal = 1;
		}	
	}	
	return sinal = 0;
}

/*Funcao auxiliar para verificar se o peso introduzido na encomenda ultrapassa o valor maximo possivel*/
int check_peso(int peso, int sinal){
	int i;
	for (i = 0; i < MAX_ENCOMENDA; i++){
		if(peso > MAX_PESO)
			return sinal = 0;
	}
	return sinal = 1;
}

/*
---Funcao para inicializar todos os produtos vazios da lista de produtos
---Retorna: void
*/
void produto_vazio(Produto prod[MAX_PRODUTO]){
	int i;
	for(i = 0; i < MAX_PRODUTO; i++)
		strcpy(prod[i].descricao, "VAZIO");
}

/* Funcao responsavel pela troca de posicoes dos produtos na lista*/
void ordena_produto(Produto aux[MAX_INPUT], int n){
	Produto save;

	save = aux[n];

	aux[n] = aux[n-1];
	
	aux[n-1] = save;
}


/*
---Funcao que adiciona produtos a lista de produtos
---Retorna: mensagem com o id do produto
*/
void add_produto(char input[], Produto prod[MAX_PRODUTO]){
	Produto new; /*Para guardar o produto a ser introduzido na lista*/
	int i;

	sscanf(input, "%*c %[^:]:%d:%d:%d", new.descricao, &new.preco, &new.peso, &new.quantidade);

	for(i = 0; i < MAX_PRODUTO; i++){
		if(strcmp(prod[i].descricao, "VAZIO") == 0){ /*Verifica que nao ha produtos na posicao*/
			prod[i] = new; /*Atualiza a lista de produtos*/
			printf("Novo Produto %d.\n", new.idProd);
			break;
		}
	}
}

/*
---Funcao que adiciona stock a um produto existente
---Retorna: void
*/
void add_qtd(char input[], Produto prod[MAX_PRODUTO]){
	int qtd, sinal = 0, idp, i;
	

	sscanf(input, "%d:%d", &idp, &qtd);
	
	sinal = check_idProd(idp, prod, sinal);
	if(sinal == 0){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	}

	for (i = 0; i < MAX_PRODUTO; i++){
		if(prod[i].idProd == idp)
			prod[i].quantidade += qtd;
	}
}


/*
---Funcao que cria um encomenda inicialmente vazia
---Retorna: mensagem com o id da encomenda
*/
void new_encomenda(Encomenda enc[MAX_ENCOMENDA]){
	int i;
	Encomenda new;
	memset(&new, 0, sizeof new); /*inicializar os parametros a 0*/

	for(i = 0; i < MAX_ENCOMENDA; i++){
		enc[i] = new;
		new.idEnc = i;
		printf("Nova encomenda %d.\n", new.idEnc);
		break;
	}	
}


/*
---Funcao que adiciona produtos a uma
---Retorna: void
*/
void add_encomenda(char input[], Encomenda enc[MAX_ENCOMENDA], Produto prod[MAX_PRODUTO]){
	int ide, idp, qtd, sinalE = 0, sinalP = 0, peso_aux, cp, i, j, k;

	sscanf(input, "%d:%d:%d", &ide, &idp, &qtd);


	/*verificar se os ids introduzidos estao corretos*/
	sinalE = check_idEnc(ide, enc, sinalE);
	if(sinalE == 0)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

	sinalP = check_idProd(idp, prod, sinalP);
		if(sinalP == 0)
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	
	for(i = 0; i < MAX_ENCOMENDA; i++){
		if(enc[i].idEnc == ide){ /* verificar se o produto ja existe na encomenda e adicionar stock */
			for (k = 0; k < MAX_PRODUTO; k++){				
				if(enc[i].product[k].idProd == idp)
					enc[i].product[k].quantidade += qtd; /* atualizar a quantidade da encomenda */
			}
			for(j = 0; j < MAX_PRODUTO; j++){
				if(prod[j].idProd == idp){
					peso_aux = prod[j].peso;
					if(prod[j].quantidade >= qtd){ /*verificar se a quantidade que pretendemos indroduzir nao ultrapassa a quantidade disponivel*/
						enc[i].product[j] = prod[j]; 
						prod[j].quantidade -= qtd; /* atualizar o stock disponivel do produto */
					}
					else if(prod[j].quantidade < qtd)
						printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
					
					cp = check_peso(peso_aux, cp); /* verificar se ao introduzir o produto na encomenda nao ultrapassa o peso maximo de uma encomenda */
					if(cp == 1){
						int pt = enc[i].peso;
						pt += peso_aux;
						if(pt > MAX_PESO)
							printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
					
						else if(cp != 1)
							enc[i].peso = pt; /* atualizar o peso da encomenda */
					}
				}
			}
		}
	}
}


/*
---Funcao que remove stock a um produto existente
---Retorna: void
*/
void remove_qtd(char input[], Produto prod[MAX_PRODUTO]){
	int idp, qtd, sinal = 0, i;

	sscanf(input, "%d:%d", &idp, &qtd);

	sinal = check_idProd(idp, prod, sinal); 
	if(sinal == 0)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);

	for(i = 0; i < MAX_PRODUTO; i++){
		if(prod[i].idProd == idp){
			if(prod[i].quantidade >= qtd) /* verifica se e possivel remover a quantidade de produtos desajada */
				prod[i].quantidade -= qtd;

			else
				printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
		}
	}
}


/*
---Funcao que remove um produto de uma encomenda
---Retorna: void
*/
void remove_produto(char input[], Encomenda enc[MAX_ENCOMENDA], Produto prod[MAX_PRODUTO]){
	int ide, idp, sinalE = 0, sinalP = 0, i, j;

	sscanf(input, "%d:%d", &ide, &idp);

	sinalE = check_idEnc(ide, enc, sinalE);
	if(sinalE == 0)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

	sinalP = check_idProd(idp, prod, sinalP);
	if(sinalP == 0)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

	for(i = 0; i < MAX_ENCOMENDA; i++){
		if(enc[i].idEnc == ide){
			for(j = 0; j < MAX_PRODUTO; j++){ /* procurar o produto na encomenda e remover */
				if(enc[i].product[j].idProd == idp){
					enc[i].product[j] = enc[i].product[j+1];
				}
			}
		}
	}
}


/*
---Funcao que calcula o custo de uma encomenda
---Retorna: o valor total da encomenda
*/
void calc_custo(char input[], Encomenda enc[MAX_ENCOMENDA]){
	int ide, sinal = 0, i, j, total;

	sscanf(input, "%d", &ide);

	sinal = check_idEnc(ide, enc, sinal);
	if(sinal == 0)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);

	for(i = 0; i < MAX_ENCOMENDA; i++){
		if(enc[i].idEnc == ide){
			for(j = 0; j < MAX_PRODUTO; j++){/* procurar o preco dos diferentes produtos na encomenda e guardar na variavel total */
				total += enc[i].product[j].preco;
			}
		}
	}
	printf("Custo da encomenda %d %d.\n", ide, total);
}


/*
---Funcao que altera o preco de um produto
---Retorna: void
*/
void altera_preco(char input[], Produto prod[MAX_PRODUTO]){
	int idp, novo_preco, i, sinal = 0;

	sscanf(input, "%d:%d", &idp, &novo_preco);

	sinal = check_idProd(idp, prod, sinal);
	if(sinal == 0)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);

	for(i = 0; i < MAX_PRODUTO; i++){/* procurar o produto na lista e alterar pelo valor desejado */
		if(prod[i].idProd == idp)
			prod[i].preco = novo_preco;
	}
}


/*
---Funcao que organiza a lista de produtos pela descricao dos diferentes produtos
---Retorna: o produto e a sua quantidade em stock
*/
void lista_descricao(char input[], Encomenda enc[MAX_ENCOMENDA], Produto prod[MAX_PRODUTO]){
	int ide, idp, sinalE = 0, sinalP = 0, qtd, i, j;
	char nome[MAX_C] = "";

	sscanf(input, "%d:%d", &ide, &idp);

	sinalE = check_idEnc(ide, enc, sinalE);
	if(sinalE == 0)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

	sinalP = check_idProd(idp, prod, sinalP);
	if(sinalP == 0)
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);


	for(i = 0; i < MAX_ENCOMENDA; i++){
		if(enc[i].idEnc == ide){
			for(j = 0; j < MAX_PRODUTO; j++){
				if(enc[i].product[j].idProd == idp){
					strcpy(nome, enc[i].product[j].descricao);
					qtd = enc[i].product[j].quantidade;

				}
			}
		}
	}
	printf("%s %d\n", nome, qtd);
}


/*
---Funcao que que organiza a lista de produtos por ordem crescente do preco
---Retorna: o nome do produto o seu preco e a quantidade em stock 
*/

void listar_produto(Produto prod[MAX_PRODUTO]){

	int i, l = 0;

	Produto aux[MAX_PRODUTO];


	for(i = 0; i < MAX_PRODUTO; i++){
		if(strcmp(prod[i].descricao, "VAZIO") != 0){
			aux[l] = prod[i];
			l++;
		}
	}

	print_infoP(aux, l);
}

/* Funcao auxiliar responsavel por imprimir os produtos*/
void print_infoP(Produto aux[MAX_INPUT], int l){
	int n, i, preco, max_preco, id, max_id;

	for(i = 1; i < l; i++){
		n = i;

		while(n > 0){
			preco = aux[n].preco;
			max_preco = aux[n-1].preco;

			id = aux[n].idProd;
			max_id = aux[n-1].idProd;

			if(preco > max_preco){
				ordena_produto(aux, n);
				n--;
			}

			if(preco == max_preco && id > max_id){ /* caso o preco seja igual esses produtos sao organizados por ordem crescente de id */
				ordena_produto(aux, n);
				n--;
			}

			break;
		}
	}
	printf("Produtos\n");
	for(i = 0; i < l; i++){
		printf("* %s %d %d em stock\n", aux[i].descricao, aux[i].preco, aux[i].quantidade);
	}
}
