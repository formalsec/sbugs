#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#define MAXPRODUTOS 10000
#define MAXDESCRICAO 64
#define MAXPRODUTOSENCOMENDA 10000
#define MAXENCOMENDAS 500 
#define MAXPESOENCOMENDA 200

typedef struct{                        /* estrutura para o produto */
    char descricao[MAXDESCRICAO];
    int  preco; 
    int  peso;  
    int  quantidade; 
    int  guarda_ids;
}Produto;

typedef struct{                        /* estrutura para a encomenda */
    int ide_encomenda;
    Produto idp_encomenda[MAXPRODUTOSENCOMENDA];
    int qtd_produtos;
    int peso_encomenda;
    int preco_encomenda;
}Encomenda;

Produto sistema[MAXPRODUTOS];           /* variavel global once sao guardados todos os produtos */
int contproduto = 0;                    /* contador global de produtos */

Encomenda encomenda[MAXENCOMENDAS];     /* onde sao guardadas todas a encomendas */
int contencom = 0;                      /* contador global de encomendas */

void adiciona_produto();

void adiciona_stock();

void lista_produto();

void altera_preco();

void remove_stock();

void nova_encomenda();

void adiciona_produto_encomenda(); 

void calcula_preco_encomenda();

void lista_desc_qtd(); 

void remove_produto_encomenda();

void maior_quantidade_produto_encomenda();

void lista_produtos_encomenda();

int main()
{
    char comando;
    while (1)                              /* ciclo infinito */
    {
        comando = getchar();
        switch(comando)
        {
            case 'x' :
                return 0;
            case 'a' : 
                adiciona_produto();
                break;
            case 'q' : 
                adiciona_stock();
                break;     
            case 'l' :         
                lista_produto();
                break;
            case 'p' : 
                altera_preco();
                break;  
            case 'r' :
                remove_stock();
                break;
            case 'N' :
                nova_encomenda();
                break;    
            case 'A' :
                adiciona_produto_encomenda(); 
                break;
            case 'C' :
                calcula_preco_encomenda();
                break;
            case 'E' :
                lista_desc_qtd(); 
                break;
            case 'R' :
                remove_produto_encomenda(); 
                break;
            case 'm' :
                maior_quantidade_produto_encomenda(); 
                break;
            case 'L' :
                lista_produtos_encomenda(); 
                break;
        } 
        getchar(); /* limpar o espaco */
    }
    return 0;
}

void adiciona_produto(){
    /* 
    adiciona um produto com o nome
    o preco o peso e quantidade ao sistema
    */
    
    Produto novo;
    
    scanf(" %[^:]:%d:%d:%d", novo.descricao,        /* espaco compensa o espaco que dou  */                                    
        &novo.preco, &novo.peso, &novo.quantidade); /* le uma string que para nos dois pontos */
         
    printf("Novo produto %d.\n", contproduto);
    
    sistema[contproduto] = novo;                    /* guarda o novo produto dentro do sistema */
    
    contproduto++;
}

void adiciona_stock(){
    /* 
    Recebe um id e uma quantidade e faz a soma dessa 
    quantidade com a quantidade existente no produto
    Devolve nada
    */
    
    int stock, idp;
    
    scanf("%d:%d", &idp, &stock);
    
    if (idp >= contproduto){    /* contador esta uma unidade a frente dai ser maior ou igual */
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp); 
        return;                 /* para terminar a funcao */
    }
    
    sistema[idp].quantidade = sistema[idp].quantidade + stock;
}

void remove_stock(){
    /*
    Recebe um id e um valor remove esse valor da quantidade 
    Devolve nada
    */
    
    int remove, idp;
    
    scanf("%d:%d", &idp, &remove);
    
    if (idp>= contproduto){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp); 
        return;
    }
    if (remove > sistema[idp].quantidade){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", remove, idp); 
        return;
    }
    
    sistema[idp].quantidade = sistema[idp].quantidade - remove;
}


void merge(Produto vetor[], int inicio1, int j1, int inicio2, int j2){
	/* junta os dois sub vetores */
    
    Produto guarda_todos[MAXPRODUTOS];	/* array para fazer a juncao */
	int i,j,k = 0;
	i=inicio1;                          /* inicio do primeiro array */ 
	                            
    	j=inicio2;	                        /* incio do segundo array */
    
	while(i<=j1 && j<=j2){              /*elementos nos dois arrays */
		if(vetor[i].preco <= vetor[j].preco)
		    guarda_todos[k++] = vetor[i++];
		else
		    guarda_todos[k++] = vetor[j++];
	}

	while(i<=j1)	
	    guarda_todos[k++] = vetor[i++];
		
	while(j<=j2)	
	    guarda_todos[k++] = vetor[j++];
		
	for(i=inicio1,j=0;i<=j2;i++,j++)
		vetor[i] = guarda_todos[j];     /*copia todos os elementos para o array principal */
}

void mergesort(Produto vetor[],int i,int j){
    /* ordena recursivamente o vetor */
	int meio;
		
	if(i<j){
		meio=(i+j)/2;                   /*encontrar o elemento no centro */
		mergesort(vetor,i,meio);		
		mergesort(vetor,meio+1,j);	    /* ordenar com recursao */
		merge(vetor,i,meio,meio+1,j);	  
	}
}

void lista_produto(){
    /* 
    Recebe nada ordena todos os produtos segundo o preco 
    Devolve o nome o preco e a quantidade 
    de cada produto ordenado de forma crescente
    */   
    
    Produto array[MAXPRODUTOS];
    int i;

    for (i=0; i<contproduto; i++){                  /* preenche os arrays com os precos e od id s dos produtos */
            array[i].preco = sistema[i].preco;    
            
            array[i].guarda_ids = i;                
    }
    
    mergesort(array, 0, contproduto-1);
    
    printf("Produtos\n");
    for (i=0; i<contproduto; i++){
        printf("* %s %d %d\n", sistema[array[i].guarda_ids].descricao, sistema[array[i].guarda_ids].preco, 
        sistema[array[i].guarda_ids].quantidade);
    }
}

void nova_encomenda(){
    /* 
    Recebe nada 
    Devolve uma mensagem com o nr
    de uma nova encomenda 
    */
    
    printf("Nova encomenda %d.\n", contencom);
    
    contencom++;
}

void altera_preco(){
    /* 
    Recebe um identificador de um produtoe um preco e altera 
    o preco desse produto no sistema e tbm na encomenda
    Devolve nada
    */

    int idp, novoPreco, i;
    
    scanf("%d:%d", &idp, &novoPreco);

    if (idp >= contproduto){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp); 
        return;
    }
   
    for (i=0; i<contencom; i++){                 /* verifica se os produtos estao na encomenda */
        if (sistema[idp].preco == encomenda[i].idp_encomenda[idp].preco){
            encomenda[i].idp_encomenda[idp].preco = novoPreco;
        }
    }
    
    sistema[idp].preco = novoPreco;   
}

void adiciona_produto_encomenda(){
    /*
    Recebe um identifificador de um produto e de uma encomenda
    e uma dada quantidade que e retirada do sistema e de uma encomenda 
    Devolve nada 
    */
    int idp, ide, qtd; scanf("%d:%d:%d", &ide, &idp, &qtd);
    if (ide >= contencom){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide); return;
    }
    if (idp >= contproduto){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide); return;
    }   
    if (sistema[idp].quantidade == 0 || sistema[idp].quantidade < qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide); return;
    }
    if (encomenda[ide].peso_encomenda + sistema[idp].peso * qtd > 200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide); 
        return;
    }
    encomenda[ide].peso_encomenda += sistema[idp].peso * qtd; /* ve se o peso da encomenda esta dentro dos limites */
    
    sistema[idp].quantidade = sistema[idp].quantidade - qtd;  /*atualiza retira a quantidade que se adiciona a encomenda*/
    
    encomenda[ide].idp_encomenda[idp].quantidade += qtd;       /* se o idp for repetido soma a quantidade */     
    
    encomenda[ide].idp_encomenda[idp].preco = sistema[idp].preco; /* caso n se altere o preco */
     
    strcpy(encomenda[ide].idp_encomenda[idp].descricao, sistema[idp].descricao); 
    /*copia a descricao do produto para a encomenda */    
}

void calcula_preco_encomenda(){
    /*
    Recebe um identificador de uma encomenda
    Devolve o calculo do preco dessa
    */

    int ide, i, preco = 0;
    
    scanf("%d", &ide);

    if (ide >= contencom){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide); 
        return;
    }
    
    for (i=0; i<contproduto; i++){                          /* procura o preco na encomenda so depois faz o calculo */
        if (encomenda[ide].idp_encomenda[i].preco == sistema[i].preco){ 
            preco += (encomenda[ide].idp_encomenda[i].preco * encomenda[ide].idp_encomenda[i].quantidade);
        }
    }
    
    printf("Custo da encomenda %d %d.\n", ide, preco); 
}

void lista_desc_qtd(){
    /*
    Recebe um identificador de encomenda e produto 
    Devolve o nome e a quantidade desse produto na encomenda 
    */
    int ide,idp;
    
    scanf("%d:%d", &ide, &idp);

    if (ide >= contencom){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide); 
        return;
    }
    
    if (idp >= contproduto){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp); 
        return;
    }
    
    printf("%s %d.\n", sistema[idp].descricao, encomenda[ide].idp_encomenda[idp].quantidade); 
}

void remove_produto_encomenda(){
    /*
    Recebe um identificador de encomenda e produto remove o produto 
    da encomenda colocando a quantidade nesta a zero
    tira o preco e o peso inerente ao produto
    Devolve nada
    */
    
    int ide, idp; scanf("%d:%d", &ide, &idp);
    
    if (ide >= contencom){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide); 
        return;
    }
    
    if (idp >= contproduto){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);  
        return;
    }
    encomenda[ide].preco_encomenda  -= (sistema[idp].preco * encomenda[ide].idp_encomenda[idp].quantidade);
    /* retira o preco do produta a encomenda */
    encomenda[ide].peso_encomenda -= (sistema[idp].peso * encomenda[ide].idp_encomenda[idp].quantidade);
    /* retira o peso do produto da encomenda */
    sistema[idp].quantidade += encomenda[ide].idp_encomenda[idp].quantidade; 
    /*repoe a quantidade do produto no sistema */
    encomenda[ide].idp_encomenda[idp].quantidade = 0;
    /* a quantidade do produto fica a zero significa que n existe esse produto na encomenda */
}

void maior_quantidade_produto_encomenda(){
    /* 
    Recebe um identificador de produto 
    Devolve uma mensagem com o valor do idp do maior
    produto o valor dessa encomenda e a quantidade 
    */
    int idp, i, maior = 0, maior_indice = 0; 
    
    scanf("%d", &idp);
    
    if (idp >= contproduto){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp); 
        return;
    }

    if (contencom == 0 || contproduto == 0){                        /* caso nao existam produtos ou nao haja encomendas */ 
        return;     
    }
    
    for (i=0; i<contencom; i++){   
        if (sistema[idp].preco == encomenda[i].idp_encomenda[idp].preco  /*verifica se o produto esta na encomenda */
            && encomenda[i].idp_encomenda[idp].quantidade > maior){     
            maior = encomenda[i].idp_encomenda[idp].quantidade; maior_indice = i;
        }
    }
    
    if (maior == 0)                                                 /* caso o produto n esteja na encomenda */
        return;
    
    printf("Maximo produto %d %d %d.\n", idp, maior_indice, maior); 
}

void lista_produtos_encomenda(){
    /* 
    Recebe um ide 
    Devolve todos os produtos existentes na encomenda ordenados 
    por ordem alfabetica com os respetivos nomes preco e quantidade
    */
    int ide, i, j, troca_idp, cont = 0, array_idp[MAXPRODUTOSENCOMENDA];
    char array_descricao[MAXPRODUTOSENCOMENDA][MAXDESCRICAO], troca[MAXDESCRICAO]; scanf("%d", &ide);
    
    if (ide >= contencom){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide); return;
    }
    
    for (i=0; i<contproduto; i++){                                  /*prenche o array com os idp s e descricoes */
        if (encomenda[ide].idp_encomenda[i].preco == sistema[i].preco 
            && encomenda[ide].idp_encomenda[i].quantidade != 0){    /*verifica se o produto esta na encomenda */
            strcpy(array_descricao[cont], encomenda[ide].idp_encomenda[i].descricao); array_idp[cont] = i; cont++; 
        }}
    
    for (j = 0; j < cont-1; j++){                   /* bubble sort algoritmo cont para nao ordenar todos os produtos */
        for (i = j+1; i < cont; i++){
            if (strcmp(array_descricao[j], array_descricao[i]) > 0){ 
                strcpy(troca, array_descricao[j]); 
                strcpy(array_descricao[j], array_descricao[i]); 
                strcpy(array_descricao[i], troca); 
                troca_idp  = array_idp[j]; array_idp[j] = array_idp[i]; array_idp[i] = troca_idp;   
            }}}

    printf("Encomenda %d\n", ide);
    for (i=0; i < cont ; i++){
        printf("* %s %d %d\n", encomenda[ide].idp_encomenda[array_idp[i]].descricao,
        encomenda[ide].idp_encomenda[array_idp[i]].preco, encomenda[ide].idp_encomenda[array_idp[i]].quantidade);                           
    }
}



