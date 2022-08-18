#include <stdio.h>
#include <string.h>
#define MAX_LENGHT_DESC 63
#define MAX_PROD_SYSTEM 10000
#define MAX_PROD_ORDER 200  /* max prod = max peso na encomenda */
#define MAX_ORDERS 500
#define MAX_PESO_IN_ENC 200
typedef struct product{
    char desc[MAX_LENGHT_DESC + 1];
    int idp, preco, peso, qtd;
}product;
#define exch(X, Y) { product t = X; X = Y; Y = t; }

/* |Inicializacao de variaveis globais| */
product sistema[MAX_PROD_SYSTEM],   /* sistema */ 
encomendas[MAX_ORDERS][MAX_PROD_ORDER],   /* conjunto de encomendas */ 
aux[MAX_PROD_SYSTEM];   /* caixa auxiliar */
int ids[2];   /*ids atuais[id_sistema, id_encomendas]*/

/* |Funcoes-auxiliares|*/
int min(int a, int b){return a <= b? a : b;}
int partition(product caixa[], int l, int r){
    int i = l-1, j = r;
    product p = caixa[r];
    while (i < j){
        while (caixa[++i].preco < p.preco || (caixa[i].preco == p.preco && caixa[i].idp < p.idp));
        while (p.preco < caixa[--j].preco || (p.preco == caixa[j].preco && caixa[j].idp > p.idp));
        if (j == l) break;
        if (i < j) exch(caixa[i], caixa[j]);
    }exch(caixa[i], caixa[r]);
    return i;
}
void quicksort(product caixa[], int l, int r){
    int i;
    if (r <= l) return;
    i = partition(caixa, l, r);
    quicksort(caixa, l, i-1);
    quicksort(caixa, i+1, r);
}
/* |Funcoes-utilizadas| */
/*  (int)tamanho_encomenda: 
    Devolve o numero de produtos existentes no conjunto;
    input: product[];   output: int. */
int tamanho_encomenda(product encomenda[]){
    int i;
    for (i = 0; i < MAX_PROD_ORDER; i++)
        if (encomenda[i].qtd == 0) break;  /* achou um espaco livre sai */ 
    return i;
}
/*  (int)total_status_enc: 
    Para um dado argumento (preco ou peso) devolve o valor total no conjunto;
    input: (char, product[]);  output: int. */
int total_status_enc(char arg[], product caixa[]){
    int i, total = 0, tam = tamanho_encomenda(caixa);   /* procura o arg dos produtos */
    for (i = 0; i < tam; i++){ 
        if (!strcmp(arg, "preco")) total += (caixa[i].preco * caixa[i].qtd);
        if (!strcmp(arg, "peso")) total += (caixa[i].peso * caixa[i].qtd);
    }return total;
}
/*  (int(?))produto_na_caixa: 
    Procura o produto pelo seu identificador. Caso o mesmo for encontrado
    devolve o seu id na encomenda, e no outro caso INVALID;
    input: (int, product[]);  output: int(?). */
int produto_na_caixa(int idp, product caixa[]){
    int i, prod_in = 0, tam = tamanho_encomenda(caixa);
    for (i = 0; i < tam; i++){
        if (caixa[i].idp == idp){   /*caso afirmativo produto encontrado */
            prod_in = 1;
            break;
        }
    }if (prod_in) return i; /* id na encomenda */
    return -1; /* nao encontrado */
}
/*  ()adiciona_produto_enc: 
    Adiciona a quantidade de produto e as suas outras caracteristicas a
    uma encomenda; 
    input: (int, product, product[]);  output: {}. */
void adiciona_produto_enc(int qtd, product produto, product encomenda[]){
    int i = produto_na_caixa(produto.idp, encomenda);
    if (i >= 0) /* o produto esta na caixa? */
        encomenda[i].qtd += qtd; /* se sim aumenta apenas a sua qtd */
    else{
        i = tamanho_encomenda(encomenda); /*id na encomenda do novo produto*/
        encomenda[i].idp = produto.idp; /*copia caracteristicas do mesmo*/
        strcpy(encomenda[i].desc, produto.desc);
        encomenda[i].preco = produto.preco;
        encomenda[i].peso = produto.peso;
        encomenda[i].qtd = qtd;
    }
}
/*  ()remove_produto_enc: 
    Remove um produto na encomenda dando espaco a outros no futuro;
    input: (int, product[]);  output: {}. */
void remove_produto_enc(int id, product encomenda[]){
    int i = produto_na_caixa(id, encomenda), /* id do produto na encomenda */
    tam_enc = tamanho_encomenda(encomenda); /* elementos da encomenda */
    if (i >= 0){
        sistema[id].qtd += encomenda[i].qtd;
        for ( ; i + 1 < tam_enc; i++){  /* a partir do id do produto temos */
            encomenda[i] = encomenda[i + 1]; /* shift left dos produtos */ 
        }encomenda[i].qtd = 0; /* o ultimo elemento da lugar a outro do futuro */
    }
}
/*  ()atualiza_encomendas: 
    Atualiza caracteristica do produto nas encomendas caso houve um apdate 
    no sistema;
    input: (int, product, product[][]);  output: {}. */
void atualiza_encomendas(int n_enc, product prod, product enc[MAX_ORDERS][MAX_PROD_ORDER]){
    int i, at;
    for (i = 0; i <= n_enc; i++){
        at = produto_na_caixa(prod.idp, enc[i]);  /* procura produto na encomenda i */
        if (at >= 0)  /* se encontrado */
            enc[i][at].preco = prod.preco;  /* atualiza */ 
    }
}
/*  (int(?))id_maxqtd_enc: 
    Devolve a encomenda que tem o produto dado em maior quantidade de todas em
    encomendas criadas (dado por ide). Caso nao for possivel devolve INVALID;
    input: (int, product, product[][]);  output: int(?). */
int id_maxqtd_enc(int ide, product produto, product encomendas[MAX_ORDERS][MAX_PROD_ORDER]){
    int i, j, tam_enc, max = 0, enc_max, prod_in = 0;
    for (i = 0; i <= ide; i++){
        tam_enc = tamanho_encomenda(encomendas[i]); /* numero de produtos da encomenda i */
        for (j = 0; j < tam_enc; j++){
            if (encomendas[i][j].idp == produto.idp){
                if (encomendas[i][j].qtd > max){ /* atualiza encomenda max */
                    max = encomendas[i][j].qtd;
                    enc_max = i;
                }prod_in = 1; /* encontrou um produto */
                break;
            }
        }
    }if (prod_in) return enc_max;
    return -1; /* nao existe nenhum produto nas encomendas */
}
/*  (int(?))descr_ordenada: 
    Avalia se a descricao 1 e a descricao 2 estao ja ordenadas alfabeticamente;
    input: (product, product);  output: int(?). */
int descr_ordenada(product p1, product p2){
    int i, tam = min(strlen(p1.desc), strlen(p2.desc));
    for (i = 0; i < tam; i++){  /* compara todas os carateres */
        if (p1.desc[i] < p2.desc[i])
            return 1;
        if (p2.desc[i] < p1.desc[i])
            return 0;
    }return 0;  /* se forem iguais*/
}
/*  ()ordena_desc: 
    Ordena os produtos da encomenda pela sua descricao, alfabeticamente;
    input: (int, product[]);  output: {}. */
void ordena_desc(int n_prod, product armazem[]){
    int i, j, done;    /* bubbleshort */
    for (i = 0; i < n_prod - 1; i++){
        done = 1;
        for (j = n_prod - 1; j > i; j--)
            if (descr_ordenada(armazem[j], armazem[j-1])){
                exch(armazem[j], armazem[j-1]);    /* troca produtos de lugar */
                done = 0;
            }
        if (done) break;   /* se o vetor ja esta ordenado sai */
    }
}
/* |Funcoes-comando| */
/*  Adiciona produto ao sistema */
void a(){
    ids[0]++;   /*identifica o produto no sistema*/
    scanf(" %[^:]:%d:%d:%d", sistema[ids[0]].desc, &sistema[ids[0]].preco,
    &sistema[ids[0]].peso, &sistema[ids[0]].qtd); sistema[ids[0]].idp = ids[0];
    printf("Novo produto %d.\n", ids[0]);
}
/*  Adiciona stock de um produto no sistema */
void q(){
    int pr_in, qtd_in;
    scanf("%d:%d", &pr_in, &qtd_in);
    if (pr_in > ids[0])    /* verifica produto no sistema */
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",pr_in);
    else    /* adiciona stock */
        sistema[pr_in].qtd += qtd_in;
}
/*  Gera nova encomenda */
void N(){
    ids[1]++;   /*identifica a encomenda*/
    printf("Nova encomenda %d.\n", ids[1]);
}
/*  Adiciona produto a uma encomenda */
void A(){
    int enc_in, pr_in, qtd_in;
    scanf("%d:%d:%d", &enc_in, &pr_in, &qtd_in);
    if (enc_in > ids[1])    /* verifica encomenda */
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",
        pr_in, enc_in);
    else if (pr_in > ids[0])    /* verifica produto */
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",
        pr_in, enc_in);
    else if (sistema[pr_in].qtd < qtd_in)   /* verifica qtd suficiente no sistema */
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",
        pr_in, enc_in);
    else if (total_status_enc("peso", encomendas[enc_in]) + (qtd_in * sistema[pr_in].peso) > MAX_PESO_IN_ENC) 
        /* verifica espaco suficiente na encomenda */
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", 
        pr_in, enc_in);
    else{   /* adiciona produto a encomenda */
        adiciona_produto_enc(qtd_in, sistema[pr_in], encomendas[enc_in]);
        sistema[pr_in].qtd -= qtd_in;   /* retira esta qtd ao sistema */
    }
}
/*  Remove stock de um produto do sistema */
void r(){
    int pr_in, qtd_in;
    scanf("%d:%d", &pr_in, &qtd_in);
    if (pr_in > ids[0])    /* verifica produto */
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",
        pr_in);
    else if (sistema[pr_in].qtd < qtd_in)   /* verifica qtd suficiente no sistema */
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",
        qtd_in, pr_in);
    else
        sistema[pr_in].qtd -= qtd_in;   /* retira esta qtd ao sistema */
}
/*  Remove um produto de uma encomenda */
void R(){
    int enc_in, pr_in;
    scanf("%d:%d", &enc_in, &pr_in);
    if (enc_in > ids[1])    /* verifica encomenda */
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",
        pr_in, enc_in);
    else if (pr_in > ids[0])    /* verifica produto */
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",
        pr_in, enc_in);
    else    /* remove produto da encomenda */
        remove_produto_enc(pr_in, encomendas[enc_in]);
}
/*  Calcula o custo de uma encomenda */
void C(){
    int enc_in;
    scanf("%d", &enc_in);
    if (enc_in > ids[1])    /* verifica encomenda */
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", enc_in);
    else    /* calcula o custo desta */
        printf("Custo da encomenda %d %d.\n",enc_in, total_status_enc("preco", encomendas[enc_in]));
}
/*  Modifica o preco de um produto */
void p(){
    int pr_in, p;
    scanf("%d:%d", &pr_in, &p);
    if (pr_in > ids[0])    /* verifica produto */
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", pr_in);
    else{    /* altera o preco deste */
        sistema[pr_in].preco = p;    /* no sistema */
        atualiza_encomendas(ids[1], sistema[pr_in], encomendas);   /* na encomenda */   
    }
}
/*  Lista um produto de uma encomenda */
void E(){
    int enc_in, pr_in, id_pr_enc;
    scanf("%d:%d", &enc_in, &pr_in);
    if (enc_in > ids[1])    /* verifica encomenda */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc_in);
    
    else if (pr_in > ids[0])    /* verifica produto */
        printf("Impossivel listar produto %d. Produto inexistente.\n", pr_in);
    else{   /* lista produto na encomenda */
        id_pr_enc = produto_na_caixa(pr_in, encomendas[enc_in]);    /* id do produto na encomenda */
        printf("%s %d.\n", sistema[pr_in].desc, encomendas[enc_in][id_pr_enc].qtd);
    }
}
/*  Determina a encomenda com maior qtd de um produto */
void m(){
    int pr_in, id_enc;
    scanf("%d", &pr_in);
    if (pr_in > ids[0])    /* verifica produto */
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", pr_in);
    else{    /* determina encomenda com qtd maxima deste produto */
        id_enc = id_maxqtd_enc(ids[1], sistema[pr_in], encomendas);
        if (id_enc >= 0)    /* avalia se encontrou a encomenda */
            printf("Maximo produto %d %d %d.\n", pr_in, id_enc, 
            encomendas[id_enc][produto_na_caixa(pr_in, encomendas[id_enc])].qtd);
    }
}
/*  Lista todos os produtos do sistema (ordenados pelo preco) */
void l(){
    int i;
    for (i = 0; i <= ids[0]; i++) 
        aux[i] = sistema[i];    /* copia produtos */
    quicksort(aux, 0, ids[0]);  /* ordena caixa auxiliar */
    printf("Produtos\n");
    for (i = 0; i <= ids[0]; i++)   /* imprime todos os produtos desta caixa */
        printf("* %s %d %d\n", aux[i].desc, aux[i].preco, aux[i].qtd);
}
/*  Lista todos os produtos de uma encomenda (ordenados pela sua descricao) */
void L(){
    int enc_in;
    scanf("%d", &enc_in);
    if (enc_in > ids[1])    /* verifica encomenda */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc_in);
    else{   /* lista produtos da encomenda ordenados pela descricao */ 
        int i, tam = tamanho_encomenda(encomendas[enc_in]);
        for (i = 0; i < tam; i++)    /* copia produtos */
            aux[i] = encomendas[enc_in][i];
        ordena_desc(tam, aux);    /* ordena caixa auxiliar */ 
        printf("Encomenda %d\n", enc_in);
        for (i = 0; i < tam; i++)    /* imprime todos os produtos desta caixa */
            printf("* %s %d %d\n", aux[i].desc, aux[i].preco, aux[i].qtd);
    }
}
int main(){
    char cmd;
    ids[0] = -1;    /* inicializa ids de modo que o produto */
    ids[1] = -1;    /* e a encomenda sejam 0 inicialmente */
    while (1){
        scanf("%c", &cmd);
        switch (cmd){
        case 'a':
            a();break;
        case 'q':
            q();break;
        case 'N':
            N();break;
        case 'A':
            A();break;
        case 'r':
            r();break;
        case 'R':
            R();break;
        case 'C':
            C();break;
        case 'p':
            p();break;
        case 'E':
            E();break;
        case 'm':
            m();break;
        case 'l':
            l();break;
        case 'L':
            L();break;
        case 'x':
            return 0;
        }
    }
}