#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS  1024	/* Maximal number of characters plus one for '\0' */
#define HT_SZ	  10657	/* Initial size of the hash tables */

#define HEAD          0 /* index of the head in ends */
#define TAIL          1	/* index of the tail in ends */