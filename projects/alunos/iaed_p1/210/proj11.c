#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
/* The maximum number of values products */
#define MAXPRODUTOS 9999
/* The maximum number of values characters by description 63 + '\0' */
#define MAXDESCRICOES 64
/* The maximum number of values orders */
#define MAXECOMENDAS 500
/* The maximum number of values weight of an order */
#define MAXPESOENCOMENDA 200
/* The characteristic of A used as the A itself */
#define key(A) (A)
/* Compare A to B, A<B*/
#define less(A, B) (key(A) < key(B))

/* Product */
typedef struct {
    int id;
    char descricao[MAXDESCRICOES];
    int preco;
    int peso;
    int stock;
} Produto;

/* Order */
typedef struct {
    Produto produtosNumaEcomenda[MAXPRODUTOS];
} Encomenda;

/* Array of product */
Produto produtos[MAXPRODUTOS];  
/* Array of order */
Encomenda encomendas[MAXECOMENDAS];
/* The number of values products or orders */
int produtoID = 0, encomendaID = 0;
/* The number of values products in order */
int numProdutosNumaEcomenda[MAXECOMENDAS] = {0};

/* Adds a new product to the system */
void adicionaNovoProduto();
/* Adds stock to an existing product in the system */
void adicionaStock();
/* Creates a new order */
void criaNovoEncomenda();
/* Adds a product to an order */
void adicionaProdutoNumEncomenda();
/* Removes stock from an existing product */
void removeStockDeProduto();
/* Removes a product from an order */
void removeProdutoNumaEncomenda();
/* Calculates the cost of an order */
void calculaCustaDaEncomenda();
/* Changes the price of an existing product in the system */
void alteraPrecoDoProduto();
/* Returns the description and quantity of a product in a given order */
void listaDescricaoQuantidadeDeProduto();
/* Returns the identifier of the order in which a given product occurs more often */
void listaIdEncomendaEmQueProdutoOcorreMaisVezes();
/* Lists all products in the system in ascending price order */
void listaTodosOsProdutosExistentes();
/* Lists all products of an order in alphabetical order from the description */
void listaTodosProdutosNumaEncomenda();

/* SelectSort for organizes all products of an order in alphabetical order from the description */
void selectionSort(Produto p[], int num);
/* seach Id of this product in this order*/
int seachIdProdutoNumaEncomenda(int ide,int idp);
/* Calcule weight of order*/
int pesoTotalDaEncomenda(int ide,int idp,int quantidade);
/* MergeSort for organizes all products in ascending order of product id */
void mergesort(Produto a[], int left, int right);
void merge(Produto a[], int left, int m, int right);

/*  ler os dados de entrada a partir da linha de comandos */
int main() {
    char comando;
    
    do{
        comando = getchar();
        switch(comando) {
            case 'a':
                adicionaNovoProduto();
                break;
            case 'q':
                adicionaStock();
                break;
            case 'N':
                criaNovoEncomenda();
                break;
            case 'A':
                adicionaProdutoNumEncomenda();
                break;
            case 'r':
                removeStockDeProduto();
                break;
            case 'R':
                removeProdutoNumaEncomenda();
                break;
            case 'C':
                calculaCustaDaEncomenda();
                break;
            case 'p':
                alteraPrecoDoProduto();
                break;
            case 'E':
                listaDescricaoQuantidadeDeProduto();
                break;
            case 'm':
                listaIdEncomendaEmQueProdutoOcorreMaisVezes();
                break;
            case 'l':
                listaTodosOsProdutosExistentes();
                break;
            case 'L':
                listaTodosProdutosNumaEncomenda();
                break;
        }
    
    } while(comando != 'x');
    /* ends the program */
    return 0;
}

void adicionaNovoProduto() {
    scanf(" %[^:]:%d:%d:%d",produtos[produtoID].descricao, &produtos[produtoID].preco, &produtos[produtoID].peso, &produtos[produtoID].stock);
    printf("Novo produto %d.\n",produtoID);
    produtos[produtoID].id = produtoID;
    produtoID++;
}

void adicionaStock() {
    int id, quantidadeStock;
    scanf("%d:%d",&id,&quantidadeStock);
    if(id<0||id>produtoID-1) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
    } else {
        produtos[id].stock += quantidadeStock; 
    }
}

void criaNovoEncomenda() {
    printf("Nova encomenda %d.\n", encomendaID);
    encomendaID++;
}

void adicionaProdutoNumEncomenda() {
    int ide, idp, quantidade,num;
    
    scanf("%d:%d:%d",&ide,&idp,&quantidade);
    if(ide<0||ide>encomendaID-1) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    } else if(idp< 0 || idp>produtoID-1) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    } else if(produtos[idp].stock<quantidade) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    } else if(pesoTotalDaEncomenda(ide,idp,quantidade)>MAXPESOENCOMENDA){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    } else {
        num = seachIdProdutoNumaEncomenda(ide,idp);
        if(num==-1) {
            encomendas[ide].produtosNumaEcomenda[numProdutosNumaEcomenda[ide]].id = idp;
            encomendas[ide].produtosNumaEcomenda[numProdutosNumaEcomenda[ide]].preco = produtos[idp].preco;
            encomendas[ide].produtosNumaEcomenda[numProdutosNumaEcomenda[ide]].peso = produtos[idp].peso;
            encomendas[ide].produtosNumaEcomenda[numProdutosNumaEcomenda[ide]].stock = quantidade;
            strcpy(encomendas[ide].produtosNumaEcomenda[numProdutosNumaEcomenda[ide]].descricao, produtos[idp].descricao);
            produtos[idp].stock -= quantidade;
            numProdutosNumaEcomenda[ide]++;
        } else {
            encomendas[ide].produtosNumaEcomenda[num].stock += quantidade;
            produtos[idp].stock -= quantidade;
        }
        
    }
}

int pesoTotalDaEncomenda(int ide,int idp,int quantidade) {
    int i,total=0;
    for(i=0;i<numProdutosNumaEcomenda[ide];i++) {
        total+=encomendas[ide].produtosNumaEcomenda[i].stock * encomendas[ide].produtosNumaEcomenda[i].peso;
    }
    total += quantidade * produtos[idp].peso;
    return total;
}

void removeStockDeProduto() {
    int idp, quantidade;
    scanf("%d:%d",&idp,&quantidade);
    if(idp< 0 || idp>produtoID-1) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    } else if(produtos[idp].stock<quantidade) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
    } else {
        produtos[idp].stock-=quantidade;
    }

}

void removeProdutoNumaEncomenda(){
    int ide, idp;
    scanf("%d:%d",&ide,&idp);
    if(ide<0||ide>encomendaID-1) {
         printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    } else if(idp< 0 || idp>produtoID-1) {
         printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }else {
          int num = seachIdProdutoNumaEncomenda(ide,idp);
          if(num!=-1) {
              produtos[idp].stock+= encomendas[ide].produtosNumaEcomenda[num].stock;
              encomendas[ide].produtosNumaEcomenda[num].stock=0;
        } 
    }
}

void calculaCustaDaEncomenda() {
    int ide,i,total=0;
    scanf("%d",&ide);
    if(ide<0||ide>encomendaID-1) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
    } else {
        int num = numProdutosNumaEcomenda[ide];
        for(i=0;i<num;i++) {
            total+=  encomendas[ide].produtosNumaEcomenda[i].preco*encomendas[ide].produtosNumaEcomenda[i].stock;
        }
        printf("Custo da encomenda %d %d.\n",ide,total);
    }
}

void alteraPrecoDoProduto() {
    int idp, preco,i;
    scanf("%d:%d",&idp,&preco);
    if(idp< 0 || idp>produtoID-1) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    } else {
        produtos[idp].preco = preco;
        for(i=0;i<encomendaID;i++) {
           int num = seachIdProdutoNumaEncomenda(i,idp);
           if(num!=-1) {
               encomendas[i].produtosNumaEcomenda[num].preco = preco;
           } 
        }
    }
}

void listaDescricaoQuantidadeDeProduto() {
    int ide, idp;

    scanf("%d:%d", &ide, &idp);
    if(ide<0||ide>encomendaID-1) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    } else if(idp< 0 || idp>produtoID-1) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    } else {
        int id = seachIdProdutoNumaEncomenda(ide,idp);
        if(id!=-1) {
            printf("%s %d.\n",encomendas[ide].produtosNumaEcomenda[id].descricao,encomendas[ide].produtosNumaEcomenda[id].stock);
        } else {
            printf("%s %d.\n",produtos[idp].descricao,0);
        }
    }
}

int seachIdProdutoNumaEncomenda(int ide,int idp) {
    int i;
    for(i=0;i<numProdutosNumaEcomenda[ide];i++) {
        if(encomendas[ide].produtosNumaEcomenda[i].id==idp) {
             return i;
        }
    }
    return -1;
}

void listaIdEncomendaEmQueProdutoOcorreMaisVezes() {
    int idp;
    scanf("%d",&idp);
    if(idp< 0 || idp>produtoID-1) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    } else {
        int i,j,contador=0,idP,id,v[MAXECOMENDAS],max=-1,maxIdE,maxIdP;
        for(i=0;i<encomendaID;i++) {
            idP = seachIdProdutoNumaEncomenda(i,idp);
            if(idP!=-1) {
                v[contador]=i;
                contador ++;
            }
        }
        for(j=0;j<contador;j++) {
            id = seachIdProdutoNumaEncomenda(v[j],idp);
            if(max<encomendas[v[j]].produtosNumaEcomenda[id].stock) {
                max = encomendas[v[j]].produtosNumaEcomenda[id].stock;
                maxIdE=v[j];
                maxIdP=id;
            }
        }
        
        if(contador>0&&encomendas[maxIdE].produtosNumaEcomenda[maxIdP].stock!=0) {
            printf("Maximo produto %d %d %d.\n",idp,maxIdE,encomendas[maxIdE].produtosNumaEcomenda[maxIdP].stock);
        }
        
    }
    
}

void listaTodosOsProdutosExistentes() {
    /* Copy orginal vector */
    Produto p[MAXPRODUTOS];
    int x,i;
    for(x = 0;x<produtoID;x++) {
        p[x]=produtos[x];
    }
    /* Organize vetor */
    mergesort(p, 0, produtoID-1);
    
    printf("Produtos\n");
    for(i=0;i < produtoID;i++ ) {
        printf("* %s %d %d\n",p[i].descricao, p[i].preco, p[i].stock);
    }
    
}




void mergesort(Produto a[], int left, int right) {
    int m = (right+left)/2;
    if (right <= left) 
    return;
    mergesort(a, left, m);
    mergesort(a, m+1, right); 
    merge(a, left, m, right);
}

void merge(Produto a[], int left, int m, int right) {
    Produto aux[MAXPRODUTOS];
    int i, j, k;
    for (i = m+1; i >left; i--)
        aux[i-1] = a[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = a[j+1]; 
    for (k = left; k <= right; k++)
        if (less(aux[j].preco, aux[i].preco)) {
             a[k] = aux[j--];
        } else if (less(aux[i].preco, aux[j].preco)) {
            a[k] = aux[i++];
        } else {
            if(less(aux[j].id,aux[i].id)) {
                a[k] = aux[j--];
            } else {
                a[k] = aux[i++];
            }
        }         
}

void listaTodosProdutosNumaEncomenda() {
    int ide;
    scanf("%d",&ide);
    if(ide<0||ide>encomendaID-1) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    } else {
         /* Copy orginal vector */
        Produto p[MAXPRODUTOS];
        int x,i;
        int num = numProdutosNumaEcomenda[ide];
        for(x = 0;x<num;x++) {
            p[x]=encomendas[ide].produtosNumaEcomenda[x];
        }
        /* Organize vetor */
        selectionSort(p,num);
        printf("Encomenda %d\n",ide);
        for(i=0;i < num; i++) {
            if(p[i].stock!=0) {
                 printf("* %s %d %d\n",p[i].descricao, p[i].preco, p[i].stock);
            }
        }

    }
   

}

void selectionSort(Produto p[], int num) {
    int i, j;
    for (i=0;i<num;i++) {
        Produto aux;
        int min =i;
        for(j = i+1; j<num;j++) {
            if(strcmp(p[j].descricao,p[min].descricao)<0) {
                min = j;
            }
        }
        aux = p[i];
        p[i] = p[min]; 
        p[min] = aux;
    }  
}

