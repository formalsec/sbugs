#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "interacao.h"

/*Recebe as tabelas de jogos e equipas e a fila de jogos e inicializa-as
colocando a NULL todos os ponteiros das variaveis a NULL. Nao retorna nada*/
void inicializa(no_jogo_tabela *tabela_jogos[],no_equipa *tabela_equipas[],lista_jogos **fila_jogos){
    int i;
    /*percorre as tabelas, colocando cada ponteiro a NULL*/
    for(i=0;i< MAX_TABELA;i++){
        tabela_jogos[i] = NULL;
        tabela_equipas[i] = NULL;
    }
    /*alocacao da memoria para a fila e colocacao de ambos componentes a NULL*/
    (*fila_jogos) = (lista_jogos*) can_fail_malloc(sizeof(lista_jogos));
    (*fila_jogos)->inicio = NULL;
    (*fila_jogos)->fim = NULL;
}

/*Recebe a tabela de equipas e a fila de jogos e liberta toda a memoria ocupada por estes*/
void liberta_memoria(no_equipa *tabela_equipas[],lista_jogos **fila_jogos){
    no_equipa *i, *aux_equipa;
    no_jogos *k,*aux_jogo;
    int j;
    /*libertacao da memoria das equipas*/
    for(j=0;j<MAX_TABELA;j++){
        if(!tabela_equipas[j]) /*se for NULL nao tem equipas*/
            continue;
        /*liberta as equipas de cada posicao de memoria*/
        for(i=tabela_equipas[j];i;i = aux_equipa){
            aux_equipa = i->proximo;
            free(i->equipa_do_no.nome);
            free(i);
        }
    }
    /*liberta a memoria dos jogos*/
    for(k=(*fila_jogos)->inicio;k;k=aux_jogo){
        aux_jogo = k->proximo;
        free(k->jogo_n->jogo1.nome);
        free(k->jogo_n->jogo1.equipa1);
        free(k->jogo_n->jogo1.equipa2);
        free(k->jogo_n);
        free(k);
    }
    free((*fila_jogos));
}

/*Le o input do stdio e executa o respetivo comando*/
int main(){
    int c,numero_equipas = 0,linha = 1;
    lista_jogos *fila_jogos; /*guarda a ordem pela qual os jogos foram introduzidos*/
    no_jogo_tabela *tabela_jogos[MAX_TABELA]; /*guarda as informacoes dos jogos introduzidos*/
    no_equipa *tabela_equipas[MAX_TABELA]; /*guarda as informacoes das equipas introduzidas*/
    inicializa(tabela_jogos,tabela_equipas,&fila_jogos); /*inicializa as variaveis*/
    while ((c = getchar()) != 'x'){

         switch (c){

             /*caso em que c == a, ie adicionar um jogo*/
             case 'a':{
                novo_jogo(tabela_equipas,&fila_jogos,tabela_jogos,linha);
                linha++;
                break;

             }

             /* caso em que c == l,ie lista todos os jogos guardados*/
             case 'l':{
                 lista_todos_jogos(fila_jogos,linha);
                 linha++;
                 break;

             }
             /* caso em que c == p,ie procura um determinado jogo*/
             case 'p':{
                 procura_jogo(tabela_jogos,linha);
                 linha++;
                 break;

             }
             /*caso em que c == r,ie apaga um determinado jogo*/
             case 'r':{
                 apaga_jogo_alvo(tabela_equipas,tabela_jogos,&fila_jogos,linha);
                 linha++;
                 break;
             }

             /*caso em que c== r,ie altera o score de um jogo*/
             case 's':{
                 altera_score_jogo(tabela_jogos,tabela_equipas,linha);
                 linha++;
                 break;
             }

             /*caso  em que c == R,ie adiciona uma equipa*/
             case 'A':{
                 adiciona_equipa_alvo(tabela_equipas,linha,&numero_equipas);
                 linha++;
                 break;
             }

             /*caso em que c == P, ie procura um determinada equipa*/
             case 'P':{
                 procura_equipa(tabela_equipas,linha);
                 linha++;
                 break;
             }

             /*caso em que c ==g,ie lista as equipas com mais vitorias*/
             case 'g':{
                 lista_mais_vitorias(tabela_equipas,linha,numero_equipas);
                 linha++;
                 break;
             }
        }
    }
    /*liberta toda a memoria alocada durante a execucao*/
    liberta_memoria(tabela_equipas,&fila_jogos);
    return 0;
}


