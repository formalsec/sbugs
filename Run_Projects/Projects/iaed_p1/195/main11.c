#include <stdio.h>
#include <string.h>
#define CHARMAX 63 
#define PESOMAX 200 
#define PRODMAX 10000 
#define ENCOMAX 500
#define INEXISTENTE -1

/* um produto tem uma descricao com um maximo de 63 caracteres um preco, peso e quantidade  */
typedef struct {
    char descricao[CHARMAX];
    int preco,peso,qtd;
} produto;

/* uma encomenda e um conjunto de produtos cujo peso e a soma do peso de cada 
    um dos seus produtos multiplicados pela sua respetiva quantidade e uma localizacao 
    onde sera adicionado o proximo produto */
typedef struct{
    produto prods[PESOMAX];
    produto sprods[PESOMAX];
    int peso,loc;
} encomenda;
 
/* troca dois valores */
void exch(produto array[],int ind1,int ind2)
{
    produto save=array[ind1];
    array[ind1]=array[ind2];
    array[ind2]=save;
}

/* vetor auxiliar mergesort */
produto aux[PRODMAX]={0};

/* junta duas listas ordenadas pelo preco numa so lista ordenada do mesmo modo */
void merge(produto a[], int left, int m, int right)
{ 
  int i, j, k;
  for (i = m+1; i > left; i--) 
    aux[i-1] = a[i-1];
  for (j = m; j < right; j++)
    aux[right+m-j] = a[j+1];
  for (k = left; k <= right; k++)
    if ((aux[j].preco < aux[i].preco) || i > m)
      a[k] = aux[j--];
    else
      a[k] = aux[i++];
}

/* igual a merge mas de acordo com a descricao em vez do preco */
void merges(produto a[], int left, int m, int right)
{ 
  int i, j, k;
  for (i = m+1; i > left; i--) 
    aux[i-1] = a[i-1];
  for (j = m; j < right; j++)
    aux[right+m-j] = a[j+1];
  for (k = left; k <= right; k++)
    if ((strcmp(aux[j].descricao,aux[i].descricao)<0) || i > m)
      a[k] = aux[j--];
    else
      a[k] = aux[i++];
}

/* mergesort de produtos de acordo com o preco*/
void mergesort(produto a[], int left, int right) 
{
    int m = (right+left)/2;
    if (right <= left)
        return;
    mergesort(a, left, m);
    mergesort(a, m+1, right);
    merge(a, left, m, right);
}

/* mergesort de produtos de acordo com a descricao */
void mergesorts(produto a[], int left, int right) 
{
    int m = (right+left)/2;
    if (right <= left)
        return;
    mergesort(a, left, m);
    mergesort(a, m+1, right);
    merges(a, left, m, right);
}

/* verifica se um produto esta presente numa lista de produtos ao comparar descricoes.
caso esteja devolve o seu indice caso  contrario devolve -1 */
int search(produto con[],char descricao[])
{
    int i;
    for (i=0;i<PESOMAX;i++)
        {
            if (strcmp(con[i].descricao,descricao)==0)
                return i;
        }
    return INEXISTENTE;
}

/* adiciona um novo produto ao sistema */
void a(produto lis[],int idp)
{
    char descricao[CHARMAX]={0};
    int preco, peso, qtd;
    scanf(" %[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);
    strcpy(lis[idp].descricao,descricao);
    lis[idp].peso=peso;
    lis[idp].preco=preco;
    lis[idp].qtd=qtd;
    printf("Novo produto %d.\n", idp);
}

/* adiciona stock a um produto existente no sistema  */
void q(produto lis[], int maxidp)
{
    int idp,qtd;
    scanf("%d:%d",&idp,&qtd);
    if (idp >= maxidp)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else
        lis[idp].qtd=lis[idp].qtd+qtd;
}

/* cria uma nova encomenda */
void N(encomenda tab[],int ide)
{
    tab[ide].loc=0;
    printf("Nova encomenda %d.\n", ide);
}

/*  adiciona um produto a uma encomenda. 
Se o produto ja existir na encomenda, adiciona a nova quantidade a quantidade existente */
void A(int maxide,int maxidp, produto lis[],encomenda tab[])
{
    int ide,idp,qtd,ind;
    scanf("%d:%d:%d",&ide,&idp,&qtd);
    if (maxide<=ide)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else if (maxidp<=idp)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    else if(lis[idp].qtd<qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
    else if ((tab[ide].peso+(qtd*(lis[idp].peso)))>200)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp,ide);
    else
        {
            ind=search(tab[ide].prods,lis[idp].descricao);
            if (ind<0)
            {
                tab[ide].prods[tab[ide].loc]=lis[idp];
                tab[ide].prods[tab[ide].loc].qtd=qtd;
                tab[ide].loc=tab[ide].loc+1;
                tab[ide].peso=tab[ide].peso+(qtd*(lis[idp].peso));
                lis[idp].qtd=lis[idp].qtd - qtd;
            }
            else
            {
                tab[ide].prods[ind].qtd=tab[ide].prods[ind].qtd+qtd;
                tab[ide].peso=tab[ide].peso+qtd*tab[ide].prods[ind].peso;
                lis[idp].qtd=lis[idp].qtd - qtd;
            }
        }
}

/* remove stock a um produto existente */
void r(int maxidp,produto lis[])
{
    int idp,qtd;
    scanf("%d:%d",&idp,&qtd);
    if (maxidp<=idp)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
    else if (lis[idp].qtd<qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
    else
        lis[idp].qtd=lis[idp].qtd - qtd;
}

/* remove um produto de uma encomenda */
void R(int maxide,int maxidp, produto lis[], encomenda tab[])
{
    int ide,idp,ind;
    scanf("%d:%d",&ide,&idp);
    if (maxide<=ide)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else if (maxidp<=idp)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    else
    {
        ind=search(tab[ide].prods,lis[idp].descricao);
        if (ind>=0)
        {
            lis[idp].qtd=lis[idp].qtd+tab[ide].prods[ind].qtd;
            tab[ide].peso=tab[ide].peso-(tab[ide].prods[ind].peso*tab[ide].prods[ind].qtd);
            tab[ide].prods[ind].qtd=0;
        }
    }
    
}

/* calcula o custo de uma encomenda */
void C(int maxide, encomenda tab[])
{
    int ide,i;
    int total=0;
    scanf("%d", &ide);
    if (maxide<=ide)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
    else
    {
        for (i=0;i<tab[ide].loc;i++)
            total+=tab[ide].prods[i].qtd*tab[ide].prods[i].preco;
        printf("Custo da encomenda %d %d.\n",ide,total);
    }
}

/* altera o preco de um produto existente no sistema */
void p(int maxide,int maxidp,produto lis[],encomenda tab[])
{
    int idp,preco,ind,i;
    scanf("%d:%d",&idp,&preco);
    if (idp>=maxidp)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
    else
    {
        lis[idp].preco=preco;
        for (i=0;i<maxide;i++)
        {
            ind=search(tab[i].prods,lis[idp].descricao);
            if (ind>=0)
                tab[i].prods[ind].preco=preco;
        }
    }
}

/* lista a descri??o e a quantidade de um produto numa encomenda */
void E(int maxide,int maxidp, produto lis[], encomenda tab[])
{
    int ide,idp,ind;
    scanf("%d:%d",&ide,&idp);
    if (maxide<=ide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    else if (maxidp<=idp)
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
    else
    {
        ind=search(tab[ide].prods,lis[idp].descricao);
        if (ind>=0)
            printf("%s %d.\n",lis[idp].descricao,tab[ide].prods[ind].qtd);
        else
            printf("%s %d.\n",lis[idp].descricao,0);
    }
    
}

/* lista o identificador da encomenda em que o produto dado ocorre mais vezes. 
Se houver 2 ou mais encomendas nessa situa??o, dever? imprimir a encomenda de menor id.*/
void m(int maxide,int maxidp, produto lis[], encomenda tab[])
{
    int idp,i,ide,ind;
    int qtd=0;
    scanf("%d",&idp);
    if (idp>=maxidp)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
    else
    {
        for (i=0;i<maxide;i++)
        {
            ind=search(tab[i].prods,lis[idp].descricao);
            if (ind>=0)
            {
                if (tab[i].prods[ind].qtd>qtd)
                {
                    qtd=tab[i].prods[ind].qtd;
                    ide=i;
                }
            }
        }
        if (qtd!=0)
            printf("Maximo produto %d %d %d.\n",idp,ide,qtd);
    }
}

/* lista os produtos do sistema por ordem crescente de preco */
void l(produto sortlis[],produto lis[],int maxidp)
{
    int i;
    for (i=0;i<maxidp;i++)
        sortlis[i]=lis[i];
    mergesort(sortlis,0,maxidp-1);
    printf("Produtos\n");
    for (i=0;i<maxidp;i++)
        printf("* %s %d %d\n",sortlis[i].descricao,sortlis[i].preco,sortlis[i].qtd);
}

/* lista os produtos de uma encomenda por ordem alfabetica */
void L(produto sortlis[],encomenda tab[],int maxide)
{
    int ide,i;
    scanf("%d",&ide);
    if (ide>=maxide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    else
    {
        for (i=0;i<tab[ide].loc;i++)
            sortlis[i]=tab[ide].prods[i];
        mergesorts(sortlis,0,tab[ide].loc-1);
        printf("Encomenda %d\n",ide);
        for (i=0;i<tab[ide].loc;i++)
        {
            if (sortlis[i].qtd!=0)
                printf("* %s %d %d\n",sortlis[i].descricao,sortlis[i].preco,sortlis[i].qtd);
        }
    }
}
/* lista de todos os produtos do sistema  */
produto lp[PRODMAX]={0};
/* lista de todos os produtos ordenada pelo preco ou pela descricao  */
produto sortlp[PRODMAX]={0};
/* lista de todas as encomendas do sistema  */
encomenda le[ENCOMAX]={0};

int main()
{
    int ch,midp,mide;
    midp=mide=0;
    while ((ch=getchar())!=EOF && ch!='x')
        {
            if (ch=='a')
            {
                a(lp, midp);
                midp++;
            }
            else if (ch=='q')
                q(lp,midp);
            else if (ch=='N')
            {
                N(le,mide);
                mide++;
            }
            else if (ch=='A')
            {
                A(mide,midp,lp,le);
            }
            else if (ch=='r')
                r(midp,lp);
            else if (ch=='R')
                R(mide,midp,lp,le);
            else if (ch=='C')
                C(mide,le);
            else if (ch=='p')
                p(mide,midp,lp,le);
            else if (ch=='E')
                E(mide,midp,lp,le);
            else if (ch=='m')
                m(mide,midp,lp,le);
            else if (ch=='l')
                l(sortlp,lp,midp);
            else if (ch=='L')
                L(sortlp,le,mide);
        }
    return 0;
}


















