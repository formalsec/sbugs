#define ZERO 0
#define UM 1
#define DOIS 2

/*______________Definitions of the Structs____________*/
/*Team defined as equipa (pointer)
  Caracteristics of an equipa : name, victorys.*/
typedef struct equipa{
	char *name;
	unsigned int victorys;
}*equipa;

/*Game defined as jogo (pointer)
  Caracteristics of a jogo : name, equipa1, equipa2, r1, r2, idNumber.*/
typedef struct jogo{
	char *name;
	equipa equipa1, equipa2;
	unsigned int r1, r2;
	unsigned long int idNumber;
	/* idNumber is the index of the games in the list of games to make the access
	   and removal easier */
}*jogo;

/*______________Prototypes of the auxiliar functions used in the comand functions________________*/

/*________________Destructor Functions_____________*/
void freeEquipa(equipa a);
void freeJogo(jogo a);

/*________________Print Functions__________________*/
void printEquipa(equipa a);
void printJogo(jogo a);

/*_______________Constructor Functions_____________*/
equipa newEquipa(char *name);
jogo newJogo(char *name, equipa equipa1, equipa equipa2, int score1, int score2);

/*_______Manipulators_of_the_Data_Elements_________*/
void removeVictory(equipa a);
void addVictory(equipa a);
void changeScore(jogo a, int s1, int s2);