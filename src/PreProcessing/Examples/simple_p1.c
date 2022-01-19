#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/*Used to simulate a bug*/
#define BUG_VAL 100

#define MAX_DESCRICAO 64
#define MAX_PRODUTOS 1000
#define LOOPS 1


typedef struct produto{
    int preco, quantidade;
    char desc[MAX_DESCRICAO];
}PRODUTO;



void* new_sym_var(unsigned int length){
	return NULL;
}



/*Function to simulate a bug*/
void check_value(int i){
	if(i==BUG_VAL){
		int* a = NULL; //Dereference NULL ptr
		*a = 0;
	}
	return;
}


void command_a(int* n_prods, PRODUTO array[]){

	if(*n_prods > MAX_PRODUTOS){
		return;
	}

	int preco;
	int qtd;

	scanf(" %[^:]:%d:%d", array[*n_prods].desc, &preco, &qtd);

	/*Trigger Bug*/
	check_value(preco);

	array[*n_prods].preco = preco;
	array[*n_prods].quantidade = qtd;

	(*n_prods)++;
	return;
}



void command_r(int* n_prods, PRODUTO array[]){

	int id, qtd;
	scanf(" %d:%d",&id, &qtd);

	if(id <= *n_prods){
		array[id].quantidade -= qtd;
	}
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