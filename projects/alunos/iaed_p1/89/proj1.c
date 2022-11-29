#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Limites */
#define stringmax 63  /* maximo de caracteres na descricao dum produto */
#define idmaxp 10000  /* maximo de produtos */
#define idmaxen 500   /* maximo de encomendas*/
#define pesomax 200   /* peso maximo de uma encomenda */
#define idmaxp_en 200 /* maximo de produtos por encomenda */
#define cmdmax 100    /* maximo de caracteres por comando (pois este vai estar num vetor) */

/* Flags */
#define False 0
#define True 1
#define CMPprecos 0
#define CMPdescricoes 1

typedef struct{
    int id;
    char descricao[stringmax];
    int preco;
    int peso;
    int quantidade;
} Produto;

typedef struct {
    Produto produtos[idmaxp_en];
    int index;   /* diz-nos o numero de produtos numa encomenda */
    int preco;   /* preco total de todos os produtos na encomenda */
    int peso;    /* peso total de totos os produtos na encomenda */
} Encomenda;

/* Prototipos */
void adiciona_produto(char cmd[]);
void adiciona_stock(char cmd[]);
void cria_encomenda();  
void adiciona_produto_encomenda(char cmd[]);
void remove_stock(char cmd[]);
void remove_produto_encomenda(char cmd[]);
void custo_encomenda(char cmd[]);
void altera_preco(char cmd[]);
void lista_descricao_quantidade(char cmd[]);
void lista_encomenda(char cmd[]);
void ordena_produtos();
void ordena_alfabetico(char cmd[]);
void mergesort(Produto vetor[], int esq, int dir, int cmp);
void merge(Produto vetor[], int esq, int m, int dir, int cmp); 
int compara_menor(Produto p1, Produto p2, int cmp);

Produto idproduto[idmaxp];       /* vetor onde vao ser colocados os produtos, organizados por id */
Encomenda idencomenda[idmaxen];  /* vetor onde vao ser colocadas as encomendas, organizadas por id */
Produto aux[idmaxp];             /* vetor auxiliar do merge/mergesort */ 
int indexidp, indexiden;         /* contadores para a quantidade de produtos e de encomendas no sistema */

/* vai ler o input do utilizador e executar o comando devido */
int main(){
    char cmd[cmdmax]={0};
    while (cmd[0]!='x'){
        scanf(" %[^\n]", cmd);
        switch (cmd[0]){
            case 'a':
                adiciona_produto(cmd);
                break;
            case 'q':
                adiciona_stock(cmd);
                break;
            case 'N':
                cria_encomenda();
                break;
            case 'A':
                adiciona_produto_encomenda(cmd);
                break;
            case 'r':
                remove_stock(cmd);
                break;
            case 'R':
                remove_produto_encomenda(cmd);
                break;
            case 'C':
                custo_encomenda(cmd);
                break;
            case 'p':
                altera_preco(cmd);
                break;
            case 'E':
                lista_descricao_quantidade(cmd);
                break;
            case 'm':
                lista_encomenda(cmd);
                break;
            case 'l':
                ordena_produtos();
                break;
            case 'L':
                ordena_alfabetico(cmd);
                break;
            default:
                break;
        }
    }
    return 0;
}

/* adiciona um novo produto ao sistema */
void adiciona_produto(char cmd[]){
    Produto res;
    sscanf(cmd, "a %[^:]:%d:%d:%d", res.descricao, &res.preco, &res.peso, &res.quantidade);
    res.id=indexidp;
    idproduto[indexidp]=res;
    printf("Novo produto %d.\n", indexidp);
    indexidp++;
}

/* adiciona stock a um produto existente no sistema */
void adiciona_stock(char cmd[]){
    int idp, qtd;
    sscanf(cmd, "q %d:%d", &idp, &qtd);
    if (idp>=indexidp){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);   
        return;
    }
    idproduto[idp].quantidade+=qtd;
}

/* cria uma nova encomenda */
void cria_encomenda(){
    printf("Nova encomenda %d.\n", indexiden);
    indexiden++;
}

/* adiciona um produto a uma encomenda */
void adiciona_produto_encomenda(char cmd[]){
    int i, iden, idp, qtd;
    sscanf(cmd, "A %d:%d:%d", &iden, &idp, &qtd);
    if (iden>=indexiden){ 
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, iden);
        return;
    }
    if (idp>=indexidp){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, iden);
        return;
    }
    if (qtd>idproduto[idp].quantidade){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, iden);
        return;
    }
    /* verificar se o peso do produto, quando adicionado ao peso total da encomenda, nao supera o limite */
    if (idproduto[idp].peso*qtd + idencomenda[iden].peso>pesomax){ 
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, iden);
        return;
    }
    /* remocao no stock de produto da quantidade pedida para a encomenda */
    idproduto[idp].quantidade-=qtd; 
    /* adicionar o peso e o preco do produto ao peso e preco total da encomenda */
    idencomenda[iden].preco+=idproduto[idp].preco*qtd;
    idencomenda[iden].peso+=idproduto[idp].peso*qtd;
    for (i=0; i<idencomenda[iden].index; i++){ 
        /* verificar se o produto ja se encontra na encomenda ao comparar o id do mesmo 
        com a de todos os produtos ja presentes na encomenda */
        if (idencomenda[iden].produtos[i].id==idproduto[idp].id){
            idencomenda[iden].produtos[i].quantidade+=qtd;
            return;    
        }
    }
    /*se o produto nao estiver ja na encomeda, adiciona-lo */
    idencomenda[iden].produtos[idencomenda[iden].index]=idproduto[idp];
    idencomenda[iden].produtos[idencomenda[iden].index].quantidade=qtd;
    idencomenda[iden].index++;    
}

/* remove stock a um produto existente no sistema */
void remove_stock(char cmd[]){
    int idp, qtd;
    sscanf(cmd, "r %d:%d", &idp, &qtd);
    if (idp>=indexidp){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);   
        return;
    }
    if (qtd>idproduto[idp].quantidade){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
    }
    idproduto[idp].quantidade-=qtd;
}

/* remove um produto de uma encomenda */
void remove_produto_encomenda(char cmd[]){
    int i, indexremove, iden, idp;
    int flag=False; /* flag que indica se o produto existe na encomenda (True) ou nao (False) */
    sscanf(cmd, "R %d:%d", &iden, &idp);
    if (iden>=indexiden){ 
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, iden);
        return;
    }
    if (idp>=indexidp){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, iden);
        return;
    }
    for (i=0; i<idencomenda[iden].index; i++){
        if (idencomenda[iden].produtos[i].id==idproduto[idp].id){
            indexremove=i;
            flag=True;
            /* como cada indice tem um produto diferente, nao e preciso continuar a procura */
            break; 
        }  
    }
    if (flag==False) 
        return;
    /* remocao do preco e peso do produto do preco e peso total da encomenda */
    idencomenda[iden].preco-=idencomenda[iden].produtos[indexremove].preco*idencomenda[iden].produtos[indexremove].quantidade;
    idencomenda[iden].peso-=idencomenda[iden].produtos[indexremove].peso*idencomenda[iden].produtos[indexremove].quantidade;
    /* voltar a colocar em stock a quantidade desse produto que estava na encomenda */
    idproduto[idp].quantidade+=idencomenda[iden].produtos[indexremove].quantidade;
    /* deslocar cada produto que se segue ao que queremos remover um indice para tras
    de modo a que esse seja overwritten, sendo portanto removido */
    for (i=indexremove; i<idencomenda[iden].index; i++)
        idencomenda[iden].produtos[i]=idencomenda[iden].produtos[i+1];
    idencomenda[iden].index--;
}

/* indica o preco total de uma encomenda */
void custo_encomenda(char cmd[]){
    int iden, custo;
    sscanf(cmd, "C %d", &iden);
    if (iden>=indexiden){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", iden);
        return;
    }
    custo=idencomenda[iden].preco;
    printf("Custo da encomenda %d %d.\n", iden, custo);
}

/* altera o preco de um produto no sistema (no stock e em qualquer encomenda em que esteja) */
void altera_preco(char cmd[]){
    int idp, iden, preco, prod;
    sscanf(cmd, "p %d:%d", &idp, &preco);
    if (idp>=indexidp){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }
    idproduto[idp].preco=preco;
    for (iden=0; iden<indexiden; iden++){
        for (prod=0; prod<idencomenda[iden].index; prod++){
            if (idencomenda[iden].produtos[prod].id==idproduto[idp].id){
                /* retirar o preco do produto ao preco total da encomenda e de seguida adicionar o novo preco */
                idencomenda[iden].preco-=idencomenda[iden].produtos[prod].preco*idencomenda[iden].produtos[prod].quantidade;
                idencomenda[iden].produtos[prod].preco=preco;
                idencomenda[iden].preco+=preco*idencomenda[iden].produtos[prod].quantidade;
                break;     
            } 
        }
    }
}

/* indica a descricao e a quantidade de um produto numa dada encomenda */
void lista_descricao_quantidade(char cmd[]){
    int idp, iden, prod, qtd;
    int flag=False;   /* flag que indica se o produto existe na encomenda ou nao */
    sscanf(cmd, "E %d:%d", &iden, &idp);
    if (iden>=indexiden){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", iden);
        return;
    }
    if (idp>=indexidp){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }
    for (prod=0; prod<idencomenda[iden].index; prod++){
        if (idencomenda[iden].produtos[prod].id==idproduto[idp].id){
            qtd=idencomenda[iden].produtos[prod].quantidade;
            flag=True;
            break;
        }
    }
    if (flag==False)
        qtd=0;
    printf("%s %d.\n", idproduto[idp].descricao, qtd);
}

/* indica o id da encomenda que contem maior quantidade de um dado produto */
void lista_encomenda(char cmd[]){
    int idp, iden, prod, idenmaior, qtdmaior=0;
    sscanf(cmd, "m %d", &idp);
    if (idp>=indexidp){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }
    /* dar return sem imprimir nada no caso de nao haver encomendas */
    if (!indexiden)
        return;
    for (iden=0; iden<indexiden; iden++){
        for (prod=0; prod<idencomenda[iden].index; prod++){
            if (idencomenda[iden].produtos[prod].id==idproduto[idp].id){
                if (idencomenda[iden].produtos[prod].quantidade>qtdmaior){
                    qtdmaior=idencomenda[iden].produtos[prod].quantidade;
                    idenmaior=iden;
                }
                break;
            }
        }
    }
    /* devolver sem imprimir nada se o produto nao existe em nenhuma encomenda */
    if (!qtdmaior)
        return;
    printf("Maximo produto %d %d %d.\n", idp, idenmaior, qtdmaior);
}

/* lista todos os produtos existentes no sistema por ordem crescente de preco */
void ordena_produtos(){
    Produto res[idmaxp]={0};
    int i; 
    /* criar uma copia do vetor de produtos e ordenar essa copia
    de modo a nao desorganizar o vetor original */   
    for (i=0; i<indexidp; i++)
        res[i]=idproduto[i];
    mergesort(res, 0, indexidp-1, CMPprecos);
    puts("Produtos");
    for (i=0; i<indexidp; i++)
        printf("* %s %d %d\n", res[i].descricao, res[i].preco, res[i].quantidade);
}

/* lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
void ordena_alfabetico(char cmd[]){
    Produto res[idmaxp_en]={0};
    int i, iden;
    sscanf(cmd, "L %d", &iden);
    if (iden>=indexiden){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", iden);
        return;
    }
    printf("Encomenda %d\n", iden);
    /* se o peso da encomenda for 0, e porque esta nao tem nenhum produto */
    if (!idencomenda[iden].peso)
        return;
    for (i=0; i<idencomenda[iden].index; i++)
        res[i]=idencomenda[iden].produtos[i];
    mergesort(res, 0, idencomenda[iden].index-1, CMPdescricoes);
    for (i=0; i<idencomenda[iden].index; i++)
        printf("* %s %d %d\n", res[i].descricao, res[i].preco, res[i].quantidade);
}

/* funcao de ordenacao que vai dividir o vetor de input em metades 
e, juntamente com a funcao merge, voltar a junta-las, agora ordenadas */
void mergesort(Produto vetor[], int esq, int dir, int cmp){
    int m =(esq+dir)/2;
    if (dir<=esq) 
        return;
    mergesort(vetor, esq, m, cmp);
    mergesort(vetor, m+1, dir, cmp);
    merge(vetor, esq, m, dir, cmp);
}

/* junta dois vetores ordenados num so vetor ordenado */
void merge(Produto vetor[], int esq, int m, int dir, int cmp){
    int i, j, k;
    for (i=m+1; i>esq; i--)
        aux[i-1]=vetor[i-1];
    for (j=m; j<dir; j++)
        aux[dir+m-j]=vetor[j+1];
    for (k=esq; k<=dir; k++){
        if (compara_menor(aux[j], aux[i], cmp) || i>m)
            vetor[k]=aux[j--];
        else
            vetor[k]=aux[i++];
    }
}

/* compara precos ou descricoes de dois produtos (de acordo com
a flag cmp), e devolve True se o primeiro for menor que o segundo */
int compara_menor(Produto p1, Produto p2, int cmp){
    if (cmp==CMPprecos && p1.preco<p2.preco)
        return True;
    if (cmp==CMPdescricoes && strcmp(p1.descricao, p2.descricao)<0)
        return True;
    return False;
}