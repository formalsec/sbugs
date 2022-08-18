#include <string.h>
#include <stdio.h>

/* Tamanho de uma string com 63 caracteres. */
#define STR_SIZE 64

/* Tamanho maximo de produtos */
#define TAM_MAX 10000

/*Quantidade maxima de encomendas */
#define MAX_ENC 500

/* Tamanho do vetor auxiliar para o mergesort*/
#define MAXN 10000

/* Valor para flag para indicar o tipo de sort */
#define PRC 1

/* Valor flag para indicar o tipo de sort */
#define STRING 0

/* Chave para preco */
#define chave_preco(A) todos_produtos[A].preco

/* Chave para ID */
#define chave_id(A) A.id

/* Chave para descricao */
#define chave_desc(A) todos_produtos[A].descricao

/* Macro para comparar os produtos segundo o preco */
#define menor_prc(A,B) ((chave_preco(A) < chave_preco(B))||((chave_preco(A) == chave_preco(B))&&menor_id(A,B)))

/* Macro para comparar os produtos segundo o id */
#define menor_id(A,B) (A < B)

/* Macro para comparar os produtos segundo ordem alfabetica */
#define menor_desc(A,B) ((strcmp(chave_desc(A),chave_desc(B)) < 0)||((strcmp(chave_desc(A),chave_desc(B)) == 0)&&menor_id(A,B)))

/* Estrutura de um produto. */
typedef struct{
    char descricao[STR_SIZE];
    int preco;
    int peso;
    int qtd;
} produto;

/* Estrutura de uma encomenda. */
typedef struct{
    int qtd[TAM_MAX];
} encomenda;

/* Vetor de tamanho 10,000 que ira guardar todos os produtos em stock */
produto todos_produtos[TAM_MAX];

/* Vetor de tamanho 500 que ira armazenar a encomenda */
encomenda todas_encomendas[MAX_ENC];

/* Vetor auxiliar para fazer sort */
int aux[TAM_MAX];

/* Flag para indicar o tipo de sort */
short k;

/* Funcao auxiliar do mergesort que junta 2 vetores ordenados num vetor ordenado */
void merge(int a[],int inicio,int meio,int fim){
    int i,j,r;
    for(i=meio+1;i>inicio;i--)
        aux[i-1] = a[i-1];
    for(j=meio;j<fim;j++)
        aux[fim+meio-j] = a[j+1];
    if(k)/* sort de acordo com o preco */
        for(r=inicio;r<=fim;r++){
            if(menor_prc(aux[j], aux[i]))
                a[r] = aux[j--];
            else
                a[r] = aux[i++];
        }
    else /* sort de acordo com a ordem alfabetica */
        for(r=inicio;r<=fim;r++){
            if(menor_desc(aux[j], aux[i]))
                a[r] = aux[j--];
            else
                a[r] = aux[i++];
        }
}

/* Funcao para ordenar os produtos de uma encomenda consoante a chave fornecida */
void mergesort(int a[],int inicio,int fim){
    int meio = (inicio+fim)/2;
    if(fim <= inicio)
        return;
    mergesort(a,inicio,meio);
    mergesort(a,meio+1,fim);
    merge(a,inicio,meio,fim);
}

/* Funcao que coloca valores do ids dos produtos num vetor */
void criar_vetor_indices(int array[]){
    int i;
    for(i=0;i<TAM_MAX;i++)
        array[i] = i;
}

/* Funcao qur coloca os valores dos ids dos produtos presentes nas encomendas num vetor*/
int criar_vetor_indices_enc(int array[],int ide){
    int i,j;
    j = 0;
    for(i=0;i<TAM_MAX;i++)
        if(todas_encomendas[ide].qtd[i] != 0){
            array[j] = i;
            j++;
        };
    return j;
}


/* Funcao que devolve o peso total de uma encomenda */
int peso_enc(int ide){
    int total,i;
    i = total = 0;
    while(todos_produtos[i].peso != 0){/* Percorre o vetor com os ids dos produtos*/
        total += todos_produtos[i].peso * todas_encomendas[ide].qtd[i];/* soma ao total (o numero de produtos) * (o peso individual) */
        i++;
    };
    return total;
}

/* Funcao "a" que adiciona um novo produto ao sistema*/
int a(int n_prod){
    int c,i;
    i = 0;
    /* para ler o espaco */
    c = getchar(); 
    /*Le a descricao do produto */
    while((c=getchar())!=':'){
        todos_produtos[n_prod].descricao[i] = c;
        i++;
    };
    todos_produtos[n_prod].descricao[i] = '\0';
    /* Le as restantes caracteristicas do produto e coloca as no produto*/
    scanf("%d:%d:%d",&todos_produtos[n_prod].preco,&todos_produtos[n_prod].peso,&todos_produtos[n_prod].qtd);
    printf("Novo produto %d.\n",n_prod);
    /* Retorna o num_produto atualizado */
    return n_prod + 1;
}

/* Funcao "q" que caso o produto exista adiciona stock ao produto e em
   caso contrario devolve um "erro" */
void q(int n_prod){
    int id,qtd;
    /* para ler o espaco */
    id = getchar();
    scanf("%d:%d",&id,&qtd);
    /* Verifica se o id do produto e valido */
    if (id < n_prod)
        todos_produtos[id].qtd += qtd;
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);
}

/* Funcao que cria uma nova encomenda */
int N(int num_e){
    printf("Nova encomenda %d.\n",num_e);
    return num_e + 1;
}


/* Funcao que caso a encomenda e o produto sejam validos adiciona um produto
   a uma encomenda ou adiciona stock a um produto ja presente nessa encomenda
   caso contrario gera um "erro" */
void A(int num_produto,int num_e){
    int ide,idp,qtd;
    /* para ler o espaco */
    ide = getchar();
    scanf("%d:%d:%d",&ide,&idp,&qtd);
    if(ide>=num_e){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    }else if(idp >= num_produto){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    }else if(qtd > todos_produtos[idp].qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
    }else if((peso_enc(ide)+qtd*todos_produtos[idp].peso)>200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
    }else{
        todas_encomendas[ide].qtd[idp] += qtd;
        todos_produtos[idp].qtd -= qtd;
    };
}

/* Funcao que caso o produto exista retira stock ao produto (se for 
   suficiente ) e em caso contrario devolve um "erro" */
void r(int num_produto){
    int idp,qtd;
    idp = getchar();
    scanf("%d:%d",&idp,&qtd);
    if(idp >= num_produto)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
    else if (todos_produtos[idp].qtd-qtd < 0)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
    else
        todos_produtos[idp].qtd -= qtd;
}

/* Funcao que caso os ids da encomenda e do produto sejam validos remove o produto IDP a encomenda IDE*/
void R(int num_e,int num_produto){
    int ide,idp;
    /* espaco*/
    ide = getchar();
    scanf("%d:%d",&ide,&idp);
    if(ide>=num_e){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    }else if(idp>=num_produto){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    }else{
        todos_produtos[idp].qtd += todas_encomendas[ide].qtd[idp];
        todas_encomendas[ide].qtd[idp] = 0;
    };
}

/* Funcao que caso o id da encomenda seja valido devolve o preco total da encomenda */
void C(int num_e,int num_produto){
    int ide,total,i;
    i = total = 0;
    /* Espaco */
    ide = getchar();
    scanf("%d",&ide);
    if(ide>=num_e){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
    }else{
        for(i=0;i<num_produto;i++)
            total+= todas_encomendas[ide].qtd[i] * todos_produtos[i].preco;
        printf("Custo da encomenda %d %d.\n",ide,total);
    };
}

/* Funcao que altera o preco de um produto caso o id deste seja valido */
void p(int num_produto){
    int idp,preco;
    /* Para o espaco */
    idp = getchar();
    scanf("%d:%d",&idp,&preco);
    if(idp>=num_produto)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
    else
        todos_produtos[idp].preco = preco;
}

/* Funcao que lista a descricao e quantidade de um produto numa encomenda (caso os ids fornecidos sejam validos) */
void E(int num_produto, int num_e){
    int ide,idp;
    /*Para o espaco */
    ide = getchar();
    scanf("%d:%d",&ide,&idp);
    if(ide >= num_e){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    }else if(idp >= num_produto){
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
    }else{
        printf("%s %d.\n",todos_produtos[idp].descricao,todas_encomendas[ide].qtd[idp]);
    };
}

/* Funcao que lista o id da encomenda em que um produto ocorre mais vezes (caso o id do produto fornecido seja valido) */
void m(int num_produto,int num_e){
    int i,idp,max,max_i;
    /* Para ler o espaco */
    idp = getchar();
    max = max_i = 0;
    scanf("%d",&idp);
    if(idp>=num_produto){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
    }else{
        for(i=0;i<num_e;i++){/* Percorre todos os produtos da encomenda e caso a quantidade seja maior atualiza os valores */
            if(todas_encomendas[i].qtd[idp]>max){
                max = todas_encomendas[i].qtd[idp];
                max_i = i;
            };
        };
        if(max)
            printf("Maximo produto %d %d %d.\n",idp,max_i,max);
    }
}

/* Funcao que lista todos os produtos de sistema por ordem crescente de preco */
void l(int num_produto){
    int indices[TAM_MAX],i;
    criar_vetor_indices(indices);
    k = PRC;
    mergesort(indices,0,num_produto-1);
    printf("Produtos\n");
    for(i=0;i<num_produto;i++){
        int id;
        id = indices[i];
        printf("* %s %d %d\n",todos_produtos[id].descricao,todos_produtos[id].preco,todos_produtos[id].qtd);
    };
}

/* Funcao que lista todos os produtos de uma encomenda por ordem alfabetica */
void L(int num_e){
    int indices[TAM_MAX],ide,i,len;
    /* Para ler o espaco */
    ide = getchar();
    scanf("%d",&ide);
    if (ide >= num_e){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    }else{
        len = criar_vetor_indices_enc(indices,ide);
        k = STRING;
        mergesort(indices,0,len-1);
        printf("Encomenda %d\n",ide);
        for(i=0;i<len;i++){
            int id;
            id = indices[i];
            printf("* %s %d %d\n",todos_produtos[id].descricao,todos_produtos[id].preco,todas_encomendas[ide].qtd[id]);
        }
    };
}

int main(){
    /* Variavel que controla quando sera terminada a execucao
       do programa */
    int estado = 1;

    /* Variavel para onde e lido o caracter lido */
    int c;

    /* Inteiro que aponta para um indice do vetor stock */
    int num_produto = 0;

    /* Inteiro que aponta para um indice do vetor num_prod_encomenda */
    int num_e = 0;
    while(estado){
        c = getchar();
        switch(c){
            case ('a'):
                num_produto = a(num_produto);
                break;
            case ('q'):
                q(num_produto);
                break;
            case ('N'):
                num_e = N(num_e);
                break;
            case('A'):
                A(num_produto,num_e);
                break;
            case ('r'):
                r(num_produto);
                break;
            case ('R'):
                R(num_e,num_produto);
                break;
            case ('C'):
                C(num_e,num_produto);
                break;
            case ('p'):
                p(num_produto);
                break;
            case ('E'):
                E(num_produto,num_e);
                break;
            case ('m'):
                m(num_produto,num_e);
                break;
            case ('l'):
                l(num_produto);
                break;
            case ('L'):
                L(num_e);
                break;
            case ('x'):
                estado = 0;
                break;
        };
    };
    return 0;
}
