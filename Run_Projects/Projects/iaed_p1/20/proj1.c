#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-------constantes------*/
#define MAX_DESCRICAO 63
#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define MAX_PESO 201

/*Estrutura de produtos*/
typedef struct produtos{
    char descricao[MAX_DESCRICAO];
    int preco;
    int peso;
    int quantidade;
    int idp;
}Produtos;

/*estrurtura de encomendas*/
typedef struct encomendas{
    int nr_pdt; /*numero de produtos existentes numa encomenda*/
    int ide; /*id da encomenda*/
    int peso_total;/*peso total da encomenda*/
    Produtos pdt_e[MAX_PESO]; /*vetor dos meus produtos da minha ecomenda*/
} Encomendas;

Produtos pdt[MAX_PRODUTOS]; /*vetor dos meus produtos do sistema*/
int nr_produtos;/*variavel que guarda o total dos produtos do meu sistema*/
Encomendas ecmd[MAX_ENCOMENDAS];/*vetor das ecomendas*/ 
int nr_encomendas;/*variavel que guarda o numero de total das encomendas*/

void adicionar_produto(){
    /*COMANDO a - permite adicionar um novo produto ao sistema*/

    char descricao[MAX_DESCRICAO];
    int preco;
    int peso;
    int quantidade;

    scanf("%[^:]:%d:%d:%d", descricao, &preco, &peso, &quantidade);

    /*verificacao do preco ser um positivo maior que zero, do peso ser positivo e da quantidade*/
    if (preco > 0 && peso > 0 && quantidade >= 0){
        /*os valores sao guardados no seu respetivo lugar*/
        strcpy(pdt[nr_produtos].descricao, descricao);
        pdt[nr_produtos].preco = preco;
        pdt[nr_produtos].peso = peso;
        pdt[nr_produtos].quantidade = quantidade;
        pdt[nr_produtos].idp = nr_produtos;
        printf("Novo produto %d.\n", nr_produtos);
        nr_produtos++; /*incrementa os numero de produtos so se o produto for adicionado ao sistema*/
    }
}

void adiciona_quantidade (){
    /*COMANDO q - permite adicionar a quantidade a um produto existente no sistema*/
    int idp, qtd;

    scanf("%d:%d", &idp, &qtd);

    /*verificacao do idp recebido, se realmente existe esse produto*/
    if (idp < nr_produtos){
        pdt[idp].quantidade = pdt[idp].quantidade + qtd; /*adiciona se a quantidade recebida*/
    } else {
        /*gera um erro se o produto nao existir*/
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
}

void cria_encomenda(){
    /*Comando N = cria uma nova encomenda*/
    
    ecmd[nr_encomendas].nr_pdt = 0; /*ao criar uma encomenda, no inicio ela nao tem produtos*/

    printf("Nova encomenda %d.\n", nr_encomendas);
    nr_encomendas++;
}

int aux_verifica_p_e(int id_enc, int id_prod){
    /*funcao auxiliar que verifica se existe o produto na encomenda*/
    int i;
    for (i = 0; i < ecmd[id_enc].nr_pdt; i++){
        if(ecmd[id_enc].pdt_e[i].idp == id_prod){
            return i;/*se existir devolve id onde existe esse produto na encomenda*/
        }
    }
    return -2;/*devolve -2 se o produto nao existir na encomenda*/
}

void adic_prod_encomenda(){
    /*COMANDO A - adiciona um produto a uma encomenda*/
    int id_e, id_p, qtd, peso_p, n, k=0;
   
    scanf("%d:%d:%d", &id_e, &id_p, &qtd);

    if (id_e < nr_encomendas){
        if (id_p < nr_produtos){
            /*verifica se existe stock suficiente para poder adicionar a encomenda*/
            if(qtd <= pdt[id_p].quantidade){
                peso_p = pdt[id_p].peso;
                /*verifica se ao adicionar o produto a encomenda nao excede o peso maximo*/
                if (MAX_PESO > (ecmd[id_e].peso_total + (peso_p * qtd))){
                    k = aux_verifica_p_e(id_e, id_p);
                    if(k!=-2){
                        /*se o produto ja existir na encomenda atualiza a quantidade, o peso tortal 
                        da encomenda e ainda atualiza o stock do produto no sistema*/
                        pdt[id_p].quantidade = pdt[id_p].quantidade - qtd;
                        ecmd[id_e].pdt_e[k].quantidade = ecmd[id_e].pdt_e[k].quantidade + qtd;
                        ecmd[id_e].peso_total = ecmd[id_e].peso_total + (pdt[id_p].peso * qtd);
                       
                    } else {
                        /*se o produto nao existir na encomenda, ele ? adicionado a minha encomenda*/
                        ecmd[id_e].ide = id_e;
                        pdt[id_p].quantidade = pdt[id_p].quantidade - qtd;
                        n = ecmd[id_e].nr_pdt;

                        ecmd[id_e].pdt_e[n].idp = id_p;
                        strcpy(ecmd[id_e].pdt_e[n].descricao, pdt[id_p].descricao);
                        ecmd[id_e].pdt_e[n].preco = pdt[id_p].preco;
                        ecmd[id_e].pdt_e[n].peso = pdt[id_p].peso;
                        ecmd[id_e].pdt_e[n].quantidade = qtd;

                        ecmd[id_e].peso_total = ecmd[id_e].peso_total + (pdt[id_p].peso * qtd);
                        ecmd[id_e].nr_pdt = ecmd[id_e].nr_pdt + 1;
                        
                    }

                }else {
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_p, id_e);
                }
            }else {
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_p, id_e);
            }
        }else{
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_p, id_e);
        }
    }else{
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_p, id_e);
    }
    
}


void remove_quantidade(){
    /*COMANDO r - remove quantidade a um produto existente*/
    int id_p, qtd;

    scanf("%d:%d", &id_p, &qtd);

    if(id_p < nr_produtos){
        if(pdt[id_p].quantidade - qtd < 0 ){
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id_p);
        }else {
            pdt[id_p].quantidade = pdt[id_p].quantidade - qtd;
        }
    }else{
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_p);
    }

}

void remove_produto(){
    /*COMANDO R - remove produto de uma encomenda*/
    int id_e, id_p, k;
    
    scanf("%d:%d", &id_e, &id_p);

    if (id_e < nr_encomendas){
        if(id_p < nr_produtos){
            k = aux_verifica_p_e(id_e, id_p);/*devolve o id onde o produto da encomenda existe*/
            
            if( k != -2){

                /*-1 significa que apagou o idp do produto na encomenda*/
                ecmd[id_e].pdt_e[k].idp = -1;
                ecmd[id_e].peso_total = ecmd[id_e].peso_total - (pdt[id_p].peso * ecmd[id_e].pdt_e[k].quantidade);
                /*ao apagar todos os valores (no meu caso fica com uma string vazia ou igualo a 0)*/
                strcpy(ecmd[id_e].pdt_e[k].descricao, "");
                ecmd[id_e].pdt_e[k].preco = 0;
                ecmd[id_e].pdt_e[k].peso = 0;

                /*volta a adicionar o stock ao produto do sistema*/
                pdt[id_p].quantidade = pdt[id_p].quantidade + ecmd[id_e].pdt_e[k].quantidade;
                ecmd[id_e].pdt_e[k].quantidade = 0;
                
            }
        } else{
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_p, id_e);
        }
        
    }else {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_p, id_e);
    }
    
}

void custo_encomenda(){
    /*COMANDO C - calcula o custo total da encomenda*/
    int id_e, i, custo, quant, custo_total = 0;

    scanf("%d", &id_e);

    if (id_e < nr_encomendas){
        for (i = 0; i < ecmd[id_e].nr_pdt; i++){
            custo = ecmd[id_e].pdt_e[i].preco;
            quant = ecmd[id_e].pdt_e[i].quantidade;
            custo_total = custo_total + (custo * quant);
        }
        printf("Custo da encomenda %d %d.\n", id_e, custo_total);
        
    }else {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_e);
    }

}

void altera_preco(){
    /*COMANDO p - altera o preco de um produto*/
    int id_p, preco, j, i;

    scanf("%d:%d", &id_p, &preco);

    if (id_p < nr_produtos){
        pdt[id_p].preco = preco;
        for (i = 0; i < nr_encomendas; i++){
            j = aux_verifica_p_e(i, id_p);
            /*verifica se o produto existe na encomenda*/
            if (j != -2){
                ecmd[i].pdt_e[j].preco = preco;/*se existir, tambem se altera o preco*/
            }
        }

    }else {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_p);
    }
}

void lista_d_q_encomenda(){
    /*COMANDO E - lista a descricao e a quantidade de um produto de uma encomenda*/

    int id_p, id_e, i=0, quantidade=0;

    scanf("%d:%d", &id_e, &id_p);

    if (id_e < nr_encomendas){
        if (id_p < nr_produtos){
            i = aux_verifica_p_e(id_e, id_p);
            if(i != -2){
                /*se o produto existir na encomenda mostra a lista*/
                printf("%s %d.\n", pdt[id_p].descricao, ecmd[id_e].pdt_e[i].quantidade);
            }else {
                /*se o produto nao existir na encomenda, lista se na mesma (o que difere 
                e que neste caso e quantidade vai ser 0)*/
                printf("%s %d.\n", pdt[id_p].descricao, quantidade);
            }
        } else{
            printf("Impossivel listar produto %d. Produto inexistente.\n", id_p);
        }  
    }else {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_e);
    }
}

int devolve_max(int id_p){
    /*funcao auiliar que devolve o ide onde o produto ocorre mais vezes*/
    int i, k1, k2, max=0;
    
    for (i = 1; i < nr_encomendas; i++){
        /*devolve o idp onde existe a encomenda*/
        k1 = aux_verifica_p_e(i, id_p);
        k2 = aux_verifica_p_e(max, id_p);
        
        if(ecmd[i].pdt_e[k1].quantidade > ecmd[max].pdt_e[k2].quantidade){
            max = i;
        } else if (ecmd[max].pdt_e[k2].quantidade == ecmd[i].pdt_e[k1].quantidade) {
            if(ecmd[max].ide > ecmd[i].ide){
                max = i;
            }
        }
    }
    return max;/*devolve o ide max*/
}

void lista_enc_max_qtd(){
    /*COMANDO m - lista o id da encomenda em que o produto ocorre mais vezes, se houver mais 
    encomendas com mesmo numero de ocorrencia imprime e encomenda de menor id*/
    int id_p, i, max_ide;

    scanf("%d\n", &id_p);

    if (id_p < nr_produtos){
        if ( nr_encomendas > 0){
            max_ide = devolve_max(id_p);/*devolve o ide onde o produto ocorre mais vezes*/
            for (i = 0; i < ecmd[max_ide].nr_pdt; i++){
                if(ecmd[max_ide].pdt_e[i].idp == id_p){
                    printf("Maximo produto %d %d %d.\n", id_p, max_ide, ecmd[max_ide].pdt_e[i].quantidade);
                }
            }
        }
        
    } else {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_p);
    }
}

void imprime_produtos(Produtos aux_produtos[MAX_PRODUTOS], int tam){
    /*imprime todos os produtos do sistema pela ordem do preco*/
    int i;

    printf("Produtos\n");
    for (i = 0; i < tam; i++){
        printf("* %s ", aux_produtos[i].descricao);
        printf("%d ", aux_produtos[i].preco);
        printf("%d\n", aux_produtos[i].quantidade);
    }
    
}

void selection_sort(Produtos aux_produtos[MAX_PRODUTOS], int tam){
    /*funcao que permite a ordenacao todos os existentes produtos 
    no sistema po ordem crescente de preco*/
    int i, min, j;
    Produtos aux;
    for (i = 0; i < (tam-1); i++){
        min = i;
        for (j = (i+1); j < tam; j++){
            if(aux_produtos[j].preco < aux_produtos[min].preco){
                min = j;
            /*se houver produtos com mesmo preco devera ordenar pelo id do produto*/
            } else if(aux_produtos[j].preco == aux_produtos[min].preco){
                if(aux_produtos[j].idp < aux_produtos[min].idp){
                    min = j;
                }
            }
        }
        aux = aux_produtos[i];
        aux_produtos[i] = aux_produtos[min];
        aux_produtos[min] = aux;
    }
}

void lista_pdt_preco(){
    /*COMANDO l - lista todos os produtos existentes no sistema por ordem do preco*/
    int i, i_aux=0;
    Produtos aux_produtos[MAX_PRODUTOS];/*vetor auxilar para produtos*/

    /*copia todos os produtos existentes no meu sistema para um vetor auxiliar*/
    for (i = 0; i < nr_produtos; i++){
        strcpy(aux_produtos[i_aux].descricao, pdt[i].descricao);
        aux_produtos[i_aux].peso = pdt[i].peso;
        aux_produtos[i_aux].preco = pdt[i].preco;
        aux_produtos[i_aux].quantidade = pdt[i].quantidade;
        aux_produtos[i_aux].idp = pdt[i].idp;
        i_aux++;
    }

    selection_sort(aux_produtos, i_aux);
    imprime_produtos(aux_produtos, i_aux);
}

void selection_sort_descricao(Produtos aux_encomenda[MAX_ENCOMENDAS], int tam){
    /*funcao que ordena os produtos duma encomenda por ordem alfabetica da descricao*/
    int i, min, j;
    Produtos aux;
    for (i = 0; i < (tam-1); i++){
        min = i;
        for (j = (i+1); j < tam; j++){
            if(strcmp(aux_encomenda[j].descricao, aux_encomenda[min].descricao)<0){
                min = j;
            }
        }
        aux = aux_encomenda[i];
        aux_encomenda[i] = aux_encomenda[min];
        aux_encomenda[min] = aux;
    }
}

void lista_pdt_enc(){
    /*COMANDO L - lista todos os produtos duma encomenda por ordem alfabetica da descricao*/
    int i, j, id_e, i_aux=0;
    Produtos aux_encomenda[MAX_PRODUTOS];/*vetor auxiliar que guarda todos os produtos da encomenda*/

    scanf("%d\n", &id_e);

    if (id_e < nr_encomendas){
        for (i = 0; i < ecmd[id_e].nr_pdt; i++){
            if(ecmd[id_e].pdt_e[i].idp != -1){
                /*copia todos os produtos duma encomenda para um vetor auxiliar*/
                aux_encomenda[i_aux].idp = ecmd[id_e].pdt_e[i].idp;
                strcpy(aux_encomenda[i_aux].descricao, ecmd[id_e].pdt_e[i].descricao);
                aux_encomenda[i_aux].preco = ecmd[id_e].pdt_e[i].preco;
                aux_encomenda[i_aux].peso = ecmd[id_e].pdt_e[i].peso;
                aux_encomenda[i_aux].quantidade = ecmd[id_e].pdt_e[i].quantidade;
                i_aux++;
            }
        }

        selection_sort_descricao(aux_encomenda, i_aux);

        /*imprime todos os produtos de uma encomenda ja ordenados por ordem alfabetica*/
        printf("Encomenda %d\n", id_e);
        for (j = 0; j < i_aux; j++){
            printf("* %s ", aux_encomenda[j].descricao);
            printf("%d ", aux_encomenda[j].preco);
            printf("%d\n", aux_encomenda[j].quantidade);
        }
        
    } else {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_e);
    }
}

int main() {
    char comando;

    do{
        switch (comando = getchar()){
            case 'a':
                getchar();
                adicionar_produto();
                break;
            case 'q':
                adiciona_quantidade();
                break;
            case 'N':
                cria_encomenda();
                break;
            case 'A':
                getchar();
                adic_prod_encomenda();
                break;
            case 'r':
                remove_quantidade();
                break;
            case 'R':
                remove_produto();
                break;
            case 'C':
                custo_encomenda();
                break;
            case 'p':
                altera_preco();
                break;
            case 'E':
                lista_d_q_encomenda();
                break;
            case 'm':
                lista_enc_max_qtd();
                break;
            case 'l':
                lista_pdt_preco();
                break;
            case 'L':
                lista_pdt_enc();
                break;
            
        }

    } while (comando != 'x');
    return 0;
}

