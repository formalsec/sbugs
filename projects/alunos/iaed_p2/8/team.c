#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "myLib.h"
#include "team.h"


/* creates new team */
Team * team_new(const char * name) {
    
    Team * t;
    extern char* strdup(const char*);
    
    t = (Team*) can_fail_malloc(sizeof(Team));
	EXIT_IF_ERROR("team_new: can_fail_malloc");

	t-> name = strdup(name); 

	return t;
}

/*frees space in memory*/
void team_free(Team *t) {
	ERROR_IF_NULL(t, "team_free", exit(EXIT_FAILURE));
	free(t->name);
	free(t);
}

/*Gets team name */
char * team_get_name(const Team *t) {
	ERROR_IF_NULL(t, "team_get_name", exit(EXIT_FAILURE));
	return t->name;
}

/* String of all the team atributes */
char * team_to_string(const Team *t, char * buf, int buf_size) {
	//extern int snprintf (char *__restrict __s, size_t __maxlen,__const char *__restrict __format, ...)__THROW __attribute__ ((__format__ (__printf__, 3, 4)));
	ERROR_IF_NULL(t, "team_to_string", exit(EXIT_FAILURE));
	snprintf(buf, buf_size, "Team: %s", team_get_name(t));
	return buf;
}

/* Prints string internal struck of team */
void team_print(const Team *t) {
	char buf[100];
	ERROR_IF_NULL(t, "team_print", exit(EXIT_FAILURE));
	printf("%s\n", team_to_string(t, buf, 100));
}