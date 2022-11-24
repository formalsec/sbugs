#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"
#include "comandos.h"
#include "hash_equipa.h"
#include "lista_dupla.h"
#define MAX_TABELA 1000

/*funcao que inicializa as hash tables*/

void init(jogo *tabela_hash[MAX_TABELA],\
equipa *tabela_hash_equipa[MAX_TABELA]) {
  int i;
  for (i = 0; i < MAX_TABELA; ++i) {
    tabela_hash[i] = NULL;
    tabela_hash_equipa[i] = NULL;
  }
}

/*funcao que liberta toda a memoria utilizada*/

void apaga_toda_mem(jogo *tabela_hash[MAX_TABELA],\
equipa *tabela_hash_equipa[MAX_TABELA], node_lista **inicio) {
  apaga_mem_jogo(tabela_hash); 
  apaga_mem_equipa(tabela_hash_equipa);
  apaga_mem_lista(inicio);
}

int main() {
    int NL = 1; /*linha de debug*/
    char comando; /*comando a ser executado*/
    equipa *tabela_hash_equipa[MAX_TABELA]; /*tabela para guardar as equipas*/
    jogo *tabela_hash[MAX_TABELA]; /*tabela para guardar os jogos*/
    node_lista *inicio = NULL; /*cabeca da lista*/
    node_lista *fim = NULL; /*cauda da lista*/
    init(tabela_hash,tabela_hash_equipa); /*iniciar tabelas*/
    scanf("%c",&comando); /*ler o comando*/

    while (comando != 'x') {
        switch (comando) { /*indica o comando a ser executado*/
            case 'a': 
            /*adiciona um jogo ao sistema*/
              adiciona_jogo(NL,tabela_hash,tabela_hash_equipa,&inicio,&fim);
              NL = NL + 1;
              break;

            case 'A':
            /*adiciona uma equipa ao sistema*/
              adiciona_equipa(NL,tabela_hash_equipa);
              NL = NL + 1;
              break;

            case 'l':
            /*lista todos os jogos no sistema*/
              lista_jogos(NL,tabela_hash,&inicio);
              NL = NL +1;
              break;

            case 'p':
            /*procura um jogo no sistema*/
              procura_jogo(NL,tabela_hash);
              NL = NL + 1;
              break;

            case 'P':
            /*procura uma equipa no sistema*/
              procura_equipa(NL,tabela_hash_equipa);
              NL = NL + 1;
              break;

            case 'r': 
            /*apaga um jogo do sistema*/
              apaga_jogo(NL,tabela_hash,tabela_hash_equipa,&inicio,&fim);
              NL = NL + 1;
              break;
            
            case 's':
            /*altera a pontuacao de um jogo no sistema*/
              altera_score(NL,tabela_hash,tabela_hash_equipa);
              NL = NL + 1;
              break;
             
            case 'g':
            /*lista todas as equipas com mais vitorias*/
              equipas_mais_jogos(NL,tabela_hash_equipa);
              NL = NL + 1;
              break;   
        }
        scanf("%c",&comando); /* executa o proximo comando */
    }

    /*liberta toda a memoria utilizada*/
    apaga_toda_mem(tabela_hash,tabela_hash_equipa,&inicio);
    return 0;
}


