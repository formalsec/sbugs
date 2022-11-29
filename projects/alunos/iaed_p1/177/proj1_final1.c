#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Tamanho max da string descricao de um produto */
#define TAMANHODESC 64
/* Numero max de produtos por encomenda */
#define MAXPROD 10000
/* Numero max de encomendas */
#define MAXENC 500
/* Peso max de cada encomenda */
#define MAXPESO 200


/* Variaveis globais que indicam o primeiro id de produto/encomenda livre */
int id_atual_prod=0,id_atual_enc=0;


/* Definicao da estrutura produto */
typedef struct produto{
    /* identificador do produto */
    int id;
    /* descricao do produto */
    char desc[TAMANHODESC];
    /* preco do produto */
    int preco;
    /* peso de cada unidade do produto */
    int peso;
    /* quantidade disponivel em stock do produto */  
    int stock; 
} Produto;

/* Definicao da estrutura encomenda */
typedef struct encomenda{
    /* vetor com as quantidades pedidas para cada produto */
    int quantidades[MAXPROD];
    /* Peso total da encomenda */
    int peso;

} Encomenda;


/* Array que contem todos os produtos criados */
Produto produtos[MAXPROD];
/* Array que contem todas as encomendas criadas */
Encomenda encomendas[MAXENC];


/* Retorna 1 se a encomenda ja existir, retorna 0 caso contrario */
int verifEncomenda(int ide){
    if (ide >= id_atual_enc)
        return 0;
    return 1;
}

/* Retorna 1 se o produto ja existir, retorna 0 caso contrario */
int verifProduto(int idp){
    if (idp >= id_atual_prod)
        return 0;
    return 1;
}

/* Retorna 0 se o produto nao estiver na encomenda. Retorna 1 se estiver. */
int contido(Produto produto, Encomenda enc){
    if (enc.quantidades[produto.id] > 0)
        return 1;
    return 0;
}

/* Retorna 1 (true) se p1 for "menor" que p2. Retorna 0 (false) caso contrario */
int less(Produto p1, Produto p2, char modo){
    
    if (modo == 's'){    /* Ordenar descricoes alfabeticamente */
        if (strcmp(p1.desc,p2.desc) < 0)
            return 1;
        else
            return 0;
        
    }

    else{    /* Ordenar por preco (crescente) */
        if (p1.preco < p2.preco)
            return 1;
        else{
            if (p1.preco == p2.preco)
                return (p1.id < p2.id);
            else
                return 0;
        }
    }
}

/* Funcao que complementa o MergeSort (une vetores ordenados) */
void merge(Produto produtos[],int left,int m,int right,char modo){
    Produto aux[MAXPROD];
    int i,j,k;

    for (i=m+1; i>left; i--)
        aux[i-1] = produtos[i-1];
    for (j=m; j<right; j++)
        aux[right+m-j] = produtos[j+1];
    for (k=left; k<=right; k++){
        if (less(aux[j],aux[i],modo) || i > m)
            produtos[k] = aux[j--];
        else
            produtos[k] = aux[i++];
    }
}

/* Algoritmo recursivo Merge Sort para ordenar um vetor de produtos. modo='s' indica
ordenacao de descricoes de produtos, enquanto modo='p' indica ordenacao de produtos
pelos seus precos */
void mergeSort(Produto produtos[],int left,int right,char modo){
    int m = (right+left)/2;
    if (left < right){
        mergeSort(produtos,left,m,modo);
        mergeSort(produtos,m+1,right,modo);
        merge(produtos,left,m,right,modo);
    }
}


/* Adiciona novo produto ao sistema */
void func_a(){
    /* Produto com dados fornecidos pelo user */
    Produto a;
    a=produtos[id_atual_prod];
    scanf(" %[^:]:%d:%d:%d", a.desc, &a.preco, &a.peso, &a.stock);
    printf("Novo produto %d.\n",id_atual_prod);
    a.id = id_atual_prod;
    /* Atualizar vetor de produtos */
    produtos[id_atual_prod]=a;
    ++id_atual_prod;
}

/* Adiciona stock a um produto existente no sistema */
void func_q(){
    /* Input do user */
    int id,qtd;
    scanf(" %d:%d",&id,&qtd);
    if (id >= id_atual_prod)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);
    else
        produtos[id].stock += qtd;
}

/* Cria uma nova encomenda no sistema */
void func_N(){
    int contador=0;
    printf("Nova encomenda %d.\n",id_atual_enc);
    /* Inicializacao da nova encomenda */
    encomendas[id_atual_enc].peso = 0;
    while (contador<=MAXPROD){
        encomendas[id_atual_enc].quantidades[contador]=0;
        ++contador;
    }
    ++id_atual_enc;
}

/* Adiciona um produto a uma encomenda */
void func_A(){
    /* Input do user */
    int ide,idp,qtdpedida;
    /* Peso da encomenda apos acrescentar o produto pedido */
    int novopeso;
    /* Encomenda a qual vamos adicionar o produto */
    Encomenda e;
    /* Produto que vamos adicionar */
    Produto p;
    scanf(" %d:%d:%d",&ide,&idp,&qtdpedida);
    
    if (!(verifEncomenda(ide)))
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else{   /* Encomenda existe */
        e = encomendas[ide];
        if (!(verifProduto(idp)))
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
        else{   /* Produto existe */
            p = produtos[idp];
            if (qtdpedida > p.stock)
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
            else{   /* Stock suficiente */
                novopeso = e.peso + (p.peso * qtdpedida);
                if (novopeso > MAXPESO)
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n",idp,ide,MAXPESO);
                else{   /* Nao excede limite peso */
                    e.peso = novopeso;
                    e.quantidades[idp] += qtdpedida;
                    p.stock -= qtdpedida;
                    /* Atualizar vetores de encomendas e produtos */
                    encomendas[ide] = e;
                    produtos[idp] = p;
                }
            }
        }
    }
}

/* Remove stock a um produto existente */
void func_r(){
    /* Input do user */
    int idp,qtd;
    scanf(" %d:%d",&idp,&qtd);

    if(idp >= id_atual_prod)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
    else{   /* Produto existe */
        if (produtos[idp].stock < qtd)
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
        else{       /* Stock n fica negativo apos remocao */
            produtos[idp].stock -= qtd;
        }
    }
}

/* Remove um produto de uma encomenda */
void func_R(){
    int ide,idp;
    Encomenda e;
    Produto p;
    scanf(" %d:%d",&ide,&idp);

    if (!(verifEncomenda(ide)))
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else{   /* Encomenda existe */
        e=encomendas[ide];
        if (!(verifProduto(idp)))
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
        else{   /* Produto existe */
            p=produtos[idp];
            e.peso -= p.peso * (e.quantidades[idp]);    /* Remover peso total do produto ao peso da encomenda */
            p.stock += e.quantidades[idp];  /* Devolver a quantidade removida ao stock */
            e.quantidades[idp] = 0;    /* Remover o produto da encomenda */
            /* Atualizar vetores de encomendas e produtos */
            encomendas[ide] = e;
            produtos[idp] = p;
        }
    }
}

/* Calcula custo de uma encomenda */
void func_C(){
    int ide,total=0,contador=id_atual_prod;
    Encomenda e;
    Produto p;
    scanf(" %d",&ide);
    if (!(verifEncomenda(ide)))
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
    else{   /* Encomenda existe */
        e = encomendas[ide];
        while (--contador >= 0){
            p = produtos[contador];
            total += p.preco * e.quantidades[contador];
        }
        printf("Custo da encomenda %d %d.\n",ide,total);
    }
}

/* Altera o preco de um produto existente no sistema */
void func_p(){
    int idp,novopreco;
    scanf(" %d:%d",&idp,&novopreco);
    if (!(verifProduto(idp)))
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
    else
        produtos[idp].preco = novopreco;
}

/* Lista a descricao e a quantidade de um produto numa encomenda */
void func_E(){
    int ide,idp;
    scanf(" %d:%d",&ide,&idp);
    if (!(verifEncomenda(ide)))
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    else{
        if (!(verifProduto(idp)))
            printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
        else{
            printf("%s %d.\n",produtos[idp].desc, encomendas[ide].quantidades[idp]);
        }
    }
}

/* Indica o id da encomenda em que o produto indicado pelo user aparece em maior quantidade */
void func_m(){
    int idp,contador = 0,ide_mais_ocorrencias = 0;
    scanf(" %d",&idp);

    if (!(verifProduto(idp)))
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
    else{   /* Produto existe */
        while (++contador<id_atual_enc)
            if (encomendas[contador].quantidades[idp] > encomendas[ide_mais_ocorrencias].quantidades[idp])
                ide_mais_ocorrencias = contador;           
        if ((encomendas[ide_mais_ocorrencias].quantidades[idp] > 0) && (id_atual_enc > 0))
            printf("Maximo produto %d %d %d.\n",idp,ide_mais_ocorrencias,encomendas[ide_mais_ocorrencias].quantidades[idp]);
    }
}

/* Lista produtos existentes no sistema por ordem crescente de preco */
void func_l(){
    /* Vetor auxiliar, para nao destruir vetor global */
    Produto a[MAXPROD];
    int contador = -1;

    while (++contador < id_atual_prod)  /* Copia para vetor auxiliar */
        a[contador] = produtos[contador];
    mergeSort(a,0,id_atual_prod-1,'p');
    printf("Produtos\n");
    contador = -1;
    while (++contador < id_atual_prod)  /* Escrita no ecra */
        printf("* %s %d %d\n", a[contador].desc, a[contador].preco, a[contador].stock);

}

/* Lista todos os produtos de uma encomenda por ordem alfabetica de descricao */
void func_L(){
    /* Vetor auxiliar, para nao destruir vetor global */
    Produto a[MAXPROD];
    int contador_a = 0,contador_e = -1,ide,indicefinal;
    scanf(" %d",&ide);

    if (!(verifEncomenda(ide)))
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    else{   /* Encomenda existe */
        while (++contador_e < id_atual_prod) /* Copia para auxiliar */
            if (encomendas[ide].quantidades[contador_e] > 0){ /* Produto existe na encomenda */
                a[contador_a] = produtos[contador_e];
                ++contador_a;
            }
        indicefinal = contador_a;
        mergeSort(a,0,indicefinal,'s');    /* Ordenar vetor auxiliar */
        contador_a = -1;
        printf("Encomenda %d\n",ide);
        while (++contador_a < indicefinal) /* Escrita no ecra */
            printf("* %s %d %d\n", a[contador_a].desc, a[contador_a].preco, encomendas[ide].quantidades[a[contador_a].id]);
    }
}


/* Programa principal */
int main(){
    /* Caracter para a leitura das funcoes */
    char c;

    /* analise do input inicial */
    while ((c=getchar()) != 'x')
        switch(c){
            case 'a':
                func_a();
                break;
            case 'q':
                func_q();
                break;
            case 'N':
                func_N();
                break;
            case 'A':
                func_A();
                break;
            case 'r':
                func_r();
                break;
            case 'R':
                func_R();
                break;
            case 'C':
                func_C();
                break;
            case 'p':
                func_p();
                break;
            case 'E':
                func_E();
                break;
            case 'm':
                func_m();
                break;
            case 'l':
                func_l();
                break;
            case 'L':
                func_L();
            default:
                break;
        }
    return 0;
}
