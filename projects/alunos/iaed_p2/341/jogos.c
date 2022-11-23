#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "jogos.h"


/*Funcao auxiliar que retorna 1 caso um jogo ja tenha sido adicionado ou 0 caso contrario
recebe um ponteiro para a Hash Table dos jogos, uma hash e uma string*/
int JogoJaAdicionado(HashTableJogos * HTJ,int hash,char * nome){

    HashNoJogos * aux = HTJ->listasjog[hash];

    for(;aux;aux = aux->proxjogoh){
        if(!strcmp(aux->dadosjogo->nomejogo,nome)){
            return 1;
        }
    }
    return 0;
}


/*Funcao auxiliar que recebe uma string e um ponteiro para a Hash Table das equipas e remove 
1 vitoria a equipa cuja string e igual a dada */
void RemoveVitoria(char * equipa,HashTableEquipas * HTE){
    int hashequipa = Hash(equipa,HTE->capacidade);
    HashNoEquipas * aux = EquipaJaAdicionada(HTE,hashequipa,equipa);
    
    (aux->dadosequipa->vitorias)--;
}


/*Funcao auxiliar que recebe uma string e um ponteiro para a Hash Table das equipas e
 adiciona 1 vitoria a equipa cuja string e igual a dada */
void AdicionaVitoria(char * equipa,HashTableEquipas * HTE){
    int hashequipa = Hash(equipa,HTE->capacidade);
    HashNoEquipas * aux = EquipaJaAdicionada(HTE,hashequipa,equipa);
    
    (aux->dadosequipa->vitorias)++;
}


/*Funcao auxiliar que dado um ponteiro para um no da lista dos jogos e 2 inteiros 
que representam a pontuacao nova de cada equipa altera a pontuacao desse jogo*/
void AlteraGolos(HashNoJogos * nojogo ,int golose1,int golose2){
    nojogo->dadosjogo->golos1 = golose1;
    nojogo->dadosjogo->golos2 = golose2;
}


/*Funcao principal do comando "a"(adiciona um jogo ao sistema),le do stdin 3 strings
(nomes do jogo e de 2 equipas) e 2 inteiros que correspondem aos golos de cada equipa e recebe 
o "conta-comandos",um ponteiro para a estrutura que guarda a cabeca e cauda da lista dos jogos,
um ponteiro paraa Hash Table das equipas e a dos jogos e adiciona 
um jogo ao sistema */
void AdicionarJogo(int * contacomandos,ListaDuplaJogo * listajogos,HashTableJogos * HTJ,HashTableEquipas * HTE){
    char bufferequipa1[MAXNOMEEQUIPA+1],bufferequipa2[MAXNOMEEQUIPA+1],buffernome[MAXNOMEJOGO+1];
    int hashbuffer1,hashbuffer2,hashnome,golose1,golose2;
    NoDuploJogos * novo;
    
    getchar();/*Retirar o espaco apos o comando*/
    scanf(LEITURA_JOGO_COMPLETO,buffernome,bufferequipa1,bufferequipa2,&golose1,&golose2);
    
    hashnome = Hash(buffernome,HTJ->capacidade);

    if (JogoJaAdicionado(HTJ,hashnome,buffernome)){
        printf("%d Jogo existente.\n",*contacomandos);
        (*contacomandos)++;
        return;
    }

    hashbuffer1 = Hash(bufferequipa1,HTE->capacidade);
    hashbuffer2 = Hash(bufferequipa2,HTE->capacidade);

    if(!(EquipaJaAdicionada(HTE,hashbuffer1,bufferequipa1)) || 
    !(EquipaJaAdicionada(HTE,hashbuffer2,bufferequipa2))){
        printf("%d Equipa inexistente.\n",*contacomandos);
        (*contacomandos)++;
        return;
    }

    novo = can_fail_malloc(sizeof(NoDuploJogos));
    novo->equipa1 = can_fail_malloc(sizeof(char)*(strlen(bufferequipa1)+1));
    novo->equipa2 = can_fail_malloc(sizeof(char)*(strlen(bufferequipa2)+1));
    novo->nomejogo = can_fail_malloc(sizeof(char)*(strlen(buffernome)+1));
    strcpy(novo->equipa1,bufferequipa1);
    strcpy(novo->equipa2,bufferequipa2);
    strcpy(novo->nomejogo,buffernome);
    novo->antjogo = listajogos->ultimo;
    novo->proxjogo = NULL;
    novo->golos1 = golose1;
    novo->golos2 = golose2;


    if(golose1 > golose2){
        AdicionaVitoria(novo->equipa1,HTE);
    }
    if (golose1 < golose2){
        AdicionaVitoria(novo->equipa2,HTE);
    }


    if(listajogos->ultimo){
        listajogos->ultimo->proxjogo = novo;
    }else{
        listajogos->cabeca = novo;
    }
    listajogos->ultimo = novo; 

    AdicionarHTJogos(HTJ,hashnome,novo);
    (*contacomandos)++;


}


/*Funcao auxiliar que liberta a memoria de 2 strings(nomes de equipas) recebidas*/
void LibertaNomes(char * equipa1,char * equipa2){
    free(equipa1);
    free(equipa2);
}


/*Funcao auxiliar que liberta a memoria de 1 string(nome do jogo), de 1 no da lista dos jogos 
e de 1 no de colisao na HashTable dos jogos recebidos*/
void LibertaJogo(char * nomejogo,NoDuploJogos * jogo,HashNoJogos * aux){
    free(nomejogo);
    free(jogo);
    free(aux);
}


/*Funcao auxiliar que faz as trocas de ponteiros necessarias
antes a libertacao de memoria das informacoes dos nos relativos ao jogo na Hash Table dos jogos
e na lista dos jogos*/
void TrocaPonteiros(HashNoJogos * auxprocura,ListaDuplaJogo * listajogos){

    if(auxprocura->dadosjogo->antjogo){
        auxprocura->dadosjogo->antjogo->proxjogo = auxprocura->dadosjogo->proxjogo;
    }else{
        /*Caso nao tenha anterior,(ou seja jogo a remover e a cabeca) trocamos a cabeca*/
        listajogos->cabeca = auxprocura->dadosjogo->proxjogo;
    }
    if(auxprocura->dadosjogo->proxjogo){
        auxprocura->dadosjogo->proxjogo->antjogo = auxprocura->dadosjogo->antjogo;
    }else{
        /*Caso nao tenha proximo,(ou seja jogo a remover e a cauda) trocamos a cauda*/
        listajogos->ultimo = auxprocura->dadosjogo->antjogo;
    }
}


/*Funcao auxiliar que faz as conexoes entre os nos "adjacentes" 
da listas do jogo e da Hash Table utilizando outras funcoes auxiliares e a libertacao da memoria 
associada ao jogo na Hash Table dos jogos e no seu no da lista dos jogos*/
void RemocaoJogo(HashNoJogos *auxprocura,HashNoJogos * auxcabeca,HashNoJogos* anterior,
ListaDuplaJogo * listajogos,char * buffer,HashTableJogos *HTJ,int hashbuffer,int *contacomandos){
    
    TrocaPonteiros(auxprocura,listajogos);
    LibertaNomes(auxprocura->dadosjogo->equipa1,auxprocura->dadosjogo->equipa2);
    if(!strcmp(auxcabeca->dadosjogo->nomejogo,buffer)){   
        HTJ->listasjog[hashbuffer] = auxcabeca->proxjogoh; 
        LibertaJogo(auxprocura->dadosjogo->nomejogo,auxprocura->dadosjogo,auxcabeca);
    }else{
        /*Caso em que o no da Hash Table nao e a cabeca,faz a procura guardando o anterior 
        para trocar o ponteiro que apontava para o no a remover */
        for(;strcmp(auxcabeca->dadosjogo->nomejogo,buffer);auxcabeca = auxcabeca->proxjogoh){
            anterior = auxcabeca;
        }
        anterior->proxjogoh = auxcabeca->proxjogoh;
        LibertaJogo(auxprocura->dadosjogo->nomejogo,auxprocura->dadosjogo,auxcabeca);
    }
    (*contacomandos)++;
}


/*Funcao principal que corresponde ao comando "r"(elimina um jogo do sistema),le do stdin uma 
string(nome do jogo),e recebe o "conta-comandos",ponteiros para a Hash Table das equipas e a 
dos jogos e um ponteiro para a estrutura que guarda a cabeca e cauda da lista dos jogos*/
void RemoverJogo(int * contacomandos,HashTableJogos * HTJ,ListaDuplaJogo * listajogos,HashTableEquipas * HTE){

    int hashbuffer;
    char buffer[MAXNOMEJOGO+1];
    HashNoJogos * auxprocura,* auxcabeca,*anterior = NULL;
    
    getchar();/*Retirar o espaco apos o comando*/
    scanf(LEITURA_NOME_JOGO,buffer);
    
    hashbuffer = Hash(buffer,HTJ->capacidade);
    
    /* Verifica se o jogo existe */
    if(!JogoJaAdicionado(HTJ,hashbuffer,buffer)){
        printf("%d Jogo inexistente.\n",*contacomandos);
        (*contacomandos)++;
        return;
    }
    /*Procura o jogo*/
    for(auxprocura = HTJ->listasjog[hashbuffer],auxcabeca = HTJ->listasjog[hashbuffer];
    strcmp(auxprocura->dadosjogo->nomejogo,buffer);auxprocura = auxprocura->proxjogoh);


    if(auxprocura->dadosjogo->golos1 == auxprocura->dadosjogo->golos2){
        RemocaoJogo(auxprocura,auxcabeca,anterior,listajogos,buffer,HTJ,hashbuffer,contacomandos);

    }else if(auxprocura->dadosjogo->golos1 > auxprocura->dadosjogo->golos2){
        RemoveVitoria(auxprocura->dadosjogo->equipa1,HTE);
        RemocaoJogo(auxprocura,auxcabeca,anterior,listajogos,buffer,HTJ,hashbuffer,contacomandos);                 

    }else if(auxprocura->dadosjogo->golos1 < auxprocura->dadosjogo->golos2){
        RemoveVitoria(auxprocura->dadosjogo->equipa2,HTE);
        RemocaoJogo(auxprocura,auxcabeca,anterior,listajogos,buffer,HTJ,hashbuffer,contacomandos);     
        
    }
}


/*Funcao principal que corresponde ao comando "p"(procura um jogo no sistema), le do stdin o nome 
do jogo e recebe "conta-comandos" e um ponteiro para a Hash Table dos jogos,escreve no stdout as
 informacoes relativas ao jogo que se deseja procurar*/
void ProcuraJogo(int * contacomandos,HashTableJogos * HTJ){
    
    int hashbuffer;
    char buffer[MAXNOMEJOGO+1];
    HashNoJogos * auxprocura;

    getchar();/*Retirar o espaco apos o comando*/
    scanf(LEITURA_NOME_JOGO,buffer);
    
    hashbuffer = Hash(buffer,HTJ->capacidade);

    for(auxprocura = HTJ->listasjog[hashbuffer];auxprocura; auxprocura = auxprocura->proxjogoh){
        if(!strcmp(auxprocura->dadosjogo->nomejogo,buffer)){
            printf("%d %s %s %s %d %d\n",*contacomandos,
            buffer,
            auxprocura->dadosjogo->equipa1,
            auxprocura->dadosjogo->equipa2,
            auxprocura->dadosjogo->golos1,
            auxprocura->dadosjogo->golos2);
            (*contacomandos)++;
            return;
        }
    }
    /*Caso nao encontre o jogo*/
    printf("%d Jogo inexistente.\n",*contacomandos);
    (*contacomandos)++;
}


/*Funcao auxiliar que recebe um ponteiro para a Hash Table das equipas e 2 strings(nome das equipas)
e remove 1 vitoria a 1a equipa recebida e adiciona uma vitoria a 2a equipa recebida*/
void TrocaVitorias(HashTableEquipas * HTE,char * equipa1,char * equipa2){
    RemoveVitoria(equipa1,HTE);
    AdicionaVitoria(equipa2,HTE);
}


/*Funcao principal que corresponde ao comando "s"(altera a pontuacao de um jogo ja adicionado ao sistema),
le do stdin o nome do jogo e a nova contagem dos golos da equipa1 e da equipa2, recebe o 
"conta-comandos" e ponteiros para a Hash Table dos jogos e a para a das equipas*/
void AlteraPontuacao(int * contacomandos,HashTableEquipas * HTE,HashTableJogos * HTJ){
    int hashbuffer,novosgolos1,novosgolos2;
    char buffer[MAXNOMEJOGO+1];
    HashNoJogos * auxprocura;

    getchar();/*Retirar o espaco apos o comando*/
    scanf(LEITURA_ALTERA_GOLOS,buffer,&novosgolos1,&novosgolos2);
    
    hashbuffer = Hash(buffer,HTJ->capacidade);
    /*Verifica se o jogo existe */
    if(!JogoJaAdicionado(HTJ,hashbuffer,buffer)){
        printf("%d Jogo inexistente.\n",*contacomandos);
        (*contacomandos)++;
        return;
    }

    /*Procura o jogo que queremos alterar a pontuacao*/
    for(auxprocura = HTJ->listasjog[hashbuffer];strcmp(auxprocura->dadosjogo->nomejogo,buffer);
    auxprocura = auxprocura->proxjogoh);

    if(novosgolos1 == novosgolos2){
        if(auxprocura->dadosjogo->golos1 > auxprocura->dadosjogo->golos2){
            RemoveVitoria(auxprocura->dadosjogo->equipa1,HTE);
        }else if(auxprocura->dadosjogo->golos1 < auxprocura->dadosjogo->golos2){
            RemoveVitoria(auxprocura->dadosjogo->equipa2,HTE);
        }	
    }else if(novosgolos1 > novosgolos2){
        if(auxprocura->dadosjogo->golos1 < auxprocura->dadosjogo->golos2){
            TrocaVitorias(HTE,auxprocura->dadosjogo->equipa2,auxprocura->dadosjogo->equipa1);
        }else if(auxprocura->dadosjogo->golos1 == auxprocura->dadosjogo->golos2){
            AdicionaVitoria(auxprocura->dadosjogo->equipa1,HTE);		
        }
    }else if(novosgolos1 < novosgolos2){
        if(auxprocura->dadosjogo->golos1 == auxprocura->dadosjogo->golos2){
            AdicionaVitoria(auxprocura->dadosjogo->equipa2,HTE);
        }else if(auxprocura->dadosjogo->golos1 > auxprocura->dadosjogo->golos2){
            TrocaVitorias(HTE,auxprocura->dadosjogo->equipa1,auxprocura->dadosjogo->equipa2);
        }
    }
    AlteraGolos(auxprocura,novosgolos1,novosgolos2);
    (*contacomandos)++;
}


/*Funcao principal que corresponde ao comando "l", recebe o "conta-comandos" e um ponteiro para
a estrutura que guarda a cabeca e a cauda da lista dos jogos, escreve no stdout as informacoes
de todos os jogos atualmente no sistema*/
void ListarJogos(int * contacomandos,ListaDuplaJogo * jogos){
    NoDuploJogos * aux = jogos->cabeca;
    
    for(;aux;aux = aux->proxjogo){
        printf("%d %s %s %s %d %d\n",*contacomandos,aux->nomejogo,aux->equipa1,
        aux->equipa2,aux->golos1,aux->golos2);
    }
    
    (*contacomandos)++;
}


/*Funcao auxiliar que recebe um ponteiro para a estrutura que guarda a cabeca e a cauda da lista dos 
jogos e liberta toda a memoria alocada para a lista e seus conteudos*/
void ApagarJogos(ListaDuplaJogo * jogos){
    NoDuploJogos * aux;
    while (jogos->cabeca){
        aux = jogos->cabeca;
        jogos->cabeca = jogos->cabeca->proxjogo;
        free(aux->equipa1);
        free(aux->equipa2);
        free(aux->nomejogo);
        free(aux);   
    }
    free(jogos);
}
