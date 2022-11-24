#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_STR 63
#define MAX_IDENT 10000
#define MAX_ENC 500
#define MAX_PESO 200
#define VAR 150

typedef struct{
    /* primeira estrutura serve para os produtos criados na lista de produtos*/
    char descricao[MAX_STR];
    int preco;
    int peso;
    int quantidade;
    int idp;
}produto;

typedef struct{
    /* segunda estrutura serve para as encomendas efetuadas*/
    int ide;
    produto prod[VAR];
    int peso_total;
}encomenda;

void Le_novo_produto(produto list_prod[], int idp){
    list_prod[idp].idp = idp;
    /* guardar o valor no idp do produto para armazenar os dados do produto na sua respetiva estrutura*/
    scanf(" %[^:]:%d:%d:%d", list_prod[list_prod[idp].idp].descricao, &list_prod[list_prod[idp].idp].preco, &list_prod[list_prod[idp].idp].peso, &list_prod[list_prod[idp].idp].quantidade);
    printf("Novo produto %d.\n", idp);
}

void Adiciona_stock(produto list_prod[], int idp_O){
    int idp, qtd;
    
    scanf(" %d:%d", &idp, &qtd);
    
    if(idp > idp_O - 1)
    /* caso o idp dado seja maior que o idp do sistema, nao existe*/
        printf("Impossivel adicionar %d ao stock. Produto inexistente.\n", idp);
    else
        list_prod[list_prod[idp].idp].quantidade += qtd;
}

void Cria_encomenda(encomenda list_enc[], int ide){
    int i;
    list_enc[ide].ide = ide;
    list_enc[ide].peso_total = 0;
    for(i = 0; i < 200; i++){
    /* ciclo que inicia todas as variaveis do produto dentro de uma encomenda para prevenir erros futuros
     Nota: o idp e iniciado a -1 para evitar erro na funcao Adicionar_prod_enc*/
        strcpy(list_enc[ide].prod[i].descricao, "");
        list_enc[ide].prod[i].preco = 0;
        list_enc[ide].prod[i].peso = 0;
        list_enc[ide].prod[i].quantidade = 0;
        list_enc[ide].prod[i].idp = -1;
    }
    printf("Nova encomenda %d.\n", ide);
}

void Adiciona_prod_enc(produto list_prod[], encomenda list_enc[], int idp_O, int ide_O, char enc){
    int ide, idp, qtd, i, n = 0;
    
    scanf(" %d:%d:%d", &ide, &idp, &qtd);
    
    if(ide > ide_O - 1 || enc != 's')
        /* a variavel enc permite dar erro caso nao tenha sido criada a primeira encoenda 0*/
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if(idp > idp_O - 1)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (list_prod[idp].quantidade - qtd < 0)
        /* parametro que verifica se o a quantidade do stock fica negativa*/
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if(list_enc[ide].peso_total + (qtd * list_prod[idp].peso) > MAX_PESO)
        /* estrutura encomenda contem .peso_total de modo a estar sempre a verificar se nao ultrapassa o MAX_PESO*/
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else{
        for(i = 0; i < VAR; i++){
            /* este ciclo verifica se o produto ja existe na encomenda e aumentar a sua quantidade, peso total e diminuir
             consequentemente a quantidade do produto na lista de produto, se for verdadeiro a funcao termina neste ciclo*/
            if(list_enc[ide].prod[i].idp == idp){
                list_enc[ide].prod[i].quantidade += qtd;
                list_enc[ide].peso_total += (list_prod[i].peso * qtd);
                list_prod[idp].quantidade -= qtd;
                n = 1;
                break;
            }
        }
        if(n != 1){
            /* caso o produto ainda nao se encontre na encoemnda cria um novo produto com esse idp com as suas carateristicas*/
            strcpy(list_enc[ide].prod[list_enc[ide].ide].descricao, list_prod[idp].descricao);
            list_enc[ide].prod[list_enc[ide].ide].peso = list_prod[idp].peso;
            list_enc[ide].prod[list_enc[ide].ide].preco = list_prod[idp].preco;
            list_enc[ide].prod[list_enc[ide].ide].quantidade = qtd;
            list_enc[ide].prod[list_enc[ide].ide].idp = list_prod[idp].idp;
            list_enc[ide].peso_total += (list_prod[idp].peso * qtd);
            list_prod[idp].quantidade -= qtd;
            list_enc[ide].ide += 1;
        }
    }
}

void Remove_stock(produto list_prod[], int idp_O){
    int idp, qtd;
    
    scanf(" %d:%d", &idp, &qtd);
    
    if(idp > idp_O - 1)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if(list_prod[list_prod[idp].idp].quantidade - qtd < 0)
        /* parametro que verifica se o a quantidade do stock fica negativa*/
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    else{
        list_prod[list_prod[idp].idp].quantidade -= qtd;
    }
}

void Remove_prod_enc(encomenda list_enc[], produto list_prod[], int idp_O, int ide_O){
    int ide, idp, i;
    scanf(" %d:%d", &ide, &idp);
    
    if(ide > ide_O - 1)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if(idp > idp_O - 1)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else{
        for (i = 0; i < VAR; i++){
                if(list_enc[ide].prod[i].idp == idp){
                    /* ciclo que verifica se o idp do produto se encontra da incomenda ide, caso seja verdadeiro devolve a quantidade de produto a lista de produtos e mete a quantiade do produto em ide a 0, caso contrario nao altera nada na encomenda ide*/
                    list_prod[list_prod[idp].idp].quantidade += list_enc[ide].prod[i].quantidade;
                    list_enc[ide].prod[i].quantidade = 0;
            }
        }
    }
}

void Calcula_custo_enc(encomenda list_enc[], int ide_O){
    int ide, i, preco_total = 0;
    scanf(" %d", &ide);
    
    if(ide > ide_O - 1)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else{
        for(i = 0; i < VAR; i++){
            /* ciclo que vai somar o custo de cada conjunto de produtos numa encomenda*/
            preco_total += (list_enc[ide].prod[i].preco * list_enc[ide].prod[i].quantidade);
        }
        printf("Custo da encomenda %d %d.\n", ide, preco_total);
    }
}

void Altera_preco(encomenda list_enc[], produto list_prod[], int idp_O){
    int idp, preco, a, e, i;
    scanf(" %d:%d", &idp, &preco);
    
    if(idp > idp_O - 1)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else{
        for(i = 0; i < idp_O; i++){
            /* primeiro ciclo que percorre a lista de produtos e altera o preco do produto cujo idp e fornecido*/
            if(list_prod[i].idp == idp)
                list_prod[i].preco = preco;
            }
        for(e = 0; e < MAX_ENC; e++){
            for(a = 0; a < VAR; a++){
                /* este ciclo vai percorrer todas as encomendas e todos os produtos e caso o produto tenha o mesmo idp ira alterar o preco para o valor fornecido*/
                if(list_enc[e].prod[a].idp == idp){
                    list_enc[e].prod[a].preco = preco;
                    break;
                }
            }
        }
    }
}

void Lista_des_qtd(encomenda list_enc[], int ide_O, int idp_O){
    int ide, idp, i;
    scanf(" %d:%d", &ide, &idp);
    
    if(ide > ide_O - 1)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if(idp > idp_O - 1)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else{
        for(i = 0; i < VAR; i++){
            /* ciclo que vai percorrer a encomenda ide ate encontrar o produto ido e imprimir a sua descricao e quantidade*/
            if(list_enc[ide].prod[list_enc[i].ide].idp == idp){
                printf("%s %d.\n", list_enc[ide].prod[list_enc[i].ide].descricao, list_enc[ide].prod[list_enc[i].ide].quantidade);
                break;
            }
        }
    }
}

void Lista_id_enc(encomenda list_enc[], int idp_O){
    int idp, i, e, enc = 0, maximo = 0;
    scanf("%d", &idp);
    
    if(idp > idp_O - 1)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else{
        for(i = 0; i < MAX_ENC; i++){
            for(e = 0; e < VAR; e++){
                /*ciclo que procura a maior quantidade do produto idp e guarda a quantidade e o numero da encomenda*/
                if(list_enc[i].prod[list_enc[e].ide].idp == idp){
                    if(list_enc[i].prod[list_enc[e].ide].quantidade > maximo){
                        maximo = list_enc[i].prod[list_enc[e].ide].quantidade;
                        enc = i;
                    }
                }
            }
        }
        printf("Maximo produto %d %d %d.\n", idp, enc, maximo);
    }
}

int main()
{
    char comando, enc = ' ';
    int idp = 0, ide = 0, i;
    produto list_prod[MAX_IDENT];
    encomenda list_enc[MAX_ENC];
    
    for(i = 0; i < MAX_IDENT; i++){
        /* ciclo que inicia a lista de produtos toda a 0 de maneira a evitar erros*/
        strcpy(list_prod[i].descricao, "");
        list_prod[i].preco = 0;
        list_prod[i].peso = 0;
        list_prod[i].quantidade = 0;
    }
        
    while((comando = getchar()) != 'x'){
        
            switch(comando)     /* a int main vai ser um ciclo switch finito onde o primeiro carater a ler sera sempre o comando e depois                      as regras dependendo do comando, x permite terminar o programa*/
    {
        case 'a':
            Le_novo_produto(list_prod, idp);
            /* cria  um novo produto no sistema*/
            idp += 1;
            break;
        case 'q':
            Adiciona_stock(list_prod, idp);
            /* adiciona stock a um produto existente no sistema*/
            break;
        case 'N':
            Cria_encomenda(list_enc, ide);
            /* cria nova encomenda*/
            enc = 's';
            ide += 1;
            break;
        case 'A':
            Adiciona_prod_enc(list_prod, list_enc, idp, ide, enc);
            /* adiciona um produto a uma encomenda. Se o produto ja existe aumenta a sua quantidade*/
            break;
        case 'r':
            Remove_stock(list_prod, idp);
            /* remove stock a um produto existente*/
            break;
        case 'R':
            Remove_prod_enc(list_enc, list_prod, idp, ide);
            /* remove um produto a uma encomenda*/
            break;
        case 'C':
            Calcula_custo_enc(list_enc, ide);
            /* calcula o custo de uma encomenda*/
            break;
        case 'p':
            Altera_preco(list_enc, list_prod, idp);
            /* altera o preco de um produto no sistema inteiro*/
            break;
        case 'E':
            Lista_des_qtd(list_enc, ide, idp);
            /* lista a descricao e a quantidade de um produto numa encomenda*/
            break;
        case 'm':
            Lista_id_enc(list_enc, idp);
            /* lista o identificador da encomenda em que o produto dado ocorre mais*/
            break;
        default:
            break;
        }
    }
    return 0;
}
