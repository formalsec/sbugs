#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>

char *strdup(const char *src) {
  char *dst = can_fail_malloc(strlen (src) + 1); 
  if (dst == NULL) return NULL;          
  strcpy(dst, src);                      
  return dst;            
}