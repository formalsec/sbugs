#include "estruturas.h"

/* atribui uma posicao na hash atraves do nome da equipa ou do jogo */
unsigned int hash(char *nome){
    int i;
    int length = strlen(nome);
    unsigned int hash_pos = 0;
    for (i = 0; i < length; i++){
        hash_pos += nome[i];                             /* soma todos os caracteres ASCI do nome */
        hash_pos = (hash_pos * nome[0]) % Tamanho_hash;  /* multiplica pela primeira letra e restringe o resultado ao tamanho da hash table */
    }
    return hash_pos;
}

/* inicializa todas as posicoes da hash table a NULL */
bloco_hash_equipa *inicializa_hash_e(){
    int i;
    bloco_hash_equipa *hash_table_e = malloc(sizeof(bloco_hash_equipa)*Tamanho_hash);
    for(i = 0;i < Tamanho_hash; i++){
        hash_table_e[i] = NULL;
    }
    return hash_table_e;
}


/* guarda uma equipa e na hash table das equipas seguindo a logistica do encadeamento externo*/
void guarda_equipa_hash(bloco_hash_equipa *table_e,equipa *e){
    int pos = hash(e->nome);                                            /* devolve a posicao onde sera guardada a equipa*/
    bloco_hash_equipa equipa1 = malloc(sizeof(struct bloco_h_equipa));  /* guarda memoria para o bloco que vai guardar na hash table */
    equipa1->next = table_e[pos];                                       /* insere o bloco pela head da lista ligada */
    table_e[pos] = equipa1;                                             
    equipa1->equipa = e;                                                /* guarda a equipa no bloco */        
                                                                    
}

/* procura uma equipa na lista ligada correspondente a posicao do return da funcao hash para o nome da equipa */
equipa *procura_equipa_hash(bloco_hash_equipa *table_e,char *nome){
    int pos = hash(nome);
    bloco_hash_equipa aux;
    aux = table_e[pos];
    while (aux != NULL && strcmp(aux->equipa->nome,nome) != 0){
        aux = aux->next;
    }
    if (aux == NULL){
        return NULL;
    }
    return aux->equipa;
}


/* inicializa todas as posicoes da hash table a NULL */
bloco_hash_jogo *inicializa_hash_j(){
    int i;
    bloco_hash_jogo *hash_table_j = malloc(sizeof(bloco_hash_jogo)*Tamanho_hash);
    for(i = 0;i < Tamanho_hash; i++){
        hash_table_j[i] = NULL;
    }
    return hash_table_j;
}

/* guarda uma equipa e na hash table das equipas seguindo a mesma logistica da hash table das equipas*/
void guarda_jogo_hash(bloco_hash_jogo *table_j,jogo *j){
    int pos = hash(j->nome);
    bloco_hash_jogo jogo1 = malloc(sizeof(struct bloco_h_jogo));
    jogo1->next = table_j[pos];
    table_j[pos] = jogo1;
    jogo1->jogo = j;
}

/* procura uma equipa na lista ligada correspondente a posicao do return da funcao hash para o nome do jogo */
jogo *procura_jogo_hash(bloco_hash_jogo *table_j,char *nome){
    int pos = hash(nome);
    bloco_hash_jogo aux;
    aux = table_j[pos];
    while ( aux != NULL && strcmp(aux->jogo->nome,nome) != 0){
        aux = aux->next;
    }
    if ( aux == NULL){
        return NULL;
    }
    return aux->jogo;
}

/* remove um jogo da hash table*/
void apaga_jogo_hash(bloco_hash_jogo *table_j, char *nome){
    bloco_hash_jogo aux;                                   /* variavel usada para percorrer a lista ligada */
    bloco_hash_jogo aux2 = NULL;                           /* variavel que corresponde ao elemento anterior ao aux para ser possivel reconectar a lista ligada */
    int pos = hash(nome);
    aux = table_j[pos];
    while (aux != NULL && strcmp(aux->jogo->nome,nome) != 0){       /* encontra o jogo */
        aux2 = aux;
        aux = aux->next;
    }
    if (aux == NULL) return; /* lista estava vazia*/
    if (aux2 == NULL){       /*o jogo que queremos apagar esta na head */
        table_j[pos] = aux->next;    
    }
    else{
        aux2->next = aux->next;     /* retira o jogo da sequencia da lista ligada */
    }
    free(aux->jogo->nome);free(aux->jogo);free(aux);  /* liberta a memoria ocupada pelo nome do jogo pelo jogo e pelo bloco da hash */
}