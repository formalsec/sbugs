#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hashtableequipas.h"
#include "hashtablejogo.h"
#include "listae.h"
#include "listaj.h"
#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 1023
#define CAP 1483
#define LEN 2

/*adiciona_jogo: Adiciona um novo jogo*/
void adiciona_jogo(int NL, listj* listajogo, linkj* headsj, linke* headse) {
    jogo* j;
    char buffer1[MAX_STR + 1];
    char buffer2[MAX_STR + 1];
    char buffer3[MAX_STR + 1];
    int sc1;
    int sc2;

    scanf(" %[^:]:%[^:]:%[^:]:%d:%d", buffer1, buffer2, buffer3, &sc1, &sc2);
    getchar();


    if (STprocuraj(buffer1, CAP, headsj) != NULL) { /*verifica se ja existe um jogo com esse nome*/
        printf("%d Jogo existente.\n", NL);
    }
    else if (STprocurae(buffer2, CAP, headse) == NULL || STprocurae(buffer3, CAP, headse) == NULL) { /*procura se existem equipas com os nomes dados*/
        printf("%d Equipa inexistente.\n", NL);
    }
    else {
        j = can_fail_malloc(sizeof(jogo)); /*crio um novo jogo*/
        j->nome = can_fail_malloc(sizeof(char) * (strlen(buffer1) + 1));
        strcpy(j->nome, buffer1);
        j->equipa1 = STprocurae(buffer2, CAP, headse);
        j->equipa2 = STprocurae(buffer3, CAP, headse);
        j->score1 = sc1;
        j->score2 = sc2;
        STinserej(j, CAP, headsj); /*adiciono o jogo  na hashtable*/

        adiciona_j(listajogo, j); /*adiciona o jogo na listajogo*/
        if (j->score1 > j->score2) { /*verifico qual equipa ganhou o jogo*/
            j->equipa1->jogosg++;
        }
        if (j->score2 > j->score1) {
            j->equipa2->jogosg++;
        }
    }
}

/*adiciona_equipa: Adiciona uma nova equipa*/
void adiciona_equipa(int NL, liste* listaequipas, linke* headse) {
    equipa* eq;
    char buffer[MAX_STR + 1];
    scanf(" %[^\n]", buffer);
    getchar();

    if (STprocurae(buffer, CAP, headse) != NULL) { /*verifico se essa aquipa ja existe*/
        printf("%d Equipa existente.\n", NL);
    }
    else {
        eq = can_fail_malloc(sizeof(equipa));/*crio uma nova equipa*/
        eq->nomeeq = can_fail_malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(eq->nomeeq, buffer);
        eq->jogosg = 0;
        adiciona_e(listaequipas, eq); /*adiciono equipa na listaequipas*/
        STinsertee(eq, CAP, headse); /*insere a equipa na hashtable*/
    }
}

/*procura_jogo: Procura um jogo com o nome dado*/
void procura_jogo(int NL, linkj* headsj) {
    char nome[MAX_STR + 1];
    scanf(" %[^\n]", nome);
    getchar();

    if (STprocuraj(nome, CAP, headsj) == NULL) {  /*verifica se ja existe um jogo com esse nome*/
        printf("%d Jogo inexistente.\n", NL);
    }
    else {
        jogo* jg = STprocuraj(nome, CAP, headsj); /*procuro esse jogo na hashtable*/
        printf("%d %s %s %s %d %d\n", NL, jg->nome, jg->equipa1->nomeeq, jg->equipa2->nomeeq, jg->score1, jg->score2);
    }
}

/*procura_equipa: Procura uma equipa dado um nome*/
void procura_equipa(int NL, linke* headse) {
    equipa* eq;
    char nequipa[MAX_STR + 1];
    scanf(" %[^\n]", nequipa);
    getchar();


    if (STprocurae(nequipa, CAP, headse) == NULL) { /*verifico se a equipa existe*/
        printf("%d Equipa inexistente.\n", NL);
    }
    else {
        eq = STprocurae(nequipa, CAP, headse); /*procuro equipa na hashtable*/
        printf("%d %s %d\n", NL, eq->nomeeq, eq->jogosg);
    }
}

/*altera_pontuacao: Altera o score de um jogo dado o nome*/
void altera_pontuacao(int NL, linkj* headsj) {
    jogo* jg;
    int score1;
    int score2;
    char nome[MAX_STR + 1];
    scanf(" %[^:]:%d:%d", nome, &score1, &score2);
    getchar();

    if (STprocuraj(nome, CAP, headsj) == NULL) { /*procura se existe esse jogo*/
        printf("%d Jogo inexistente.\n", NL);
    }

    else {
        jg = STprocuraj(nome, CAP, headsj); /*procura esse jogo na hashtable*/

        if (jg->score1 > jg->score2) { /*retiro jogos ganhos relativos ao score anterior*/
            jg->equipa1->jogosg--;
        }
        if (jg->score2 > jg->score1) {
            jg->equipa2->jogosg--;
        }

        jg->score1 = score1; /*atualizo os scores*/
        jg->score2 = score2;

        if (jg->score1 > jg->score2) { /*atualizo os jogos ganhos relativos ao score dado*/
            jg->equipa1->jogosg++;
        }
        if (jg->score2 > jg->score1) {
            jg->equipa2->jogosg++;
        }
    }
}

/*remove_jogo: Apaga um jogo dado um nome*/
void remove_jogo(int NL, listj* listajogo, linkj* headsj) {
    jogo* jg;
    nodej* aux;
    char nome[MAX_STR + 1];
    scanf(" %[^\n]", nome);
    getchar();

    if (STprocuraj(nome, CAP, headsj) == NULL) { /*verifico se esse jogo existe*/
        printf("%d Jogo inexistente.\n", NL);
    }
    else {
        aux = listajogo->head;
        while(aux){ /*encontro o nodej da listajogo com esse jogo para o eliminar*/
            if(strcmp(aux->j->nome, nome) == 0){
                apaga_nodej(listajogo, aux);
                break;
            }
            aux = aux->next;
        }
        jg = STprocuraj(nome, CAP, headsj); /*procuro o jogo na hashtable*/
        
        if (jg->score1 > jg->score2) { /*retiro jogos ganhos relativos ao jogo a ser eliminado*/
            jg->equipa1->jogosg--;
        }
        if (jg->score2 > jg->score1) {
            jg->equipa2->jogosg--;
        }
        
        STapagaj(jg, CAP, headsj); /*apago o jogo da hashtable*/
    }
}

/*listajogos: Lista todos os jogos introduzidos*/
void listajogos(int NL, listj* listajogo){
    nodej* tmp;
    getchar();
    tmp = listajogo->head;
    while (tmp){ /*ando por todos os jogo que existem na listajogo*/
        printf("%d %s %s %s %d %d\n", NL, tmp->j->nome, tmp->j->equipa1->nomeeq, tmp->j->equipa2->nomeeq, tmp->j->score1, tmp->j->score2);
        tmp = tmp->next;
    }
}

/*equipasvencedoras: Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica (do nome da equipa)*/
void equipasvencedoras(int NL, liste* listaequipas){
    nodee* aux;
    int tam = LEN;
    int i = 0;
    int l;
    char** vitoriosos = can_fail_malloc(sizeof(char*)* LEN); /*crio uma lista que vai ter o nome das equipas com mais jogos ganhos*/
    int max = 0;
    getchar();
    aux = listaequipas->head;
    if(aux == NULL){ /*se a listaequipas estiver vazia nao retorno nada*/
        free(vitoriosos);
        return;
    }
    while(aux){ /*encontrar equipas com numero maximo de vitorias*/
        if(aux->e->jogosg == max){  /*caso a equipa tenha tantos jogos ganhos quanto o maximo ate ao momento*/
            if(i >= tam){ /*se a lista dos vitoriosos ja estiver cheia aumento o seu tamanho*/
                tam = 2*tam;
                vitoriosos = can_fail_realloc(vitoriosos, sizeof(char*)* tam);
            }
            vitoriosos[i] = aux->e->nomeeq;
            i++;
        }
        else if(aux->e->jogosg > max){ /*se uma equipa tiver um maior numero de jogos ganhos do que o valor de max*/
            max = aux->e->jogosg;
            vitoriosos[0] = aux->e->nomeeq;
            i = 1;
        }
        aux = aux->next;
    }
    
    /*ordem lexicografica*/
    quicksort(vitoriosos, 0, i-1);
    
    printf("%d Melhores %d\n", NL, max);
    for(l = 0; l < i; l++){ /*retorno todos os nomes das equipas com o numero maximo de jogos ganhos*/
        printf("%d * %s\n", NL, vitoriosos[l]);
    }
    
    free(vitoriosos);
}

int main() {
    int NL = 0;
    listj* listajogo = mk_listj();
    liste* listaequipas = mk_liste();
    linkj* headsj = STiniciaj(CAP);
    linke* headse = STiniciae(CAP);
    char tecla;
    while ((tecla = getchar()) != 'x' && tecla != EOF) {    /*verifica se a tecla obtida e um 'x' ou se chegou ao fim do ficheiro*/
        NL++;
        switch (tecla) {
            case ('a'):
                adiciona_jogo(NL, listajogo, headsj, headse); /*adiciona_jogo: Adiciona um novo jogo*/
                break;
            case ('A'):
                adiciona_equipa(NL, listaequipas, headse); /*adiciona_equipa: Adiciona uma nova equipa*/
                break;
            case ('l'):
                listajogos(NL, listajogo); /*listajogos: Lista todos os jogos introduzidos*/
                break;
            case ('p'):
                procura_jogo(NL, headsj);  /*procura_jogo: Procura um jogo com o nome dado*/
                break;
            case  ('P'):
                procura_equipa(NL, headse); /*procura_equipa: Procura uma equipa dado um nome*/
                break;
            case ('r'):
                remove_jogo(NL, listajogo, headsj); /*remove_jogo: Apaga um jogo dado um nome*/
                break;
            case ('s'):
                altera_pontuacao(NL, headsj); /*altera_pontuacao: Altera o score de um jogo dado o nome*/
                break;
            case('g'):
                equipasvencedoras(NL, listaequipas); /*equipasvencedoras: Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica (do nome da equipa)*/
                break;
            }
    }
    
    /*liberto toda a memoria alocada nas varias listas e hashtables usadas*/
    free_listj(listajogo);
    free_liste(listaequipas);
    STfree_hte(CAP, headse);
    STfree_htj(CAP, headsj);
	return 0;
}