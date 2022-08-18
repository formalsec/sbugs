#include <stdio.h>
#include <string.h>
/* define o numero maximo de caracteres da descricao de um produto        */
/*      (incluindo o caracter de fim de cadeia de caracteres)             */
#define NOME 64
/*      define o numero maximo de produtos possiveis (idp) [0,9999]       */
#define PRODUTOS 10000
/*     define o numero maximo de encomendas possiveis (ide)  [0,499]      */
#define ENCOMENDAS 500
/* define a quantidade maxima de produtos que uma encomenda pode ter      */
#define PESO 200
/* TRUE e FALSE usados em funcoes auxiliares, a fim de nao repetir codigo */
#define TRUE 1
#define FALSE 0


/* declaracao do tipo produto   */
typedef struct {
    int id,peso,preco,quant;
    char nome[NOME];
} produto;

/* declaracao do tipo encomenda */
typedef struct {
    /* quantidade (quant) sera a quantidade de produtos diferentes da encomenda
    enquanto que o peso eh a soma do peso de cada produto da encomenda */
    int peso,quant;
    produto produto[PESO];
} encomenda;


/*-------------------VARIAVEIS GLOBAIS--------------------*/

/* variavel produtos sera o iventario/stock de todos os produtos existentes */
produto produtos[PRODUTOS];

/* variavel encomendas sera o iventario de todas as encomendas existentes   */
encomenda encomendas[ENCOMENDAS];

/* variaveis de contagem dos produtos e encomendas existentes. como ambas incrementam a cada novo
produto e encomenda, o numero atual de cada um sera (cont_idp - 1) e (cont_ide - 1), respetivamente.*/
int cont_idp,cont_ide;


/*-------------------FUNCOES AUXILIARES--------------------*/

/* uso do algoritmo de ordenacao merge sort para a funcao 'l' */
void merge(int copia_idp[], int esq, int meio, int dir);
void mergeSort(int copia_idp[], int esq, int dir);

/* funcao auxiliar que avalia se um produto ja existe em stock */
int existe_prod(int idp)
{
    if (idp >= cont_idp) {
        return FALSE;
    }
    return TRUE;
}

/* funcao auxiliar que avalia se uma encomenda ja existe */
int existe_encomenda(int ide)
{
    if (ide >= cont_ide) { 
        return FALSE;
    }
    return TRUE;
}

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

int main() 
{
    int c;
    while ((c = getchar()) != EOF) 
    {
        switch(c) {
            case 'a':
                a();
                break;
            case 'q':
                q();
                break;
            case 'N':
                N();
                break;
            case 'A':
                A();
                break;
            case 'r':
                r();
                break;
            case 'R':
                R();
                break;
            case 'C':
                C();
                break;
            case 'p':
                p();
                break;
            case 'E':
                E();
                break;
            case 'm':
                m();
                break;
            case 'l':
                l();
                break;
            case 'L':
                L();
                break;
            case 'x':
                break;
        }
    }
    return 0;
}

/*funcao que recebe todos os atributos do tipo produto e adiciona esse produto ao stock*/
void a()
{
    scanf(" %[^:]:%d:%d:%d",produtos[cont_idp].nome,&produtos[cont_idp].preco,&produtos[cont_idp].peso,&produtos[cont_idp].quant);
    printf("Novo produto %d.\n",cont_idp);
    cont_idp++;
}

/*funcao que recebe um identificador de produto (idp) e uma quantidade (quant) e adiciona essa quantidade
 do produto idp ao stock*/
void q()
{
    int idp,quant;
    scanf("%d:%d",&idp,&quant);

    /* necessario que o produto com id 'idp' exista */
    if (existe_prod(idp) == FALSE) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
        return;
    }

    produtos[idp].quant += quant;
}

/*funcao que recebe um identificador de encomenda (ide) e cria uma nova encomenda vazia */
void N()
{
    printf("Nova encomenda %d.\n",cont_ide);
    cont_ide++;
}

/*funcao que recebe um ide, idp e quantidade adicionando ah encomenda 'ide' o produto 'idp' com a quantidade 'quant'*/
void A()
{
    int idp,ide,quant,i;
    scanf("%d:%d:%d",&ide,&idp,&quant);

    /*necessario que a encomenda 'ide' exista*/
    if (existe_encomenda(ide) == FALSE) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
        return;
    }

    /* necessario que o produto com id 'idp' exista */
    if (existe_prod(idp) == FALSE) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
        return;
    }

    /*necessario que a quantidade em stock seja suficiente para remover a quantidade 'quant'*/
    if (quant > produtos[idp].quant) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
        return;
    }

    /*necessario que nao haja mais que 200 unidades de produtos na encomenda 'ide'*/
    if ((encomendas[ide].peso + (produtos[idp].peso*quant)) > PESO) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
        return;
    }

    /* 2 casos possiveis: o produto ja existir na encomenda ou nao*/

    for (i = 0; i < encomendas[ide].quant; i++) {
        /*se a encomenda ja tiver o produto idp */
        if (encomendas[ide].produto[i].id == idp) {
            encomendas[ide].peso += (produtos[idp].peso*quant);
            encomendas[ide].produto[i].quant += quant;
            produtos[idp].quant -= quant;
            return;
        }      
    }
    /* caso contrario*/
    encomendas[ide].produto[encomendas[ide].quant].id = idp;
    encomendas[ide].produto[encomendas[ide].quant].quant = quant;
    produtos[idp].quant -= quant;
    encomendas[ide].peso += (produtos[idp].peso*quant);
    /*quantidade de produtos diferentes na encomenda incrementa*/
    encomendas[ide].quant++;
}

/*funcao que recebe um idp e uma quantidade e remove do stock a quantidade 'quant' do produto 'idp'*/
void r()
{
    int idp,quant;
    scanf("%d:%d",&idp,&quant);

    /* necessario que o produto com id 'idp' exista */
    if (existe_prod(idp) == FALSE) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
        return;
    }
    
    /*necessario que a quantidade que se pretende remover nao seja maior que a existente do produto idp*/
    if (produtos[idp].quant < quant) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",quant,idp);
        return;
    }

    /*sendo possivel remover o produto, quantidade de stock sera alterada */
    produtos[idp].quant -= quant;
}

/*funcao que recebe um ide e um idp e remove a totalidade do produto 'idp' da encomenda 'ide' */
void R()
{
    int j,i,ide,idp,remove,atualiza = 0;
    scanf("%d:%d",&ide,&idp);

    /*necessario que a encomenda 'ide' exista*/
    if (existe_encomenda(ide) == FALSE) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
        return;
    }

    /* necessario que o produto com id 'idp' exista */
    if (existe_prod(idp) == FALSE) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
        return;
    }

    /*ao remover a totalidade, o produto deixa de existir na encomenda pelo que eh preciso 
    atualizar: as posicoes no tipo encomenda; o peso e quantidade de produtos da mesma; 
    a quantidade de produtos do stock. */
    for (i = 0; i < encomendas[ide].quant;i++) {
        if (encomendas[ide].produto[i].id == idp) {
            atualiza = 1;
            remove = encomendas[ide].produto[i].quant;
            /*os produtos das posicoes posteriores ao idp no array dos produtos de uma encomenda 
            recuam uma posicao*/
            for (j = i; j < encomendas[ide].quant - 1; j++) {
                encomendas[ide].produto[j] = encomendas[ide].produto[j+1];
            }
        }
    }
    if (atualiza == 1) {
        produtos[idp].quant += remove;
        encomendas[ide].peso -= (remove*produtos[idp].peso);
        encomendas[ide].quant -= 1;
    }
}

/*funcao que recebe um ide e calcula o custo da encomenda 'ide'*/
void C()
{
    int ide,id,i,custo = 0;
    scanf("%d",&ide);

    /*necessario que a encomenda 'ide' exista*/
    if (existe_encomenda(ide) == FALSE) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }

    for (i = 0; i < encomendas[ide].quant;i++) {
        id = encomendas[ide].produto[i].id;
        custo += encomendas[ide].produto[i].quant*produtos[id].preco;
    }

    printf("Custo da encomenda %d %d.\n",ide,custo);
}

/*funcao que recebe um idp e um preco e altera o preco registado do idp pelo preco recebido*/
void p()
{
    int preco,idp;
    scanf("%d:%d",&idp,&preco);

    /* necessario que o produto com id 'idp' exista */
    if (existe_prod(idp) == FALSE) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
        return;
    }

    produtos[idp].preco = preco;
}

/*funcao que recebe um ide e idp e retorna a descricao de idp e a quantidade do produto 
idp na encomenda ide */
void E()
{
    /*variavel 'existe' tem como objetivo identificar o caso em que o produto nao se encontra na encomenda*/
    int ide,idp,i,existe = 0;
    scanf("%d:%d",&ide,&idp);

    /*necessario que a encomenda 'ide' exista*/
    if (existe_encomenda(ide) == FALSE) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }

    /* necessario que o produto com id 'idp' exista */
    if (existe_prod(idp) == FALSE) {
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
        return;
    }

    /*percorre todos os produtos da encomenda e compara os seus id's com o idp recebido*/
    for (i = 0; i < encomendas[ide].quant; i++) {
        if (encomendas[ide].produto[i].id == idp) {
            printf("%s %d.\n", produtos[idp].nome,encomendas[ide].produto[i].quant);
            existe = 1;
        }
    }

    /*se nao existir nenhum produto idp na encomenda ide entao a funcao retorna apenas
    a descricao de idp*/
    if (existe == 0) {
        printf("%s 0.\n",produtos[idp].nome);
    }
}

/*funcao que recebe um idp e devolve o ide da encomenda em que idp ha em maior quantidade*/ 
void m()
{
    int i,j,idp,max_ide=0,max_quant=0;
    scanf("%d",&idp);

    /* necessario que o produto com id 'idp' exista */
    if (existe_prod(idp) == FALSE) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
        return;
    }

    for (i = 0; i < cont_ide; i++) {
        for (j = 0; j < encomendas[i].quant; j++) {
            /*se o produto se encontrar na encomenda i*/
            if (encomendas[i].produto[j].id == idp) {
                /*se a quantidade desse produto na encomenda i for maior que a anteriormente
                guardada (max_quant) ,ou zero no caso de ser a primeira encomenda que contenha o produto idp,
                entao max_quant passa a ser essa mesma quantidade e guardamos o ide da encomenda em max_ide*/
                if (encomendas[i].produto[j].quant > max_quant) {
                    max_quant = encomendas[i].produto[j].quant;
                    max_ide = i;
                }
                /* se houver duas encomendas com a mesma quantidade compara-se os seus ide e 
                o que for maior eh aquele que sera devolvido*/
                if (encomendas[i].produto[j].quant == max_quant) {
                    if (i < max_ide) {
                        max_ide = i;
                    }
                }
            }
        }
    }

    /*nao devolve nada se nao houver quantidade do produto idp em nenhuma encomenda*/
    if (max_quant > 0) {
        printf("Maximo produto %d %d %d.\n",idp,max_ide,max_quant);
    }

}

/*funcao que lista por ordem de preco todos os produtos existentes em stock*/
void l()
{
    int i,copia_idp[PRODUTOS];

    /*copia_idp sera um array contendo todos os ids de produtos criados */
    for (i = 0; i < cont_idp; i++) {
        copia_idp[i] = i;
    }

    /*implementacao do algoritmo mergesort*/
    mergeSort(copia_idp,0,cont_idp - 1);

    printf("Produtos\n");
    for (i=0; i < cont_idp;i++) {
        printf("* %s %d %d\n",produtos[copia_idp[i]].nome,produtos[copia_idp[i]].preco,produtos[copia_idp[i]].quant);
    }
}

/*funcao que recebe um ide de encomenda e lista todos os produtos nesta de ordem alfabetica*/
void L()
{
    int ide,i,j,idp_j=0,idp_i=0;
    produto aux;
    
    scanf("%d",&ide);

    /*necessario que a encomenda 'ide' exista*/
    if (existe_encomenda(ide) == FALSE) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }

    for (i = 0; i < encomendas[ide].quant; i++) {
        for (j = i + 1; j < encomendas[ide].quant; j++){
            /*idp_j e idp_i guardam os identificadores de cada produto e do seguinte*/
            idp_i = encomendas[ide].produto[i].id;
            idp_j =  encomendas[ide].produto[j].id;
            /* nesta condicao procedemos a uma troca*/
            if(strcmp(produtos[idp_i].nome,produtos[idp_j].nome) > 0 ) {
                /*o produto original na posicao i da encomenda ide sera guardado no produto 'aux' 
                para que o produto j fique com as informacoes relativas ao i original, sendo que 
                eh o ultimo a sofrer a troca*/
                aux = encomendas[ide].produto[i];
                encomendas[ide].produto[i].id = encomendas[ide].produto[j].id;
                encomendas[ide].produto[i].quant = encomendas[ide].produto[j].quant;
                encomendas[ide].produto[j] = aux;
            }
        }
    }
    printf("Encomenda %d\n",ide);

    /*percorre todos os produtos na encomenda, guarda o seu (potencialmente novo) id e prossegue ah listagem de cada 
    produto, sendo que idp_i correspondera a cada id por ordem alfabetica dos nomes assicoados a estes*/
    for (i = 0; i < encomendas[ide].quant; i++) {
        idp_i = encomendas[ide].produto[i].id;
        printf("* %s %d %d\n",produtos[idp_i].nome,produtos[idp_i].preco,encomendas[ide].produto[i].quant);
    }
}

void merge(int copia_idp[], int esq, int meio, int dir) 
{ 
    int i, j, k; 
    int n1 = meio - esq + 1; 
    int n2 =  dir - meio; 
  
    /* criacao de arrays temporarios*/
    int ESQ[PRODUTOS], DIR[PRODUTOS]; 
  
    /*guarda 'metade' dos elementos de copia_idp para o array
    temporario ESQ (representa os elementos ah esquerda)*/
    for (i = 0; i < n1; i++) {
        ESQ[i] = copia_idp[esq + i];   
    }

    /*mesmo procedimento para os elementos do lado direito*/
    for (j = 0; j < n2; j++) {
        DIR[j] = copia_idp[meio + 1+ j]; 
    }
    i = 0;
    j = 0;
    k = esq;
    /*ciclo que percorre cada elemento do lado direito e esquerdo comparando-os 
    e ordenando copia_idp tendo em conta os precos associados a cada elemento*/
    while (i < n1 && j < n2) { 
        if (produtos[ESQ[i]].preco <= produtos[DIR[j]].preco) { 
            copia_idp[k] = ESQ[i]; 
            i++; 
        } 
        else { 
            copia_idp[k] = DIR[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) { 
        copia_idp[k] = ESQ[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) { 
        copia_idp[k] = DIR[j]; 
        j++; 
        k++; 
    } 
} 
  
/*mergesort recebe um array e a dimensao dos elementos da esquerda e da direita*/
/*funciona recursivamente ate obter vetores de um so elemento*/
void mergeSort(int copia_idp[], int esq, int dir) 
{ 
    if (esq < dir) { 
        int meio = esq + (dir - esq)/2; 
        mergeSort(copia_idp, esq, meio); 
        mergeSort(copia_idp, meio+1, dir); 
  
        merge(copia_idp, esq, meio, dir); 
    } 
} 




