#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projeto.h"


/*
*************************************************
*                                               *
*                   FUNCAO MAIN                 *
*                                               *
*************************************************
*/
int main()
{
    /*variavies locais da funcao main. Duas estruturas criadas nesta funcao, prod e new_encm*/
    encomendas new_encm[MAXENC];
    product prod[MAXPROD];  
    char c;
    int idp = 0, num_encomendas = 0;

    /*Inicializacao estrategica de cada estrutura de maneira a poder realizar remocoes e outras funcoes*/
    inicializa_enc(new_encm);
    inicializa_prod(prod);

    /*Ciclo de verificacao de comandos, que recebe o primeiro caracter do input. Termina coma tecla 'x'*/
    while( (c = getchar()) != 'x')
    {
        switch (c)
        {
            case 'a': 
                a_comando(prod, idp);
                idp++;
                break;
            case 'q':
                q_comando(prod);
                break;
            case 'N':
                N_comando(new_encm, num_encomendas);
                num_encomendas++;
                break;
            case 'A':
                A_comando(new_encm, prod);
                break;
            case 'r':
                r_comando(prod);
                break;
            case 'R':
                R_comando(prod, new_encm);
                break;
            case 'C':
                C_comando(prod, new_encm, idp);
                break;
            case 'p':
                p_comando(prod);
                break;
            case 'E':
                E_comando(prod, new_encm);
                break;
            case 'm':
                m_comando(prod, new_encm, num_encomendas);
                break;
            case 'l':
                l_comando(prod, 0, idp);
                break;
            case 'L':
                L_comando(new_encm, prod, idp);
                break;
        }
    }
    return 0;
}

/*
*************************************************
*                                               *
*         FUNCOES AUXILIARES DA MAIN            *
*                                               *
*************************************************
*/

void a_comando(product prod[], int idp)
{
    prod[idp].idp = idp;
    scanf(" %[^:]:%d:%d:%d", prod[idp].descricao, &prod[idp].preco, &prod[idp].peso, &prod[idp].qtd);
    printf("Novo produto %d.\n", idp);
}

/*****************************************************************************************************/

void q_comando(product prod[])
{   
    int identf, quant;
    scanf(" %d:%d", &identf, &quant);

    /*Verificacao da existencia do produto no stock, chamando a funcao 'verifica_prod'*/
    if (verifica_prod(prod, identf) == 1)
    {
        /*Adicionar a quantidade ao produto no sistema*/
        prod[identf].qtd += quant;
    }
    else
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", identf);
    }
}

/*****************************************************************************************************/

void N_comando(encomendas new_encm[], int num_encomendas)
{
    new_encm[num_encomendas].ide = num_encomendas;
    printf("Nova encomenda %d.\n", num_encomendas);
}

/*****************************************************************************************************/

void A_comando(encomendas new_encm[], product prod[])
{
    int ide, idp, qtd, verif = 0, a;
    scanf(" %d:%d:%d", &ide, &idp, &qtd);

    /*Verificacao da existencia dessa encomenda, chamando a funcao 'verifica_enc'*/
    if (verifica_enc(new_encm, ide) == 1)
    {
        /*Verificacao da existencia do produto no stock, chamando a funcao 'verifica_prod'*/
        if (verifica_prod(prod, idp) == 1)
        {
            /*Verificacao se a quantidade existente no stock e superior ou igual a quantidade a adicionar a encomenda*/
            if (prod[idp].qtd >= qtd)
            {
                /*Verificacao se o peso_total da encomenda com a adicao do peso do produto a adicionar e menor ou igual a 200*/
                if ((new_encm[ide].peso_total + (prod[idp].peso * qtd)) <= 200)
                {   
                    new_encm[ide].peso_total += (prod[idp].peso * qtd);

                    /*Ciclo que vai a todos os produtos numa encomenda, e para quando encontra o produto pedido*/
                    for (a = 0; a < new_encm[ide].num_pedidos; a++)
                    {
                        /*Verificacao da existencia desse produto na encomenda ide*/
                        if (new_encm[ide].pedidos[a].idp == idp)
                        {
                            new_encm[ide].pedidos[a].qntd += qtd;
                            /*Caso o produto exista, a variavel verif muda para 1, provando a existencia do produto*/
                            verif = 1; break;
                        } 
                    }
                    /*Caso a existencia do produto na encomenda nao se verifique*/
                    if (verif == 0)
                    {
                        /*Adicao de um produto a encomenda ide, e os dados necessarios*/
                        new_encm[ide].pedidos[new_encm[ide].num_pedidos].idp = idp;
                        new_encm[ide].pedidos[new_encm[ide].num_pedidos].qntd = qtd;
                        new_encm[ide].num_pedidos++;
                    }
                    /*Retirar a quantidade do stock que adicionamos a encomenda*/
                    prod[idp].qtd -= qtd;
                }
                else
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
            }
            else
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);       
        }
        else
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/*****************************************************************************************************/

void r_comando(product prod[])
{
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);

    /*Verificacao da existencia do produto no stock, chamando a funcao 'verifica_prod'*/
    if (verifica_prod(prod, idp) == 1)
    {
        /*Verificacao do valor da quantidade em stock se retiramos a quantidade pedida, nao podendo ficar negativa*/
        if(prod[idp].qtd - qtd >= 0)
        {
            prod[idp].qtd = prod[idp].qtd - qtd;
        }
        else
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
         printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
}

/*****************************************************************************************************/

void R_comando(product prod[], encomendas new_encm[])
{
    int ide, idp, a, i;
    scanf(" %d:%d", &ide, &idp);

    /*Verificao da existencia da encomenda, chamando a funcao 'verifica_enc'*/
    if (verifica_enc(new_encm, ide) == 1)
    {
        /*Verificacao da existencia do produto no stock, chamando a funcao 'verifica_prod'*/
        if (verifica_prod(prod, idp) == 1)
        {
            /*Ciclo que vai a todos os pedidos de uma encomenda ide, e para quando encontra o produto pedido*/
            for (a = 0; a < new_encm[ide].num_pedidos; a++)
            { 
                /*Verificacao da existencia desse produto na propria encomenda*/
                if (new_encm[ide].pedidos[a].idp == idp)
                {
                    /*Retirar o peso do produto selecionado. Adicionar o produto retirado ao stock do sistema*/
                    new_encm[ide].peso_total -= (prod[idp].peso * new_encm[ide].pedidos[a].qntd);
                    prod[idp].qtd += new_encm[ide].pedidos[a].qntd;
                    
                    /*Ciclo que apos encontrado o produto pedido, vai aos restantes produtos da encomenda*/
                    for (i = a; i < new_encm[ide].num_pedidos; i++)
                    {
                        /*Verifica se o produto pedido nao e o ultimo da encomenda*/
                        if (i != new_encm[ide].num_pedidos -1)
                        {
                            /*Seguindo cada iteracao do ciclo, faz-se shift para a esquerda de todos os produtos seguintes*/
                            new_encm[ide].pedidos[i].idp =  new_encm[ide].pedidos[i+1].idp;
                            new_encm[ide].pedidos[i].qntd = new_encm[ide].pedidos[i+1].qntd;
                        }
                        /*Caso o produto seja o ultimo da encomenda, nao se faz shift, e inicializa se aquela posicao, como incialmente*/
                        else{
                            new_encm[ide].pedidos[i].idp = -1;
                            new_encm[ide].pedidos[i].qntd = 0;
                        }
                    }
                    new_encm[ide].num_pedidos--;
                    break;
                }   
            }       
        }
        else
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/*****************************************************************************************************/

void C_comando(product prod[], encomendas new_encm[], int idp)
{
    int ide, total = 0, i, a;
    scanf(" %d", &ide);

    /*Verificacao da existencia da encomenda, chamando a funcao 'verifica_enc'*/
    if (verifica_enc(new_encm, ide) == 1)
    {
        /*Caso existam produtos na encomenda ide, vai realizar o valor do total*/
        if (new_encm[ide].num_pedidos > 0)
        {
           /*Ciclo que vai a todos os produtos individualmente e calcula o seu custo na encomenda e adiciona ao total*/
            for(i = 0; i < idp; i++)
            {
                /*Ciclo que vai a todos os produtos na encomenda ide, e para quando encontra o produto pretendido pelo ciclo anterior*/
                for (a = 0; a < new_encm[ide].num_pedidos; a++)
                {
                    /*Verificacao da existencia do produto i na encomenda*/
                    if (new_encm[ide].pedidos[a].idp == prod[i].idp)
                    {
                        total += (new_encm[ide].pedidos[a].qntd * prod[i].preco);
                        break;
                    }
                }   
            }
            printf("Custo da encomenda %d %d.\n", ide, total); 
        }
        else /*Caso nao exista nenhum produto na encomenda, retorna o valor total igual a 0*/
            printf("Custo da encomenda %d %d.\n", ide, total);        
    }
    else
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
}

/*****************************************************************************************************/

void p_comando(product prod[])
{
    int idp, preco;
    scanf(" %d:%d", &idp, &preco);

    /*Verificacao da existencia do produto, chamando a funcao 'verifica_prod'*/
    if (verifica_prod(prod, idp) == 1)
    {
        prod[idp].preco = preco;
    }
    else
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}

/*****************************************************************************************************/

void E_comando(product prod[], encomendas new_encm[])
{
    int ide, idp, a, verif = 0;
    scanf(" %d:%d", &ide, &idp);

    /*Verificacao da existencia da encomenda, chamando a funcao 'verifica_enc'*/
    if (verifica_enc(new_encm, ide) == 1)
    {
        /*Verificacao da existencia desse produto, chamando a funcao 'verifica_prod'*/
        if (verifica_prod(prod, idp) == 1)
        {
            /*Ciclo que vai a todos os produtos da encomenda ide, e para quando encontra o produto pretendido*/
            for (a = 0; a < new_encm[ide].num_pedidos; a++)
            {
                /*Verificacao da existencia do produto na encomenda ide*/
                if (new_encm[ide].pedidos[a].idp == idp)
                {
                    printf("%s %d.\n", prod[idp].descricao, new_encm[ide].pedidos[a].qntd);
                    verif = 1; /*Caso o produto exista, verif fica 1, provando a existencia de produto*/
                    break;
                }
            }
            /*Caso apos o ciclo anterior, nao se tenha encontrado o produto anterior, devolve quantidade 0*/
            if (verif == 0)
            {
                printf("%s 0.\n", prod[idp].descricao);
            } 
        }
        else
            printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}

/*****************************************************************************************************/

void m_comando(product prod[], encomendas new_encm[], int num_encomendas)
{
    int idp, i, num, maior = 0, indice = 0, a;
    scanf(" %d", &idp);
    num = num_encomendas;

    /*Verificacao da existencia do produto, chamando a funcao 'verifica_prod'*/
    if (verifica_prod(prod, idp) == 1)
    {
        /*Ciclo que verifica todas as encomendas existentes*/
        for (i = 0; i < num_encomendas; i++)
        {
            /*Ciclo que vai a todos os produtos na encomenda determinada pelo ciclo anterior, para quando encontra o produto*/
            for(a = 0; a < new_encm[i].num_pedidos; a++)
            {
                /*Verificacao da existencia desse produto na encomenda*/
                if (new_encm[i].pedidos[a].idp == idp)
                {
                    num--;
                    /*Verificacao da quantidade desse produto na encomenda i, em relacao a variavel 'maior', 
                    que guarda a maior quantidade existente de todas as encomendas com esse produto*/
                    if (new_encm[i].pedidos[a].qntd > maior)
                    {
                        maior = new_encm[i].pedidos[a].qntd;
                        indice = i;
                    }
                    break;
                }
            }
        }
        /*Verificacao da existencia de pelo menos uma encomenda com o produto selecionado*/
        if (num != num_encomendas)
        {
            printf("Maximo produto %d %d %d.\n", idp, indice, maior);
        }
    }
    else 
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
}

/*****************************************************************************************************/

void l_comando(product prod[], int l, int idp)
{
    int i, a;

    /*Estrutura criada a partir da estrutura definida product. Servira para fazer um backup/copia de todos os produtos existentes*/
    product ordem[MAXPROD];

    /*Ciclo que copia todos os produtos existentes ate ao momento para o backup, estrutura ordem*/
    for(a = 0; a < idp; a++)
    {
        ordem[a] = copia_produto(prod[a]);
    }
    /*Algoritmo de ordenacao*/
    mergeSort(ordem, l, idp-1);
    printf("Produtos\n");
    /*Ciclo que vai a todos os produtos na estrutura ordem ordenado e vai printar*/
    for (i = 0; i < idp; i++)
    {
        printf("* %s %d %d\n", ordem[i].descricao, ordem[i].preco, ordem[i].qtd);
    }
}

/*****************************************************************************************************/

void L_comando(encomendas new_encm[], product prod[], int idp)
{
    int ide, j, i, a, indice = 0, quantidade = 0;
    /*Estrutura criada a partir da estrutura definida product. Servira para guardar um unico produto e os seus dados*/
    product palavra; 
    /*Estrutura criada a partir da estrutura definida product. Servira para fazer um backup/copia de todos os produtos existentes*/
    product ordenacao[MAXPROD];
    scanf(" %d", &ide);

    /*Verificao da existencia da encomenda, chamando a funcao 'verifica_enc'*/
    if (verifica_enc(new_encm, ide) == 1)
    {   /*Ciclo que vai a todos os produtos no sistema*/
        for(a = 0; a < idp; a++)
        {   /*Ciclo que vai a todos os produtos na encomenda ide, para quando encontrado o produto*/
            for (i = 0; i < new_encm[ide].num_pedidos; i++)
            {   /*Verificacao da existencia do produto do primeiro ciclo com o que ta na encomenda*/
               if (new_encm[ide].pedidos[i].idp == prod[a].idp)
                {
                    ordenacao[indice] = copia_produto(prod[a]); /*Copia esse produto e todas os seus dados para a estrutura ordenacao*/
                    indice++; break;
                } 
            }
        }
        /*Ciclos que ordena todos os produtos no backup segundo a sua descricao*/
        for (j = 0; j < indice ;j++)
        {
           for (i = 0; i < indice ; i++)
            {   /*Caso o i nao seja o ultimo termo*/
                if (i != indice-1)
                {   /*Compara e verifica duas strings de cada vez, e determina se a maior e a primeira.*/
                    if (strcmp(ordenacao[i].descricao, ordenacao[i+1].descricao) > 0)
                    {   /*Troca dos termos*/
                        palavra = copia_produto(ordenacao[i]); 
                        ordenacao[i] = copia_produto(ordenacao[i+1]);
                        ordenacao[i+1] = copia_produto(palavra);
                    }  
                }
            } 
        }
        printf("Encomenda %d\n", ide);
        if (new_encm[ide].num_pedidos > 0) /*Caso existam produtos na encomenda*/
        {   /*Ciclo que vai a todos os produtos ordenados da estrutura ordenacao*/
            for (i = 0; i < indice; i++)
            {   /*Ciclo que vai a todos os produtos na encomenda*/
                for(a = 0; a < new_encm[ide].num_pedidos;a++)
                {   /*Quando encontra o produto na encomenda, guarda a quantidade na encomenda*/
                    if (new_encm[ide].pedidos[a].idp == ordenacao[i].idp)
                    {
                        quantidade = new_encm[ide].pedidos[a].qntd;
                        printf("* %s %d %d\n", ordenacao[i].descricao, ordenacao[i].preco, quantidade);
                    }
                }
            }
        }
    }
    else
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}

/*****************************************************************************************************/

void merge(product ordem[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    product L[MAXPROD]; /*estrutura para a parte esquerda do pivot m*/
    product R[MAXPROD]; /*estrutura para a parte direita do pivot m*/

    for (i = 0; i < n1; i++) /*Ciclo que copia para a estrutura L a parte esquerda do pivot*/
        L[i] = copia_produto(ordem[l+i]);
    for (j = 0; j < n2; j++) /*Ciclo que copia para a estrutura R a parte direita do pivot*/
        R[j] = copia_produto(ordem[m+1+j]);
  
    i = 0; j = 0; k = l;
    /*Ordenacao consoante o mesmo numero de termos em ambos as estruturas*/
    while (i < n1 && j < n2) 
    { 
        if (L[i].preco <= R[j].preco) 
        { 
            ordem[k] = copia_produto(L[i]); i++; 
        } 
        else
        { 
            ordem[k] = copia_produto(R[j]); j++; 
        } 
        k++; 
    } 
    /*Caso o lado esquerdo seja maior que o lado direito, copia os restantes termos*/
    while (i < n1) 
    { 
        ordem[k] = copia_produto(L[i]); i++; k++; 
    } 
    /*Caso o lado esquerdo seja maior que o lado direito, copia os restantes termos*/
    while (j < n2) 
    { 
        ordem[k] = copia_produto(R[j]); j++; k++; 
    } 
} 

/*****************************************************************************************************/

void mergeSort(product ordem[], int l, int r) 
{   /*Vai dividindo a lista em dois sucessivamente, enquanto houver pelo menos termos na lista*/
    if (l < r) 
    {   
        int m = l+(r-l)/2; 
        mergeSort(ordem, l, m); 
        mergeSort(ordem, m+1, r); 
        merge(ordem, l, m, r); 
    } 
} 

/*****************************************************************************************************/

void inicializa_enc(encomendas enc[])
{
    int i, a;
    
    for (i = 0; i < MAXENC; i++)
    {/*Vai a todos os MAXENC(500) encomendas possiveis de existir e coloca valores estrategicos em cada variavel*/
        enc[i].ide = -1;
        enc[i].peso_total = 0;
        enc[i].num_pedidos = 0;
        for (a = 0; a < MAXENCPROD; a++)
        {/*Vai a todos os MAXENCPROD(200) produtos possiveis de existir na enc e coloca valores estrategicos
         em cada variavel*/
            enc[i].pedidos[a].idp = -1;
            enc[i].pedidos[a].qntd = 0;
        }
    }
}

/*****************************************************************************************************/

void inicializa_prod(product prodt[])
{
    int i;
    for (i = 0; i < MAXPROD; i++)
    {/*Vai a todos os MAXPROD (10000) produtos possiveis de existir e coloca valores estrategicos em cada variavel*/
        prodt[i].preco = 0;
        prodt[i].peso = 0;
        prodt[i].qtd = 0;
        prodt[i].idp = -1;
        strcpy(prodt[i].descricao, "0");
    }
}

/*****************************************************************************************************/

int verifica_prod(product prodct[], int idp)
{
    int existe;
    /*Vai a estrutura e verifica se existe de facto esse produto no sistema e retorna 1 caso verdadeiro*/
    if (prodct[idp].idp == idp){
        existe = 1;
    }
    else{
        existe = 0;
    }
    return existe;
}

/*****************************************************************************************************/

int verifica_enc(encomendas enc[], int ide)
{
    int existe;
    /*Vai a estrutura e verifica se existe de facto essa encomenda e retorna 1 caso verdadeiro*/
    if (enc[ide].ide == ide){
        existe = 1;
    }
    else{
        existe = 0;
    }
    return existe;
}

/*****************************************************************************************************/

product copia_produto(product prod_or){
    /*Criacao de uma estrutura 'prod_cpy' para onde os valores vao ser copiados*/
    product prod_cpy;
    prod_cpy.preco = prod_or.preco;
    prod_cpy.peso = prod_or.peso;
    prod_cpy.qtd = prod_or.qtd;
    prod_cpy.idp = prod_or.idp;
    strcpy(prod_cpy.descricao, prod_or.descricao); 
    return prod_cpy;   
}
/*****************************************************************************************************/
