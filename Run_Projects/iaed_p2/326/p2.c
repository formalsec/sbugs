#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h" /* inclui o ficheiro com as estruturas usadas no projeto */
#define HASH_SIZE 1000 /* tamanho da hash table, tambem usado como fator para a funcao hash */
#define MAX_STRLEN 1024 /* numero maximo de carateres para o nome de uma equipa/jogo */

int hash(char *v, int M) { /* funcao que faz hash de uma string, neste caso usa se o nome da equipa/jogo */
    int h = 0, a = 127;

    for(; *v != '\0'; v++)
        h = (a*h + *v) % M;
    return h;
}


void initTeamList(team_list * lista_equipas) { /* inicializa a lista das equipas */

    lista_equipas->head = NULL;
    lista_equipas->last = NULL;

}


void initTeamHash(team_list **teamHash) { /* inicializa a hash table das equipas */
    int i;

    for(i = 0; i < HASH_SIZE; i++) {
        teamHash[i] = malloc(sizeof(team_list));
        initTeamList(teamHash[i]);
    }
}


void initMatchHash(match_list **matchHash) { /* inicializa a hash table dos jogos */
    int i;

    for(i = 0; i < HASH_SIZE; i++) {
        matchHash[i] = malloc(sizeof(match_list));
        matchHash[i]->head = NULL;
        matchHash[i]->last = NULL;
    }
}


matches * make_match_list() { /* inicializa a lista dos jogos */
    matches * matchList = malloc(sizeof(matches));

    matchList->head = NULL;
    matchList->last = NULL;

    return matchList;
}


void destroy_team_list(team_list * lista_equipas) { /* funcao que destroi a lista ligada dos jogos */
    team * aux;

    while(lista_equipas->head) {
        aux = lista_equipas->head->next;
        free(lista_equipas->head->team_name);
        free(lista_equipas->head);
        lista_equipas->head = aux;
    }

    free(lista_equipas);
}


void destroy_match_list(match_list * lista_jogos) { /* funcao que destroi uma lista de jogos, usada para as listas da hash table dos jogos */
    match * aux;

    while(lista_jogos->head) {
        aux = lista_jogos->head->next;
        free(lista_jogos->head->match_name);
        free(lista_jogos->head->team1_name);
        free(lista_jogos->head->team2_name);
        free(lista_jogos->head);
        lista_jogos->head = aux;
    }

    free(lista_jogos);
}


void destroy_match_list2(matches * lista_jogos) { /* funcao que destroi a lista ligada dos jogos */
    m_name * aux;

    while(lista_jogos->head) {
        aux = lista_jogos->head->next;
        free(lista_jogos->head->match_name);
        free(lista_jogos->head);
        lista_jogos->head = aux;
    }

    free(lista_jogos);
}


int team_exists(team_list **teamHash, char *name) { /* verifica se ja existe alguma equipa na hashtable com o nome da equipa a ser adicionada */
    int ind = hash(name, HASH_SIZE);

    team * head = teamHash[ind]->head;

    if(head) {
        if(strcmp(head->team_name, name) == 0)
            return 1;
        for(; head->next != NULL; head = head->next) {
            if(strcmp(head->team_name, name) == 0)
                return 1;
        }
    }
    return 0;
}


void insertTeamList(team_list * team_list, char *team_name) { /* adiciona uma equipa a lista dos nomes das equipas usada no comando 'g' */
    team * new_team = malloc(sizeof(team));

    new_team->team_name = malloc((strlen(team_name)+1)*sizeof(char));

    strcpy(new_team->team_name, team_name);

    new_team->next = NULL;

    if(team_list->last != NULL) {
        team_list->last->next = new_team;
        team_list->last = new_team;
    }
    else {
        team_list->head = new_team;
        team_list->last = new_team;
    }
}



void insertTeam(team_list **teamHash, char *name) { /* adiciona uma equipa a hash table */
    int ind = hash(name, HASH_SIZE);
    
    team * new_team = malloc(sizeof(team));
    
    new_team->team_name = malloc((strlen(name)+1)*sizeof(char));
    strcpy(new_team->team_name, name);
    new_team->wins = 0;
    new_team->next = NULL;

    if(teamHash[ind]->last != NULL) {
        teamHash[ind]->last->next = new_team;
        teamHash[ind]->last = new_team;
    }
    else {
        teamHash[ind]->head = new_team;
        teamHash[ind]->last = new_team;
    }
}


void add_team(team_list **teamHash, team_list * lista_equipas, int NL) { /* da scan ao nome da equipa, se a equipa nao existir, adiciona a equipa a hash table */
    char * team_name = malloc(MAX_STRLEN * sizeof(char));

    scanf("  %[^:\n]", team_name);

    if(team_exists(teamHash, team_name)) {
        printf("%d Equipa existente.\n", NL);
        free(team_name);
        return;
    }

    else {
        insertTeam(teamHash, team_name);
        insertTeamList(lista_equipas, team_name);
        free(team_name);
    }
}


void add_win(team_list **teamHash, char *team_name) {
    int ind = hash(team_name, HASH_SIZE);

    team * head = teamHash[ind]->head;

    if(strcmp(head->team_name, team_name) == 0) {
        teamHash[ind]->head->wins += 1;
        return;
    }
    else {
        for(; head->next != NULL; head = head->next) {
            if(strcmp(head->team_name, team_name) == 0) {
                teamHash[ind]->head->wins += 1;
                return;
            }

        }
    }
}


void remove_win(team_list **teamHash, char *team_name) {
    int ind = hash(team_name, HASH_SIZE);

    team * head = teamHash[ind]->head;

    if(strcmp(head->team_name, team_name) == 0) {
        teamHash[ind]->head->wins -= 1;
        return;
    }
    else {
        for(; head->next != NULL; head = head->next) {
            if(strcmp(head->team_name, team_name) == 0) {
                teamHash[ind]->head->wins -= 1;
                return;
            }

        }
    }
}


int match_exists(match_list **matchHash, char *name) {
    int ind = hash(name, HASH_SIZE);

    if(matchHash[ind]->head) {
        match * head = matchHash[ind]->head;
        
        if(head) {
            if(strcmp(head->match_name, name) == 0)
                return 1;
            for(; head->next != NULL; head = head->next) {
                if(strcmp(head->match_name, name) == 0)
                    return 1;
            }
        }
    }
    return 0;
}


void insertMatchList(matches * match_list, char *match_name) { /* adiciona um jogo a lista dos nomes dos jogos usada no comando 'l' */
    m_name * new_match = malloc(sizeof(m_name));

    new_match->match_name = malloc((strlen(match_name)+1)*sizeof(char));

    strcpy(new_match->match_name, match_name);

    
    if(match_list->last != NULL) {
        match_list->last->next = new_match;
        match_list->last = new_match;
    }
    else {
        match_list->head = new_match;
        match_list->last = new_match;
    }

    new_match->previous = match_list->last;
    new_match->next = NULL;
}


void insertMatch(match_list **matchHash, team_list **teamHash, char *match_name, char *team1_name, char *team2_name, int team1_score, int team2_score) { /* adiciona um jogo a hash table */
    int ind = hash(match_name, HASH_SIZE); 

    match * new_match = malloc(sizeof(match));

    new_match->match_name = malloc((strlen(match_name)+1)*sizeof(char));
    new_match->team2_name = malloc((strlen(team2_name)+1)*sizeof(char));
    new_match->team1_name = malloc((strlen(team1_name)+1)*sizeof(char));

    strcpy(new_match->match_name, match_name);
    strcpy(new_match->team1_name, team1_name);
    strcpy(new_match->team2_name, team2_name);
    
    new_match->team1_score = team1_score;
    new_match->team2_score = team2_score;
    
    new_match->previous = matchHash[ind]->last;
    new_match->next = NULL;

    if(matchHash[ind]->last != NULL) {
        matchHash[ind]->last->next = new_match;
        matchHash[ind]->last = new_match;
    }
    
    else {
        matchHash[ind]->head = new_match;
        matchHash[ind]->last = new_match;
    }
        
    if(team1_score > team2_score) /* vai adicionar a vitoria a equipa que ganhou o jogo */
        add_win(teamHash, team1_name);
    else if(team1_score < team2_score)
        add_win(teamHash, team2_name);
    else
        return;
}


void add_match(match_list **matchHash, team_list **teamHash, matches *lista_jogos, int NL) {
    char * match_name = malloc(MAX_STRLEN * sizeof(char));
    char * team1_name = malloc(MAX_STRLEN * sizeof(char));
    char * team2_name = malloc(MAX_STRLEN * sizeof(char));
    int team1_score, team2_score;

    scanf("  %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", match_name, team1_name, team2_name, &team1_score, &team2_score);

    if(match_exists(matchHash, match_name)) { /* verifica se o jogo ja existe */
        printf("%d Jogo existente.\n", NL);
        free(match_name);
        free(team1_name);
        free(team2_name);
        return;
    }

    else if(!team_exists(teamHash, team1_name) || !team_exists(teamHash, team2_name)) { /* verifica se as ambas as equipas existem */
        printf("%d Equipa inexistente.\n", NL);
        free(match_name);
        free(team1_name);
        free(team2_name);
        return;
    }

    else {  /* se o jogo nao ja existir e se ambas as equipas existirem, adiciona o jogo */
        insertMatch(matchHash, teamHash, match_name, team1_name, team2_name, team1_score, team2_score);
        insertMatchList(lista_jogos, match_name);
    }

    free(match_name);
    free(team1_name);
    free(team2_name);
}


void team_lookup(team_list **teamHash, int NL) { /* procura uma equipa e retorna o seu nome e a quantidade de jogso ganhos */
    char *team_name = malloc(MAX_STRLEN * sizeof(char));
    int ind;
    team * head;

    scanf("  %[^:\n]", team_name);

    ind = hash(team_name, HASH_SIZE);
    head = teamHash[ind]->head;

    if(!team_exists(teamHash, team_name)) { /* ve se existe a equipa */
        printf("%d Equipa inexistente.\n", NL);
        free(team_name);
        return;
    }

    else { /* se existir, vai percorrer a lista das equipas em que esta inserida a equipa para ver quantas jogos ganhou */
        if(strcmp(head->team_name, team_name) == 0) {
                printf("%d %s %d\n", NL, team_name, head->wins);
                free(team_name);
                return;
            }
        while(head->next) {
            if(strcmp(head->team_name, team_name) == 0) {
                printf("%d %s %d\n", NL, team_name, head->wins);
                free(team_name);
                return;
            }
            head = head->next;
        }
    }
}


void match_lookup_aux(match_list **matchHash, int NL, char * match_name) {
    int ind = hash(match_name, HASH_SIZE);
    match * head = matchHash[ind]->head;

    if(head->next != NULL) {
        for(; head->next != NULL; head = head->next) {
            if(strcmp(head->match_name, match_name) == 0)
                break;
        }
    }

    printf("%d %s %s %s %d %d\n", NL, match_name, head->team1_name, head->team2_name, head->team1_score, head->team2_score);
}


void match_lookup(match_list **matchHash, int NL) {  /* funcao que procura um jogo e torna o nome do mesmo, das duas equipas, e o score das equipas */
    char *match_name = malloc(MAX_STRLEN * sizeof(char));

    scanf("  %[^:\n]", match_name);

    if(!match_exists(matchHash, match_name)) { /* verifica se o jogo existe de todo, antes de ir procura lo na hash table */
        printf("%d Jogo inexistente.\n", NL);
        free(match_name);
        return;
    }

    else { /* se existir, vai percorrer a lista dos jogos em que esta inserido o jogo para obter os dados desse jogo */
        match_lookup_aux(matchHash, NL, match_name);
        free(match_name);
        return;
    }
}


void remove_match_list(matches *lista_jogos, char * match_name) { /* remove um jogo da lista dos jogos utilizada no comando 'g' */
    m_name * head = lista_jogos->head;

    if(head->next != NULL) {
        for(; head->next != NULL; head = head->next) {
            if(strcmp(head->match_name, match_name) == 0)
                break;
        }
    }

    if(head->previous != NULL)
        head->previous = head->next;
    else
        lista_jogos->head = head->next;
    
    if(head->next != NULL)
        head->next->previous = head->previous;
    else
        lista_jogos->last = head->previous;

    free(head);
}

void remove_match(team_list **teamHash, match_list **matchHash, char * match_name) { /* funcao utilizada na delete_match */
    int ind = hash(match_name, HASH_SIZE);
    match * head = matchHash[ind]->head;

    if(head->next != NULL) {
        for(; head->next != NULL; head = head->next) {
            if(strcmp(head->match_name, match_name) == 0) {
                break;
            }
        }
    }

    if(head->team1_score > head->team2_score) {
        remove_win(teamHash, head->team1_name);
    }

    else if(head->team1_score < head->team2_score) {
        remove_win(teamHash, head->team2_name);
    }

    if(head->previous != NULL)
        head->previous = head->next;
    else
        matchHash[ind]->head = head->next;
    
    if(head->next != NULL)
        head->next->previous = head->previous;
    else
        matchHash[ind]->last = head->previous;

    free(head);
}


void delete_match(team_list **teamHash, match_list **matchHash, matches *lista_jogos, int NL) { /* apaga um jogo da hashtable e da lista dos jogos usada no comando 'l' */
    char *match_name = malloc(MAX_STRLEN * sizeof(char));

    scanf("  %[^:\n]", match_name);

    if(!match_exists(matchHash, match_name)) {
        printf("%d Jogo inexistente.\n", NL);
        free(match_name);
        return;
    }

    remove_match(teamHash, matchHash, match_name);
    remove_match_list(lista_jogos, match_name);

    free(match_name);
}


void altera_score(team_list **teamHash, match_list **matchHash, char * match_name, int new_1, int new_2) { /* funcao "auxiliar" que altera o score de um jogo, utilizada na change_score */
    int ind = hash(match_name, HASH_SIZE);
    match * head = matchHash[ind]->head;
    int old_1, old_2;

    if(head->next != NULL) {
        for(; head->next != NULL; head = head->next) {
            if(strcmp(head->match_name, match_name) == 0) {
                break;
            }
        }
    }

    old_1 = head->team1_score;
    old_2 = head->team2_score;

    if((old_1 > old_2) && (new_1 == new_2))
        remove_win(teamHash, head->team1_name);
    else if((old_1 > old_2) && (new_1 < new_2)) {
        remove_win(teamHash, head->team1_name);
        add_win(teamHash, head->team2_name);
    }
    
    else if((old_1 == old_2) && (new_1 > new_2))
        add_win(teamHash, head->team1_name);
    else if((old_1 == old_2) && (new_1 < new_2))
        add_win(teamHash, head->team2_name);
    else if((old_1 < old_2) && (new_1 == new_2))
        remove_win(teamHash, head->team2_name);
    else if((old_1 < old_2) && (new_1 > new_2)) {
        remove_win(teamHash, head->team2_name);
        add_win(teamHash, head->team1_name);
    }

    head->team1_score = new_1;
    head->team2_score = new_2;
}


void change_score(team_list **teamHash, match_list **matchHash, int NL) { /* altera o score de um jogo */
    char * match_name = malloc(MAX_STRLEN * sizeof(char));
    int team1_new_score, team2_new_score;

    scanf("  %[^:\n]:%d:%d", match_name, &team1_new_score, &team2_new_score);

    if(!match_exists(matchHash, match_name)) { /* ve se a equipa existe, se nao existe, imprime erro, se existir, altera o score com uma funcao auxiliar */
        printf("%d Jogo inexistente.\n", NL);
        free(match_name);
        return;
    }

    else {
        altera_score(teamHash, matchHash, match_name, team1_new_score, team2_new_score);
        free(match_name);
        return;
    }
}


void print_games(matches *lista_jogos, match_list **matchHash, int NL) { /* imprime os jogos por ordem que foram introduzidos */
    m_name * head;

    if(lista_jogos->head == NULL) {
        return;
    }

    else {
        head = lista_jogos->head;
        for(; head != NULL; head = head->next) {
            match_lookup_aux(matchHash, NL, head->match_name);
        }
    }
}


int lookup_team_wins(team_list **teamHash, char * team_name) { /* retorna as wins de uma equipa dado o nome */
    int ind = hash(team_name, HASH_SIZE);
    team * head = teamHash[ind]->head;

    if(strcmp(head->team_name, team_name) == 0)
                return head->wins;
    else {
        while(head->next) {
            if(strcmp(head->team_name, team_name) == 0) {
                return head->wins;
            }
            head = head->next;
        }
    }
    return 0;
}


int sorted(team_list * lista_equipas) { /* percorre a lista das equipas utilizada no comando 'g' para ver se esta por ordem alfabetica */
    team * t_head = lista_equipas->head;

    if(t_head->next == NULL)
        return 1;
    while(t_head->next) {
        if(strcmp(t_head->team_name, t_head->next->team_name) > 0)
            return 0;
        t_head = t_head->next;
    }
    return 1;
}


void print_teams(team_list *lista_equipas, team_list **teamHash, int NL) {
    int i, list_len = 0, max_wins = 0;
    char * temp = malloc(MAX_STRLEN * sizeof(char));

    team * head;
    team * t_head = lista_equipas->head;

    team_list * lista_eq = malloc(sizeof(team_list));

    initTeamList(lista_eq);

    for(i = 0; i < HASH_SIZE; i++) { /* percorre a hash table para atualizar as wins nesta lista (lista_equipas) e calcula as wins maximas das equipas */
        if(teamHash[i]->head != NULL) {
            head = teamHash[i]->head;
            while(head) {
                head->wins = lookup_team_wins(teamHash, head->team_name); /* atualiza as wins na lista */
                if(head->wins > max_wins)
                    max_wins = head->wins;
                if(head->next != NULL)
                    head = head->next;
                else
                    break;
            }
        }
    }
    
    for(i = 0; i < HASH_SIZE; i++) { /* percorre a hash table, outra vez, e adiciona todas as equipas com as wins maximas a lista criada nesta funcao - lista_eq */
        if(teamHash[i]->head != NULL) {
            head = teamHash[i]->head;
            while(head) {
                if(head->wins == max_wins) {
                    insertTeamList(lista_eq, head->team_name);
                    list_len += 1;
                }
                if(head->next != NULL)
                    head = head->next;
                else
                    break;
            }
        }
    }

    if(lista_eq->head == NULL) {
        free(temp);
        destroy_team_list(lista_eq);
        return;
    }

    if(lista_eq->head->next == NULL) {
        printf("%d Melhores %d\n%d * %s\n", NL, max_wins, NL, lista_eq->head->team_name);
        free(temp);
        destroy_team_list(lista_eq);
        return;
    }

    if(lista_eq->head) {
        while(!sorted(lista_eq)) { /* enquanto a lista nao tiver organizada alfabeticamente */
            t_head = lista_eq->head;
            while(t_head) {
                if(t_head->next != NULL) {
                    if(strcmp(t_head->team_name, t_head->next->team_name) > 0) { /* troca os nomes das equipas, sorting por bubble sort */
                        strcpy(temp, t_head->team_name);
                        free(t_head->team_name);
                        t_head->team_name = malloc((strlen(t_head->next->team_name)+1) * sizeof(char));
                        strcpy(t_head->team_name, t_head->next->team_name);
                        free(t_head->next->team_name);
                        t_head->next->team_name = malloc((strlen(temp) + 1) * sizeof(char));
                        strcpy(t_head->next->team_name, temp);
                    }
                    t_head = t_head->next;
                }
                else
                    break;
            }
        }
    }

    t_head = lista_eq->head;

    printf("%d Melhores %d\n", NL, max_wins);
    while(t_head) { /* imprime as equipas */
        printf("%d * %s\n", NL, t_head->team_name);
        if(t_head->next != NULL)
            t_head = t_head->next;
        else
            break;
        }

    destroy_team_list(lista_eq);
    free(temp);
}


void end(team_list *lista_equipas, matches *lista_jogos, team_list **teamHash, match_list **matchHash) { /* funcao que termina o programa, destruindo as listas e as hash tables */
    int i;

    destroy_team_list(lista_equipas);
    destroy_match_list2(lista_jogos);
    
    for(i = 0; i < HASH_SIZE; i++) {
        destroy_team_list(teamHash[i]);
        destroy_match_list(matchHash[i]);
    }
}

int main() { /* funcao main com declaracao de variaveis e o ciclo de scan dos comandos a serem executados */
    char c; /* char c usado para fazer scan do comando a executar */
    int NL = 1; /* numero que mantem tracking das linhas dos comandos */

    /* utilizam se duas hash tables para guardar os jogos e as equipas para executar a maior parte dos comandos */

    team_list *teamHash[HASH_SIZE]; /* declara hash table das equipas */
    match_list *matchHash[HASH_SIZE]; /* declara hash table dos jogos */

    /* para alem das hash tables, utilizamos tambem estas listas para ser mais facil de executar os comandos 'g' e 'l' */

    matches *lista_jogos = make_match_list(); 
    team_list *lista_equipas = malloc(sizeof(team_list));

    initTeamList(lista_equipas); /* inicializa a lista ligada das equipas */
    initTeamHash(teamHash); /* inicializa a hash table das equipas */
    initMatchHash(matchHash); /* inicializa a hash table dos jogos */

    while((c=getchar()) != 'x') {
        switch(c) {
            case 'a':
                add_match(matchHash, teamHash, lista_jogos, NL);
                NL++;
                break;
            case 'A':
                add_team(teamHash, lista_equipas, NL);
                NL++;
                break;
            case 'p':
                match_lookup(matchHash, NL);
                NL++;
                break;
            case 'P':
                team_lookup(teamHash, NL);
                NL++;
                break;
            case 'r':
                delete_match(teamHash, matchHash, lista_jogos, NL);
                NL++;
                break;
            case 's':
                change_score(teamHash, matchHash, NL);
                NL++;
                break;
            case 'l':
                print_games(lista_jogos, matchHash, NL);
                NL++;
                break;
            case 'g':
                print_teams(lista_equipas, teamHash, NL);
                NL++;
                break;
        }
    }

    end(lista_equipas, lista_jogos, teamHash, matchHash);

    return 0;
}