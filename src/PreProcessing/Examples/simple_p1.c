#include<stdlib.h>
#include<stdio.h>
#include<string.h>


#define MAX_DESCRICAO 64
#define MAX_PRODUTOS 1000
#define LOOPS 5

typedef struct produto{
    int preco, quantidade;
    char desc[MAX_DESCRICAO];
}PRODUTO;


void command_a(int* n_prods, PRODUTO array[]){
	scanf(" %[^:]:%d:%d", array[*n_prods].desc, &array[*n_prods].preco, &array[*n_prods].quantidade);
	(*n_prods)++;
	return;
}



void command_r(int* n_prods, PRODUTO array[]){

	int id, qtd;
	scanf(" %d:%d",&id, &qtd);
	array[id].quantidade -= qtd;
	return;
}


void command_l(int* n_prods, PRODUTO array[]){

	for(int i=0; i<*n_prods; i++){
		printf("* %s %d %d\n", array[i].desc, array[i].preco, array[i].quantidade);
	}
	return;
}

int main(){

	int n_prods = 0;
	PRODUTO prods[MAX_PRODUTOS];

	for(int i=0; i<LOOPS; i++){
		int c = getchar();
		switch(c){
			case 'a':
				command_a(&n_prods, prods);
				break;
			case 'r':
				command_r(&n_prods, prods);
				break;
			case 'l':
				command_l(&n_prods, prods);
				break;
			case 'x':
            	return 0;
            default:
            	printf("Invalid command: %c", c);
		}
		getchar();
	}

	return 0;
}