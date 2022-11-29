#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define C 1000
#define ALLPROD 10000
#define MAXENC 500
#define MAXPROD 200


typedef struct produto{
	int id;
	char desc[63];
	int preco;
	int peso;
	int stock;
	int flag;
	int n_enc;
}prod;



prod mat[MAXENC][MAXPROD] = {0};		/*matriz 500x200 em que as linhas representam encomendas e as colunas os produtos*/
prod vet[ALLPROD] = {0};				/*vetor onde sao guardados todos os produtos do sistema*/
prod nv[MAXPROD] = {0};					/*vetor utilizado para dar sort na funcao L*/
prod nv2[MAXENC] = {0};					/*vetor utilizado para dar sort na funcao m*/




int compara_preco(prod p1, prod p2){	/*funcao que recebe dois produtos e compara o preco dos dois*/
	if (p1.preco > p2.preco)
		return 1;
	return 0;
}

int compara_stock(prod p1, prod p2){	/*funcao que recebe 2 produtos e compara o stock dos dois*/
	if (p1.stock > p2.stock)
		return 1;
	return 0;
}

void bubble_sort(int n){				/*funcao de ordenacao utilizando o algoritmo bubblesort*/
	int i, j;
	prod temp;

	for (i = 0; i < n; i++){
		for (j = i; j < n; j++){
			if (compara_preco(vet[i],vet[j])){
				temp = vet[j];
				vet[j] = vet[i];
				vet[i] = temp;
			}
		}
	}
}

void bubble_sort_stock(int n){			/*funcao de ordenacao utilizando o algoritmo bubblesort*/
	int i, j;
	prod temp;

	for (i = 0; i < n; i++){
		for (j = i; j < n; j++){
			if (compara_stock(nv2[i],nv2[j])){
				temp = nv2[j];
				nv2[j] = nv2[i];
				nv2[i] = temp;
			}
		}
	}
}




int calcula_peso(int n){				/*funcao que recebe o identificador de uma encomenda e calcula o peso total da mesma*/
	int peso_total = 0;
	int count;

	for(count = 0; count < MAXPROD; count++){
		peso_total += (mat[n][count].peso * mat[n][count].stock);
	}
	return peso_total;

}


int calcula_custo(int n){				/*funcao que recebe o identificador de uma encomenda e calcula o custo total da mesma*/

	int custo_total = 0;
	int count;

	for(count = 0; count < MAXPROD; count++){
		if (mat[n][count].peso != 0){
			custo_total += (mat[n][count].preco * mat[n][count].stock);
		}
	}
	return custo_total;
}


int conta_prod(){						/*funcao que conta o numero de produtos no inventario*/
  int i;
  for (i = 0; vet[i].peso != 0; i++){}
  return i;
}

int conta_prod_2(){						/*funcao que conta o numero de produtos no vetor nv2[]*/
	int i;
	for(i = 0; nv2[i].peso != 0; i++){}
	return i;
}

prod ve_produto() {						
   prod input = {0};

   char str[C];
   char *token;
   char *v[C];
   int i;

   fgets(str, C, stdin);
   token = strtok(str, ":\n");

   /*ciclo que divide o input e guarda o obtido dentro de um vetor*/
   for (i = 0; token != NULL; i++) {
       v[i] = token;
       token = strtok(NULL, ":\n");
   }	

   /*passa do vetor para a estrutura*/
   input.id = 0;
   strcpy(input.desc, v[0]);
   input.preco = atoi(v[1]);
   input.peso = atoi(v[2]);
   input.stock = atoi(v[3]);


   return input;
}




void command_a(){
	prod input = {0};
	int count;

	input = ve_produto();

	for (count = 0; strcmp(vet[count].desc, "\0") != 0; count++);
	vet[count] = input;
	vet[count].id += count;
	printf("Novo produto %d.\n",vet[count].id);
}


void command_q(){


   char str[C];
   char *token;
   char *v[C];
   int i;

   fgets(str, C, stdin);
   token = strtok(str, ":\n");

   /*ciclo que divide o input e guarda o obtido dentro de um vetor*/
   for (i = 0; token != NULL; i++) {
       v[i] = token;
       token = strtok(NULL, ":\n");
   }
   /*verifica se o produto existe, ou seja, se o peso e diferente de 0*/
   if (vet[atoi(v[0])].peso != 0){
   	vet[atoi(v[0])].stock += atoi(v[1]);
   }
   else(printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", atoi(v[0])));
   	
}

void command_N(){

	int count;

	for (count = 0; mat[count][0].flag != 0; count++);
	mat[count][0].flag = 1;
	printf("Nova encomenda %d.\n",count);

}


void command_A(){
   	char str[C];
   	char *token;
   	char *v[C];
   	int i;


   	fgets(str, C, stdin);
   	token = strtok(str, ":\n");

   	/*ciclo que divide o input e guarda o obtido dentro de um vetor*/
   	for (i = 0; token != NULL; i++) {
   	    v[i] = token;
   	    token = strtok(NULL, ":\n");
   	}
   	/*verifica se a encomenda existe*/
   	if (mat[atoi(v[0])][0].flag == 1){
   		/*verifica se o produto existe*/
   		if(vet[atoi(v[1])].peso != 0){
   			/*verifica se ha stock sufuciente para adicionar a encomenda*/
			if (atoi(v[2]) <= vet[atoi(v[1])].stock){
				/*verifica se o peso total depois de adicionarmos o produto nao passa das 200 unidades de peso*/
				if (calcula_peso(atoi(v[0])) + (vet[atoi(v[1])].peso * atoi(v[2])) <= 200){
					if (mat[atoi(v[0])][vet[atoi(v[1])].id].peso == 0){
						mat[atoi(v[0])][vet[atoi(v[1])].id] = vet[atoi(v[1])];
						mat[atoi(v[0])][vet[atoi(v[1])].id].stock = atoi(v[2]);
						mat[atoi(v[0])][vet[atoi(v[1])].id].flag = 1;
						vet[atoi(v[1])].stock -= atoi(v[2]);
					}
				
					else{
						mat[atoi(v[0])][vet[atoi(v[1])].id].stock += atoi(v[2]);
						vet[atoi(v[1])].stock -= atoi(v[2]);

					}
				}
				else{printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",atoi(v[1]), atoi(v[0]));}
			}
			else{printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", atoi(v[1]), atoi(v[0]));}   	
		}
		else{printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",atoi(v[1]), atoi(v[0]));}
   	}
   	else{printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",atoi(v[1]), atoi(v[0]));}
}



void command_r(){


   char str[C];
   char *token;
   char *v[C];
   int i;

   fgets(str, C, stdin);
   token = strtok(str, ":\n");

   /*ciclo que divide o input e guarda o obtido dentro de um vetor*/
   for (i = 0; token != NULL; i++) {
       v[i] = token;
       token = strtok(NULL, ":\n");
   }
   if (vet[atoi(v[0])].peso != 0){
   		if((vet[atoi(v[0])].stock - atoi(v[1])) >= 0){
   			vet[atoi(v[0])].stock = vet[atoi(v[0])].stock - atoi(v[1]);
   		}
   		else(printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", atoi(v[1]), atoi(v[0])));
   }
   else(printf("Impossivel remover stock do produto %d. Produto inexistente.\n", atoi(v[0])));
   	
}

void command_R(){

	char str[C];
	char *token;
	char *v[C];
	int i;

    fgets(str, C, stdin);
    token = strtok(str, ":\n");

	/*ciclo que divide o input e guarda o obtido dentro de um vetor*/
	for (i = 0; token != NULL; i++) {
	     v[i] = token;
	     token = strtok(NULL, ":\n");
	}
    
	if (mat[atoi(v[0])][0].flag == 1){
		if (vet[atoi(v[1])].peso != 0){

			mat[atoi(v[0])][vet[atoi(v[1])].id].peso = 0;
			vet[atoi(v[1])].stock += mat[atoi(v[0])][vet[atoi(v[1])].id].stock;
			mat[atoi(v[0])][vet[atoi(v[1])].id].stock = 0;



		}
		else(printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", atoi(v[1]), atoi(v[0])));
	}
	else{printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",atoi(v[1]), atoi(v[0]));}
}


void command_C(){

	char str[C];
	char *token;
	char *v[C];
	int i, custo;

    fgets(str, C, stdin);
    token = strtok(str, ":\n");

	/*ciclo que divide o input e guarda o obtido dentro de um vetor*/
	for (i = 0; token != NULL; i++) {
	     v[i] = token;
	     token = strtok(NULL, ":\n");
	}

	if (mat[atoi(v[0])][0].flag == 1){
		custo = calcula_custo(atoi(v[0]));
		printf("Custo da encomenda %d %d.\n",atoi(v[0]), custo );
	}
	else{printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",atoi(v[0]));}
}




void command_p(){


   char str[C];
   char *token;
   char *v[C];
   int i, count;

   fgets(str, C, stdin);
   token = strtok(str, ":\n");

   /*ciclo que divide o input e guarda o obtido dentro de um vetor*/
   for (i = 0; token != NULL; i++) {
       v[i] = token;
       token = strtok(NULL, ":\n");
   }
   if (vet[atoi(v[0])].peso != 0){
   	vet[atoi(v[0])].preco = atoi(v[1]);
   	for(count = 0; count < MAXENC; count++){
   		if(mat[count][vet[atoi(v[0])].id].peso != 0){
   			mat[count][vet[atoi(v[0])].id].preco =atoi(v[1]);
   		}
   	}
   }
   else(printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", atoi(v[0])));
   	
}


void command_E(){
	char str[C];
    char *token;
    char *v[C];
    int i;

    fgets(str, C, stdin);
    token = strtok(str, ":\n");

    /*ciclo que divide o input e guarda o obtido dentro de um vetor*/
    for (i = 0; token != NULL; i++) {
        v[i] = token;
        token = strtok(NULL, ":\n");
    }

    if ((mat[atoi(v[0])][0].flag = 1)){
    	if (vet[atoi(v[1])].peso != 0){
    		printf("%s %d.\n",vet[atoi(v[1])].desc, mat[atoi(v[0])][atoi(v[1])].stock);
    	}
    	else{printf("Impossivel listar produto %d. Produto inexistente.\n",atoi(v[1]));}
    }
    else{printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",atoi(v[0]));}
}

void command_m(){
	char str[C];
    char *token;
    char *v[C];
    int i, count, count2 = 0, n;
    int j;
    fgets(str, C, stdin);
    token = strtok(str, ":\n");

    /*ciclo que divide o input e guarda o obtido dentro de um vetor*/
    for (i = 0; token != NULL; i++) {
        v[i] = token;
        token = strtok(NULL, ":\n");
    }


    /*passa os produtos de cada encomenda para um vetor nv2*/
    if (vet[atoi(v[0])].peso != 0){
		for(count = 0; count < MAXENC; count++){
			if (mat[count][vet[atoi(v[0])].id].peso != 0){			
				nv2[count2] = mat[count][vet[atoi(v[0])].id];
				nv2[count2].n_enc = count;
				count2++;
			}
		}
		/*ordena os produtos pela quantidade em stock*/
		if (nv2[0].peso != 0)	{
    		bubble_sort_stock(conta_prod_2());
    		n = conta_prod_2() - 1;
    		printf("Maximo produto %d %d %d.\n", atoi(v[0]), nv2[n].n_enc , nv2[n].stock);
    		/*limpa o vetor nv2 colocando o peso de todos os produtos a 0*/
    		for(j = 0; j < MAXENC; j++){
    			nv2[j].peso = 0;
    		}
    	}
    }
    else{printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",atoi(v[0]));}

}

void command_l(){
	int i;
	bubble_sort(conta_prod());
	printf("Produtos\n");
	for(i = 0; vet[i].peso != 0; i++){
		printf("* %s %d %d\n",vet[i].desc, vet[i].preco, vet[i].stock);
	}
}

void command_L(){
	char str[C];
    char *token;
    char *v[C];
    prod temp;
    int i,j,k,n,m,c;
    int count;
    int count2 = 0;

    fgets(str, C, stdin);
    token = strtok(str, ":\n");

    /*ciclo que divide o input e guarda o obtido dentro de um vetor*/
    for (i = 0; token != NULL; i++) {
        v[i] = token;
        token = strtok(NULL, ":\n");
    }

    /*verifica se a encomenda exite e adiciona todos os produtos dessa encomenda a um vetor nv*/
    if ((mat[atoi(v[0])][0].flag == 1)){
    	for(count = 0; count < MAXPROD; count++){
    		if (mat[atoi(v[0])][count].peso != 0){
    			nv[count2] = mat[atoi(v[0])][count];
    			count2++;
    		}
    		else{count2++;}
    		
    	}

    	n = sizeof(nv)/sizeof(nv[0]);

    	/*ordena as descricoes dos produtos do vetor nv por ordem alfabetica*/
		for (k = 0; k < n - 1 ; k++){
	        for (j = k + 1; j < n; j++){
	            if (strcmp(nv[k].desc, nv[j].desc) > 0){
	                temp = nv[k];
	                nv[k] = nv[j];
	                nv[j] = temp;
	            }
	        }
	    }

	    printf("Encomenda %d\n", atoi(v[0]));
	    for(m = 0; m < n; m++){
	    	if (nv[m].peso != 0){
	    		printf("* %s %d %d\n", nv[m].desc, nv[m].preco, nv[m].stock);
	    	}
	    }
	     /*limpa o vetor nv colocando o peso de todos os elementos a 0*/
	    for(c = 0; c < MAXPROD; c++){
	    	nv[c].peso = 0;
	    }

    }
    else{printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",atoi(v[0]));}

}


int main() {
   char c;

   for (;;) {

       c = getchar();

       switch (c) {
           case 'a':
               getchar();
               command_a();
               break;
           case 'q':
               getchar();
               command_q();
               break;
           case 'N':
               getchar();
               command_N();
               break;
           case 'A':
               getchar();
               command_A();
               break;
           case 'r':
               getchar();
               command_r();
               break;
           case 'R':
               getchar();
               command_R();              
               break;
           case 'C':
               getchar();
               command_C();
               break;
           case 'p':
               getchar();
               command_p();
               break;
           case 'E':
               getchar();
               command_E();
               break;
            case 'm':
               getchar();
               command_m();
               break;
             case 'l':
               getchar();
               command_l();
               break;
            case 'L':
               getchar();
               command_L();		
               break;
           case 'x':
               return 0;
           default:
               break;
       }

   }
}



