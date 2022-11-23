#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "tabelaJogos.h"

int main(){

    /*declaracao de variaveis*/
    char comando;
    char nomeEquipa[1024], nomeEquipa2[1024], nomeJogo[1024];
    int pont1, pont2;
    int ord, numINP;
    pEquipa novaEquipa;
    pJogo novoJogo;
    listaEq equipasAdicionadas;
    pTabela jogosAdicionados;

    /*Inicializacao de variaveis*/
    equipasAdicionadas = criarListaEquipas(); /*Equipas a ser inseridas*/
    jogosAdicionados = novaTabJogos(10000); /*Jogos a ser inseridos*/
    ord = 1;
    numINP = 0;
    novaEquipa = NULL;
    novoJogo = NULL;

    /*Menu de comandos*/
    while ( (comando = getchar()) != 'x'){
        switch (comando){
        case 'A':
            numINP++;
            scanf(" %s", nomeEquipa);
            novaEquipa = criarEquipa(nomeEquipa);
            equipasAdicionadas = adicionarNovaEquipa(novaEquipa, equipasAdicionadas, numINP);
            break;
        
        case 'P':
            numINP++;
            scanf(" %s", nomeEquipa);
            novaEquipa = procurarEquipa(equipasAdicionadas, nomeEquipa);
            mostrarEquipa(novaEquipa, numINP);
            break;

        case 'g':
            numINP++;
            melhoresEquipas(equipasAdicionadas, numINP);
            break;

        case 'a':
            numINP++;
            scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nomeJogo, nomeEquipa, nomeEquipa2, &pont1, &pont2);
            novoJogo = criarJogo(nomeJogo, nomeEquipa, nomeEquipa2, pont1, pont2, equipasAdicionadas, numINP);
            adicionarJogoTabela(jogosAdicionados,novoJogo, ord, numINP);
            ord++;
            break;

        case 'p':
            numINP++;
            scanf(" %s", nomeJogo);
            novoJogo = procurarJogoTabela(jogosAdicionados, nomeJogo);
            mostrarJogo(novoJogo, numINP);
            break;

        case 'r':
            numINP++;
            scanf(" %s", nomeJogo);
            apagarJogoTabela(jogosAdicionados, nomeJogo, numINP);
            break;

        case 's':
            numINP++;
            scanf(" %[^:\n]:%d:%d", nomeJogo, &pont1, &pont2);
            alteraPontuacao(jogosAdicionados, nomeJogo, pont1, pont2, numINP);
            break;
        
        case 'l':
            numINP++;
            listarJogos(jogosAdicionados,  ord, numINP);
            break;
        }
    }
    
    /*Libertacao de memoria*/
    libertarListaEquipas(equipasAdicionadas);
    libertarTabela(jogosAdicionados);
    return 0;
}