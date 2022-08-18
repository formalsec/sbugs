#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h" /* atraves deste include, acesso os ficheiros hashtable.h, equipa.h e Jogo.h */
#define Tamanho_HashTable 50051 

int main(){
    char comando, nome[MAXIMO_CARACTERES], equipa_casa[MAXIMO_CARACTERES], equipa_fora[MAXIMO_CARACTERES];                
    int  score_equipa_casa, score_equipa_fora;
    int  NL = 1;                    /* NL representa o numero da linha de input. Vai sendo incrementado a cada comando e podera surgir em output */
    Jogo *HashTable_Jogos = NULL;
    Jogo jogo = NULL;
    Equipa *HashTable_Equipas = NULL;
    Equipa equipa = NULL;
    Lista lista = NULL;
    Lista_Equipas lista_equipas = NULL;
/* Inicializacao das hashtables dos jogos e das equipas */
    HashTable_Jogos = inicializa(Tamanho_HashTable);
    HashTable_Equipas = inicializa_equipas(Tamanho_HashTable);

/* Funcao principal composta por um ciclo constantemente a espera de comandos e executando esses comandos (atraves de funcoes) ate que o comando seja o fim do programa */
    comando = getchar();
    while (comando != 'x'){
        switch(comando){
            case 'a':
                scanf(" %[^:]:%[^:]:%[^:]:%d:%d", nome, equipa_casa, equipa_fora, &score_equipa_casa, &score_equipa_fora);
                if (procura(nome, HashTable_Jogos, Tamanho_HashTable) == NULL){
                    if (verifica_equipas(equipa_casa, equipa_fora, HashTable_Equipas, Tamanho_HashTable) == 0){                
                        jogo = novo_jogo(nome, equipa_casa, equipa_fora, score_equipa_casa, score_equipa_fora);
                        HashTable_Jogos = insere(jogo, HashTable_Jogos, Tamanho_HashTable);
                        lista = insere_lista(lista, jogo);
                        HashTable_Equipas = atribui_vitoria(HashTable_Equipas, jogo -> Equipa_Casa, jogo -> Equipa_Fora, jogo -> Score_Equipa_Casa, jogo -> Score_Equipa_Fora, Tamanho_HashTable);
                    }
                    else{
                        printf("%d Equipa inexistente.\n", NL);
                    }
                }
                else{
                    printf("%d Jogo existente.\n", NL);
                }
                NL += 1;
                break;

            case 'A':
                scanf(" %[^\n]", nome);
                if (equipa_nova(nome, HashTable_Equipas, Tamanho_HashTable) == 0){
                    equipa = nova_equipa(nome);
                    HashTable_Equipas = insere_equipa(equipa, HashTable_Equipas, Tamanho_HashTable);
                    lista_equipas = insere_lista_equipas(lista_equipas, equipa);
                }
                else{
                    printf("%d Equipa existente.\n", NL);
                }
                NL += 1;
                break;
            
            case 'P':
                procura_equipa(HashTable_Equipas, Tamanho_HashTable, NL);
                NL += 1;
                break;

            case 'l':
                print_lista(lista, NL);
                NL += 1;
                break;
                
            case 'p':
                scanf(" %[^\n]" , nome);
                jogo = procura(nome, HashTable_Jogos, Tamanho_HashTable);
                if (jogo != NULL){
                    printf("%d %s %s %s %d %d\n", NL, jogo -> Nome, jogo -> Equipa_Casa, jogo -> Equipa_Fora, jogo -> Score_Equipa_Casa, jogo -> Score_Equipa_Fora);
                }
                else{
                    printf("%d Jogo inexistente.\n", NL);
                }
                NL += 1;
                break;
            
            case 'r':
                scanf(" %[^\n]" , nome);
                jogo = procura(nome, HashTable_Jogos, Tamanho_HashTable);
                if (jogo != NULL){
                    HashTable_Equipas = retira_vitoria(HashTable_Equipas, jogo -> Equipa_Casa, jogo -> Equipa_Fora, jogo -> Score_Equipa_Casa, jogo -> Score_Equipa_Fora, Tamanho_HashTable);
                    lista = apaga_na_lista(lista, nome);
                    HashTable_Jogos = apaga_jogo(HashTable_Jogos, nome, Tamanho_HashTable);
                }
                else{
                    printf("%d Jogo inexistente.\n", NL);
                }
                NL += 1;
                break;
            
            case 's':
                scanf(" %[^:]", nome);
                jogo = procura(nome, HashTable_Jogos, Tamanho_HashTable);
                if (jogo != NULL ){
                    HashTable_Equipas = retira_vitoria(HashTable_Equipas, jogo -> Equipa_Casa, jogo -> Equipa_Fora, jogo -> Score_Equipa_Casa, jogo -> Score_Equipa_Fora, Tamanho_HashTable);
                    HashTable_Jogos = altera_score(nome, HashTable_Jogos, Tamanho_HashTable);
                    HashTable_Equipas = atribui_vitoria(HashTable_Equipas, jogo -> Equipa_Casa, jogo -> Equipa_Fora, jogo -> Score_Equipa_Casa, jogo -> Score_Equipa_Fora, Tamanho_HashTable);
                }
                else{
                    printf("%d Jogo inexistente.\n", NL);
                }
                NL += 1;
                break;

            case 'g':
                print_lista_equipas(lista_equipas, NL);
                NL += 1;
                break;
        }
        comando = getchar();
    }

    /* Libertar a memoria alocada */
    free_equipas(lista_equipas);
    free_jogos(lista);
    free(HashTable_Jogos);
    free(HashTable_Equipas);
    return 0;
}


 /* Projecto realizado no ambito da cadeira de Introducao a Algoritmos e Estrutura de Dados.*/
 /* Instituto Superior Tecnico (Taguspark)*/

/********************************************************FIM***DO***PROJETO*****************************************/