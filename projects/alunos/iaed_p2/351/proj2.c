#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "proj2.h"

int main()
{
    /* initialize the hash tables and lists needed */
    hash_table *ht_teams, *ht_games;
    l_list *l_teams,*l_games;
    l_ht_info *info = can_fail_calloc(1,sizeof(l_ht_info));
    ht_teams = create_ht();
    ht_games = create_ht();
    l_teams = create_l_list();
    l_games = create_l_list();
    srand(time(NULL)); /* seed RNG */
    /* initialize the l_ht_info struct */
    info -> ht_teams = ht_teams;
    info -> ht_games = ht_games;
    info -> l_teams = l_teams;
    info -> l_games = l_games;
    /* process commands from stdio */
    commands_loop(info);
    /* free all created pointers */
    free_l_list(l_teams,&free_team);
    free_l_list(l_games,&free_game);
    ht_delete_ht(ht_games);
    ht_delete_ht(ht_teams);
    free(info);

    return 0;
}

/* function to free team structs*/
void free_team(void *ptr)
{
    team *p_team = (team*)ptr;
    free(p_team->name);
    free(p_team);
}


/* function to free game structs*/
void free_game(void *ptr)
{
    game *p_game = (game*)ptr;
    free(p_game->name);
    free(p_game->team1);
    free(p_game->team2);
    free(p_game);
}

/* will process stdio for commands and executes
   the given program function */
int commands_loop(l_ht_info *info)
{
    /* used for debugging which input line gave which output */
    int cmd_counter = 1;
    char io_buffer[IBUFFER_SIZE];
    char cmd = '\0';
    /* command has to break the loop */
    while(TRUE)
    {
        fgets(io_buffer,IBUFFER_SIZE,stdin);/* extract line from stdin into io_buffer */
        /* get first char from the line, to compare with recognized commands */
        if(sscanf(io_buffer,"%c",&cmd)) /* only proceed if cmd got successfully filled*/
        {
            switch(cmd) /* compare cmd with known commands */
            {
                case 'a': add_game_proc(io_buffer,info,cmd_counter);break;
                case 'A': add_team_proc(io_buffer,info,cmd_counter);break;
                case 'l': list_games_proc(info,cmd_counter);break;
                case 'p': search_game_proc(io_buffer,info,cmd_counter);break;
                case 'P': search_team_proc(io_buffer,info,cmd_counter);break;
                case 'r': delete_game_proc(io_buffer,info,cmd_counter);break;
                case 's': change_game_score_proc(io_buffer,info,cmd_counter);break;
                case 'g': teams_most_wins_proc(info,cmd_counter);break;
                case 'x': return 0;
            }
            cmd_counter++;
        }
    }
}

/* if possible, adds a new game to l_ht_info */
int add_game_proc(char *io_buffer, l_ht_info *info, int cmd_ctr)
{
    char name[MAX_NAME_SIZE],tm1[MAX_NAME_SIZE],tm2[MAX_NAME_SIZE];
    int score1 = 0,score2 = 0;
    game *p_game;
    team *p_team1,*p_team2;
    sscanf(io_buffer,"%*c %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",name,tm1,tm2,&score1,&score2);
    /* error detection  ifs */
    if(search_game_by_name(name,info,&p_game))
    {
        printf("%d Jogo existente.\n",cmd_ctr);
        return FALSE;
    }
    if(!search_team_by_name(tm1,info,&p_team1))
    {
        printf("%d Equipa inexistente.\n",cmd_ctr);
        return FALSE;
    }
    if(!search_team_by_name(tm2,info,&p_team2))
    {
        printf("%d Equipa inexistente.\n",cmd_ctr);
        return FALSE;
    }
    /* -------------------- */
    if(score1>score2)p_team1->games_won++;
    if(score1<score2)p_team2->games_won++;
    add_game(info,name,tm1,tm2,score1,score2);
    return TRUE;
}

/* adds a new game to l_ht_info, to both the hash table and list */
void add_game(l_ht_info *info,char *name,char *tm1, char *tm2,int score1, int score2)
{
    char *p_name,*p_tm1,*p_tm2;
    int len;
    ulong key = ht_key_from_str(name); /* obtain key for the given name */
    ht_node *p_ht_node = create_ht_node();
    l_node *p_l_node = create_l_node();
    game *p_game = can_fail_malloc(sizeof(game));
    /* allocates just enough space for the strings, and copies them over */
    len = strlen(name);
    p_name = can_fail_malloc(sizeof(char)* (len +1));
    strcpy(p_name,name);
    len = strlen(tm1);
    p_tm1 = can_fail_malloc(sizeof(char)* (len +1));
    strcpy(p_tm1,tm1);
    len = strlen(tm2);
    p_tm2 = can_fail_malloc(sizeof(char)* (len +1));
    strcpy(p_tm2,tm2);
    /* set the values of the game struct,and add the game struct to both
       the hash table and the linked list */
    p_game->name = p_name; p_game->team1 = p_tm1; p_game->team2 = p_tm2;
    p_game->score1 = score1; p_game->score2 = score2;
    p_l_node->info_struct = p_game;
    p_ht_node->info_struct = p_l_node; /* hash table contains pointer to list element */
    l_list_add_node_end(info->l_games,p_l_node);
    ht_insert_node(info->ht_games,p_ht_node,key);
    return;
}

/* if possible, adds a new team to l_ht_info */
int add_team_proc(char *io_buffer, l_ht_info *info, int cmd_ctr)
{
    char name[MAX_NAME_SIZE];
    team *p_team;
    sscanf(io_buffer,"%*c %[^:\n]",name);
    if(search_team_by_name(name,info,&p_team))
    {
        printf("%d Equipa existente.\n",cmd_ctr);
        return FALSE;
    }
    add_team(info,name);
    return TRUE;
}

/* adds a new team to l_ht_info, to both the hash table and list */
void add_team(l_ht_info *info,char *name)
{
    char *p_name;
    int len;
    ulong key = ht_key_from_str(name); /* obtain key for the given name */
    ht_node *p_ht_node = create_ht_node();
    l_node *p_l_node = create_l_node();
    team *p_team = can_fail_calloc(1,sizeof(team));
    /* allocates just enough space for the strings, and copies them over */
    len = strlen(name);
    p_name = can_fail_malloc(sizeof(char)* (len +1));
    strcpy(p_name,name);
    *(p_name+len) = '\0';
    /* set the values of the game struct, update ht_nodes info_struct ptr
       and finally insert the node in the hash table */
    p_team->name = p_name;
    p_team->games_won = 0;
    p_l_node->info_struct = p_team;
    p_ht_node->info_struct = p_l_node;
    l_list_add_node_end(info->l_teams,p_l_node);
    ht_insert_node(info->ht_teams,p_ht_node,key);
    return;
}

/* lists in stdio all current games in the order they were inserted */
int list_games_proc(l_ht_info *info, int cmd_ctr)
{
    l_list *l_games = info->l_games;
    l_node *p_l_node = l_games->head;
    game *p_game;
    int scr1,scr2;
    /* iterate all the games in the list and print their info to stdio */
    for(;p_l_node!=NULL;p_l_node = p_l_node->next)
    {
        p_game = ((game*)p_l_node->info_struct);
        scr1 = p_game->score1; scr2 = p_game->score2;
        printf("%d %s %s %s %d %d\n",cmd_ctr,p_game->name,p_game->team1,p_game->team2,scr1,scr2);
    }
    return TRUE;
}

/* outputs to stdio the game info for the game whose name was passed in
   the io_buffer, if a game with such a name doesnt exist, outputs an
   error message */
int search_game_proc(char *io_buffer, l_ht_info *info, int cmd_ctr)
{
    char name[MAX_NAME_SIZE],*tm1,*tm2;
    int score1,score2;
    game *p_game = NULL;
    sscanf(io_buffer,"%*c %[^:\n]",name);
    /* if a game with said name exists, update p_game */
    search_game_by_name(name,info,&p_game);
    /* if p_game is still NULL, a game with such a name wasnt yet created */
    if(p_game == NULL)
    {
        printf("%d Jogo inexistente.\n",cmd_ctr);
        return FALSE;
    }
    tm1 = p_game->team1;
    tm2 = p_game->team2;
    score1 = p_game->score1;
    score2 = p_game->score2;
    printf("%d %s %s %s %d %d\n",cmd_ctr,name,tm1,tm2,score1,score2);
    return TRUE;
}

/* outputs to stdio the team info for the team whose name was passed in
   the io_buffer, if a team with such a name doesnt exist, outputs an
   error message */
int search_team_proc(char *io_buffer, l_ht_info *info, int cmd_ctr)
{
    char name[MAX_NAME_SIZE];
    int games_won;
    team *p_team = NULL,**ptr_team_ptr = &p_team;
    sscanf(io_buffer,"%*c %[^:\n]",name);
    /* if a team with said name exists, update p_game */
    search_team_by_name(name,info,ptr_team_ptr);

    /* if p_team is still NULL, a team with such a name wasnt yet created */
    if(p_team == NULL)
    {
        printf("%d Equipa inexistente.\n",cmd_ctr);
        return FALSE;
    }
    games_won = p_team->games_won;
    printf("%d %s %d\n",cmd_ctr,name,games_won);
    return TRUE;
}

/* deletes a game from record if possible, and updates the games won by the teams */
int delete_game_proc(char *io_buffer, l_ht_info *info, int cmd_ctr)
{
    char name[MAX_NAME_SIZE];
    ulong key;
    ht_node *p_ht_node;
    l_node *p_l_node;
    sscanf(io_buffer,"%*c %[^:\n]",name);
    key = ht_key_from_str(name);
    p_ht_node = ht_get_base_node(info->ht_games,key);
    if(p_ht_node == NULL) /* hash table has no entry with said key print error*/
    {
        printf("%d Jogo inexistente.\n",cmd_ctr);
        return FALSE;
    }
    /* follows the p_l_node chain until game is found or end of chain is reached */
    for(;p_ht_node != NULL; p_ht_node = p_ht_node->next)
    {
        p_l_node = (l_node*)p_ht_node->info_struct;
        /* found p_l_node, break for loop */
        if(strcmp(((game*)p_l_node->info_struct)->name,name) == 0) break;
        /* reached end without finding p_l_node, print error */
        if(p_ht_node->next == NULL)
        {
            printf("%d Jogo inexistente.\n",cmd_ctr);
            return FALSE;
        }
    }
    /* update the games won for teams involved in the removed game and remove the game from info*/
    dgp_update_games_won(info,(game*)p_l_node->info_struct);
    l_list_remove_node(info->l_games,p_l_node,free_game); /* this function also frees the game */
    ht_delete_node(info->ht_games,p_ht_node,key);
    return TRUE;
}

/* handles the updating of games won when a game is removed from record */
void dgp_update_games_won(l_ht_info *info, game *p_game)
{
    team *p_team1,*p_team2;
    search_team_by_name(p_game->team1,info,&p_team1);
    search_team_by_name(p_game->team2,info,&p_team2);
    if(p_game->score1 > p_game->score2)
    {
        p_team1->games_won--;
    }
    if(p_game->score1 < p_game->score2)
    {
        p_team2->games_won--;
    }
    return;
}

/* changes the score of a recorded game, and updates the games won by the teams */
int change_game_score_proc(char *io_buffer, l_ht_info *info, int cmd_ctr)
{
    char name[MAX_NAME_SIZE];
    int scr1,scr2;
    game *p_game = NULL;
    sscanf(io_buffer,"%*c %[^:\n]:%d:%d",name,&scr1,&scr2);
    /* if no game is found with such name, print error */
    if(!search_game_by_name(name,info,&p_game))
    {
        printf("%d Jogo inexistente.\n",cmd_ctr);
        return FALSE;
    }
    /* function that handles the update of games won*/
    cgsp_update_games_won(info,p_game,scr1,scr2);
    /* update the actual scores in the recorded game */
    p_game->score1 = scr1;
    p_game->score2 = scr2;
    return TRUE;
}
/* updates games won for teams that had a game's score changed */
void cgsp_update_games_won(l_ht_info *info,game *p_game,int scr1,int scr2)
{
    int pre_scr1,pre_scr2;
    team *p_team1,*p_team2;
    pre_scr1 = p_game->score1; pre_scr2 = p_game->score2;
    search_team_by_name(p_game->team1,info,&p_team1); /* get pointers to the teams */
    search_team_by_name(p_game->team2,info,&p_team2);
    /* process games won according to score changes */
    if(pre_scr1 > pre_scr2)
    {
        if(scr1 == scr2)p_team1->games_won--;
        if(scr1 < scr2)
        {
            p_team1->games_won--;
            p_team2->games_won++;
        }
    }
    if(pre_scr1 < pre_scr2)
    {
        if(scr1 == scr2)p_team2->games_won--;
        if(scr1 > scr2)
        {
            p_team1->games_won++;
            p_team2->games_won--;
        }
    }
    if(pre_scr1 == pre_scr2)
    {
        if(scr1 > scr2)p_team1->games_won++;
        if(scr1 < scr2)p_team2->games_won++;
    }
    return;
}

/* processes the teams list to find the teams with most games won
   then prints them according to the required standard */
int teams_most_wins_proc(l_ht_info *info, int cmd_ctr)
{
    l_list *l_max_winners = NULL;
    l_node *lst_node, *temp_l_node;
    team *p_team;
    int max_wins = -1,n_winners;
    if(info->l_teams->head == NULL) return FALSE; /* if there are no teams, return */
    /* go through the list of teams, and gather the teams with most wins into a new list */
    for(lst_node = info->l_teams->head; lst_node != NULL; lst_node = lst_node->next)
    {
        p_team = (team*)lst_node->info_struct;
        if(p_team->games_won > max_wins) /* if the team has more wins than the current max wins */
        {
            max_wins = p_team->games_won; /* update max wins */
            n_winners = 0;
            free_l_list_and_node_only(l_max_winners); /* delete old list */
            l_max_winners = create_l_list(); /* create new list to hold winners */
        }
        if(p_team->games_won == max_wins) /* if the game has max_wins, add it to winners list */
        {
            temp_l_node = create_l_node();
            temp_l_node->info_struct = (void*)p_team;
            l_list_add_node_end(l_max_winners,temp_l_node);
            n_winners++;
        }
    }
    /* print the teams names */
    tmwp_sort_print(l_max_winners,n_winners,max_wins,cmd_ctr);
    free_l_list_and_node_only(l_max_winners);
    return TRUE;
}

/* sorts the names of the teams with the max wins, and prints them according to standard */
void tmwp_sort_print(l_list* l_winners, int n_winners, int max_wins, int cmd_ctr)
{
    int title_flag = FALSE, arr_pos = 0;
    char ** chr_arr = can_fail_malloc(sizeof(char*) * n_winners);
    l_node *lst_node;
    /* pass the team names into the char pointer array */
    for(lst_node = l_winners->head; lst_node != NULL;arr_pos++,lst_node = lst_node->next)
    {
        *(chr_arr+arr_pos) = ((team*)lst_node->info_struct)->name;
    }
    quicksort(chr_arr,0,n_winners-1,NULL,swap_char); /* sort the names */
    /* print according to the standard */
    for(arr_pos = 0; arr_pos < n_winners; arr_pos ++)
    {
        if(!title_flag)
        {
            printf("%d Melhores %d\n", cmd_ctr, max_wins);
            title_flag = TRUE;
        }
        printf("%d * %s\n",cmd_ctr, *(chr_arr+arr_pos));
    }
    free(chr_arr);
    return;
}
/* function that swaps the pointers in chr_arr on the indexes given , passed to quicksort */
void swap_char(int idx_1, int idx_2, char **chr_arr, void *info_struct)
{
    char *p_chr_temp;
    UNUSED(info_struct); /* unused, but has to exist to interface with quicksort */
    p_chr_temp = *(chr_arr + idx_1);
    *(chr_arr + idx_1) = *(chr_arr + idx_2);
    *(chr_arr + idx_2) = p_chr_temp;
    return;
}

/* returns TRUE if a game with a given name was already created
   and updates the ptr pointed to by p_game */
int search_game_by_name(char *name, l_ht_info *info,game **p_game)
{
    ulong key = ht_key_from_str(name);
    ht_node *p_ht_node;
    l_node *node;
    p_ht_node = ht_get_base_node(info->ht_games,key);

    /* cycle through the node chain for the position key in the hashtable */
    for(;p_ht_node != NULL; p_ht_node = p_ht_node->next)
    {
        node = (l_node*)p_ht_node->info_struct;
        /* if names are equal, it means game was already created */
        if(strcmp(((game*)node->info_struct)->name,name) == 0)
        {
            *p_game = (game*)node->info_struct;
            return TRUE;
        }
    }
    *p_game = NULL;
    return FALSE;
}

/* returns TRUE if a team with a given name was already created
   and updates the ptr pointed to by p_team */
int search_team_by_name(char *name, l_ht_info *info,team **p_team)
{
    ulong key = ht_key_from_str(name);
    ht_node *p_ht_node;
    l_node *node;
    p_ht_node = ht_get_base_node(info->ht_teams,key);

    /* cycle through the node chain for the position key in the hashtable */
    for(;p_ht_node != NULL; p_ht_node = p_ht_node->next)
    {
        node = (l_node*)p_ht_node->info_struct;
        /* if names are equal, it means team was already created */
        if(strcmp(((team*)node->info_struct)->name,name) == 0)
        {
            *p_team = (team*)node->info_struct;
            return TRUE;
        }
    }
    *p_team = NULL;
    return FALSE;
}
