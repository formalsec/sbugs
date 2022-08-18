#include "team.h"

/* Cria uma nova equipa com o nome e numero de vitorias fornecidos. O nome
   fornecido eh copiado para um novo espaco da memoria com o tamanho exato do
   nome. Devolve o ponteiro que aponta para a nova equipa. */
Team *newTeam(char *name, int wins) {
    Team *team = (Team *) malloc(sizeof(Team));

    /* Copiar nome para novo espaco com apenas o tamanho necessario. */
    team->name = (char *) malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(team->name, name);

    team->wins = wins;

    return team;
}

/* Liberta a memoria da equipa fornecida. */
void freeTeam(Team *team) {
    free(team->name);
    free(team);
}

/* Devolve o nome da equipa fornecida. */
char *getTeamName(Team *team) {
    return team->name;
}

/* Devolve o numero de vitorias da equipa fornecida. */
int getTeamWins(Team *team) {
    return team->wins;
}

/* Adiciona o numero de vitorias fornecido ao total de vitorias da equipa dada.
   O numero de vitorias eh decrementado se o numero de vitorias fornecido for
   negativo. */
void addTeamWins(Team *team, int wins) {
    team->wins = team->wins + wins;
}

/* Dah print da equipa fornecida com o numero de linha fornecido. */
void printTeam(Team *team, int nl) {
    printf("%d * %s\n", nl, team->name);
}

/* Devolve numero de comparacao entre o nome fornecido e a equipa fornecido.
   Negativo -> nome fornecido encontra-se ah esquerda.
   Igual -> nome fornecido eh igual.
   Positivo -> nome fornecido encontra-se ah direita. */
int teamKeyOrder(char *name, Team *team) {
    return strcmp(name, team->name);
}

/* Devolve numero de comparacao entre os jogos fornecidos.
   Negativo -> team1 fornecido encontra-se ah esquerda de team2.
   Igual -> team1 fornecido eh igual a team2.
   Positivo -> team1 fornecido encontra-se ah direita de team2. */
int teamsOrder(Team *team1, Team *team2) {
    return strcmp(team1->name, team2->name);
}

