#include "libr_const.h"
#include "data_structures.h"

/* Reads a strings from standart input until the terminator character is hit.
   Allocates it and returns it's pointer */
char * read_string(char terminator);

/* Reads from standart input until terminator character is hit.
   Returns the number corresponding to the input. */
int read_number(char terminator);

/* Comparator function for qsort() */
int comparator(const void *p1, const void *p2);

/*  */
int error_check_r_s(Game *srch, char *name, int *NL);