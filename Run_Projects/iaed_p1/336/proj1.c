#include <stdio.h>                
#include <string.h>               

/*################################### Definicao de constantes #############################*/

#define DIMPRO 10000     /*numero maximo de produtos no sistema*/ 
#define DIMENC 500       /*numero maximo que cada encomenda pode conter*/            
#define MAXPESO 200      /*peso maximo que cada encomenda pode conter*/            
#define DIMDISC 63       /*numero de caracteres maximo que a descricao de cada produto pode conter*/           
#define ATIVO 1          /*constante utilizada na variavel estado*/           
#define DESATIVO 0       /*constante utilizada na variavel estado*/     
#define ENCPRO 200       /*numero maximo de produtos dentro de uma encomenda*/
#define DIMEST 2         /*dimensao da tabela auxiliar ati[DIMENC][DIMEST]*/
#define ELM 1            /*constante utilizada na tabela ati posicao que indica numero de produtos numa encomenda*/ 
#define EST 0            /*constante utilizada na tabela ati posicao que indica estado de encomenda*/ 
 
/*################################### Definicao de abstracoes ##############################*/

#define less(A, B) (A <= B) /*verifica se A e menor ou igual que B para valores inteiros*/
#define lesschar(A, B) (strcmp(B, A) > 0) /*verifica se B vem primeiro alfabeticamente que A*/

/*################################### Definicao de estruturas #############################*/

/*estrutura PRODUCT representa cada produto existente no sistema*/
typedef struct{
    int idp, preco, peso, qtd;
    char describe[DIMDISC];
} PRODUCT;

/*estrutura PROENCOMENDA representa cada produto dentro de uma encomenda de forma mais simplificada*/
typedef struct{
    int idp, qtd;
} PROENCOMENDA;

/*estrutura ENCOMENDA representa cada encomenda existente no sistema*/
typedef struct{
    int ide, peso, numprod;
    PROENCOMENDA pro[ENCPRO];
} ENCOMENDA;

/*######################################### Prototipos ################################*/

/*Funcoes auxiliares*/

int prcur_aux(ENCOMENDA enc[DIMENC], int idp, int ide, int numprod);

void merge(PRODUCT ord[DIMPRO], int l, int m, int r, int estado);

void mergesort(PRODUCT ord[DIMPRO], int l, int h, int estado);

/*Funcoes principais*/

void command_a_(PRODUCT sto[DIMPRO], int idp);

void command_q_(PRODUCT sto[DIMPRO]);

void command_N_(ENCOMENDA enc[DIMENC], int ide, int ati[DIMENC][DIMEST]);

void command_A_(ENCOMENDA enc[DIMENC], PRODUCT sto[DIMPRO], int ati[DIMENC][DIMEST]);

void command_r_(PRODUCT sto[DIMPRO]);

void command_R_(ENCOMENDA enc[DIMENC], PRODUCT sto[DIMPRO], int ati[DIMENC][DIMEST]);

void command_C_(ENCOMENDA enc[DIMENC], PRODUCT sto[DIMPRO], int ati[DIMENC][DIMEST]);

void command_p_(PRODUCT sto[DIMPRO]);

void command_E_(ENCOMENDA enc[DIMENC], PRODUCT sto[DIMPRO], int ati[DIMENC][DIMEST]);

void command_m_(ENCOMENDA enc[DIMENC], PRODUCT sto[DIMPRO], int ati[DIMENC][DIMEST]);

void command_l_(PRODUCT sto[DIMPRO], int idp);

void command_L_(ENCOMENDA enc[DIMENC], PRODUCT sto[DIMPRO], int ati[DIMENC][DIMEST], int idp);

/*######################################## Funcao Main ################################*/

/*funcao onde e chamada qualquer funcao command com base no input*/
int main(){
    int idp = -1, estado = ATIVO, ide = -1;
    char c;
    static int ati[DIMENC][DIMEST] = {0}; /*guarda o estado e o numero de produtos existentes numa encomenda*/
    static PRODUCT sto[DIMPRO] = {0}; /*representa todos os produtos existentes no sistema*/
    static ENCOMENDA enc[DIMENC] = {0}; /*representa a lista de encomendas existentes*/

    while(1)
    {
        scanf("%c", &c);

        if (estado == ATIVO)
        {
            switch(c)
            {
                case 'a':
                    idp++;
                    command_a_(sto, idp); break;
                case 'q':
                    command_q_(sto); break;

                case 'N':
                    ide++;
                    command_N_(enc, ide, ati); break;

                case 'A':
                    command_A_(enc, sto, ati); break;

                case 'r':
                    command_r_(sto); break;

                case 'R':
                    command_R_(enc, sto, ati); break;

                case 'C':
                    command_C_(enc, sto, ati); break;

                case 'p':
                    command_p_(sto); break;

                case 'E':
                    command_E_(enc, sto, ati); break;

                case 'm':
                    command_m_(enc, sto, ati); break;

                case 'l':
                    command_l_(sto, idp); break;

                case 'L':
                    command_L_(enc, sto, ati, idp); break;

                case 'x':
                    return 0;
            }
        }
        if (c == '\n') estado = ATIVO; /*o input seguinte ao \n sera o caracter que a main pretende ler do input*/
        else estado = DESATIVO;
    }
}

/*##################################### Funcao auxiliar ################################*/

/*retorna a posicao prcur onde cada produto se encontra na encomenda caso esse exista e -1 caso nao exista*/
int prcur_aux(ENCOMENDA enc[DIMENC], int idp, int ide, int numprod)
{
    int prcur = -1, i;

    for(i = 0; i < numprod; i++)
    {
        if (enc[ide].pro[i].idp == idp)
        {
            prcur = i;
            break;
        }
    }
    return prcur;
}

/*############################ Algoritmo de ordenacao Merge Sort #######################*/

/*Funcao auxiliar da funcao mergesort*/
void merge(PRODUCT ord[DIMPRO], int l, int m, int r, int estado) 
{   
    int k = l, ie, id;
    int n1 = m - l + 1, n2 = r - m;

    PRODUCT e[DIMPRO], d[DIMPRO]; /*inicializacao de tabelas de produtos auxiliares*/

    for(ie = l; ie <= m; ie++) e[ie-l] = ord[ie]; /*guarda produtos que estao e esquerda do meio da particao*/

    for(id = m + 1; id <= r; id++) d[id-m-1] = ord[id]; /*guarda produtos que estao e esquerda do meio da particao*/

    ie = 0; id = 0; 

    while((ie < n1) && (id < n2))
    {
        /*a variavel estado corresponde ao commando que chamou a funcao mergesort*/
        if (estado) /*tem valor 1 se foi chamada pelo comando l e tem valor 0 se foi chamada pelo comando L*/
        {
            /*less(A, B) (A <= B) utilizando <= para tornar o algoritmo de ordenacao estavel*/
            if (less(e[ie].preco, d[id].preco)) ord[k++] = e[ie++];

            else ord[k++] = d[id++];
        }
        else
        {
            /*lesschar(A, B) (strcmp(B, A) > 0) se B estiver posicionado antes de A no alfabeto*/
            if (lesschar(e[ie].describe, d[id].describe)) ord[k++] = e[ie++]; 

            else ord[k++] = d[id++];
        }
    }
    /*copia os restantes elementos da tabela e para ord se existir algum*/
    while(ie < n1) ord[k++] = e[ie++];
    
    /*copia os restantes elementos da tabela d para ord se existir algum*/
    while(id < n2) ord[k++] = d[id++];
}   

/*Funcao recursiva utilizada nos comandos l e L tendo o objetivo de ordenar produto por preco ou alfabeticamente*/
void mergesort(PRODUCT ord[DIMPRO], int l, int h, int estado)
{
    int mid;
    if (l < h)
    {
    /*mid representa a posicao intermediaria da tabela com l o indice mais a esquerda e h o indice mais a direita de ord*/
        mid = ((l + h) / 2);

        mergesort(ord, l, mid, estado); /*primeira metade da tabela*/
        mergesort(ord, mid + 1, h, estado); /*segunda metade da tabela*/
        merge(ord, l, mid, h, estado); /*ordena e junta particoes da tabela*/
    }
}


/*##########################################################################################

###################################### Funcoes principais ##################################

###########################################################################################*/

/*Tem o objetivo de definir novos produtos e adiciona los ao sistema*/
void command_a_(PRODUCT sto[DIMPRO], int idp)
{
    sto[idp].idp = idp; 

    scanf(" %[^:]s", sto[idp].describe);
    scanf(":%d:%d:%d", &sto[idp].preco, &sto[idp].peso, &sto[idp].qtd);

    printf("Novo produto %d.\n", idp);
}

/*###########################################################################################*/

/*Tem o objetivo de adicionar stock a um produto ja existente no sistema*/
void command_q_(PRODUCT sto[DIMPRO])
{
    int idp, qtd;

    scanf("%d:%d", &idp, &qtd);
    /*verifica se produto existe no sistema*/
    if (sto[idp].preco != 0)
    {
        sto[idp].qtd += qtd;
    }
    else printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

/*###########################################################################################*/

/*Tem o objetivo de criar uma nova encomenda*/
void command_N_(ENCOMENDA enc[DIMENC], int ide, int ati[DIMENC][DIMEST])
{
    /*ativa a encomenda de identificador ide*/
    ati[ide][EST] = ATIVO;
    enc[ide].ide = ide;

    printf("Nova encomenda %d.\n", enc[ide].ide);
}

/*###########################################################################################################*/

/*Tendo o objetivo de adicionar um novo produto ou adicionar stock a um produto ja existente numa encomenda*/
void command_A_(ENCOMENDA enc[DIMENC], PRODUCT sto[DIMPRO], int ati[DIMENC][DIMEST])
{
    int ide, idp, qtd, prcur, i;
    
    scanf(" %d:%d:%d", &ide, &idp, &qtd); 
    /*verifica se existe encomenda no sistema*/
    if (ati[ide][EST] != ATIVO)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else 
    {
        /*verifica se existe produto no sistema*/
        if (sto[idp].preco == 0)
        {
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }
        else 
        {
            /*verifica se existe quantidade de produto suficiente em stock*/
            if (sto[idp].qtd < qtd)
            {
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
            }
            else 
            {
                /*verifica se ao adicionar produto o peso da encomenda nao passa o limite maximo*/
                if (enc[ide].peso + (sto[idp].peso * qtd) > MAXPESO)
                {
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
                }
                else 
                {
                    /*verifica se nao existe na encomenda o produto a adicionar*/
                    prcur = prcur_aux(enc, idp, ide, ati[ide][ELM]);

                    if (prcur == -1) 
                    {
                        /*procura a posicao seguinte ao ultimo produto existente listado na encomenda*/
                        for(i = 0; i < DIMENC; i++) 
                        {
                            if (enc[ide].pro[i].qtd == 0)
                            {
                                prcur = i;
                                break;
                            }
                        }
                        /*adiciona um novo produto a encomenda*/
                        enc[ide].pro[prcur].idp = sto[idp].idp; 
                        enc[ide].pro[prcur].qtd = qtd;
                        ati[ide][ELM] += 1;
                    }
                    /*adiciona stock ao produto ja existente na encomenda*/
                    else enc[ide].pro[prcur].qtd += qtd;

                    /*retira o stock do produto adicionado a encomenda do sistema*/
                    sto[idp].qtd -= qtd;
                    /*incrementa o peso total do produto adicionado ao peso da encomenda*/
                    enc[ide].peso += sto[idp].peso * qtd;
                }
            }
        }
    }
}

/*###################################################################################################################################*/

/*Tem o objetivo de remover o stock a um produto existente no sistema*/
void command_r_(PRODUCT sto[DIMPRO])
{
    int idp, qtd;

    scanf(" %d:%d", &idp, &qtd);
    /*verifica se existe produto no sistema*/
    if (sto[idp].preco == 0) printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else 
    {
        /*verifca se a quantidade de produto a remover existe em stock*/
        if (sto[idp].qtd < qtd) printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        else sto[idp].qtd -= qtd;
    }
}

/*###############################################################################################################################*/

/*Tem o objetivo de remover um produto existente numa encomenda*/
void command_R_(ENCOMENDA enc[DIMENC], PRODUCT sto[DIMPRO], int ati[DIMENC][DIMEST])
{
    int ide, idp, i, prcur;

    scanf(" %d:%d", &ide, &idp);
    /*verifica se existe encomenda*/
    if (ati[ide][EST] != ATIVO) printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else 
    {   
        /*verifica se existe produto no sistema*/
        if (sto[idp].preco == 0) printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        else
        {
            /*verifica se o produto existe na encomenda*/
            prcur = prcur_aux(enc, idp, ide, ati[ide][ELM]);

            if (prcur != -1)
            {
                /*retira o peso do produto retirado da encomenda*/
                enc[ide].peso -= sto[idp].peso * enc[ide].pro[prcur].qtd;
                /*aumenta o stock do produto retirado ao sistema*/
                sto[idp].qtd += enc[ide].pro[prcur].qtd;

                /*move todos os produtos colocados na posicoes seguintes ao produto eliminado para a posicao anterior aos mesmos*/
                for(i = prcur; i < ati[ide][ELM]; i++) enc[ide].pro[i] = enc[ide].pro[i+1];
                /*retira 1 ao numero de produtos existentes na encomenda*/
                ati[ide][ELM] -= 1;
            }
        }
    }
}

/*##############################################################################################################*/

/*Tem o objetivo de calcular o custo de uma encomenda.*/
void command_C_(ENCOMENDA enc[DIMENC], PRODUCT sto[DIMPRO], int ati[DIMENC][DIMEST])
{
    int ide, i, subtotal = 0, total = 0, prcur;
    scanf(" %d", &ide);
    /*verifica se existe encomenda*/
    if (ati[ide][EST] != ATIVO) printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else 
    {
        for(i = 0; i < DIMPRO; i++)
        {
            /*procura a posicao em que o produto com idp i se encontra na encomenda caso exista*/ 
            prcur = prcur_aux(enc, i, ide, ati[ide][ELM]);

            /*verifica se o produto com idp i existe na encomenda*/
            if (enc[ide].pro[prcur].idp == sto[i].idp)
            {
                subtotal = sto[i].preco * enc[ide].pro[prcur].qtd;
                total += subtotal;
            }
        }
        printf("Custo da encomenda %d %d.\n", ide, total);
    }
}

/*##########################################################################################################*/

/*Tem o objetivo de alterar o preco de um produto existente no sistema*/
void command_p_(PRODUCT sto[DIMPRO])
{
    int idp, preco;

    scanf(" %d:%d", &idp, &preco);
    /*verifica se existe produto no sistema*/
    if (sto[idp].preco == 0) printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else sto[idp].preco = preco;
}

/*###########################################################################################################*/

/*Tem o objetivo de retornar a descricao e a quantidade de um produto existente numa encomenda*/
void command_E_(ENCOMENDA enc[DIMENC], PRODUCT sto[DIMPRO], int ati[DIMENC][DIMEST])
{
    int ide, idp, prcur;

    scanf(" %d:%d", &ide, &idp);
    /*verifica se existem encomenda*/
    if (ati[ide][EST] != ATIVO) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else
    {   
        /*verifica se existe produto no sistema*/
        if (sto[idp].preco == 0) printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        else
        {
            /*verifica se o produto existe ou nao na encomenda*/
            prcur = prcur_aux(enc, idp, ide, ati[ide][ELM]);

            if (prcur != -1) printf("%s %d.\n", sto[idp].describe, enc[ide].pro[prcur].qtd);
            else printf("%s %d.\n", sto[idp].describe, 0);
        }
    }
}

/*################################################################################################################*/

/*Tem o objetivo de listar o identificador da encomenda em que um produto dado ocorre mais vezes*/
void command_m_(ENCOMENDA enc[DIMENC], PRODUCT sto[DIMPRO], int ati[DIMENC][DIMEST])
{
    int idp, a, i, maior = 0, ide = 0; 

    scanf(" %d", &idp);
    /*verifica se existe produto no sistema*/
    if (sto[idp].preco == 0) printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else 
    {
        /*percorre todas as encomendas existentes no sistema*/
        for(a = 0; a < DIMENC; a++)
        {
            /*verifica se a encomenda a existe*/
            if (ati[a][EST])
            {
                /*procura pelo produto idp dentro da encomenda a*/
                for(i = 0; i < ati[a][ELM]; i++)
                {
                    if ((enc[a].pro[i].qtd > maior) && (enc[a].pro[i].idp == idp))
                    {
                        /*caso exista maior quantidade guarda a quantidade em maior e o ide da encomenda em ide*/
                        maior = enc[a].pro[i].qtd;
                        ide = a;
                    }
                }
            }
            else break;
        }
        if (maior != 0) printf("Maximo produto %d %d %d.\n", idp, ide, maior);
    }
}

/*###########################################################################################################*/

/*Tem o objetivo de listar todos os produtos existentes no sistema por ordem crescente de preco*/
void command_l_(PRODUCT sto[DIMPRO], int idp)
{
    int p, n;
    PRODUCT ord[DIMPRO];

    /*criacao da tabela ord que guarda todos os produtos existentes no sistema*/
    for(n = 0; n <= idp; n++) 
    {
        ord[n] = sto[n];
    }
    /*chamada da funcao de ordenacao mergesort para ordenar a tabela ord por ordem crecente de preco*/
    mergesort(ord, 0, idp, ATIVO);

    printf("Produtos\n");

    for(p = 0; p < idp + 1; p++)
    {   
        printf("* %s %d %d\n", sto[ord[p].idp].describe, sto[ord[p].idp].preco, sto[ord[p].idp].qtd);
    }
}

/*#########################################################################################################*/

/*Tem o objetivo de listar por ordem alfabetica da descricao dos produtos de uma certa encomenda*/
void command_L_(ENCOMENDA enc[DIMENC], PRODUCT sto[DIMPRO], int ati[DIMENC][DIMEST], int idp)
{
    int ide, p, e, prcur;
    PRODUCT ord[DIMENC];

    scanf(" %d", &ide);
    /*verifica se existe encomenda*/
    if (ati[ide][EST] != ATIVO) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

    else 
    {
        /*criacao da tabela ord que guarda todos os produtos existentes numa encomenda*/
        for(e = 0; e < ati[ide][ELM]; e++) 
        {
        /*percorre todos os produtos do sistema ate encontrar o mesmo produto existente na encomenda na posicao e*/
            for(p = 0; p <= idp; p++)
            {   
                if (enc[ide].pro[e].idp == sto[p].idp)
                {
                    ord[e] = sto[p];
                    break;
                }
            }
        }

        /*chamada da funcao mergesort que ordena todos os produtos da tabela ord em ordem alfabetica da descricao*/
        mergesort(ord, 0, ati[ide][ELM]-1, DESATIVO);
        
        printf("Encomenda %d\n", ide);

        for(p = 0; p < ati[ide][ELM]; p++)
        {
            /*procura a posicao em que o produto com idp de ord[p] se encontra na encomenda*/ 
            prcur = prcur_aux(enc, ord[p].idp, ide, ati[ide][ELM]);

            printf("* %s %d %d\n", ord[p].describe, ord[p].preco, enc[ide].pro[prcur].qtd);
        }
    }
}

/*###################################### FIM DE CODIGO ##############################################*/
