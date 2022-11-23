#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Valor maximo de produtos suportado */
#define PRODMAX 10000

/* Valor maximo de carateres permitido para a descricao de um produto (incluindo '\0') */
#define DESCMAX 64

/* Valor maximo de encomendas suportado */
#define ORDMAX 501

/* Valor maximo de carateres permitido para um comando */
#define COMMAX 100

/* Valor maximo permitido para o peso de uma encomenda */
#define PESOMAX 200

/* Estrutura que armazena os produtos e o seu preco, peso, e quantidade, respetivamente */
struct struct_produtos {

        int id;
        char desc[DESCMAX];
        int preco;
        int peso;
        int qtd;
    };

struct struct_produtos inventario[PRODMAX];

/*Estruturas de apoio a ordena?ao das listas */
struct struct_produtos temp[PRODMAX];
struct struct_produtos aux[PRODMAX];

/* Estrutura que armazena as encomendas com os seus respetivos produtos e quantidade pedida,
    custo e peso totais
 */
struct struct_encomendas {

        int produtos[PRODMAX];
        int preco;
        int peso;
    };

struct struct_encomendas encomendas[PRODMAX];

/* Variaveis de contagem dos produtos e das encomendas, respetivamente
   Recebe uma descricao, um preco, um peso e uma qauntidade
 */
int i=0;
int j=0;

/* Inicializa o novo produto
   Recebe uma descricao, um preco, um peso e uma qauntidade
 */
void command_a(char d[DESCMAX], int p, int w, int q) {
    
    inventario[i].id = i;
    inventario[i].preco = p;
    inventario[i].peso = w;
    inventario[i].qtd = q;
    strncpy(inventario[i].desc, d + 1, DESCMAX - 1);
}

/* Adiciona a quantidade pretendida de stock a um produto existente no sistema
   Recebe um produto e uma quantidade
 */
void command_q(int p, int q) {

    inventario[p].qtd += q;
}

/* Adiciona a quantidade pretendida de um produto a uma encomenda e atualiza
    os valores totais do preco e peso da mesma
   Recebe uma encomenda, um produto e uma quantidade
*/
void command_A(int e, int p, int q) {

        encomendas[e].produtos[p] += q;
        encomendas[e].peso = (encomendas[e].peso + (inventario[p].peso * q));
        encomendas[e].preco = (encomendas[e].preco + (inventario[p].preco * q));
    }

/* Remove a pretendida quantidade de stock a um produto do sistema
   Recebe um produto e uma quantidade
 */
void command_r(int p, int q) {

    inventario[p].qtd = inventario[p].qtd - q;
}

/* Remove o produto pretendido da encomenda e atualiza os valores totais do
    preco e peso da encomenda
   Recebe uma encomenda, um produto e uma quantidade
*/
void command_R(int e, int p, int q) {

    encomendas[e].peso = encomendas[e].peso - (inventario[p].peso * q);
    encomendas[e].preco = encomendas[e].preco - (inventario[p].preco * q);
    encomendas[e].produtos[p] = 0;
}

/* Identifica a encomenda cuja quantidade pedida de certo produto e maior
   Recebe um produto
 */
int command_m(int p) {

    int k, e = -1, m = 0;

    for (k = 0; k < j; k++) 
        if (encomendas[k].produtos[p] > m) {
            m = encomendas[k].produtos[p];
            e = k;
    }
    return e;
}

/* Merge e mergesort efeteuam a ordenacao da estrutura pretendida
   Recebem uma estrutura, a primeira e ultima posicoes da estrutura e um modo
   O modo "mode", valor 0 ou 1, seleciona ordenacao por ordem crescente de
    precos ou ordem alfabetica de descricoes, respetivamente
*/
void merge(struct struct_produtos t[], int left, int m, int right, int mode) {
    int k, l, n;
    for (k = m + 1; k > left; k--)
        aux[k - 1] = t[k - 1];
    for (l = m; l < right; l++)
        aux[right + m - l] = t[l + 1];
    for (n = left; n <= right; n++)
        if (mode)    
            if (strcmp(aux[l].desc, aux[k].desc) < 0)
                t[n] = aux[l--];
            else
                t[n] = aux[k++];
        else
            if (aux[l].preco == aux[k].preco && aux[l].id < aux[k].id)
                t[n] = aux[l--];
            else if (aux[l].preco == aux[k].preco && aux[l].id > aux[k].id)
                t[n] = aux[k++];
            else if (aux[l].preco < aux[k].preco)
                t[n] = aux[l--];
            else
                t[n] = aux[k++];
}

void mergesort(struct struct_produtos t[], int left, int right, int mode) {
    int m = (right+left)/2;
    if (right <= left)
        return;
    mergesort(t, left, m, mode);
    mergesort(t, m+1, right, mode);
    merge(t, left, m, right, mode);

}

/* Conforme o comando introduzido, faz a selecao da operacao e excuta-a */ 
int main() {

    int command;
    int idp, ide;
    int preco, peso, qtd;
    char desc[DESCMAX];
    int k, c;
 
    while((command=getchar())!='x') {
        switch(command) {
            
            /* Adiciona um novo produto ao sistema */
            case 'a':

                scanf("%[^:]:%d:%d:%d", desc, &preco, &peso, &qtd);
                command_a(desc, preco, peso, qtd);
                printf("Novo produto %d.\n", i);
                i++;
                break;
            
            /* Adiciona stock a um produto existente */
            case 'q':

                scanf("%d:%d", &idp, &qtd);
                if (i > idp)
                    command_q(idp, qtd);
                else
                    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
                break;

            /* Cria e inicializa uma nova encomenda*/
            case 'N':

                encomendas[j].preco = 0;
                encomendas[j].peso = 0;
                printf("Nova encomenda %d.\n", j);
                j++;
                break;

            /* Adiciona um produto a uma encomenda */
            case 'A':

                scanf("%d:%d:%d", &ide, &idp, &qtd);
                if(j <= ide)
                    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
                
                else if(i <= idp)
                    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
                
                else if(qtd > inventario[idp].qtd)
                    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
                
                else if((encomendas[ide].peso + (inventario[idp].peso * qtd)) > PESOMAX)
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
                
                else {
                    command_A(ide, idp, qtd);
                    command_r(idp, qtd);
                }
                break;

            /* Remove stock a um produto existente no sitema */
            case 'r':
                
                scanf("%d:%d", &idp, &qtd);
                if (i > idp) {
                    if (qtd > inventario[idp].qtd)
                        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
                    else
                        command_r(idp, qtd);
                }
                
                else
                    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
                break;

            /* Remove um produto de uma encomenda */
            case 'R':
                
                scanf("%d:%d", &ide, &idp);
                if (j <= ide)
                    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
               
                else if (i <= idp)
                    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
                
                else {
                    command_q(idp, encomendas[ide].produtos[idp]);
                    command_R(ide, idp, encomendas[ide].produtos[idp]);
                }
                break;

            /* Imprime o custo de uma encomenda */  
            case 'C':
                
                scanf("%d", &ide);
                if (j <= ide)
                    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
               
                else
                    printf("Custo da encomenda %d %d.\n", ide, encomendas[ide].preco);
                break;

            /* Altera o preco de um produto existente no sistema e atualiza o preco total
               das encomendas em que o produto esta listado
            */
            case 'p':
                
                scanf("%d:%d", &idp, &preco);
                if (i > idp) {
                    for (ide = 0; ide <= j; ide++)
                        if (encomendas[ide].produtos[idp] != 0){
                            encomendas[ide].preco = encomendas[ide].preco - (inventario[idp].preco * encomendas[ide].produtos[idp]);
                            encomendas[ide].preco = encomendas[ide].preco + (preco * encomendas[ide].produtos[idp]);
                        }
                    inventario[idp].preco = preco;
                }
                
                else
                    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
                break;

            /* Imprime a descricao e quantidade de um produto numa dada encomenda */
            case 'E':
                
                scanf("%d:%d", &ide, &idp);
                if (j <= ide)
                    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
                
                else if (i <= idp)
                    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
                
                else
                    printf("%s %d.\n", inventario[idp].desc, encomendas[ide].produtos[idp]);
                break;

            /* Retorna o indentificador da encomenda em que o produto introduzido e
               pedido em maior quantidade
            */ 
            case 'm':
                
                scanf("%d", &idp);
                if (i <= idp)
                    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
                
                else if (command_m(idp) == -1)
                    ;
               
                else
                    printf("Maximo produto %d %d %d.\n", idp, command_m(idp), encomendas[command_m(idp)].produtos[idp]);
                break;

            /* Lista os produtos existentes no sistema por ordem crecente de preco */
            case 'l':

                printf("Produtos\n");
                for(k = 0; k < i; k++) {
                    temp[k] = inventario[k];
                }
                mergesort(temp, 0, i-1, 0);

                for(k = 0; k < i; k++)
                    printf("* %s %d %d\n",temp[k].desc, temp[k].preco, temp[k].qtd);
                break;

            /* Lista os produtos existentes numa encomenda por ordem alfabetica 
               das respetivas descricoes
            */
            case 'L':
                
                scanf("%d", &ide);
                if (j <= ide)
                    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
                
                else {    
                    printf("Encomenda %d\n", ide);
                    c = 0;
                    for(k = 0; k < i; k++)
                        if (encomendas[ide].produtos[k] != 0) {
                            temp[c] = inventario[k];
                            temp[c].qtd = encomendas[ide].produtos[k];
                            c++;
                    }
        
                    mergesort(temp, 0, c-1, 1);

                    for(k = 0; k < c; k++)
                        printf("* %s %d %d\n",temp[k].desc, temp[k].preco, temp[k].qtd);
                }
                break;
            
            /* Termina o programa */
            case 'x':
                break;
        }
    }
    return 0;
}