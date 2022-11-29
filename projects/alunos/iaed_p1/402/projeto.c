#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include<string.h>

/* CONSTANTES */
#define MAX_IDP 10000
#define MAX_ENC 500
#define MAX_PESO 200

/* FUNCOES */
#define exch(A, B){Produto t=A; A=B; B=t;}


/* Definicao da estrutura PRODUTO */
typedef struct produto{

	int idp;							/* Identificador de produto */
	char desc[64];						/* Descricao com 63 caracteres + '\0' */
	int preco;							/* Preco do produto */
	int peso;							/* Peso do produto */
	int qtd;							/* Quantidade em stock */

} Produto;


/* Definicao da estrutura Encomenda */
typedef struct encomenda{
		
	int ide;							/* Numero de encomenda */
	int n_prod;							/* Numero de produtos na encomenda */
	Produto prod_enc[MAX_PESO];			/* Vetor com todos os produtos da encomenda */
	 
} Encomenda;	


/*-------------------------------------------------------------------------------------------------------------------*/

/* Variaveis globais*/
Produto produtos[MAX_IDP]; 				/* Vetor com todos os produtos */
int indice_produtos=0;	   				/* Contador de produtos */
Encomenda encomendas[MAX_ENC];			/* Vetor com todas as encomendas */
int indice_encomendas=0;				/* Contador das encomendas */


/* Criacao do produto que eh guardado na variavel global (stock de produtos) */
Produto cria_produto(){

	Produto a;

	/* Inicializa a zero */
	a.idp=indice_produtos;
	/* Cada vez que chamam esta funcao, o indice (numero de produtos) aumenta */
	indice_produtos++;					
	
	scanf(" %[^:]:%d:%d:%d\n", a.desc,&a.preco,&a.peso,&a.qtd);			
	
	/* Guarda no vetor dos PRODUTOS */
	produtos[a.idp]=a;
	
	printf("Novo produto %d.\n",a.idp);

	return a;
}


/* Edita a quantidade do produto consoante a quantidade inserida */ 
void edita_quantidade(){

	int quantidade,idp;

	scanf(" %d:%d\n",&idp,&quantidade);
	
	if (idp>=indice_produtos){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
	}
	/* Adiciona ao produto idp a quantidade inserida no vetor dos PRODUTOS */
	else produtos[idp].qtd+=quantidade;
}


/*Criacao da encomenda */
Encomenda cria_encomenda(){
	
	Encomenda a;

	/* Inicializa a zero */
	a.ide=indice_encomendas;
	/* Incrementa do numero de encomendas */
	indice_encomendas++;

	printf("Nova encomenda %d.\n",a.ide);

	return a;
}


/* AUXILIAR - Calcula peso total da encomenda */
int peso_Enc(Encomenda encomenda){

	int peso_total=0,i;

	for (i=0;i<encomenda.n_prod;i++){
		/* (O peso do produto da encomenda + a Quantidade inserida) x Peso do produto da encomenda */
		peso_total+=encomenda.prod_enc[i].peso * encomenda.prod_enc[i].qtd;
		
	}

	return peso_total;
} 


/* Adiciona produtos ? encomenda */
void add_produto(){

	int quantidade,i,idp,ide;

	scanf(" %d:%d:%d",&ide,&idp,&quantidade);

	if (idp>=indice_produtos){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
	}
	else if (ide>=indice_encomendas){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
	}
	else if (quantidade>produtos[idp].qtd){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
	}
	else if (peso_Enc(encomendas[ide]) + produtos[idp].peso * quantidade > MAX_PESO){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
	}
	else{

		int FLAG=0;

		/* Corre todos os produtos da encomenda */
		for (i=0;i<encomendas[ide].n_prod;i++){			
			
			/* Se ja existir o produto na encomenda */
			if(encomendas[ide].prod_enc[i].idp == idp){

				/* Aciona a flag, significa que o produto idp esta na encomenda */
				FLAG = 1;
				
				/* Adiciona a quantidade de produto na encomenda */
            	encomendas[ide].prod_enc[i].qtd += quantidade;
           		/* Retira quantidade de produto adicionado a encomenda */
           		produtos[idp].qtd-=quantidade;
				
				/* Sai do ciclo */
				break;
			}
		}

		/* Se nao houver nenhum produto ou se esse produto nao estiver no vetor dos produtos das encomendas */
		if (FLAG==0){

			/* Adiciona o produto a encomenda */
			encomendas[ide].prod_enc[i] = produtos[idp];
			/* Adiciona o produto ao vetor das quantidades da encomenda */
			encomendas[ide].prod_enc[i].qtd=quantidade;
    		/* Incrementa o contador de produtos na encomenda */
    		encomendas[ide].n_prod++;
    		/* Retira quantidade de produto adicionado a encomenda */
    		produtos[idp].qtd-=quantidade;
    	}
	}
}


/*Remove stock aos produtos */
void remove_stock(){

	int quantidade,idp;

	scanf(" %d:%d",&idp,&quantidade);
	if (idp>=indice_produtos){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
	}
	else if (produtos[idp].qtd-quantidade<0){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade,idp);
	}
	else{
		/* Retira a quantidade ao produto */
		produtos[idp].qtd-=quantidade;
	}
}


/* AUXILIAR - Esta funcao compara a descricao de cada produto */
int compare(Produto v_produtos_1, Produto v_produtos_2, int flag){

	/* Compara por ordem alfabetica 'L' */
	if (flag==1){
		
		return strcmp(v_produtos_1.desc,v_produtos_2.desc)<0;
	}
	/* Compara pelo preco ou pelo idp 'l' */
	else{
		
		if (v_produtos_1.preco==v_produtos_2.preco){
			
			return v_produtos_1.idp<v_produtos_2.idp;
		}
	
		return v_produtos_1.preco<v_produtos_2.preco;
	}

	return 0;
}


/* AUXILIAR - Esta funcao toma o ultimo elemento como pivot, 
			  poe esse pivot na posicao correta no vetor ordenado,
			  e adiciona todos os menor que o pivot a esquerda do pivot
			  e os maiores a sua direita. */
int partition(Produto v_produtos[], int l, int r, int flag){ 
    
    /* Compara por ordem alfabetica 'L' */
    
    int i=l-1;
    int j=r;
    Produto v=v_produtos[r];
		
	if (flag==0){
  		while (i<j){

   			while (compare(v_produtos[++i], v,0));
   		
   			while (compare(v,v_produtos[--j],0))
   				if (j==l)
   					break;
   		
   			if (i<j)
   				exch(v_produtos[i], v_produtos[j]);
   		
   		}
   		exch(v_produtos[i], v_produtos[r]);
   		return i;
	}
	/* Compara pelo preco ou pelo idp 'l' */
	else{
  		while (i<j){

   			while (compare(v_produtos[++i], v,1));
   		
   			while (compare(v,v_produtos[--j],1))
   				if (j==l)
   					break;
   		
   			if (i<j)
   				exch(v_produtos[i], v_produtos[j]);
   		
   		}
   		exch(v_produtos[i], v_produtos[r]);
   		return i;
	}
} 

  
/* A funcao principal que executa o QuickSort
 	produtos[] --> vetor a ser ordenado, 
  	low  --> indice inicial, 
  	high  --> indice final */
void quickSort(Produto v_produtos[], int l, int r, int flag){ 
    
    int i;

    /* Compara por ordem alfabetica 'L' */
    if (flag==0){

    	if (r<=l)
    		return;

    	i=partition(v_produtos,l,r,0);
    	quickSort(v_produtos,l,i-1,0);
    	quickSort(v_produtos,i+1,r,0);
    }
    /* Compara pelo preco 'l' */
    else{
    	
    	if (r<=l)
    		return;

    	i=partition(v_produtos,l,r,1);
   	 	quickSort(v_produtos,l,i-1,1);
   		quickSort(v_produtos,i+1,r,1);
    }
}  


/* Cria lista com todos os produtos atualizados */
void lista_produtos(){

	int i;
	Produto prod_aux[MAX_IDP+1];

	/* Guarda o vetor de PRODUTOS num vetor auxiliar */
	for (i=0;i<indice_produtos;i++){
		prod_aux[i]=produtos[i];
	}
	
	printf("Produtos\n");
	
	/* Ordena o vetor dos produtos auxiliar */
	quickSort(prod_aux,0,indice_produtos-1,0);
	
	/* Corre todos os produtos */
	for (i=0;i<indice_produtos;i++){

		printf("* %s %d %d\n",prod_aux[i].desc,prod_aux[i].preco,prod_aux[i].qtd);
	}
}


/* Remove o produto da encomenda */
void remove_prod_enc(){

	int ide,idp,i;

	scanf(" %d:%d",&ide,&idp);
	if (ide>=indice_encomendas){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
	}
	else if (idp>=indice_produtos){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
		return;
	}
	else{
		/* Corre todos os produtos da encomenda dada */
		for (i=0;i<encomendas[ide].n_prod;i++){
			/* Se o produto dado estiver contido nessa encomenda */
			if (encomendas[ide].prod_enc[i].idp==idp){
				
				/* Repoe a quantidade de produto da encomenda ao vetor de todos os produtos */
        		produtos[idp].qtd+=encomendas[ide].prod_enc[i].qtd;

				/* Elimina toda a quantidade do produto na encomenda */
        		encomendas[ide].prod_enc[i].qtd=0;		
			}
		}
    }
}


/* Calcula o custo da encomenda */
void calc_custo(){

	int i, ide, custo_total=0;

	scanf(" %d",&ide);
	
	if (ide>=indice_encomendas){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
	}
	else{

		/* Corre todos os produtos da encomenda dada */
		for (i=0;i<encomendas[ide].n_prod;i++){

			/* Incrementa o custo de cada produto na encomenda (preco x qauntidade) */
			custo_total+=encomendas[ide].prod_enc[i].preco*encomendas[ide].prod_enc[i].qtd;
		}
		
		printf("Custo da encomenda %d %d.\n", ide,custo_total);
	}
}
 
 

/* Cria lista de todos os produtos atualizados da encomenda */
void lista_prod_enc(){

	int e,i,ide;
	Produto prod_aux_enc[MAX_IDP];

	scanf(" %d",&ide);

	
	if (ide>=indice_encomendas){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
	}
	
	else{
		
		/* Copia os produtos da encomenda dada para um vetor auxiliar */
		for (e=0;e<encomendas[ide].n_prod;e++){
			
			prod_aux_enc[e]=encomendas[ide].prod_enc[e];
		}
	
		/* Ordena a encomenda auxiliar */
		quickSort(prod_aux_enc,0,encomendas[ide].n_prod-1,1);

        printf("Encomenda %d\n", ide);
        
        /* Corre todos os produtos da encomenda dada */
        for (i=0;i<encomendas[ide].n_prod;i++){
        	/* Se tiverem a quantidade a 0 significa que foram removidos, logo nao imprime */
        	if (prod_aux_enc[i].qtd>0)
        	
        		printf("* %s %d %d\n",prod_aux_enc[i].desc,prod_aux_enc[i].preco,prod_aux_enc[i].qtd);
        }
    }
}


/* Altera o preco do produto */
void altera_preco(){

	int i,e,idp,preco;

	scanf(" %d:%d",&idp,&preco);
	if (idp>=indice_produtos)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
	
	/* Altera o preco do produto dado no vetor dos produtos */
	produtos[idp].preco=preco;
	
	/* Corre cada encomenda */
	for (i=0;i<indice_encomendas;i++){
		/* Corre todos os produtos de cada encomenda */
		for (e=0;e<encomendas[i].n_prod;e++){
			/* Se o produto dado estiver contido numa encomenda */
			if (encomendas[i].prod_enc[e].idp==idp)
				/* Altera o preco do produto nessa encomenda */
				encomendas[i].prod_enc[e].preco=preco;
		}
	}
}


/* Lista a descri??o e a quantidade de um produto numa encomenda */
void desc_qtd(){

	int ide,idp,i,FLAG=0;

	scanf(" %d:%d",&ide,&idp);

	if (ide>=indice_encomendas)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);

	else if (idp>=indice_produtos)
		printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
	
	else{
		/* Corre todos os produtos da encomenda */
		for (i=0;i<encomendas[ide].n_prod;i++){
			/* Se o produto estiver na encomenda */
			if (encomendas[ide].prod_enc[i].idp==idp){
				/* Ele esta la */
				FLAG =1;
				/* Printa a descricao e quantidade */
				printf("%s %d.\n",encomendas[ide].prod_enc[i].desc,encomendas[ide].prod_enc[i].qtd);
			}	
		}
		/* Se ele nao estiver na encomenda */
		if (FLAG==0){
			/* Printa a descricao do produto e a quantidade a '0' */ 
			printf("%s %d.\n",produtos[idp].desc,0);
		}
	} 	
}


void max_id_founder(){

	int idp;
	int i,j;
	int contador_ide=0;
	int contador_qtd=0;

	scanf(" %d",&idp);

	if (idp >=indice_produtos){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	}
	else {	
		
		/* Corre todas as encomendas */
		for (i=0;i<indice_encomendas;i++){
			/* Corre todos os produtos de cada encomenda */
			for (j=0;j<encomendas[i].n_prod;j++){
				/* Se ele estiver numa encomenda */
				if (encomendas[i].prod_enc[j].idp==idp){
					/* Se a quantidade for maior que a anterior */
					if (encomendas[i].prod_enc[j].qtd > contador_qtd){

						contador_qtd=encomendas[i].prod_enc[j].qtd;
						contador_ide=i;
					}
				}
			}
		}
		/* Se nao houver quantidades negativas */
		if (contador_qtd>0)
			printf("Maximo produto %d %d %d.\n",idp,contador_ide,contador_qtd);
	}
}



int main(){

	int c;

	while ((c=getchar())!='x'){

		switch(c){

			default:
				break;

			case 'a':
				cria_produto();
				break;
			
			case 'q':
				edita_quantidade();
				break;
			
			case 'N':
				cria_encomenda();
				break;
			
			case 'A':
				add_produto();
				break;

			case 'l':
				lista_produtos();
				break;

			case 'r':
				remove_stock();
				break;

			case 'R':
				remove_prod_enc();
				break;

			case 'C':
				calc_custo();
				break;

			case 'p':
				altera_preco();
				break;

			case 'L':
				lista_prod_enc();
				break;

			case 'E':
				desc_qtd();
				break;

			case 'm':
				max_id_founder();
				break;
		}
	}

	return 0;
}