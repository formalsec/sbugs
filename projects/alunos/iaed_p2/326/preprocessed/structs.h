#ifndef STRUCTS
#define STRUCTS

typedef struct team_node { /* estrutura do node das equipas */
    char *team_name;
    int wins;
    struct team_node *next;
} team;

typedef struct { /* estrutura lista de equipas */
    team *head, *last;
} team_list;

typedef struct match_node { /* estrutura do node dos jogos */
    char *match_name;
    char *team1_name;
    char *team2_name;
    int team1_score;
    int team2_score;
    struct match_node *previous, *next;
} match;

typedef struct { /* estrutura da lista dos jogos */
    match *head, *last;
} match_list;

typedef struct match_name {
    char *match_name;
    struct match_name *previous, *next;
} m_name;

typedef struct match_names_list {
    m_name *head, *last;
} matches;


#endif