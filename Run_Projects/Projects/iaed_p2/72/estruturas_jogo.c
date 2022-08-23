#include "estruturas_jogo.h"

/*
  init_jogos: () -> Jogos
  Retorna um ponteiro para uma estrutura Jogos ja inicializada
*/
Jogos init_jogos(){
    return calloc(1,sizeof(struct jogos));
}

/*
  insere_jogo: (Jogos, Jogo) -> ()
  Insere um jogo na estrutura Jogos
*/
void insere_jogo(Jogos jogos, Jogo jogo){
    int ind;

    /*obtem a hash do nome do jogo*/
    ind = hash(nome_jogo(jogo),M_jogos);

    /*insere o elemento na entrada hash da hashtable*/
    jogos->ht[ind] = push_jogo(jogos->ht[ind],jogo);

    /*verifica se o jogo e o primero inserido*/
    if(jogos->primeiro == NULL){
        /*define o jogo como primeiro jogo inserido*/
        jogos->primeiro = jogos->ht[ind];
        jogos->ht[ind]->ant_inserido = NULL;
    }

    else{
        /*liga o jogo com o anterior*/
        jogos->ht[ind]->ant_inserido = jogos->ultimo;
        jogos->ultimo->prox_inserido = jogos->ht[ind];
    }

    /*define o proximo inserido como NULL e define o jogo como ultimo inserido*/
    jogos->ht[ind]->prox_inserido = NULL;
    jogos->ultimo = jogos->ht[ind];
}

/*
  push_jogo: (No_Jogo, Jogo) -> ()
  Insere um jogo na entrada da hashtable selecionada
*/
No_Jogo push_jogo(No_Jogo atual, Jogo jogo){
    No_Jogo novo;

    novo = malloc(sizeof(struct no_jogo));
    novo->jogo = jogo;
    novo->prox = atual;

    /*coloca o jogo na cabeca da entrada da hashtable*/
    return novo;
}

/*
  procura_jogo: (Jogos, char*) -> Jogo
  Procura um jogo
*/
Jogo procura_jogo(Jogos jogos, char* nome){
    int ind;

    ind = hash(nome,M_jogos);
    
    return procura_ht_jogos(jogos->ht[ind],nome);
}

/*
  procura_ht_jogos: (No_Jogo, char*) -> Jogo
  Procura um jogo na entrada da hashtable correspondente
*/
Jogo procura_ht_jogos(No_Jogo no, char* nome){
    while(no != NULL){
        /*compara o nome dado com o nome do jogo a ser percorrido*/
        if(!strcmp(nome,nome_jogo(no->jogo)))
            return no->jogo;

        no = no->prox;
    }

    /*retorna NULL caso o jogo nao exista*/
    return NULL;
}

/*
  remove_jogos: (Jogos, char*) -> Jogo
  Remove um jogo da hashtable e da linked list  
*/
Jogo remove_jogos(Jogos jogos, char* nome){
    int ind;
    Jogo jogo;
    No_Jogo no, ant;
    
    /*obtem a coluna com os jogos com a mesma hash*/
    ind = hash(nome,M_jogos);
    no = jogos->ht[ind];

    /*procura pelo jogo guardanto o jogo anterior da hashtable*/
    while(no != NULL){
        if(!strcmp(nome,nome_jogo(no->jogo)))
            break;

        ant = no;
        no = no->prox;
    }

    /*retorna NULL caso nao encontre*/
    if(no == NULL)
        return NULL;

    /*verifica se o elemento esta na cabeca da coluna*/
    if(no == jogos->ht[ind])   
        jogos->ht[ind] = no->prox;

    else
        ant->prox = no->prox;
    
    /*verifica se o elemento esta no meio da linked list*/
    if(no->ant_inserido != NULL && no->prox_inserido != NULL){
        no->ant_inserido->prox_inserido = no->prox_inserido;
        no->prox_inserido->ant_inserido = no->ant_inserido;
    }
    
    else{ 
        /*verifica se e o primeiro elemento*/
        if(no == jogos->primeiro){
            jogos->primeiro = no->prox_inserido;
            
            /*verifica se nao e o ultimo*/
            if(no->prox_inserido != NULL)
                no->prox_inserido->ant_inserido = NULL;
        }

        /*verifica se e o ultimo elemento*/
        if(no == jogos->ultimo){
            jogos->ultimo = no->ant_inserido;
            
            /*verifica se nao e o primeiro*/
            if(no->ant_inserido != NULL)
                no->ant_inserido->prox_inserido = NULL;
        }
    }
    
    /*liberta no e retorna o jogo correspondente*/
    jogo = no->jogo;
    free(no);
    return jogo;
}

/*
  print_todos_jogos: (Jogos, unsigned int) -> ()
  Imprime todos os jogos por ordem de insercao
*/
void print_todos_jogos(Jogos jogos, unsigned int NL){
    No_Jogo temp = jogos->primeiro;
    
    /*percorre toda a linked list e imprime todos os jogos*/
    while(temp != NULL){
        printf("%u %s %s %s %d %d\n",NL,nome_jogo(temp->jogo),nome_equipa(obtem_equipa1(temp->jogo)),
               nome_equipa(obtem_equipa2(temp->jogo)),obtem_score1(temp->jogo),obtem_score2(temp->jogo));
        
        temp = temp->prox_inserido;
    }
}

/*
  destroi_jogos: (Jogos) -> ()
  Liberta o espaco usado pelas estruturas de Jogos assim como destroi todos
  os jogos existentes
*/
void destroi_jogos(Jogos jogos){
    No_Jogo temp;

    /*percorre toda a linked list*/
    while(jogos->primeiro != NULL){
        temp = jogos->primeiro->prox_inserido;
        
        free_jogo(jogos->primeiro->jogo);      
        free(jogos->primeiro);
        
        jogos->primeiro = temp;
    }

    /*liberta a estrutura*/
    free(jogos);
}
