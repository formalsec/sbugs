#include <stdio.h>
#include <string.h>
#include "declaracoes.h"

/* Auxiliar: Devolve o index associado a um jogo. Caso o jogo seja inexistente, 
   devolve um index impossivel. */
int returnGameIndex(Game g[MAX_G], char n[MAX_CHARS + 1], int i) {
    int x;
    for (x = 0; x <= i; x++) {
        if (strcmp(g[x].name, n) == 0) return x;
        else continue;
    }
    return -1;
}

/* Auxiliar: Devolve o index associado a uma equipa. Caso a equipa seja inexistente, 
   devolve um index impossivel. */
int returnTeamIndex(Team t[MAX_T], char n[MAX_CHARS + 1], int j) {
    int x;
    for (x = 0; x <= j; x++) {
        if (strcmp(t[x].name, n) == 0) return x;
        else continue;
    }
    return -1;
}

/* Auxiliar: Compara resultados antigos e novos para determinar se 
   se incrementa ou decrementa a vitoria a uma equipa. */
int addOrSubtractVictories(int s1, int s2, int ns1, int ns2) {
    if (s1 > s2 && ns1 < ns2) return 0;
    else if (s1 < s2 && ns1 > ns2) return 1;
    else if (s1 == s2 && ns1 > ns2) return -1;
    else if (s1 == s2 && ns1 < ns2) return 2;
    else if (s1 > s2 && ns1 == ns2) return -2;
    else if (s1 < s2 && ns1 == ns2) return 3;
    else return -3;
}

/* Cria um novo jogo, caso ainda seja inexistente e as equipas existirem, (Comando a). */
int createNewGame(Game g[MAX_G], Team t[MAX_T], int nl, int i, int j) {
    
    char n[MAX_CHARS + 1], t1[MAX_CHARS + 1], t2[MAX_CHARS + 1];
    int s1, s2;
    int a, b, c;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", n, t1, t2, &s1, &s2);
    a = returnGameIndex(g, n, i);
    b = returnTeamIndex(t, t1, j);
    c = returnTeamIndex(t, t2, j);
    
    if (a != -1) {
        printf("%d Jogo existente.\n", nl);
        return 0;
    }
    else if (b == -1 || c == -1) {
        printf("%d Equipa inexistente.\n", nl);
        return 0;
    }
    else if (i < MAX_G) {
        strcpy(g[i].name, n);
        strcpy(g[i].team1, t1);
        strcpy(g[i].team2, t2);
        g[i].score1 = s1; 
        g[i].score2 = s2;
        if (s1 > s2) t[b].victories++;
        else if (s2 > s1) t[c].victories++;
        return 1;
    }
    return 0;
}

/* Cria uma nova equipa, caso ainda seja inexistente, (Comando A). */
int createNewTeam(Team t[MAX_T], int nl, int j) {    
    
    char n[MAX_CHARS + 1];
    int a;
    
    scanf(" %[^\n]", n);
    a = returnTeamIndex(t, n, j);
    
    if (a != -1) {
        printf("%d Equipa existente.\n", nl);
    }
    else if (j < MAX_T) {
        strcpy(t[j].name, n);
        t[j].victories = 0;
        return 1;
    }
    return 0;
}

/* Lista todos os jogos existentes, (Comando l). */
void listGames(Game g[MAX_G], int nl, int i) {
    int x;
    for (x = 0; x < i; x++) {
        printf("%d %s %s", nl, g[x].name, g[x].team1); 
        printf(" %s %d %d\n", g[x].team2, g[x].score1, g[x].score2);
    }
}

/* Procura um jogo e devolve os detalhes referentes, (Comando p). */
void searchGame(Game g[MAX_G], int nl, int i) {
    
    int a;
    char n[MAX_CHARS + 1];    
    
    scanf(" %[^\n]", n);
    a = returnGameIndex(g, n, i);
    
    if (a == -1) printf("%d Jogo inexistente.\n", nl);
    else {
        printf("%d %s %s", nl, g[a].name, g[a].team1);
        printf(" %s %d %d\n", g[a].team2, g[a].score1, g[a].score2);
    }
}

/* Procura uma equipa e devolve os detalhes referentes, (Comando P). */
void searchTeam(Team t[MAX_T], int nl, int j) {
    
    int a;
    char n[MAX_CHARS + 1];
    
    scanf(" %[^\n]", n);
    a = returnTeamIndex(t, n, j);
    
    if (a == -1) printf("%d Equipa inexistente.\n", nl);
    else printf("%d %s %d\n", nl, t[a].name, t[a].victories);
}

/* Remove um jogo do sistema, (Comando r). */
int removeGame(Game g[MAX_G], Team t[MAX_T], int nl, int i, int j) {
    
    int a, b, c, x;
    char n[MAX_CHARS + 1];  
    
    scanf(" %[^\n]", n);
    a = returnGameIndex(g, n, i);

    if (a == -1) {
        printf("%d Jogo inexistente.\n", nl);
    }
    else {
        b = returnTeamIndex(t, g[a].team1, j);
        c = returnTeamIndex(t, g[a].team2, j);
        if (g[a].score1 > g[a].score2) t[b].victories--;
        else if (g[a].score2 > g[a].score1) t[c].victories--;
        for (x = a; x <= i; x++) {
            g[x] = g[x+1];
        }
        return 1;
    }
    return 0;
}

/* Altera o resultado de um jogo, incrementando ou decrementando o n de vitorias, (Comando s). */
void changeScore(Game g[MAX_G], Team t[MAX_T], int nl, int i, int j) {
    
    char n[MAX_CHARS + 1];
    int s1, s2;
    int a, b, c, d;
    
    scanf(" %[^:]:%d:%d", n, &s1, &s2);
    a = returnGameIndex(g, n, i);
    
    if (a == -1) printf("%d Jogo inexistente.\n", nl);
    else if (s1 >= 0 && s2 >= 0) {
        b = returnTeamIndex(t, g[a].team1, j);
        c = returnTeamIndex(t, g[a].team2, j); 
        d = addOrSubtractVictories(g[a].score1, g[a].score2, s1, s2);        
        if (d == 0) { t[b].victories--; t[c].victories++; 
        }
        else if (d == 1) { t[b].victories++; t[c].victories--; 
        }
        else if (d == -1) t[b].victories++;
        else if (d == 2) t[c].victories++;
        else if (d == -2) t[b].victories--;
        else if (d == 3) t[c].victories--;  
        g[a].score1 = s1;
        g[a].score2 = s2;
    }
}

/* Lista as equipas com o maior n de vitorias por ordem lexicografica, (Comando g). */
void listMostWins(Team t[MAX_T], int nl, int j) {   
    
    int max_v = 0;
    int x = 0, y, z = -1;
    char o[MAX_O][MAX_CHARS + 1], temp[MAX_CHARS + 1];
    
    while (x < j) {
        if (max_v < t[x].victories) max_v = t[x].victories;
        x++;
    }

    for (x = 0; x < j; x++) {
        if (t[x].victories == max_v) { 
            z++; strcpy(o[z], t[x].name);
        }
        else continue;
    }

    for (x = 0; x <= z; x++) {
        for (y = x + 1; y <= z; y++) {
            if (strcmp(o[x], o[y]) > 0) { 
                strcpy(temp, o[x]); 
                strcpy(o[x], o[y]); 
                strcpy(o[y], temp); 
            }
        }
    }

    if (j > 0) {
        printf("%d Melhores %d\n", nl, max_v);
        for (x = 0; x <= z; x++) printf("%d * %s\n", nl, o[x]);
    }
}

/* Processa comandos e realiza diferentes funcoes, consoante o comando. 
   Se o comando for x, o programa encerra. */
int main() {
    
    int a;
    char c;
    
    /* Variavel estatica associada ao numero do input. */
    static int nl = 0;
    
    /* Variavel estatica associada ao indice maximo da lista de jogos. */
    static int i = 0;
    
    /* Variavel estatica associada ao indice maximo da lista de equipas. */
    static int j = 0;

    static Game games[MAX_G]; /* Lista de jogos da base de dados. */
    static Team teams[MAX_T]; /* Lista de equipas da base de dados. */
    
    scanf("%c", &c);
    while (c != 'x') {
        switch (c) {
            case 'a': 
                nl++;  
                a = createNewGame(games, teams, nl, i, j);
                if (a == 1) i++;
                break;
            case 'A': 
                nl++;
                a = createNewTeam(teams, nl, j); 
                if (a == 1) j++;
                break;
            case 'l': nl++; listGames(games, nl, i); break;
            case 'p': nl++; searchGame(games, nl, i); break;
            case 'P': nl++; searchTeam(teams, nl, j); break;
            case 'r': 
                nl++; 
                a = removeGame(games, teams, nl, i, j);
                if (a == 1) i--;
                break;
            case 's': nl++; changeScore(games, teams, nl, i, j); break;
            case 'g': nl++; listMostWins(teams, nl, j); break;
        }
        scanf("%c", &c);
    }  
    return 0;
}