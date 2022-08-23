#include <stdio.h>
#include <string.h>
#define MAXPESO 200
#define MAXDEF 64
#define MAX_ID_PROD 9999 
#define MAX_ID_ENC  499
#define MAX_STR 300
#define MAX_PROD 10000
#define ORDENAR 0
#define ID 1
typedef int Item;
#define key(A)  A
#define less(A,B) (key(A) < key(B))
#define	exch(A,B) {Item t = A; A = B; B = t;}

typedef struct{
	int id;
	char des[MAXDEF];
	int preco;
	int peso;
	int stck;
}produto;

typedef struct{
	produto prod; 	                             
	int peso;
	int prod_stck[MAX_PROD];   /*armazena na parte do vetor cuja chave ? o id do produto a quantidade do mesmo*/
	int preco;
}encomenda;

int id_prod;        		/*id do produto e global de modo a nunca ser repetida*/
int id_enc;                 /*id da encomenda e global de modo a nunca ser repetida*/
int id_enc_prod;

produto prod[MAX_ID_PROD];

encomenda enc[MAX_ID_ENC];

int aux;
/*
void inicia_stock(){
for (aux =0; aux < MAX_ID_ENC; aux++)
	for(int aux1 = 0; aux1 < MAX_ID_PROD; aux1++)
		enc[aux].prod_stck[aux1] = 0;
}
*/
/*constroi o produto a partir do input*/
void Setproduto(int id, char prod_des[MAXDEF], int preco, int peso, int stck);
/*

*/
/*cria o produto na base de dados*/
void command_a();

/*adiciona stock a prods existentes*/
void adiciona_stock();

/*cria uma nova encomenda*/
void command_N();

/*adiciona produtos a encomendas*/
void command_A();

/*diminui o stock de um produto*/
void remove_stock(int idp, int qnt);

/*remove a quantidade introduzida do stock de um prod*/
void command_r();

/*remove o produto da encomenda*/
void command_R();

/*calcula o custo de uma encomenda*/
void command_C();

/*altera o preco de um produto existente*/
void command_p();

/*lista a descricao e a quantidade de um produto na encomenda*/
void command_E();

/*indica a encomenda em q o produto esta mais vezes*/
void command_m();

void swap(int* a, int* b); 

void quickSort(int arr[], int low, int high);

int partition (int arr[], int low, int high); 

void copia_vect(produto orig[MAX_PROD], int ordenar[MAX_PROD]){
	for(aux = 0 ;aux < id_prod; aux++){
        ordenar[aux] = orig[aux].preco;
        printf("input:%d\n", ordenar[aux]);
    }
   	return;
}

void Merge(Item a[],int l,int m,int r){
    int i,j,k,aux[MAX_PROD];
    for (i=m+1;i>l;i--){aux[i-1]=a[i-1];}
    for (j=m;j<r;j++){aux[r+m-j]=a[j+1];}
    for (k=l;k<=r;k++){
        if less(aux[j],aux[i]){a[k]=aux[j--];}
        else{a[k]=aux[i++];}
    }
}
void MergeSort(Item a[],int l,int r){
    int m=(l+r)/2;
    if (r<=l){return;}
    MergeSort(a,l,m);
    MergeSort(a,m+1,r);
    Merge(a,l,m,r);
}

int idp, qnt, preco, peso, aux, exist, ide, copia[MAX_PROD]; 
char crct, des[MAXDEF];

/*chama as funcoes que executam todos os comandos possiveis */
int main(){
	/*inicia_stock();*/
	while((crct= getchar()) != EOF && crct != 'x'){
		switch (crct){
			case('a'):
				command_a();
				break;

			case('q'):
				adiciona_stock();
				break;

			case('N'):
				command_N();
				break;

			case('A'):
				command_A();
				break;
		
			case('r'):
				command_r();
				break;

			case('R'):
				command_R();	
				break;

			case('C'):
				command_C();
				break;

			case('p'):
				command_p();
				break;
			
			case('E'):
				command_E();
				break;


			case('m'):
				command_m();
				break;

			case('l'):  
				printf("Produtos\n");
				copia_vect(prod, copia);
   				MergeSort(copia, 0, id_prod-1);
   				for(aux=0; aux < id_prod;aux++)
   					printf("*%s %d %d\n", prod[copia[aux]].des, prod[copia[aux]].preco, prod[copia[aux]].stck);
				break;
		}
	}
	return 0;
}

void Setproduto(int id, char prod_des[MAXDEF], int preco, int peso, int stck){
	prod[id].id = id;
	strcpy(prod[id].des, prod_des);
	prod[id].preco = preco;
	prod[id].peso = peso;
	prod[id].stck = stck;
}

void command_a(){
	idp = id_prod++;
	scanf("%[^:]:%d:%d:%d", des, &preco, &peso, &qnt); 				  	
	Setproduto(idp, des, preco, peso, qnt);
	printf("Novo produto %d.\n", idp);
}


void adiciona_stock(){
	scanf("%d:%d", &idp, &qnt);
	if (idp >= id_prod)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp); 
	else{
		prod[idp].stck += qnt;	
	}
}


void command_N(){
	ide = id_enc++;
	printf("Nova encomenda %d\n", ide);
}

void command_A(){
	scanf("%d:%d:%d", &ide, &idp, &qnt);
	if(ide >= id_enc){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}	
	
	else if (idp >= id_prod){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}

	else if (prod[idp].stck < qnt){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	}

	else if ((prod[idp].peso * qnt + enc[ide].peso) > MAXPESO){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
	}	

	else{
		exist = 1;
		for(aux=0; aux < id_prod; aux++){
			if (aux == idp){
				exist = 0; 										                    /* indica que o pruduto ja se encontrava na encomenda*/ 
				enc[ide].prod_stck[aux]+= qnt;
				enc[ide].peso += prod[idp].peso * qnt;
				remove_stock(idp, qnt);
				break; 
			}
		}
		if (exist){                                                                  /* inicializa o produto se nao se encontra na encomenda*/ 
			enc[ide].prod_stck[idp] = qnt;
			enc[ide].peso = prod[idp].peso * qnt;
			remove_stock(idp, qnt);
		}
	}
}

void remove_stock(int idp, int qnt){
	if (idp >= id_prod)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	else if(prod[idp].stck < qnt)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qnt, idp);
	else{
		prod[idp].stck -= qnt;
	}
}

void command_r(){
	scanf("%d:%d", &idp, &qnt);
	remove_stock(idp, qnt);
}

void command_R(){
	scanf("%d:%d", &ide, &idp);
	if (ide >= id_enc)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

	else if(idp >= id_prod)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", qnt, idp);
			
	else if (enc[ide].prod_stck[idp] != 0){
		enc[ide].prod_stck[idp] = 0;
		enc[ide].peso -= prod[idp].peso * qnt;
		adiciona_stock(idp, qnt);
	}	
}

void command_C(){
	scanf("%d", &ide);
	if (ide >=id_enc)
		printf("Impossivel calcular custo da encomenda %d\n", ide);
	
	else{
		enc[ide].preco = 0;
		for (aux=0; aux < id_prod; aux++){
			enc[ide].preco += (prod[aux].preco * enc[ide].prod_stck[aux]);
		}
		printf("Custo da encomenda %d %d.\n", ide, enc[ide].preco);
	}
}

void command_p(){
	scanf("%d:%d", &idp, &qnt);
	if (idp >= id_prod)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	else{
		prod[idp].preco = qnt;
	}
}

void command_E(){
	scanf("%d:%d", &ide, &idp);
	if (idp >= id_prod)
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	
	else if(ide >= id_enc)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	
	else{
		printf("%s %d\n", prod[idp].des, enc[ide].prod_stck[idp]);	
	}
}

void command_m(){
	scanf("%d", &idp);
	if (idp >= id_prod)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.", idp);
	
	else{
		exist = 0;
		qnt = 0;
		for (aux=0; aux < id_enc; aux++){
			if(enc[aux].prod_stck[idp] > qnt){
				exist = 1;
				qnt = enc[aux].prod_stck[idp];
				ide = aux;
			}
		}
		if (exist)
			printf("Maximo produto %d %d %d", idp, ide, qnt);
	}
}

