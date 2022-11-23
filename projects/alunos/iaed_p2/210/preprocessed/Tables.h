#include "Structs.h"

/* Auxiliar values to hash a team or game by its name */
#define HASH_VALUE_1 127
#define HASH_VALUE_2 31415
#define HASH_VALUE_3 27183

/*______________Definitions of the Structs____________*/
/* This struct holds a game and a variable that allows 
   us to know if the position is or was once occupied.
   This variables prevents a bug of double hashing 
   that when you would search a game that was on the 
   table you wouldnt find it, because one of the 
   previous games that it had a collision with was 
   removed so the search would stop on that position
   and wouldnt find the wanted game.*/
typedef struct element{
	jogo game;
	int ocupado;
}*element;

/*_______________Initialization Functions_____________*/
void tableEInit(int max);
void tableJInit(int max);
void initArrayE(int max);
void initArrayJ(int max);

/*_______________Hash Functions_______________________*/
int hash1(char *v, int M);
int hash2(char *v, int M);

/*_______________Insertion Functions__________________*/
void insertArrayE(equipa element);
int insertArrayJ(jogo element);
void tableEInsert(equipa a);
void tableJInsert(jogo a, int pos);

/*_________________Searching Functions________________*/
equipa tableESearch(char *name);
element tableJSearch(char *name);

/*_________________Removing Functions_________________*/
void removeArrayJ(int pos);
void tableJDelete(jogo j);

/*_________________Printing Functions_________________*/
void printJogos(int linha);
void printEquipas(int linha, int n);

/*________________Destructor Functions________________*/
void freeArrayE();
void freeArrayJ();
void freeTableE();
void freeTableJ();

/*_________________Auxiliar Functions_________________*/
int findPrime(int M);
void expandTableE();
void expandTableJ();
void expandArrayE();
void expandArrayJ();
int putBiggerOnTop();
void heapify(int n, int i);
void heapsort(int n);
int getNequipas();