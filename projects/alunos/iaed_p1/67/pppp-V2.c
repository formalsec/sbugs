#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define MAX_PROD_POR_ENCOMENDAS 200
#define MAX_DESCRICAO 64

#define SIM 1
#define NAO 0

void a();
void q();
void N();
void A();
void r();
void R();
void C();
void p();
void E();
void m();
void l();
void L();

void mergesort(int a[], int left, int right, int prod[]);
void merge(int a[], int left, int m, int right, int prod[]);

struct Produto{
    int numero;
    char descricao[MAX_DESCRICAO];
    int preco,peso,quantidade;
};

struct Encomenda{
    int produtos[MAX_PROD_POR_ENCOMENDAS],quantidade[MAX_PROD_POR_ENCOMENDAS],numero_produtos,peso;
};

/* Variaveis Globais*/

struct Produto Prod[MAX_PRODUTOS]; /* Inicializa estruturas de produtos */
struct Encomenda Encom[MAX_ENCOMENDAS]; /* Inicializa estruturas de encomendas */
int identificador_produtos=0,identificador_encomendas=0; /* Dois contadores que contam o numero de produtos e encomendas adicionados ao sistema */

int main(){
    char n;
    for(n=getchar();n!='x';n=getchar()){  /*Ciclo que verifica o primeiro caracter de cada linha e manda para a funcao apropriada */
        if ( n =='a'){
            n=getchar();
            a();
        }
        else if ( n == 'q'){
            n=getchar();
            q();
        }
        else if ( n == 'N'){
            N();
        }
        else if ( n == 'A'){
            n=getchar();
            A();
        }
        else if ( n == 'r'){
            n=getchar();
            r();
        } 
        else if ( n == 'R'){
            n=getchar();
            R();
        }
        else if ( n == 'C'){
            n=getchar();
            C();
        }
        else if ( n == 'p'){
            n=getchar();
            p();
        }
        else if ( n == 'E'){
            n=getchar();
            E();
        }
        else if ( n == 'm'){
            n=getchar();
            m();
        }
        else if ( n == 'l'){
            l();
        }
        else if ( n == 'L'){
            getchar();
            L();
        }
        for(;n!='\n';)
            n=getchar();
    }
    return 0;
}

void a(){ /* Funcao que adiciona um produto novo ao sistema*/
    char nome[MAX_DESCRICAO];
    int preco,peso,qtd;
    scanf("%[^:]:%d:%d:%d", nome, &preco, &peso, &qtd);
    strcpy(Prod[identificador_produtos].descricao, nome);
    Prod[identificador_produtos].numero = identificador_produtos;
    Prod[identificador_produtos].peso = peso;
    Prod[identificador_produtos].preco = preco;
    Prod[identificador_produtos].quantidade = qtd;
    printf("Novo produto %d.\n",identificador_produtos);
    identificador_produtos++; /* Incrementa o numero de produtos no sistema */
}

void q(){ /* Funcao que adiciona stock a um produto existente no sistema*/
    int qtd,iden;
    scanf("%d:%d",&iden, &qtd);
    if (iden < identificador_produtos) /* Se o produto existir, adiciona stock ao produto */
        Prod[iden].quantidade += qtd;
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", iden);
}

void N(){ /* Funcao que cria uma nova encomenda */
    int i;
    Encom[identificador_encomendas].peso=0; /* Inicializa o peso total da encomenda a 0 */
    Encom[identificador_encomendas].numero_produtos=0; /* Inicializa o numero de produtos na encomenda a 0 */
    for (i=0;i<MAX_PROD_POR_ENCOMENDAS;i++) /* Inicializa todos os produtos da encomenda a -1 sabendo que nao existe nenhum produto com este identificador */
        Encom[identificador_encomendas].produtos[i] = -1; 
    printf("Nova encomenda %d.\n",identificador_encomendas);
    identificador_encomendas++; /* Incrementa o numero de encomendas no sistema */
}

void A(){ /* Funcao que adiciona um produto a uma encomenda */
    int iden,encomenda,qtd,i;
    int Existe=NAO; /* Variavel que reflete se um produto ja existe na encomenda ou nao */
    scanf("%d:%d:%d",&encomenda,&iden, &qtd);
    if (identificador_encomendas<=encomenda) /* Se a encomenda nao existir, imprime uma mensagem de erro */
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",iden,encomenda);
    else if (identificador_produtos<=iden) /* Se o produto nao existir, imprime uma mensagem de erro */
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",iden,encomenda);
    else if (qtd>Prod[iden].quantidade) /* Se nao existir stock suficiente do produto, imprime uma mensagem de erro */
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",iden,encomenda);
    else if (Encom[encomenda].peso + (Prod[iden].peso*qtd)>200) /* Caso o peso supere o maximo, imprime uma mensagem de erro */
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",iden,encomenda);
    else{ /* Caso contrario, retira a quantidade de produto ao stock e atualiza o peso */
        Prod[iden].quantidade -= qtd;
        Encom[encomenda].peso += Prod[iden].peso*qtd;
        for (i=0;i<MAX_PROD_POR_ENCOMENDAS;i++) /* Verifica se o produto ja existe na encomenda */
            if (Encom[encomenda].produtos[i]==iden){
                /* Caso exista adiciona a quantidade a quantidade existente, Existe passa a SIM e sai do ciclo */
                Encom[encomenda].quantidade[i]+=qtd;
                Existe=SIM;
                break;
            }
        if (Existe==NAO) /* Caso nao exista, procura o primeiro sitio onde o produto e -1 (vazio) e adiciona o produto e a sua qtd a encomenda */
            for (i=0;i<MAX_PROD_POR_ENCOMENDAS;i++)
                if (Encom[encomenda].produtos[i]==-1){
                    Encom[encomenda].produtos[i] = iden;
                    Encom[encomenda].quantidade[i]=qtd;
                    Encom[encomenda].numero_produtos+=1; /* Incrementa o numero de produtos na encomenda */
                    break;
                }
    }
}

void r(){ /* Funcao que remove stock a um produto existente */
    int iden,qtd;
    scanf("%d:%d",&iden,&qtd);
    if (iden>=identificador_produtos) /* Se o produto nao existir, imprime uma mensagem de erro */
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",iden);
    else if (qtd>Prod[iden].quantidade) /* Se nao existir stock suficiente, imprime uma mensagem de erro */
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,iden);
    else /* Caso contrario remove a quantidade ao stock */ 
        Prod[iden].quantidade-=qtd;
}

void R(){ /* Funcao que remove um produto de uma encomenda */
    int iden_prod,iden_enc,i;
    scanf("%d:%d",&iden_enc,&iden_prod);
    if (iden_enc>=identificador_encomendas) /* Se a encomenda nao existir, imprime uma mensagem de erro */
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",iden_prod,iden_enc);
    else if (iden_prod>=identificador_produtos) /* Se o produto nao existir, imprime uma mensagem de erro */
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",iden_prod,iden_enc);
    else{ /* Caso contrario, procura o produto na encomenda */
        for (i=0;i<MAX_PROD_POR_ENCOMENDAS;i++)
            if (Encom[iden_enc].produtos[i]==iden_prod){
                Encom[iden_enc].peso-=Prod[iden_prod].peso*Encom[iden_enc].quantidade[i]; /* Atualiza o peso da encomenda */
                Prod[iden_prod].quantidade+=Encom[iden_enc].quantidade[i]; /* Adiciona a quantidade de produto que se encontrava na encomenda ao stock do produto */
                Encom[iden_enc].produtos[i]=-1; /* Passa o produto a -1 para mostrar que se encontra vazio */
                Encom[iden_enc].quantidade[i]=0;
                Encom[iden_enc].numero_produtos-=1; /* Decrementa o numero de produtos na encomenda */
                break;
            }
    }
}

void C(){ /* Funcao que calcula o custo de uma encomenda */
    int iden,total=0,i;
    scanf("%d",&iden);
    if (iden>=identificador_encomendas) /* Se a encomenda nao existir, imprime uma mensagem de erro */ 
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",iden);
    else{ /* Corre os produtos na encomenda e vai adicionando o preco de cada produto ao total */
        for (i=0;i<MAX_PROD_POR_ENCOMENDAS;i++)
            if(Encom[iden].produtos[i]!=-1)
                total+=Prod[Encom[iden].produtos[i]].preco*Encom[iden].quantidade[i];
        printf("Custo da encomenda %d %d.\n",iden,total);
    }
}

void p(){ /* Funcao que altera o preco de um produto existente no sistema */
    int iden,preco;
    scanf("%d:%d",&iden,&preco);
    if (iden>=identificador_produtos) /* Se o produto nao existir, imprime uma mensagem de erro */
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",iden);
    Prod[iden].preco=preco; /* Altera o preco */
}

void E(){ /* Funcao que retorna a descricao e a quanntidade de um produto numa dada encomenda */
    int iden_enc,iden_prod,i;
    scanf("%d:%d",&iden_enc,&iden_prod);
    if (iden_enc>=identificador_encomendas) /* Se a encomenda nao existir, imprime uma mensagem de erro */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",iden_enc);
    else if (iden_prod>=identificador_produtos) /* Se o produto nao existir, imprime uma mensagem de erro */
        printf("Impossivel listar produto %d. Produto inexistente.\n",iden_prod);
    else
        for (i=0;i<MAX_PROD_POR_ENCOMENDAS;i++){/* Percorre os produtos na encomenda */ 
            if (Encom[iden_enc].produtos[i]==iden_prod){ /* Caso o produto exista na encomenda, imprime a sua descricao e quantidade */
                printf("%s %d.\n",Prod[iden_prod].descricao,Encom[iden_enc].quantidade[i]);
                break;
            }
            else if (i==MAX_PROD_POR_ENCOMENDAS-1){ /* Se chegar ao fim dos produtos sem encontrar o produto, imprime a seua descricao e a quantidade igual a zero */
                printf("%s 0.\n",Prod[iden_prod].descricao);
                break;
            }
        }
}

void m(){ /* Funcao que retorna o identificador da encomenda em que um dado produto ocorre mais vezes */
    int iden_prod,enc_max,qtd=-1,i,j;
    int Existe=NAO; /* Variavel que indica se o produto existe em alguma encomenda */
    scanf("%d",&iden_prod);
    if (iden_prod>=identificador_produtos) /* Se o produto nao existir, imprime uma mensagem de erro */
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",iden_prod);
    for (i=0;i<identificador_encomendas;i++) /* Ciclo que percorre as encomendas */
        for (j=0;j<MAX_PROD_POR_ENCOMENDAS;j++) /* Verifica se o produto existe na encomenda */
            if (Encom[i].produtos[j]==iden_prod)
                if (Encom[i].quantidade[j]>qtd){ /* Se a quantidade do produto for maior altera a quantidade maxima e a encomenda */
                    Existe=SIM;
                    enc_max=i;
                    qtd=Encom[i].quantidade[j];
                }
    if (Existe == SIM)
        printf("Maximo produto %d %d %d.\n",iden_prod,enc_max,qtd);                
}

void l(){ /* Funcao que lista todos os produtos existentes no sistema por ordem crescente de preco */
    int numeros[MAX_PRODUTOS],precos[MAX_PRODUTOS],i;
    printf("Produtos\n");
    for (i=0;i<identificador_produtos;i++){ /* Ciclo que cria dois vetores, um com os identificadores e outro com os precos dos produtos */
        numeros[i]=i;
        precos[i]=Prod[i].preco;
    }
    if (identificador_produtos!=0) /* Caso exista pelo menos um produto no sistema, usa mergesort para os ordenar */
        mergesort(precos,0,identificador_produtos-1,numeros);

    for (i=0;i<identificador_produtos;i++) /* Imprime os produtos, o seu preco e a sua quantidade pela ordem por que foram ordenados */
        printf("* %s %d %d\n",Prod[numeros[i]].descricao,precos[i],Prod[numeros[i]].quantidade);
}

void mergesort(int a[], int left, int right, int prod[]){ 
    int m = (right+left)/2;

    if (right<=left)
        return;
    mergesort(a, left, m, prod); 
    mergesort(a, m+1, right, prod); 
    merge(a, left, m, right, prod);
}

void merge(int a[], int left, int m, int right, int prod[]){ 
    int i, j, k;
    int aux_preco[MAX_PRODUTOS],aux_numero[MAX_PRODUTOS];
    for (i = m+1; i > left; i--){ /* Este ciclo e o proximo constroem dois vetores auxiliares */
        aux_preco[i-1] = a[i-1]; 
        aux_numero[i-1] = prod[i-1];
    }
    for (j = m; j < right; j++){
        aux_preco[right+m-j] = a[j+1]; 
        aux_numero[right+m-j] = prod[j+1];
    }
    for (k = left; k <= right; k++){ /* Ordenacao elemento a elemento e construcao do vetor a */
        if (aux_preco[j] < aux_preco[i]){

            a[k] = aux_preco[j]; 
            prod[k] = aux_numero[j--];
        }
        else if(aux_preco[j] == aux_preco[i] && aux_numero[j]<aux_numero[i]){ /* Verificacao necessaria para manter a estabilidade do algoritmo */
            a[k] = aux_preco[j]; 
            prod[k] = aux_numero[j--];
        }
        else{
            a[k] = aux_preco[i]; 
            prod[k] = aux_numero[i++];
        }
    }
}






void L(){ /* Funcao que lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
    int iden_enc,numero_prod;
    scanf("%d",&iden_enc);
    if (iden_enc>=identificador_encomendas) /* Se a encomenda nao existir, imprime uma mensagem de erro */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",iden_enc);
    else{
        printf("Encomenda %d\n",iden_enc);
        numero_prod=Encom[iden_enc].numero_produtos;
        if (numero_prod!=0){
            int produtos[MAX_PROD_POR_ENCOMENDAS],qtd[MAX_PROD_POR_ENCOMENDAS];
            char descricoes[MAX_PROD_POR_ENCOMENDAS][MAX_DESCRICAO];
            int i,j=0;
            for (i=0;i<=MAX_PROD_POR_ENCOMENDAS;i++) /* Ciclo que cria tres vetores, um com as descricoes, um com as quantidades e outro com os identificadores dos produtos na encomenda */
                if (Encom[iden_enc].produtos[i]!=-1){
                    produtos[j]=Encom[iden_enc].produtos[i];
                    qtd[j]=Encom[iden_enc].quantidade[i];
                    strcpy(descricoes[j],Prod[Encom[iden_enc].produtos[i]].descricao);
                    j++;
                }
            for (i=0; i<numero_prod; i++){ /* Ciclo que usa os tres vetores criados e uma pequena modificacao do insertion sort para ordenar os produtos */
                int aux_prod,aux_qtd,min = i; 
                char aux_desc[MAX_DESCRICAO];
                for (j=i+1; j<numero_prod; j++) 
                    if (strcmp(descricoes[j], descricoes[min])<0) 
                        min = j;  
                strcpy(aux_desc, descricoes[i]);
                strcpy(descricoes[i], descricoes[min]); 
                strcpy(descricoes[min], aux_desc);
                aux_prod = produtos[i];
                produtos[i] = produtos[min];
                produtos[min] = aux_prod;
                aux_qtd = qtd[i];
                qtd[i] = qtd[min];
                qtd[min] = aux_qtd;
            }
            for (i=0;i<numero_prod;i++) /* Impressao dos produtos pela ordem em que foram ordenados */
                printf("* %s %d %d\n",Prod[produtos[i]].descricao,Prod[produtos[i]].preco,qtd[i]);
        }
    }
}
