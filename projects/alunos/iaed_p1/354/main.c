#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define MAX_IDP 10000   /*maximo de idp permitido*/
#define MAX_DES 63      /*maximo de caracteres das strigs*/
#define MAX_IDE 500     /*maximo de ide permitido*/
#define MAX_peso 200    /*maximo de peso permitido*/
#define exch(A, B) {produto t = A; A=B; B=t;}   /*metodo utilizado no quicksort*/

/*estrutura do produto com todos os seus constituintes*/
typedef struct {
    int idp;
    char descricao[MAX_DES];
    int preco;
    int peso;
    int qtd;
}produto;

/*estrutura da encomenda om todos os seus constituintes*/
typedef struct {
    int pes; /*peso da encomenda*/
    int qtd; /*quantidade de produtos colocados na encomenda*/
    produto enc[MAX_peso]; /*produtos da encomenda*/
}Encomenda;

Encomenda Enc_exis[MAX_IDE]; /*vector com todas as encomendas existentes*/
produto Prod_exis[MAX_IDP];  /*vector com todos os produtos do sistema*/
int idp_at = 0;              /*variaveis globais que guarda o ide e o idp atuais*/
int ide_at = 0;

/*Adiciona_Produto : adiciona um novo produto ao sistema criando um identificador para ele*/
void Adiciona_Produto() {
    produto pro; /*cria um novo produto que vai receber toda a informacao dada pelo utilizador*/
    scanf(" %[^:]:%d:%d:%d", pro.descricao, &pro.preco, &pro.peso, &pro.qtd);
    pro.idp = idp_at;
    Prod_exis[pro.idp] = pro; /*insere o novo produto na lista de produtos no sistema*/
    printf("Novo produto %d.\n", pro.idp);
}

/*Adiciona_Stock: verifica se um produto se encontra no sistema e se estiver coloca mais desse produto no sistema*/
void Adiciona_Stock() {
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    if (idp < idp_at) { /*verifica se o idp existe nos produtos ja existentes*/
        Prod_exis[idp].qtd += qtd;
    }
    else printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

/*Cria_Encomenda: cria uma nova encomenda*/
void Cria_Encomenda() {
    printf("Nova encomenda %d.\n", ide_at);
}

/*Encontrar indice do produto na encomenda*/
int Encontra_IP(Encomenda E, int idp) {
    int i;
    for (i = 0; i < E.qtd ; i++)
        if (E.enc[i].idp == idp) /*procura se numa encomenda ja existe um produto com o idp dado e se houver da o indice em que se encontra no vector*/
            return i;
    return -2; /*se nao encontra o produto retorna -2*/
}

/*Adiciona_Prod_Enc: adiciona o produto a ecomenda. se ja existir o produto aumenta a sua quantidade*/
void Adiciona_Prod_Enc() {
    int ide, idp, qtd;
    scanf("%d:%d:%d", &ide, &idp, &qtd);
    if (ide >= ide_at)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp >= idp_at)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (Prod_exis[idp].qtd - qtd < 0)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if (Enc_exis[ide].pes + (Prod_exis[idp].peso * qtd) > MAX_peso)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else if (Encontra_IP(Enc_exis[ide], idp) >= 0) { /*se encontrar o idp nos idps dos produtos dessa encomenda*/
        Enc_exis[ide].enc[Encontra_IP(Enc_exis[ide], idp)].qtd += qtd; /*aumenta a quantidade desse produto na encomenda*/
        Prod_exis[idp].qtd -= qtd; /*retira a quantidade do produto colocada na encomenda do sistema*/
        Enc_exis[ide].pes += (Prod_exis[idp].peso * qtd); /*atualiza o peso da encomenda*/
    }
    else {
        /*cria um produto copia do original do sistema apenas com a quantidade pedida e coloca o na encomenda*/
        produto p;
        p.idp = Prod_exis[idp].idp;
        strcpy(p.descricao, Prod_exis[idp].descricao);
        p.preco = Prod_exis[idp].preco;
        p.qtd = qtd;
        p.peso = Prod_exis[idp].peso;
        Prod_exis[idp].qtd -= qtd;/*retira a quantidade do produto colocada na encomenda do sistema*/
        Enc_exis[ide].enc[Enc_exis[ide].qtd] = p;
        Enc_exis[ide].pes += (Prod_exis[idp].peso * qtd); /*atualiza o peso da encomenda*/
        Enc_exis[ide].qtd++; /*atualiza a quantidade da encomenda*/
    }
}

/*Remove_Stock : remove o stock a um produto existente*/
void Remove_Stock() {
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    if (idp >= idp_at)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if (Prod_exis[idp].qtd - qtd < 0)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    else Prod_exis[idp].qtd -= qtd;
}

/*Remove_PE: remove um produto de uma encomenda*/
void Remove_PE() {
    int ide, idp, idpp;
    scanf("%d:%d", &ide, &idp);
    if (ide >= ide_at)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp >= idp_at)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else {
        if (Encontra_IP(Enc_exis[ide], idp) >= 0) { /*se encontrar o produto na encomenda*/
            idpp = Encontra_IP(Enc_exis[ide], idp); /*indice do produto na encomenda*/
            Prod_exis[idp].qtd += Enc_exis[ide].enc[idpp].qtd; /*volta a colocar a quantidade do produto no sistema*/
            Enc_exis[ide].pes -= (Enc_exis[ide].enc[idpp].qtd * Enc_exis[ide].enc[idpp].peso); /*dimminui o peso da encomenda*/
            Enc_exis[ide].enc[idpp].qtd = 0; /*retira o produto da encomenda*/
        }
    }
}

/*Custo_E: calcula o custo de uma encomenda*/
void Custo_E() {
    int ide, res, i;
    res = 0; /*preco da encomenda*/
    scanf("%d", &ide);
    if (ide >= ide_at)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else {
        for (i = 0; i < Enc_exis[ide].qtd; i++) /*calcula o preco de cada produto da encomenda*/
            res += (Enc_exis[ide].enc[i].preco * Enc_exis[ide].enc[i].qtd); /* soma na variavel res*/
        printf("Custo da encomenda %d %d.\n", ide, res);
    }
}

/*Altera_Preco: altera o preco de um produto existente no sistema*/
void Altera_Preco() {
    int idp, preco, i;
    scanf("%d:%d", &idp, &preco);
    if (idp >= idp_at)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else {
        Prod_exis[idp].preco = preco; /*altera o preco do produto no sistema*/
        for (i = 0; i < ide_at; i++) { /*altera o preco em cada uma das encomendas que teem esse produto*/
            if (Encontra_IP(Enc_exis[i], idp) >= 0)
                Enc_exis[i].enc[Encontra_IP(Enc_exis[i], idp)].preco = preco;
        }
    }
}

/*L_descricaoqtd: lista a descricao e a quantidade de um produto numa encomenda*/
void L_descricaoqtd() {
    int ide, idp, idpe;
    scanf("%d:%d", &ide, &idp);
    if (ide >= ide_at)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if (idp >= idp_at)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else {
        if (Encontra_IP(Enc_exis[ide], idp) >= 0) { /*se encontrar esse produto dentro da encomenda*/
            idpe = Encontra_IP(Enc_exis[ide], idp); /*indice em que o produto se encontra na encomenda*/
            printf("%s %d.\n", Enc_exis[ide].enc[idpe].descricao, Enc_exis[ide].enc[idpe].qtd);
        }
        else if (Encontra_IP(Enc_exis[ide], idp) == -2) /*se nao encontrar o produto na encomenda*/
            printf("%s %d.\n", Prod_exis[idp].descricao, 0);
    }
}

/*L_idep: lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
void L_idep() {
    int idp, i, max = 0, res = -1; /*inicializo as variaveis max e res correspondetes a quantidade maxima do produto numa encomenda e ao ide da encomenda respetivamente*/
    scanf("%d", &idp);
    if (idp >= idp_at)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else {
        for (i = 0; i < ide_at; i++)
            if (Encontra_IP(Enc_exis[i], idp) != -2) { /*se o produto existir na encomenda*/
                if (Enc_exis[i].enc[Encontra_IP(Enc_exis[i], idp)].qtd > max) { /*se a quantidade for maior do que em outras encomendas*/
                    max = Enc_exis[i].enc[Encontra_IP(Enc_exis[i], idp)].qtd; /*max passa a ser essa quantidade */
                    res = i; /*res passa a ter o ide dessa encomenda*/
                }
                else if (Enc_exis[i].enc[Encontra_IP(Enc_exis[i], idp)].qtd == max) /*se a quantidade for igual a maxima ja encontrada*/
                    if (i < res) /*verifica qual das duas tem o ide menor e res passa a ter o valor do ide menor*/
                        res = 1;
            }
        if (res >= 0)
            printf("Maximo produto %d %d %d.\n", idp, res, max);
    }
}

/*Quick Sort: algoritmo de ordenacao*/
int less(produto a, produto v, char o) {
    if (o == 'l') { /*se a tecla pressionada for 'l'*/
        if (a.preco == v.preco) /*se os precos dos produtos forem iguais*/
            return (a.idp < v.idp); /* e escolhido o que tem o idp menor*/
        return  (a.preco < v.preco); /*se nao e escolhido de ordem crescente de preco dos produtos*/
        }
    if (o == 'L') /*se a tecla pressionada for 'L'*/
        return (strcmp(a.descricao, v.descricao) < 0); /*compara as descricoes dos produtos da encomenda*/
    return 0;
}

int partition(produto a[], int l, int r, char o) {
    int i = l - 1;
    int j = r;
    produto v = a[r]; /*pivot*/
    while (i < j) {
        while (less(a[++i], v, o)); /*verifica o criterio de ordenacao do lado esquerdo do pivot*/
        while (less(v, a[--j], o))  /*verifica o criterio de ordenacao do lado direito do pivot*/
            if (j == l) /*caso em o pivot esta na primeira posicao do vector*/
                break;
        if (i < j) 
            exch(a[i], a[j]); /*faz a troca*/
    }
    exch(a[i], a[r]); /*coloca o pivot na sua posicao final*/
    return i; /*ponto onde partiu o vector*/
}

void quicksort(produto a[], int l, int r, char o) {
    int i;
    if (r <= l) return;
    i = partition(a, l, r, o);
    quicksort(a, l, i - 1, o);
    quicksort(a, i + 1, r, o);
}

/*L_Ppreco: lista todos os produtos existentes no sistema por ordem crescente de preco. caso tenha o mesmo preco ordena por identificador do produto.*/
void L_Ppreco() {
    int i;
    char o = 'l';
    produto copia[MAX_IDP];
    for (i = 0; i < idp_at; i++) /*faz uma copia dos produtos no sistema*/
        copia[i] = Prod_exis[i];
    quicksort(copia, 0, idp_at - 1, o); /*aplica a ordenacao a essa copia do sistema*/
    printf("Produtos\n");
    for (i = 0; i < idp_at; i++)
        printf("* %s %d %d\n", copia[i].descricao, copia[i].preco, copia[i].qtd);
}

/*L_PED: lista todos os produtos de uma encomenda por ordem alfab?tica da descricao*/
void L_PED() {
    int i,j=0, ide;
    char o = 'L';
    produto copia[MAX_IDP];
    scanf("%d", &ide);
    if (ide >= ide_at)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else {
        for (i = 0; i < Enc_exis[ide].qtd; i++) /*cria uma copia da encomenda sem os elementos que foram eliminados anteriormente*/
            if (Enc_exis[ide].enc[i].qtd != 0)
                copia[j++] = Enc_exis[ide].enc[i];
        quicksort(copia, 0, j-1, o); /*ordena essa copia*/
        printf("Encomenda %d\n", ide);
        for (i = 0; i<j; i++)
            printf("* %s %d %d\n", copia[i].descricao, copia[i].preco, copia[i].qtd);
    }
}

int main() {
    char tecla;
    while ((tecla = getchar()) != 'x' && tecla != EOF) {    /*verifica se a tecla obtida e um 'x' ou se chegou ao fim do ficheiro*/
        if (tecla != '\n')
            switch (tecla) {
            case ('a'):
                Adiciona_Produto(); /*adiciona um novo produto ao sistema criando um identificador para ele*/
                idp_at++;           /*atualiza valor do idp atual*/
                break;
            case ('q'):
                Adiciona_Stock();   /*verifica se um produto se encontra no sistema e se estiver coloca mais desse produto no sistema*/
                break;
            case ('N'):
                Cria_Encomenda();   /*cria uma nova encomenda*/
                ide_at++;           /*atualiza o valor do ide atual*/
                break;
            case ('A'):
                Adiciona_Prod_Enc();/*adiciona o produto a ecomenda. se ja existir o produto aumenta a sua quantidade*/
                break;
            case  ('r'):
                Remove_Stock();     /*remove o stock a um produto existente*/
                break;
            case ('R'):
                Remove_PE();        /*remove um produto de uma encomenda*/
                break;
            case ('C'):
                Custo_E();          /*calcula o custo de uma encomenda*/
                break;
            case ('p'):
                Altera_Preco();     /*altera o preco de um produto existente no sistema*/
                break;
            case ('E'):
                L_descricaoqtd();   /*lista a descricao e a quantidade de um produto numa encomenda*/
                break;
            case ('m'):
                L_idep();           /*lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
                break;
            case ('l'):
                L_Ppreco();         /*lista todos os produtos existentes no sistema por ordem crescente de preco. caso tenha o mesmo preco ordena por identificador do produto.*/
                break;
            case ('L'):
                L_PED();            /*lista todos os produtos de uma encomenda por ordem alfab?tica da descricao*/
                break;
            }
    }
    return 0;
}