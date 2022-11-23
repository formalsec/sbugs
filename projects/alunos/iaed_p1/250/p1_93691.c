#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Numero maximo de valores que podem ser armazenados*/
#define MAX_IDP 10000
#define MAX_STR 64
#define MAX_PARAM 4
#define MAX_PESO 200
#define MAX_INPUT 99 
#define MAX_IDE 500
#define MAX_PROD_ENC 200


/*Estruturas*/
typedef struct{
    int idp, preco, peso, stock;
    char descricao[MAX_STR];
} Produto;

typedef struct{
	int idp, quantidade;
} Elemento_Encomenda;

typedef struct{
	Elemento_Encomenda produto[MAX_PROD_ENC];
	int peso, max_prod_enc_atual;
} Encomenda;


/*Prototipos*/
char SepararInput(char input[MAX_INPUT], char input_separado[MAX_PARAM][MAX_STR]);

void InicializarProduto(Produto lista[]);

void AdicionarNovoProduto(char input_separado[MAX_PARAM][MAX_STR], Produto lista_produtos[MAX_IDP], int idp_atual);

void AdicionarStockProduto(char input_separado[MAX_PARAM][MAX_STR], Produto lista_produtos[MAX_IDP], int idp_atual);

void InicializarEncomenda(Encomenda lista[]);

void CriarEncomenda(int ide_atual);

void AdicionarProdutoEncomenda(char input_separado[MAX_PARAM][MAX_STR], Encomenda lista_encomendas[MAX_IDE], Produto lista_produtos[MAX_IDP], int ide_atual, int idp_atual);

void RemoverStockProduto(char input_separado[MAX_PARAM][MAX_STR], Produto lista_produtos[MAX_IDP], int idp_atual);

void RemoverProdutoEncomenda(char input_separado[MAX_PARAM][MAX_STR], Encomenda lista_encomendas[MAX_IDE], Produto lista_produtos[MAX_IDP], int ide_atual, int idp_atual);

void CalcularCustoEncomenda(char input_separado[MAX_PARAM][MAX_STR], Encomenda lista_encomendas[MAX_IDE], Produto lista_produtos[MAX_IDP], int ide_atual, int idp_atual);

void AlterarPrecoProduto(char input_separado[MAX_PARAM][MAX_STR], Produto lista_produtos[MAX_IDP], int idp_atual);

void ListarProdutoEncomenda (char input_separado[MAX_PARAM][MAX_STR], Encomenda lista_encomendas[MAX_IDE], Produto lista_produtos[MAX_IDP], int ide_atual, int idp_atual);

void ListarMaxProdutoEncomenda(char input_separado[MAX_PARAM][MAX_STR], Encomenda lista_encomendas[MAX_IDE], int idp_atual, int ide_atual);

void MergingSistema(Produto lista_produtos[MAX_IDP], int menor, int meio, int maior);

void SortSistema(Produto lista_produtos[MAX_IDP], int menor, int maior);

void OrdenarProdutosSistema(int idp_atual, Produto lista_produtos[MAX_IDP]);

void MergingEncomenda(Elemento_Encomenda produtos_encomenda[], Produto lista_produtos[MAX_IDP], int menor, int meio, int maior);

void SortEncomenda(Elemento_Encomenda produtos_encomenda[], Produto lista_produtos[MAX_IDP], int menor, int maior);

void OrdenarProdutosEncomenda(char input_separado[MAX_PARAM][MAX_STR], int ide_atual, int idp_atual, Produto lista_produtos[MAX_IDP], Encomenda lista_encomendas[MAX_IDE]);


/*Le os valores de stdin e executa cada comando chamando a respetiva funcao*/
int main(){
	Produto lista_produtos[MAX_IDP];	/*Vetor de produtos*/

	Encomenda lista_encomendas[MAX_IDE];	/*Vetor de encomendas*/

	char input[MAX_INPUT]="\0", input_separado[MAX_PARAM][MAX_STR] = {"\0"};

	int idp_atual=0, ide_atual=0;

	InicializarProduto(lista_produtos);

  	InicializarEncomenda(lista_encomendas);

    while(1){
    	if(fgets(input, MAX_INPUT-1, stdin) != NULL){

        	switch(SepararInput(input, input_separado)){

            	case 'a':
					AdicionarNovoProduto(input_separado, lista_produtos, idp_atual);
					idp_atual++;
                	break;

            	case 'q':
					AdicionarStockProduto(input_separado, lista_produtos, idp_atual);
                	break;

            	case 'N':
					CriarEncomenda(ide_atual);
					ide_atual++;
                	break;

            	case 'A':
					AdicionarProdutoEncomenda(input_separado, lista_encomendas, lista_produtos, ide_atual, idp_atual);
                	break;

            	case 'r':
					RemoverStockProduto(input_separado, lista_produtos, idp_atual);
                	break;

            	case 'R':
					RemoverProdutoEncomenda(input_separado, lista_encomendas, lista_produtos, ide_atual, idp_atual);
                	break;

            	case 'C':
					CalcularCustoEncomenda(input_separado, lista_encomendas, lista_produtos, ide_atual, idp_atual);
                	break;

            	case 'p':
					AlterarPrecoProduto(input_separado, lista_produtos, idp_atual);
                	break;

            	case 'E':
					ListarProdutoEncomenda (input_separado, lista_encomendas, lista_produtos, ide_atual, idp_atual);
                	break;

				case 'm':
					ListarMaxProdutoEncomenda(input_separado, lista_encomendas, idp_atual, ide_atual);
                	break;

				case 'l':
					OrdenarProdutosSistema(idp_atual, lista_produtos);
                	break;

				case 'L':
					OrdenarProdutosEncomenda(input_separado, ide_atual, idp_atual, lista_produtos, lista_encomendas);
					break;

            	case 'x':
            		return 0;
              		break;

        	}

    	}

  	}

    return 0;
}


/*
Separa o input recebido em diferentes parametros
Input: String que e dada pelo utilizador, matriz onde sera colocado o input sem ':'
Output: Comando a executar
 */
char SepararInput(char input[MAX_INPUT], char input_separado[MAX_PARAM][MAX_STR]){
    int a=0, i=0;
    char *token = strtok(input, " "), comando = *token;

    token = strtok(NULL, ":");

    for(a=0; a<MAX_PARAM; a++)
        strcpy(input_separado[a],"\0");

    while (token != NULL){
        strcpy(input_separado[i],token);
        token = strtok(NULL, ":");
        i++;
    }

    return comando;
}


/*Inicializa os parametros de um vetor de estruturas do tipo Produto*/
void InicializarProduto(Produto lista[]){
	int prod;

	for(prod=0; prod < MAX_IDP; prod++){
		lista[prod].idp = -1;
    	lista[prod].preco = 0;
    	lista[prod].peso = 0;
		lista[prod].stock = 0;
		lista[prod].descricao[0] = '\0';
	}

}


/*
Comando a: Adiciona um novo produto ao sistema
Input: 'a descricao:preco:peso:quantidade'
Output: Informacao do id do produto criado
*/
void AdicionarNovoProduto(char input_separado[MAX_PARAM][MAX_STR], Produto lista_produtos[MAX_IDP], int idp_atual){
	int preco = atoi(input_separado[1]), peso = atoi(input_separado[2]), qtd = atoi(input_separado[3]);

	if(idp_atual == MAX_IDP) 
		return;

	strcpy(lista_produtos[idp_atual].descricao, input_separado[0]);
	lista_produtos[idp_atual].idp = idp_atual;
	lista_produtos[idp_atual].preco = preco;
	lista_produtos[idp_atual].peso = peso;
	lista_produtos[idp_atual].stock = qtd;

	printf("Novo produto %d.\n", idp_atual);
}


/*
Comando q: Adiciona stock a um produto existente no sistema
Input: 'q idp:quantidade'
Output: Erro aplicavel 
*/
void AdicionarStockProduto(char input_separado[MAX_PARAM][MAX_STR], Produto lista_produtos[MAX_IDP], int idp_atual){
	int idp = atoi(input_separado[0]), qtd = atoi(input_separado[1]), id_prod;

	for(id_prod = 0; id_prod < idp_atual; id_prod++){	
		
		if(idp == lista_produtos[id_prod].idp){
			lista_produtos[id_prod].stock += qtd;
			return;
		}

	}

	printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}


/*Inicializa os parametros de um vetor de estruturas do tipo Encomenda*/
void InicializarEncomenda(Encomenda lista[]){
	int enc, prod;

	for(enc=0; enc < MAX_IDE; enc++){

		for(prod=0; prod < MAX_PROD_ENC; prod++){	
    		lista[enc].produto[prod].idp = -1;
    		lista[enc].produto[prod].quantidade = 0;
    	}

    	lista[enc].peso = 0;
		lista[enc].max_prod_enc_atual = 0;
	}

}


/*
Comando N: Cria uma nova encomenda
Input: 'N'
Output: Informacao do id da encomenda criada 
*/
void CriarEncomenda(int ide_atual){

	if(ide_atual == MAX_IDE)
		return;

	printf("Nova encomenda %d.\n", ide_atual);
}


/*
Comando A: Adiciona um produto a uma encomenda. Se o produto ja existir na encomenda, adiciona quantidade
Input: 'A ide:idp:quantidade'
Output: Erros aplicaveis 
*/
void AdicionarProdutoEncomenda(char input_separado[MAX_PARAM][MAX_STR], Encomenda lista_encomendas[MAX_IDE], Produto lista_produtos[MAX_IDP], int ide_atual, int idp_atual){
	int ide = atoi(input_separado[0]), idp = atoi(input_separado[1]), qtd = atoi(input_separado[2]), prod, id_prod;

	if (ide < ide_atual){

		if(idp < idp_atual){

			/*descobre o index (id_prod) do produto dentro da lista de produtos*/
			for(id_prod = 0; id_prod < idp_atual; id_prod++){	

				if(idp == lista_produtos[id_prod].idp)
					break;

			}

			if(lista_produtos[id_prod].stock >= qtd){

				if((lista_encomendas[ide].peso + (qtd * lista_produtos[id_prod].peso)) <= MAX_PESO){

					for(prod=0; prod < lista_encomendas[ide].max_prod_enc_atual; prod++){	

						if (idp == lista_encomendas[ide].produto[prod].idp){
							lista_encomendas[ide].produto[prod].quantidade += qtd;
							lista_encomendas[ide].peso += (qtd * lista_produtos[id_prod].peso);
							lista_produtos[id_prod].stock -= qtd;
							return;
						}

					}

					for(prod=0; prod < lista_encomendas[ide].max_prod_enc_atual + 1; prod++){	

						if (lista_encomendas[ide].produto[prod].idp == -1){
							lista_encomendas[ide].produto[prod].idp = idp;
							lista_encomendas[ide].produto[prod].quantidade += qtd;
							lista_encomendas[ide].peso += (qtd * lista_produtos[id_prod].peso);

							if(prod >= lista_encomendas[ide].max_prod_enc_atual)
								lista_encomendas[ide].max_prod_enc_atual++;

							lista_produtos[id_prod].stock -= qtd;
							return;
						}

					}

				} 
				else
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);

			}	
			else
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);

		}	
		else
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);		
		
	} 
	else
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	
	return;
}


/*
Comando r: Remove stock a um produto existente
Input: 'r idp:quantidade'
Output: Erros aplicaveis 
*/
void RemoverStockProduto(char input_separado[MAX_PARAM][MAX_STR], Produto lista_produtos[MAX_IDP], int idp_atual){
	int idp = atoi(input_separado[0]), qtd = atoi(input_separado[1]), id_prod;

	for(id_prod=0; id_prod < idp_atual; id_prod++){	

		if (lista_produtos[id_prod].idp == idp){

			if(qtd <= lista_produtos[id_prod].stock)
				lista_produtos[id_prod].stock -= qtd;

			else 
				printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
			
			return;

		}

	}
	printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);

}


/*
Comando R: Remove um produto de uma encomenda
Input: 'R ide:idp'
Output: Erros aplicaveis 
*/
void RemoverProdutoEncomenda(char input_separado[MAX_PARAM][MAX_STR], Encomenda lista_encomendas[MAX_IDE], Produto lista_produtos[MAX_IDP], int ide_atual, int idp_atual){  
	int ide = atoi(input_separado[0]), idp = atoi(input_separado[1]), prod, id_prod;

	if (ide < ide_atual){

		if(idp < idp_atual){

			/*descobre o index (id_prod) do produto dentro da lista de produtos*/
			for(id_prod = 0; id_prod < idp_atual; id_prod++){	

				if(idp == lista_produtos[id_prod].idp)
					break;

			}

			for(prod=0; prod < lista_encomendas[ide].max_prod_enc_atual; prod++){	

				if (idp == lista_encomendas[ide].produto[prod].idp){
					int qtd = lista_encomendas[ide].produto[prod].quantidade;

					lista_encomendas[ide].peso -= (lista_produtos[id_prod].peso * qtd);
					lista_encomendas[ide].produto[prod].quantidade = 0;
					lista_encomendas[ide].produto[prod].idp = -1;
					lista_produtos[id_prod].stock += qtd;

					return;
				}

			}

		}	
		else
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);		
		
	} 
	else
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	
	return;
}


/*
Comando C: Calcula o custo de uma encomenda
Input: 'C ide'
Output: Informacao do custo total da encomenda ou erros aplicaveis 
*/
void CalcularCustoEncomenda(char input_separado[MAX_PARAM][MAX_STR], Encomenda lista_encomendas[MAX_IDE], Produto lista_produtos[MAX_IDP], int ide_atual, int idp_atual){
	int ide = atoi(input_separado[0]), prod, total=0, id_prod;

	if (ide < ide_atual){

		for(prod=0; prod < lista_encomendas[ide].max_prod_enc_atual; prod++){	

			for(id_prod = 0; id_prod < idp_atual; id_prod++){

				if(lista_encomendas[ide].produto[prod].idp == lista_produtos[id_prod].idp){
					total += (lista_encomendas[ide].produto[prod].quantidade * lista_produtos[id_prod].preco);
					break;
				}

			}
			
		}
		printf("Custo da encomenda %d %d.\n", ide, total);
		return;

	} 
	else
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	
	return;
}


/*
Comando p: Altera o preco de um produto existente no sistema
Input: 'p idp:preco'
Output: Erro aplicavel 
*/
void AlterarPrecoProduto(char input_separado[MAX_PARAM][MAX_STR], Produto lista_produtos[MAX_IDP], int idp_atual){
	int idp = atoi(input_separado[0]), preco = atoi(input_separado[1]), id_prod;

	for(id_prod = 0; id_prod < idp_atual; id_prod++){	

		if(idp == lista_produtos[id_prod].idp){
			lista_produtos[id_prod].preco = preco;
			return;
		}

	}
	
	printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}


/*
Comando E: Lista a descricao e a quantidade de um produto numa encomenda
Input: 'E ide:idp'
Output: Listagem dos produtos ou erros aplicaveis 
*/
void ListarProdutoEncomenda (char input_separado[MAX_PARAM][MAX_STR], Encomenda lista_encomendas[MAX_IDE], Produto lista_produtos[MAX_IDP], int ide_atual, int idp_atual){
	int ide = atoi(input_separado[0]), idp = atoi(input_separado[1]), prod, id_prod;

	if (ide < ide_atual){
		
		if(idp < idp_atual){

			/*descobre o index (id_prod) do produto dentro da lista de produtos*/
			for(id_prod = 0; id_prod < idp_atual; id_prod++){

				if(idp == lista_produtos[id_prod].idp)
					break;

			}

			for(prod=0; prod < lista_encomendas[ide].max_prod_enc_atual; prod++){	

				if (idp == lista_encomendas[ide].produto[prod].idp){
					printf("%s %d.\n", lista_produtos[id_prod].descricao, lista_encomendas[ide].produto[prod].quantidade);
					return;					
				}

			}

			printf("%s %d.\n", lista_produtos[id_prod].descricao, 0);
			return;

		}	
		else
			printf("Impossivel listar produto %d. Produto inexistente.\n", idp);		
		
	} 
	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	
	return;
}


/*
Comando m: Lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas nessa situacao, imprime a encomenda de menor id.
Input: 'm idp'
Output: Informacao do produto nas condicoes acima referidas ('idp ide quantidade') ou erros aplicaveis 
*/
void ListarMaxProdutoEncomenda(char input_separado[MAX_PARAM][MAX_STR], Encomenda lista_encomendas[MAX_IDE], int idp_atual, int ide_atual){ 
	int idp = atoi(input_separado[0]), prod, enc, max[3] = {0, 0, -1};
	
	max[0] = idp;

	if(ide_atual == 0)
		return;

	if(idp < idp_atual){

		for(enc=0; enc < ide_atual; enc++){

			for (prod=0; prod < lista_encomendas[enc].max_prod_enc_atual; prod++){	

				if (idp == lista_encomendas[enc].produto[prod].idp){

					if (lista_encomendas[enc].produto[prod].quantidade > max[2]){
						max[1] = enc;
						max[2] = lista_encomendas[enc].produto[prod].quantidade;
					}
				
				}

			}

		}
		if(max[2] != -1){
			printf("Maximo produto %d %d %d.\n", max[0], max[1], max[2]);
			return;
		}

	}
	else
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);

	return;
}


/*Merge sort para o comando l*/
void MergingSistema(Produto lista_produtos[MAX_IDP], int menor, int meio, int maior){
	int i, j, k; 
    int n1 = meio - menor + 1, n2 =  maior - meio; 
  
    Produto esq[MAX_IDP/2], drt[MAX_IDP/2]; 
  
    for (i = 0; i < n1; i++) 
    	esq[i] = lista_produtos[menor + i]; 

    for (j = 0; j < n2; j++) 
        drt[j] = lista_produtos[meio + 1 + j]; 
  
    i = 0;
    j = 0; 
    k = menor;

    while (i < n1 && j < n2){ 

        if(esq[i].preco < drt[j].preco){ 
            lista_produtos[k] = esq[i]; 
            i++; 
        }

		else if((esq[i].preco == drt[j].preco) && (esq[i].idp < drt[j].idp)){
			lista_produtos[k] = esq[i]; 
            i++;
		}

        else{
            lista_produtos[k] = drt[j]; 
            j++; 
        } 

        k++; 
    } 

    while (i < n1){ 
        lista_produtos[k] = esq[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2){ 
        lista_produtos[k] = drt[j]; 
        j++; 
        k++; 
    }

}


void SortSistema(Produto lista_produtos[MAX_IDP], int menor, int maior){
	
	if(menor < maior){
		int meio = menor + (maior - menor) / 2;

		/*Aplicacao do merge sort para a parte esquerda e direita do vetor, respetivamente*/ 
		SortSistema(lista_produtos, menor, meio);
		SortSistema(lista_produtos, meio+1, maior);

		MergingSistema(lista_produtos, menor, meio, maior);
	}

}


/*
Comando l: Lista todos os produtos do sistema por ordem crescente de preco. Se houver 2 ou mais produtos nessas condicoes, imprime por ordem crecente de id do produto
Input: 'l'
Output: Listagem de produtos ordenados segundo as condicoes acima referidas 
*/
void OrdenarProdutosSistema(int idp_atual, Produto lista_produtos[MAX_IDP]){
	int prod;

	SortSistema(lista_produtos, 0, idp_atual-1);

	printf("Produtos\n");

	for(prod=0; prod < idp_atual; prod++)
		printf("* %s %d %d\n", lista_produtos[prod].descricao, lista_produtos[prod].preco, lista_produtos[prod].stock);

}

/*Merge sort para o comando L*/
void MergingEncomenda(Elemento_Encomenda produtos_encomenda[], Produto lista_produtos[MAX_IDP], int menor, int meio, int maior){
	int i, j, k, prod1, prod2; 
    int n1 = meio - menor + 1, n2 =  maior - meio; 
  
    Elemento_Encomenda esq[MAX_PROD_ENC/2], drt[MAX_PROD_ENC/2]; 
  
    for (i = 0; i < n1; i++) 
        esq[i] = produtos_encomenda[menor + i]; 

    for (j = 0; j < n2; j++) 
        drt[j] = produtos_encomenda[meio + 1 + j]; 
  
    i = 0;
    j = 0; 
    k = menor;

    while (i < n1 && j < n2){ 
    
		for(prod1 = 0; prod1 < MAX_IDP; prod1++){
			if(esq[i].idp == lista_produtos[prod1].idp) 
				break;
		}
		
		for(prod2 = 0; prod2 < MAX_IDP; prod2++){
			if(drt[j].idp == lista_produtos[prod2].idp) 
				break;
		}

        if (strcmp(lista_produtos[prod2].descricao, lista_produtos[prod1].descricao) > 0){ 
            produtos_encomenda[k] = esq[i]; 
            i++; 
        }

        else{
            produtos_encomenda[k] = drt[j]; 
            j++; 
        } 

        k++; 
    } 

    while (i < n1){ 
        produtos_encomenda[k] = esq[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2){ 
        produtos_encomenda[k] = drt[j]; 
        j++; 
        k++; 
    }

}


void SortEncomenda(Elemento_Encomenda produtos_encomenda[], Produto lista_produtos[MAX_IDP], int menor, int maior){
	
	if (menor < maior){
        int meio = menor + (maior - menor) / 2; 
  
        /*Aplicacao do merge sort para a parte esquerda e direita do vetor, respetivamente*/ 
        SortEncomenda(produtos_encomenda, lista_produtos, menor, meio); 
        SortEncomenda(produtos_encomenda, lista_produtos, meio+1, maior); 

        MergingEncomenda(produtos_encomenda, lista_produtos, menor, meio, maior); 
    } 

}


/*
Comando L: Lista todos os produtos de uma encomenda por ordem alfabetica da descricao
Input: 'L ide'
Output: Listagem dos produtos ordenados segundo as condicoes acima referidas ou erro aplicavel 
*/
void OrdenarProdutosEncomenda(char input_separado[MAX_PARAM][MAX_STR], int ide_atual, int idp_atual, Produto lista_produtos[MAX_IDP], Encomenda lista_encomendas[MAX_IDE]){
	int ide = atoi(input_separado[0]), prod, id_prod, k=0;

	if(ide < ide_atual){
		Elemento_Encomenda produtos_encomenda[MAX_PROD_ENC];

		for(prod=0; prod < lista_encomendas[ide].max_prod_enc_atual; prod++){

			if(lista_encomendas[ide].produto[prod].idp != -1){
				produtos_encomenda[k] = lista_encomendas[ide].produto[prod];
				k++;
			}

		}

		SortEncomenda(produtos_encomenda, lista_produtos, 0, k-1);
		
		printf("Encomenda %d\n", ide);

		for(prod=0; prod < k; prod++){

			for(id_prod = 0; id_prod < idp_atual; id_prod++){

				if(produtos_encomenda[prod].idp == lista_produtos[id_prod].idp) 
					break;

			}
			printf("* %s %d %d\n", lista_produtos[id_prod].descricao, lista_produtos[id_prod].preco, produtos_encomenda[prod].quantidade);

		}

	}
	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	
	return;
}