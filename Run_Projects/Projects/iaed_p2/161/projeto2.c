#include <stdio.h>
#include <stdlib.h>
#include "tabela_equipas.h"
#include "tabela_jogos.h"

/* dimensao maxima de strings */
#define DIM_STR 1024

/* dimensao inicial das tabelas de dispersao */
#define MODULO 31

/* Flag para funcao altera_vitorias_equipa  */
#define VITORIA 1
#define NAO_VITORIA -1

/* eh devolvido EMPATE pela funcao obtem_vencedor_jogo em caso de EMPATE */
#define EMPATE NULL



 /* adiciona um novo jogo ---------------------------------------------------------------------- */
void adiciona_jogo(lista *lista_jogos, pTabela_jogos tabela_jogos, 
                    pTabela_equipas tabela_equipas, unsigned int Num_Linha)
{
    char buffer[3][DIM_STR]; /* buffer para guardar o nome dos jogos e das equipas */
    unsigned int score[2];
    
    pJogo novo_jogo; /* jogo que vai ser adicionado */
    

    scanf(" %[^:]:%[^:]:%[^:]:%u:%u", buffer[0], buffer[1], buffer[2],
                                    &score[0], &score[1]);

    /* verifica se o jogo existe */
    if (procura_jogo_tabela(tabela_jogos, buffer[0]) != NULL)
        {
            printf("%u Jogo existente.\n", Num_Linha);
            return;
        }

    /* verifica se as equipas existem */
    if (procura_equipa_tabela(tabela_equipas, buffer[1]) == NULL || 
        procura_equipa_tabela(tabela_equipas, buffer[2]) == NULL)
        {
            printf("%u Equipa inexistente.\n", Num_Linha);
            return;
        }

    /* cria jogo */
    novo_jogo = cria_jogo(buffer[0], buffer[1], buffer[2], score);

    /* adiciona jogo 'a lista de jogos */
    adiciona_jogo_lista(lista_jogos, novo_jogo);

    /* adiciona jogo 'a tabela de jogos */
    adiciona_jogo_tabela(tabela_jogos, novo_jogo);

    /* atualiza as vitorias das equipas se for necessario */
    if (score[0] > score[1])
        altera_vitorias_equipa(procura_equipa_tabela(tabela_equipas, buffer[1]), 1);
    
    else if (score[0] < score[1])
        altera_vitorias_equipa(procura_equipa_tabela(tabela_equipas, buffer[2]), 1);
    
    return;
}

/* lista todos os jogos introduzidos ----------------------------------------------------------- */
void lista_todos_jogos(lista *lista_jogos, unsigned int Num_Linha)
{
    print_lista_jogos(lista_jogos, Num_Linha);
    
    return;
}

/* procura um jogo dado o nome ----------------------------------------------------------------- */
void procura_jogo(pTabela_jogos tabela_jogos, unsigned int Num_Linha)
{
    char nome_jogo[DIM_STR]; 
    pJogo jogo;

    scanf(" %[^\n]", nome_jogo);

    /* procura o jogo na tabela */
    jogo = procura_jogo_tabela(tabela_jogos, nome_jogo);

    /* verifica se o jogo existe */
    if (jogo == NULL)
        printf("%u Jogo inexistente.\n", Num_Linha);
    
    else
        print_jogo(jogo, Num_Linha);

    return;
}


/* adiciona uma nova equipa -------------------------------------------------------------------- */
void adiciona_equipa(pTabela_equipas tabela_equipas, unsigned int Num_Linha)
{
    char buffer[DIM_STR]; /* buffer para o nome da equipa */

    scanf(" %[^\n]", buffer);

    /* verifica se a equipa existe */
    if (procura_equipa_tabela(tabela_equipas, buffer) != NULL)
        printf("%u Equipa existente.\n", Num_Linha);
    
    else /* adiciona equipa 'a tabela */
        adiciona_equipa_tabela(tabela_equipas, cria_equipa(buffer));

    return;
}


/* procura uma equipa dado um nome ------------------------------------------------------------- */
void procura_equipa(pTabela_equipas tabela_equipas, unsigned int Num_Linha)
{
    char nome_equipa[DIM_STR];
    pEquipa equipa;

    scanf(" %[^\n]", nome_equipa);

    equipa = procura_equipa_tabela(tabela_equipas, nome_equipa);

    /* verifica se a equipa existe */
    if (equipa == NULL)
        printf("%u Equipa inexistente.\n", Num_Linha);
        
    else
        print_equipa(equipa, Num_Linha);

    return;
}


/* apaga um jogo dado um nome ------------------------------------------------------------------ */
void apaga_jogo(pTabela_jogos tabela_jogos, lista *lista_jogos,
                 pTabela_equipas tabela_equipas, unsigned int Num_Linha)
{
    char nome_jogo[DIM_STR];
    pJogo jogo;
    
    scanf(" %[^\n]", nome_jogo);
    
    /* verifica se o jogo existe e remove o jogo da tabela*/
    if ((jogo = remove_jogo_tabela(tabela_jogos, nome_jogo)) == NULL)
        {
            printf("%u Jogo inexistente.\n", Num_Linha);
            return;
        }
    
    
    /* remove o jogo da lista */
    remove_jogo_lista(lista_jogos, nome_jogo);
    
    /* atualiza as vitorias das equipas se for necessario */
    if (obtem_vencedor_jogo(jogo) != EMPATE)
        altera_vitorias_equipa(procura_equipa_tabela(tabela_equipas, 
                                obtem_vencedor_jogo(jogo)), NAO_VITORIA);

    /* liberta a memoria alocada ao jogo removido */
    free_jogo(jogo);

    return;
}


/* altera a pontuacao de um jogo --------------------------------------------------------------- */
void altera_pontuacao(pTabela_jogos tabela_jogos, 
                        pTabela_equipas tabela_equipas, unsigned int Num_Linha)
{
    char nome_jogo[DIM_STR];
    unsigned int novo_score[2];
    
    char* vencedor_anterior;
    char* vencedor_atual;

    pJogo jogo;

    scanf(" %[^:]:%u:%u", nome_jogo, &novo_score[0], &novo_score[1]);

    /* verifica se o jogo existe */
    if ((jogo = procura_jogo_tabela(tabela_jogos, nome_jogo)) == NULL)
    {
        printf("%u Jogo inexistente.\n", Num_Linha);
        return;
    }

    /* guarda o vencedor anterior */
    vencedor_anterior = obtem_vencedor_jogo(jogo);

    /* altera o score */
    altera_score_jogo(jogo, novo_score);

    /* obtem o vencedor atual */
    vencedor_atual = obtem_vencedor_jogo(jogo);

    /* atualiza as vitorias das equipas */
    if (vencedor_anterior != EMPATE && vencedor_atual != EMPATE)
    {
        if (strcmp(vencedor_anterior, vencedor_atual) != 0)
        {
            altera_vitorias_equipa(procura_equipa_tabela(tabela_equipas, 
                                                        vencedor_anterior), NAO_VITORIA);
            altera_vitorias_equipa(procura_equipa_tabela(tabela_equipas, vencedor_atual), VITORIA);
        }
    }
    else if (vencedor_atual != EMPATE)
        altera_vitorias_equipa(procura_equipa_tabela(tabela_equipas, vencedor_atual), VITORIA);
        
    else if (vencedor_anterior != EMPATE)
        altera_vitorias_equipa(procura_equipa_tabela(tabela_equipas, 
                                                        vencedor_anterior), NAO_VITORIA);
    
    return;
}

/* --------------------------------------------------------------------------------------------- */
int main()
{
    char comando;

    lista *lista_jogos; /* lista que contem os jogos */
    pTabela_jogos tabela_jogos; /* tabela que contem os jogos */
    pTabela_equipas tabela_equipas; /* tabela que contem as equipas */

    unsigned int Num_Linha = 1; /* numero da linha do comando */

    /* inicializacao das estruturas */
    lista_jogos = inicializa_lista_jogos();
    tabela_jogos = inicializa_tabela_jogos(MODULO);
    tabela_equipas = inicializa_tabela_equipas(MODULO);
    
    

    while((comando = getchar())!= 'x')
        switch (comando)
        {
        case 'a': /* a nome-jogo:nome-equipa1:nome-equipa2:score1:score2 */
            adiciona_jogo(lista_jogos, tabela_jogos, tabela_equipas, Num_Linha++);
            break;
        
        case 'l': /* l */
            lista_todos_jogos(lista_jogos, Num_Linha++); 
            break;
        
        case 'p': /* p nome-jogo */
            procura_jogo(tabela_jogos, Num_Linha++);
            break;

        case 'r': /* r nome-jogo */
            apaga_jogo(tabela_jogos, lista_jogos, tabela_equipas, Num_Linha++);
            break;
        
        case 's': /* s nome-jogo:score1:score2 */
            altera_pontuacao(tabela_jogos, tabela_equipas, Num_Linha++);
            break;
        
        case 'A': /* A nome-equipa */
            adiciona_equipa(tabela_equipas, Num_Linha++);
            break;
        
        case 'P': /* P nome-equipa */
            procura_equipa(tabela_equipas, Num_Linha++);
            break;
            
        case 'g': /* g */
            print_melhores_equipas(tabela_equipas, Num_Linha++);
            break;
        }

        
    /* destroi as estruturas */
    destroi_tabela_equipas(tabela_equipas);
    destroi_tabela_jogos(tabela_jogos);
    destroi_lista_jogos(lista_jogos);
    return 0;
}

