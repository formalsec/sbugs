#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_BUFFER 256
#define MAX_PRODUTOS 20000	
#define MAX_ENCOMENDAS 5000
#define MAX_DESCRIPT 63
#define MAX_PRODUTOS_ENCOMENDADOS 300

typedef unsigned char bool;
//enum { false = 0, true = 1 };

typedef struct 
{
	int pid;
	char descricao[MAX_DESCRIPT];
	int preco;
	int peso;
	int quantidade_stock;
}estrutura_produto; /*Estrutura dos produtos*/

int numero_produto = -1; /*Sempre que um produto e criado este numero e incrementado. vai ser igual ao pid */

estrutura_produto lista_produtos[MAX_PRODUTOS]; /*Guarda todos os produtos. Tem maximo de produtos definidos em cima e a posicao dos numeros vai ser igual ao seu pid*/
estrutura_produto lista_produtos_auxiliar[MAX_PRODUTOS]; /*vai ser a lista com o pre?o ordenado  */
estrutura_produto aux[MAX_PRODUTOS]; /*vai ser usado no merge de produtos para ficarem listados com o pre?o*/

typedef struct 
{
	int eid;
	estrutura_produto produto_encomendado[MAX_PRODUTOS_ENCOMENDADOS]; /*Guardar os produtos que sejam encomendados numa encomenda espicifica */
	int peso;
}estrutura_encomendas; /*Estrutura de encomendas */

int numero_encomendas = -1; /*Sempre que uma encomenda e criada este numero e incrementado. vai ser igual ao eid*/
int numero_produto_encomendado = 0;

estrutura_encomendas lista_encomendas[MAX_ENCOMENDAS]; /*Guarda todas as encomendas*/
estrutura_produto lista_produtos_encomendados_auxiliar[MAX_PRODUTOS];/*lista com a encomenda ordenada alfabeticamente*/
estrutura_produto aux_produto_encomendado[MAX_PRODUTOS];/**/


/* Funcoes Auxiliares, verificacoes e elementos de procura */
int verifica_tamanho_descricao(char *frase){
	if(strlen(frase) < MAX_DESCRIPT){  /*Nesta funcao pretendo verificar se o tamanho dan descricaodada nao e maior que 63 como dito no enunciado */
		return 1;
	}
	else{
		return 2;
	}
}

int verifica_encomenda(int n){  /*Esta funcao vai verificar se o eid dado pertence a uma encomenda ou nao */
	int i, j = 0;
	for(i = 0; i <= numero_encomendas; i++){
		if (lista_encomendas[i].eid == n){
			j++;
			break;
		}
	}
	if (j > 0){
		return 1;
	}
	else{
		return 2;
	}
}

int verifica_produto(int n){ /* Esta funcao vai verificar se o pid dado pertence a um produto ou nao*/
	int i, j = 0;
	for(i = 0; i <= numero_produto; i++){
		if(lista_produtos[i].pid == n){
			j = lista_produtos[i].pid;
			break;
		}
	}
	if(n == j){
		return 1;
	}
	else{
		return 2;
	}
}

int verifica_produto_encomenda(int n, int m){  /*Esta funcao vai verificar se um pertence a uma encomenda especifica*/
	if(verifica_encomenda(n) == 1 && verifica_produto(m) == 1 ){
		if (lista_encomendas[n].produto_encomendado[m].pid == lista_produtos[m].pid) {
			return 1;
		}
		else{
			return 2;
		}
	}
	else{
		return 2;
	}
}


int verifica_quantidade_stock(int n, int q){	/*Funcao que verifica se a quantidade em causa e maior ou igual a quantidade em stock de um produto*/
	if(verifica_produto(n) == 1){
		if(lista_produtos[n].quantidade_stock >= q){
			return 1;
		}
		else{
			return 2;
		}
	}
	else{
		return 2;
	}
}

int verifica_peso_encomenda(int n, int m, int q){ /*Funcao que verifica se a o peso da encomenda nao excede osuposto*/
	if(verifica_encomenda(n) == 1){
		if(verifica_produto(m) == 1){
			if((lista_encomendas[n].peso + lista_produtos[m].peso*q) < 201){ /*Aqui vou verificar se o peso da encomenda mais o peso do produto vezes a quantidade dada nao excede o suposto*/
				return 1;
			}
			else{
				return 2;
			}
		}
		else{
			return 2;
		}
	}
	else{
		return 2;
	}
}

int procura_encomenda(int n){  /*Dado um produto esta funcao procura em que encomenda e que o produto esta encomendado*/
	int i;
	for(i = 0; i <= numero_encomendas; i++){
		if(verifica_produto(n) == 1){
			if(lista_encomendas[i].produto_encomendado[n].pid == lista_produtos[n].pid){
				return i; /*retorna o eid se o produto tiver sido encomendado*/
			}
			else{
				break;
			}
		}
	}
	return -1;
}

int procura_produto(int n){ /*Esta funcao procura um produto dado uma encomenda*/
	int i;
	for(i = 0; i <= numero_produto; i++){
		if(verifica_encomenda(n) == 1){
			if(lista_encomendas[n].produto_encomendado[i].pid == lista_produtos[i].pid){ /*Aqui verifico se o pid na encomenda e igual ao da lista de produtos global*/
				return i; 
			}
			else{
				break;
			}
		}
	}
	return -1;
}


/*             */

void adiciona_produto(char *frase){ /*Funcao para adicionar produtos*/
	estrutura_produto p;
	int counter = 0, dados[3];
	memset(&p, 0, sizeof(estrutura_produto)); /*Ocupa o espaco de memoria para o produto*/
	frase = strtok(frase, ":");/*Apanhar o texto todo separado por :*/
	if(verifica_tamanho_descricao(frase) == 1){
		strcpy(p.descricao, frase);
		while (counter < 3){
		dados[counter++] = atoi(strtok(NULL, ":"));
	}
	numero_produto++;
	counter = 0;
	p.preco = dados[0];
	p.peso = dados[1];
	p.quantidade_stock = dados[2];
	p.pid = numero_produto;
	memcpy(&lista_produtos[numero_produto], &p, sizeof(estrutura_produto));/*copiar o produto criado para a lista global de produtos*/

	printf("Novo produto %d.\n", p.pid);
	}	
}

void adiciona_stock_produto(char *frase){ /*Funcao que adiciona stock a um produto especifico*/
	int novo_id, novo_stock;
	
	novo_id = atoi(strtok(frase, ":")); 
	novo_stock = atoi(strtok(NULL, ":"));
	
	if(verifica_produto(novo_id) == 1){
		lista_produtos[novo_id].quantidade_stock += novo_stock; 
	}
	else{
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", novo_id);
	}
}

void cria_encomenda(){ /*Funcao que cria uma nova encomenda*/
	estrutura_encomendas encomenda;
	memset(&encomenda, 0, sizeof(estrutura_encomendas)); /*Ocupa o espaco de memoria para a encomenda*/
	numero_encomendas++;
	encomenda.eid = numero_encomendas;
	memcpy(&lista_encomendas[numero_encomendas], &encomenda, sizeof(estrutura_encomendas));/*Copiar a encomenda criada para a lista global de encomendas*/  
	printf("Nova encomenda %d.\n", encomenda.eid);
}

void calcula_custo_encomenda(char *frase){ /*Funcao que calcula o custo de uma encomenda*/
	int total = 0, j, novo_eid;
	novo_eid = atoi(strtok(frase, ""));
	if(verifica_encomenda(novo_eid) == 1){ /*Verifica encomenda*/
		for(j = 0; j <= numero_produto; j++){/*Ciclo for que vai correr os produtos encomendados para encontrar o encomendado*/
			if(verifica_produto_encomenda(novo_eid, j) == 1){ /*Verifica que o produto esta encomendado*/
				total += lista_encomendas[novo_eid].produto_encomendado[j].preco*lista_encomendas[novo_eid].produto_encomendado[j].quantidade_stock;
			}
		}
		printf("Custo da encomenda %d %d.\n", novo_eid, total);
	}
	else{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", novo_eid);
	}	
}


void adiciona_produto_encomenda(char *frase){ /*Funcao que adiciona produto a encomenda*/
	int counter = 0, dados[2];
	int novo_eid, novo_pid, novo_stock;
	novo_eid = atoi(strtok(frase,":"));
	while (counter < 2){
		dados[counter++] = atoi(strtok(NULL, ":"));
	}
	counter = 0;
	novo_pid = dados[0];
	novo_stock = dados[1];
	if(verifica_encomenda(novo_eid) == 1){
		if(verifica_produto(novo_pid) == 1){
			if(verifica_quantidade_stock(novo_pid, novo_stock) == 1){
				if(verifica_peso_encomenda	(novo_eid, novo_pid, novo_stock) == 1){
					if(verifica_produto_encomenda(novo_eid, novo_pid) == 1){ /*Se o produto ja estiver encomendado adiciona se os novos valores aos ja existentes*/
						lista_encomendas[novo_eid].produto_encomendado[novo_pid].quantidade_stock += novo_stock;
						lista_produtos[novo_pid].quantidade_stock -= novo_stock;
						lista_encomendas[novo_eid].peso += lista_produtos[novo_pid].peso*novo_stock;  
						lista_encomendas[novo_eid].produto_encomendado[novo_pid].preco = lista_produtos[novo_pid].preco;
						strcpy(lista_encomendas[novo_eid].produto_encomendado[novo_pid].descricao, lista_produtos[novo_pid].descricao);
					}
					else{ /*O produto ainda nao foi encomendado entao vou copiar o produto da lista de produtos para a lista de produtos encomendados dentro da encomenda*/
						memcpy(&lista_encomendas[novo_eid].produto_encomendado[novo_pid], &lista_produtos[novo_pid], sizeof(estrutura_produto));
						lista_encomendas[novo_eid].produto_encomendado[novo_pid].pid = lista_produtos[novo_pid].pid;
						lista_encomendas[novo_eid].produto_encomendado[novo_pid].quantidade_stock = novo_stock;
						lista_encomendas[novo_eid].peso += lista_produtos[novo_pid].peso*novo_stock;
						lista_encomendas[novo_eid].produto_encomendado[novo_pid].preco = lista_produtos[novo_pid].preco; 
						lista_produtos[novo_pid].quantidade_stock -= novo_stock;
						numero_produto_encomendado = lista_produtos[novo_pid].pid;
						strcpy(lista_encomendas[novo_eid].produto_encomendado[novo_pid].descricao, lista_produtos[novo_pid].descricao);
					}
				}						
				else{
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", novo_pid, novo_eid);
				}
			}
			else{
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", novo_pid, novo_eid);							}
		}
		else{
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", novo_pid, novo_eid);
		}
	}	
	else{
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", novo_pid, novo_eid);
	}
}


void remove_stock_produto(char *frase){ /*Funcao que remove stock ao produto*/
	int novo_pid, novo_stock;
	novo_pid = atoi(strtok(frase, ":"));
	novo_stock = atoi(strtok(NULL, ":"));
	if(verifica_produto(novo_pid) == 1){
		if(verifica_quantidade_stock(novo_pid, novo_stock) == 1){
			lista_produtos[novo_pid].quantidade_stock -= novo_stock;
		}
		else{
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", novo_stock, novo_pid);
		}
	}
	else{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", novo_pid);
	}
}


void altera_preco_produto(char *frase){ /*Funcao que altera o preco de um poduto*/
	int novo_pid, novo_preco, i;
	novo_pid = atoi(strtok(frase, ":"));
	novo_preco = atoi(strtok(NULL, ":"));
	if(verifica_produto(novo_pid) == 1){
		lista_produtos[novo_pid].preco = novo_preco;
		i = procura_encomenda(novo_pid); /*Encontro se o prodduto foi encomendado*/
		if(i >= 0){/*Se houver um encomenda com este produto entao na encomenda tambem se altera o preco*/
			if(verifica_produto_encomenda(i, novo_pid)){
			lista_encomendas[i].produto_encomendado[novo_pid].preco = novo_preco;
			}
		}
	}
	else{	
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", novo_pid);
	}
}

void remove_produto_encomenda(char *frase){ /*Funcao que remove os produtos da encomenda*/
	int novo_eid, novo_pid;
	novo_eid = atoi(strtok(frase, ":"));
	novo_pid = atoi(strtok(NULL, ":"));
	if(verifica_encomenda(novo_eid) == 1){
		if(verifica_produto(novo_pid) == 1){
			if(verifica_produto_encomenda(novo_eid, novo_pid) == 1){ /*Se o eid e pid dados passarem esta verificacao entao todos os seus valores passao a zero*/
				lista_encomendas[novo_eid].peso -= lista_encomendas[novo_eid].produto_encomendado[novo_pid].quantidade_stock*lista_produtos[novo_pid].peso;
				lista_encomendas[novo_eid].produto_encomendado[novo_pid].peso = 0;
				lista_encomendas[novo_eid].produto_encomendado[novo_pid].preco = 0;
				lista_encomendas[novo_eid].produto_encomendado[novo_pid].quantidade_stock = 0;
			}
		}
		else{
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", novo_pid, novo_eid);
		}
	}
	else{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", novo_pid, novo_eid);
	}
}



void lista_descricao_quantidade(char *frase){ /*Funcao que lista a descricao e quantidade de um produto encomendado*/
	int novo_eid, novo_pid;
	novo_eid = atoi(strtok(frase, ":"));
	novo_pid = atoi(strtok(NULL, ":"));
	if(verifica_encomenda(novo_eid) == 1){
		if(verifica_produto(novo_pid) == 1){
			if(lista_encomendas[novo_eid].produto_encomendado[novo_pid].pid == lista_produtos[novo_pid].pid){
				if(lista_encomendas[novo_eid].produto_encomendado[novo_pid].preco > 0){
					printf("%s %d.\n", lista_encomendas[novo_eid].produto_encomendado[novo_pid].descricao, lista_encomendas[novo_eid].produto_encomendado[novo_pid].quantidade_stock);
				}
			}
		}
		else{
			printf("Impossivel listar produto %d. Produto inexistente.\n", novo_pid);
		}
	}
	else{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", novo_eid);
	}
}

void lista_encomenda_com_mais_produto(char *frase){ /*Dado um pid esta funcao vao listar a encomenda que tem mais desse produto*/
	int novo_pid, counter=0, i, j = 0;
	novo_pid = atoi(strtok(frase, ""));
	if(verifica_produto(novo_pid) == 1){
		for(i = 0; i <= numero_encomendas; i++){
			if(lista_encomendas[i].produto_encomendado[novo_pid].quantidade_stock > 0 && lista_encomendas[i].produto_encomendado[novo_pid].quantidade_stock >= counter){
				counter = lista_encomendas[i].produto_encomendado[novo_pid].quantidade_stock;
				i = j;
			}
			else{
				return;
			}
		}
		printf("Maximo produto %d %d %d\n", novo_pid, j, counter);
	}
	else{
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", novo_pid);
	}
}

/*Funcao merge para listar os produtos pelo preco crescente*/

void merge_produtos(int low, int middle, int high){ 
	int i, j, k;
	for(i = low; i <= high; i++){
		memcpy(&aux[i], &lista_produtos_auxiliar[i], sizeof(estrutura_produto));
	}
	i = low;
	j = middle +1;
	k = low;

	while(i <= middle && j <= high){
		if(aux[i].preco <= aux[j].preco){ 
			lista_produtos_auxiliar[k].pid = aux[i].pid;
			lista_produtos_auxiliar[k].preco = aux[i].preco;
			lista_produtos_auxiliar[k].peso = aux[i].peso;
			lista_produtos_auxiliar[k].quantidade_stock = aux[i].quantidade_stock;
			strcpy(lista_produtos_auxiliar[k].descricao, aux[i].descricao);
			i++;
		}
		else{
			lista_produtos_auxiliar[k].pid = aux[j].pid;
			lista_produtos_auxiliar[k].preco = aux[j].preco;
			lista_produtos_auxiliar[k].peso = aux[j].peso;
			lista_produtos_auxiliar[k].quantidade_stock = aux[j].quantidade_stock;
			strcpy(lista_produtos_auxiliar[k].descricao, aux[j].descricao);
			j++;
		}
		k++;
	}
	while(i <= middle){
		lista_produtos_auxiliar[k] = aux[i];
		lista_produtos_auxiliar[k].preco = aux[i].preco;
		lista_produtos_auxiliar[k].peso = aux[i].peso;
		lista_produtos_auxiliar[k].quantidade_stock = aux[i].quantidade_stock;
		strcpy(lista_produtos_auxiliar[k].descricao, aux[i].descricao); 
		k++;
		i++;
	}
}


void mergesortpreco(int low, int high){
	if(low < high){
		int middle = (low + high)/ 2;

		mergesortpreco(low, middle); /*Dividir a lista recursivamente*/
		mergesortpreco(middle+1, high);
		merge_produtos(low, middle, high);
	}
}

void lista_produtos_preco(){
	int i;
	for(i = 0; i <= numero_produto; i++){
		memcpy(&lista_produtos_auxiliar[i], &lista_produtos[i], sizeof(estrutura_produto)); /*Criar a lista auxliar para guardar todos os valores da lista de produtos*/
	}
	mergesortpreco(0, numero_produto);
	printf("Produto\n");
	for(i = 0; i <= numero_produto; i++){
		if(lista_produtos_auxiliar[i].preco > 0){
			printf("* %s %d %d\n", lista_produtos_auxiliar[i].descricao, lista_produtos_auxiliar[i].preco, lista_produtos_auxiliar[i].quantidade_stock);
		}
	}
}



/*Funcao merge que vai ordenar a encomenda alfabeticamente*/

void merge_produtos_encomendados(int low, int middle, int high){
	int i, j, k;
	for(i = low; i <= high; i++){
		memcpy(&aux_produto_encomendado[i], &lista_produtos_encomendados_auxiliar[i], sizeof(estrutura_produto));
	}
	i = low;
	j = middle +1;
	k = low;

	while(i <= middle && j <= high){
		if(strcmp(aux_produto_encomendado[i].descricao, aux_produto_encomendado[j].descricao) < 0){
			lista_produtos_encomendados_auxiliar[k].pid = aux_produto_encomendado[i].pid;
			lista_produtos_encomendados_auxiliar[k].preco = aux_produto_encomendado[i].preco;
			lista_produtos_encomendados_auxiliar[k].peso = aux_produto_encomendado[i].peso;
			lista_produtos_encomendados_auxiliar[k].quantidade_stock = aux_produto_encomendado[i].quantidade_stock;
			strcpy(lista_produtos_encomendados_auxiliar[k].descricao, aux_produto_encomendado[i].descricao);
			i++;
		}
		else{
			lista_produtos_encomendados_auxiliar[k].pid = aux_produto_encomendado[j].pid;
			lista_produtos_encomendados_auxiliar[k].preco = aux_produto_encomendado[j].preco;
			lista_produtos_encomendados_auxiliar[k].peso = aux_produto_encomendado[j].peso;
			lista_produtos_encomendados_auxiliar[k].quantidade_stock = aux_produto_encomendado[j].quantidade_stock;
			strcpy(lista_produtos_encomendados_auxiliar[k].descricao, aux_produto_encomendado[j].descricao);
			j++;
		}
		k++;
	}
	while(i <= middle){
		lista_produtos_encomendados_auxiliar[k].pid = aux_produto_encomendado[i].pid;
		lista_produtos_encomendados_auxiliar[k].preco = aux_produto_encomendado[i].preco;
		lista_produtos_encomendados_auxiliar[k].peso = aux_produto_encomendado[i].peso;
		lista_produtos_encomendados_auxiliar[k].quantidade_stock = aux_produto_encomendado[i].quantidade_stock;
		strcpy(lista_produtos_encomendados_auxiliar[k].descricao, aux_produto_encomendado[i].descricao);
		k++;
		i++;
	}
}
void mergesort_encomenda(int low, int high){
	if(low < high){
		int middle = low + (high-low) / 2;

		mergesort_encomenda(low, middle); 
		mergesort_encomenda(middle+1, high);
		merge_produtos_encomendados(low, middle, high);
	}
}


void lista_produtos_alfabetica(char *frase){
	int novo_eid, i;
	novo_eid = atoi(strtok(frase, ""));
	for(i = 0; i <= numero_produto_encomendado; i++){
		memcpy(&lista_produtos_encomendados_auxiliar[i], &lista_encomendas[novo_eid].produto_encomendado[i], sizeof(estrutura_produto));
	}
	if(verifica_encomenda(novo_eid) == 1){
		mergesort_encomenda(0, numero_produto_encomendado);
		printf("Encomenda %d\n", novo_eid);
		for(i = 0; i <= numero_produto_encomendado; i++){
			if(lista_produtos_encomendados_auxiliar[i].preco > 0 && lista_produtos_encomendados_auxiliar[i].quantidade_stock > 0){
				printf("* %s %d %d\n", lista_produtos_encomendados_auxiliar[i].descricao, lista_produtos_encomendados_auxiliar[i].preco, lista_produtos_encomendados_auxiliar[i].quantidade_stock);
			}
		}

	}
	else{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", novo_eid);
	}
}

/*Funcao main*/

int main(){
	bool loop = 1;
	char command;
	char input[TAM_BUFFER];

	while (loop) {
		fgets(input, TAM_BUFFER, stdin); 
		command = input[0];

		switch(command){
			case 'a':
				adiciona_produto(input+2);
				break;
			case 'q':
				adiciona_stock_produto(input+2);
				break;
			case 'N':
				cria_encomenda();
				break;
			case 'A':
				adiciona_produto_encomenda(input+2);
				break;
			case 'r':
				remove_stock_produto(input+2);
				break;
			case 'R':
				remove_produto_encomenda(input+2);
				break;
			case 'C':
				calcula_custo_encomenda(input+2);
				break;
			case 'p':
				altera_preco_produto(input+2);
				break;
			case 'E': 
				lista_descricao_quantidade(input+2);
				break;
			case 'm':
				lista_encomenda_com_mais_produto(input+2);
				break;		
			case 'l':
				lista_produtos_preco();
				break;	
			case 'L':
				lista_produtos_alfabetica(input+2);
				break;
			case 'x':
				loop = 0;
		}
	}
	return 0;
}
