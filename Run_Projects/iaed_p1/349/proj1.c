#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NIDENT 10000	/* Numero maximo de produtos. */
#define NDESCR 64		/* Numero maximo de caracteres da descricao. */
#define NENCOM 500		/* Numero maximo de encomendas. */
#define PENCOM 200		/* Peso maximo por encomenda. */


typedef struct Produto{
	
	int identificador;
	char descricao[NDESCR];
	int preco;
	int peso;
	int quantidade;

}Produto;


typedef struct Encomenda{
	Produto prod[NIDENT];
	int qt_prod;
	int id_e;
	int peso_e;

}Encomenda;


/*****************Global Variables*********************/

/* Array que guarda as informacoes do produto. */
Produto pvetor[NIDENT];

/* Array que guarda as informacoes das encomendas. */
Encomenda evetor[NENCOM];

/* Variavel que controla o numero de produtos. */
int cont_pgeral = 0;

/* Variavel que controla o numero de encomendas. */
int cont_egeral = 0;

/******************************************************/


/* Funcao que adiciona um novo produto ao sistema. */
void AddProduct(){

	getchar();
	scanf("%[^:]:%d:%d:%d", pvetor[cont_pgeral].descricao, &pvetor[cont_pgeral].preco, &pvetor[cont_pgeral].peso, &pvetor[cont_pgeral].quantidade);
	pvetor[cont_pgeral].identificador = cont_pgeral;
	printf("Novo produto %d.\n", cont_pgeral);
}


/* Funcao que adiciona stock a um produto existente. */
void AddStock(){
	
	/* Variaveis utilizadas para captar o idp e a qtd do input. */
	int idp=0, qtd=0;

	getchar();
	scanf("%d:%d",&idp, &qtd);
	if (idp>= cont_pgeral)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	else
		pvetor[idp].quantidade += qtd;
}


/* Funcao que cria uma nova encomenda. */
void NewOrder(){

	printf("Nova encomenda %d.\n", cont_egeral);
}


/* Funcao que adiciona um produto a uma encomenda. */
void AddToOrder(){

	/* Variaveis  utilizadas para captar o ide, o idp e a qtd do input. */
	int ide, idp, quantidade;

	/* Variaveis auxiliares. */
	int x=0,estado=0, tamanho=0, peso_atual=0, peso_entrar=0, peso_produto=0;

	getchar();
	scanf("%d:%d:%d", &ide, &idp, &quantidade);

	if (ide>=cont_egeral){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		estado = 1;
	}
	else if(idp>=cont_pgeral){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		estado = 1;
	}
	
	/* Caso o produto ja exista na encomenda. */
	for(x=0; x<evetor[ide].qt_prod; x++){
		if(evetor[ide].prod[x].identificador == idp){
			estado = 1;
			peso_atual = evetor[ide].peso_e;
			peso_entrar = quantidade * pvetor[idp].peso;
			if (pvetor[idp].quantidade - quantidade < 0)
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
			else if ( peso_atual + peso_entrar > PENCOM)
				printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide );
			else{
				evetor[ide].prod[x].quantidade += quantidade;
				pvetor[idp].quantidade -= quantidade;
				evetor[ide].peso_e += peso_entrar;
			}
		}
	}

	/* Caso o produto nao exista na encomenda. */
	if (estado==0){
		tamanho = evetor[ide].qt_prod;
		peso_produto = pvetor[idp].peso * quantidade;
		if (pvetor[idp].quantidade - quantidade < 0)
			printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		else if (evetor[ide].peso_e +  peso_produto > PENCOM){
			printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide );
		}

		else{
			evetor[ide].prod[tamanho].identificador = idp;
			strcpy(evetor[ide].prod[tamanho].descricao,pvetor[idp].descricao);
			evetor[ide].prod[tamanho].quantidade = quantidade;
			pvetor[idp].quantidade -= quantidade;
			evetor[ide].peso_e += peso_produto;
			evetor[ide].qt_prod += 1;
		}
	}
}


/* Funcao que remove stock a um produto existente. */
void RemoveStock(){
	
	/* Variaveis utilizadas para captar o idp e a qtd do input. */
	int idp=0, qtd=0;

	getchar();
	scanf("%d:%d", &idp, &qtd);
	if (idp>= cont_pgeral)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	else if ((pvetor[idp].quantidade - qtd) < 0)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
	else
		pvetor[idp].quantidade -= qtd;
}


/* Funcao que remove um produto de uma encomenda. */
void RemoveFromOrder(){

	/* Variaveis utilizadas para captar o ide e a idp do input. */
	int ide, idp, i=0;

	getchar();
	scanf("%d:%d", &ide, &idp);
	if (ide >= cont_egeral)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if( idp >= cont_pgeral)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	for(i=0; i<evetor[ide].qt_prod; i++){
		if(evetor[ide].prod[i].identificador == idp){
			pvetor[idp].quantidade += evetor[ide].prod[i].quantidade;
			evetor[ide].peso_e -= (evetor[ide].prod[i].quantidade * pvetor[idp].peso);
			evetor[ide].prod[i].quantidade = 0;
		}
		else continue;
	}
}


/* Funcao que calcula o custo de uma encomenda. */
void OrderCost(){

	/* Variaveis utilizadas para captar o ide. */
	int ide, i, total=0;

	getchar();
	scanf("%d", &ide);
	if (ide >= cont_egeral)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	else{
		for(i=0; i< evetor[ide].qt_prod; i++){
			if(evetor[ide].prod[i].quantidade > 0)
				total += (evetor[ide].prod[i].quantidade * pvetor[(evetor[ide].prod[i].identificador)].preco);
			else continue;
		}
		printf("Custo da encomenda %d %d.\n", ide, total);
	}
}


/* Funcao que troca o preco a um produto existente. */
void ChangePrice(){
	
	/* Variaveis utilizadas para captar o idp e a qtd do input. */
	int idp=0, pric=0;

	getchar();
	scanf("%d:%d", &idp, &pric);
	if (idp>= cont_pgeral)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	else
		pvetor[idp].preco = pric;
}


/* Funcao que lista a descricao e a quantidade do produto na encomenda. */
void OrderProperties(){
	
	/* Variaveis utilizadas para captar o ide e o idp do input. */
	int ide, idp, estado=0;

	/* Variavel usada para ciclo. */
	int i;

	getchar();
	scanf("%d:%d", &ide, &idp);
	if (ide >= cont_egeral)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else if (idp >= cont_pgeral)
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	else{
		for(i=0; i < evetor[ide].qt_prod; i++){
			if (evetor[ide].prod[i].identificador == idp){
					printf("%s %d.\n", pvetor[idp].descricao, evetor[ide].prod[i].quantidade);
					estado=1;
			}
			else continue;
		}
	if (estado == 0)
		printf("%s 0.\n", pvetor[idp].descricao);
	}
}


/* Funcao que indica a encomenda com mais produto. */
void LargestProductinOrder(){

	int idp, i, e, maior = 0, maior2 = 0, estado =0;
	getchar();
	scanf("%d", &idp);

	if (idp >= cont_pgeral)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);

	else {
		for (i=0; i< cont_egeral; i++){
			for(e=0; e< evetor[i].qt_prod; e++){
				if(evetor[i].prod[e].identificador == idp){
					if(evetor[i].prod[e].quantidade > maior){
						maior = evetor[i].prod[e].quantidade;
						maior2 = i;
						estado = 1;
					}
				}
			}
		}
	}

	if (estado == 1)
		printf("Maximo produto %d %d %d.\n", idp, maior2, maior);
} 


/* Funcao que divide a array dos precos e a array dos ids em duas arrays. */
void Merge(int arr[NIDENT],int ids[NIDENT], int l, int m, int r){
	
	/* Variaveis de ciclos e de comprimentos de arrays. */ 
    int i, j, k; 
    int n1 = m-l+1; 
    int n2 = r-m; 
  	
    /* Cria arrays temporarias. */
    int L[NIDENT], R[NIDENT],P[NIDENT], Q[NIDENT];
 	
 	/* Copia a informacao para os Arrays L,R,P,Q. */
    for (i = 0; i < n1; i++){
        L[i] = arr[l+i];
        P[i] = ids[l+i]; 
    }
    for (j = 0; j < n2; j++){ 
        R[j] = arr[m+1+j];
        Q[j] = ids[m+1+j];
    } 

    /* Reinicializa as variaveis. */
    i = 0;  
    j = 0; 
    k = l; 

    /* Volta a meter os valores nas arrays originais. */
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){ 
            arr[k] = L[i];
            ids[k] = P[i]; 
            i++; 
        } 
        else{ 
            arr[k] = R[j];
            ids[k] = Q[j]; 
            j++; 
        } 
        k++; 
    } 

    /* Copia os	valores restantes da L e P se ainda houver. */
    while (i < n1){
        arr[k] = L[i];
        ids[k] = P[i]; 
        i++; 
        k++; 
    } 
  
  	/* Copia os	valores restantes da R e Q se ainda houver. */
    while (j < n2){
        arr[k] = R[j];
        ids[k] = Q[j];
        j++; 
        k++; 
    } 
} 

  
/* Algoritmo de ordenacao utilizado para ordenar os produtos. */
void MergeSort(int arr[NIDENT], int ids[NIDENT], int l, int r){

    if (l < r){
    	int m = l+(r-l)/2; 
        MergeSort(arr,ids, l, m); 
        MergeSort(arr,ids, m+1, r); 
        Merge(arr,ids, l, m, r); 
    } 
}


/* Funcao que ordena os produtos por preco. */
void SortPrice(){

	/* Variaveis usadas para ciclos. */
	int i=0, j=0;

	/* Array que guarda copia dos precos. */
	int arr[NIDENT];

	/* Array que guarda copia dos identificadores. */
	int ids[NIDENT];

	for(i=0; i<cont_pgeral; i++){
		arr[i] = pvetor[i].preco;
		ids[i] = pvetor[i].identificador;
	}

	/* Chamada da funcao que ordena os precos. */
	MergeSort(arr, ids, 0,(cont_pgeral-1));

	printf("Produtos\n");
	for(j=0; j<cont_pgeral; j++)
		printf("* %s %d %d\n", pvetor[ids[j]].descricao,pvetor[ids[j]].preco,pvetor[ids[j]].quantidade);
}


/* Algoritmo de ordenacao utilizado para ordenar os produtos de uma encomenda por ordem alfabetica. */
void AlphabeticalSort(char arr[NIDENT][NDESCR], int ids[NIDENT], int ide){

	/* Variaveis usadas para ciclos e auxiliares. */
	int i, j, aux2;

	/* Variavel auxiliar para guardar "strings". */
	char aux[NDESCR];

	for(i=1; i < evetor[ide].qt_prod; i++) {
	  	for(j=1; j < evetor[ide].qt_prod; j++) {
	        if (strcmp(arr[j-1], arr[j]) > 0) {
	           strcpy(aux, arr[j-1]);
	           aux2 = ids[j-1];
	           strcpy(arr[j-1], arr[j]);
	           ids[j-1] = ids[j];
	           strcpy(arr[j], aux);
	           ids[j] = aux2;
	        }
	    }
	}
}


/* Funcao que ordena os produtos de uma encomenda por ordem alfabetica. */
void SortName(){

	/* Variaveis usadas para ciclos e guardar ide do input. */
	int l, x, e, ide;

	/* Array que guarda copia dos identificadores. */
	int  ids[NIDENT];

	/* Array que guarda copia das descricoes. */
	char arr[NIDENT][NDESCR];

	getchar();
	scanf("%d", &ide);

	if (ide >= cont_egeral)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

	else{
		for(e=0; e< evetor[ide].qt_prod; e++){
			ids[e] = evetor[ide].prod[e].identificador;
			strcpy(arr[e],evetor[ide].prod[e].descricao);
		}

		/* Chamada da funcao que ordena as descricoes. */
		AlphabeticalSort(arr, ids, ide);

	   	printf("Encomenda %d\n", ide);
	   	for(x=0; x< evetor[ide].qt_prod; x++){
	   		for(l=0; l< evetor[ide].qt_prod; l++){
	   			if((evetor[ide].prod[l].identificador == ids[x]) && (evetor[ide].prod[l].quantidade > 0)){
	   				printf("* %s %d %d\n", pvetor[ids[x]].descricao, pvetor[ids[x]]. preco, evetor[ide].prod[l].quantidade);
	   			}
	   		}
	   	}
	}
}


/* Le o comando do input e redirenciona cada comando para a sua funcionalidade. */
int main(){

	/* Variavel que guarda a letra do comando do input. */
	char c;

	while ((c = getchar()) != EOF && c != 'x'){
		if (c == 'a'){
			AddProduct();
			cont_pgeral += 1;
		}
		else if (c == 'q')
			AddStock();

		else if (c == 'N'){
			NewOrder();
			cont_egeral += 1;
		}
		else if (c == 'A')
			AddToOrder();

		else if (c == 'r')
			RemoveStock();

		else if (c == 'R')
			RemoveFromOrder();

		else if (c == 'C')
			OrderCost();

		else if (c == 'p')
			ChangePrice();

		else if (c == 'E')
			OrderProperties();

		else if (c == 'm')
			LargestProductinOrder();

		else if (c == 'l')
			SortPrice();

		else if (c == 'L')
			SortName();

		else
			continue;
	}
	return 0;
}