#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DESCRICAO 63
#define MAX_PRODUTOS 10000	
#define MAX_ENCOMENDAS 500
#define MAX_PESO_ENCOMENDAS 200
#define MAX_COMANDO 1000
 
typedef struct Produto{
	int id;
	int preco;
	int peso;
	int stock;
	char descricao[MAX_DESCRICAO];
}Produto;

typedef struct itemEncomenda{
	int id;
	int qnt;
	struct itemEncomenda *next;
}itemEncomenda;

typedef struct Encomenda{
	int id;
	int nprodutos;
	int peso;
	itemEncomenda *head;
}Encomenda;

Produto produtos[MAX_PRODUTOS];
Encomenda encomendas[MAX_ENCOMENDAS];
int pid = 0;
int pide = 0;

void adicionaProduto(char args[]){
	
	char descricao[MAX_DESCRICAO];
	int preco;
	int peso;
	int qnt;
	sscanf(args, "%[^:]:%d:%d:%d", descricao, &preco, &peso, &qnt);
	produtos[pid].id = pid;
	strcpy(produtos[pid].descricao, descricao);
	produtos[pid].preco = preco;
	produtos[pid].peso = peso;
	produtos[pid].stock = qnt;
	printf("Novo produto %d.\n", pid);
	pid++;
	return;
}


void adicionaStock(char args[]){
	int id, qnt, i;

	sscanf(args,"%d:%d", &id, &qnt);

	for (i = 0; i < MAX_PRODUTOS; i++){
		if (produtos[i].id == id){
			produtos[i].stock += qnt;
			return;
		}
	}
	printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
	return;
}

void adicionaEncomenda(){
	encomendas[pide].id = pide;
	encomendas[pide].head = NULL;
	encomendas[pide].peso = 0;
	encomendas[pide].nprodutos = 0;
	printf("Nova encomenda %d.\n", pide);
	pide++;
}	

void adicionaProdutoEncomenda(char args[]){
	int ide, idp, qnt;
	itemEncomenda* temp;
	sscanf(args, "%d:%d:%d", &ide, &idp, &qnt);
	if(ide > pide -1){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return;
	}
	if(idp > pid -1){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	}
	if (produtos[idp].stock < qnt){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		return;
	}
	if(encomendas[ide].peso + qnt*produtos[idp].peso > MAX_PESO_ENCOMENDAS){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
		return;
	}
	encomendas[ide].peso += qnt*produtos[idp].peso;
	temp = encomendas[ide].head;
	if(encomendas[ide].head == NULL){
  		encomendas[ide].head = can_fail_malloc(sizeof(itemEncomenda));
		encomendas[ide].head->id = idp;
		encomendas[ide].head->qnt = qnt;
		encomendas[ide].head->next = NULL;
		encomendas[ide].nprodutos++;
	}
	else{
 		while(temp->next != NULL){
			if(temp->id == idp){
				temp->qnt += qnt;
				return;
			}
    		temp = temp->next;
  		}
		temp->next = can_fail_malloc(sizeof(itemEncomenda));	
		temp->next->id = idp;
		temp->next->qnt = qnt;
		temp->next->next = NULL;
		encomendas[ide].nprodutos++;
	}
	produtos[idp].stock -= qnt;
	return;
}

void removeProduto(char args[]){
	int idp, qnt;
	sscanf(args,"%d:%d", &idp, &qnt);
	if (idp > pid - 1){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
		return;
	}
	if(produtos[idp].stock < qnt ){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qnt, idp);
		return; 
	}
	produtos[idp].stock -= qnt;
	return;
}

void removeEncomenda(char args[]){
	int ide, idp;
	itemEncomenda* temp;
	itemEncomenda* prev;
	sscanf(args, "%d:%d", &ide, &idp);
	if (ide > pide - 1){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return;
	}
	if (idp > pid - 1){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	}

	temp = encomendas[ide].head;
	prev = encomendas[ide].head;

	if(encomendas[ide].head->id ==idp){
		encomendas[ide].head = encomendas[ide].head->next;
		encomendas[ide].peso -= temp->qnt*produtos[idp].peso;
		produtos[idp].stock += temp->qnt;
		free(temp);
		encomendas[ide].nprodutos--;
		return;
	}
	while(temp != NULL){
		if(temp->id == idp){
			prev->next = temp->next;
			encomendas[ide].peso -= temp->qnt*produtos[idp].peso;
			produtos[idp].stock += temp->qnt;
			free(temp);
			encomendas[ide].nprodutos--;
			return;
		}
		prev = temp;
		temp = temp->next;
	}
	printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	return;
}

void calculaCusto(char args[]){
	int ide, custo, id, qnt;
	itemEncomenda* temp;
	sscanf(args, "%d", &ide);
	if(ide > pide - 1){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}
	temp = encomendas[ide].head;
	while(temp != NULL){
		id = temp->id;
		qnt = temp->qnt;
		custo += produtos[id].preco*qnt;
		temp= temp->next;
	}
	printf("Custo da encomenda %d %d.\n", ide, custo);
	return;

}

void alteraPreco(char args[]){
	int idp, preco;
	sscanf(args,"%d:%d", &idp, &preco);
	if(idp > pid - 1){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
		return;
	}
	produtos[idp].preco = preco;
	return;
}

void listaProduto(char args[]){
	int ide, idp;
	itemEncomenda* temp;
	sscanf(args, "%d:%d", &ide, &idp);
	if(ide > pide - 1){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}
	temp = encomendas[ide].head;
	while(temp != NULL){
		if(temp->id == idp){
			printf("%s %d\n",produtos[idp].descricao ,temp->qnt);
			return;
		}
		temp= temp->next;
	}
	printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
	return;
}

void maiorProduto(char args[]){
	int idp, i, ideRef, qntRef;
	itemEncomenda* temp;
	qntRef = 0;
	ideRef = -1;
	sscanf(args,"%d", &idp);
	if(idp > pid - 1){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
		return;
	}
	for(i=0; i< pid - 1; i++){
		temp = encomendas[i].head;
		while(temp != NULL){
			if(temp->id == idp){
				if (qntRef < temp->qnt){
					qntRef = temp->qnt;
					ideRef = i;
				}
			}
		}
	}
	if (ideRef == -1){
		return;
	}
	printf("Maximo produto %d %d %d.\n", idp, ideRef, qntRef);
	return;
}

void sortProdutos(){
	int i,j;
	Produto Sorted[MAX_PRODUTOS];
	Produto temp;
	for(i = 0; i < pid; i++){
  		strcpy(Sorted[i].descricao, produtos[i].descricao);
		Sorted[i].id = produtos[i].id;
		Sorted[i].peso = produtos[i].peso;
		Sorted[i].preco = produtos[i].preco;
		Sorted[i].stock = produtos[i].stock;
	}
	for(i = 0; i < pid; i++){
		for(j = 0; j < i; j++){
    		if(Sorted[j].preco > Sorted[j+1].preco){
      			temp = Sorted[j];
      			Sorted[j] = Sorted[j+1];
     			Sorted[j+1] = temp;
   			}
 		}
	}
	printf("Produtos\n");
	for(i=0; i < pid; i++){
		printf("* %s %d %d\n", Sorted[i].descricao, Sorted[i].preco, Sorted[i].stock);
	}
	return;
}

void sortEncomenda(char args[]){
	int ide, i, n, j;
	itemEncomenda* temp;
	itemEncomenda swap;
	itemEncomenda Sorted[MAX_PRODUTOS];
	sscanf(args, "%d", &ide);
	if (ide > pide - 1){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}
	n = 0;
	temp = encomendas[ide].head;
	while(temp != NULL){
		Sorted[n].id = temp->id;
		Sorted[n].qnt = temp->qnt;
		temp = temp->next;
		n++;
	}
	for(i = 0; i < n; i++){
		for(j = 0; j < i; j++){
    		if(strcmp(produtos[Sorted[j].id].descricao, produtos[Sorted[j+1].id].descricao)>0){
      			swap.id = Sorted[j].id;
				swap.qnt = Sorted[j].qnt;
      			Sorted[j].id = Sorted[j+1].id;
				Sorted[j].qnt = Sorted[j+1].qnt;
     			Sorted[j+1].id = swap.id;
				Sorted[j+1].qnt = swap.qnt;
   			}
 		}
	}
	printf("Encomenda %d\n", ide);
	for(i=0; i<encomendas[ide].nprodutos; i++){
		printf("* %s %d %d\n", produtos[Sorted[i].id].descricao, produtos[Sorted[i].id].preco, Sorted[i].qnt);
	}
	return;
}





int main(){
	char cmd[MAX_COMANDO];
	char letra;
	char args[MAX_COMANDO - 2];

	while (1){
		fgets(cmd, MAX_COMANDO, stdin);
		sscanf(cmd,"%c %s",&letra, args);

		switch (letra){

			case 'a':
				adicionaProduto(args);
			break;

			case 'q':
				adicionaStock(args);
			break;

			case 'N':
				adicionaEncomenda();
			break;

			case 'A':
				adicionaProdutoEncomenda(args);
			break;

			case 'r':
				removeProduto(args);
			break;

			case 'R':
				removeEncomenda(args);
			break;

			case 'C':
				calculaCusto(args); 
			break;

			case 'p':
				alteraPreco(args);
			break;

			case 'E':
				listaProduto(args);
			break;

			case 'm':
				maiorProduto(args);
			break;

			case 'l':
				sortProdutos();
			break;

			case 'L':
				sortEncomenda(args);
			break;
			
			case 'x':
				return 0;
			break;

		}
	}
}