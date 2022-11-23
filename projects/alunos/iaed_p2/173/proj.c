#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Generic_Binary_Tree.h"
#include "Generic_Linked_List.h"
#include "equipa.h"
#include "jogo.h"

#define MAX_CHARS 1023


/*
Funcao que retorna o sinal de um inteiro
*/
int sign(int x) {
    return (x > 0) - (x < 0);
}

/*
Funcao de comparacao para nomes (strings em geral) de jogos e de equipas
*/
int nome_compare_func(void*a, void*b){
    return strcmp((char*)b,(char*)a);
}

/*
Funcao para libertar uma equipa
*/
void bt_free_equipa(void* data){
    free_equipa(data);
}

/*
Funcao para libertar um jogo
*/
void bt_free_jogo(void* data){
    free_jogo(data);
}

/*
Funcao para obter o nome de uma equipa a partir de uma estrutura generica
*/
void *bt_get_nome_equipa(void *a){
    return (void *) get_nome_equipa((Equipa*)a);
}

/*
Funcao para obter o nome de um jogo a partir de uma estrutura generica
*/
void *bt_get_nome_jogo(void *a){
    return (void *) get_nome_jogo((Jogo*)a);
}

/*
Adiciona uma equipa a base de dados
in  -> A <nome>
*/
void ad_equipa(int *nl,BTlink *equipas){
    char nome[MAX_CHARS];
    Equipa* equipa;
    (*nl)++;

    scanf(" %[^:\n]",nome);
    equipa = cria_equipa(nome);
    if (bintree_add_item(equipas, equipa, sizeof(*equipa), bt_free_equipa,bt_get_nome_equipa, nome_compare_func)){
        printf("%d Equipa existente.\n",*nl);
        return;
    }
}

/*
Adiciona um jogo a base de dados
in  -> a <nome>:<equipa1>:<equipa2>:<score1>:<score2>
*/
void ad_jogo(int *nl,BTlink *equipas,BTlink *jogos,int *i_jogos){
    char nome[MAX_CHARS],e1_nome[MAX_CHARS],e2_nome[MAX_CHARS];
    Jogo *jogo;
    void *e1,*e2;
    int s1,s2;
    (*nl)++;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome,e1_nome,e2_nome,&s1,&s2);


    if (bintree_search(*jogos,nome,bt_get_nome_jogo,nome_compare_func) != NULL){
        printf("%d Jogo existente.\n",*nl);
        return;
    }

    e1 = (Equipa*) bintree_search(*equipas, e1_nome,bt_get_nome_equipa,nome_compare_func);
    e2 = (Equipa*) bintree_search(*equipas, e2_nome,bt_get_nome_equipa,nome_compare_func);

    if ((e1 == NULL) || (e2 == NULL)){
        printf("%d Equipa inexistente.\n",*nl);
        return;
    }

    jogo = cria_jogo(nome,e1,e2,s1,s2,*nl);

    /* incrementar a pontuacao da equipa vencedora */
    if (s1 > s2){
        alt_score_equipa(get_equipa1_jogo(jogo),1);
    }else if (s1 < s2){
        alt_score_equipa(get_equipa2_jogo(jogo),1);
    }
    
    bintree_add_item(jogos, jogo, sizeof(*jogo), bt_free_jogo, bt_get_nome_jogo, nome_compare_func);
    (*i_jogos)++;
}

/*
Procura por um jogo na base de dados
in  -> p <nome>
out -> <nl> <nome> <equipa1> <equipa2> <score1> <score2>
*/
void procura_jogo(int *nl,BTlink jogos){
    char nome[MAX_CHARS];
    Jogo *jogo;
    (*nl)++;
    scanf(" %[^:\n]",nome);
    jogo = (Jogo*) bintree_search(jogos,nome,bt_get_nome_jogo,nome_compare_func);
    if (jogo == NULL){
        printf("%d Jogo inexistente.\n",*nl);
    }else{
        printf("%d %s %s %s %d %d\n",*nl, get_nome_jogo(jogo),get_nome_equipa(get_equipa1_jogo(jogo)),get_nome_equipa(get_equipa2_jogo(jogo)),get_score1_jogo(jogo),get_score2_jogo(jogo));
    }
}

/*
Procura por uma equipa na base de dados
in  -> P <nome>
out -> <nl> <nome> <score>
*/
void procura_equipa(int *nl,BTlink equipas){
    char nome[MAX_CHARS];
    Equipa *equipa;
    (*nl)++;
    scanf(" %[^:\n]",nome);
    equipa = (Equipa*) bintree_search(equipas,nome,bt_get_nome_equipa,nome_compare_func);
    if (equipa == NULL){
        printf("%d Equipa inexistente.\n",*nl);
    }else{
        printf("%d %s %d\n",*nl,get_nome_equipa(equipa),get_score_equipa(equipa));
    }
}

/*
Remove um jogo da base de dados
in  -> r <nome>
*/
void remove_jogo(int *nl,BTlink *jogos,int *i_jogos){
    char nome[MAX_CHARS];
    Jogo* jogo;
    (*nl)++;
    scanf(" %[^:\n]",nome);
    if (*jogos == NULL) {
        printf("%d Jogo inexistente.\n",*nl);
        return;
    }

    jogo = bintree_search(*jogos,nome,bt_get_nome_jogo,nome_compare_func);

    if (jogo == NULL){
        printf("%d Jogo inexistente.\n",*nl);
        return;
    }
    /* decrementar a pontuacao da equipa vencedora */
    if (get_score1_jogo(jogo) > get_score2_jogo(jogo)){
        alt_score_equipa(get_equipa1_jogo(jogo),-1);
    }else if (get_score1_jogo(jogo) < get_score2_jogo(jogo)){
        alt_score_equipa(get_equipa2_jogo(jogo),-1);
    }

    bintree_delete_item(jogos,nome,bt_get_nome_jogo,bt_free_jogo,nome_compare_func);    
    (*i_jogos)--;
}

/*
Altera a pontuacao de um jogo na base de dados
in  -> s <nome>:<score1>:<score2>
*/
void altera_pontuacao(int* nl,BTlink *jogos){
    char nome[MAX_CHARS];
    int s1,s2,prev_s1,prev_s2;
    Jogo* jogo;
    (*nl)++;
    scanf(" %[^:\n]:%d:%d",nome,&s1,&s2);

    jogo = bintree_search(*jogos,nome,bt_get_nome_jogo,nome_compare_func);

    if (jogo == NULL){
        printf("%d Jogo inexistente.\n",*nl);
        return;
    }
    /* prev_s1 e prev_s2 irao guardar os scores do jogo antes da alteracao */
    prev_s1 = get_score1_jogo(jogo);
    prev_s2 = get_score2_jogo(jogo);

    alt_score_jogo(jogo,s1,s2);

    /* Caso a equipa vencedora continue a mesma, nao ha alteracoes nas pontuacoes das equipas */
    if (sign(prev_s1-prev_s2) == sign(s1-s2)) return;
    
    /* Os seguintes casos irao ajustar as pontuacoes das equipas consoante a mudanca */
    
    /* Alterar pontuacao da equipa 1*/
    if (sign(prev_s1-prev_s2) == 1)
        alt_score_equipa(get_equipa1_jogo(jogo),-1);
    else if ((sign(prev_s1-prev_s2)==-1))
        alt_score_equipa(get_equipa1_jogo(jogo),sign(s1-s2));
    else if ((sign(prev_s1-prev_s2)==0))
        alt_score_equipa(get_equipa1_jogo(jogo),(1+sign(s1-s2))/2);
    
    /* Alterar a pontuacao da equipa 2 */
    if (sign(prev_s2-prev_s1) == 1)
        alt_score_equipa(get_equipa2_jogo(jogo),-1);
    else if ((sign(prev_s2-prev_s1)==-1))
        alt_score_equipa(get_equipa2_jogo(jogo),sign(s2-s1));
    else if ((sign(prev_s2-prev_s1)==0))
        alt_score_equipa(get_equipa2_jogo(jogo),(1+sign(s2-s1))/2);
}

/* 
Funcao para comparar os id's de dois jogos
*/
int cmp_id(const void *a,const void *b){
    return ((*( Jogo**)a)->id - (*( Jogo**)b)->id);
}   

/*
Lista todos os jogos pela ordem que foram introduzidos
in  -> l
out -> NL <nome> <equipa1> <equipa2> <score1> <score2>
*/
void lista_jogos(int *nl,BTlink *jogos,int i_jogos){
    int i;
    void **lista_jogos;
    i = 0;
    (*nl)++;
    if (*jogos != NULL){
        /* criar um array de tamanho i_jogos, copiar a arvore de jogos para o array, ordenar e fazer print */
        lista_jogos = can_fail_malloc(sizeof(Jogo*)*(i_jogos));
        bintree_array(*jogos,lista_jogos,sizeof(Jogo*));
        qsort(lista_jogos,i_jogos,sizeof(struct Jogo**),cmp_id);
        for (i=0;i<i_jogos;i++){
            printf("%d %s %s %s %d %d\n",*nl,((Jogo*)lista_jogos[i])->nome,get_nome_equipa(((Jogo*)lista_jogos[i])->e1),get_nome_equipa(((Jogo*)lista_jogos[i])->e2),((Jogo*)lista_jogos[i])->s1,((Jogo*)lista_jogos[i])->s2);
        }
        free(lista_jogos);
    }  
}

/*
Funcao para comparar vitorias de equipas 
*/
int cmp_func(const void *a,const void *b){
    return ((*( Equipa**)b)->vitorias - (*( Equipa**)a)->vitorias);
}

/*
Funcao que servira de condicao para adicionar equipas a uma lista ao percorrer a arvore binaria
*/
void condition(void *a,Link *lista){
    int best;
    int team_score;
    if (a == NULL) return;
    team_score = get_score_equipa((Equipa *)a);

    if (*lista != NULL) best = get_score_equipa((Equipa*)linkedlist_get_item(*lista,0));
    else best = 0;

    if (team_score > best){
        *lista = linkedlist_reset(*lista,free); 
        linkedlist_add_item(lista,a,sizeof(Equipa));
        best = team_score;
    }else if (team_score == best){
        linkedlist_add_item(lista,a,sizeof(Equipa));
    }
}

/*
Lista as melhores equipas
in  -> g
out -> <nl> Melhores <melhor_pontuacao>
            <nome> * <score>
*/
void lista_equipas(int *nl,BTlink *equipas){
    Link lista_equipas;
    int i,count = 0;
    (*nl)++;
    if (*equipas != NULL){
        lista_equipas = bintree_to_list_condition(*equipas,condition);

        count = linkedlist_get_length(lista_equipas);
        printf("%d Melhores %d\n",*nl,get_score_equipa((Equipa*)linkedlist_get_item(lista_equipas,0)));
        for (i=0;(i<count);i++){
            printf("%d * %s\n",*nl,get_nome_equipa((Equipa*)linkedlist_get_item(lista_equipas,i)));
        }
        linkedlist_free(lista_equipas,free);
    }  
}



int main(){
    char cmd;
    int nl = 0,i_jogos=0;
    BTlink equipas = bintree_create();
    BTlink jogos = bintree_create();

    while(1){
        scanf("%c",&cmd);
        switch (cmd){
            case 'a':
                ad_jogo(&nl,&equipas,&jogos,&i_jogos);
            break;

            case 'A':
                ad_equipa(&nl,&equipas);
            break;
            
            case 'p':
                procura_jogo(&nl,jogos);
            break;

            case 'P':
                procura_equipa(&nl,equipas);
            break;
            
            case 'r':
                remove_jogo(&nl,&jogos,&i_jogos);
            break;
    
            case 's':
                altera_pontuacao(&nl,&jogos);
            break;
            
            case 'l':
                lista_jogos(&nl,&jogos,i_jogos);
            break;
            
            case 'g':
                lista_equipas(&nl,&equipas);
            break;
            
            case 'x':
                bintree_free(equipas,bt_free_equipa);
                bintree_free(jogos,bt_free_jogo);
                return 0;
            break;
        }
    }
    return 0;
}

