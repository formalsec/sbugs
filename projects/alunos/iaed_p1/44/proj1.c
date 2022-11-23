#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUTOS 10000 /*numero maximo de produtos que pode existir no sistema*/
#define MAX_DESC_PRODUTO 63 /*maximo de carateres que a descricao de um produto pode ter*/
#define MAX_ENTRADA 1000 /*numero maximo de carateres que o input pode ter*/
#define MAX_ENCOMENDAS 500 /*numero maximo de encomendas que pode existir no sistema*/
#define MAX_PESO_ENCOMENDA 200 /*peso maximo que uma encomenda pode ter*/
#define ESPACO " " /*carater que separa o comando do restante input*/
#define SEPARADOR ":" /*carater que separa os atributos do input*/
#define NOVA_LINHA "\n" /*carater de nova linha*/

typedef struct produto{     /*define um produto como uma estrutura com 5 atributos*/
    int idp;
    char desc[MAX_DESC_PRODUTO];
    int preco;
    int peso;
    int qtd;
}Produto;

typedef struct encomenda{ /*define uma encomenda como uma estrutura com 2 atributos e um conjunto de produtos*/
    int ide;
    int peso;
    Produto lista_prod[MAX_PESO_ENCOMENDA];
}Encomenda;

Produto lista_produtos[MAX_PRODUTOS];           /*define uma lista de produtos*/
Encomenda lista_encomendas[MAX_ENCOMENDAS];     /*define uma lista de encomendas*/

/*define os comandos*/
void a(char *atr1, char *atr2, char *atr3, char *atr4, Produto lista_produtos[]);
void q(char *atr1, char *atr2, Produto lista_produtos[]);
void N(Encomenda lista_encomendas[]);
void A(char *atr1, char *atr2, char *atr3, Produto lista_produtos[], Encomenda lista_encomendas[]);
void r(char *atr1, char *atr2, Produto lista_produtos[]);
void R(char *atr1, char *atr2, Produto lista_produtos[], Encomenda lista_encomendas[]);
void C(char *atr1, Encomenda lista_encomendas[]);
void p(char *atr1, char *atr2, Produto lista_produtos[], Encomenda lista_encomendas[]);
void E(char *atr1, char *atr2, Produto lista_produtos[], Encomenda lista_encomendas[]);
void m(char *atr1, Produto lista_produtos[], Encomenda lista_encomendas[]);
void l(Produto lista_produtos[]);
void L(char *atr1, Encomenda lista_encomendas[]);

int main(){
    int i, e;
    char *atr1, *atr2, *atr3, *atr4;
    char entrada[MAX_ENTRADA], *comando;
    
    for(i=0; i<MAX_PRODUTOS; i++){                /*inicializa a lista de produtos*/
        lista_produtos[i].idp = -1;               /*com idp a -1, para facilitar comparacoes e lancamento de erros nos diferentes comandos,*/
        strcpy(lista_produtos[i].desc, "NULL");   /*e os restantes atributos do produto a 0*/
        lista_produtos[i].preco = 0;
        lista_produtos[i].peso = 0;
        lista_produtos[i].qtd = 0;
    }
    
    for(i=0; i<MAX_ENCOMENDAS; i++){                /*inicializa a lista de encomendas*/
        lista_encomendas[i].ide = -1;               /*com ide e idp a -1, para facilitar comparacoes e lancamento de erros,*/
        lista_encomendas[i].peso = 0;               /*e os restantes atributos da encomenda a 0*/
        for(e=0; e<MAX_PESO_ENCOMENDA; e++){
            lista_encomendas[i].lista_prod[e].idp = -1;
            strcpy(lista_encomendas[i].lista_prod[e].desc, "NULL");
            lista_encomendas[i].lista_prod[e].preco = 0;
            lista_encomendas[i].lista_prod[e].peso = 0;
            lista_encomendas[i].lista_prod[e].qtd = 0;
        }
    }

    while(1){   /*ciclo infinito para receber input, sai com o comando x*/
        fgets(entrada, MAX_ENTRADA, stdin); /*le uma linha do stdin*/
        comando = strtok(entrada, ESPACO);  /*separa o comado do restante input*/

        switch (*comando)
        {
            case 'a':   /*caso o comando = a, recebe quatro atributos e executa o a*/
                atr1 = strtok(NULL, SEPARADOR);
                atr2 = strtok(NULL, SEPARADOR);
                atr3 = strtok(NULL, SEPARADOR);
                atr4 = strtok(NULL, NOVA_LINHA);
                a(atr1, atr2, atr3, atr4, lista_produtos);
                break;
            case 'q':   /*caso o comando = q, recebe dois atributos e executa o q*/
                atr1 = strtok(NULL, SEPARADOR);
                atr2 = strtok(NULL, NOVA_LINHA);
                q(atr1, atr2, lista_produtos);
                break;
            case 'N':   /*caso o comando = N, executa o N*/
                N(lista_encomendas);
                break;
            case 'A':   /*caso o comando = A, recebe tres atributos e executa o A*/
                atr1 = strtok(NULL, SEPARADOR);
                atr2 = strtok(NULL, SEPARADOR);
                atr3 = strtok(NULL, NOVA_LINHA);
                A(atr1, atr2, atr3, lista_produtos, lista_encomendas);
                break;
            case 'r':   /*caso o comando = r, recebe dois atributos e executa o r*/
                atr1 = strtok(NULL, SEPARADOR);
                atr2 = strtok(NULL,NOVA_LINHA);
                r(atr1, atr2, lista_produtos);
                break;
            case 'R':   /*caso o comando = R, recebe dois atributos e executa o R*/
                atr1 = strtok(NULL, SEPARADOR);
                atr2 = strtok(NULL, NOVA_LINHA);
                R(atr1, atr2, lista_produtos, lista_encomendas);
                break;
            case 'C':   /*caso o comando = C, recebe um atributo e executa o C*/
                atr1 = strtok(NULL, NOVA_LINHA);
                C(atr1, lista_encomendas);
                break;
            case 'p':   /*caso o comando = p, recebe dois atributos e executa o p*/
                atr1 = strtok(NULL, SEPARADOR);
                atr2 = strtok(NULL, NOVA_LINHA);
                p(atr1, atr2, lista_produtos, lista_encomendas);
                break;
            case 'E':   /*caso o comando = E, recebe dois atributos e executa o E*/
                atr1 = strtok(NULL, SEPARADOR);
                atr2 = strtok(NULL, NOVA_LINHA);
                E(atr1, atr2, lista_produtos, lista_encomendas);
                break;
            case 'm':   /*caso o comando = m, recebe um atributo e executa o m*/
                atr1 = strtok(NULL, NOVA_LINHA);
                m(atr1, lista_produtos, lista_encomendas);
                break;
            case 'l':   /*caso o comando = l, executa o l*/
                l(lista_produtos);
                break;
            case 'L':   /*caso o comando = L, recebe um atributo e executa o L*/
                atr1 = strtok(NULL, NOVA_LINHA);
                L(atr1, lista_encomendas);
                break;
            case 'x':   /*caso o comando = x, termina o programa e retorna 0*/
                exit(0);
        }
    }
}

/*comando a - adiciona um novo produto ao sistema na proxima entrada vazia da lista de produtos*/
void a(char *atr1, char *atr2, char *atr3, char *atr4, Produto lista_produtos[]){
    int i=0;
    while(lista_produtos[i].idp != -1){
        i=i+1;
    }
    lista_produtos[i].idp = i;
    strcpy(lista_produtos[i].desc, atr1);
    lista_produtos[i].preco = atoi(atr2);
    lista_produtos[i].peso = atoi(atr3);
    lista_produtos[i].qtd = atoi(atr4);
    printf("Novo produto %d.\n", i);
}

/*comando q - adicona stock a um produto existente no sistema*/
void q(char *atr1, char *atr2, Produto lista_produtos[]){
    if(lista_produtos[atoi(atr1)].idp == -1 ){
        printf("Impossivel adicionar produto %s ao stock. Produto inexistente.\n", atr1);
    }
    else{
        lista_produtos[atoi(atr1)].qtd += atoi(atr2);
    }
}

/*comando N - cria uma nova encomenda na proxima entrada vazia da lista de encomendas*/
void N(Encomenda lista_encomendas[]){ 
    int i=0;
    
    while(lista_encomendas[i].ide != -1){
        i=i+1;
    }
    lista_encomendas[i].ide = i;
    printf("Nova encomenda %d.\n", i);
}

/*comando A - adiciona um produto a uma encomenda ou, caso o produto j? exista na encomenda,
adiciona stock desse produto a encomenda*/
void A(char *atr1, char *atr2, char *atr3, Produto lista_produtos[], Encomenda lista_encomendas[]){
    int i=0, peso_total=0, ja_existe = 0;
    peso_total = lista_encomendas[atoi(atr1)].peso + (lista_produtos[atoi(atr2)].peso * atoi(atr3));
    if(lista_encomendas[atoi(atr1)].ide == -1){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", atoi(atr2), atoi(atr1));
    }
    else if(lista_produtos[atoi(atr2)].idp == -1){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", atoi(atr2), atoi(atr1));
    }
    else if(lista_produtos[atoi(atr2)].qtd < (atoi(atr3))){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", atoi(atr2), atoi(atr1));
    }
    else if(peso_total > MAX_PESO_ENCOMENDA){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", atoi(atr2), atoi(atr1));
    }
    else{
        for(i=0; i<MAX_PESO_ENCOMENDA; i++){
            if(lista_encomendas[atoi(atr1)].lista_prod[i].idp == atoi(atr2)){
                ja_existe=1;
            }
        }
        if(ja_existe == 1){
            i=0;
            while(lista_encomendas[atoi(atr1)].lista_prod[i].idp != atoi(atr2)){
                i=i+1;
            }
            lista_encomendas[atoi(atr1)].peso = peso_total;
            lista_encomendas[atoi(atr1)].lista_prod[i].qtd += atoi(atr3);
            lista_produtos[atoi(atr2)].qtd -= atoi(atr3);
        }
        else{
            i=0;
            while(lista_encomendas[atoi(atr1)].lista_prod[i].idp != -1){
                i=i+1;
            }
            lista_encomendas[atoi(atr1)].peso = peso_total;
            lista_encomendas[atoi(atr1)].lista_prod[i].idp = lista_produtos[atoi(atr2)].idp;
            strcpy(lista_encomendas[atoi(atr1)].lista_prod[i].desc, lista_produtos[atoi(atr2)].desc);
            lista_encomendas[atoi(atr1)].lista_prod[i].preco = lista_produtos[atoi(atr2)].preco;
            lista_encomendas[atoi(atr1)].lista_prod[i].peso = lista_produtos[atoi(atr2)].peso;
            lista_encomendas[atoi(atr1)].lista_prod[i].qtd = atoi(atr3);
            lista_produtos[atoi(atr2)].qtd -= atoi(atr3);
        }
    }
}

/*comando r - remove stock a um produto existente no sistema*/
void r(char *atr1, char *atr2, Produto lista_produtos[]){
    int qtd_final = lista_produtos[atoi(atr1)].qtd - atoi(atr2);
    if(lista_produtos[atoi(atr1)].idp == -1){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", atoi(atr1));
    }
    else if(qtd_final < 0){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", atoi(atr2), atoi(atr1));
    }
    else{
        lista_produtos[atoi(atr1)].qtd -= atoi(atr2);
    }
}

/*comando R - remove um produto de uma encomenda*/
void R(char *atr1, char *atr2, Produto lista_produtos[], Encomenda lista_encomendas[]){
    int i, j;
    if(lista_encomendas[atoi(atr1)].ide == -1){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", atoi(atr2), atoi(atr1));
    }
    else if(lista_produtos[atoi(atr2)].idp == -1){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", atoi(atr2), atoi(atr1));
    }
    else{
        for(i=0; i<MAX_PESO_ENCOMENDA; i++){
            if(lista_encomendas[atoi(atr1)].lista_prod[i].idp == atoi(atr2)){
                while(lista_encomendas[atoi(atr1)].lista_prod[i].idp != atoi(atr2)){
                    i=i+1;
                }
                lista_produtos[atoi(atr2)].qtd += lista_encomendas[atoi(atr1)].lista_prod[i].qtd;
                lista_encomendas[atoi(atr1)].peso -= (lista_encomendas[atoi(atr1)].lista_prod[i].peso*lista_encomendas[atoi(atr1)].lista_prod[i].qtd);
                for(j = i; j<MAX_PESO_ENCOMENDA-1; j++){
                    if(lista_encomendas[atoi(atr1)].lista_prod[j+1].idp != -1){
                        lista_encomendas[atoi(atr1)].lista_prod[j].idp = lista_encomendas[atoi(atr1)].lista_prod[j+1].idp;
                        strcpy(lista_encomendas[atoi(atr1)].lista_prod[j].desc, lista_encomendas[atoi(atr1)].lista_prod[j+1].desc);
                        lista_encomendas[atoi(atr1)].lista_prod[j].preco = lista_encomendas[atoi(atr1)].lista_prod[j+1].preco;
                        lista_encomendas[atoi(atr1)].lista_prod[j].peso = lista_encomendas[atoi(atr1)].lista_prod[j+1].peso;
                        lista_encomendas[atoi(atr1)].lista_prod[j].qtd = lista_encomendas[atoi(atr1)].lista_prod[j+1].qtd;
                    }
                    else{
                        lista_encomendas[atoi(atr1)].lista_prod[j].idp = -1;
                        strcpy(lista_encomendas[atoi(atr1)].lista_prod[j].desc, "NULL");
                        lista_encomendas[atoi(atr1)].lista_prod[j].preco = 0;
                        lista_encomendas[atoi(atr1)].lista_prod[j].peso = 0;
                        lista_encomendas[atoi(atr1)].lista_prod[j].qtd = 0;
                    }
                }
            }
        }
    }
}

/*comando C - calcula o custo de uma encomenda e retorna ao utilizador*/
void C(char *atr1, Encomenda lista_encomendas[]){
    int i, custo=0;
    if(lista_encomendas[atoi(atr1)].ide == -1){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", atoi(atr1));
    }
    else{
        for(i=0; i<MAX_PESO_ENCOMENDA; i++){
            if(lista_encomendas[atoi(atr1)].lista_prod[i].idp != -1){
                custo+= (lista_encomendas[atoi(atr1)].lista_prod[i].preco * lista_encomendas[atoi(atr1)].lista_prod[i].qtd);
            }
        }
        printf("Custo da encomenda %d %d.\n", atoi(atr1), custo);
    }
}

/*comando p - altera o preco de um produto existente no sistema*/
void p(char *atr1, char *atr2, Produto lista_produtos[], Encomenda lista_encomendas[]){
    int i, e;
    if(lista_produtos[atoi(atr1)].idp == -1){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", atoi(atr1));
    }
    else{
        for(i=0; i<MAX_ENCOMENDAS;i++){
            for(e=0;e<MAX_PESO_ENCOMENDA;e++){
                if(lista_encomendas[i].lista_prod[e].idp == atoi(atr1)){
                    lista_encomendas[i].lista_prod[e].preco = atoi(atr2);
                }
            }
        }
        lista_produtos[atoi(atr1)].preco = atoi(atr2);
    }
}

/*comando E - lista a descricao e a quantidade de um produto numa encomenda*/
void E(char *atr1, char *atr2, Produto lista_produtos[], Encomenda lista_encomendas[]){
    int i, existe = 0;
    if(lista_encomendas[atoi(atr1)].ide == -1){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(atr1));
    }
    else if(lista_produtos[atoi(atr2)].idp == -1){
        printf("Impossivel listar produto %d. Produto inexistente.\n", atoi(atr2));
    }
    else{
        for(i=0; i<MAX_PESO_ENCOMENDA; i++){
            if(lista_encomendas[atoi(atr1)].lista_prod[i].idp == atoi(atr2)){
                existe=1;
            }
        }
        if(existe == 1){
            i=0;
            while(lista_encomendas[atoi(atr1)].lista_prod[i].idp != atoi(atr2)){
                i=i+1;
            }
            printf("%s %d.\n",lista_produtos[atoi(atr2)].desc, lista_encomendas[atoi(atr1)].lista_prod[i].qtd);
        } 
        else{
            printf("%s 0.\n", lista_produtos[atoi(atr2)].desc);
        }
    }
}

/*comando m - lista o id da encomenda em que o produto dado ocorre mais vezes
se houver mais que uma encomenda com a mesma quantidade desse produto
imprime a encomenda de menor id*/
void m(char *atr1, Produto lista_produtos[], Encomenda lista_encomendas[]){
    int i, e, max=0, ide=-1;
    if(lista_produtos[atoi(atr1)].idp == -1){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", atoi(atr1));
    }
    else{
        for(i=0; i<MAX_ENCOMENDAS; i++){
            for(e=0;e<MAX_PESO_ENCOMENDA; e++){
                if(lista_encomendas[i].lista_prod[e].idp == atoi(atr1)){
                    if(lista_encomendas[i].lista_prod[e].qtd == max){
                        max=max;
                        ide=ide;
                    }
                    else if(lista_encomendas[i].lista_prod[e].qtd < max){
                        max = max;
                        ide=ide;
                    }
                    else{
                        max= lista_encomendas[i].lista_prod[e].qtd;
                        ide = lista_encomendas[i].ide;
                    }
                }
            }
        }
        if(max!= 0 && ide != -1){
            printf("Maximo produto %d %d %d.\n", atoi(atr1), ide, max);
        }
    }
}

/*comando l - lista todos os produtos existentes no sistema por ordem crescente de preco
se houver mais que um produto com o mesmo id, imprime por ordem crescente de id*/
void l(Produto lista_produtos[]){
    int i, j;
    Produto p;
    for(i=0; i<MAX_PRODUTOS-1; i++){
        for(j=1; j<MAX_PRODUTOS-i-1; j++){
            if(lista_produtos[i].idp != -1 && lista_produtos[i+j].idp != -1){
                if(lista_produtos[i].preco > lista_produtos[i+j].preco){
                    p= lista_produtos[i];
                    lista_produtos[i] = lista_produtos[i+j];
                    lista_produtos[i+j]= p;
                }
            }
        }
    }
    printf("Produtos\n");
    for(i=0; i<MAX_PRODUTOS; i++){
        if(lista_produtos[i].idp != -1){
            printf("* %s %d %d\n", lista_produtos[i].desc, lista_produtos[i].preco, lista_produtos[i].qtd);
        }      
    }
}

/*comando L - lista todos os produtos existentes numa encomenda por ordem alfabetica de descricao*/
void L(char *atr1, Encomenda lista_encomendas[]){
    int i, j;
    Produto p;
    if(lista_encomendas[atoi(atr1)].ide == -1){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(atr1));
    }
    else{
        for(i=0; i<MAX_PESO_ENCOMENDA-1; i++){
            for(j=1; j< MAX_PESO_ENCOMENDA-i-1; j++){
                if(lista_encomendas[atoi(atr1)].lista_prod[i].idp != -1 && lista_encomendas[atoi(atr1)].lista_prod[i+j].idp != -1){
                    if(strcmp(lista_encomendas[atoi(atr1)].lista_prod[i].desc, lista_encomendas[atoi(atr1)].lista_prod[i+j].desc) > 0){
                        p= lista_encomendas[atoi(atr1)].lista_prod[i];
                        lista_encomendas[atoi(atr1)].lista_prod[i] = lista_encomendas[atoi(atr1)].lista_prod[i+j];
                        lista_encomendas[atoi(atr1)].lista_prod[i+j] = p;
                    }
                }
            }
            
        }
        printf("Encomenda %d\n", atoi(atr1));
        for(i=0; i<MAX_PESO_ENCOMENDA; i++){
            if(lista_encomendas[atoi(atr1)].lista_prod[i].idp != -1){
                printf("* %s %d %d\n", lista_encomendas[atoi(atr1)].lista_prod[i].desc, lista_encomendas[atoi(atr1)].lista_prod[i].preco, lista_encomendas[atoi(atr1)].lista_prod[i].qtd);
            }
        }
    }
}