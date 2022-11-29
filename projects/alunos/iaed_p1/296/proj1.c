#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* constantes */
#define MAXPROD 10000 /* Numero maximos de produtos */
#define MAXECOM 500  /* Numero maximo de encomendas */
#define MAXDESC 64  /* Numero de caracteres maximo na descricao do produto incluindo '\0' */
#define MAXPESO 200 /* Peso maximo de uma encomenda */
#define INPUT 200   /* tamanho maximo para a informacao do input*/

int cmd; /* contem o valor numerico da tabela ASCII do comando dado*/
char input[INPUT]; /* Vetor que vai conter a informacao do input dado*/

/* Estrutura dos produtos*/
struct produto{
/* Cada produto e composto por um id peso preco quantidade e uma descricao*/	
	int id,peso,preco,qtd;
	char desc[MAXDESC];
}stock[MAXPROD]; /* stock e um vetor de produtos, estrutura permanente, enquanto temp serve como uma variavel temporaria
							que ira servir para colocar as informacoes dos produtos na estrutura permanente*/

struct produto temp;
/* Estrutura das encomendas*/
struct encomenda{
/* Cada encomenda e composta por um id e peso e tem a estrututra dos produtos dentro para os varios produtos que poderao existir dentro da encomenda*/	
	int id,peso;
	struct produto prt[MAXPESO];
}ecm[MAXECOM]; /* ecm e um vetor de encomendas que e a estrutura permanete. tempE: e a variavel temporaria que serve para
							colocar as informacoes da encomenda na estrutura permanente*/

struct encomenda tempE;
/***************** FUNCOES AUXILIARES *******************/

/* Funcao que ira ler a linha dada pelo input*/
int LeLinha(){
	int i,c;
	if(!(cmd == 'N' || cmd == 'x' || cmd == 'l' )) /* O getchar e utlizado para "comer" o espaco que ha entre o comando dado e as informacoes dadas*/ 
		getchar();
	for (i=0; ((c = getchar()) != EOF && c != '\n'); ++i)
		input[i] = c;    /* Enquanto nao houver EOF ou '\n' a informacao fica guardada caracter a caracter no vetor input*/
	input[i] = '\0'; /*Como o input e uma string tenho de adiconar no fim o caracter '\0'*/
	return 0;
}

/* Funcao que extrai a informacao para cada comando dado.O uso do strtokr e do ponteiro res
 e para aceder a informacao alojada dentro do input e partir nos bocados necessarios*/
int ExtractInfo(int n){
	char *res = input;
	switch(n){
		case 'a':
			strcpy(temp.desc,__strtok_r(res,":",&res)); 
			temp.preco = atoi(__strtok_r(res,":",&res)); 
			temp.peso = atoi(__strtok_r(res,":",&res));
			temp.qtd = atoi(__strtok_r(res,":",&res));
			break;
		case 'q':
			temp.id = atoi(__strtok_r(res,":",&res));
			temp.qtd = atoi(__strtok_r(res,":",&res));
			break;
		case 'r':
			temp.id = atoi(__strtok_r(res,":",&res));
			temp.qtd = atoi(__strtok_r(res,":",&res));
			break;
		case 'R':
			tempE.id = atoi(__strtok_r(res,":",&res));
			temp.id = atoi(__strtok_r(res,":",&res));
			break;
		case 'A':
			tempE.id = atoi(__strtok_r(res,":",&res));
			temp.id = atoi(__strtok_r(res,":",&res));
			temp.qtd = atoi(__strtok_r(res,":",&res));
			break;
		case 'C':
			tempE.id = atoi(input);
			break;
		case 'p':
			temp.id = atoi(__strtok_r(res,":",&res));
			temp.preco = atoi(__strtok_r(res,":",&res));
			break;
		case 'E':
			tempE.id = atoi(__strtok_r(res,":",&res));
			temp.id = atoi(__strtok_r(res,":",&res));
			break;
		case 'm':
			temp.id = atoi(input);
			break;
		case 'L':
			tempE.id = atoi(input);
			break;
	}
	return 0;
}

/* Fuuncao que organiza os produtos por ordem de preco no stock e por ordem alfabetica no caso das encomendas usando o algoritmo MergeSort*/
int Merge(int lim_inf, int lim_sup,int meio, int tab_final[], int string){
	int i,j,k, tab_aux[MAXPROD],PRTAUX[MAXPESO];
	if (string == 0){ /* Verificacao em que se estamos a ordenar os produtos do stock ou na encomenda*/
		for(i = meio + 1; i > lim_inf; i--)
			tab_aux[i-1] = tab_final[i-1]; /* 2 ciclos for que sao usados para copiar os valores para o vetor auxiliar*/
		for(j = meio; j < lim_sup; j++)
			tab_aux[lim_sup + meio - j] = tab_final[j + 1];
		for(k = lim_inf; k <= lim_sup; k++){
			if(stock[tab_aux[j]].preco < stock[tab_aux[i]].preco) /* Comparacao do preco utilizando o vetor auxiliar ordenando assim o vetor inical*/
				tab_final[k] = tab_aux[j--];
			else if(stock[tab_aux[j]].preco == stock[tab_aux[i]].preco && stock[tab_aux[j]].id < stock[tab_aux[i]].id) /* Se o preco for igual ordena se pela ordem crescente*/
				tab_final[k] = tab_aux[j--];																			/*do id do produto*/
			else
				tab_final[k] = tab_aux[i++];
			}
	}
	else{
		for(i = meio + 1; i > lim_inf; i--) /* 2 ciclos que sao usados para copiar os valores para o vetor auxiliar*/
			PRTAUX[i-1] = tab_final[i-1];
		for(j = meio; j < lim_sup; j++)
			PRTAUX[lim_sup + meio - j] = tab_final[j + 1];
		for(k = lim_inf; k <= lim_sup; k++){
			if(strcmp(ecm[tempE.id].prt[PRTAUX[j]].desc, ecm[tempE.id].prt[PRTAUX[i]].desc) < 0) /* Comparacao das descricoes utilizando o vetor auxiliar*/
				tab_final[k] = PRTAUX[j--];															/*ordenando assim o vetor inicial*/
			else
				tab_final[k] = PRTAUX[i++];
		}

	}
	return 0;
}

/* Funcao iniicial do MergeSort que e usada para dividir os vetores em vetores mais pequenos diminuindo assim a complexidade
e aumentando consequentemente a eficacia do algoritmo*/
int MergeSort(int lim_inf, int lim_sup, int tab_final[], int string){
	int meio = (lim_inf + lim_sup)/2;
	if(lim_sup <= lim_inf)
		return 0;
	MergeSort(lim_inf, meio,tab_final, string);
	MergeSort(meio + 1, lim_sup, tab_final, string);
	Merge(lim_inf, lim_sup, meio, tab_final, string);
	return 0;
}

/***************** FUNCOES PRINCIPAIS *******************/

/* Funcao que adiciona um produto ao stock*/
int cmd_a(){
	int e;
	for(e=0; e < MAXPROD; e++){
		if (stock[e].id == -1){  /* Atraves da variavel temporaria temp colocamos as informacoes dos produtos no stock que e a estrutura permanente*/
			strcpy(stock[e].desc,temp.desc);
			stock[e].preco = temp.preco;
			stock[e].peso = temp.peso;
			stock[e].qtd = temp.qtd;
			stock[e].id = e;
			break;
		}
	}
	printf("Novo produto %d.\n", stock[e].id);
	return 0;
}

/* Funcao que adiciona quantidade ao produto no stock se este existir*/
int cmd_q(){
	if(stock[temp.id].id != -1) /* Verificacao da exitencia do produto se nao existir a funcao da erro*/
		stock[temp.id].qtd += temp.qtd;
	else
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", temp.id);
	return 0;
}

/* Funcao que cria uma encomenda*/
int cmd_N(){
	int e;
	for(e = 0; e < MAXECOM; e++){
		if(ecm[e].id == -1){
			ecm[e].id = e;
			break;
		}
	}
	printf("Nova encomenda %d.\n",ecm[e].id);
	return 0;
}

/* Funcao que adiciona o produto a encomenda se ambos exitirem e se houver quantidade no stock suficiente e se a encomenda nao ultrapassar o peso maximo*/ 
int cmd_A(){
	int e;
	if(ecm[tempE.id].id != -1){ /* Verificoes de se a encomenda e produto existem se existe quantidade suficiente e se a encomenda nao ultrapassa o peso maximo respetivamente*/ 
		if(stock[temp.id].id != -1){  /* Se nao passar nas verificacoes da erro por ordem das verificacoes*/
			if(temp.qtd <= stock[temp.id].qtd){
				if(ecm[tempE.id].peso + (temp.qtd * stock[temp.id].peso) <= MAXPESO){
					for(e = 0; e < MAXPESO; e++){
						if(ecm[tempE.id].prt[e].id == -1){ /* Se o produto ainda nao existir na encomenda a funcao adiciona esse produto*/
							ecm[tempE.id].prt[e].id = temp.id;
							strcpy(ecm[tempE.id].prt[e].desc, stock[temp.id].desc);
							ecm[tempE.id].prt[e].preco = stock[temp.id].preco;
							ecm[tempE.id].prt[e].peso = stock[temp.id].peso;
							ecm[tempE.id].prt[e].qtd += temp.qtd;
							ecm[tempE.id].peso += (stock[temp.id].peso * temp.qtd); /* Aumento do peso da encomenda*/
							stock[temp.id].qtd -= temp.qtd; /* Reduz a quantidade de produto no stock*/
							break;
						}
						else if(ecm[tempE.id].prt[e].id == temp.id){ /* Se o produto ja existir na encomenda simplesmente adiciona a quantidade indicada*/
							ecm[tempE.id].prt[e].qtd += temp.qtd;
							ecm[tempE.id].peso += (stock[temp.id].peso * temp.qtd); 
							stock[temp.id].qtd -= temp.qtd;
							break;
						}
					}
				}
				else
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",temp.id,tempE.id);
			}
			else
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", temp.id,tempE.id);
		}
		else
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",temp.id,tempE.id);
	}
	else
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", temp.id,tempE.id);
	return 0;
}

/* Funcao que reduz a quantidade de um produto ao stock se houver essa quantidade no stock e se o produto existir*/
int cmd_r(){
	if(stock[temp.id].id != -1){ /* Verificacao da existencia do produto no stock*/
		if(temp.qtd <= stock[temp.id].qtd) /* Verifca se a quantidade a remover existe no stock*/
			stock[temp.id].qtd -= temp.qtd;
		else
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",temp.qtd,temp.id);
	}
	else 
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n",temp.id);
	return 0;
}

/* Funcao que remove um produto de uma encomenda se ambos existirem e se o produto existir na encomenda pondo assim a sua quantidade a 0.
De forma a voltar a poder ser adicionado a encomenda nao apago a informacao do produto na encomenda simplesmente zero a sua quantidade*/
int cmd_R(){
	int e,counter = 0;
	if(ecm[tempE.id].id != -1){ /* Verificacao da exitencia da encomenda e do produto no stock*/
		if(stock[temp.id].id != -1){
			for(e = 0; e < MAXPESO; e++){
				if(ecm[tempE.id].prt[e].id == temp.id){ /* Se o produto exite na encomenda removo a quantidade do produto a encomenda e atualizo o stock e o peso da encomenda*/
					stock[temp.id].qtd += ecm[tempE.id].prt[e].qtd;
					ecm[tempE.id].peso -= ecm[tempE.id].prt[e].qtd * ecm[tempE.id].prt[e].peso;
					ecm[tempE.id].prt[e].qtd = 0;
				}
				else if (counter == MAXPESO) /* Se o contador chega ao valor maximo de produtos na encomenda significa que o produto na esta na encomenda e da erro*/
					printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", temp.id, tempE.id);
				else
					counter++; /* Contador que vai incrementando a medida que nao se encontra o produto na encomenda*/
			}
		}
		else
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",temp.id,tempE.id);
	}
	else
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",temp.id,tempE.id);
	return 0;
}

/* Funcao que calcula o custo de uma encomenda se esta existir*/
int cmd_C(){
	int e, custo = 0;
	if(ecm[tempE.id].id != -1){ /* Verificacao da exitencia da encomenda se nao a funcao da erro*/
		for( e = 0; e < MAXPESO; e++){ /* Ciclo que soma ao custo da encomenda o custo de cada produto dentro da encomenda*/
			if(ecm[tempE.id].prt[e].id != -1)
				custo += ecm[tempE.id].prt[e].preco * ecm[tempE.id].prt[e].qtd;
		}
		printf("Custo da encomenda %d %d.\n", tempE.id,custo);	
	}	
	else
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",tempE.id);
	return 0;
}

/* Funcao que altera o preco de um produto se este existir*/
int cmd_p(){
	int e,i;
	if(stock[temp.id].id != -1){ /* Verifica se o produto existe se nao da erro*/
		stock[temp.id].preco = temp.preco; /* Altercao do preco do produto no stock*/
		for(e = 0; e < MAXECOM; e++){ /* Ciclo que ira verificar se o produto existe em alguma encomenda e se existir altera o preco na encomenda tambem*/
			if(ecm[e].id != -1){
				for(i = 0; i < MAXPESO; i++){
					if(ecm[e].prt[i].id == temp.id)
						ecm[e].prt[i].preco = temp.preco;
				}
			}
			else
				break;
		}
	}
	else
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", temp.id);
	return 0;
}

/* Funcao que lista a quantidade de um produto numa encomenda se ambos existirem*/
int cmd_E(){
	int i, qtd_prd = 0;
	if(ecm[tempE.id].id != -1){ /*Verificacoes da existencia da encomenda e do produto se um deles nao existir a funcao da erro*/
		if(stock[temp.id].id != -1){
			for(i = 0; i < MAXPESO; i++){
				if(ecm[tempE.id].prt[i].id == temp.id) /* Se o produto existe na encomenda da o valor da quantidade existente e lista a quantidade do produto na encomenda*/
					qtd_prd = ecm[tempE.id].prt[i].qtd;
			}
			printf("%s %d.\n",stock[temp.id].desc, qtd_prd);
		}
		else
			printf("Impossivel listar produto %d. Produto inexistente.\n",temp.id);
	}
	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",tempE.id);
	return 0;
}

/* Fuuncao que lista o identificador da encomenda que contem a maior quantidade do produto dados se este existir*/
int cmd_m(){
	int e, max = 0,ide = 0, i;
	if(stock[temp.id].id != -1){ /* Verificacao da existencia do produto se nao da erro*/
		for(e = 0; e < MAXECOM; e++){  /* Ciclo que percorre as varias encomendas existentes e que atribui ao maximo o valor da quantidade do produto*/
			if(ecm[e].id != -1){					/*da encomenda em que este exitie em maior quantidade*/
				for(i = 0; i < MAXPESO; i++){
					if(ecm[e].prt[i].id == temp.id){
						if (e == 0){
							max = ecm[e].prt[i].qtd;
							ide = e;
						}
						else if(ecm[e].prt[i].qtd > max){
							max = ecm[e].prt[i].qtd;
							ide = e;
						}
					} 
				}
			}
			else
				break;		
		}
		if(max != 0) /* Funciona como verificacao que o produto existe na encomenda pois a quantidade de cada produto nas encomendas e iniciada a 0*/
			printf("Maximo produto %d %d %d.\n",temp.id,ide,max);
	}
	else
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", temp.id);
	return 0;
}

/* Funcao que lista os produtos do stock por ordem crescente de preco*/
int cmd_l(){
	int e,i, counter = 0, tab_final[MAXPROD];
	for(e = 0; e < MAXPROD; e++){  /* Ciclo para armazenar os idp dos produtos existentes no stock para comparar depois na funcao MergeSort*/
		if(stock[e].id != -1){
			tab_final[e] = stock[e].id;
			counter++;
		}
		else 
			break;
	}
	MergeSort(0, counter-1, tab_final, 0); /* Sort dos produtos*/
	
	printf("Produtos\n");
	for(i = 0; i < counter; i++)
		printf("* %s %d %d\n",stock[tab_final[i]].desc, stock[tab_final[i]].preco, stock[tab_final[i]].qtd);
	return 0;
}

/* Funcao que lista os produtos de uma encomenda por ordem alfabetica s esta encomenda exitir*/
int cmd_L(){
	int e,j, PRT[MAXPESO], lim_sup = 0;
	if(ecm[tempE.id].id != -1){ /* Verificacao da existencia da encomenda se nao da erro*/
		for(j = 0; j < MAXPESO; j++){
			if(ecm[tempE.id].prt[j].id != -1){ /*Ciclo que ira colocar o indice do produto exitente da encomenda no vetor auxiliar para ser usado depois no MergeSort*/
				PRT[lim_sup] = j;
				lim_sup++;
			}
		}
		MergeSort(0, lim_sup-1, PRT,1); /* Sort dos produtos da encomenda*/

		printf("Encomenda %d\n",tempE.id);
		for(e = 0; e < lim_sup; e++){
			if(ecm[tempE.id].prt[PRT[e]].qtd > 0) /* So lista os produtos que tem quantidade superior a 0*/
				printf("* %s %d %d\n", ecm[tempE.id].prt[PRT[e]].desc, ecm[tempE.id].prt[PRT[e]].preco, ecm[tempE.id].prt[PRT[e]].qtd);
		}
	}
	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", tempE.id);
	return 0;
}

/*Funcao principal do programa que comeca por inicializar parametros de ambas as estruturas e e responsavel por redirecionar para as funcoes correspondentes
dependendo do comando dado e funciona em loop ate que lhe e atribuido o comando x e terminar assim o programa*/
int main(){
	int bol = 1,e,j;
	for (e = 0; e < MAXPROD; e++) /* Inicializacao dos idp dos produtos do stock a -1*/
		stock[e].id = -1;
	for(e=0; e < MAXECOM; e++){
		for(j=0; j< MAXPESO; j++){ /* Inicializacao dos ide das encomendas a -1 e o peso desta a 0 e cada produto da encomenda*/
			ecm[e].id = -1;			/*e inicializado com o deu preco e peso a 0 e idp a -1*/
			ecm[e].peso = 0;
			ecm[e].prt[j].id = -1;
			ecm[e].prt[j].preco = 0;
			ecm[e].prt[j].qtd = 0;
		}
	}
	while(bol){            /* Corpo do ciclo da funcao.*/
		cmd = getchar();    /* A funcao comeca por adquirir o comando de seguida le a linha extrai a informacao do input e de seguida*/ 
		LeLinha();			/*e redirecionado para a funcao correspoondente ao comando*/
		ExtractInfo(cmd);
		switch(cmd){
			case 'a':
				cmd_a();
				break;
			case 'q':
				cmd_q();
				break;
			case 'N':
				cmd_N();
				break;
			case 'A':
				cmd_A();
				break;
			case 'r':
				cmd_r();
				break;
			case 'R':
				cmd_R();
				break;
			case 'C':
				cmd_C();
				break;
			case 'p':
				cmd_p();
				break;
			case 'E':
				cmd_E();
				break;
			case 'm':
				cmd_m();
				break;
			case 'l':
				cmd_l();
				break;
			case 'L':
				cmd_L();
				break;
			case 'x':
			bol = 0;
			break;
		}
	}
	return 0;
}