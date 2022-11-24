#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ENC 500 /*Quantidade max de encomendas*/
#define MAX_ID 10000 /*Quantidade max de produtos possiveis no sistema*/
#define MAX_LENGHT 63 /*Tamanho max da descricao do produto*/
#define MAX_PESO 200 /*Massa max de cada encomenda*/

/*   > TABELA -> array que guarda ID, preco, peso, quantidade do produto 
 * introduzido no sistema.
 * 	 > TABELA_DESCRICAO -> array que contem a descricao de produto 
 * introduzido no sistema. Exp: TABELA_DESCRICAO[3]=descricao de produto
 * com ID = 3.
 *  > ENCOMENDA -> array que guarda a encoemnda criada. Exp: 
 * ENCOMENDA[3][4]=quantidade de produto (ID=4) na encomenda (IDE=3) */

	
static int TABELA[MAX_ID][4], ENCOMENDA[MAX_ENC][(MAX_ID+1)]; 
static char TABELA_DESCRICAO[MAX_ID][MAX_LENGHT];
char descricao[MAX_LENGHT], resto[150], comando, palavra[MAX_LENGHT];


/* merge e mergeSort efetuam ordenacao de produtos pelo preco e pela descriacao */	
void merge(int arr[], int l, int m, int r, int identificacao) 
{ 
    int n1, n2, *L, *R; 
    int i, j, k;
    n1 = m - l + 1; 
    n2 =  r - m;
    L = (int *) can_fail_malloc(n1 * sizeof(int));
    R = (int *) can_fail_malloc(n2 * sizeof(int));
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
        
    i = 0; j= 0; k = l;
    while (i < n1 && j < n2) 
    { 
	/* identificacao==0 -> serao comparados os numeros
	 * identificacao==1 -> serao comparadas as descricoes*/
		if (identificacao == 0){ 
        if (TABELA[L[i]][1] <= TABELA[R[j]][1]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
		}
		else {
		if (identificacao == 1){ 
			if (strcmp(TABELA_DESCRICAO[L[i]],TABELA_DESCRICAO[R[j]])<0) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
			}		
		}
    } 
 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    }
    free(L); free(R); 
}

void mergeSort(int arr[], int l, int r, int identificacao) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
        mergeSort(arr, l, m, identificacao); 
        mergeSort(arr, m+1, r, identificacao); 
        merge(arr, l, m, r, identificacao); 
    } 
} 

/*	Funcao que calcula a massa da encomenda	*/
int calcula(int TABELA[MAX_ID][4], int ENCOMENDA[MAX_ENC][10001], \
int ide, int idp, int qnt){
	int s = 0, i;
	for (i=0; i<MAX_ID; i++){
		s=s+ENCOMENDA[ide][i]*TABELA[i][2];
		}
	s=s+qnt*TABELA[idp][2];
	return s;
	}

/* Funcao que separa o <resto> em descricao, preco, peso e quantidade */
void a(char resto[], char descricao[], int *preco, int *peso, int *qnt){
	int price, weight, qtty;
	sscanf(resto, "%[^:]%*c%d%*c%d%*c%d", descricao, &price, \
	&weight, &qtty);
	*preco = price; *peso = weight; *qnt = qtty;
	}
/* Funcao que separa o <resto> em idp e quantidade */
void q(char resto[], int *idp, int *qnt){
	int id, quantidade;
	sscanf(resto, "%d%*c%d", &id, &quantidade);
	*idp = id; *qnt = quantidade;
	}
/* Funcao que separa o <resto> em ide, idp e quantidade */
void A(char resto[], int *ide, int *idp, int *qnt){
	int id_prod, id_enc, qtty;
	sscanf(resto, "%d%*c%d%*c%d", &id_enc, &id_prod, &qtty);
	*ide = id_enc; *idp = id_prod; *qnt = qtty;
	}
/* Funcao que separa o <resto> em ide e idp */	
void R(char resto[], int *ide, int *idp){
	int id_prod, id_enc;
	sscanf(resto, "%d%*c%d", &id_enc, &id_prod);
	*ide = id_enc; *idp = id_prod; 
	}
/* Funcao que identifica no <resto> o ide */	
void C(char resto[], int *ide){
	int id_enc;
	sscanf(resto, "%d", &id_enc);
	*ide = id_enc;
	}
/* Funcao que separa o <resto> em idp e preco */
void p(char resto[], int *idp, int *preco){
	int id_prod, price;
	sscanf(resto, "%d%*c%d", &id_prod, &price);
	*idp = id_prod; *preco = price;
	}

int main(){
/* > ID funciona como contador de (ultimo produto+1), IDE funciona
* como contador de (ultima encomenda iniacializada+1)  */
	int preco=0, peso = 0, qnt=0, ID=0, idp=0, IDE = 0, ide = 0;
	
	scanf("%[^\n]",palavra);
	sscanf(palavra, "%c%*c%[^\n]", &comando, resto);

	while (comando != 'x'){
		if (comando == 'a'){
			a(resto, descricao, &preco, &peso, &qnt);
			strcpy(TABELA_DESCRICAO[ID], descricao);
			TABELA[ID][0] =	ID;
			TABELA[ID][1] = preco;
			TABELA[ID][2] = peso;
			TABELA[ID][3] = qnt;
			printf("Novo produto %d.\n", ID);
			++ID;	
			}
		if (comando =='q'){
			int variavel = 0;
			q(resto, &idp, &qnt);
			if (TABELA[idp][2]==0){ 
				printf("Impossivel adicionar produto %d ao stock. \
Produto inexistente.\n", idp);
				}
			else{
				variavel = TABELA[idp][3]+qnt;
				TABELA[idp][3]= variavel;
				}
			}
		if (comando =='N'){

			ENCOMENDA[IDE][MAX_ID]=1;
			printf("Nova encomenda %d.\n",IDE);
			++IDE;
			}
		if (comando =='A'){
			int variavel; int soma=0;
			A(resto, &ide, &idp, &qnt);
			soma=calcula(TABELA, ENCOMENDA, ide, idp, qnt);
			if (ENCOMENDA[ide][MAX_ID] == 0){
				printf("Impossivel adicionar produto %d a encomenda %d.\
 Encomenda inexistente.\n", idp, ide);
				}
			else if (TABELA[idp][2]==0){
				printf("Impossivel adicionar produto %d a encomenda %d.\
 Produto inexistente.\n", idp , ide);
				}
			else if (TABELA[idp][3]<qnt){
				printf("Impossivel adicionar produto %d a encomenda %d.\
 Quantidade em stock insuficiente.\n", idp , ide);
				}
			else if (soma>MAX_PESO){
				printf("Impossivel adicionar produto %d a encomenda %d.\
 Peso da encomenda excede o maximo de 200.\n", idp, ide);
				}
				
			else{
				variavel=ENCOMENDA[ide][idp]+qnt;
				TABELA[idp][3]= TABELA[idp][3]-qnt;
				ENCOMENDA[ide][idp]=variavel;
				}
			}
		if (comando =='r'){
			int variavel = 0;
			q(resto, &idp, &qnt); 
			if (TABELA[idp][1]==0){ 
				printf("Impossivel remover stock do produto %d. \
Produto inexistente.\n", idp);
				}
			else if(TABELA[idp][3]<qnt){
				printf("Impossivel remover %d unidades do produto %d \
do stock. Quantidade insuficiente.\n", qnt, idp);
					}
			else{
				variavel = TABELA[idp][3]-qnt;
				TABELA[idp][3]= variavel;
					}
			}	
		if (comando =='R'){
			R(resto, &ide, &idp);
			if (ENCOMENDA[ide][MAX_ID] == 0){
				printf("Impossivel remover produto %d a encomenda %d. \
Encomenda inexistente.\n", idp, ide);
					}
			else if(TABELA[idp][2]==0){
				printf("Impossivel remover produto %d a encomenda %d. \
Produto inexistente.\n", idp, ide);
					}
			else{
				TABELA[idp][3]=TABELA[idp][3]+ENCOMENDA[ide][idp];	
				ENCOMENDA[ide][idp]=0;	
					}
				}
		if (comando =='C'){
			int i, soma = 0;
			C(resto, &ide);
			if (ENCOMENDA[ide][MAX_ID] == 0){
				printf("Impossivel calcular custo da encomenda %d.\
 Encomenda inexistente.\n", ide);
					}
			else{
				for (i=0; i<(MAX_ID); i++){
					soma+=ENCOMENDA[ide][i]*TABELA[i][1];
						}
				printf("Custo da encomenda %d %d.\n", ide, soma);	
					}
				}
			if (comando =='p'){
				p(resto, &idp, &preco);
				if (TABELA[idp][2]!=0){TABELA[idp][1] = preco;}
				else{
					printf("Impossivel alterar preco do produto %d.\
 Produto inexistente.\n", idp);
						}
					}
			if (comando =='E'){
 /* Como o conteudo do <resto> (ide:idp) e igual no comando R e no 
  * comando E entao reutilizo a funcao R para identificar ide e idp*/
				R(resto, &ide, &idp);
				if (ENCOMENDA[ide][MAX_ID] == 0){
					printf("Impossivel listar encomenda %d.\
 Encomenda inexistente.\n",ide);}
				else if (TABELA[idp][2]==0){printf("Impossivel listar \
produto %d. Produto inexistente.\n",idp);
						}
				else{
					printf("%s %d.\n",TABELA_DESCRICAO[idp],\
					ENCOMENDA[ide][idp]);
						}
					}		
			if (comando =='m'){
				int i,qtty=0;
				C(resto, &ide);		
				idp = ide; ide = 0;
				if (TABELA[idp][0]==0 && TABELA[idp][2]==0){
					printf("Impossivel listar maximo do produto %d. \
Produto inexistente.\n",idp);
						}
				else{
					for (i=0; i<MAX_ENC; i++){
					if (ENCOMENDA[i][idp]>qtty){
						qtty = ENCOMENDA[i][idp] ;ide = i;
							}
						}
					if (qtty > 0){
						printf("Maximo produto %d %d %d.\n",\
						idp, ide, qtty);
							}
						}	
					}
			if (comando =='l'){
				int i ,j = 0, identificacao = 0;
				static int nova_lista[MAX_ID];
				for (i=0; i< ID+1; i++){
					if (TABELA[i][2]){
						nova_lista[j]=i;
						++j;					
								}
							}
				mergeSort(nova_lista, 0, j-1, identificacao);		
				printf("Produtos\n");	
					for (i=0; i<ID; i++){
					if (TABELA[nova_lista[i]][2]>0){
						printf("* %s %d %d\n", \
						TABELA_DESCRICAO[nova_lista[i]], \
						TABELA[nova_lista[i]][1], \
						TABELA[nova_lista[i]][3]);
							}
						}
					}
			if (comando =='L'){
				int i ,j=0, last_id=-1, identificacao = 1;
				static int nova_lista[MAX_ID];
				C(resto, &ide);
				if (ENCOMENDA[ide][MAX_ID]==0){
					printf("Impossivel listar encomenda %d. \
Encomenda inexistente.\n", ide);
						}
				else {
					for (i=0; i< ID+1; i++){
						if (ENCOMENDA[ide][i]){
							nova_lista[j]=i;
							++j;					
							}
						}
				mergeSort(nova_lista, 0, j-1, identificacao);	
				printf("Encomenda %d\n", ide);
				for (i=0; i<j; i++){
					if (ENCOMENDA[ide][nova_lista[i]] && \
					nova_lista[i] != last_id && \
					TABELA[nova_lista[i]][1]){
						printf("* %s %d %d\n", \
						TABELA_DESCRICAO[nova_lista[i]], \
						TABELA[nova_lista[i]][1], \
						ENCOMENDA[ide][nova_lista[i]]);
						last_id = nova_lista[i]; /*impede que o mesmo
						elemento seja imprimido duas vezes seguidas */
								}
							}
						}					
					}	
		scanf("	%[^\n]",palavra);
		sscanf(palavra, "%c%*c%[^\n]", &comando, resto);
		}
	return 0;
}
