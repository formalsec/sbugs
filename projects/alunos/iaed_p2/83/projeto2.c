#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "JogoEquipa.h"
#include "hashtable.h"
#include "lista.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define CARACTERES_MAX 1023 /* Numero maximo de caracteres que o nome de uma 
                               equipa/jogo pode ter */


/* Funcao auxiliar que atribui uma vitoria a uma equipa */
void atribui_vitoria(Equipa Equipa)
{
    Equipa -> vitorias = Equipa -> vitorias + 1;
}


/* Funcao auxiliar que retira uma vitoria a uma equipa */
void retira_vitoria(Equipa Equipa)
{
    Equipa -> vitorias = Equipa -> vitorias - 1;
}


/* Funcao auxiliar que lista strings por ordem lexicografica */
int cstring_cmp(const void *a, const void *b) 
{ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
} 


/* Comando "a" que adiciona um novo jogo.
   Formato de entrada: `a nome:equipa1:equipa2:score1:score2`
   Formato de saida: NADA (excepto erro).
*/
void comando_a(int* max_jogos, int* max_equipas, int* N_jogos, Jogo* TabJogos, 
               Equipa* TabEquipas, int* N_linhas, link* head, link* tail)
{
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int score2;
    Equipa Equipa1;
    Equipa Equipa2;
    Jogo Jogo;

    nome = (char*)can_fail_malloc(sizeof(char) * 1023);
    equipa1 = (char*)can_fail_malloc(sizeof(char) * 1023);
    equipa2 = (char*)can_fail_malloc(sizeof(char) * 1023);

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);

    Jogo = TabJogossearch(max_jogos, TabJogos, nome);

    if (Jogo == NULL) /* Caso em que o Jogo que se pretende adicionar nao existe */
    {
        Equipa1 = TabEquipassearch(max_equipas, TabEquipas, equipa1);

        if (Equipa1 == NULL) /* Caso em que a primeira equipa do jogo que se 
                           pretende adicionar nao existe */
        {
            printf("%d Equipa inexistente.\n", *N_linhas);
        }

        else /* Caso em que a primeira equipa do jogo que se pretende adicionar existe */
        {   
            Equipa2 = TabEquipassearch(max_equipas, TabEquipas, equipa2);
        
            if (Equipa2 == NULL) /* Caso em que a segunda equipa do jogo que se 
                                    pretende adicionar nao existe */
            {
                printf("%d Equipa inexistente.\n", *N_linhas);
            }

            else
            {
                if (score2 > score1)
                {
                    atribui_vitoria(Equipa2);
                }

                else if (score1 > score2)
                {
                    atribui_vitoria(Equipa1);
                }

                
                Jogo = newJogo(nome, equipa1, equipa2, score1, score2);
                insertEnd(head, tail, Jogo);
                TabJogosinsert(max_jogos, N_jogos, TabJogos, Jogo);
            }
        }
    }

    else /* Caso em que a equipa que se pretende adicionar ja existe */
    {
        printf("%d Jogo existente.\n", *N_linhas);
    }

    free(nome);
    free(equipa1);
    free(equipa2);
}


/* Comando "A" que adiciona uma nova equipa.
   Formato de entrada: `A nome`.
   Formato de saida: NADA (excepto erro).
*/
void comando_A(int* max_equipas, int* N_equipas, Equipa* TabEquipas, int* N_linhas)
{
    char *nome;
    Equipa Equipa;
    
    nome = (char*)can_fail_malloc(sizeof(char) * 1023);
    
    scanf(" %[^:\n]", nome);

    Equipa = TabEquipassearch(max_equipas, TabEquipas, nome);

    if (Equipa == NULL) /* Caso em que a equipa que se pretende adicionar nao existe */
    {
        Equipa = newEquipa(nome, 0);
        TabEquipasinsert(max_equipas, N_equipas, TabEquipas, Equipa);
    }

    else /* Caso em que a equipa que se pretende adicionar ja existe */
    {
        printf("%d Equipa existente.\n", *N_linhas);
    }

    free(nome);
}


/* Comando "p" que procura um jogo com o nome dado.
   Formato de entrada: `p nome`
   Formato de saida: Igual ao formato de saida do comando `l` mas apenas com o jogo `nome`.
*/
void comando_p(int* max_jogos, Jogo* TabJogos, int* N_linhas)
{
    char *nome;
    Jogo Jogo;

    nome = (char*)can_fail_malloc(sizeof(char) * 1023);

    scanf(" %[^:\n]", nome);

    Jogo = TabJogossearch(max_jogos, TabJogos, nome);

    if (Jogo != NULL) /* Caso em que o Jogo que se procura existe */
    {
        printf("%d ", *N_linhas);
        printJogo(Jogo);
    }

    else /* Caso em que o Jogo que se procura nao existe */
    {
        printf("%d Jogo inexistente.\n", *N_linhas);
    }

    free(nome);
}


/* Comando "P" que procura uma equipa dado o nome.
   Formato de entrada: `P nome`.
   Formato de saida: `NL nome numero-de-jogos-ganhos`.
*/
void comando_P(int* max_equipas, Equipa* TabEquipas, int* N_linhas)
{
    char *nome;
    Equipa Equipa;
    
    nome = (char*)can_fail_malloc(sizeof(char) * 1023);
    
    scanf(" %[^:\n]", nome);

    Equipa = TabEquipassearch(max_equipas, TabEquipas, nome);
    
    if (Equipa != NULL) /* Caso em que a equipa que se procura existe */
    {
        printf("%d ", *N_linhas);
        printEquipa(Equipa);
    }

    else /* Caso em que a equipa que se procura nao existe */
    {
        printf("%d Equipa inexistente.\n", *N_linhas);
    }

    free(nome);
}


/* Comando "r" que apaga um jogo dado o nome.
   Formato de entrada: `r nome`
   Formato de saida: NADA (excepto erro).
*/
void comando_r(int* max_jogos, int* max_equipas, int* N_jogos, 
               Jogo* TabJogos, Equipa* TabEquipas, link* head, link* tail, int* N_linhas)
{
    char *nome;
    Jogo Jogo;
    Equipa Equipa;
    
    nome = (char*)can_fail_malloc(sizeof(char) * 1023);
    
    scanf(" %[^:\n]", nome);

    Jogo = TabJogossearch(max_jogos, TabJogos, nome);

    if (Jogo != NULL) /* Caso em que o Jogo que se procura existe */
    {
        if ((Jogo -> score1) > (Jogo -> score2))
        {
            Equipa = TabEquipassearch(max_equipas, TabEquipas, (Jogo -> equipa1));
            retira_vitoria(Equipa);
        }

        else if ((Jogo -> score1) < (Jogo -> score2))
        {
            Equipa = TabEquipassearch(max_equipas, TabEquipas, (Jogo -> equipa2));
            retira_vitoria(Equipa);
        }

        delete(head, tail, Jogo);
        TabJogosdelete(max_jogos, N_jogos, TabJogos, nome);
    }

    else /* Caso em que o Jogo que se procura nao existe */
    {
        printf("%d Jogo inexistente.\n", *N_linhas);
    }

    free(nome);
}


/* Comando "s" que altera o score de um jogo dado o nome.
   Formato de entrada: `r nome`.
   Formato de saida: NADA (excepto erro).
*/
void comando_s(int* max_jogos, int* max_equipas, 
               Jogo* TabJogos, Equipa* TabEquipas, int* N_linhas)
{
    char *nome;
    int novo_score1;
    int novo_score2;
    Jogo Jogo;
    Equipa Equipa;
    
    nome = (char*)can_fail_malloc(sizeof(char) * 1023);
    
    scanf(" %[^:\n]:%d:%d", nome, &novo_score1, &novo_score2);

    Jogo = TabJogossearch(max_jogos, TabJogos, nome);

    if (Jogo != NULL) /* Caso em que o Jogo que se procura existe */ 
    {
        if ((Jogo -> score1) > (Jogo -> score2)) /* Caso em que no resultado inicial a equipa1 vence */
        {
            Equipa = TabEquipassearch(max_equipas, TabEquipas, (Jogo -> equipa1));

            if (novo_score1 < novo_score2)
            {
                retira_vitoria(Equipa);
                Equipa = TabEquipassearch(max_equipas, TabEquipas, (Jogo -> equipa2));
                atribui_vitoria(Equipa);
            }

            else if (novo_score1 == novo_score2)
            {
                retira_vitoria(Equipa);
            }
        }

        else if ((Jogo -> score1) < (Jogo -> score2)) /* Caso em que no resultado inicial a equipa2 vence */
        {
            Equipa = TabEquipassearch(max_equipas, TabEquipas, (Jogo -> equipa2));

            if (novo_score1 > novo_score2)
            {
                retira_vitoria(Equipa);
                Equipa = TabEquipassearch(max_equipas, TabEquipas, (Jogo -> equipa1));
                atribui_vitoria(Equipa);
            }

            else if (novo_score1 == novo_score2)
            {
                retira_vitoria(Equipa);
            }
        }

        else if ((Jogo -> score1) == (Jogo -> score2)) /* Caso em que no resultado inicial nao ha equipa vencedora */
        {
            if (novo_score1 > novo_score2)
            {
                Equipa = TabEquipassearch(max_equipas, TabEquipas, (Jogo -> equipa1));
                atribui_vitoria(Equipa);
            }

            else if (novo_score1 < novo_score2)
            {
                Equipa = TabEquipassearch(max_equipas, TabEquipas, (Jogo -> equipa2));
                atribui_vitoria(Equipa);
            }
        }

        Jogo -> score1 = novo_score1;
        Jogo -> score2 = novo_score2;
    }

    else /* Caso em que o Jogo que se procura nao existe */
    {
        printf("%d Jogo inexistente.\n", *N_linhas);
    }

    free(nome);
}


/* Comando "l" que lista todos os jogos introduzidos.
   Formato de entrada: `l`.
   Formato de saida: Uma linha por jogo no formato abaixo.
*/
void comando_l(link head, int* N_linhas)
{
    printLista(head, N_linhas);
}


/* Comando "g" que encontra as equipas com mais vitorias e lista-as por ordem lexicografica
   Formato de entrada: `g`
   Formato de saida:
    NL Melhores numero-de-jogos-ganhos
    NL * nome-equipa1
    NL * nome-equipa2
    NL * nome-equipa3
*/
void comando_g(int* max_equipas, Equipa* TabEquipas, int* N_linhas)
{
    int maior = 0;
    int acumulador = 0;
    int contador = 0;
    int i = 0;
    char **Tabela;

    while (i < (*max_equipas)) /* Eh percorrida uma vez a tabela de forma a encontrar o maior numero vitorias
                                  e o numero de equipas que verificam esse numero de vitorias */
    {
        if (TabEquipas[i] != NULL)
        {
            if ((TabEquipas[i] -> vitorias) > maior)
            {
                maior = (TabEquipas[i] -> vitorias);
                acumulador = 1;
            }

            else if ((TabEquipas[i] -> vitorias) == maior)
            {
                acumulador++;
            }
        }
        
        i++;
    }

    i = 0;

    if (acumulador > 0) /* Caso em que existe pelo menos uma equipa */
    {
        Tabela = (char**)can_fail_malloc((acumulador) * CARACTERES_MAX);

        while (i < (*max_equipas) && contador < acumulador) /* Eh percorrida uma segunda vez de forma a guardar num vetor
                                                               os ponteiros das strings das equipas que verificaram o maior
                                                               numero de vitorias */
        {
            
            if (TabEquipas[i] != NULL) 
            {
                if ((TabEquipas[i] -> vitorias) == maior)
                {
                    Tabela[contador] = TabEquipas[i] -> nome;
                    contador++;
                }
            }
            
            i++;
        }

        contador = 0;

        qsort(Tabela, acumulador, sizeof(char *), cstring_cmp);
    
        printf("%d Melhores %d\n", *N_linhas, maior);
        
        while (contador < acumulador)
        {
            printf("%d * %s\n", *N_linhas, Tabela[contador]);
            contador++;
        }
    
        free(Tabela);
    }

}    


/* Funcao principal */
int main()
{
    char c;

    int *max_jogos; /* Numero maximo de Jogos */
    int *max_equipas; /* Numero maximo de Equipas */
    Jogo *TabJogos; /* Tabela dos Jogos */
    Equipa *TabEquipas; /* Tabela das Equipas */
    link *head; /* Primeiro elemento da lista */
    link *tail; /* Ultimo elemento da lista */
    int N_jogos = 0; /* Numero de Jogos */
    int N_equipas = 0; /* Numero de Equipas */
    int N_linhas = 1; /* Numero da linha do input */
    
    max_jogos = (int*)can_fail_malloc(sizeof(int));
    max_equipas = (int*)can_fail_malloc(sizeof(int));
    head = (link*)can_fail_malloc(sizeof(link));
    tail = (link*)can_fail_malloc(sizeof(link));

    *max_jogos = 997;
    *max_equipas = 997;
    *head = NULL;
    *tail = NULL;
    
    TabJogos = (Jogo*)can_fail_malloc((*max_jogos) * sizeof(Jogo));
    TabEquipas = (Equipa*)can_fail_malloc((*max_equipas) * sizeof(Equipa));

    TabJogosinit(max_jogos, &N_jogos, TabJogos);
    TabEquipasinit(max_equipas, &N_equipas, TabEquipas);

    c = getchar();

    while (c != 'x') /* O comando 'x' termina o programa */
    {
        if (c == 'a')
        {
            comando_a(max_jogos, max_equipas, &N_jogos, TabJogos, TabEquipas, &N_linhas, head, tail);
        
            if ((N_jogos) == (*max_jogos)/2) /* Caso a capacidade da Tabela de Jogos chegue a meio, esta sera expandida */
            {
                TabJogos = expand_jogos(max_jogos, &N_jogos, TabJogos);
            }
        }
        
        else if (c == 'A')
        {
            comando_A(max_equipas, &N_equipas, TabEquipas, &N_linhas);

            if ((N_equipas) == (*max_equipas)/2) /* Caso a capacidade da Tabela de Equipas chegue a meio, esta sera expandida */
            {
                TabEquipas = expand_equipas(max_equipas, &N_equipas, TabEquipas);
            }
        }

        else if (c == 'p')
        {
            comando_p(max_jogos, TabJogos, &N_linhas);
        }
        
        else if (c == 'P')
        {
            comando_P(max_equipas, TabEquipas, &N_linhas);
        }

        else if (c == 'r')
        {
            comando_r(max_jogos, max_equipas, &N_jogos, TabJogos, TabEquipas, head, tail, &N_linhas);
        }

        else if (c == 's')
        {
            comando_s(max_jogos, max_equipas, TabJogos, TabEquipas, &N_linhas);
        }

        else if (c == 'l')
        {
            comando_l(*head, &N_linhas);
        }

        else if( c == 'g')
        {
            comando_g(max_equipas, TabEquipas, &N_linhas);
        }
        
        c = getchar();
        c = getchar();
        N_linhas++;
    }

    freeTabJogos(max_jogos, TabJogos);
    freeTabEquipas(max_equipas, TabEquipas);
    freeLista(*head);
    free(max_jogos);
    free(max_equipas);
    free(head);
    free(tail);

    return 0;
}