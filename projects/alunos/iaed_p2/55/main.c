#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "comandos.h"
#include "constantes.h"
#include "listas.h"
#include "estruturas.h"
#include "tabelas_dispersao.h"

int main(){    

    char comando = '#'; /* Variavel para armazenar o Comando */
    int NL = 0; /* Identificador do numero da linha do comando de input */
    int M = M_HASH; /* Dimensao da tabela de dispersao de equipas. */
    int MJ = MJ_HASH; /* Dimensao da tabela de dispersao de jogos. */
    lista_ponteiro* lp = cria_lista_ponteiros();
    /* Cria tabela de dispersao de equipas. */
    tabela_equipa* TB_equipa = cria_tabela_equipa(M);
    /* Cria tabela de dispersao de jogos. */
    tabela_jogo* TB_jogo = cria_tabela_jogo(MJ);

    /* Obtem comandos e chama a respectiva funcao */
    while((comando = getchar()) != 'x'){
        
        if(DEBUG)
            printf("main: comando=%c### NL = %d\n", comando, NL);

        seleciona_funcao(comando, lp, TB_equipa, TB_jogo, M, MJ, ++NL);
    }

    /* Liberta toda a memoria associada a lista de ponteiros. */
    liberta_lista_ponteiro(lp); 
    /* Liberta toda a memoria associada a uma tabela_equipa (struct tabela_equipa) */
    liberta_tabela_equipa(TB_equipa, M);
    /* Liberta toda a memoria associada a uma tabela_jogo (struct tabela_jogo) */
    liberta_tabela_jogo(TB_jogo, MJ);
 

    return 0;
}