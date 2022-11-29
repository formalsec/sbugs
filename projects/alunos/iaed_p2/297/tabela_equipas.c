#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "tabela_equipas.h"

/*  Funcao de dispersao para a tabela de equipas (versao dos slides) */
size_t hash_e(const char* s, size_t max){
    size_t h = 0, a = 31415, b = 27183;
    for ( ; *s != '\0'; s++, a = a*b % (max-1))
        h = (a*h + *s) % max;
    return h;
}

/*  Inicializa tabela de equipas alocando o espaco suficiente */
equipas* inic_equipas(size_t max){
    equipas* t = can_fail_malloc(sizeof(equipas));
    t->capacidade = max;            /* capacidade da tabela */
    t->sz = 0;                      /* numero de elementos inseridos comeca a 0 */
    /* aloco o espaco de cada jogo e coloco tudo a NULL */
    t->tb = can_fail_calloc(t->capacidade, sizeof(equipa)); 
    return t;
}

/*  Auxiliar. Gera uma nova equipa. Aloca e copia o espaco necessario de memoria */
equipa* make_equipa(size_t vit, const char* nome){
    equipa* new_e = can_fail_malloc(sizeof(equipa));     /* aloco espaco equipa */
    new_e->flag = can_fail_malloc((strlen(nome) + 1) * sizeof(char));    /* aloca espaco flag */
    strcpy(new_e->flag, nome);      /* copia para esse espaco a flag correspondente */
    new_e->vitorias = vit;          /* o numero de vitorias e inicializado com o dado */
    return new_e;
}

/*  Procura equipa. Se nao existir retorna NULL, caso contrario a hash da e */
int procura_e(const char* nome, equipas* tb_e){
    size_t h = hash_e(nome, tb_e->capacidade);
    while (tb_e->tb[h]){    /* ate encontrar um espaco vazio, ie, intervalo entre clusters */
        if (equal_e(tb_e->tb[h]->flag, nome))  /* se encontrar a equipa */
            return h;       /* devolve a propria hash para ser reutilizada */
        else
            h = (h+1) % (tb_e->capacidade); /* se nao, procura seguintes */ 
    }return INVALID_E;      /* nao encontrou */
}

/* Liberta uma equipa */
void free_equipa(equipa* e){
    free(e->flag);                  /* liberta nome da equipa */
    free(e);                        /* liberta equipa */
}

/*  Auxiliar. Caso a tabela esteja 50% cheia realoca o dobro do espaco da tabela */ 
equipas* expand_e(equipas* tb_e){
    size_t i;
    equipas* old = tb_e;            /* copia tabela */
    tb_e->capacidade *= 2;          /* duplica capacidade */
    tb_e = inic_equipas(tb_e->capacidade);      /* realoca tabela de nova capacidade*/
    
    for (i = 0; i < tb_e->capacidade / 2; i++)    /* copia todas equipas antes inseridas */
        if (old->tb[i]){
            tb_e = insere_e(old->tb[i]->vitorias, old->tb[i]->flag, tb_e);
            free_equipa(old->tb[i]);            /* liberta equipa antiga */
        }
    free(old->tb);                  /* liberta tabela antiga */
    free(old);
    return tb_e;
}

/*  Adiciona uma equipa a tabela de equipas */
equipas* insere_e(size_t vit, const char* flag, equipas* tb_e){
    size_t h = hash_e(flag, tb_e->capacidade);
    while (tb_e->tb[h])             /* procura um espaco livre (NULL) */
        h = (h+1) % (tb_e->capacidade);
    tb_e->tb[h] = make_equipa(vit, flag);   /* cria nova equipa */
    if (tb_e->sz++ > tb_e->capacidade / 2)  /* caso a tabela estaja 50% cheia */
        tb_e = expand_e(tb_e);              /* expando a tabela */
    return tb_e;
}

/*  Devolve o maior numero de jogos ganhos das equipas da tabela */
size_t max_vitorias(equipas* tb_e){
    size_t i, max = 0;
    for (i = 0; i < tb_e->capacidade; i++)  /* verifica todos os espacos da tabela */
        if (tb_e->tb[i])                    /* se for uma equipa */
            if (tb_e->tb[i]->vitorias > max)    /* verifica o numero de vitorias */
                max = tb_e->tb[i]->vitorias;    /* atualiza max */
    return max;
}

/*  Auxiliar. Aloca o espaco necessario e insere a string dada.
 *  Devolve o ponteiro correspondente */
char* make_str(char* flag){
    char* s = can_fail_malloc((strlen(flag)+1)* sizeof(char));
    strcpy(s, flag);
    return s;
}

/*  Devolve o numero de strings correspondentes ao nome das melhores equipas da tabela */
size_t n_strings(size_t max, equipas* tb_e){
    size_t i, n = 0;
    for (i = 0; i < tb_e->capacidade; i++){ /* verifica se a equipa e a melhor */
        if (tb_e->tb[i])    
            if (tb_e->tb[i]->vitorias == max)
                n++;                        /* atualiza contador caso seja melhor */
    }
    return n;
}

/*  Auxiliar. Condicao de ordenacao de um vector para quicksort */
int cmp_strings(const void *a, const void *b){ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

/*  Encontra as melhores equipas da tabela, devolvendo os nomes correspondentes */
char** encontra_melhores(size_t n_strings, size_t max, equipas* tb_e){
    size_t i, j = 0;
    char** melhores = can_fail_calloc(n_strings, sizeof(char*)); /* gera espaco adequado */
    for (i = 0; i < tb_e->capacidade; i++){     /* verifica se a equipa e melhor */
        if (tb_e->tb[i]){
            if (tb_e->tb[i]->vitorias == max)   /* se for adiciona o nome */
                melhores[j++] = make_str(tb_e->tb[i]->flag); 
            if (j == n_strings) break;          /* se ja encontrou todas as melhores, sai */
        }
    }/* ordena por ordem lexicografica */
    qsort(melhores, n_strings, sizeof(char *), cmp_strings);   
    return melhores;
}

/*  Liberta toda a memoria alocada dos jogos e da tabela */
void free_equipas(equipas* tb_e){
    size_t i;
    /* percorre a hashtable libertando toda memoria de cada equipa */
    for (i = 0; i < tb_e->capacidade; i++)
        if(tb_e->tb[i])
            free_equipa(tb_e->tb[i]);   /* liberta equipa */
    free(tb_e->tb);     /* liberta tabela */
    free(tb_e);
}