#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT 9O
#define PRODUCTOS 10000
#define ENCOMENDAS 500
#define DESCRICAO 64
#define PESO 200

typedef struct produto{
    int id;
    int preco;
    int peso;
    int quantidade;
    char descricao[DESCRICAO];
}produto;

/* vetor de produtos */
produto produtos[PRODUCTOS];
int nr_produtos;

typedef struct produto_enc{
    int id;
    char descricao[64];
}produto_enc;

typedef struct encomenda{
    int nr_produtos;
    int peso;
    produto_enc produtos[PESO];
    int quantidades[PRODUCTOS];
}encomenda;

/*vetor de encomendas */
encomenda encomendas[ENCOMENDAS];
int nr_encomendas;

/* devolve o indice do produto idp no vetor de produtos da encomenda ide*/
int indice_produto_encomenda(int ide, int idp){
    int i, indice = -1;
    for(i=0; i<encomendas[ide].nr_produtos; i++)
        if(idp == encomendas[ide].produtos[i].id)
            indice = i;
    return indice;
}

/* adiciona um produto ao sistema*/
void a(char descricao[DESCRICAO], int preco, int peso, int quantidade){

    strcpy(produtos[nr_produtos].descricao,descricao);
    produtos[nr_produtos].preco = preco;
    produtos[nr_produtos].peso = peso;
    produtos[nr_produtos].quantidade = quantidade;
    produtos[nr_produtos].id = nr_produtos;

    printf("Novo produto %d.\n", nr_produtos);
    nr_produtos++;
}

/* aumenta a quantidade de um produto no sistema */
void q(int idp, int quantidade){
    if(nr_produtos > idp)
        produtos[idp].quantidade += quantidade;
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

/* cria uma nova encomenda */
void N(){
    printf("Nova encomenda %d.\n",nr_encomendas);
    nr_encomendas++;
}

/* adiciona um produto a uma encomenda */
void A(int ide, int idp, int quantidade){
    int indice, novo_indice = -1, i;
    produto_enc p, p2;
    char descricao[64];

    if(nr_encomendas > ide) {
        if (nr_produtos > idp) {
            if (produtos[idp].quantidade >= quantidade) {
                if (PESO >= quantidade * produtos[idp].peso + encomendas[ide].peso) {

                    indice = indice_produto_encomenda(ide,idp);
                    if(indice == -1){

                        strcpy(descricao,produtos[idp].descricao);
                        for(i=0;i<encomendas[ide].nr_produtos;i++)
                            if(strcmp(descricao,encomendas[ide].produtos[i].descricao) < 0){
                                novo_indice = i;
                                break;
                            }

                        if(novo_indice != -1){
                            for(i = novo_indice; i < encomendas[ide].nr_produtos; i++){
                                p2 = encomendas[ide].produtos[i];
                                encomendas[ide].produtos[i] = p;
                                p = p2;
                            }
                            encomendas[ide].produtos[i] = p;
                            encomendas[ide].produtos[novo_indice].id = idp;
                            strcpy(encomendas[ide].produtos[novo_indice].descricao, produtos[idp].descricao);
                            encomendas[ide].quantidades[idp] = quantidade;
                        }
                        else{
                            encomendas[ide].produtos[encomendas[ide].nr_produtos].id = idp;
                            strcpy(encomendas[ide].produtos[encomendas[ide].nr_produtos].descricao, produtos[idp].descricao);
                            encomendas[ide].quantidades[idp] = quantidade;
                        }
                        encomendas[ide].nr_produtos++;
                    } else
                        encomendas[ide].quantidades[idp] += quantidade;

                    encomendas[ide].peso += quantidade * produtos[idp].peso;
                    produtos[idp].quantidade -= quantidade;

                } else
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
            } else
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        } else
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    } else
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/* remove certa quantidade de um produto no sistema */
void r(int idp, int quantidade){
    if(nr_produtos > idp){
        if(produtos[idp].quantidade - quantidade >= 0)
            produtos[idp].quantidade -= quantidade;
        else
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
    } else
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
}

/* remove um certo produto de uma encomenda */
void R(int ide, int idp){
    int indice, i;
    produto_enc p , p2;

    if(nr_encomendas > ide) {
        if (nr_produtos > idp) {

            indice = indice_produto_encomenda(ide,idp);
            if(indice == -1)
                return;
            else{
                produtos[idp].quantidade += encomendas[ide].quantidades[idp];
                encomendas[ide].peso -= encomendas[ide].quantidades[idp] * produtos[idp].peso;
                encomendas[ide].quantidades[idp] = 0;

                for(i = encomendas[ide].nr_produtos - 1; i > indice; i--){
                    p2 = encomendas[ide].produtos[i];
                    encomendas[ide].produtos[i] = p;
                    p = p2;
                }
                encomendas[ide].produtos[i] = p;
                encomendas[ide].nr_produtos--;
            }
        } else
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    } else
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/* calcula o custo de uma encomenda */
void C(int ide){
    int i, preco_total = 0;
    if(nr_encomendas > ide){
        for(i=0; i<encomendas[ide].nr_produtos; i++)
           preco_total += encomendas[ide].quantidades[encomendas[ide].produtos[i].id] * produtos[encomendas[ide].produtos[i].id].preco;
        printf("Custo da encomenda %d %d.\n", ide, preco_total);
    } else
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
}

/* altera o preco de um produto no sistema */
void p(int idp, int novo){
    if(nr_produtos > idp)
        produtos[idp].preco = novo;
    else
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
}

/* lista um certo produto numa encomenda */
void E(int ide, int idp){
    if(nr_encomendas > ide){
        if(nr_produtos > idp) {
            if (indice_produto_encomenda(ide, idp) == -1)
                printf("%s 0.\n", produtos[idp].descricao);
            else
                printf("%s %d.\n", produtos[idp].descricao,
                       encomendas[ide].quantidades[idp]);
        } else
            printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    } else
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}

/* indica a maxima quantidade de um produto e a sua respetiva encomenda */ 
void m(int idp){
    int i, max_quantidade = 0, max_encomenda = 0;
    if(nr_produtos > idp) {
        for(i=0; i<nr_encomendas; i++){
            if(encomendas[i].quantidades[idp] > 0)
                if(max_quantidade < encomendas[i].quantidades[idp]){
                    max_encomenda = i;
                    max_quantidade = encomendas[i].quantidades[idp];
                }
        }
        if(max_quantidade)
            printf("Maximo produto %d %d %d.\n", idp, max_encomenda, max_quantidade);
    } else
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
}

void merge(produto arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    produto L[PRODUCTOS], R[PRODUCTOS];

    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while(i < n1 && j < n2){
        if(L[i].preco <= R[j].preco){
            arr[k] = L[i];
            i++;
        } else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }

    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
}

void mergeSort(produto arr[], int l, int r){
    int m;
    if(l < r){
        m = l+(r-l)/2;

        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);

        merge(arr,l,m,r);
    }
}

/* lista os produtos no sistema por ordem de preco */
void l(){
    int i;
    produto produtos_copia[PRODUCTOS];
    for(i = 0; i<nr_produtos;i++) {
        produtos_copia[i].id = produtos[i].id;
        produtos_copia[i].preco = produtos[i].preco;
        produtos_copia[i].quantidade = produtos[i].quantidade;
        produtos_copia[i].peso = produtos[i].peso;
        strcpy(produtos_copia[i].descricao, produtos[i].descricao);
    }


    mergeSort(produtos_copia, 0, nr_produtos-1);
    printf("Produtos\n");
    for(i=0; i<nr_produtos; i++)
        printf("* %s %d %d\n", produtos_copia[i].descricao, produtos_copia[i].preco, produtos_copia[i].quantidade);
}

/* lista os produtos numa encomenda por ordem alfabetica da descricao */
void L(int ide){
    int i;
    if(nr_encomendas > ide){
        printf("Encomenda %d\n", ide);
        for (i = 0; i < encomendas[ide].nr_produtos; i++)
            printf("* %s %d %d\n", encomendas[ide].produtos[i].descricao, produtos[encomendas[ide].produtos[i].id].preco, encomendas[ide].quantidades[encomendas[ide].produtos[i].id]);
    } else
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}

int main(){
    char comando, input[80], descricao[DESCRICAO];
    const char corte[2] = ":";
    int idp, ide, preco, peso, quantidade;

    /* inicializa os produtos e encomendas no sistema a 0 */
    nr_produtos = 0;
    nr_encomendas = 0;

    while(comando != 'x'){
        comando = getchar();
        fgets(input, sizeof(input), stdin);

        switch(comando){
            case 'a':
                strcpy(descricao,strtok(&input[1],corte));
                preco = atoi(strtok(NULL,corte));
                peso = atoi(strtok(NULL,corte));
                quantidade = atoi(strtok(NULL,corte));
                a(descricao,preco,peso,quantidade);
                break;
            case 'q':
                idp = atoi(strtok(input,corte));
                quantidade = atoi(strtok(NULL,corte));
                q(idp,quantidade);
                break;
            case 'N':
                N();
                break;
            case 'A':
                ide = atoi(strtok(input,corte));
                idp = atoi(strtok(NULL,corte));
                quantidade = atoi(strtok(NULL,corte));
                A(ide,idp,quantidade);
                break;
            case 'r':
                idp = atoi(strtok(input,corte));
                quantidade = atoi(strtok(NULL,corte));
                r(idp,quantidade);
                break;
            case 'R':
                ide = atoi(strtok(input,corte));
                idp = atoi(strtok(NULL,corte));
                R(ide,idp);
                break;
            case 'C':
                ide = atoi(input);
                C(ide);
                break;
            case 'p':
                idp = atoi(strtok(input,corte));
                preco = atoi(strtok(NULL,corte));
                p(idp,preco);
                break;
            case 'E':
                ide = atoi(strtok(input,corte));
                idp = atoi(strtok(NULL,corte));
                E(ide,idp);
                break;
            case 'm':
                idp = atoi(input);
                m(idp);
                break;
            case 'l':
                l();
                break;
            case 'L':
                ide = atoi(input);
                L(ide);
                break;
            default:
                break;
        }

    }
    return 0;
}
