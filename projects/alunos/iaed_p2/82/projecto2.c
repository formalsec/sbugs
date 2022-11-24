#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define MAXCSTRING 1023
#define MAXJOGOS 1000
#define MAXEQUIPAS 1000

/* definir o tipo jogo */

typedef struct jogo{
    char nome[MAXCSTRING];
    char equipa1[MAXCSTRING];
    char equipa2[MAXCSTRING];
    int score1;
    int score2;
}Jogo;

/* declarar a lista de jogos e a lista de equipas */

Jogo jogos[MAXJOGOS];
char equipas[MAXEQUIPAS][MAXCSTRING];
int NL = 0;

/* declarar todas as funcoes */

void nova_equipa();
void novo_jogo();
int existe_equipa(char equipa[MAXCSTRING]);
int existe_jogo(char nome[MAXCSTRING]);
void lista_jogos();
void apaga_jogo();
void altera_score();
void procura_jogo();
void procura_equipa();
int n_jogos_ganhos(char equipa[MAXCSTRING]);
void lista_melhores();

/* switch para os diferentes comandos ate o comando ser == 'x', em que o programa termina */
int main(){

    int i;
    char comando;
    Jogo jogo_vazio = {"?","?","?",-1,-1};

    for (i=0; i<MAXEQUIPAS; i++){    /* inicializar a lista de equipas com equipas vazias */
        strcpy(equipas[i], "?");
    }

    for (i=0; i<MAXJOGOS; i++){     /* inicializar a lista de jogos com jogos vazios*/
        jogos[i] = jogo_vazio;
    }

    do{
        switch (comando = getchar()){

            case 'A':
                NL++;
                nova_equipa();
                break;

            case 'a':
                NL++;
                novo_jogo();
                break;

            case 'l':
                NL++;
                lista_jogos();
                break;
            
            case 'r':
                NL++;
                apaga_jogo();
                break;

            case 's':
                NL++;
                altera_score();
                break;

            case 'p':
                NL++;
                procura_jogo();
                break;
            
            case 'P':
                NL++;
                procura_equipa();
                break;
            
            case 'g':
                NL++;
                lista_melhores();
                break;

            case 'e':
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                for (i=0; i<5; i++)
                    printf("%s\n",equipas[i]);
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                break;

            case 'j':
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                for (i=0; i<5; i++)
                    printf("%s %s %s %d %d\n", jogos[i].nome, jogos[i].equipa1, jogos[i].equipa2, jogos[i].score1, jogos[i].score2);
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                break;

        }
    } while (comando != 'x');

    return 0;
}

/* adiciona uma nova equipa a lista de equipas */
void nova_equipa(){

    int i;
    char nova_equipa[MAXCSTRING];

    scanf(" %[^:\n]", nova_equipa);

    if (existe_equipa(nova_equipa) == 1){
        printf("%d Equipa existente.\n", NL);
        return;
    }

    else{
        for (i=0; i<MAXEQUIPAS; i++){
            if (strcmp(equipas[i], "?") == 0){
                strcpy(equipas[i], nova_equipa);
                return;
            }
        }
    }
}

/* adiciona um novo jogo a lista de jogos */
void novo_jogo(){

    int i;
    Jogo novo_jogo;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", novo_jogo.nome, novo_jogo.equipa1, novo_jogo.equipa2, &novo_jogo.score1, &novo_jogo.score2);

    if (existe_jogo(novo_jogo.nome) == 1){
        printf("%d Jogo existente.\n", NL);
        return;
    }

    if (existe_equipa(novo_jogo.equipa1) == 0 || existe_equipa(novo_jogo.equipa2) == 0){
        printf("%d Equipa inexistente.\n", NL);
        return;
    }

    for (i=0; i<MAXJOGOS; i++){
        if (strcmp(jogos[i].nome, "?") == 0){
            jogos[i] = novo_jogo;
            return;
        }
    }
}

/* retorna 1 se a equipa existe, retorna 0 se a equipa nao existe */
int existe_equipa(char equipa[MAXCSTRING]){

    int i;

    for (i=0; strcmp(equipas[i], "?") != 0; i++){
        if (strcmp(equipas[i], equipa) == 0){
            return 1;
        }
    }

    return 0;
}

/* retorna 1 se o jogo existe, retorna 0 se o jogo nao existe */
int existe_jogo(char nome[MAXCSTRING]){

    int i;

    for (i=0; strcmp(jogos[i].nome, "?") != 0; i++){
        if (strcmp(jogos[i].nome, nome) == 0){
            return 1;
        }
    }

    return 0;
}

/* lista todos os jogos introduzidos */
void lista_jogos(){
    
    int i;

    for (i=0; strcmp(jogos[i].nome, "?") != 0; i++){
        printf("%d %s %s %s %d %d\n", NL, jogos[i].nome, jogos[i].equipa1, jogos[i].equipa2, jogos[i].score1, jogos[i].score2);
    }
}

/* apaga um jogo da lista de jogos dado o seu nome */
void apaga_jogo(){

    int i, e;
    char nome[MAXCSTRING];

    scanf(" %[^:\n]", nome);

    if (existe_jogo(nome) == 0){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    else{
        for (i=0; strcmp(jogos[i].nome, "?") != 0; i++){
            if (strcmp(jogos[i].nome, nome) == 0){
                for (e=i; strcmp(jogos[e].nome, "?") != 0; e++){
                    jogos[e] = jogos[e+1];
                }
                return;
            }
        }
    }
}
 /* altera o score de um jogo dado o seu nome */
void altera_score(){

    int i, score1_novo, score2_novo;
    char nome[MAXCSTRING];

    scanf(" %[^:\n]:%d:%d", nome, &score1_novo, &score2_novo);

    if (existe_jogo(nome) == 0){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    else{
        for (i=0; strcmp(jogos[i].nome, "?") != 0; i++){
            if (strcmp(jogos[i].nome, nome) == 0){
                jogos[i].score1 = score1_novo;
                jogos[i].score2 = score2_novo;
                return;
            }
        }
    }
}

/* procura um jogo dado o seu nome */
void procura_jogo(){

    int i;
    char nome[MAXCSTRING];

    scanf(" %[^:\n]", nome);

    if (existe_jogo(nome) == 0){
        printf("%d Jogo inexistente.\n", NL);
    }

    else{
        for (i=0; strcmp(jogos[i].nome, "?") != 0; i++){
            if (strcmp(jogos[i].nome, nome) == 0){
                printf("%d %s %s %s %d %d\n", NL, jogos[i].nome, jogos[i].equipa1, jogos[i].equipa2, jogos[i].score1, jogos[i].score2);
                return;
            }
        }
    }
}

/* procura uma equipa dado o seu nome */
void procura_equipa(){

    int i, jogos_ganhos = 0;
    char nome_equipa[MAXCSTRING];

    scanf(" %[^:\n]", nome_equipa);

    if (existe_equipa(nome_equipa) == 0){
        printf("%d Equipa inexistente.\n", NL);
    }

    else{
        for (i=0; strcmp(jogos[i].nome, "?") != 0; i++){
            if (strcmp(jogos[i].equipa1, nome_equipa) == 0 && jogos[i].score1 > jogos[i].score2){
                jogos_ganhos++;
            }
            if (strcmp(jogos[i].equipa2, nome_equipa) == 0 && jogos[i].score2 > jogos[i].score1){
                jogos_ganhos++;
            }
        }

        printf("%d %s %d\n", NL, nome_equipa, jogos_ganhos);
    }
}

/* retorna o numero de jogos ganhos por um equipa */
int n_jogos_ganhos(char equipa[MAXCSTRING]){

    int i, jogos_ganhos = 0;

    for (i=0; strcmp(jogos[i].nome, "?") != 0; i++){
        if (strcmp(jogos[i].equipa1, equipa) == 0 && jogos[i].score1 > jogos[i].score2){
            jogos_ganhos++;
        }
        if (strcmp(jogos[i].equipa2, equipa) == 0 && jogos[i].score2 > jogos[i].score1){
            jogos_ganhos++;
        }
    }

    return jogos_ganhos;
}

/* Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica (do nome da equipa) */
void lista_melhores(){

    int i, e = 0, n = 0, contador = 0;
    char melhores[MAXEQUIPAS][MAXCSTRING], temp[MAXCSTRING];

    if (strcmp(equipas[0], "?") != 0){

        for (i=0; i<MAXEQUIPAS; i++){
            strcpy(melhores[i], "?");
        }

        for (i=0; strcmp(equipas[i], "?") != 0; i++){
            if (n_jogos_ganhos(equipas[i]) > n){
                n = n_jogos_ganhos(equipas[i]);
            }
        }

        for (i=0; strcmp(equipas[i], "?") != 0; i++){
            if (n_jogos_ganhos(equipas[i]) == n){
                strcpy(melhores[e], equipas[i]);
                e++;
            }
        }

        for (i=0; strcmp(melhores[i], "?") != 0; i++){
            contador++;
        }

        for (i=0; i<contador; i++){
            for (e=i+1; e<contador; e++){
                if (strcmp(melhores[i],melhores[e]) > 0){
                    strcpy(temp, melhores[i]);
                    strcpy(melhores[i], melhores[e]);
                    strcpy(melhores[e], temp);
                }
            }
        }

        printf("%d Melhores %d\n", NL, n);
        for (i=0; strcmp(melhores[i], "?") != 0; i++){
            printf("%d * %s\n", NL, melhores[i]);
        }
    }
}