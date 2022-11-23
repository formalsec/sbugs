#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Definicao de constantes*/
#define MAX_ID 10000
#define MAX_DESCRICAO 64
#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define MAX_PESO_ENCOMENDA 200

/*Constantes utilizadas na matriz bidimensional da estrutura Encomenda*/
#define ID 0
#define QTD 1


/*Estrutura Produto que contem o id(inteiro), a descricao(string), o preco(inteiro),
o peso(inteiro) e a quantidade(inteiro) de um produto*/
typedef struct produto{
    int id;
    char descricao[MAX_DESCRICAO];
    int preco;
    int peso;
    int quantidade;
}Produto;


/*Estrutura Encomenda que contem uma matriz bidimensional de inteiros cujo indice 0 
corresponde ao ID e 1 a quantidade do produto na encomenda,o peso total da encomenda(inteiro)
 e o numero de produtos na encomenda(inteiro)*/
typedef struct encomenda{
    int produtosEncomenda[MAX_PESO_ENCOMENDA][2];
    int pesoEncomenda;
    int nroProds;
}Encomenda;

/*Prototipos de funcoes*/
void novoProduto();
void adicionaStock();
void novaEncomenda();
void addProdEncomenda();
void removeProdStock();
void removeProdEncomenda();
void custoEncomenda();
void alteraPreco();
void mostraProdEncomenda();
void encomendaMaisProduto();
void listarPreco();
void listarProdsEncomenda();
void mergeSort(int array[], int esq, int dir);
void mergeAux(int array[],int esq, int med, int right);
void mergeStrings(int array[], int esq, int dir);
void mergeStrAux(int array[], int esq, int med, int dir);
int procuraIndexEncomenda(int ide, int idp);

/*Funcao utilizada para debug*/
void mostraProds();


/*Estrutura de dados onde irao ser introduzidos todos os produtos que serao adicionados ao sistema*/
Produto stockProdutos[MAX_PRODUTOS];

/*Estrutura de dados onde todas as encomendas criadas estao localizadas*/
Encomenda encomendas[MAX_ENCOMENDAS];


/*Variaveis que indicam qual o identificador maximo tanto dos produtos como das encomendas*/
int idProdutos = 0;
int idEncomendas = 0;

/*Vetores auxiliares que sao utilizados nas funcoes mergeSort e mergeAux, e mergeStrings e mergeStrAux respetivamente*/
int mergeArr[MAX_PRODUTOS];
int mergeArrStr[MAX_PESO_ENCOMENDA];

/*--------------------------------------------------MAIN-------------------------------------------------------------------*/
int main()
{
    char funcao;
    while((funcao = getchar()) != EOF){
        switch(funcao){   
            case('a'):
                novoProduto();
                break;
            case('q'):
                adicionaStock();
                break;
            case('N'):
                novaEncomenda();
                break;
            case('A'):
                addProdEncomenda();
                break;
            case('r'):
                removeProdStock();
                break;
            case('R'):
                removeProdEncomenda();
                break;
            case('C'):
                custoEncomenda();
                break;
            case('p'):
                alteraPreco();
                break;
            case('E'):
                mostraProdEncomenda();
                break;
            case('m'):
                encomendaMaisProduto();
                break;
            case('l'):
                listarPreco();
                break;
            case('L'):
                listarProdsEncomenda();
                break;
            case('x'):
                exit(0);
                break;
            case('k'):
                mostraProds();
                break;
            
        }
    }
    return 0;
}

/*-------------------------------------------------------------------------------------------------------*/

/*---------------------------------FUNCOES AUXILIARES----------------------------------------------------*/


/*Funcao que recebe uma string, que corresponde a descricao,e tres inteiros, 
que correspondem ao preco, peso e quantidade de um produto a ser adicionado ao sistema*/
void novoProduto()
{
    scanf(" %[^:]:%d:%d:%d", stockProdutos[idProdutos].descricao, &stockProdutos[idProdutos].preco, 
                            &stockProdutos[idProdutos].peso, &stockProdutos[idProdutos].quantidade);

    stockProdutos[idProdutos].id = idProdutos;
    
     

    /*Output do identificador do produto introduzido*/
    printf("Novo produto %d.\n", stockProdutos[idProdutos].id);


    /*Incremento do identificador de produtos maximo atual*/
    idProdutos++;
}


/*Funcao que recebe dois inteiros, o identificador de um produto e uma quantidade,
e adiciona a quantidade desejada do produto dado no stock*/
void adicionaStock()
{
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);

    
    /*Verifica se o produto existe na base de dados*/
    if(idp < idProdutos){
        stockProdutos[idp].quantidade += qtd;
    }
    /*Caso o produto seja inexistente, cria um erro*/
    else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
}

/*Funcao que cria adiciona uma nova encomenda ao sistema*/
void novaEncomenda()
{
    
    encomendas[idEncomendas].nroProds = 0;
    encomendas[idEncomendas].pesoEncomenda = 0;

    
    /*Output do identificador da encomenda criada*/
    printf("Nova encomenda %d.\n",idEncomendas);
    
    /*Incremento do identificador de encomendas*/
    idEncomendas++;
}

/*Funcao que recebe tres inteiros, o identificador de uma encomenda, o identificador
de um produto e a quantidade do produto a ser adicionada uma determinada encomenda*/
void addProdEncomenda()
{   
    int idp, ide, qtd;
    int len, i;
    scanf(" %d:%d:%d", &ide, &idp, &qtd);

    /*Condicao que verifica se o identificador de encomenda eh valido*/
    if(ide >= idEncomendas){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }

    /*Condicao que verifica se o identificador do produto a ser adicionado eh valido*/
    if(idp >= idProdutos){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }

    /*Condicao que verifica se o stock do produto a ser adicionado eh suficiente*/
    if(stockProdutos[idp].quantidade < qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }

    /*Condicao que verifica se o peso da encomenda nao ultrapassa o limite*/
    if(encomendas[ide].pesoEncomenda + stockProdutos[idp].peso * qtd > MAX_PESO_ENCOMENDA){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }
    
    len = encomendas[ide].nroProds;
    i = procuraIndexEncomenda(ide, idp);
    
    if( i >= 0 ){
        
        
        encomendas[ide].produtosEncomenda[i][QTD] = encomendas[ide].produtosEncomenda[i][QTD] + qtd;
        encomendas[ide].pesoEncomenda = encomendas[ide].pesoEncomenda + qtd * stockProdutos[idp].peso;
        stockProdutos[idp].quantidade = stockProdutos[idp].quantidade - qtd;

    

    }else{

        encomendas[ide].produtosEncomenda[len][ID] = idp;
        encomendas[ide].produtosEncomenda[len][QTD] = qtd;

        /*Adiciona o peso dos produtos ao peso total da encomenda, e remove a quantidade adicionada a encomenda do stock de produtos*/
        encomendas[ide].pesoEncomenda = encomendas[ide].pesoEncomenda + qtd * stockProdutos[idp].peso;
        stockProdutos[idp].quantidade = stockProdutos[idp].quantidade - qtd;

        /*Incrementa o numero de produtos que se encontram na encomenda*/
        encomendas[ide].nroProds++;
    }
   
}

/*Funcao que recebe dois inteiro que correspondem ao identificador de um produto
e a quantidade que se pretende remover do stock desse determinado produto*/
void removeProdStock()
{
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);

    /*Condicao que verifica se o produto existe*/
    if(idp >= idProdutos){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }
    
    /*Condicao que verifica se ao remover produtos do stock o stock nao fica negativo*/
    if(stockProdutos[idp].quantidade - qtd < 0){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
    }
    
    stockProdutos[idp].quantidade -= qtd;

    
}

/*Funcao que recebe dois inteiros, o identificador de uma encomenda e o identificador de um produto
e remove o produto indicado da encomenda referida*/
void removeProdEncomenda()
{
    int ide, idp, i;
    scanf(" %d:%d", &ide, &idp);

    /*Condicao que verifica se a encomenda existe*/
    if(ide >= idEncomendas){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    
    /*Condicao para verificar se o produto existe*/
    if(idp >= idProdutos){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp , ide);
        return;
    }

    i = procuraIndexEncomenda(ide, idp);
    
    if(i >= 0){    
        stockProdutos[idp].quantidade += encomendas[ide].produtosEncomenda[i][QTD];
        
        /*Remove o peso que os produtos pesavam no peso total da encomenda*/
        encomendas[ide].pesoEncomenda -= stockProdutos[idp].peso * encomendas[ide].produtosEncomenda[i][QTD];

        encomendas[ide].produtosEncomenda[i][QTD] = 0;
    }


}

/*Funcao que recebe um inteiro que corresponde ao identificador de uma encomenda e 
calcula e imprime o custo da encomenda desejada*/
void custoEncomenda()
{
    int ide, precoEncomenda = 0;
    int i, len, identificador;
    scanf(" %d", &ide);

    /*Condicao que verifica se a encomenda existe no sistema*/
    if(ide >= idEncomendas){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    
    len = encomendas[ide].nroProds;

    /*ciclo que ve quais os produtos que estao na encomenda e depois calcula o preco total de cada produto na encomenda*/
    for(i=0; i < len; i++){
        identificador = encomendas[ide].produtosEncomenda[i][ID];
        precoEncomenda = precoEncomenda + stockProdutos[identificador].preco * encomendas[ide].produtosEncomenda[i][QTD];
    }

    /*Output da funcao*/
    printf("Custo da encomenda %d %d.\n", ide, precoEncomenda);
    
}


/*Funcao que recebe um inteiro, que corresponde ao identificador de um produto e
 altera o preco de um produto que esteja em stock*/
void alteraPreco()
{
    int idp, novoPreco;
    scanf(" %d:%d", &idp, &novoPreco);

    /*Condicao que verifica se o produto existe*/
    if(idp >= idProdutos){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }

    stockProdutos[idp].preco = novoPreco;
    
}


/*Funcao que recebe dois inteiros, o identificador de uma encomenda e o identificador de
um produto e o programa imprime a descricao do porduto e a quantidade do mesmo na encomenda*/
void mostraProdEncomenda()
{
    int ide, idp;
    int indice, quantidade;
    scanf(" %d:%d", &ide, &idp);

    /*Condicao que verifica se a encomenda existe*/
    if(ide >= idEncomendas){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    /*Condicao que verifica se o produto existe*/
    if(idp >= idProdutos){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }
    indice = procuraIndexEncomenda(ide, idp);
    
    if(indice >= 0){
        quantidade = encomendas[ide].produtosEncomenda[indice][QTD];
    }
    /*Se o produto nao existir na encomenda, imprime se o produto com quantidade 0*/
    else{
        quantidade = 0;
    }

    printf("%s %d.\n", stockProdutos[idp].descricao, quantidade);
}



/*Funcao que recebe um inteiro que corresponde ao identificador de um produto,
e determina e devolve em que encomenda o produto ocorre mais vezes e a sua
quantidade nessa encomenda*/
void encomendaMaisProduto()
{
    int idp;
    int encomendaMaisRecorrente = -1, quantidadeMaxima = 0;
    int i,j;
    scanf(" %d", &idp);

    /*Condicao que verifica se o produto existe*/
    if(idp >= idProdutos){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }

    /*Ciclo que procura em qual encomenda o produto ocorre mais vezes*/
    for(i = 0; i < idEncomendas; i++){
        j = procuraIndexEncomenda(i, idp);
        /*Condicao que verifica se o produto existe na encomenda e se a sua quantidade nessa encomenda
        e superior a quantidade maxima verificada ate a esta iteracao do ciclo*/
        if(j >= 0 && encomendas[i].produtosEncomenda[j][QTD] > quantidadeMaxima){
            encomendaMaisRecorrente = i;
            quantidadeMaxima = encomendas[i].produtosEncomenda[j][QTD];
        }
    }

    /*Condicao que verifica se a encomenda e valida e se a quantidade e maior que 0*/
    if(encomendaMaisRecorrente >= 0 && quantidadeMaxima > 0){
        printf("Maximo produto %d %d %d.\n", idp, encomendaMaisRecorrente, quantidadeMaxima);
    }
}


/*Funcao que imprime uma lista dos produtos que estao em stock, que sao
imprimidos por ordem de preco ascendente*/
void listarPreco()
{
    int i, produtosOrdenados[MAX_PRODUTOS], len;
    
    len = idProdutos;

    /*Ciclo que introduz num vetor os identificadores dos produtos em stock*/
    for(i = 0; i < len; i++){
        produtosOrdenados[i] = i;
    }

    /*Chamada da funcao "mergeSort" que ordena por preco os produtos no vetor*/   
    mergeSort(produtosOrdenados, 0, len-1);

    printf("Produtos\n");
    for(i = 0; i< len; i++){
        printf("* %s %d %d\n", stockProdutos[produtosOrdenados[i]].descricao, stockProdutos[produtosOrdenados[i]].preco, 
                               stockProdutos[produtosOrdenados[i]].quantidade);
    }
}

/*Funcao que recebe um inteiro que corresponde ao identificador de uma 
encomenda, e imprime os produtos que estao na encomenda ordenada por
descricao em ordem alfabetica*/
void listarProdsEncomenda()
{
    int ide, prodsEncomenda[MAX_PESO_ENCOMENDA] = {0};
    int i, j = 0;
    int len, indice, quantidade;
    scanf(" %d", &ide);

    /*Condicao que verifica se a encomenda existe*/
    if(ide >= idEncomendas){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    len = encomendas[ide].nroProds -1;

    /*Ciclo que insere identificadores dos produtos existentes na encomenda num vetor*/
    for(i = 0; i < idProdutos ; i++){
        indice = procuraIndexEncomenda(ide, i);
        if(indice >= 0 && encomendas[ide].produtosEncomenda[indice][QTD] > 0){
            prodsEncomenda[j] = i;
            j++; 
        }
    }


    /*Chamada da funcao "mergeStrings" que ordena o vetor por ordem alfabetica de descricao*/
    mergeStrings(prodsEncomenda, 0, len);


    

    printf("Encomenda %d\n", ide);
    for(i = 0; i < len+1; i++){
        indice = procuraIndexEncomenda(ide, prodsEncomenda[i]);
        quantidade = encomendas[ide].produtosEncomenda[indice][QTD];
        if(indice >= 0 && quantidade > 0)
            printf("* %s %d %d\n", stockProdutos[prodsEncomenda[i]].descricao, stockProdutos[prodsEncomenda[i]].preco, quantidade);
        
    }

}

void mostraProds()
{
    int i,j, ide;
    scanf(" %d", &ide);

    for(i = 0; i< MAX_PESO_ENCOMENDA; i++){
            j = procuraIndexEncomenda(ide, i);
            if(j >= 0)
                printf("%s %d %d\n", stockProdutos[i].descricao, stockProdutos[i].preco, encomendas[ide].produtosEncomenda[j][QTD]);
    }
}



/*Funcao auxiliar que recebe dois inteiros correspondentes ao identificador de
  uma encomenda e ao identificador de um produto e retorna a posicao de um produto
  na matriz bidimensional da encomenda desejada, ou retorna -1 caso o produto
  nao seja encontrado*/
int procuraIndexEncomenda(int ide, int idp)
{
    int i, len = encomendas[ide].nroProds;

    for(i = 0; i < len; i++){
        if(encomendas[ide].produtosEncomenda[i][ID] == idp){
            return i;
        }
    }

    
    return -1;
}



void mergeAux(int array[],int esq, int med, int dir)
{
    int i, j, k;

    /*Ciclos que colocam os elementos do vetor a ordenar no vetor auxiliar*/
    for(i = med+1; i > esq; i--){
        mergeArr[i-1] = array[i-1];
    }
    for(j = med ; j < dir; j++){
        mergeArr[dir+med-j] = array[j+1];
    }

    /*ciclo de ordenacao que verifica so o preco do elemento do vetor da esquerda e menor que 
    o do elemento do vetor da direita ou se os precos forem iguais, qual dos elementos 
    tem o identificador de produto menor*/
    for(k = esq; k <= dir; k++){
        if(stockProdutos[mergeArr[j]].preco < stockProdutos[mergeArr[i]].preco || 
          (stockProdutos[mergeArr[j]].preco == stockProdutos[mergeArr[i]].preco && mergeArr[j] < mergeArr[i])){
            array[k] = mergeArr[j];
            j--;
        }else{
            array[k] = mergeArr[i];
            i++;
        }
    }
}

/*Merge Sort aplicado a numeros inteiros*/
void mergeSort(int array[], int esq, int dir)
{
    int med = (esq+dir)/2;

    if( dir <= esq){
        return;
    }

    mergeSort(array, esq, med);
    mergeSort(array, med + 1, dir);
    mergeAux(array, esq, med, dir);

}



void mergeStrAux(int array[], int esq, int med, int dir)
{
    int i, j, k;

    /*Ciclos que colocam os elementos do vetor a ordenar no vetor auxiliar*/
    for(i = med+1; i > esq; i--){
        mergeArrStr[i-1] = array[i-1];
    }
    for(j = med; j < dir; j++){
        mergeArrStr[dir+med-j] = array[j+1];
    }

    /*Ciclo de ordenacao, que ordena em ordem alfabetica*/
    for(k = esq; k <= dir; k++){
        if(strcmp(stockProdutos[mergeArrStr[j]].descricao,stockProdutos[mergeArrStr[i]].descricao) < 0 || 
           mergeArr[i] > mergeArr[med]){
            array[k] = mergeArrStr[j];
            j--;
        }else{
            array[k] = mergeArrStr[i];
            i++;
        }
    }
}

/*Merge Sort aplicado a strings*/
void mergeStrings(int array[], int esq, int dir)
{
    int med = (dir+esq) / 2;

    if(dir <= esq){
        return;
    }

    
    mergeStrings(array, esq, med);
    mergeStrings(array, med + 1, dir);
    mergeStrAux(array, esq, med, dir);
}
