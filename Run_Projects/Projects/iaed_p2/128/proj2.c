#include "funcoes.h"

void le_comandos(link_jogo *heads_jogo,link*heads,limites_lista *jogo,int n_linha);

int main()
{
    /*hashtable para as equipas*/
    link* heads;

    /*hashtable para os jogos*/
    link_jogo* heads_jogo;

    /*limites da lista duplamente ligada*/
    limites_lista* jogo;
    
    

    /*variavel que indica o numero da linha do comando*/
    int n_linha=1;

    /*inicializacao das hashtables e da lista duplamente ligada*/
    jogo=nova_lista();
    heads=inicializa(HEADS_EQUIPAS);
    heads_jogo=inicializa_hash_jogo(HEADS_JOGOS);

    le_comandos(heads_jogo,heads,jogo,n_linha);
    /*no fim detroi as hashtables e a lista */
    destroi_tudo(heads_jogo,jogo,heads,HEADS_JOGOS,HEADS_EQUIPAS);
    return 0;
}

/*funcao que le e executa os comandos introduzidos*/
void le_comandos(link_jogo *heads_jogo,link*heads,limites_lista *jogo,int n_linha)
{
    char letra;
    scanf("%c",&letra);

    /*estrutura que vai lendo a letra do comando e executando o comando
    conforme a letra introduzida ate ser introduzida a letra 'x'*/
    while(letra!='x')
    {
        switch(letra)
        {
            case 'a':
                adiciona_jogo(jogo,heads_jogo,heads,n_linha);
                /*o numero da linha incrementa a cada chamada de funcao*/
                n_linha++;
                break;
            case 'A':
                adiciona_equipa(heads,n_linha);
                n_linha++;
                break;
            case 'l':
                print_jogos(jogo,n_linha);
                n_linha++;
                break;
            case 'p':
                devolve_jogo(heads_jogo,n_linha);
                n_linha++;
                break;
            case 'P':
                devolve_equipa(heads,n_linha);
                n_linha++;
                
                break;
            case 'r':
                apaga_jogo(heads_jogo,jogo,n_linha);
                n_linha++;
                break;
            case 's':
                altera_score(heads_jogo,n_linha);
                n_linha++;
                break;
            case 'g':
                equipas_mais_vitorias(heads,HEADS_EQUIPAS,n_linha);
                n_linha++;
                break;
        }
        scanf("%c",&letra);
    }

}
