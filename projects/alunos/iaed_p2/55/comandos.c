#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "constantes.h"
#include "comandos.h"
#include "listas.h"
#include "estruturas.h"
#include "tabelas_dispersao.h"

/* Chama a funcao do respectivo comando recebido */
void seleciona_funcao(char comando, lista_ponteiro* lp, tabela_equipa* TB_eq, \
                         tabela_jogo* TB_jg, int M, int MJ, int NL){

    if(DEBUG)
        printf("s_f:  comando=%c### NL = %d\n", comando, NL);

    switch (comando){
        case 'a':	/* a - Adiciona um novo jogo. */
            a(lp, TB_eq, TB_jg, M, MJ, NL); break;
        case 'A':	/* A - Adiciona uma nova equipa. */
            A(TB_eq, M, NL); break;
        case 'l':	/* l - Lista todos os jogos pela ordem em que foram introduzidos. */
            l(lp, NL); break;
        case 'p':	/* p - Procura um jogo. */
            p(TB_jg , MJ, NL); break;
        case 'P':	/* P - Procura uma equipa. */
            P(TB_eq, M, NL); break;
        case 'r':	/* r - Apaga um jogo. */
            r(lp, TB_eq, TB_jg, M, MJ, NL); break;
        case 's':	/* s - Altera a pontuacao (score) de um jogo. */
            s(TB_eq, TB_jg, M, MJ, NL); break;
        case 'g':	/* g - Encontra as equipas que venceram mais jogos. */
            g(TB_eq, M, NL); break;
    }
}

/* a: Adiciona um novo jogo. */
void a(lista_ponteiro* lp, tabela_equipa* TB_equipa, tabela_jogo* TB_jogo, int M, int MJ, int NL){

    char jogo[MAX_CARACTERES] = "", equipa1[MAX_CARACTERES] = "", equipa2[MAX_CARACTERES] = "";
    int score1 = 0, score2 = 0;
    elo_jogo Novo_no = NULL;
    elo_ponteiro no_ponteiro;
    elo_equipa No_equipa1 = NULL, No_equipa2 = NULL;
    lista_equipa *LE1 = NULL, *LE2 = NULL;
    lista* LJ = NULL;

    /* Formato de entrada: a nome:equipa1:equipa2:score1:score2 */
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%i:%i", jogo, equipa1, equipa2, &score1, &score2);
    getchar();

    if(DEBUG)
        printf("%d a %s:%s:%s:%i:%i\n", NL, jogo, equipa1, equipa2, score1, score2);

    /* Retorna ponteiro para lista_equipa pesquisada ou NULL caso nao exista a lista. */
    LE1 = pesquisa_lista_equipa(TB_equipa, equipa1, M);
    LE2 = pesquisa_lista_equipa(TB_equipa, equipa2, M);
    /* Retorna ponteiro para lista_jogo pesquisada ou NULL caso nao exista a lista. */
    LJ = pesquisa_lista_jogo(TB_jogo, jogo, MJ);

    /* Formato de saida: NADA (excepto erro). */
    /* Erros:
    NL Jogo existente. no caso de ja existir um jogo com esse nome no sistema. */
    if(LJ != NULL){
        if((procura_no_jogo(LJ, jogo)) != NULL){
            printf("%d Jogo existente.\n", NL);
            return;
        }
    }
    /* NL Equipa inexistente. no caso de uma das equipas ou ambas nao existirem no sistema. */
    if(LE1 != NULL && LE2 != NULL){
        No_equipa1 = procura_no_equipa(LE1, equipa1);
        No_equipa2 = procura_no_equipa(LE2, equipa2);
    /* NL Equipa inexistente. no caso de uma das equipas ou ambas nao existirem no sistema. */
        if(No_equipa1 == NULL || No_equipa2 == NULL){
            printf("%d Equipa inexistente.\n", NL);
            return;
        }
        else if(No_equipa1 != NULL && No_equipa2 != NULL){
            /* Retorna ponteiro para lista de jogos inserida ou cria caso nao exista a lista. */
            LJ = insere_ou_cria_lista_jogo(TB_jogo, jogo, MJ);
            /* Cria/inicializa um no_jogo (struct estr_jogo) e retorna o no_jogo */
            Novo_no = cria_no_jogo(jogo, equipa1, equipa2, score1, score2);
            /* Adiciona um no como o ultimo elemento da lista. */
            no_ponteiro = cria_no_ponteiro(Novo_no);
            Novo_no->pt_no_ponteiro = no_ponteiro;
            no_ponteiro->ponteiro = Novo_no;
            adiciona_fim(LJ, Novo_no);
            adiciona_fim_ponteiro(lp, no_ponteiro);
            /* Incrementa o numero de vitorias da Equipa vencedora. */
            if(score1 > score2){
                *(No_equipa1->vitorias) += 1; 
            }
            else if(score1 < score2){
                *(No_equipa2->vitorias) += 1; 
            }
        }
    }
    else{
        printf("%d Equipa inexistente.\n", NL);
    }
    return;
}

/*  A: Adiciona uma nova equipa.*/
void A(tabela_equipa* TB_equipa, int M, int NL){

    char nome[MAX_CARACTERES] = "";
    elo_equipa Novo_no = NULL;
    lista_equipa* LE = NULL;

    if(DEBUG)
        printf("comando A: \n");

    /* Formato de entrada: A nome */
    scanf(" %[^\n]", nome);
    getchar();

    if(DEBUG)
        printf("A %d:%s\n", NL, nome);

    /* Retorna ponteiro para lista_equipa inserida ou NULL caso nao exista a lista. */
    LE = insere_ou_cria_lista_equipa(TB_equipa, nome, M);

    if((procura_no_equipa(LE, nome)) != NULL){
        printf("%d Equipa existente.\n", NL);
    }
    else{
        /* Cria/inicializa um no_equipa (struct estr_equipa) e retorna o no_equipa */
        Novo_no = cria_no_equipa(nome);
        /* Adiciona o no_equipa como o ultimo elemento da lista. */
        adiciona_equipa_fim(LE, Novo_no);
    }
    return;
}

/* l: Lista todos os jogos pela ordem em que foram introduzidos. */
void l(lista_ponteiro* lp, int NL){
    
    elo_ponteiro inicio = lp->inicio;

    /* Formato de entrada: l */
    getchar();

    if(DEBUG)
        printf("comando l: NL = %d\n", NL);

    /* Formato de saida: Uma linha por jogo no formato abaixo*/
    /* NL nome-jogo nome-equipa1 nome-equipa2 score1 score2 */
    /* Os jogos deverao ser listados pela ordem em que foram introduzidos. */
    while (inicio != NULL){
        printf("%d %s %s", NL, *(inicio->ponteiro->jogo), *(inicio->ponteiro->equipa1) );
        printf(" %s", *(inicio->ponteiro->equipa2) );
        printf(" %d %d\n", *(inicio->ponteiro->score1), *(inicio->ponteiro->score2) );
        inicio = inicio->proximo;
    }
   
    /* Caso nao exista nenhum jogo no sistema, o comando nao imprime nada. */
    /* Erros: Nao aplicavel. */
    return;
}

/* p: Procura um jogo. */
void p(tabela_jogo* TB_jogo ,int MJ, int NL){

    char jogo[MAX_CARACTERES] = "";
    elo_jogo No_jogo = NULL;
    lista* LJ = NULL;

    /* Formato de entrada: p nome */
    scanf(" %[^\n]", jogo);
    getchar();

    if(DEBUG)
        printf("p %s\n", jogo);

    if(DEBUG)
        printf("comando l: NL = %d\n", NL);

    /* Retorna ponteiro para lista_jogo pesquisada ou NULL caso nao exista a lista. */
    LJ = pesquisa_lista_jogo(TB_jogo, jogo, MJ);
    
    if(LJ != NULL){
        No_jogo = procura_no_jogo(LJ, jogo);
    
        /* Formato de saida: Igual ao formato de saida do comando l mas apenas com o jogo nome. */
        if(No_jogo != NULL){
            printf("%d %s %s %s", NL, *(No_jogo->jogo), *(No_jogo->equipa1), *(No_jogo->equipa2));
            printf(" %d %d\n", *(No_jogo->score1), *(No_jogo->score2) );
        }
        /* Erros:
        NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema. */
        else{
            printf("%d Jogo inexistente.\n", NL);
        }
    }
    else{
        printf("%d Jogo inexistente.\n", NL);
    }
    return;
}

/* P: Procura uma equipa. */
void P(tabela_equipa* TB_equipa, int M, int NL){

    char equipa[MAX_CARACTERES] = "";
    elo_equipa No_equipa = NULL;
    lista_equipa* LE = NULL;

    /* Formato de entrada: P nome */
    scanf(" %[^\n]", equipa);
    getchar();

    /* Retorna ponteiro para lista_equipa pesquisada ou NULL caso nao exista a lista. */
    LE = pesquisa_lista_equipa(TB_equipa, equipa, M);

    if(DEBUG)
        printf("P %s\n", equipa);

    if(LE != NULL){
        No_equipa = procura_no_equipa(LE, equipa);

        if(No_equipa == NULL){
            printf("%d Equipa inexistente.\n", NL);
        }
        /* Formato de saida: NL nome numero-de-jogos-ganhos. */
        else{
            printf("%d %s %d\n", NL, equipa, *(No_equipa->vitorias) );
        }
    }
    else{
        printf("%d Equipa inexistente.\n", NL);
    }
    return;
}

/* r: Apaga um jogo. */
void r(lista_ponteiro* lp, tabela_equipa* TB_equipa, tabela_jogo* TB_jogo, int M, int MJ, int NL){

    char jogo[MAX_CARACTERES] = "";
    elo_jogo No_jogo = NULL;
    elo_ponteiro no_ponteiro = NULL;
    elo_equipa No_equipa1 = NULL, No_equipa2 = NULL;
    lista_equipa* LE1 = NULL;
    lista_equipa* LE2 = NULL;
    lista* LJ = NULL;

    /* Formato de entrada: r nome */
    scanf(" %[^\n]", jogo);
    getchar();

    if(DEBUG)
        printf("r %s\n", jogo);

    /* Retorna ponteiro para lista_jogo pesquisada ou NULL caso nao exista a lista. */
    LJ = pesquisa_lista_jogo(TB_jogo, jogo, MJ);
    
    if(LJ != NULL){

        No_jogo = procura_no_jogo(LJ, jogo);
        /* Formato de saida: NADA (excepto erro). */
        if(No_jogo != NULL){
            /* Retorna ponteiro para lista_equipa pesquisada ou NULL caso nao exista a lista. */
            LE1 = pesquisa_lista_equipa(TB_equipa, *(No_jogo->equipa1), M);
            LE2 = pesquisa_lista_equipa(TB_equipa, *(No_jogo->equipa2), M);

            if(LE1 != NULL && LE2 != NULL){
                No_equipa1 = procura_no_equipa(LE1, *(No_jogo->equipa1));
                No_equipa2 = procura_no_equipa(LE2, *(No_jogo->equipa2));
                /* Decrementa o numero de vitorias da Equipa vencedora. */
                if(*(No_jogo->score1) > *(No_jogo->score2)){
                    *(No_equipa1->vitorias) -= 1; 
                }
                else if(*(No_jogo->score1) < *(No_jogo->score2)){
                    *(No_equipa2->vitorias) -= 1; 
                }
                /* Remove o jogo. */
                no_ponteiro = No_jogo->pt_no_ponteiro;
                No_jogo->pt_no_ponteiro = NULL;
                remove_no_ponteiro(lp, no_ponteiro);
                remove_no_jogo(LJ, No_jogo); 
            }
        }
        /* Erros:
        NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema. */
        else{
            printf("%d Jogo inexistente.\n", NL);
        }
    }
    /* Erros:
    NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema. */
    else{
        printf("%d Jogo inexistente.\n", NL);
    }
    return;
}

/* s: Altera a pontuacao (score) de um jogo. */
void s(tabela_equipa* TB_equipa, tabela_jogo* TB_jogo, int M, int MJ, int NL){

    char jogo[MAX_CARACTERES] = "";
    int score1 = 0, score2 = 0, score_velho1 = 0, score_velho2 = 0;
    elo_jogo No_jogo = NULL;
    elo_equipa No_equipa1 = NULL, No_equipa2 = NULL;
    lista_equipa *LE1 = NULL, *LE2 = NULL;
    lista* LJ = NULL;

    /* Formato de entrada: s nome:score1:score2 */
    scanf(" %[^:]:%i:%i", jogo, &score1, &score2);
    getchar();

    LJ = pesquisa_lista_jogo(TB_jogo, jogo, MJ);

    if(LJ != NULL){
        No_jogo = procura_no_jogo(LJ, jogo);
        /* Formato de saida: NADA (excepto erro). */
        if(No_jogo != NULL){
            LE1 = pesquisa_lista_equipa(TB_equipa, *(No_jogo->equipa1), M);
            LE2 = pesquisa_lista_equipa(TB_equipa, *(No_jogo->equipa2), M);
            if(LE1 != NULL && LE2 != NULL){
                score_velho1 = *(No_jogo->score1);
                score_velho2 = *(No_jogo->score2);
                No_equipa1 = procura_no_equipa(LE1, *(No_jogo->equipa1));
                No_equipa2 = procura_no_equipa(LE2, *(No_jogo->equipa2));

                /* Altera o numero de vitorias das Equipas. Jogo com empates. */
                altera_vitorias_empate(score1, score2, score_velho1, score_velho2, \
                                         No_equipa1, No_equipa2); 

                /* Altera o numero de vitorias das Equipas. Jogo como vitorias Equipa1. */
                altera_vitorias_equipa1(score1, score2, score_velho1, score_velho2, \
                                         No_equipa1, No_equipa2); 

                /* Altera o numero de vitorias das Equipas. Jogo como vitorias Equipa2. */
                altera_vitorias_equipa2(score1, score2, score_velho1, score_velho2, \
                                         No_equipa1, No_equipa2); 

                /* Altera score do Jogo. */
                altera_score(score1, score2, No_jogo);
            }
        }
        /* Erros:
        NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema. */
        else{
            printf("%d Jogo inexistente.\n", NL);
        }
    /* Erros:
    NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema. */
    }
    else{
        printf("%d Jogo inexistente.\n", NL);
    }
    return;
}

/* Funcao auxiliar da funcao qsort utilizada na funcao g.*/
int compara_nome(const void* a, const void* b){
    char ***aa, ***bb;
    aa = (char***)a;
    bb = (char***)b;
    return strcmp(**aa, **bb);
}


/* g: Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica. */ 
void g(tabela_equipa* TB_equipa, int M, int NL){

    int i = 0, k = 0;
    elo_equipa inicio = NULL;
    lista_equipa* LE;

    /* Retorna o valor de max_vitorias */
    int Max_vitorias = retorna_max_vitorias_tabela(TB_equipa, M);

    /* Retorna quantidade de equipas com max_vitorias */
    int Contador_vitorias = retorna_contador_max_vitorias_tabela(TB_equipa, M, Max_vitorias);

    /*Cria vetor de ponteiros para os nomes das equipas com max_vitorias. */  
    char*** Vetor_equipas = (char***) can_fail_malloc(sizeof(char**) * Contador_vitorias);

    /*Formato de entrada: g */
    getchar();

    /* Caso nao exista nenhuma equipa, nao imprime nada (nem a palavra Melhores). */
    if(eh_vazia_tabela_equipa(TB_equipa, M)){
        free(Vetor_equipas);
        return;
    }

    if(!eh_vazia_tabela_equipa(TB_equipa, M)){
        for(i = 0; i < M; i++){
            LE = TB_equipa->cabecas_eq[i];
            if(LE != NULL){
                inicio = LE->inicio;
            /* Cria vetor com equipas que tem numero de vitorias igual a max_vitorias.*/
                while (inicio != NULL){
                    if(*(inicio->vitorias) == Max_vitorias){
                        Vetor_equipas[k++] = inicio->equipa;
                    }
                    inicio = inicio->proximo;
                }
            }
        }
    }
    
    qsort(Vetor_equipas, Contador_vitorias, sizeof(char**), compara_nome);

    /* Formato de saida:

    NL Melhores numero-de-jogos-ganhos
    NL * nome-equipa1
    NL * nome-equipa2
    NL * nome-equipa3
    ...
    
    Erros: Nao aplicavel. */

    printf("%d Melhores %d\n", NL, Max_vitorias);
    for(i = 0; i < Contador_vitorias; i++){
        printf("%d * %s\n", NL, *(Vetor_equipas[i]));
    }
    free(Vetor_equipas);

    return;
}

