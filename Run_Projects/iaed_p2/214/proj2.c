#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Definir as constantes e os seus valores. */
#define MAX_NAME 1024
#define MAX_TEAM 1024
#define MAX_SCORE 3
#define GAME_EXISTS "Jogo existente."
#define GAME_NOT_EXISTS "Jogo inexistente."
#define TEAM_EXISTS "Equipa existente."
#define TEAM_NOT_EXISTS "Equipa inexistente."
#define TABLE_SIZE 1009


/*Estrutura para Equipa*/
typedef struct Teams{
    char *name;
    int counterw;
} *Team;


/* Estrutura para os Jogos*/
typedef struct Games{
    
    char* name;
    Team team1;
    char *score1;
    Team team2;
    char *score2;

} *Game;


/* Estrutura para nodes*/
typedef struct node {
    Game g;
    struct node *next;

} *link;

/* Estrutura para nodes*/
typedef struct node1{
    Team t;
    struct node1 *next;

} *link1;

int counter; /*contador NL*/

link addGame();
link insert();
link lookup();
Game createGame();

link1 addTeam();
link1 insertTeam();
link1 lookupT();
Team createTeam();

void listGames();
void printGame();
void searchGame();

void searchTeam();
void printTeam();

link deleteGame();
link delete();
void editScoreTeam();

void editGameScore();

void listBestTeams();
int countWonGames();
void printTeam2();

int hash();

void sortFrees();

void freeTable();
void freeList();
void freeNode();

void freeTableT();
void freeListT();
void freeNodeT();



/* A funcao main recebe diferentes instrucoes:

 a = Adiciona um novo jogo.
 A = Adiciona uma nova equipa. 
 l = Lista todos os jogos pela ordem em que foram introduzidos. 
 p = Procura um jogo. 
 P = Procura uma equipa.  
 r = Apaga um jogo. 
 s = Altera a pontuacao (score) de um jogo. 
 g = Encontra as equipas que venceram mais jogos. - not working well
 x = Fecha/termina o programa.
 
 Usa um switch para saber qual a instrucao pretendida.
 */
int main() {

    int c, i;

    link *table;
    link1 *tablet;

    link linkedList = NULL;
    link1 teamsList = NULL;
    
    table = (link *) malloc(sizeof(link) * TABLE_SIZE);
    for (i = 0; i < TABLE_SIZE; i++)
        table[i] = NULL;

    tablet = (link1 *) malloc(sizeof(link1) * TABLE_SIZE);
    for (i = 0; i < TABLE_SIZE; i++)
        tablet[i] = NULL;
    

    while(1) {
        c = getchar();

        switch(c){
            case 'a':

                linkedList = addGame(linkedList, table, tablet);
                break;

            case 'A':

                teamsList = addTeam(teamsList, tablet);
                break;

            case 'l':

                listGames(linkedList);
                break;

            case 'p':

                searchGame(table);
                break;

            case 'P':

                searchTeam(tablet);
                break;

            case 'r':

                linkedList = deleteGame(linkedList, table);
                break;

            case 's':

                editGameScore(table);
                break;

            case 'g':

                listBestTeams(teamsList);
                break;

            case 'x':

                sortFrees(linkedList, table, teamsList, tablet);
                return 0;

            default:
                break;
        }
        while(c != '\n')
            c = getchar();
    }

    return 1;
}


/* 
    A funcao addGame:

        -Recebe como argumentos a lista ligada jogos, hashtable dos jogos e ainda a hashtable das equipas.
        -Para alem dos restantes argumentos como nome de jogo, nomes das equipas e dois scores.
        -Tem como funcoes auxiliares a createGame e a insert.
        -Adiciona o jogo criado aos nodes da lista ligada e da hashtable dos jogos recebidas.
        -Retorna a lista ligada com os nodes adicionados.
        -Retorna erro se:
            -O jogo ja existir.
            -As equipas nao existirem.
*/

link addGame(link linkedList, link* table, link1* tablet){

    char name[MAX_NAME];
    char name1[MAX_TEAM];
    char name2[MAX_TEAM];
    char score1[MAX_SCORE];
    char score2[MAX_SCORE];
    char *nameg, *team1, *team2, *scoret1, *scoret2;
    int index, index1, index2;
    Game game;
    counter +=1;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%[^:\n]:%[^:\n]", name, name1, name2, score1, score2);
    
    index = hash(name);
    index1 = hash(name1);
    index2 = hash(name2);

    if(lookup(table[index], name) != NULL) {  
        printf("%d %s\n", counter, GAME_EXISTS);
        return linkedList;
    }

    else if((lookupT(tablet[index1], name1) == NULL) || ((lookupT(tablet[index2], name2) == NULL))) { 
        printf("%d %s\n", counter, TEAM_NOT_EXISTS);
        return linkedList;
    }

    nameg =(char *) malloc(sizeof(char) * strlen(name) + 1);
    strcpy(nameg, name);

    team1 = (char *) malloc(sizeof(char) * strlen(name1) + 1);
    strcpy(team1, name1);
            
    team2 = (char *) malloc(sizeof(char) * strlen(name2) + 1);
    strcpy(team2, name2);
  
    scoret1 = (char *) malloc(sizeof(char) * strlen(score1) + 1);
    strcpy(scoret1, score1);

    scoret2 = (char *) malloc(sizeof(char) * strlen(score2) + 1);
    strcpy(scoret2, score2);

    game = createGame(nameg, team1, team2, scoret1, scoret2, tablet);

    table[index] = insert(table[index], game);
    linkedList = insert(linkedList, game);

    free(team1);
    free(team2);
    
    return linkedList;

}


/* 
    A funcao createGame:
        -Recebe como argumentos as caracteristicas de um jogo (nome, nome equipa1, nome equipa2, score1 e score2.)
        -Recebe ainda a hashtable das equipas para fazer a correspondencia das equipas e da vitoria respetiva.
        -Retorna o jogo criado.
*/
Game createGame(char *name, char *name1, char *name2, char *scoret1, char *scoret2, link1* tablet) {

    int index, index2;
    Game game;
    link1 n1;
    link1 n2;

    index = hash(name1);
    index2 = hash(name2);
    n1 = lookupT(tablet[index], name1);
    n2 = lookupT(tablet[index2], name2);

    game = (Game) malloc(sizeof(struct Games));

    game->name = name;

    game->team1 = n1->t;
    game->score1 = scoret1;

    game->team2 = n2->t;
    game->score2 = scoret2;


    if((n1 != NULL) && (n2 != NULL)){
        if(atoi(scoret1) > atoi(scoret2))
            n1->t->counterw +=1;
        else if(atoi(scoret1) < atoi(scoret2))
            n2->t->counterw +=1;
    }

    return game;
}


/* 
    A funcao addTeam:

        -Recebe como argumentos a lista ligada, a hashtable das equipas e um nome de uma equipa.
        -Tem como funcoes auxiliares a createTeam e a insertTeam.
        -Adiciona a equipa criada aos nodes da lista ligada e da hashtable recebidas.
        -Retorna a lista ligada com os nodes adicionados.
        -Retorna erro se:
            -A equipa ja existir.
*/

link1 addTeam(link1 teamsList, link1* tablet){

    char name[MAX_NAME];
    char *team1;
    int index;
    Team team;
    counter +=1;

    scanf(" %[^:\n]", name);
    
    index = hash(name);

    if (lookup(tablet[index], name) != NULL) {  
        printf("%d %s\n", counter, TEAM_EXISTS);
        return teamsList;
    }

    team1 =(char *) malloc(sizeof(char) * strlen(name) + 1);
    strcpy(team1, name);

    team = createTeam(team1);

    tablet[index] = insertTeam(tablet[index], team);
    teamsList = insertTeam(teamsList, team);
    
    return teamsList;

}

/* 
    A funcao createTeam:
        -Recebe como argumento o nome da equipa.
        -Retorna a equipa criada com o contador de vitorias ja a zero.
*/

Team createTeam(char *name) {

    Team team;

    team = (Team) malloc(sizeof(struct Teams));

    team->name = name;
    team->counterw = 0;

    return team;
}

/* 
    A funcao listGames:
        -Trata-se de uma funcao recursiva.
        -Realiza print de uma lista de jogos pela sua ordem de insercao.
        -Tem como auxilio a funcao printGame. 
*/

void listGames(link n) {

    if (n == NULL){
        counter += 1;
        return;
    }

    else{
        listGames(n->next);
        printGame(n->g);
    }
}


/* 
    A funcao listBestTeams:
        -Realiza print de uma lista de equipas alfabeticamente, mas tendo em conta o max de numero de jogos ganhos.
        -Tem como auxilio a funcao countWonGames e a funcao printGame. 
*/
void listBestTeams(link1 n) {


    if(n == NULL){
        counter += 1;
        return;
    }

    else{

        int c;
        link1 t;

        counter +=1;

        c = countWonGames(n);
        
        printf("%d Melhores %d\n", counter, c);

        for(t = n; t != NULL; t = t->next){
            if(t->t->counterw == c){
                printTeam2(t->t);
            }
        }
    }
}



/* 
    A funcao countWonGames:
        -Recebe como argumentos a lista ligada.
        -Retorna o numero maximo de vitorias de jogos das equipas.
*/

int countWonGames(link1 n){

    link1 t;
    int max = 0, lastmax = 0;

    for (t = n ; t != NULL; t = t->next){
        max = t->t->counterw;
        if (max > lastmax)
            lastmax = max;
    }
    return lastmax;
}

/* 
    A funcao searchGame:

        -Recebe como argumentos a hashtable e um nome.
        -Procura o jogo ao qual esta associado o nome.
        -Usa a funcao lookup e a printGame como auxiliar.
        -Imprime o jogo procurado e os seus elementos (nomes das duas equipas e respetivos scores).
        -Retorna erro se:
            -O jogo nao existir.
*/

void searchGame(link *table) {

    char name[MAX_NAME];
    link n;
    int index;
    scanf(" %[^:\n]", name);
    counter += 1;
    
    index = hash(name);
    n = lookup(table[index], name);

    if (n == NULL) {
        printf("%d %s\n",counter, GAME_NOT_EXISTS);
        return;
    }

    printGame(n->g);
}

/* 
    A funcao searchTeam:

        -Recebe como argumentos a hashtable e um nome.
        -Procura a equipa ao qual esta associado o nome.
        -Usa a funcao lookupT e a printTeam como auxiliar.
        -Imprime a equipa procurada e o seu numero de jogos ganhos/vitorias.
        -Retorna erro se:
            -A equipa nao existir.
*/

void searchTeam(link1 *tablet){

    char name[MAX_TEAM];
    int index;
    link1 n;
    scanf(" %[^:\n]", name);
    counter += 1;

    index = hash(name);
    n = lookupT(tablet[index], name);

    if (n == NULL) {
        printf("%d %s\n",counter, TEAM_NOT_EXISTS);
        return;
    }

    printTeam(n->t);

}


/* 
    A funcao printGame:
    -Realiza print de um jogo com todas as suas caracteristicas. 
*/
void printGame(Game g) {

    printf("%d %s %s %s %s %s\n", counter, g->name, g->team1->name, g->team2->name, g->score1, g->score2);
}

/* 
    A funcao printTeam:
    -Realiza print de uma equipa com todas as suas caracteristicas. 
*/
void printTeam(Team t) {

    printf("%d %s %d\n", counter, t->name, t->counterw);
}

/* 
    A funcao printTeam2:
    -Realiza print de uma equipa mas apenas o seu nome.
*/
void printTeam2(Team t) {

    printf("%d * %s\n", counter, t->name);

}


/* 
    A funcao deleteGame:

        -Recebe como argumentos a lista ligada e a hashtable.
        -Apaga o jogo ao qual esta associado o nome.
        -Usa a funcao delete como auxiliar.
        -Retorna erro se:
            -O jogo nao existir.
*/

link deleteGame(link linkedList, link* table) {
    
    link n;
    char name[MAX_NAME];
    int index;
    counter += 1;
    scanf(" %[^:\n]", name);
    index = hash(name);

    n = lookup(table[index], name);

    if( n == NULL) {

        printf("%d %s\n", counter, GAME_NOT_EXISTS);
        return linkedList;
    }

    if(atoi(n->g->score1) > atoi(n->g->score2)){
        n->g->team1->counterw -= 1;
    }

    if(atoi(n->g->score1) < atoi(n->g->score2)){
        n->g->team2->counterw -= 1;
    }


    linkedList = delete(linkedList, name, 0);
    table[index] = delete(table[index], name, 1);

    return linkedList;
}

/* 
    A funcao delete:

        -Recebe como argumentos o primeiro node (head), um nome e um inteiro.
        -Tem como funcao auxiliar a freeNode.
        -Jogo encontrado:
            -Se freesGame = 1, liberta o node e todos os seus componentes dentro do jogo.
            -Se freesGame = 0, liberta apenas o node em si.
            -Retorna o node head.
        -Jogo nao encontrado:
            -Retorna NULL.
*/

link delete(link head, const char* name, int freesGame) {

    link t, prev = NULL;
    
    for(t = head, prev = NULL; t != NULL; prev = t , t = t->next) 
        if(strcmp(t->g->name, name) == 0) {
            
            if(t == head)
                head = head->next;
            else 
                prev->next = t->next;

            if (freesGame)
                freeNode(t, 1);
            else
                free(t);
            return head;
        }
        
    return NULL;
}

/* 
    A funcao editGameScore:

        -Recebe como argumentos a hashtable, um nome do jogo e dois scores.
        -Altera os scores no jogo ao qual esta associado o nome.
        -Ainda tem atencao a alteracao das vitorias das equipas dependendo dos novos scores recebidos.
        -Retorna erro se:
            -O nome recebido nao existir.
*/

void editGameScore(link *table) {

    char name[MAX_NAME];
    char score1[MAX_SCORE];
    char score2[MAX_SCORE];
    char *scoret1, *scoret2;
    int index;
    link n;

    counter += 1;
    
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]", name, score1, score2);

    index = hash(name);
    n = lookup(table[index], name);

    if(n == NULL) {  
        printf("%d %s\n", counter, GAME_NOT_EXISTS);
        return;
    }

    if(atoi(n->g->score1) > atoi(n->g->score2)){
        n->g->team1->counterw--;
    }

    if(atoi(n->g->score2) > atoi(n->g->score1)){
        n->g->team2->counterw--;
    }

 
    scoret1 = (char *) malloc(sizeof(char) * strlen(score1) + 1);;
    strcpy(scoret1, score1);

    scoret2 = (char *) malloc(sizeof(char) * strlen(score2) + 1);;
    strcpy(scoret2, score2);


    n->g->score1 = realloc(n->g->score1, sizeof(char) * strlen(scoret1) + 1);
    strcpy(n->g->score1, scoret1);

    n->g->score2 = realloc(n->g->score2, sizeof(char) * strlen(scoret2) + 1);
    strcpy(n->g->score2, scoret2);

    if(atoi(n->g->score1) > atoi(n->g->score2)){
       n->g->team1->counterw++;
    }

    else if(atoi(n->g->score2) > atoi(n->g->score1)){
        n->g->team2->counterw++;
    }
    
    free(scoret1);
    free(scoret2);
}

/* 
    A funcao hash:

        -Trata-se de uma funcao de dispersao.
        -Gera um inteiro a partir de uma soma ponderada de caracteres.
*/

int hash(const char *v) {

    int h, a = 127;
    
    for (h = 0; *v != '\0'; v++)
        h = (a * h + *v) % TABLE_SIZE;
    
    return h;
}


/* 
    As funcoes insert e insertTeam:

        -Recebem como argumentos o primeiro node (head) e um jogo/equipa (dependendo da funcao).
        -Criam um novo node e inserem este no inicio da lista ligada.
            -Quanto a insertTeam ainda tenta inserir o node de forma a que fique por ordem alfabetica. (nao concluido totalmente)
        -Retornam o node head.
*/

link insert(link head, Game g) { /*jogo*/
    
    link newNode = (link) malloc(sizeof(struct node));
    newNode->g = g;
    newNode->next = head;

    return newNode;
}

link1 insertTeam(link1 head, Team t) { /*equipa*/
    
    link1 n;
    link1 temp;
    link1 newNode1 = (link1) malloc(sizeof(struct node1));

    newNode1->t = t;

    if(head == NULL){
        newNode1->next = NULL;
        return newNode1;
    }

    else{

        if(head->next == NULL){
            if((strcmp(head->t->name, t->name) < 0)){
                head->next = newNode1;
                newNode1->next = NULL;
                return head;  
            }
            else{
                head->next = NULL;
                newNode1->next = head;
                head = newNode1;
                return head;
            }
        }

        for(n = head ; n->next != NULL; n = n->next){

            if(strcmp(n->t->name, t->name) > 0){
                temp = n;
                n = newNode1;
                newNode1->next = temp;
                if(n->next == head){
                    head = newNode1;
                }
                return head;
            }

            else if((strcmp(n->t->name, t->name) < 0) && (strcmp(n->next->t->name, t->name) > 0)){
                temp = n->next;
                n->next = newNode1;
                newNode1->next = temp;
                return head;
            }
        }
        
        n->next = newNode1;
        newNode1->next = NULL;
        return head;
    }
    
}

/* 
    As funcoes de lookup e lookupT:

        -Recebem como argumentos o primeiro node (head) e um nome.
        -Devolve, o node se o jogo/equipa com o nome existir.
        -Caso contrario, retorna NULL.
*/

link lookup(link head, const char* name) {  /*jogo*/
    
    link t;

    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->g->name, name) == 0)
            return t;
    return NULL;
}

link1 lookupT(link1 head, const char* name) { /*equipa*/
      
    link1 t;

    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->t->name, name) == 0)
            return t;
    return NULL;
}


/* 
    A funcao sortFrees:
    
        -Recebe como argumentos a lista ligada e a hashtable.
        -Chama as funcoes freeTable e freeList para libertar os argumentos.
*/

void sortFrees(link linkedList, link* table, link1 teamsList, link1* tablet){
  
    freeTable(table);
    freeList(linkedList, 1);
    freeTableT(tablet);
    freeListT(teamsList, 1);

}


/* 
    As funcoes freeTable e freeTableT:
        - Libertam cada lista ligada da respetiva hashtable e de seguida a hashtable em si.
*/

void freeTable(link *table) {

    int i;
    for (i = 0; i < TABLE_SIZE; i++) 
        freeList(table[i], 0);

    free(table);
}

void freeTableT(link1 *tablet) {

    int i;
    for (i = 0; i < TABLE_SIZE; i++) 
        freeListT(tablet[i], 0);

    free(tablet);
}


/* 
    As funcoes freeList e freeListT:
        -Recebem como argumentos um node e ainda um inteiro com valor 1 ou 0.
        -Trata-se de uma funcao recursiva que percorre a lista ligada e ao chegar ao fim, 
        comeca a libertar os nodes por ordem de insercao.
        -Se g/t = 1, esta funcao foi chamada pela funcao sortFrees.
        -Se g/t = 0. esta funcao foi chamada pela funcao freeTable.
        -Serve apenas para nao se libertar 2x o mesmo jogo e/ou equipa.
*/

void freeList(link n, int g) {

    if (n == NULL)
        return;

    freeList(n->next, g);
    freeNode(n, g);
}

void freeListT(link1 n, int t) {

    if (n == NULL)
        return;

    freeListT(n->next, t);
    freeNodeT(n, t);
}


/* 
    As funcoes freeNode e freeNodeT :
        -Recebem como argumentos um node e ainda um inteiro com valor 1 ou 0.
        -Se g/t1 = 1, liberta o node e todos os seus componentes dentro do jogo / equipa.
        -Se g/t1 = 0, liberta apenas o node em si.
*/
void freeNode(link t, int g) {

    if (g) {

        free(t->g->score2);
        free(t->g->score1);
        free(t->g->name);
        free(t->g);
    }

    free(t);

}

void freeNodeT(link1 t, int t1) {

    if (t1) {

        free(t->t->name);
        free(t->t);
    }

    free(t);

}