#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Maximo produto diferente que pode existir*/
#define MAX_PRO_DIF 10000

/*Numero de caracteres do nome do produto*/
#define DESCRICAO 63

/* Numero de encomedas*/
#define ENCOMENDAS 500

/* Peso maximo e tambem o numeros de produtos diferentes
que pode existir numa encomenda*/
#define MAX_PESO 200

/* estrurura dos produtos*/
typedef struct produto
    /*qtp=quantidade*/
    {   
        char descricao[DESCRICAO];
        int preco;
        int peso;
        int qtp;
    }produto;

/* estrutura das encomendas*/
typedef struct encomenda
    /*pro=vetor com os produtos numa encomenda,
     *qtp= vetor das quantidade de cada produto,
     *n_elem= numero de produtos diferentes existentes numa encomenda*/
    {   
        int pro[MAX_PESO];
        int peso;
        int n_elem;
        int qtp[MAX_PESO];
    }encomenda;

/*funcao que cria um novo produto
 *recebe o vazio e devolve um novo produto*/
produto __a__()
    /* pres=preco dado pelo utilizador
     * quant=quantidade dado pelo utilizador*/
{   produto a;
    int pres,peso,quan,i=0;
    char c;
    c=getchar();
    c=getchar();
    while (c!=':'){
        a.descricao[i]=c;
        i++;
        c=getchar();
    }
    a.descricao[i]='\0';
    scanf("%d:%d:%d",&pres,&peso,&quan);
    a.preco=pres;
    a.peso=peso;
    a.qtp=quan;
    return a;
}

/* funcao cria um nova encomenda
 * recebe vazio e devolve uma nova encomenda*/
encomenda cria_encomenda()
{
    encomenda a;
    a.peso=MAX_PESO;
    a.n_elem=0;
    return a;
}

/* funcao que verifica a existencia de um produto numa encomenda
 * recebe os produtos numa encomenda(pro), 
    a identificacao do produto(idp) e o numero de elementos da encomenda(elem)
 * Devolve a posicao do produto na encomenda, caso exista,
   caso contrario devolve -1*/
int verifica(int pro[MAX_PESO],int idp,int elem)
{
    int i;
    for (i=0;i<elem;i++){
        if (pro[i]==idp)
            return i;
    }
    return -1;  
}

/* mete um produto numa encomenda
 * recebe o vetor das encomenda, o vetor dos produtos, a identificacao do produto(idp) e da encomenda(ide)*/
void por_produto_enc(encomenda iden_encomenda[ENCOMENDAS],produto p[MAX_PRO_DIF],int idp,int qtp,int ide)
{
    /* n e o numero de elementos da encomenda
     * m e a posicao do produto na encomenda se existir*/
    int n,m;
    n=iden_encomenda[ide].n_elem;
    m=verifica(iden_encomenda[ide].pro,idp,n);
    if (m!=-1){
        iden_encomenda[ide].qtp[m]+=qtp;
    }
    else{
        iden_encomenda[ide].qtp[n]=qtp;
        iden_encomenda[ide].pro[n]=idp;
        iden_encomenda[ide].n_elem++;
    }
    iden_encomenda[ide].peso-=p[idp].peso*qtp;
    p[idp].qtp-=qtp;
}


/* remove produto numa encomenda
 * recebe o vetor das encomendas, a identificacao do produto(idp) e da encomenda(ide) e o vetor dos produto*/
void remove_produto(encomenda iden_encomenda[ENCOMENDAS],int idp,int ide,produto p[MAX_PRO_DIF])
{
    /* n e o numero de elementos da encomenda
     * m e a posicao do produto na encomenda se existir*/
    int n,i,m;
    i=0;
    n=iden_encomenda[ide].n_elem;
    m=verifica(iden_encomenda[ide].pro,idp,n);
    if (m!=-1){
        p[idp].qtp+=iden_encomenda[ide].qtp[m];
        iden_encomenda[ide].peso+=(iden_encomenda[ide].qtp[m]*p[idp].peso);
        for (i=(m+1);m<n;m++){
            iden_encomenda[ide].pro[m]=iden_encomenda[ide].pro[i];
            iden_encomenda[ide].qtp[m]=iden_encomenda[ide].qtp[i];
            i++;

        }
    iden_encomenda[ide].n_elem--;
    }
}

/* calculo o custa da encomenda
 * recebe a o vetor encomenda, o vetor dos produtos e a identificacao da encomenda(ide)
 * devolve o total do preco a pagar*/
int custo(encomenda enc[ENCOMENDAS],produto p[MAX_PRO_DIF],int ide)
{
    /* n e o numero de elementos da encomenda*/
    int i,total,n;
    n=enc[ide].n_elem;
    total=0;
    for (i=0;i<n;i++){
        total+=(p[enc[ide].pro[i]].preco)*enc[ide].qtp[i];
    }
    return total;
}

/* Indica qual encomenda tem mais produtos
 * Recebe o vetor das encomeda, a identificacao do produto(idp) e o numero de encomendas(n_enc)*/
void maximo_produto(encomenda iden_encomenda[ENCOMENDAS],int idp,int n_enc)
{
    /* m e a posicao do produto na encomenda se existir
     * ide e a identificacao da encomenda com mais produto
     * qtp e a quantidade de produtos existentes numa encomenda*/
    int i,m,ide,qtp;
    qtp=0;
    ide=-1;
    for (i=0;i<n_enc;i++){
        m=verifica(iden_encomenda[i].pro,idp,iden_encomenda[i].n_elem);
        if (m!=-1){
            if (qtp<iden_encomenda[i].qtp[m]){
                ide=i;
                qtp=iden_encomenda[i].qtp[m];
            }
        }
    }
    if (ide!=-1)
        printf("Maximo produto %d %d %d.\n",idp,ide,qtp);
}

/* Faz a particao da lista com as identificacoes da produtos(idp_ord)
 * Recebe idp_ord, o inicio e o fim do vetro idp_ord e o vetor dos produtos
 * Devolve a posicao do meio da lista idp_ord*/
int particao(int idp_ord[MAX_PRO_DIF],int inicio,int fim, produto p[MAX_PRO_DIF])
{
    /* v e o pivo*/
    int i=inicio-1;
    int aux,j=fim;
    int v=idp_ord[fim];
    while(i<j){
        while (p[idp_ord[++i]].preco<p[v].preco || (p[idp_ord[i]].preco==p[v].preco && idp_ord[i]<v));
        while (p[v].preco<p[idp_ord[--j]].preco || (p[idp_ord[j]].preco==p[v].preco && idp_ord[j]>v))
            if (j==inicio)
                break;
        if (i<j){
            aux=idp_ord[i];
            idp_ord[i]=idp_ord[j];
            idp_ord[j]=aux;
        }
    }
    aux=idp_ord[i];
    idp_ord[i]=idp_ord[fim];
    idp_ord[fim]=aux;
    return i;
}

/* ordena a lista de identificoes de produtos (idp_ord)
 * Recebe o vetor dos produtos, o inicio e fim da lista idp_ord*/
void ordena_lista(produto p[MAX_PRO_DIF],int inicio, int fim,int idp_ord[MAX_PRO_DIF])
{
    int i;
    if (fim<=inicio)
        return;
    i=particao(idp_ord,inicio,fim,p);
    ordena_lista(p,inicio,i-1,idp_ord);
    ordena_lista(p,i+1,fim,idp_ord);
}

/* ordena os produtos numa encomenda(enc)
 * recebe uma encomenda e a lista de produtos*/
void ordena_enc(encomenda enc,produto p[MAX_PRO_DIF])
{
    /*n e o numero de produtos numa encomenda
     *pro contem a identificacao dos produtos
     *qtp contem a quantidade de cada produto*/
    int i,n,j,aux;
    int pro[MAX_PESO],qtp[MAX_PESO];
    char desc[DESCRICAO];
    n=enc.n_elem;
    for (i=0;i<n;i++){
        pro[i]=enc.pro[i];
        qtp[i]=enc.qtp[i];
    }
    for (i=0;i<n;i++){
        strcpy(desc, p[pro[i]].descricao);
        for (j=i+1;j<n;j++){
            if(strcmp(desc,p[pro[j]].descricao)>0){
                strcpy(desc,p[pro[j]].descricao);
                aux=pro[i];
                pro[i]=pro[j];
                pro[j]=aux;
                aux=qtp[i];
                qtp[i]=qtp[j];
                qtp[j]=aux;
            }
        }
        printf("* %s %d %d\n",desc,p[pro[i]].preco,qtp[i]);
    }
}

/* Le o comando que o utilizador quer executar*/
int main ()
{
    /* l e o caracter do comando que utlizador vai utilizar
     * iden e o numero de produtos existentes 
     * iden_enc e o numero de encomendas existentes
     * ord_lis indica se a lista idp_ord ja esta ordenada (ord_lis==1) ou nao (ord_lis==0)
     * idp,qtp,ide sao valores dados pelo utilizador
     * idp_ord e um lista com todas as identificoes dos produtos
     * iden_pro e um vetor com as informacoes dos produtos
     * iden_encomenda e um vetor com as informacoes das encomendas*/
    char l;
    int iden,iden_enc,ord_lis;
    int idp,qtp,ide,arg1;
    int idp_ord[MAX_PRO_DIF];
    produto iden_pro[MAX_PRO_DIF];
    encomenda iden_encomenda[ENCOMENDAS];
    l=getchar();
    iden=0;
    iden_enc=0;
    ord_lis=0;
    while (l!='x')
    {
        switch (l)
        {
            case 'a':
                iden_pro[iden]=__a__();
                printf("Novo produto %d.\n",iden);
                idp_ord[iden]=iden;
                iden++;
                ord_lis=0;
                break;
            
            case 'q':
                scanf("%d:%d",&idp,&qtp);
                if (idp>=iden){
                    printf("Impossivel adicionar produto %d ",idp);
                    printf("ao stock. Produto inexistente.\n");
                    }
                else
                    iden_pro[idp].qtp+=qtp;
                break;
            case 'N':
                iden_encomenda[iden_enc]=cria_encomenda();
                printf("Nova encomenda %d.\n",iden_enc);
                iden_enc++;
                break;
            
            case 'A':
                scanf("%d:%d:%d",&ide,&idp,&qtp);
                if (iden_enc<=ide)
                    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);

                else if (iden<=idp)
                    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);

                else if (qtp>iden_pro[idp].qtp)
                    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);

                else if ((qtp*iden_pro[idp].peso)>iden_encomenda[ide].peso)
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
                else
                    por_produto_enc(iden_encomenda,iden_pro,idp,qtp,ide);
                break;
            
            case 'r':
                scanf("%d:%d",&idp,&qtp);
                if (idp>=iden)
                    printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
                else if (qtp>iden_pro[idp].qtp)
                    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtp,idp);
                else
                    iden_pro[idp].qtp-=qtp;
                break;
            
            case 'R':
                scanf("%d:%d",&ide,&idp);
                if (ide>=iden_enc)
                    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
                else if (idp>=iden)
                    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
                else
                    remove_produto(iden_encomenda,idp,ide,iden_pro);
                break;
            
            case 'C':
                scanf("%d",&ide);
                if (ide>=iden_enc)
                    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
                else{
                    printf("Custo da encomenda %d %d.\n",ide,custo(iden_encomenda,iden_pro,ide));
                }
                break;
            
            case 'p':
                scanf("%d:%d",&idp,&arg1);
                if (idp>=iden)
                    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
                else{
                    iden_pro[idp].preco=arg1;
                    ord_lis=0;
                }
                break;
            
            case 'E':
                scanf("%d:%d",&ide,&idp);
                if (ide>=iden_enc)
                    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
                else if (idp>=iden)
                    printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
                else{
                    arg1=verifica(iden_encomenda[ide].pro,idp,iden_encomenda[ide].n_elem);
                    if (arg1==(-1)){
                        printf("%s 0.\n",iden_pro[idp].descricao);
                        }
                    else{
                        printf("%s %d.\n",iden_pro[idp].descricao,iden_encomenda[ide].qtp[arg1]);
                        }
                }
                break;
            
            case 'm':
                scanf("%d",&idp);
                if (idp>=iden)
                    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
                else{ 
                    maximo_produto(iden_encomenda,idp,iden_enc);
                }
                break;

            case 'l':
                printf("Produtos\n");
                arg1=iden-1;
                if (ord_lis==0)
                    ordena_lista(iden_pro,0,arg1,idp_ord);
                for (arg1=0;arg1<iden;arg1++){
                    printf("* %s %d %d\n",iden_pro[idp_ord[arg1]].descricao,iden_pro[idp_ord[arg1]].preco,iden_pro[idp_ord[arg1]].qtp);
                }
                ord_lis=1;
                break;
            
            case 'L':
                scanf("%d",&ide);
                if (ide>=iden_enc)
                    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
                else{
                    printf("Encomenda %d\n",ide);
                    ordena_enc(iden_encomenda[ide],iden_pro);
                }
                break;
        }
        l=getchar();
    }
    return 0;
}