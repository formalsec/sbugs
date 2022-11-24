#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PRODUCT_ID 10000
#define MAX_SIZE_DESCRIPTION 64
#define MAX_ORDER_ID 500 
#define MAX_WEIGHT 200

/*
| __a__ | adiciona um novo produto ao sistema |
| __q__ | adiciona stock a um produto existente no sistema |
| __N__ | cria uma nova encomenda |
| __A__ | adiciona um produto a uma encomenda |
| __r__ | remove stock a um produto existente |
| __R__ | remove um produto de uma encomenda |
| __C__ | calcula o custo de uma encomenda |
| __p__ | altera o pre?o de um produto existente no sistema |
| __E__ | retorna a descri??o e a quantidade de um produto numa dada encomenda |
| __m__ | retorna o identificador da encomenda em que um dado produto ocorre mais vezes |
| __l__ | lista todos os produtos existentes no sistema por ordem crescente de pre?o |
| __L__ | lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o |
| __x__ | termina o programa |
*/
void adiciona_novo_produto();
void adiciona_stock_sistema();
void cria_nova_encomenda();
void adiciona_produto_encomenda();
void remove_stock_produto();
void retorna_identificador_encomenda();
void listar_produtos_existentes_sistema_crescente();
void remove_produto_encomenda();
void calcula_custo_encomenda();
void altera_preco_produto();
void lista_descricao_quantidade_produto_encomenda();
void lista_produtos_encomenda_alfabetica();
      

typedef struct Produto{
    int id;
    char descricao[MAX_SIZE_DESCRIPTION];
    int preco;
    int peso;
    int quantidade_stock; 

} Produto;


typedef struct Encomenda{
    int id;
    Produto produtos[MAX_PRODUCT_ID];
    int products_size;
    
}Encomenda;


Produto produtos[MAX_PRODUCT_ID];
static int numero_produtos=0;
Encomenda encomendas[MAX_ORDER_ID];
int numero_encomendas=0;
Produto produtos_ordenados[MAX_PRODUCT_ID];
Produto aux;
int i;
int j;
int ide;

void sort_produtos_preco(Produto input[], Produto output[],int size);
void sort_produtos_alfabetica(Produto input[], Produto output[],int size);



/**
a - adiciona um novo produto ao sistema
Formato de entrada: a descricao:preco:peso:qtd
Formato de sa?da: Novo produto <idp>. onde <idp> ? o identificador do produto criado.
*/
void adiciona_novo_produto(){
    static int id=0;
    int preco;
    int peso;
    int quantidade_stock;
    char descricao[MAX_SIZE_DESCRIPTION],c;
    c=getchar(); /*consumir primeiro espa?o do comando antes da descricao*/
    c=getchar();
    for(i=0;i<MAX_SIZE_DESCRIPTION-1 && c!=':';i++){
        descricao[i]=c;
        descricao[i+1]='\0';
        c=getchar();        
    }
    scanf("%d:%d:%d",&preco,&peso,&quantidade_stock);
    /*validar valor maximo do id do produto, para garantir que nao sao inseridos valores com id superior a 9999*/
    if(id>=MAX_PRODUCT_ID){
        return;
    }
    /*o mesmo produto n?o ? inserido 2 vezes*/
    for(i=0;i<numero_produtos;i++){
        Produto prod = produtos[i];
        if(strcmp(prod.descricao, descricao)==0){
            return;
        }
    }
    /*criar produto e adicionar ao stock*/
    produtos[numero_produtos].id = id;
    strcpy(produtos[numero_produtos].descricao,descricao);
    produtos[numero_produtos].preco = preco;
    produtos[numero_produtos].peso= peso;
    produtos[numero_produtos].quantidade_stock = quantidade_stock;    
    printf("Novo produto %d.\n", id); 
    id++;
    numero_produtos++; 
}


/**
q - adiciona stock a um produto existente no sistema
Formato de entrada: q idp:qtd
Formato de sa?da: NADA (excepto erro)
Erros:
Impossivel adicionar produto <idp> ao stock. Produto inexistente. 
no caso de n?o existir nenhum produto criado com esse identificador
*/
void adiciona_stock_sistema(){
    int id;
    int qt_stock;
    scanf("%d:%d", &id, &qt_stock);
    if(id>=numero_produtos){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
        return;    
    }
    produtos[id].quantidade_stock=produtos[id].quantidade_stock + qt_stock;
}



/**
N - cria uma nova encomenda
Formato de entrada: N
Formato de sa?da: Nova encomenda <ide>. onde <ide> ? o identificador da encomenda criada.
*/
void cria_nova_encomenda(){
    static int id=0;
    /*validar valor maximo do id do produto, para garantir que nao sao inseridos valores com id superior a 9999*/
    if(id>=MAX_ORDER_ID){
        return;
    }
    encomendas[numero_encomendas].id=id;
    printf("Nova encomenda %d.\n", id);
    numero_encomendas++;
    id++;
}



/**
A - adiciona um produto a uma encomenda. Se o produto j? existir na encomenda, 
adiciona a nova quantidade ? quantidade existente
Formato de entrada: A ide:idp:qtd
Formato de sa?da: NADA (excepto erro)
*/
void adiciona_produto_encomenda(){
    int idp;
    int qtd;
    int peso=0;
    int produto_existe=0;
    scanf("%d:%d:%d", &ide, &idp,&qtd);
    if(ide>=numero_encomendas){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp,ide);
        return;
    }
    if(idp>=numero_produtos){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp,ide);
        return;
    }
    if(produtos[idp].quantidade_stock<qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp,ide);
        return;
    }
    for(i=0;i<encomendas[ide].products_size;i++){
        peso = peso + encomendas[ide].produtos[i].peso*encomendas[ide].produtos[i].quantidade_stock;
    }
    if(peso+produtos[idp].peso*qtd>MAX_WEIGHT){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", idp,ide,MAX_WEIGHT);
        return;
    }
    for(i=0;i<encomendas[ide].products_size;i++){
        if(encomendas[ide].produtos[i].id==idp){
            encomendas[ide].produtos[i].quantidade_stock = qtd + encomendas[ide].produtos[i].quantidade_stock;
            produto_existe=1;
        }
    }
    if(produto_existe==0){
        encomendas[ide].produtos[encomendas[ide].products_size].id=produtos[idp].id;
        strcpy(encomendas[ide].produtos[encomendas[ide].products_size].descricao , produtos[idp].descricao);
        encomendas[ide].produtos[encomendas[ide].products_size].preco=produtos[idp].preco;
        encomendas[ide].produtos[encomendas[ide].products_size].peso=produtos[idp].peso;
        encomendas[ide].produtos[encomendas[ide].products_size].quantidade_stock=qtd;
        encomendas[ide].products_size++;
        /*
        printf("products_size %d\n", encomendas[ide].products_size);
        printf("peso anterior:%d\n", peso);
        printf("peso atual: %d", produtos[idp].peso);
        */
    }
    produtos[idp].quantidade_stock=produtos[idp].quantidade_stock-qtd;    
}



/**
r - remove stock a um produto existente
Formato de entrada: r idp:qtd
Formato de sa?da: NADA (excepto erro)
*/
void remove_stock_produto(){
    int idp;
    int qtd;
    scanf("%d:%d", &idp, &qtd);
    if(idp>=numero_produtos){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }
    if(produtos[idp].quantidade_stock<qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd,idp);
        return;
    }
    produtos[idp].quantidade_stock=produtos[idp].quantidade_stock-qtd;    
}



/**
m - lista o identificador da encomenda em que o produto dado ocorre mais vezes. 
Se houver 2 ou mais encomendas nessa situa??o,
dever? imprimir a encomenda de menor id.
Formato de entrada: m idp
*/
void retorna_identificador_encomenda(){
    int idp;
    int qtd;
    int encontrei=0;
    scanf("%d", &idp);
    if(idp>=numero_produtos){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }
    for(i=0;i<numero_encomendas;i++){
        for(j=0;j<encomendas[i].products_size;j++){
            if(encomendas[i].produtos[j].id==idp){
                if(encontrei==0){
                    qtd=encomendas[i].produtos[j].quantidade_stock;
                    ide=encomendas[i].id;
                }
                else{
                    if(encomendas[i].produtos[j].quantidade_stock>qtd){
                        qtd=encomendas[i].produtos[j].quantidade_stock;
                        ide=encomendas[i].id;
                    }
                }
                encontrei=1;
            }
        }
    } 
    if(encontrei==1){
        printf("Maximo produto %d %d %d.\n",idp,ide,qtd);
    }
}

void sort_produtos_preco(Produto input[], Produto output[],int size){
    for(i=0;i<size;i++){
        output[i].id=input[i].id;
        strcpy(output[i].descricao,input[i].descricao);
        output[i].preco=input[i].preco;
        output[i].peso=input[i].peso;
        output[i].quantidade_stock=input[i].quantidade_stock;
    }
    for(i=0;i<size;i++){
        for(j=0;j<size-i-1;j++){
            if(output[j].preco>output[j+1].preco){
                /*copia elemento para auxiliar*/
                aux.id=output[j].id;
                strcpy(aux.descricao,output[j].descricao);
                aux.preco=output[j].preco;
                aux.peso=output[j].peso;   
                aux.quantidade_stock=output[j].quantidade_stock;
                
                /*copia elemento+1 para elemento*/
                output[j].id=output[j+1].id;
                strcpy(output[j].descricao,output[j+1].descricao);
                output[j].preco=output[j+1].preco;
                output[j].peso=output[j+1].peso;
                output[j].quantidade_stock=output[j+1].quantidade_stock;
                
                /*copia auxiliar para elemento+1*/
                output[j+1].id=aux.id;
                strcpy(output[j+1].descricao,aux.descricao);
                output[j+1].preco=aux.preco;
                output[j+1].peso=aux.peso;
                output[j+1].quantidade_stock=aux.quantidade_stock;   
            }
        }
    }
}


/**
l - lista todos os produtos existentes no sistema por ordem crescente de pre?o.
Se houver 2 ou mais produtos com o mesmo pre?o, dever? imprimir esses por ordem crescente de id de produto
Formato de entrada: l
Formato de sa?da: Um bloco no formato abaixo, e em que os produtos s?o listados por ordem crescente de pre?o
*/
void listar_produtos_existentes_sistema_crescente(){
    sort_produtos_preco(produtos,produtos_ordenados,numero_produtos);
    printf("Produtos\n");
    for(i=0;i<numero_produtos;i++){
        printf("* %s %d %d\n", produtos_ordenados[i].descricao, produtos_ordenados[i].preco, produtos_ordenados[i].quantidade_stock);
    }
}


/**
R - remove um produto de uma encomenda
Formato de entrada: R ide:idp
Formato de sa?da: NADA (excepto erro)
*/
void remove_produto_encomenda(){
    int idp;
    int i;
    int produto_existe=0;
    int indice_produto_a_remover;
    scanf("%d:%d", &ide, &idp);
    if(ide>=numero_encomendas){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp,ide);
        return;
    }
    if(idp>=numero_produtos){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp,ide);
        return;
    }
    for(i=0;i<encomendas[ide].products_size;i++){
        if(encomendas[ide].produtos[i].id==idp){
            produto_existe=1;
            indice_produto_a_remover=i;
        }
    }
    if(produto_existe==1){
        produtos[idp].quantidade_stock= produtos[idp].quantidade_stock + encomendas[ide].produtos[indice_produto_a_remover].quantidade_stock;
        for(i=indice_produto_a_remover;i<encomendas[ide].products_size-1;i++){
            /*copiar os elemento+1 para elemento*/
            encomendas[ide].produtos[i].id=encomendas[ide].produtos[i+1].id;
            strcpy(encomendas[ide].produtos[i].descricao, encomendas[ide].produtos[i+1].descricao);
            encomendas[ide].produtos[i].preco= encomendas[ide].produtos[i+1].preco;
            encomendas[ide].produtos[i].peso= encomendas[ide].produtos[i+1].peso;
            encomendas[ide].produtos[i].quantidade_stock= encomendas[ide].produtos[i+1].quantidade_stock;
            
        }
        encomendas[ide].products_size--;    
    }
}



/**
C - calcula o custo de uma encomenda
Formato de entrada: C ide
Formato de sa?da: Custo da encomenda <ide> <total>. onde 
<total> ? o valor total da encomenda <ide>
*/
void calcula_custo_encomenda(){
    int custo_encomenda;
    custo_encomenda = 0;
    scanf("%d", &ide);
    if(ide>=numero_encomendas){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    for(i=0;i<encomendas[ide].products_size;i++){
        custo_encomenda = custo_encomenda + encomendas[ide].produtos[i].preco * encomendas[ide].produtos[i].quantidade_stock;
    }
    printf("Custo da encomenda %d %d.\n",ide, custo_encomenda);
}




/**
p - altera o pre?o de um produto existente no sistema
Formato de entrada: p idp:preco
Formato de sa?da: NADA (excepto erro)
*/
void altera_preco_produto(){
    int idp;
    int preco;
    scanf("%d:%d", &idp,&preco);

    if(idp>=numero_produtos){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
        return; 
    }
    produtos[idp].preco = preco;
    for(i=0;i<numero_encomendas;i++){
        for(j=0;j<encomendas[i].products_size;j++){
            if(encomendas[i].produtos[j].id==idp){
                encomendas[i].produtos[j].preco = produtos[idp].preco;
                
            }
        }
    }
}



/**
E - lista a descri??o e a quantidade de um produto numa encomenda
Formato de entrada: E ide:idp
Formato de sa?da: <desc> <qtd>. onde <desc> ? a descri??o do produto <idp> e <qtd>
? a quantidade desse produto na encomenda <ide>
*/
void lista_descricao_quantidade_produto_encomenda(){
    int idp;
    int i=0;
    scanf("%d:%d", &ide,&idp);


    if(ide>=numero_encomendas){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    if(idp>=numero_produtos){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;

    }
    
    for(i=0;i<encomendas[ide].products_size;i++){
        if(encomendas[ide].produtos[i].id==idp){
            printf("%s %d.\n", encomendas[ide].produtos[i].descricao, encomendas[ide].produtos[i].quantidade_stock);
            return;
    
        }
       
    }
    printf("%s %d.\n", produtos[idp].descricao,0);
}        
      

void sort_produtos_alfabetica(Produto input[], Produto output[],int size){
    for(i=0;i<size;i++){
        output[i].id=input[i].id;
        strcpy(output[i].descricao,input[i].descricao);
        output[i].preco=input[i].preco;
        output[i].peso=input[i].peso;
        output[i].quantidade_stock=input[i].quantidade_stock;
    }
    for(i=0;i<size;i++){
        for(j=0;j<size-i-1;j++){
            if(strcmp(output[j].descricao,output[j+1].descricao)>=1){
                /*copia elemento para auxiliar*/
                aux.id=output[j].id;
                strcpy(aux.descricao,output[j].descricao);
                aux.preco=output[j].preco;
                aux.peso=output[j].peso;
                aux.quantidade_stock=output[j].quantidade_stock;
                
                /*copia elemento+1 para elemento*/
                output[j].id=output[j+1].id;
                strcpy(output[j].descricao,output[j+1].descricao);
                output[j].preco=output[j+1].preco;
                output[j].peso=output[j+1].peso;
                output[j].quantidade_stock=output[j+1].quantidade_stock;
                
                /*copia auxiliar para elemento+1*/
                output[j+1].id=aux.id;
                strcpy(output[j+1].descricao,aux.descricao);
                output[j+1].preco=aux.preco;
                output[j+1].peso=aux.peso;
                output[j+1].quantidade_stock=aux.quantidade_stock;   
            }
        }
    }
}

/**
L - lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o
Formato de entrada: L <ide>

Formato de sa?da: Um bloco no formato abaixo, e em que os produtos s?o listados por ordem alfab?tica de descri??o
*/
void lista_produtos_encomenda_alfabetica(){
    scanf("%d", &ide);
    if(ide>=numero_encomendas){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    sort_produtos_alfabetica(encomendas[ide].produtos,produtos_ordenados,encomendas[ide].products_size);
    printf("Encomenda %d\n", ide);
    for(i=0;i<encomendas[ide].products_size;i++){
        printf("* %s %d %d\n", produtos_ordenados[i].descricao, produtos_ordenados[i].preco, produtos_ordenados[i].quantidade_stock);   
    }
}

void ler_comando(char comando){
    if (comando=='x'){
        EOF;
    }
    switch(comando){
        case 'a': {  
            adiciona_novo_produto();
            break;
        }
        case 'q':{
            adiciona_stock_sistema();
            break;
        }
        case 'N':{
            cria_nova_encomenda();
            break;
        }
        case 'A':{
            adiciona_produto_encomenda();
            break;
        }
        case 'r':{
            remove_stock_produto();
            break;
        }
        case 'm':{
            retorna_identificador_encomenda();
            break;
        }
        case 'l':{
            listar_produtos_existentes_sistema_crescente();
            break;
        }
        case 'R':{
            remove_produto_encomenda();
            break;
        }
        case 'C':{
            calcula_custo_encomenda();
            break;
        }
        case 'p':{
            altera_preco_produto();
            break;
        }
        case 'E':{
            lista_descricao_quantidade_produto_encomenda();
            break;
        }
        case 'L':{
            lista_produtos_encomenda_alfabetica();
            break;
        }
        /*default:
            while(getchar()!=EOF);*/

    }


}      


int main(){
    char comando;
    comando=getchar();
    while(comando!='x'){
        ler_comando(comando);
        comando=getchar();
    }    

    return 0;
}    
