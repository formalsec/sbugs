#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "_features.h"

list *f_addgame(char *game_name,char *t1,char *t2,int s1,int s2,int nl,list *jogos){
    pTeam team1=Tsearch(t1), team2=Tsearch(t2);
    if(Gsearch(game_name)!=NULL){ /*proucra na hash se o jogo existe*/
        printf("%d Jogo existente.\n",nl);
        return jogos;
    }
    else if(team1==NULL || team2==NULL){ /*procura se as equipas existem na hash*/
        printf("%d Equipa inexistente.\n",nl);
        return jogos;
    }
    else{
        if(s1>s2) team1->wins+=1; /*adiciona uma win na equipa que ganhou*/
        else if(s2>s1) team2->wins+=1;
        Ginsert(game_name, t1, t2, s1, s2);
        return list_insert(game_name, jogos);
    }
}

void print_games(list *jogos,int nl){
    list *temp=jogos;
    temp=temp->next;
    while(temp!=NULL){ /*percorre a lista de jogos*/
        show_game(temp->str,nl);
        temp=temp->next;
    }
}

void add_team(char *team_name,int nl){
    if(Tsearch(team_name)!=NULL) printf("%d Equipa existente.\n",nl);
    else{
        Tinsert(team_name);
    }
}

void show_game(char *game_name,int nl){
    games v;
    v=Gsearch(game_name);
    if(v==NULL) printf("%d Jogo inexistente.\n",nl);
    else printf("%d %s %s %s %d %d\n",
               nl,v->game_name,v->team1,v->team2,v->score1,v->score2);
}

void delete_game(char *game_name,list *jogos, int nl){
    int s1,s2;
    games temp;
    temp=Gsearch(game_name);
    if(temp==NULL) printf("%d Jogo inexistente.\n",nl);
    else{
        s1=temp->score1; s2=temp->score2;
        if(s1>s2) Tsearch(temp->team1)->wins-=1; /*retira as wins da equipa se ela deixou ser a equipa vencedora*/
        else if(s2>s1) Tsearch(temp->team2)->wins-=1;
        Gdelete(game_name);
        list_remove(game_name, jogos);
    }
}

void change_score(char *game_name,int s1, int s2,int nl){
    int score1, score2;
    games v;
    v=Gsearch(game_name);
    if(v==NULL) printf("%d Jogo inexistente.\n",nl);
    else{/*encontra a opcao que ocorreu na mudanca deste jogo*/
        score1=v->score1; score2=v->score2;
        if(score1>score2){
            if(s1==s2) Tsearch(v->team1)->wins-=1;
            else if(s1<s2){
                Tsearch(v->team1)->wins-=1;
                Tsearch(v->team2)->wins+=1;
            }
        }
        else if(score1<score2){
            if(s1==s2) Tsearch(v->team2)->wins-=1;
            else if(s1>s2){
                Tsearch(v->team2)->wins-=1;
                Tsearch(v->team1)->wins+=1;
            }
        }
        else{
            if(s1>s2) Tsearch(v->team1)->wins+=1;
            else if(s1<s2) Tsearch(v->team2)->wins+=1;
        }
        v->score1=s1; v->score2=s2;
    }
}

void search_team(char *equipa,int nl){
    pTeam temp;
    temp=Tsearch(equipa);
    if(temp==NULL){
        printf("%d Equipa inexistente.\n",nl);
    }
    else printf("%d %s %d\n",nl,equipa,temp->wins);
}

static int sortstring( const void  *a, const void *b ){/*funcao que diz qual das strings e maior ou menor*/
    char **v1, **v2;
    v1 = (char **) a;
    v2 = (char **) b;
    return strcmp(*v1,*v2);
}

void best_teams(int nl){
    int max=0,i=0,j;
    char *top[1049];
    pTeam temp;
    max=max_wins();
    
    for(j=0;j<TABLE_SIZE;j++){ /*percorre a hash table e recolhe todos os jogos com o msm numero de wins*/
        temp=Thash(j);
        if(temp!=NULL)
            if(temp->wins==max){
                top[i]=stringdup(temp->team_name);
                i++;
            }
        }
        
    if(i>0){
        qsort(top, i, sizeof(char*), sortstring);/*ordena as equipas por ordem alfabetica*/
        printf("%d Melhores %d\n",nl,max);
        for(j=0;j<i;j++){
            printf("%d * %s\n",nl,top[j]);
            free(top[j]);
    }
    }
}
