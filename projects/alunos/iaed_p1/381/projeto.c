#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define PROD 10000
#define ENC 500
#define PROD_ENC 200
#define NOME 63
#define exch(A,B) {int t = A; A=B; B=t;}

/*Estrutura de um produto, nome,preco, qtd, peso, idp*/
struct Stock
{
        char nome[NOME + 1];
        int preco, peso, qtd, idp;
};
/*Estrutura de uma encomenda, n de produtos, peso_total, preco_total,um array de produtos vai conter as especifica?oes de cada produto*/
struct Encomendas
{
    int n_produtos, peso, preco;
    struct Stock produto_encomenda[PROD_ENC] ;
};

/*Array de produtos*/
struct Stock produto[PROD];
/*Array de encomendas*/
struct Encomendas encomenda[ENC];
/*Variaveis globais controladoras do n de produtos e de encomendas, respetivamente */
int p = -1, e = -1;
char c;/* char correspondente ao comando utilizado. E global para usar a funcao partition de duas maneiras diferentes*/

int partition(int a[], int l, int r)
{
    int i = l-1;
    int j = r;
    int v= a[r];
    while(i < j)
    {
        if (c == 'l')/*caso o comando escolhido seja 'l' ira ordenar os indices dos produtos por preco*/
        {
            /*solicitamos de mais uma condicao pois caso o preco seja igual temos que ordenar por idp */
            while (produto[a[++i]].preco < produto[v].preco || (produto[a[i]].preco == produto[v].preco && a[i] < v));
            while (produto[v].preco < produto[a[--j]].preco || (produto[a[j]].preco == produto[v].preco && a[j] > v))
                if (j == l)
                    break;
        }
        else if (c == 'L')/*caso o comando escolhido seja 'L' ira ordenar os indices dos produtos das encomendas por nome, usando o strcmp */
        {
            while (strcmp(produto[a[++i]].nome, produto[v].nome) < 0);
            while (strcmp(produto[v].nome, produto[a[--j]].nome) < 0)
                if (j == l)
                    break;
        }
        if (i < j)
            exch(a[i], a[j]);
    }
    exch(a[i], a[r]);
    return i;

}

void quicksort(int a[], int l, int r)
{
    /*Algoritmo de ordenacao*/
    int i;
    if (r <= l)
        return;
    i = partition(a, l, r);
    quicksort(a, l, i-1);
    quicksort(a, i+1, r);
}

void a_Command()
{
    /*Incrementa-se o numero de produtos e fazemos scanf das lpropriedades dos produtos;por fim guardamos o seu idp sendo igual ao proprio p */
    p = p+1;
    scanf(" %[^:]:%d:%d:%d", produto[p].nome, &produto[p].preco, &produto[p].peso, &produto[p].qtd );
    produto[p].idp = p;
    printf("Novo produto %d.\n", p);
}

void q_Command()
{
    /* Verificamos se existe erro, caso nao haja incrementamos no produto[idp] a quantidade pretendida*/
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);
    if (idp>p)/*caso o produto nao exista*/
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else
        produto[idp].qtd += qtd;


}

void r_Command()
{
    /*Verificamos os erros caso nao haja decrementamos no produto[idp] a quantidade pretendida*/
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);
    if (idp>p)/*caso o produto nao exista*/
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if ((produto[idp].qtd - qtd) < 0)/*caso a quantidade produto[idp] seja menor que a quantidade que se quer retirar*/
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    else
        produto[idp].qtd -= qtd;

}

void p_Command()
{
    /* Verifica?ao de erros caso nao haja faz-se a troca do preco*/
    int idp, preco, j, i;
    scanf(" %d:%d", &idp, &preco);
    if (idp>p)/*caso o produto nao exista*/
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else if (e == -1)/*caso nenhuma encomenda tenha sido criada, faz apenas a troca do preco*/
        produto[idp].preco = preco;
    else /*caso hajam encomendasa criadas temos de verificar se esse produto se encontra numa delas*/
    {
        for (j=0; j <= e; j++)
        {
            for (i=0; i <= encomenda[j].n_produtos; i++)
            {
                if (encomenda[j].produto_encomenda[i].idp == idp)
                {
                    /*caso encontre, vai retirar o preco total desse produto da encomenda, atualizar o preso e voltar a incrementar no preco total da encomenda*/
                    encomenda[j].preco -= encomenda[j].produto_encomenda[i].preco * encomenda[j].produto_encomenda[i].qtd;
                    encomenda[j].produto_encomenda[i].preco = preco;
                    encomenda[j].preco += preco * encomenda[j].produto_encomenda[i].qtd;
                    break;
                }
            }
        }
        produto[idp].preco = preco;
    }

}

void m_Command()
{
    int idp, maxqtd, ide, i, j ;
    scanf(" %d", &idp);
    maxqtd = 0;
    ide = -1;
    if (idp > p)/*caso o produto nao exista*/
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else
    {
        /*Vai percorrer todas as encomendas e os respetivos produtos quando encontrar guarda qtd e o ide.Esta variavel max qtd ? atualizada
          caso a qtd do produto noutra encomenda seja maior. */
        for(j=0; j <= e; j++)
        {
            for(i=0; i <= encomenda[j].n_produtos; i++)
            {
                if (encomenda[j].produto_encomenda[i].idp == idp)
                {
                    if (encomenda[j].produto_encomenda[i].qtd > maxqtd)
                    {
                        maxqtd = encomenda[j].produto_encomenda[i].qtd;
                        ide = j;
                    }
                }
            }
        }
        if (maxqtd)
            printf("Maximo produto %d %d %d.\n", idp, ide, maxqtd);
    }

}

void l_Command()
{
    /*recolhe os indices de todos os produtos, ordena-os por preco e por fim printa-os na ordem certa*/
    int i, a[PROD];
    printf("Produtos\n");
    for (i=0; i<= p; i++)
    {
        a[i]=i;
    }
    quicksort(a, 0, p);
    for (i=0; i<= p; i++)
    {

        printf("* %s %d %d\n", produto[a[i]].nome, produto[a[i]].preco, produto[a[i]].qtd);
    }


}

void N_Command()
{
    /*Apenas incrementa a variavel do numero de encomendas e inicializa o n de produtos a -1 par saber que se encontra empty*/
    printf("Nova encomenda %d.\n", ++e);
    encomenda[e].n_produtos = -1;
}

void A_Command()
{
    int ide, idp, qtd,i, a=0 ;
    scanf(" %d:%d:%d", &ide, &idp, &qtd);
    if (ide > e)/*caso esse ide de encomenda ainda nao tenha sido criado*/
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp > p)/*caso o produto nao exista*/
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (qtd > produto[idp].qtd)/*caso a quantidade pretendida seja superior a quantidade do produto */
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if ((encomenda[ide].peso + produto[idp].peso * qtd) > 200)/*caso o peso da encomenda exceda o 200*/
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else
    {
        /* A variavel 'a' vai servir de controlador, isto e se esta ficar a=1, representa que o produto ja estava dentro da encomenda
           caso a continue =0, significa que a encomenda nao se encontra na encomenda*/
        for (i=0; i <= encomenda[ide].n_produtos; i++)
        {
            if ( encomenda[ide].produto_encomenda[i].idp == idp)
            {
                /*como se encontra na encomenda apenas atualizamos o preco e o peso da encomenda, e a quantidade do produto e retiramos a qtd ao stock*/
                encomenda[ide].preco += produto[idp].preco * qtd;
                encomenda[ide].peso += produto[idp].peso * qtd;
                encomenda[ide].produto_encomenda[i].qtd += qtd;
                produto[idp].qtd -= qtd;
                a=1;
            }
        }
        if (a == 0)
        {
            /*como o produto nao se encontra na encomenda, atualizamos o preco e o peso, tiramos qtd ao stock acrescentamos 1 poduto
              ao numero de produtos, e por fim guardamos as caracteristicas do produto, no produto[x] da encomenda */
            encomenda[ide].peso += produto[idp].peso  * qtd;
            encomenda[ide].preco += produto[idp].preco * qtd;
            produto[idp].qtd -= qtd;
            encomenda[ide].n_produtos += 1;
            strcpy(encomenda[ide].produto_encomenda[encomenda[ide].n_produtos].nome, produto[idp].nome);
            encomenda[ide].produto_encomenda[encomenda[ide].n_produtos].preco = produto[idp].preco;
            encomenda[ide].produto_encomenda[encomenda[ide].n_produtos].peso = produto[idp].peso;
            encomenda[ide].produto_encomenda[encomenda[ide].n_produtos].idp = produto[idp].idp;
            encomenda[ide].produto_encomenda[encomenda[ide].n_produtos].qtd = qtd;
        }

    }

}

void R_Command()
{
    int ide, idp, i;
    scanf(" %d:%d", &ide, &idp);
    if (ide>e)/*caso a encomenda ide ainda nao tenha sido criada*/
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp>p)/*caso o produto nao exista*/
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else
    {
        for (i=0; i <= encomenda[ide].n_produtos; i++)
        {
            if (encomenda[ide].produto_encomenda[i].idp == idp)
            {
                /*depois de encontrar o produto atualizamos o peso e o preco da ancomenda, voltamos a repor o stock
                  e igualmos a qtd do produto da encomenda a 0 */
                encomenda[ide].peso -= produto[idp].peso * encomenda[ide].produto_encomenda[i].qtd;
                encomenda[ide].preco -= produto[idp].preco * encomenda[ide].produto_encomenda[i].qtd;
                produto[idp].qtd += encomenda[ide].produto_encomenda[i].qtd;
                encomenda[ide].produto_encomenda[i].qtd = 0;
                break;
            }
        }
    }

}

void C_Command()
{
    int ide;
    scanf(" %d", &ide);
    if (ide > e)/*caso a encomenda ide ainda nao tenha sido criada*/
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
    else /*apenas printa o preco da encomenda[x]*/
        printf("Custo da encomenda %d %d.\n", ide, encomenda[ide].preco);


}

void E_Command()
{
    int ide, idp, i, qtd=0;
    scanf(" %d:%d", &ide, &idp);
    if (ide > e)/*caso a encomenda ide ainda nao tenha sido criada*/
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if (idp > p)/*caso o produto nao exista*/
        printf ("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else
    {
        /*se encontrar o produto na encomenda iguala a qtd, a qtd do produto na encomenda.
          Caso nao encontre esse produto a qtd fica como default =0 */
        for (i=0; i <= encomenda[ide].n_produtos; i++)
        {
            if (encomenda[ide].produto_encomenda[i].idp == idp)
            {
                qtd = encomenda[ide].produto_encomenda[i].qtd;
                break;
            }
        }
        printf("%s %d.\n", produto[idp].nome, qtd);
    }

}

void L_Command()
{
    int ide,i, a[PROD_ENC], qtd,j;
    scanf(" %d", &ide);
    if (ide > e)/*caso a encomenda ide ainda nao tenha sido criada*/
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else
    {
        /*armazena-se no a[i] todos os idps dos produtos*/
        printf("Encomenda %d\n", ide);
        for (i=0; i<= encomenda[ide].n_produtos; i++)
        {
            a[i]=encomenda[ide].produto_encomenda[i].idp;
        }
        /*o vetor e ordenamo pelo nome do produto com esse idp*/
        quicksort(a, 0, encomenda[ide].n_produtos);
        for(i=0; i <= encomenda[ide].n_produtos; i++)
        {
            for (j = 0; j <= encomenda[ide].n_produtos; j++)
            {
                if (a[i] == encomenda[ide].produto_encomenda[j].idp)
                {
                    /*descorbrir qual e a quantidade do produto na encomenda, com indice a[i] */
                    qtd = encomenda[ide].produto_encomenda[j].qtd;
                    break;
                }
            }
            if (qtd != 0)/*caso a qtd desse produto for 0, nao printa*/
                printf("* %s %d %d\n", encomenda[ide].produto_encomenda[j].nome, encomenda[ide].produto_encomenda[j].preco, qtd);
        }
    }
}


int main()
{
    while (1)/*ciclo infinito verifica o primeiro caracter, caso este for igual a 'x' acaba o programa*/
    {
        scanf("%c", &c);
        switch(c) /*Compara o primeiro char como os comandos caso seja igual executa a funcao do mesmo*/
        {
            case 'a': a_Command();
                      break;
            case 'q': q_Command();
                      break;
            case 'r': r_Command();
                      break;
            case 'p': p_Command();
                      break;
            case 'm': m_Command();
                      break;
            case 'l': l_Command();
                      break;
            case 'N': N_Command(); /* feito*/
                      break;
            case 'A': A_Command();
                      break;
            case 'R': R_Command();
                      break;
            case 'C': C_Command();
                      break;
            case 'E': E_Command();
                      break;
            case 'L': L_Command();
                      break;
            case 'x':  return 0;
        }
    }
    return 0;
}
