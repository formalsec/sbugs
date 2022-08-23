#include <stdio.h>
#include <string.h>

#define MAX_PROD 10000 /* Numero maximo de produtos no sistema */
#define MAX_ENCOMENDA 500 /* Numero maximo de encomendas */
#define PRODUTOS 200 /* Numero maximo de produtos por encomenda */
#define CHAR 64 /* Numero maximo de caracteres por descricao */

struct produto {  /* estrutura do produto */
    int idp;
    char descricao[CHAR];
    int preco;
    int peso;
    int qtd;
};

/* Variaveis identificadoras da quantidade de produtos e encomendas em stock + 1*/
int idp = 0, ide = 0;

/* Estrutura do artigo - produto que pertence a encomenda */
struct artigo {
    int idp;
    int qtd;
};

/* Estrutura da encomenda */
struct encomenda {
    int ide;
    struct artigo lista_artigos[PRODUTOS];
    int peso;
    int last; /* ultimo + 1 artigo da lista */
};

struct produto sistema[MAX_PROD]; /* vetor que contem todos os produtos */
struct encomenda lista_enc[MAX_ENCOMENDA]; /* vetor de encomendas */

int left, right;

/* Inicializacao funcoes auxiliares - comandos*/
void executa_a(char descricao[], int preco, int peso, int qtd);
void executa_q(int identificador, int qtd);
void executa_N();
void executa_A(int enc, int identificador, int qtd);
void executa_r(int dentificador, int qtd);
void executa_R(int enc, int identificador);
void executa_C(int enc);
void executa_p(int identificador, int preco);
void executa_E(int enc, int identificador);
void executa_m(int identificador);
void executa_l();
void executa_L(int enc);

/* inicializacao das funcoes de ordenadacao */
void mergesort(struct artigo desord[], int left, int right);
void merge(struct artigo desord[], int left, int m, int right);
void quicksort(struct produto desordenado[], int left, int right);
int partition(struct produto desordenado[], int left, int right);
int less(struct produto a, struct produto b);
void exch(struct produto desordenado[], int a, int b);
int less_a(struct artigo a, struct artigo b);


/* le o input e executa os comandos correspondentes */
int main () {
    /* variaveis de input */
    char descricao[CHAR];
    int preco, peso, qtd;
    int identificador, enc;

    char comando;
    while ((comando = getchar()) != 'x') { /* enquanto nao receber o x, entra no switch */
        switch (comando) {
            case 'a':
                scanf(" %[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);
                executa_a(descricao, preco, peso, qtd);
                break;
            case 'q':
                scanf("%d:%d", &identificador, &qtd);
                executa_q(identificador, qtd);
                break;
            case 'N':
                executa_N();
                break;
            case 'A':
                scanf("%d:%d:%d", &enc, &identificador, &qtd);
                executa_A(enc, identificador, qtd);
                break;
            case 'r':
                scanf("%d:%d", &identificador, &qtd);
                executa_r(identificador, qtd);
                break;
            case 'R':
                scanf("%d:%d", &enc, &identificador);
                executa_R(enc, identificador);
                break;
            case 'C':
                scanf("%d", &enc);
                executa_C(enc);
                break;
            case 'p':
                scanf("%d:%d", &identificador, &preco);
                executa_p(identificador, preco);
                break;
            case 'E':
                scanf("%d:%d", &enc, &identificador);
                executa_E(enc, identificador);
                break;
            case 'm':
                scanf("%d", &identificador);
                executa_m(identificador);
                break;
            case 'l':
                executa_l();
                break;
            case 'L':
                scanf("%d", &enc);
                executa_L(enc);
                break;
        }
        getchar(); /* tirar o '\n' do input */
    }
   return 0;
}

/* adiciona novo produto ao sistema */
void executa_a(char descricao[], int preco, int peso, int qtd) {
    sistema[idp].idp = idp;
    strcpy (sistema[idp].descricao, descricao);
    sistema[idp].preco = preco;
    sistema[idp].peso = peso;
    sistema[idp].qtd = qtd;
    printf("Novo produto %d.\n", idp++);
}

/* adiciona stock a um produto criado */
void executa_q(int identificador, int qtd) {
    if (identificador < idp) /* o valor do identificador tem de ser inferior ao idp para o produto existir*/
        sistema[identificador].qtd += qtd;
    else
        printf ("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", identificador);
}

/* cria uma nova encomenda */
void executa_N() { /* DON'T THINK THIS IS RIGHT */
    lista_enc[ide].ide = ide;
    lista_enc[ide].peso = 0;
    lista_enc[ide].last = 0;
    printf("Nova encomenda %d.\n", ide++);
}

/* adiciona um produto a uma encomenda ou adiciona nova quantidade, no caso de o produto ja existir na encomenda */
void executa_A(int enc, int identificador, int qtd) {
    int i;
    if (enc >= ide) {
        printf ("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", identificador, enc);
        return;
    }
    else if (identificador >= idp) {
        printf ("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", identificador, enc);
        return;
    }
    else if (sistema[identificador].qtd < qtd) {
        printf ("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", identificador, enc);
        return;
    }
    else if (lista_enc[enc].peso + (sistema[identificador].peso * qtd) > PRODUTOS) {
        printf ("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", identificador, enc);
        return;
    }
    for (i = 0; i < lista_enc[enc].last; i++) { /* percorre a lista de artigos de uma encomenda */
        if (lista_enc[enc].lista_artigos[i].idp == identificador) { /* verifica se o produto ja se encontra na encomenda para adicionar quantidade */
            lista_enc[enc].lista_artigos[i].qtd += qtd;
            lista_enc[enc].peso += (qtd * sistema[identificador].peso);
            sistema[identificador].qtd -= qtd;
            return;
        }
    }
    /* adiciona artigo a encomenda */
    lista_enc[enc].lista_artigos[lista_enc[enc].last].idp = identificador;
    lista_enc[enc].lista_artigos[lista_enc[enc].last].qtd = qtd;
    lista_enc[enc].peso += (qtd * sistema[identificador].peso);
    sistema[identificador].qtd -= qtd;
    lista_enc[enc].last++;
}

/* remove stock a um produto existente */
void executa_r(int identificador, int qtd) {
    if (identificador >= idp)
        printf ("Impossivel remover stock do produto %d. Produto inexistente.\n", identificador);
    else if (sistema[identificador].qtd < qtd)
        printf ("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, identificador);
    else
        sistema[identificador].qtd -= qtd;
}

/* remove um produto de uma encomenda */
void executa_R(int enc, int identificador) {
    int i;
    int j = lista_enc[enc].last;
    if (enc >= ide)
        printf ("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", identificador, enc);
    else if (identificador >= idp)
        printf ("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", identificador, enc);
    else {
        /* ciclo para encontrar qual a posicao do artigo na encomenda */
        for (i = 0; i < lista_enc[enc].last; i++) {
            if (lista_enc[enc].lista_artigos[i].idp == identificador) {
                sistema[identificador].qtd += lista_enc[enc].lista_artigos[i].qtd;
                lista_enc[enc].peso -= sistema[identificador].peso * lista_enc[enc].lista_artigos[i].qtd;
                lista_enc[enc].last--;
                break;
            }
        }
        /* reescrita dos artigos, adicionados depois do removido, na posicao anterior */
        for (; i < j - 1; i++) {
            lista_enc[enc].lista_artigos[i] = lista_enc[enc].lista_artigos[i+1];
        }
    }
}

/* calcula o custo de uma encomenda */
void executa_C(int enc) { /* YOU ARE HERE */
    int i;
    int preco_enc = 0;
    if (enc >= ide)
        printf ("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", enc);
    else {
        for (i = 0; i < lista_enc[enc].last; i++)
            preco_enc += (sistema[lista_enc[enc].lista_artigos[i].idp].preco * lista_enc[enc].lista_artigos[i].qtd);
        printf("Custo da encomenda %d %d.\n", enc, preco_enc);
    }
}

/* altera o preco de um produto existente no sistema */
void executa_p(int identificador, int preco) {
    if (identificador >= idp)
        printf ("Impossivel alterar preco do produto %d. Produto inexistente.\n", identificador);
    else
        sistema[identificador].preco = preco;
}

/* lista a descricao e a quantidade de um produto numa encomenda */
void executa_E(int enc, int identificador) {
    int i;
    if (identificador >= idp)
        printf ("Impossivel listar produto %d. Produto inexistente.\n", identificador);
    else if (enc >= ide)
        printf ("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
    else {
        for (i = 0; i < lista_enc[enc].last; i++) {
            if (lista_enc[enc].lista_artigos[i].idp == identificador) {
                printf("%s %d.\n", sistema[identificador].descricao, lista_enc[enc].lista_artigos[i].qtd);
                return;
            }
        }
        printf("%s 0.\n", sistema[identificador].descricao);
    }
}

/* lista o identificador da encomenda em que um dado produto ocorre mais vezes */
void executa_m(int identificador) {
    int max = 0;
    int i, j;
    int max_enc = 0;

    if (identificador >= idp) {
        printf ("Impossivel listar maximo do produto %d. Produto inexistente.\n", identificador);
        return;;
    }
    else {
        for (j = 0; j < ide; j++) { /* percorre as encomendas */
            for (i = 0; i < lista_enc[j].last; i++) { /* percorre os artigos de uma dada encomenda */
                /* verifica se o produto aparece na encomenda e, caso pertenca, se a sua quantidade e superior ao maximo ate entao registado */
                if (lista_enc[j].lista_artigos[i].idp == identificador && lista_enc[j].lista_artigos[i].qtd > max) {
                    max = lista_enc[j].lista_artigos[i].qtd;
                    max_enc = j;
                    break;
                }
            }
        }
        if (max == 0) /* verifica se o produto nao ocorre em nenhuma encomenda */
            return;
        else
            printf("Maximo produto %d %d %d.\n", identificador, max_enc, max);
    }
}

/* lista todos os produtos existentes no sistema por ordem crescente de preco */
void executa_l() {
    struct produto desordenado[MAX_PROD]; /* vetor copia do sistema de produtos */
    int i;
    for (i = 0; i < idp; i++) /* copia o conteudo do vetor sistema para ser ordenado */
        desordenado[i] = sistema[i];
    quicksort(desordenado, 0, idp-1);
    printf("Produtos\n");
    for (i=0; i < idp; i++)
        printf("* %s %d %d\n", desordenado[i].descricao, desordenado[i].preco, desordenado[i].qtd);
}

/* lista todos os produtos de uma encomenda por ordem alfabetica */
void executa_L(int enc) {
    struct artigo desord[PRODUTOS]; /* vetor copia dos artigos de uma encomenda */
    int i;
    if (enc >= ide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
    else {
        for (i = 0; i < lista_enc[enc].last; i++) /* copia o conteudo do vetor sistema para ser ordenado */
            desord[i] = lista_enc[enc].lista_artigos[i];
        mergesort(desord, 0, lista_enc[enc].last-1);
        printf("Encomenda %d\n", enc);
        for (i=0; i < lista_enc[enc].last; i++)
            printf("* %s %d %d\n", sistema[desord[i].idp].descricao, sistema[desord[i].idp].preco, desord[i].qtd);
    }
}

/* Funcoes de ordenacao */

/* funcao de ordenacao dos precos dos produtos no sistema */
void quicksort(struct produto desordenado[], int left, int right) {
    int i;
    if (right <= left)
        return;

    i = partition(desordenado, left, right);
    quicksort(desordenado, left, i-1);
    quicksort(desordenado, i+1, right);
}

/* funcao auxiliar do quicksort*/
int partition(struct produto desordenado[], int left, int right) {
    int i = left-1;
    int j = right;
    struct produto pivo = desordenado[right];

    while (i < j) {
        while (less(desordenado[++i], pivo))
            ;
        while (less(pivo, desordenado[--j]))
            if (j == left)
                break;
        if (i < j) {
            exch(desordenado, i, j);
        }
    }
    exch(desordenado, i, right);
    return i;
}

/* funcao que ordena os produtos de uma encomenda por ordem alfabetica */
void mergesort(struct artigo desord[], int left, int right) {
    int m = (right+left)/2;
    if (right <= left)
        return;
    mergesort(desord, left, m);
    mergesort(desord, m+1, right);
    merge(desord, left, m, right);
}

/* funcao auxiliar do merge*/
void merge(struct artigo desord[], int left, int m, int right) {
    struct artigo aux[PRODUTOS];
    int i, j, k;
    for (i = m+1; i > left; i--)
        aux[i-1] = desord[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = desord[j+1];
    for (k = left; k <= right; k++)
        if (less_a(aux[j], aux[i]))
            desord[k] = aux[j--];
        else
            desord[k] = aux[i++];
}


/* compara o preco de dois produtos e, para o caso deste ser igual, compara o seu idp */
int less(struct produto a, struct produto b) {
    return((a.idp < b.idp && (a.preco == b.preco)) || (a.preco < b.preco));
}

/* troca dois produtos de forma a ficarem ordenados por preco entre si */
void exch(struct produto desordenado[], int a, int b) {
    struct produto c = desordenado[b];
    desordenado[b] = desordenado[a];
    desordenado[a] = c;
}

/* compara duas strings, correspondentes a descricao de um produto */
int less_a(struct artigo a, struct artigo b) {
    return(strcmp(sistema[a.idp].descricao, sistema[b.idp].descricao) < 0);
}
