#include "p1.h"

int main(){
	char comando, parametros[MAXARG];  

	 do {
        comando = getchar();
        fgets(parametros, MAXARG, stdin);
        switch(comando) {
           case 'a':
           		comando_a(parametros);
				break;

			case 'q':
				comando_q(parametros);
				break;

			case 'N':
				comando_N();
				break;

			case 'A':
				comando_A(parametros);
				break;

			case 'r':
				comando_r(parametros);
				break;

			case 'R':
				comando_R(parametros);
				break;

			case 'C':
				comando_C(parametros);
				break;

			case 'p':
				comando_p(parametros);
				break;

			case 'E':
				comando_E(parametros);
				break;

			case 'm':
				comando_m(parametros);
				break;

			case 'l':
				comando_l();
				break;

			case 'L':
				comando_L(parametros);
				break;
        }
    } while (comando != 'x');
    
    return 0;
}

void separaInput(char arg[MAXARG], char res[][MAXARG]){
	int i=0;
	char* token;
	char delim[3];
	strcpy(delim, ":");                                         /* separa parametros por : */
	token = strtok(arg, delim);
	while(token != NULL){
		strcpy(res[i], token);
		token = strtok(NULL, delim);
		i++;
	}
}

void removeEspaco(char *str){
    int i;
    int cont = 0; 
    for (i = 0; str[i]; i++) 
        if (str[i] != ' ') 
            str[cont++] = str[i]; 
    str[cont] = '\0'; 
} 

void comando_a(char arg[]){
	char inputSeparado[4][MAXARG];                            
	separaInput(arg, inputSeparado);
	removeEspaco(inputSeparado[0]);
	strcpy(produtos[contaProdutos].descricao,inputSeparado[0]);
	produtos[contaProdutos].preco = atoi(inputSeparado[1]);
	produtos[contaProdutos].peso = atoi(inputSeparado[2]);
	produtos[contaProdutos].stock = atoi(inputSeparado[3]);
    produtos[contaProdutos].flag = 1;
	printf("Novo produto %d.\n", contaProdutos);
	++ contaProdutos;
}

int comando_q(char arg[]){
	int idp, qtd;
	char inputSeparado[2][MAXARG];
	separaInput(arg, inputSeparado);
	idp = atoi(inputSeparado[0]);                                 /*id do produto*/
	qtd = atoi(inputSeparado[1]);                                 /*quantidade de stock a adicionar*/
    if(produtos[idp].flag == 1){
        produtos[idp].stock = produtos[idp].stock + qtd;
        return 0;
    }
    else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
		return -1;
    }
}

void comando_N(){
	encomendas[contaEncomendas].flag = 1; 
	printf("Nova encomenda %d.\n", contaEncomendas);
	++contaEncomendas;
}

int comando_A(char arg[]){ 
	int ide, idp, qtd;
	char inputSeparado[3][MAXARG];
	separaInput(arg, inputSeparado);
	ide = atoi(inputSeparado[0]);                                       /* id da encomenda */
	idp = atoi(inputSeparado[1]);                                       /* id do produto */
	qtd = atoi(inputSeparado[2]);                                       /* quantidade a adicionar na encomenda */
	if(encomendas[ide].flag == 1){                              
		if(produtos[idp].flag == 1){                            
			if(produtos[idp].stock - qtd >=0){                           /* tem stock suficiente */
				if((encomendas[ide].peso + qtd*produtos[idp].peso)<= 200){ /* nao pesa 200 */
	                encomendas[ide].produtosEncomendas[idp] = produtos[idp]; 
					produtos[idp].stock = produtos[idp].stock - qtd;     /*remover qtd no stock do produto*/
					encomendas[ide].peso = encomendas[ide].peso + qtd*produtos[idp].peso; /*atualizar peso da encomenda*/
					encomendas[ide].quantidade[idp] = encomendas[ide].quantidade[idp] + qtd; /*quantidade do produto na encomenda*/
					encomendas[ide].contaProdEnc++;
					return 0;
				}
				else{
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
					return -1; 
				}
			}
			else{
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
				return -1;
			}
		}
		else{
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
			return -1;
		}
	}
	else{
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return -1;
	}
}

int comando_r(char arg[]){
	int idp, qtd;
	char inputSeparado[2][MAXARG];
	separaInput(arg, inputSeparado);
	idp = atoi(inputSeparado[0]);                                   /* id do produto */
	qtd = atoi(inputSeparado[1]);                                   /* quantidade de stock a remover */
	if(produtos[idp].flag == 1){                        
		if(produtos[idp].stock - qtd >=0){
			produtos[idp].stock = produtos[idp].stock - qtd;
		}
		else{
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
			return -1;
		}
	}
	else{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
		return -1;
	}
	return -1;
}

int comando_R(char arg[]){
	int ide, idp;
	char inputSeparado[2][MAXARG];
	separaInput(arg, inputSeparado);
	ide = atoi(inputSeparado[0]);                                   /* id da encomenda */
	idp = atoi(inputSeparado[1]);                                   /* id do produto */
	if(encomendas[ide].flag == 1){
		if(produtos[idp].flag == 1){
            if(encomendas[ide].produtosEncomendas[idp].flag == 1){  /* se o produto existir na encomenda */
		    	encomendas[ide].contaProdEnc = encomendas[ide].contaProdEnc -1;
            }
			encomendas[ide].peso = encomendas[ide].peso - encomendas[ide].quantidade[idp]*produtos[idp].peso; /* atualizar peso da encomenda */
			produtos[idp].stock = produtos[idp].stock + encomendas[ide].quantidade[idp];  /* atualizar stock do produto */
			encomendas[ide].produtosEncomendas[idp].flag = 0;         /* colocar flag a zero pq o produto deixa de existir na encomenda */
			strcpy(encomendas[ide].produtosEncomendas[idp].descricao, "vazio"); 
			encomendas[ide].quantidade[idp] = 0;
			return 0;
		}
		else{
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
			return -1;
		}
	}
	else{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return -1;
	}return -1;
}

int comando_C(char arg[]){
	int i;
	int ide, total=0;                                              /* total e o custo total da encomenda */ 
	char inputSeparado[1][MAXARG];
	separaInput(arg, inputSeparado);
	ide = atoi(inputSeparado[0]);                                  /* id da encomenda */
	if(encomendas[ide].flag == 1){
		for(i=0; i<= contaProdutos-1; i++){
			if(encomendas[ide].produtosEncomendas[i].flag == 1){
				total = total + produtos[i].preco * encomendas[ide].quantidade[i];
			}
		}
		printf("Custo da encomenda %d %d.\n", ide, total);
		return 0;
	}
	else{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
		return -1;
	}
	return -1;
}

int comando_p(char arg[]){
	int idp, preco;
	char inputSeparado[2][MAXARG];
	separaInput(arg, inputSeparado);
	idp = atoi(inputSeparado[0]);                                 /* id do produto */
	preco = atoi(inputSeparado[1]);                               /* preco novo */
	if(produtos[idp].flag ==1){
		produtos[idp].preco = preco;
		return 0;
	}
	else{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
		return -1;
	}
	return -1;
}

int comando_E(char arg[]){
	int ide, idp;
	char inputSeparado[2][MAXARG];
	separaInput(arg, inputSeparado);
	ide = atoi(inputSeparado[0]);                                /* id da encomenda */
	idp = atoi(inputSeparado[1]);                                /* id do produto */
	if(encomendas[ide].flag ==1){
		if(produtos[idp].flag == 1){
			printf("%s %d.\n", produtos[idp].descricao, encomendas[ide].quantidade[idp]);
			return 0;
		}
		else{
			printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
			return -1;
		}
	}
	else{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return -1;
	}
	return -1;
}

int comando_m(char arg[]){
	int i;
	int idp, idFinal = -1, qtdFinal = -1, qtd = -1; 
	char inputSeparado[1][MAXARG];
	separaInput(arg, inputSeparado);
	idp = atoi(inputSeparado[0]);                                /* id do produto */
	if(produtos[idp].flag ==1){
		for(i=0; i<= contaEncomendas-1; i++){
			if(encomendas[i].produtosEncomendas[idp].flag == 1){
				qtd = encomendas[i].quantidade[idp];            /* guarda a quantidade do produto numa determinada encomenda */
				if(qtd > qtdFinal){                             /* se a quantidade for maior que o valor guardado em qtdFinal, atualiza */
					qtdFinal = qtd;                             /* guarda a maior quantidade */
					idFinal = i;                                /* guarda o id da encomenda */
				}
			}
		}
		if(contaEncomendas == 0 || idFinal == -1){              /* se nao existirem encomendas ou o produto nao existir em nenhuma encomenda */
			return 0;
		}
		else{
			printf("Maximo produto %d %d %d.\n", idp, idFinal, qtdFinal);
			return 0;
		}
	}
	else{
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
		return -1;
	}
	return -1;
}
 
void comando_l(){
int i,f,l =1;                                                  /* l e o identificador para a funcao l, na funcao merge e mergeSort */
Produto auxl[MAXPROD];                                         /* vetor auxiliar de produtos a ordenar */
for (i=0; i<= contaProdutos-1; i++)
	auxl[i] = produtos[i];
mergeSort(auxl, 0, contaProdutos-1, l);
printf("Produtos\n");
	for(f=0;f<=contaProdutos-1;f++)
        printf("* %s %d %d\n", auxl[f].descricao, auxl[f].preco, auxl[f].stock);
}

int comando_L(char arg[]){
	int i, j,k,t, l=2;                                       /* l e o identificador para a funcao L, na funcao merge e mergeSort */
	int ide;                                                 /* id da encomenda */
	Produto auxprod[MAXPROD];                                /* vetor auxiliar de produtos a ordenar */
	char inputSeparado[1][MAXARG];
	separaInput(arg, inputSeparado);
	ide = atoi(inputSeparado[0]);
    /* inicializa??o do vetor auxiliar */
	for(k=0; k<=contaProdutos-1; k++){
        auxprod[k].flag = 0;
		strcpy(auxprod[k].descricao," ");
	}
	if(encomendas[ide].flag ==1){
		for (i=0; i<=contaProdutos-1; i++){
			if(strcmp(encomendas[ide].produtosEncomendas[i].descricao, produtos[i].descricao)==0){
				auxprod[i]= produtos[i];
			}
		}
	}
	else{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return -1;
	}
    mergeSort(auxprod, 0, contaProdutos-1, l);
	printf("Encomenda %d\n", ide);
	for (j=0; j<= contaProdutos-1; j++){
		for(t=0; t<=contaProdutos-1; t++){
			if(encomendas[ide].contaProdEnc > 0){            /* se a encomenda tiver produtos */
				if(strcmp(auxprod[j].descricao, encomendas[ide].produtosEncomendas[t].descricao)==0) /* comparacao para aceder a quantidade desse produto */
					printf("* %s %d %d\n", auxprod[j].descricao,auxprod[j].preco,encomendas[ide].quantidade[t]);
			}
		}
	}return 0;
}

void mergeSort(Produto a[],int i,int j, int f){
	int mid;	
	if(i<j){
        if (f == 1){
		    mid=(i+j)/2;
		    mergeSort(a,i,mid,f);	                 	/* recursao para a esquerda */
		    mergeSort(a,mid+1,j,f);	                    /* recursao para a direita */
		    merge(a,i,mid,mid+1,j,f);	
        }
        else if(f == 2){
            mid=(i+j)/2;
		    mergeSort(a,i,mid,f);		               /* recursao para a esquerda */
		    mergeSort(a,mid+1,j,f);	                   /* recursao para a direita */
            merge(a,i,mid,mid+1,j,f);	
        }
	}
}
 
void merge(Produto a[],int i1,int j1,int i2,int j2, int f){
	Produto temp[MAXPROD];                             /* vetor de produtos auxiliar */
	int i,j,k;
	i=i1;	                                           /* inicio do primeiro vetor */
	j=i2;	                                           /* inicio do segundo vetor */
	k=0;
    if(f == 1){                                        /* f = 1 identifica funcao l, ordenacao pelo preco */
        while(i<=j1 && j<=j2){	
            if(a[i].preco<a[j].preco)
                temp[k++]=a[i++];
            else if(a[i].preco==a[j].preco && i<j)
                temp[k++]=a[i++];
            else
                temp[k++]=a[j++];
        }
    }
    else if (f==2){                                    /* f = 2 identifica funcao L, ordenacao pela descricao */
        while(i<=j1 && j<=j2){	
		    if(strcmp(a[i].descricao,a[j].descricao)<0)
		    	temp[k++]=a[i++];
		    else
		    	temp[k++]=a[j++];
	    }
    }
	while(i<=j1)	                                 /* copiar os restantes elementos do primeiro vetor */
		temp[k++]=a[i++];
	while(j<=j2)	                                 /* copiar os restantes elementos do segundo vetor */
		temp[k++]=a[j++];
    for(i=i1,j=0;i<=j2;i++,j++)                      /* transferir elementos de novo para vetor inicial ( de temp[] para a[] ) */
		    a[i]=temp[j];
}












