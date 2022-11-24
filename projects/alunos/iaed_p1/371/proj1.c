#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define DESCRICAO 64
#define MAX 10000
#define MAX_ENCOMENDA 500
typedef struct produto{
	int id;
	char descricao[DESCRICAO];
	int preco;
	int peso;
	int stock;
} Produto;
Produto produtos_main[MAX];    	/*Lista global que guarda os produtos*/


typedef struct encomenda{
	Produto tab[MAX];
	int preco_total;
	int peso_total;
	int prods;
	int maior_id;
}Encomenda;
Encomenda encomenda_main[MAX_ENCOMENDA];   	/*Lista Global que guarda as encomendas*/
Encomenda aux_L[MAX_ENCOMENDA];	
/*Lista Global que guarda descricoes usadas na ordenacao da funcao ordenaProd_encomenda(L)*/			


/* Funcao que tem como objetivo adicionar um novo
produto ao sistema. O comando para a executar e 'a'*/
void addProd(Produto sistema[MAX], int idp){
	int c,e = 0;
	char desc_copy[MAX];
		getchar();	/*ira apagar o espaco que fica entre "a" "descricao" */
		while ((c = getchar()) != ':'){
			desc_copy[e++] = c;
		}
		desc_copy[e] = '\0';
		strcpy(sistema[idp].descricao, desc_copy);									
		/*apos obter a descricao passa-a para o sistema
		 para que fique guardada na estrutura do produto*/
		scanf("%d:%d:%d", &sistema[idp].preco, &sistema[idp].peso, &sistema[idp].stock);
		printf("Novo produto %d.\n", idp);
}

/* Funcao que tem como objetivo adicionar stock a um 
produto do sistema. O comando para a executar e 'q'*/
void addStock(Produto sistema[MAX], int i){
	int idp, qtd;
	scanf("%d:%d", &idp, &qtd);
	if (idp > i - 1){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	}
	else{
		sistema[idp].stock += qtd; 
	}

}

/* Funcao que tem como objetivo criar uma nova encomenda.
O comando para a executar e 'N'*/
void criaEncomenda(int ide){
	printf("Nova encomenda %d.\n", ide );
}

/* Funcao que tem como objetivo adicionar um produto a uma encomenda.
O comando para a executar e 'A'*/
void addProd_Encomenda(Produto sistema[MAX], Encomenda encomendas[MAX_ENCOMENDA], int i, int e,Encomenda aux_L[MAX_ENCOMENDA]){
	int idp,qtd,ide,j, flag = 2;
	scanf("%d:%d:%d", &ide, &idp, &qtd);

		for (j = 0; j < encomendas[ide].maior_id; j++){					
		/*ciclo criado para verificar se o produto ja se encontra na encomenda*/							
					if(strcmp(encomendas[ide].tab[j].descricao,sistema[idp].descricao) == 0){         
						flag = 0;	
						/*caso ja esteja a flag ficara a 0*/																
					}	
		}			
	

	strcpy(encomendas[ide].tab[idp].descricao, sistema[idp].descricao);
	encomendas[ide].tab[idp].peso = sistema[idp].peso;
	encomendas[ide].tab[idp].preco = sistema[idp].preco;
	
	if (ide > e - 1){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		flag = 0;
	}
	else{ if (idp > i - 1){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp, ide);
		flag = 0;
	}
	else{ if (sistema[idp].stock < qtd){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp, ide);
		flag = 0;
	}
	else{ if (encomendas[ide].peso_total + (encomendas[ide].tab[idp].peso * qtd) > 200){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp, ide);
		flag = 0;
		}
		else{
			/*se nao houver erros entao adicionara o produto a encomenda*/
			encomendas[ide].peso_total += encomendas[ide].tab[idp].peso * qtd; 

			encomendas[ide].preco_total += sistema[idp].preco * qtd;

			encomendas[ide].tab[idp].stock += qtd;
			sistema[idp].stock -= qtd;

			}

			if (flag != 0){	
			/*se a flag nao for 0 significa que o produto nao
			 estava na encomenda portanto adiciona-o*/													
				encomendas[ide].prods++;
				strcpy(aux_L[ide].tab[idp].descricao,sistema[idp].descricao);
				/*servira para ordenar as descricoes posteriormente*/  
			}
			if(encomendas[ide].maior_id - 1 < idp ){
				/*para saber qual o maior idp numa encomenda*/
				encomendas[ide].maior_id = idp + 1;
			}
	
	}}}
}

/* Funcao que tem como objetivo remover stock a um produto existente.
O comando para a executar e 'r'*/
void removestk(Produto sistema[MAX], int i){
	int idp, qtd;
	scanf("%d:%d", &idp, &qtd);
	if(idp > i - 1){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp );
	}
	else if(qtd > sistema[idp].stock){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
	}
	else{
		sistema[idp].stock -= qtd;
	}

}

/* Funcao que tem como objetivo remover um prod. de uma encomenda.
O comando para a executar e 'R'*/
void removeProd_Encomenda(Produto sistema[MAX], Encomenda encomendas[MAX_ENCOMENDA], int i, int e){
	int ide,idp,qtd;
	scanf("%d:%d", &ide, &idp);
	if (ide > e - 1){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
	else{ if (idp > i - 1){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
		else{
			if(encomendas[ide].tab[idp].stock != 0){
				encomendas[ide].prods -= 1;
			}
			qtd = encomendas[ide].tab[idp].stock; 
			encomendas[ide].tab[idp].stock = 0;
			encomendas[ide].peso_total -= encomendas[ide].tab[idp].peso * qtd;
			encomendas[ide].tab[idp].peso = 0;
			encomendas[ide].preco_total -= sistema[idp].preco * qtd;
			sistema[idp].stock += qtd;



		}


	}



}


/*Funcao que calcula o custo de uma encomenda.
O comando para a executar e 'C'*/
void CalculaCusto(Encomenda encomendas[MAX_ENCOMENDA], int e){
	int ide;
	scanf("%d", &ide);
	if (ide > e - 1){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	}
	else{
		printf("Custo da encomenda %d %d.\n", ide, encomendas[ide].preco_total);
	}

}



/*Funcao que altera o preco de um produto existente no sistema.
O comando para a executar e 'p'*/
void alteraPreco(Produto sistema[MAX],Encomenda encomendas[MAX_ENCOMENDA], int i,int e){
	int idp, novo_preco,j,ide;
	scanf("%d:%d", &idp, &novo_preco);
	if (idp > i - 1){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	}
	else{
		for(ide = 0; ide < e; ide++){
			for (j = 0; j < encomendas[ide].maior_id; j++){				
				/*ciclo que ira percorrer todas as encomendas
				e procurar as descricoes dos produtos*/							
				if(strcmp(encomendas[ide].tab[j].descricao,sistema[idp].descricao) == 0){
				/*caso as descricoes sejam iguais
				significa que temos o produto certo*/	
				encomendas[ide].preco_total -= (sistema[idp].preco * encomendas[ide].tab[j].stock); 
				sistema[idp].preco = novo_preco;
				encomendas[ide].preco_total += (sistema[idp].preco * encomendas[ide].tab[j].stock); 
				}

			}

		}
		sistema[idp].preco = novo_preco;	/*caso o produto nao esteja numa encomenda o
											seu preco e necessario ser atualizado na mesma*/
		
	}

}



/*Funcao que retorna a descri??o e
a quantidade de um produto numa dada encomenda.
O comando para a executar e 'E'*/
void descreveProd(Produto sistema[MAX],Encomenda encomendas[MAX_ENCOMENDA], int i, int e){
	int ide,idp;
	scanf("%d:%d", &ide, &idp);
	if (ide > e - 1){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	else{ if (idp > i -1){
			printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
		}
		else{if(encomendas[ide].tab[idp].stock != 0){
			printf("%s %d.\n",encomendas[ide].tab[idp].descricao, encomendas[ide].tab[idp].stock);
		}
			if(encomendas[ide].tab[idp].stock == 0){
				printf("%s %d.\n",sistema[idp].descricao, encomendas[ide].tab[idp].stock);

			}

		}
	}
}



/*retorna o identificador
da encomenda em que um dado produto ocorre mais vezes.
O comando para a executar e 'm'*/
void prodRepetido_encomenda(Encomenda encomendas[MAX_ENCOMENDA],int i){
	int idp,ide,maior = 0,enc = 0;
	scanf("%d", &idp);
	if (idp > i - 1 ){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp );
	}
	else{
		for (ide = 0; ide <= i ; ide++){
			if (encomendas[ide].tab[idp].stock == maior){ 
			/*caso a qtd na encomenda seja igual a maior
			 quantidade entao atualiza o menor ide*/  
				if (ide < enc){
					enc = ide;
				}

			}
			if (encomendas[ide].tab[idp].stock > maior){
				/*caso a qtd seja maior que a maior quantidade
				 atualiza a maior qtd e o ide correspondente*/
				maior = encomendas[ide].tab[idp].stock;     
				enc = ide;

			}

		}
	}
	if (maior > 0){
		printf("Maximo produto %d %d %d.\n",idp, enc, maior );
	}
	


}



/*Funcao auxiliar a funcao ordena_arr que consiste em ordenar
o arr do tipo Produto de acordo com o preco*/
void merge(Produto arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    Produto L[MAX], R[MAX]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
 
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i].preco <= R[j].preco) /*aqui estabelece-se a condicao de ordenacao (preco)*/
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
} 
  
/*Funcao cuja finalidade e ordenar o arr fornecido
pelo seu preco e utiliza a funcao merge como sua auxiliar*/
void ordena_arr(Produto arr[], int l, int r) 
{ 
    if (l < r) 
    { 

        int m = l+(r-l)/2; 
  
        ordena_arr(arr, l, m); 
        ordena_arr(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 
/*lista todos os produtos
existentes no sistema por ordem crescente de pre?o.
O comando para a executar e 'l'*/
void precoProd(Produto sistema[MAX], int r){
	int i;
	Produto arr_ordenado[MAX];
	if (r == 0){					/*caso especial em que nao existem produtos criados*/
		printf("Produtos\n");
	}
	else{
		for(i = 0; i < r; i++){	
		/*passar para um vetor todos os precos e idp
		 correspondentes para que este seja ordenado*/							
			arr_ordenado[i].preco = sistema[i].preco;
			arr_ordenado[i].id = i;
		}
	

		ordena_arr(arr_ordenado, 0, r - 1); 
		/*chama a funcao de ordenacao onde daqui
		 saira o vetor ordenado pelos precos*/               
		printf("Produtos\n");
		for(i = 0; i < r ; i++){
				printf("* %s %d %d\n",sistema[arr_ordenado[i].id].descricao, arr_ordenado[i].preco, sistema[arr_ordenado[i].id].stock );

		}

	}


}


/*lista todos os produtos de uma encomenda por ordem
 alfab?tica da descri??o.
 O comando para a executar e 'L'*/
void ordenaProd_Encomenda(Encomenda encomendas[MAX_ENCOMENDA],Encomenda aux_L[MAX_ENCOMENDA], int r, int idp, Produto sistema[MAX]){
	int ide,j,i;
	char ord[MAX_ENCOMENDA];
	scanf("%d", &ide);

	if (ide > r - 1){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide );
	}
	else if (encomendas[ide].prods == 0){
		printf("Encomenda %d\n", ide);
	}
	else{
		if(encomendas[ide].prods == 1){
			printf("Encomenda %d\n", ide);
			for(j = 0; j < idp; j++){
				if(strcmp(aux_L[ide].tab[j].descricao,sistema[j].descricao) == 0 &&(encomendas[ide].tab[j].stock > 0))
				printf("* %s %d %d\n",encomendas[ide].tab[j].descricao, encomendas[ide].tab[j].preco, encomendas[ide].tab[j].stock);
			}
			
		}
		else{

	   		for(i = 0;i <= encomendas[ide].prods; i++){
	      		for(j = i + 1;j <= encomendas[ide].prods; j++){	
	      		/*ciclo que anda dentro dos produtos na encomenda pretendida*/							
	         		if(strcmp(aux_L[ide].tab[i].descricao,aux_L[ide].tab[j].descricao)>0){ 
	            		strcpy(ord,aux_L[ide].tab[i].descricao);
	            		strcpy(aux_L[ide].tab[i].descricao,aux_L[ide].tab[j].descricao);
	            		strcpy(aux_L[ide].tab[j].descricao,ord);
	            		/*daqui sai o vetor aux_L com todas as descricoes ordenadas por ordem alfabetica*/                           
	         		}
	      		}
	      	}
	      	printf("Encomenda %d\n", ide);
	   		for(i = 0; i <= encomendas[ide].maior_id; i++){
	   			for(j = 0; j < idp; j++){
	   				if (strcmp(aux_L[ide].tab[i].descricao,sistema[j].descricao) == 0 && (encomendas[ide].tab[i].stock > 0)){ 
	   					/*como se esta a utilizar um vetor com apenas descricoes entao
	   					e necessario encontrar o preco e stock correspondentes*/  
	   						printf("* %s %d %d\n",aux_L[ide].tab[i].descricao, sistema[j].preco, encomendas[ide].tab[j].stock);
	   				}
	   				
	   			}
	      		
	   		}

		}

   
		}



}





int main(){
	char comando; /*variavel que guarda o comando a ser executado*/
	int contador_indice = 0,contador_indice2 = 0;  /*variaveis correspondentes ao idp e ide, respetivamente*/
	/*Ate ser primido o comando x o programa estara sempre
	em funcionamento e a espera que um dos comandos seja primido*/
	while (comando != 'x'){
		scanf("%c", &comando);
		if (comando == 'a'){
			addProd(produtos_main, contador_indice);
			contador_indice++;
		}
		if (comando == 'q'){
			addStock(produtos_main, contador_indice);
		}
		if (comando == 'N'){
			criaEncomenda(contador_indice2);
			contador_indice2++;
		}
		if (comando == 'A'){
			addProd_Encomenda(produtos_main,encomenda_main,contador_indice,contador_indice2, aux_L);
		}
		if (comando == 'r'){
			removestk(produtos_main, contador_indice);
		}
		if (comando == 'R'){
			removeProd_Encomenda(produtos_main,encomenda_main,contador_indice,contador_indice2);
		}
		if (comando == 'C'){
			CalculaCusto(encomenda_main,contador_indice2);
		}
		if (comando == 'p'){
			alteraPreco(produtos_main,encomenda_main,contador_indice,contador_indice2);
		}
		if (comando == 'E'){
			descreveProd(produtos_main,encomenda_main,contador_indice,contador_indice2);
		}
		if (comando == 'm'){
			prodRepetido_encomenda(encomenda_main, contador_indice);
		}
		if (comando == 'l'){
			precoProd(produtos_main, contador_indice);
		}
		
		if (comando == 'L'){
			ordenaProd_Encomenda(encomenda_main, aux_L, contador_indice2, contador_indice, produtos_main);
		}
	}
	return 0;

}





