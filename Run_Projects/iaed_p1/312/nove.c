#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* directivas de pre-compilador, definicao de tipos/estruturas, variaveis globais, etc. */

#define MAX_CARACTERES 63
#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define max_PESO_E 200


/* definicao da estrutura Produto e Encomenda onde sao definidos todos os tipos necessarios a resolucao do projeto*/

typedef struct
 {
    int identificador;
    char descricao[MAX_CARACTERES];
    int preco;
    int peso;
    int quant_stk;
}Produto;

typedef struct
{
    int identificador_encomenda;
    int peso_encomenda;
    int n_produtos;
    Produto produtosEncomenda[200];
}Encomenda;

/* Globais */
Produto p1;
Produto produtos[MAX_PRODUTOS];
Encomenda Encomendas[MAX_ENCOMENDAS];
Encomenda e1;
int idp = 0; /* contar o numero de produtos e ir identificando os */
int ide =0; /* contar o numero de encomendas */



/*comandos a executar*/
void a(){

    int preco,peso,quant_stk;

    scanf("%[^:]:%d:%d:%d",p1.descricao,&preco,&peso,&quant_stk);

    p1.preco = preco;
    p1.peso=peso;
    p1.quant_stk=quant_stk;
    p1.identificador = idp;
    produtos[idp] = p1;

    printf("Novo produto %d.\n",p1.identificador);

    idp++; /* proximo que entrar no sistema */
}


void q(){

    int identifi,quantidade;

    scanf("%d:%d",&identifi,&quantidade);

    p1.identificador=identifi;

    if (identifi<=idp) /* se existir aumento quantidade_stock */
        p1.quant_stk = quantidade + p1.quant_stk;

    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",identifi);
}

void N(){

    e1.identificador_encomenda = ide;
    Encomendas[ide] = e1;
    Encomendas[ide].n_produtos=0;

    printf("Nova encomenda %d.\n",ide);

    ++ide;
}


void A(){

    int iden_enc,ide_pro,qtd;
    int percorrer;

    scanf("%d:%d:%d",&iden_enc,&ide_pro,&qtd);

    if (iden_enc > ide)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",ide_pro,iden_enc);

     if(ide_pro > idp)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",ide_pro,iden_enc);

     if (qtd > produtos[ide_pro].quant_stk)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",ide_pro,iden_enc);

     if (Encomendas[iden_enc].peso_encomenda + (produtos[ide_pro].peso * (qtd)) > max_PESO_E)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",ide_pro,iden_enc);

    /*percorrer produtos da encomenda e verificar se o produto ja existia */
    for (percorrer = 0;percorrer < Encomendas[iden_enc].n_produtos;percorrer++)
    {
        if (Encomendas[iden_enc].produtosEncomenda[percorrer].identificador == ide_pro)
        {
            Encomendas[iden_enc].produtosEncomenda[percorrer].quant_stk += qtd;
            Encomendas[iden_enc].peso_encomenda += (produtos[ide_pro].peso * qtd); /* aumentar o peso da encomenda */
            produtos[ide_pro].quant_stk -= qtd; /* reduzir o stock do produto no sistema , hipotese de chamar r()*/
        }
    }
    /* se o produto nao existir ainda na encomenda adiciono */
    Encomendas[iden_enc].produtosEncomenda[Encomendas[iden_enc].n_produtos] = produtos[ide_pro];
    Encomendas[iden_enc].produtosEncomenda[Encomendas[iden_enc].n_produtos].quant_stk = qtd;
    Encomendas[iden_enc].n_produtos = Encomendas[iden_enc].n_produtos + 1 ;
    Encomendas[iden_enc].peso_encomenda += (produtos[ide_pro].peso) * qtd; /* aumentar o peso da encomenda */
    produtos[ide_pro].quant_stk -= qtd; /* reduzir o stock do produto no sistema */

    }


void r(){

    int identifi,quantidade;

    scanf("%d:%d",&identifi,&quantidade);

    if (identifi>idp)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",identifi);

    if (produtos[identifi].quant_stk < quantidade)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",quantidade,identifi);

    produtos[identifi].quant_stk -= quantidade ; /*reduzir quantidade indicada , se o produto existir*/

}

void R(){

    int iden_enc,ide_pro;
    int i;

    scanf("%d:%d",&iden_enc,&ide_pro);

    if (iden_enc > ide)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",ide_pro,iden_enc);

     if(ide_pro > idp)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",ide_pro,iden_enc);

    for(i=0;i<Encomendas[iden_enc].n_produtos;i++)
    {
        if (Encomendas[iden_enc].produtosEncomenda[i].identificador == ide_pro)
        {
            Encomendas[iden_enc].produtosEncomenda[i].peso =0; /*por peso = 0 se apagar da encomenda*/
            produtos[ide_pro].quant_stk ++;
        }

    }
}

void C(){

    int idencom;
    int i;
    int custo;

    scanf("%d",&idencom);

    if (idencom > ide)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",idencom);
    else {
        for (i=0;i<Encomendas[idencom].n_produtos;i++)
        {
            custo +=((Encomendas[idencom].produtosEncomenda[i].preco)*Encomendas[idencom].produtosEncomenda[i].quant_stk);
        }
    }
    printf("Custo da encomenda %d %d\n",idencom,custo);

}

void p(){
    int p,idpr;

    scanf("%d:%d",&idpr,&p);

    if (idpr > idp)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idpr);
    else
        produtos[idpr].preco = p;
}

void E(){
    int iden,ip;
    int quantidade;
    int i;

    scanf("%d:%d",&iden,&ip);

    if (iden > ide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",iden);
    else if (ip>idp)
        printf("Impossivel listar produto %d. Produto inexistente.\n",ip);

    for (i = 0;i < Encomendas[iden].n_produtos;i++)
        {
            if (Encomendas[iden].produtosEncomenda[i].identificador == ip)
                quantidade = Encomendas[iden].produtosEncomenda[i].quant_stk;
        }
        printf("%s %d\n",produtos[ip].descricao,quantidade);

}

void m(){

    printf("erro");
}


void l()
{
    printf("erro");
}
void L()
{
    printf("erro");
}


int main()
{
    char comando;

    while((comando = getchar()) != 'x' ){
        switch(comando){
        case 'a':
            a(); /* Executa o comando a */
            break;
        case 'q':
            q(); /* Executa o comando q */
            break;
        case 'N':
            N(); /* Executa o comando N */
            break;
        case 'A':
            A(); /* Executa o comando A */
            break;
        case 'r':
            r(); /* Executa o comando r */
            break;
        case 'R':
            R(); /* Executa o comando R */
            break;
        case 'C':
            C(); /* Executa o comando C */
            break;
        case 'p':
            p(); /* Executa o comando P */
            break;
        case 'E':
            E(); /* Executa o comando E */
            break;
        case 'm':
            m(); /* Executa o comando m */
            break;
        case 'l':
            l(); /* Executa o comando l */
            break;
        case 'L':
            L(); /* Executa o comando L */
            break;
        }
        getchar(); /* le o '\n' introduzido pelo utilizador */
    }
    return 0; /* done */
}
