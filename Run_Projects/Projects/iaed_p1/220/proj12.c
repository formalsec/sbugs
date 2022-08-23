#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/****************************************************************************/
/**************************** Definicao de constantes ***********************/
/****************************************************************************/

#define NPROD 10000 
#define NENCOMENDAS 500
#define PESOENCOMENDA 200


/****************************************************************************/
/*************************** Prototipo de funcoes ***************************/
/****************************************************************************/

void adiciona_produto(); 
void add_stock();
void remove_stock_produto();
void altera_preco_prod();
/*void preco_prod_cresc();*/
void nova_encomenda();
void sair();

/****************************************************************************/
/*********** Declaracao das estruturas Produto e Encomenda  *****************/
/****************************************************************************/

typedef struct{
	int ProductInd[NPROD];
	char descricao[63];
	int preco;
	int peso;
	int qtd;
}Produto;

typedef struct{
	int EncomendaInd[NENCOMENDAS];
	int ide;
	int peso;
	Produto prod;
}Encomenda;


/*****************************************************************************/
/********************** Declaracao de variaveis globais **********************/
/*****************************************************************************/

int ProductInd = 0;       /* Indice de produtos - conta quantos ha */
int EncomendaInd = 0;     /* Indice de encomendas - conta quantos ha */
Produto prod[NPROD];     /*defini?ao de vetor Tipo Produto, nome produtos*/
Encomenda encomenda[NENCOMENDAS]; /*defini?ao de vetor Tipo Encomendas, nome encomendas*/




/****************************************************************************/
/*********************************** Main ***********************************/
/****************************************************************************/


int main(){

	int ProductInd = 0;
	char descricao[63];
	int preco, peso, qtd;
	int qtd_n;


	char menu;

	while (1) {
		menu = getchar();											 /* le o comando */ 
		switch (menu){

		case 'a': 
			scanf("%s:%d:%d:%d", descricao,&preco ,&peso, &qtd);
			adiciona_produto();           							/* Executa comando a */ 
			break;

		case 'q': 
			scanf("%d:%d", &ProductInd, &qtd_n);
			add_stock();                  							/* Executa comando q */ 
			break;
		case 'r': 
			scanf("%d:%d", &ProductInd, &qtd_n);
			remove_stock_produto();       							/* Executa comando r */ 
			break;
		case 'P':
			scanf("%d:%d",&	ProductInd,&preco);
			altera_preco_prod();		  							/* Executa comando P */ 
			break;
		/*case 'l':*/
			/*preco_prod_cresc();*/		 							/* Executa comando l */ 
			/*break;*/
		case 'N':
			nova_encomenda();
			break;
		/*case 'A':*/
			/*scanf("%d:%d:%d", &ProductInd,&EncomendaInd, &qtd);*/
			/*add_prod_encomenda();	*/								/* Executa comando A */ 
			/*break;*/
		case 'x': 
			exit(0);											 	/* Termina o programa com sucesso */
		default:
			printf("ERRO: Comando desconhecido \n");		
	    }
	
	    getchar(); 													/* Le o '\n' introduzido pelo utilizador */

	}

	return 0;
} 


/****************************************************************************/
/****************************** Implementacao *******************************/
/****************************************************************************/

void adiciona_produto(char* descricao, int preco, int peso, int qtd){


		if (ProductInd != NPROD){
			strcpy(prod[ProductInd].descricao, descricao);
			prod[ProductInd].preco = preco;
			prod[ProductInd].peso = peso;
			prod[ProductInd].qtd = qtd;

		}
		printf("Novo produto %d.\n", ProductInd);
		ProductInd++;	
	
}


void add_stock(int ProductInd, int qtd_n){

	/*int qtd_n = 0;*/

	if ( ProductInd > 9999){

		printf(" Impossivel adicionar produto%d ao stock. Produto inexistente\n", ProductInd);  
	}

	else{

		prod[ProductInd].qtd += qtd_n; 

	}

}

void remove_stock_produto(int ProductInd, int qtd_n){

	/*int qtd_n = 0;*/

	if ( ProductInd > 9999){

		printf(" Impossivel adicionar produto%d ao stock. Produto inexistente\n", ProductInd);  
	}

	else{

		prod[ProductInd].qtd -= qtd_n; 

	}

}

void altera_preco_prod(int ProductInd, int preco){
		
		if ( ProductInd > 9999){

		printf("ERRO: Impossivel alterar preco do produto %d. Produto inexistente.\n",ProductInd);

		}

		else{

			prod[ProductInd].preco = preco;
		}
}


void nova_encomenda(){

	if (EncomendaInd != NENCOMENDAS){
			encomenda[EncomendaInd].ide = 0;		
		}
		
		printf("Nova encomenda %d.\n", EncomendaInd);
		EncomendaInd++;
}	







