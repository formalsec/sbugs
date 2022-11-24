#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_STRING 63
#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define MAX_PRODUTOS_PESO 200

/***********************/
/* Estruturas de Dados */
/***********************/
typedef struct produto{
    int identificador;
    char descricao[MAX_STRING];
    int preco;
    int peso;
    int quantidade;
}PRODUTO;

typedef struct encomenda{
    int identificador;
    int numero_produtos;
    PRODUTO produtos[MAX_PRODUTOS_PESO];
}ENCOMENDA;

/*********************/
/* Variaveis Globais */
/*********************/
/* numero de produtos no sistema */
int idp = 0;

/* numero de encomendas no sistema*/
int ide = 0;

/* vetor que contem todos os produtos do sistema */
PRODUTO vetor_de_produtos[MAX_PRODUTOS];

/* vetor que contem todas as encomendas do sistema */
ENCOMENDA vetor_de_encomendas[MAX_ENCOMENDAS];

/* vetor auxiliar utilizado pelo algoritmo mergesort */
PRODUTO vetor_auxiliar[MAX_PRODUTOS]; 

/**************/
/* Prototipos */
/**************/
void adiciona_produto(char descricao[MAX_STRING], int preco, int peso, int quantidade);
void cria_encomenda();
void adiciona_produto_encomenda(int id_encomenda, int id_produto, int quantidade);
void retorna_descricao_e_quantidade(int id_encomenda, int id_produto);
void adiciona_stock(int id_produto, int quantidade);
void remove_stock(int id_produto, int quantidade);
void calcula_custo_encomenda(int id_encomenda);
void altera_preco_produto(int id_produto, int preco);
void retorna_encomenda_produto_aparece_mais_vezes(int id_produto);
void remove_produto_encomenda(int id_encomenda, int id_produto);
void ordena_por_preco();
void ordena_alfabeticamente(int id_encomenda);
void inicializa_vetor_de_produtos();
void inicializa_vetor_de_encomendas();
int existe_encomenda(int id_encomenda, int id_produto, int flag);
int existe_produto(int id_encomenda, int id_produto, int flag);
int tem_stock(int id_encomenda, int id_produto, int quantidade);
int peso_adequado(int id_encomenda, int id_produto, int quantidade);
int encontra_indice(int id_encomenda, int id_produto);
void reestrutura_produtos_encomenda(int id_encomenda, int indice_a_remover);
void merge(PRODUTO vetor_substituto[MAX_PRODUTOS], int left, int half, int right, int flag);
void mergesort(PRODUTO vetor_substituto[MAX_PRODUTOS], int left, int right, int flag);

/********/
/* main */
/********/
int main(){

    int preco = 0, peso = 0, quantidade = 0;
    int id_encomenda=0, id_produto=0;
    char token, descricao[MAX_STRING];

    inicializa_vetor_de_produtos();
    inicializa_vetor_de_encomendas();

    do{
        token = getchar();
        if(token == 'a'){
            scanf(" %[^':']:%d:%d:%d", descricao, &preco, &peso, &quantidade);
            adiciona_produto(descricao, preco, peso, quantidade);
        }
        if(token == 'q'){
            scanf(" %d:%d", &id_produto, &quantidade);
            adiciona_stock(id_produto, quantidade);
        }
        if(token == 'N'){
            cria_encomenda();
        }
        if(token == 'A'){
            scanf(" %d:%d:%d", &id_encomenda, &id_produto, &quantidade);
            adiciona_produto_encomenda(id_encomenda, id_produto, quantidade);
        }
        if(token == 'r'){
            scanf(" %d:%d", &id_produto, &quantidade);
            remove_stock(id_produto, quantidade);
        }
        if(token == 'R'){
            scanf(" %d:%d", &id_encomenda, &id_produto);
            remove_produto_encomenda(id_encomenda, id_produto);
        }
        if(token == 'C'){
            scanf(" %d", &id_encomenda);
            calcula_custo_encomenda(id_encomenda);
        }
        if(token == 'p'){
            scanf(" %d:%d", &id_produto, &preco);
            altera_preco_produto(id_produto, preco);
        }
        if(token == 'E'){
            scanf(" %d:%d", &id_encomenda, &id_produto);
            retorna_descricao_e_quantidade(id_encomenda, id_produto);
        }
        if(token == 'm'){
            scanf(" %d", &id_produto);
            retorna_encomenda_produto_aparece_mais_vezes(id_produto);
        }
        if(token == 'l'){
            ordena_por_preco();
        }
        if(token == 'L'){
            scanf(" %d", &id_encomenda);
            ordena_alfabeticamente(id_encomenda);
        }
    }while(token != 'x');

    return 0;
}

/**********************/
/* Funcoes Principais */
/**********************/

/*
    Funcao que adiciona um novo produto ao sistema. O produto
    e criado com as caracteristicas passados como argumento da
    funcao e adicionado ao vetor_de_produtos.
*/
void adiciona_produto(char descricao[MAX_STRING], int preco, int peso, int quantidade){

    vetor_de_produtos[idp].identificador = idp;
    strcpy(vetor_de_produtos[idp].descricao, descricao);
    vetor_de_produtos[idp].preco = preco;
    vetor_de_produtos[idp].peso = peso;
    vetor_de_produtos[idp].quantidade = quantidade;
    printf("Novo produto %d.\n", idp);
    idp++;
}


/* 
    Funcao que adiciona stock ao produto cujo id e id_produto,
    se o produto existe no vetor_de_produtos.
*/
void adiciona_stock(int id_produto, int quantidade){

    if(existe_produto(-10, id_produto, 0)){
        vetor_de_produtos[id_produto].quantidade += quantidade;
    }
}


/*
    Funcao que cria uma nova encomenda, adicionando-a
    ao vetor_de_encomendas.
*/
void cria_encomenda(){

    vetor_de_encomendas[ide].identificador = ide;
    vetor_de_encomendas[ide].numero_produtos = 0;
    printf("Nova encomenda %d.\n", ide);
    ide++;
}


/*
    Funcao que adiciona o produto cujo id e id_produto a encomenda
    cujo id e id_encomenda, se a encomenda e o produto existem no 
    sistema, se ha stock suficiente do produto e se a encomenda nao 
    excede o preco maximo. Se o produto ja existir na encomenda, 
    adiciona a nova quantidade a quantidade existente.
*/
void adiciona_produto_encomenda(int id_encomenda, int id_produto, int quantidade){

    int numero_produtos = 0;
    int indice = 0;

    numero_produtos=vetor_de_encomendas[id_encomenda].numero_produtos;
    if(existe_encomenda(id_encomenda, id_produto, 70) && existe_produto(id_encomenda, id_produto, 70) && tem_stock(id_encomenda, id_produto, quantidade) && peso_adequado(id_encomenda, id_produto, quantidade)){
        indice = encontra_indice(id_encomenda, id_produto);
        if(indice == -2){
            vetor_de_encomendas[id_encomenda].produtos[numero_produtos].identificador =  vetor_de_produtos[id_produto].identificador;
            strcpy( vetor_de_encomendas[id_encomenda].produtos[numero_produtos].descricao,vetor_de_produtos[id_produto].descricao);
            vetor_de_encomendas[id_encomenda].produtos[numero_produtos].preco = vetor_de_produtos[id_produto].preco;
            vetor_de_encomendas[id_encomenda].produtos[numero_produtos].peso = (vetor_de_produtos[id_produto].peso * quantidade);
            vetor_de_encomendas[id_encomenda].produtos[numero_produtos].quantidade = quantidade;
                
            vetor_de_encomendas[id_encomenda].numero_produtos++;
                
            remove_stock(id_produto, quantidade);
        }
        else{
            vetor_de_encomendas[id_encomenda].produtos[indice].quantidade += quantidade;
            vetor_de_encomendas[id_encomenda].produtos[indice].peso += (vetor_de_produtos[id_produto].peso * quantidade);

            remove_stock(id_produto, quantidade); 
        }
    }
}


/*
    Funcao que remove stock ao produto cujo id e id_produto, 
    se este existe no sistema e se tem stock suficiente.
*/
void remove_stock(int id_produto, int quantidade){

    if(existe_produto(-20, id_produto, 0) && tem_stock(-20, id_produto, quantidade)){
        vetor_de_produtos[id_produto].quantidade -= quantidade;
    }
}


/*
    Funcao que remove o produto cujo id e id_produto da encomenda
    cujo id e id_encomenda, se o produto e a encomenda existirem 
    no sistema e se o produto existir na encomenda.
    O produto e removido e depois e feita um chamada a uma funcao 
    auxiliar que reestrutura o vetor de produtos da encomenda 
    id_encomenda. 
*/
void remove_produto_encomenda(int id_encomenda, int id_produto){

    int indice_a_remover = 0;
    
    if(existe_encomenda(id_encomenda,id_produto, 170) && existe_produto(id_encomenda,id_produto, 170)){
        indice_a_remover = encontra_indice(id_encomenda, id_produto);    
        if(indice_a_remover != -2 && indice_a_remover >= 0){

            adiciona_stock(id_produto, vetor_de_encomendas[id_encomenda].produtos[indice_a_remover].quantidade);

            reestrutura_produtos_encomenda(id_encomenda, indice_a_remover);

            vetor_de_encomendas[id_encomenda].numero_produtos--;
        }
    }
}


/*
    Funcao que calcula o custo da encomenda cujo id e id_encomenda,
    se esta existe no sistema. O valor apresentado e a soma do custo
    de todos os produtos na encomenda.
*/
void calcula_custo_encomenda(int id_encomenda){

    int custoTotal= 0;
    int counter = 0;

    if(existe_encomenda(id_encomenda, -1000, 0)){
        for(counter = 0; counter < vetor_de_encomendas[id_encomenda].numero_produtos; counter++){
            custoTotal += (vetor_de_encomendas[id_encomenda].produtos[counter].preco * vetor_de_encomendas[id_encomenda].produtos[counter].quantidade);
        }
        printf("Custo da encomenda %d %d.\n", id_encomenda, custoTotal);
    }
}


/*
    Funcao que altera o preco do produto cujo id e id_produto
    se este existe no sistema. A alteracao do preco ocorre quer
    no vetor_de_produtos, quer em todas as encomendas em que
    o produto existe.
*/
void altera_preco_produto(int id_produto, int preco){

    int indice = 0;
    int counter = 0;

    if(existe_produto(-30, id_produto, 0)){
        vetor_de_produtos[id_produto].preco = preco;
        for(counter = 0; counter < ide; counter++){
            indice = encontra_indice(counter, id_produto);
            if(indice != -2){
                vetor_de_encomendas[counter].produtos[indice].preco = preco;
            } 
        }
    }
}


/*
    Funcao que retorna a descricao e a quantidade do produto cujo 
    id e id_produto na encomenda cujo id e id_encomenda. Se o
    produto nao existe na encomenda a quantidade apresentada e 0.
*/
void retorna_descricao_e_quantidade(int id_encomenda, int id_produto){

    int indice = 0;

    if(existe_encomenda(id_encomenda, -900, 0) && existe_produto(-50, id_produto, 0)){
        indice = encontra_indice(id_encomenda, id_produto);
        if(indice == -2){
            printf("%s %d.\n", vetor_de_produtos[id_produto].descricao, 0); 
        }
        else{
            printf("%s %d.\n", vetor_de_encomendas[id_encomenda].produtos[indice].descricao, vetor_de_encomendas[id_encomenda].produtos[indice].quantidade);
        }
    }
}


/*
    Funcao que retorna o identificador da encomenda em que o produto
    cujo id e id_produto ocorre mais vezes. Se houver 2 ou mais
    encomendas nessa situacao, imprime a encomenda de menor id.
*/
void retorna_encomenda_produto_aparece_mais_vezes(int id_produto){

    int quantidade_maxima = 0, id_encomenda = 0, indice= 0;
    int counter = 0, flag = 0;

    if(existe_produto(-40, id_produto, 0)){
        for(counter = 0; counter < ide; counter++){ 
            indice = encontra_indice(counter, id_produto);
            if(indice == -2){
            }
            else{
                if(vetor_de_encomendas[counter].produtos[indice].quantidade > quantidade_maxima){
                    quantidade_maxima = vetor_de_encomendas[counter].produtos[indice].quantidade;
                    id_encomenda = vetor_de_encomendas[counter].identificador;
                    flag = 1;
                }
                else if(vetor_de_encomendas[counter].produtos[indice].quantidade == quantidade_maxima){
                    if(vetor_de_encomendas[counter].identificador < vetor_de_encomendas[id_encomenda].identificador){
                        id_encomenda=counter;
                    }
                }
            }
        }
        if(ide != 0 && flag == 1){
            printf("Maximo produto %d %d %d.\n", id_produto, id_encomenda, quantidade_maxima);
        }
    }
}


/*
    Funcao que  lista todos os produtos existentes no sistema por
    ordem crescente de preco. Se houver 2 ou mais produtos com o 
    mesmo preco, imprime esses produtos por ordem crescente de id 
    de produto. Esta funcao recorre ao algoritmo mergesort e a 
    um vetor igual ao vetor_de_produtos (vetor_substituto) para 
    ordenar e apresentar os resultados.
*/
void ordena_por_preco(){

    PRODUTO vetor_substituto[MAX_PRODUTOS];
    int counter1=0, counter2=0;
    
    for(counter2 = 0; counter2 < idp; counter2++){
        vetor_substituto[counter2].identificador = vetor_de_produtos[counter2].identificador;
        strcpy(vetor_substituto[counter2].descricao, vetor_de_produtos[counter2].descricao);
        vetor_substituto[counter2].preco = vetor_de_produtos[counter2].preco;
        vetor_substituto[counter2].peso = vetor_de_produtos[counter2].peso;
        vetor_substituto[counter2].quantidade = vetor_de_produtos[counter2].quantidade;
    }
    
    mergesort(vetor_substituto, 0, idp-1, 70);
    printf("Produtos\n");
    for(counter1 = 0; counter1 < idp; counter1++){
        printf("* %s %d %d\n", vetor_substituto[counter1].descricao, vetor_substituto[counter1].preco, vetor_substituto[counter1].quantidade); 
    }
}

/*
    Funcao que lista todos os produtos da encomenda cujo id e
    id_encomenda por ordem alfabetica da descricao, se a encomenda
    existir no sistema.
*/
void ordena_alfabeticamente(int id_encomenda){

    int counter = 0;

    if(existe_encomenda(id_encomenda, -800, 0)){

        mergesort(vetor_de_encomendas[id_encomenda].produtos, 0, vetor_de_encomendas[id_encomenda].numero_produtos-1, 170);
        
        printf("Encomenda %d\n", id_encomenda);
        for(counter=0; counter < vetor_de_encomendas[id_encomenda].numero_produtos; counter++){
            printf("* %s %d %d\n", vetor_de_encomendas[id_encomenda].produtos[counter].descricao, vetor_de_encomendas[id_encomenda].produtos[counter].preco, vetor_de_encomendas[id_encomenda].produtos[counter].quantidade); 
        }
    }
}

/**********************/
/* Funcoes Auxiliares */
/**********************/

/* 
    Funcao que inicializa a variavel global vetor_de_produtos
*/
void inicializa_vetor_de_produtos(){

    int counter = 0;

    for(counter = 0; counter < MAX_PRODUTOS; counter++){
        vetor_de_produtos[idp].identificador = -1;
        strcpy(vetor_de_produtos[idp].descricao, "VAZIO"); 
        vetor_de_produtos[idp].preco = -1;
        vetor_de_produtos[idp].peso = -1;
        vetor_de_produtos[idp].quantidade = -1;
    }
}


/* 
    Funcao que inicializa a variavel global vetor_de_encomendas
*/
void inicializa_vetor_de_encomendas(){

    int counter1 = 0, counter2 = 0;

    for(counter1 = 0; counter1 < MAX_ENCOMENDAS; counter1++){
        vetor_de_encomendas[counter1].identificador = -1;
        vetor_de_encomendas[counter1].numero_produtos = 0;
        for(counter2 = 0; counter2 < MAX_PRODUTOS_PESO; counter2++){
            vetor_de_encomendas[counter1].produtos[counter2].identificador = -1;
            strcpy(vetor_de_encomendas[counter1].produtos[counter2].descricao, "VAZIO"); 
            vetor_de_encomendas[counter1].produtos[counter2].preco = -1;
            vetor_de_encomendas[counter1].produtos[counter2].peso = -1;
            vetor_de_encomendas[counter1].produtos[counter2].quantidade = -1;
        }
    }
}


/* 
    Funcao que reestrutura a organizacao dos produtos da encomenda
    cujo id e id_encomenda. A partir do indice do produto que e removido
    recua um indice todos os produtos ainda existentes no vetor, se o produto
    removido nao ocupa o ultimo indice(199).
*/
void reestrutura_produtos_encomenda(int id_encomenda, int indice_a_remover){

    int counter1 = 0, counter2 = 0;

    if(indice_a_remover == 199){
        return;
    }
    else{
        for(counter1 = indice_a_remover, counter2 = 0; counter2 < ((vetor_de_encomendas[id_encomenda].numero_produtos)-indice_a_remover); counter1++, counter2++){
        vetor_de_encomendas[id_encomenda].produtos[counter1].identificador =  vetor_de_encomendas[id_encomenda].produtos[counter1+1].identificador;
        strcpy( vetor_de_encomendas[id_encomenda].produtos[counter1].descricao, vetor_de_encomendas[id_encomenda].produtos[counter1+1].descricao);
        vetor_de_encomendas[id_encomenda].produtos[counter1].preco =  vetor_de_encomendas[id_encomenda].produtos[counter1+1].preco;
        vetor_de_encomendas[id_encomenda].produtos[counter1].peso = vetor_de_encomendas[id_encomenda].produtos[counter1+1].peso;
        vetor_de_encomendas[id_encomenda].produtos[counter1].quantidade = vetor_de_encomendas[id_encomenda].produtos[counter1+1].quantidade;
        }
    }
}


/* 
    Funcao que verifica se a encomenda cujo id e id_encomenda existe
    no sistema, isto e, no vetor_de_encomendas. Faz uso de flags
    para distinguir a sua chamada por diferentes funcoes e devolver
    o codigo de erro adequado, se esse for o caso.
*/
int existe_encomenda(int id_encomenda, int id_produto, int flag){

    int counter = 0;

    for(counter = 0; counter < ide; counter++){
        if(vetor_de_encomendas[counter].identificador == id_encomenda){
            return 1;
        }
    }
    if(id_produto == -1000){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_encomenda);
    }
    else if(id_produto == -900){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_encomenda);
    }
    else if(id_produto == -800){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_encomenda);
    }
    else if(flag == 70){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_produto, id_encomenda);
    }
    else if(flag == 170){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_produto, id_encomenda);
    }
    return 0;
}

/* 
    Funcao que verifica se o produto cujo id e id_produto existe
    no sistema, isto e, no vetor_de_produtos. Faz uso de flags
    para distinguir a sua chamada por diferentes funcoes e devolver
    o codigo de erro adequado, se esse for o caso.
*/
int existe_produto(int id_encomenda, int id_produto, int flag){

    int counter = 0;

    for(counter = 0; counter < idp; counter++){
        if(vetor_de_produtos[counter].identificador == id_produto){
            return 1;
        }
    }
    if(id_encomenda == -10){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id_produto);
    }
    else if(id_encomenda == -20){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_produto);
    }
    else if(id_encomenda == -30){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_produto);
    }
    else if(id_encomenda == -40){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_produto);
    }
    else if(id_encomenda == -50){
        printf("Impossivel listar produto %d. Produto inexistente.\n", id_produto);
    }
    else if(flag == 70){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_produto, id_encomenda);
    }
    else if(flag == 170){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_produto, id_encomenda);
    }
    return 0;
}

/* 
    Funcao que verifica se ha stock do produto cujo id e 
    id_produto, ou seja, se a quantidade em stock do produto 
    e superior a que se quer retirar.
*/
int tem_stock(int id_encomenda, int id_produto, int quantidade){

    if(vetor_de_produtos[id_produto].quantidade >= quantidade)
        return 1;
    if(id_encomenda == -20){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, id_produto);
    }
    else{
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_produto, id_encomenda);
    }
    return 0;
}


/* 
    Funcao que calcula se o peso da encomenda id_encomenda e menor que
    200 quando lhe e adicionado o produto id_produto na quantidade dada.
*/
int peso_adequado(int id_encomenda, int id_produto, int quantidade){

    int pesoEncomenda = 0, pesoTotal = 0;
    int counter = 0;

    for(counter = 0; counter < vetor_de_encomendas[id_encomenda].numero_produtos ; counter++){
        pesoEncomenda += vetor_de_encomendas[id_encomenda].produtos[counter].peso;
    }
    pesoTotal = pesoEncomenda + (vetor_de_produtos[id_produto].peso * quantidade);

    if(pesoTotal <= 200){
        return 1;
    }
    else{
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_produto, id_encomenda);
    }
    return 0;
}


/* 
    Funcao que retorna o indice do produto cujo id e id_produto na 
    encomenda cujo id e id_encomenda. Se o produto nao existe na
    encomenda, retorna -2.
*/
int encontra_indice(int id_encomenda, int id_produto){

    int counter = 0;

    for(counter = 0; counter < MAX_PRODUTOS_PESO; counter++){
        if(vetor_de_encomendas[id_encomenda].produtos[counter].identificador == id_produto){

            return counter;
        }
    }
   return -2;
}

/**************************/
/* Algoritmo de Ordenacao */
/**************************/

/* 
    O codigo de mergesort e partilhado pelas funcoes ordena_por_preco
    e ordena_alfabeticamente. Os criterios de comparacao utilizados
    no codigo de merge pelas 2 funcoes referidas anteriormente 
    sao separados atraves do uso de flags. A primeira compara primeiro
    o preco e, caso este seja igual, compara com base no id do produto (flag=70). 
    A segunda funcao compara alfabeticamente (flag = 170).
*/

/*
    Funcao que constroi o vector auxiliar e vai escolhendo os
    elementos das pontas de forma a ordenar o vetor vetor_substituto
*/
void merge(PRODUTO vetor_substituto[MAX_PRODUTOS], int left, int half, int right, int flag){ 

  int counter1, counter2, counter3;

  for (counter1 = half+1; counter1 > left; counter1--){
    vetor_auxiliar[counter1-1] = vetor_substituto[counter1-1];
  }
  for (counter2 = half; counter2 < right; counter2++){
    vetor_auxiliar[right+half-counter2] = vetor_substituto[counter2+1];
  }
    if(flag==70){
        for (counter3 = left; counter3 <= right; counter3++){
            if (vetor_auxiliar[counter2].preco < vetor_auxiliar[counter1].preco){
                vetor_substituto[counter3] = vetor_auxiliar[counter2--];
            }
            else if(vetor_auxiliar[counter2].preco == vetor_auxiliar[counter1].preco){
                if(vetor_auxiliar[counter2].identificador < vetor_auxiliar[counter1].identificador){
                    vetor_substituto[counter3] = vetor_auxiliar[counter2--];
                }
                else{
                    vetor_substituto[counter3] = vetor_auxiliar[counter1++];   
                }
            }
            else
                vetor_substituto[counter3] = vetor_auxiliar[counter1++]; 
        }
    }
    else if(flag == 170){
         for (counter3 = left; counter3 <= right; counter3++){
            if (strcmp(vetor_auxiliar[counter2].descricao, vetor_auxiliar[counter1].descricao)<0)
                vetor_substituto[counter3] = vetor_auxiliar[counter2--];
            else
                vetor_substituto[counter3] = vetor_auxiliar[counter1++];
         }
    }
}

/*
    Funcao que parte sucessivamente ao meio o vetor de elementos 
    a ordenar, vetor_substituto, ate obter vetores com apenas um
    elemento.
*/
void mergesort(PRODUTO vetor_substituto[MAX_PRODUTOS], int left, int right, int flag) { 

  int half = (right+left)/2;

  if (right <= left)
    return;

  mergesort(vetor_substituto, left, half, flag);
  mergesort(vetor_substituto, half+1, right, flag);
  merge(vetor_substituto, left, half, right, flag);
}