#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "tabela_jogos.h"

/*  Funcao de dispersao para a tabela de jogos (versao dos slides) */
size_t hash_j(const char* s, size_t max){
    size_t h = 0, a = 31415, b = 27183;
    for ( ; *s != '\0'; s++, a = a*b % (max-1))
        h = (a*h + *s) % max;
    return h;
}

/*  Inicializa tabela de jogos alocando o espaco suficiente */
jogos* inic_jogos(size_t max){
    jogos* t = can_fail_malloc(sizeof(jogos));
    t->capacidade = max;            /* capacidade da tabela */
    t->sz = 0;                      /* numero de elementos inseridos comeca a 0 */
    /* aloco o espaco de cada jogo e coloco tudo a NULL */
    t->tb = can_fail_calloc(t->capacidade, sizeof(jogos));  
    return t;                                  
}

/*  Auxiliar. Aloca o espaco necessario e insere a string dada.
 *  Devolve o ponteiro correspondente */
char* insere_str(const char* s){
    char* esp = can_fail_malloc((strlen(s)+1) * sizeof(char));
    strcpy(esp, s);
    return esp;
}

/*  Cria um jogo dadas as suas caracteristicas alocando o espaco necessario */
jogo* make_jogo(const char* nome, const char* neq1, const char* neq2, size_t s1, size_t s2){
    jogo* new_j = can_fail_malloc(sizeof(jogo));     /* inicio novo jogo */
    
    /* copia caracteristicas para o novo jogo */ 
    new_j->nome = insere_str(nome);
    new_j->equipa1 = insere_str(neq1);
    new_j->equipa2 = insere_str(neq2);
    new_j->score1 = s1;
    new_j->score2 = s2;
    
    return new_j;
}

/*  Procura jogo. Se nao existir retorna NULL, caso contrario a hash do j */
int procura_j(const char* nome, jogos* tb_j){
    size_t h = hash_j(nome, tb_j->capacidade);
    while (tb_j->tb[h]){    /* ate encontrar um espaco vazio, i.e, intervalo entre clusters */
        if (equal_j(tb_j->tb[h]->nome, nome))  /* se encontrar o jogo */
            return h;       /* devolve a propria hash para ser reutilizada */
        else
            h = (h+1) % (tb_j->capacidade); /* se nao, procura seguintes */
    }return INVALID_J;      /* nao encontrou */
}

/*  Libera um jogo */
void free_jogo(jogo* j){
    free(j->nome);                  /* liberta nome do jogo */
    free(j->equipa1);               /* liberta nome da equipa 1 no jogo */
    free(j->equipa2);               /* liberta nome da equipa 2 no jogo */
    free(j);                        /* liberta jogo */
}

/*  Auxiliar. Caso a tabela esteja 50% cheia realoca o dobro do espaco da tabela */
jogos* expand_j(jogos* tb_j){
    size_t i;
    jogos* old = tb_j;              /* copia tabela */
    tb_j->capacidade *= 2;              /* duplica capacidade */
    tb_j = inic_jogos(tb_j->capacidade);        /* realoca tabela de nova capacidade*/
    
    for (i = 0; i < tb_j->capacidade/2; i++){   /* copia todas equipas antes inseridas */
        if (old->tb[i]){
            tb_j = insere_j(old->tb[i], tb_j);
        }
    }free(old->tb);
    free(old);                      /* liberta tabela antiga */
    return tb_j;
}

/** Adiciona um jogo a tabela de acordo com as suas caracteristicas
 *  Caso metade da tabela fica cheia de jogos, expande-se a tabela */ 
jogos* insere_j(jogo* j, jogos* tb_j){
    size_t h = hash_j(j->nome, tb_j->capacidade);
    while (tb_j->tb[h])             /* procura um espaco livre (NULL) */
        h = (h+1) % (tb_j->capacidade);
    tb_j->tb[h] = j;                
    if (tb_j->sz++ > tb_j->capacidade / 2)  /* caso a tabela esteja 50% cheia */
        tb_j = expand_j(tb_j);      /* expando a tabela */
    return tb_j;
}

/*  Auxiliar. Reinsere os elementos consecutivos da posicao dada na tabela*/
void reinsere_seguintes(size_t hash, jogos* tb_j){
    size_t i, tam = tb_j->capacidade;
    jogo* tmp;   /* jogo auxiliar para nao perder posicao do jogo na hashtable */
    
    /* percorre elementos a seguir ate encontrar uma posicao vazia */
    for (i = (hash+1) % tam; tb_j->tb[i]; i = (i+1) % tam){  
        tmp = tb_j->tb[i];
        tb_j->tb[i] = NULL;             /* espaco fica vazio */
        tb_j->sz--;                     /* retira jogo */
        tb_j = insere_j(tmp, tb_j);     /* insere o jogo novamente */
    }
}

/*  Remove um jogo da tabela libetando toda a memoria respetiva a ele.
 *  Reinsere todos os jogos que estejam em posicoes consecutivas */
void remove_jogo(size_t hash, jogos* tb_j){
    free_jogo(tb_j->tb[hash]);      /* liberto jogo */
    
    /* atualizo hashtable */
    tb_j->tb[hash] = NULL;
    tb_j->sz--;
    reinsere_seguintes(hash, tb_j);
}

/* Liberta toda a memoria alocada dos jogos e da tabela */
void free_jogos(jogos* tb_j){
    size_t i;
    
    /* percorre a hashtable libertando toda memoria de cada jogo */
    for (i = 0; i < tb_j->capacidade; i++)    
        if(tb_j->tb[i]) 
            free_jogo(tb_j->tb[i]);     /* liberta jogo */
    free(tb_j->tb);     /* liberta tabela */
    free(tb_j);
}