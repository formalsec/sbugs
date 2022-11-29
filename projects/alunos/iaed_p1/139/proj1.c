#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/*-------------------------------Constantes----------------------------------*/

#define chave(A) (A)
#define menor_igual(A,B) (chave(A).preco<=chave(B).preco)
#define copia(A,B) (A=B)
#define menor_igual_str(A,B) (strcmp(chave(A).nome,chave(B).nome)<=0)
#define MAX_LETRAS 64 /* 63 carateres + '\0' */
#define IDENT 10000
#define MAX_ENCOMENDAS 500
#define FALSO 0
#define VERDADEIRO 1
#define MAX_PROD_ENC 200

/* estrutura de um produto: tem nome,preco,peso e quantidade*/
typedef struct Produto
{
    char nome[MAX_LETRAS];
    int preco,peso,quantidade;
}Produto;

/* estrutura de um produto de uma encomenda, para alem das caracteristicas 
normais tem um id que identifica o produto na encomenda*/
typedef struct Encomenda
{
    Produto prod;
    int id_produto;
}Encomenda;

void adic_sub_peso(int id_produto,int peso_encomendas[],int qtd,int id_encomenda);
void adiciona_stock_prod(int id,int qtd);
void adiciona_stock_enc(int id_encomenda,int id_produto,int qtd);
int existe_encomenda_produto(int id,int marcador);
int prod_na_encomenda(int id_prod,int id_encomenda);
void retira_stock_prod(int id,int qtd);
void retira_stock_enc(int id_encomenda,int id_produto,int qtd);
int adiciona_prod( );
void adiciona_stock();
int adiciona_encomenda();
void adic_prod_encomenda(int peso_encomendas[]);
void remove_stock();
void retira_produto_encomenda(int peso_encomendas[]);
void custo_encomenda();
void muda_preco();
void lista_nome_quant();
void lista_encomenda();
void merge_sort(Produto produtos[],int l, int r);
void merge(Produto produtos[],int l,int m, int r);
void organiza_produtos();
void merge_sort_char(Encomenda  a[],int l, int r);
void merge_char(Encomenda  a[],int l,int m, int r);
void organiza_encomenda();




/*-------------------------------Variaveis Globais---------------------------*/

/* sistema composto por no maximo 10000 produtos*/
Produto produtos[IDENT]={0};

/* conjunto das encomendas composto por 500 encomendas e no maximo 200 
produtos por encomenda visto que o peso maximo e 200kg e cada produto
tem no minimo 1kg*/
Encomenda encomendas[MAX_ENCOMENDAS][200];

/*marcadores para saber quantos produtos e quantas encomendas, respetivamente,
ja foram registadas*/
int identificador=0,ident_enc=0;

/*vetor para saber quantos produtos ja existem em cada encomenda*/
int prod_encomenda[MAX_ENCOMENDAS]={0};

int main()
{
    
    
    /*letra para definir o comando a utilizar*/
    char letra;

    /*vetor para registar o peso de cada encomenda*/
    int peso_encomendas[MAX_ENCOMENDAS]={0};

    
    
    
    /*enquanto nao for introduzida a letra 'x' o programa vai continuar
    lendo a letra e executando o respetivo comando*/
    scanf("%c",&letra);
    while(letra!='x')
    {
        switch(letra)
        {
            case 'a':
            
            /*igualamos o identificador ao valor da funcao para o valor 
            deste ir atualizando sabendo quantos produtos ha*/
                
                identificador=adiciona_prod();
                break;
            case 'q':
                
                adiciona_stock();
                break;
            case 'N':
            /*o mesmo caso do identificador so que com as encomendas*/
                ident_enc=adiciona_encomenda();
                break;
            case 'A':
                adic_prod_encomenda(peso_encomendas);
                break;
            case 'r':
                
                remove_stock();
                break;
            case 'R':
                retira_produto_encomenda(peso_encomendas);
                break;
            case 'C':
                custo_encomenda();
                break;
            case 'p':
                muda_preco();
                break;
            case 'E':
                lista_nome_quant();
                break;
            case 'm':
                lista_encomenda();
                break;
            case 'l':
                organiza_produtos();
                break;
            case 'L':
                organiza_encomenda();
                break;
        }
        scanf("%c",&letra);
    }
    return 0;
}


/*-------------------------------Funcoes auxiliares--------------------------*/



/*funcao que subtrai ou adiciona peso ao registo das encomendas,
introduzindo um qtd negativo para subtrair ou positivo para adicionar*/
void adic_sub_peso(int id_produto,int peso_encomendas[],int qtd,int id_encomenda)
{
    peso_encomendas[id_encomenda]+=(produtos[id_produto].peso*qtd);
}

/*funcao auxiliar para adicionar uma certa quantidade ao produto no sistema*/
void adiciona_stock_prod(int id,int qtd)
{
    produtos[id].quantidade+=qtd;
}

/*funcao auxiliar que adiciona uma certa quantidade de um produto a uma encomenda*/
void adiciona_stock_enc(int id_encomenda,int id_produto,int qtd)
{
    encomendas[id_encomenda][id_produto].prod.quantidade+=qtd;
}

/*funcao auxiliar que determina se a encomenda ou o produto existem*/
int existe_encomenda_produto(int id,int marcador)
{
    /* para tal e introduzido o marcador da encomenda/produto e o id do produto
    que desejam saber se existe ou nao, se for superior ao marcador quer dizer que ainda
    nao foi registado*/

    if(id>=marcador)
        return FALSO;
    else
        return VERDADEIRO;
}

/*funcao para saber se um produto ja se encontra na encomenda*/
int prod_na_encomenda(int id_prod,int id_encomenda)
{
    /*percorre todos os produtos existentes de uma encomenda. Se o id do produto 
    pretendido estiver na encomenda e a sua quantidade for maior que 0
    entao e' porque o produto existe nessa encomenda*/
    int i;
    int j=prod_encomenda[id_encomenda];
    for(i=0;i<j;i++)
    {
        if(encomendas[id_encomenda][i].id_produto==id_prod)
        {
            if (encomendas[id_encomenda][i].prod.quantidade!=0)
                return VERDADEIRO;
            break;
        }
    }
    
    
    return FALSO;
}

/* funcao auxiliar para remover stock a um produto no sistema*/

void retira_stock_prod(int id,int qtd)
{
    produtos[id].quantidade-=qtd;
}

/* funcao auxiliar para remover stock a um produto numa encomenda*/

void retira_stock_enc(int id_encomenda,int id_produto,int qtd)
{
    encomendas[id_encomenda][id_produto].prod.quantidade-=qtd;
}

/*-------------------------------Funcoes principais--------------------------*/

/* funcao para adicionar um certo produto ao sistema */
int adiciona_prod( )
{
    
    
    int preco,peso,quantidade;
    char nome[MAX_LETRAS];
    
    scanf(" %[^:]:%d:%d:%d",nome,&preco,&peso,&quantidade);

    /* Guardar as variaveis no produto do sistema  */
    
    strcpy(produtos[identificador].nome,nome);
    produtos[identificador].preco=preco;
    produtos[identificador].peso=peso;
    produtos[identificador].quantidade=quantidade;
    
    

    printf("Novo produto %d.\n",identificador);

    /* incrementacao e retorno do identificador para ir
    atualizando o seu valor, sabendo assim quantos diferentes
    produtos existem*/
    identificador++;
    return identificador;
    
}




/* funcao que adicionada uma certa quantidade de um certo
porduto existente no sistema*/

void adiciona_stock()
{
    
    int id,qtd;
    
    scanf("%d:%d",&id,&qtd);
   
    /* o stock e adicionado se ja estiver registado senao
gera uma mensagem de erro*/
    if(existe_encomenda_produto(id,identificador)==VERDADEIRO)
    {
        adiciona_stock_prod(id,qtd);
    }
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);
    
}

/* funcao que cria uma encomenda nova*/
int adiciona_encomenda()
{
    /* Criacao da encomenda ao incrementar o id de encomendas
    e posterior retorno da variavel    */
    printf("Nova encomenda %d.\n",ident_enc);
    
    ident_enc++;
    return ident_enc;

}








/* funcao para adicionar uma certa quantidade de um produto
a uma dada encomenda*/
void adic_prod_encomenda(int peso_encomendas[])
{
    

    int id_encomenda,id_produto,quant,i,state;

    scanf("%d:%d:%d",&id_encomenda,&id_produto,&quant);

    /*condicoes necessarias para adicionamento:*/

    /*encomenda existir*/
    if(existe_encomenda_produto(id_encomenda,ident_enc)==FALSO)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",id_produto,id_encomenda);

    /*produto existir*/

    else if(existe_encomenda_produto(id_produto,identificador)==FALSO)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",id_produto,id_encomenda);

    /*haver quantidade suficiente para a encomenda*/
    else if(quant>produtos[id_produto].quantidade)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",id_produto,id_encomenda);
    
    /*nao exceder o peso de 200*/
    else if((peso_encomendas[id_encomenda]+produtos[id_produto].peso*quant)>200)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",id_produto,id_encomenda);

    else
    {
        
        /*estado para saber se o produto esta na encomenda*/
        state=prod_na_encomenda(id_produto,id_encomenda);
        
        for(i=0;i<200;i++)
        {
            /* se o espaco na encomenda estiver livre(quantidade==0) e o produto 
            nao estiver na encomenda o produto e adicionado e os seus dados 
            sao copiados para a encomenda*/
            if ( state==FALSO && encomendas[id_encomenda][i].prod.quantidade==0 )
            {
                
                adiciona_stock_enc(id_encomenda,i,quant);
                
                strcpy(encomendas[id_encomenda][i].prod.nome,produtos[id_produto].nome);
                encomendas[id_encomenda][i].prod.preco=produtos[id_produto].preco;
                encomendas[id_encomenda][i].id_produto=id_produto;
                prod_encomenda[id_encomenda]++;
                
                break;
            }

            /* se o produto ja estiver na encomenda e o id corresponder ao do produto
            a quantidade e' adicionada mas nao sao copiados os dados pois eles ja
            se encontravam na encomenda*/
            else if (encomendas[id_encomenda][i].id_produto==id_produto && state==VERDADEIRO)
            {
                
                adiciona_stock_enc(id_encomenda,i,quant);
                break;
            }
        }

        /*e adicionado o peso a encomenda e retirado o stock do produto no sistema
        para meter na encomenda*/
        adic_sub_peso(id_produto,peso_encomendas,quant,id_encomenda);
        retira_stock_prod(id_produto,quant);
        

        
    }
    

}


/* funcao que remove uma certa quantidade de um produto*/
void remove_stock()
{
    
    int id,qtd;

    scanf("%d:%d",&id,&qtd);

    /* para essa quantidade ser adicionada o produto tem que:*/
    /* existir;*/
    if(existe_encomenda_produto(id,identificador)==FALSO)
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",id);
    }

    /*ter stock suficiente*/
    else if(qtd>produtos[id].quantidade)
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,id);
    }

    /* se verificar as condicoes necessarias e' removida a quantidade desejada*/
    else
    {
        retira_stock_prod(id,qtd);
    }
}

/*funcao que remove um certo produto de uma encomenda*/
void retira_produto_encomenda(int peso_encomendas[])
{
    
    int id_produto,id_encomenda,i,j;

    scanf("%d:%d",&id_encomenda,&id_produto);

    /*num de produtos na encomenda*/
    j=prod_encomenda[id_encomenda];

    /* encomenda tem que existir*/
    if(existe_encomenda_produto(id_encomenda,ident_enc)==FALSO)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",id_produto,id_encomenda);
    
    /*produto tem que existir*/
    else if(existe_encomenda_produto(id_produto,identificador)==FALSO)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",id_produto,id_encomenda);
    else
    {
        /* e atualizado:
        --> o peso da encomenda ao subtrair o peso total do produto existente
        --> o stock ao ser adicionado o stock removido a encomenda
        --> a encomenda ao ser-lhe removido toda a quantidade do produto*/
        
        /*ciclo que percorre o num de produtos nessa encomenda ate encontrar o produto*/
        for(i=0;i<j;i++)
        {
            if(encomendas[id_encomenda][i].id_produto==id_produto)
            {
                adic_sub_peso(id_produto,peso_encomendas,-encomendas[id_encomenda][i].prod.quantidade,id_encomenda);
                adiciona_stock_prod(id_produto,encomendas[id_encomenda][i].prod.quantidade);
                retira_stock_enc(id_encomenda,i,encomendas[id_encomenda][i].prod.quantidade);
                break;
            }
        }
        
        
        
    }
}

/*funcao que calcula o custo de uma encomenda*/
void custo_encomenda()
{
    
    int id_encomenda;
    int i,cost=0,j;

    scanf("%d",&id_encomenda);

    /*num de produtos na encomenda*/
    j=prod_encomenda[id_encomenda];

    /*encomenda tem que existir*/
    if(existe_encomenda_produto(id_encomenda,ident_enc)==FALSO)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id_encomenda);
    else
    {
        /*percorre todos os produtos nessa encomenda e vai adicionando o preco*quantidade*/
        for(i=0;i<j;i++)
        {
            cost+=encomendas[id_encomenda][i].prod.preco*encomendas[id_encomenda][i].prod.quantidade;
        }
            
        printf("Custo da encomenda %d %d.\n",id_encomenda,cost);
        
    }
    
}

/*funcao que altera o preco de um produto existente no sistema*/
void muda_preco()
{
    
    int id_produto,preco,i,j;

    scanf("%d:%d",&id_produto,&preco);

    /*produto tem que existir*/

    if(existe_encomenda_produto(id_produto,identificador)==FALSO)
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",id_produto);
    }
    else 
    {   
        /*preco muda no sistema*/
        produtos[id_produto].preco=preco;

        /*ciclo percorre as encomendas e se o produto existir o seu preco e mudado*/
        for(i=0;i<ident_enc;i++)
        {
            for(j=0;j<prod_encomenda[i];j++)
            {
                if(encomendas[i][j].id_produto==id_produto)
                {
                    encomendas[i][j].prod.preco=preco;
                    break;
                }
            }
            
        }
    }
}

/*funcao que lista a descricao e a quantidade de um produto numa encomenda*/
void lista_nome_quant()
{
    
    int id_encomenda,id_produto,quant=0,i,j;

    scanf("%d:%d",&id_encomenda,&id_produto);

    j=prod_encomenda[id_encomenda];

    /*encomenda tem que existir*/
    if(existe_encomenda_produto(id_encomenda,ident_enc)==FALSO)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_encomenda);
    
    /*produto tem que existir*/
    else if(existe_encomenda_produto(id_produto,identificador)==FALSO)
        printf("Impossivel listar produto %d. Produto inexistente.\n",id_produto);

    else
    {
        /*se o produto existir na encomenda*/
        if(prod_na_encomenda(id_produto,id_encomenda)==VERDADEIRO)
        {
            /*percorre os produtos da encomenda e quando o encontrar a sua 
            quantidade e' guardada e o ciclo acaba*/
            for(i=0;i<j;i++)
            {
                if(encomendas[id_encomenda][i].id_produto==id_produto )
                {
                    quant=encomendas[id_encomenda][i].prod.quantidade;
                    
                    break;
                }
            } 
        }  
        printf("%s %d.\n",produtos[id_produto].nome,quant);
    }
}

/*funcao que lista o identificador da encomenda  em que o produto dado ocorre mais vezes*/
void lista_encomenda()
{
    
    int id_produto;
    int i=0,max=0,id_encomenda=0,j;

    scanf("%d",&id_produto);

    /*produto tem que existir*/
    if(existe_encomenda_produto(id_produto,identificador)==FALSO)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id_produto);
    
    
    else 
    {
        /* percorre cada encomenda registada*/
        for(i=0;i<ident_enc;i++)
        {
            
            for(j=0;j<prod_encomenda[i];j++)
            {
                if(encomendas[i][j].id_produto==id_produto)
                {
                    /*se a quantidade do produto naquela encomenda for maior que o maximo
                este e substituido e e' guardado o id dessa encomenda*/
                    if (max<encomendas[i][j].prod.quantidade)
                    {
                        max=encomendas[i][j].prod.quantidade;
                        id_encomenda=i;
                        break;
                        
                    }
                    
                }
                
            }
            
        }

        /* para haver retorno tem que haver encomendas e haver alguma encomenda 
        com esse produto*/
        if(ident_enc!=0 && max!=0)
            printf("Maximo produto %d %d %d.\n",id_produto,id_encomenda,max);
    }
}

/*algoritmo de ordenacao merge sort*/

void merge(Produto a[],int l,int m, int r)
{
    int i,j,k;
    int n1=m-l+1;
    int n2=r-m;
    
    /*vetores auxiliares */
    Produto L[IDENT/2],R[IDENT/2];

    /*copiar os elementos para o vetor auxiliar(metade para cada vetor)*/
    for(i=0;i<n1;i++)
        copia(L[i],a[l+i]);
        
    for(j=0;j<n2;j++)
        copia(R[j],a[m+1+j]);
        
    i=0,j=0,k=l;

    /*organiza o vetor(se o elemento da metade da direita for maior ou igual
    ao da esquerda o elemento da esquerdo vai para a posicao k do vetor principal 
    se nao vai o elemento da direita)*/
    while(i<n1 && j<n2)
    {
        if(menor_igual(L[i],R[j]))
        {
            copia(a[k],L[i++]);
            
            
        }
        else
        {
            copia(a[k],R[j++]);
            
        }
        k++;
    }

    /*copiar os restantes elementos para o vetor principal*/
    while(i<n1)
    {
        copia(a[k++],L[i++]);
        
    }
    while(j<n2)
    {
        copia(a[k++],R[j++]);
        
    }
    
}
void merge_sort(Produto a[],int l, int r)
{
    
    if(r>l)
    {
        int m=l+(r-l)/2;
        merge_sort(a,l,m);
        merge_sort(a,m+1,r);
        merge(a,l,m,r);
    }
}
/*funcao que lista todos os produtos existentes no sistema por ordem crescente de preco*/
void organiza_produtos()
{
    /*vetor de produtos auxiliar*/
    Produto A[IDENT]={0};
    int i;

    
    /*produtos existentes sao copiados do sistema original
    para um auxiliar para que o original nao seja alterado*/
    for(i=0;i<identificador;i++)
    {
        A[i]=produtos[i];
        
                  
    }

    /*utilizado o merge sort para ordenar os produtos por ordem de preco*/
    merge_sort(A,0,identificador-1);
    printf("Produtos\n");
    
    /*e' imprimido cada produto ja ordenado*/
    for(i=0;i<identificador;i++)
    {
        printf("* %s %d %d\n",A[i].nome,A[i].preco,A[i].quantidade);
    }


}

/*versao do algoritmo merge sort para strings, metodo semelhante ao anterior*/ 
void merge_char(Encomenda a[],int l,int m, int r)
{
    int i,j,k;
    int n1=m-l+1;
    int n2=r-m;
    

    Encomenda L[200],R[200];

    for(i=0;i<n1;i++)
        copia(L[i],a[l+i]);
        
    for(j=0;j<n2;j++)
        copia(R[j],a[m+1+j]);
        
    i=0,j=0,k=l;
    while(i<n1 && j<n2)
    {
        if(menor_igual_str(L[i].prod,R[j].prod))
        {
            copia(a[k],L[i++]);
        }
        else
        {
            copia(a[k],R[j++]);
            
        }
        k++;
    }
    while(i<n1)
    {
        copia(a[k++],L[i++]);
        

    }
    while(j<n2)
    {
        copia(a[k++],R[j++]);
        
    }
    
}
void merge_sort_char(Encomenda  a[],int l, int r)
{
    
    if(r>l)
    {
        int m=l+(r-l)/2;
        merge_sort_char(a,l,m);
        merge_sort_char(a,m+1,r);
        merge_char(a,l,m,r);
    }
}

/* lista todos os produtos de uma encomenda por ordem alfabetica de descricao*/
void organiza_encomenda()
{
    
    int i,id_encomenda,j,k=0;
    
    /*estrutura de encomendas auxiliar*/
    Encomenda A[200];
    scanf("%d",&id_encomenda);
    
    j=prod_encomenda[id_encomenda];
    
    /* se existir a encomenda*/
    if(existe_encomenda_produto(id_encomenda,ident_enc)==VERDADEIRO)
    {
        /*preenchimento do vetor auxiliar com os produtos da encomenda*/
        for(i=0;i<j;i++)
        {
            if (encomendas[id_encomenda][i].prod.quantidade!=0)
            {
                A[k]=encomendas[id_encomenda][i];
                k++;
            }
        }
        
        /*organizacao com merge sort*/
        merge_sort_char(A,0,k-1);
        printf("Encomenda %d\n",id_encomenda);
        
        /*ciclo para imprimir os produtos ja organizados*/
        for(i=0;i<k;i++)
        {
            
            
            printf("* %s %d %d\n",A[i].prod.nome,A[i].prod.preco,A[i].prod.quantidade);

        }
    }
    else
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_encomenda);


}