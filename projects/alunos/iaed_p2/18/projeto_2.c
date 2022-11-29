#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "jogos.h"
#include "equipas.h"

void open_files(int argc, char const *argv[]);

int main(int argc, char const *argv[]) {
  int runner = 0, commandNumber = 0;
  Teams *listTeams = NULL;
  Game *listGames = NULL;
  Game *forFree;
  char string[MAX_STRING_SIZE * 4];
  char c;
  open_files(argc, argv);

  while (runner == 0) {
    switch (c = fgetc(inputFile)) {
      /*
      * __a__ - Adiciona um novo jogo.
        * Formato de entrada: `a nome:equipa1:equipa2:score1:score2`
        * Formato de saida: NADA (excepto erro).
        * Erros:
          * `NL Jogo existente.` no caso de ja existir um jogo com esse nome no sistema.
          * `NL Equipa inexistente.` no caso de uma das equipas ou ambas nao existirem no sistema.
      */
      case 'a':
        commandNumber++;
        /*fscanf(inputFile, "%s", string);*/
        fgetc(inputFile);
        fgets(string, MAX_STRING_SIZE * 4, inputFile);
        string[strlen(string) - 1] = '\0';
        prepareGame(&listGames, listTeams, string, commandNumber);
        break;
      /*
      * __l__ - Lista todos os jogos introduzidos.
        * Formato de entrada: `l`
        * Formato de saida: Uma linha por jogo no formato abaixo

              NL nome-jogo nome-equipa1 nome-equipa2 score1 score2

          Os jogos deverao ser listados pela ordem em que foram introduzidos.
          Caso nao exista nenhum jogo no sistema, o comando nao imprime nada.
        * Erros: Nao aplicavel.
      */
      case 'l':
        commandNumber++;
        printGames(listGames, commandNumber);
        break;
      /*
      * __p__ - Procura um jogo com o nome dado.
        * Formato de entrada: `p nome`
        * Formato de saida: Igual ao formato de saida do comando `l` mas apenas com o jogo `nome`.
        * Erros:
          * `NL Jogo inexistente.` no caso de nao existir nenhum jogo com esse nome no sistema.
      */
      case 'p':
      commandNumber++;
      fgetc(inputFile);
      fgets(string, MAX_STRING_SIZE, inputFile);
      string[strlen(string) - 1] = '\0';
      /*fscanf(inputFile, "%s", string);*/
      searchGame(listGames, string, commandNumber);
      break;
    /*
    * __r__ - Apaga um jogo dado um nome.
      * Formato de entrada: `r nome`
      * Formato de saida: NADA (excepto erro).
      * Erros:
        * `NL Jogo inexistente.` no caso de nao existir nenhum jogo com esse nome no sistema.
    */
    case 'r':
      commandNumber++;
      fgetc(inputFile);
      fgets(string, MAX_STRING_SIZE, inputFile);
      string[strlen(string) - 1] = '\0';
      /*fscanf(inputFile, "%s", string);*/
      listGames = removeGame(listGames, listTeams, string, commandNumber);
      break;
    /*
    * __s__ - Altera o score de um jogo dado o nome.
      * Formato de entrada: `s nome:score1:score2`
      * Formato de saida: NADA (excepto erro).
      * Erros:
        * `NL Jogo inexistente.` no caso de nao existir nenhum jogo com esse nome no sistema.
    */
    case 's':
      commandNumber++;
      fgetc(inputFile);
      fgets(string, MAX_STRING_SIZE, inputFile);
      string[strlen(string) - 1] = '\0';
      /*fscanf(inputFile, "%s", string);*/
      changeScore(listGames, listTeams, string, commandNumber);
      break;
    /*
    * __A__ - Adiciona uma nova equipa.
      * Formato de entrada: `A nome`
      * Formato de saida: NADA (excepto erro).
      * Erros:
        * `NL Equipa existente.` no caso de ja existir uma equipa com esse nome no sistema.
    */
    case 'A':
      commandNumber++;
      fgetc(inputFile);
      fgets(string, MAX_STRING_SIZE, inputFile);
      string[strlen(string) - 1] = '\0';
      /*fscanf(inputFile, "%s", string);*/
      if(listTeams == NULL){
        listTeams = createTeams(string);
      }
      else if(addTeam(string, listTeams) == 0){
        fprintf(outputFile ,"%d Equipa existente.\n", commandNumber);
      }
      break;
    /*
    * __P__ - Procura uma equipa dado um nome.
      * Formato de entrada: `P nome`
      * Formato de saida: `NL nome numero-de-jogos-ganhos`.
      * Erros:
        * `NL Equipa inexistente.` no caso de nao existir nenhuma equipa com esse nome no sistema.
    */
    case 'P':
      commandNumber++;
      fgetc(inputFile);
      fgets(string, MAX_STRING_SIZE, inputFile);
      string[strlen(string) - 1] = '\0';
      /*fscanf(inputFile, "%s", string);*/
      printTeam(listTeams, string, commandNumber);
      break;
    /*
    * __g__ - Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica (do nome da equipa).
      * Formato de entrada: `g`
      * Formato de saida:

            NL Melhores numero-de-jogos-ganhos
            NL * nome-equipa1
            NL * nome-equipa2
            NL * nome-equipa3
            ...
        Caso nao exista nenhuma equipa, o comando nao imprime nada (nem a palavra `Melhores`).
      * Erros: Nao aplicavel.
    */
    case 'g':
      commandNumber++;
      printBest(listTeams, commandNumber);
      break;
    case 'x':
      runner = 1;
      break;
    }
    string[0] = '\0';
  }
  freeTeams(listTeams);
  if (listGames != NULL){
    while (listGames->nextGame != NULL) {
      forFree = listGames;
      listGames = forFree->nextGame;
      freeGame(forFree);
    }
    if (listGames != NULL){
      freeGame(listGames);
    }
  }
  fclose(outputFile);
  fclose(inputFile);
  return 0;
}

/*
If there is an input and output file used as argument, initialise them here, otherwise,
inicialise the input as stdin and the output as stdout
*/

void open_files(int argc, char const *argv[]){
  if(argc > 1 && argc < 4){
    inputFile = fopen(argv[1], "r");
    if(argc == 3){
      outputFile = fopen(argv[2], "w");
    }
    else{
      outputFile = stdout;
    }
  }
  else{
    inputFile = stdin;
    outputFile = stdout;
  }
  if(!inputFile || !outputFile){
    perror("Couldn't open files");
    exit(EXIT_FAILURE);
  }
}
