#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Importacao dos modulos necessarios para a manipulacao dos jogos e equipas */
#include "jogos.h"
#include "equipas.h"

/* Constantes que indicam se o programa deve continuar a correr ou encerrar */
#define FLAG_CORRER 1
#define FLAG_TERMINAR 0

/* Constantes que afirmam se existe alguma equipa em sistema ou nao */
#define NENHUMA_EQUIPA 0
#define EXISTE_EQUIPA 1

/* Valor que define o tamanho maximo dos nomes introduzidos */
#define MAX_LEN_STR 1023
/* Valor que define o tamanho maximo das hashtables para os jogos e equipas */
#define INIT_HASHTABLES 307


int vitorias_equipa(link_equipa *equipa);

int main()
{
    
    int linha_input = 1;

    /* Variaveis que indicam o estado do programa e se ja foi adicionada alguma equipa */
    int flag_prog = FLAG_CORRER;
    int flag_equipas = NENHUMA_EQUIPA;

    char command;

    /* Variaveis que armazenam temporariamente o input recebido */
    int score1, score2; 
    char nome_jogo_temp[MAX_LEN_STR], equipa1_temp[MAX_LEN_STR],
    equipa2_temp[MAX_LEN_STR]; 
    char nome_equipa[MAX_LEN_STR];

    link_equipa *equipa1, *equipa2;
    link_jogo *jogo;

    /* Ponteiros para as estruturas de armazenamento dos dados do programa */
    hashtable_equipas *tabela_equipas;
    hashtable_jogos *tabela_jogos; 
    lista_ord_jogos *lista_jogos;

    /* Inicializacao das estruturas de armazenamento de dados */
    tabela_equipas = inicializa_equipas(INIT_HASHTABLES);
    tabela_jogos = inicializa_jogos(INIT_HASHTABLES);
    lista_jogos = inicializa_jogos_lista();


    /* Enquanto o utilizador nao indicar para encerrar o programa */
    while (flag_prog)
    {
        /* Le-se um comando do uilizador, e escolhe-se um formato de input
        consoante o comando introduzido */
        scanf("%c", &command);
        
        switch (command)
        {
        /* Caso em que se pretende adicionar um novo jogo */    
        case 'a':
            scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome_jogo_temp, equipa1_temp, 
                  equipa2_temp, &score1, &score2);

            /* Procuram-se as equipas indicadas nos dados ja introduzidos */
            equipa1 = procurar_equipa(equipa1_temp, tabela_equipas);
            equipa2 = procurar_equipa(equipa2_temp, tabela_equipas);
            
            /* Se o nome introduzido para o novo jogo ja existir, nao se adiciona */
            if(!(procurar_jogo(nome_jogo_temp, tabela_jogos) == NULL))
                printf("%d Jogo existente.\n", linha_input);

            /* Se alguma das equipas nao existir, nao se adiciona */
            else if(equipa1 == NULL || equipa2 == NULL)
                printf("%d Equipa inexistente.\n", linha_input);
                
            /* Caso contrario, adiciona-se o novo jogo a base de dados */
            else
                inserir_jogo(nome_jogo_temp, equipa1, equipa2, score1, score2, tabela_jogos, lista_jogos);
            
            linha_input++;
            break;
        
        /* Caso em que se pretende listar todos os jogos, por ordem de introducao */
        case 'l':
            listar_todos_jogos(linha_input, lista_jogos);

            linha_input++;
            break;

        /* Caso em que se pretende obter as caracteristicas do jogo introduzido */
        case 'p':
            scanf(" %[^:\n]", nome_jogo_temp);

            /* Procura-se pelo jogo na base de dados */
            jogo = procurar_jogo(nome_jogo_temp, tabela_jogos);

            /* Caso o jogo nao exista, entao mostra-se um erro */
            if(jogo == NULL)
                printf("%d Jogo inexistente.\n", linha_input);

            /* Caso contrario, mostra-se as suas caracteristicas */
            else
                printf("%d %s %s %s %d %d\n", linha_input, 
                jogo->pointer_jogo->nome_jogo,
                jogo->pointer_jogo->pequipa1->nome_equipa, 
                jogo->pointer_jogo->pequipa2->nome_equipa,
                jogo->pointer_jogo->pontos1, jogo->pointer_jogo->pontos2);

            linha_input++;
            break;

        /* Caso em que se pretende eliminar da base de dados um dado jogo */
        case 'r':
            scanf(" %[^:\n]", nome_jogo_temp);

            /* Caso o jogo nao exista devolve-se um erro */
            if(procurar_jogo(nome_jogo_temp, tabela_jogos) == NULL)
                printf("%d Jogo inexistente.\n", linha_input);

            /* Caso contrario, apaga-se */
            else
                apagar_jogo(nome_jogo_temp, tabela_jogos, lista_jogos);

            linha_input++;
            break;

        /* Caso em que se pretende alterar o resultado de um jogo */
        case 's':
            scanf(" %[^:\n]:%d:%d", nome_jogo_temp, &score1, &score2);
            jogo = procurar_jogo(nome_jogo_temp, tabela_jogos);

            /* Caso o jogo nao exista, devolve-se um erro */
            if(procurar_jogo(nome_jogo_temp, tabela_jogos) == NULL)
                printf("%d Jogo inexistente.\n", linha_input);

            /* Caso contrario, faz-se a aletracao pretendida */
            else
                alterar_jogo(jogo, score1, score2);

            linha_input++;
            break;

        /* Caso em que se pretende adicionar uma nova equipa ao sistema */
        case 'A':
            scanf(" %[^:\n]", nome_equipa);

            /* Caso esta ainda nao exista, adiciona-se */ 
            if(procurar_equipa(nome_equipa, tabela_equipas) == NULL)
                adicionar_equipa(nome_equipa, tabela_equipas);

            /* Caso contrario, devolve-se um erro */
            else
                printf("%d Equipa existente.\n", linha_input);

            /* Ao adicionar-se uma equipa, entao existe pelo menos uma equipa no sistema */
            flag_equipas = EXISTE_EQUIPA;
            linha_input++;
            break;

        /* Caso em que se pretende obter as caracteristicas de uma dada equipa */
        case 'P':
            scanf(" %[^:\n]", nome_equipa);
            equipa1 = procurar_equipa(nome_equipa, tabela_equipas);

            /* Caso a equipa exista, mostram-se as suas caracteristicas */
            if(equipa1 != NULL)
                printf("%d %s %d\n", linha_input, nome_equipa, equipa1->numero_vitorias);

            /* Caso contrario, devolve-se um erro */
            else
                printf("%d Equipa inexistente.\n", linha_input);

            linha_input++;
            break;

        /* Caso em que se pretende listar todas as equipas com mais vitorias */
        case 'g':
            /* Caso existam equipas */
            if(flag_equipas)
                listar_melhores_equipas(tabela_equipas, linha_input);

            linha_input++;
            break;

        /* Caso em que o utilizador pretende encerrar o programa */
        case 'x':
            /* Liberta-se toda a memoria utilizada */ 
            destruir_equipas(tabela_equipas);
            destruir_jogos(tabela_jogos); 
            destruir_lista(lista_jogos);

            flag_prog = FLAG_TERMINAR;

        default:
            break;
        }
        
        
    }
    return 0;
}
