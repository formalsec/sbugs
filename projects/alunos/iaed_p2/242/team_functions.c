#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "team_functions.h"
#include "game_functions.h"


/****************************************************************************************/
/*	Recebe como argumento um nome, do jogo ou equipa, e devolve um numero gerado a      */
/*  partir desse nome, que vai ser o indice da tabela.                                  */
/****************************************************************************************/
int hash(char *name){
    int h, a, b;
    a = 31415;
    b = 27183;
    for(h = 0; *name != '\0'; name++, a = a*b %(TABLE_SIZE - 1)){
        h = (a*h + *name) % TABLE_SIZE;
    }
	return h;
}


/****************************************************************************************/
/*	Recebe como argumento a hashtable das equipas e percorre a tabela inteira           */
/*  inicializando tudo a NULL.                                                          */
/****************************************************************************************/
void init_hash_table_team(team** hash_table_team){
    int i;
    for(i = 0; i < TABLE_SIZE; i++){
        hash_table_team[i] = NULL;
    }
}


/****************************************************************************************/
/*	Aloca memoria para uma nova equipa, recebe como argumento o nome e o numero de      */
/*  vitorias da equipa.	Devolve o ponteiro para a equipa criada.                        */
/****************************************************************************************/
team* new_team(char* new_name, int n_wins){
    team* x = can_fail_malloc(sizeof(struct stru_team));
    x -> name = can_fail_malloc(sizeof(char)*strlen(new_name)+1);
    strcpy(x -> name, new_name);
    x -> wins = n_wins;
    x -> next = NULL;
    return x;
}


/****************************************************************************************/
/*	Recebe como argumento a cabeca da lista ligada, o nome da equipa e o numero de      */
/*  vitorias da equipa. Aloca a memoria necessaria atraves da funcao new_team e insere  */
/*  a nova equipa no inicio da lista, atualizando a cabeca e devolve o ponteiro         */
/*  para a nova cabeca.                                                                 */
/****************************************************************************************/
team* insertBeginList_team(team* head, char *t_name, int wins){
    team* x;
    x = new_team(t_name, wins);
    x -> next = head;
    return x;
}


/****************************************************************************************/
/*	Recebe como argumento o nome da equipa e a hashtable das equipas, calcula o indice  */
/*  da hashtable atraves do nome e da funcao hash, por fim insere a nova equipa na lista*/ 
/*  ligada atraves da funcao insertBeginList_team, que devolve a nova cabeca da lista.  */
/****************************************************************************************/
void HTinsert_team(char* t_name, team** hash_table_team){    
    int index;
    index = hash(t_name);
    hash_table_team[index] = insertBeginList_team(hash_table_team[index], t_name, 0);
}


/****************************************************************************************/
/*	Recebe como argumento o nome da equipa e a hastable das equipas, e verifica se      */
/*  existe a equipa com o nome dado na hashtable, se existir devolve o ponteiro para    */
/*  a equipa, caso contrario devolve o ponteiro a NULL.                                 */
/****************************************************************************************/
team* hash_table_lookup_team(char* name, team** hash_table_team){
    int index = hash(name);
    team *tmp = hash_table_team[index];
    while(tmp && strcmp(tmp -> name, name) != 0){
        tmp = tmp -> next;
    }
    return tmp;
}


/****************************************************************************************/
/*  Recebe como argumento o nome da equipa e a hashtable das equipas.                   */
/*	E responsavel por verificar se a equipa que se pretende inserir ja existe,          */
/*  chamando a funcao hash_table_lookup_team, se a equipa existir da print do erro,     */
/*  caso contrario chama a funcao HTinsert_team para inserir a nova equipa na hashtable.*/										                                      
/****************************************************************************************/
void cmd_A(char* t_name, int NL, team** hash_table_team){
    if(hash_table_lookup_team(t_name, hash_table_team) != NULL){
        printf("%d Equipa existente.\n", NL);
    }
    else{
        HTinsert_team(t_name, hash_table_team);
    }
}


/****************************************************************************************/
/*	Recebe como argumento o nome da equipa e a hashtable das equipas, verifica se       */
/*  a equipa existe atraves da funcao hash_table_lookup_team, se existir da print       */
/*  do nome da equipa e do numero de vitorias, caso contrario da print do erro          */
/*  "Equipa inexistente."                                                               */
/****************************************************************************************/
void cmd_P(char* t_name, int NL, team** hash_table_team){
    if(hash_table_lookup_team(t_name, hash_table_team) != NULL){
        team* tmp = hash_table_lookup_team(t_name, hash_table_team);
        printf("%d %s %d\n",NL, tmp->name, tmp->wins);
    }
    else{
        printf("%d Equipa inexistente.\n", NL);
    }
}


/****************************************************************************************/
/*	Recebe como argumento a hashtable das equipas, percorre a tabela a procura do numero*/
/*  maximo de vitorias, e devolve o valor depois de a percorrer.                        */
/****************************************************************************************/
int get_max(team** hash_t){
    int max = 0;
    int i;
    team* tmp;
    for(i = 0; i < TABLE_SIZE; i++){
        tmp = hash_t[i];
        while(tmp != NULL){
            if(tmp->wins > max){
                max = tmp->wins;
            }
        tmp = tmp->next;
        }
    }
    return max;
}


/****************************************************************************************/
/*	Recebe como argumento a cabeca da lista, o nome da equipa e o seu numero de         */
/*  vitorias, e insere ja por ordem alfabetica na lista, devolvendo a cabeca da lista.  */
/****************************************************************************************/
team* insert_alpha(team* head, char *t_name, int wins){
    team* current; 
    team* x;
    x = new_team(t_name, wins);
    if (head == NULL || strcmp(head->name, t_name) > 0){ 
        x->next = head; 
        return x; 
    } 
    else{ 
        current = head; 
        while (current->next!=NULL && strcmp(current->next->name, x->name) < 0){ 
            current = current->next; 
        } 
        x->next = current->next; 
        current->next = x;
        return head; 
    } 
}


/****************************************************************************************/
/*	Recebe como argumento um ponteiro para a cabeca da lista das equipas com numero     */
/*  maximo de vitorias se a lista nao for vazia percorre a lista e da print a todas as  */
/*  equipas, se a lista for vazia, nao faz nada.                                        */
/****************************************************************************************/
void print_max(team** max_teams, int NL){
    team* tmp = *max_teams;
    if(tmp != NULL){
        printf("%d Melhores %d\n", NL, tmp->wins);
        while(tmp != NULL){
            printf("%d * %s\n", NL, tmp -> name);
            tmp = tmp -> next;
        }   
    }
}


/****************************************************************************************/
/*	Recebe como argumento o ponteiro para a cabeca da lista (sempre NULL) e a hashtabla */
/*  das equipas, obtem o numero maximo de vitorias atraves da funcao get_max,           */
/*  de seguida percorre a hashtble e sempre que encontrar uma equipa com o numero de    */
/*  vitorias igual ao valor maximo, insere essa equipa por ordem alfabetica             */
/*  na lista (inicialmente vazia), depois de ter percorrida a hashtable inteira, atraves*/
/*  de print_max, da print as equipas da lista, por fim com a funcao destroy_teams_lst, */
/*  liberta a lista das equipas com o numero maximo de vitorias, deixando a vazia para  */
/*  a proxima vez que cmd_g for chamada.                                                */
/****************************************************************************************/
void cmd_g(team** max_teams, int NL, team** hash_t_team){
    int max = get_max(hash_t_team);
    int i;
    team* tmp;
    for(i = 0; i < TABLE_SIZE; i++){
        tmp = hash_t_team[i];
        while(tmp != NULL){
        if(tmp->wins == max){
            *max_teams = insert_alpha(*max_teams, tmp->name, tmp->wins);
        }
        tmp = tmp->next;
        }
    }
    print_max(max_teams, NL);
    destroy_teams_lst(max_teams);
}


/****************************************************************************************/
/*	Recebe como argumento um ponteiro para uma equipa, e liberta o ponteiro.            */
/****************************************************************************************/
void FREEnode_team(team* t){
    free(t->name);
    free(t);
}


/****************************************************************************************/
/*	Recebe como argumento a cabeca de uma lista de equipas.                             */
/*  atualiza a cabeca pelo proximo elemento na lista, liberta a memoria da primeira     */
/*  e devolve a cabeca atualizada.                                                      */
/****************************************************************************************/
team* pop_team(team* head){
    team* aux;
    aux = head;
    head = aux->next;
    FREEnode_team(aux);
    return head;
}


/****************************************************************************************/
/*	Recebe como argumento um ponteiro para a cabeca de uma lista de equipas.            */
/*  percorre a lista e atraves da funcao pop_team, liberta a memoria para cada elemento */
/*  da lista.                                                                           */
/****************************************************************************************/
void destroy_teams_lst(team** list_t){
    while(*list_t != NULL){
        *list_t = pop_team(*list_t);
    }
}


/****************************************************************************************/
/*	Recebe como argumento a hashtable das equipas, percorre a hashtable inteira         */
/*  e liberta todos os elementos atraves da funcao pop_team.                            */
/****************************************************************************************/
void destroy_teams(team** hash_table_team){
    int i;
    for(i = 0; i < TABLE_SIZE; i++){
        while(hash_table_team[i] != NULL){
            hash_table_team[i] = pop_team(hash_table_team[i]);
        }
    }
}