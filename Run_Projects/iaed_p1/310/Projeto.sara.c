#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAXINPUT 1000
#define MAXSTR 64 
#define TIPOSDEDADOS 5
#define MAXPESO 200
#define MAXENCOMENDAS 500
#define MAXPRODUTOS 10000


/* Estrutura que contem 4 inteiros e 1 string
utilizada ao longo de todo o programa */
typedef struct {
    int id_produto;
    char desc_produto[MAXSTR];
    int preco_produto;
    int peso_produto;
    int stock_produto;
} produto;


/* Estrutura que contem 1 vetor de produtos e 3 inteiros e utilizada 
ao longo de todo o programa */
typedef struct {
    int id_encomenda;
    produto e[MAXPESO]; /* Vetor de produtos */
    int quantidade;
    int peso_encomenda;
} encomenda;


int idp = 0; /* Contador de idps */
int ide = 0; /* Contador de ides */
produto inventario_produtos[MAXPRODUTOS]; /* Inventario (vetor) onde se encontram os produtos inseridos no sistema */
encomenda lista_encomendas[MAXENCOMENDAS]; /* Lista (vetor) de todas as encomendas que tem no seu interior produtos */


/* Separa os dados introduzidos pelo utilizador e guarda-os (funcao auxiliar) */
int split_string(char to_split[MAXSTR], char target[TIPOSDEDADOS][MAXSTR]) {
    int i;
    char * word;
    for (i = 0; i < TIPOSDEDADOS; i++) {
        strncpy(target[i], "", MAXSTR);
    }
    word = strtok(to_split, ":");
    for (i = 0; word != NULL; i++) {
        strncpy(target[i], word, MAXSTR);   
        word = strtok(NULL, ":");
    }
    return i;
}


/* Le os dados introduzidos pelo utilizador (funcao auxiliar) */
int read_line(char s[]) {
    int c, i = 0;
    while ((c = getchar()) != EOF && c != '\n' && c != '\0') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}


/* Formato de entrada: a descricao:preco:peso:qtd */
/* Formato de saida: Novo produto <idp>. onde <idp> e o identificador do produto criado. */
/* Erros: nenhum */
/* Esta funcao cria um novo produto no sistema */
void adiciona_produto() {
    char s[MAXINPUT]; /* declaracao de uma variavel para onde entrara o input antes de ser separado */
    char dados[TIPOSDEDADOS][MAXSTR]; /* declaracao de uma variavel onde os dados serao guardados ja separados */
    read_line(s); /* Leitura dos dados para dentro da variavel s */
    split_string(s, dados); /* separa os dados da variavel s para a variavel dados */
    inventario_produtos[idp].id_produto = idp;
    strcpy(inventario_produtos[idp].desc_produto, dados[0]); /* dados[0] = descricao */
    inventario_produtos[idp].preco_produto = atoi(dados[1]); /* atoi(dados[1]) = preco */
    inventario_produtos[idp].peso_produto = atoi(dados[2]); /* atoi(dados[2]) = peso */
    inventario_produtos[idp].stock_produto = atoi(dados[3]); /* atoi(dados[3]) = stock */
    printf("Novo produto %d.\n", inventario_produtos[idp].id_produto);
    idp++; /* Aumentar o "contador" de idps */
}


/* Formato de entrada: q idp:qtd */
/* Fromato de saida: NADA */
/* Erros: * no caso de nao existir nenhum produto criado com esse identificador */
/* Esta funcao adiciona stock a um produto existente no sistema */
void adiciona_stock() {
    char s[MAXINPUT];
    char dados[TIPOSDEDADOS][MAXSTR];
    read_line(s);
    split_string(s, dados);
    if (atoi(dados[0]) >= idp) { /* atoi(dados[0]) = id do produto - Caso o idp introduzido seja maior que o "contador" de idps entao 
    esse produto nao existe no sistema */
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", atoi(dados[0]));
        return;
        }
    inventario_produtos[atoi(dados[0])].stock_produto += atoi(dados[1]); /* atoi(dados[1]) = quantidade */
}


/* Formato de entrada: N */
/* Formato de saida: Nova encomenda <ide>. onde <ide> e o identificador da encomenda criada. */
/* Erros: nenhum */
/* Esta funcao cria uma nova encomenda no sistema */
void cria_nova_encomenda() {
    char s[MAXINPUT];
    char dados[TIPOSDEDADOS][MAXSTR];
    read_line(s);
    split_string(s, dados);
    lista_encomendas[ide].id_encomenda = ide;
    printf("Nova encomenda %d.\n", ide);
    ide++; /* Aumentar o "contador" de ides */
}


/* Formato de entrada: A ide:idp:qtd */
/* Formato de saida: NADA (excepto erro) */
/* Erros: * no caso de nao existir nenhuma encomenda criada com esse identificador
          * no caso de nao existir nenhum produto criado com esse identificador
          * no caso de nao existir stock suficiente desse produto para satisfazer a encomenda
          * no caso de a adicao desse produto exceder o peso maximo permitido por encomenda */
/* Esta funcao adiciona um produto a uma encomenda. Se o produto ja existir na encomenda, adiciona a nova quantidade a quantidade existente */
void adiciona_produto_encomenda() {
    int a = 1; /* Variavel de controlo que verifica se entramos ou nao no for */
    int i;
    char s[MAXINPUT];
    char dados[TIPOSDEDADOS][MAXSTR];
    read_line(s);
    split_string(s, dados);
    if (atoi(dados[0]) >= ide) { /* atoi(dados[0]) = id da encomenda - Caso o ide introduzido seja maior que o 
    "contador" de ides entao essa encomenda nao existe */
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", atoi(dados[1]), atoi(dados[0])); 
        return;
    }
    else if (atoi(dados[1]) >= idp) { /* atoi(dados[1]) = id do produto - Caso o idp introduzido seja maior que o "contador" 
    de idps entao esse produto nao existe */
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", atoi(dados[1]), atoi(dados[0]));
        return;
    }
    else if (inventario_produtos[atoi(dados[1])].stock_produto < atoi(dados[2])) { /* atoi(dados[2]) = quantidade - Caso a quantidade pretendida
     seja maior que o stock disponivel para o produto */
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", atoi(dados[1]), atoi(dados[0]));
        return;
    }
    else if (lista_encomendas[atoi(dados[0])].peso_encomenda + (atoi(dados[2]) * inventario_produtos[atoi(dados[1])].peso_produto) > MAXPESO) {
        /* Caso os produtos a adicionar ultrapassem o maximo de peso por encomenda */
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", atoi(dados[1]), atoi(dados[0]));
        return;
    }
    for (i = 0; i < lista_encomendas[atoi(dados[0])].quantidade; i++) { /* Percorre todos os produtos na encomenda introduzida e ve se existe
     algum produto igual ao introduzido pelo utilizador */
        if (lista_encomendas[atoi(dados[0])].e[i].id_produto == atoi(dados[1])) {
            lista_encomendas[atoi(dados[0])].e[i].stock_produto += atoi(dados[2]);
            lista_encomendas[atoi(dados[0])].peso_encomenda += atoi(dados[2]) * inventario_produtos[atoi(dados[1])].peso_produto;
            inventario_produtos[atoi(dados[1])].stock_produto -= atoi(dados[2]);
            a = 0;
            break;
        }
    }
    if (a == 1) { /* Caso o produto nao exista ainda na encomenda entao vamos introduzi-lo */
        strcpy(lista_encomendas[atoi(dados[0])].e[lista_encomendas[atoi(dados[0])].quantidade].desc_produto, inventario_produtos[atoi(dados[1])].desc_produto);
        lista_encomendas[atoi(dados[0])].e[lista_encomendas[atoi(dados[0])].quantidade].id_produto = atoi(dados[1]);
        lista_encomendas[atoi(dados[0])].e[lista_encomendas[atoi(dados[0])].quantidade].stock_produto = atoi(dados[2]);
        lista_encomendas[atoi(dados[0])].peso_encomenda += atoi(dados[2]) * inventario_produtos[atoi(dados[1])].peso_produto;
        inventario_produtos[atoi(dados[1])].stock_produto -= atoi(dados[2]);
        lista_encomendas[atoi(dados[0])].quantidade++; /* Incrementamos a quantidade de produtos que existem na encomenda */
    }
}


/* Formato de entrada: r idp:qtd */
/* Formato de saida: NADA (excepto erro) */
/* Erros: * no caso de nao existir nenhum produto criado com esse identificador 
          * no caso de a quantidade de stock restante apos a remocao ser negativa */
/* Esta funcao remove stock a um produto existente */
void remove_stock() {
    char s[MAXINPUT];
    char dados[TIPOSDEDADOS][MAXSTR];
    read_line(s);
    split_string(s, dados);
    if (atoi(dados[0]) >= idp) { /* atoi(dados[0]) = id do produto */
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", atoi(dados[0])); 
        return;
    }
    else if (inventario_produtos[atoi(dados[0])].stock_produto < atoi(dados[1])) { /* atoi(dados[1]) = quantidade - Caso a quantidade 
    a remover seja maior que a disponivem em stock emite erro */
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", atoi(dados[1]), atoi(dados[0]));
        return;
    }
    inventario_produtos[atoi(dados[0])].stock_produto -= atoi(dados[1]); /* Remocao da quantidade ao produto no sistema */
}


/* Formato de entrada: R ide:idp */
/* Formato de saida: NADA (excepto erro) */
/* Erros: * no caso de nao existir nenhuma encomenda criada com esse identificador 
          * no caso de nao existir nenhum produto criado com esse identificador */
/* Esta funcao remove um produto de uma encomenda */
void remove_produto_encomenda() {
    int i;
    char s[MAXINPUT];
    char dados[TIPOSDEDADOS][MAXSTR];
    read_line(s);
    split_string(s, dados);
    if (atoi(dados[0]) >= ide) { /* atoi(dados[0]) = id do produto */
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", atoi(dados[1]), atoi(dados[0]));
        /* atoi(dados[1]) = id da encomenda */
        return;
    }
    else if (atoi(dados[1]) >= idp) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", atoi(dados[1]), atoi(dados[0]));
        return;
    }
    else {
        for (i = 0; i < lista_encomendas[atoi(dados[0])].quantidade; i++) {
            if (lista_encomendas[atoi(dados[0])].e[i].id_produto == atoi(dados[1])) {
                lista_encomendas[atoi(dados[0])].peso_encomenda -= lista_encomendas[atoi(dados[0])].e[i].stock_produto * inventario_produtos[atoi(dados[1])].peso_produto;
                inventario_produtos[atoi(dados[1])].stock_produto += lista_encomendas[atoi(dados[0])].e[i].stock_produto; /* Aumenta a quantidade de produto
                 no inventario consoante a quantidade que esse produto tinha na encomenda */
                lista_encomendas[atoi(dados[0])].e[i].id_produto = 0;
                lista_encomendas[atoi(dados[0])].e[i].preco_produto = 0;    /* Estas 4 linhas servem para fazer "reset" ao valores que 
                                                                                        correspondiam ao antigo produto */
                lista_encomendas[atoi(dados[0])].e[i].stock_produto = 0;
                lista_encomendas[atoi(dados[0])].e[i].peso_produto = 0;
            }
        }
    }
} 


/* Formato de entrada: C ide */
/* Formato de saida: Custo da encomenda <ide> <total>. onde <total> e o valor total da encomenda <ide> */
/* Erros: * no caso de nao existir nenhuma encomenda criada com esse identificador */
/* Esta funcao calcula o custo de uma encomenda */
void calcula_custo() {
    int i;
    int c = 0; /* Variavel onde ira ser guardado o custo */
    char s[MAXINPUT];
    char dados[TIPOSDEDADOS][MAXSTR];
    read_line(s);
    split_string(s, dados);
    if (atoi(dados[0]) >= ide) { /* atoi(dados[0]) = id da encomenda */
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", atoi(dados[0]));
        return;
    }
    for (i = 0; i < lista_encomendas[atoi(dados[0])].quantidade; i++) { /* Percorre todos os produtos da encomenda e guarda o seu custo */
            c += (lista_encomendas[atoi(dados[0])].e[i].stock_produto * inventario_produtos[lista_encomendas[atoi(dados[0])].e[i].id_produto].preco_produto); 
            /* Calcula o custo multiplicando o preco com a quantidade */
    }
    printf("Custo da encomenda %d %d.\n", atoi(dados[0]), c);
}


/* Formato de entrada: p idp:preco */
/* Formato de saida: NADA (excepto erro) */
/* Erros: * no caso de nao existir nenhum produto criado com esse identificador */
/* Esta funcao altera o pre?o de um produto existente no sistema */
void altera_preco_produto() {
    char s[MAXINPUT];
    char dados[TIPOSDEDADOS][MAXSTR];
    read_line(s);
    split_string(s, dados);
    if (atoi(dados[0]) >= idp) { /* atoi(dados[0]) = id produto */
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", atoi(dados[0]));
        return;
   }
   inventario_produtos[atoi(dados[0])].preco_produto = atoi(dados[1]); /* atoi(dados[1]) = novo preco */
}


/* Formato de entrada: E ide:idp */
/* Formato de saida: <desc> <qtd>. onde <desc> e a descricao do produto <idp> e <qtd> e a quantidade desse produto na encomenda <ide> */
/* Erros: * no caso de nao existir nenhuma encomenda criada com esse identificador 
          * no caso de nao existir nenhum produto criado com esse identificador */
/* Esta funcao lista a descricao e a quantidade de um produto numa encomenda */
void descricao_quantidade() {
    int qtd = 0, i;
    char s[MAXINPUT];
    char dados[TIPOSDEDADOS][MAXSTR];
    read_line(s);
    split_string(s, dados);
    if (atoi(dados[0]) >= ide) { /* atoi(dados[0]) = id da encomenda */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(dados[0]));
        return;
    }
    else if (atoi(dados[1]) >= idp) { /* atoi(dados[1]) = id do produto */
        printf("Impossivel listar produto %d. Produto inexistente.\n", atoi(dados[1]));
        return;
    }
    for (i = 0; i < lista_encomendas[atoi(dados[0])].quantidade; i++) { /* Percorre todos os produtos ate encontrar o mesmo na encomenda */
        if (lista_encomendas[atoi(dados[0])].e[i].id_produto == atoi(dados[1])) { /* Verifica se encontramos o produto */
            qtd += lista_encomendas[atoi(dados[0])].e[i].stock_produto; /* Quando encontra ve a quantidade do produto */
        }
    }
    printf("%s %d.\n", inventario_produtos[atoi(dados[1])].desc_produto, qtd); 
}   


/* Formato de entrada: m idp */
/* Formato de saida: Maximo produto <idp> <ide> <qtd>. onde <ide> e o numero da encomenda em que <idp> ocorre mais vezes, sendo essa quantidade <qtd> */
/* Erros: * no caso de nao existir nenhum produto criado com esse identificador */
/* Esta funcao lista o identificador da encomenda em que o produto dado ocorre mais vezes. 
   Se houver 2 ou mais encomendas nessa situacao, devera imprimir a encomenda de menor id */
void lista_identificador() {
    int i = 0, e, x = 0, final = -10; /* A variavel "final" serve de controlo verificando
    se existe ou nao uma encomenda que tenha esse produto */
    char s[MAXINPUT];
    char dados[TIPOSDEDADOS][MAXSTR];
    read_line(s);
    split_string(s, dados);
    if (atoi(dados[0]) >= idp) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", atoi(dados[0]));
        return;
    }
    while (i < ide) { /* Percorre todas as encomendas */
        for (e = 0; e < lista_encomendas[i].quantidade; e++) {
            if (lista_encomendas[i].e[e].id_produto == atoi(dados[0])) {
                if (lista_encomendas[i].e[e].stock_produto > x) {
                    final = lista_encomendas[i].id_encomenda; /* Guarda os identificadores de encomendas ate
                     que chegue a encomenda com maior numero de produto */
                    x = lista_encomendas[i].e[e].stock_produto; /* Guarda a quantidade de produto na encomenda */
                }
            }
        }
        i++;
    }
    if (final >= 0) {
        printf("Maximo produto %d %d %d.\n", atoi(dados[0]), final, x);
    }
}


/* Recebe 2 vetores de produtos e 3 inteiros e auxilia a funcao m_s_1 a ordenar 
os produtos consoante a ordem crescente de precos */
void intercala_1(produto aux[], produto a[], int left, int m, int right) {
    int i, j, k;
    for (i = m + 1; i > left; i--) {
        aux[i - 1] = a[i - 1];
    }
    for (j = m; j < right; j++) {
        aux[right + m - j] = a[j + 1];
    }
    for (k = left; k <= right; k++){
        if ((aux[j].preco_produto < aux[i].preco_produto) || i > m) {
            a[k] = aux[j--];
        }
        else
            a[k] = aux[i++];
        /* Divisao do vetor inicial em vetores mais pequenos */
    }
}


/* Recebe dois vetores de produtos e 2 inteiros e chama recursivamente 
a funcao intercala_1 e ela propria */
void m_s_1(produto aux[], produto a[], int left, int right) {
    int m = (right + left) / 2; /* Local medio do vetor */
    if (right <= left) { 
        return;
    }
    m_s_1(aux, a, left, m);
    m_s_1(aux, a, m + 1, right);
    intercala_1(aux, a, left, m, right);
}


/* Formato de entrada: l */
/* Formato de saida: Um bloco no formato abaixo, e em que os produtos sao listados por ordem crescente de preco */
/* Erros: Nao aplicavel */
/* Esta funcao lista todos os produtos existentes no sistema por ordem crescente de preco. 
   Se houver 2 ou mais produtos com o mesmo preco, devera imprimir esses por ordem crescente de id de produto */
void auxiliar() {
    int i;
    produto aux[MAXPRODUTOS]; /* Inicializacao de um vetor auxiliar de produtos */
    produto final[MAXPRODUTOS]; /* Inicializacao de um vetor de produtos - copia do inventario de produtos*/
    for (i = 0; i < idp; i++){
        final[i] = inventario_produtos[i]; 
    }
    m_s_1(aux, final, 0, idp - 1);
    printf("Produtos\n");
    for (i = 0; i < idp; i++){
        printf("* %s %d %d\n", final[i].desc_produto, final[i].preco_produto, final[i].stock_produto);
    }
}


/* Recebe dois vetores de produtos e 3 inteiros e auxilia a funcao m_s_2 a ordenar 
os produtos consoante a ordem alfabetica dividindo o vetor original em vetores mais pequenos */
void intercala_2(produto aux[], produto a[], int left, int m, int right) {
    int i, j, k;
    for (i = m + 1; i > left; i--) {
        aux[i - 1] = a[i - 1];
    }
    for (j = m; j < right; j++) {
        aux[right + m - j] = a[j + 1];
    }
    for (k = left; k <= right; k++){
        if ((strcmp(aux[j].desc_produto, aux[i].desc_produto) < 0) || i > m) { /* Compara a ordem 
        consoante a tabela ASCII */
            a[k] = aux[j--];
        }
        else
            a[k] = aux[i++];
    }
}


/* Recebe dois vetores de produtos e dois inteiros chama recursivamente 
a funcao intercala_2 e ela propria */
void m_s_2(produto aux[], produto a[], int left, int right) {
    int m = (right + left) / 2;
    if (right <= left) {
        return;
    }
    m_s_2(aux, a, left, m);
    m_s_2(aux, a, m + 1, right);
    intercala_2(aux, a, left, m, right);
}


/* Formato de entrada: L <ide> */
/* Formato de saida: Um bloco no formato abaixo, e em que os produtos sao listados por ordem alfabetica de descricao */
/* Erros: * no caso de nao existir nenhuma encomenda criada com esse identificador */
/* Esta funcao lista todos os produtos de uma encomenda por ordem alfabetica da descricao  */
void auxiliar_2() {
    produto aux[MAXPESO]; /* Inicializacao de um vetor auxiliar de produtos */
    produto final[MAXPESO]; /* Inicializacao de um vetor de produtos - copia dos produtos da encomenda */
    int i;
    char s[MAXINPUT];
    char dados[TIPOSDEDADOS][MAXSTR];
    read_line(s);
    split_string(s, dados);
    if (atoi(dados[0]) >= ide) { /* atoi(dados[0]) = id da encomenda */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(dados[0]));
        return;
    }
    for (i = 0; i < lista_encomendas[atoi(dados[0])].quantidade; i++){
        final[i].id_produto = lista_encomendas[atoi(dados[0])].e[i].id_produto;
        final[i].stock_produto = lista_encomendas[atoi(dados[0])].e[i].stock_produto;
        final[i].preco_produto = lista_encomendas[atoi(dados[0])].e[i].preco_produto;
        strcpy(final[i].desc_produto, lista_encomendas[atoi(dados[0])].e[i].desc_produto);
    }
    m_s_2(aux, final, 0, lista_encomendas[atoi(dados[0])].quantidade - 1);
    printf("Encomenda %d\n", atoi(dados[0]));
    for (i = 0; i < lista_encomendas[atoi(dados[0])].quantidade; i++){ /* Percorre os produtos dentro da encomenda */
        if (final[i].stock_produto > 0) { /* Seleciona os que tiverem stock positivo */
            printf("* %s %d %d\n", final[i].desc_produto, inventario_produtos[final[i].id_produto].preco_produto, final[i].stock_produto);
        }
    }
}


/* Funcao geral que recebe um comando e direciona o utilizador consoante o mesmo */
int menu() {
    int run = 1; /* Variavel de controlo para garatir que quando introduzimos o
    comando "x" o ciclo termina e sai do programa */
    char operation;
    while (run == 1) {
        operation = getchar(); /* Guarda o comando numa variavel */
        if (operation != 'N')
            getchar(); /* Remove o espaco depois do comando exceto quando o comando e o "N" */
        switch (operation) {
            case 'a':
                adiciona_produto();
                break;
            case 'q':
                adiciona_stock();
                break;
            case 'N':
                cria_nova_encomenda();
                break;
            case 'A':
                adiciona_produto_encomenda();
                break;
            case 'r':
                remove_stock();
                break;
            case 'R':
                remove_produto_encomenda();
                break;
            case 'C':
                calcula_custo();
                break;
            case 'p':
                altera_preco_produto();
                break;
            case 'E':
                descricao_quantidade();
                break;
            case 'm':
                lista_identificador();
                break;
            case 'l':
                auxiliar();
                break;
            case 'L':
                auxiliar_2();
                break;            
            case 'x':
                run = 0; /* Faz o "update" da variavel de controlo */
                break;
        }
    }
    return 0;
}


/* Funcao principal que chama a funcao geral (menu) deste programa */
int main() {
    menu();
    return 0;
}

