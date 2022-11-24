#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXPROD 10000
#define MAXENC 500
#define MAXINPUT 256

/*=============== Estruturas =================*/
typedef struct{
    int id;
    char descricao[64];
    int preco;
    int peso;
    int quantStock;
}Produto;

typedef struct{
    int id;
    Produto listCompras[MAXPROD];
    int pesoTotal;
}Encomenda;

/*========== Declaracao de funcoes =========*/
void adicionaProduto();
void adicionaProdEstrutura(Produto prod);
void adicionaStock();
void criaEncomenda();
void colocaProdEncomenda();
void imprimeLstProdutos();
void removeStock();
void alteraPrecoStock();
void listaDescricaoQuantEncomenda();
void calculaCustoEncomenda();
void removeProdEncomenda();
void listaIdpMax();
void imprimelistaComprasAlfabeticamente();
char *ajustaDescricao(Produto prod);

/* Array de estruturas onde s?o guardados os produtos*/
Produto listaProdutos[MAXPROD];
Encomenda listaEncomendas[MAXENC];
int arrayIndexListProdutos = 0;
int arrayIndexListEncomenda = 0;
int arrayIndexListCompras = 0;
int numEncomenda = 0;
int triggerEncomenda = 0;
int triggerIdpZero = 0;
char novaDescricao[MAXINPUT];

/*===================================== CODIGO PRINCIPAL(MAIN) =======================================*/
int main(){

    char comando;

    while(1){
        comando = getchar();
        switch (comando) {
        case 'a':
            adicionaProduto();
            break;
        case 'q':
            adicionaStock();
            break;
        case 'N':
            criaEncomenda();
            break;
        case 'A':
            colocaProdEncomenda();
            break;
        case 'r':
            removeStock();
            break;
        case 'R':
            removeProdEncomenda();
            break;
        case 'C':
            calculaCustoEncomenda();
            break;
        case 'p':
            alteraPrecoStock();
            break;
        case 'E':
            listaDescricaoQuantEncomenda();
            break;
        case 'm':
            listaIdpMax();
            break;
        case 'l':
            imprimeLstProdutos();
            break;
        case 'L':
            imprimelistaComprasAlfabeticamente();
            break;
        case 'x':
            return EXIT_SUCCESS;
        }
    }
    return 0;
}


/*===================================== FUNCOES MENORES ======================================*/
void adicionaProduto(){

    char input[MAXINPUT];
    char * token;
    const char delim[3] = ":";

    Produto novoProduto;

    int counter = 0;

    fgets(input, sizeof(input), stdin);

    token = strtok(input, delim);

    while(token != NULL){
        if(counter == 0){
            strcpy(novoProduto.descricao, token);
        }
        if(counter == 1){
            sscanf(token, "%d", &novoProduto.preco);
        }
        if(counter == 2){
            sscanf(token, "%d", &novoProduto.peso);
        }
        else{
            sscanf(token, "%d", &novoProduto.quantStock);
        }
        counter++;
        token = strtok(NULL, delim);
    }
    ajustaDescricao(novoProduto);
    printf("Novo produto %d.\n", arrayIndexListProdutos);
    adicionaProdEstrutura(novoProduto);
}

void adicionaStock(){

    char input[MAXINPUT];
    char * token;
    
    int count = 0;
    int prodID, prodStock;
    int i;
    int stateConditionIdp = 0;

    fgets(input, sizeof(input), stdin);

    token = strtok(input, ":");

    while(token != NULL){
        if(count == 0){
            sscanf(token, "%d", &prodID);
        }
        else{
            sscanf(token, "%d", &prodStock);
        }
        count++;
        token = strtok(NULL, ":");
    }

    for(i = 0; i < arrayIndexListProdutos; i++){
        if(listaProdutos[i].id == prodID){
            listaProdutos[i].quantStock += prodStock;
            stateConditionIdp = 1;
        }
    }
    if(stateConditionIdp == 0){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prodID);
    }
}

void removeStock(){

    char input[MAXINPUT];
    char * token;

    int counter = 0;
    int i;
    int prodID, prodRemStock;
    int stateConditionIdp = 0;

    fgets(input, sizeof(input), stdin);

    token = strtok(input, ":");

    while(token != NULL){
        if(counter == 0){
            sscanf(token, "%d", &prodID);
        }
        else{
            sscanf(token, "%d", &prodRemStock);
        }
        counter++;
        token = strtok(NULL, ":");
    }

    for(i = 0; i < arrayIndexListProdutos; i++){
        if(listaProdutos[i].id == prodID){
            if(prodRemStock > listaProdutos[i].quantStock){
                printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", prodRemStock, prodID);
                return;
            }
            else{
                listaProdutos[i].quantStock -= prodRemStock;
                stateConditionIdp = 1;
            }
        }
    }
    if(stateConditionIdp == 0){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prodID);
        return;
    }
}

void criaEncomenda(){

    Encomenda novaEncomenda;

    novaEncomenda.id = numEncomenda;
    novaEncomenda.pesoTotal = 0;
    listaEncomendas[numEncomenda] = novaEncomenda;

    arrayIndexListEncomenda++;
    numEncomenda++;
    triggerEncomenda = 1;

    printf("Nova encomenda %d.\n", novaEncomenda.id);
}


void colocaProdEncomenda(){
    char *token;
    char input[MAXINPUT];
    const char delim[2] = ":";

    int counter = 0;
    int ide, idp, quant;
    int i, j;
    int stateConditionIde = 0, stateConditionIdp = 0;

    /*TRATAMENTO DE INPUT*/
    fgets(input, sizeof(input), stdin);

    token = strtok(input, delim);

    while(token != NULL){
        if(counter == 0){
            sscanf(token, "%d", &ide);
        }
        if(counter == 1){
            sscanf(token, "%d", &idp);
        }
        else{
            sscanf(token, "%d", &quant);
        }
        counter++;
        token = strtok(NULL, delim);
    }

    /*VERIFICACOES E RESPETIVOS ERROS*/
    for(i = 0; i < arrayIndexListProdutos; i++){
        if(listaProdutos[i].id == idp){
            if(listaProdutos[i].quantStock != 0){
                if(listaProdutos[i].quantStock < quant){
                    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
                    return;
                }
            }
        }
    }
    /*ADICIONA O PRODUTO A ENCOMENDA VERIFICANDO SE ESTA NAO EXCEDE O PESO MAXIMO*/
    for(i = 0; i < arrayIndexListEncomenda; i++){
        for(j = 0; j < arrayIndexListProdutos; j++){
            if(listaEncomendas[i].id == ide){
                stateConditionIde = 1;
                if(listaEncomendas[i].listCompras[j].id == idp){
                    if(listaProdutos[j].id == idp){
                        stateConditionIdp = 1;
                        if(listaEncomendas[i].pesoTotal + listaProdutos[j].peso * quant > 200 && idp != 0){
                            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
                            return;
                        }
                        else{
                            /*ADICIONA NOVO PRODUTO ? ENCOMENDA CASO SE TRATE DO ID:0*/
                            if(idp == 0){
                                if(listaProdutos[j].quantStock < quant){
                                    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
                                    return;
                                }
                                if(listaEncomendas[i].pesoTotal + listaProdutos[j].peso * quant > 200){
                                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
                                    return;
                                }
                                triggerIdpZero = 1;
                                listaProdutos[j].quantStock -= quant;
                                listaEncomendas[i].listCompras[j].quantStock += quant;
                                listaEncomendas[i].pesoTotal += listaProdutos[j].peso * quant;
                                listaEncomendas[i].listCompras[j].peso = listaProdutos[j].peso;
                                listaEncomendas[i].listCompras[j].preco = listaProdutos[j].preco;
                                strcpy(listaEncomendas[i].listCompras[j].descricao, listaProdutos[j].descricao);
                            }
                            /*INCREMENTA PESO E STOCK DE ELEMENTO JA PRESENTE NA ENCOMENDA*/
                            else{
                                if(listaProdutos[j].quantStock < quant){
                                    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
                                    return;
                                }
                                listaProdutos[j].quantStock -= quant;
                                listaEncomendas[i].listCompras[j].quantStock += quant;
                                listaEncomendas[i].pesoTotal += listaProdutos[j].peso * quant;
                            }
                        }
                    }
                }
                else{
                    if(listaProdutos[j].id == idp && listaEncomendas[i].id == ide){
                        stateConditionIdp = 1;
                        if(listaProdutos[j].quantStock < quant){
                            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
                            return;
                        }
                        if(listaEncomendas[i].pesoTotal + listaProdutos[j].peso * quant > 200){
                            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
                            return;
                        }
                        /*ADICIONA NOVO PRODUTO ? ENCOMENDA*/
                        else{
                            listaProdutos[j].quantStock -= quant;
                            listaEncomendas[i].listCompras[j].quantStock += quant;
                            listaEncomendas[i].pesoTotal += listaProdutos[j].peso * quant;
                            listaEncomendas[i].listCompras[j].id = listaProdutos[j].id;
                            listaEncomendas[i].listCompras[j].preco = listaProdutos[j].preco;
                            listaEncomendas[i].listCompras[j].peso = listaProdutos[j].peso;
                            strcpy(listaEncomendas[i].listCompras[j].descricao, listaProdutos[j].descricao);
                        }
                    }
                }
            }
        }
    }
    /*VERIFICACOES E ERROS*/
    if(stateConditionIde == 0 && stateConditionIdp == 0){
        if(stateConditionIde == 0){
            printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
            return;
        }
    }
    if(stateConditionIdp == 0){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    if(stateConditionIde == 0){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
}

void removeProdEncomenda(){
    char input[MAXINPUT];
    char * token;

    int ide, idp, i, j;
    int counter = 0, stateConditionIde = 0, stateConditionIdp = 0;

    fgets(input, sizeof(input), stdin);
    token = strtok(input, ":");
    while(token != NULL){
        if(counter == 0){
           sscanf(token, "%d", &ide); 
        }
        else{
            sscanf(token, "%d", &idp);
        }
        counter++;
        token = strtok(NULL, ":");
    }

    for(i = 0; i < arrayIndexListProdutos; i++){
        if(listaProdutos[i].id == idp){
            stateConditionIdp = 1;
        }
    }

    for(i = 0; i < arrayIndexListEncomenda; i++){
        for(j = 0; j < arrayIndexListProdutos; j++){
            if(listaEncomendas[i].id == ide){ 
                stateConditionIde = 1;
                if(listaEncomendas[i].listCompras[j].id == idp){
                    listaEncomendas[i].pesoTotal -= listaEncomendas[i].listCompras[j].peso * listaEncomendas[i].listCompras[j].quantStock;
                    listaProdutos[j].quantStock += listaEncomendas[i].listCompras[j].quantStock;
                    listaEncomendas[i].listCompras[j].quantStock = 0;
                    stateConditionIdp = 1;
                }
            }
        }
    }
    if(stateConditionIde == 0){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if(stateConditionIdp == 0){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
}

void listaDescricaoQuantEncomenda(){
    char *token;
    char input[MAXINPUT];

    int counter = 0;
    int ide, idp;
    int i, j;
    int stateConditionIde = 0, stateConditionIdp = 0;

    /*TRATAMENTO DE INPUT*/
    fgets(input, sizeof(input), stdin);

    token = strtok(input, ":");

    while(token != NULL){
        if(counter == 0){
            sscanf(token, "%d", &ide);
        }
        else{
            sscanf(token, "%d", &idp);
        }
        counter++;
        token = strtok(NULL, ":");
    }
    /*LISTA A DESCRICAO E A QUANT DO PRODUTO IDP NA ENCOMENDA IDE*/
    for(i = 0; i < arrayIndexListEncomenda; i++){
        for(j = 0; j < arrayIndexListProdutos; j++){
            if(listaProdutos[j].id == idp){
                stateConditionIdp = 1;
            }
            if(listaEncomendas[i].id == ide){
                    stateConditionIde = 1;
            }
            if(stateConditionIdp == 1 && stateConditionIde == 1){
                if(idp == 0){
                    printf("%s %d.\n",
                        ajustaDescricao(listaProdutos[0]),
                        listaEncomendas[ide].listCompras[0].quantStock);
                    return;
                }
                if(listaEncomendas[ide].listCompras[idp].id == idp){
                        printf("%s %d.\n",
                            ajustaDescricao(listaEncomendas[ide].listCompras[idp]),
                            listaEncomendas[ide].listCompras[idp].quantStock);
                        return;
                }
                else{
                    printf("%s %d.\n",
                        ajustaDescricao(listaProdutos[idp]),
                        listaEncomendas[ide].listCompras[idp].quantStock);
                    return;
                }
            }
        }
    }
    if(stateConditionIdp == 0){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }
    if(stateConditionIde == 0){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
}

void calculaCustoEncomenda(){

    char input[MAXINPUT];
    int ide, i, j; 
    int sum = 0, stateConditionIde = 0;

    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &ide);

    for(i = 0; i < arrayIndexListEncomenda; i++){
        if(ide == 0 && triggerEncomenda == 0){
            printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
            return;
        }
        else if(ide == 0 && triggerEncomenda > 0){
            sum += listaEncomendas[0].listCompras[i].preco * listaEncomendas[0].listCompras[i].quantStock;
            stateConditionIde = 1;

        }
        for(j = 0; j < arrayIndexListProdutos; j++){
            if(listaEncomendas[i].id == ide){
                sum += listaEncomendas[i].listCompras[j].preco * listaEncomendas[i].listCompras[j].quantStock;
                stateConditionIde = 1;
            }
        }
    }
    if(stateConditionIde == 0){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    printf("Custo da encomenda %d %d.\n", ide, sum);
}

void alteraPrecoStock(){
    char input[MAXINPUT];
    char * token;

    int i, j, counter = 0, stateConditionIdp = 0;
    int idp, novoPreco;
    
    fgets(input, sizeof(input), stdin);
    token = strtok(input, ":");

    while(token != NULL){
        if(counter == 0){
            sscanf(token, "%d", &idp);
        }
        else{
            sscanf(token, "%d", &novoPreco);
        }
        counter++;
        token = strtok(NULL, ":");
    }

    for(i = 0; i < arrayIndexListProdutos; i++){
        if(listaProdutos[i].id == idp){
            stateConditionIdp = 1;
            listaProdutos[i].preco = novoPreco;
        }
    }
    for(j = 0; j < arrayIndexListEncomenda; j++){
        if(listaEncomendas[j].listCompras[idp].id == idp){
            listaEncomendas[j].listCompras[idp].preco = novoPreco;
        }
    }
    if(stateConditionIdp == 0){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }
}

void listaIdpMax(){

    char input[MAXINPUT];
    int i, j;
    int idp, indexEnc;
    int max = 0, stateConditionIdp = 0, stateConditionPrint = 0;

    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &idp);


    for(i = 0; i < arrayIndexListProdutos; i++){
        if(listaProdutos[i].id == idp){
            stateConditionIdp = 1;
            break;
        }
    }
    for(i = 0; i < arrayIndexListEncomenda; i++){
        for(j = 0; j < arrayIndexListProdutos; j++){
            if(idp == 0){
                if(triggerIdpZero == 0){
                    return;
                }
                else{
                    if(max < listaEncomendas[i].listCompras[idp].quantStock){
                        max = listaEncomendas[i].listCompras[idp].quantStock;
                        indexEnc = i;
                        stateConditionPrint = 1;
                    }
                }
            }
            else{
                if(listaEncomendas[i].listCompras[j].id == idp){
                    stateConditionPrint = 1;
                    if(max < listaEncomendas[i].listCompras[j].quantStock){
                        max = listaEncomendas[i].listCompras[j].quantStock;
                        indexEnc = i;
                    }
                }
            }
        }
    }
    if(stateConditionIdp == 0){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }
    if(stateConditionPrint == 1){
        printf("Maximo produto %d %d %d.\n", idp, indexEnc, max);
    }
}

void imprimeLstProdutos()
{
    int i, j;
    Produto tmp;

    printf("Produtos\n");
    for(i = 0; i < arrayIndexListProdutos; i++){
        for(j = 0; j < arrayIndexListProdutos - 1; j++){
            if(listaProdutos[j].preco > listaProdutos[j+1].preco){
               tmp = listaProdutos[j+1];
                listaProdutos[j+1] = listaProdutos[j];
                listaProdutos[j] = tmp;
            }
            else if(listaProdutos[j].preco == listaProdutos[j+1].preco){
                if(listaProdutos[j].id > listaProdutos[j+1].id){
                    tmp = listaProdutos[j+1];
                    listaProdutos[j+1] = listaProdutos[j];
                    listaProdutos[j] = tmp;
                }
            }
        }
        printf("*%s %d %d\n",
            listaProdutos[i].descricao,
            listaProdutos[i].preco,
            listaProdutos[i].quantStock);
    }
}

void imprimelistaComprasAlfabeticamente(){

    char input[MAXINPUT];
    int ide, i, stateConditionIde = 0;
    Produto tmp;

    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &ide);

    for(i = 0; i < arrayIndexListProdutos-1; i++){
        if(strcmp(listaEncomendas[ide].listCompras[i].descricao, listaEncomendas[ide].listCompras[i+1].descricao) > 0){
            tmp = listaEncomendas[ide].listCompras[i];
            listaEncomendas[ide].listCompras[i] = listaEncomendas[ide].listCompras[i+1];
            listaEncomendas[ide].listCompras[i+1] = tmp;
        }
        if(ide >= arrayIndexListEncomenda){
            printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
            return;
        }
        if(listaEncomendas[i].id == ide){
            stateConditionIde = 1;
        }
    }
    if(stateConditionIde == 0){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    if(triggerEncomenda != 1){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    printf("Encomenda %d\n", ide);
    for(i = 0; i < arrayIndexListProdutos; i++){
        if(strcmp(listaEncomendas[ide].listCompras[i].descricao, "\0") != 0){
            printf("*%s %d %d\n",
                listaEncomendas[ide].listCompras[i].descricao,
                listaEncomendas[ide].listCompras[i].preco,
                listaEncomendas[ide].listCompras[i].quantStock);
        }
    }
}

/*============================== FUNCOES AUXILIARES =================================*/
void adicionaProdEstrutura(Produto prod)
{
    listaProdutos[arrayIndexListProdutos] = prod;
    listaProdutos[arrayIndexListProdutos].id = arrayIndexListProdutos;
    arrayIndexListProdutos++;
}

char *ajustaDescricao(Produto prod)
{
    int i, len;

    len = strlen(prod.descricao);

    for(i = 0; i < len; i++){
        prod.descricao[i] = prod.descricao[i+1];
    }
    strcpy(novaDescricao, prod.descricao);
    return novaDescricao;
}