#ifndef ALLOCATORS_H
#define ALLOCATORS_H

#include <time.h>
#include <stdlib.h>

void *can_fail_malloc(size_t nbytes) {
  srand(time(NULL));
  double fail = (double) rand() / (double) RAND_MAX;
  if (fail <= 0.10) return NULL;
  return malloc(nbytes);
}

void *can_fail_calloc(size_t nmemb, size_t size) {
  srand(time(NULL));
  double fail = (double) rand() / (double) RAND_MAX;
  if (fail <= 0.10) return NULL;
  return calloc(nmemb, size);
}

void *can_fail_realloc(void *ptr, size_t size) {
  srand(time(NULL));
  double fail = (double) rand() / (double) RAND_MAX;
  if (fail <= 0.10) return NULL;
  return realloc(ptr, size);
}


#endif
