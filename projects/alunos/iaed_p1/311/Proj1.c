#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/*Programa em linguagem C que permite gerir stocks de produtos e encomendas*/

/*Maximo de caracteres de uma descricao*/
#define MAX_CHAR 63  
/*Maximo de produtos*/           
#define MAX 10000  
/*Maximo de encomendas*/               
#define MAX_ENCOMENDAS 500 
 /*Peso maximo de cada encomenda*/        
#define MAX_PESO 200               
/*Funcao auxiliar para ordenar*/
typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A,B) { Item t = A; A = B; B =t;}



typedef struct produto
{
	int  preco, peso, qtd;
	char descricao[MAX_CHAR];
}Produto;


typedef struct encomenda
{
	int peso, preco, qtd_total, quantidade[MAX];
}Encomenda;

/*Vetor de produtos*/
Produto todos_produtos[MAX]; 

/* contador produtos */
int idp ;  


/*Vetor de encomendas*/
Encomenda todas_encomendas[MAX_ENCOMENDAS];

/* contador encomendas */
int ide; 


/*Adiciona um novo produto ao sistema*/
void executa_a(){
	scanf(" %[^:]:%d:%d:%d", todos_produtos[idp].descricao, &todos_produtos[idp].preco, 
		&todos_produtos[idp].peso, &todos_produtos[idp].qtd);
	printf("Novo produto %d.\n", idp);
	idp++;
}

/*Adiciona stock a um produto existente no sistema*/
void executa_q(){
	int idp_exemplo; 
	int stock; 
	scanf("%d:%d", &idp_exemplo, &stock);
	if(idp_exemplo < idp){
		todos_produtos[idp_exemplo].qtd += stock;		
	}
	else {
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_exemplo);
	}
}
 
/*Cria uma nova encomenda*/
void executa_N(){
	printf("Nova encomenda %d.\n",ide);
	ide++;
}


/*Adiciona um produto a uma encomenda.Caso o produto ja exista,
adiciona a nova quantidade ? existente*/
void executa_A(){
	int ide_exemplo; 
	int idp_exemplo; 
	int stock; 
	scanf("%d:%d:%d", &ide_exemplo, &idp_exemplo, &stock);
	if(ide_exemplo >= ide){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_exemplo, ide_exemplo);
	}
	else if(idp_exemplo >= idp){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_exemplo, ide_exemplo);
	}
	else if(todos_produtos[idp_exemplo].qtd - stock< 0){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_exemplo, ide_exemplo);
	}
	else if((todos_produtos[idp_exemplo].peso * stock) + todas_encomendas[ide_exemplo].peso > MAX_PESO){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_exemplo, ide_exemplo);
	}
	else{
		/*Caso o produto exista atualizamos os valores da encomenda e do produto*/
		todas_encomendas[ide_exemplo].peso += (todos_produtos[idp_exemplo].peso * stock);  
		todas_encomendas[ide_exemplo].preco += (todos_produtos[idp_exemplo].preco * stock);
		todos_produtos[idp_exemplo].qtd -= stock;
		todas_encomendas[ide_exemplo].quantidade[idp_exemplo] += stock;
		todas_encomendas[ide_exemplo].qtd_total += stock;
		
	}
}

/*Remove stock a um produto existente*/
void executa_r(){
	int idp_exemplo; 
	int stock; 
	scanf("%d:%d", &idp_exemplo, &stock);	
	if(idp_exemplo >= idp){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_exemplo);
	}
	else if(todos_produtos[idp_exemplo].qtd - stock < 0){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock ,idp_exemplo);
	}
	else{
		todos_produtos[idp_exemplo].qtd -= stock;
	}
}
 
/*Remove um produto de uma encomenda*/
void executa_R(){
	int ide_exemplo; 
	int idp_exemplo; 
	scanf("%d:%d", &ide_exemplo, &idp_exemplo);
	if(ide_exemplo >= ide){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp_exemplo ,ide_exemplo);
	}
	else if(idp_exemplo >= idp){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp_exemplo,ide_exemplo);
	}
	else{
		/*Caso a encomenda e o produto existam,atualizamos os valores destes*/
		todas_encomendas[ide_exemplo].peso -= (todas_encomendas[ide_exemplo].quantidade[idp_exemplo]*todos_produtos[idp_exemplo].peso);
		todas_encomendas[ide_exemplo].preco -= (todas_encomendas[ide_exemplo].quantidade[idp_exemplo]*todos_produtos[idp_exemplo].preco);
		todos_produtos[idp_exemplo].qtd += todas_encomendas[ide_exemplo].quantidade[idp_exemplo];
        todas_encomendas[ide_exemplo].qtd_total -= todas_encomendas[ide_exemplo].quantidade[idp_exemplo];
        todas_encomendas[ide_exemplo].quantidade[idp_exemplo] = 0;
	}
}

/*Calcula o custo de uma encomenda*/
void executa_C(){
	int ide_exemplo; 
	scanf("%d",&ide_exemplo);
	if(ide_exemplo >= ide){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide_exemplo);
	}
	else{
		printf("Custo da encomenda %d %d.\n",ide_exemplo,todas_encomendas[ide_exemplo].preco);
	}
}

/*Altera o preco de um produto existente no sistema*/
void executa_p(){
	int idp_exemplo; 
	int novo_preco; 	
	scanf("%d:%d", &idp_exemplo, &novo_preco);
	if(idp_exemplo >= idp){		
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_exemplo);
	}
	else {
		int ide_exemplo;
		/*Ao alterar o preco do produto, teremos que consequentemente 
		alterar o preco das encomendas que contenham esse produto*/
		for(ide_exemplo=0 ; ide_exemplo < ide ; ide_exemplo++){
			todas_encomendas[ide_exemplo].preco -= todas_encomendas[ide_exemplo].quantidade[idp_exemplo]*todos_produtos[idp_exemplo].preco;
		    todas_encomendas[ide_exemplo].preco += todas_encomendas[ide_exemplo].quantidade[idp_exemplo]*novo_preco;  
		}   
		todos_produtos[idp_exemplo].preco = novo_preco;
	}
}

/*Lista a descricao e a quantidade de um produto numa encomenda*/
void executa_E(){
	int ide_exemplo; 
	int idp_exemplo; 
	scanf("%d:%d", &ide_exemplo, &idp_exemplo);
	if(ide_exemplo >= ide){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_exemplo);
	}
	else if(idp_exemplo >= idp){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp_exemplo);
	}
	else{
		printf("%s %d.\n",todos_produtos[idp_exemplo].descricao, todas_encomendas[ide_exemplo].quantidade[idp_exemplo]);
	}
}

/*Lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
void executa_m(){
	int idp_exemplo; 
	scanf("%d", &idp_exemplo);
	if(idp_exemplo >= idp){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp_exemplo);
	}
	else{
		int ide_exemplo; 
		int j=0;/*maior quantidade do produto*/
		int n; /*guarda o indice da encomenda*/
		for(ide_exemplo =0 ; ide_exemplo < ide ; ide_exemplo++){
			if(todas_encomendas[ide_exemplo].quantidade[idp_exemplo] > j){
				/*Enquanto nao encontrar nenhuma encomenda com 
				mais produto que j, guarda esse valor em j*/
				j = todas_encomendas[ide_exemplo].quantidade[idp_exemplo]; 
				n = ide_exemplo;
			}
		}
		if(j >0){
			printf("Maximo produto %d %d %d.\n",idp_exemplo,n,j);
		}
	}
}

/*Funcao auxiliar que implementa um algoritmo de ordenacao*/
int partition(Item a[], int l , int r){
	int i = l-1;
	int j = r;
	Item v = a[r];
	while(i <j){
		while(less(a[++i], v));
		while(less(v, a[--j]))
			if(j ==l)
				break;
		if( i <j )
			exch(a[i], a[j]);
	}
	exch(a[i], a[r]);
	return i;
}

/*Funcao auxiliar que implementa um algoritmo de ordenacao*/
void quicksort(Item a[], int l , int r ){
	int i;
	if(r <= l) return;
	i = partition(a, l, r);
	quicksort(a ,l,i-1);
	quicksort(a ,i+1,r);
}

/*Lista todos os produtos existentes no sistema por ordem crescente de preco*/
void executa_l(){
	int idp_exemplo;
	int j;
	int vet[MAX];
	for(idp_exemplo=0 ; idp_exemplo < idp ; idp_exemplo++){
		vet[idp_exemplo] = todos_produtos[idp_exemplo].preco;
	}
	quicksort(vet, 0, idp-1);
	printf("Produtos\n");
	for(j=0 ; j < idp ; j++){
		for(idp_exemplo=0; idp_exemplo < idp ; idp_exemplo++){
			if(vet[j] == todos_produtos[idp_exemplo].preco){
				printf("* %s %d %d\n", todos_produtos[idp_exemplo].descricao, vet[j], todos_produtos[idp_exemplo].qtd);
				break;
			}
		}
	}
}






/*Lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
void executa_L(){
    int i=0, n=0, ide_exemplo, idp_exemplo, j;
    char str[MAX][63], temp[63];
    
    scanf("%d", &ide_exemplo);
    if(ide_exemplo >= ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_exemplo);
    }
    else{
        for(idp_exemplo=0; idp_exemplo < idp ; idp_exemplo++){
            if(todas_encomendas[ide_exemplo].quantidade[idp_exemplo] > 0){
                strcpy(str[n], todos_produtos[idp_exemplo].descricao);
                n++;
            }
        }
        /*Algoritmo de ordenacao de strings*/
        for(i=0; i<= n; i++)
             for(j=i+1 ; j<= n ; j++){
                 if(strcmp(str[i],str[j])>0){
                     strcpy(temp,str[i]);
                     strcpy(str[i],str[j]);
                     strcpy(str[j],temp);
                }
            }
        printf("Encomenda %d\n",ide_exemplo);
        for(j=0; j < n; j++){
            for(idp_exemplo=0; idp_exemplo < idp; idp_exemplo++){
                if(strcmp(str[j],todos_produtos[idp_exemplo].descricao)){
                    printf("* %s %d %d\n",str[j], todos_produtos[idp_exemplo].preco , todas_encomendas[ide_exemplo].quantidade[idp_exemplo]);
                    break;
                }
            }
        }

    }
}


/*Escolhe entre um dos comandos*/
int main(){
	char comando;
	while((comando = getchar())!= 'x'){
		switch (comando){
			case 'a':
			   executa_a();
			   break;
			case 'q':
			   executa_q();
			   break;
			case 'N':
			   executa_N();
			   break;
 			case 'A':
 			   executa_A();
			   break;
            case 'r':
			    executa_r();
			    break;
			case 'R':
                executa_R();
			    break;
			case 'C':
			   executa_C();
			   break;
			case 'p':
			    executa_p();
			    break;
			case 'E':
			   executa_E();
			   break;
			case 'm':
			   executa_m();
			   break;
			case 'l':
			   executa_l();
			   break;
			case 'L':
			  executa_L();
			  break;
		}
		getchar();
	}	
	return 0;
}


