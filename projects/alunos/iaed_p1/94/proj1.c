#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/*Indice i de cada vetor do tipo 'encomenda.produtos[x][i]' onde se localiza o indice do produto.*/
#define IDP 0
/*Indice i de cada vetor do tipo 'encomenda.produtos[x][i]' 
onde se localiza a quantidade do produto na encomenda.*/
#define QTD 1
/*Valor devolvido pela funcao 'idp_na_encomenda' 
caso nao exista um produto com o indice idp na encomenda de indice ide*/
#define NOT_FOUND -1

/*
Estrutura 'produto':
    -idp: indice do produto no vetor 'vet_produtos';
    -preco: preco atual do produto;
    -peso: peso do produto;
    -qtd: quantidade do produto em stock nao reservado a encomendas;
    -des: descricao do produto;
*/
typedef struct{
    int idp, preco, peso, qtd;
    char des[64];
}produto;

/*
Estrutura 'encomenda':
    -count: contador do numero de produtos diferentes reservados para encomenda;
    -produtos: matriz de 200 linhas e duas colunas. Cada linha, x, guarda 2 valores relativos a um produto:
        *produtos[x][IDP]: o indice do produto no vetor 'vet_produtos';
        *produtos[x][QTD]: a quantidade do produto reservada para encomenda;
*/
typedef struct{
    int count, produtos[200][2]; 
}encomenda;

/*Numero atual de produtos registados no sistema.*/
int prod_count;
/*Numero atual de encomendas registadas no sistema.*/
int enc_count;
/*Vetor que armazena todos os produtos registados no sistema.*/
produto vet_produtos[10000];
/*Vetor que armazena todas as encomendas registadas no sistema.*/
encomenda vet_encomendas[500];

/*
Funcao 'copia_vetores_int':
    Argumentos - dois vetores de inteiros e um inteiro correspondente ao seu tamanho;
    Descricao - copia os valores 'vetor_2' para o 'vetor_1';
    Valor de Retorno - void;
*/
void copia_vetores_int(int vetor_1[], int vetor_2[], int size){
    int i;
    for (i = 0; i < size; ++i)
        vetor_1[i] = vetor_2[i];
}

/*
Funcao 'copia_vetores_prod':
    Argumentos - dois vetores de produtos e um inteiro correspondente ao seu tamanho;
    Descricao - copia os valores do 'vetor_2' para o 'vetor_1';
    Valor de Retorno - void;
*/
void copia_vetores_prod(produto vetor_1[], produto vetor_2[], int size){
    int i;
    for (i = 0; i < size; ++i)
        vetor_1[i] = vetor_2[i];
}

/*
Funcao 'idp_na_encomenda':
    Argumentos - um indice de encomenda e um indice de produto;
    Descricao - procura pelo produto idp na encomenda ide;
    Valor de Retorno - um inteiro correspondente ao indice do produto idp na encomenda ide. 
                       Caso este produto nao exista na encomenda o valor de retorno e NOT_FOUND;
*/
int idp_na_encomenda(int ide, int idp){
    int i;

    for (i = 0; i < vet_encomendas[ide].count; ++i){
        if (idp == vet_encomendas[ide].produtos[i][IDP])
            return i;
    }

    return NOT_FOUND;
}

/*
Funcao 'peso_encomenda':
    Argumento - um indice de encomenda;
    Descricao - Calcula o peso total da encomenda ide;
    Valor de Retorno - um long correspondente ao peso total da encomenda ide;
*/
long peso_encomenda(int ide){
    int i;
    long total = 0;

    for (i = 0; i < vet_encomendas[ide].count; ++i)
        total += (vet_produtos[vet_encomendas[ide].produtos[i][IDP]].peso * vet_encomendas[ide].produtos[i][QTD]);
    
    return total;
}

/*
Funcao 'merge_prod':
    Argumentos - um vetor de produtos e tres indices: o esquerdo, o do meio e o direito;
    Descricao - realiza o processo de merge do algoritmo Merge Sort no vetor de produtos 'a' 
                entre os "sub-vetores" que vao de a[left] a a[m] e de a[m + 1] a a[right].
                A ordenacao e feita por preco e em caso de empate e escolhido o produto com menor indice;
    Valor de Retorno - void;
*/
void merge_prod(produto a[10000], int left, int m, int right){
    int i, j, l;
    produto aux[10000];


    for (i = m + 1; i > left; --i)
        aux[i - 1] = a[i - 1];


    for (j = m; j < right; ++j)
        aux[right + m - j] = a[j + 1];


    for(l = left; l <= right; ++l){
        if (aux[j].preco < aux[i].preco)
            a[l] = aux[j--];

        else if (aux[j].preco > aux[i].preco)
            a[l] = aux[i++];

        else if (aux[j].idp < aux[i].idp)
            a[l] = aux[j--];

        else
            a[l] = aux[i++];
    }
}

/*
Funcao 'merge_sort_prod':
    Argumentos - um vetor de produtos e dois indices: o esquerdo e o direito;
    Descricao - realizao algoritmo de ordenacao Merge Sort para o vetor 'a' 
                entre o o indice 'left' e o indice 'right';
    Valor de Retorno - void;
*/
void merge_sort_prod(produto a[10000], int left, int right){
    int m = (right + left)/2;

    if (right <= left)
        return;

    merge_sort_prod(a, left, m);
    merge_sort_prod(a, m + 1, right);
    merge_prod(a, left, m, right);
}

/*
Funcao 'merge_enc':
    Argumentos - uma matriz de inteiros e tres indices: o esquerdo, o do meio e o direito;
    Descricao - realiza o processo de merge do algoritmo Merge Sort na matriz de inteiros 'a' entre 
                as "sub-matrizes" que vao de a[left] a a[m] e de a[m + 1] a a[right]. A ordenacao 
                entre dois vetores x e y e feita comparando as descricoes dos produtos com indice 
                a[x][IDP] e a[y][IDP] e escolhendo o que vem primeiro por ordem alfabetica;
    Valor de Retorno - void;

*/
void merge_enc(int a[199][2], int left, int m, int right){
    int i, j, l, aux[199][2];

    for (i = m + 1; i > left; --i)
        copia_vetores_int(aux[i - 1], a[i - 1], 2);


    for (j = m; j < right; ++j)
        copia_vetores_int(aux[right + m - j], a[j + 1], 2);


    for (l = left; l <= right; ++l){
        if (strcmp(vet_produtos[aux[i][IDP]].des,  vet_produtos[aux[j][IDP]].des) > 0){
            copia_vetores_int(a[l], aux[j], 2);
            --j;
        }

        else{
            copia_vetores_int(a[l], aux[i], 2);
            ++i;
        }
    }
}

/*
Funcao 'merge_sort_enc':
    Argumentos - uma matriz de inteiros e dois indices: o esquerdo e o direito;
    Descricao - realiza o algoritmo de ordenacao Merge Sort para a matriz 'a' 
                entre o o indice 'left' e o indice 'right';
    Valor de Retorno - void;
*/
void merge_sort_enc(int a[199][2], int left, int right){
    int m = (left + right)/2;

    if (left >= right)
        return;

    merge_sort_enc(a, left, m);
    merge_sort_enc(a, m + 1, right);
    merge_enc(a, left, m, right);
}

/*
Comando 'a':
    Descricao - adiciona um novo produto ao sistema.
*/
void a(){
    produto prod;
    getchar();
    scanf("%[^:]:%d:%d:%d", prod.des, &prod.preco, &prod.peso, &prod.qtd);
    prod.idp = prod_count;
    vet_produtos[prod_count] = prod;
    printf("Novo produto %d.\n", prod_count);
    ++prod_count;
}

/*
Comando 'q':
    Descricao - adiciona stock a um produto existente no sistema.
*/
void q(){
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);

    if (idp >= prod_count)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else
        vet_produtos[idp].qtd += qtd;
}

/*
Comando 'N':
    Descricao - cria uma nova encomenda.
*/
void N(){
    printf("Nova encomenda %d.\n", enc_count);
    ++enc_count;
}

/*
Comando 'A':
    Descricao - adiciona um produto a uma encomenda.
*/
void A(){
    int ide, idp, qtd, i;
    scanf("%d:%d:%d", &ide, &idp, &qtd);
    
    if (ide >= enc_count)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    
    else if (idp >= prod_count)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    
    else if (vet_produtos[idp].qtd < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    
    else if ((peso_encomenda(ide) + (vet_produtos[idp].peso * qtd)) > 200)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    
    else{
        if ((i = idp_na_encomenda(ide, idp)) != NOT_FOUND)
            vet_encomendas[ide].produtos[i][QTD] += qtd;
        
        else{
            vet_encomendas[ide].produtos[vet_encomendas[ide].count][IDP] = idp;
            vet_encomendas[ide].produtos[vet_encomendas[ide].count][QTD] = qtd;
            ++vet_encomendas[ide].count;
        }
        vet_produtos[idp].qtd -= qtd;
    }   
}

/*
Comando 'r':
    Descricao - remove stock a um produto existente.
*/
void r(){
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);

    if (idp >= prod_count)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    
    else if (qtd > vet_produtos[idp].qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    
    else
        vet_produtos[idp].qtd -= qtd;
}

/*
Comando 'R':
    Descricao - remove um produto de uma encomenda.
*/
void R(){
    int ide, idp, i;
    scanf("%d:%d", &ide, &idp);
    
    if (ide >= enc_count)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    
    else if (idp >= prod_count)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    
    else if ((i = idp_na_encomenda(ide, idp)) != NOT_FOUND){
        vet_produtos[idp].qtd += vet_encomendas[ide].produtos[i][QTD];
        
        for (; i < vet_encomendas[ide].count; ++i)
            copia_vetores_int(vet_encomendas[ide].produtos[i],vet_encomendas[ide].produtos[i + 1], 2);
        
        --vet_encomendas[ide].count;
    }
}

/*
Comando 'C':
    Descricao - calcula o custo de uma encomenda.
*/
void C(){
    int ide, i;
    long preco = 0;
    scanf("%d", &ide);

    if (ide >= enc_count)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    
    else{
        for (i = 0; i < vet_encomendas[ide].count; ++i)
            preco += vet_encomendas[ide].produtos[i][QTD] * vet_produtos[vet_encomendas[ide].produtos[i][IDP]].preco;
        
        printf("Custo da encomenda %d %ld.\n", ide, preco);
    }
}

/*
Comando 'p':
    Descricao - altera o preco de um produto existente no sistema.
*/
void p(){
    int idp, preco;
    scanf("%d:%d", &idp, &preco);
    
    if (idp >= prod_count)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    
    else
        vet_produtos[idp].preco = preco;
}

/*
Comando 'E':
    Descricao - retorna a descricao e a quantidade de um produto numa dada encomenda.
*/
void E(){
    int ide, idp, i;
    scanf("%d:%d", &ide, &idp);
    
    if (ide >= enc_count)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    
    else if (idp >= prod_count)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    
    else{
        if ((i = idp_na_encomenda(ide, idp)) != NOT_FOUND)
            printf("%s %d.\n", vet_produtos[idp].des, vet_encomendas[ide].produtos[i][QTD]);
        
        else
            printf("%s 0.\n", vet_produtos[idp].des);
    }
    
}

/*
Comando 'm':
    Descricao - retorna o identificador da encomenda em que um dado produto ocorre mais vezes.
*/
void m(){
    int idp, maior = 0, ide = NOT_FOUND, i, j;
    scanf("%d", &idp);
    if (idp >= prod_count)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    
    else{
        for (i = 0; i < enc_count; ++i)
            if ((j = idp_na_encomenda(i, idp)) != NOT_FOUND && vet_encomendas[i].produtos[j][QTD] > maior){
                    maior = vet_encomendas[i].produtos[j][QTD];
                    ide = i;
            }
        
        if (ide != NOT_FOUND)
            printf("Maximo produto %d %d %d.\n", idp, ide, maior);
    }
}

/*
Comando 'l':
    Descricao - lista todos os produtos existentes no sistema por ordem crescente de preco.
*/
void l(){
    int i;
    produto vet_prod_copia[10000];
    copia_vetores_prod(vet_prod_copia, vet_produtos, prod_count);
    merge_sort_prod(vet_prod_copia, 0, prod_count - 1);
    printf("Produtos\n");
    
    for (i = 0; i < prod_count; ++i){
        printf("* %s %d %d\n", vet_prod_copia[i].des, vet_prod_copia[i].preco, vet_prod_copia[i].qtd);
    }
}

/*
Comando 'L':
    Descricao - lista todos os produtos de uma encomenda por ordem alfabetica da descricao.
*/
void L(){
    int ide, i, copia_enc[199][2];
    
    scanf("%d", &ide);
    if (ide >= enc_count)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    
    else{
        for (i = 0; i < vet_encomendas[ide].count; ++i){
            copia_enc[i][IDP] = vet_encomendas[ide].produtos[i][IDP];
            copia_enc[i][QTD] = vet_encomendas[ide].produtos[i][QTD];
        }
        
        merge_sort_enc(copia_enc, 0, vet_encomendas[ide].count - 1);
        printf("Encomenda %d\n", ide);
        
        for (i = 0; i < vet_encomendas[ide].count; ++i){
            printf("* %s %d %d\n", vet_produtos[copia_enc[i][IDP]].des, vet_produtos[copia_enc[i][IDP]].preco, copia_enc[i][QTD]);
        }
    }
}


/*
Funcao 'main':
    Descricao - o main trata-se de um loop que identifica que comando foi inserido e chama a 
                funcao adequada, ate ser inserido o comando x.
*/
int main(){
    int c;
    while ((c = getchar()) != 'x'){
        switch (c){
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
        }
    }
    return 0;
}