#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_P 10000     /*maximo de produtos*/
#define MAX_E 500       /*maximo de encomendas*/
#define MAX_PESO 200    /*maximo de peso de uma encomenda*/
#define OCUPADO 1       /*usado no estado (ocupado)*/

/*um produto tem descricao, preco, peso, quantidade e um id*/
typedef struct produto
{
    char descricao[63];
    int preco;
    int peso;
    int qtd;
    int idp;

} produto;

/*uma encomenda tem o estado (ocupada/nao iniciada), peso total, e um id*/
typedef struct encomenda 
{   
    int ide;
    int estado;
    int pesoTotal;

} encomenda;

/*inicializa globalmente uma tabela de produtos(tabP), uma tabela de encomendas(tabE), 
uma tabela com os ide e os respetivos produtos e quantidades(tabela_id) e os ids(idp,ide)*/
produto tabP[MAX_P];
encomenda tabE[MAX_E];
int tabela_id[MAX_E][MAX_PESO][2] = {0};
int idp = 0;
int ide = 0;

/*--------------------------------------------------------FUNCOES------------------------------------------------------------------------*/

void cria_produto()
{
    char descricao[63];
    int preco, peso, qtd;
    scanf(" %[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);
    strcpy(tabP[idp].descricao, descricao);
    tabP[idp].preco = preco;
    tabP[idp].peso = peso;
    tabP[idp].qtd = qtd;
    tabP[idp].idp = idp;
    printf("Novo produto %d.\n", idp);
    idp++;
    return;
}

void add_stock()
{
    int n_idp, novaqtd;
    scanf(" %d:%d", &n_idp, &novaqtd);
    
    if (n_idp > idp - 1)
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", n_idp);
    }
    else
    {
        tabP[n_idp].qtd += novaqtd;
    }

    return;
}

void cria_encomenda()
{
    tabE[ide].estado = OCUPADO;
    tabE[ide].ide = ide;
    tabE[ide].pesoTotal = 0;
    printf("Nova encomenda %d.\n", ide);
    ide++;
    return;
}

void add_produto()
{
    int n_ide, n_idp, qtd, i = 0, id_nada = -1;
    scanf(" %d:%d:%d", &n_ide, &n_idp, &qtd);
    
    if (tabE[n_ide].estado == OCUPADO)
    {
        if (n_idp > idp - 1) printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",n_idp,n_ide);
        else if (tabP[n_idp].qtd < qtd) printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",n_idp,n_ide);
        else if((tabE[n_ide].pesoTotal + qtd*tabP[n_idp].peso) > 200) printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",n_idp,n_ide);
        
        else
        {    /*ciclo que percorre a tabela que contem os produtos da encomenda*/
            /*para quando encontra o produto com o idp desejado(caso esteja la) ou ate chegar ao fim da tabela*/
            for (i = 0; i <= MAX_PESO - 1; i++)
            {   
                /*verifica se nao ? um sitio vazio*/
                if (tabela_id[n_ide][i][0] == n_idp && tabela_id[n_ide][i][1] != 0)      
                {
                    /*caso o produto ja esteja na encomenda*/
                    tabela_id[n_ide][i][1] += qtd; 
                    tabP[n_idp].qtd -= qtd;
                    tabE[n_ide].pesoTotal += tabP[n_idp].peso * qtd;
                    return;
                }
                if (tabela_id[n_ide][i][0] == 0 && tabela_id[n_ide][i][1] == 0) id_nada = i;
            }
            
            /*caso o produto ainda nao esteja na encomenda coloca no ultimo espaco vazio verificado no for anterior*/
            if (id_nada != -1)
            {
                tabela_id[n_ide][id_nada][0] = n_idp;
                tabela_id[n_ide][id_nada][1] = qtd;
                tabE[n_ide].pesoTotal += tabP[n_idp].peso * qtd;
            }
            
            tabP[n_idp].qtd -= qtd;
        }
        return;
    }
    else
        {printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", n_idp, n_ide);};
    return;
}

void r_stock()
{
    int n_idp, qtd;
    scanf(" %d:%d", &n_idp, &qtd);
    if (n_idp > idp - 1) printf("Impossivel remover stock do produto %d. Produto inexistente.\n", n_idp);
    else if (tabP[n_idp].qtd < qtd) printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,n_idp);
    else 
    {
        tabP[n_idp].qtd -= qtd;
    }
    return;
}

void r_produto ()
{
    int n_ide, n_idp, i;
    scanf(" %d:%d", &n_ide, &n_idp);
    if (tabE[n_ide].estado != OCUPADO) printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",n_idp,n_ide);
    else if (n_idp > idp - 1) printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",n_idp,n_ide);
    else 
    {
        for (i = 0; i <= MAX_PESO - 1; i++)
        {
            /*percorre a tabela_id a procura do produto*/
            if (tabela_id[n_ide][i][0] == n_idp && tabela_id[n_ide][i][1] != 0)
            {
                /*adiciona de volta ao stock a qtd que estava na encomenda*/
                tabP[n_idp].qtd += tabela_id[n_ide][i][1];
                
                /*o sitio do produto (idp) e qtd passa para o estado inicial e retira se o peso*/
                tabE[n_ide].pesoTotal -= tabP[tabela_id[n_ide][i][0]].peso * tabela_id[n_ide][i][1];
                tabela_id[n_ide][i][0] = 0;
                tabela_id[n_ide][i][1] = 0;
                return;
            }
        }
    }
    return;
}

void custo()
{
    int n_ide,i,custo = 0;
    scanf(" %d", &n_ide);
    /*so faz caso a encomenda esteja no estado ocupado*/
    if (tabE[n_ide].estado == OCUPADO)
    {
        /*percorre a tabela_id e quando encontra um produto add ao custo*/
        for (i= 0; i <= MAX_PESO - 1; i++)
        {
            if (tabela_id[n_ide][i][0] == 0 && tabela_id[n_ide][i][1] == 0) {continue;}
            else
            {
                custo += tabP[tabela_id[n_ide][i][0]].preco * tabela_id[n_ide][i][1];
            }
        }
        printf("Custo da encomenda %d %d.\n",n_ide, custo);
    }
    else
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",n_ide);
    }
    return;
}

void muda_preco()
{
    int n_idp, preco, i;
    scanf(" %d:%d", &n_idp, &preco);
    /*percorre a tabela de produtos a procura do produto*/
    for (i = 0; i <= MAX_P - 1 ; i++)
    {
        if (tabP[i].idp == n_idp)
        {
            tabP[n_idp].preco = preco;
            return;
        }
    }
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",n_idp);
    return;
}

void lista_E()
{
    int n_ide,n_idp,i;
    scanf(" %d:%d", &n_ide, &n_idp);
    /*verifica se o produto existe e se a encomenda esta no estado ocupado*/
    if (n_idp > idp - 1) printf("Impossivel listar produto %d. Produto inexistente.\n",n_idp);
    else if (tabE[n_ide].estado != OCUPADO) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",n_ide);
    else
    {
        /*percorre a tabela_id e cada vez que encontra um produto da print da descricao e da qtd na encomenda*/
        for(i = 0; i <= (MAX_PESO - 1); i++)
        {
            if(tabela_id[n_ide][i][0] == n_idp && tabela_id[n_ide][i][1] != 0)
            {
            printf("%s %d.\n",tabP[n_idp].descricao, tabela_id[n_ide][i][1]);
            return;
            }
        }
        printf("%s %d.\n",tabP[n_idp].descricao, 0);
    }
    return;
}

void maximo_produto()
{
    int n_idp, i, p, maximo_qtd1 = 0, maximo_qtd2 = 0, maximo_ide;
    scanf(" %d", &n_idp);
    if (n_idp > idp - 1) printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",n_idp);
    else
    {   
        /*percorre a tabela de encomendas*/
        for(i = 0; (i <= MAX_E - 1) && tabE[i].estado == OCUPADO; i++)
        {   
            /*caso a encomenda exista percorre os produtos ate encontrar o que deseja (caso haja)*/
            for(p = 0; (p <= MAX_PESO - 1); p++)
            {
                if (tabela_id[i][p][0] == n_idp && tabela_id[i][p][1] != 0)
                {   
                     maximo_qtd1 = tabela_id[i][p][1];
                        
                    /*atualiza a quantidade, o idp e o ide caso a qtd seja superior a anterior*/
                    if (maximo_qtd1 > maximo_qtd2)
                    {
                        maximo_qtd2 = maximo_qtd1;
                        maximo_ide = i;
                        break;
                    }
                }
            }
        }
        if (maximo_qtd1 != 0) printf("Maximo produto %d %d %d.\n",n_idp, maximo_ide, maximo_qtd2);
    }
    return; 
}

/*---------------------------------------------------Algoritmos----------------------------------------------------------*/

void quicksort_L(char a[][63],int b[],int left,int right)
{
    /*organiza a tabela de strings e atualiza (conforme as trocas) a tabela com os ids*/
    int i, j, troca1, pivot;
    char troca2[63];
    if (left < right)
    {
        pivot = left;
        i = left;
        j = right;

        while(i<j)
        {
            while(strcmp (a[i],a[pivot])<= 0 &&  i< right)
                i++;
            
            while(strcmp(a[j],a[pivot]) > 0)
                j--;
            
            if(i<j)
            {
                troca1=b[i];
                b[i]=b[j];
                b[j]=troca1;

                strcpy(troca2,a[i]);
                strcpy(a[i],a[j]);
                strcpy(a[j],troca2);
            }  
        }
        troca1=b[pivot];
        b[pivot]=b[j];
        b[j]=troca1;

        strcpy(troca2,a[pivot]);
        strcpy(a[pivot],a[j]);
        strcpy(a[j],troca2);
        
        quicksort_L(a,b,left,j-1);
        quicksort_L(a,b,j+1,right);
    }
    return;
}

void sort_L()
{
    int n_ide, i, m = 0, count = 0, p = 0;
    int tabP_ids[MAX_PESO] = {0};
    char tabP_desc[MAX_PESO][63] = {0};
    scanf(" %d", &n_ide);

    if (tabE[n_ide].estado == OCUPADO)
    {
        for (i = 0; i <= MAX_PESO - 1;i++)
        {
            /*criacao de duas tabelas, uma com os idps e outra com pointers para strings(descricao dos idps respetivos) sem espacos vazios (m prevente)*/
            if (tabela_id[n_ide][i][0] == 0 && tabela_id[n_ide][i][1] == 0) {continue;}
            else 
            {
            count += 1;
            tabP_ids[m] = tabela_id[n_ide][i][0];
            strcpy(&tabP_desc[m][0], tabP[tabela_id[n_ide][i][0]].descricao);
            m++;
            }
        }
        /*caso a tabela esteja a zeros e porque a encomenda esta vazia*/
        if (count == 0) 
        {
            printf("Encomenda %d\n",n_ide);
            return;
        }
        /*tabela de strings, tabela com os ids respetivos, o limite esquerdo(indice onde comeca) e o direito(ultimo indice)*/
        quicksort_L(tabP_desc, tabP_ids, 0, count -1);
        
        printf("Encomenda %d\n",n_ide);
        /*for que percorre a tabela dos ids (tabP_ids)*/
        for (p = 0; p <= count -1 ;p++)
        {    
            /*for que percorre a tabela da encomenda com os produtos*/
            for (i = MAX_PESO - 1; i >= 0; i--)
            {   /*quando encontra (ou seja o idp e igual e a qtd diff de 0 da print)*/
                if (tabela_id[n_ide][i][0] == tabP_ids[p] && tabela_id[n_ide][i][1] != 0)
                {
                printf("* %s %d %d\n", tabP[tabP_ids[p]].descricao, tabP[tabP_ids[p]].preco, tabela_id[n_ide][i][1]);
                }
            }
        }
        return;
    }
    else 
    {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",n_ide);
    return;
    }
}

void quicksort_l(int a[],int b[],int left,int right)
{
    /*organiza a tabela de precos e atualiza (conforme as trocas) a tabela com os ids*/
    int i, j, troca1,troca2, pivot;
    if (left < right)
    {
        pivot = left;
        i = left;
        j = right;

        while(i<j)
        {
            
            while(a[i] <= a[pivot] &&  i< right)
                i++;
            
            while(a[j] > a[pivot])
                j--;
            
            if(i<j)
            {
                troca1=b[i];
                b[i]=b[j];
                b[j]=troca1;

                troca2 = a[i];
                a[i] = a[j];
                a[j]=troca2;
            }  
        }
        troca1=b[pivot];
        b[pivot]=b[j];
        b[j]=troca1;

        troca2=a[pivot];
        a[pivot]=a[j];
        a[j]=troca2;
        
        quicksort_l(a,b,left,j-1);
        quicksort_l(a,b,j+1,right);
    }
    return;
}

void sort_l()
{
    int tabP_ids[MAX_P] = {0};
    int tabP_precos[MAX_P] = {0};
    int i, igual = 0, primeiro;
    /*fica se com duas tabelas uma com os ids e outra com os respetivos precos*/
    for (i = 0; i <= idp -1; i++)
    {
        tabP_ids[i] = i;
        tabP_precos[i] = tabP[i].preco;
    }
    quicksort_l(tabP_precos,tabP_ids,0, idp - 1);
    
    /*re-organiza de acordo com os ids se os precos forem iguais*/
    if (idp - 1 > 1)
    {
        for (i = 1; i <= idp -1;i++)
        {
            if (tabP_precos[i] == tabP_precos[i - 1])
            {
                if (igual == 0)
                {    
                    primeiro = i - 1;
                    igual = OCUPADO;
                }
            }
            else if (igual == OCUPADO)
            {
                igual = 0;
                quicksort_l(tabP_ids,tabP_precos,primeiro,i -1);
            }
        }
        /*caso os que sejam iguais estejam no fim*/
        if (igual == OCUPADO && tabP_precos[idp - 1] == tabP_precos[idp - 2])
        {
            igual = 0;
            quicksort_l(tabP_ids,tabP_precos,primeiro,idp -1);
        }
        else if (igual == OCUPADO)
        {
            igual = 0;
            quicksort_l(tabP_ids,tabP_precos,primeiro,idp -2);
        }
    }
    printf("Produtos\n");
    for (i = 0;i <= idp - 1; i++)
    {
        printf("* %s %d %d\n", tabP[tabP_ids[i]].descricao, tabP[tabP_ids[i]].preco, tabP[tabP_ids[i]].qtd);
    }
    return;
}

/*-------------------------------------------------------MAIN-------------------------------------------------------------------*/

int main()
{   
    char c = '\0';
    
    while (c != 'x')
    {   
        c = getchar();
        
        switch(c)
        {   
        case 'a':
            cria_produto();
            break;
        case 'q':
            add_stock();
            break;
        case 'N':
            cria_encomenda();
            break;
        case 'A':
            add_produto();
            break;
        case 'r':
            r_stock();
            break;
        case 'R':
            r_produto();
            break;
        case 'C':
            custo();
            break;
        case 'p':
            muda_preco();
            break;
        case 'E':
            lista_E();
            break;
        case 'm':
            maximo_produto();
            break;
        case 'l':
            sort_l();
            break;
        case 'L':
            sort_L();
            break;
        }
    }
    return 0;  
}
