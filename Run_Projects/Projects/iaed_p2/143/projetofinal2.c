#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "hash.h"

#define MAXCHARS 1024

Hash_Jogos *add_novo_jogo(int NL, Hash_Jogos *hash_j, Hash_Equipa *hash_e, equipa *e);
void todos_jogos(int NL, Hash_Jogos *J, jogo *j);
void procura_jogo(int NL, Hash_Jogos *J, jogo *j);
void apaga_jogo(int NL, Hash_Jogos *J, jogo *j);
void altera_score(int NL, Hash_Jogos *J, jogo *j);
Hash_Equipa *add_nova_equipa(int NL, Hash_Equipa *hash);
void procura_equipa(int NL, Hash_Equipa *E, equipa *e);
void equipas_ganharam_mais_jogos(int NL, Hash_Equipa *E, equipa *e);

void quicksort(jogo *J, int first, int last);
int compara(const void *a, const void *b);


int main(){

    
    int NL = 1; /*variavel para contar as linhas do input*/
    char ch_main; 
    Hash_Equipa *Equipas; /* inicializacao do ponteiro *Equipas do tipo Hash_Equipa */
    Hash_Jogos *Jogos; /* inicializacao do ponteiro *Jogos do tipo Hash_Jogos */



    /*alocar espaco para o ponteiro Equipas*/
    Equipas = (Hash_Equipa*) malloc (sizeof(Hash_Equipa));

    /*tamanho inicial da hash*/
    Equipas->tam_hash = 11;

    /*iniciar o ponteiro das equipas*/
    Equipas->equipas = Equipa_init(Equipas->tam_hash, &Equipas->tam_hash, Equipas->equipas); 

    /*contagem do numero de equipas que sao inseridas*/
    Equipas->n_equipas = 0;




    /*alocar espaco para o ponteiro Jogos */
    Jogos = (Hash_Jogos*) malloc (sizeof(Hash_Jogos));

    /*tamanho inicial da hash*/
    Jogos->tam_hash = 11;

    /*iniciar o ponteiro dos jogos*/
    Jogos->jogos = Jogo_init(Jogos->tam_hash, &Jogos->tam_hash, Jogos->jogos);

    /*conta a ordem do input dos jogos para depois poder ordenar*/
    Jogos->n_jogos = 0;

    /*conta o numero de jogos*/
    Jogos->numero_jogos = 0;

   


   
    while((ch_main = getchar()) != EOF){
    

        switch(ch_main){

            case 'a':
            Jogos = add_novo_jogo(NL, Jogos, Equipas, Equipas->equipas);
            NL++;
            break;

            case 'l':
            todos_jogos(NL, Jogos, Jogos->jogos);
            NL++;
            break;

            case 'p':
            procura_jogo(NL, Jogos, Jogos->jogos);
            NL++;
            break;

            case 'r':
            apaga_jogo(NL, Jogos, Jogos->jogos);
            NL++;
            break;

            case 's':
            altera_score(NL, Jogos, Jogos->jogos);
            NL++;
            break;

            case 'A':
            Equipas = add_nova_equipa(NL, Equipas);
            NL++;
            break;

            case 'P':
            procura_equipa(NL, Equipas, Equipas->equipas);
            NL++;
            break;

            case 'g':
            equipas_ganharam_mais_jogos(NL, Equipas, Equipas->equipas);
            NL++;
            break;

            case 'x':
            Equipa_FREE(Equipas->tam_hash, Equipas->equipas);
            Jogo_FREE(Jogos->tam_hash, Jogos->jogos);
            free(Equipas);
            free(Jogos);
            return 0;
        }
    } 
    return 0;
}


/*funcao que adiciona nova equipa*/
Hash_Equipa *add_nova_equipa(int NL, Hash_Equipa *hash){
    

    char nome_equipa[MAXCHARS];
    equipa p;


    scanf(" %1023[^:\n]", nome_equipa);
    
    
    
    if (Equipa_search(hash->tam_hash, nome_equipa, hash->equipas) == NULL){
        p = (equipa) malloc (sizeof(struct Equipa)); /* alocar memoria para uma equipa */
        p->nome = (char*) malloc(sizeof(char)*(strlen(nome_equipa) + 1)); /* alocar memoria para o nome da equipa */
        strcpy(p->nome, nome_equipa);

        p->n_vitorias = 0; /* inicializar o numero de vitorias a 0 */

        Equipa_insert(hash->tam_hash, hash->equipas, p); /*inserir a equipa na hash */
        hash->n_equipas++;
        

        /* se o numero de equipas atingir metade do tamanho da hash, aumenta-se o tamanho da hash para o dobro */
        if(hash->n_equipas == (hash->tam_hash) / 2){
            hash->equipas = Equipa_expand(&hash->tam_hash, hash->equipas);
            
        }
    }
    else{
        printf("%d Equipa existente.\n", NL);
    }
    return hash;
}



/*funcao procura uma equipa*/
void procura_equipa(int NL, Hash_Equipa *E, equipa *e){
    
    
    char nome_equipa[MAXCHARS];
    equipa e1;

    scanf(" %1023[^:\n]", nome_equipa);
   
   
    e1 = Equipa_search(E->tam_hash, nome_equipa, e);

    
    if(e1 != NULL){
        printf("%d %s %d\n", NL, e1->nome, e1->n_vitorias);
        return;
    }
    
    
    printf("%d Equipa inexistente.\n", NL); 
}




/*funcao que insere um novo jogo*/
Hash_Jogos *add_novo_jogo(int NL, Hash_Jogos *hash_j, Hash_Equipa *hash_e, equipa *e){
    

    char nome_jogo[MAXCHARS];
    char equipa1[MAXCHARS];
    char equipa2[MAXCHARS];
    int score1;
    int score2;
   
    jogo p;
    equipa e1;
    equipa e2;

    

    scanf(" %1023[^:\n]:%1023[^:\n]:%1023[^:\n]:%d:%d", nome_jogo, equipa1, equipa2, &score1, &score2);
    

    if (Jogo_search(hash_j->tam_hash, nome_jogo, hash_j->jogos) == NULL){

        /* procurar equipas com os nomes 'equipa1' e 'equipa2' */
        e1 = Equipa_search(hash_e->tam_hash, equipa1, e);
        e2 = Equipa_search(hash_e->tam_hash, equipa2, e);

        if (e1 != NULL && e2 != NULL){
            
            p = (jogo) malloc (sizeof(struct Jogo)); /* alocar memoria para um jogo */
            p->nome = (char*) malloc(sizeof(char)*(strlen(nome_jogo) + 1)); 
            strcpy(p->nome, nome_jogo);

            
            p->equipa1 = e1;
            p->equipa2 = e2;


            p->ordem_input = hash_j->n_jogos; /* atualiza a ordem de input para ordenar jogos futuramente */

            p->score_equipa1 = score1;
            p->score_equipa2 = score2;


            if(score1 > score2){
                e1->n_vitorias++;
            }

            else if(score1 < score2){
                e2->n_vitorias++;
            }
            

            Jogo_insert(hash_j->tam_hash, hash_j->jogos, p); /*inserir o jogo na hash */
            hash_j->n_jogos++;
            hash_j->numero_jogos++;
            

            /* se o numero de jogos atingir metade do tamanho da hash, aumenta-se o tamanho da hash para o dobro */
            if(hash_j->n_jogos == (hash_j->tam_hash) / 2){
            hash_j->jogos = Jogo_expand(&hash_j->tam_hash, hash_j->jogos);
            }  
        
        }
        else{    
            printf("%d Equipa inexistente.\n", NL);
        }
    }
    else{
        printf("%d Jogo existente.\n", NL);
    }
    return hash_j;
}




/*funcao que lista todos os jogos por ordem de input*/
void todos_jogos(int NL, Hash_Jogos *J, jogo *j){


    unsigned int i;
    unsigned int s = 0;
    int x;
    jogo *v_jogos;


    v_jogos = (jogo*) malloc(sizeof(jogo) * J->numero_jogos); /* alocar memoria para o vetor v_jogos */

    for(i = 0; i < J->tam_hash; i++){
        if(j[i] != NULL){
           v_jogos[s] = j[i]; /* introduzir os jogos existentes no vetor v_jogos */
           s++;
        }
    }

    /* ordenar os jogos pela sua ordem de input */
    quicksort(v_jogos, 0, J->numero_jogos - 1);

    for(x = 0; x < J->numero_jogos; x++){
        printf("%d %s %s %s %d %d\n", NL, v_jogos[x]->nome, v_jogos[x]->equipa1->nome, v_jogos[x]->equipa2->nome, v_jogos[x]->score_equipa1, v_jogos[x]->score_equipa2);
    }

    free(v_jogos);
}


/* funcao usada para ordenar os jogos pela sua ordem de input */
void quicksort(jogo *J, int first, int last){
    int i, j, pivot;
    jogo temp;

    if(first < last){
        pivot = first;
        i = first;
        j = last;

        while(i < j){
            while(J[i]->ordem_input <= J[pivot]->ordem_input && i<last)
                i++;
            while(J[j]->ordem_input > J[pivot]->ordem_input)
                j--;
            if(i < j){
                temp = J[i];
                J[i] = J[j];
                J[j] = temp;
            }
        }

        temp = J[pivot];
        J[pivot] = J[j];
        J[j] = temp;
        quicksort(J, first, j-1);
        quicksort(J, j+1, last);

    }
}


/*funcao que procura todos os jogos*/
void procura_jogo(int NL, Hash_Jogos *J, jogo *j){
    


    char nome_jogo[MAXCHARS];
    jogo j1;

    scanf(" %1023[^:\n]", nome_jogo);


    /* procurar jogo com nome 'nome_jogo' */
    j1 = Jogo_search(J->tam_hash, nome_jogo, j);

    
    if(j1 != NULL){
        printf("%d %s %s %s %d %d\n", NL, j1->nome, j1->equipa1->nome, j1->equipa2->nome,
        j1->score_equipa1, j1->score_equipa2);
        return;
    }
        
    
    printf("%d Jogo inexistente.\n", NL); 
}



/*funcao que apaga um jogo*/
void apaga_jogo(int NL, Hash_Jogos *J, jogo *j){
    
    char nome_jogo[MAXCHARS];
    jogo p;
    
    scanf(" %1023[^:\n]", nome_jogo);

    /* procurar jogo com nome 'nome_jogo' */
    p = Jogo_search(J->tam_hash, nome_jogo, j);

    if(p != NULL){

        if(p->score_equipa1 > p->score_equipa2){
            p->equipa1->n_vitorias--;
            Jogo_delete(J->tam_hash, nome_jogo, j);
            J->numero_jogos--;

        }
        else if(p->score_equipa1 < p->score_equipa2){
            p->equipa2->n_vitorias--;
            Jogo_delete(J->tam_hash, nome_jogo, j);
            J->numero_jogos--;
        }
        else{
            Jogo_delete(J->tam_hash, nome_jogo, j);
            J->numero_jogos--;
        }
        return;
    }
    printf("%d Jogo inexistente.\n", NL);
}



/*funcao que altera o score*/
void altera_score(int NL, Hash_Jogos *J, jogo *j){
    

    char nome_jogo[MAXCHARS];
    int score1, score2;
    jogo jogo;


    scanf(" %1023[^:\n]:%d:%d", nome_jogo, &score1, &score2);

    /* procurar o jogo com o nome 'nome_jogo' */
    jogo = Jogo_search(J->tam_hash, nome_jogo, j);
    

    if(jogo != NULL){


        if(jogo->score_equipa1 > jogo->score_equipa2){
            if(score1 < score2){
                jogo->equipa2->n_vitorias++;
                jogo->equipa1->n_vitorias--;
            }
            else if(score1 == score2){
                jogo->equipa1->n_vitorias--;
            }
        }
        else if(jogo->score_equipa1 < jogo->score_equipa2){
            if(score1 > score2){
                jogo->equipa1->n_vitorias++;
                jogo->equipa2->n_vitorias--;
            }
            else if(score1 == score2){
                jogo->equipa2->n_vitorias--;
            }
        }
        else if(jogo->score_equipa1 == jogo->score_equipa2){
            if(score1 < score2){
                jogo->equipa2->n_vitorias++;
            }
            if(score1 > score2){
                jogo->equipa1->n_vitorias++;
            }
        }

        jogo->score_equipa1 = score1;
        jogo->score_equipa2 = score2;
        return;
    }    
    printf("%d Jogo inexistente.\n", NL);
}




/*funcao que mostra equipas vencedoras*/
void equipas_ganharam_mais_jogos(int NL, Hash_Equipa *E, equipa *e){

    unsigned int i, x;
    int s = 0; /* contador de equipas que ganharam mais jogos*/
    int t = 0; /* indice do vetor */
    int max_vitorias = 0; /* variavel que vai ser igual ao numero maximo de vitorias existentes */

    char **vetor_strings; /* vetor que armazena os nomes das equipas com o numero maximo de vitorias */

    
    /* se nao houver equipas termina a funcao */
    if(E->n_equipas == 0) return;


    /* procurar o numero maximo de vitorias */
    for(x = 0; x < E->tam_hash; x++){
        if(e[x]){
            if(e[x]->n_vitorias > max_vitorias){
                s = 0; /* inicia a contagem a 0 caso haja um numero maximo de vitorias superior ao anterior */
                max_vitorias = e[x]->n_vitorias;
            }
            if(e[x]->n_vitorias == max_vitorias){
                s++;
            }
        }
    }

    /* alocar espaco para o vetor que ira' alocar os nomes das equipas com o numero maximo de vitorias */
    vetor_strings = (char**) malloc (sizeof(char*) * s);  


    for(i = 0; i < E->tam_hash; i++){
        if(e[i]){
            if(e[i]->n_vitorias == max_vitorias){
                /* alocar o nome da equipa em vetor_strings */
                vetor_strings[t] = (char*) malloc(sizeof(char) * strlen(e[i]->nome) + 1);
                strcpy(vetor_strings[t], e[i]->nome);
                t++; 
            }
        }
    }

    /* ordenar lexicograficamente as equipas com o numero maximo de vitorias */
    qsort(vetor_strings, s, sizeof(char*), compara);

    
    printf("%d Melhores %d\n", NL, max_vitorias);


    for(t = 0; t < s; t++){
        printf("%d * %s\n", NL, vetor_strings[t]);
    }


    for(t = 0; t < s; t++){
        free(vetor_strings[t]);
    }
    free(vetor_strings);
}


/* funcao para comparar strings */
int compara(const void *a, const void *b){

    int i;
    const char **ia = (const char**) a;
    const char **ib = (const char**) b;

    i = strcmp(*ia, *ib);

    return i;
}