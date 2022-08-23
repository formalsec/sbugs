#ifndef COMUNS_H
#define  COMUNS_H

	
	#define MAX_STRING 1024
	#define SIZE_HASH 15731   	/*tamanho da hash table dos jogos*/
	#define SIZE_HASH_EQUIPAS 20071  /*tamanho da hash table das equipas*/

int hash(char *v, int M);

int hash1(char *v,int M);

char *reduce_string(char s[MAX_STRING]);



#endif  /*COMUNS_H*/
