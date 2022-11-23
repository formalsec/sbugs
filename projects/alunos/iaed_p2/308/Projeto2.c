#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_TABLE 1009
#define STRLEN 1023



/*---------------------------------------------------------------------------------------------------------------------------------------------*/

/* estrutura de uma equipa */
typedef struct Equipa{
    char* nome;
    int vitorias;
    struct Equipa *next;
} Equipa;


/* estrutura de hash table para as equipas */
typedef struct{
    Equipa **indice;
} hash_Equipa;






static hash_Equipa * hashtable_equipa;





/* funcao hash */
unsigned int hash(const char *nome){
    unsigned long int length = strlen(nome);
    unsigned int valor = 0;
    unsigned int i;
    
    for(i = 0; i < length; i++){
        valor = valor * 55 + nome[i];
    }
    
    valor = valor % MAX_TABLE;
    
    
    return valor;
}


void  inicia_hashtable_equipa(){
    /* aloca memoria para a tabela */
    hashtable_equipa = can_fail_malloc(sizeof(hash_Equipa));
    
    /* aloca memoria para os indices da tabela hash das equipas */
    hashtable_equipa->indice = can_fail_malloc(sizeof(Equipa) * MAX_TABLE);
    
    /* inciar todos os indices a 0 */
    int i = 0;
    for (; i < MAX_TABLE; i++){
        hashtable_equipa->indice[i] = NULL;
    }
}


void adiciona_tabela_hash_equipa(){
    
    /* dar scan ao input do user */
    char buffer[STRLEN], *nome;
    scanf(" %[^:\n]", buffer);
    nome = can_fail_malloc(sizeof(char) * strlen(buffer) + 1);
    strcpy(nome, buffer);

    
    unsigned int index = hash(nome);
    Equipa *entrada = hashtable_equipa->indice[index];
    
    
    /* cria uma equipa */
    Equipa * equipa;
    equipa = can_fail_malloc(sizeof(Equipa));
    equipa->nome = nome;
    equipa->vitorias = 0;
    equipa->next = NULL;
    

    /* se o indice da equipa estiver vazio insere a nova equipa */
    if (entrada == NULL) {
        
        /* insere a equipa no indice */
        hashtable_equipa->indice[index] = equipa;

        return;
    }
    
    
    Equipa *Anterior;
    Anterior = can_fail_malloc(sizeof(Equipa));
    
    /* caso o indice ja esteja ocupado vamos usar o ponteiro next para evitar colisoes */
    /* usando um ciclo white vamos inserir no proximo ponteiro vazio                   */
    while (entrada != NULL) {
        /* se o nome ja estiver na lista entao retorna erro */
        if (strcmp(entrada->nome, nome) == 0) {
            printf("_Equipa existente.\n");
            free(equipa);
            free(Anterior);
            return;
        }
        /* avanca para o proximo ate encotrar um espaco vazio */
        Anterior = entrada;
        entrada = Anterior->next;
    }
    
    /* encontra espaco vazio insere a equipa nesse indice */
    Anterior->next = equipa;
}


void procura_equipa(){
    
    
    /* dar scan ao input do user */
    char buffer[STRLEN], *nome;
    scanf(" %[^:\n]", buffer);
    nome = can_fail_malloc(sizeof(char) * strlen(buffer) + 1);
    strcpy(nome, buffer);
    
    
    unsigned int index = hash(nome);
    Equipa *entrada = hashtable_equipa->indice[index];
    
    
    /* primeiro verificar se o nome da equipa pertence a lista*/
    if (entrada== NULL) {
        printf("_ Equipa inexistente.\n");
        return;
    }
    /* percorrer a lista ate encontrar a equipa */
    while (entrada != NULL) {
        if (strcmp(entrada->nome, nome) == 0) {
            printf("_ %s %d.\n", entrada->nome, entrada->vitorias);
            return;
        }
        /* avanca para o proximo ponteiro */
        entrada = entrada->next;
    }
    /* se nao encontrar uma equipa com esse nome entao nao existe */
    printf("_ Equipa inexistente.\n");
}




/*---------------------------------------------------------------------------------------------------------------------------------------------*/



/* estrutura de um jogo */
typedef struct Jogo{
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int socre2;
    struct Jogo *next;
} Jogo;

/* estrutura de uma hash table para jogos */
typedef struct{
    Jogo **indice;
} hash_Jogo;





hash_Jogo * hashtable_jogo;



void  inicia_hashtable_jogo(){
    /* aloca memoria para a tabela */
    hashtable_jogo = can_fail_malloc(sizeof(hash_Jogo));
    
    /* aloca memoria para os indices da tabela hash das equipas */
    hashtable_jogo->indice = can_fail_malloc(sizeof(Jogo) * MAX_TABLE);
    
    /* inciar todos os indices a 0 */
    int i = 0;
    
    for(; i < MAX_TABLE; i++){
        hashtable_jogo->indice[i] = NULL;
    }
}


bool verifica_equipa(char *nome){
    unsigned int index = hash(nome);
    
    while (hashtable_equipa->indice[index] != NULL) {
            if (strcmp(hashtable_equipa->indice[index]->nome, nome) == 0){
                return true;
        }
        hashtable_equipa->indice[index] = hashtable_equipa->indice[index]->next;
    }
    return false;
}


void adiciona_hash_tabela_jogo(){
    
    
    /* dar scan ao input */
    char buffer_nome[STRLEN], buffer_equipa1[STRLEN], buffer_equipa2[STRLEN];
    char *nome, *equipa1, *equipa2;
    int score1, score2;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", buffer_nome, buffer_equipa1, buffer_equipa2, &score1, &score2);
    nome = can_fail_malloc(sizeof(char) * strlen(buffer_nome) + 1);
    equipa1 = can_fail_malloc(sizeof(char) * strlen(buffer_equipa1) + 1);
    equipa2 = can_fail_malloc(sizeof(char) * strlen(buffer_equipa2) + 1);
    strcpy(nome, buffer_nome);
    strcpy(equipa1, buffer_equipa1);
    strcpy(equipa2, buffer_equipa2);
    
    
    int index = hash(nome);
    Jogo *entrada = hashtable_jogo->indice[index];
    int index_equipa1 = hash(equipa1);
    int index_equipa2 = hash(equipa2);

    
    /* primeiro verificar se as equipas existem */
    if (verifica_equipa(equipa1) == 0 || verifica_equipa(equipa2) == 0) {
        printf("_ Equipa inexistente.\n");
        return;
    }
    
    
    /* cria jogo */
    Jogo * jogo;
    jogo = can_fail_malloc(sizeof(Jogo));
    jogo->nome = nome;
    jogo->equipa1 = equipa1;
    jogo->equipa2 = equipa2;
    jogo->score1 = score1;
    jogo->socre2 = score2;
    jogo->next = NULL;
    
    
    /* se o indice estiver vazio introduzir logo o jogo */
    if (entrada == NULL) {
        hashtable_jogo->indice[index] = jogo;
        
        /* por ultimo verificar qual das equipas ganhou o jogo e marcar a vitoria */
        if (score1 > score2){
            hashtable_equipa->indice[index_equipa1]->vitorias += 1;
            return;
        }
        else if (score2 > score1){
            hashtable_equipa->indice[index_equipa2]->vitorias += 1;
            return;
        }
    }
    
    
    Jogo *Anterior;
    Anterior = can_fail_malloc(sizeof(Jogo));
    
    /* caso o indice ja esteja ocupado vamos move-lo para o ponteiro seguinte */
        while (entrada != NULL) {
            /* se o nome ja estiver na lista entao retorna erro */
            if (strcmp(entrada->nome, nome) == 0) {
                printf("_ Jogo existente.\n");
                free(jogo);
                free(Anterior);
                return;
            }
            /* avanca para o proximo ate encotrar um espaco vazio */
            Anterior = entrada;
            entrada = Anterior->next;
        }
    
    /* encontra espaco vazio insere a equipa nesse indice */
    Anterior->next = jogo;
    
    
    /* por ultimo verificar qual das equipas ganhou o jogo e marcar a vitoria */
    if (score1 > score2){
        hashtable_equipa->indice[index_equipa1]->vitorias += 1;
    }
    else if (score2 > score1){
        hashtable_equipa->indice[index_equipa2]->vitorias += 1;
    }
}

void procura_jogo(){
    
    /* dar scan ao input */
    char buffer[STRLEN];
    char *nome;
    scanf(" %[^:\n]", buffer);
    nome = can_fail_malloc(sizeof(char) * strlen(buffer) + 1);
    strcpy(nome, buffer);
    
    
    unsigned int index = hash(nome);
    Jogo *entrada = hashtable_jogo->indice[index];
    
    
    /* primeiro verificar se o jogo existe */
    if (entrada ==  NULL) {
        printf("_ Jogo inexistente.\n");
        return;
    }
    
    /* caso o indice nao esteja vazio vamos procurar os valores */
    while (entrada != NULL) {
        if (strcmp(entrada->nome, nome) == 0){
            printf("_ %s %s %s %d %d.\n", entrada->nome, entrada->equipa1, entrada->equipa2, entrada->score1, entrada->socre2);
            return;
        }
        /* move para o proximo ponteiro se o nome nao corresponder */
        entrada = entrada->next;
    }
    /* se nao encontrar o nome na pilha de ponteiros devolde erro*/
    printf("_Jogo inexistente.\n");
}


void apaga_jogo(){
    
    /* dar scan ao input do user */
    char buffer[STRLEN];
    char *nome;
    scanf(" %[^:\n]", buffer);
    nome = can_fail_malloc(sizeof(char) * strlen(buffer) + 1);
    strcpy(nome, buffer);
    
    
    unsigned int index = hash(nome);
    Jogo *entrada = hashtable_jogo->indice[index];
    
    
    /* se o indice estiver vazio devolvemos erro */
    if (entrada == NULL) {
        printf("_ Jogo inexistente.\n");
        return;
    }
    
    unsigned int index_equipa1 = hash(entrada->equipa1);
    unsigned int index_equipa2 = hash(entrada->equipa2);

    
    /* caso o indice esteja vazio procuramos o indice para apagar */
    while (entrada != NULL) {
        /* se o nome corresponder */
        if (strcmp(entrada->nome, nome) == 0) {

            
            /* antes de anular o indice temos de anular a vitoria da equipa que venceu */
            if (entrada->score1 > entrada->socre2)
                hashtable_equipa->indice[index_equipa1]->vitorias -= 1;
            
            else if (entrada->socre2 > entrada->score1)
                hashtable_equipa->indice[index_equipa2]->vitorias -= 1;
            
            
            /* anula o indice */
            hashtable_jogo->indice[index] = NULL;
            return;
        }
        /* avanca para o proximo ponteiro */
        entrada = entrada->next;
    }
    /* se percorrer a lista toda e nao encontrar o jogo devolve erro */
    printf("_ Jogo inexistente.\n");
}

void altera_score(){
    
    /* dar scan ao input do user */
    char buffer[STRLEN];
    char *nome;
    int score1, score2;
    scanf(" %[^:\n]:%d:%d", buffer, &score1, &score2);
    nome = can_fail_malloc(sizeof(char) * strlen(buffer) + 1);
    strcpy(nome, buffer);
    

    printf("%s %d %d", nome, score1, score2);
    
    unsigned int index = hash(nome);
    Jogo *entrada = hashtable_jogo->indice[index];
    
    
    /* se o indice estiver vazio retorna erro */
    if (entrada == NULL) {
        printf("_ Jogo inexistente.\n");
        return;
    }
    
    unsigned int index_equipa1 = hash(hashtable_jogo->indice[index]->equipa1);
    unsigned int index_equipa2 = hash(hashtable_jogo->indice[index]->equipa2);
    
    /* percorrer o ponteiro para encontrar o nome do jogo */
    while (entrada != NULL) {
        /* o nome e o mesmo */
        if (strcmp(entrada->nome, nome) == 0) {
            
            /* primeiro vamos verificar os scores anteriores e subtrair uma vitoria */
            /* o score1 anterior e maior que o score2 anterior*/
            if (hashtable_jogo->indice[index]->score1 > hashtable_jogo->indice[index]->socre2)
                hashtable_equipa->indice[index_equipa1] -= 1;
            
            /* o score2 anterior e maior que o score1 anterior e subtrair uma vitoria */
            else if (hashtable_jogo->indice[index]->socre2 > hashtable_jogo->indice[index]->score1)
                hashtable_equipa->indice[index_equipa2] -= 1;
            
            /* agora acrescentar a vitoria tendo em conta os novos scores */
            if (score1 > score2)
                hashtable_equipa->indice[index_equipa1] += 1;
            
            else if (score2 > score1)
                hashtable_equipa->indice[index_equipa2] += 1;
            
            /* por ultimo alterar os valores guardados na lista de jogos */
            hashtable_jogo->indice[index]->score1 = score1;
            hashtable_jogo->indice[index]->socre2 = score2;
            
            return;
        }
        /* avanca para o proximo ponteiro */
        entrada = entrada->next;
    }
    /* se nao encontrar o nome do jogo na lista retorna erro */
    printf("_ Jogo inexistente.\n");
}



/*---------------------------------------------------------------------------------------------------------------------------------------------*/


int main(){
    char comando;
    
    
    
    inicia_hashtable_equipa();
    inicia_hashtable_jogo();
    
    
    
     while ((comando = getchar()) != 'x') {
         
         
         switch (comando)
         {
             case 'A':
                 adiciona_tabela_hash_equipa();
                 break;
                 
             case 'a':
                 adiciona_hash_tabela_jogo();
                 break;
                 
             case 'P':
                 procura_equipa();
                 break;
                 
             case 'p':
                 procura_jogo();
                 break;
                 
             case 'r':
                 apaga_jogo();
                 break;
                 
             case 's':
                 altera_score();
                 break;
             case 'l':
                 
                 break;
                 
             default:
                 break;
         }
     }
     
    return 0;
}
