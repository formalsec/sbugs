#include "projeto.h"

/* Le o nome do jogo e das equipas a adicionar, assim como os scores das duas 
equipas, verifica se o jogo e inexistente e se as equipas existentes, caso se 
verifiquem as condicoes adiciona o jogo a hash table e a lista ligada */
void add_jogo(equipa *table_equipas, jogo *table_jogos, jogo *head, jogo *tail, int linha){
    /* Buffers utilizados para as strings */
    char nome_jogo[MAXSTR], nome_equipa1[MAXSTR], nome_equipa2[MAXSTR] ;
    int score1=0, score2=0;

    scanf(" %[^:]:%[^:]:%[^:]:%d:%d", nome_jogo, nome_equipa1, nome_equipa2, &score1, &score2);

    /* Funcoes procura_jogo e procura_equipa devolvem NULL caso nao encontrem
    nenhum jogo/equipa com o nome dado */
    if(procura_jogo(table_jogos, nome_jogo)!=NULL){
        printf("%d Jogo existente.\n", linha);
        return;
    }
    if (procura_equipa(table_equipas, nome_equipa1)==NULL ||
        procura_equipa(table_equipas, nome_equipa2)==NULL){
        printf("%d Equipa inexistente.\n", linha);
        return;
    }

    add_jogo_hash(table_jogos, table_equipas, nome_jogo, nome_equipa1, nome_equipa2, score1, score2);
    add_jogo_lista(head, tail, table_jogos, nome_jogo);
}

/* Adiciona jogo a hash table, calculando o indice da tabela correspondente
ao nome do jogo dado atraves da funcao hash*/ 
void add_jogo_hash(jogo*table_jogos, equipa*table_equipas, char*nome_jogo, char*nome_equipa1, char*nome_equipa2,int score1,int score2){
    int i;

    i=hash(nome_jogo, HASH_TABLE_SIZE_JOGOS);

    table_jogos[i] = insere_jogo(&table_jogos[i], table_equipas, nome_jogo, nome_equipa1, nome_equipa2, score1, score2);

    return;
}

/* Aloca memoria para o jogo, para o nome do jogo e para os scores do jogo, cria
o jogo dado o que recebe como input e insere-o no inicio da lista */
jogo insere_jogo(jogo *head, equipa *table_equipas, char *nome_jogo, char *nome_equipa1, char *nome_equipa2,int score1,int score2){
    jogo novo = (jogo)malloc(sizeof(struct str_jogo));
    novo->nome = (char *) malloc(sizeof(char)*(strlen(nome_jogo)+1));
    strcpy(novo->nome,nome_jogo);
    
    /* Associa as equipas de um jogo as equipas ja criadas na hash table das equipas */
    novo->equipa1 = procura_equipa(table_equipas, nome_equipa1);
    novo->equipa2 = procura_equipa(table_equipas, nome_equipa2);

    /* Atualiza o numero de jogos ganhos das equipas */
    if(score1>score2){
        (*novo->equipa1->jogos_ganhos)++;
    }
    else if(score2>score1){
        (*novo->equipa2->jogos_ganhos)++;
    }

    novo->score1 = (int *) malloc(sizeof(int));
    *novo->score1 = score1;
    novo->score2 = (int *) malloc(sizeof(int));
    *novo->score2 = score2; 

    novo->next = *head;
    return novo;
}

/* Apos ter adicionado o jogo a hash table, encontra-o e adiciona-o 
no final da lista ligada, utilizando a tail para tal */
void add_jogo_lista(jogo *head, jogo *tail, jogo *table_jogos, char* nome_jogo){
    jogo novo;

    /* Encontra o jogo na hash table atraves do seu nome */
    novo = procura_jogo(table_jogos, nome_jogo);

    novo->next_lista = NULL;

    /* Caso nao existam jogos na lista, tanto a tail como a head sao atualizadas*/
    if(*head == NULL){
        *tail=novo;
        *head=novo;
        return;
    }

    /* Em todos os outros casos, apenas a tail e atualizada */
    (*tail)->next_lista=novo;
    *tail=novo;
}

/* Funcao que devolve o jogo com o nome dado, caso nao encontre devolve NULL 
Calcula o indice em que o jogo se pode encontrar na hash table, apenas procurando
na lista correspondente a esse indice*/
jogo procura_jogo(jogo *table_jogos, char *nome_jogo) {
    int i;
    i=hash(nome_jogo, HASH_TABLE_SIZE_JOGOS);

    return searchList_jogo(table_jogos[i], nome_jogo);
}

/* Percorre toda a lista ate encontrar o jogo com o nome dado */
jogo searchList_jogo(jogo head, char *nome_jogo){  
    jogo aux;
    aux = head;  
    while (aux != NULL){  
        if (strcmp(aux->nome,nome_jogo)==0){
            return aux;  
        }  
        aux = aux->next;  
    }  
    return NULL;  
} 

/* Percorre a lista ligada dos jogos, imprimindo toda a informacao associada aos mesmos */
void print(jogo head, int linha) {
    jogo first = head;

    while (first!=NULL){
        printf("%d %s %s %s %d %d\n", linha, first->nome,first->equipa1->nome,first->equipa2->nome,*first->score1,*first->score2 );
        first = first->next_lista;
    }
}

/* Le o nome dado, verifica se existe algum jogo com esse nome, caso exista
lista as informacoes correspondentes a esse jogo*/
void print_jogo(jogo *table_jogos, int linha){
    jogo jogo;
    char nome_jogo[MAXSTR];

    scanf(" %[^:\n]", nome_jogo);
    
    jogo=procura_jogo(table_jogos, nome_jogo);
    if(jogo==NULL){
        printf("%d Jogo inexistente.\n", linha);
    }
    else{
        printf("%d %s %s %s %d %d\n", linha, jogo->nome, jogo->equipa1->nome, jogo->equipa2->nome, *jogo->score1, *jogo->score2);
    } 
}

/* Altera o score de um jogo, atualizando portanto o numero de jogos ganhos
das equipas desse jogo, caso seja necessario */
void altera_score(jogo *table_jogos, int linha){
    char nome_jogo[MAXSTR];
    int score1=0, score2=0;
    jogo jogo;

    scanf(" %[^:]:%d:%d", nome_jogo, &score1, &score2);

    /* Verifica se o jogo existe */
    jogo = procura_jogo(table_jogos, nome_jogo);

    if(jogo==NULL){
        printf("%d Jogo inexistente.\n", linha);
        return;
    }

    /* Situacao em que inicialmente a equipa 1 tinha ganho o jogo */
    if(*jogo->score1>*jogo->score2){
        /* Caso a equipa 1 passe a perder ou empatar, perde uma vitoria */
        if(score1<=score2){
            (*jogo->equipa1->jogos_ganhos)--;
            /* Caso a equipa 2 passe a ganhar, ganha uma vitoria */
            if(score1<score2){
                (*jogo->equipa2->jogos_ganhos)++;
            }
        }
    }
    /* Situacao em que inicialmente a equipa 2 tinha ganho o jogo */
    else if(*jogo->score1<*jogo->score2){
        /* Caso a equipa 2 passe a perder ou empatar, perde uma vitoria */
        if(score1>=score2){
            (*jogo->equipa2->jogos_ganhos)--;
            /* Caso a equipa 1 passe a ganhar, ganha uma vitoria */
            if(score1>score2){
                (*jogo->equipa1->jogos_ganhos)++;
            }
        }
    }
    /* Situacao em que inicialmente havia empate */
    else{
        /* Caso a equipa 1 passe a ganhar, ganha uma vitoria */
        if(score1>score2){
            (*jogo->equipa1->jogos_ganhos)++;
        }
        /* Caso a equipa 2 passe a ganhar, ganha uma vitoria */
        else if(score1<score2){
            (*jogo->equipa2->jogos_ganhos)++;
        }
    }

    /* Atualiza os scores do jogo */
    *jogo->score1=score1;
    *jogo->score2=score2;

    return;
}

/* Le nome do jogo a remover, verifica se o jogo existe, caso exista remove-o
da lista primeiro, e de seguida remove-o da hash table */
void remove_jogo(jogo *head, jogo *tail, jogo *table_jogos, int linha){
    char nome_jogo[MAXSTR];
    jogo aux, prev, teste;
    int i;

    scanf(" %[^:\n]", nome_jogo);

    /* Verifica se o jogo com o nome dado existe */
    teste=procura_jogo(table_jogos, nome_jogo);
    if(teste==NULL){
        printf("%d Jogo inexistente.\n", linha);
        return;
    }

    /* Caso a equipa 1 ganhasse neste jogo, perde uma vitoria */
    if(*teste->score1>*teste->score2){
        (*teste->equipa1->jogos_ganhos)--;
    }
    /* Caso a equipa 2 ganhasse neste jogo, perde uma vitoria */
    else if(*teste->score1<*teste->score2){
        (*teste->equipa2->jogos_ganhos)--;
    }

    /* Percorre toda a lista de jogos ate encontrar o jogo com o nome dado */
    for(aux = *head, prev = NULL; aux != NULL; prev = aux, aux = aux->next_lista){
        if(strcmp(aux->nome, nome_jogo) == 0){
            /* Caso o jogo seja o unico na lista, tanto a head como a tail
            passam a NULL pois a lista passa a ser vazia*/
            if(aux == *head && aux == *tail){
                *head = NULL;
                *tail = NULL;
            }
            /* Caso o jogo a remover seja a head, esta e atualizada */
            else if(aux == *head){
                *head = aux->next_lista;
            }
            /* Caso o jogo a remover seja a tail, esta e atualizada */
            else if(aux == *tail){
                *tail=prev;
                (*tail)->next_lista=NULL;
            }
            /* Caso contrario, a remocao e normal */
            else{
                prev->next_lista = aux->next_lista;
            }
        }
    }
    
    /* Atraves da funcao hash, encontra-se o indice da hash table em que se
    encontra o jogo*/
    i=hash(nome_jogo, HASH_TABLE_SIZE_JOGOS);
    
    table_jogos[i]=remove_jogo_hash(table_jogos[i], nome_jogo);
}

/* Percorre a lista da hash table em que se encontra o jogo ate encontrar o jogo
com o nome dado, quando o encontra remove-o da lista e liberta a memoria alocada 
inicialmente para este */
jogo remove_jogo_hash(jogo head, char *nome_jogo){
    jogo aux, prev;

    for(aux = head, prev = NULL; aux != NULL; prev = aux, aux = aux->next){
        if(strcmp(aux->nome, nome_jogo) == 0){
            /* Caso o jogo a remover seja a head da lista, esta e atualizada */
            if(aux == head){
                head = aux->next;
            }
            else{
                prev->next = aux->next;
            }
            /* Free de todos os ponteiros associados a estrutura jogo, excepto 
            o que aponta para as equipas, pois estas continuam a existir */
            free(aux->nome);
            free(aux->score1);
            free(aux->score2);
            free(aux);
            return head;
        }
    }
    return head;
}
