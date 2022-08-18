#include "MAIN_FUNTIONS.h"


 /* Main Fuctions. */ 


/*Adds a new game if boths teams are in the system. 
If one of the teams wins, gets one more victory. */
void add_game(Game ** game_hash, team ** team_hash, int NL){
    char name_game[MAXCAR], teamA[MAXCAR], teamB[MAXCAR];
    int index, scoreA, scoreB;
    team * A, *B;
    Game * new, * game;

    scanf(" %[^:\n]: %[^:\n]: %[^:\n]: %d: %d", name_game, teamA, teamB, &scoreA, &scoreB);

    index = hash(name_game);
    game = game_hash[index];

    if(!game){

        if( !(A = get_team(team_hash, teamA))){
            printf("%d Equipa inexistente.\n", NL);
            return ;
        }
        
        if( !(B = get_team(team_hash, teamB))){
            printf("%d Equipa inexistente.\n", NL);
            return ;
        }

        game = create_game(name_game, A, B, scoreA, scoreB);
        game->NL = NL;

        if(scoreA > scoreB)
            A->vitories++;
        
        else if(scoreB > scoreA)
            B->vitories++;
        
        game_hash[index] = game;
        return ;
    }
        

    for(; game; game = game->next){
        if(!strcmp(game->name, name_game)){
            printf("%d Jogo existente.\n", NL);

            return ;
        }
        if(!game->next) break;

    }

    if( !(A= get_team(team_hash, teamA))){
        printf("%d Equipa inexistente.\n", NL);

        return ;
    }

    if( !(B= get_team(team_hash, teamB))){
        printf("%d Equipa inexistente.\n", NL);

        return ;
    }
    
    
    new = create_game(name_game, A, B, scoreA, scoreB);
    new->NL = NL;   
    game->next = new;

    if(scoreA > scoreB)
        A->vitories++;
        
    else if(scoreB > scoreA)
        B->vitories++;  
    
    return ;
}



/* Shows all the games in order of insert. */
void show_list_game(Game ** game_hash, int NL){
    Game * p, *s = NULL;
    int i = 0;
    
    for(;i < HASH_SIZE; i++){
        p = game_hash[i];
        for(; p; p = p->next){
            s = add_order_game(s, p->name, p->A, p->B, p->scoreA, p->scoreB, p->NL);
        }
    }

    if(!s) return;

    p = s;
   
    for(; s; s = s-> next){
        printf("%d %s %s %s %d %d\n",
            NL,s->name, s->A->name, s->B->name, s->scoreA, s->scoreB);
    }

    p = destroy_game(p);

}


/* Searchs the game in the system. */
void search_game(Game ** game_hash, int NL){
    char name[MAXCAR];
    Game * s;

    scanf("%[^:\n]", name);

    s = game_hash[hash(name)];

    for(; s; s = s->next)
        if(!strcmp(s->name, name)){
            printf("%d %s %s %s %d %d\n",
                NL, s->name, s->A->name, s->B->name, s->scoreA, s->scoreB);
            return;
        }

    printf("%d Jogo inexistente.\n", NL); 
}


/* Changes the score of the game. */ 
void change_score_game(Game ** game_hash, int NL){
    Game * game;
    char name_game[MAXCAR];
    int new_scoreA, new_scoreB, index = 0;

    scanf(" %[^:\n]: %d: %d", name_game, &new_scoreA, &new_scoreB);
    index = hash(name_game);

    game = game_hash[index];

    while(game){
        if(!strcmp(game->name, name_game)){
            break;
        }
        game = game->next;
    }

    if(!game){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    if(game->scoreA > game->scoreB){
        if( new_scoreA < new_scoreB){
            game->A->vitories--;
            game->B->vitories++;      
        }
        else if(new_scoreA == new_scoreB){
            game->A->vitories--;
        }
    }
    else if(game->scoreA < game->scoreB){
        if(new_scoreA > new_scoreB){
            game->A->vitories++;
            game->B->vitories--; 
        }
        else if( new_scoreA == new_scoreB){
            game->B->vitories--; 
        }
    }
    else if(game->scoreA == game->scoreB){
        if( new_scoreA > new_scoreB){
            game->A->vitories++;
        }
        else if(new_scoreA < new_scoreB){
            game->B->vitories++; 
        }
    }

    game->scoreA = new_scoreA;
    game->scoreB = new_scoreB;
    
}

/* Deletes the game. */
void delete_game(Game ** game_hash, int NL){
    Game * delete, * aux;
    char name[MAXCAR];
    int index = 0;

    scanf("%[^:\n]",name);

    index = hash(name);
    delete = game_hash[index];

    if(!delete){
        printf("%d Jogo inexistente.\n", NL);
        return ;
    }

    /* Verify if the first game has the same name. */
    if(!(strcmp(delete->name, name))){
        if(delete->scoreA > delete->scoreB){
            delete->A->vitories--;
        }
        else if(delete->scoreB > delete->scoreA){
            delete->B->vitories--;
        }
        game_hash[index] = pop_game(game_hash[index]);
        return ;
    }
    
    aux = delete;
    delete = delete->next;

    for(; delete; delete = delete->next, aux = aux->next){
        if(!strcmp(delete->name, name)){
            if(delete->scoreA > delete->scoreB){
                delete->A->vitories--;
            }
            else if(delete->scoreB > delete->scoreA){
                delete->B->vitories--;
            }

            delete = pop_game(delete);
            aux -> next = delete;
            
            return ;
        }
    }

    printf("%d Jogo inexistente.\n", NL);
    return ;
} 


/* Adds a new team  in the teams system. */ 
void add_team(team ** team_hash, int NL){
    char name[MAXCAR];

    scanf("%[^:\n]", name);

    list_put_team(team_hash, name, NL);    
}


/* Searchs a team by the name.
If the team exists, shows the team and his number of victories. */
void team_search(team ** team_hash, int NL){
    char name[MAXCAR];
    team * lookteam = NULL;

    scanf("%[^:\n]", name);

    lookteam = team_hash[hash(name)];
    
    for(; lookteam; lookteam = lookteam->next){
        if(!strcmp(lookteam->name, name)){
            printf("%d %s %d\n", NL, lookteam->name, lookteam->vitories);
            return;
        }
    }
    
    printf("%d Equipa inexistente.\n", NL);
}


/* Shows the teams who has the most victories in lexicographic order. */
void most_vitories(team ** team_hash, int NL){
    int i = 0;
    team * point, * print = NULL, *free_team;
    

    for(i = 0; i < HASH_SIZE; i++){
        point = team_hash[i];
        for(; point; point = point -> next){
            if(!print){
                print = create_team(point->name);
                print->vitories = point->vitories;
            }
            else if(point -> vitories >= print->vitories){
               print = push_team(point->name, print);
               print->vitories = point ->vitories;
            }
        }
    }

    if(!print) return;
    
    point = NULL;
    free_team = print;

    printf("%d Melhores %d\n", NL, print->vitories);
    
    /* Organize the teams who has more vitories on lexicographic order. */
    for(; print; print = print->next){
        point = add_order_team(point, print->name);
        if(print->next == NULL) break;
        if(print->vitories > print->next->vitories)
            break;
    }
    
    print = point;

    for (; print; print = print->next){
        printf("%d * %s\n", NL, print->name);
    }
    
    free_team = destroy_index_team(free_team);   
    point = destroy_index_team(point);
    
}