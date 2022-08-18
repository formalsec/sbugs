#include <stdio.h>
#include <string.h>
#define STRP   63 /*numero maximo de caracteres da descricao*/
#define MAXP 10000 /*numero maximo de produtos*/
#define MAXPE 200 /*como o peso maximo por encomenda eh 200 e 
cada produto tem no minimo peso =1, entao so ha ate 200 produtos*/
#define MAXE 500 /*numero maximo de encomendas*/
#define key_p(A) (A.price) /*componente preco de um produto*/
#define key_d(A) (A.description) /*componente preco de um produto*/

/* estrutura produto: com identificador,
descricao, preco, peso e quantidade em stock */
typedef struct produto
{
    int id;
    char description[STRP];
    int price;
    int weight;
    int stock;
} produto;

/* estrutura encomenda: com identificador, peso,
contador de produtos por encomenda e um conjunto de produtos*/
typedef struct encomenda
{
    int order_id;
    int order_weight;
    int contador_pe; /*contador de produtos na encomenda*/
    produto products[MAXPE];
} encomenda;


typedef int item; /*item usado no mergesort*/
int less(produto A, produto B, char chave[12])
{
    if (strcmp(chave, "description\0") == 0)
        return (strcmp(key_d(A), key_d(B)) < 0);
    if (strcmp(chave, "price\0") == 0)
    {   
        if ((key_p(A) == key_p(B)) && (A.id < B.id))
            return 1;
        else
            return (key_p(A) < key_p(B));  
    } 
    return 0;
}

/*------------algoritmo de ordenacao - merge sort------------*/
void merge(item a[], int left, int m, int right, char chave[12],produto portfolio_p[MAXP])
{
    int i,j,k;
    item aux[MAXP];
    for(i = m+1; i > left; i--)
        aux[i-1] = a[i-1];
    for(j = m; j < right; j++)
        aux[right+m-j] = a[j+1];
    for (k = left; k <= right; k++) /*vai ordenar o vetor a[]*/
        if (less(portfolio_p[aux[j]], portfolio_p[aux[i]], chave))
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
}

void mergesort(item b[], int left, int right, char chave[12], produto portfolio_p[MAXP])
{
    int m = (right + left)/2;
    if(right <= left) 
        return;
    mergesort(b,left,m,chave, portfolio_p);
    mergesort(b,m+1,right,chave,portfolio_p);
    merge(b,left,m,right,chave, portfolio_p);
}
/*------------------------------------------------------------*/

/*inicializacao de variaveis*/
produto portfolio_p[MAXP] = {{0,"",0,0,0}}; /*produtos existentes*/
encomenda portfolio_e[MAXE] = {{0,0,0,{{0,"",0,0,0}}}}; /*encomendas existentes*/

/*cabecalho das funcoes auxiliares*/
void novo_p(int idp, produto a, produto portfolio_p[MAXP]);
int existe_p(int a, int idp); /*testar se o produto existe*/
void nova_e(int ide, encomenda e, encomenda portfolio_e[MAXE]);
int existe_e( int i, int ide); /*testar se a encomenda existe*/
int letra_A (int a, int i, int qtd, produto portfolio_p[MAXP], encomenda portfolio_e[MAXE], int idp, int ide);
int letra_r(int a, int qtd, produto portfolio_p[MAXP], int idp);
int letra_R(int a, int i, produto portfolio_p[MAXP], encomenda portfolio_e[MAXE], int idp, int ide);
int letra_C(int i, produto portfolio_p[MAXP], encomenda portfolio_e[MAXE], int total, int ide);
int letra_p(int a, int price, int ide, produto portfolio_p[MAXP], encomenda portfolio_e[MAXE], int idp);
int letra_E (int a, int i, produto portfolio_p[MAXP], encomenda portfolio_e[MAXE], int idp, int ide);
int letra_m(int a, produto maximo, int ide, encomenda portfolio_e[MAXE], int idp);
int letra_l(int idp, produto portfolio_p[MAXP]);
int letra_L(int i, produto portfolio_p[MAXP], encomenda portfolio_e[MAXE], int ide);

/*-----------------------------------------------*/

int main()
{

  int idp, ide, qtd, price, total; /*idp e ide correspondem a numero de produtos e encomendas, respetivamente*/
  char c;
  produto a = {0};
  encomenda e = {0};
  idp = 0, ide = 0, total = 0;
  
   while ((c = getchar()) != 'x') 
  {
      switch(c)
      {
        case 'a': /*adiciona novo produto ao sistema */
        {
            scanf("\n%[^:]:%d:%d:%d", a.description, &a.price, &a.weight, &a.stock);
            novo_p(idp, a, portfolio_p);
            idp++;
            break;
        }

        case 'q': /*adiciona stock a um produto existente no sistema*/
        {   
            scanf("%d:%d", &a.id, &a.stock);
            if (existe_p(a.id, idp) == 1)
                portfolio_p[a.id].stock += a.stock;   
            else
                printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", a.id);
            break;
        }

        case 'N': /*cria uma nova encomenda*/
        {   
            nova_e(ide, e, portfolio_e);
            ide++;
            break;
        }

        case 'A': /*adiciona um produto a uma encomenda*/
        {
            scanf("%d:%d:%d", &e.order_id, &a.id, &qtd);
            letra_A(a.id, e.order_id, qtd, portfolio_p, portfolio_e, idp, ide);
            break;
        }

        case 'r': /*remove stock a um produto existente*/
        {
            scanf("%d:%d", &a.id, &qtd);
            letra_r(a.id, qtd, portfolio_p, idp);
            break;
        }

        case 'R': /*remove um produto a uma encomenda*/
        {
            scanf("%d:%d", &e.order_id, &a.id);
            letra_R(a.id, e.order_id,portfolio_p, portfolio_e, idp, ide);
            break;
        }

        case 'C': /*calcula o custo de uma encomenda*/
        {   
            scanf("%d", &e.order_id);
            letra_C(e.order_id, portfolio_p, portfolio_e, total, ide);
            break;
        }

        case 'p': /*altera o preco de um produto existente no sistema*/
        {
            scanf("%d:%d", &a.id, &price);
            letra_p(a.id, price, ide, portfolio_p, portfolio_e, idp);           
            break;
        }

        case 'E': /*retorna a decricao e a quantidade
        de um produto numa encomenda*/
        {
            scanf("%d:%d", &e.order_id, &a.id);
            letra_E(a.id, e.order_id, portfolio_p, portfolio_e, idp, ide);
            break;
        }

        case 'm': /*retorna o identificador da encomenda em 
        que um dado produto ocorre mais vezes*/
        {
            produto maximo = {0};
            scanf("%d", &a.id);
            letra_m(a.id, maximo, ide, portfolio_e, idp);
            break;
        }

        case 'l': /*lista todos os produtos existentes no sistema
        por ordem crescente de preco*/
        {
            letra_l(idp, portfolio_p);
            break;
        }

        case 'L': /*lista todos os produtos de uma encomenda
        por ordem alfabetica da descricao*/
        {
            scanf("%d", &e.order_id);
            letra_L(e.order_id, portfolio_p, portfolio_e, ide);
            break;
        }

      getchar();
    } 
  }
  return 0;
}

/*adiciona novo produto ao sistema */
void novo_p(int idp, produto a, produto portfolio_p[MAXP]) 
{
    if (idp != MAXP)
    {
        a.id = idp;
        portfolio_p[idp] = a; /*O indice do portfolio corresponde ao id do produto*/
        printf("Novo produto %d.\n", a.id);
    }
}

/*testar se o produto existe ou nao */
int existe_p(int a, int idp) 
{

    if (a < idp)
    {
        return 1;
    }
    else
        return 0;
}
/*testar se a encomenda existe ou nao */
int existe_e( int i, int ide) 
{

    if (i < ide)
        return 1;
    else
        return 0;
}

 /*adiciona nova encomenda ao sistema */
void nova_e(int ide, encomenda e, encomenda portfolio_e[MAXE])
{
    if (ide != MAXE)
    {
        e.order_id = ide;  
        portfolio_e[ide] = e;
        printf("Nova encomenda %d.\n", e.order_id);
    }
}

/*adiciona um produto a uma encomenda*/
int letra_A (int a, int i, int qtd, produto portfolio_p[MAXP], encomenda portfolio_e[MAXE], int idp, int ide)
{
    int contador1, k;
    if (existe_p(a, idp) != 1) /*produto nao existe*/
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", a, i);
        return 0;
    }
    
    else if (existe_e(i, ide) != 1) /*se encomenda nao existir*/
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", a, i);
        return 0;
    }

    else if (portfolio_p[a].stock < qtd) /*se nao houver stock suficiente*/
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", a, i);
        return 0;
    }

    else if ((portfolio_e[i].order_weight + (qtd*portfolio_p[a].weight)) > 200) /*se exceder peso da encomenda*/
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", a, i);
        return 0;  
    }


    for(k = 0; k < portfolio_e[i].contador_pe; k++)
    {
        if (portfolio_e[i].products[k].id == a) /*produto ja existe na encomenda */
        {
            portfolio_e[i].products[k].stock += qtd;
            portfolio_p[a].stock -= qtd;
            portfolio_e[i].order_weight += (qtd*portfolio_p[a].weight);
            return 0;
        }
    }

    /*produto nao existe na encoemnda*/
    {
        contador1 = portfolio_e[i].contador_pe;
        portfolio_e[i].products[contador1].id = a;
        portfolio_e[i].products[contador1].stock += qtd;
        portfolio_e[i].contador_pe++;
        portfolio_p[a].stock -= qtd;
        portfolio_e[i].order_weight += (qtd*portfolio_p[a].weight);
        return 0; 
    }
}
/*remove stock a um produto existente*/
int letra_r(int a, int qtd, produto portfolio_p[MAXP], int idp)
{
    if (existe_p(a, idp) != 1)
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", a);
        return 0;
    }

    else if ((portfolio_p[a].stock - qtd) < 0) 
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, a);
        return 0;
    }

    else
    {    
        portfolio_p[a].stock -= qtd;
        return 0;
    } 
}
/*remove um produto a uma encomenda*/
int letra_R(int a, int i, produto portfolio_p[MAXP], encomenda portfolio_e[MAXE], int idp, int ide)
{
    int k, p;

    if (existe_e(i, ide) != 1) 
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", a, i);
        return 0;
    }
    else if (existe_p(a, idp) != 1)
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", a, i);
        return 0;
    }

    for(k = 0; k < portfolio_e[i].contador_pe; k++)
    {
        if (portfolio_e[i].products[k].id == a) /*testar se o produto existe na encomenda*/
        {
            portfolio_p[a].stock += portfolio_e[i].products[k].stock;
            /*remover peso do produto da encomenda*/
            portfolio_e[i].order_weight -= portfolio_p[a].weight*portfolio_e[i].products[k].stock;
            /*eliminar produto*/
            for (p = k ; p < portfolio_e[i].contador_pe; p++)
                portfolio_e[i].products[p] = portfolio_e[i].products[p+1];
            portfolio_e[i].contador_pe--;
        }
    }
    return 0;
}
/*calcula o custo de uma encomenda*/
int letra_C(int i, produto portfolio_p[MAXP], encomenda portfolio_e[MAXE], int total, int ide)
{
    int p;
    if (existe_e(i, ide) != 1)
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", i);
        return 0;
    }
    else
    {
         for(p = 0; p < portfolio_e[i].contador_pe; p++)
            total = total + (portfolio_p[portfolio_e[i].products[p].id].price*portfolio_e[i].products[p].stock); /* qtd*preco */
        printf("Custo da encomenda %d %d.\n", i, total);
        return 0;
    }
}
/*altera o preco de um produto existente no sistema*/
int letra_p(int a, int price, int ide, produto portfolio_p[MAXP], encomenda portfolio_e[MAXE], int idp)
{
    int i, k;
    if (existe_p(a, idp) != 1)
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", a);
        return 0;
    }
    else /* aterar o preco no sistema*/
        portfolio_p[a].price = price;

    for(i = 0; i < ide; i++) /* alterar o preco de todas as encomendas 
    que tenham o produto com o id passado como input*/
    {
        for(k = 0; k < portfolio_e[i].contador_pe; k++)
            if(portfolio_e[i].products[k].id == a)
                portfolio_e[i].products[k].price = price;
    }  
    return 0;
}

/*retorna a decricao e a quantidade de um produto numa encomenda*/
int letra_E (int a, int i, produto portfolio_p[MAXP], encomenda portfolio_e[MAXE], int idp, int ide)
{
    int k;
    int existe_pe = 0;
    if (existe_p(a, idp) != 1)
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", a);
        return 0;
    }
    else if (existe_e(i, ide) != 1)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", i);
        return 0;
    }

    else
    {
        for (k = 0; k < portfolio_e[i].contador_pe;k++)
        {
            if (portfolio_e[i].products[k].id == a)
            {
                existe_pe =1;
                printf("%s %d.\n", portfolio_p[a].description, portfolio_e[i].products[k].stock);
            }
        }
        if (existe_pe == 0)
            printf("%s 0.\n", portfolio_p[a].description);
        return 0;
    }
}

/*retorna o identificador da encomenda em que um dado produto ocorre mais vezes*/
int letra_m(int a, produto maximo, int ide, encomenda portfolio_e[MAXE], int idp)
{
    int i, k, existe_pe;
    existe_pe = 0;
    if(existe_p(a, idp) != 1)
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", a);
        return 0;
    }
    else
    {
        for(i = 0; i < ide; i++) /*percorre as encomendas*/
        {
            for(k = 0; k < portfolio_e[i].contador_pe; k++)
            {
                if (portfolio_e[i].products[k].id == a)
                {
                    existe_pe  = 1;
                    if (portfolio_e[i].products[k].stock > maximo.stock)
                    {
                        maximo.stock = portfolio_e[i].products[k].stock;
                        maximo.id = portfolio_e[i].order_id; /*id da encomenda cujo stock do produto eh maximo*/
                    }
                    if (portfolio_e[i].products[k].stock == maximo.stock &&
                        portfolio_e[i].order_id < maximo.id)
                        {
                            maximo.stock = portfolio_e[i].products[k].stock;
                            maximo.id = portfolio_e[i].order_id;
                        }
                }
            }
        }   
        if (existe_pe == 1)
            printf("Maximo produto %d %d %d.\n", a, maximo.id, maximo.stock);
        return 0;
    }
}

 /*lista todos os produtos existentes no sistema por ordem crescente de preco*/
int letra_l(int idp, produto portfolio_p[MAXP])
{
    int i;
    item b[MAXP];
    for(i = 0; i < idp; i++) /*cria uma string com os ids dos produtos nas encomendas*/
    {
        b[i] = portfolio_p[i].id;
    }
    mergesort(b, 0, idp-1, "price\0", portfolio_p);
    printf("Produtos\n");
    for(i = 0; i < idp; i++)
    {
        printf("* %s %d %d\n", portfolio_p[b[i]].description, portfolio_p[b[i]].price, portfolio_p[b[i]].stock);
    }
    return 0;
}

/*lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
int letra_L(int i, produto portfolio_p[MAXP], encomenda portfolio_e[MAXE], int ide)
{
    int p, k,j;
    item b[MAXP];
    if (existe_e(i, ide) != 1)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", i);
        return 0;
    }
    else
    {
        for(k = 0; k < portfolio_e[i].contador_pe; k++) /*cria uma string com os ids dos produtos na encomenda*/
        {
            b[k] = portfolio_e[i].products[k].id;
        }
        
        mergesort(b, 0, portfolio_e[i].contador_pe -1, "description\0", portfolio_p);
        printf("Encomenda %d\n", i);
        for(p = 0; p < portfolio_e[i].contador_pe; p++)
        {
            for(j = 0; j < portfolio_e[i].contador_pe; j++)
                if (portfolio_e[i].products[j].id == b[p])
                    printf("* %s %d %d\n", portfolio_p[b[p]].description, portfolio_p[b[p]].price, portfolio_e[i].products[j].stock);
        }
    }
    return 0;
}