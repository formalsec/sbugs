#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max_descricao 64
#define max_encomendas 500
#define max_produtos 10000
#define max_lista_produtos 1300
/*Joao Miguel Cunha Pereira 95602*/
int currentPID = 0; /*id do produto atual comeca em 0 */
int currentEID = 0; /*id da encomenda atual comeca em 0 */

typedef struct Produto{
    int idp;
    char descricao[max_descricao];        /*descricao com maximo de 63 caracteres*/
    int preco;
    int peso;
    int qtd;
}produto;

typedef struct lista_prods{
    int qtd, idp;
}lp_naencomenda;

typedef struct Encomenda{
    int ide, peso, total_produtos;
    lp_naencomenda lista_produtos[max_lista_produtos];               /*encomenda com maximo de 10000 produtos*/
}encomenda;

void get_input(char s[], char c, produto prods[], encomenda encs[]);
void adiciona_produto(char descricao[], int preco, int peso, int qtd, produto lp[]);
void lista_produtos(produto produtos[]);
void adiciona_produtoencomenda(int ide, int idp, int qtd,produto lp[], encomenda ecs[]);
void cria_encomenda(encomenda ecs[]);
void listaprodsnaencomenda(int ide, produto produtos[], encomenda ecs[]);
void adiciona_stock(int idp, int qtd, produto produtos[]);
void remove_stock(int idp, int qtd, produto produtos[]);
void remove_produtoencomenda(int ide, int idp, produto produtos[], encomenda ecs[]);
void calculacusto(int ide, produto produtos[], encomenda ecs[]);
void alterapreco(int idp, int preco, produto produtos[]);
void listaprodutonumaencomenda(int ide, int idp, produto produtos[], encomenda ecs[]);
void ocorremaisvezes(int idp, encomenda ecs[]);
void mergesort(produto produtos[], int left, int right);
void merge(produto produtos[], int left, int m, int right);
void mergesortL(lp_naencomenda listaprodutos[],produto produtos[], int left, int right);
void mergeL(lp_naencomenda listaprodutos[],produto produtos[], int left, int m, int right);
int main(){
    produto produtos[max_produtos];
    encomenda encomendas[max_encomendas];
    char input[1000];
    int flag = 1;
    do{
        switch(getchar()){

            case('a'):
                scanf("%s", input);
                get_input(input,'a', produtos, encomendas);
                break;
            case('q'):
                scanf("%s", input);
                get_input(input, 'q', produtos, encomendas);
                break;
            case('N'):
                cria_encomenda(encomendas);
                break;
            case('A'):
                scanf("%s", input);
                get_input(input, 'A', produtos, encomendas);
                break;
             case('r'):
                scanf("%s", input);
                get_input(input, 'r', produtos, encomendas);
                break;
            case('R'):
                scanf("%s", input);
                get_input(input, 'R', produtos, encomendas);
                break;
            case('C'):
                scanf("%s", input);
                get_input(input, 'C', produtos, encomendas);
                break;
            case('p'):
                scanf("%s", input);
                get_input(input, 'p', produtos, encomendas);
                break;
            case('E'):
                scanf("%s", input);
                get_input(input, 'E', produtos, encomendas);
                break;
            case('m'):
                scanf("%s", input);
                get_input(input, 'm', produtos, encomendas);
                break;
            case('l'):
                lista_produtos(produtos);
                break;
            case('L'):
                scanf("%s", input);
                get_input(input, 'L', produtos, encomendas);
                break;
            case('x'):
                flag = 0;
                break;
        }
    }while(flag == 1);
    return 0;  
}
    
void get_input(char s[], char c, produto prods[], encomenda encs[]){
    char aux[4][max_descricao];
    int i = 0;
    char* particao = strtok(s,":");
    while(particao != NULL){
        strcpy(aux[i], particao);
        particao = strtok(NULL, ":");
        i++;
    }
    if (c == 'a'){
        adiciona_produto(aux[0], atoi(aux[1]), atoi(aux[2]), atoi(aux[3]), prods);
     }
    if (c == 'A'){
        adiciona_produtoencomenda(atoi(aux[0]), atoi(aux[1]), atoi(aux[2]),prods, encs);
    }
    if (c == 'L'){
        listaprodsnaencomenda(atoi(aux[0]),prods, encs);
    }
    if (c == 'q'){
        adiciona_stock(atoi(aux[0]), atoi(aux[1]), prods);
    }
    if (c == 'r'){
        remove_stock(atoi(aux[0]), atoi(aux[1]), prods);
    }
    if (c == 'R'){
        remove_produtoencomenda(atoi(aux[0]), atoi(aux[1]), prods, encs);
    }
    if (c == 'C'){
        calculacusto(atoi(aux[0]), prods, encs);
    }
    if (c == 'p'){
        alterapreco(atoi(aux[0]), atoi(aux[1]), prods);
    }
    if (c == 'E'){
        listaprodutonumaencomenda(atoi(aux[0]), atoi(aux[1]), prods, encs);
    }
    if (c == 'm'){
        ocorremaisvezes(atoi(aux[0]), encs);
    }
}  

void adiciona_produto(char descricao[], int preco, int peso, int qtd, produto prods[]){
    produto p;
    strcpy(p.descricao, descricao);
    p.preco = preco;
    p.peso = peso;
    p.qtd = qtd;
    p.idp = currentPID;
    prods[currentPID] = p;
    printf("Novo produto %d.\n", currentPID);
    currentPID++;
}

void lista_produtos(produto produtos[]){
    int i;
    int l = 0;
    int r = currentPID-1;
    produto produtoaux[10000];
    for(i=0; i<currentPID; i++){
        produtoaux[i] = produtos[i];
    }
    printf("Produtos\n");
    mergesort(produtoaux, l, r);
    for (i=0; i<currentPID; i++){  
        printf("* %s %d %d\n" ,produtoaux[i].descricao, produtoaux[i].preco, produtoaux[i].qtd);
    }
}

void cria_encomenda(encomenda ecs[]){
    encomenda e;
    e.ide = currentEID;
    ecs[currentEID] = e;
    printf("Nova encomenda %d.\n", currentEID);
    currentEID++;
}

void adiciona_produtoencomenda(int ide, int idp, int qtd,produto produtos[], encomenda ecs[]){
    produto p;
    encomenda e;
    lp_naencomenda lp;
    int i, flag = 0;
    int subtracao;
    int pesohipotetico;
    if (ide >= currentEID){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
        return;
    }
    else if (idp >= currentPID){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp, ide);
        return;
    }
    else{
        p = produtos[idp];
        e = ecs[ide];
        subtracao = p.qtd - qtd;
        pesohipotetico = e.peso + (p.peso*qtd);
        if (subtracao < 0){
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
            return;
        }
        else if(pesohipotetico > 200){
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
            return;
        }
        else{
            p.qtd = p.qtd - qtd;
            e.peso += p.peso * qtd;
            for(i=0; i<e.total_produtos && flag == 0; i++){
                if (e.lista_produtos[i].idp == idp){
                    e.lista_produtos[i].idp = idp;
                    e.lista_produtos[i].qtd += qtd;
                    flag = 1;
                }
            } 
            if (flag == 0){
                lp.idp = idp;
                lp.qtd = qtd;
                e.lista_produtos[e.total_produtos] = lp;
                e.total_produtos+= 1;
            }
            produtos[idp] = p;
            ecs[ide] = e;
        }
    }
}

void listaprodsnaencomenda(int ide,produto produtos[], encomenda ecs[]){ 
    int i, idp, qtd;
    encomenda e;
    produto p;
    int l = 0;
    int r;
    if (ide >= currentEID){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }    
    else{
        e = ecs[ide];
        r = e.total_produtos - 1;
        printf("Encomenda %d\n", e.ide);
        mergesortL(e.lista_produtos, produtos, l, r);
        for(i=0; i<e.total_produtos;i++){
            idp = e.lista_produtos[i].idp;
            qtd = e.lista_produtos[i].qtd;
            p = produtos[idp];
            printf("* %s %d %d\n", p.descricao, p.preco, qtd);
        }
    }            
}

void adiciona_stock(int idp, int qtd, produto produtos[]){
    int flagprod = 0;
    int j;
    if (idp >= currentPID){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
    }
    else{
        for(j=0; j<currentPID && flagprod == 0; j++){
            if(produtos[j].idp == idp){
                produtos[j].qtd += qtd;
                flagprod = 1;
            }   
        }
    }
}
void remove_stock(int idp, int qtd, produto produtos[]){
    int flagprod = 0;
    int flagremov = 0;
    int j;
    int qtd1;
    for(j=0; j<currentPID && flagprod == 0; j++){
        if(produtos[j].idp == idp){
            qtd1 = produtos[j].qtd;
            if((qtd1-= qtd) >= 0){
                flagremov = 1;
                produtos[j].qtd -= qtd;
            }
            flagprod = 1;
        }
    }
    if(flagprod == 0){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
    }
    else if(flagremov == 0){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd, idp);
    }
}
void remove_produtoencomenda(int ide, int idp, produto produtos[], encomenda ecs[]){
    int l;
    int k = 0;
    int qtd, pos;
    encomenda e;
    int flag = 0;
    if (ide >= currentEID){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    }
    else if(idp >= currentPID){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp, ide);
    }
    else{
        e = ecs[ide];
        for(k=0; k<e.total_produtos && flag == 0; k++){
            if (e.lista_produtos[k].idp == idp){
                flag = 1;
                qtd = e.lista_produtos[k].qtd;
            }
        }
        if (flag == 1){
            pos = k-1;
            adiciona_stock(idp, qtd, produtos);
            e.peso = e.peso - produtos[idp].peso * qtd;
            for (l=pos; l<e.total_produtos; l++){
                e.lista_produtos[l] = e.lista_produtos[l+1];
                }
            e.total_produtos --;
            ecs[ide] = e;
        }
    }
}
void calculacusto(int ide, produto produtos[], encomenda ecs[]){
    encomenda e;
    produto p;
    int i, qtd, idp;
    int custo = 0;
    if (ide >= currentEID){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        e = ecs[ide];
        for(i=0; i<e.total_produtos; i++){
            idp = e.lista_produtos[i].idp;
            qtd = e.lista_produtos[i].qtd;
            p = produtos[idp];
            custo += p.preco*qtd;
        }
        printf("Custo da encomenda %d %d.\n", ide, custo);

    }       
}
void alterapreco(int idp, int preco, produto produtos[]){
    produto p;
    if (idp >= currentPID){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else{
        p = produtos[idp];
        p.preco = preco;
        produtos[idp] = p;
    }
}
void listaprodutonumaencomenda(int ide, int idp, produto produtos[], encomenda ecs[]){
    encomenda e;
    produto p;
    int i;
    int qtd = 0;
    int flag = 0;
    if (ide >= currentEID){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else if(idp >= currentPID){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else{
        e = ecs[ide];
        p = produtos[idp];
        for (i=0; i<e.total_produtos && flag == 0; i++){
            if (e.lista_produtos[i].idp == idp){
                qtd = e.lista_produtos[i].qtd;
                flag = 1;
            }
        }
        printf("%s %d.\n", p.descricao, qtd);
    }
}
void ocorremaisvezes(int idp, encomenda ecs[]){
    encomenda e;
    int i,j;
    int flag = 0;
    int maximo = 0;
    int ide;
    if (idp >= currentPID){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
    else{
        for(i=0; i<currentEID; i++){
            flag = 0;
            e = ecs[i];
            for(j=0; j<e.total_produtos && flag == 0;j++){
                if(e.lista_produtos[j].idp == idp){
                    flag = 1;
                    if(e.lista_produtos[j].qtd > maximo){
                        maximo = e.lista_produtos[j].qtd;
                        ide = e.ide;
                    }
                }
            }
        }
        if (maximo > 0){
            printf("Maximo produto %d %d %d.\n", idp, ide, maximo);
        }
    }
}
void mergesort(produto produtoaux[], int left, int right){
    int meio = (left + right)/2;
    if (right<=left)
        return;
    mergesort(produtoaux, left, meio);
    mergesort(produtoaux, meio+1, right);
    merge(produtoaux, left, meio, right);
}
void merge(produto produtoaux[], int left, int m, int right){
    int i, j, k;
    produto aux[10000];
    for (i = m+1; i > left; i--){
        aux[i-1] = produtoaux[i-1];
    }
    for (j = m; j < right; j++){
        aux[right+m-j] = produtoaux[j+1];
    }
    for (k = left; k <= right; k++){
        if ((aux[j].preco < aux[i].preco) || (i > m)){
            produtoaux[k] = aux[j--];
        }  
        else{
            produtoaux[k] = aux[i++];
        }
    }
}

void mergesortL(lp_naencomenda listaprodutos[],produto produtos[], int left, int right){
    int meio = (left + right)/2;
    if (right<=left)
        return;
    mergesortL(listaprodutos, produtos, left, meio);
    mergesortL(listaprodutos, produtos, meio+1, right);
    mergeL(listaprodutos, produtos, left, meio, right);
}
void mergeL(lp_naencomenda listaprodutos[], produto produtos[], int left, int m, int right){
    int i, j, k;
    lp_naencomenda auxL[10000];
    for (i = m+1; i > left; i--){
        auxL[i-1] = listaprodutos[i-1];
    }
    for (j = m; j < right; j++){
        auxL[right+m-j] = listaprodutos[j+1];
    }
    for (k = left; k <= right; k++){
         if ((strcmp(produtos[auxL[j].idp].descricao, produtos[auxL[i].idp].descricao)<0))
             listaprodutos[k] = auxL[j--];
      else
        listaprodutos[k] = auxL[i++];
    }
}