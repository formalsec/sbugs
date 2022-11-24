#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_STOCK 10000
#define MAX_ENCOMENDAS 500
#define MAX_PROD_ENCOMENDADOS 200
#define MAX_PESO_ENCOMENDA 200
#define DESMAX 64

#define isInEncomenda 1
#define notInEncomenda 2

#define Enable 1
#define Disable 2

#define True 2
#define False 1

/*produto*/
typedef struct{
    int idp; /* um int no intervalo [0, 9 999]*/
    char description_produto[DESMAX]; /*string ate 63 caracters*/
    int price_produto; /* int maior que 0*/
    int weight_produto; /*int maior que 0*/
    int qtd_produto; /*int maior ou igual a 0*/
    int isActive;
    int insideEcomenda;
}produto;

/*encomenda*/
typedef struct{
    /*conjunto de produtos e uma encomenda*/
    produto conj[MAX_PROD_ENCOMENDADOS];

    int ide; /*ide da encomenda*/
    int weight_encomenda; /*peso da encomenda max e 200*/
    int isActive;
    int current_size;
    int total_price;

}encomenda;

/*todos os produtos distintos em stock*/
produto stock[MAX_STOCK];
/*lista de todas as encomendas ate 500*/
encomenda lista_encomendas[MAX_ENCOMENDAS];

/*contadores do idp e ide*/
int idp_counter = 0;
int ide_counter = 0;

/*Prototipos*/
void init_Stock();
void init_Encomendas();
void a();
void q();
void N();
void A();
void r();
void R();
void C();
void p();
void E();
void m();
void l();
void L();

void adicionaProdutoAEcomenda();

int produtoExiste(int aux_idp);
int encomendaExiste(int aux_ide);
int produtoDentroDeEncomenda(int aux_idp, int aux_ide);

int main(){

    char comando;

    init_Stock();
    init_Encomendas();


    while((comando = getchar()) != 'x'){
        switch(comando){
            case 'a':
                a();
                break;
            case 'q':
                q();
                break;
            case 'N':
                N();
                break;
            case 'A':
                A();
                break;
            case 'r':
                r();
                break;
            case 'R':
                R();
                break;
            case 'C':
                C();
                break;
            case 'p':
                p();
                break;
            case 'E':
                E();
                break;
            case 'm':
                m();
                break;
            case 'l':
                l();
                break;
            case 'L':
                L();
                break;
            case '\n':
                break;
            
        }
        
    }

    return 0;
}
/**** Funcoes auxiliares ************************************/
int produtoExiste(int aux_idp){
    int res = False;
    if(stock[aux_idp].idp == aux_idp && stock[aux_idp].isActive == Enable){
        res = True;
    }
    return res;
}

int encomendaExiste(int aux_ide){
    int res = False;
    if(lista_encomendas[aux_ide].ide == aux_ide && lista_encomendas[aux_ide].isActive == Enable){
        res = True;
    }
    return res;
}

int produtoDentroDeEncomenda(int aux_idp, int aux_ide){
    int res = False;
    if(lista_encomendas[aux_ide].conj[aux_idp].insideEcomenda == True){
        res = True;
    }
    return res;
}
/***********************************************************/
void init_Stock(){
    int i;
    produto vazio;

    vazio.idp = -1;
    vazio.price_produto = 0;
    vazio.weight_produto = 0;
    vazio.qtd_produto = 0;
    vazio.isActive = Disable;
    vazio.insideEcomenda = Disable;

    for(i=0;i<MAX_STOCK;i++){
        stock[i] = vazio;
    }
}

void init_Encomendas(){
    int i;
    encomenda vazio;

    vazio.ide = -1;
    vazio.weight_encomenda = 0;
    vazio.isActive = Disable;

    for(i=0;i<MAX_ENCOMENDAS;i++){
        lista_encomendas[i] = vazio;
    }
}

void a(){
    /*adiciona um novo produto ao stock*/
    char aux_des[DESMAX];
    int aux_price;
    int aux_weight;
    int aux_qtd;

    char c_spaces;

    produto novo_produto;

    /*Input*/
    /*para ignorar espacos entre o comando e as instrucoes*/
    while((c_spaces = getchar()) != ' ');
    scanf("%[^:]:%d:%d:%d", aux_des, &aux_price, &aux_weight, &aux_qtd);
    
    /*criacao do produto*/
    novo_produto.idp = idp_counter;
    strcpy(novo_produto.description_produto, aux_des);
    novo_produto.price_produto = aux_price;
    novo_produto.weight_produto = aux_weight;
    novo_produto.qtd_produto = aux_qtd;
    novo_produto.isActive = Enable;
    novo_produto.insideEcomenda = False;
    /*adicionar ao stock*/
    stock[idp_counter] = novo_produto;
    /*aumenta idp para o proximo produto criado*/
    idp_counter++;

    /*output*/
    printf("Novo produto %d.\n", novo_produto.idp);
}

void q(){
    /*adiciona stock a um produto existente no stock*/
    int aux_idp;
    int aux_qtd;

    /*input*/
    scanf("%d:%d", &aux_idp, &aux_qtd);
    /*Assigment*/
    if(produtoExiste(aux_idp) == True){
        stock[aux_idp].qtd_produto += aux_qtd;
    }
    else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", aux_idp);
    }

}

void N(){
    /*cria uma nova encomenda*/
    int aux_weight = 0;

    encomenda nova_encomenda;

    /*Assignment*/
    nova_encomenda.weight_encomenda = aux_weight;
    nova_encomenda.ide = ide_counter;
    nova_encomenda.isActive = Enable;
    nova_encomenda.current_size = 0;
    nova_encomenda.total_price = 0;
    /*Adicionar a lista de encomendas*/
    lista_encomendas[ide_counter] = nova_encomenda;
    /*aumenta ide para proxima encomenda criada*/
    ide_counter++;

    /*output*/
    printf("Nova encomenda %d.\n", nova_encomenda.ide);


}

void A(){
    /*adiciona um produto a uma encomenda. 
    Se o produto j? existir na encomenda, 
    adiciona a nova quantidade ? quantidade existente*/
    int aux_ide;
    int aux_idp;
    int aux_qtd;

    char c_spaces;
    /*input*/
    while((c_spaces = getchar()) != ' ');
    scanf("%d:%d:%d", &aux_ide, &aux_idp, &aux_qtd);
    /*Assignment*/

 
    if(encomendaExiste(aux_ide) == True){
       
        if(produtoExiste(aux_idp) == True){
            
            if(stock[aux_idp].qtd_produto >= aux_qtd){
                
                if(lista_encomendas[aux_ide].weight_encomenda + (stock[aux_idp].weight_produto * aux_qtd) <= MAX_PESO_ENCOMENDA){
                   
                    adicionaProdutoAEcomenda(aux_ide, aux_idp, aux_qtd);
                }else{
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", aux_idp, aux_ide);
                }
            }
            else{
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", aux_idp, aux_ide);
            }
        }
        else{
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", aux_idp, aux_ide);
        }
    }
    else{
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", aux_idp, aux_ide);
    }
}

void adicionaProdutoAEcomenda(int ide, int idp, int qtd){
    /*Procedimento que atualiza o sistema ao adicionar
    produto a encomenda*/
    
    if(produtoDentroDeEncomenda(idp, ide) == True){
        stock[idp].qtd_produto -= qtd;
        lista_encomendas[ide].conj[idp].qtd_produto += qtd;
        lista_encomendas[ide].weight_encomenda += stock[idp].weight_produto * qtd;
        /*lista_encomendas[ide].total_price += stock[idp].price_produto * qtd;*/
        
    }else{
        lista_encomendas[ide].conj[idp] = stock[idp];
        strcpy(lista_encomendas[ide].conj[idp].description_produto, stock[idp].description_produto);
        lista_encomendas[ide].conj[idp].insideEcomenda = True;
        stock[idp].qtd_produto -= qtd;
        lista_encomendas[ide].conj[idp].qtd_produto = qtd;
        lista_encomendas[ide].weight_encomenda += stock[idp].weight_produto * qtd;
        /*lista_encomendas[ide].total_price += stock[idp].price_produto * qtd;*/
        lista_encomendas[ide].current_size += 1;   
    }
    
}

void r(){
    /*remove stock a um produto existente*/
    int aux_idp;
    int aux_qtd;

    /*input*/
    scanf("%d:%d", &aux_idp, &aux_qtd);
    /*Assignment*/
    if(produtoExiste(aux_idp) == True){
        if(stock[aux_idp].qtd_produto - aux_qtd >= 0){
            stock[aux_idp].qtd_produto -= aux_qtd;

        }else{
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", aux_qtd, aux_idp);
        }

    }else{
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", aux_idp);
    }

}

void R(){
    /*remove um produto de uma encomenda*/
    int aux_ide;
    int aux_idp;


    /*input*/
    scanf("%d:%d", &aux_ide, &aux_idp);

    /*Assignment*/
    if(encomendaExiste(aux_ide) == True){
        if(produtoExiste(aux_idp) == True){
            /*if(produtoDentroDeEncomenda(aux_idp, aux_ide) == True){*/
                /*lista_encomendas[aux_ide].conj[aux_idp].insideEcomenda = False;*/
                /*lista_encomendas[aux_ide].total_price -= stock[aux_idp].price_produto * lista_encomendas[aux_ide].conj[aux_idp].qtd_produto;*/
                stock[aux_idp].qtd_produto += lista_encomendas[aux_ide].conj[aux_idp].qtd_produto;
                
                lista_encomendas[aux_ide].weight_encomenda -= stock[aux_idp].weight_produto * lista_encomendas[aux_ide].conj[aux_idp].qtd_produto;
                lista_encomendas[aux_ide].conj[aux_idp].qtd_produto = 0;
                lista_encomendas[aux_ide].current_size -= 1;

            /*}*/
        }else{
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", aux_idp, aux_ide);
        }
    }else{
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", aux_idp, aux_ide);
    }
}

void C(){
    /*calcula custo de uma encomenda*/
    int aux_ide;
    int i;
    int total;
    
    /*input*/
    scanf("%d", &aux_ide);

    total = 0;

    /*Assignment*/
    if(encomendaExiste(aux_ide) == True){
        for(i=0; i <MAX_ENCOMENDAS; i++){
            
            total += stock[i].price_produto * lista_encomendas[aux_ide].conj[i].qtd_produto;
        }
        
        
        lista_encomendas[aux_ide].total_price = total;
        
        printf("Custo da encomenda %d %d.\n", aux_ide, lista_encomendas[aux_ide].total_price);
    }else{
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", aux_ide);
    }


}

void p(){
    /*altera o preco de um produto existente no sistema*/
    int aux_idp;
    int aux_price;
    int i;
    int j;

    /*input*/
    scanf("%d:%d", &aux_idp, &aux_price);

    /*Assignment*/
    if(produtoExiste(aux_idp) == True){
        stock[aux_idp].price_produto = aux_price;

        for(i=0; i<ide_counter; i++){
            for(j=0; j < MAX_ENCOMENDAS; j++){
                lista_encomendas[i].conj[j].price_produto = aux_price;
            }
            
        }
    }else{
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", aux_idp);
    }

}

void E(){
    /*lista a descricao e a quantidade de um produto
    numa encomenda*/
    int aux_ide;
    int aux_idp;

    /*input*/
    scanf("%d:%d", &aux_ide, &aux_idp);
    
    /*Assignment*/
    if(encomendaExiste(aux_ide) == True){
        if(produtoExiste(aux_idp) == True){
            /*if(produtoDentroDeEncomenda(aux_idp, aux_ide) == True){*/
                printf("%s %d.\n", stock[aux_idp].description_produto, lista_encomendas[aux_ide].conj[aux_idp].qtd_produto);
            /*}*/

        }else{
            printf("Impossivel listar produto %d. Produto inexistente.\n", aux_idp);
        }
    }else{
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", aux_ide);
    }
}

void m(){
    /*lista o identificador da encomenda em que o produto dado
    ocorre mais vezes. Se houver 2 ou mais encomendas nessa situacao
    imprime a encomenda com menor id*/
    int aux_idp;
    int i;
    int encomenda_com_mais_produto;


    /*input*/
    scanf("%d", &aux_idp);
   

    /*Assignment*/
    if(produtoExiste(aux_idp) == True){
        
        int aux_qtd_2 = 0;
        for(i=0; i< ide_counter; i++){
            int aux_qtd = lista_encomendas[i].conj[aux_idp].qtd_produto;
            if(aux_qtd > aux_qtd_2){
                aux_qtd_2 = aux_qtd;
                encomenda_com_mais_produto = i;
            }
        }
        if(aux_qtd_2 > 0)
            printf("Maximo produto %d %d %d.\n", aux_idp, encomenda_com_mais_produto, lista_encomendas[encomenda_com_mais_produto].conj[aux_idp].qtd_produto);

    }else{
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", aux_idp);
    }

}

void l(){
    /*lista todos os produtos existentes 
    no stock por ordem crescente de pre?o*/
    int i, j;

    /*Provavel ter de criar um stock aux para nao alterar a ordem por indice
    do stock global*/
    /*produto aux_stock[MAX_STOCK]*/

    for(i=0; i < idp_counter; i++){
        int min = i;
        produto aux;
        for(j = i+1; j < idp_counter; j++){
            if(stock[j].price_produto < stock[min].price_produto){
                min = j;
            }else if(stock[j].price_produto == stock[min].price_produto){
                if(stock[j].idp < stock[min].idp){
                    min = j;
                }

            }
        }
        aux = stock[i]; stock[i] = stock[min]; stock[min] = aux;
    }

    /*printf("* %s %d %d\n", stock[0].description_produto, stock[0].price_produto, stock[0].qtd_produto);*/
    printf("Produtos\n");
    for(i=0; i < idp_counter; i++){
        
        printf("* %s %d %d\n", stock[i].description_produto, stock[i].price_produto, stock[i].qtd_produto);
    }

}

void L(){
    /*lista todos os produtos de uma encomenda 
    por ordem alfabetica de descricao*/
    int i,j;
    int aux_ide;
    int tamanho_encomenda;

    /*input*/
    scanf("%d", &aux_ide);

    tamanho_encomenda = lista_encomendas[aux_ide].current_size;

    /*Aqui em prinicipio vai ser o insertionSort*/
    /*Assignment*/
    if(encomendaExiste(aux_ide) == True){
        for(i = 0; i < tamanho_encomenda; i++){
            int min = i;
            produto aux;
            for(j = i+1; j < tamanho_encomenda; j++){
                if(lista_encomendas[aux_ide].conj[j].description_produto[0] <= lista_encomendas[aux_ide].conj[min].description_produto[0]){
                    min = j;
                }
            }
            aux = lista_encomendas[aux_ide].conj[i]; 
            lista_encomendas[aux_ide].conj[i] = lista_encomendas[aux_ide].conj[min];
            lista_encomendas[aux_ide].conj[min] = aux;
        }

        printf("Encomenda %d\n", aux_ide);
        for(i=0; i < tamanho_encomenda; i++){
            
            /*if()*/
            printf("* %s %d %d\n", lista_encomendas[aux_ide].conj[i].description_produto, stock[i].price_produto, lista_encomendas[aux_ide].conj[i].qtd_produto);
        }

    }else{
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", aux_ide);
    }

}

