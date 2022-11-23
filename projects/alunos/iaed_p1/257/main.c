#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "structs.h"


/* Array com todos os produtos do sistema. */
produto produtos[MAX_PROD];

/* Array com todos as encomendas do sistema. */
encomenda encomendas[MAX_ENC];

/* O valor do proximo id a atribuir a um produto. */
int nextprdctid = 0;

/* O valor do proximo id a atribuir a uma encomenda. */
int nextencid = 0; 

/* Faz reset a todos os valores do produto a ser eliminado retornando o produto com os valores apos o reset. */
produto elimina_produto(produto prdct){
	prdct.id = -1;
	strcpy(prdct.descricao,"\0");
	prdct.preco = VAZIO;
	prdct.peso = VAZIO;
	prdct.stock = VAZIO;
	prdct.posfull = VAZIO;
	return prdct;
}

/* Verifica se um produto existe dentro de uma encomenda, se nao der erro(retronar -1) retrorna a posicao onde se encontra. */
int exist_em_encomenda(int pid, int eid){
	int i;
	encomenda enc = encomendas[eid];
	for(i = 0; i < enc.totalprdcts;i++){
		if(enc.prdcts[i].id == pid)
			return i;
	}
	return -1;
}

/* Funcao auxiliar do mergesort que devolve o array ordenado ao juntar os varios sub arrays. */
void Merge(produto *arr, int low, int mid, int high){
    int mergedSize = high - low + 1;
    produto *temp = (produto *)can_fail_malloc(mergedSize * sizeof(produto));
    int mergePos = 0;
    int leftPos = low;
    int rightPos = mid + 1;

    while (leftPos <= mid && rightPos <= high){
        if (arr[leftPos].preco < arr[rightPos].preco){
           
            temp[mergePos++] = arr[leftPos++];
        }
        else{
        	if((arr[leftPos].preco == arr[rightPos].preco) && (arr[leftPos].id < arr[rightPos].id)){
        		temp[mergePos++] = arr[leftPos++];
        	}
        	else{
            
            	temp[mergePos++] = arr[rightPos++];
        	}
    	}
        
    }

    while (leftPos <= mid){
        temp[mergePos++] = arr[leftPos++];
    }

    while (rightPos <= high){
        temp[mergePos++] = arr[rightPos++];
    }

    assert(mergePos == mergedSize);

    for (mergePos = 0; mergePos < mergedSize; ++mergePos)
        arr[low + mergePos] = temp[mergePos];

    free(temp);         
    
}

/* Ordena por ordem crescente de preco e em caso de empate por id um dado array de produtos utilizando o algoritmo mergesort. */
static
void MergeSort(produto *arr, int low, int high){
    if (low < high){
        int mid = (low + high) / 2;

        MergeSort(arr, low, mid);
        MergeSort(arr, mid + 1, high);

        Merge(arr, low, mid, high);
    }
}

/* Adiciona um novo produto ao sistema. */
void commando_a(char in[MAX_TMNH_INPUT]){
	produto tmp;
	tmp.id = nextprdctid;
	strcpy(tmp.descricao, strtok(in,":"));
	tmp.preco = atoi(strtok(NULL,":"));
	tmp.peso = atoi(strtok(NULL,":"));
	tmp.stock = atoi(strtok(NULL,"\n"));
	tmp.posfull = CHEIO;
	produtos[nextprdctid++] = tmp;
	printf("Novo produto %d.\n",tmp.id);
}

/* Adiciona stock a um produto existente no sistema. */
void commando_q(char in[MAX_TMNH_INPUT]){
	produto tmp;
	int pid = atoi(strtok(in,":"));
	int qtd = atoi(strtok(NULL,"\n"));
	tmp = produtos[pid];
	if(tmp.posfull != CHEIO)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",pid);
	else{
		tmp.stock += qtd;
		produtos[pid] = tmp;		
	}
}

/* Cria  uma nova encomenda. */
void commando_N(){
	encomenda tmp;
	tmp.id = nextencid;
	tmp.totalprdcts = 0;
	tmp.pesototal = 0;
	tmp.precototal = 0;
	tmp.posfull = CHEIO;
	encomendas[nextencid++] = tmp;
	printf("Nova encomenda %d.\n",tmp.id);
}

/* Adiciona um produto a uma encomenda. */
void commando_A(char in[MAX_TMNH_INPUT]){
	int eid = atoi(strtok(in,":"));
	int pid = atoi(strtok(NULL,":"));
	int qtd = atoi(strtok(NULL,"\n"));
	encomenda tmp = encomendas[eid];
	produto ogprdct = produtos[pid];
	produto prdcttoadd;
	/* verificacoes*/
	if(tmp.posfull != CHEIO)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", pid, eid);
	else{
		if(ogprdct.posfull != CHEIO)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", pid, eid);
		
		else{
			if((qtd > ogprdct.stock) && ogprdct.posfull == CHEIO)
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", pid, eid);
			else{
				if(((tmp.pesototal + (qtd*ogprdct.peso)) > MAX_PESO) && (ogprdct.posfull == CHEIO) && (tmp.posfull == CHEIO))
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", pid, eid, MAX_PESO);
				else{
					int pos = exist_em_encomenda(pid, eid);
					if(pos != -1){
						tmp.prdcts[pos].stock += qtd;
						tmp.precototal += (tmp.prdcts[pos].preco*qtd);
						tmp.pesototal += (tmp.prdcts[pos].peso*qtd);
					}
					else{
						prdcttoadd.id = ogprdct.id;
						strcpy(prdcttoadd.descricao,ogprdct.descricao);
						prdcttoadd.preco = ogprdct.preco;
						prdcttoadd.peso = ogprdct.peso;
						prdcttoadd.stock = qtd;
						prdcttoadd.posfull = CHEIO;
						tmp.prdcts[tmp.totalprdcts++] = prdcttoadd;
						tmp.pesototal += (prdcttoadd.peso*qtd);
						tmp.precototal += (prdcttoadd.preco*qtd);
					}
					encomendas[eid] = tmp;
					ogprdct.stock -= qtd;
					produtos[pid] = ogprdct;
				}
			}
		}
	}
	
}

/* Remove stock a um produto existente. */
void commando_r(char in[MAX_TMNH_INPUT]){
	int pid = atoi(strtok(in,":"));
	int qtd = atoi(strtok(NULL,"\n"));
	produto tmp = produtos[pid];
	/* verificacoes*/
	if(tmp.posfull != CHEIO)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", pid);
	else{
		if(((tmp.stock - qtd) < 0) && (tmp.posfull == CHEIO))
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, pid);
		else{
			tmp.stock -= qtd;
			produtos[pid] = tmp;	
		}
	}
}

/* Remove um produto de uma encomenda. */
void commando_R(char in[MAX_TMNH_INPUT]){
	int i,j,qtd = 0;
	int eid = atoi(strtok(in,":"));
	int pid = atoi(strtok(NULL,"\n"));
	int pos = exist_em_encomenda(pid, eid);
	encomenda tmp = encomendas[eid];
	/* verificacoes*/
	if(tmp.posfull != CHEIO)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", pid, eid);
	else{
		if(produtos[pid].posfull != CHEIO)
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", pid, eid);
		if((produtos[pid].posfull == CHEIO)&&(tmp.posfull == CHEIO) &&(pos!=-1)){
			produto tochange = produtos[pid];
			for(i = 0;i<tmp.totalprdcts;i++){
				if(tmp.prdcts[i].id == pid){
					tmp.precototal -= (tmp.prdcts[i].preco*tmp.prdcts[i].stock);
					tmp.pesototal -= (tmp.prdcts[i].peso*tmp.prdcts[i].stock);
					qtd = tmp.prdcts[i].stock;
					tmp.prdcts[i] = elimina_produto(tmp.prdcts[i]);
					for(j = i; j<tmp.totalprdcts-1;j++){
						tmp.prdcts[j] = tmp.prdcts[j+1];
					}
					break;
				}
			}
			tochange.stock += qtd;
			produtos[pid] = tochange;
			tmp.totalprdcts -= 1;
			encomendas[eid] = tmp;
		}
	}
}

/* Calcula o custo de uma encomenda. */
void commando_C(char in[MAX_TMNH_INPUT]){
	int eid = atoi(strtok(in,"\n"));
	encomenda tmp = encomendas[eid];
	/* verificacoes*/
	if(tmp.posfull != CHEIO)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", eid);
	else
		printf("Custo da encomenda %d %d.\n", eid, tmp.precototal);
}

/* Altera o preco de um produto existente. */
void commando_p(char in[MAX_TMNH_INPUT]){
	int i,j,pid = atoi(strtok(in,":"));
	int npreco = atoi(strtok(NULL,"\n"));
	produto tmp = produtos[pid];
	/* verificacoes*/
	if(tmp.posfull != CHEIO)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", pid);
	else{
		produtos[pid].preco = npreco;
		for(i = 0; i < nextencid; i++){
			encomenda enc = encomendas[i];
			for(j = 0; j < enc.totalprdcts; j++){
				if(enc.prdcts[j].id == pid){
					enc.precototal -= (enc.prdcts[j].preco*enc.prdcts[j].stock);
					enc.prdcts[j].preco = npreco;
					enc.precototal += (npreco*enc.prdcts[j].stock);
					encomendas[i] = enc;
					break;
				}
			}	
		}
	}
}

/* Retorna a descricao e a quantidade de um produto numa dada encomenda. */
void commando_E(char in[MAX_TMNH_INPUT]){
	int eid = atoi(strtok(in,":"));
	int pid = atoi(strtok(NULL,"\n"));
	int i;
	encomenda tmp = encomendas[eid];
	produto encomendado;
	/* verificacoes*/
	if(tmp.posfull != CHEIO)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", eid);
	else{
		if(produtos[pid].posfull != CHEIO)
			printf("Impossivel listar produto %d. Produto inexistente.\n", pid);
		else{
			i = exist_em_encomenda(pid,eid);
			if(i != -1){
				encomendado = tmp.prdcts[i];
				printf("%s %d.\n", encomendado.descricao, encomendado.stock);
			}
			else{
				encomendado = produtos[pid];
				printf("%s 0.\n", encomendado.descricao);
			}
		}
	}
}

/* Retorna o id da encomenda em que um dado produto occore mais vezes. */
void commando_m(char in[MAX_TMNH_INPUT]){
	int pid = atoi(strtok(in,"\n"));
	int maxval = 0,maxeid = 0,i,j;
	encomenda tmp;
	/* verificacoes*/
	if(produtos[pid].posfull != CHEIO)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", pid);
	else{
		for(i = 0; i < nextencid;i++){
			tmp = encomendas[i];
			for(j = 0;j < tmp.totalprdcts;j++){
				if((tmp.prdcts[j].id == pid) && (tmp.prdcts[j].stock > maxval)){
					maxval = tmp.prdcts[j].stock;
					maxeid = tmp.id;
				}
				if((tmp.prdcts[j].id == pid) && (tmp.prdcts[j].stock == maxval) && (tmp.id < maxeid))
					maxeid = tmp.id;
			}
		}
		if(maxval > 0)
			printf("Maximo produto %d %d %d.\n", pid, maxeid, maxval);
	}
}

/* Lista todos os produtos existentes por ordem crescente de preco. */
void commando_l(){
	produto *arr = (produto *)can_fail_malloc(MAX_PROD * sizeof(produto));
	int i;
	for(i = 0; i < nextprdctid;i++){
		arr[i] = produtos[i];
	}

	MergeSort(arr, 0, nextprdctid-1);
	printf("Produtos\n");

	for(i = 0;i< nextprdctid;i++)
		printf("* %s %d %d\n",arr[i].descricao, arr[i].preco, arr[i].stock);

	free(arr);
}

/* Lista todos os produtos de uma encomenda por ordem alfabetica da descricao. */
void commando_L(char in[MAX_TMNH_INPUT]){
	int i,j,eid = atoi(strtok(in,"\n"));
	encomenda tmp = encomendas[eid];
	/* verificacoes*/
	if(tmp.posfull != CHEIO)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", eid);
	else{
		produto temp,ordalf[MAX_PRD_ENC];
		for(i = 0; i < tmp.totalprdcts;i++)
			ordalf[i] = tmp.prdcts[i];
    	for(i = 0; i < tmp.totalprdcts; i++){
        	for(j = i+1; j < tmp.totalprdcts; j++){
            	if(strcmp(ordalf[i].descricao, ordalf[j].descricao)>0){
					temp = ordalf[i];
                	ordalf[i] = ordalf[j];
                	ordalf[j] = temp;
            	}
        	}
    	}
    	printf("Encomenda %d\n", eid);
    	for(i = 0; i < tmp.totalprdcts; i++)
    		printf("* %s %d %d\n", ordalf[i].descricao, ordalf[i].preco, ordalf[i].stock);
	}

}

/* Termina o programa. */
void commando_x(){
	exit(EXIT_SUCCESS);
}

int main(){
	char line[MAX_TMNH_INPUT]; 
	while (fgets(line, MAX_TMNH_INPUT, stdin)){
 		char command;
 	 	char input[MAX_TMNH_INPUT];
 	 	sscanf(line,"%c %s", &command, input);
 	 	switch(command){
 	 		case 'a':
 	 			commando_a(input);
 	 			break;
 	 		case 'q':
 	 			commando_q(input);
 	 			break;
 	 		case 'N':
 	 			commando_N();
 	 			break;
 	 		case 'A':
 	 			commando_A(input);
 	 			break;
 	 		case 'r':
 	 			commando_r(input);
 	 			break;
 	 		case 'R':
 	 			commando_R(input);
 	 			break;
 	 		case 'C':
 	 			commando_C(input);
 	 			break;
 	 		case 'p':
 	 			commando_p(input);
 	 			break;
 	 		case 'E':
 	 			commando_E(input);
 	 			break;
 	 		case 'm':
 	 			commando_m(input);
 	 			break;
 	 		case 'l':
 	 			commando_l();
 	 			break;
 	 		case 'L':
 	 			commando_L(input);
 	 			break;
 	 		case 'x':
 	 			commando_x();
 	 			break;
 		}
 	} 
	return 0;
}
