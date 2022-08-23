#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 10000
#define MAX_DESCRICAO 64
#define MAX_ENCOMENDAS 500

typedef struct
{
    int id;
    char* descricao[MAX_DESCRICAO];
    int preco;
    int peso;
    int stock;
} Produto;

typedef struct
{
    int id;
    Produto produtosEncomenda[200];
    int numeroProdutos;
} Encomenda;



void novoProduto(char* descricao, int preco, int peso, int quantidade);
void adicionaStock(int idp, int quantidade);
void novaEncomenda();
void adicionaProduto(int ide, int idp, int quantidade);
void removeStockProduto(int idp, int quantidade);
void removeProdutoEncomenda(int ide, int idp);
void custoEncomenda(int ide);
void alteraPreco(int idp, int preco);
void listaProdutoEncomenda(int ide, int idp);
void encomendaComMaisProduto(int idp);
void listaTodosProdutos();
void listaTodosProdutosEncomenda(int ide);
void terminaPrograma();

int id_prod = 0;
int id_enc = 0;
Produto produtos[MAX_PRODUTOS];
Encomenda encomendas[MAX_ENCOMENDAS];

int main()
{
    char arg[MAX_DESCRICAO], command;
    int arg2, arg3, arg4;

    while(1){
        scanf("%c", &command);
        switch (command)
        {

            case 'a':
                /*novo produto*/
                scanf("%[^:]:%d:%d:%d", arg, &arg2, &arg3, &arg4);
                novoProduto(arg ,arg2, arg3,arg4);
                break;

            case 'q':
                scanf("%d:%d", &arg2, &arg3);
                adicionaStock(arg2, arg3);
                /*adicionar stock*/
                break;

            case 'N':
                novaEncomenda();
                /*nova encomenda*/
                break;

            case 'A':
                /*adiciona produto a encomenda*/
                scanf("%d:%d:%d", &arg2, &arg3, &arg4);
                adicionaProduto(arg2, arg3, arg4);

                break;

            case 'r':
                /*remove stock*/
                scanf("%d:%d", &arg2, &arg3);
                removeStockProduto(arg2, arg3);
                break;

            case 'R':
                /*remove produto da encomenda*/
                scanf("%d:%d", &arg2, &arg3);
                removeProdutoEncomenda(arg2,arg3);
                break;

            case 'C':
                /*calcula custo encomenda*/
                scanf("%d", &arg2);
                custoEncomenda(arg2);
                break;

            case 'p':
                /*altera pre?o produto*/    
                scanf("%d:%d", &arg2, &arg3);
                alteraPreco(arg2,arg3);
                break;

            case 'E':
                /*lista a descri??o e a quantidade de um produto na encomenda*/ 
                scanf("%d:%d", &arg2, &arg3);
                listaProdutoEncomenda(arg2, arg3);
                break;

            case 'm':
                /*lista o identificador da encomenda em que o produto ocorre mais vezes*/
                scanf("%d", &arg2);
                encomendaComMaisProduto(arg2);
                break;

            case 'l':
                /*lista todos os produtos por ordem crescente de pre?o*/
                listaTodosProdutos();
                break;

            case 'L':
                /*lista todos os produtos de uma encomenda*/
                scanf("%d", &arg2);
                listaTodosProdutosEncomenda(arg2);
                break;

            case 'x':
                /*termina programa*/
                terminaPrograma();
                break;

            default:
                break;
            };
    };
    return -1;
}

/*a*/
void novoProduto(char* descricao, int preco, int peso, int quantidade){
    Produto prod;
    prod.id = id_prod;
    prod.descricao[MAX_DESCRICAO] = descricao;
    prod.preco = preco;
    prod.peso = peso;
    prod.stock = quantidade;

    produtos[id_prod] = prod;

    printf("Novo produto %d\n", id_prod);

    id_prod++;
}

/*q*/
void adicionaStock(int idp, int quantidade){
    int p;
    for (p=0; p<MAX_PRODUTOS; p++){
        if (produtos[p].id == idp){
            produtos[idp].stock += quantidade;
            break;
        }
    }
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

/*N*/
void novaEncomenda(){
    Encomenda enc;
    enc.id = id_enc;
    enc.numeroProdutos = 0;
    encomendas[id_enc] = enc;

    printf("Nova encomenda %d\n", id_enc);

    id_enc++;
}

/*A*/
void adicionaProduto(int ide, int idp, int quantidade){
    /*talvez isto n?o possa ser assim e ter que ser que criar um novo e igualar todos os dados*/
    encomendas[ide].produtosEncomenda[encomendas[ide].numeroProdutos] = produtos[idp];
    
    encomendas[ide].produtosEncomenda[encomendas[ide].numeroProdutos].stock = quantidade;
    encomendas[ide].numeroProdutos++;
}

/*r*/
void removeStockProduto(int idp, int quantidade){
    int p;
    for (p=0; p<MAX_PRODUTOS; p++){
        if (produtos[p].id == idp){
            
            if (produtos[idp].stock - quantidade < 0){
                printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
                break;
            }
            else{
                produtos[idp].stock -= quantidade;
                break;
            }

        }
    }
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);  
}

/*R*/
void removeProdutoEncomenda(int ide, int idp){
    int p, q, e, aux, c;
    for (q=0; q<MAX_PRODUTOS; q++){
        if (produtos[q].id == idp){/*ve se produto existe*/
            for (e = 0; e < MAX_ENCOMENDAS; e++ ){
                if (encomendas[e].id == ide){ /*ve se encomenda existe*/
                    for (p = 0; p < encomendas[ide].numeroProdutos; p++ ){
                        if (encomendas[p].id == idp){
                            aux = p;
                        }
                    }
                    for (c = aux; c<encomendas[ide].numeroProdutos; c++){
                        encomendas[ide].produtosEncomenda[c] = encomendas[ide].produtosEncomenda[c+1];
                    }
                    break;
                }
            }
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        break;
        }   
    }
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
}

/*C*/
void custoEncomenda(int ide){
    int custo;
    int p, e;
    for (e = 0; e < MAX_ENCOMENDAS; e++ ){
        if (encomendas[e].id == ide){
            for (p = 0; p < encomendas[ide].numeroProdutos; p++ )
                custo += encomendas[ide].produtosEncomenda[p].preco;
            printf("Custo da encomenda %d %d.\n", ide, custo);
            break;
        }
    }
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide); 
}

/*p*/
void alteraPreco(int idp, int preco){
    int p;
    for (p=0; p<MAX_PRODUTOS; p++){
        if (produtos[p].id == idp){
            produtos[p].preco = preco;
            break;
        }
    }
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}

/*E*/
void listaProdutoEncomenda(int ide, int idp){
    int p, q,e;
    for (q=0; q<MAX_PRODUTOS; q++){
        if (produtos[q].id == idp){/*ve se o produto existe*/
            for (e = 0; e < MAX_ENCOMENDAS; e++ ){
                if (encomendas[e].id == ide){ /*ve se encomenda existe*/
                    for (p = 0; p < encomendas[ide].numeroProdutos; p++ ){
                        if (encomendas[ide].produtosEncomenda[p].id == idp)
                                printf("%s %d.\n", *encomendas[ide].produtosEncomenda[p].descricao, encomendas[ide].produtosEncomenda[p].stock);
                    }
                    break;
                }
            }
            printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
            break;
        }
    }
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);   
}

/*m*/
void encomendaComMaisProduto(int idp){
    int e, p, q;
    int aux_qtd, aux_nr_enc;

    for (q=0; q<MAX_PRODUTOS; q++){
        if (produtos[q].id == idp){
            for (e = 0; e < MAX_ENCOMENDAS; e++ ){
                for (p = 0; p < encomendas[e].numeroProdutos; p++ ){
                    if (encomendas[e].produtosEncomenda[p].id == idp){
                        if(encomendas[e].produtosEncomenda[p].stock >= aux_qtd){
                            aux_qtd = encomendas[e].produtosEncomenda[p].stock;
                            aux_nr_enc = e;
                        }  
                    }
                }
            }
            printf("Maximo produto %d %d %d.\n", idp, aux_nr_enc, aux_qtd);
            break;
        }
    }
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
}


void listaTodosProdutos(){
    
}

void listaTodosProdutosEncomenda(int ide){
    int p;
    p = ide;
    printf("ola %d", p);
}

void terminaPrograma(){
    
}




