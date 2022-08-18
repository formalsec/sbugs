#include "jogos.h"

/* liberta a memoria ocupada por um jogo */
void apaga_jogo(Jogo a){
    free(a->nome);
    free(a->equipa1);
    free(a->equipa2);
    free(a);
}

/* cria um jogo alocando memoria para o mesmo */
Jogo novo_jogo(char * nome,char * e1,char * e2, int s1, int s2){
    Jogo new = (Jogo)malloc(sizeof(struct jogo));
    new->score_e1 = s1;
    new->score_e2 = s2;
    new->nome = malloc(strlen(nome) +1);
    strcpy(new->nome, nome);
    new->equipa1= malloc(strlen(e1) +1 );
    strcpy(new->equipa1, e1);
    new->equipa2= malloc(strlen(e2) +1);
    strcpy(new->equipa2, e2);
    return new;
}

/* inicia a hashtable dos jogos alocando do memoria para a mesma */
link_jogo * init_tab_jogos(){
    int i,tamanho =TAM_HASHTABLE_JOGOS;
    link_jogo *jogos;
    jogos = malloc(tamanho*sizeof(link_jogo));
    for(i = 0; i < tamanho; i++)
        jogos[i] = NULL;
    return jogos;
}

/* insere um jogo na hashtable dos jogos */
void insere_tab_jogo(Jogo jogo,link_jogo *jogos){
    int tamanho =TAM_HASHTABLE_JOGOS,i = hash(key(jogo),tamanho);
    jogos[i] = insere_jogo_cadeia(jogos[i], jogo);
}

/* insere um jogo na cadeia  tratando assim das colisoes
 na hashtable(externalchaning) dos jogos */
link_jogo insere_jogo_cadeia(link_jogo equi_slot,Jogo jogo){
    link_jogo new = NULL;
    new = malloc(sizeof(struct node_jogo));
    new->next = equi_slot;
    new->jogo = jogo;
    return new;
}


/* procura na hashtable dos jogos um jogo devolvendo o jogo */
Jogo procura_tab_jogo(Key v,link_jogo *jogos){
    int tamanho = TAM_HASHTABLE_JOGOS,
        i = hash(v,tamanho);
    return procura_jogo_cadeia(jogos[i], v);
}

/* procura na cadeia(linkedlist) um jogo pelo nome */
Jogo procura_jogo_cadeia(link_jogo equi_slot,Key v){
    while(equi_slot != NULL){
        if(strcmp(v,key(equi_slot->jogo)) ==0 )
            return equi_slot->jogo;
        equi_slot = equi_slot->next;
    }
    return NULL;
}

/* apaga um jogo da hashtable dos jogos */
void apaga_tab_jogo(link_jogo * jogos,Key nome){
    int i = hash(nome,TAM_HASHTABLE_JOGOS);
    link_jogo temp,anterior;
    temp = jogos[i];
    
    for(temp = jogos[i],anterior = NULL; temp!=NULL;anterior = temp,temp = temp->next){
        if(strcmp(temp->jogo->nome,nome) == 0){
            if(temp == jogos[i])
                jogos[i] = temp->next;
            else
                anterior->next = temp->next;
            temp->jogo->nome = "APAGADO";
        }
    }
    
}


/* inicia a linked list dos jogos */
Lista_jogos inicia_ls(){
    Lista_jogos l = malloc(sizeof(struct lista_jogos));
    l->cabeca = l->ultimo = NULL;
    return l;
}


/* adiciona no fim um jogo a lista duplamente ligada */
Lista_jogos adiciona_jogo_ls(Jogo jogo,Lista_jogos l){
    link_jogo_ls novo = malloc(sizeof(struct node_jogo_ls));
    novo->prev = l->ultimo;
    novo->next = NULL;
    novo->jogo = jogo;
    if(l->ultimo) l->ultimo->next = novo;
    else l->cabeca = novo;
    l->ultimo = novo;
    return l;
}

/* apaga a doublelinked list dos jogos  */
void apaga_ls_jogos(Lista_jogos l){
    link_jogo_ls temp1,temp2;
    temp1 = l->cabeca;
    while(temp1 != NULL){
        temp2 = temp1;
        temp1 = temp1->next;
        free(temp2);
    }
    free(l);
}

/* apaga a tabela dos jogos */
void apaga_tab_jogos(link_jogo * jogos){
    int i;
    link_jogo temp1,temp2;
    Jogo jogo_temp;
    for(i=0; i<TAM_HASHTABLE_JOGOS; i++){
        if(jogos[i] != NULL){
            temp1 = jogos[i];
            while(temp1 != NULL){
                jogo_temp = temp1->jogo;
                temp2 = temp1;
                temp1 = temp1->next;
                apaga_jogo(jogo_temp);
                free(temp2);
            }
        }
    }
    free(jogos);
}





