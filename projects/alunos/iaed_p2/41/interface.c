#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "interface.h"

/*Interface function that reads the user inputs and executes the corresponding functions.*/
void execute_command(team_node * tree_ptr, game_item * hash_ptr)
{
    char command = ' ';
    
    char gm_name[1023], tm_name[1023], t1_name[1023], t2_name[1023];
    int s1, s2, m, NL;
    team_node tm, t1, t2;
    game_node gm;
    game_node order_fst = NULL;
    game_node order_crnt = NULL;
    game_node order_prev = NULL;
    game_item hashtbl;

    NL = 1;

    while(command != 'x')
    {
        command = getchar();

        switch (command)
        {
            case 'A':
                /*Input*/
                scanf(" %[^:\n]", tm_name);
                
                /*Get AVL tree node*/
                tm = (search_team(tree_ptr, tm_name));

                if(tm == NULL)
                    insert_team(tree_ptr, create_team(tm_name));
                else
                    printf("%d Equipa existente.\n", NL);

                NL++;
                break;

            case 'a':
                /*Input*/
                scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", gm_name, t1_name, t2_name, &s1, &s2);

                t1 = search_team(tree_ptr, t1_name);
                t2 = search_team(tree_ptr, t2_name);
                gm = search_game(hash_ptr, gm_name);

                if((t1 != NULL) && (t2 != NULL) && (gm == NULL))
                {
                    if(order_fst == NULL)
                    {
                        insert_game(hash_ptr, create_game(gm_name, t1->team, t2->team, s1, s2), &order_fst, &order_crnt);
                        
                        order_prev = order_fst;
                    }
                    else
                    {
                        insert_game(hash_ptr, create_game(gm_name, t1->team, t2->team, s1, s2), &order_fst, &order_crnt);
                        
                        /*Order hash table by insertion order*/
                        order_prev->in_next = order_crnt;
                        order_crnt->in_previous = order_prev;
                        order_prev = order_crnt;
                    }
                    /*Add one victory to winner team*/
                    if(s1 > s2)
                        inc_score(t1->team);
                    else if(s1 < s2)
                        inc_score(t2->team);
             
                }
                /*Check for error*/
                else if(gm != NULL)
                    printf("%d Jogo existente.\n", NL);
                else if((t1 == NULL) || (t2 == NULL))
                    printf("%d Equipa inexistente.\n", NL);
                
                NL++;
                break;
            
            case 'l':

                insertion_order(order_fst, NL);

                NL++;
                break;
            
            case 'p':
                /*Input*/
                scanf(" %[^:\n]", gm_name);

                gm = search_game(hash_ptr, gm_name);

                if(gm != NULL)
                    print_game(gm, NL);
                else
                    printf("%d Jogo inexistente.\n", NL);

                NL++;
                break;

            case 'P':
                /*Input*/
                scanf(" %[^:\n]", tm_name);

                /*Get AVL tree node*/
                tm = search_team(tree_ptr, tm_name);

                if(tm != NULL)
                    printf("%d %s %d\n", NL, tm->team->name, tm->team->score);
                if(tm == NULL)
                    printf("%d Equipa inexistente.\n", NL); 
                
                NL++;
                break;

            case 'r':
                /*Input*/
                scanf(" %[^:\n]", gm_name);
                
                /*Get hash table node*/
                gm = search_game(hash_ptr, gm_name);
                
                /*Check for error*/    
                if(gm != NULL)
                {
                    hashtbl = hash_ptr[hash_function(gm_name)];
                    s1 = gm->game->score_1;
                    s2 = gm->game->score_2;

                    /*Change the scores*/
                    if(s1 > s2)
                        dec_score(gm->game->team_1);
                    if(s1 < s2)
                        dec_score(gm->game->team_2);

                    delete_ordered(&order_fst, gm);
                    delete_game(hashtbl,gm);
                }
                else
                    printf("%d Jogo inexistente.\n", NL);

                NL++;
                break;
            
            case 's':
                /*Input*/
                scanf(" %[^:\n]:%d:%d", gm_name, &s1, &s2);
                
                /*Get hash table node*/
                gm = search_game(hash_ptr, gm_name);

                /*Check for error*/
                if(gm != NULL)
                    update_score(gm, s1, s2);
                else
                    printf("%d Jogo inexistente.\n", NL);
                
                NL++;
                break;
            
            case 'g':
                /*Check for error*/
                if(*tree_ptr != NULL)
                {
                    /*Get the most amount of victories*/
                    m = victories(*tree_ptr);
                    printf("%d Melhores %d\n", NL, m);
                    in_order(tree_ptr, m, NL);
                }
                
                NL++;
                break;
            
            case 'x':
                /*Free AVL tree and hash table*/
                free_teams(*tree_ptr);
                free_games(hash_ptr);
                exit(0);
                break;
            
            default:
                break;
        }
    }
}