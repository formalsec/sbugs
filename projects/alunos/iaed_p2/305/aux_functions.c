#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "aux_functions.h"

/*-------------------------------------------------------------------------------------------------
	Auxilary functions
-------------------------------------------------------------------------------------------------*/

/* Reads a strings from standart input until the terminator character is hit.
   Allocates it and returns it's pointer */
char * read_string(char terminator){
	char temp[MAX_CHARS];	/* string where input will be temporarily placed */
	char *str;				
	
	if(terminator == ':'){
		scanf("%[^:]", temp);
	}
	else{
		scanf("%[^\n]", temp);
	}
	getchar();

	str = (char *) can_fail_malloc((strlen(temp) + 1) * sizeof(char));
	strcpy(str, temp);

	return str;
}

/* Reads from standart input until terminator character is hit.
   Returns the number corresponding to the input. */
int read_number(char terminator){
	int dig;
	int n=0;
	
	while((dig = getchar()) != terminator){
		n = (n*10) + (dig-48);
	}
	
	return n;
}

/* Comparator function for qsort() */
int comparator(const void *p1, const void *p2){
	return strcmp(*(char **)p1, *(char **)p2);
}

/*  */
int error_check_r_s(Game *srch, char *name, int *NL){
	if(srch == NULL){
		printf("%d Jogo inexistente.\n", *NL);
		free(name);
		return 1;
	}
	return 0;
}