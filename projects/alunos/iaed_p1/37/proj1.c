#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MAXPROD 500

typedef struct product {
    int id;
    char desc[63];
    int price;
    int weight;
    int amount;
} product;

typedef struct delivery{
    int totalWeight;
    int totalProd;
    /*id ------ amount*/
    int products[MAXPROD][2];

}delivery;
int counterProd = 0;
int counterDel = 0;

product prodList[10000];
delivery delList[500];

int end = 0;


void processInput(char input[]){
    int idtemp, sum, i, ide, idp;
    switch(input[0]){
        case 'a':
            /* Adicao de um produto a lista global */
            strcpy(prodList[counterProd].desc, strtok(input + 2,":"));
            prodList[counterProd].price = atoi(strtok(NULL, ":"));
            prodList[counterProd].weight = atoi(strtok(NULL, ":"));
            prodList[counterProd].amount = atoi(strtok(NULL, ":"));
            printf("Novo produto %d.\n", counterProd);
            prodList[counterProd].id = counterProd;
            counterProd++;
            break;
        case 'q': 
        {
            /*Adicao de stock a um produto*/
            idtemp = atoi(strtok(input + 2, ":"));
            sum = atoi(strtok(NULL, ":"));
            /* ERROS */
            if(!(idtemp < counterProd)){
                printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idtemp);
                break;
            }
            prodList[idtemp].amount += sum;
            break;
        }
            
            
        case 'N':
        {
            /* Adicao de uma encomenda ao sistema */
            delList[counterDel].totalWeight = 0;
            delList[counterDel].totalProd = 0;
            for(i = 0; i < MAXPROD; i++){
                delList[counterDel].products[i][0] = -1;
                delList[counterDel].products[i][1] = -1;
            }
            if(counterDel < 500){
                counterDel++;
            } else{
                /* ERROS */
                printf("Impossivel adicionar mais encomendas.\n");
            }
            printf("Nova encomenda %d.\n", counterDel - 1);
            break;
        }
            
        case 'A':
        {
            /*Adicao de quantidade de um produto a uma encomenda/Insercao de um produto numa encomenda*/
            int qtd, weight, soloweight;
            ide = atoi(strtok(input + 2, ":"));
            idp = atoi(strtok(NULL, ":"));
            qtd = atoi(strtok(NULL, ":"));
            /* ERROS */
            if(!(ide < counterDel)){
                printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp, ide);
                break;
            }
            if(!(idp < counterProd)){
                printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
                break;
            }
            if(prodList[idp].amount < qtd){
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
                break;
            }
            soloweight = (prodList[idp].weight * qtd);
            weight = soloweight + delList[ide].totalWeight;
            if(weight > 200){
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
                break;
            }
            prodList[idp].amount -= qtd;
            delList[ide].totalWeight = weight;
            delList[ide].totalProd++;

            for(i = 0; i < MAXPROD; i++){
                if(delList[ide].products[i][0] == idp){
                   delList[ide].products[i][1] += qtd;
                   break;
                }
                if(delList[ide].products[i][0] == -1){
                   delList[ide].products[i][0] = idp;
                   delList[ide].products[i][1] = qtd;
                   break;
                }
            }
            
            break;
        }
        case 'r':
        {   
            /* Remocao de stock de um produto */
            int quant, temp;
            idp = atoi(strtok(input + 2, ":"));
            quant = atoi(strtok(NULL, ":"));
            /* ERROS */
            if(!(idp < counterProd)){
                printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
                break;
            }
            temp = prodList[idp].amount - quant;
            if(temp < 0){
                printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quant, idp);
                break;
            }
            prodList[idp].amount = temp;
            break;
        }
        case 'R':
        {
            /* Remocao de um produto duma encomenda */
            int j, tempid;
            j = -1;
            ide = atoi(strtok(input + 2, ":"));
            idp = atoi(strtok(NULL, ":"));
            /* ERROS */
            if(!(ide < counterDel)){
                printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp, ide);
                break;
            }
            if(!(idp < counterProd)){
                printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
                break;
            }
            for(i = 0; i < MAXPROD; i++){
                if(delList[ide].products[i][0] == -1){
                    break;
                }
                if(delList[ide].products[i][0] == idp){
                    j = i;
                    prodList[idp].amount += delList[ide].products[i][1];
                    break;
                }
            }
            if(j != -1){
                tempid = delList[ide].products[j][0];
                delList[ide].totalWeight -= prodList[tempid].weight * delList[ide].products[j][1];
                for(i = j; i < MAXPROD; i++){
                    if(i == 199){
                        delList[ide].products[i][0] = -1;
                        delList[ide].products[i][1] = -1;
                    } else {
                        delList[ide].products[i][0] = delList[ide].products[i+1][0];
                        delList[ide].products[i][1] = delList[ide].products[i+1][1];
                    }
                }
            }
            break;
        }   
        case 'C':
        {
            /* Apresentacao do preco total de uma encomenda */
            int num, calc;
            calc = 0;
            ide = atoi(strtok(input + 2, ":"));
            /* ERROS */
            if(!(ide < counterDel)){
                printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
                break;
            }
            for(i = 0; i < MAXPROD; i++){
                num = delList[ide].products[i][0]; /* id of product */
                if(num != -1){
                    calc += (delList[ide].products[i][1] * prodList[num].price);
                } else {
                    break;
                }
            }
            printf("Custo da encomenda %d %d.\n",ide, calc);
            break;
        }
        case 'p':
        {
            /* Alteracao de preco de produto */
            int price;
            idp = atoi(strtok(input + 2, ":"));
            price = atoi(strtok(NULL, ":"));
            /* ERROS */
            if(!(idp < counterProd)){
                printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
                break;
            }
            prodList[idp].price = price;
            break;
        }
        case 'E':
        {   
            /* Apresentacao de um produto pertencente a uma encomenda*/
            int t;
            t = -1;
            ide = atoi(strtok(input + 2, ":"));
            idp = atoi(strtok(NULL, ":"));
            /* ERROS */
            if(!(ide < counterDel)){
                printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
                break;
            }
            if(!(idp < counterProd)){
                printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
                break;
            }
            /* Busca do produto */
            for(i=0; i< MAXPROD; i++){
                if(delList[ide].products[i][0] == -1){
                    break;
                }
                if(delList[ide].products[i][0] == idp){
                    t = i;
                    break;
                }
            }
            if(t == -1){
                printf("%s 0.\n", prodList[idp].desc);
            } else {
                printf("%s %d.\n", prodList[idp].desc, delList[ide].products[t][1]);
            }
            break;
        }
        case 'm':
        {
            /* Procura do identificador de encomenda onde o produto pretendido tem maior numero de unidades*/
            int qua, j, finalid, enc;
            qua = 0;
            finalid = -1;
            idp = atoi(strtok(input + 2, ":"));
            /* ERROS */
            if(!(idp < counterProd)){
                printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
                break;
            }
            /* Passagem por todas as encomendas e respetivos produtos */
            for(i = 0; i < counterDel; i++){
                for(j = 0; j< MAXPROD;j++){
                    if(delList[i].products[j][0] == -1){
                        break;
                    }
                    if(delList[i].products[j][0]  == idp && delList[i].products[j][1] > qua){
                        qua = delList[i].products[j][1];
                        finalid = delList[i].products[j][0];
                        enc = i;
                        break;
                    }
                }
            }
            if(!(finalid == -1)){
                printf("Maximo produto %d %d %d.\n", finalid, enc, qua);
            }
            break;
        }
        case 'l':
        {
            /* Organizacao de produtos por ordem crescente de preco*/
            int pass; 
            product link;
            product * obj;
            obj = (product *)can_fail_malloc(sizeof(product) * counterProd);
            pass = 0;
            for(i = 0; i < counterProd; i++){
                obj[i] = prodList[i];
            }

            /* BUBBLE SORT */
            while (pass == 0){
                pass = 1;
                for (i = 0; i < (counterProd - 1); i++){
                    if(obj[i].price > obj[i + 1].price){
                        link = obj[i];
                        obj[i] = obj[i + 1];
                        obj[i + 1] = link;
                        pass = 0;
                    }
                }
            }
            printf("Produtos\n");
            for (i = 0; i < counterProd; i++){
                printf("* %s %d %d\n",obj[i].desc, obj[i].price, obj[i].amount);
            }
            free(obj);
            break;
        }
        case 'L':
        {
            /* Organizacao de produtos numa encomenda por ordem alfabetica*/
            int tempID, skip, pass, arrSize, tempPrice, tempQuant, tempr;
            char tempDesc[63];
            int * price, * quantity;
            char ** desc;
            price = (int*)can_fail_malloc(sizeof(int) * MAXPROD);
            quantity = (int *)can_fail_malloc(sizeof(int) * MAXPROD);
            desc = (char **)can_fail_malloc(MAXPROD * sizeof(char *));
            for(i=0;i<MAXPROD;i++){
                desc[i] = (char *)can_fail_malloc(63 * sizeof(char));
            }
            ide = atoi(strtok(input + 2, ":"));


            /* ERROS */
            if(!(ide < counterDel)){
                printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
                break;
            }

            /* Associacao dos atributos dos produtos a arrays auxiliares */
            for(i = 0; i<MAXPROD ; i++){
                tempr = delList[ide].products[i][0];
                if(tempr > -1){
                    tempID = delList[ide].products[i][0];
                    price[i] = prodList[tempID].price;
                    quantity[i]= delList[ide].products[i][1];
                    strcpy(desc[i], prodList[tempID].desc);
                    arrSize = i+1;
                } else {
                    break;
                }
            }
            pass = 0;
            skip = 0;
            /* Verifica??o se existem produtos na encomenda */
            if(delList[ide].products[0][0] == -1){
                
                skip = 1;
                pass = 1;
            }


            /*BUBBLE SORT*/

            /* Ate nao terem sido feitas altera?oes aos arrays manter o algoritmo a correr */
            while (pass == 0){
                pass = 1;
                for (i = 0; i < arrSize; i++){
                    if((i + 1) == arrSize){
                        break;
                    }
                    if(strcmp(desc[i], desc[i + 1]) > 0){
                        strcpy(tempDesc, desc[i]);
                        tempPrice = price[i];
                        tempQuant = quantity[i];
                        strcpy(desc[i], desc[i + 1]);
                        price[i] = price[i + 1];
                        quantity[i] = quantity[i + 1];
                        strcpy(desc[i + 1], tempDesc);
                        price[i + 1] = tempPrice;
                        quantity[i + 1] = tempQuant;
                        pass = 0;
                    }   
                    
                }
            }



            /* Caso existam produtos na encomenda imprimir por ordem alfabetica */
            printf("Encomenda %d\n", ide);
            if(skip == 0){
                for (i = 0; i < arrSize; i++){
                    printf("* %s %d %d\n",desc[i], price[i], quantity[i]);
                }
            }


            /* Libertacao de memoria */
            for(i=0;i<MAXPROD;i++){
                free(desc[i]);
            }
            free(desc);
            free(quantity);
            free(price);
            break;
        }
        case 'x':
            end = 1;
    }
}


int main(){
    do{
        char input[500];
        /* Leitura de inputs */
        fgets(input, 499, stdin);
        processInput(input);
    }while(end == 0);
    
    
    return 0;
}
