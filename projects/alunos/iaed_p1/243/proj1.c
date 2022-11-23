#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DESCRICAO 65
#define ENCOMENDAS 500
#define PRODUTOS 10000
#define MAX_INPUT 1000


typedef struct 
{
	int idp;
	char descricao[DESCRICAO];
	int preco;
	int peso;	
	int quantidadeEmStock;
	
} Produto;

typedef struct 
{
	int ide;
	int pesoatual;
	int quantidadeatual;
	int precototal;
	Produto arrayprodutos[200];
	int produtosporencomenda;
}Encomenda;


const char delimitators[] = ":";
Produto produtos[PRODUTOS];
Encomenda encomenda[ENCOMENDAS];
int numeroDeProdutos=0;
int numeroDeEncomendas=0;
char input[MAX_INPUT];


int AdicionaProduto();
int AdicionaStock();
void CriaEncomenda();
int AddProdutoEncomenda();
int RemoveStockProduto();
int RemoveProduto();
int CalculaCusto();
int AlteraPreco();
int RetornaDescricaoQuantidade();
int RetornaID();
void ListaPreco();
int ListaAlfabeticamente();


int main()
{
	char comando;
	while ((comando = getchar()) != 'x')
	{
		switch (comando){
			case 'a':
				AdicionaProduto();
				break;
			case 'q':
				AdicionaStock();
				break;
			case 'r':
				RemoveStockProduto();
				break;
			case 'N':
				CriaEncomenda();
				break;
			case'A':
				AddProdutoEncomenda();
				break;
			case 'R':
				RemoveProduto();
				break;
			case 'C':
				CalculaCusto();
				break;
			case 'p':
				AlteraPreco();
				break;
			case 'E':
				RetornaDescricaoQuantidade();
				break;
			case 'm':
				RetornaID();
				break;
			case 'l':
				ListaPreco();
				break;
			case 'L':
				ListaAlfabeticamente();
		}
	}
	return 0;
}
/* Recebe um produto com determinada descri??o, preco, peso e quantidade e adiciona-o ao vetor de produtos*/
int AdicionaProduto(){ 				/*Comando a*/

	Produto tmp_produto;
	char* token;
	

	getchar();
	fgets(input,MAX_INPUT,stdin);
		
	token = strtok(input,delimitators);
	strcpy(tmp_produto.descricao,token);
		
	token = strtok(NULL,delimitators);
	tmp_produto.preco = atoi(token);

	token = strtok(NULL,delimitators);
	tmp_produto.peso = atoi(token);
		
	token = strtok(NULL,delimitators);
	tmp_produto.quantidadeEmStock = atoi(token);



	strcpy(produtos[numeroDeProdutos].descricao,tmp_produto.descricao);


	produtos[numeroDeProdutos].preco = tmp_produto.preco;


	produtos[numeroDeProdutos].peso = tmp_produto.peso;


	produtos[numeroDeProdutos].quantidadeEmStock = tmp_produto.quantidadeEmStock;


	produtos[numeroDeProdutos].idp = numeroDeProdutos;


	printf("Novo produto %d.\n",produtos[numeroDeProdutos].idp);

	numeroDeProdutos++;

	return 0;
}

/*Adiciona uma determinada quantidade de um produto ao stock existente desse produto*/
int AdicionaStock(){				/*Comando q*/

	int i=0;
	char* token;
	int nidp;
	int nquantidade;

	getchar();
	fgets(input,MAX_INPUT,stdin);



	token = strtok(input,delimitators);
	nidp = atoi(token);


	token = strtok(NULL,delimitators);
	nquantidade = atoi(token);


	for(i=0;i<numeroDeProdutos;i++){
		if(nidp == produtos[i].idp){
			produtos[i].quantidadeEmStock += nquantidade;
			return 1;
			}			
	}
	printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",nidp);
	return 0;
	

	
}

/*Cria uma encomenda, aumentando o vetor de encomendas existente no sistema*/
void CriaEncomenda(){				/*Comando N*/

	encomenda[numeroDeEncomendas].ide = numeroDeEncomendas;
	printf("Nova encomenda %d.\n",encomenda[numeroDeEncomendas].ide);
	numeroDeEncomendas++;


}

/*Recebe um identificador de encomenda e de produto e uma determinada quantidade e adiciona essa quantidade produto com esse id no vetor de produtos que existe dentro de cada encomenenda*/
int AddProdutoEncomenda(){			/*Comando A*/

/*	int i=0;
	int j=0;*/
	char* token;
	int nide;
	int nidp;
	int nquantidade;

	getchar();
	fgets(input,MAX_INPUT,stdin);

	token = strtok(input,delimitators);
	nide = atoi(token);


	token = strtok(NULL,delimitators);
	nidp = atoi(token);


	token = strtok(NULL,delimitators);
	nquantidade = atoi(token);




	if(nide == encomenda[nide].ide && numeroDeEncomendas>0){
		if(nidp == produtos[nidp].idp && numeroDeProdutos>0){
			if(produtos[nidp].quantidadeEmStock - nquantidade >=0){
				if(encomenda[nide].pesoatual + nquantidade*produtos[nidp].peso <= 200){		
					encomenda[nide].arrayprodutos[nidp].idp = produtos[nidp].idp;
					encomenda[nide].arrayprodutos[nidp].quantidadeEmStock += nquantidade;
					strcpy(encomenda[nide].arrayprodutos[nidp].descricao,produtos[nidp].descricao);
					produtos[nidp].quantidadeEmStock -= nquantidade;
					encomenda[nide].precototal += nquantidade*produtos[nidp].preco;
					encomenda[nide].pesoatual += nquantidade*produtos[nidp].peso;
					
					return 1;
				}
				printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",nidp,nide);
				return 0;
			}
			printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",nidp,nide);
			return 0;
		}
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",nidp,nide);
		return 0;
	}
	printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",nidp,nide);
	return 0;
}		

/*Remove uma determinada quantidade de um produto ao stock existente desse produto*/
int RemoveStockProduto(){			/*Comando r*/
	int i=0;
	char* token;
	int nidp;
	int nquantidade;

	getchar();
	fgets(input,MAX_INPUT,stdin);

	token = strtok(input,delimitators);
	nidp = atoi(token);


	token = strtok(NULL,delimitators);
	nquantidade = atoi(token);


	for(i=0;i<PRODUTOS;i++){
		if(nidp == produtos[i].idp && numeroDeProdutos>0){
			if(produtos[i].quantidadeEmStock - nquantidade>=0){
				produtos[i].quantidadeEmStock -= nquantidade;
				return 1;
				break;
			}
			else{
				printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",nquantidade,produtos[i].idp);
				return 0;
			}
		}
		
	}
	printf("Impossivel remover stock do produto %d. Produto inexistente.\n",nidp);
	return 0;
	
}

/*Dado um identificador de encomenda e produto, remove esse produto dessa encomenda e acrescenta a quantidade de produto a remover ao stock desse produto*/
int RemoveProduto(){			/*Comando R*/
	char* token;
	int nide;
	int nidp;


	getchar();
	fgets(input,MAX_INPUT,stdin);

	token = strtok(input,delimitators);
	nide = atoi(token);
	
	token = strtok(NULL,delimitators);
	nidp = atoi(token);

	if(nide == encomenda[nide].ide && numeroDeEncomendas>0){
		if(nidp == produtos[nidp].idp && numeroDeProdutos>0){
			
			encomenda[nide].precototal -= encomenda[nide].arrayprodutos[nidp].quantidadeEmStock*produtos[nidp].preco;
			encomenda[nide].pesoatual -= encomenda[nide].arrayprodutos[nidp].quantidadeEmStock*produtos[nidp].peso;
			produtos[nidp].quantidadeEmStock += encomenda[nide].arrayprodutos[nidp].quantidadeEmStock;
			encomenda[nide].arrayprodutos[nidp].preco = 0;
			encomenda[nide].arrayprodutos[nidp].peso = 0;
			encomenda[nide].arrayprodutos[nidp].quantidadeEmStock = 0;
			
			return 1;
		}
		
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",nidp,nide);
		return 0;
	}
	printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",nidp,nide);
	return 0;
}

/*Calcula o custo total de uma encomenda*/
int CalculaCusto(){				/*Comando C*/
	char* token;
	int nide;

	getchar();
	fgets(input,MAX_INPUT,stdin);

	token = strtok(input,delimitators);
	nide = atoi(token);

	if(nide == encomenda[nide].ide){
		printf("Custo da encomenda %d %d.\n",nide,encomenda[nide].precototal);
		return 1;
		}
	printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",nide);
	return 0;
}

/*Dado um identificador de produto, altera o preco desse produto*/
int AlteraPreco(){				/*Comando P*/
	char* token;
	int nidp;
	int npreco;
	int i;

	getchar();
	fgets(input,MAX_INPUT,stdin);

	token = strtok(input,delimitators);
	nidp = atoi(token);


	token = strtok(NULL,delimitators);
	npreco = atoi(token);


	if(nidp == produtos[nidp].idp){
		for(i=0;i<numeroDeEncomendas;i++){
			if(nidp == encomenda[i].arrayprodutos[nidp].idp){
				encomenda[i].precototal -= produtos[nidp].preco*encomenda[i].arrayprodutos[nidp].quantidadeEmStock;
				encomenda[i].precototal += npreco*encomenda[i].arrayprodutos[nidp].quantidadeEmStock;
			}
		}
		produtos[nidp].preco = npreco;

		return 1;
	}
	printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",nidp);
	return 0;
}

/*Dado um id de encomenda e produto, devolve a descricao e quantidade desse produto existente na encomenda dada*/
int RetornaDescricaoQuantidade(){		/*Comando E*/

	char* token;
	int nide;
	int nidp;

	getchar();
	fgets(input,MAX_INPUT,stdin);

	token = strtok(input,delimitators);
	nide = atoi(token);

	token = strtok(NULL,delimitators);
	nidp = atoi(token);

	if(nide == encomenda[nide].ide && numeroDeEncomendas>0){
		if(nidp == produtos[nidp].idp && numeroDeProdutos>0){
			printf("%s %d.\n",produtos[nidp].descricao,encomenda[nide].arrayprodutos[nidp].quantidadeEmStock);
			return 1;
		}
		printf("Impossivel listar produto %d. Produto inexistente.\n",nidp);
		return 0;
		
	}
	printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",nide);
	return 0;
	
}


/*Percorre o vetor de encomendas e verifica qual a encomenda que contem uma maior quantidade de um dado produto*/
int RetornaID(){					/*Comando m*/

	char* token;
	int nidp;
	int i;
	int max=0;
	int idencomenda=0;
/*	int k;
*/
	getchar();
	fgets(input,MAX_INPUT,stdin);

	token = strtok(input,delimitators);
	nidp = atoi(token);


		if(nidp == produtos[nidp].idp && numeroDeProdutos>0){
			for(i=0;i<numeroDeEncomendas;i++){
				if(encomenda[i].arrayprodutos[nidp].quantidadeEmStock>max && nidp == encomenda[i].arrayprodutos[nidp].idp){
					max = encomenda[i].arrayprodutos[nidp].quantidadeEmStock;
					idencomenda = encomenda[i].ide;
				}
			}
			
			
			
			if(max!=0){
				printf("Maximo produto %d %d %d.\n",nidp, idencomenda ,max);
				return 1;
			}
			else{
				return 0;
			}
			
		}
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",nidp);
		return 0;

}

/*Lista o preco dos produtos do sistema por ordem crescente*/
void ListaPreco(){				/*Comando l*/
	
	int i,d;
	Produto tmp_produto;
	for(i=0;i<numeroDeProdutos-1;i++){
		for(d=0;d<numeroDeProdutos-i-1;d++){

			if(produtos[d].preco > produtos[d + 1].preco){

				tmp_produto = produtos[d];
				produtos[d] = produtos[d+1];
				produtos[d+1] = tmp_produto;
			}
		}
	}
	printf("Produtos\n");
	for(i=0;i<numeroDeProdutos;i++){
		printf("* %s %d %d\n",produtos[i].descricao,produtos[i].preco,produtos[i].quantidadeEmStock);
	}

}


/*Lista alfabeticamente os produtos duma determinada encomenda*/
int ListaAlfabeticamente(){			/*Comando L*/

	int i,j;
	char* token;
	int nide;
	Produto tmp_produto;


	getchar();
	fgets(input,MAX_INPUT,stdin);

	token = strtok(input,delimitators);
	nide = atoi(token);

	if(nide == encomenda[nide].ide && numeroDeEncomendas>0){
   		for (i = 0; i < numeroDeProdutos-1; i++) {
       		for (j = 0; j < numeroDeProdutos-i-1; j++){  
           		if (strcmp(encomenda[nide].arrayprodutos[j].descricao,encomenda[nide].arrayprodutos[j+1].descricao)>0){
           	
           		
           			tmp_produto = produtos[j];
					produtos[j] = produtos[j+1];
					produtos[j+1] = tmp_produto;
           		}
       		}	
      		
  		}
	
   

		printf("Encomenda %d\n",encomenda[nide].ide);
		for(i=0;i<numeroDeProdutos;i++){
			if(encomenda[nide].arrayprodutos[i].quantidadeEmStock>0){
			printf("* %s %d %d\n",produtos[i].descricao,produtos[i].preco,encomenda[nide].arrayprodutos[i].quantidadeEmStock);
			}
		}
		return 1;
	}
	printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",nide);
   	return 0;	
}
   