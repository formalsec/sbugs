#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PROD 10000
#define MAX_ENC 500
#define MAX_CARAC 64 /*a contar com o \0*/
#define Item Produto
#define key_p(A) A.preco
#define key_id(A) A.idp
#define key_desc(A) A.desc
#define less_p(A, B) (key_p(A) < key_p(B))
#define less_id(A, B) (key_id(A) < key_id(B))
#define less_desc(A, B) (strcmp(key_desc(A), key_desc(B)) < 0)
int flag_Ll = 0; /*indica se foi pedido o comando l ou L*/

/*definicao do tipo produto*/
typedef struct produto{
	int idp;
	char desc[MAX_CARAC];
	int preco;
	int peso;
	int qtd;
}Produto;

/*converte as varias informacoes num produto*/
Produto converte(int idp, char descricao[MAX_CARAC], int preco, int peso, int qtd){
	Produto produto;
	produto.idp = idp;
	strcpy(produto.desc, descricao);
	produto.preco = preco;
	produto.peso = peso;
	produto.qtd = qtd;
	return produto;
}

/*isola a descricao do produto numa string*/
const char* slicing_char(char a[]){
	char desc[MAX_CARAC];
	char* desc_f;
	int i, j = 0;
	/*isolar a descricao do comando e do espaco em branco que o segue*/
	for (i = 2; i < MAX_CARAC + 2; i++){
		desc[j] = a[i];
		j++;
	}
	desc_f = desc;
	return desc_f;
} 


/*isola e converte em inteiro a primeira informacao de um comando*/
int slicing_int(char a[]){
	int num;
	char desc[MAX_CARAC];
	strcpy(desc, slicing_char(a));
	num = atoi(desc);
	return num;
}

/*ordena um vetor por ordem crescente de preco ou alfabeticamente (conforme o comando)*/
void merge(Item a[], int l, int m, int r){
	int i, j, k;
	Item aux[MAX_PROD];
	/*construcao de vetor auxiliar*/
	for (i = m + 1; i > l; i--){
		aux[i - 1] = a[i - 1];
	}
	for (j = m; j < r; j++){
		aux[r + m - j] = a[j + 1];
	}
	/*se for o comando l*/
	if (flag_Ll == 1){
		/*ordenar os produtos por ordem crescente de preco*/
		for (k = l; k <= r; k++){
			if (less_p(aux[i], aux[j]) || j < m){
				a[k] = aux[i];
				i++;
			}
			else if (less_p(aux[j], aux[i]) || i > m){
				a[k] = aux[j];
				j--;
			}
			/*se o preco for o mesmo*/
			else {
				if (less_id(aux[i], aux[j]) || j < m){
					a[k] = aux[i];
					i++;
				}
				else {
					a[k] = aux[j];
					j--;
				}
			}
		}
	}
	/*se for o comando L*/
	else if (flag_Ll == 2){
		/*ordenar os produtos por ordem alfabetica*/
		for (k = l; k <= r; k++){
			if (less_desc(aux[i], aux[j]) || j < m){
				a[k] = aux[i];
				i++;
			}
			else {
				a[k] = aux[j];
				j--;
			}
		}
	}
}


/*algoritmo merge*/
void mergesort(Item a[], int l, int r){
	int m;
	if (l < r){
		m = (r + l) / 2;
		mergesort(a, l, m);
		mergesort(a, m + 1, r);
		merge(a, l, m, r);
	}
}

/*imprime varios elementos de uma lista*/
void print_vetor(Produto a[], int lim){
	int i;
	for (i = 0; i < lim; i++) {
		if (flag_Ll == 1){
			printf("* %s %i %i\n", a[i].desc, a[i].preco, a[i].qtd);
		}
		else if (flag_Ll == 2 && a[i].qtd != 0){
			printf("* %s %i %i\n", a[i].desc, a[i].preco, a[i].qtd);
		}
	}	
}


/*lista_enc: lista em que cada encomenda esta na posicao com indice igual ao seu id e eh uma lista de 
produtos, cada um na posicao com indice igual ao seu id*/
Produto lista_enc[MAX_ENC][MAX_PROD];

int main(){
	/*idp: indica o id do proximo produto a ser criado
	  ide: indica o id da proxima encomenda a ser criada
	  id_p: id de um produto
	  id_e: id de uma encomenda
	  max: quantidade maxima de um produto numa encomenda*/
	int arg2, arg3, arg4, i, idp = 0, id_p, id_e, ide = 0, preco, max, peso;
	/*arg1: comando, espaco em branco e descricao do produto
	  desc: descricao do produto ja isolada*/
	char arg1[MAX_CARAC + 2], desc[MAX_CARAC], comando;
	Produto produto, prod_enc;
	/*lista_prod: lista em que cada produto esta na posicao com indice igual ao seu id*/
	Produto lista_prod[MAX_PROD], lista_copia[MAX_PROD];
	scanf("%[^:\n]:%i:%i:%i", arg1, &arg2, &arg3, &arg4);
	comando = arg1[0];
	while (comando != 'x'){
		switch(comando){
			/*cria produto*/
			case 'a':
				strcpy(desc, slicing_char(arg1));
				produto = converte(idp, desc, arg2, arg3, arg4);
				printf("Novo produto %i.\n", idp);
				lista_prod[idp] = produto;
				idp++;
				break;
			/*adiciona stock ao produto*/
			case 'q':
				id_p = slicing_int(arg1);
				produto = lista_prod[id_p];
				if (idp <= id_p){
					printf("Impossivel adicionar produto %i ao stock. Produto inexistente.\n", id_p);
				}
				else {
					produto.qtd += arg2;
					lista_prod[id_p] = produto;
				}
				break;
			/*cria encomenda*/
			case 'N':
				printf("Nova encomenda %i.\n", ide) ;
				ide++;
				break;
			/*adiciona produto a encomenda*/
			case 'A':
				produto = lista_prod[arg2];
				id_e = slicing_int(arg1);
				peso = 0;
				/*calcula peso da encomenda antes de adicionar produto*/
				for (i = 0; i < idp; i++){
					prod_enc = lista_enc[id_e][i];
					peso += (prod_enc.peso * prod_enc.qtd);
				}
				if (ide <= id_e){
					printf("Impossivel adicionar produto %i a encomenda %i. Encomenda inexistente.\n", arg2, id_e);
				}
				else if (idp <= arg2){
					printf("Impossivel adicionar produto %i a encomenda %i. Produto inexistente.\n", arg2, id_e);
				}
				else if (arg3 > produto.qtd){
					printf("Impossivel adicionar produto %i a encomenda %i. Quantidade em stock insuficiente.\n", arg2, id_e);
				}
				else if ((peso + (arg3 * produto.peso)) > 200){
					printf("Impossivel adicionar produto %i a encomenda %i. Peso da encomenda excede o maximo de 200.\n", arg2, id_e);
				}
				/*se o produto ja existir na encomenda*/
				else if ((prod_enc = lista_enc[id_e][arg2]).qtd != 0){
					prod_enc.qtd += arg3;
					lista_enc[id_e][arg2] = prod_enc;
					produto.qtd = produto.qtd - arg3;
					lista_prod[arg2] = produto;
				}
				/*se o produto ainda nao existir na encomenda*/
				else {
					prod_enc = converte(arg2, produto.desc, produto.preco, produto.peso, arg3);
					lista_enc[id_e][arg2] = prod_enc;
					produto.qtd = produto.qtd - arg3;
					lista_prod[arg2] = produto;
				}
				break;
			/*remove stock ao produto*/
			case 'r':
				id_p = slicing_int(arg1);
				produto = lista_prod[id_p];
				if (idp <= id_p) {
					printf("Impossivel remover stock do produto %i. Produto inexistente.\n", id_p);
				}
				else if (produto.qtd < arg2){
					printf("Impossivel remover %i unidades do produto %i do stock. Quantidade insuficiente.\n", arg2, id_p);
				}
				else {
					produto.qtd -= arg2;
					lista_prod[id_p] = produto;
				}
				break;
			/*remove produto de encomenda*/
			case 'R':
				id_e = slicing_int(arg1);
				if (ide <= id_e){
					printf("Impossivel remover produto %i a encomenda %i. Encomenda inexistente.\n", arg2, id_e);
				}
				else if (idp <= arg2){
					printf("Impossivel remover produto %i a encomenda %i. Produto inexistente.\n", arg2, id_e);
				}
				else {
					produto = lista_enc[id_e][arg2];
					lista_prod[arg2].qtd += produto.qtd;
					produto.qtd = 0;
					lista_enc[id_e][arg2] = produto;
				}
				break;
			/*calcula custo da encomenda*/
			case 'C':
				id_e = slicing_int(arg1);
				preco = 0;
				if (ide <= id_e){
					printf("Impossivel calcular custo da encomenda %i. Encomenda inexistente.\n", id_e);
				}
				else {
					for (i = 0; i < idp; i++){
						produto = lista_enc[id_e][i];
						preco += produto.preco * produto.qtd;
					}
					printf("Custo da encomenda %i %i.\n", id_e, preco);
				}
				break;
			/*altera preco de produto*/
			case 'p':
				id_p = slicing_int(arg1);
				if (idp <= id_p){
					printf("Impossivel alterar preco do produto %i. Produto inexistente.\n", id_p);
				}
				else {
					/*altera preco do produto no sistema*/
					lista_prod[id_p].preco = arg2;
					/*altera preco do produto nas encomendas*/
					for (i = 0; i < ide; i++){
						lista_enc[i][id_p].preco = arg2;
					}
				}
				break;
			/*diz a descricao e quantidade de um produto numa encomenda*/
			case 'E':
				id_e = slicing_int(arg1);
				if (ide <= id_e){
					printf("Impossivel listar encomenda %i. Encomenda inexistente.\n", id_e);
				}
				else if (idp <= arg2){
					printf("Impossivel listar produto %i. Produto inexistente.\n", arg2);
				}
				else {
					strcpy(desc, lista_prod[arg2].desc);
					printf("%s %i.\n", desc, lista_enc[id_e][arg2].qtd);
				}
				break;
			/*retorn id da encomenda em que existe mais um produto e a sua quantidade*/
			case 'm':
				id_p = slicing_int(arg1);
				id_e = 0;
				max = 0;
				if (idp <= id_p){
					printf("Impossivel listar maximo do produto %i. Produto inexistente.\n", id_p);
				}
				else {
					for (i = 0; i < ide; i++){
						/*se um produto existe em maior quantidade numa encomenda do que noutra*/
						if (lista_enc[i][id_p].qtd != 0 && lista_enc[i][id_p].qtd > max){
							max = lista_enc[i][id_p].qtd;
							id_e = i;
						}
						/*se duas encomendas tiverem a mesma quantidade*/
						else if (lista_enc[i][id_p].qtd != 0 && lista_enc[i][id_p].qtd == max){
							if (id_e > i){
								id_e = i;
							}
						}
					}
					/*so retorna algo se o produto existir nalguma encomenda e existirem encomendas*/
					if (max != 0 && ide != 0){
						printf("Maximo produto %i %i %i.\n", id_p, id_e, max);
					}
				}
				break;
			/*lista os produtos do sistema por ordem crescente de preco*/
			case 'l':
				flag_Ll = 1;
				printf("Produtos\n");
				/*copia a lista de produtos para preservar os indices de cada produto*/
				for (i = 0; i < idp; i++){
					lista_copia[i] = lista_prod[i];
				}
				mergesort(lista_copia, 0, idp - 1);
				print_vetor(lista_copia, idp);
				flag_Ll = 0;
				break;
			/*lista os produtos de uma encomenda por ordem alfab?tica*/
			case 'L':
				id_e = slicing_int(arg1);
				if (ide <= id_e){
					printf("Impossivel listar encomenda %i. Encomenda inexistente.\n", id_e);
				}
				else {
					flag_Ll = 2;
					printf("Encomenda %i\n", id_e);
					/*copia a lista de uma encomenda para preservar o indice dos produtos*/
					for (i = 0; i < idp; i++){
						lista_copia[i] = lista_enc[id_e][i];
					}
					mergesort(lista_copia, 0, idp - 1);
					print_vetor(lista_copia, idp);
					flag_Ll = 0;
				}
				break;
		}
		scanf(" %[^:\n]:%i:%i:%i", arg1, &arg2, &arg3, &arg4);
		comando = arg1[0];
	}
	return 0;
}