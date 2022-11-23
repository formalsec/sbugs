#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "projeto.h"

/* Funcao que lista pela ordem de insercao todos os jogos presentes na base de dados. */
void lista_todos(int contador, pList l){
    pJogo t;
    for(t = l -> head; t != NULL; t = t -> next){
        printf("%d %s %s %s %d %d\n", contador, t -> nome, t -> equipa1, t -> equipa2, t -> score1, t -> score2);
    }
}


/* Funcao que adiciona um jogo ah base de dados. */
void adiciona_jogo(int contador, pHash h, pHash_e h_e, pList l){
    char nome[MAX];
    char equipa1[MAX];
    char equipa2[MAX];
    int score1;
    int score2;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);

    if(ht_search(h, nome) != NULL){
        printf("%d Jogo existente.\n", contador);
    }
    else if(ht_search_e(h_e, equipa1) == NULL || ht_search_e(h_e, equipa2) == NULL){
        printf("%d Equipa inexistente.\n", contador);
    }
    else{ 
        pEquipa e;
        pJogo novo;
        novo = cria_jogo(nome, equipa1, equipa2, score1, score2);

        if(novo -> vencedora != NULL){
            e = ht_search_e(h_e, novo -> vencedora);
            e -> wins += 1;
        }
        ht_insert(h, novo);
        list_insert(l, novo);
    }
}


/* Funcao que lista os dados de um dado jogo. */
void lista_jogo(int contador, pHash h){
    pJogo j;
    char nome[MAX];
    scanf(" %[^:\n]", nome);
    j = ht_search(h, nome);
    if(j == NULL){
        printf("%d Jogo inexistente.\n", contador);
    }
    else{
        printf("%d %s %s %s %d %d\n", contador, nome, j -> equipa1, j -> equipa2, j -> score1, j-> score2);
    }
}


/* Funcao que apaga da base de dados um dado jogo. */
void apaga_jogo(int contador, pHash h, pHash_e h_e, pList l){
    pJogo j;
    pEquipa e;
    char nome[MAX];
    scanf(" %[^:\n]", nome);

    j = ht_search(h, nome);
    if(j == NULL){
        printf("%d Jogo inexistente.\n", contador);
    }
    else{
        if(j -> vencedora != NULL){
            e = ht_search_e(h_e, j -> vencedora);
            e -> wins -= 1;
        }
        list_delete(l, j);
        ht_delete(h, nome);
    }
}


/* Funcao que altera as pontuacoes de um dado jogo. */
void altera_score(int contador, pHash h, pHash_e h_e){
    pJogo j;
    char nome[MAX];
    int score1, score2;

    scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);

    j = ht_search(h, nome);
    if(j == NULL){
        printf("%d Jogo inexistente.\n", contador);
    }
    else{  
        pEquipa e, e1;
        pJogo j_atualizado;
        j_atualizado = cria_jogo(j -> nome, j -> equipa1, j -> equipa2, score1, score2);

        if(j -> vencedora != NULL && j_atualizado -> vencedora != NULL){
            if(strcmp(j -> vencedora, j_atualizado -> vencedora) != 0){
                e = ht_search_e(h_e, j_atualizado -> vencedora);
                e -> wins += 1;
                e1 = ht_search_e(h_e, j -> vencedora);
                e1 -> wins -= 1;
                free(j -> vencedora);
                j -> vencedora = dup(j_atualizado -> vencedora);
            }
        }
        else if(j -> vencedora == NULL && j_atualizado -> vencedora != NULL){
            e = ht_search_e(h_e, j_atualizado -> vencedora);
            e -> wins += 1;
            j -> vencedora = dup(j_atualizado -> vencedora); 
        }
        else if(j -> vencedora != NULL && j_atualizado -> vencedora == NULL){
            e = ht_search_e(h_e, j -> vencedora);
            e -> wins -= 1;
            free(j->vencedora);
            j -> vencedora = NULL;
        }
        
        j -> score1 = score1;
        j -> score2 = score2;
        free_jogo(j_atualizado);
        
    }
}


/* Funcao que adiciona uma equipa ah base de dados. */
void adiciona_equipa(int contador, pHash_e h_e){
    char nome_e[MAX];
    scanf(" %[^:\n]", nome_e);

    if(ht_search_e(h_e, nome_e) != NULL){
        printf("%d Equipa existente.\n", contador);
    }
    else{
        pEquipa e = cria_equipa(nome_e);
        ht_insert_e(h_e, e);
    }
}


/* Funcao que lista os dados da equipa dada. */
void lista_equipa(int contador, pHash_e h_e){
    pEquipa e;
    char nome_e[MAX];
    scanf(" %[^:\n]", nome_e);

    e = ht_search_e(h_e, nome_e);
    if(e == NULL){
        printf("%d Equipa inexistente.\n", contador);
    }
    else{
        printf("%d %s %d\n", contador, nome_e, e -> wins);
    }
}


/* Funcao auxiliar para a funcao de ordenacao qsort. */
int cmpstr(const void *p1, const void *p2){
    char **v1, **v2;
    v1 = (char **) p1;
    v2 = (char **) p2;
    return strcmp(*v1, *v2);
}


/* Funcao que lista por ordem lexicografica do nome da equipa as equipas com mais vitorias. */
void lista_melhores(int contador, pHash_e h_e){
    int i, j, k,max_wins = 0, n_max_wins = 0, c = 0;
    char **melhores;
    pLink_e temp;

    for(i = 0; i < h_e -> M; i++){
        temp = h_e -> heads_e[i];
        while(temp){
            if(temp -> e -> wins > max_wins){
                max_wins = temp -> e -> wins;
                n_max_wins = 1;
            }
            else if(temp -> e -> wins == max_wins){
                n_max_wins += 1;
            }
            temp = temp -> next;
        }
    }
    if(n_max_wins != 0){
        melhores = (char**) can_fail_malloc(sizeof(char*) * n_max_wins);
        for(k = 0; k < h_e -> M && c != n_max_wins; k++){
            temp = h_e -> heads_e[k];
            while(temp){
                if(temp -> e -> wins == max_wins){
                    melhores[c] = dup(temp -> e -> nome_e);
                    c++;
                }
                temp = temp -> next;
            }
        }
        qsort(melhores, n_max_wins, sizeof(char*), cmpstr);
        printf("%d Melhores %d\n", contador, max_wins);
        for(j = 0; j < n_max_wins; j++){
            printf("%d * %s\n", contador, melhores[j]);
            free(melhores[j]);
        }
        free(melhores);
    }
}


/* Funcao principal que executa, consoante o comando inserido, uma acao. */
int main(){
    /* Variavel que representa o comando, ou seja, o primeiro careter inserido pelo utilizador. */ 
    char comando;
    /* Variavel que representa o numero da linha do comando de input que originou determinado output. */ 
    int contador = 0;
    /* Inicializacao da variavel que representa a lista de jogos. */
    pList l = list_init();
    /* Inicializacao da variavel que representa a hastable de jogos. */
    pHash h = ht_init(1123);
    /* Inicializacao da variavel que representa a hastable de equipas. */
    pHash_e h_e = ht_init_e(1123);

    while((comando = getchar()) != EOF){
        contador++;
        switch (comando){
            case 'A':
                adiciona_equipa(contador, h_e);
                break;
            case'P':
                lista_equipa(contador, h_e);
                break;
            case 'a':
                adiciona_jogo(contador, h, h_e, l);
                break;
            case 'p':
                lista_jogo(contador, h);
                break;
            case 'l':
                lista_todos(contador, l);
                break;
            case 'r':
                apaga_jogo(contador, h, h_e, l);
                break;
            case 's':
                altera_score(contador, h, h_e);
                break;
            case'g':
                lista_melhores(contador, h_e);
                break;
            case 'x':
                ht_e_destroy(h_e);
                ht_destroy(h);
                free(l);
                return EXIT_SUCCESS;
            default:
                printf("Comando invalido!");
                return EXIT_FAILURE;
        }
        getchar(); 
    }
    return 0; 
}
