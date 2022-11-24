#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "commands.h"
#include "items.h"

/* dimensao das hash tables */
#define HASH_DIM_EQ 20261
#define HASH_DIM_JG 41603

/* numero de linhas de input */
int num_ln = 0;
void incrementa_linha () { num_ln++; }

/* numero de jogos inseridos */
int jgs_ins = 0;

/*  hash tables */
linkJogo *heads_jogos = NULL;
linkEquipa *heads_equipas = NULL;

/* FUNCOES DA HASH */

/* Hash */
int hash_eq(char *str) {
    /* transformcao da string num codigo */
    int h = 0, a = 127;
    for (; *str != '\0'; str++)
        h = (a*h + *str) % HASH_DIM_EQ;
    return h;
}

int hash_jg(char *str) {
    /* transformcao da string num codigo */
    int h = 0, a = 127;
    for (; *str != '\0'; str++)
        h = (a*h + *str) % HASH_DIM_JG;
    return h;
}

/* inicializacao da hash equipas */
void inicializar_hash_equipas () {
    int i;
    heads_equipas = (linkEquipa*)can_fail_malloc(HASH_DIM_EQ*sizeof(linkEquipa));
    for (i=0; i < HASH_DIM_EQ; i++)
        heads_equipas[i] = NULL;
}

/* inicializacao da hash jogos */
void inicializar_hash_jogos () {
    int i;
    heads_jogos = (linkJogo*)can_fail_malloc(HASH_DIM_JG*sizeof(linkJogo));
    for (i=0; i < HASH_DIM_JG; i++)
        heads_jogos[i] = NULL;
}

/* liberta memoria no final do programa */
void liberta_memoria() {
    int i;
    linkJogo j,j_aux;
    linkEquipa e,e_aux;
    for (i=0; i < HASH_DIM_JG; i++) {
        /* liberta hash de jogos */
        if ((heads_jogos != NULL) && (heads_jogos[i] != NULL)) {
            for (j = heads_jogos[i]; j != NULL;) {
                heads_jogos[i] = j->next;
                if (j != NULL) { 
                    j_aux = j;
                    j = j->next;
                    liberta_mem_jogo(j_aux);
                }
            }
        }
    }
    for (i=0; i < HASH_DIM_EQ; i++) {
        /* liberta hash de equipas */
        if ((heads_equipas != NULL) && (heads_equipas[i] != NULL)) {
            for (e = heads_equipas[i]; e != NULL;) {
                heads_equipas[i] = e->next;
                if (e != NULL) {
                    e_aux = e;
                    e = e->next;
                    liberta_mem_equipa(e_aux);
                }
            }
        }
    }
}

/* FUNCOES COMANDO */

/* Comando 'a' */
void adiciona_novo_jogo (char *nome, char *eq1, char *eq2, int s1, int s2) {
    int cdg, cdg_eq1, cdg_eq2;
    cdg = hash_jg(nome);
    cdg_eq1 = hash_eq(eq1);
    cdg_eq2 = hash_eq(eq2);
    incrementa_linha ();
    /* verifica se jogo ja existe */
    if ((heads_jogos != NULL) && (procura_jogo_item(heads_jogos[cdg], nome) != NULL))
        printf("%d Jogo existente.\n",num_ln);
    /* vertifica se equipas nao existem */
    else if ((heads_equipas == NULL) ||
             (procura_equipa_item(heads_equipas[cdg_eq1], eq1) == NULL) ||
              (procura_equipa_item(heads_equipas[cdg_eq2], eq2) == NULL))
        printf("%d Equipa inexistente.\n",num_ln);
    /* cria novo jogo */
    else {  
        if (heads_jogos == NULL)
            inicializar_hash_jogos();
        heads_jogos[cdg] = coloca_jogo(heads_jogos[cdg], nome, eq1, eq2, s1, s2);
        altera_vitorias_equipa (eq1,eq2,s1,s2,1);
        heads_jogos[cdg]->ord = jgs_ins;
        jgs_ins++;
    }
}

/* Comando 'A' */
void adiciona_nova_equipa (char *nome) {
    int cdg = hash_eq(nome);
    incrementa_linha ();
    if (heads_equipas == NULL)
        inicializar_hash_equipas();
    /* verifica se equipa ja existe */
    if (procura_equipa_item(heads_equipas[cdg], nome) != NULL)
        printf("%d Equipa existente.\n",num_ln);
    /* cria nova equipa */
    else {
        heads_equipas[cdg] = coloca_equipa(heads_equipas[cdg], nome);
    }
}

/* Comando 'l' */
void lista_jogos () {
    int i;
    incrementa_linha ();
    /* print dos jogos por ordem de insercao */
    if (heads_jogos != NULL) {
        for (i=0; i < jgs_ins; i++){
            print_jogo(i);
        }
    }
}

/* Comando 'p' */
void procura_jogo (char *nome) {
    int cdg = hash_jg(nome);
    linkJogo jg;
    incrementa_linha ();
    /* verifica se ja foi introduzido algum jogo */
    if (heads_jogos == NULL) {
        printf("%d Jogo inexistente.\n",num_ln);
    }
    else {
        jg = procura_jogo_item(heads_jogos[cdg], nome);
        /* verifica resultado da procura */
        if (jg == NULL)
            printf("%d Jogo inexistente.\n",num_ln);
        else
            printf("%d %s %s %s %d %d\n", num_ln, jg->nome, jg->eq1, jg->eq2, jg->s1, jg->s2);
    }
}

/* Comando 'P' */
void procura_equipa (char *nome) {
    int cdg = hash_eq(nome);
    linkEquipa equipa;
    incrementa_linha ();
    /* verifica se ja foi introduzido alguma equipa */
    if (heads_equipas == NULL) {
        printf("%d Equipa inexistente.\n",num_ln);
    }
    else {
        equipa = procura_equipa_item(heads_equipas[cdg], nome);
        /* verifica resultado da procura */
        if (equipa == NULL)
            printf("%d Equipa inexistente.\n",num_ln);
        else
            printf("%d %s %d\n", num_ln, equipa->nome, equipa->vitorias);
    }
}

/* Comando 'r' */
void apaga_jogo (char *nome) {
    int cdg = hash_jg(nome);
    linkJogo jg;
    incrementa_linha ();
    /* verifica se jogo nao existe */
    if ((heads_jogos == NULL) || (procura_jogo_item(heads_jogos[cdg], nome) == NULL))
        printf("%d Jogo inexistente.\n",num_ln);
    /* apaga se existir */
    else {
        jg = procura_jogo_item(heads_jogos[cdg], nome);
        /* altera num vitorias das equipas envolvidas */
        altera_vitorias_equipa(jg->eq1,jg->eq2,jg->s1,jg->s2,0);
        heads_jogos[cdg] = remove_jogo(heads_jogos[cdg], nome);
    }
}

/* Comando 's' */
void altera_score (char *nome, int s1, int s2) {
    linkJogo jg;
    int cdg = hash_jg(nome);
    incrementa_linha ();
    /* verifica se jogo nao existe */
    if ((heads_jogos == NULL) || (procura_jogo_item(heads_jogos[cdg], nome) == NULL))
        printf("%d Jogo inexistente.\n",num_ln);
    /* altera score se existir */
    else {
        jg = procura_jogo_item(heads_jogos[cdg], nome);
        /* altera num vitorias das equipas envolvidas */
        altera_vitorias_equipa(jg->eq1,jg->eq2,jg->s1,jg->s2,0);
        altera_vitorias_equipa(jg->eq1,jg->eq2,s1,s2,1);
        jg->s1 = s1;
        jg->s2 = s2;
    }
}

/* Comando 'g' */
void lista_vencedores () {
    linkEquipa e;
    char *equipas_vencedoras[HASH_DIM_EQ];
    int i, num_eq = 0;
    unsigned int max_vit = 0;
    incrementa_linha();
    if (heads_equipas != NULL) {
        /* calcula num max de vitorias */
        for (i=0; i < HASH_DIM_EQ; i++) {
            if (heads_equipas != NULL) {
                for (e = heads_equipas[i]; e != NULL; e = e->next) {
                    if (e->vitorias > max_vit)
                        max_vit = e->vitorias;
                }
            }
        }
        printf("%d Melhores %d\n", num_ln, max_vit);
        /* guarda equipas com num max de vitorias */
        for (i=0; i < HASH_DIM_EQ; i++) {
            if (heads_equipas != NULL) {
                for (e = heads_equipas[i]; e != NULL; e = e->next) {
                    if (e->vitorias == max_vit) {
                        equipas_vencedoras[num_eq] = e->nome;
                        num_eq++;
                    }
                }
            }
        }
        /* da sort e print das equipas */
        qsort(equipas_vencedoras, num_eq, sizeof(char *), cstrcmp);
        for (i=0; i < num_eq; i++)
            printf("%d * %s\n",num_ln,equipas_vencedoras[i]);
    }
}


/* FUNCOES AUXILIARES */

/* compara strings com ponteiros void */
int cstrcmp(const void *str1, const void *str2) 
{ 
    const char **resa = (const char **)str1;
    const char **resb = (const char **)str2;
    return strcmp(*resa, *resb);
} 

/* print jogos */
void print_jogo (int ord) {
    int i;
    linkJogo jg;
    /* procura jogo por ordem introducao */
    for (i=0; i < HASH_DIM_JG; i++) {
        if (heads_jogos[i] != NULL) {
            for (jg = heads_jogos[i]; jg != NULL; jg = jg->next) {
                if (jg->ord == ord) {
                    printf("%d %s %s %s %d %d\n", num_ln, jg->nome, jg->eq1, jg->eq2, jg->s1, jg->s2);
                    return;
                }
            }
        }
    }
}

/* altera (atribui ou retira) vitorias a uma equipa */
void altera_vitorias_equipa (char *eq1, char *eq2, int s1, int s2, int est) {
    int cdg_venc = -1;
    linkEquipa vencedor;
    /* calcula vencedor */
    if (s1 > s2) {
        cdg_venc = hash_eq(eq1);
        vencedor = procura_equipa_item(heads_equipas[cdg_venc],eq1);
    }
    else if (s1 < s2) {
        cdg_venc = hash_eq(eq2);
        vencedor = procura_equipa_item(heads_equipas[cdg_venc],eq2);
    }
    /* alteria vitorias se nao for empate */
    if (cdg_venc != -1) {
        /* estado != 0, atribui vitoria */
        if (est)
            vencedor->vitorias++;
        /* estado = 0, retira vitoria */
        else
            vencedor->vitorias--;
    }
}