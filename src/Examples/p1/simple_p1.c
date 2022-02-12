#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/*Used to simulate a bug*/
#define BUG_VAL 100

#define MAX_DESCRICAO 64
#define MAX_PRODUTOS 10
#define LOOPS 1


typedef struct produto{
    int preco, quantidade;
    char desc[MAX_DESCRICAO];
}PRODUTO;



int n_prods = 0;
PRODUTO prods[MAX_PRODUTOS];



/*Function to simulate a bug*/
void check_value(int i){
	if(i==BUG_VAL){
		int* a = NULL; //Dereference NULL ptr
		*a = 0;
	}
	return;
}


void command_a(){

	if(n_prods > MAX_PRODUTOS){
		return;
	}

	int preco;
	int qtd;

	scanf(" %[^:]:%d:%d", prods[n_prods].desc, &preco, &qtd);

	prods[n_prods].preco = preco;
	prods[n_prods].quantidade = qtd;

	(n_prods)++;
	return;
}



void command_r(){

	int id, qtd;
	scanf(" %d:%d",&id, &qtd);

	if(id <= n_prods){
		prods[id].quantidade -= qtd;
	}
	return;
}


void command_l(){

	for(int i=0; i<n_prods; i++){
		printf("* %s %d %d\n", prods[i].desc, prods[i].preco, prods[i].quantidade);
	}
	return;
}

int main(){



	for(int i=0; i<LOOPS; i++){
		int c = getchar();
		switch(c){
			case 'a':
				command_a();
				break;
			case 'r':
				command_r();
				break;
			case 'l':
				command_l();
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