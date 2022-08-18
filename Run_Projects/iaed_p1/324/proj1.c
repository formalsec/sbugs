#include <stdio.h>
#include <string.h>

#define MAX_DESCRICAO 63
#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define MAX_PRODUTOS_ENCOMENDA 200
#define NAOEXISTE 0
#define EXISTE 1
#define POR_DESCRICAO 0
#define POR_PRECO 1
#define menor_preco(A, B) (A.preco < B.preco)
#define exch(A, B) { Produto t = A; A = B; B = t; }


/* -------------------------------------------------- Estruturas -------------------------------------------------------------------------------------------*/
typedef struct produto{
    int idp; /* um identificador (um n?mero inteiro no intervalo [0, 9 999]) */
    char descricao[MAX_DESCRICAO]; /*  uma descri??o (uma string n?o vazia com um m?ximo de 63 caracteres) */
    int preco;/* o seu pre?o (um n?mero inteiro maior que 0) */
    int peso;/* o seu peso (um n?mero inteiro maior que 0) */
    int quant_stock;/* a sua quantidade dentro de uma encomenda ou stock no contexto do vetor todos os produtos (um n?mero inteiro maior ou igual a 0) */
} Produto;

typedef struct encomenda{
    int ide, n_produtos; /*  um identificador, e um indicador de produtos existentes na encomenda respetivamente  */
    Produto produtos[MAX_PRODUTOS_ENCOMENDA];
} Encomenda;


/*-------------------------------------------------- VARIAVEIS GLOBAIS ------------------------------------------------------------------------------------ */
Produto todos_produtos[MAX_PRODUTOS]; /* um vetor de produtos que guarda todos os produtos criados, eh ordenado pelo identeficador de cada produto */
Encomenda todas_encomendas[MAX_ENCOMENDAS];  /* um vetor de encomendas que guarda todos as encomendas criadas, eh ordenado pelo identeficador de cada encomenda */
int idp = 0; /* contador auxiliar, ao vetor todas_produtos. Este eh incrementado sempre que um produto e criado */
int ide = 0; /* contador auxiliar, ao vetor todas_encomendas. Este eh incrementado sempre que uma encomenda eh criada */
int primeiro_produto = NAOEXISTE; /* flag que mostra se o primeiro produto ja foi criado, visto o idp ser inicializado a zero */
int primeira_encomenda = NAOEXISTE; /* flag que mostra se a primeira encomenda ja foi criada, visto o ide ser inicializado a zero */


/*-----------------------------------------------------DECLARACAO FUNCOES-----------------------------------------------------------------------------------*/

/* adiciona um novo produto ao sistema*/
void novo_produto();
/* adiciona stock a um produto existente no sistema */
void ad_stock();
/* cria uma nova encomenda */
void nova_encomenda();
/* adiciona um produto a uma encomenda */
void adiciona_produto();
/* remove stock a um produto existente (leitura de argumentos fora da funcao, visto ser necessario remover do stock sem utilizar comandos ) */
void re_stock(int idp_re, int quantidade_re);
/* remove um produto de uma encomenda */
void re_produto_encomenda();
/* calcula o custo de uma encomenda */
void custo_encomenda();
/* altera o pre?o de um produto existente no sistema */
void altera_preco();
/* retorna a descricao e a quantidade de um produto numa dada encomenda */
void descricao_quantidade();
/* retorna o identificador da encomenda em que um dado produto ocorre mais vezes */
void ide_comais_produto();
/* lista todos os produtos existentes no sistema por ordem crescente de preco */
void ordena_preco(Produto lista[],int n_produtos);
/* lista todos os produtos de uma encomenda por ordem alfab?tica da descricao */
void ordena_alfabetica();
/* compara dois produtos, o metodo pode ser por descricao ou por preco */
int compara_produtos(Produto a,Produto b,int metodo);
/* calcula o peso de uma encomenda */
int calc_peso(Encomenda encomenda);
/* algorimto de ordenacao auxiliar quicksort */
int partition(Produto a[], int l, int r, int metodo);
/* algorimto de ordenacao */
void quicksort(Produto a[], int l, int r, int metodo);






/*------------------------------------------------------- MAIN ---------------------------------------------------------------------------------------------*/
int main()
{
    int idp_re, quantidade_re;
    while (1) {
        char command;
        command = getchar();
        switch (command) {
            case 'a':
                novo_produto();
            /* Chama a funcao responsavel pela execucao do comando a */
                break;
            case 'q':
                ad_stock();
            /* Chama a funcao responsavel pela execucao do comando q */
                break;
            case 'N':
                nova_encomenda();
                break;
            /* Chama a funcao responsavel pela execucao do comando N */
                break;
            case 'A':
                adiciona_produto();
            /* Chama a funcao responsavel pela execucao do comando A */
                break;
            case 'r':
                scanf(" %d:%d", &idp_re, &quantidade_re);
                re_stock(idp_re, quantidade_re);
            /* Chama a funcao responsavel pela execucao do comando r */
                break;
            case 'R':
                re_produto_encomenda();
            /* Chama a funcao responsavel pela execucao do comando R */
                break;
            case 'C':
                custo_encomenda();
            /* Chama a funcao responsavel pela execucao do comando c */
                break;
            case 'p':
                altera_preco();
            /* Chama a funcao responsavel pela execucao do comando P */
                break;
            case 'E':
                descricao_quantidade();
            /* Chama a funcao responsavel pela execucao do comando E */
                break;
            case 'm':
                ide_comais_produto();
            /* Chama a funcao responsavel pela execucao do comando m */
                break;
            case 'l':
            /* Chama a funcao responsavel pela execucao do comando l */
                ordena_preco(todos_produtos,idp+1);
                break;
            case 'L':
            /* Chama a funcao responsavel pela execucao do comando L */
                ordena_alfabetica(todos_produtos,idp+1);
                break;
            case 'x':
            /* Termina o programa com sucesso (STDLIB) */
                return 0;
        }
       getchar();
    }
}


/* ------------------------------------------------------------- FUNCOES AUX ------------------------------------------------------------------------------ */

void novo_produto()
{
    /* como o idp (variavel que conta o numero de produtos )comeca em zero na primeira vez que eh criado um novo produto, nao incrementamos o contador */
    if(primeiro_produto == EXISTE)
        idp++;

    if(primeiro_produto == NAOEXISTE)
        primeiro_produto = EXISTE;
    /* Guardar no vetor dos produtos o indice do produto que ?  igual ao do contador de produtos */
    todos_produtos[idp].idp = idp;
    scanf(" %[^:]:%d:%d:%d",todos_produtos[idp].descricao,&todos_produtos[idp].preco, &todos_produtos[idp].peso, &todos_produtos[idp].quant_stock);
    printf("Novo produto %d.\n",todos_produtos[idp].idp);
}


void ad_stock()
{
    int idp_ad, quantidade;
    scanf(" %d:%d", &idp_ad,&quantidade);
    
    if(idp < idp_ad || primeiro_produto == NAOEXISTE){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp_ad);
        return;
    }
    /* Guardar no vetor dos produtos o novo valor do stock */
    todos_produtos[idp_ad].quant_stock += quantidade;
    
}


void nova_encomenda()
{
    /* como o ide (variavel que conta o numero de encomendas )comeca em zero na primeira vez que eh criado uma nova encomenda, nao incrementamos o contador */
    if(primeira_encomenda == EXISTE)
        ide++;
    
    if(primeira_encomenda == NAOEXISTE)
        primeira_encomenda = EXISTE;
    
    printf("Nova encomenda %d.\n",ide);
    
    
    
}


void adiciona_produto()
{
    int ide_ad, idp_ad, quantidade,i;
    
    scanf(" %d:%d:%d", &ide_ad, &idp_ad, &quantidade);
    /* Erro Encomenda inexistente */
    if (ide < ide_ad || primeira_encomenda == NAOEXISTE)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp_ad,ide_ad);
    
    /* Erro Produto inexistente */
    else if (idp < idp_ad || primeiro_produto == NAOEXISTE)
        printf ("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp_ad,ide_ad);
    
    /* Erro  Quantidade em stock insuficiente */
    else if (quantidade  > todos_produtos[idp_ad].quant_stock )
        printf ("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp_ad,ide_ad);
    
    /* compara o peso total da encomenda (incluindo o peso do produto a adicionar) com o max de peso (200) */
    else if ( 200 < calc_peso(todas_encomendas[ide_ad]) + todos_produtos[idp_ad].peso * quantidade)
        printf ("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp_ad,ide_ad);
    
    /* No caso em que o produto ja existe na encomenda apenas adicionamos ? encomenda a quantidade */
    else{
        for(i = 0; i< todas_encomendas[ide_ad].n_produtos; i++){
            if(todas_encomendas[ide_ad].produtos[i].idp == idp_ad){
                todas_encomendas[ide_ad].produtos[i].quant_stock += quantidade;
                re_stock(idp_ad, quantidade);
                return;
            }
        }
    
    /* No caso em que o produto nao existe na encomenda */
    /* adiciona o produto ah lista de produtos na encomenda */
    todas_encomendas[ide_ad].produtos[todas_encomendas[ide_ad].n_produtos] = todos_produtos[idp_ad];
    /* regista a quantidade respetiva */
    todas_encomendas[ide_ad].produtos[todas_encomendas[ide_ad].n_produtos].quant_stock = quantidade;
    /* adiciona 1 ao numero de produtos da encomenda */
    todas_encomendas[ide_ad].n_produtos++;
    re_stock(idp_ad, quantidade);
    }
}


void ordena_preco(Produto lista[], int n_produtos )
{
    int i;
    Produto copia_lista[MAX_PRODUTOS];
    
    for (i=0; i<=idp ; i++)  /* Backup da lista de produtos, de forma a deixar o total_produtos ordenado pelo idp.*/
        copia_lista[i] = lista[i];
    
    quicksort(copia_lista, 0,n_produtos-1,POR_PRECO);
    printf("Produtos\n");
    
    if(primeiro_produto == EXISTE)
        for (i=0; i<n_produtos; i++)
            printf("* %s %d %d\n",copia_lista[i].descricao, copia_lista[i].preco, copia_lista[i].quant_stock);
}


int calc_peso(Encomenda encomenda)
{
    int i,peso=0;
    
    for(i=0; i < encomenda.n_produtos; i++)
        peso += encomenda.produtos[i].peso * encomenda.produtos[i].quant_stock;
    
    return peso;
}


void re_stock(int idp_re, int quantidade_re)
{
    /* Erro Produto inexistente */
    if (idp_re > idp || primeiro_produto == NAOEXISTE )
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp_re);
    
    /* Erro Encomenda inexistente */
    else if(todos_produtos[idp_re].quant_stock < quantidade_re )
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",quantidade_re,idp_re);
    
    /* Guardar no vetor dos produtos o novo valor do stock */
    else
        todos_produtos[idp_re].quant_stock -= quantidade_re;
    
}


void re_produto_encomenda()
{
    int ide_re, idp_re, i, i_pro_encomenda, pro_removido = NAOEXISTE;
    scanf(" %d:%d", &ide_re, &idp_re );
    /* Erro Encomenda inexistente */
    if (ide < ide_re || primeira_encomenda == NAOEXISTE){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp_re, ide_re);
    }
    /* Erro Produto inexistente */
    else if (idp < idp_re || primeiro_produto == NAOEXISTE){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp_re, ide_re);
    }
    /* encontrar o indice do produto na lista de produtos da encomenda   */
    for (i=0; i< todas_encomendas[ide_re].n_produtos; i++){
        if(todas_encomendas[ide_re].produtos[i].idp == idp_re){
            i_pro_encomenda = i;
            pro_removido = EXISTE;
            }
    }
     /* se o produto nao existe  */
    if(pro_removido == NAOEXISTE) return;
    /* adicionar a quantidade do produto na encomenda do stock */
    
    todos_produtos[idp_re].quant_stock += todas_encomendas[ide_re].produtos[i_pro_encomenda].quant_stock;
    /* remover o produto da lista de produtos da encomenda */
    for (i=i_pro_encomenda; i< todas_encomendas[ide_re].n_produtos; i++)
        todas_encomendas[ide_re].produtos[i] = todas_encomendas[ide_re].produtos[i+1];
    /* remover 1 ao numero de produtos da encomenda */
    todas_encomendas[ide_re].n_produtos--;
    
}

void custo_encomenda()
{
    int custo_total = 0, ide_input, i;
    scanf(" %d", &ide_input);
    /* Erro Encomenda inexistente */
    if (ide < ide_input || primeira_encomenda == NAOEXISTE ){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide_input);
        return;
    }
    /* percorre todos os produtos na encomenda, atualizando o custo_total (somando consecutivamente o custo de cada produto da encomenda )*/
    for(i=0; i<todas_encomendas[ide_input].n_produtos; i++){
        custo_total += todas_encomendas[ide_input].produtos[i].preco * todas_encomendas[ide_input].produtos[i].quant_stock;
    }
    
    printf("Custo da encomenda %d %d.\n",ide_input, custo_total);
}

void altera_preco()
{
    int preco, idp_input,i,j;
    scanf( " %d:%d", &idp_input, &preco );
    /* Erro Encomenda inexistente */
    if ( idp < idp_input || primeiro_produto == NAOEXISTE )
       printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp_input);
    /* atualiza o valor do preco no vetor todos os produtos */
    todos_produtos[idp_input].preco = preco;
    
    /* atualiza o valor do preco do produto em todas as encomendas */
    for (i=0; i<=ide; i++ )
        for (j=0; j<=todas_encomendas[i].n_produtos; j++)
            if(todas_encomendas[i].produtos[j].idp == idp_input)
                todas_encomendas[i].produtos[j].preco = preco;
}

void descricao_quantidade()
{
    int i, idp_input, ide_input ;
    scanf( " %d:%d", &ide_input, &idp_input );
    /* Erro Encomenda inexistente */
    if ( ide < ide_input || primeira_encomenda == NAOEXISTE ){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide_input);
        return;
    }
    /* Erro Produto inexistente */
    if ( idp < idp_input || primeiro_produto == NAOEXISTE){
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp_input);
        return;
    }
    /* percorre todos os produtos na encomenda ate encontrar o produto com idp indicado no input, seguidamente imprime a respetiva descricao e quantidade */
    for (i=0; i<todas_encomendas[ide_input].n_produtos; i++){
        if (todas_encomendas[ide_input].produtos[i].idp == idp_input){
            printf("%s %d.\n",todas_encomendas[ide_input].produtos[i].descricao,todas_encomendas[ide_input].produtos[i].quant_stock);
            return;
        }
    }
    /* Caso em que o produto nao existe em nenhuma encomenda */
    printf("%s 0.\n",todos_produtos[idp_input].descricao);
}

void ide_comais_produto()
{
    int idp_input, i, j, ide_comais_produto = 0, quantidade = 0, flag = NAOEXISTE;
    scanf( " %d",&idp_input );
    /* Erro Produto inexistente */
    if ( idp < idp_input || primeiro_produto == NAOEXISTE )
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp_input);
    
    /* Percorre todas as encomendas todos os produtos em todas as encomendas */
    for (i=0; i<=ide; i++ )
        for (j=0; j<todas_encomendas[i].n_produtos; j++)
            if(todas_encomendas[i].produtos[j].idp == idp_input){ /* quando encontra o produto  */
                if(todas_encomendas[i].produtos[j].quant_stock == quantidade)  /* no caso de a quantidade do produto na encomenda ser igual ah maior ate ao momento  */
                    if(i < ide_comais_produto) /* compara o idp */
                        ide_comais_produto = i; /* atualiza o ide com mais produto */
                    
                if(todas_encomendas[i].produtos[j].quant_stock > quantidade){ /* no caso de a quantidade  do produto na encomenda for maior do que a maior ate ao momento  */
                    ide_comais_produto = i; /* atualiza o ide com mais produto*/
                    quantidade = todas_encomendas[i].produtos[j].quant_stock; /* atualiza a quantidade */
                }
                flag = EXISTE; /* confirma que existe o produto indicado pelo input pelo menos numa encomenda */
            }

    
    if(flag == EXISTE)
        printf("Maximo produto %d %d %d.\n",idp_input, ide_comais_produto, quantidade);
}

void ordena_alfabetica()
{
    int i,ide_input;
    Produto copia_lista[MAX_PRODUTOS];
    scanf(" %d", &ide_input);
    /* Erro Encomenda inexistente */
    if ( ide < ide_input || primeira_encomenda == NAOEXISTE ){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide_input);
        return;
    }

    for (i=0;i< todas_encomendas[ide_input].n_produtos; i++)  /* Backup da lista de encomendas, de forma a deixar o total_produtos ordenado pelo ide.*/
        copia_lista[i] = todas_encomendas[ide_input].produtos[i];
    
    quicksort(copia_lista, 0,todas_encomendas[ide_input].n_produtos-1, POR_DESCRICAO); /* ordena os produtos da copia da lista por descricao */
    printf("Encomenda %d\n", ide_input);
    
    for (i=0; i< todas_encomendas[ide_input].n_produtos; i++)
        printf("* %s %d %d\n",copia_lista[i].descricao, copia_lista[i].preco, copia_lista[i].quant_stock);
}

int compara_produtos(Produto a,Produto b,int metodo) {
    if (metodo == POR_DESCRICAO)
        return strcmp(a.descricao,b.descricao) < 0;
    
    if (metodo == POR_PRECO){
        if(a.preco != b.preco )
            return a.preco < b.preco;
        else
            return a.idp < b.idp;
    }
    return 0;
    
}




int partition(Produto a[], int l, int r, int metodo )
{
    int i = l-1;
    int j = r;
    Produto v = a[r];
    
    while(i < j){
        while (compara_produtos(a[++i],v,metodo));
        while (compara_produtos(v, a[--j],metodo))
            if (j == l)
                break;
        if (i < j)
            exch(a[i],a[j]);
    }
    
    exch(a[i],a[r]);
    return i;
    
}


void quicksort(Produto a[], int l, int r,int metodo)
{
    int i;
    
    if(r <= l)
        return;
    i = partition(a,l,r,metodo);
    quicksort(a, l, i-1,metodo);
    quicksort(a, i+1, r,metodo);
}





