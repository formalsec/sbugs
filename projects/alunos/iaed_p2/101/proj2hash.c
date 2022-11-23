#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"
#include "hash_jogos.h"
#include "hash_equipas.h"

#define STRMAX 1024


int main()
{
    Jogo *J, **JHash;

    Jogos *Match_Lst;

    Equipa *E, *E1, *E2, **EHash;

    Equipas *Team_Lst;

    /* Valor maximo inicial da hash table */
    int Init = 7;

    /* JN contem o numero atual de elementos
     e JM o numero maximo da hash de jogos */
    int JN = 0, JM = Init;

    /* EN contem o numero atual de elementos
     e EM o numero maximo da hash de equipas */
    int EN = 0, EM = Init;

    /* Identificador da linha do comando */
    unsigned int NL = 1;

    /* Variaveis auxiliares */
    unsigned int Score1, Score2, Max;

    /* Variaveis auxiliares */
    int i, NEquipas;

    /* Identificador do comando */
    char C;

    /* Vetor de strings auxiliar */
    char **Nomes;

    /* String com tamanho maximo */
    char buffer[STRMAX];

    JHash = JNova_Hash(JM);
    EHash = ENova_Hash(EM);
    Match_Lst = init_jogos();
    Team_Lst = init_equipas();

    do
    {
        C = getchar();
        switch(C) {

            /* Adiciona um novo jogo */
            case 'a':

                /* Criar um novo jogo */
                J = novo_jogo();

                scanf(" %[^:\n]:", buffer);
                J->nome =
                (char*) can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
                strcpy(J->nome, buffer);

                scanf("%[^:\n]:", buffer);
                J->Equipas[0] = 
                (char*) can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
                strcpy(J->Equipas[0], buffer);

                scanf("%[^:\n]:", buffer);
                J->Equipas[1] = 
                (char*) can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
                strcpy(J->Equipas[1], buffer);

                scanf("%u:%u", &J->score[0], &J->score[1]);

                E1 = EProcura_Hash(EHash, J->Equipas[0], EM);
                E2 = EProcura_Hash(EHash, J->Equipas[1], EM);

                /* Erros */
                if (JProcura_Hash(JHash, J->nome, JM) != NULL) {
                    printf("%u Jogo existente.\n", NL++);
                    elimina_jogo(J);
                    continue;
                }
                if (E1 == NULL) {
                    printf("%u Equipa inexistente.\n", NL++);
                    elimina_jogo(J);
                    continue;
                }
                if (E2 == NULL) {
                    printf("%u Equipa inexistente.\n", NL++);
                    elimina_jogo(J);
                    continue;
                }

                /* Atribuir a vitoria 'a equipa vencedora */
                if (J->score[0] > J->score[1])
                    E1->jganhos++;
                
                else if (J->score[0] < J->score[1])
                    E2->jganhos++;
                
                /* Adicionar o jogo 'a hash table */
                JInsere_Hash(JHash, J, JM);

                /* Expande a hash table se estiver 50% ocupada */
                if (++JN > JM/2) {
                    JM = JM + JM;
                    JHash = Jexpande(JHash, JM);
                }

                /* Adicionar o jogo 'a lista de jogos */
                if (Match_Lst->head == NULL) {
                    Match_Lst->head = J;
                    Match_Lst->last = J;
                }
                else {
                    Match_Lst->last->next = J;
                    J->prev = Match_Lst->last;
                    Match_Lst->last = J;
                }

                ++NL;
                continue;


            /* Lista todos os jogos introduzidos */
            case 'l':

                if (Match_Lst->head != NULL)
                    for (J=Match_Lst->head; J!=NULL; J=J->next)
                        printf("%u %s %s %s %u %u\n",
                         NL, J->nome,
                         J->Equipas[0], J->Equipas[1],
                         J->score[0], J->score[1]);
                ++NL;
                continue;
            

            /* Procura um jogo com o nome dado */
            case 'p':

                scanf(" %[^:\n]", buffer);

                J = JProcura_Hash(JHash, buffer, JM);

                /* Erros */
                if (J == NULL) {
                    printf("%u Jogo inexistente.\n", NL++);
                    continue;
                }
                
                printf("%u %s %s %s %u %u\n",
                         NL, J->nome,
                         J->Equipas[0], J->Equipas[1],
                         J->score[0], J->score[1]);
                ++NL;
                continue;


            /* Apaga um jogo dado um nome */
            case 'r':

                scanf(" %[^:\n]", buffer);

                J = JProcura_Hash(JHash, buffer, JM);

                /* Erros */
                if (J == NULL) {
                    printf("%u Jogo inexistente.\n", NL++);
                    continue;
                }

                /* Retirar a vitoria da equipa vencedora */
                if (J->score[0] > J->score[1]) {
                    E1 = EProcura_Hash(EHash, J->Equipas[0], EM);
                    E1->jganhos--;
                }
                
                else if (J->score[0] < J->score[1]) {
                    E2 = EProcura_Hash(EHash, J->Equipas[1], EM);
                    E2->jganhos--;
                }       
                
                /* Apagar o jogo da hash table */
                JN = JRemove_Hash(JHash, buffer, JM, JN);
                
                /* Apagar o jogo da lista de jogos e da memoria */
                Match_Lst = remove_jogo(Match_Lst, buffer);

                ++NL;
                continue;

            
            /* Altera o score de um jogo dado o nome */
            case 's':

                scanf(" %[^:\n]:", buffer);

                scanf("%u:%u", &Score1, &Score2);

                J = JProcura_Hash(JHash, buffer, JM);

                /* Erros */
                if (J == NULL) {
                    printf("%u Jogo inexistente.\n", NL++);
                    continue;
                }

                /* Retirar a vitoria da equipa vencedora */
                E1 = EProcura_Hash(EHash, J->Equipas[0], EM);
                E2 = EProcura_Hash(EHash, J->Equipas[1], EM);

                if (J->score[0] > J->score[1])
                    E1->jganhos--;
                
                else if (J->score[0] < J->score[1])
                    E2->jganhos--;

                /* Atribuir a nova vitoria */
                if (Score1 > Score2)
                    E1->jganhos++;
                
                else if (Score1 < Score2)
                    E2->jganhos++;

                /* Ajustar o score do jogo */
                J->score[0] = Score1;
                J->score[1] = Score2;

                ++NL;
                continue;


            /* Adiciona uma nova equipa */
            case 'A':

                /* Criar uma nova equipa */
                E = nova_equipa();

                scanf(" %[^:\n]", buffer);
                E->nome =
                (char*) can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
                strcpy(E->nome, buffer);
            
                /* Erros */
                if (EProcura_Hash(EHash, E->nome, EM) != NULL) {
                    printf("%u Equipa existente.\n", NL++);
                    elimina_equipa(E);
                    continue;
                }

                /* Adicionar a equipa 'a hash table */
                EInsere_Hash(EHash, E, EM);

                /* Expande a hash table se estiver 50% ocupada */
                if (++EN > EM/2) {
                    EM = EM + EM;
                    EHash = Eexpande(EHash, EM);
                }

                /* Adicionar a equipa 'a lista */
                if (Team_Lst->head == NULL) {
                    Team_Lst->head = E;
                    Team_Lst->last = E;
                }
                else {
                    Team_Lst->last->next = E;
                    Team_Lst->last = E;
                }

                ++NL;
                continue;

            
            /* Procura uma equipa dado um nome */
            case 'P':

                scanf(" %[^:\n]", buffer);

                E = EProcura_Hash(EHash, buffer, EM);

                /* Erros */
                if (E == NULL) {
                    printf("%u Equipa inexistente.\n", NL++);
                    continue;
                }
                
                printf("%u %s %u\n", NL, E->nome, E->jganhos);
                ++NL;
                continue;


            /* Encontra as equipas que ganharam mais jogos e lista
            por ordem lexicografica (do nome da equipa) */
            case 'g':

                if (EN) {
                /* Encontrar as equipas que ganharam mais jogos */
                    Max = encontra_max(Team_Lst);
                    Nomes = (char**)can_fail_malloc(sizeof(char*)*EN);
                    NEquipas = encontra_melhores(Team_Lst, Max, Nomes);

                /* Ordenar as equipas lexicograficamente */
                    qsort(Nomes, NEquipas, sizeof(char*), compare);
                    
                    printf("%u Melhores %u\n", NL, Max);
                    for(i=0; i<NEquipas; ++i) {
                        printf("%u * %s\n", NL, Nomes[i]);
                    }
                    
                    free(Nomes);
                }
                ++NL;
                continue;
            
        }
    /* Termina o programa */
    }   while (C != 'x');
    
    JDestroi_Hash(JHash, Match_Lst);
    EDestroi_Hash(EHash, Team_Lst);
    free(Team_Lst);
    free(Match_Lst);
    
    return 0;
}
