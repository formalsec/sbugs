#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projeto2.h"


int existe_equipa(e_node **hashtable, int location, char *texto)
{
    e_node *aux;
    int procura = 0;
    /*Ciclo que percorre todos os nos de um determinado indice da hash*/
    for(aux = hashtable[location];aux!= NULL;aux=aux->next)
    {
        /*Comparacao de duas strings, para determinar a existencia da string*/
        if(strcmp(aux->nome, texto) == 0)
        {
            /*Caso em que a comparacao da True, ou seja, existe essa equipa na hash*/
            procura = 1;
            break; /*Para a procura, porque ja fez encontrou a equipa*/
        }
    }
    return procura;
}

/**************************************************************************************************/

void remove_vitoria(node * aux,e_node ** equipas)
{
    e_node *tmp;
    int location;
    /*Verificacao de quem tinha ganho no jogo a ser eliminado*/
    /*Se a equipa1 tem mais golos entao, a vitoria foi deles*/
    if (aux->jogo->score1 > aux->jogo->score2)
    {
        location = get_location(aux->jogo->equipa1);
        /*Ciclo para encontrar a equipa1 e retirar uma vitoria*/
        for(tmp = equipas[location];tmp != NULL;tmp=tmp->next)
        {
            if(strcmp(aux->jogo->equipa1, tmp->nome) == 0)
            {
                tmp->vitorias -=1; break;/*Para o ciclo quando retira a vitoria*/
            }
        }
    }
    /*Se a equipa2 tem mais golos entao, a vitoria foi deles*/
    if (aux->jogo->score1 < aux->jogo->score2)
    {
        location = get_location(aux->jogo->equipa2);
        /*Ciclo para encontrar a equipa2 e retirar uma vitoria*/
        for(tmp = equipas[location];tmp != NULL;tmp=tmp->next)
        {
            if(strcmp(aux->jogo->equipa2, tmp->nome) == 0)
            {
                tmp->vitorias -=1; break;/*Para o ciclo quando retira a vitoria*/
            }
        }
    }
}

/**************************************************************************************************/

void remove_jogo(jogos * jg,node *aux)
{  
    /*Caso o node seja o primeiro*/
    if(aux->jogo->previous == NULL)
        /*Coloca a head no elemento seguinte, uma vez que vamos eliminar o primeiro*/
        jg->head = aux->jogo->next;
    else 
        /*Conecta o elemento anterior ao a seguir a ele, desconectando o ponteiro previous*/
        aux->jogo->previous->next = aux->jogo->next;

    /*Caso o node seja o ultimo*/
    if(aux->jogo->next == NULL) 
        /*Coloca o last no elemento anterior, uma vez que vamos eliminar o ultimo*/
        jg->last = aux->jogo->previous;
    else 
        /*Conecta o elemento a seguir ao elemento anterior a ele, desconectando o ponteiro next*/
        aux->jogo->next->previous = aux->jogo->previous;
    /*Uma vez desconectados os ponteiros next e previous, da NULL em ambos*/
    aux->jogo->previous = NULL;
    aux->jogo->next = NULL;
}

/**************************************************************************************************/

vencedores copia_produto(vencedores l)
{
    vencedores copia;
    strcpy(copia.vencedor, l.vencedor);
    return copia;
}

/**************************************************************************************************/

void listar_vencedores(e_node ** equipas, int maior, int conta, int NL)
{
    e_node * aux;
    int i, j=0, tmp;
    /*Criacao de uma lista com 'conta' espacos para guardar os varios vencedores*/
    vencedores * lista = malloc(sizeof(vencedores)*conta);
    vencedores palavra;
    /*Ciclo de inicializacao da lista de vencedores*/
    for(i = 0;i != conta;i++)
        strcpy(lista[i].vencedor, "0");
    /*Ciclo para copiar os varios vencedores da hash para a lista de vencedores*/
    for(i = 0;i<HASHTABLE_SIZE;i++)
    {
        if(equipas[i]!=NULL)
        {
            for(aux=equipas[i];aux!=NULL;aux=aux->next)
            {
                if(aux->vitorias == maior) 
                {
                    strcpy(lista[j].vencedor,aux->nome);
                    j++; /*Variavel que determina o numero exato de elementos que vai possuir a lista*/
                }   
            }
        }
    }
    tmp = j;
    printf("%d Melhores %d\n", NL, maior);
    /*Ciclos que vao ordenar a lista de vencedores por ordem alfabetica*/
    for(j = 0;j<tmp;j++)
    {
        for(i= 0;i<tmp;i++)
        {
            if(i!=tmp-1)
            {
                if(strcmp(lista[i].vencedor, lista[i+1].vencedor)>0)
                {
                    /*Troca de elementos/strings para ordenar*/
                    palavra = copia_produto(lista[i]);
                    lista[i] = copia_produto(lista[i+1]);
                    lista[i+1]=copia_produto(palavra);
                }
            }  
        }
    }
    /*Ciclo para printar os respetivos vencedores por ordem*/
    for(i=0;i != tmp;i++)
    {
        printf("%d * %s\n", NL,  lista[i].vencedor);
    }
    /*Uma vez utilizada a lista, liberta se a memoria usada para a criar*/
    free(lista);
}
/**************************************************************************************************/