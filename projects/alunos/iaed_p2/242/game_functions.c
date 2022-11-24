#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "team_functions.h"
#include "game_functions.h"

/****************************************************************************************/
/*	Recebe como argumento a hashtable dos jogos e percorre a tabela inteira             */
/*  inicializando tudo a NULL.                                                          */
/****************************************************************************************/
void init_hash_table_game(game** hash_table_game){
    int i;
    for(i = 0; i < TABLE_SIZE; i++){
        hash_table_game[i] = NULL;
    }
}


/****************************************************************************************/
/*	Aloca memoria para um novo jogo, recebe como argumento os parametros da estrutura.  */
/*  Devolve o ponteiro para o jogo criado.                                              */
/****************************************************************************************/
game* new_game(char* n_name, char* n_t1, char* n_t2, int n_g_t1, int n_g_t2){
    game* x = can_fail_malloc(sizeof(struct stru_game));
    x -> name = can_fail_malloc(sizeof(char)*strlen(n_name)+1);
    x -> t1 = can_fail_malloc(sizeof(char)*strlen(n_t1)+1);
    x -> t2 = can_fail_malloc(sizeof(char)*strlen(n_t2)+1);
    strcpy(x -> name, n_name);
    strcpy(x -> t1, n_t1);
    strcpy(x -> t2, n_t2);
    x -> g_t1 = n_g_t1;
    x -> g_t2 = n_g_t2;
    x -> next = NULL;
    return x;
}


/**************************************************************************************************/
/*	Recebe como argumento a cabeca da lista ligada e todos os parametros da struct game.          */
/*  Aloca a memoria necessaria atraves da funcao new_game e insere o novo jogo no inicio da lista,*/
/*  atualizando as cabecas e devolve o ponteiro para a nova cabeca.                               */
/**************************************************************************************************/
game* insertBeginList_game(game* head, char* name, char* t1, char* t2, int g_t1, int g_t2){
    game* x;
    x = new_game(name, t1, t2, g_t1, g_t2);
    x -> next = head;
    return x;
}


/**************************************************************************************************/
/*	Recebe como argumento ponteiro para a cabeca nodeGame(cabeca da lista de ponteiros            */
/*  de ponteiros de jogos), e o ponteiro para o jogo que se pretende inserir. O novo jogo e       */
/*  adicionado no inicio da lista, atualiza o prev e o next da nova cabeca.                       */
/*  (esta lista e utilizada no cmd_l)                                                             */
/**************************************************************************************************/
void insert_node(nodeGame** game_order, game* n_game){
    nodeGame* new_node = (nodeGame*)can_fail_malloc(sizeof(nodeGame)); 
  
    new_node->Game = n_game; 
  
    new_node->next = *game_order; 
    new_node->prev = NULL; 
  
    if (*game_order != NULL){
        (*game_order)->prev = new_node; 
    }
  
    *game_order = new_node; 
}


/************************************************************************************************/
/*	Recebe como argumento os parametros da struct game, a hashtable de jogos e o ponteiro       */
/*  da cabeca da lista de nodeGame. Atraves do nome do jogo e da funcao hash calcula o indice,  */ 
/*  por fim insere a equipa na hashtable com a funcao insertBeginList_game e tambem na lista de */
/*  ponteiros nodeGame com a funcao insert_node.                                                */
/************************************************************************************************/
void HTinsert_game(char* name, char* t1, char* t2, int g_t1, int g_t2, game** hash_table_game,
 nodeGame** game_order){
    int index;
    index = hash(name);
    hash_table_game[index] = insertBeginList_game(hash_table_game[index], name, t1, t2, g_t1, g_t2);
    insert_node(game_order, hash_table_game[index]);
}


/****************************************************************************************/
/*	Recebe como argumento o nome do jogo e a hastable dos jogos, e verifica se existe   */
/*  o jogo com o dado nome na hashtable, se existir devolve o ponteiro para o jogo, caso*/
/*  contrario devolve o ponteiro a NULL.                                                */
/****************************************************************************************/
game* hash_table_lookup_game(char* name, game** hash_table_game){
    int index = hash(name);
    game *tmp = hash_table_game[index];
    while(tmp && strcmp(tmp -> name, name) != 0){
        tmp = tmp -> next;
    }
    return tmp;
}


/*************************************************************************************************/
/* Funcao que recebe os parametros da struct game, a hashtable de jogos, a hashtable das equipas */
/* e a lista de nodeGame. Depois de verificar que tanto o jogo como as duas equipas do jogo      */
/* existem(atraves das funcoes hash_table_lookup_game e team, se o jogo nao existir e as equipas */
/* existirem, e chamada a funcao HTinsert_game, para inserir o jogo na hashtable e atualizar     */
/* a lista de ponteiro.                                                                          */
/*************************************************************************************************/
void cmd_a(char* name, char* t1, char* t2, int g_t1, int g_t2, int NL, game** H_T_game, 
team** H_T_team, nodeGame** game_order){
    team* aux;
    if(hash_table_lookup_game(name, H_T_game)){
        printf("%d Jogo existente.\n", NL);
    }
    else if(!(hash_table_lookup_team(t1, H_T_team) && hash_table_lookup_team(t2, H_T_team))){
        printf("%d Equipa inexistente.\n", NL);
    }
    else{
        HTinsert_game(name, t1, t2, g_t1, g_t2, H_T_game, game_order);
        if(g_t1 > g_t2){
            aux = hash_table_lookup_team(t1, H_T_team);
            aux->wins++;
        }
        else if(g_t1 < g_t2){
            aux = hash_table_lookup_team(t2, H_T_team);
            aux->wins++;
        }
    }
}


/*****************************************************************************************/
/*	Recebe como argumento o nome do jogo e hashtable dos jogos, verifica se o jogo       */
/*  existe atraves da funcao hash_table_lookup_game, se existir da print do nome do jogo,*/
/*  dos nomes das equipas e os respetivos golos, caso contrario print "Jogo inexistente."*/
/*****************************************************************************************/
void cmd_p(char* g, int NL, game** hash_table_game){
    if(hash_table_lookup_game(g, hash_table_game) != NULL){
        game* tmp = hash_table_lookup_game(g, hash_table_game);
        printf("%d %s %s %s %d %d\n", NL, tmp->name, tmp->t1, tmp->t2, tmp->g_t1, tmp->g_t2);
    }
    else{
        printf("%d Jogo inexistente.\n", NL);
    }
}


/*****************************************************************************************/
/*	Recebe como argumento a cabeca da lista de ponteiros nodeGame, que contem ponteiros  */
/*  para todos os jogos inseridos, percorre a lista e vai dando print do nome de cada    */
/*  jogo, das duas equipas e dos seus respetivos golos.                                  */
/*****************************************************************************************/
void cmd_l(nodeGame* game_order, int NL){
    nodeGame* aux;
    aux = game_order;
    while(aux != NULL){
        printf("%d %s %s %s %d %d\n", NL, aux->Game->name, aux->Game->t1, aux->Game->t2, 
        aux->Game->g_t1, aux->Game->g_t2);
        aux = aux->next;
    }
}


/*************************************************************************************************/
/*	Recebe como argumento a hashtable dos jogos e a das equipas, o nome do jogo e o              */
/*  novo resultado. Se o jogo existir, compara o resultado novo com o antigo e muda o numero de  */
/*  vitorias no caso do resultado afetar as vitorias de alguma equipas depois da mudanca.        */
/*************************************************************************************************/
void cmd_s(team** hash_table_team, game** hash_table_game, char* name, int g_t1, int g_t2, int NL){
    team* tmp_t;
    game* tmp_g;
    tmp_g = hash_table_lookup_game(name, hash_table_game);
    if(tmp_g != NULL){
        if(tmp_g->g_t1 > tmp_g->g_t2){
            if(g_t1 == g_t2){
                tmp_t = hash_table_lookup_team(tmp_g->t1, hash_table_team);
                tmp_t->wins--;
            }
            else if(g_t1 < g_t2){
                tmp_t = hash_table_lookup_team(tmp_g->t1, hash_table_team);
                tmp_t->wins--;
                tmp_t = hash_table_lookup_team(tmp_g->t2, hash_table_team);
                tmp_t->wins++;
            }
        }
        else if(tmp_g->g_t1 == tmp_g->g_t2){
            if(g_t1 > g_t2){
                tmp_t = hash_table_lookup_team(tmp_g->t1, hash_table_team);
                tmp_t->wins++;
            }
            else if(g_t1 < g_t2){
                tmp_t = hash_table_lookup_team(tmp_g->t2, hash_table_team);
                tmp_t->wins++;
            }
        }
        else if(tmp_g->g_t1 < tmp_g->g_t2){
            if(g_t1 > g_t2){
                tmp_t = hash_table_lookup_team(tmp_g->t1, hash_table_team);
                tmp_t->wins++;
                tmp_t = hash_table_lookup_team(tmp_g->t2, hash_table_team);
                tmp_t->wins--;
            }
            else if(g_t1 == g_t2){
                tmp_t = hash_table_lookup_team(tmp_g->t2, hash_table_team);
                tmp_t->wins--;
            }
        }
        tmp_g->g_t1 = g_t1;
        tmp_g->g_t2 = g_t2;
    }
    else{
        printf("%d Jogo inexistente.\n", NL);
    }
}


/****************************************************************************************/
/*	Recebe como argumento um ponteiro para um jogo, e liberta o ponteiro.               */
/****************************************************************************************/
void FREEnode_game(game* t){
    free(t->name);
    free(t->t1);
    free(t->t2);
    free(t);
}


/****************************************************************************************/
/*	Recebe como argumento a cabeca de uma lista de jogos.                               */
/*  atualiza a cabeca pelo proximo elemento na lista, liberta a memoria da primeira     */
/*  e devolve a cabeca atualizada.                                                      */
/****************************************************************************************/
game* pop_game(game* head){
    game* aux;
    aux = head;
    head = aux->next;
    FREEnode_game(aux);
    return head;
}


/****************************************************************************************/
/*	Recebe como argumento a hashtable dos jogos, percorre a hashtable inteira           */
/*  e liberta todos os elementos atraves da funcao pop_game.                            */
/****************************************************************************************/
void destroy_games(game** hash_table_game){
    int i;
    for(i = 0; i < TABLE_SIZE; i++){
        while(hash_table_game[i] != NULL){
            hash_table_game[i] = pop_game(hash_table_game[i]);
        }
    }
}


/****************************************************************************************/
/*	Recebe como argumento a cabeca da lista de ponteiros de jogos.                      */
/*  atualiza a cabeca pelo proximo elemento na lista, liberta a memoria da primeira     */
/*  e devolve a cabeca atualizada.                                                      */
/****************************************************************************************/
nodeGame* pop_node(nodeGame* head){
    nodeGame* aux;
    aux = head;
    head = aux->next;
    free(aux);
    return head;
}


/****************************************************************************************/
/*	Recebe como argumento a lista dos ponteiros dos jogos, percorre a lista             */
/*  e liberta todos os elementos atraves da funcao pop_node.                            */
/****************************************************************************************/
void destroy_order(nodeGame** game_order){
    while(*game_order != NULL){
        *game_order = pop_node(*game_order);
    }
}


/****************************************************************************************/
/*	Recebe como argumento o nome do jogo e a cabeca da lista onde se encontra           */
/*  esse jogo (na hashtable), percorre a lista e quando encontrar o jogo, atraves       */
/*  da funcao FREEnode_game liberta a memoria do ponteiro, devolvendo a cabeca.         */
/****************************************************************************************/
game* delete_1game(game* head, char* name){
    game* t;
    game* prev;
    for(t = head, prev = NULL; t != NULL; prev = t, t = t->next){
        if(strcmp(t->name, name) == 0){
            if(t == head){
                head = t->next;
            }
            else{
                prev->next = t->next;
            }
            FREEnode_game(t);
            return head;
        }
    }
    return head;
}


/****************************************************************************************/
/* Recebe como argumento a lista de ponteiros de nodeGame, e o nome do jogo que se      */
/* pretende remover, percorre a lista e quando encontrar o ponteiro para o jogo,        */
/* liberta o ponteiro.                                                                  */
/****************************************************************************************/
void delete_node(nodeGame** game_order, char* txt){
    nodeGame* t;
    for(t = *game_order; t != NULL; t = t->next){
        if(strcmp(t->Game->name, txt) == 0){
            if(t == *game_order){
                *game_order = t->next;
            }
            if(t->next != NULL){
                t->next->prev = t->prev;
            }
            if(t->prev != NULL){
                t->prev->next = t->next;
            }
            free(t);
            return;
        } 
    }
    return;
}


/****************************************************************************************/
/* Recebe como argumento a lista de ponteiros nodeGame, e inverte a sua ordem.          */
/****************************************************************************************/
void reverse(nodeGame** list){
    nodeGame *temp = NULL;   
    nodeGame *current = *list; 
    while (current !=  NULL){ 
       temp = current->prev; 
       current->prev = current->next; 
       current->next = temp;               
       current = current->prev; 
    }       
    if(temp != NULL){ 
        *list = temp->prev; 
    }
}


/*****************************************************************************************/
/* Recebe como argumento a hashtable de jogos, hashtable de equipas, a lista de ponteiros*/
/* nodeGame e o nome do jogo que se pretende remover, se esse jogo existir na hashtable  */
/* modifica o numero de vitorias das duas equipas se for necessario, e remove o jogo     */
/* da hashtable e o ponteiro nodeGame que aponta para esse jogo da lista                 */
/*****************************************************************************************/
void cmd_r(team** H_T_team, game** H_T_game, char* name, int NL, nodeGame** game_order){
    team* tmp_t;
    game* tmp_g;
    int index;
    tmp_g = hash_table_lookup_game(name, H_T_game);
    if(tmp_g != NULL){
        if(tmp_g->g_t1 > tmp_g->g_t2){
            tmp_t = hash_table_lookup_team(tmp_g->t1, H_T_team);
            tmp_t->wins--;
        }
        else if(tmp_g->g_t1 < tmp_g->g_t2){
            tmp_t = hash_table_lookup_team(tmp_g->t2, H_T_team);
            tmp_t->wins--;
        }
        index = hash(name);
        delete_node(game_order, name);
        H_T_game[index] = delete_1game(H_T_game[index], name);
        
    }
    else{
        printf("%d Jogo inexistente.\n", NL);
    }
}