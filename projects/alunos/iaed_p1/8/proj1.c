#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#define SZDESC 64
#define MAXWEIGHT 200
#define SZPROD 10000
#define SZENC 500
#define SZQTD 1000

/*Jo?o Dinis Silva Ferreira n? 75332*/

int converte_string_int(char *str, int i);

int main(){
	
	struct produto{
		
		char descricao[SZDESC];
		int preco;
		int peso;
		int qtd;
		int idp;
		
	};
	
	struct encomenda{
		
		int ide;
		int produtos_na_encomenda[SZQTD];
		int qtd[SZQTD];
		
	};
	
	struct produto lista_produtos[SZPROD];
	struct encomenda lista_encomendas[SZENC];
	
	char comando[100], letra_comando, ch;
	int m = 0;
	int i, k, n;/*vari?veis para serem usadas em ciclos e como placeholders tempor?rios de informa??o*/
	/*int array[1000][SZDESC];*/ /*variavel temporaria*/
	/*char desc_temp[SZDESC];*/
	
	/*estado ? uma vari?vel usada para algumas compara??es pelo c?digo.
	 *Tem utiliza?ao muito restrita a linhas de c?digo adjacentes e pode ser reutilizada
	 desde que seja sempre devolvida ao estado inicial de -1*/
	int estado = -1;
		
	/*Vari?veis tempor?rias para serem usadas nos selection sorts*/
	int left, right;
	int a, b;
	
	int max;
	
	int index_produto; /*Vari?vel temporaria para quando queremos aceder a um produto espec?fico da tabela*/
	int index_encomenda; /*Semelhante ao index_produto, mas para a lista das encomendas*/
	
	int total_produtos = -1, total_encomendas = -1;
	int identificador_temporario, quantidade_temporaria, peso_temporario, preco_temporario;
	/*Os seguintes chars sao strings temporarias cujos valores vao ser convertidos para inteiros mais a frente*/
	char preco_temp[8], peso_temp[8], qtd_temp[8], idp_temp[6], ide_temp[4];
	
	while (1){
		
		for(i = 0;(ch = getchar()) != '\n'; i++){
			comando[i] = ch;
			
		}
		
		comando[i] = '\0';
		
		letra_comando = comando[0];
		
		if (letra_comando == 'x')
			return 0;
		
		switch(letra_comando){
			
			case 'a':
				
				if (total_produtos == SZPROD-1){
					
					printf("Limite de produtos alcan?ado. Imposs?vel adicionar mais.\n");
					break;
					
				}
				
				total_produtos++;
				
				for(k = 2; comando[k] != ':'; k++)
					lista_produtos[total_produtos].descricao[k-2] = comando[k];
				
				lista_produtos[total_produtos].descricao[k-2] = '\0';
				k++;
				
				/* Agora vamos buscar a parte da string que ? referente ao pre?o e vamos converter para um inteiro*/
				for(i = 0; comando[k] != ':'; k++, i++)

					preco_temp[i] = comando[k];
				
				preco_temp[i] = '\0';
				i--;
				k++;
				
				lista_produtos[total_produtos].preco = converte_string_int(preco_temp, i);
				
				
				/* Agora vamos buscar a parte da string que ? referente ao peso e vamos converter para um inteiro*/
				for(i = 0; comando[k] != ':'; k++, i++)

					peso_temp[i] = comando[k];
				
				peso_temp[i] = '\0';
				i--;
				k++;
				
				lista_produtos[total_produtos].peso = converte_string_int(peso_temp, i);
				
				
				/* Agora vamos buscar a parte da string que ? referente ? quantidade e vamos converter para um inteiro*/
				for(i = 0; comando[k] != '\0'; k++, i++)

					qtd_temp[i] = comando[k];
				
				qtd_temp[i] = '\0';
				i--;
				k++;
				
				lista_produtos[total_produtos].qtd = converte_string_int(qtd_temp, i);
				
				
				/*S? falta criar um identificador para este produto e incrementar o total_produtos*/
				
				lista_produtos[total_produtos].idp = total_produtos;
				/*Aqui podemos atribuir o total_produtos ao idp porque em nenhuma parte do c?digo vamos remover produtos do sistema*/
				
				printf("Novo produto %d.\n", lista_produtos[total_produtos].idp);
				break; /*Faz break do switch principal e de volta para o main loop*/
			
			case 'q':
				
				for(k = 2, i = 0; comando[k] != ':'; k++, i++)
					idp_temp[i] = comando[k];
				idp_temp[i] = '\0';
				
				i--;
				k++;
				
				identificador_temporario = converte_string_int(idp_temp, i);
				
				
				/*Agora vamos ver se este identificador_temporario existe no sistema*/
				
				estado = 0;
				
				for(i=0; i <= total_produtos; i++){
					
					if (lista_produtos[i].idp == identificador_temporario){
						estado = 1;
						index_produto = i; /*atribu?mos o i ? vari?vel temporaria index_produto para podermos reutilizar no for seguinte*/
						break;
					}
					
				}
				
				if (estado == 0){
					
					printf("Imposs?vel adicionar produto %d ao stock. Produto inexistente.\n", identificador_temporario);
					estado = -1;
					break;
					
				}
				estado = -1;
				
				
				/* Agora vamos buscar a parte da string que ? referente ? quantidade que vai ser adicionada e vamos converter para um inteiro*/
				for(i = 0; comando[k] != '\0'; k++, i++)

					qtd_temp[i] = comando[k];
				
				qtd_temp[i] = '\0';
				i--;
				k++;
				
				quantidade_temporaria = converte_string_int(qtd_temp, i);
				
				lista_produtos[index_produto].qtd += quantidade_temporaria;
				break; /*Faz break do switch principal e de volta para o main loop*/
			
			case 'N':
				
				if (total_encomendas == SZENC-1){
					
					printf("Total de encomendas alcan?ado. Imposs?vel adicionar mais.\n");
					break;
					
				}
				
				total_encomendas++;
				
				lista_encomendas[total_encomendas].ide = total_encomendas;
				
				/*Inicializo as duas listas dentro da encomenda a -1 e 0*/
				
				for (i = 0; i < SZPROD; i++){
					lista_encomendas[total_encomendas].produtos_na_encomenda[i] = -1;
					lista_encomendas[total_encomendas].qtd[i] = 0;
				}
				

				break;
				
			case 'A':	/*Adiciona um produto a uma encomenda*/
				
				for(k = 2, i = 0; comando[k] != ':'; k++, i++)
					ide_temp[i] = comando[k];
				ide_temp[i] = '\0';
				
				i--;
				k++;
				
				identificador_temporario = converte_string_int(ide_temp, i);
				
				/*n toma o valor do identificador_temporario, porque esta vari?vel vai ser agora reutilizada*/
				
				n = identificador_temporario;
				
				for(i = 0; comando[k] != ':'; k++, i++)

					idp_temp[i] = comando[k];
				
				idp_temp[i] = '\0';
				i--;
				k++;
				
				identificador_temporario = converte_string_int(idp_temp, i);
				
				/*Vamos ver se a encomenda existe*/
				
				estado = 0;
				
				for(i = 0; i <= total_encomendas; i++){
					
					if (lista_encomendas[i].ide == n){
						
						estado = 1;
						index_encomenda = i;
					}
					
				}
				
				if(estado == 0){
					
					printf("Imposs?vel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", identificador_temporario, n);
					estado = -1;
					break;
					
				}
				
				estado = 0;
				
				for(i = 0; i <= total_produtos; i++){
					
					if (lista_produtos[i].idp == identificador_temporario){
						
						estado = 1;
						index_produto = i;
					}
					
				}
				
				if(estado == 0){
					
					printf("Imposs?vel adicionar produto %d a encomenda %d. Produto inexistente.\n", identificador_temporario, n);
					estado = -1;
					break;
					
				}
				
				estado = -1;
				
				/*Agora que j? vimos que a encomenda e o produto existem, vamos ver a quantidade que queremos adicionar ? encomenda*/
				
				for(i = 0; comando[k] != '\0'; k++, i++)

					qtd_temp[i] = comando[k];
				
				qtd_temp[i] = '\0';
				i--;
				k++;
				
				quantidade_temporaria = converte_string_int(qtd_temp, i);
				
				/*verificar o stock deste produto*/
				
				if(lista_produtos[index_produto].qtd < quantidade_temporaria){
					
					printf("Imposs?vel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", identificador_temporario, n);
					break;
					
				}
				
				/*Por fim, falta verificar o peso*/
				
				peso_temporario = (lista_produtos[index_produto].peso*quantidade_temporaria);
				
				for(i = 0; lista_encomendas[n].produtos_na_encomenda[i] != -1; i++)
					
					peso_temporario += (lista_encomendas[n].qtd[i]*lista_produtos[index_produto].peso);
				
				if (peso_temporario > MAXWEIGHT){
					
					printf("Imposs?vel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",identificador_temporario, n);
					break;
					
				}
				
				/*Neste ponto n?o existe nenhum erro, podemos atualizar a encomenda. Falta ainda ver se o produto j? existe na encomenda
				 Se existir, vamos acrescentar a qtd, senao, criamos e acrescentamos a qtd*/
				
				estado = 0;
				
				for(i = 0; lista_encomendas[n].produtos_na_encomenda[i] != -1; i++)
					
					if(lista_encomendas[n].produtos_na_encomenda[i] == identificador_temporario){
						estado = 1;
						break;
						
					}
					
				
				if (estado == 1){
					
					lista_encomendas[n].qtd[i] += quantidade_temporaria;
				}
				
				else{
					
					lista_encomendas[n].produtos_na_encomenda[i] = identificador_temporario;
					lista_encomendas[n].qtd[i] = quantidade_temporaria;
					
				}
				
				estado = -1;
				
				/*Por fim, reduzimos o stock do produto*/
				
				lista_produtos[index_produto].qtd -= quantidade_temporaria;
				
				break;
			
			case 'r':
				
				for(k = 2, i = 0; comando[k] != ':'; k++, i++)
					idp_temp[i] = comando[k];
				idp_temp[i] = '\0';
				
				i--;
				k++;
				
				identificador_temporario = converte_string_int(idp_temp, i);
				
				/*Agora vamos ver se este identificador_temporario existe no sistema*/
				
				estado = 0;
				
				for(i=0; i <= total_produtos; i++){
					
					if (lista_produtos[i].idp == identificador_temporario){
						estado = 1;
						index_produto = i; /*atribu?mos o i ? vari?vel temporaria index_produto para podermos reutilizar no ciclo for seguinte*/
						break;
					}
					
				}
				
				if (estado == 0){
					
					printf("Imposs?vel remover stock do produto %d. Produto inexistente.\n", identificador_temporario);
					estado = -1;
					break;
					
				}
				estado = -1;
				
				
				/* Agora vamos buscar a parte da string que ? referente ? quantidade que vai ser subtra?da e vamos converter para um inteiro*/
				for(i = 0; comando[k] != '\0'; k++, i++)

					qtd_temp[i] = comando[k];
				
				qtd_temp[i] = '\0';
				i--;
				k++;
				
				quantidade_temporaria = converte_string_int(qtd_temp, i);
				
				/*Vamos ver se podemos remover esta quantidade do stock*/
				
				if(quantidade_temporaria > lista_produtos[identificador_temporario].qtd){
					
					printf("Imposs?vel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade_temporaria,
																												lista_produtos[identificador_temporario].idp);
					
					break;
					
				}
				
				lista_produtos[identificador_temporario].qtd -= quantidade_temporaria;
				
				break;
				
			case 'R': /*Remover produto de uma encomenda*/
				
				for(k = 2, i = 0; comando[k] != ':'; k++, i++)
					ide_temp[i] = comando[k];
				ide_temp[i] = '\0';
				
				i--;
				k++;
				
				identificador_temporario = converte_string_int(ide_temp, i);
				
				/*n toma o valor do identificador_temporario, porque esta vari?vel vai ser agora reutilizada*/
				
				n = identificador_temporario;
				
				for(i = 0; comando[k] != '\0'; k++, i++)

					idp_temp[i] = comando[k];
				
				idp_temp[i] = '\0';
				i--;
				k++;
				
				identificador_temporario = converte_string_int(idp_temp, i);
				
				/*Vamos ver se a encomenda existe*/
				
				estado = 0;
				
				for(i = 0; i <= total_encomendas; i++){
					
					if (lista_encomendas[i].ide == n){
						
						estado = 1;
						index_encomenda = i;
					}
					
				}
				
				if(estado == 0){
					
					printf("Imposs?vel remover produto %d a encomenda %d. Encomenda inexistente.\n", identificador_temporario, n);
					estado = -1;
					break;
					
				}
				
				estado = 0;
				
				for(m = 0; m <= total_produtos; m++){
					
					if (lista_produtos[m].idp == identificador_temporario){
						
						estado = 1;
						index_produto = m;
					}
					
				}
				
				if(estado == 0){
					
					printf("Imposs?vel remover produto %d a encomenda %d. Produto inexistente.\n", identificador_temporario, n);
					estado = -1;
					break;
					
				}
				
				estado = -1;
				
				/*Agora vamos remover o produto da encomenda e depois reorganizamos a encomenda para n?o termos listas com lacunas no meio*/
				
				for(i = 0; lista_encomendas[index_encomenda].produtos_na_encomenda[i] != identificador_temporario; i++)
					;
				
				lista_produtos[index_produto].qtd += lista_encomendas[index_encomenda].qtd[i];
				
				
				for(k = i; i < SZPROD-1 ; k++){
					
					lista_encomendas[index_encomenda].produtos_na_encomenda[k] = lista_encomendas[index_encomenda].produtos_na_encomenda[k+1];
					lista_encomendas[index_encomenda].qtd[k] = lista_encomendas[index_encomenda].qtd[k+1];
					
					if(lista_encomendas[index_encomenda].produtos_na_encomenda[k] == -1)
						break;

				}
				
				/*Se quis?ssemos remover uma encomenda que j? n?o tem produtos*/
				/*
				if (lista_encomendas[index_encomenda].produtos_na_encomenda[0] != -1){
					
					total_encomendas--;
					reset_encomenda(index_encomenda);
					
				}*/
				
				break;
			
			case 'C':
				
				for(k = 2, i = 0; comando[k] != '\0'; k++, i++)
					ide_temp[i] = comando[k];
				ide_temp[i] = '\0';
				
				i--;
				k++;
				
				identificador_temporario = converte_string_int(ide_temp, i);
				
				for(i = 0; i < SZENC; i++){
					
					if(lista_encomendas[i].ide == identificador_temporario){
						
						index_encomenda = i;
						break;
						
					}
					
				}
				
				if(i == SZENC){
					
					printf("Imposs?vel calcular custo da encomenda %d. Encomenda inexistente.\n", identificador_temporario);
					break;
					
				}
				
				preco_temporario = 0;
				
				for(i= 0; lista_encomendas[index_encomenda].produtos_na_encomenda[i] != -1; i++){
					
					index_produto = lista_encomendas[index_encomenda].produtos_na_encomenda[i];
					
					preco_temporario += lista_encomendas[index_encomenda].qtd[i] *
										lista_produtos[index_produto].preco;
					
				}
				
				printf("Custo da encomenda %d %d.\n", lista_encomendas[index_encomenda].ide,
													  preco_temporario);
				
				break;
				
			case 'p':
				
				for(k = 2, i = 0; comando[k] != ':'; k++, i++)
					idp_temp[i] = comando[k];
				idp_temp[i] = '\0';
				
				i--;
				k++;
				
				identificador_temporario = converte_string_int(idp_temp, i);
				
				/*Agora vamos ver se este identificador_temporario existe no sistema*/
				
				estado = 0;
				
				for(i=0; i <= total_produtos; i++){
					
					if (lista_produtos[i].idp == identificador_temporario){
						estado = 1;
						index_produto = i; /*atribu?mos o i ? vari?vel temporaria index_produto para podermos reutilizar no ciclo for seguinte*/
						break;
					}
					
				}
				
				if (estado == 0){
					
					printf("Imposs?vel alterar preco do produto %d. Produto inexistente.\n", identificador_temporario);
					estado = -1;
					break;
					
				}
				estado = -1;
				
				for(i = 0; comando[k] != '\0'; k++, i++)

					preco_temp[i] = comando[k];
				
				preco_temp[i] = '\0';
				i--;
				k++;
				
				lista_produtos[identificador_temporario].preco = converte_string_int(preco_temp, i);
				
				break;
				
			case 'E':
				
				for(k = 2, i = 0; comando[k] != ':'; k++, i++)
					ide_temp[i] = comando[k];
				ide_temp[i] = '\0';
				
				i--;
				k++;
				
				identificador_temporario = converte_string_int(ide_temp, i);
				
				/*n toma o valor do identificador_temporario, porque esta vari?vel vai ser agora reutilizada*/
				
				n = identificador_temporario;
				
				for(i = 0; comando[k] != '\0'; k++, i++)

					idp_temp[i] = comando[k];
				
				idp_temp[i] = '\0';
				i--;
				k++;
				
				identificador_temporario = converte_string_int(idp_temp, i);
				
				/*Vamos ver se a encomenda existe*/
				
				estado = 0;
				
				for(i = 0; i <= total_encomendas; i++){
					
					if (lista_encomendas[i].ide == n){
						
						estado = 1;
						index_encomenda = i;
					}
					
				}
				
				if(estado == 0){
					
					printf("Imposs?vel listar encomenda %d. Encomenda inexistente.\n", n);
					estado = -1;
					break;
					
				}
				
				estado = 0;
				
				for(i = 0; i <= total_produtos; i++){
					
					if (lista_produtos[i].idp == identificador_temporario){
						
						estado = 1;
						index_produto = i;
					}
					
				}
				
				if(estado == 0){
					
					printf("Impossivel listar produto %d. Produto inexistente.\n", identificador_temporario);
					estado = -1;
					break;
					
				}
				
				estado = -1;
				
				for(i = 0; lista_encomendas[index_encomenda].produtos_na_encomenda[i] != -1; i++){
					
					if (lista_encomendas[index_encomenda].produtos_na_encomenda[i] == identificador_temporario)
						break; /*Guarda o i*/
					
				}
				
				
				if(lista_encomendas[index_encomenda].qtd[i] == -1)
					lista_encomendas[index_encomenda].qtd[i] = 0;
				
				printf("%s %d.\n", lista_produtos[identificador_temporario].descricao,
								   lista_encomendas[index_encomenda].qtd[i]);
				
				break;
				
			case 'm':
				
				if (total_encomendas == -1)
					break;
				
				for(k = 2, i = 0; comando[k] != '\0'; k++, i++)
					idp_temp[i] = comando[k];
				idp_temp[i] = '\0';
				
				i--;
				k++;
				
				identificador_temporario =  converte_string_int(idp_temp, i);
				
				/*Agora vamos ver se este identificador_temporario existe no sistema*/
				
				estado = 0;
				
				for(i=0; i <= total_produtos; i++){
					
					if (lista_produtos[i].idp == identificador_temporario){
						estado = 1;
						index_produto = i; /*atribu?mos o i ? vari?vel temporaria index_produto para podermos reutilizar no ciclo for seguinte*/
						break;
					}
					
				}
				
				if (estado == 0){
					
					printf("Imposs?vel listar maximo do produto %d. Produto inexistente.\n", identificador_temporario);
					estado = -1;
					break;
					
				}
				estado = -1;
				
				max = -1;
				
				for(i = 0; i <= total_encomendas; i++){
					
					for(k = 0; lista_encomendas[i].produtos_na_encomenda[k] != -1; k++){
						
						if(lista_encomendas[i].produtos_na_encomenda[k] == identificador_temporario){
							
							if(lista_encomendas[i].qtd[k] > max){
								
								max = lista_encomendas[i].qtd[k];
								n = i;
								m = k;
								
							}
							
							break;
							
						}
					}
				}
				
				if (max == -1)
					break;
				
				printf("Maximo produto %d %d %d.\n", identificador_temporario,
													 lista_encomendas[n].ide,
													 max);
				
				break;
				
			case 'l': /*insertion sort para pre?os*/
				
				printf("Produtos\n");
				
				if(total_produtos >= 0){
				
					left = 0;
					right = total_produtos;
						
					for(a = 0 + left; a <= right; a++){
							
						struct produto v = lista_produtos[a];
						
						b = a-1;
							
						while(b >= left && v.preco < lista_produtos[b].preco){
							
							lista_produtos[b+1] = lista_produtos[b];
							b--;
								
						}
							
						lista_produtos[b+1] = v;
							
					}
					
					for(i = 0; i<= total_produtos;i++){
						
						printf("* %s %d %d\n", lista_produtos[i].descricao,
											lista_produtos[i].preco,
											lista_produtos[i].qtd);
						
						
					}
					
				}
				break;
			case 'L':
				break;
				
			/*case '':
				
				for(k = 2, i = 0; comando[k] != '\0'; k++, i++)
					ide_temp[i] = comando[k];
				ide_temp[i] = '\0';
				
				i--;
				k++;
				
				switch(i){
					
					case 0:
						identificador_temporario = 	ide_temp[i]-'0';
						break;					
						
					case 1:
						
						identificador_temporario = 	(ide_temp[i]-'0') + 
													(ide_temp[i-1]-'0')*10;
																
						break;	
					
					case 2:
						
						identificador_temporario = 	(ide_temp[i]-'0') + 
													(ide_temp[i-1]-'0')*10 +
													(ide_temp[i-2]-'0')*100;
						break;	
						
						
				};
				
				for(i = 0; i < SZENC; i++){
					
					if(lista_encomendas[i].ide == identificador_temporario){
						
						index_encomenda = i;
						break;
						
					}
					
				}
				
				if(i == SZENC){
					
					printf("Imposs?vel listar encomenda %d. Encomenda inexistente.\n", identificador_temporario);
					break;
					
				}
				
				printf("Encomenda\n");
				
				if(total_encomendas >= 0){
				
					left = 0;*/
					
					/*Vamos ver quantos produtos existem nesta encomenda e atribuir esse valor a right*/
					
					/*max = -1;
					for(i = 0; i <= SZPROD-1;i++){
						if (lista_encomendas[index_encomenda].produtos_na_encomenda[i] != -1)
							max++;
					}*/
					
					/*Vamos ler*/
					/*for (a = 0; i <= max; i++){
						
						for(k = 0, m = 0; k<SZPROD && m < SZQTD; k++){
							if(lista_produtos[k].idp == lista_encomendas[index_encomenda].produtos_na_encomenda[a]){
								for(n = 0; n < SZDESC; n++){
									
									array[m][n] = lista_produtos[k].descricao[n];
									m++;
									
									if(array[m][n] == '\0')
										break;
								}
							}
								
							
							
						}
						
						b = a-1;
						
						while(b >= 0 && )
						
						
					}
					
						
					for(a = 0 + left; a <= right; a++){
							
						struct produto v = lista_encomendas[index_encomenda].produtos_na_encomenda[a];
						
						b = a-1;
							
						while(b >= left && v.preco < lista_encomendas[index_encomenda].produtos_na_encomenda){
							
							lista_encomendas[index_encomenda].produtos_na_encomenda[b+1] = lista_encomendas[index_encomenda].produtos_na_encomenda[b];
							b--;
								
						}
							
						lista_encomendas[index_encomenda].produtos_na_encomenda[b+1] = v;
							
					}
					
					for(i = 0; i<= total_encomendas;i++){
						
						printf("* %s %d %d\n", lista_produtos[i].descricao,
											lista_produtos[i].preco,
											lista_produtos[i].qtd);
						
						
					}
				}
				
				break;*/
				
				
		};/*Fim do switch(letra_comando)*/
		
		/*printf("\n***********\nLista de produtos no sistema: \n");
		
		for (i = 0; i<= total_produtos;i++){
			printf(" Descri??o:   %s\n",lista_produtos[i].descricao);
			printf(" Quantidade:  %d\n",lista_produtos[i].qtd);
			printf(" Pre?o:       %d\n",lista_produtos[i].preco);
			printf(" Peso:        %d\n",lista_produtos[i].peso);
			printf(" -> IDP:      %d\n",lista_produtos[i].idp);
			
		}
		
		printf("\n***********\nLista de encomendas no sistema: \n");
		
		for(i = 0; i <= total_encomendas; i++){
			
			printf(" -> IDE:      %d\n", lista_encomendas[i].ide);
			printf("Lista de produtos e respectiva quantidade:\n");
			
			for(k = 0; lista_encomendas[i].produtos_na_encomenda[k] != -1; k++)
				printf("IDP:  %d    Qtd:  %d    Nome: %s\n", lista_encomendas[i].produtos_na_encomenda[k],
															 lista_encomendas[i].qtd[k],
															 lista_produtos[lista_encomendas[i].produtos_na_encomenda[k]].descricao);
			
		}
		*/
	
	
	
	} /*Fim do while(1)*/
		
				
	return 0;

} /*Fim to main*/




int converte_string_int(char *str, int i){
	
	int n;
	
	switch(i){
					
		case 0:
			n = 	 str[i]-'0';
			break;					
			
		case 1:
			
			n =  	(str[i]-'0') + 
					(str[i-1]-'0')*10;
			
			break;	
			
		case 2:
			
			n =		(str[i]-'0') + 
					(str[i-1]-'0')*10 +
					(str[i-2]-'0')*100;
			break;	
			
		case 3:
			
			n =		(str[i]-'0') + 
					(str[i-1]-'0')*10 +
					(str[i-2]-'0')*100 +
					(str[i-3]-'0')*1000;
			break;	
			
		case 4:
			
			n =	 	(str[i]-'0') + 
					(str[i-1]-'0')*10 +
					(str[i-2]-'0')*100 +
					(str[i-3]-'0')*1000 + 
					(str[i-4]-'0')*10000;
			break;	
			
		case 5:
			
			n = 	(str[i]-'0') + 
					(str[i-1]-'0')*10 +
					(str[i-2]-'0')*100 +
					(str[i-3]-'0')*1000 + 
					(str[i-4]-'0')*10000 +
					(str[i-5]-'0')*100000;
			break;
			
		case 6:
			
			n = 	(str[i]-'0') + 
					(str[i-1]-'0')*10 +
					(str[i-2]-'0')*100 +
					(str[i-3]-'0')*1000 + 
					(str[i-4]-'0')*10000 +
					(str[i-5]-'0')*100000 +
					(str[i-6]-'0')*1000000;
			break;	
			
	};

	return n;
}
