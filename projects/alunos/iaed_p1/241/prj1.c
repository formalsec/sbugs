#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_descricao 63
#define MAX_stock_produtos 10000	
#define MAX_encomendas 500
#define MAX_peso_encomenda 200
#define MAX_instr 1024

int idp_final = 0; 	/*contador do numero de produtos adicionados ao stock*/
int ide_final = 0;	/*contador do numero de encomendas criadas*/

struct Produto {

	int id;
	int preco;
	int peso;
	int qtd_stock;
	char descricao[MAX_descricao]; 

};

struct Encomenda {

	struct Produto produtos_e[MAX_stock_produtos];  /*array composto por structs do tipo Produto*/
	int peso;
	int id;

};

struct Produto produtos[MAX_stock_produtos];  /*array composto por structs do tipo Produto*/
struct Encomenda encomendas[MAX_encomendas];  /*array composto por structs do tipo Encomenda*/


void adiciona_produto(char argv[MAX_instr]){

	struct Produto produto_x;  /*struct que sera usado para guardar os varios elementos do Produto*/

	char delimt[2] = ":"; /*delimitador para o input*/

	char* dscr;   
	char* prc;
	char* ps;
	char* qtd;

	dscr = strtok(argv, delimt);	/*repartir os diferentes elementos do produto pelas variaveis atraves do delimitador*/
	prc = strtok(NULL, delimt);	
	ps = strtok(NULL, delimt);
	qtd = strtok(NULL, delimt);

	strcpy(produto_x.descricao, dscr);		/*copiar o str para o struct do tipo Produto*/

	produto_x.preco = strtol(prc, NULL, 10);    /*passar o pointer para inteiro*/
	produto_x.peso = strtol(ps, NULL, 10);
	produto_x.qtd_stock = strtol(qtd, NULL, 10);

	produto_x.id = idp_final;

	produtos[idp_final] = produto_x;

	idp_final ++;

	printf("%s%d%s\n", "Novo produto ", produto_x.id, ".");  /*output da funcao*/

}


void adiciona_stock(char argv[MAX_instr]){

	char delimt[2] = ":";	/*delimitador para o input*/
	
	char* idp; 
	char* qtd;

	int idp_i;
	int qtd_i;

	idp = strtok(argv, delimt);	  /*repartir os diferentes dados do produto pelas variaveis atraves do delimitador*/
	qtd = strtok(NULL, delimt);

	idp_i = strtol(idp, NULL, 10);	/*passar o pointer para inteiro*/
	qtd_i = strtol(qtd, NULL, 10);

	if(produtos[idp_i].id == idp_i){
		 produtos[idp_i].qtd_stock += qtd_i;	  /*incrementa a quantidade de um produto existente no stock*/
	}

	else{
		printf("%s%d%s\n", "Impossivel adicionar produto ", idp_i , " ao stock. Produto inexistente.");
	}
}


void cria_encomenda(){

	struct Encomenda encomenda_x;	/*struct que sera usado para guardar os varios elementos da Encomenda*/

	encomenda_x.id = ide_final;
	encomenda_x.peso = 0;
	encomendas[ide_final] = encomenda_x;

	printf("%s%d%s\n", "Nova encomenda ", ide_final, ".");   /*output da funcao*/

	ide_final ++;

}


void adiciona_prd_a_enc(char argv[MAX_instr]){

	char delimt[2] = ":";	/*delimitador para o input*/

	char* ide;
	char* idp;
	char* qtd;

	int ide_i;
	int idp_i;
	int qtd_i;
	int peso_adc;

	ide = strtok(argv, delimt);		/*repartir os diferentes dados do produto pelas variaveis atraves do delimitador*/
	idp = strtok(NULL, delimt);
	qtd = strtok(NULL, delimt);

	ide_i = strtol(ide, NULL, 10);		 /*passar o pointer para inteiro*/
	idp_i = strtol(idp, NULL, 10);
	qtd_i = strtol(qtd, NULL, 10);

	peso_adc = produtos[idp_i].peso * qtd_i;

	if(encomendas[ide_i].id != ide_i){
		printf("%s%d%s%d%s\n", "Impossivel adicionar produto ", idp_i, " a encomenda ", ide_i ,". Encomenda inexistente.");
	}

	else if(produtos[idp_i].id != idp_i){
		printf("%s%d%s%d%s\n", "Impossivel adicionar produto ", idp_i, " a encomenda ", ide_i ,". Produto inexistente.");
	}

	else if(produtos[idp_i].qtd_stock < qtd_i){
		printf("%s%d%s%d%s\n", "Impossivel adicionar produto ", idp_i, " a encomenda ", ide_i ,". Quantidade em stock insuficiente.");
	}

	else if(encomendas[ide_i].peso + peso_adc > MAX_peso_encomenda){
		printf("%s%d%s%d%s\n", "Impossivel adicionar produto ", idp_i, " a encomenda ", ide_i ,". Peso da encomenda excede o maximo de 200.");
	}

	else{
		if(encomendas[ide_i].produtos_e[idp_i].id != idp_i){   /*caso o produto nao exista na encomenda*/
			
			encomendas[ide_i].produtos_e[idp_i] = produtos[idp_i];	/*cria o produto na encomenda*/
			encomendas[ide_i].produtos_e[idp_i].qtd_stock = qtd_i;	/*mete a quantidade certa no produto na encomenda*/

			produtos[idp_i].qtd_stock -= qtd_i;		/*decrementa a quantidade do stock do produto*/
		}

		else{
			encomendas[ide_i].produtos_e[idp_i].qtd_stock += qtd_i;   /*incrementa a quantidade do produto na encomenda*/
			produtos[idp_i].qtd_stock -= qtd_i;	  /*decrementa a quantidade do stock do produto*/
		}
	}
}


void remove_stock(char argv[MAX_instr]){

	char delimt[2] = ":";	/*delimitador para o input*/

	char* idp;
	char* qtd;

	int idp_i;
	int qtd_i;

	idp = strtok(argv, delimt);   /*repartir os diferentes dados do produto pelas variaveis atraves do delimitador*/
	qtd = strtok(NULL, delimt);

	idp_i = strtol(idp, NULL, 10);		 /*passar o pointer para inteiro*/
	qtd_i = strtol(qtd, NULL, 10);

	if(produtos[idp_i].id != idp_i){
		printf("%s%d%s\n", "Impossivel remover stock do produto ", idp_i ,". Produto inexistente.");
	}

	else if(produtos[idp_i].qtd_stock < qtd_i){
		printf("%s%d%s%d%s\n", "Impossivel remover ", qtd_i ," unidades do produto ", idp_i ," do stock. Quantidade insuficiente.");
	}

	else{
		produtos[idp_i].qtd_stock -= qtd_i;   /*decrementa a quantidade do stock do produto*/
	}
}


void remove_prd_enc(char argv[MAX_instr]){

	char delimt[2] = ":";	/*delimitador para o input*/
	char rem[2] = " ";

	char* ide;
	char* idp;

	int ide_i;
	int idp_i;

	ide = strtok(argv, delimt);   /*repartir os diferentes dados do produto pelas variaveis atraves do delimitador*/
	idp = strtok(NULL, delimt);

	ide_i = strtol(ide, NULL, 10);		 /*passar o pointer para inteiro*/
	idp_i = strtol(idp, NULL, 10);	

	if(produtos[idp_i].id != idp_i){
		printf("%s%d%s%d%s\n", "Impossivel remover produto ", idp_i ," a encomenda ", ide_i ,". Produto inexistente.");
	}

	else if(encomendas[ide_i].id != ide_i){
		printf("%s%d%s%d%s\n", "Impossivel remover produto ", idp_i ," a encomenda ", ide_i ,". Encomenda inexistente.");
	}

	else{
		encomendas[ide_i].produtos_e[idp_i].id = produtos[MAX_stock_produtos].id;     /*reinicia as varias variaveis do produto em questao*/
		encomendas[ide_i].produtos_e[idp_i].preco = produtos[MAX_stock_produtos].preco;
		encomendas[ide_i].produtos_e[idp_i].peso = produtos[MAX_stock_produtos].peso;
		encomendas[ide_i].produtos_e[idp_i].qtd_stock = produtos[MAX_stock_produtos].qtd_stock;
		strcat(encomendas[ide_i].produtos_e[idp_i].descricao, rem);
	}
}


void custo_encomenda(char argv[MAX_instr]){

	char delimt[2] = ":";	/*delimitador para o input*/

	char* ide;
	int ide_i;
	int i;
	int preco_e;  /*preco total*/

	ide = strtok(argv, delimt);    /*repartir os diferentes dados do produto pelas variaveis atraves do delimitador*/

	ide_i = strtol(ide, NULL, 10);		 /*passar o pointer para inteiro*/

	for(i = 0; i < ide_final; i++){
		preco_e += encomendas[ide_i].produtos_e[i].preco * encomendas[ide_i].produtos_e[i].qtd_stock;   /*ciclo que vai somando os precos de todos os*/
	}																									/*produtos na dentro da encomenda */

	if(encomendas[ide_i].id != ide_i){
		printf("%s%d%s\n", "Impossivel calcular custo da encomenda ", ide_i,". Encomenda inexistente.");
	}

	else{
		printf("%s%d %d%s\n", "Custo da encomenda ", ide_i , preco_e, ".");	/*output da funcao*/
	}
}


void altera_preco(char argv[MAX_instr]){

	char delimt[2] = ":";	/*delimitador para o input*/

	char* idp;
	char* preco;
	
	int idp_i;
	int preco_i;
	int i;

	idp = strtok(argv, delimt);    /*repartir os diferentes dados do produto pelas variaveis atraves do delimitador*/
	preco = strtok(NULL, delimt);

	idp_i = strtol(idp, NULL, 10);		 /*passar o pointer para inteiro*/
	preco_i = strtol(preco, NULL, 10);

	if(produtos[idp_i].id != idp_i){
		printf("%s%d%s\n", "Impossivel alterar preco do produto ", idp_i,". Produto inexistente.");
	}

	else{
		produtos[idp_i].preco = preco_i;  /*altera o preco do produto em questao no stock*/

		for(i = 0; i < ide_final; i++){
			encomendas[i].produtos_e[idp_i].preco = preco_i;  /*altera o preco do produto em questao em todas as encomendas criadas ate ao momento*/
		}
	}
}


void lista_prd_enc(char argv[MAX_instr]){

	char delimt[2] = ":";	/*delimitador para o input*/

	char* ide;
	char* idp;

	int ide_i;
	int idp_i;

	ide = strtok(argv, delimt);   /*repartir os diferentes dados do produto pelas variaveis atraves do delimitador*/
	idp = strtok(NULL, delimt);

	ide_i = strtol(ide, NULL, 10);	  /*passar o pointer para inteiro*/
	idp_i = strtol(idp, NULL, 10);

	if(produtos[idp_i].id != idp_i){
		printf("%s%d%s\n", "Impossivel listar produto ", idp_i , ". Produto inexistente.");
	}

	else if(encomendas[ide_i].id != ide_i){
		printf("%s%d%s\n", "Impossivel listar encomenda ", ide_i , ". Encomenda inexistente.");
	}

	else{
		printf("%s%s%d\n",  encomendas[ide_i].produtos_e[idp_i].descricao, " ", encomendas[ide_i].produtos_e[idp_i].qtd_stock); /*output da funcao*/ 
	}
}


void lista_prd_maior_qtd(char argv[MAX_instr]){

	char delimt[2] = ":";	/*delimitador para o input*/

	char* idp;

	int idp_i;
	int ide_maior = 0; /*indentificador da encomenda com a maior quantidade do produto em questao*/
	int i;

	idp = strtok(argv, delimt);    /*repartir os diferentes dados do produto pelas variaveis atraves do delimitador*/

	idp_i = strtol(idp, NULL, 10);		 /*passar o pointer para inteiro*/

	if(produtos[idp_i].id != idp_i){
		printf("%s%d%s\n", "Impossivel listar maximo do produto ", idp_i ,". Produto inexistente.");
	}

	else{
		for(i = 0; i < ide_final; i++){		/*ciclo que percorre as varias encomendas e compara a quantidade do produto em questao com o atual maior*/
			if(encomendas[i].produtos_e[idp_i].qtd_stock > encomendas[ide_maior].produtos_e[idp_i].qtd_stock){			
				ide_maior = encomendas[i].id;
			}
			
			else if(encomendas[i].produtos_e[idp_i].qtd_stock == encomendas[ide_maior].produtos_e[idp_i].qtd_stock){
				if(encomendas[i].id < encomendas[ide_maior].id){  /*caso sejam iguais em termos de quantidade o ide_maior vai ser o que tiver o menor*/
					ide_maior = encomendas[i].id;				  /*id entre eles*/
				}
			}
		}
		printf("%s%d %d %d\n", "Maximo produto ", idp_i, ide_maior, encomendas[ide_maior].produtos_e[idp_i].qtd_stock); /*output da funcao*/
	}
}


void lista_prd_ordem_cresc(){

	struct Produto produtos_x[MAX_stock_produtos]; /*array composto por structs do tipo Produto*/
	struct Produto produto_temp;	/*struct que sera usado para guardar os varios elementos do Produto*/

	int i, j;
	int n = idp_final;  

	for(i = 0; i < idp_final; i++){		/*copia o array com todos os produtos em stock*/
		produtos_x[i] = produtos[i];
	}

    for(i = 0; i < n-1; i++){      /*bubble sort*/
    	for (j = 0; j < n-i-1; j++){  
    		if(produtos_x[j].preco > produtos_x[j+1].preco){  
            	produto_temp = produtos_x[j];
            	produtos_x[j] = produtos_x[j+1];
            	produtos_x[j+1] = produto_temp;
            }
        }	  
    }
    
    printf("%s\n", "Produtos");

    for(i = 0; i < n; i++){
    	printf("* %s %d %d\n", produtos_x[i].descricao, produtos_x[i].preco, produtos_x[i].qtd_stock); 
    }   /*ciclo com os varios outputs da funcao*/
}


void lista_enc_ordem_alfab(char argv[MAX_instr]){

	struct Encomenda encomendas_x[MAX_encomendas];  /*array composto por structs do tipo Encomenda*/
	struct Encomenda encomenda_temp;	/*struct que sera usado para guardar os varios elementos da Encomenda*/

	char delimt[2] = ":";	/*delimitador para o input*/

	int i, j;
	int n = ide_final; 

	char* ide;

	int ide_i;

	ide = strtok(argv, delimt);    /*repartir os diferentes dados do produto pelas variaveis atraves do delimitador*/

	ide_i = strtol(ide, NULL, 10); 	  /*passar o pointer para inteiro*/

	for(i = 0; i < ide_final; i++){
		encomendas_x[i] = encomendas[i];  /*copia o array com todas as encomendas criadas*/
	}

    for(i = 0; i < n-1; i++){    /*bubble sort*/  
    	for (j = 0; j < n-i-1; j++){  
    		if(strcmp(encomendas[ide_i].produtos_e[j].descricao, encomendas[ide_i].produtos_e[j+1].descricao) > 0){  
            	encomenda_temp = encomendas_x[j];
            	encomendas_x[j] = encomendas_x[j+1];
            	encomendas_x[j+1] = encomenda_temp;
            }
        }
    }
    
    printf("%s%d\n", "Encomenda ", ide_i);

    for(i = 0; i < n; i++){
    	printf("* %s %d %d\n", encomendas_x[ide_i].produtos_e[i].descricao, encomendas_x[i].produtos_e[i].preco, encomendas_x[i].produtos_e[i].qtd_stock);
    }  /*ciclo com os varios outputs da funcao*/
}


int main(){

	char instruction[MAX_instr];
	char cmd = ' ';	

	while(cmd != 'x'){

		cmd = getchar();
		

		switch (cmd){

			case 'a':
				getchar();
				scanf("%[^\n]s", instruction);
				adiciona_produto(instruction);
				break;
			
			case 'q':
				getchar();
				scanf("%[^\n]s", instruction);
				adiciona_stock(instruction);
				break;

			case 'N':
				cria_encomenda();
				break;

			case 'A':
				getchar();
				scanf("%[^\n]s", instruction);
				adiciona_prd_a_enc(instruction);
				break;

			case 'r':
				getchar();
				scanf("%[^\n]s", instruction);
				remove_stock(instruction);
				break;

			case 'R':
				getchar();
				scanf("%[^\n]s", instruction);
				remove_prd_enc(instruction);
				break;

			case 'C':
				getchar();
				scanf("%[^\n]s", instruction);
				custo_encomenda(instruction);
				break;

			case 'p':
				getchar();
				scanf("%[^\n]s", instruction);
				altera_preco(instruction);
				break;

			case 'E':
				getchar();
				scanf("%[^\n]s", instruction);
				lista_prd_enc(instruction);
				break;

			case 'm':
				getchar();
				scanf("%[^\n]s", instruction);
				lista_prd_maior_qtd(instruction);
				break;

			case 'l':
				lista_prd_ordem_cresc();
				break;

			case 'L':
				getchar();
				scanf("%[^\n]s", instruction);
				lista_enc_ordem_alfab(instruction);
				break;	
		}
	}
	return 0;
}
