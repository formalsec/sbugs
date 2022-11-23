#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define TAMANHODESCRICAO 63 /*tamanho maximo de um descricao de um produto*/
#define PRODUTOSMAX 10000  /*maximo de produtos que o sistema pode conter*/
#define ENCOMENDASMAX 500  /*maximo de encomendas que podem ocorrer*/
#define PESOMAX 200        /*maximo de peso que uma encomenda pode ter*/


/* variaveis globais */
int tam_produtos = 0;       /*inteiro que guarda o tamanho do vetor dos produtos*/
int tam_encomendas = 0;     /*inteiro que guarda o tamanho do vetor das encomendas*/ 

typedef struct produto{
    int identificador;
    char descricao[TAMANHODESCRICAO];
    int preco;
    int peso;
    int quantidade;
}produto;

typedef struct encomenda{
    int ident;
    int peso;
    int len;
    int produto_id[PESOMAX];/*vetor onde se guardam os ids dos produtos na encomenda*/
    int produto_quantidade[PESOMAX];/*vetor onde se guardam as quantidades dos produtos na encomenda*/
}encomenda;

/* Funcoes auxiliares */

void insertionSort_L(produto vetor[], int left, int right){
    int i,j;
    for(i=left+1;i<=right;i++){
        produto v;
        strcpy(v.descricao,vetor[i].descricao);
        v.preco = vetor[i].preco;
        v.quantidade = vetor[i].quantidade;
        j = i-1;
        while(j>=left && strcmp(v.descricao,vetor[j].descricao)<0){
            strcpy(vetor[j+1].descricao,vetor[j].descricao);
            vetor[j+1].preco = vetor[j].preco;
            vetor[j+1].quantidade = vetor[j].quantidade;
            j--;
        }
        vetor[j+1].preco = v.preco;
        strcpy(vetor[j+1].descricao, v.descricao);
        vetor[j+1].quantidade = v.quantidade;
    }
}

void merge(produto arr[], int l, int m, int r){
    int i,j,k;
    int n1 = m - l + 1;
    int n2 = r - m;
    produto L[PRODUTOSMAX], R[PRODUTOSMAX];

    for(i=0;i<n1;i++){
        strcpy(L[i].descricao, arr[l+i].descricao);
        L[i].preco = arr[l+i].preco;
        L[i].quantidade = arr[l+i].quantidade;
    }
    for(j=0;j<n2;j++){
        strcpy(R[j].descricao, arr[m+1+j].descricao);
        R[j].preco = arr[m+1+j].preco;
        R[j].quantidade = arr[m+1+j].quantidade;
    }

    i = 0;
    j = 0;
    k = l;

    while(i<n1 && j<n2){
        if(L[i].preco <= R[j].preco){
            strcpy(arr[k].descricao,L[i].descricao);
            arr[k].preco = L[i].preco;
            arr[k].quantidade = L[i].quantidade;
            i++;
        }
        else{
            strcpy(arr[k].descricao,R[j].descricao);
            arr[k].preco = R[j].preco;
            arr[k].quantidade = R[j].quantidade;
            j++;
        }
        k++;
    }

    while(i<n1){
        strcpy(arr[k].descricao, L[i].descricao);
        arr[k].preco = L[i].preco;
        arr[k].quantidade = L[i].quantidade;
        i++;
        k++;
    }

    while(j<n2){
        strcpy(arr[k].descricao,R[j].descricao);
        arr[k].preco = R[j].preco;
        arr[k].quantidade = R[j].quantidade;
        j++;
        k++;
    }

}

void mergeSort(produto arr[],int l, int r){
    int m;
    if(l<r){
        m = (l+r)/2;

        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);

        merge(arr,l,m,r);
    }
}
/* ---------------------- */


/*Adiciona novo produto ao sistema*/
void a(produto v[]){
    scanf(" %[^:]:%d:%d:%d", v[tam_produtos].descricao, &v[tam_produtos].preco, &v[tam_produtos].peso, &v[tam_produtos].quantidade);
    v[tam_produtos].identificador = tam_produtos;
    printf("Novo produto %d.\n", v[tam_produtos].identificador);
    tam_produtos = tam_produtos + 1;
}


/*Adiciona stock a um produto existente no sistema*/
void q(produto v[]){
    int idp, qtd, i;
    scanf("%d:%d", &idp, &qtd);
    for(i = 0; i<tam_produtos; i++){
        if(v[i].identificador == idp){
            /*produto encontrado*/
            v[i].quantidade += qtd;
            return;
        }
    }
    if(i == tam_produtos){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
}


/*Cria uma nova encomenda*/
void N(encomenda v[]){
    encomenda e;
    e.ident = tam_encomendas;
    e.peso = 0;
    e.len = 0;
    v[tam_encomendas] = e;
    printf("Nova encomenda %d.\n", e.ident);
    tam_encomendas = tam_encomendas + 1;
}

/*Adiciona um produto a uma encomenda*/
void A(encomenda v[], produto u[]){
    int ide, idp, qtd, i, j, k;
    scanf("%d:%d:%d", &ide,&idp,&qtd);
    for(k=0;k<tam_encomendas;k++){
        if(v[k].ident == ide){
            break;
        }
    }

    if(k == tam_encomendas){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    

    for(i=0;i<tam_produtos;i++){
        if(u[i].identificador == idp){
            if((u[i].quantidade - qtd) >= 0){
                u[i].quantidade = u[i].quantidade - qtd;
                break;
            }
            else{
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
                return;
            }
        }
    }

    if(i == tam_produtos){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    /*caso o produto ja esteja na encomendas*/
    for(j=0;j<v[k].len;j++){
        if(v[k].produto_id[j] == idp && v[k].peso + (u[i].peso * qtd) <= PESOMAX){
            v[k].produto_quantidade[j] += qtd;
            v[k].peso = v[k].peso + (u[i].peso * qtd);
            return;
        }
        if(v[k].produto_id[j] == idp && v[k].peso + (u[i].peso * qtd) > PESOMAX){
            u[i].quantidade = u[i].quantidade + qtd;
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp,ide);
            return;
        }
    }

    /*caso o produto seja adicionado pela primeira vez a encomenda*/
    if(v[k].peso + (u[i].peso * qtd) <= PESOMAX){
        v[k].produto_id[j] = idp;
        v[k].produto_quantidade[j] = qtd;
        v[k].len = v[k].len + 1;
        v[k].peso = v[k].peso + (u[i].peso * qtd);
        return;
    }
    else{
        u[i].quantidade = u[i].quantidade + qtd;
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp,ide);
        return;
    }

}


/*Remove stock a um produto existente*/
void r(produto v[]){
    int qtd,idp,i;
    scanf("%d:%d", &idp,&qtd);
    for(i=0;i<tam_produtos;i++){
        if(v[i].identificador == idp){
            /*produto encontrado*/
            if((v[i].quantidade - qtd) >= 0){
                v[i].quantidade = v[i].quantidade - qtd;
                return;
            }
            else{
                printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
                return;
            }
        }
    }
    if(i == tam_produtos){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }
}


/*Remove um produto de uma encomenda*/
void R(encomenda v[], produto u[]){
    int ide, idp, i, k, x;
    scanf("%d:%d", &ide, &idp);
    for(i=0;i<tam_encomendas;i++){
        if(v[i].ident == ide){
           break;
        }
    }

    if(i == tam_encomendas){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }

    for(x=0;x<v[i].len;x++){
        if(v[i].produto_id[x] == idp){
            v[i].peso = v[i].peso - (v[i].produto_quantidade[x] * u[idp].peso);
            break;
        }
    }

    for(k=0;k<tam_produtos;k++){
        if(u[k].identificador == idp){
            u[k].quantidade = u[k].quantidade + v[i].produto_quantidade[x];
            break;
        }
    }

    if(k == tam_produtos){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    /*remover o produto da encomenda neste caso peermanece nela mas com quantidade 0*/
    v[i].produto_quantidade[x] = 0;
}


/*Calcula o custo de uma encomenda*/
void C(encomenda v[], produto u[]){
    int ide, i, j, total = 0;   
    scanf("%d", &ide);
    for(i=0;i<tam_encomendas;i++){
        if(v[i].ident == ide){
            break;
        }
    }

    if(i == tam_encomendas){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    for(j=0;j<v[i].len;j++){
                                               /*preco do produto*/
        total += (v[i].produto_quantidade[j] * u[v[i].produto_id[j]].preco);
    }

    printf("Custo da encomenda %d %d.\n", ide, total);
    return;
}


/*Altera o preco de um produto existente no sistema*/
void p(produto v[]){
    int idp, preco, i;
    scanf("%d:%d", &idp, &preco);
    for(i=0;i<tam_produtos;i++){
        if(v[i].identificador == idp){
            /*produto encontrado*/
            v[i].preco = preco;
            return;
        }
    }
    if(i == tam_produtos){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }
}


/*Retorna a descricao e quatidade de um produto numa dada encomenda*/
void E(encomenda v[], produto u[]){
    int ide, idp, i, j, k;
    scanf("%d:%d", &ide,&idp);
    for(i=0;i<tam_encomendas;i++){
        if(v[i].ident == ide){
            break;
        }
    }
    if(i == tam_encomendas){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    for(k=0;k<tam_produtos;k++){
        if(u[k].identificador == idp){
            break;
        }
    }
    if(k == tam_produtos){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }
    for(j=0;j<v[i].len;j++){
        if(v[i].produto_id[j] == idp){
            printf("%s %d.\n", u[k].descricao, v[i].produto_quantidade[j]);
            return;
        }
    }
    /*se nao encontrar correspondecia no ciclo entao este tem qtd 0 na encomenda*/
    printf("%s %d.\n", u[k].descricao, 0);
    
}


/*Retorna o identificador da encomenda em que um dado produto ocorre mais vezes*/
void m(encomenda v[], produto u[]){
    int idp, i, j, k;
    int ident_min = 0;
    int quantidade = 0;
    scanf("%d", &idp);
    for(i=0;i<tam_produtos;i++){
        if(u[i].identificador == idp){
            break;
        }
    }

    if(i == tam_produtos){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }
    if(tam_encomendas == 0){
        return;
    }
    for(j=0;j<tam_encomendas;j++){
        for(k=0;k<v[j].len;k++){
            /*encontrei o produto*/
            if(v[j].produto_id[k] == idp){
                if(v[j].produto_quantidade[k] > quantidade){
                    ident_min = v[j].ident;
                    quantidade = v[j].produto_quantidade[k];
                }
                if(v[j].produto_quantidade[k] == quantidade && v[j].ident < ident_min){
                    ident_min = v[j].ident;
                }
            }
        }
    }
    if(j == tam_encomendas && quantidade == 0){ /*condicao para verificar que a nao existem encomendas no vetor*/ 
        return;
    }
    printf("Maximo produto %d %d %d.\n", idp, ident_min, quantidade);
    return;


}


/*Lista todos os produtos existentes no sistema por ordem crescente de preco*/
void l(produto v[]){
    produto auxiliar[PRODUTOSMAX];
    int i, b;

    for(i=0;i<tam_produtos;i++){
        /*copiar para um novo vetor os produtos com as componetes nnecessarias para a ordenacao*/
        strcpy(auxiliar[i].descricao, v[i].descricao);
        auxiliar[i].preco = v[i].preco;
        auxiliar[i].quantidade = v[i].quantidade;
    }
    /*ordenar o vetor criado para nao mexer nos indices do vetor dos produtos*/
    mergeSort(auxiliar,0,tam_produtos-1);
    
    printf("Produtos\n");
    for(b=0;b<tam_produtos;b++){
        printf("* %s %d %d\n", auxiliar[b].descricao, auxiliar[b].preco, auxiliar[b].quantidade);
    }
}


/*Lista todos os produtos de uma encomenda por ordem alfabetica de descricao*/
void L(encomenda v[], produto b[]){
    int ide, k, a, i, j;
    produto aux[PRODUTOSMAX];
    scanf("%d", &ide);
    for(k=0;k<tam_encomendas;k++){
        if(v[k].ident == ide){
            break;
        }
    }
    if(k == tam_encomendas){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    /*copiar as componentes necessarias dos produtos para um vetor aux*/
    for(i=0;i<v[k].len;i++){
        for(j=0;j<tam_produtos;j++){
            if(v[k].produto_id[i] == b[j].identificador){
                strcpy(aux[i].descricao, b[j].descricao);
                aux[i].preco = b[j].preco;
                aux[i].quantidade = v[k].produto_quantidade[i];
            }
        }
    }

    /*ordenar o vetor novo para nao mexer com os indices na encomenda*/
    insertionSort_L(aux,0,v[k].len - 1);

    printf("Encomenda %d\n", ide);
    for(a=0;a<v[k].len;a++){
        if(aux[a].quantidade > 0){
            printf("* %s %d %d\n", aux[a].descricao, aux[a].preco, aux[a].quantidade);
        }
    }


}

int main(){
    char c;
    produto sistema[PRODUTOSMAX];
    encomenda sistema_encomendas[ENCOMENDASMAX];
    c = getchar();
    while(c != 'x'){
        switch(c){
            case 'a':
                a(sistema);
                break;
            case 'q':
                q(sistema);
                break;
            case 'N':
                N(sistema_encomendas);
                break;
            case 'A':
                A(sistema_encomendas,sistema);
                break;
            case 'r':
                r(sistema);
                break;
            case 'R':
                R(sistema_encomendas,sistema);
                break;
            case 'C':
                C(sistema_encomendas,sistema);
                break;
            case 'p':
                p(sistema);
                break;
            case 'E':
                E(sistema_encomendas,sistema);
                break;
            case 'm':
                m(sistema_encomendas,sistema);
                break;
            case 'l':
                l(sistema);
                break;
            case 'L':
                L(sistema_encomendas, sistema);
                break;
        }
        c = getchar();
    }
    return 0;
}