#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct produto {
       
       int preco;
       int peso;
       int stock;
       char descricao[63];
       int existe;
       
    } produto;

produto produtos[10000];

typedef struct encomenda {
    
        char produtos[10000][2];
        int peso_total;
        int existe2;

    } encomenda;

encomenda encomendas[500];

long contador_produtos = -1;

long contador_encomendas = -1;

/*prototipo de todas as funcoes ultilizadas no main*/

void adiciona_produto();

void adiciona_stock();

void adiciona_encomenda();

void adiciona_p_encomenda();

void remove_stock();

void remove_p_encomenda();

void calcula_custo();

void altera_preco();

void informacao_produto();

void lista_encomenda();

void lista_produtos();




int main()
{

    char letra;

    letra = 'z';

    while (letra != 'x')
    {
        letra = getchar();
    
        switch(letra)
        {
            case 'a':  
            adiciona_produto();
            break;

            case 'q':
            adiciona_stock();
            break;

            case 'N':
            adiciona_encomenda();
            break;

            case 'A':
            adiciona_p_encomenda();
            break;

            case 'r':
            remove_stock();
            break;

            case 'R':
            remove_p_encomenda();
            break;

            case 'C':
            calcula_custo();
            break;

            case 'p':
            altera_preco();
            break;

            case 'E':
            informacao_produto();
            break;

            case 'm':
            lista_encomenda();
            break;
            
            case 'l':
            lista_produtos();
            break;

        }
    }

    return 0;
}



void adiciona_produto()
{
    char preco_auxiliar[10];
    char peso_auxiliar[5];
    char stock_auxiliar1[10];

    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    int i4 = 0;

    int controlador = 0;

    int c;

    contador_produtos++;
    
    getchar();

    while ((c = getchar()) != '\n')
    {
        if (c == ':')
        {
            controlador++;
        }
        else
        {
            if (controlador == 0)
            {
                produtos[contador_produtos].descricao[i1] = c;
                i1++;
            }

            else if (controlador == 1)
            {
                preco_auxiliar[i2] = c;
                i2++;
            }

            else if (controlador == 2)
            {
                peso_auxiliar[i3] = c;
                i3++;
            }

            else if (controlador == 3)
            {
                stock_auxiliar1[i4] = c;
                i4++;
            }
        }
    }
    produtos[contador_produtos].preco = atoi(preco_auxiliar);
    produtos[contador_produtos].peso = atoi(peso_auxiliar);
    produtos[contador_produtos].stock = atoi(stock_auxiliar1);
    produtos[contador_produtos].existe = 1;

    printf("Novo produto %ld.\n", contador_produtos);
}



void adiciona_stock()
{
    int controlador = 0;

    char stock_auxiliar2[10];
    char produto_auxiliar[7];

    int x;
    int i1 = 0;
    int i2 = 0;

    int c;

    getchar();

    while ((c = getchar()) != '\n')
    {

        if (c == ':')
        {
            controlador++;
        }
        
        else
        {
            if (controlador == 0)
            {
                produto_auxiliar[i1] = c;
                i1++;
            }

            else if (controlador == 1)
            {
                stock_auxiliar2[i2] = c;
                i2++;
            }
        }
    }
    x = atoi(produto_auxiliar);

    if (produtos[x].existe != 1)
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", x);
    }
    else
    {
        produtos[x].stock += atoi(stock_auxiliar2);
    }
}



void adiciona_encomenda()
{
    ++contador_encomendas;

    printf("Nova encomenda %ld.\n", contador_encomendas);

    encomendas[contador_encomendas].existe2 = 1;

}



void adiciona_p_encomenda()
{
    int controlador = 0;

    char encomenda_auxiliar[5];
    char stock_auxiliar3[10];
    char produto_auxiliar2[7];

    int x;
    int y;
    int z;
    int peso_adicional;

    int i1 = 0;
    int i2 = 0;
    int i3 = 0;

    int c;

    getchar();

    while ((c = getchar()) != '\n')
    {

        if (c == ':')
        {
            controlador++;
        }
        
        else
        {
            if (controlador == 0)
            {
                encomenda_auxiliar[i1] = c;
                i1++;
            }

            else if (controlador == 1)
            {
                produto_auxiliar2[i2] = c;
                i2++;
            }

            else if (controlador == 2)
            {
                stock_auxiliar3[i3] = c;
                i3++;
            }
        }
    }

    x = atoi(encomenda_auxiliar);

    y = atoi(produto_auxiliar2);

    z = atoi(stock_auxiliar3);

    peso_adicional = z * produtos[y].peso;

    if (encomendas[x].existe2 != 1)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", y, x);
    }
    else if (produtos[y].existe != 1)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", y, x);
    }
    else if (produtos[y].stock - z < 0)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", y, x);
    }
    else if (encomendas[x].peso_total + peso_adicional > 200)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", y, x);
    }
    else
    {
        encomendas[x].produtos[y][0] += z;   /* adiciona o stock a encomenda */

        produtos[y].stock -= z;           /* remove o stock do produto */
        
        encomendas[x].peso_total += peso_adicional; /* adiciona o peso */

        encomendas[x].produtos[y][1] = 1; /* marca este produto como a ser utilizado na encomenda*/
        
    }
}



void remove_stock()
{
    int controlador = 0;

    char stock_auxiliar4[10];
    char produto_auxiliar3[7];

    int x;
    int y;

    int i1 = 0;
    int i2 = 0;

    int c;

    getchar();

    while ((c = getchar()) != '\n')
    {

        if (c == ':')
        {
            controlador++;
        }

        else
        {
            if (controlador == 0)
            {
                produto_auxiliar3[i1] = c;
                i1++;
            }

            else if (controlador == 1)
            {
                stock_auxiliar4[i2] = c;
                i2++;
            }
        }
    }
    x = atoi(produto_auxiliar3);

    y = atoi(stock_auxiliar4);

    if (produtos[x].existe != 1)
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", x);
    }

    else if (produtos[x].stock - y < 0)
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", y, x);
    }
    
    else
    {
        produtos[x].stock = produtos[x].stock - y;
    
    }
}



void remove_p_encomenda()
{
    int controlador = 0;

    char encomenda_auxiliar2[5];
    char produto_auxiliar4[7];
    int x;
    int y;
    int peso_a_remover;

    int i1 = 0;
    int i2 = 0;

    int c;

    getchar();

    while ((c = getchar()) != '\n')
    {

        if (c == ':')
        {
            controlador++;
        }

        else
        {
            if (controlador == 0)
            {
                encomenda_auxiliar2[i1] = c;
                i1++;
            }

            else if (controlador == 1)
            {
                produto_auxiliar4[i2] = c;
                i2++;
            }
        }
    }
    x = atoi(encomenda_auxiliar2);

    y = atoi(produto_auxiliar4);

    if (encomendas[x].existe2 != 1)
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", y, x);
    }

    else if (produtos[y].existe != 1)
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", y, x);
    }
    
    else
    {
        peso_a_remover = encomendas[x].produtos[y][0] * produtos[y].peso; /* calcula o peso que ira ser removido ao tirar o produto da encomenda */

        produtos[y].stock += encomendas[x].produtos[y][0]; /*adiciona o stock do produto que vamos remover ao stock do produto */

        encomendas[x].produtos[y][0] = 0;   /* muda o stock desse produto para zero */

        encomendas[x].peso_total = encomendas[x].peso_total - peso_a_remover; /* remove o peso contando com o stock retirado */

        encomendas[x].produtos[y][1] = 0; /* marca este produto como retirado da encomenda*/

    }
}



void calcula_custo()
{
    char encomenda_auxiliar3[100];

    int x;
    int custo_total;

    int i1 = 0;
    int i2 = 0;
    int c;

    getchar(); /* remove o espaco entre o caracter inicial e os indicadores */

    while ((c = getchar()) != '\n')
    {
        encomenda_auxiliar3[i1] = c;
        i1++;
    }
    x = atoi(encomenda_auxiliar3);

    if (encomendas[x].existe2 != 1)
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", x);
    }

    else
    {
        custo_total = 0;

        while (i2 < 10000)
        {
            if (encomendas[x].produtos[i2][1] == 1) /* analisa se o produto esta na encomenda */
            {

                custo_total += encomendas[x].produtos[i2][0] * produtos[i2].preco;

            }
            i2++;
        }

        printf("Custo da encomenda %d %d.\n", x, custo_total);

    }
}



void altera_preco()
{
    int controlador = 0;

    char produto_auxiliar5[7];
    char preco_auxiliar2[10];

    int x = 0;
    int y = 0;

    char str[20];

    int i1 = 0;
    int i2 = 0;

    int c;

    getchar();

    while ((c = getchar()) != '\n')
    {

        if (c == ':')
        {
            controlador++;
        }

        else
        {
            if (controlador == 0)
            {
                produto_auxiliar5[i1] = c;
                i1++;
            }

            else if (controlador == 1)
            {
                preco_auxiliar2[i2] = c;
                i2++;
            }
        }
    }


    
    x = atoi(produto_auxiliar5);

    strcpy(str, preco_auxiliar2);

    y = atoi(str);

    if (produtos[x].existe != 1)
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", x);
    }

    else
    {
        produtos[x].preco = 0;
        produtos[x].preco = y;
    }
}



void informacao_produto()
{
    int controlador = 0;

    char encomenda_auxiliar4[5];
    char produto_auxiliar6[7];

    int x;
    int y;

    int i1 = 0;
    int i2 = 0;

    int c;

    getchar();

    while ((c = getchar()) != '\n')
    {

        if (c == ':')
        {
            controlador++;
        }

        else
        {
            if (controlador == 0)
            {
                encomenda_auxiliar4[i1] = c;
                i1++;
            }

            else if (controlador == 1)
            {
                produto_auxiliar6[i2] = c;
                i2++;
            }
        }
    }
    
    x = atoi(encomenda_auxiliar4);

    y = atoi(produto_auxiliar6);

    if (encomendas[x].existe2 != 1)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", x);
    }

    else if (produtos[y].existe != 1)
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", y);
    }

    else
    {
        printf("%s %d.\n", produtos[y].descricao, encomendas[x].produtos[y][0]);
    }
}



void lista_encomenda()
{
    char produto_auxiliar7[6];
    char lista_encomendas[500];

    int contador2 = 0;
    
    int encomenda_stocks = 0;
    int registador_encomenda;
    int existe_produto_na_encomenda;

    int x;
    int y = 0;
    int contador =0;

    char str1[20];

    int i1 = 0;

    int c;

    getchar(); /* remove o espaco entre o caracter inicial e os indicadores */

    while ((c = getchar()) != '\n')
    {
        produto_auxiliar7[i1] = c;
        i1++;
    }

    strcpy(str1, produto_auxiliar7);

    x = atoi(str1);

    if (produtos[x].existe != 1)
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", x);
    }
    
    else
    {
        while (contador < 500)
        {
            if (encomendas[contador].produtos[x][1] == 1)
            {
                lista_encomendas[contador2] = contador;
                contador2++;
                existe_produto_na_encomenda = 1;
            }
            contador++;
        }

        if (existe_produto_na_encomenda == 1)
        {
            while (contador2 > -1)
            {
                y = lista_encomendas[contador2];
                if (encomendas[y].produtos[x][0] >= encomenda_stocks)
                {
                    encomenda_stocks = encomendas[y].produtos[x][0];
                    registador_encomenda = lista_encomendas[contador2];

                }
                contador2--;
            }
            printf("Maximo produto %d %d %d.\n", x, registador_encomenda, encomenda_stocks);
        }   
    }
}


void lista_produtos()
{
    int i1 = 0;

    int contador_produtos = 0;

    while (i1 < 100)
    {
        contador_produtos = 0;

        while (contador_produtos < 10000)
        {
            if (produtos[contador_produtos].preco == i1 + 1)
            {
                printf("* %s %d %d\n", produtos[contador_produtos].descricao, produtos[contador_produtos].preco, produtos[contador_produtos].stock);
            }
            contador_produtos++;
        }
        i1++;
    }   
}
