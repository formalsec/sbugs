#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUTOS 10000           		/* maximo de produtos que pode existir */ 
#define MAX_DESCRICAO 64             		/* maximo de caracteres que a descri??o pode ter */
#define MAX_ENCOMENDAS 500           		/* maximo de encomendas que pode haver */
#define MAX_PESO 200                		/* peso maximo de cada encomenda */
#define MAX_PRODUTOS_ENCOMENDA 200   		/* maximo de produtos por encomenda*/
#define MAX_INPUT 1024             			/* tamanho maximo do input */

typedef struct produto{						/* estrutura que tem todas as caracteristicas de cada produto */
	char descricao[MAX_DESCRICAO];
	int preco;
	int peso;
	int stock;
	int idp;
} produto;

typedef struct encomenda{					/* estrutura que tem as caracteristicas de cada encomenda */
	int ide;
	int peso;
	produto info_produtos[MAX_PRODUTOS];	/* chama a estrutura produto para conseguir aceder ?s suas caracteristicas */
} encomenda;

produto catalogo_produtos[MAX_PRODUTOS];			/* catalogo_produto ? uma estrutura do tipo produto com maximo de produtos igual a 10000 */
encomenda catalogo_encomendas[MAX_ENCOMENDAS];		/* catalogo_encomendas ? uma estrutura do tipo encomenda com maximo de encomendas igual a 500 */
int proximo_produto = 0, run = 1;
int proxima_encomenda = 0;
char input[1024];

void adiciona_produto(){							/* funcao que adiciona produtos ao sistema */
	char auxiliar[4][64];
	int i = 0, j;

	char* corta;									/* leitura do input */
	corta = strtok(input, " ");						/* vai separar o input ate ao primeiro espaco*/
	while( corta != NULL ) {						/* vai separar o inoput cada vez que encontra*/
		corta = strtok(NULL, ":");
      	if (corta == NULL)
        	 break;
      	strcpy(auxiliar[i], corta);
      	i++;
   	}

   	for(j = 0; j < MAX_PRODUTOS; j++){				/* vai percorrer todos os produtos */
   		if(catalogo_produtos[j].idp == -1){			/* condicao usada para encontrar o produto que o input tem */
   			strcpy(catalogo_produtos[j].descricao, auxiliar[0]);
			catalogo_produtos[j].preco = atoi(auxiliar[1]);
			catalogo_produtos[j].peso = atoi(auxiliar[2]);
			catalogo_produtos[j].stock = atoi(auxiliar[3]);
			catalogo_produtos[j].idp = j;
			break;
		}
	}

	printf("Novo produto %d.\n", proximo_produto);									
}

void adiciona_stock(){							/* adiciona stock a produtos existentes */
	char auxiliar[2][64];
	int id, stock, i = 0;

	char* corta;
	corta = strtok(input, " ");
	while( corta != NULL ){
		corta = strtok(NULL, ":");
      	if (corta == NULL)
        	 break;
      	strcpy(auxiliar[i], corta);
      	i++;
   	}

	id = atoi(auxiliar[0]);						/* transforma a string em auxiliar 0 para um inteiro e a variavel id guarda esse valor */
	stock = atoi(auxiliar[1]);

	if(proximo_produto > id)					/* condicao para verificar que o produto existe no sistema */
		catalogo_produtos[id].stock += stock;
	else 
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
}

void cria_encomenda(){							/* cria encomenda no sistema */
	int i;

	for(i = 0; i < MAX_ENCOMENDAS; i++){		/* for usado para percorrer todas as encomendas */
		if(catalogo_encomendas[i].ide == -1){
			catalogo_encomendas[i].ide = i ;
			break;
		}
	}

	printf("Nova encomenda %d.\n", catalogo_encomendas[i].ide);

}

void adiciona_produto_encomenda(){				/* adiciona um produto a uma encomenda */
	char auxiliar[3][64];
	int id_encomenda, id_produto, quantidade, i = 0 , j;

	char* corta;
	corta = strtok(input, " ");
	while( corta != NULL ){
		corta = strtok(NULL, ":");
      	if (corta == NULL)
        	 break;
      	strcpy(auxiliar[i], corta);
      	i++;
   	}

	id_encomenda = atoi(auxiliar[0]);
	id_produto = atoi(auxiliar[1]);
	quantidade = atoi(auxiliar[2]);

	if (id_encomenda >= proxima_encomenda)								/* verifica se a encomenda existe no sistema */
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_produto, id_encomenda);
	else if (id_produto >= proximo_produto)								/* verifica se o produto existe no sitema */
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_produto, id_encomenda);
	else if (catalogo_produtos[id_produto].stock - quantidade < 0)		/* verififca se a quantidade de stock que se quer adicionar ? encomedna existe na quantidade no sistema */
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_produto, id_encomenda);
	else if (catalogo_encomendas[id_encomenda].peso + (quantidade * catalogo_produtos[id_produto].peso) > MAX_PESO)				/* verifica se o peso nao se exdece para alem do limite de 200 */
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_produto, id_encomenda);
	else{
		for( j = 0; j < MAX_PESO ; j++){
			if(catalogo_encomendas[id_encomenda].info_produtos[j].idp == -1){
				catalogo_encomendas[id_encomenda].info_produtos[j].stock = quantidade;
				catalogo_produtos[id_produto].stock -= quantidade;				/* ? tirado ao produto no sistema a quantidade que se adiciona na encomenda */
				catalogo_encomendas[id_encomenda].peso += quantidade * catalogo_produtos[id_produto].peso;		/* soma-se o o peso da encomenda ja existente com o peso do produto a multiplicar com a quantidade que se poe na encomenda */
				catalogo_encomendas[id_encomenda].info_produtos[j].idp = id_produto;
				break;
			}
			else if(catalogo_encomendas[id_encomenda].info_produtos[j].idp == id_produto){
				catalogo_encomendas[id_encomenda].info_produtos[j].stock += quantidade;
				catalogo_produtos[id_produto].stock -= quantidade;
				catalogo_encomendas[id_encomenda].peso += quantidade * catalogo_produtos[id_produto].peso;
				break;
			}
		}
	}
}

void remove_stock(){					/* remove stock de um produto existente no sistema */
	char auxiliar [2][64];
	int id, stock, i = 0;

	char* corta;
	corta = strtok(input, " ");
	while( corta != NULL ){
		corta = strtok(NULL, ":");
      	if (corta == NULL)
        	 break;
      	strcpy(auxiliar[i], corta);
      	i++;
   	}

	id = atoi(auxiliar[0]);
	stock = atoi(auxiliar[1]);

	if (proximo_produto > id){			/* verifica se o produto existe no sistema */
		if (catalogo_produtos[id].stock >= stock)
			catalogo_produtos[id].stock -= stock;
		else
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock, id);
	}
	else
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
}

void remove_produto_encomenda(){				/* remove procuto da encomenda */
	char auxiliar[2][64];
	int i = 0, id_encomenda, id_produto, j, contador = 0;

	char* corta;
	corta = strtok(input, " ");
	while( corta != NULL ){
		corta = strtok(NULL, ":");
      	if (corta == NULL)
        	 break;
      	strcpy(auxiliar[i], corta);
      	i++;
   	}

	id_encomenda = atoi(auxiliar[0]);
	id_produto = atoi(auxiliar[1]);

	if (catalogo_encomendas[id_encomenda].ide == -1)			/* verifica se a encomenda existe */
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_produto, id_encomenda);		
	else if (catalogo_produtos[id_produto].idp == -1)			/* verifica se o produto existe */
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_produto, id_encomenda);
	else{
		for( j = 0; j < MAX_PESO; j++){							
			if(catalogo_encomendas[id_encomenda].info_produtos[j].idp == id_produto){			/* vai verificar se o produto existe na encomenda que o input deu */
				catalogo_encomendas[id_encomenda].peso -= catalogo_encomendas[id_encomenda].info_produtos[j].stock *  catalogo_produtos[id_produto].peso;
				catalogo_produtos[id_produto].stock += catalogo_encomendas[id_encomenda].info_produtos[j].stock;
				catalogo_encomendas[id_encomenda].info_produtos[j].stock = 0;
			}
			else if(contador == MAX_PESO)
				printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_produto, id_encomenda);
			else
				contador++;
		}
	}
}

void custo_encomenda(){						/* calcula o custa da encomenda */
	char auxiliar[1][64];
	int i = 0, j , custo = 0;

	char* corta;
	getchar();
	while( corta != NULL ) {
		corta = strtok(NULL, " ");
      	if (corta == NULL)
        	 break;
      	strcpy(auxiliar[i], corta);
      	i++;
   	}

	if(catalogo_encomendas[atoi(auxiliar[0])].ide == -1)				/* verifica se a encomenda existe ou nao no sistema */
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", atoi(auxiliar[0]));
	else {
		for( j = 0; j < MAX_PESO; j++)
			custo += catalogo_encomendas[atoi(auxiliar[0])].info_produtos[j].stock * catalogo_produtos[j].preco;
		printf("Custo da encomenda %d %d.", atoi(auxiliar[0]), custo);
	}
}
      
void altera_preco(){					/* altera o preco a um procuto no sistema */
	char auxiliar [2][64];
	int id, novo_preco, i = 0;

	char* corta;
	while( corta != NULL ) {
		corta = strtok(NULL, ":");
      	if (corta == NULL)
        	 break;
      	strcpy(auxiliar[i], corta);
      	i++;
   	}

	id = atoi(auxiliar[0]);
	novo_preco= atoi(auxiliar[1]);

	if (proximo_produto > id)			/* verfifica se o produto existe no sistema */
		catalogo_produtos[id].preco = novo_preco;
	else 
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
}


void descricao_produto_encomenda(){

}

void id_encomenda(){
	
}

void lista_crescente(){

}

void lista_alfabetica(){

}


int main(){
	int i, j;
	for(i = 0; i < MAX_ENCOMENDAS; i++){
		for ( j = 0 ; j <MAX_PESO ; j++){
			catalogo_encomendas[i].info_produtos[j].idp = -1;
			catalogo_encomendas[i].ide = -1;
		}
	}
	for (i = 0; i < MAX_PRODUTOS; i++){
		catalogo_produtos[i].idp = -1;
	}
		while(run){
		fgets(input, MAX_INPUT, stdin);
		switch (input[0]){
			case 'a':
				adiciona_produto();
				proximo_produto++;
				break;
			case 'q':
				adiciona_stock();
				break;
			case 'N':
				cria_encomenda();
				proxima_encomenda++;
				break;
			case 'A':
				adiciona_produto_encomenda();
				break;
			case 'r':
				remove_stock();
				break;
			case 'R':
				remove_produto_encomenda();
				break;
			case 'C':
				custo_encomenda();
				break;
			case 'p':
				altera_preco();
				break;
			case 'E':
				descricao_produto_encomenda();
				break;
			case 'm':
				id_encomenda();
				break;
			case 'l':
				lista_crescente();
				break;
			case 'L':
				lista_alfabetica();
				break;
			case 'x':
				run = 0;
				break;
		}
	}
	return 0;
}