/*File generated by PreProcessor.py*/


#include "common_code.h"


char *StringDup(char *string)
{
  char *new = (char *) malloc((sizeof(char)) * (strlen(string) + 1));
  strcpy(new, string);
  return new;
}

int HashU(char *string, int M)
{
  int h = 0;
  for (; (*string) != '\0'; string++)
    h = ((127 * h) + (*string)) % M;

  return h;
}
