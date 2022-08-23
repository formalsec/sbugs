#include <stdio.h>
#include <string.h>
#define MAX_P 10000     /* numero maximo de produtos */
#define MAX_E 500       /* numero maximo de encomendas */
#define MAX_S 63        /* numero maximo de caracteres de uma descricao */
#define MAX_PESO 200    /* numero maximo que uma encomenda pode pesar */
#define key(A) (A)      /* abstracao utilizada nas seguintes */
#define less(A, B) (key(A) < key(B))   /* abstracao util para funcao ordena, que ordena vetores de inteiros */
#define exch(A, B) { int t = A; A = B; B = t; }   /* abstracao util para funcao ordena_s_auxiliar, que ordena vetores de strings */

/* inicializiacao das variaveis globais identificadores, de forma a ir contando as sucessivas encomendas e produtos a serem criados; desta forma ficarao sempre com o identificador do produto seguinte a ser adicionado */
int ind_p = 0, ind_e = 0;

/* associar o nome 'Produto' a uma estrutura definida, com quatro caracteristicas; */
typedef struct produto{
    char descricao[MAX_S];
    int preco;
    int peso;
    int qtd;
} Produto;

/* associar o nome 'Encomenda' a uma estrutura definida, com um vetor com os ids dos produtos adicionados a essa encomenda, bem como a quantidade de cada produto nessa encomenda, sendo que cada indice i corresponde ao idp do respetivo produto, por fim a caracteristica n_prod corresponde ao numero de produtos adicionados ah encomenda ide */
typedef struct encomenda{
    int produtos[MAX_P];
    int qtd[MAX_P];
    int n_prod;
} Encomenda;

/* Variaveis globais, sendo que o stock eh um vetor de estruturas, no qual o indice eh o id do produto; as encomendas sao representadas por um vetor 'enc' de encomendas (estruturas), no qual o indice do mesmo corresponde ao id da encomenda em questao */
Produto stock[MAX_P] = {0};
Encomenda enc[MAX_E] = {0};

/* variaveis globais que serao uteis para ordenacao nas funcoes auxiliares de ordenacao relativas ao comando 'l' */
int aux1[MAX_P];
int aux2[MAX_P];

/* comando 'a': adiciona um novo produto ao sistema */
void novo_produto()
{
    int preco, peso, qtd;
    char descricao[MAX_S];

    /* Leitura de um produto do input */
    scanf("%[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);

    /* Guarda produto no stock */
    strcpy(stock[ind_p].descricao, descricao);
    stock[ind_p].preco = preco;
    stock[ind_p].peso = peso;
    stock[ind_p].qtd = qtd;

    printf("Novo produto %d.\n", ind_p++);  /* incremento da variavel com o numero de indices de produtos */
}

/* comando 'q': adiciona stock a um produto existente no sistema */
void add_stock()
{
    int idp, qtd;

    /* leitura do input do idp de um produto e da quantidade a adicionar no stock */
    scanf("%d:%d", &idp, &qtd);

    /* verificar se o produto com (id = idp) existe */
    if (idp >= ind_p)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else
        stock[idp].qtd += qtd;
}

/* comando 'N': cria uma nova encomenda */
void nova_encomenda()
{
    printf("Nova encomenda %d.\n", ind_e++);    /* incremento da variavel com o numero de indices de encomendas */
}

/* funcao auxiliar que calcula o peso de uma determinada quantidade de um produto */
int calcula_peso(int idp, int qtd)
{
    return (stock[idp].peso*qtd);
}

/* funcao auxiliar que calcula o peso de uma encomenda */
int calcula_peso_encomenda(int ide)
{
    int i, total = 0;

    /* ciclo que vai somando o peso de cada produto na encomenda ide, invocando a funcao anterior */
    for (i = 0; i < enc[ide].n_prod; i++)
        total += calcula_peso(enc[ide].produtos[i],enc[ide].qtd[enc[ide].produtos[i]]);
    
    return total;
}

/* comando 'A': adiciona um produto a uma encomenda. Se o produto ja existir na encomenda, adiciona a nova quantidade ah quantidade existente */
void add_produto()
{
    int ide, idp, qtd, i;

    /* leitura do produto a adicionar ah encomenda com identificador ide */
    scanf("%d:%d:%d", &ide, &idp, &qtd);

    if (ide >= ind_e)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp >= ind_p)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (stock[idp].qtd < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if (calcula_peso(idp, qtd)+calcula_peso_encomenda(ide) > MAX_PESO)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else{
        stock[idp].qtd -= qtd;     /* subtrair a mesma qtd ao stock */
        for (i = 0; i < enc[ide].n_prod; i++)
            if (enc[ide].produtos[i] == idp){   /* no caso de o produto a ser adicionado ja existir na encomenda */
                enc[ide].qtd[idp] += qtd;
                return; /* saida da funcao */
            }
        enc[ide].qtd[idp] = qtd;
        enc[ide].produtos[i] = idp;   /* adiciona ao vetor com ids dos produtos da encomenda o produto dado */
        enc[ide].n_prod++;  /* incremento do numero de produtos na encomenda */
    }
}

/* comando 'r': remove stock a um produto existente */
void remove_stock()
{
    int idp, qtd;

    /* leitura do produto e da quantidade a adicionar ao mesmo no stock */
    scanf("%d:%d", &idp, &qtd);

    if (idp >= ind_p)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if (stock[idp].qtd < qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    
    else
        stock[idp].qtd -= qtd;

}

/* comando 'R': remove um produto de uma encomenda */
void remove_produto()
{
    int ide, idp, i, j;

    /* leitura da encomenda e do produto a ser removido da mesma */
    scanf("%d:%d", &ide, &idp);

    if (ide >= ind_e)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp >= ind_p)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else{
        for (i = 0; i < enc[ide].n_prod; i++)
            if (enc[ide].produtos[i] == idp){   /* no caso de o produto existir na encomenda */
                for (j = i; j < (enc[ide].n_prod)-1; j++)
                    enc[ide].produtos[j] = enc[ide].produtos[j+1];  /* retira o produto da encomenda */
                enc[ide].n_prod--;  /* decremento do numero de produtos de uma encomenda */
                stock[idp].qtd += enc[ide].qtd[idp];    /* soma ao stock a quantidade a retirar da encomenda */
                enc[ide].qtd[idp] = 0;  /* quantidade desse produto a remover da encomenda passa a 0 */
                break;    /* saida do ciclo */
            }
    }
}

/* comando 'C': calcula o custo de uma encomenda */
void custo_encomenda()
{
    /* i sera variavel de iteracao e total sera variavel a imprimir */
    int ide, i, total = 0;

    /* leitura do input da encomenda da qual se quer calcular o preco */
    scanf("%d", &ide);

    if (ide >= ind_e)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else{
        /* ciclo que vai calculando o preco de cada quantidade do produto i na encomenda ide */
        for (i = 0; i < enc[ide].n_prod; i++)
            total += (enc[ide].qtd[enc[ide].produtos[i]])*(stock[enc[ide].produtos[i]].preco);
        printf("Custo da encomenda %d %d.\n", ide, total);
    }
}

/* comando 'p': altera o preco de um produto existente no sistema */
void altera_preco()
{
    int idp, preco;

    /* leitura do identificador do produto a ser alterado, assim como o novo preco estabelecido */
    scanf("%d:%d", &idp, &preco);

    if (idp >= ind_p)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else
        stock[idp].preco = preco;

}

/* comando 'E': lista a descricao e a quantidade de um produto numa encomenda */
void lista_produto()
{
    int ide, idp;

    /* leitura de uma encomenda e um produto do input */
    scanf("%d:%d", &ide, &idp);

    if (ide >= ind_e)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if (idp >= ind_p)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else
        printf("%s %d.\n", stock[idp].descricao, enc[ide].qtd[idp]);

}

/* comando 'm': lista o identificador da encomenda em que o produto dado ocorre mais vezes */
void lista_encomenda_produto()
{
    /* variavel max contem a maior quantidade do produto idp numa determinada encomenda; i eh variavel de iteracao;
    variavel max_e vai conter o id da encomenda em que o produto dado ocorre mais vezes */
    int idp, i, max = 0, max_e = 0;
    /* leitura do produto do input */
    scanf("%d", &idp);

    if (idp >= ind_p)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else{
        /* ciclo que percorre todas as encomendas criadas, ah procura da maior quantidade do produto dado */
        for (i = 0; i < ind_e; i++)
            if (enc[i].qtd[idp] > max){    /* caso a quantidade do produto na encomenda i seja maior que a variavel max, que contem a maior quantidade desse produto numa determinada encomenda */
                max = enc[i].qtd[idp];
                max_e = i;
            }
        if (max != 0 && ind_e != 0)   /* excluindo o caso de nenhuma encomenda conter este produto ou de nao existirem encomendas */
            printf("Maximo produto %d %d %d.\n", idp, max_e, max);
    }
}

/* funcao auxiliar de ordenacao de dois vetores ah custa do primeiro, relativamente ao comando 'l';
deste modo, cada vez que efetua uma troca no primeiro vetor dos precos, efetua tambem no segundo, o dos ids */
void ordena_auxiliar(int a1[], int a2[], int l, int m, int r)
{
    int i,j,k;

    for (i = m + 1; i > l; i--){
        aux1[i-1] = a1[i-1];
        aux2[i-1] = a2[i-1];
    }
    for (j = m; j < r; j++){
        aux1[r+m-j] = a1[j+1];
        aux2[r+m-j] = a2[j+1];
    }
    for (k = l; k <= r; k++){
        if (less(aux1[j],aux1[i]) || ((aux1[j] == aux1[i]) && aux2[j] < aux2[i])){  /* segunda condicao para o caso de os precos serem os mesmos, sendo o criterio de desempate os ids dos respetivos produtos */
            a1[k] = aux1[j];
            a2[k] = aux2[j--];
        }
        else{
            a1[k] = aux1[i];
            a2[k] = aux2[i++];
        }
    }
}

/* funcao auxiliar que ordena os dois vetores passados como argumentos na funcao lista_todos_produtos; invoca tambem funcao ordena_auxiliar (ordenacao merge sort) */
void ordena(int a1[], int a2[], int l, int r)
{
    int m = (r + l)/ 2;

    if (r <= l)
        return;
    
    ordena(a1, a2, l, m);
    ordena(a1, a2, m + 1, r);
    ordena_auxiliar(a1, a2, l, m, r);
}

/* comando 'l': lista todos os produtos existentes no sistema por ordem crescente de preco */
void lista_todos_produtos()
{
    /* vetores dos ids dos produtos e dos seus precos */
    int tab1[MAX_P], tab2[MAX_P];
    int i;

    /* ciclo para atribuir os precos e os ids dos produtos criados, respetivamente, as sucessivas posicoes dos vetores */
    if (ind_p != 0){
        for (i = 0; i < ind_p; i++){   /* tab1 contem os precos dos produtos e tab2 os indices dos mesmos */
            tab1[i] = stock[i].preco;
            tab2[i] = i;
        }

        /* chamada da funcao que ordena os vetores tab1 e tab2, por ordem crescente de preco, ou seja tendo em conta o tab1 que contem os mesmos */
        ordena(tab1, tab2, 0, ind_p-1);
    
        printf("Produtos\n");

        /* ciclo para imprimir todos os produtos agora ordenados por preco */
        for (i = 0; i < ind_p; i++)
            printf("* %s %d %d\n", stock[tab2[i]].descricao, stock[tab2[i]].preco, stock[tab2[i]].qtd);
    }
    else    /* caso nao haja produtos */
        printf("Produtos\n");

}

/* funcao auxiliar de ordenacao de dois vetores ah custa do primeiro, relativamente ao comando 'L';
deste modo, cada vez que efetua uma troca no primeiro vetor das descricoes, efetua tambem no segundo, o dos ids */
int ordena_s_auxiliar(char a1[MAX_P][MAX_S], int a2[], int l, int r)
{
    char v[MAX_S];
    char s[MAX_S];
    int i = l - 1;
    int j = r;
    strcpy(v, a1[r]);

    while (i < j){
        while (strcmp(a1[++i], v) < 0);
        while (strcmp(v, a1[--j]) < 0)
            if (j == l)
                break;
        if (i < j){
            strcpy(s, a1[i]);   strcpy(a1[i], a1[j]);   strcpy(a1[j], s);
            exch(a2[i], a2[j]);
        }
    }

    strcpy(v, a1[i]);   strcpy(a1[i], a1[r]);   strcpy(a1[r], v);
    exch(a2[i], a2[r]);
    return i;
}

/* funcao auxiliar que ordena os dois vetores passados como argumentos na funcao lista_encomenda_produtos; invoca tambem a funcao ordena_auxiliar_s (ordenacao quicksort) */
void ordena_s(char a1[MAX_P][MAX_S], int a2[], int l, int r)
{
    int i;
    
    if (r <= l)
        return;
    
    i = ordena_s_auxiliar(a1, a2, l, r);
    ordena_s(a1, a2, l, i-1);
    ordena_s(a1, a2, i+1, r);

}

/* comando 'L': lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
void lista_encomenda_produtos()
{
    /* tab1 eh vetor de strings de forma ser direta a ordenacao alfebetica das descricoes;
    tab2 eh vetor de inteiros, contendo os ids dos produtos da encomenda */
    char tab1[MAX_P][MAX_S];
    int tab2[MAX_P];
    int i, ide;

    /* leitura do input do numero da encomenda a ser listada */
    scanf("%d", &ide);

    if (ide >= ind_e)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else{
        /* copia para o vetor criado no inicio da funcao das descricoes dos produtos que existem na encomenda dada */
        for (i = 0; i < enc[ide].n_prod; i++){
            strcpy(tab1[i],stock[enc[ide].produtos[i]].descricao);
            tab2[i] = enc[ide].produtos[i];
        }

        /* chamada da funcao ordena_s que vai ordenar os dois vetores passados como argumentos */
        ordena_s(tab1, tab2, 0, (enc[ide].n_prod) - 1);
    
        printf("Encomenda %d\n", ide);

        /* ciclo para ir listando os produtos contidos na encomenda */
        for (i = 0; i < enc[ide].n_prod; i++)
            printf("* %s %d %d\n", stock[tab2[i]].descricao, stock[tab2[i]].preco, enc[ide].qtd[tab2[i]]);
    }
}

int main()
{
    int c = 0;

    /* ir lendo comandos dados no input ate ser lido 'x' (fim) */
    while (c != EOF){
        switch(c = getchar()){
            case 'a':
                c = getchar(); /* leitura do espaco a seguir ao comando */
                novo_produto();
                break;
            case 'q':
                c = getchar();
                add_stock();
                break;
            case 'N':
                nova_encomenda();
                break;
            case 'A':
                c = getchar();
                add_produto();
                break;
            case 'r':
                c = getchar();
                remove_stock();
                break;
            case 'R':
                c = getchar();
                remove_produto();
                break;
            case 'C':
                c = getchar();
                custo_encomenda();
                break;
            case 'p':
                c = getchar();
                altera_preco();
                break;
            case 'E':
                c = getchar();
                lista_produto();
                break;
            case 'm':
                c = getchar();
                lista_encomenda_produto();
                break;
            case 'l':
                lista_todos_produtos();
                break;
            case 'L':
                c = getchar();
                lista_encomenda_produtos();
                break;
            case 'x':
                break;
        }
        /* ler o caracter '\n', ou EOF no caso do 'x', de forma a sair do ciclo */
        c = getchar();
    }
    return 0;
}
