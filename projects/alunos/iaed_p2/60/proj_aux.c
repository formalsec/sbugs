#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "proj_aux.h"


/* obter indice da hashtable */
int hash(char *nome) {
    int h = 0, a = 127;
    for (; *nome != '\0'; nome++)
        h = (a*h + *nome) % M;
    return h;
}


/* inicializar hashtable de equipas colocando a sua head a null*/
elink * init_eq() {
    int i;
    elink *heads_eq;
    heads_eq = can_fail_malloc(M*sizeof(struct equipa));
    for (i = 0; i < M; i++)
        heads_eq[i] = NULL;
    return heads_eq;
}


/* inicializar hashtable de jogos colocando a sua head a null */
jlink * init_jog() {
    int i;
    jlink *heads_j;
    heads_j = can_fail_malloc(M*sizeof(struct jogo));
    for (i = 0; i < M; i++)
        heads_j[i] = NULL;
    return heads_j;
}


/*  SEARCH
    int i = hash(equipa->nome);
    return lookup(heads[i], nome);
*/


/* recebe ponteiro para lista da hashtable e nome de equipa
   procura a equipa na lista e devolve o seu valor */
eq lookup_eq(elink head, char* nome) {
    elink e;
    for(e = head; e != NULL; e = e->next){
        if(strcmp(e->eq->nome, nome) == 0)
            return e->eq;
    }
    return NULL;
}

/* recebe ponteiro para lista da hashtable e nome de jogos
   procura a jogo na lista e devolve o seu valor */
j lookup_j(jlink head, char* nome) {
    jlink j;
    for(j = head; j != NULL; j = j->next)
        if(strcmp(j->jog->nome, nome) == 0)
            return j->jog;
    return NULL;
}

/* insere equipa num determinado indice da hashtable */
elink insertBegin_eq(elink head, eq equipa) {
    elink eq = can_fail_malloc(sizeof(struct equipa));
    eq->eq = equipa;
    eq->next = head;
    return eq; /* devolve a nova head */
}

/* insere jogo num determinado indice da hashtable */
jlink insertBegin_j(jlink head, j jogo) {
    jlink j = can_fail_malloc(sizeof(struct jogo));
    if (head != NULL)
        head->prev = j;

    j->jog = jogo;
    j->next = head;
    return j;

}


/* adiciona um novo jogo */
void executa_a(jlink *heads_j, list_j *list_j, elink *heads_eq, int nl) {
    /* inicializar variaveis */
    char nome_jogo[MAX_STR];
    char nome_eq1[MAX_STR];
    char nome_eq2[MAX_STR];
    int score1, score2;
    j jogo;
    int i;
    int j, k;
    eq eq1, eq2;
    /* recebe input */
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome_jogo, nome_eq1, nome_eq2, &score1, &score2);

    /* calcula indice dos valores das respetivas hashtables */
    i = hash(nome_jogo);
    j = hash(nome_eq1);
    k = hash(nome_eq2);

    /* verifica se o jogo ja existe */
    if (lookup_j(heads_j[i], nome_jogo) != NULL) {
        printf ("%d Jogo existente.\n", nl);
    }
    /* verifica se ambas as equipas existem */
    else if ((eq1 = lookup_eq(heads_eq[j], nome_eq1)) == NULL || 
        (eq2 = lookup_eq(heads_eq[k], nome_eq2)) == NULL) {
        printf("%d Equipa inexistente.\n", nl);
    }
    else {
        /* aloca espaco em memoria para o jogo */
        jogo = can_fail_malloc(sizeof(struct jogo));
        /* guarda os seus valores */
        jogo->equipa1 = eq1;
        jogo->equipa2 = eq2;
        jogo->score1 = score1;
        jogo->score2 = score2;
        /* aloca espaco em memoria para o nome do jogo */
        jogo->nome = (char*)can_fail_malloc(sizeof(char)*(strlen(nome_jogo)+1));
        strcpy(jogo->nome, nome_jogo);
        /* insere jogo na lista da hashtable correspondente ao indice calculado */
        heads_j[i] = insertBegin_j(heads_j[i], jogo);
    
        /* adicionar jogo a lista */
        insertEndList(list_j, jogo);

        /* altera o score da equipa vencedora */
        if (score1 < score2) {
            eq2->vitorias += 1;
        }
        else if(score1 > score2) {
            eq1->vitorias += 1;
        }
    }
}


/* adiciona uma nova equipa */
void executa_A(elink *heads_eq, int nl) {
    /* inicializar variaveis */
    char nome_eq[MAX_STR];
    int i;
    eq equipa;
    int j;
    eq eq;
    /* recebe input */
    scanf(" %[^:\n]", nome_eq);
    /* calcula indice dos da equipa para a hashtable */
    j = hash(nome_eq);

    if ((eq = lookup_eq(heads_eq[j], nome_eq)) != NULL)
        printf ("%d Equipa existente.\n", nl);


    /* adicionar equipa a hashtable */
    else {
        equipa = can_fail_malloc(sizeof(struct equipa));
        equipa->nome = (char*)can_fail_malloc(sizeof(char)*(strlen(nome_eq)+1));
        strcpy(equipa->nome, nome_eq);
        equipa->vitorias = 0;
        i = hash(equipa->nome);
        heads_eq[i] = insertBegin_eq(heads_eq[i], equipa);
    }
}


/* lista todos os jogos */
void executa_l(list_j *list_j, int nl) {
    jlink t;
    /* percorre lista de jogos e altera imprime as informacoes relativas a cada jogo */
    for(t = list_j->head; t != NULL; t = t->next)
        printf("%d %s %s %s %d %d\n", nl, t->jog->nome, t->jog->equipa1->nome,
            t->jog->equipa2->nome, t->jog->score1, t->jog->score2);
}


/* procura um jogo com o nome dado */
void executa_p(jlink *heads_j, int nl) {
    char nome_jogo[MAX_STR];
    int i;
    j jog;

    scanf(" %[^:\n]", nome_jogo);
    /* obtem indice do jogo na hashtable */
    i = hash(nome_jogo);
    /* verifica se o jogo nao existe */
    if ((jog = lookup_j(heads_j[i], nome_jogo)) == NULL)
        printf ("%d Jogo inexistente.\n", nl);
    else {
        printf("%d %s %s %s %d %d\n", nl, jog->nome, jog->equipa1->nome, jog->equipa2->nome,
            jog->score1, jog->score2);
    }
}

/* procura uma equipa com o nome dado */
void executa_P(elink *heads_eq, int nl) {
    char nome_eq[MAX_STR];
    int i;
    eq equipa;

    scanf(" %[^:\n]", nome_eq);

    i = hash(nome_eq);
    if ((equipa = lookup_eq(heads_eq[i], nome_eq)) == NULL)
        printf ("%d Equipa inexistente.\n", nl);
    else {
        printf("%d %s %d\n", nl, equipa->nome, equipa->vitorias);
    }

} 

/* altera o score de um jogo dado o nome */
void executa_s(jlink *heads_j, int nl) {    
    char nome_jogo[MAX_STR];
    int score1, score2;
    j jogo;
    int i;

    scanf(" %[^:\n]:%d:%d", nome_jogo, &score1, &score2);
    i = hash(nome_jogo);
    /* erros */
    if (( jogo = lookup_j(heads_j[i], nome_jogo)) == NULL)
        printf ("%d Jogo inexistente.\n", nl);

    else {
        /* se a equipa1 fosse vencedora e deixa-se de o ser, retira-se a vitoria */
        if (jogo->score1 > jogo->score2 && score1 <= score2)
            jogo->equipa1->vitorias -= 1;
        /* se a equipa2 fosse vencedora e deixa-se de o ser, retira-se a vitoria */
        else if (jogo->score1 < jogo->score2 && score1 >= score2)
            jogo->equipa2->vitorias -= 1;
        /* se a equipa1 passar a ser vencedora, adiciona-se a vitoria */
        if (jogo->score1 <= jogo->score2 && score1 > score2)
            jogo->equipa1->vitorias += 1;    
        /* se a equipa2 passar a ser vencedora, adiciona-se a vitoria */
        else if (jogo->score1 >= jogo->score2 && score1 < score2)
            jogo->equipa2->vitorias += 1;
        /* altera-se no jogo o valor dos scores */
        jogo->score1 = score1;
        jogo->score2 = score2;
    }    
}


/* apaga um jogo dado um nomes */
void executa_r(jlink *heads_j, list_j *list_j, int nl) {
    char nome_jogo[MAX_STR];
    int i;
    j jogo;

    scanf(" %[^:\n]", nome_jogo);
    i = hash(nome_jogo);
    if (( jogo = lookup_j(heads_j[i], nome_jogo)) == NULL)
        printf ("%d Jogo inexistente.\n", nl);
    else{
        /* retirar vitoria da equipa que tinha ganhado o jogo */
        if (jogo->score1 > jogo->score2)
            jogo->equipa1->vitorias -= 1;
        else if (jogo->score1 < jogo->score2)
            jogo->equipa2->vitorias -=1;
        
        heads_j[i] = delete_jog(heads_j[i], nome_jogo);
        *list_j = delete_j(*list_j, nome_jogo);
    }
}

/* funcao auxiliar que remove jogo da hashtable */
jlink delete_jog(jlink head, char* nome) {
    jlink jogo;
    for(jogo = head; jogo != NULL; jogo = jogo->next) {
        if(strcmp(jogo->jog->nome, nome) == 0) {
            if(jogo == head)
                head = jogo->next;
            else
                jogo->prev->next = jogo->next;
            if (jogo->next != NULL)
                jogo->next->prev = jogo->prev;
            
            free(jogo);
            break;
        }
    }
    return head;
}

/* funcao auxiliar que remove jogo da hashtable */
list_j delete_j(list_j list_j, char* nome) {
    jlink jogo;
    for(jogo = list_j.head; jogo != NULL; jogo = jogo->next) {
        if(strcmp(jogo->jog->nome, nome) == 0) {
            if(jogo == list_j.head)
                list_j.head = jogo->next;
            else
                jogo->prev->next = jogo->next;
            if (jogo->next != NULL)
                jogo->next->prev = jogo->prev;
            else
                list_j.tail = jogo->prev;

            free(jogo->jog->nome);
            free(jogo->jog);
            free(jogo);
            break;
        }
    }
    return list_j;
}



/* insere jogo no fim da lista */
list_j * insertEndList(list_j *list_j, j jogo) {
    /* aloca espaco para o no */
    jlink j = can_fail_malloc(sizeof(struct node_jog));
    /* coloca o jogo */
    j->jog = jogo;
    j->next = NULL;
    if (list_j->head == NULL) {
        list_j->head = j;
    }
    else
        list_j->tail->next = j;

    j->prev = list_j->tail;
    list_j->tail = j;
    return list_j;
}

/* funcao que liberta a hastable das equipas */
void free_hash_eq(elink *heads_eq) {
    int i;
    for(i = 0; i < M; i++)
        free_list_eq(heads_eq[i]);
    free(heads_eq);
}


/* funcao que liberta a lista dos indice das hashtables das equipas */
void free_list_eq(elink head) {
    elink eq;
    while (head != NULL) {
        eq = head->next;
        free(head->eq->nome);
        free(head->eq);
        free(head);
        head = eq;
    }
}

/* funcao que liberta a hastable dos jogos */
void free_hash_jog(jlink *heads_j) {
    int i;
    for (i = 0; i < M; i++)
        free_list_jog(heads_j[i]);
    free(heads_j);
}

/* funcao que liberta a lista dos indice das hashtables jogos */
void free_list_jog(jlink head) {
    jlink j;
    while (head != NULL) {
        j = head->next;
        free(head->jog->nome);
        free(head->jog);
        free(head);
        head = j;
    }
}

/* funcao que liberta a lista de jogos */
void free_list_j(list_j *list_j) {
    jlink j;
    while (list_j->head != NULL) {
        j= list_j->head->next;
        free(list_j->head);
        list_j->head = j;
    }
}
