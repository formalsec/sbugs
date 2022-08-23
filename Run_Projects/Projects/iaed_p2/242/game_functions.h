#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

/****************************************/
/*	 Prototipo das funcoes dos jogos	*/
/****************************************/

void init_hash_table_game(game** hash_table_game);
void insert_node(nodeGame** game_order, game* n_game);
void HTinsert_game(char* name, char* t1, char* t2, int g_t1, int g_t2, game** hash_table_game, 
nodeGame** game_order);
void cmd_a(char* name, char* t1, char* t2, int g_t1, int g_t2, int NL, game** H_T_game, 
team** H_T_team, nodeGame** game_order);
void cmd_p(char* g, int NL, game** hash_table_game);
void cmd_l(nodeGame* game_order, int NL);
void cmd_s(team** hash_table_team, game** hash_table_game, char* name, int g_t1, int g_t2, int NL);
void FREEnode_game(game* t);
void destroy_games(game** hash_table_game);
void destroy_order(nodeGame** game_order);
void delete_node(nodeGame** game_order, char* txt);
void reverse(nodeGame** list);
void cmd_r(team** H_T_team, game** H_T_game, char* name, int NL, nodeGame** game_order);
game* new_game(char* n_name, char* n_t1, char* n_t2, int n_g_t1, int n_g_t2);
game* insertBeginList_game(game* head, char* name, char* t1, char* t2, int g_t1, int g_t2);
game* hash_table_lookup_game(char* name, game** hash_table_game);
game* pop_game(game* head);
game* delete_1game(game* head, char* name);
nodeGame* pop_node(nodeGame* head);

#endif