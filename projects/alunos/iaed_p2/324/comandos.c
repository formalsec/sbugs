#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projeto2.h"


void a_comando(jogos *jg,node ** jg_hash,e_node **eqp_hash, int NL)
{
    char nome[SIZE];
    /*Nodes, e_nodes e jg_node auxiliares*/
    e_node *tmp_1, *tmp_2;
    node * aux;
    jg_node *jg_aux;

    int location_2, location_3, location_1;
    char equipa1[SIZE], equipa2[SIZE];
    int score1, score2, procura = 0, procura_1=0,procura_2=0;
    /*Leitura do conjunto de argumentos do standard input*/
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d\n", nome, equipa1, equipa2, &score1,&score2);
    /*Determinar o indice da string na hash*/
    location_1 = get_location(nome);
    /*Ciclo que vai a todos os node de um determinado indice da hash*/
    for(aux = jg_hash[location_1];aux!=NULL;aux=aux->next)
    {
        /*Verificacao da existencia de um determinado jogo*/
        if(strcmp(aux->nome_jogo, nome) == 0)
        {
            procura = 1;
            break;/*Para o ciclo quando encontra o jogo*/
        }
    }
    /*Caso o jogo ja exista*/
    if( procura == 1)
        printf("%d Jogo existente.\n", NL);
    else
    {
        /*Determinar os indices das strings na hash*/
        location_2 = get_location(equipa1); 
        location_3 = get_location(equipa2);
        /*Ciclos que vao a todos os e_node de uma determinado indice da hash*/
        /*Ciclo que verifica a existencia da equipa1*/
        for(tmp_1 = eqp_hash[location_2];tmp_1!= NULL;tmp_1=tmp_1->next)
        {
            if(strcmp(tmp_1->nome, equipa1)== 0)
            {
                procura_1 = 1;
                break;/*Para quando encontra a equipa1*/
            }
        }
        /*Ciclo que verifica a existencia da equipa2*/
        for(tmp_2 = eqp_hash[location_3];tmp_2!= NULL;tmp_2=tmp_2->next)
        {
            if(strcmp(tmp_2->nome, equipa2)== 0)
            {
                procura_2 = 1;
                break;/*Para quando encontra a equipa2*/
            }
        }
        /*Caso as equipas existam, adicionam uma vitoria a equipa vencedora*/
        if((procura_1 == 1) &&(procura_2 == 1))
        {
            /*Adicionam um no a lista de jogos com os argumentos recebidos*/
            jg_aux= add_last_jg(jg, nome, equipa1, equipa2, score1, score2);
            /*E depois adiciona a hash o no do jogo, e liga o no da lista ao da hash*/
            insert_into_table(jg_hash, jg_aux);
            if(score1 >score2) tmp_1->vitorias++;
            if(score1<score2) tmp_2->vitorias++;
        }
        else
        {
            printf("%d Equipa inexistente.\n", NL);
        }
    }
}

/**************************************************************************************************/

void l_comando(jogos *jg, int NL)
{
    jg_node *aux;
    /*Ciclo que vai printar todos os jogos*/
    for (aux = jg->head;aux!= NULL;aux=aux->next)
    {
        printf("%d %s %s %s %d %d\n", NL, aux->value, aux->equipa1, aux->equipa2, aux->score1, aux->score2);
    }
}

/**************************************************************************************************/

void p_comando(node **hashtable, int NL)
{
    node * aux;
    char texto[SIZE];
    int procura = 0, location;
    /*Leitura do conjunto de argumentos do standard input*/
    scanf(" %[^:\n]\n", texto);
    /*Determinar o indice na hash da string recebida*/
    location = get_location(texto);
    /*Caso esse indice esteja vazio, nao existe jogo*/
    if(hashtable[location] == NULL)
    {
        printf("%d Jogo inexistente.\n", NL);
    }
    else
    {
        /*Ciclo que corre todos os node da hash naquele determinado indice*/
        for(aux = hashtable[location];aux!=NULL;aux=aux->next)
        {
            /*Caso encontre o jogo que procurava*/
            if(strcmp(aux->nome_jogo, texto) == 0)
            {
                procura = 1;
                break;/*Para o ciclo quando encontra o jogo*/
            }
        }
        if(procura == 1)
        {
            printf("%d %s %s %s %d %d\n", NL, aux->jogo->value, aux->jogo->equipa1, aux->jogo->equipa2, aux->jogo->score1,aux->jogo->score2);
        }
        else printf("%d Jogo inexistente.\n", NL);
    }
}

/**************************************************************************************************/

void r_comando(jogos * jg, node ** hashtable, e_node ** equipas, int NL)
{
    char texto[SIZE];
    node * aux;
    int location, procura = 0;
    /*Leitura do conjunto de argumentos do standard input*/
    scanf(" %[^:\n]\n", texto);
    /*Determinar o indice na hash da string recebida*/
    location = get_location(texto);
    /*Caso esse indice esteja vazio, nao existe jogo*/
    if (hashtable[location] == NULL)
        printf("%d Jogo inexistente.\n", NL);
    else
    {
        /*Ciclo que corre todos os node da hash naquele determinado indice*/
        for(aux = hashtable[location];aux!= NULL;aux=aux->next)
        {
            /*Caso encontre o jogo que procurava*/
            if(strcmp(aux->nome_jogo, texto) == 0)
            {
                procura =1;
                break;/*Para o ciclo quando encontra o jogo*/
            }
        }
        if(procura != 1) printf("%d Jogo inexistente.\n", NL);
        else
        {
            /*Caso o jogo exista, elimina se o jogo da lista ligada de jogos e da hash*/
            remove_vitoria(aux, equipas);
            remove_jogo(jg,aux);
            /*Apos desconectar o no do jogo da lista, colocamos a key vazia na hash em vez de dar free ja*/
            strcpy(aux->nome_jogo, "");
        }
    }
}

/**************************************************************************************************/

void s_comando(node ** hashtable,e_node ** equipas,int NL)
{
    char texto[SIZE];
    node * aux;
    e_node * tmp, *tmp_1;
    int score_1, score_2, location, location_1,location_2, procura = 0, aux_1,aux_2;
    /*Leitura do conjunto de argumentos do standard input*/
    scanf(" %[^:]:%d:%d\n",texto, &score_1, &score_2);
    location = get_location(texto);
    if(hashtable[location] == NULL)
        printf("%d Jogo inexistente.\n", NL);
    else
    {
        for(aux = hashtable[location];aux!= NULL;aux=aux->next)
        {
            if(strcmp(aux->nome_jogo, texto)==0)
            {
                procura = 1;
                break;
            }
        }
        if (procura != 1)
        {
            printf("%d Jogo inexistente.\n", NL);
        }
        else
        {
            location_1 = get_location(aux->jogo->equipa1);
            location_2 = get_location(aux->jogo->equipa2);
            /*Guarda os valores antigos do score para determinar o antigo vencedor*/
            aux_1 = aux->jogo->score1;
            aux_2 = aux->jogo->score2;
            /*Atualiza se os scores daquele jogo*/
            aux->jogo->score1 = score_1;
            aux->jogo->score2 = score_2;
            /*Ciclos que vao procurar a localizacao da equipa1 e equipa2*/
            for(tmp = equipas[location_1];tmp != NULL;tmp=tmp->next)
            {
                if(strcmp(tmp->nome, aux->jogo->equipa1)== 0)
                {
                    /*Caso a equipa1 tenha sido a vencedor no score anterior retirara se uma vitoria*/
                    if(aux_1 > aux_2) tmp->vitorias -=1;
                    /*Caso a quipa1 seja a vencedora novamente neste novo score, adiciona uma vitoria */
                    if(score_1 >score_2) tmp->vitorias +=1;
                    break; /*Para o ciclo quando faz a alteracao*/
                }
            }
            for(tmp_1 = equipas[location_2];tmp_1 != NULL;tmp_1=tmp_1->next)
            {
                if(strcmp(tmp_1->nome, aux->jogo->equipa2)== 0)
                {
                    if(aux_1 < aux_2) tmp_1->vitorias -=1;
                    if(score_1 < score_2) tmp_1->vitorias +=1;
                    break;
                }
            }
        }
    }
}

/**************************************************************************************************/

void A_comando(e_node ** hashtable, int NL)
{   
    char texto[SIZE];
    int location, procura;
    scanf(" %[^:\n]\n", texto);
    location = get_location(texto);
    /*Caso a suposta localizacao da equipa esteja vazia*/
    if(hashtable[location] == NULL)
        /*Adiciona a equipa a hash*/
        insert_into_equipas(hashtable, texto);
    else
    {
        /*Vai a suposta localizacao e verifica se a equipa ja existe na hash*/
        procura = existe_equipa(hashtable, location, texto);
        if(procura == 1) 
            printf("%d Equipa existente.\n", NL);
        else /*Adiciona a quipa a hash*/
            insert_into_equipas(hashtable, texto);
    }
}

/**************************************************************************************************/

void P_comando(e_node ** hashtable, int NL)
{
    e_node * aux;
    char texto[SIZE];
    int location, procura=0;
    scanf(" %[^:\n]\n", texto);
    location = get_location(texto);
    if(hashtable[location] == NULL)
        printf("%d Equipa inexistente.\n", NL);
    else
    {
        /*Ciclo que vai a todos os e_node da hash*/
        for(aux = hashtable[location];aux!= NULL;aux=aux->next)
        {
            /*Verifica a existencia daquela equipa*/
            if(strcmp(aux->nome, texto) == 0)
            {
                procura = 1;
                break;/*Para o ciclo caso encontre a equipa pedida*/
            }
        }
        if (procura == 1)
            printf("%d %s %d\n", NL, aux->nome, aux->vitorias);
        else printf("%d Equipa inexistente.\n", NL);
    }
}

/**************************************************************************************************/

void g_comando(e_node ** equipas, int NL)
{
    e_node * aux;
    int maior = 0, i, conta = 0;
    /*Ciclo que vai a todos os indices da Hash*/
    for(i= 0;i<HASHTABLE_SIZE;i++)
    {
        if(equipas[i]!=NULL)
        {
            /*Ciclo que percorre todos os e_node da hash*/
            for(aux=equipas[i];aux!=NULL;aux=aux->next)
            {
                /*Vai guardar o maior numero de vitorias*/
                if(aux->vitorias >= maior) 
                {
                    maior = aux->vitorias;
                    conta ++;
                }
            }
        }
    }
    /*Caso existam equipas na hash, vai listar os vencedores*/
    if(conta !=0)
        listar_vencedores(equipas, maior, conta, NL);
}
/**************************************************************************************************/