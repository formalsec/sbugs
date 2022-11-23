#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Valor maximo de careteres da string descricao. */
#define MAX_DESCRICAO 64
/* Valor maximo de produtos diferentes. */
#define MAX_PRODUTOS 10000
/* Valor maximo de encomendas diferentes. */
#define MAX_ENCOMENDAS 500
/* Valor maximo de produtos diferentes em cada encomenda. */
#define MAX_P_ENCOMENDAS 200

/* Prototipos das funcoes. */
void sistema_init();
void encomendas_init();
void produtos_init();
void adiciona_novo_produto();                 
void adiciona_stock();
void cria_encomenda();
void adiciona_produto_encomenda();
void remove_stock();
void remove_produto_encomenda();
void custo_encomenda();
void altera_preco();
void descri_quant_produto_encomenda();
void ide_produto_max();
void lista_produtos_sistema();
void lista_produtos_encomenda();

/* Fun??o que cria o tipo produto que representa um produto no sistema de logistica. */
typedef struct produto {

    int idp;
    char descri[MAX_DESCRICAO];
    int preco, peso;
    int qtd;

}produto;


/* Fun??o que cria o tipo encomenda que representa uma encomenda no sistema de logistica. */
typedef struct encomenda{

    int ide;
    produto produtos[MAX_P_ENCOMENDAS];

}encomenda;

/* Variavel global que contabiliza o numero de produtos de um sistema. */
int n_produtos;
/* Variavel global que contabiliza o numero de encomendas de um sistema. */
int n_encomendas;
/* Variavel global que representa o produto correspondente ao argumento inserido pelo utilizador. */
produto p;
/* Variavel global que representa a encomenda correspondente ao argumento inserido pelo utilizador. */
encomenda e;
/* Variavel global que corresponde a um vetor de produtos que representa o inventario. */
produto sistema[MAX_PRODUTOS];
/* Variavel global que que corresponde a um vetor de encomendas e representa todas as encomendas. */
encomenda encomendas[MAX_ENCOMENDAS];
/* Variavel global que corresponde a uma copia do vetor de produtos que representa o inventario. */
produto aux[MAX_PRODUTOS];


/* Funcao que inicializa o vetor sistema, que contem todos os produtos do sistema, a -1. */
void sistema_init(){
    int i;
    for(i = 0; i < MAX_PRODUTOS; i++){
        sistema[i].idp = -1;
    }
}


/* Funcao que inicializa o vetor encomendas, que contem todos as encomendas do sistema, a -1. */
void encomendas_init(){
    int i;
    for(i = 0; i < MAX_ENCOMENDAS; i++){
        encomendas[i].ide = -1;
    }
}


/* Funcao que inicializa o vetor produtos, que representa os produtos de uma encomenda, a -1. */
void produtos_init(){
    int i, j;
    for(i = 0; i < MAX_ENCOMENDAS; i++){
         for(j = 0; j < MAX_P_ENCOMENDAS; j++){
            encomendas[i].produtos[j].idp = -1;
        }
    }
}


/* Funcao que adiciona um novo produto ao sistema de logistica e que retorna o seu identificador. */
void adiciona_novo_produto(){ 
    int i = n_produtos - 1;
    sistema[i].idp = i;
    sistema[i].preco = p.preco;       
    sistema[i].peso = p.peso;
    sistema[i].qtd = p.qtd;
    strcpy(sistema[i].descri, p.descri);

    printf("Novo produto %d.\n", i);
}


/* Funcao que adiciona stock, ou seja, quantidade a um produto existente no sistema. */
void adiciona_stock(){
    if (sistema[p.idp].idp == -1){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", p.idp);
    }
    else{
        sistema[p.idp].qtd += p.qtd;
    }
}


/* Funcao que cria uma nova encomenda, ou seja, adiciona uma encomenda ao sistema de logistica e retorna 
o seu identificador. */
void cria_encomenda(){
    int i = n_encomendas - 1;
    encomendas[i].ide = i;

    printf("Nova encomenda %d.\n", i);
}


/* Funcao que adiciona quantidade de um produto a uma encomenda, quer seja um produto novo ah encomenda ou 
um produto ja existente nela. */
void adiciona_produto_encomenda(){
    int i, k, j, peso_total = 0, a = 0;
    if(encomendas[e.ide].ide == -1){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", p.idp , e.ide); 
    }
    else if(sistema[p.idp].idp == -1){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", p.idp , e.ide);
    }
    else if((sistema[p.idp].idp != -1) && (sistema[p.idp].qtd < p.qtd)){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", p.idp, e.ide);
    }
    else{
        for(i = 0; i < MAX_P_ENCOMENDAS; i++){
            if(encomendas[e.ide].produtos[i].idp != -1){
                peso_total += (encomendas[e.ide].produtos[i].peso * encomendas[e.ide].produtos[i].qtd);
            }
        }
        peso_total = peso_total + (p.qtd * sistema[p.idp].peso);
        
        if(peso_total > MAX_P_ENCOMENDAS){
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", p.idp, e.ide);
        }
        else{
            for(k = 0; k < MAX_P_ENCOMENDAS; k++){
                /* Se o produto estiver na encomenda. */
                if(encomendas[e.ide].produtos[k].idp == p.idp){
                        
                    encomendas[e.ide].produtos[k].qtd += p.qtd;
                    a = 1;
                }
            }
            if(a == 0){
                for(j = 0; j < MAX_P_ENCOMENDAS; j++){
                    /* Se o produto ainda nao estiver na encomenda. */
                    if(encomendas[e.ide].produtos[j].idp == -1){

                        encomendas[e.ide].produtos[j].idp = p.idp;
                        encomendas[e.ide].produtos[j].qtd = p.qtd;
                        strcpy(encomendas[e.ide].produtos[j].descri, sistema[p.idp].descri);
                        encomendas[e.ide].produtos[j].peso = sistema[p.idp].peso;
                        encomendas[e.ide].produtos[j].preco = sistema[p.idp].preco;
                        break;  
                    }
                }
            }
            sistema[p.idp].qtd -= p.qtd;
        }
    }
}


/* Funcao que retorna a descricao e a quantidade de um produto dentro de uma encomenda. */
void descri_quant_produto_encomenda(){
    int i, a = 0;
    if(encomendas[e.ide].ide == -1){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", e.ide);
    }
    else if(sistema[p.idp].idp == -1){
        printf("Impossivel listar produto %d. Produto inexistente.\n", p.idp);
    }
    else{
        for(i = 0; i < MAX_P_ENCOMENDAS; i++){
            if(encomendas[e.ide].produtos[i].idp == p.idp){
                printf("%s %d.\n", sistema[p.idp].descri, encomendas[e.ide].produtos[i].qtd);
                a = 1;
                break;
            }
        }
        if(a != 1){
            printf("%s %d.\n", sistema[p.idp].descri, 0);
        }
    }
}


/* Funcao retorna o custo total de uma encomenda. */
void custo_encomenda(){
    int j, custo_total = 0;
    if(encomendas[e.ide].ide == -1){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", e.ide);
    }
    else{
        for(j = 0; j < MAX_P_ENCOMENDAS; j++){
            if(encomendas[e.ide].produtos[j].idp != -1){
                custo_total += encomendas[e.ide].produtos[j].preco * encomendas[e.ide].produtos[j].qtd;
            }
        }
        printf("Custo da encomenda %d %d.\n", e.ide, custo_total);
    }
}


/* Funcao que remove stock, ou seja, quantidade a um produto do sistema de logistica. */
void remove_stock(){
    if(sistema[p.idp].idp == -1){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", p.idp);
    }
    else if(sistema[p.idp].qtd - p.qtd < 0){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", p.qtd, p.idp);
    }
    else {
        sistema[p.idp].qtd -= p.qtd;
    }
}


/* Funcao que remove um produto de uma encomenda. */
void remove_produto_encomenda(){
    int i; 
    if(encomendas[e.ide].ide == -1){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", p.idp, e.ide);
    }
    else if(sistema[p.idp].idp == -1){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", p.idp, e.ide);
    }
    else{
        for(i = 0; i < MAX_P_ENCOMENDAS; i++){
            if(encomendas[e.ide].produtos[i].idp == p.idp){

                encomendas[e.ide].produtos[i].idp = -1;
                sistema[p.idp].qtd += encomendas[e.ide].produtos[i].qtd;
            }
        }
    }
}


/* Funcao que altera preco de um produto existente no sistema de logistica, inclusive nas encomendas em que 
ele esta. */
void altera_preco(){
    int i, j;
    if(sistema[p.idp].idp == -1){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", p.idp);
    }
    else{
        sistema[p.idp].preco = p.preco;

        for(i = 0; i < n_encomendas; i++){
            for(j = 0; j < MAX_P_ENCOMENDAS; j++){
                if(encomendas[i].produtos[j].idp == p.idp){
                    encomendas[i].produtos[j].preco = p.preco;
                }
            }
        } 
    }
}


/* Funcao que lista o identificador da encomenda em que o produto dado ocorre mais vezes. */
void ide_produto_max(){
    int i, j, a = 0, maior = 0;
    if(sistema[p.idp].idp == -1){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", p.idp);
    }
    else if(n_encomendas != 0){

        for(i = 0; i < n_encomendas; i++){
            for(j = 0; j < MAX_P_ENCOMENDAS; j++){
                
                if(encomendas[i].produtos[j].idp == p.idp) {
                    a = 1;

                    if(encomendas[i].produtos[j].qtd > maior){
                        maior = encomendas[i].produtos[j].qtd;
                        e.ide = encomendas[i].ide;
                    }
                    if((encomendas[i].produtos[j].qtd == maior) && (e.ide > i)) {

                        maior = encomendas[i].produtos[j].qtd;
                        e.ide = i;
                    }
                }
            }
        }
        if(a == 1){
            printf("Maximo produto %d %d %d.\n", p.idp, e.ide, maior);
        }
    }
}


/* Funcao do algoritmo de ordenacao que ordena os produtos do sistema por ordem crescente do seu preco. */
void merge_preco(produto arr[], int l, int m, int r) { 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    produto L[MAX_PRODUTOS], R[MAX_PRODUTOS]; 
    for (i = 0; i < n1; i++){
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j]; 
    }
    i = 0; 
    j = 0;  
    k = l;  
    while (i < n1 && j < n2) { 
        if(L[i].preco <= R[j].preco){
            arr[k] = L[i]; 
            i++; 
        }
        else{ 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
}


/* Funcao do algoritmo de ordenacao que ordena os produtos de uma encomenda por ordem alfabetica da sua 
descricao. */
void merge_descri(produto arr[], int l, int m, int r) { 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    produto L[MAX_P_ENCOMENDAS], R[MAX_P_ENCOMENDAS]; 
    for (i = 0; i < n1; i++){
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j]; 
    }
    i = 0; 
    j = 0;  
    k = l;  
    while (i < n1 && j < n2) { 
        if (strcmp(L[i].descri, R[j].descri) <= 0){  
            arr[k] = L[i]; 
            i++; 
        }
        else{ 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
}


/* Funcao que ordena um vetor de produtos dado. */
void mergeSort(produto arr[], int l, int r, int escolha) { 
    if (l < r) { 
        int m = l + (r - l) / 2; 
        mergeSort(arr, l, m, escolha); 
        mergeSort(arr, m + 1, r, escolha);

        if(escolha == 1){
            merge_preco(arr, l, m, r);
        }
        else{
            merge_descri(arr, l, m ,r);
        } 
    } 
}


/* Funcao que lista por ordem crescente de preco os produtos existentes no sistema. */
void lista_produtos_sistema(){
    int j, i;
    /* Copia dos produtos do vetor sistema para o vetor auxilar, aux. */
    for(j = 0; j < n_produtos; j++){
        aux[j] = sistema[j];               
    }
    mergeSort(aux, 0, n_produtos - 1, 1);           

    printf("Produtos\n");
    for(i = 0; i < n_produtos; i++){
        printf("* %s %d %d\n", aux[i].descri, aux[i].preco, aux[i].qtd);  
    }
}


/* Funcao que lista por ordem alfabetica da descricao os produtos de uma encomenda. */
void lista_produtos_encomenda(){
    int i, j = 0, n_p_encomenda = 0;
    produto a[MAX_P_ENCOMENDAS];
    if(encomendas[e.ide].ide == -1){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", e.ide);
    }
    else{ 
        /* Copia das encomendas do vetor encomendas para um vetor auxiliar, a. */
        for(i = 0; i < MAX_P_ENCOMENDAS; i++){
            if(encomendas[e.ide].produtos[i].idp != -1){
                n_p_encomenda++;
                a[j] = encomendas[e.ide].produtos[i];
                j++;
            } 
        }
        mergeSort(a, 0, n_p_encomenda - 1, 0);

        printf("Encomenda %d\n", e.ide);
        for(i = 0; i < n_p_encomenda; i++){
            printf("* %s %d %d\n", a[i].descri, a[i].preco, a[i].qtd);
        }
    } 
}


/* Funcao principal que executa, consoante o comando inserido, uma operacao de logistica no sistema. */
int main(){
    /* Variavel que representa o comando, ou seja, o primeiro careter inserido pelo utilizador. */
    char comando;
    /* Inicializacao do vetor dos produtos do sistema. */
    sistema_init();
    /* Inicializacao do vetor das encomendas. */
    encomendas_init();
    /* Inicializacao do vetor dos produtos das encomendas. */
    produtos_init();
    while((comando = getchar()) != EOF){
        switch (comando){
            case 'a':
                n_produtos += 1;
                scanf(" %[^:]:%d:%d:%d", p.descri, &p.preco, &p.peso, &p.qtd);
                adiciona_novo_produto();
                break;
            case 'q':
                scanf(" %d:%d", &p.idp, &p.qtd);
                adiciona_stock();
                break;
            case 'N':
                n_encomendas += 1;
                cria_encomenda();
                break;
            case 'A':
                scanf(" %d:%d:%d", &e.ide, &p.idp, &p.qtd);
                adiciona_produto_encomenda();
                break;
            case 'r':
                scanf(" %d:%d", &p.idp, &p.qtd);
                remove_stock();
                break;
            case 'R':
                scanf(" %d:%d", &e.ide, &p.idp);
                remove_produto_encomenda();
                break;
            case'C':
                scanf(" %d", &e.ide);
                custo_encomenda();
                break;
            case'p':
                scanf(" %d:%d", &p.idp, &p.preco);
                altera_preco();
                break;
            case'E':
                scanf(" %d:%d", &e.ide, &p.idp);
                descri_quant_produto_encomenda();
                break;
            case'm':
                scanf(" %d", &p.idp);
                ide_produto_max();
                break;
            case 'l':
                lista_produtos_sistema();
                break;
            case 'L':
                scanf(" %d", &e.ide);
                lista_produtos_encomenda();
                break;
            case 'x':
                return EXIT_SUCCESS;
            default:
                printf("Comando invalido!");
                return EXIT_FAILURE;
        }
        getchar(); 
    }
    return 0;
}
