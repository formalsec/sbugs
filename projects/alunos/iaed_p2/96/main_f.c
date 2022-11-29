#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "main_f.h"


/* adiciona uma equipa */
void A(bloco_hash_equipa *table_e,bloco_hash_equipa *lista_e, int NL){
    char nome_e[Tamanho_max_letras];                     /* variavel usada para guardar o nome */
    equipa *e;                                           /* equipa a adiconar */
    scanf(" %[^:\n]",nome_e);                            /* le o nome da equipa */
    if (procura_equipa_hash(table_e,nome_e) != NULL){    /* procura a equipa e se ela ja existe da erro */
        printf("%d Equipa existente.\n",NL);
    }
    else{                                                /* se nao existe */
    e = can_fail_malloc(sizeof(equipa));                          /* guarda a equipa a adicionar */
    e->nome = can_fail_malloc(sizeof(char)*(strlen(nome_e)+1));   /* garante que nao guarda espaco a mais na memoria para o nome da equipa a adicionar */
    strcpy(e->nome,nome_e);                              
    e->vitorias = 0;                                     
    guarda_lista_e(lista_e,e);                           /* guarda na lista das equipas */
    guarda_equipa_hash(table_e,e);                       /* guarda na hash das equipas */
    }
}


/* adiciona um jogo */
void a(bloco_hash_jogo *table_j,bloco_hash_equipa *table_e,bloco_hash_jogo *lista_ord_h,
bloco_hash_jogo *lista_ord_t,int NL){
    char nome_j[Tamanho_max_letras],equipa1[Tamanho_max_letras],equipa2[Tamanho_max_letras];  /* variaveis dos nomes do jogo e das equipas */
    int score1,score2;                                                                        /* scores das equipas */
    equipa *aux1,*aux2;                                                                       /* variaveis auxiliares para obter as equipas participantes */
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome_j,equipa1,equipa2,&score1,&score2);           
    aux1 = procura_equipa_hash(table_e,equipa1);                                              
    aux2 = procura_equipa_hash(table_e,equipa2);                                              
    if(procura_jogo_hash(table_j,nome_j) != NULL){        /* se o jogo n existe da erro */
        printf("%d Jogo existente.\n",NL);
    }
    else if (aux1 == NULL || aux2 == NULL){               /* se alguma das equipas participantes nao existir da erro */
        printf("%d Equipa inexistente.\n",NL);
    }
    else{                                                 /* senao guarda o jogo */
        jogo *j = can_fail_malloc(sizeof(jogo));                                                       
        j->nome = can_fail_malloc(sizeof(char)*(strlen(nome_j)+1));                                    
        j->equipa1 = aux1;                                                                    
        j->equipa2 = aux2;
        strcpy(j->nome,nome_j);                                                               
        j->score1 = score1 ; j->score2 = score2;                                              
        if ( score1 > score2 ){                           /* atribui vitorias */
            j->equipa1->vitorias+=1;
        }
        else if( score1 < score2 ){
            j->equipa2->vitorias +=1;
        }
        guarda_jogo_hash(table_j,j);                      /* guarda jogo na hash table dos jogos */
        guarda_lista_ord(lista_ord_h,lista_ord_t,j);      /* guarda jogo na lista ordenada dos jogos */
    } 
}

/* imprime a informacao sobre uam equipa */
void P(bloco_hash_equipa *table_e, int NL){
    char nome_e[Tamanho_max_letras];                      /* nome da equipa */
    equipa *aux;                                         
    scanf(" %[^:\n]",nome_e);
    aux = procura_equipa_hash(table_e,nome_e);
    if( aux == NULL){                                     /* se a equipa nao existe da erro */
        printf("%d Equipa inexistente.\n",NL);
    }
    else{                                                 /* senao imprime o nome e as vitorias */
        printf("%d %s %d\n",NL,aux->nome,aux->vitorias);
    }
}

/* imprime a informacao sobre um jogo */
void p(bloco_hash_jogo *table_j, int NL){
    char nome_j[Tamanho_max_letras];                       /* nome do jogo */
    jogo *aux;  
    scanf(" %[^:\n]",nome_j);                   
    aux = procura_jogo_hash(table_j,nome_j);
    if( aux == NULL){                                      /* se a equipa nao existe da erro */
        printf("%d Jogo inexistente.\n",NL);
    }
    else{                                                  /* senao imprime o nome do jogo e das equipas e os scores */
        printf("%d %s %s %s %d %d\n",NL,aux->nome,aux->equipa1->nome,aux->equipa2->nome,
        aux->score1,aux->score2);
    }
}

/* altera o score de um jogo */
void s(bloco_hash_jogo *table_j, bloco_hash_equipa *table_e,int NL){
    char nome_j[Tamanho_max_letras];                       /* nome do jogo */
    int n_score1,n_score2;                                 /* novos scores */
    jogo *aux; 
    scanf(" %[^:\n]:%d:%d",nome_j,&n_score1,&n_score2);
    aux = procura_jogo_hash(table_j,nome_j);               
    if( aux == NULL){                                      /* se o jogo n existir da erro */
        printf("%d Jogo inexistente.\n",NL);
    }
    else{                                                  /* senao altera o score do jogo e reatribui as vitorias */
        equipa *aux_e1, *aux_e2; 
        aux_e1 = procura_equipa_hash(table_e,aux->equipa1->nome);
        aux_e2 = procura_equipa_hash(table_e,aux->equipa2->nome);
        
        if (aux->score1 > aux->score2){                    /* retira uma vitoria a quem tinha ganho antes */
            aux_e1->vitorias--;
        }
        else if (aux->score1 < aux->score2){
            aux_e2->vitorias--;
        }
        if (n_score1 > n_score2){                          /* atribui uma vitoria a quem ganhou consuante o novo score */
            aux_e1->vitorias++;
        }
        else if(n_score1 < n_score2){
            aux_e2->vitorias++;
        }
    aux->score1 = n_score1; aux->score2 = n_score2;        /* atualiza scores do jogo */
    }
}
 

/* remove um jogo da hash table */ 
void r(bloco_hash_jogo *table_j,bloco_hash_jogo *lista_ord_h,bloco_hash_jogo *lista_ord_t,int NL){
    char nome_j[Tamanho_max_letras];                        /* nome do jogo */
    jogo *aux;
    scanf(" %[^:\n]",nome_j);
    aux = procura_jogo_hash(table_j,nome_j);
    if ( aux == NULL){                                      /* se o jogo n existir da erro */
        printf("%d Jogo inexistente.\n",NL);
        return;
    }
    if (aux->score1 > aux->score2){                         /* retira vitorias a quem tinha ganho o jogo */
            aux->equipa1->vitorias--;
        }
        else if (aux->score1 < aux->score2){
           aux->equipa2->vitorias--;
        }
    apaga_lista_ord(lista_ord_h,lista_ord_t,nome_j);        /* remove da lista ordenada do jogos */
    apaga_jogo_hash(table_j,nome_j);                        /* remove da hash table do jogos */
}

/* imprime toda a informacao de todos os jogos por ordem de insercao */
void l(bloco_hash_jogo *head,int NL){                       /* recebe a head da lista ordenada dos jogos */
    bloco_hash_jogo aux;
    aux = (*head);
    if (aux == NULL){                                       /* se a lista esta vazia nao imprima nada */
        return;
    }
    while (aux != NULL){                                    /* senao precorre a lista e imprime a informcao sobre todos os jogos */
        printf("%d %s %s %s %d %d\n",NL,aux->jogo->nome,aux->jogo->equipa1->nome,
        aux->jogo->equipa2->nome,aux->jogo->score1,aux->jogo->score2);
        aux = aux->next;
    }
}

/* imprime todas as equipas com mais vitorias por ordem lexicografica */
void g(bloco_hash_equipa *lista_e, int NL){                 /* recebe a lista de todas as equipas */
    int max_v = 0;                                          /* numero maximo de vitorias */
    bloco_hash_equipa *lista_e_v,aux1,aux2,aux3;                            
    aux1 = lista_e[0];                                      /* primeiro elemento da lista */
    if (aux1 == NULL){
        return;
    }
    lista_e_v = can_fail_malloc(sizeof(bloco_hash_equipa));           /* inicializa a lista ordenada */
    lista_e_v[0] = NULL;                                     
    while (aux1 != NULL){                                    /* percorre a lista das equipas e obtem o numero maximo de vitorias */
        if (aux1->equipa->vitorias > max_v){
            max_v = aux1->equipa->vitorias;
        }
            aux1 = aux1->next;
    }
    aux1 = lista_e[0];                                        /* retorna ao primeiro elemento da lista */
    while (aux1 != NULL){                                     /* percorre a lista das equipas */
        if (aux1->equipa->vitorias == max_v){                 /* se a equipa o maximo numero de vitorias */
            guarda_ord_alfabetica(lista_e_v,aux1->equipa);    /* guarda por ordem lexicografica na lista nova */
        }
        aux1 = aux1->next;
    }
    printf("%d Melhores %d\n",NL,max_v);                      
    aux2 = lista_e_v[0];
    while (aux2 != NULL){
        printf("%d * %s\n",NL,aux2->equipa->nome);             /* imprime todas as equipas com o maximo numero de vitorias por ordem lexicografica */
        aux2 = aux2->next;
    }
    while ((*lista_e_v) != NULL){                              /* apaga a lista ordenada */        
        aux3 = (*lista_e_v)->next;
        free((*lista_e_v));
        (*lista_e_v) = aux3;
    }
    free(lista_e_v);      
}


/* acaba a execucao do programa e liberta a memoria */
void x(bloco_hash_equipa *h_e, bloco_hash_equipa *l_e, bloco_hash_jogo *h_j, bloco_hash_jogo *l_j_h,
bloco_hash_jogo *l_j_t){                   /* recebe a hash das e quipas e dos jogos e todas as listas das equipas e dos jogos */
    int pos_e,pos_j;
    bloco_hash_equipa aux_e;
    bloco_hash_jogo aux_j;
    while ((*l_e) != NULL){                /* apaga todos os blocos da lista das equipas */
        aux_e = (*l_e)->next;
        free((*l_e));
        (*l_e) = aux_e;
    }
    free(l_e);                             /* apaga a lista ou seja hash table de uma linha */
    while ((*l_j_h) != NULL){              /* apaga todos os blocos da lista dos jogos */
        aux_j = (*l_j_h)->next;
        free((*l_j_h));
        (*l_j_h) = aux_j;
    }
    free(l_j_h);                           /* apaga a head da lista dos jogos */                           
    free(l_j_t);                           /* apaga a tail lista dos jogos  */
    for (pos_e = 0; pos_e < Tamanho_hash; pos_e++){     /* apaga todos os blocos da hash tabel das equipas e todos os nomes das equipas  todas equipas */
        while (h_e[pos_e] != NULL){
            aux_e = h_e[pos_e]->next;
            free(h_e[pos_e]->equipa->nome);free(h_e[pos_e]->equipa);free(h_e[pos_e]);
            h_e[pos_e] = aux_e;
        }
    }
    free(h_e);                              /* apaga a hash table das equipas */
    for (pos_j = 0; pos_j < Tamanho_hash; pos_j++){     /* apaga todos os blocos da hash tabel dos jogos e todos os jogos e nomes dos jogos */
        while (h_j[pos_j] != NULL){
            aux_j = h_j[pos_j]->next;
            free(h_j[pos_j]->jogo->nome);free(h_j[pos_j]->jogo);free(h_j[pos_j]);
            h_j[pos_j] = aux_j;
        }
    }
    free(h_j);                              /* apaga a hash table dos jogos */
}