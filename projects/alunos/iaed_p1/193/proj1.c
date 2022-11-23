#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define DIM_STOCK 10000
#define DIM_LSTENC 500
#define DIM_ENCOM 200
#define DIM_DESC 64

/* contadores de prod/enc */
int qntdd_prod, qntdd_enc;

/* leitor de comando */
char reader;

/* estrutura produto */

typedef struct produto {
    char desc[DIM_DESC];
    int id, preco, peso, qntdd;
} produto;

produto stock[DIM_STOCK];

/* estrutura encomenda */

typedef struct encomenda {
    int n_prod;
    produto produto[DIM_ENCOM];
} encomenda;

encomenda lst_enc[DIM_LSTENC];

/* funcoes aux prod */

int peso_produto(produto prod) {
    return prod.peso;
}
int preco_produto(produto prod) {
    return prod.preco;
}
int qntdd_produto(produto prod) {
    return prod.qntdd;
}
int id_produto(produto prod) {
    return prod.id;
}

int get_pos_produto (int idp) {
    int i;
    for (i=0; i < qntdd_prod; i++)
        if (id_produto(stock[i]) == idp)
            return i;
    return idp;
}

/* funcoes aux encomenda */

int nprod_encomenda(encomenda enc) {
    return enc.n_prod;
}
int peso_encomenda(encomenda enc) {
    int i;
    int res = 0;
    for (i=0; i < nprod_encomenda(enc); i++)  {
        res += ( peso_produto(enc.produto[i]) * qntdd_produto(enc.produto[i]));
    }
    return res;
}

/* funcoes sort */ 

int aux_int[DIM_STOCK];
/* merge de produtos */
void merge_int(int left, int m, int right) {
    int i, j, k;
    for (i = m+1; i > left; i--)
        aux_int[i-1] = preco_produto(stock[i-1]);
    for (j = m; j < right; j++)
        aux_int[right+m-j] = preco_produto(stock[j+1]);
    for (k = left; k <= right; k++)
        if (aux_int[j] < aux_int[i] || i > m)
            stock[k] = stock[j--];
        else
            stock[k] = stock[i++];
}

void mergesort_int(int left, int right) {
    int m = (right+left)/2;
    if (right <= left) 
        return;
    mergesort_int(left, m);
    mergesort_int(m+1, right);
    merge_int(left, m, right);
}


encomenda enc_aux;  
/* merge de produtos numa encomenda */
void merge_desc(int left, int m, int right,int ide) {
    int i, j, k;
    for (i = m+1; i > left; i--)
        enc_aux.produto[i-1] = lst_enc[ide].produto[i-1];
    for (j = m; j < right; j++)
        enc_aux.produto[right+m-j] = lst_enc[ide].produto[j+1];
    for (k = left; k <= right; k++) 
        if (strcmp(enc_aux.produto[j].desc, enc_aux.produto[i].desc) < 0 || i > m)
            lst_enc[ide].produto[k] = enc_aux.produto[j--];
        else
            lst_enc[ide].produto[k] = enc_aux.produto[i++];
}

void mergesort_desc(int left, int right,int ide) {
    int m = (right+left)/2;
    if (right <= left) 
        return;
    mergesort_desc( left, m,ide);
    mergesort_desc( m+1, right,ide);
    merge_desc( left, m, right,ide);
}


/* funcoes dos comandos */

void novo_produto () {
    /*  comando "a" */
    /* armazena os valores num prod de stock */
    int idp = qntdd_prod;
    reader = getchar(); /* retira o ' ' */
    scanf("%[^:]:%d:%d:%d",stock[idp].desc, &stock[idp].preco, &stock[idp].peso, &stock[idp].qntdd);
    stock[idp].id = idp;
    qntdd_prod++;
    printf("Novo produto %d.\n", idp);
}

void adicionar_produto_stock () {
    /* comando 'q' */
    /* soma a qntdd introduzida a quantidade ja existente no stock */
    int idp,qntdd,ind;

    scanf("%d:%d",&idp,&qntdd);
    ind = get_pos_produto(idp);
    
    if (idp >= qntdd_prod)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else
        stock[ind].qntdd += qntdd;
}

void nova_encomenda() {
    /* comando 'N' */
    /* inicializa/valida um nova encomenda */
    int ide = qntdd_enc;

    lst_enc[ide].n_prod = 0;
    qntdd_enc++;
    printf("Nova encomenda %d.\n", ide);
}

void adicionar_produto_encomenda () {
    /* comando 'A' */
    /* adiciona produto a uma encomenda ou qntdd se ja existir */
    int idp,ide,qntdd,i,ind;

    scanf("%d:%d:%d",&ide,&idp,&qntdd);
    ind = get_pos_produto(idp);
    /* verificar erros (4) */
    if (idp >= qntdd_prod)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    else if (ide >= qntdd_enc)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else if ( qntdd_produto(stock[ind]) < qntdd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
    else if ( (peso_encomenda(lst_enc[ide]) + (peso_produto(stock[ind]) * qntdd) ) > 200)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
    else {                                                             
        for (i=0; i < nprod_encomenda(lst_enc[ide]); i++) 
            /* produto ja exist na encomenda */              
            if (idp == id_produto(lst_enc[ide].produto[i])) {
                lst_enc[ide].produto[i].qntdd += qntdd;
                stock[ind].qntdd -= qntdd;
                return;
            }
        /* novo produto na encomenda */
        lst_enc[ide].produto[lst_enc[ide].n_prod] = stock[ind];
        lst_enc[ide].produto[lst_enc[ide].n_prod].qntdd = qntdd;
        stock[ind].qntdd -= qntdd;
        lst_enc[ide].n_prod++;
    }
}


void remover_produto_stock () {
    /* comando 'r' */
    /* remove qntdd de um produto em stock */
    int idp,qntdd,ind;

    scanf("%d:%d",&idp,&qntdd);
    ind = get_pos_produto(idp);
    /* verificar erros (2) */
    if (idp >= qntdd_prod)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
    else if (qntdd_produto(stock[ind]) < qntdd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qntdd, idp);
    else 
        stock[ind].qntdd -= qntdd;        
}

void remover_produto_encomenda () {
    /* comando 'R' */
    /* remove produto de uma encomenda */
    int idp,ide,ind,i;

    scanf("%d:%d",&ide,&idp);
    ind = get_pos_produto(idp);
    /* verificar erros (2) */
    if (ide >= qntdd_enc)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else if (idp >= qntdd_prod)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    else 
        for(i=0;i < nprod_encomenda(lst_enc[ide]); i++)
            if (idp == id_produto(lst_enc[ide].produto[i])) {
                /* coloca no stock e retira da encomenda */
                stock[ind].qntdd += lst_enc[ide].produto[i].qntdd; 
                lst_enc[ide].produto[i].qntdd = 0;
            }
}

void calcular_custo_encomenda () {
    /* comando 'C' */
    /* calcula o custo da encomenda */
    int ide,i,res = 0;

    scanf("%d",&ide);
    /* verificar erros (1) */
    if (ide >= qntdd_enc)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
    else {
        for(i=0;i < nprod_encomenda(lst_enc[ide]); i++)
            res += (qntdd_produto(lst_enc[ide].produto[i]) * preco_produto(lst_enc[ide].produto[i]));
        printf("Custo da encomenda %d %d.\n",ide ,res);
    }   
}

void alterar_preco_produto () {
    /* comando 'p' */
    /* altera preco de um produto */
    int idp,preco,i,j,ind;

    scanf("%d:%d",&idp,&preco);
    ind = get_pos_produto(idp);
    /* verificar erros (1) */
    if (idp >= qntdd_prod)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
    else {
        /* alteracao no stock */
        stock[ind].preco = preco;
        /* alteracao nas encomendas */
        for (i=0; i < qntdd_enc; i++)
            for (j=0; j < nprod_encomenda(lst_enc[i]); j++)
                if (idp == id_produto(lst_enc[i].produto[j]))
                    lst_enc[i].produto[j].preco = preco;
    }
}

void listar_desc_qntdd_produto () {
    /* comando 'E' */
    /* list descricao e qntdd de um produto numa encomenda*/
    int idp,ide,i,ind;

    scanf("%d:%d",&ide,&idp);
    ind = get_pos_produto(idp);
    /* verificar erros (2) */
    if (idp >= qntdd_prod)
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp); 
    else if (ide >= qntdd_enc)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    else {
        for(i=0;i < nprod_encomenda(lst_enc[ide]); i++) 
            if (idp == id_produto(lst_enc[ide].produto[i])) {
                printf("%s %d.\n",lst_enc[ide].produto[i].desc, qntdd_produto(lst_enc[ide].produto[i]));
                return;
            }
        printf("%s 0.\n",stock[ind].desc);
    }
}

void listar_max_produto () {
    /* comando 'm' */
    /* lista encomenda com maior qntdd do produto */
    int idp,ide,i,j,qntdd_max;

    scanf("%d",&idp);
    qntdd_max = 0;
    ide = 0;
    if (idp >= qntdd_prod)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
    else {
        for (i=0; i < qntdd_enc; i++)
            for (j=0; j < nprod_encomenda(lst_enc[i]); j++)
                if (idp == id_produto(lst_enc[i].produto[j]) &&
                    qntdd_produto(lst_enc[i].produto[j]) > qntdd_max) {
                        qntdd_max = qntdd_produto(lst_enc[i].produto[j]);
                        ide = i;
                    }
        if (qntdd_max)
            printf("Maximo produto %d %d %d.\n",idp,ide,qntdd_max);
    }
}

void listar_produtos_ord () {
    /* comando 'l' */
    /* lista produtos ordenados por preco */ 
    int i;
    
    mergesort_int(0,qntdd_prod-1);
    printf("Produtos\n");
    for(i=0; i<qntdd_prod; i++)
        printf("* %s %d %d\n", stock[i].desc, stock[i].preco, stock[i].qntdd);
}
  

void lista_encomenda_alf () {  
    /* comando 'L' */
    /* lista produtos de um encomendas ordenados por ordem alfabetica */
    int ide,i;

    scanf("%d",&ide);
    /* verificar erros (1) */
    if (ide >= qntdd_enc)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    else {
        mergesort_desc(0,nprod_encomenda(lst_enc[ide])-1,ide);
        printf("Encomenda %d\n", ide);
        for(i=0;i < nprod_encomenda(lst_enc[ide]); i++)
            if (lst_enc[ide].produto[i].qntdd > 0)
                 printf("* %s %d %d\n",lst_enc[ide].produto[i].desc,lst_enc[ide].produto[i].preco,lst_enc[ide].produto[i].qntdd);
    }
}

/* funcao main */

int main () {

    while (reader != EOF) {
        
        /* retira o char do comando */
        reader = getchar();
        /* chama a funcao correspondente */
        if(reader == 'a') {
            novo_produto();
        }
        else if(reader == 'q') {
            adicionar_produto_stock();
        }
        else if(reader == 'N') {
            nova_encomenda();
        }
        else if(reader == 'A') {
            adicionar_produto_encomenda();
        }
        else if(reader == 'r') {
            remover_produto_stock();
        }
        else if(reader == 'R') {
            remover_produto_encomenda();
        }
        else if(reader == 'C') {
            calcular_custo_encomenda();
        }
        else if(reader == 'p') {
            alterar_preco_produto();
        }
        else if(reader == 'E') {
            listar_desc_qntdd_produto();
        }
        else if(reader == 'm') {
            listar_max_produto();
        }
        else if(reader == 'l') {
            listar_produtos_ord();
        }
        else if(reader == 'L') {
            lista_encomenda_alf();
        }
    }
    return 0;
}