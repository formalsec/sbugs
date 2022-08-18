#include <stdio.h>
#include <string.h>

/* Numero maximo de produtos no sistema e por encomenda, e de encomendas guardado */
#define MAX_PRODUTOS 10000
#define MAX_ENC_NUM 500
/* Maximo de peso por encomenda (tambem e o numero maximo de produtos por encomenda) */
#define MAX_ENC_PESO 200
/* Tamanho maximo de strings */
#define MAX_STRING 64 /* 63 + 1 (para contar com o '\0') */

/* Estrutura produto */
typedef struct produto {
    int id; /* Identificador do produto */
    char descricao[MAX_STRING];
    int preco;
    int peso;
    int qtd; /* Quantidade em stock */
} produto;

/* Estrutura encomenda */
typedef struct encomenda {
    produto prods[MAX_ENC_PESO]; /* Produtos da encomenda */
    int prod_num; /* Numero de produtos da encomenda */
    int id; /* Identificador da encomenda */
    int peso;
} encomenda;

/* Produtos em stock (vetor) */
produto armazem[MAX_PRODUTOS];

/* Vetor de encomendas */
encomenda pedidos[MAX_ENC_NUM];

/* Contadores de produtos e de encomendas */
int p_num, e_num;

/* Verifica se o produto existe dentro de uma encomenda */
int teste_produto_encomenda(int ide, int idp) {
    int i;
    for (i = 0; i < MAX_ENC_PESO; i++) {
        /* Se o id corresponder e o produto tiver sido inicializado ja */
        if (pedidos[ide].prods[i].id == idp && pedidos[ide].prods[i].peso != 0) {
            return i;
        }
    }
    /* Caso o produto nao exista na encomenda */
    return -1;
}

/* Verifica se a encomenda existe (1 se existir, 0 caso contrario) */
int teste_encomenda(int ide) {
    return (pedidos[ide].id == ide && e_num);
}

/* Verifica se o produto existe no sistema (1 se existir, 0 caso contrario) */
int teste_produto(int idp) {
    return (armazem[idp].id == idp && p_num);
}

/* Efetua o merge, de acordo com o preco */
void merge_preco(produto vetor[], int esq, int meio, int dir) {
    produto tmp[MAX_PRODUTOS];
    int i, j, k;
    /* Criacao do vetor auxiliar tmp (do meio para fora) */
    for (i = meio+1; i > esq; i--) {
        tmp[i-1] = vetor[i-1];
    }
    for (j = meio; j < dir; j++) {
        tmp[dir+meio-j] = vetor[j+1]; /* A ordem e inversa */
    }
    /* Ordenacao do vetor */
    for (k = esq; k <= dir; k++) {
        /* Criterio de comparacao: preco (para precos iguais, primeiro o que tem id menor) */
        if (tmp[j].preco < tmp[i].preco || (tmp[j].preco == tmp[i].preco && tmp[j].id < tmp[i].id)) {
            /* Associa ao vetor o valor de tmp[j], e decrementa j */
            vetor[k] = tmp[j--];
        } else {
            /* Associa ao vetor o valor de tmp[i], e incrementa i */
            vetor[k] = tmp[i++];
        }
    }
}

/* Efetua o merge, de acordo com o id */
void merge_id(produto vetor[], int esq, int meio, int dir) {
    produto tmp[MAX_PRODUTOS];
    int i, j, k;
    for (i = meio+1; i > esq; i--) {
        tmp[i-1] = vetor[i-1];
    }
    for (j = meio; j < dir; j++) {
        tmp[dir+meio-j] = vetor[j+1];
    }
    for (k = esq; k <= dir; k++) {
        /* Criterio de comparacao: id */
        if (tmp[j].id < tmp[i].id) {
            vetor[k] = tmp[j--];
        } else {
            vetor[k] = tmp[i++];
        }
    }
}

/* Efetua o merge, de acordo com o nome */
void merge_nome(produto vetor[], int esq, int meio, int dir) {
    produto tmp[MAX_PRODUTOS];
    int i, j, k;
    for (i = meio+1; i > esq; i--) {
        tmp[i-1] = vetor[i-1];
    }
    for (j = meio; j < dir; j++) {
        tmp[dir+meio-j] = vetor[j+1];
    }
    for (k = esq; k <= dir; k++) {
        /* Criterio de comparacao: descricao */
        if (strcmp(tmp[j].descricao, tmp[i].descricao) < 0) {
            vetor[k] = tmp[j--];
        } else {
            vetor[k] = tmp[i++];
        }
    }
}

/* Funcao principal do mergesort */
void mergesort(produto vetor[], int esq, int dir, int ctrl) {
    int meio = (dir+esq)/2;
    if (dir <= esq) {
        /* Caso o vetor tenha no maximo 1 elemento (condicao de paragem) */
        return;
    }
    /* Dividir a operacao recursivamente, ate a condicao de paragem acima */
    mergesort(vetor, esq, meio, ctrl);
    mergesort(vetor, meio+1, dir, ctrl);
    /* ctrl: 0 -> ordenacao por nome; 1 -> por preco; 2 -> por id */
    if (ctrl == 0) {
        merge_nome(vetor, esq, meio, dir);
        
    } else if (ctrl == 1) {
        merge_preco(vetor, esq, meio, dir);
    } else if (ctrl == 2) {
        merge_id(vetor, esq, meio, dir);
    }
}

/* Adiciona um novo produto ao sistema (comando 'a') */
void adicionar_produto_sistema(char descricao[], int preco, int peso, int qtd) {
    /* Copia da descricao */
    strcpy(armazem[p_num].descricao, descricao);
    /* Copia dos restantes parametros para o sistema */
    armazem[p_num].id = p_num;
    armazem[p_num].preco = preco;
    armazem[p_num].peso = peso;
    armazem[p_num].qtd = qtd;
    /* Saida da funcao */
    printf("Novo produto %d.\n", p_num);
    /* Atualizacao do numero de produtos no sistema */
    p_num++;
}

/* Adiciona stock a um produto existente no sistema (comando 'q') */
void adicionar_stock(int idp, int qtd) {
    /* Se o produto existir, adicionar stock */
    if (teste_produto(idp)) {
        armazem[idp].qtd += qtd;
    } else {
        /* Senao, dar erro */
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
}

/* Cria uma nova encomenda (comando 'N') */
void adicionar_encomenda() {
    pedidos[e_num].id = e_num;
    pedidos[e_num].peso = 0;
    pedidos[e_num].prod_num = 0;
    printf("Nova encomenda %d.\n", e_num);
    /* Incrementar a variavel para a proxima iteracao */
    e_num++;
}

/* Remove stock a um produto existente (comando 'r') */
void remove_stock(int idp, int qtd) {
    if (!teste_produto(idp)) {
        /* Se o produto nao existir */
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    } else {
        if ((armazem[idp].qtd - qtd) >= 0) {
            armazem[idp].qtd -= qtd;
        } else {
            /* Caso a quantidade no sistema fique <= 0 */
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        }
    }
}

/* Adiciona um produto a uma encomenda (comando 'A') */
void adicionar_produto_encomenda(int ide, int idp, int qtd) {
    int i;
    if (!teste_encomenda(ide)) {
        /* Se a encomenda nao existir */
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    } else if (!teste_produto(idp)) {
        /* Se o produto nao existir */
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    } else if (qtd > armazem[idp].qtd) {
        /* Se a quantidade em stock nao for suficiente */
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    } else if ((pedidos[ide].peso + (qtd * armazem[idp].peso)) > MAX_ENC_PESO) {
        /* Se o peso da encomenda ultrapassar as 200 unidades */
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }
    /* Se nao existir o produto na encomenda, colocar la nova entrada */
    if ((i = teste_produto_encomenda(ide, idp)) == -1) {
        i = pedidos[ide].prod_num;
        pedidos[ide].prods[i] = armazem[idp];
        pedidos[ide].prods[i].qtd = 0;
        /* Aumentar o contador de produtos da encomenda */
        pedidos[ide].prod_num++;
    }
    /* Atribuicao de valores */
    remove_stock(idp, qtd);
    pedidos[ide].prods[i].qtd += qtd;
    pedidos[ide].peso += (armazem[idp].peso * qtd);
}

/* Remove um produto de uma encomenda (comando 'R') */
void remove_produto_encomenda(int ide, int idp) {
    int i;
    if (!teste_encomenda(ide)) {
        /* Se a encomenda nao existir */
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    } else if (!teste_produto(idp)) {
        /* Se o produto nao existir em sistema */
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    } else {
        /*Se o produto nao existir na encomenda*/
        if ((i = teste_produto_encomenda(ide, idp)) != -1) {
            /* Alteracao de valores */
            pedidos[ide].peso -= (pedidos[ide].prods[i].qtd * pedidos[ide].prods[i].peso);
            armazem[idp].qtd += pedidos[ide].prods[i].qtd;
            /* Fazer shift dos produtos 1 para a esquerda */
            while (i < pedidos[ide].prod_num) {
                pedidos[ide].prods[i] = pedidos[ide].prods[i+1];
                i++;
            }
            /* Decrescimo do contador de produtos */
            pedidos[ide].prod_num--;
        }
    }
}

/* Calcula o custo de uma encomenda (comando 'C') */
void calcula_custo(int ide) {
    int i, total = 0;
    if (teste_encomenda(ide)) {
        for (i = 0; i < pedidos[ide].prod_num; i++) {
            total += (pedidos[ide].prods[i].preco * pedidos[ide].prods[i].qtd);
        }
        printf("Custo da encomenda %d %d.\n", ide, total);
    } else {
        /* Caso a encomenda nao exista */
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
}

/* Altera o pre?o de um produto existente no sistema (comando 'p') */
void altera_preco_produto(int idp, int preco) {
    int i, j;
    if (teste_produto(idp)) {
        /* Alterar o preco no vetor */
        armazem[idp].preco = preco;
        /* Alterar o preco nas encomendas */
        for (i = 0; i < e_num; i++) {
            if ((j = teste_produto_encomenda(i, idp)) != -1) {
                pedidos[i].prods[j].preco = preco;
            }
        }
    } else {
        /* Caso o produto nao exista */
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
}

/* Retorna a descri??o e a quantidade de um produto numa encomenda (comando 'E') */
void lista_produto_encomenda(int ide, int idp) {
    int i, qtd = 0;
    if (teste_encomenda(ide)) {
        if (teste_produto(idp)) {
            /* Se o produto existir na encomenda */
            if ((i = teste_produto_encomenda(ide, idp)) != -1) {
                qtd = pedidos[ide].prods[i].qtd;
            }
            printf("%s %d.\n", armazem[idp].descricao, qtd);
        } else {
            /* Caso o produto nao exista */
            printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        }
    } else {
        /* Caso a encomenda nao exista */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
}

/* Retorna a encomenda em que um produto ocorre mais vezes (comando 'm') */
void lista_produto_ocorremais(int idp) {
    int i, j, maior = -1, qtd = 0;
    if (!e_num) {
        /* Caso nao existam produtos */
        return;
    }
    if (teste_produto(idp)) {
        for (i = 0; i < e_num; i++) {
            /* Se existir o produto em maior quantidade na encomenda */
            if ((j = teste_produto_encomenda(i, idp)) != -1 && pedidos[i].prods[j].qtd > qtd) {
                qtd = pedidos[i].prods[j].qtd;
                maior = i;
            }
        }
        if (maior == -1) {
            /* Caso o valor nao se tenha alterado */
            return;
        } else {
            printf("Maximo produto %d %d %d.\n", idp, maior, qtd);
        }
    } else {
        /* Caso o produto nao exista */
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
}

/* Lista todos os produtos existentes no sistema por ordem crescente de pre?o (comando 'l') */
void lista_produtos_preco() {
    int i;
    /* Sort dos produtos pelo preco */
    mergesort(armazem, 0, p_num - 1, 1);
    /* Print pela nova ordem */
    printf("Produtos\n");
    i = 0;
    while(i < p_num) {
        printf("* %s %d %d\n", armazem[i].descricao, armazem[i].preco, armazem[i].qtd);
        i++;
    }
    /* Sort pelo id, para os produtos voltarem a ordem original */
    mergesort(armazem, 0, p_num - 1, 2);
}

/* Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o (comando 'L') */
void lista_encomenda_nome(int ide) {
    int i;
    if (teste_encomenda(ide)) {
        /* Sort dos produtos */
        mergesort(pedidos[ide].prods, 0, pedidos[ide].prod_num - 1, 0);
        /* Print pela nova ordem */
        printf("Encomenda %d\n", ide);
        i = 0;
        while(i < pedidos[ide].prod_num) {
            printf("* %s %d %d\n", pedidos[ide].prods[i].descricao, pedidos[ide].prods[i].preco, pedidos[ide].prods[i].qtd);
            i++;
        }
    } else {
        /* Caso a encomenda nao exista */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
}

int main() {
    /* Caracter correspondente a funcao desejada e argumentos para as funcoes */
    char s, arg1[MAX_STRING];
    int arg2, arg3, arg4;
    /* Segunda condicao de paragem */
    while ((s = getchar()) != EOF) {
        /* Interpretador dos Casos dados */
        switch (s) {
            case 'a':
                getchar(); /* Para eliminar o espaco do proximo scanf */
                scanf("%63[^:]:%d:%d:%d", arg1, &arg2, &arg3, &arg4);
                adicionar_produto_sistema(arg1, arg2, arg3, arg4);
                break;
            
            case 'q':
                scanf("%d:%d", &arg2, &arg3);
                adicionar_stock(arg2, arg3);
                break;
            
            case 'N':
                adicionar_encomenda();
                break;
            
            case 'A':
                scanf("%d:%d:%d", &arg2, &arg3, &arg4);
                adicionar_produto_encomenda(arg2, arg3, arg4);
                break;
            
            case 'r':
                scanf("%d:%d", &arg2, &arg3);
                remove_stock(arg2, arg3);
                break;
            
            case 'R':
                scanf("%d:%d", &arg2, &arg3);
                remove_produto_encomenda(arg2, arg3);
                break;
            
            case 'C':
                scanf("%d", &arg2);
                calcula_custo(arg2);
                break;
            
            case 'p':
                scanf("%d:%d", &arg2, &arg3);
                altera_preco_produto(arg2, arg3);
                break;
            
            case 'E':
                scanf("%d:%d", &arg2, &arg3);
                lista_produto_encomenda(arg2, arg3);
                break;
            
            case 'm':
                scanf("%d", &arg2);
                lista_produto_ocorremais(arg2);
                break;
            
            case 'l':
                lista_produtos_preco();
                break;
            
            case 'L':
                scanf("%d", &arg2);
                lista_encomenda_nome(arg2);
                break;
            
            case 'x':
                /* Primeira condicao de paragem */
                return 0;
            
            default:
                break;
        }
        getchar();
    }
    return 0;
}