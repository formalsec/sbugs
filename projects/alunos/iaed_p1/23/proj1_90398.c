#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCOMA 100   /* Numero maximo de carateres de um comando */
#define MAXDESC 64    /* Numero maximo de carateres da descricao de um produto */
#define MAXPROD 10000 /* Numero maximo de produtos diferentes no sistema */
#define T_ENCOM 200   /* Tamanho maximo de cada encomenda (em produtos) */
#define MAXENCOM 500  /* Numero maximo de encomendas */

typedef struct produto {
    int id;
    char descricao[MAXDESC];
    int preco; 
    int peso; 
    int quantidade; 
} produto;

typedef struct encomenda {
    int id;
    produto produtos[T_ENCOM];
    int tamanho;
    int peso;
} encomenda;

int i;                          /* Variavel para "memorizar" o sitio no comando */
int idp;                        /* Identificador do produto (total de produtos) */
int ide;                        /* Identificador de uma encomenda (total de encomendas) */
int haEncomendas;               /* Flag que marca a adicao da primeira encomenda ah lista de encomendas */
int haProdutos;                 /* Flag que marca a adicao do primeiro produto ao sistema */
int tamanhoProdutosAOrdenar_L;  /* Tamanho do array ProdutosAOrdenar_L usado na funcao do comando 'L' */

/* Array de produtos que compoe o sistema */
produto sistema[MAXPROD];
/* Array de encomendas que compoe a "lista" de encomendas */
encomenda encomendas[MAXENCOM];
/* Array que vai ser ordenado na funcao do comando 'l' */
produto ProdutosAOrdenar_l[MAXPROD];
/* Array que vai ser ordenado na funcao do comando 'L' */
produto ProdutosAOrdenar_L[T_ENCOM];

void analisarComando(char comando[]);
void funcao_a(char comando[]);
void funcao_q(char comando[]);
void funcao_N();
void funcao_A(char comando[]);
void funcao_r(char comando[]);
void funcao_R(char comando[]);
void funcao_C(char comando[]);
void funcao_p(char comando[]);
void funcao_E(char comando[]);
void funcao_m(char comando[]);
void funcao_l();
void funcao_L(char comando[]);

int obtemNumero(char comando[]);
int produtoEmEncomenda(int idE, int idP);
int produtoEmEncomendas(int idP);
int encomendaExiste(int idE);
int produtoExiste(int idP);
int testaStock(int idP, int qtd);
int testaPeso(int idE, int idP, int qtd);
void alteraPrecoProdutoNasEncomendas(int idP, int novoPreco);
int obtemPosProduto(int nEncomenda, int idP);
int encomendaComMaisProduto(int idP);
void copiaString(char s1[], char s2[]);

/* Para a funcao_l */
void ordenaProdutos_l(int esquerda, int direita);
int particaoProdutos_l(int esquerda, int direita);
int menor_l(produto p1, produto p2);
void troca_l(int id1, int id2);

/* Para a funcao_L */
void ordenaProdutos_L(int esquerda, int direita);
int particaoProdutos_L(int esquerda, int direita);
int menor_L(produto p1, produto p2);
void troca_L(int id1, int id2);
void lower(char string[]);

/* Le comandos dados pelo utilizador e age sobre o sistema de logistica */
int main() { 
    char comando[MAXCOMA];
    int c, j;

    /* Mantem o programa a funcionar ate o comando 'x' */
    while (1) {
        c = getchar();
        j = 0;

        /* Obtem um comando */
        while (c != '\n' && c != EOF) {
            comando[j] = c;
            c = getchar();
            j++;
        }
        comando[j] = '\0';

        /* Para o programa com o comando 'x' */
        if (comando[0] == 'x') {
            return 0;
        }
        else {
            analisarComando(comando);
        }
    }
    return 0;
}

/* Le comando e age em concordancia */
void analisarComando(char comando[]) { 
    /* Faz reset da posicao dentro do comando (i) */  
    i = 0;

    switch (comando[0]) {
        case 'a':
            funcao_a(comando);
            break;
        case 'q':
            funcao_q(comando);
            break;
        case 'N':
            funcao_N(comando);
            break;
        case 'A':
            funcao_A(comando);
            break;
        case 'r':
            funcao_r(comando);
            break;
        case 'R':
            funcao_R(comando);
            break;
        case 'C':
            funcao_C(comando);
            break;
        case 'p':
            funcao_p(comando);
            break;
        case 'E':
            funcao_E(comando);
            break;
        case 'm':
            funcao_m(comando);
            break;
        case 'l':
            funcao_l(comando);
            break;
        case 'L':
            funcao_L(comando);
            break;
        default:
            break;
    }
}

/* Adiciona um novo produto ao sistema */
void funcao_a(char comando[]) {
    produto novoProduto;
    char descricao[MAXDESC];

    /* Obtem a descricao */
    i = 2;
    while (comando[i] != ':') {
        descricao[i-2] = comando[i];
        i++;
    }
    descricao[i-2] = '\0';

    /* Faz com que o idp nao seja incrementado com a adicao do primeiro produto */
    if (haProdutos) {
        idp++;
    }

    /* Cria o novo produto */
    novoProduto.id = idp;
    copiaString(novoProduto.descricao, descricao);  /* Atribui a descricao ao produto */
    novoProduto.preco = obtemNumero(comando);
    novoProduto.peso = obtemNumero(comando);
    novoProduto.quantidade = obtemNumero(comando);

    /* Introduz o novo produto no sistema */
    sistema[idp] = novoProduto;

    /* Ativa permanentemente a flag 'haProdutos' */
    haProdutos = 1;

    /* Output */
    printf("Novo produto %d.\n", idp);    
}

/* Adiciona stock a um produto existente no sistema */
void funcao_q(char comando[]) {
    int idP = obtemNumero(comando);
    int qtd = obtemNumero(comando);
                
    /* Testa a existencia do produto no sistema */
    if (produtoExiste(idP) && haProdutos) {
        sistema[idP].quantidade += qtd;
    }
    else {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idP);
    }
}

/* Cria uma nova encomenda */
void funcao_N() {
    encomenda novaEncomenda;

    /* Faz com que o ide nao seja incrementado com a adicao da primeira encomenda */
    if (haEncomendas) {
        ide++;
    }

    /* Cria a nova encomenda */
    novaEncomenda.id = ide;
    novaEncomenda.peso = 0;
    novaEncomenda.tamanho = 0;

    /* Introduz a nova encomenda na lista de encomendas */
    encomendas[ide] = novaEncomenda;

    /* Ativa permanentemente a flag 'haEncomendas' */
    haEncomendas = 1;

    /* Output */
    printf("Nova encomenda %d.\n", ide);
}

/* Adiciona um produto a uma encomenda. Se o produto j? existir na 
encomenda, adiciona a nova quantidade ? quantidade existente */
void funcao_A(char comando[]) {
    int tamanho;
    int posProd;
    produto novoProduto;

    int idE = obtemNumero(comando);
    int idP = obtemNumero(comando);
    int qtd = obtemNumero(comando);

    if (encomendaExiste(idE) && haEncomendas) {
        if (produtoExiste(idP) && haProdutos) {
            tamanho = encomendas[idE].tamanho;

            if (testaStock(idP, qtd)) {
                if (testaPeso(idE, idP, qtd)) {
                    if (produtoEmEncomenda(idE, idP)) {
                        posProd = obtemPosProduto(idE, idP);
                        encomendas[idE].produtos[posProd].quantidade += qtd;
                    }
                    /* Se o produto nao existir na encomenda */
                    else {
                        novoProduto.id = idP;
                        copiaString(novoProduto.descricao, sistema[idP].descricao);
                        novoProduto.preco = sistema[idP].preco;
                        novoProduto.peso = sistema[idP].peso;
                        novoProduto.quantidade = qtd;

                        encomendas[idE].produtos[tamanho] = novoProduto;
                        encomendas[idE].tamanho += 1;
                    }
                    sistema[idP].quantidade -= qtd;
                    encomendas[idE].peso += (qtd * sistema[idP].peso);
                }
                /* Se peso a ser adicionado faz exceder peso maximo de uma encomenda */
                else {
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idP, idE);
                }
            }
            /* Se nao existir quantidade de produto suficiente no stock do sistema */
            else {
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idP, idE);    
            }
        }
        /* Se o produto nao existe no sistema */
        else {
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idP, idE);
        }
    }
    /* Se encomenda nao existe na lista de encomendas */
    else {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idP, idE);
    }
}

/* Remove stock a um produto existente no sistema */
void funcao_r(char comando[]) {
    int idP = obtemNumero(comando);
    int qtd = obtemNumero(comando);

    if (produtoExiste(idP) && haProdutos) {
        if (testaStock(idP, qtd)) {
            sistema[idP].quantidade -= qtd;
        }
        /* Se nao existe produto suficiente em stock */
        else {
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idP);
        }
    }
    /* Se o produto nao existe no sistema */
    else {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idP);
    }
}

/* Remove um produto de uma encomenda */
void funcao_R(char comando[]) {
    int idE = obtemNumero(comando);
    int idP = obtemNumero(comando);
    int qtd;
    int posProd;

    if (encomendaExiste(idE) && haEncomendas) {
        if (produtoExiste(idP) && haProdutos) {
            /* Remover o produto da encomenda corresponde a lhe dar o id -1 */
            if (produtoEmEncomenda(idE, idP)) {
                posProd = obtemPosProduto(idE, idP);
                qtd = encomendas[idE].produtos[posProd].quantidade;

                /* "Limpa" o produto da encomenda */
                encomendas[idE].produtos[posProd].id = -1;
                encomendas[idE].produtos[posProd].quantidade = 0;
                encomendas[idE].peso -= (sistema[idP].peso * qtd);

                /* Repoe stock do produto no sistema */
                sistema[idP].quantidade += qtd;
            }
            else {
                return;
            }
        }
        /* Se o produto nao existe no sistema */
        else {
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idP, idE);
        }
    }
    /* Se a encomenda nao existe na lista de encomendas */
    else {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idP, idE);
    }
}

/* Calcula o custo de uma encomenda */
void funcao_C(char comando[]) {
    int idE = obtemNumero(comando);
    int j, tamanho;
    int custo = 0;

    if (encomendaExiste(idE) && haEncomendas) {
        tamanho = encomendas[idE].tamanho;

        for (j = 0; j < tamanho; j++) {
            if (encomendas[idE].produtos[j].id > -1) {
                custo += (encomendas[idE].produtos[j].preco * encomendas[idE].produtos[j].quantidade);
            }
        }
        /* Output */
        printf("Custo da encomenda %d %d.\n", idE, custo);
    }
    /* Se a encomenda nao existe na lista de encomendas */
    else {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idE);
    }
}

/* Altera o preco de um produto existente no sistema */
void funcao_p(char comando[]) {
    int idP = obtemNumero(comando);
    int novoPreco = obtemNumero(comando);

    if (produtoExiste(idP) && haProdutos) {
        sistema[idP].preco = novoPreco;
        alteraPrecoProdutoNasEncomendas(idP, novoPreco);
    }
    /* Se o produto nao existe no sistema */
    else {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idP);
    }
}

/* Lista a descricao e a quantidade de um produto numa encomenda */
void funcao_E(char comando[]) {
    int idE = obtemNumero(comando);
    int idP = obtemNumero(comando);
    int posProd;

    if (encomendaExiste(idE) && haEncomendas) {
        if (produtoExiste(idP) && haProdutos) {
            if (produtoEmEncomenda(idE, idP)) {
                posProd = obtemPosProduto(idE, idP);
                printf("%s %d.\n", sistema[idP].descricao, encomendas[idE].produtos[posProd].quantidade);
            }
            else {
                printf("%s 0.\n", sistema[idP].descricao);
            }
        }
        /* Se o produto nao existe no sistema */
        else {
            printf("Impossivel listar produto %d. Produto inexistente.\n", idP);
            return;
        }
    }
    /* Se encomenda nao existe na lista de encomendas */
    else {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idE);
        return;
    }
}

/* Lista o identificador da encomenda com maior quantidade de produto */
void funcao_m(char comando[]) {
    int idP = obtemNumero(comando);
    int indiceResultado;
    int qtd;
    int posProd;

    if (haEncomendas) {
        if (produtoExiste(idP) && haProdutos) {
            if (produtoEmEncomendas(idP)) {
                indiceResultado = encomendaComMaisProduto(idP);
                posProd = obtemPosProduto(indiceResultado, idP);
                qtd = encomendas[indiceResultado].produtos[posProd].quantidade;

                printf("Maximo produto %d %d %d.\n", idP, indiceResultado, qtd);
            }
            /* Se o produto nao ocorre em nenhuma encomenda */
            else {
                return;
            }
        }
        /* Se o produto nao existe no sistema */
        else {
            printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idP);
        }
    }
    /* Se nao existem encomendas no sistema */
    else {
        return;
    }
}

/* Lista todos os produtos existentes no sistema por ordem crescente de preco */
void funcao_l() {
    int j;

    if (haProdutos) {
        /* Copiar sistema[] para ProdutosAOrdenar_l[] */
        for (j = 0; j < idp + 1; j++) {
            produto novoProduto; 

            novoProduto.id = sistema[j].id;
            copiaString(novoProduto.descricao, sistema[j].descricao);
            novoProduto.preco = sistema[j].preco;
            novoProduto.quantidade = sistema[j].quantidade;

            ProdutosAOrdenar_l[j] = novoProduto;
        }
        /* Ordenar produtos por ordem crescente de preco com quicksort */
        ordenaProdutos_l(0, idp);
    }

    /* Output */
    printf("Produtos\n");
    if (haProdutos) {
        for (j = 0; j < idp + 1; j++) {
            printf("* %s %d %d\n", ProdutosAOrdenar_l[j].descricao, ProdutosAOrdenar_l[j].preco, ProdutosAOrdenar_l[j].quantidade);
        }
    }
}

/* Lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
void funcao_L(char comando[]) {
    int idE;
    int tamanho;
    int j;

    idE = obtemNumero(comando);

    if (encomendaExiste(idE) && haEncomendas) {
        tamanho = encomendas[idE].tamanho;

        if (tamanho > 0) {
            /* Faz reset do tamanho do array ProdutosAOrdenar_L */
            tamanhoProdutosAOrdenar_L = 0;

            /* Copiar encomendas[idE].produtos[] para ProdutosAOrdenar_L[] */
            for (j = 0; j < tamanho; j++) {
                produto novoProduto; 

                novoProduto.id = encomendas[idE].produtos[j].id;
                copiaString(novoProduto.descricao, encomendas[idE].produtos[j].descricao);
                novoProduto.preco = encomendas[idE].produtos[j].preco;
                novoProduto.quantidade = encomendas[idE].produtos[j].quantidade;

                ProdutosAOrdenar_L[j] = novoProduto;
                tamanhoProdutosAOrdenar_L++;
            }
            /* Ordenar alfabeticamente produtos da encomenda com quicksort */
            ordenaProdutos_L(0, tamanhoProdutosAOrdenar_L - 1);

            /* Output */
            printf("Encomenda %d\n", idE);
            for (j = 0; j < tamanhoProdutosAOrdenar_L; j++) {
                /* Se o produto nao tiver sido removido da encomenda */
                if (ProdutosAOrdenar_L[j].id > -1) {
                    printf("* %s %d %d\n", ProdutosAOrdenar_L[j].descricao,
                                           ProdutosAOrdenar_L[j].preco,
                                           ProdutosAOrdenar_L[j].quantidade);
                }
            }
        }
        /* Se a encomenda nao tiver produtos */
        else {
            /* Output */
            printf("Encomenda %d\n", idE);
        }
    }
    /* Se a encomenda nao existir na lista de encomendas */
    else {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idE);
    }
}


/* Le e retorna o numero seguinte da string comando usando a variavel global i */
int obtemNumero(char comando[]) {
    int j = 0;
    char arrayNumero[MAXCOMA];

    while (comando[i] < '0' || comando[i] > '9') {
        i++;
    }
    while (comando[i] >= '0' && comando[i] <= '9') {
        arrayNumero[j] = comando[i];
        i++;
        j++;
    }
    arrayNumero[j] = '\0';
    return atoi(arrayNumero);
}

/* Testa a existencia de um produto numa encomenda */
int produtoEmEncomenda(int idE, int idP) {
    int j;
    int tamanho = encomendas[idE].tamanho;

    /* Para cada produto j na encomenda idE */
    for (j = 0; j < tamanho; j++) {
        if (encomendas[idE].produtos[j].id == idP) {
            return 1;
        }
    }
    return 0;
}

/* Testa a existencia de um dado produto em todas as encomendas */
int produtoEmEncomendas(int idP) {
    int j = 0;

    /* Para cada encomenda j */
    for (j = 0; j < ide + 1; j++) {
        if (produtoEmEncomenda(j, idP)) {
            return 1;
        }
    }
    return 0;
}

/* Testa a existencia da encomenda idE na lista de encomendas */
int encomendaExiste(int idE) {
    return (haEncomendas && idE <= ide);
}

/* Testa a existencia do produto idP no sistema */
int produtoExiste(int idP) {
    return (haProdutos && idP <= idp);
}

/* Testa suficiencia de produto idP em stock no sistema */
int testaStock(int idP, int qtd) {
    return (sistema[idP].quantidade >= qtd);
}

/* Testa se peso adicionado ah encomenda idE nao excede o maximo de 200 */
int testaPeso(int idE, int idP, int qtd) {
    int pesoAdicionado = sistema[idP].peso *  qtd;
    return ((encomendas[idE].peso + pesoAdicionado) <= 200);
}

/* Altera o preco de um produto em todas as encomendas da lista de encomendas */
void alteraPrecoProdutoNasEncomendas(int idP, int novoPreco) {
    int j, k;

    /* Para cada encomenda j da lista de encomendas */
    for (j = 0; j < ide + 1; j++) {
        /* Para cada produto k na encomenda j */
        for (k = 0; k < encomendas[j].tamanho; k++) {
            if (encomendas[j].produtos[k].id == idP) {
                encomendas[j].produtos[k].preco = novoPreco;
            }
        }
    }
}

/* Obtem a posicao de um produto numa encomenda */
int obtemPosProduto(int idE, int idP) {
    int tamanho = encomendas[idE].tamanho;
    int j;

    /* Para cada produto j na encomenda idE */
    for (j = 0; j < tamanho; j++) {
        if (encomendas[idE].produtos[j].id == idP) {
            return j;
        }
    }
    return 0;
}

/* Obtem o identificador da encomenda com maior quantidade de produto idP */
int encomendaComMaisProduto(int idP) {
    int max = -1;
    int j;
    int indiceResultado = 0;
    int posProduto;

    /* Para cada encomenda j */
    for (j = 0; j < ide + 1; j++) {
        /* Obtem a posicao que o produto idP ocupa em cada encomenda */
        if (produtoEmEncomenda(j, idP)) {
                posProduto = obtemPosProduto(j, idP);
        }
        else {
            continue;
        }
        /* Se o produto nao foi removido e se a sua quantidade eh maior que o maximo anterior */
        if (encomendas[j].produtos[posProduto].id > -1 && encomendas[j].produtos[posProduto].quantidade > max) {
            max = encomendas[j].produtos[posProduto].quantidade;
            indiceResultado = j;
        }
    }
    return indiceResultado;
}

/* Ordena produtos por ordem crescente de preco usando quicksort */
void ordenaProdutos_l(int esquerda, int direita) {
    int k;

    if (direita <= esquerda) {
        return;
    }

    k = particaoProdutos_l(esquerda, direita);

    ordenaProdutos_l(esquerda, k-1);
    ordenaProdutos_l(k+1, direita);
}

/* Divide array de produtos ordenando ambas as metades em
maiores e menores que o pivot e retornando a sua posicao */
int particaoProdutos_l(int esquerda, int direita) {
    int k = esquerda - 1;
    int j = direita;
    produto pivot = ProdutosAOrdenar_l[direita];

    while (k < j) {
        while (menor_l(ProdutosAOrdenar_l[++k], pivot));
        while (menor_l(pivot, ProdutosAOrdenar_l[--j])) {
            if (j == esquerda) {
                break;
            }
        }
        if (k < j) {
            troca_l(k, j);
        }
    }
    troca_l(k, direita);
    return k;
}

/* Testa se preco do p1 eh menor que o preco do p2 */
int menor_l(produto p1, produto p2) {
    if (p1.preco < p2.preco) {
        return 1;
    }
    else if (p1.preco == p2.preco) {
        return p1.id < p2.id;
    }
    else {
        return 0;
    }
}

/* Troca o id1 com o id2 no array ProdutosAOrdenar_l */
void troca_l(int id1, int id2) {
    int auxID1;
    char auxDesc1[MAXDESC];
    int auxPreco1;
    int auxQuantidade1;

    /* Cria variaveis auxiliares */
    auxID1 = ProdutosAOrdenar_l[id1].id;
    copiaString(auxDesc1, ProdutosAOrdenar_l[id1].descricao);
    auxPreco1 = ProdutosAOrdenar_l[id1].preco;
    auxQuantidade1 = ProdutosAOrdenar_l[id1].quantidade;

    /* Copia produto2 para produto1 */
    ProdutosAOrdenar_l[id1].id = ProdutosAOrdenar_l[id2].id;
    copiaString(ProdutosAOrdenar_l[id1].descricao, ProdutosAOrdenar_l[id2].descricao);
    ProdutosAOrdenar_l[id1].preco = ProdutosAOrdenar_l[id2].preco;
    ProdutosAOrdenar_l[id1].quantidade = ProdutosAOrdenar_l[id2].quantidade;

    /* Copia produto1 para produto2 */
    ProdutosAOrdenar_l[id2].id = auxID1;
    copiaString(ProdutosAOrdenar_l[id2].descricao, auxDesc1);
    ProdutosAOrdenar_l[id2].preco = auxPreco1;
    ProdutosAOrdenar_l[id2].quantidade = auxQuantidade1;    
}

/* Ordena os produtos de uma encomenda por ordem alfabetica da descricao usando quicksort */
void ordenaProdutos_L(int esquerda, int direita) {
    int k;

    if (direita <= esquerda) {
        return;
    }

    k = particaoProdutos_L(esquerda, direita);

    ordenaProdutos_L(esquerda, k-1);
    ordenaProdutos_L(k+1, direita);
}

/* Divide array de produtos ordenando alfabeticamente ambas as metades em maiores
e menores que o pivot (alfabeticamente) e retornando a sua posicao */
int particaoProdutos_L(int esquerda, int direita) {
    int k = esquerda - 1;
    int j = direita;
    produto pivot = ProdutosAOrdenar_L[direita];

    while (k < j) {
        while (menor_L(ProdutosAOrdenar_L[++k], pivot));
        while (menor_L(pivot, ProdutosAOrdenar_L[--j])) {
            if (j == esquerda) {
                break;
            }
        }
        if (k < j) {
            troca_L(k, j);
        }
    }
    troca_L(k, direita);
    return k;
}

/* Testa se descricao do p1 vem alfabeticamente antes da do p2 */
int menor_L(produto p1, produto p2) {
    int j = 0;
    char desc1[MAXDESC], desc2[MAXDESC];
    int len1, len2;

    copiaString(desc1, p1.descricao);
    copiaString(desc2, p2.descricao);

    len1 = strlen(desc1);
    len2 = strlen(desc2);
    
    /* Transforma a copia das strings em lowercase para a ordenacao */
    lower(desc1);
    lower(desc2);

    if (len1 == len2) {
        for (j = 0; j < len1; j++) {
            if (desc1[j] < desc2[j]) {
                return 1;
            }
            else if (desc1[j] > desc2[j]) {
                return 0;
            }
        }
        return 0;
    }
    else if (len1 < len2) {
        for (j = 0; j < len1; j++) {
            if (desc1[j] < desc2[j]) {
                return 1;
            }
            else if (desc1[j] > desc2[j]) {
                return 0;
            }
        }
        return 1;
    }
    else if (len1 > len2) {
        for (j = 0; j < len2; j++) {
            if (desc1[j] < desc2[j]) {
                return 1;
            }
            else if (desc1[j] > desc2[j]) {
                return 0;
            }
        }
        return 0;
    }
    return 0;
}


/* Troca o produto na posicao pos1 com o produto na posicao pos2 no array ProdutosAOrdenar_L */
void troca_L(int pos1, int pos2) {
    int auxID1;
    char auxDesc1[MAXDESC];
    int auxPreco1;
    int auxPeso1;
    int auxQuantidade1;

    /* Cria variaveis auxiliares */
    auxID1 = ProdutosAOrdenar_L[pos1].id;
    copiaString(auxDesc1, ProdutosAOrdenar_L[pos1].descricao);
    auxPreco1 = ProdutosAOrdenar_L[pos1].preco;
    auxPeso1 = ProdutosAOrdenar_L[pos1].peso;
    auxQuantidade1 = ProdutosAOrdenar_L[pos1].quantidade;

    /* Copia produto2 para produto1 */
    ProdutosAOrdenar_L[pos1].id = ProdutosAOrdenar_L[pos2].id;
    copiaString(ProdutosAOrdenar_L[pos1].descricao, ProdutosAOrdenar_L[pos2].descricao);
    ProdutosAOrdenar_L[pos1].preco = ProdutosAOrdenar_L[pos2].preco;
    ProdutosAOrdenar_L[pos1].peso = ProdutosAOrdenar_L[pos2].peso;
    ProdutosAOrdenar_L[pos1].quantidade = ProdutosAOrdenar_L[pos2].quantidade;

    /* Copia produto1 para produto2 */
    ProdutosAOrdenar_L[pos2].id = auxID1;
    copiaString(ProdutosAOrdenar_L[pos2].descricao, auxDesc1);
    ProdutosAOrdenar_L[pos2].preco = auxPreco1;
    ProdutosAOrdenar_L[pos2].peso = auxPeso1;
    ProdutosAOrdenar_L[pos2].quantidade = auxQuantidade1;
}

/* Transforma uma string em lowercase */
void lower(char string[]) {
    int j = 0;

    while (string[j] != '\0') {
        /* Se carater for um numero nao faz nada */
        if (string[j] >= '0' && string[j] <= '9') {
            j++;
            continue;
        }
        if (string[j] >= 'A' && string[j] <= 'Z') {
            string[j] += 'a' - 'A';
        }
        j++;
    }
}

/* Copia a string s2 (origem) para a string s1 (destino) */
void copiaString(char s1[], char s2[]) {
    int j = 0;

    for (j = 0; s2[j] != '\0'; j++) {
        s1[j] = s2[j];
    }
    s1[j] = '\0';
}
