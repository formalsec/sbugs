#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/*defini as constantes que serao necessarias*/
#define MAXCHAR 63
#define MAXIDP 10000
#define MAXIDE 500
#define MAXPESO 200


/*criar a estrutura produto*/
typedef struct produto {
    int identP;
    char descricao[MAXCHAR];
    int preco;
    int peso;
    int qtd;
} produto;

/*criar a estrutura item, que sera utilizado na estrutura encomenda*/
typedef struct item {
    int identP;
    int qtd;
} item;

/*criar a estrutura encomenda*/
typedef struct encomenda {
    item prod[MAXIDP];
    int identE;
    int peso;
} encomenda;

 /*declaracao das variaveis globais, que serao utilizadas ao
 longo de todo o codigo*/
int idp = 0;
int ide = 0;
produto prod[MAXIDP];
encomenda encom[MAXIDE];


/*verifica o maior de dois precos*/
int comparadorProdutos(int a, int b) {
    return prod[a].preco <= prod[b].preco;
}

/*verifica o caracter que vem primeiro alfabeticamente, utilizando
a biblioteca de strings*/
int comparadorProdutosEncomenda(int a, int b) {
    return strcmp(prod[a].descricao, prod[b].descricao) <= 0;
}

/*adicionara um produto ao sistema, por ordem
crescente comecando em 0*/
void AdicionaProduto() {
    scanf(" %[^:]:%d:%d:%d", prod[idp].descricao, &prod[idp].preco,
          &prod[idp].peso, &prod[idp].qtd);

    prod[idp].identP = idp;
    printf("Novo produto %d.\n", prod[idp].identP);
    idp++;
}

/*adiciona stock ao produto caso seja possivel*/
void AdicionaStock() {
    int identificadorP, quantidade;
    scanf("%d:%d", &identificadorP, &quantidade);

    /*verifica se o produto nao existe*/
    if (identificadorP >= idp) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",
               identificadorP);
    } else {
        /*caso exista  adiciona a quantidade nova ah existeste*/
        prod[identificadorP].qtd += quantidade;
    }
}

/*cria a encomenda, sendo que o ide comeca em 0 e cresce de unidade
 em unidade*/
void CriaEncomenda() {
    encom[ide].identE = ide;
    printf("Nova encomenda %d.\n", ide);
    ide++;
}

/*adiciona um produto a uma encomenda, caso o mesmo seja possivel*/
void AdicionaProdutoEncomenda() {
    int identificadorP, identificadorE, quantidade;
    int peso;
    scanf("%d:%d:%d", &identificadorE, &identificadorP, &quantidade);
    peso = prod[identificadorP].peso * quantidade;

    /*verifica se a encomenda existe*/
    if (identificadorE >= ide) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",
               identificadorP, identificadorE);
    /*verifica se o produto existe*/
    } else if (identificadorP >= idp) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",
               identificadorP, identificadorE);
    /*verifica se a quantidade do produto e suficiente*/
    } else if (prod[identificadorP].qtd < quantidade) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",
               identificadorP, identificadorE);
    /*verifica se o peso nao excede o peso maximo*/
    } else if (peso + encom[identificadorE].peso > MAXPESO) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",
               identificadorP, identificadorE);
    } else {
        /*no caso de nao haver erros  adiciona o produto de identificadorP ah encomenda de identificadorE*/
        encom[identificadorE].peso += peso;
        encom[identificadorE].prod[identificadorP].qtd += quantidade;
        prod[identificadorP].qtd -= quantidade;
        encom[identificadorE].prod[identificadorP].identP = identificadorP;
    }
}

/*remove quantidade de um produto do mesmo, caso esta acao seja possivel*/
void RemoveStock() {
    int identificadorP, quantidade;
    scanf("%d:%d", &identificadorP, &quantidade);

    /*verifica se existe o produto*/
    if (identificadorP >= idp) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",
               identificadorP);
    } else {
        /*no caso da quantidade no produto ser maior que a quantidade  remove a quantidade*/
        if (prod[identificadorP].qtd >= quantidade) {
            prod[identificadorP].qtd -= quantidade;
        } else {
            /*se a quantidade a retirar for maior que a existente no produto  eh erro*/
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",
             quantidade,identificadorP);
        }
    }
}

/*remove um produto de uma encomenda, caso seja possivel*/
void RemoveProdutoEncomenda() {
    int identificadorE, identificadorP, peso;
    scanf("%d:%d", &identificadorE, &identificadorP);

    /*verifica se a encomenda existe*/
    if (identificadorE >= ide) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",
               identificadorP, identificadorE);
    /*verifica se o produto existe*/
    } else if (identificadorP >= idp) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",
               identificadorP, identificadorE);
    } else {
        /*se nao existir erros  entao eh removido o produto de identificadorP
         da encomenda de identificadorE*/
        peso = prod[identificadorP].peso * encom[identificadorE].prod[identificadorP].qtd;
        encom[identificadorE].peso -= peso;
        prod[identificadorP].qtd += encom[identificadorE].prod[identificadorP].qtd;
        encom[identificadorE].prod[identificadorP].qtd = 0;
    }
}

/*calcula o custo total de uma encomenda*/
void CalculaCusto() {
    int i, custo = 0, identificadorE;
    scanf("%d", &identificadorE);

    /*verifica se a encomenda existe*/
    if (identificadorE >= ide) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",
               identificadorE);
    } else {
        /*caso a encomenda exista  eh adicionado o preco de cada produto da mesma*/
        for (i = 0; i < idp; i++)
            custo += prod[i].preco * encom[identificadorE].prod[i].qtd;
        printf("Custo da encomenda %d %d.\n", identificadorE, custo);

    }
}

/*altera o preco de um certo produto*/
void AlteraPreco() {
    int identificadorP, preco;
    scanf("%d:%d", &identificadorP, &preco);

    /*verifica se o produto existe*/
    if (identificadorP >= idp) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",
               identificadorP);
    } else {
        /*substitui o preco antigo pelo preco recebido*/
        prod[identificadorP].preco = preco;
    }
}

/*imprimira a descricao e a quantidade de um certo produto de uma certa encomenda*/
void DescricaoQuantidade() {
    int identificadorP, identificadorE;
    scanf("%d:%d", &identificadorE, &identificadorP);

    /*verifica se a encomenda existe*/
    if (identificadorE >= ide) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",
               identificadorE);
    /*verifica se o produto existe*/
    } else if (identificadorP >= idp) {
        printf("Impossivel listar produto %d. Produto inexistente.\n",
               identificadorP);
    } else {
        printf("%s %d.\n", prod[identificadorP].descricao,
         encom[identificadorE].prod[identificadorP].qtd);

    }
}

/*ve qual a encomenda em que o produto existe em maior quantidade*/
void MaiorOcurrencia() {
    int i, encomenda, quantidade = 0, identificadorP;
    scanf("%d", &identificadorP);

    /*verifica se o produto existe*/
    if (identificadorP >= idp) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",
               identificadorP);
    } else {
        for (i = 0; i < ide; i++) {
            /*se a quantidade numa encomenda de produto de identificadorP
             for superior a encomenda maior anterior, entao a quantidade e
              encomenda sao alteradas*/
            if (encom[i].prod[identificadorP].qtd > quantidade) {
                /*a quantidade eh a quantidade do produto de identificadorP
                 em cada encomenda*/
                quantidade = encom[i].prod[identificadorP].qtd;
                /*guarda o identificador da encomenda que ate ao momento teve maior
                 numero do produtos de identificadorP*/
                encomenda = i;
            }
        }
        if (quantidade != 0)
            /*se o produto existir entao a funcao imprime o identificadorP  o identificador
             da encomenda e a quantidade do produto na encomenda*/
            printf("Maximo produto %d %d %d.\n", identificadorP, encomenda, quantidade);
    }
}

/*funcao auxiliar que serve para ordenar, explicado ao longo da mesma*/
void mergeSort(int p[MAXIDP], int aux[MAXIDP], int i, int f, char c) {
    int m, j, k, l, comparador;

    /*verifica se o indice final eh igual ou menor que o inicial*/
    if (f - i < 1)
        return;
    /*m representa o meio do vetor*/
    m = (i + f) / 2;
    /*recursiva*/
    mergeSort(aux, p, i, m, c);
    mergeSort(aux, p, m + 1, f, c);

    k = i;
    l = m + 1;
    /*ciclo que vai comparando certos aspetos dos produtos,
     nas funcoes indicadas*/
    for (j = i; j <= f; j++) {
        /*verificar o limite superior*/
        if (l > f || k > f) {
            comparador = 0;
        /*verifica qual a funcao que esta a chamar o algoritmo*/
        } else if (c == 'P') {
            /*se se tratar da funcao 'l', eh utilizada a funcao comparadorProdutos*/
            comparador = comparadorProdutos(p[k], p[l]);
        } else {
            /*se nao, trata se da funcao 'L' e eh utilizada a funcao
             comparadorProdutosEncomenda*/
            comparador = comparadorProdutosEncomenda(p[k], p[l]);
        }

        /*ordena por ordem crescente a unidade que depende da funcao que chama
         o mergeSort*/
        if (k <= m && (l > f || comparador)) {
            aux[j] = p[k];
            k++;
        } else {
            aux[j] = p[l];
            l++;
        }
    }
}

/*lista todos os produtos que existem no sistema, ordenando, utilizando mergeSort,
 pelos precos*/
void ListaPreco() {
    int i, aux[MAXIDP];
    int produtos[MAXIDP];
    for (i = 0; i < MAXIDP; i++) {
        produtos[i] = i;
    }

    for (i = 0; i < MAXIDP; i++) {
        /*produtos[i] e guardado num vetor auxiliar*/
        aux[i] = produtos[i];
    }
    /*ordena por ordem crescente*/
    mergeSort(aux, produtos, 0, idp - 1, 'P');

    printf("Produtos\n");
    /*lista os produtos, ja de acordo com os precos*/
    for (i = 0; i < idp; i++) {
        printf("* %s %d %d\n", prod[produtos[i]].descricao,
         prod[produtos[i]].preco, prod[produtos[i]].qtd);
    }
}

/*lista os produtos todos existentes numa encomenda, ordenando, utilizando o mergeSort,
 pelo primeira letra, alfabeticamente*/
void ListaEncomenda() {
    int identificadorE, i, j = 0, produtos[MAXIDP], aux[MAXIDP];
    scanf("%d", &identificadorE);

    /*verifica a nao existencia da encomenda*/
    if (identificadorE >= ide) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",
               identificadorE);
    } else {
        for (i = 0; i < idp; i++) {
            /*inicializa o vetor*/
            produtos[i] = -1;
            /*se a encomenda tem produtos cujas quantidades sao
             sao maiores ou iguais a 1, eh guardado no vetor produtos[i]
              o identificador dos produtos da encomenda*/
            if (encom[identificadorE].prod[i].qtd > 0) {
                produtos[j++] = encom[identificadorE].prod[i].identP;
            }
        }

        for (i = 0; i < j; i++) {
            /*vetor auxuliar aux[i]*/
            aux[i] = produtos[i];
        }
        /*algoritmo que vai ordenar o vetor dos produtos*/
        mergeSort(aux, produtos, 0, j - 1, 'E');

        printf("Encomenda %d\n", identificadorE);
        for (i = 0; i < j; i++) {
            printf("* %s %d %d\n", prod[produtos[i]].descricao, prod[produtos[i]].preco,
                   encom[identificadorE].prod[produtos[i]].qtd);
        }
    }

}

/*funcao principal, que ve qual a letra, representacao da funcao, fazendo a
 acao correspondente a mesma*/
int main() {

    int car;

    /*ve qual sera o primeiro caracter*/
    while ((car = getchar())) {
        switch (car) {
            case 'a':
                AdicionaProduto();
                break;
            case 'q':
                AdicionaStock();
                break;
            case 'N':
                CriaEncomenda();
                break;
            case 'A':
                AdicionaProdutoEncomenda();
                break;
            case 'r':
                RemoveStock();
                break;
            case 'R':
                RemoveProdutoEncomenda();
                break;
            case 'C':
                CalculaCusto();
                break;
            case 'p':
                AlteraPreco();
                break;
            case 'E':
                DescricaoQuantidade();
                break;
            case 'm':
                MaiorOcurrencia();
                break;
            case 'l':
                ListaPreco();
                break;
            case 'L':
                ListaEncomenda();
                break;
            /*sai do ciclo*/
            case 'x':
                return 0;
        }
        getchar();
    }
    return 0;
}
