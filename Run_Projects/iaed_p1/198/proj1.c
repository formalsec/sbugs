#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXNOME 64      /*Numero maximo de caracteres num nome de um produto.*/
#define MAXPROD 10000   /*Numero maximo de produtos criados.*/ 
#define MAXENC 500      /*Numero maximo de encomendas.*/
#define PRODS 200       /*Numero maximo de produtos numa encomenda.*/
#define EXIST 1         /*Define se uma entidade que se procura existe.*/
#define N_EXIST 0       /*Define se uma entidade que se procura nao existe.*/
#define N_COLOCADO -1   /*Define se um lugar de uma encomenda ainda nao foi ocupado.*/



typedef struct producto{
    long int idp;               /*Identificador de um produto.*/
    char descricao[MAXNOME];    /*Descricao/nome de um produto.*/
    long int preco;             /*Preco de um produto.*/
    long int peso;              /*Peso de um produto.*/
    long int qtd;               /*Quantidade de um produto em stock.*/
} produto;

typedef struct enc{
    long int ide;               /*Identificador de uma encomenda.*/
    long int id[PRODS];         /*Vetor que guarda os indices dos produtos adicionados a respetiva encomenda.*/
    long int quant[PRODS];      /*Vetor que guarda as quantidades dos produtos adicionados, na entrada com o mesmo indice daquela em que se encontra o respetivo id.*/
    long int indice;            /*Guarda qual o proximo indice de vetor a ser ocupado nos dois vetores anteriores.*/
} encomenda;

/*FUNCOES PRINCIPAIS (A sua descricao encontra-se junto ao seu codigo).*/
void funcao_a(produto[], long int[]);
void funcao_q(produto[], long int[]);
void funcao_N(long int[], encomenda[]);
void funcao_A(encomenda[], produto[], long int[], long int[]);
void funcao_r(long int[], produto[]);
void funcao_R(encomenda[], produto[], long int[], long int[]);
void funcao_C(encomenda[], produto[], long int[]);
void funcao_p(long int[], produto[]);
void funcao_E(encomenda[], produto[], long int[], long int[]);
void funcao_m(encomenda[], long int[], long int[]);
void funcao_l(produto[], long int[]);
void funcao_L(produto[], encomenda[], long int[]);

/*FUNCOES AUXILIARES - ajudam no funcionamento das principais.*/
int aux_exist_prod(long int, long int[]);
int aux_exist_enc(long int[], long int);
int aux_exist_stock(produto[], long int, long int);
long int aux_peso_enc(produto[], encomenda[], long int);
void selectionsort1(produto[], long int[], long int);
void selectionsort2(produto[], long int[], long int[], long int);

int main()
{
    char c[2];    
    produto sistema[MAXPROD];           /*Vetor que guardara todos os produtos criados.*/
    encomenda encom[MAXENC];            /*Vetor que guardara todas as encomendas criadas.*/
    long int sistema_ocup[MAXPROD];     /*Vetor que regista os produtos criados: entrada do indice do produto a 0, se o produto nao existir, e 1 se existir.*/
    long int encomendas_ocup[MAXENC];   /*Vetor que regista as encomendas criadas: entrada do indice da encomenda a 0, se ela nao existir, e 1 se existir.*/
    c[1]='\0';
    scanf("%c", &c[0]);
    while (c[0] != EOF)
    {
        switch(c[0]){
            case 'a':
                funcao_a(sistema, sistema_ocup);
                break;

            case 'q':
                funcao_q(sistema, sistema_ocup);
                break;

            case 'N':
                funcao_N(encomendas_ocup, encom);
                break;

            case 'A':
                funcao_A(encom, sistema, encomendas_ocup, sistema_ocup);
                break;

            case 'r':
                funcao_r(sistema_ocup, sistema);
                break;

            case 'R':
                funcao_R(encom, sistema, sistema_ocup, encomendas_ocup);
                break;

            case 'C':
                funcao_C(encom, sistema, encomendas_ocup);
                break;

            case 'p':
                funcao_p(sistema_ocup, sistema);
                break;

            case 'E':
                funcao_E(encom, sistema, encomendas_ocup, sistema_ocup);
                break;

            case 'm':
                funcao_m(encom, sistema_ocup, encomendas_ocup);
                break;

            case 'l':
                funcao_l(sistema, sistema_ocup);
                break;

            case 'L':
                funcao_L(sistema, encom, encomendas_ocup);
                break;

            case 'x':
                exit(0);      
        } 
    scanf("%c", &c[0]);
    }

    return 0;
}

/*Cria um novo produto e adiciona-o ao sistema.*/
void funcao_a(produto sist[MAXPROD], long int ocupados[MAXPROD])
{
    char nome[MAXNOME];
    long int prc, pes, quant;
    static  long int ind = 0;                               /*Este inteiro guarda qual o indice do proximo produto a ser criado.*/
    scanf(" %[^:]:%ld:%ld:%ld", nome, &prc, &pes, &quant);   
    sist[ind].idp = ind;
    strcpy(sist[ind].descricao, nome);                                                                      
    sist[ind].preco = prc;
    sist[ind].peso = pes;
    sist[ind].qtd = quant;
    ocupados[ind] = EXIST;                                  /*Guarda no vetor proprio que o produto de identificador ind existe.*/    
    printf("Novo produto %ld.\n", ind);
    ++ind;
}

/*Adiciona stock a um produto existente no sistema.*/
void funcao_q(produto sist[MAXPROD], long int ocupados[MAXPROD])
{
    long int quant, iprd;
    scanf("%ld:%ld", &iprd, &quant);
    if (ocupados[iprd] != 0)
        sist[iprd].qtd += quant;
    else
        printf("Impossivel adicionar produto %ld ao stock. Produto inexistente.\n", iprd);
}

/*Cria uma nova encomenda.*/
void funcao_N(long int vetor_encomendas[MAXENC], encomenda conj_enc[MAXENC])
{
    static long int enc_n = 0;              /*Este inteiro guarda qual o indice da proxima encomenda a ser criada.*/
    long int i;
    printf("Nova encomenda %ld.\n", enc_n);
    conj_enc[enc_n].indice = 0;
    conj_enc[enc_n].ide = enc_n;
    vetor_encomendas[enc_n] = EXIST;        /*Guarda no vetor proprio que a encomenda de identificador enc_n existe.*/
    for (i=0; i<PRODS; i++)
    {
        conj_enc[enc_n].id[i] = N_COLOCADO;         /*Como 0 e um indice valido de um produto, o vetor de indices e todo iniciado a -1, para evitar erros.*/
        conj_enc[enc_n].quant[i] = N_COLOCADO; 
    }
    enc_n++;
}

/*Adiciona um novo produto ou uma quantidade adicional de um produto a uma encomenda.*/ 
void funcao_A(encomenda conj_enc[MAXENC], produto sist[MAXPROD], long int encs_exist[MAXENC], long int prods_exist[MAXPROD])
{
    long int iprd, ienc, quantd;
    scanf("%ld:%ld:%ld", &ienc, &iprd, &quantd);
    
    if (aux_exist_enc(encs_exist, ienc) == N_EXIST)
        printf("Impossivel adicionar produto %ld a encomenda %ld. Encomenda inexistente.\n", iprd, ienc);
    else if (aux_exist_prod(iprd, prods_exist) == N_EXIST)
        printf("Impossivel adicionar produto %ld a encomenda %ld. Produto inexistente.\n", iprd, ienc);
    else if (aux_exist_stock(sist, iprd, quantd) == N_EXIST)
        printf("Impossivel adicionar produto %ld a encomenda %ld. Quantidade em stock insuficiente.\n", iprd, ienc);
    else if (aux_peso_enc(sist, conj_enc, ienc) + (quantd*(sist[iprd].peso)) > 200)
        printf("Impossivel adicionar produto %ld a encomenda %ld. Peso da encomenda excede o maximo de 200.\n", iprd, ienc);
    else    
    {
        int i, estado;
        long int ind;
        estado = N_EXIST;                           /*Inicialmente, um produto e considerado como nao existente numa encomenda.*/
        i = 0;        
        ind = conj_enc[ienc].indice;
        sist[iprd].qtd -= quantd; 
        for (i = 0; i<ind ; i++)
        {
            if (conj_enc[ienc].id[i] == iprd)       /*Verifica-se o identificador do produto que se pretende adicionar ja existe na encomenda.*/
            {
                estado = EXIST;                     
                conj_enc[ienc].quant[i] += quantd;  /*Se o produto existir, e adicionada a quantidade ja existente a quantidade inserida.*/              
            }            
        }
        if (estado == N_EXIST)                      /*Se o produto ainda nao existe na encomenda, ira passar a ocupar a primeira posicao livre dentro desta.*/
        {
            conj_enc[ienc].id[ind] = iprd;          /* Identificador do produto colocado no vetor de identificadores.*/
            conj_enc[ienc].quant[ind] = quantd;     /* Quantidade do produto colocado na entrada correspondente no vetor de quantidades.*/
            ++conj_enc[ienc].indice;            
        }       
    }
}

/*Remove stock a um produto existente.*/
void funcao_r(long int ocupados[MAXPROD], produto sist[MAXPROD])
{
    long int iprd, quant;
    scanf("%ld:%ld", &iprd, &quant);
    if (ocupados[iprd] == N_EXIST)
        printf("Impossivel remover stock do produto %ld. Produto inexistente.\n", iprd);
    else if ((sist[iprd].qtd - quant) < 0)
        printf("Impossivel remover %ld unidades do produto %ld do stock. Quantidade insuficiente.\n", quant, iprd);
    else
        sist[iprd].qtd -= quant;    
}

/*Remove um produto a uma encomenda.*/
void funcao_R(encomenda conj_enc[MAXENC], produto sist[MAXPROD], long int prods_exist[MAXPROD], long int encs_exist[MAXENC])
{
    long int ienc, iprd;
    scanf("%ld:%ld", &ienc, &iprd);
    if (aux_exist_enc(encs_exist, ienc) == N_EXIST)
        printf ("Impossivel remover produto %ld a encomenda %ld. Encomenda inexistente.\n", iprd, ienc);
    else if (aux_exist_prod(iprd, prods_exist) == N_EXIST)
        printf ("Impossivel remover produto %ld a encomenda %ld. Produto inexistente.\n", iprd, ienc);
    else
    {
        long int ini, i_prod_enc, ind_p, a, estado;
        ind_p = conj_enc[ienc].indice;
        estado = N_EXIST;                                               /*Inicialmente considera-se que o produto que se pretende remover nao esta na encomenda.*/
        for (i_prod_enc = 0; i_prod_enc < ind_p; i_prod_enc++)
        {
            if (conj_enc[ienc].id[i_prod_enc] == iprd)
            {
                a = i_prod_enc;
                estado = EXIST;
                sist[iprd].qtd += conj_enc[ienc].quant[i_prod_enc];     /*O produto e definido como existente na encomenda,*/ 
                                                                        /*e a posicao do seu indice e quantidade e guardada. */          
            }              
        }
        if (estado == EXIST)                                            /*Se o produto existir, todos os produtos inseridos apos aquele que se vai retirar passam a*/
                                                                        /*estar guardados na posicao anterior, de forma a nao existirem espacos vazios entre produtos.*/
        { 
            for (ini = a; ini < ind_p-1; ini++)
            {
                conj_enc[ienc].id[ini] = conj_enc[ienc].id[ini+1];
                conj_enc[ienc].quant[ini] = conj_enc[ienc].quant[ini+1];            
            }
            --conj_enc[ienc].indice;
        }
    }
}

/*Calcula o custo de uma encomenda.*/
void funcao_C(encomenda conj_enc[MAXENC], produto sist[MAXPROD], long int encs_exist[MAXENC])
{
    long int ienc;
    scanf("%ld", &ienc);
    if (aux_exist_enc(encs_exist, ienc) == N_EXIST)
        printf("Impossivel calcular custo da encomenda %ld. Encomenda inexistente.\n", ienc);
    else
    {
        int i_prd_enc, ind_p, preco_t;
        long int idprd;
        preco_t = 0;
        ind_p = conj_enc[ienc].indice;
        for(i_prd_enc = 0; i_prd_enc < ind_p; i_prd_enc++)
        {
            idprd = conj_enc[ienc].id[i_prd_enc]; 
            preco_t += (conj_enc[ienc].quant[i_prd_enc])*(sist[idprd].preco);
        }   
        printf("Custo da encomenda %ld %d.\n", ienc, preco_t);
    }    
}

/*Altera o preco de um produto existente no sistema.*/
void funcao_p(long int ocupados[MAXPROD], produto sist[MAXPROD])
{
    long int iprd, prc;
    scanf("%ld:%ld", &iprd, &prc);
    if (ocupados[iprd] == N_EXIST)
        printf("Impossivel alterar preco do produto %ld. Produto inexistente.\n", iprd);
    else
        sist[iprd].preco = prc;    
}

/*Lista a descricao e a quantidade de um produto numa encomenda.*/
void funcao_E(encomenda conj_enc[MAXENC], produto sist[MAXPROD], long int encs_exist[MAXENC], long int prods_exist[MAXPROD])
{
    long int ienc, iprd;
    scanf("%ld:%ld", &ienc, &iprd);
    if (aux_exist_enc(encs_exist, ienc) == N_EXIST)
        printf("Impossivel listar encomenda %ld. Encomenda inexistente.\n", ienc);
    else if (aux_exist_prod(iprd, prods_exist) == N_EXIST)
        printf("Impossivel listar produto %ld. Produto inexistente.\n", iprd);
    else
    {
        long int quantd, estado;
        int i_prd_enc, ind_p;
        estado = N_EXIST;
        ind_p = conj_enc[ienc].indice;
        for(i_prd_enc = 0; (i_prd_enc < ind_p) && estado == N_EXIST; i_prd_enc++)
        {
            if (conj_enc[ienc].id[i_prd_enc] == iprd)
            {
                estado = EXIST;
                quantd = conj_enc[ienc].quant[i_prd_enc];
                printf("%s %ld.\n", sist[iprd].descricao, quantd); 
            }                       
        }
        if (estado == N_EXIST)
            printf("%s %d.\n", sist[iprd].descricao, 0);       
    }       
}

/*Indica qual a encomenda em que um produto surge mais vezes.*/
void funcao_m(encomenda conj_enc[MAXENC], long int prods_exist[MAXPROD], long int encs_exist[MAXENC])
{
    long int iprd;
    scanf ("%ld", &iprd);
    if (aux_exist_prod(iprd, prods_exist) == N_EXIST)
        printf("Impossivel listar maximo do produto %ld. Produto inexistente.\n", iprd);
    else
    {
        long int res_enc, quantd, id_enc, i_prod_enc, ind_p;
        res_enc = 0;
        quantd = N_COLOCADO;        
        for (id_enc=0; encs_exist[id_enc] != 0; id_enc++)
        {
            ind_p = conj_enc[id_enc].indice;
            for (i_prod_enc = 0; i_prod_enc < ind_p; i_prod_enc++)
            {
                if ((conj_enc[id_enc].id[i_prod_enc] == iprd) && (conj_enc[id_enc].quant[i_prod_enc] > quantd))
                {
                    quantd = conj_enc[id_enc].quant[i_prod_enc];
                    res_enc = id_enc;
                }
            }
        }
        if (quantd != N_COLOCADO)
            printf ("Maximo produto %ld %ld %ld.\n", iprd, res_enc, quantd);   
    }    
}

/*Lista todos os produtos no sistema por ordem crescente de preco.*/
void funcao_l(produto sist[MAXPROD], long int prods_exist[MAXPROD])
{
    long int contador, i;
    long int aux[MAXPROD];
    contador = 0;
    for (i=0; prods_exist[i]!=0; i++)
    {
        ++contador;
        aux[i] = sist[i].idp;           /*E criado um vetor com os identificadores dos produtos criados.*/
    }        

    selectionsort1(sist, aux, contador);   
    printf ("Produtos\n");    

    for(i=0; i<contador; i++)
    {
        printf("* %s %ld %ld\n", sist[aux[i]].descricao, sist[aux[i]].preco, sist[aux[i]].qtd);       
    }
}

/*Lista todos os produtos de uma encomenda por ordem alfabetica.*/
void funcao_L(produto sist[MAXPROD], encomenda conj_enc[MAXENC], long int encs_exist[MAXENC])
{
    long int ienc;
    scanf("%ld", &ienc);
    if (aux_exist_enc(encs_exist, ienc) == N_EXIST)
        printf ("Impossivel listar encomenda %ld. Encomenda inexistente.\n", ienc);
    else
    {
        long int iprd, ind_p, i, iprd2;
        long int aux[PRODS], aux2[PRODS];   /*aux e um vetor que guarda os indices dos produtos numa encomenda.*/
        ind_p = conj_enc[ienc].indice;      /*aux2 e um vetor que guarda em que entrada do vetor de indices de uma*/
                                            /*encomenda se encontra um certo indice. Complementa aux.*/          
        for (i=0; i<ind_p; i++)
        { 
            aux[i] = conj_enc[ienc].id[i];
            aux2[i] = i;
        }        
        
        selectionsort2(sist, aux, aux2, ind_p);
        printf("Encomenda %ld\n", ienc);

        for (i = 0; i < ind_p; i++)
        {
            iprd = aux[i];
            iprd2 = aux2[i];
            printf("* %s %ld %ld\n", sist[iprd].descricao, sist[iprd].preco, conj_enc[ienc].quant[iprd2]);
        }
    }    
}

/*Verifica se um produto com um dado identificador existe.*/
int aux_exist_prod(long int indice, long int vetor_prods[MAXPROD])
{
    if (vetor_prods[indice] == N_EXIST)
        return 0;
    else
        return 1;
}

/*Verifica se uma encomenda com um dado identificador existe.*/
int aux_exist_enc(long int vetor_encs[MAXENC], long int indice)
{
    if (vetor_encs[indice] == N_EXIST)
        return 0;
    else 
        return 1;
}

/*Verifica se existe a quantidade de stock pretendida.*/
int aux_exist_stock(produto sist[MAXPROD], long int id_produto, long int quantidade)
{
    if (sist[id_produto].qtd < quantidade)
        return 0;
    else 
        return 1;
}

/*Calcula o peso de uma encomenda.*/
long int aux_peso_enc(produto sist[MAXPROD], encomenda conj_enc[MAXENC], long int id_enc)
{
    int i_prd_enc, ind_p, peso_t;
    long int idprd;
    peso_t = 0;
    ind_p = conj_enc[id_enc].indice;
    for(i_prd_enc = 0; i_prd_enc < ind_p; i_prd_enc++)
    {
        idprd = conj_enc[id_enc].id[i_prd_enc]; 
        peso_t += (conj_enc[id_enc].quant[i_prd_enc])*(sist[idprd].peso);
    }
    return peso_t;
}

/*Organiza um vetor de identificadores de produtos, com base no preco a eles associado.*/
void selectionsort1(produto sist[MAXPROD], long int vetor_num[], long int right)
{
    long int i, j;
    long int auxx, min;
    for (i=0; i < right-1; i++)
    {
        min = i;
        for (j=i+1; j < right; j++)
        {
            if (sist[vetor_num[j]].preco<sist[vetor_num[min]].preco) 
                min = j;
            else if ((sist[vetor_num[j]].preco == sist[vetor_num[min]].preco) && sist[vetor_num[j]].idp<sist[vetor_num[min]].idp)
            /*No caso de os precos serem iguais, verifica-se qual o produto com o menor identificador.*/
                min = j;
        }
        auxx = vetor_num[i];
        vetor_num[i]=vetor_num[min];
        vetor_num[min]=auxx;
    }
}

/*Organiza um vetor de indices e um vetor de identificadores.*/
void selectionsort2(produto sist[MAXPROD], long int vetor_num[], long int vetor_inds[], long int right)
{
    long int i, j;
    long int auxx, min, min2, auxx2;
    int result;
    for (i=0; i<right-1; i++)
    {
        min = i;
        min2 = i;
        for (j=i+1; j<right; j++)
        {
            result = strcmp(sist[vetor_num[j]].descricao, sist[vetor_num[min]].descricao);
            if (result < 0)
            { 
                min = j;
                min2 = j;
            }
        }
        auxx = vetor_num[i];
        auxx2 = vetor_inds[i];

        vetor_num[i]=vetor_num[min];
        vetor_inds[i]=vetor_inds[min2];

        vetor_num[min]=auxx;
        vetor_inds[min2]=auxx2;
    }
}