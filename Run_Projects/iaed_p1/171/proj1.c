#include <stdio.h>
#include <string.h>
#define MAX_ENCOMENDAS 499
#define MAX_PRODUTOS 9999
#define PESO_MAX 200
static int ide=-1;
static int idp=-1;
/* Criacao do tipo sistema para armazenar as informa?oes dos produtos
    numa estrutura com vetores que serao acedidos atraves da variavel universal 'idp' */
typedef struct {
    char descricao[MAX_PRODUTOS][62];
    int preco[MAX_PRODUTOS];
    int peso[MAX_PRODUTOS];
    int qtd[MAX_PRODUTOS];
    /* o vetor 'idps_ordenados' vai guardar os identificadores ordenados por ordem alfabetica das
    descricoes correspondentes */
    int idps_ordenados[MAX_PRODUTOS];
} sistema;
sistema sstm;

/* Algumas funcoes auxiliares para aceder ao sistema */

int preco_produto(int ident_p){
    return sstm.preco[ident_p];
}
int qtd_produto(int ident_p){
    return sstm.qtd[ident_p];
}
int peso_produto(int ident_p){
    return sstm.peso[ident_p];
}
int indice_idp_ordenado(int ident_p){
    int i;
    for (i=0;i<=idp;i++){
        if (sstm.idps_ordenados[i]==ident_p){
            return i;
        }
    }
    return i;
}

/*A funcao less_alfa recebe dois identificadores de produtos
e retorna 1 se a descricao do primeiro for menor alfabeticamente que a descricao do segundo*/

int less_alfa(int ident1, int ident2){
    int i,tamanho;
    char c1,c2;
    if (strlen(sstm.descricao[ident1])<strlen(sstm.descricao[ident2])){
        tamanho=strlen(sstm.descricao[ident1]);
    }
    else{
        tamanho=strlen(sstm.descricao[ident2]);
    }
    for(i=0;i<=tamanho;i++){
        c1=sstm.descricao[ident1][i]; c2=sstm.descricao[ident2][i];
        if (c1<c2){
            return 1;
        }
        if (c2<c1){
            return 0;
        }
    }
    return strlen(sstm.descricao[ident1])<=strlen(sstm.descricao[ident2]);
}

/* Criacao do tipo encomenda que permite armazenar os identificadores dos produtos na encomenda
e as suas quantidades (com o mesmo indice correspondente) e o inteiro n_produtos_e que corresponde ao maior indice */ 

typedef struct {
    int idpe[MAX_PRODUTOS];
    int qtd[MAX_PRODUTOS];
    int n_produtos_e;
} encomenda;
encomenda encomendas[MAX_ENCOMENDAS];

/* Algumas funcoes auxiliares para encomendas e para relacionar identificadores de encomendas com identificadores de produtos */

int n_produtos(int ident_e){
    return encomendas[ident_e].n_produtos_e;
}
int obter_indice_p(int ident_e,int ident_p){
    int i;
    for(i=0;i<=n_produtos(ident_e);i+=1){
        if (encomendas[ident_e].idpe[i]==ident_p){
            return i;
        }
    }
    return i; 
}

int peso_encomenda(int ident_e){
    int i,peso=0;
    for (i=0;i<=n_produtos(ident_e);i+=1){
        peso+=peso_produto(encomendas[ident_e].idpe[i])*encomendas[ident_e].qtd[i];
    }
    return peso;
}

/*A funcao 'produto_in' retorna 1 apenas se o produto estiver presente na encomenda */

int produto_in(int ident_e, int ident_p){
    int i;
    for (i=0;i<=n_produtos(ident_e);i+=1){
        if (encomendas[ident_e].idpe[i]==ident_p){
            return 1;
        }
    }
    return 0;
}

int qtd_produto_e(int ident_e, int ident_p){
    return encomendas[ident_e].qtd[obter_indice_p(ident_e,ident_p)];
}

void a(char desc[62], int preco, int peso, int qtd){
    int i=0,j;
    idp++;
    strcpy(sstm.descricao[idp],desc);
    sstm.preco[idp]=preco;
    sstm.peso[idp]=peso;
    sstm.qtd[idp]=qtd;

    /* organizar o vetor idps_ordenados por preco crescente */

    for(i=0;i<idp && preco_produto(idp)>=preco_produto(sstm.idps_ordenados[i]);i++){
        ;
    }
    for(j=idp;j>i;j-=1){
        sstm.idps_ordenados[j]=sstm.idps_ordenados[j-1];
    }
    sstm.idps_ordenados[i]=idp;
    printf("Novo produto %d.\n", idp);
}
void l(){
    int j;
    printf("Produtos\n");
    for (j=0;j<=idp;j+=1){

        /* Como o vetor 'idps_ordenados' e organizado logo desde o inicio nao e necessario utilizar algoritmos de ordenacao nesta funcao */

        printf("* %s %d %d\n",sstm.descricao[sstm.idps_ordenados[j]],preco_produto(sstm.idps_ordenados[j]),qtd_produto(sstm.idps_ordenados[j]));
    }
}
void q(int ident_p, int qtd){
    if (ident_p<=idp){
        sstm.qtd[ident_p]+=qtd;
    }
    else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",ident_p);
    }
}
void N(){
    ide++;
    /* so quando for adicionado o primeiro produto e que o 'n_produtos_e' ficara a 0 */
    encomendas[ide].n_produtos_e=-1;
    /* coloca-se o primeiro identificador a '-1' para podermos identificar quando e que a encomenda esta vazia */
    encomendas[ide].idpe[0]=-1;
    printf("Nova encomenda %d.\n", ide);
}

void r(int ident_p, int qtd){
    if (ident_p>idp){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",ident_p);
    }
    else if (qtd>qtd_produto(ident_p)){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd, ident_p);
    }
    else{
        sstm.qtd[ident_p]-=qtd;
    }
    
}
void A(int ident_e, int ident_p, int qtd){
    int i,j;
    if (ident_e>ide){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", ident_p,ident_e);
    }
    else if(ident_p>idp){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", ident_p, ident_e);
    }
    else if (qtd>qtd_produto(ident_p)){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",ident_p,ident_e);
    }
    else if ((qtd*peso_produto(ident_p))+peso_encomenda(ident_e)>PESO_MAX){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",ident_p,ident_e);
    }
    else {
        /* No caso do produto estar presente na encomenda so precisamos de aumentar a quantidade */
        if (produto_in(ident_e,ident_p)){
            encomendas[ident_e].qtd[obter_indice_p(ident_e,ident_p)]+=qtd;
        }
        else{
            
            /* Organizar os identificadores e as respetivas quantidades por ordem alfabetica das suas descricoes */
            
            if (encomendas[ident_e].idpe[0]!=-1){
                for(i=0;i<=n_produtos(ident_e);i++){
                    if (less_alfa(ident_p,encomendas[ident_e].idpe[i])){
                        break;
                    }
                }
                for(j=n_produtos(ident_e)+1;j>i;j--){
                    encomendas[ident_e].idpe[j]=encomendas[ident_e].idpe[j-1];
                    encomendas[ident_e].qtd[j]=encomendas[ident_e].qtd[j-1];
                }
                encomendas[ident_e].idpe[i]=ident_p;
                encomendas[ident_e].qtd[i]=qtd;
            }
            else{
                /* caso seja o primeiro produto a ser adicionado nao e necessario organizar */
                encomendas[ident_e].idpe[0]=ident_p;
                encomendas[ident_e].qtd[0]=qtd;
            }
            encomendas[ident_e].n_produtos_e+=1;
            
        }
        r(ident_p,qtd);
    }
}
void E(int ident_e,int ident_p){
    if (ident_e>ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ident_e);
    }
    else if(ident_p>idp){
        printf("Impossivel listar produto %d. Produto inexistente.\n", ident_p);
    }
    else{
        if (produto_in(ident_e,ident_p)){
            printf("%s %d.\n",sstm.descricao[ident_p],qtd_produto_e(ident_e,ident_p));
        }
        else{
            printf("%s 0.\n",sstm.descricao[ident_p]);
        }
    }
}

void L(int ident_e){ 
    if (ident_e>ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ident_e);
    }
    else{
        int i;
        printf("Encomenda %d\n",ident_e);
        for (i=0;i<=n_produtos(ident_e);i++){
            /* Novamente nao e necessario usar algoritmos de ordenacao porque o vetor 'idpe' ja esta ordenado*/
            printf("* %s %d %d\n", sstm.descricao[encomendas[ident_e].idpe[i]], 
            sstm.preco[encomendas[ident_e].idpe[i]],qtd_produto_e(ident_e,encomendas[ident_e].idpe[i]));
        }
    }
}

void R(int ident_e,int ident_p){
    int i;
    if (ident_e>ide){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",ident_p,ident_e);
    }
    else if(ident_p>idp){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",ident_p,ident_e);
    }
    else{
        /* A funcao R so faz algo se o produto estiver presente na encomenda */
        if (produto_in(ident_e,ident_p)){
            q(ident_p,qtd_produto_e(ident_e,ident_p));
            /* ao remover o produto temos de manter a ordem dos restantes */
            for(i=obter_indice_p(ident_e,ident_p);i<n_produtos(ident_e);i++){
                encomendas[ident_e].idpe[i]=encomendas[ident_e].idpe[i+1];
                encomendas[ident_e].qtd[i]=encomendas[ident_e].qtd[i+1];
            }
            encomendas[ident_e].n_produtos_e-=1;
        }
    }
}
void C(int ident_e){
    if (ident_e>ide){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ident_e);
    }
    else{
        int i, total=0;
        for(i=0;i<=n_produtos(ident_e);i++){
            total+=preco_produto(encomendas[ident_e].idpe[i])*encomendas[ident_e].qtd[i];
        }
        printf("Custo da encomenda %d %d.\n", ident_e, total);
    }
}
void p(int ident_p, int preco){
    int i,j;
    if (ident_p>idp){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", ident_p);
    }
    else{
        if (preco>preco_produto(ident_p)){
            for(i=idp;i>indice_idp_ordenado(ident_p);i--){
                if (preco_produto(sstm.idps_ordenados[i])<preco ||
                 (preco_produto(sstm.idps_ordenados[i])==preco && ident_p>sstm.idps_ordenados[i])){
                    break;
                }
            }
            for(j=indice_idp_ordenado(ident_p);j<i;j++){
                sstm.idps_ordenados[j]=sstm.idps_ordenados[j+1];
            }
        }
        else{
            for(i=0;i<indice_idp_ordenado(ident_p);i++){
                if(preco_produto(sstm.idps_ordenados[i])>preco ||
                (preco_produto(sstm.idps_ordenados[i])==preco && ident_p<sstm.idps_ordenados[i])){
                    break;
                }
            }
            for(j=indice_idp_ordenado(ident_p);j>i;j--){
                sstm.idps_ordenados[j]=sstm.idps_ordenados[j-1];
            }            
        }
        sstm.idps_ordenados[i]=ident_p;
        sstm.preco[ident_p]=preco;
    }
}
void m(int ident_p){
    if (ident_p>idp){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", ident_p);
    }
    else{
    /* variaves 'qtd_max' e 'idpe_max' vao guardar a encomenda em que o produto existe em  maior quantidade
    e a sua respetiva quantidade na encomenda */
    int i,qtd_max=0,idpe_max;
        for (i=0;i<=ide;i++){
            if (produto_in(i,ident_p) && encomendas[i].qtd[obter_indice_p(i,ident_p)]>qtd_max){
                qtd_max=encomendas[i].qtd[obter_indice_p(i,ident_p)];
                idpe_max=i;
            }
        }
        if (qtd_max!=0){
            printf("Maximo produto %d %d %d.\n", ident_p, idpe_max, qtd_max);
        }
    }
}
int main(){
    char c='0', descricao[62];
    int preco, peso, qtd,identificador;
    int ident_e,ident_p;
    while (c!='x'){
        switch (c=getchar()){
            case 'a':
                scanf(" %[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);
                a(descricao, preco, peso, qtd);
                break;
            case 'l':
                l();
                break;
            case 'q':
                scanf(" %d:%d", &identificador,&qtd);
                q(identificador,qtd);
                break;
            case 'N':
                N();
                break;
            case 'A':
                scanf(" %d:%d:%d", &ident_e,&ident_p,&qtd);
                A(ident_e,ident_p,qtd);
                break;
            case 'E':
                scanf(" %d:%d", &ident_e,&ident_p);
                E(ident_e,ident_p);
                break;
            case 'L':
                scanf(" %d", &ident_e);
                L(ident_e);
                break;
            case 'r':
                scanf(" %d:%d", &ident_p, &qtd);
                r(ident_p,qtd);
                break;
            case 'R':
                scanf(" %d:%d", &ident_e, &ident_p);
                R(ident_e,ident_p);
                break;
            case 'C':
                scanf(" %d",&ident_e);
                C(ident_e);
                break;
            case 'p':
                scanf(" %d:%d", &ident_p,&preco);
                p(ident_p,preco);
                break;
            case 'm':
                scanf(" %d", &ident_p);
                m(ident_p);
                break;
        }
    }
    return 0;
}

