#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int id_produto_count = 1;
int id_encomenda_count = 1;

struct produto{
    int id_produto;
    char descricao[63];
    int preco;
    int peso;
    int stock;
};
struct produto produto_aux;
struct produto empty_product;
struct produto lista_produtos[10000];
struct produto lista_encomendas[500][10000];
struct produto lista_produtos_aux[10000];




void a(char indescricao, int inpreco, int inpeso, int inqtd){
    struct produto novo_produto;
    
    novo_produto.id_produto = id_produto_count;
    strcpy( novo_produto.descricao, &indescricao);
    novo_produto.preco = inpreco;
    novo_produto.peso = inpeso;
    novo_produto.stock = inqtd;
    
    
    lista_produtos[id_produto_count] = novo_produto;
    printf("Novo produto %d\n", id_produto_count);
    id_produto_count += 1;
    
}

void q(int idp, int qtd){
    if (idp <= id_produto_count){
        lista_produtos[idp].stock += qtd;
    }
    else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.", idp);
    }
}

void N(){
    
    printf("Nova encomenda %d", id_encomenda_count);
    id_encomenda_count += 1;
}


void r(int idp, int qtd){
    if(idp > id_produto_count){
        printf("Impossivel remover stock do produto %d. Produto inexistente.", idp);
    }
    if(lista_produtos[idp].stock < qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.", qtd, idp);
    }
    
    else{
        lista_produtos[idp].stock = lista_produtos[idp].stock - qtd;
    }
}

void A(int ide, int idp, int qtd){

    int peso_total = 0;
    int i;
    struct produto produto_encomenda = lista_produtos[idp];

    if(id_encomenda_count < ide ){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.", idp, ide);
    }
    if(id_produto_count < idp){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.", idp, ide);
    }
    if(lista_produtos[idp].stock < qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.", idp, ide);
    }
    for(i = 0;i<500;i++){
        peso_total = (lista_encomendas[ide][i].peso * lista_encomendas[ide][i].stock) + peso_total;       
    }
    if(peso_total + (lista_produtos[idp].peso * qtd) > 200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.", idp, ide);
    }
    else{
        for(i = 0;i<500;i++){
            if(lista_encomendas[ide][i].id_produto == idp){
                lista_encomendas[ide][i].stock += qtd;
                return;
            }
        }
        
        produto_encomenda.stock = qtd;
        lista_encomendas[ide][idp] = produto_encomenda;
        r(idp,qtd);

    }
}

void R(int ide, int idp){
    if(id_encomenda_count < ide ){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.", idp, ide);
    }
    if(id_produto_count < idp){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.", idp, ide);
    }
    else{
        lista_encomendas[ide][idp] = empty_product;
    }
}

void C(int ide){
    int i;
    if(id_encomenda_count < ide ){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.", ide);
    }
    else{
        int custo_total = 0;
        for(i = 0; i<500;i++){
            custo_total += (lista_encomendas[ide][i].preco * lista_encomendas[ide][i].stock);
        }
        printf("Custo da encomenda %d %d.", ide, custo_total);
    }
}

void p(int idp, int preco){
    if(id_produto_count < idp){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.", idp);
    }
    else{
        lista_produtos[idp].preco = preco;
    }
}

void E(int ide, int idp){
    if(id_encomenda_count < ide ){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.", ide);
    }
    if(id_produto_count < idp ){
        printf("Impossivel listar produto %d. Encomenda inexistente.", ide);
    }
    else{
        printf("%s %d", lista_encomendas[ide][idp].descricao, lista_encomendas[ide][idp].stock);
    }
}

void m(int idp){
    int i;
    if(idp > id_produto_count){
        printf("Impossivel remover stock do produto %d. Produto inexistente.", idp);
    }
    else{
        int max_quantidade;
        int max_ide;

        for(i = 0;i<500;i++){
            if(lista_encomendas[i][idp].stock > max_quantidade){
                max_quantidade = lista_encomendas[i][idp].stock;
                max_ide = i;
            }
        }
        printf("Maximo produto %d %d %d.", idp, max_ide, max_quantidade);
    }
    
}

void l(){
    int i;
    int j;
    for(i = 0;i<10000;i++){
        lista_produtos_aux[i] = lista_produtos[i];
    }

    for(i = 0;i<10000-1;i++){
        for(j = i + 1; j <= 10000;j++){
            if(lista_produtos_aux[j].preco < lista_produtos_aux[i].preco){
                produto_aux = lista_produtos_aux[i];
                lista_produtos_aux[i] = lista_produtos_aux[j];
                lista_produtos_aux[j] = produto_aux;
            }
        }
    }
    printf("Produtos");
    for(i = 0;i<10000;i++){
        printf("\n* %s %d %d", lista_produtos_aux[i].descricao, lista_produtos_aux[i].preco, lista_produtos_aux[i].stock);
    }
}




int main(){
    



    while(1){
        char command;
        int argide;
        int argidp;
        char argdescricao;
        int argpreco;
        int argpeso;
        int argqtd;

        scanf("%c", &command);

        switch(command){
            case 'a':
                scanf("%s:%d:%d:%d", &argdescricao, &argpreco, &argpeso, &argqtd);
                a(argdescricao, argpreco, argpeso, argqtd);
                break;
            
            case 'q':
                scanf("%d:%d", &argidp, &argqtd);
                q(argidp,argqtd);
                break;

            case 'N':
                N();
                break;

            case 'A':
                scanf("%d:%d:%d", &argide, &argidp, &argqtd);
                A(argide, argidp, argqtd);
                break;

            case 'r':
                scanf("%d:%d", &argidp, &argqtd);
                r(argidp, argqtd);
                break;

            case 'R':
                scanf("%d:%d", &argide, &argidp);
                R(argide, argidp);
                break;

            case 'C':
                scanf("%d", &argide);
                C(argide);
                break;

            case 'p':
                scanf("%d:%d", &argidp, &argpreco);
                p(argidp, argpreco);
                break;

            case 'E':
                scanf("%d:%d", &argide, &argidp);
                E(argide, argidp);
                break;
            
            case 'm':
                scanf("%d", &argidp);
                m(argidp);
                break;
            
            case 'l':
                l();
                break;


            case 'x':
                return 0;

            default:
                printf("Error!\n");
                break;
        }
    }

}