#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sistema.h"

/** Verifica se ha espaco em branco e consome-o
 *  Caso nao haja relata assertion */
char rd_ws(void) {
    const int wesp = getchar();
    assert(!(wesp != ' ' && wesp != '\n' && wesp != EOF));
    return wesp;
}

/** Le o comando feito pelo utilizador e o espaco este e o que e dado
 *  Caso o comando nao tenha argumentos absorve tambem o caracter new line */
int rd_cmd(void) {
    const int c = getchar();
    rd_ws();
    return c;
}

/** Inicializa sistema alocando o espaco suficiente para as tabelas e para a lista
 *  Devolve o sistema formado */
sistema* inic_sistema(void){
    sistema* s = can_fail_malloc(sizeof(sistema));
    s->tb_j = inic_jogos(INIC_CAP_J);       /* inicializa tabela de jogos */
    s->tb_e = inic_equipas(INIC_CAP_E);     /* inicializa tabela de equipas */
    s->l = inic_lista();                    /* inicializa lista de jogos inseridos */
    return s;
}

/** Comando a: Adiciona um novo jogo ao sistema - tabela de jogos
 *  Caso o jogo exista ou caso alguma equipa nao pertenca ao sistema relata erro */
void cmd_a(size_t count, sistema* s){
    char buf1[MAX_NAMEJ_SZ], buf2[MAX_FLAG_SZ], buf3[MAX_FLAG_SZ];
    size_t s1, s2;
    int h1, h2;
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%lu:%lu", buf1, buf2, buf3, &s1, &s2);
    /* caso existe este jogo no sistema relata erro! */
    if(procura_j(buf1, s->tb_j) != INVALID_J){
        printf("%lu Jogo existente.\n", count); return;}
    /* procura equipas envolvidas no jogo a inserir */
    h1 = procura_e(buf2, s->tb_e); h2 = procura_e(buf3, s->tb_e);
    /* caso nao exista alguma equipa no sistema relata erro! */
    if(h1 == INVALID_E || h2 == INVALID_E)
        printf("%lu Equipa inexistente.\n", count);
    else{   /* caso as equipas pertencem ao sistema e sao diferentes */
        if (!equal_e(buf2, buf3)){
            /* cria jogo, alocando o espaco necessario */
            jogo* j = make_jogo(buf1, buf2, buf3, s1, s2);
            /* insere jogo na tabela de jogos */
            s->tb_j = insere_j(j, s->tb_j); 
            /* incrementa numero de vitorias da equipa vencedora */
            if (s1 > s2) s->tb_e->tb[h1]->vitorias++;
            if (s1 < s2) s->tb_e->tb[h2]->vitorias++;
            /* adiciona jogo a lista de jogos inseridos */
            push_last(j, s->l);
        }
    }
}

/** Comando A: Adiciona uma nova equipa ao sistema - tabela de equipas
 *  Caso ja exista esta equipa no sistema relata erro */
void cmd_A(size_t count, sistema* s){
    char buf1[MAX_FLAG_SZ];
    scanf("%[^:\n]", buf1);
    /* procura a equipa existe */
    if (procura_e(buf1, s->tb_e) != INVALID_E)   /* se nao relata erro! */
        printf("%lu Equipa existente.\n", count);  
    else                            /* caso exista insere equipa no sistema */
        s->tb_e = insere_e(0, buf1, s->tb_e);
}

/** Comando p: Procura um jogo no sistema - tabela de jogos
 *  Caso o jogo nao exista no sistema relata erro */
void cmd_p(size_t count, sistema* s){
    char buf1[MAX_NAMEJ_SZ];
    int h;
    scanf("%[^:\n]", buf1);
    h = procura_j(buf1, s->tb_j);   /* procura se o jogo existe */
    if (h != INVALID_J)             /* caso exista imprime caracteristicas do jogo */
        printf("%lu %s %s %s %lu %lu\n", count, buf1,
        s->tb_j->tb[h]->equipa1, s->tb_j->tb[h]->equipa2,
        s->tb_j->tb[h]->score1, s->tb_j->tb[h]->score2);
    else                            /* se nao relata erro! */
        printf("%lu Jogo inexistente.\n", count);
}

/** Comando P: Procura uma equipa no sistema - tabela de equipas
 *  Caso a equipa nao exista no sistema relata erro */
void cmd_P(size_t count, sistema* s){
    char buf1[MAX_FLAG_SZ];
    int h;
    scanf("%[^:\n]", buf1);
    h = procura_e(buf1, s->tb_e);   /* procura se a equipa existe no sistema */
    if (h != INVALID_J)             /* caso existe imprime caracteristicas da equipa */
        printf("%lu %s %lu\n", count, buf1, s->tb_e->tb[h]->vitorias);
    else                            /* se nao relata erro! */
        printf("%lu Equipa inexistente.\n", count);
}

/*  Auxiliar&Comando s. Atualiza pontuacao de um jogo da tabela de jogos e lista */
void atualiza_score(int h, size_t s1, size_t s2, sistema* s){
    node* n = procura_l(s->tb_j->tb[h]->nome, s->l);
    /* atualiza pontuacoes */
    n->jogo->score1 = s1; n->jogo->score2 = s2;
    s->tb_j->tb[h]->score1 = s1;
    s->tb_j->tb[h]->score2 = s2;
}

/** Comando s: Altera a pontuacao de um jogo afetando o numero de vitorias das equipas
 *  Caso o jogo nao exista no sistema relata erro */
void cmd_s(size_t count, sistema* s){
    char buf1[MAX_NAMEJ_SZ];
    size_t s1, s2;
    int h, he1, he2; 
    scanf("%[^:\n]:%lu:%lu", buf1, &s1, &s2);
    h = procura_j(buf1, s->tb_j);   /* procura se o jogo existe */
    if (h != INVALID_J){            /* caso o jogo exista procede a alteracao */
        he1 = procura_e(s->tb_j->tb[h]->equipa1, s->tb_e);  /* procura equipas */
        he2 = procura_e(s->tb_j->tb[h]->equipa2, s->tb_e);  /* envolvidas */
        
        /* atualiza numero de vitorias das equipas envolvidas */
        if (s1 < s2 && s->tb_j->tb[h]->score1 >= s->tb_j->tb[h]->score2){
            if (s->tb_j->tb[h]->score1 > s->tb_j->tb[h]->score2)
		        s->tb_e->tb[he1]->vitorias--;    
            s->tb_e->tb[he2]->vitorias++;
        }
        if (s1 == s2 && s->tb_j->tb[h]->score1 != s->tb_j->tb[h]->score2){
            if (s->tb_j->tb[h]->score1 > s->tb_j->tb[h]->score2)
		        s->tb_e->tb[he1]->vitorias--;
	        else
		        s->tb_e->tb[he2]->vitorias--;
        }
        if (s1 > s2 && s->tb_j->tb[h]->score1 <= s->tb_j->tb[h]->score2){
            if (s->tb_j->tb[h]->score1 < s->tb_j->tb[h]->score2)
		        s->tb_e->tb[he2]->vitorias--;    
            s->tb_e->tb[he1]->vitorias++;
        }
        atualiza_score(h, s1, s2, s);   /* atualiza pontuacao do jogo */

    }else                           /* se nao relata erro! */
        printf("%lu Jogo inexistente.\n", count);
}

/*  Comando l: Lista todos os jogos pela ordem em que foram introduzidos no sistema */
void cmd_l(size_t count, sistema* s){
    node* tmp;                      /* percorre a lista de jogos inseridos */
    for (tmp = s->l->head; tmp; tmp = tmp->next) /* imprime todos os jogos */
        printf("%lu %s %s %s %lu %lu\n", count, tmp->jogo->nome,
            tmp->jogo->equipa1, tmp->jogo->equipa2,
            tmp->jogo->score1, tmp->jogo->score2);
}

/** Comando r: Apaga um jogo. Remove-o definitivamente do sistema - tabela de jogos
 *  Caso o jogo nao exista no sistema relata erro */
void cmd_r(size_t count, sistema* s){
    char buf1[MAX_NAMEJ_SZ];
    int h, he1, he2;
    scanf("%[^:\n]", buf1);
    h = procura_j(buf1, s->tb_j);   /* procura se o jogo existe */
    if (h == INVALID_J)             /* caso negativo relata erro! */
        printf("%lu Jogo inexistente.\n", count);
    else{                           /* caso afirmativo procede a remocao */
        node* n = procura_l(buf1, s->l);
        he1 = procura_e(s->tb_j->tb[h]->equipa1, s->tb_e);
        he2 = procura_e(s->tb_j->tb[h]->equipa2, s->tb_e);
        /* atualiza o numero de vitorias das duas equipas */
        if (s->tb_j->tb[h]->score1 > s->tb_j->tb[h]->score2)
            s->tb_e->tb[he1]->vitorias--;
        if (s->tb_j->tb[h]->score1 < s->tb_j->tb[h]->score2)
            s->tb_e->tb[he2]->vitorias--;
        remove_jogo(h, s->tb_j);    /* remocao do jogo da tabela de jogos */
        remove_node(n, s->l);       /* remocao do no que apontava para o jogo */
    }
}

/*  Comando g: Encontra as equipas que venceram mais jogos */
void cmd_g(size_t count, sistema* s){
    char** melhores;           /* para guarda dos nomes das melhores equipas */
    size_t i, max, n;
    if (s->tb_e->sz == 0) return;   /* nada no caso de nao existirem equipas */
    max = max_vitorias(s->tb_e);    /* numero maximo de vitorias */
    n = n_strings(max, s->tb_e);    /* numero de equipas que sao as melhores */
    melhores = encontra_melhores(n, max, s->tb_e);   /* ja ordenado */
    printf("%lu Melhores %lu\n", count, max);
    for (i = 0 ; i < n; i++){
        printf("%lu * %s\n", count, melhores[i]);
        free(melhores[i]);  /* liberta espaco do nome da equipa */
    }
    free(melhores);         /* por fim, liberto vector de nomes da equipa */
}

/*  Liberta toda memoria alocada no programa */
void free_sistema(sistema* s){
    free_lista(s->l);               /* liberta lista e componentes */
    free_jogos(s->tb_j);            /* liberta tabela de jogos e componentes */
    free_equipas(s->tb_e);          /* liberta tabela de equipas e componentes */
    free(s);
}
