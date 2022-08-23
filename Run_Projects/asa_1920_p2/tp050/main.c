#include <stdio.h>
#include <stdlib.h>

#define CAMINHO 0
#define CASA 1
#define SUPERMERCADO 2
#define DIRECOES 4

typedef struct node { /*cruzamentos*/
    /* cima, direita, baixo, esquerda */
    struct node ** direcoes; /*lista com os ponteiros para todas direcoes pela ordem escrita adirecoes[0]*/
    int isChecked; /*0 = not Checked*/
    int type; /*0 = caminho, 1 = casa, 2 = supermecado*/
	struct node * anterior; /*ponteiro auxiliar para a funcao bfs*/
} node;
node *** list;
node ** supermercadosList;
node ** casasList;
int supermercados, casas;
node ** queue;

void atualizaCheck(node * arg){
	arg->isChecked = 1;
	if(arg->anterior)
		atualizaCheck(arg->anterior);
}

void clearPath( node * arg){
	arg->isChecked = 0;
	if(arg->anterior)
		clearPath(arg->anterior);
}

int bfs(node * arg,int type){
	int i, numeroElementos = 0, posicao = 0;
	node * aux;
	queue[numeroElementos++] = arg;
	arg->isChecked = 2;
	while (numeroElementos > posicao) { 
       	aux = queue[posicao++];
        for (i = 0; i < DIRECOES; i++) { 
            if (aux->direcoes[i] && aux->direcoes[i]->type!= arg->type && !aux->direcoes[i]->isChecked) { 
                aux->direcoes[i]->isChecked = 2;
                aux->direcoes[i]->anterior = aux;  
                queue[numeroElementos++] = aux->direcoes[i]; 
                if (aux->direcoes[i]->type == type){
                	atualizaCheck(aux->direcoes[i]);
                    for(i = 0;i < numeroElementos; i++){
                    	if(queue[i]->isChecked == 2)
                    		queue[i]->isChecked = 0;
                    }
                    return 1; 
                }
            } 
        } 
    }
    return 0; 
}

void overridebfs(node * arg, int type){
	int i, numeroElementos = 0, posicao = 0;
	node * aux;
	queue[numeroElementos++] = arg;
	arg->isChecked = 2;
	while (numeroElementos > posicao) { 
       	aux = queue[posicao++];
        for (i = 0; i < DIRECOES; i++) {
        	if(aux->direcoes[i]){ 
            	if (aux->direcoes[i]->type == type || (aux->direcoes[i]->type!= arg->type && !aux->direcoes[i]->isChecked)) {
                	if (aux->direcoes[i]->type == type){
               			clearPath(aux->direcoes[i]->anterior);
               			aux->direcoes[i]->isChecked = 2;
               			aux->direcoes[i]->anterior = aux;  
               			queue[numeroElementos++] = aux->direcoes[i];
               			atualizaCheck(aux->direcoes[i]);
               		    for(i = 0;i < numeroElementos; i++){
               		    	if(queue[i]->isChecked == 2)
               		    		queue[i]->isChecked = 0;
               		    } 
               		}
               		else{
                	aux->direcoes[i]->isChecked = 2;
               		aux->direcoes[i]->anterior = aux;  
                	queue[numeroElementos++] = aux->direcoes[i];
                	}
            	}
            } 
        } 	
    }
}

int resolve(){
	int i, resultado = 0, auxResultado;
	if(casas >= supermercados){
		for(i = 0; i < supermercados; i++){
			resultado += bfs(supermercadosList[i], CASA);
		}
		auxResultado = resultado;
		do{
			resultado = auxResultado;
			for(i = 0; i < supermercados; i++){
				if(!supermercadosList[i]->isChecked)
					overridebfs(supermercadosList[i],CASA);
			}
			for(i = 0; i < casas; i++){
				if(!casasList[i]->isChecked){
					auxResultado += bfs(casasList[i],SUPERMERCADO);
				}
			}
		}while(auxResultado > resultado);	
	}
	else{
		for(i = 0; i < casas; i++){
			resultado += bfs(casasList[i], SUPERMERCADO);
		}
		auxResultado = resultado;
		do{
			resultado = auxResultado;
			for(i = 0; i < casas; i++){
				if(!casasList[i]->isChecked){
					printf("indice:%d\n",i);
					overridebfs(casasList[i],SUPERMERCADO);
				}
			}
			for(i = 0; i < supermercados; i++){
				if(!supermercadosList[i]->isChecked){
					auxResultado += bfs(supermercadosList[i],CASA);
				}
			}
		}while(auxResultado > resultado);
	}
	return resultado;
}


int main(){
	int avenidas, ruas;
	int i, j, auxAvenida, auxRua;

	scanf("%d %d", &avenidas, &ruas);
	list = malloc(avenidas * sizeof(node**));
	for(i = 0; i < avenidas; i++){
		list[i] = malloc(ruas * sizeof(node*));
	}

	queue = malloc(ruas*avenidas*sizeof(node*));
	for(i = 0; i < avenidas; i++){
		for(j = 0; j < ruas; j++){
				list[i][j] = malloc(sizeof(node));
				list[i][j]->direcoes = malloc(4* sizeof(node*));
		}
	}
	auxAvenida = avenidas - 1;
	auxRua = ruas - 1;

	/*inicializacao dos cantos da matriz*/
	list[0][0]->direcoes[0] = NULL;
	list[0][0]->direcoes[1] = list[1][0];
	list[0][0]->direcoes[2] = list[0][1];
	list[0][0]->direcoes[3] = NULL;
	list[0][0]->type = CAMINHO;
	list[0][0]->isChecked = 0;
	list[0][0]->anterior = NULL;

	list[0][auxRua]->direcoes[0] = list[0][auxRua-1];
	list[0][auxRua]->direcoes[1] = list[1][auxRua];
	list[0][auxRua]->direcoes[2] = NULL;
	list[0][auxRua]->direcoes[3] = NULL;
	list[0][auxRua]->type = CAMINHO;
	list[0][auxRua]->isChecked = 0;
	list[0][auxRua]->anterior = NULL;

	list[auxAvenida][0]->direcoes[0] = NULL;
	list[auxAvenida][0]->direcoes[1] = NULL;
	list[auxAvenida][0]->direcoes[2] = list[auxAvenida][1];
	list[auxAvenida][0]->direcoes[3] = list[auxAvenida-1][0];
	list[auxAvenida][0]->type = CAMINHO;
	list[auxAvenida][0]->isChecked = 0;
	list[auxAvenida][0]->anterior = NULL;

	list[auxAvenida][auxRua]->direcoes[0] = list[auxAvenida][auxRua-1];
	list[auxAvenida][auxRua]->direcoes[1] = NULL;
	list[auxAvenida][auxRua]->direcoes[2] = NULL;
	list[auxAvenida][auxRua]->direcoes[3] = list[auxAvenida-1][auxRua];
	list[auxAvenida][auxRua]->type = CAMINHO;
	list[auxAvenida][auxRua]->isChecked = 0;
	list[auxAvenida][auxRua]->anterior = NULL;

	/*inicializacao das margens da matriz (excluindo os cantos)*/
	for(j = 1; j < auxRua; j++){
		list[0][j]->direcoes[0] = list[0][j-1];
		list[0][j]->direcoes[1] = list[1][j];
		list[0][j]->direcoes[2] = list[0][j+1];
		list[0][j]->direcoes[3] = NULL;
		list[0][j]->type = CAMINHO;
		list[0][j]->isChecked = 0;
		list[0][j]->anterior = NULL;

		list[auxAvenida][j]->direcoes[0] = list[auxAvenida][j-1];
		list[auxAvenida][j]->direcoes[1] = NULL;
		list[auxAvenida][j]->direcoes[2] = list[auxAvenida][j+1];
		list[auxAvenida][j]->direcoes[3] = list[auxAvenida-1][j];
		list[auxAvenida][j]->type = CAMINHO;
		list[auxAvenida][j]->isChecked = 0;
		list[auxAvenida][j]->anterior = NULL;
	}
	for(i = 1; i < auxAvenida; i++){
		list[i][0]->direcoes[0] = NULL;
		list[i][0]->direcoes[1] = list[i+1][0];
		list[i][0]->direcoes[2] = list[i][1];
		list[i][0]->direcoes[3] = list[i-1][0];
		list[i][0]->type = CAMINHO;
		list[i][0]->isChecked = 0;
		list[i][0]->anterior = NULL;

		list[i][auxRua]->direcoes[0] = list[i][auxRua-1];
		list[i][auxRua]->direcoes[1] = list[i+1][auxRua];
		list[i][auxRua]->direcoes[2] = NULL;
		list[i][auxRua]->direcoes[3] = list[i-1][auxRua];
		list[i][auxRua]->type = CAMINHO;
		list[i][auxRua]->isChecked = 0;
		list[i][auxRua]->anterior = NULL;
	}
	/*inicializacao de toda os nodes que nao se encontram nas margens da matriz*/
	for(i = 1; i < auxAvenida; i++){
		for(j = 1; j < auxRua; j++){
				list[i][j]->direcoes[0] = list[i][j-1];
				list[i][j]->direcoes[1] = list[i+1][j];
				list[i][j]->direcoes[2] = list[i][j+1];
				list[i][j]->direcoes[3] = list[i-1][j];
				list[i][j]->type = CAMINHO;
				list[i][j]->isChecked = 0;
				list[i][j]->anterior = NULL;
		}
	}

	scanf("%d %d", &supermercados, &casas);

	supermercadosList = malloc(supermercados * sizeof(node*));
	for(i = 0; i < supermercados; i++){
		scanf("%d %d", &auxAvenida, &auxRua);
		auxRua--;
		auxAvenida--;
		list[auxAvenida][auxRua]->type = SUPERMERCADO;
		supermercadosList[i] = list[auxAvenida][auxRua];
	}

	casasList = malloc(casas * sizeof(node*));
	for(i = 0; i < casas; i++){
		scanf("%d %d", &auxAvenida, &auxRua);
		auxRua--;
		auxAvenida--;
		list[auxAvenida][auxRua]->type = CASA;
		casasList[i] = list[auxAvenida][auxRua];
	}
	printf("%d\n", resolve());
	return 0;
}
