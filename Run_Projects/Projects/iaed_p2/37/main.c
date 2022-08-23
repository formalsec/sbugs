#include "FUNCOES.h"

/* 
 * A main le o carater(comando) do std input  e realiza a acao pretendida.
 * Inicializa a lista de jogos e de equipas e chama as funcoes que inicializam as hash tables.
*/

int main() {
    /* NL e o "contador" de inputs, incrementado sempre que eh dado um novo comando. */
    int NL = 1;
    char comando;
    /* Inicializacao das listas. */
    tlink LThead = NULL, LTtail = NULL;
    glink LGhead = NULL, LGtail = NULL;
    /* Inicializacao das hash tables. */
    tlink* HashTeams = initTeams();
    glink* HashGames = initGames();
    scanf("%c", &comando);
    while (comando != 'x') {
        switch (comando) {
            case 'a':
                adicionaJogo(NL, &LGhead, &LGtail, HashTeams, HashGames);
                NL++;
                break;
            case 'A':
                adicionaEquipa(NL, &LThead, &LTtail, HashTeams);
                NL++;
                break;
            case 'l':
                listaJogos(NL, &LGhead);
                NL++;
                break;
            case 'p':
                procuraJogo(NL, HashGames);
                NL++;
                break;
            case 'P':
                procuraEquipa(NL, HashTeams);
                NL++;
                break;
            case 'r':
                apagaJogo(NL, &LGhead, &LGtail, HashGames);
                NL++;
                break;
            case 's':
                alteraScore(NL, HashGames);
                NL++;
                break;
            case 'g':
                melhoresEquipas(NL, &LThead);
                NL++;
                break;
        }
        scanf("%c", &comando);
    }
    sair(&LThead, &LTtail, &LGhead, &LGtail, HashTeams, HashGames);
    return 0;
}
