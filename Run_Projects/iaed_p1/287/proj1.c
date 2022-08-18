#include <stdio.h>
#include <string.h>

typedef struct {
	int identificador;  
	char descricao[63];     /*Defini??o das duas estruturas encomenda e produto que serao usadas no projeto*/
	int preco;              /*com todas as caracteristicas necessarias*/
	int peso;
	int stock;
	
}produto;

typedef struct {
	int identificador;
	int peso;
	int produtos[200][2]; /*cada encomenda ter? um vetor com 200 subvetores de 2 posicoes cada. 200 ? o maximo de produtos de uma encomenda*/
}encomenda;               /*e em cada subtuplo ser? armazenado na primeira posicao do subvetor o idp de um produto e na segunda a sua quantidade no vetor*/

#define max_produtos 10000
#define max_encomendas 500            /*defini?ao de algumas constantes uteis ao projeto*/
#define max_descricao 63
#define max_produtos_encomenda 200
#define max_peso 200

produto vec_prod[max_produtos];         /*Criei 2 vetores que armazenam todos os produtos e encomendas como variaveis globais.*/
encomenda vec_encomendas[max_encomendas];

/*Funcoes Secundarias*/

void apaga_letra_comando(char input[]){
	int i, tamanho = strlen(input);     /*apaga os 2 primeiros carateres do input*/
	for (i = 2; i < tamanho; i++){	        /*introduzido pelo utilizador*/
		input[i-2] = input[i];
	}
	input[i-2] = '\0';
}

void separa_input(char input[], char dados[][max_descricao]){
	int i = 0, e = 0, o = 0;
	while (input[o] != '\0'){	
		if (input[o] == ':'){          /*Separa os dados do input introduzido pelo utilizador*/
			dados[i][e] = '\0';        /*E guarda cada dado separado num vetor com os subvetores que forem necessarios*/
			e=0;					   /*Cada dado num subvetor ordenados pela mesma ordem do input que depender?*/
			i++;					   /*de operacao para operacao*/
		} 
		else{
			dados[i][e] = input[o];
			e++;
		}
		o++;
	}
	dados[i][e] = '\0'; 
}

int str_para_int(char input[]){
	int resultado = 0, i, p;
	p = strlen(input);                  /*transforma um numero da sua string para o tipo inteiro*/
	for (i = 0; i < p; i++){
		resultado = (resultado * 10) + (input[i] - '0');
	}
	return resultado;
}

void merge(int a[], int l, int m, int r){
	int i, j, k, aux[max_produtos];
	for (i = m+1; i > l; i--)
		aux[i-1] = a[i-1];
	for (j = m; j < r; j++)
		aux[r+m-j] = a[j+1];
	for (k = l; k <= r; k++)
		if (aux[j] - aux[i] < 0 || i > m)
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
}

void merge_sort(int a[], int l, int r){  /*Algoritmo de ordena?ao*/
	int m = (r+l)/2;
	if (r <= l)
		return;
	merge_sort(a, l, m);
	merge_sort(a,m+1,r);
	merge(a, l, m, r);
} 

void merge_funcao_L(int a[], int l, int m, int r){
	int i, j, k, aux[max_produtos_encomenda]; /*Ordena??o de indices do vetor global que guarda todos os produtos*/
	for (i = m + 1; i > l; i--)               /*por ordem alfabetica das descri??es dos produtos*/
		aux[i - 1] = a[i - 1];
	for (j = m; j < r; j++)
		aux[r + m - j] = a[j+1];
	for (k = l; k <= r; k++){
		if (strcmp(vec_prod[j].descricao, vec_prod[i].descricao) < 0)
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
	}
}

void merge_sort_funcao_L(int a[], int l, int r){ /*Algoritmo de ordena??o*/
	int m = (r+l)/2;
	if (r<=l)
		return;
	merge_sort_funcao_L(a, l, m);
	merge_sort_funcao_L(a, m+1,r);
	merge_funcao_L(a, l, m, r);
}

/*Funcoes Primarias*/

void adicionanovoproduto(char input[]){
	int i, e, euros = 0, kg = 0, quantidade = 0;  
	char dados[4][max_descricao];   /*criei um vetor com 4 posicoes para guardar os dados do novo produto a descricao*/    
	apaga_letra_comando(input);     /*peso, stock e preco*/
	separa_input(input, dados);		
	euros = str_para_int(dados[1]);      /*Passo os dados de string para inteiro*/
	kg = str_para_int(dados[2]);
	quantidade = str_para_int(dados[3]);

	for (e = 0; e < max_produtos; e++){    /*adiciono todos os dados ?s componentes da estrutura produto*/
		if (vec_prod[e].preco == -1){      /*? primeira posicao do vetor que guarda os*/
			vec_prod[e].preco = euros;     /*produtos que ainda nao tenha nenhum produto*/
			vec_prod[e].peso = kg;         /*verifico isto vendo se o pre?o do produto ? -1*/
			vec_prod[e].stock = quantidade;
			vec_prod[e].identificador = e;
			for (i = 0; i < max_descricao; i++){   /* o identificador do produto ? sempre igual ao indice do vetor onde os produtos sao guardados*/
				vec_prod[e].descricao[i] = dados[0][i];
			}
			vec_prod[e].descricao[i] = '\0';
			break;		
		}
	}
	printf("Novo produto %d.\n", vec_prod[e].identificador);  /*faco o print pedido*/
}

void adicionastock(char input[]){
	char dados[2][max_descricao];
	int quantidade, idp;
	apaga_letra_comando(input);
	separa_input(input, dados);

	idp = str_para_int(dados[0]);
	quantidade = str_para_int(dados[1]);

	if (vec_prod[idp].identificador == idp)      /*verifico se o produto existe, se existir adiciono o stock*/
			vec_prod[idp].stock += quantidade;   /*caso contrario retorno um erro*/
	else 
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

void remove_stock(char input[]){
	char dados[2][max_descricao];
	int quantidade, idp;
	apaga_letra_comando(input);
	separa_input(input, dados);
	idp = str_para_int(dados[0]);
	quantidade = str_para_int(dados[1]);

	if (vec_prod[idp].identificador == idp){    /*verifico se o produto existe, se existir verifico se o seu stock ? menor do que*/
		if (vec_prod[idp].stock >= quantidade)	/* a quantidade que se quer remover, se for menor retorno um erro e se nao existir produto*/
				vec_prod[idp].stock -= quantidade;/*retorno outro erro. Caso contrario removo do stock a quantidade do input*/
		else 
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
		}
	else 
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
}

void altera_preco(char input[]){
	char dados[2][max_descricao];
	int euros, idp;
	apaga_letra_comando(input);
	separa_input(input, dados);
	idp = str_para_int(dados[0]);
	euros = str_para_int(dados[1]);            /*verifico se o produto existe, se existir altero o seu pre?o.*/
											   /*caso contrario retorno um erro*/
	if (vec_prod[idp].identificador == idp)
		vec_prod[idp].preco = euros;
	else
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}

void ordena_produtos_sistema(){
	int vetor_precos[max_produtos], i, p = 0, contador = 0, e, m, l;

	for (i = 0; i < max_produtos; i++){      /*o objetivo desta funcao ? ordenar todos os produtos pelo preco de forma crescente*/
		vetor_precos[i] = -1;                /* se o preco for igual devera aparecer primeiro o produto com numero de identicacao mais baixo*/ 
	}                                        /*criei um vetor em que o seu objetivo ser? armazenar todos os pre?os e inicializo todas as suas posicoes a -1*/

	for (i = 0; i < max_produtos; i++){
		if (vec_prod[i].preco != -1){               /*Coloco todos os pre?os dos produtos existentes*/
			vetor_precos[p] = vec_prod[i].preco;     
			p++;
		}
	}

	for (i = 0; i < max_produtos; i++){           /*Vejo qual o numero de pre?os*/
		if (vetor_precos[i] != -1)
			contador++;
	}

	merge_sort(vetor_precos, 0, contador-1);    /*ordeno o vetor com os pre?os*/
	
    printf("Produtos\n");
	for (e = 0; e < contador; e++){
		for (i = 0; i < max_produtos; i++){                  /*percorro todos os pre?os ordenados e para cada pre?o, se este nao for igual ao anterior*/
			if (vetor_precos[e] != vetor_precos[e-1]){       /*percorro todos os produtos e os que tenham o pre?o fa?o o print pedido*/
				if (vec_prod[i].preco == vetor_precos[e]){   /*Como no vetor global os produtos estao ordenados de forma crescente de idp*/
					printf("* ");                            /*caso tenham pre?o igual ser?o ordenados por idp*/
					l = strlen(vec_prod[i].descricao);
					for (m = 0; m < l; m++){
						putchar(vec_prod[i].descricao[m]);
					}
					printf(" %d %d\n", vec_prod[i].preco, vec_prod[i].stock);
				}
			}
		}
	}
}

void cria_encomenda(){                                    /*percorro todas as posi?oes do vetor global que guarda as encomendas e encontro*/
	int i;                                                /* qual a primeira posicao que ainda nao tenha uma encomenda guardada*/
	for (i = 0; i < max_encomendas; i++){
		if (vec_encomendas[i].identificador == -1){
			vec_encomendas[i].identificador = i;
			vec_encomendas[i].peso = 0;
			break;
		}
	}
	printf("Nova encomenda %d.\n", vec_encomendas[i].identificador);
}

void adiciona_prod_encomenda(char input[]){
	char dados[3][max_descricao];
	int ide, idp, quantidade, i, contador = 0, e, contador2 = 0, contador3 = 0, contador4 = 0, peso_prod, peso_enc, contador5 = 0;
	apaga_letra_comando(input);
	separa_input(input, dados);
	ide = str_para_int(dados[0]);
	idp = str_para_int(dados[1]);
	quantidade = str_para_int(dados[2]);

	for (i = 0; i < max_encomendas; i++){
		if (vec_encomendas[i].identificador == ide){        /*verifico se a encomenda existe e crio uma variavel peso da encomenda*/
			contador++;                                     /*que me facilitar? os calculos mais ? frente*/
			peso_enc = vec_encomendas[i].peso;
		}
	}
	if (contador == 0)                                      /*retorno o print necess?rio senao houver encomenda*/
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	
	for (i = 0; i < max_produtos; i++){
		if (vec_prod[i].identificador == idp){      /*verifico se existe produto, se existir verifico se a quantidade em stock ? menor*/
			peso_prod = vec_prod[i].peso;           /*do que a quantidade que se quer adicionar na encomenda*/
			contador5++;
			e = i;
			if (vec_prod[i].stock < quantidade && contador != 0){   /*dou print do erro se a quantidade em stock nao for necessaria e caso nao tenha dado erro de encomenda nao existente*/
				contador2++;
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
			}
		}
	}
	if (contador5 == 0 && contador != 0)         /*dou print do erro caso o produto nao exista e caso nao tenha dado erro de encomenda nao existente*/
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	
	if ((peso_enc + (quantidade * peso_prod)) > 200 && contador5 != 0 && contador != 0 && contador2 == 0){
		contador4++;                             /*verifico se o peso total da encomenda sera maior que 200 e se nao deu nenhum erro anterior*/
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
	}
	if (contador2 == 0 && contador == 1 && contador4 == 0 && contador5 != 0){ /*verifico se algum dos erros acontece, senao acontecer adiciono o produto a encomenda*/
		vec_prod[e].stock -= quantidade;                                      /*retiro a quantidade adicionada do stock do produto*/
		for (i = 0; i < max_encomendas; i++){                                 /*de seguida verifico se o produto j? se encontra na encomeda*/
			if (vec_encomendas[i].identificador == ide){                      /*se ja existir na encomenda adiciono a quantidade ? quantidade de produto que ja estava*/
				vec_encomendas[i].peso = (peso_enc + (quantidade * peso_prod)); /* na encomenda, caso contrario adiciono o produto ? encomenda*/
				for (e = 0; e < 200; e++){
					if (vec_encomendas[i].produtos[e][0] == idp){
						vec_encomendas[i].produtos[e][1] += quantidade;
						contador3++;
						break;
					}
				}
				if (contador3 == 0){
					for (e = 0; e < 200; e++){
						if (vec_encomendas[i].produtos[e][0] == -1){
						vec_encomendas[i].produtos[e][0] = idp;
						vec_encomendas[i].produtos[e][1] = quantidade;
						break;
						}
					}
				}
				break;
			}
		}
	}
}

void remove_prod_encomenda(char input[]){
	int ide, idp, contador = 0, contador2 = 0, i,e, peso_produto;
	char dados[2][max_descricao];
	apaga_letra_comando(input);
	separa_input(input,dados);
	ide = str_para_int(dados[0]);
	idp = str_para_int(dados[1]);  

	if (vec_encomendas[ide].identificador == ide){   /*verifico se existe a encomenda*/      
			contador++;
	}
	                                                 
	if (contador == 0)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

	for (i = 0; i < max_produtos; i++){
		if (vec_prod[i].identificador == idp){
			contador2++;
			peso_produto = vec_prod[i].peso;
		}
	}

	if (contador2 == 0 && contador != 0)       /*verifico de existe o produto e se nao deu erro de encomenda inexistente para nao ocorrerem dois erros em simultaneo*/
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	
	if (contador2 == 1 && contador == 1){
		for (i = 0; i < max_encomendas; i++){                  /*verifico se o produto esta na encomenda e se estiver removo o*/
			if (vec_encomendas[i].identificador == ide){       /*atualizo o peso da encomenda e volto a repor a quantidade do prouduto*/
				for (e = 0; e < max_peso; e++){                /*existente na encomenda no stock do produto*/
					if (vec_encomendas[i].produtos[e][0] == idp){
						vec_prod[idp].stock += vec_encomendas[i].produtos[e][1];
						vec_encomendas[i].peso -= (peso_produto * vec_encomendas[i].produtos[e][1]);
						vec_encomendas[i].produtos[e][0] = -1;
						vec_encomendas[i].produtos[e][1] = -1;
					}
				}
			break;
			}
		}
	}
}

void calcula_custo(char input[]){
	int soma = 0, ide, i, e, idp_qnt[200][2], precos[200];    
	char dados[1][max_descricao];
	apaga_letra_comando(input);
	separa_input(input, dados);
	ide = str_para_int(dados[0]);

	for (i = 0; i < max_produtos_encomenda; i++){           /*passo todas os idps e quantidades da encomenda para um vetor denominado idp_qnt*/
		idp_qnt[i][0] = vec_encomendas[ide].produtos[i][0];
		idp_qnt[i][1] = vec_encomendas[ide].produtos[i][1];
	}
	for (i = 0; i < max_produtos_encomenda; i++){
		for (e = 0; e < max_produtos; e++){                                       /*para cada idp da encomenda vou buscar o seu pre?o e coloco no vetor precos*/
			if (vec_prod[e].identificador == vec_encomendas[ide].produtos[i][0]){ /*de forma a ficar o idp e o respetivo pre?o no mesmo indice dos dois vetores diferentes*/
				precos[i] = vec_prod[e].preco;
			}
		}
	}
	for (i = 0; i < max_produtos_encomenda; i++){          /*calculo o custo*/
		if (precos[i] != -1)
			soma += (idp_qnt[i][1] * precos[i]);
	}
	if (vec_encomendas[ide].identificador != ide)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide); /*caso a encomenda exista fa?o print do custo, caso contrario fa?o print do erro*/
	else
		printf("Custo da encomenda %d %d.\n", ide, soma);
}

void lista_descricao_quantidade(char input[]){
	int i, m, n, ide, idp, contador = 0, contador1 = 0, contador2 = 0;
	char dados[2][63];
	apaga_letra_comando(input);
	separa_input(input, dados);
	ide = str_para_int(dados[0]);
	idp = str_para_int(dados[1]);
	if (vec_prod[idp].identificador == idp)
		contador++;
	
	if (vec_encomendas[ide].identificador != ide){ /*verifico se existe a encomenda*/
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		contador2++;
	}

	if (contador == 0 && contador2 == 0)   /*verifico se existe o produto e nao houve erro de encomenda inexistente*/
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	
	for (i = 0; i < max_produtos_encomenda; i++){
		if (vec_encomendas[ide].produtos[i][0] == idp){
			contador1++;                                    /*Verifico se o produto existe na enomenda*/
			break;
		}
	}
	                                                      /*Verifico se todas as condicoes anteriores se verificam*/
	if (contador != 0 && contador1 != 0 && contador2 == 0){
		if (vec_encomendas[ide].identificador == ide){            /*fa?o o print pedido.*/
			for (i = 0; i < max_produtos_encomenda; i++){
				if (vec_encomendas[ide].produtos[i][0] == idp){
					for (m = 0; m < max_produtos; m++){
						if (vec_prod[m].identificador == idp){
							for (n = 0; n < max_descricao && vec_prod[m].descricao[n] != '\0' ; n++)
								putchar(vec_prod[m].descricao[n]);
							printf(" %d.\n", vec_encomendas[ide].produtos[i][1]);
						}
					}
				}
			}
		}
	}
                                                            /*se o produto nao existir na encomenda faco print da sua descricao*/
	if (contador != 0 && contador1 == 0 && contador2 == 0){ /*e a sua quantidade nessa encomenda ? 0*/
		for (m = 0; m < max_produtos; m++){
			if (vec_prod[m].identificador == idp){
				for (n = 0; n < max_descricao && vec_prod[m].descricao[n] != '\0' ; n++)
					putchar(vec_prod[m].descricao[n]);
				printf(" 0.\n");
			}
		}
	}
}

void max_prod(char input[]){
	int i, e, max = 0, ide, idp, contador = 0, contador1 = 0;
	char dados[1][max_descricao];
	apaga_letra_comando(input);
    separa_input(input, dados);
    idp = str_para_int(dados[0]);

    if (vec_prod[idp].identificador != idp){                                               /*verifico se o produto existe*/
    	printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    	contador++;
    }
    for (i = 0; i < max_encomendas; i++){
    	for(e = 0; e < max_produtos_encomenda; e++){
    		if (vec_encomendas[i].produtos[e][0] == idp && vec_encomendas[i].produtos[e][1] > max){
    			max = vec_encomendas[i].produtos[e][1];              /*inicializo uma variavel max = 0, percorro todas as encomendas*/
    			ide = i;                                             /*Para cada encomenda percorro todos os seus produtos e se */
    			contador1++;                                         /*algum for o produto que se quer descobrir o maximo verifica se*/
    		}                                                        /*a sua quantidade nessa encomenda ? maior do que a variavel max*/
    	}                                                            /*cao seja atualiza se o valor da variavel para a quantidade desse produto na encomenda*/
    }
    if (contador == 0 && contador1 != 0)   /*Se a encomenda existir e se o produto ocorrer pelo menos uma vez nas encomendas fa?o print do maximo*/
    	printf("Maximo produto %d %d %d.\n", idp, ide, max);
}

void ordena_produtos_encomeda(char input[]){
	int ide, i, k, vec_indices[max_produtos_encomenda], e, tamanho = 0, quantidade;
	char dados[1][max_descricao];
	apaga_letra_comando(input);
	separa_input(input, dados);
	ide = str_para_int(dados[0]);

	if (vec_encomendas[ide].identificador != ide)              /*verifico se a encomenda existe*/
	printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	
	else{
		for(i = 0; i < max_produtos_encomenda; i++){           /*vou buscar todos os indices ,do vetor global onde guardo os produtos, dos produtos*/
			for (e = 0; e < max_produtos; e++){                /*que a encomenda tenha e guardo os no vetor chamado vec_indices*/
				if (vec_prod[e].identificador == vec_encomendas[ide].produtos[i][0] && vec_prod[e].identificador != -1){
					vec_indices[tamanho] = e;
					tamanho++;
					break;
				}
			}
		}
   
		merge_sort_funcao_L(vec_indices, 0, tamanho - 1);  /*ordeno todos os indices por ordem alfabetica das descricoes dos respetivos produtos*/

		printf("Encomenda %d\n", ide);
		for(i = 0; i < tamanho; i++){
			printf("* ");
			for (e = 0; e < max_descricao && vec_prod[vec_indices[i]].descricao[e] != '\0' ; e++){
				putchar(vec_prod[vec_indices[i]].descricao[e]);                            /*Fa?o o print pedido de acordo com as instrucoes dadas no enunciado*/
			}                                                                              
			for (k = 0; k < max_produtos_encomenda; k++){
				if (vec_encomendas[ide].produtos[k][0] == vec_indices[i]){
					quantidade = vec_encomendas[ide].produtos[k][1];
					break;
				}
			}
			printf(" %d %d\n", vec_prod[vec_indices[i]].preco, quantidade);
		}
	}
}


int main(){	
	char input[100];
	int c, i, e, running = 1;
	
	for(i = 0; i < max_produtos; i++){
		vec_prod[i].identificador = -1;        
		vec_prod[i].peso = -1;
		vec_prod[i].preco = -1;              /*coloco todos as caracteristicas dos produtos no vetor onde sao armazenados a -1*/
		vec_prod[i].stock = -1;				 /* e a descricao uma string vazia */
		for (e = 0; e < max_descricao; e++){
			vec_prod[i].descricao[e] = ' ';
		}
	}
	for (i = 0; i < max_encomendas; i++){     /* o mesmo para as encomendas*/
		vec_encomendas[i].identificador = -1;
		vec_encomendas[i].peso = -1;
		for (e = 0; e < 200; e++){
			vec_encomendas[i].produtos[e][0] = -1;
			vec_encomendas[i].produtos[e][1] = -1;
		}

	}
	while (running == 1){
		c = getchar();
		for (i = 0; c != '\n' && c != EOF; i++){ 
			input[i] = c;	                     /*Leio o input introduzido pelo utilizador e guardo numa variavel local*/
			c = getchar();
		}
		input[i] = '\0';
 	
		switch (input[0]){
			case 'a':      /*seleciono a operacao e criei uma funcao para cada operacao do meu programa que chamo consoante a primeira letra do input*/				
				adicionanovoproduto(input);
				break;                      
			case 'q':
				adicionastock(input);
				break;
			case 'r':
				remove_stock(input);
				break;
			case 'p':
				altera_preco(input);
				break;
			case 'l':
				ordena_produtos_sistema();
				break;
			case 'N':
				cria_encomenda();
				break;
			case 'A':
				adiciona_prod_encomenda(input);
				break;
			case 'R':
				remove_prod_encomenda(input);
				break;
			case 'C':
				calcula_custo(input);
				break;
			case 'E':
				lista_descricao_quantidade(input);
				break;
			case 'm':
				max_prod(input);
				break;
			case 'L':
				ordena_produtos_encomeda(input);
				break;
			case 'x':
				running = 0;
				break;
		}
	}
	return 0;
}

