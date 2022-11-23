#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* directivas de pre-compilador, definicao de tipos/estruturas, variaveis globais, etc. */

# define encocor 500
# define prodcor 10000
# define charcor 63
# define Pesolim 200


/* definicao da estrutura Produto que recebe definidos todas as caracteristicas de um produto, o produtoenco que recebe os produtos das
 * encomendas e a estrutura encomenda, para resolucao do projeto*/
typedef struct produto{
    int identificador;
    char descricao [charcor];
    int preco;
    int peso;
    int qtd;
}produto;
produto vetorprodutos[prodcor];         /* directivas de pre-compilador, definicao de tipos/estruturas, criacao do vetor, para armazenar prudutos*/
produto b;
produto ordenado[prodcor];

typedef struct produtoenco {
    int qtd_e;
    int idp_e;
    int preco;
}produtoenco;

typedef struct {
    int identificador;
    produtoenco produto[prodcor];

}encomenda;
encomenda p;                            /* directivas de pre-compilador, definicao de tipos/estruturas, criacao do vetor, para armazenar encomendas. etc.*/
encomenda vetorencomenda[encocor];



/* adiciona um novo produto ao sistema */
void d_a(){
    int incrimentador = 0;

    char nome[charcor];
    int c = 0;
    printf("insira o preco: ");
    scanf("%d", &c);
    b.preco = c;
    printf("insira o peso: ");\
    scanf("%d", &c);
    b.peso = c;
    printf("insira a quantidade em stock: ");
    scanf("%d", &c);
    b.qtd = c;
    printf("insira a discricao: ");
    scanf("%s", &nome[charcor]);
    strcpy(b.descricao,nome);
    b.identificador++;
    if (b.identificador < prodcor) {
        vetorprodutos[incrimentador]= b;
        incrimentador++;
        printf("Novo produto %d\n", vetorprodutos[incrimentador-1].identificador);
    }

}
/* adiciona stock a um produto existente no sistema*/
void d_q(){
    int a=0;
    int i=0;
    int c=0;
    printf("insira o identificador do produto: ");
    scanf("%d", &a);
    printf("insira o stock: ");
    scanf("%d", &c);

    while (vetorprodutos[i].identificador>0){
        if(vetorprodutos[i].identificador==a){
            vetorprodutos[i].qtd=vetorprodutos[i].qtd+c;
        }
        else{
            printf("Impossivel adicionar produto <idp> ao stock. Produto inexistente.\n");
        }
        i++;

    }
}
/* cria uma nova encomenda */
void d_N(){
    int j=0;
    p.identificador++;
    vetorencomenda[j]=p;
    vetorencomenda[j].identificador=p.identificador;
    j++;
}
/* adiciona um produto a uma encomenda*/
void d_A(){
int corer=0;
    int i=0;
    int h=0;
    int bh=0;
    int qtd;
    int ide=0;
    int idp=0;
    printf("insira o identificador da encomenda: ");
    scanf("%d", &ide);
    printf("insira o identificador do produto: ");
    scanf("%d", &idp);
    printf("insira a quantidade de stock: ");
    scanf("%d", &qtd);
    int j;
        for(j = 0; j <encocor; ++j) {
            if (vetorencomenda[i].identificador==ide) {
                int i=0;
                for (int i = 0; i < prodcor; ++i) {
                    if (b.identificador==idp){
                        if(vetorprodutos[i].peso<=Pesolim){
                            if(vetorprodutos[i].identificador==vetorencomenda[j].produto[i].idp_e){
                                if(vetorprodutos[i].qtd>=qtd) {
                                    vetorencomenda[j].produto[i].qtd_e+=qtd;
                                }
                            }
                            else if(vetorprodutos[i].qtd>=qtd){
                                vetorprodutos[i].qtd-=qtd;
                                vetorencomenda[j].produto[i].qtd_e=qtd;
                                vetorencomenda[j].produto[i].idp_e=b.identificador;
                                vetorencomenda[j].produto[i].preco=vetorprodutos[i].preco;
                            } else if (vetorprodutos[i].qtd<qtd){
                                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
                            }
                        } else{
                            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200\n", idp, ide);
                        }
                    }else{
                        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
                    }
                }
            }else{
                printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
            }

        }



    }
/* remove stock a um produto existente */
void d_r(){
    int idp=0;
    int i=0;
    int c=0;
    int q=0;
    printf("insira o identificador: ");
    scanf("%d", &idp);
    printf("insira o stock: ");
    scanf("%d", &c);

    while (vetorprodutos[i].identificador>0){
        if(p.identificador==idp){
            if( vetorencomenda[i].produto[i].idp_e==idp) {
                if ((vetorprodutos[i].qtd - vetorencomenda[i].produto[i].qtd_e) >= c) {
                    vetorprodutos[i].qtd = vetorprodutos[i].qtd - c;
                }
            }
        }
        else{
            printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        }
        i++;

    }

}
/* remove um produto de uma encomendaet */
void d_R(){
    int ide=0;
    int idp=0;
    printf("insira o identificador da encomenda: ");
    scanf("%d", &ide);
    printf("insira o identificador do produto: ");
    scanf("%d", &idp);
    for (int i = 0; i < encocor; ++i) {
        if (p.identificador==ide){
            if(vetorencomenda[i].produto[i].idp_e==idp){
                vetorencomenda[i].produto[i].idp_e=0;
                vetorencomenda[i].identificador=0;
                vetorencomenda[i].produto[i].qtd_e=0;
            } else if(vetorencomenda[i].produto[i].idp_e==idp!=0 && i==4){
                printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
            }
        }
    };

}
/* calcula o custo de uma encomenda*/
void d_C(){
    int ide=0;
    printf("insira o identificador da encomenda: ");
    scanf("%d", &ide);
    int total=0;
    int qtd=0;
    int resultado=0;
    int total1=0;
        for (int i = 0; i <encocor ; ++i) {
                for (int j = 0; j < prodcor; ++j) {
                        if (ide == p.identificador) {
                            total += vetorencomenda[i].produto[j].preco;
                             qtd += vetorencomenda[i].produto[j].qtd_e;
                        }
                }

        }
    resultado=(total*qtd);
    printf("Custo da encomenda %d %d.\n", ide, resultado);
}
/* altera o pre?o de um produto existente no sistema*/
void d_p(){
    int idp=0;
    int preco=0;
    printf("insira o identificador do produto: ");
    scanf("%d", &idp);
    printf("insira o preco: ");
    scanf("%d", &preco);


    for (int i = 0; i <encocor ; ++i) {
        for (int j = 0; j < prodcor; ++j) {
            if(idp==vetorprodutos[i].identificador && idp==vetorencomenda[i].produto[i].idp_e){
                vetorprodutos[j].preco=preco;
                vetorencomenda[i].produto[j].preco=preco;
            }
        }
    }
}
/* retorna a descri??o e a quantidade de um produto numa dada encomenda*/
void d_E(){
    int ide=0;
    int idp=0;
    printf("insira o identificador da encomenda: ");
    scanf("%d", &ide);
    printf("insira o identificador do produto: ");
    scanf("%d", &idp);
    for (int i = 0; i <encocor; ++i) {
        for (int j = 0; j < prodcor; ++j) {
            if(ide==vetorencomenda[i].identificador){
                if(idp==vetorencomenda[i].produto[i].idp_e){
                        printf("%s %d:",vetorprodutos[j].descricao, vetorencomenda[i].produto[i].qtd_e);
                }
            }
        }
    }
}
/* retorna o identificador da encomenda em que um dado produto ocorre mais vezes*/
void d_m(){
   int vetor[prodcor];
    for (int i = 0; i < prodcor; ++i) {
        for (int j = 0; j < prodcor; ++j) {
            if (vetorencomenda[i].identificador>vetorencomenda[i + 1].identificador) {
                vetor[i] = vetorencomenda[i].identificador;
                vetorprodutos[i].identificador = vetorprodutos[i + 1].identificador;
                vetorprodutos[i + 1].identificador = vetor[i];

            }
        }
    }
    int i,po=0,maior;
    maior = vetor[0];
    for(i=0; i<prodcor; i++){
        if (vetor[i] > maior){
            maior = vetor[i];
            po=i;
        }
    }
    printf("Maximo produto%d",maior);
}

/* lista todos os produtos existentes no sistema por ordem crescente de pre?o*/
void d_l(){
    int num;
    for (int i = 0; i < prodcor; ++i) {
        for (int j = 0; j < prodcor; ++j) {
            if (vetorprodutos[i].preco>vetorprodutos[i+1].preco){
                ordenado[i]=vetorprodutos[i];
                vetorprodutos[i]=vetorprodutos[i+1];
                vetorprodutos[i+1]=ordenado[i];
            }
        }

    }
    for (int k = 0; k < prodcor; ++k) {
        printf("%s %d %d\n", vetorprodutos[k].descricao, vetorprodutos[k].preco, vetorprodutos[k].qtd);
    }
}
void d_L(){
}
/* Funcao Main com um loop que termina com o comando x e estrutura condicional (switch) com uma vari?vel (Comando) que
 * caso a introducao de um caracter, um determinado comando ? executado.*/
    int main (){
    int controlador=0;
    while(1) {
        char comando;
        printf("insira o comnado: ");
        scanf("%s", &comando);
        switch (comando) {
            case 'a':
                d_a();
                break;
            case 'q':
                d_q();
                break;
            case 'N':
                d_N();break;
            case 'A':
                d_A();break;
            case 'r':
                d_r();break;
            case 'R':
                d_R();break;
            case 'C':
                d_C();break;
            case 'p':
                d_p();break;
            case 'E':
                d_E();break;
            case 'm':
                d_m();break;
            case 'l':
                d_l();break;
            case 'L':
                d_L();break;
            case 'x':
                return EXIT_SUCCESS;         /* termina o programa*/
            default:
                printf("ERRO: Comando l [%c] desconhecido\n",comando);
                break;
        }
    }
}



