#ifndef TEAM_H_
#define TEAM_H_

/* Tamanho maximo da descricao do produto */
#define TEAM_MAX_NAME 1023

typedef struct team {
	char *name;
} Team;


Team * team_new       (const char * name);
void      team_free     (Team *t);

char * team_get_name     (const Team *t);

char * team_to_string    (const Team *t, char * buf, int buf_size);
void   team_print        (const Team *t);


#endif
