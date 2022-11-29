#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definicao de constantes */
#define TABLE_JOGOS_SIZE 83093 /* Dimensao maxima da hashtable de Jogos */
#define TABLE_EQUIPA_SIZE 33637 /* Dimensao maxima da hashtable Equipas */
#define STRING_SIZE 1024 /* Dimensao maxima das strings de nomes de jogos e equipas */
#define VICTORY 1 /* valor a adicionar as vitorias de uma equipa */
#define DEFEAT -1 /* valor a adicionar as vitorias de uma equipa */
#define RESERVED_NAME ":" /* Nome reservado para jogos eliminados */
#define DUMMY "dummy" /* Nome plceholder para equipas associadas a um jogo eliminado */

/* Definicao da estrutura de Equipa para uso numa hashtable de equipas*/
typedef struct equipa {
    char* name;
    int wins;
} *pEquipa;

/* Definicao da estrutura de Jogo para uso numa hashtable de jogos*/
typedef struct jogo {
    char* name;
    char* equipa1;
    char* equipa2;
    int score1;
    int score2;
} *pJogo;

/* Definicao do no de nomes de jogos e/ou equipas */
typedef struct nomeElemento {
    char* nome;
    struct nomeElemento* next;
} *pNome;

static int JT_M; /* tamanho da hashtable de Jogos */
static int EQ_M; /* tamanho da hashtable de Equipas */
static pEquipa *equipas; /* tabela de pointers de Equipas */
static pJogo *jogos; /* tabela de pointers de Jogos */
static pNome headNomesJogos; /* head de lista de nomes de jogos */
static pNome headNomesEquipas; /* head de lista de nomes de equipas */

/* Hash simples oriunda do livro Algorithms in C (p.578) */
int hash(char *v, int M) {
    int h = 0, a = 127;
    for (; *v != '\0'; v++)
    {
        h = (a*h + *v) % M;
    }
    return h;
}

/* Hash Universal oriunda do livro Algorithms in C (p.579) */
int hash2(char *v, int M) {
    unsigned int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
    {
        h = (a*h + *v) % M;
    }
    
    return h;
}

/* Funcao de alocagem de memoria para uma string */
char *strdup(const char *s) {
    size_t size = strlen(s) + 1;
    char *p = can_fail_malloc(size);
    if (p)
    {
        memcpy(p, s, size);
    }
    return p;
}

/* Funcao de alocacao da estrutura para nome de equipas e/ou jogos */
pNome newNomeElemento(char* name) {
    pNome new = (pNome)can_fail_malloc(sizeof(struct nomeElemento));
    new->nome = strdup(name);
    new->next = NULL;
    return new;
}

/* Funcao para dealocacao da memoria ocupada pelas estruturas de nomes de Elementos */
void freeNomeElemento(pNome elem) {
    free(elem->nome);
    free(elem);
}

/* Funcao de alocacao da estrutura para Jogos */
pJogo newGame(char* name, char* equipa1, char* equipa2) {
    pJogo new = (pJogo)can_fail_malloc(sizeof(struct jogo));
    new->name = strdup(name);
    new->equipa1 = strdup(equipa1);
    new->equipa2 = strdup(equipa2);
    new->score1 = 0;
    new->score2 = 0;
    return new;
}

/* Funcao de dealocacao da memoria ocupada pela estrutura de Jogos */
void freeGame(pJogo jogo) {
    free(jogo->name);
    free(jogo->equipa1);
    free(jogo->equipa2);
    free(jogo);
}

/* Funcao para alocacao da estrutura para Equipas */
pEquipa newTeam(char*name) {
    pEquipa new = (pEquipa)can_fail_malloc(sizeof(struct equipa));
    new->wins = 0;
    new->name = strdup(name);
    return new;
}


/***** Funcoes de manipulacao da lista de nomes de Jogos, ordenada em funcao da ordem de insercao/criacao de cada Jogo *****/

/* Funcao de inicializacao do pointeiro referente a head da lista de nomes de Jogos */
void NJinit() {
    headNomesJogos = NULL;
}

/* Funcao de insercao do no nome do jogo no final da lista existente */
void NJinsert(pNome jogo) {
    pNome temp = headNomesJogos;
    if (headNomesJogos == NULL)
    {
        headNomesJogos = jogo;
        return;
    }
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = jogo;
}

/* Funcao de remocao do no de nome do jogo atraves da procura do dado nome na lista, seguido da 
atualizacao do ponteiro de e para os nos adjacentes e libertacao da memoria do no eliminado */
void NJdelete(char* nome) {
    pNome curr = headNomesJogos;
    pNome prev;

    while ((curr->next != NULL) & (strcmp(curr->nome, nome) != 0)) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == headNomesJogos) 
    {
        headNomesJogos = curr->next;
    } else
    {
        prev->next = curr->next;
    }
    freeNomeElemento(curr);
}

/***** Funcoes de manipulacao da lista de nomes de Equipas, ordenada em funcao da ordem lexicografica do nome de cada Equipa *****/

/* Funcao de inicializacao do pointeiro referente a head da lista de nomes de Equipas */
void NEinit() {
    headNomesEquipas = NULL;
}

/* Funcao de insercao ordenada de nomes, atraves da comparacao da ordem lexicografica entre o no a inserir e o no acedido no ciclo */
void NEinsert(pNome equipa) {
    pNome current = headNomesEquipas;

    if (headNomesEquipas == NULL || strcmp(equipa->nome, current->nome) < 0)
    {
        equipa->next = headNomesEquipas;
        headNomesEquipas = equipa;
        return;
    }
    
    while ((current->next != NULL) && (strcmp(equipa->nome, current->next->nome) > 0))
    {
        current = current->next;
    }
    equipa->next = current->next;
    current->next = equipa;
}

/***** Funcoes de manipulacao da hashtable de Equipas *****/

/* Funcao de inicializacao da hashtable de equipas */
void EQinit(int m) {
    int i;
    EQ_M = m;
    equipas = (pEquipa*)can_fail_malloc(EQ_M*sizeof(pEquipa));
    for (i = 0; i < EQ_M; i++)
    {
        equipas[i] = NULL;
    }
}

/* Funcao de insercao da Equipa por procura linear */
void EQinsert(pEquipa equipa) {
    int i = hash(equipa->name, EQ_M);
    while (equipas[i] != NULL)
    {
        i = (i+1) % EQ_M;
    }
    equipas[i] = equipa;
}

/* Funcao de pesquisa da Equipa por procura linear */
pEquipa EQsearch(char * key) {
    int i = hash(key, EQ_M);
    
    while (equipas[i] != NULL)
    {
        if (strcmp(equipas[i]->name, key) == 0)
        {
            return equipas[i];
        }
        else
        {
            i = (i+1) % EQ_M;
        }
    }
    return NULL;
}

/* Funcao de atualizacao do valor de vitorias de uma Equipa */
void EQupdateVictory(char* key, int value) {
    pEquipa equipa = EQsearch(key);
    equipa->wins += value;
}

/* Funcao de impressao de calculo e impressao das equipas com o maior numeros de vitorias,
atraves do uso de uma lista ordenada lexicograficamente */
void EQmaxVictories(unsigned int nl) {
    pNome temp = headNomesEquipas;
    int max = 0;
    pEquipa equipa;

    while (temp != NULL)
    {
        equipa = EQsearch(temp->nome);
        max = (equipa->wins > max) ? equipa->wins : max;
        temp = temp->next;
    }
    temp = headNomesEquipas;
    printf("%u Melhores %d\n", nl, max);
    while (temp != NULL)
    {
        equipa = EQsearch(temp->nome);
        if (equipa->wins == max)
        {
            printf("%u * %s\n",nl, equipa->name);
        }
        temp = temp->next;   
    }  
}

/***** Funcoes de manipulacao da hashtable de Jogos *****/

/* Funcao de inicializacao da hashtable de jogos */
void JTinit(int m) {
    int i;
    JT_M = m;
    jogos = (pJogo*)can_fail_malloc(JT_M*sizeof(pJogo));
    for (i = 0; i < JT_M; i++)
    {
        jogos[i] = NULL;
    }
}

/* Funcao de insercao de Jogo por Double Hashing */
void JTinsert(pJogo jogo) {
    int i = hash2(jogo->name, JT_M);
    int k = hash(jogo->name, JT_M);

    while (jogos[i] != NULL)
    {
        if (strcmp(jogos[i]->name, RESERVED_NAME) == 0) /* verificacao para index disponivel gracas a eliminacao do Jogo presente anteriormente nesta posicao da tabela */
        {
            break;
        }
        else
        {
            i = (i + k) % JT_M;
        }
    }
    jogos[i] = jogo;
}

/* Funcao de pesquisa de Jogo por Double Hashing */
pJogo JTsearch(char* key) {
    int i = hash2(key, JT_M);
    int k = hash(key, JT_M);
    
    while (jogos[i] != NULL)
    {
        if (strcmp(jogos[i]->name, key) == 0)
        {
            return jogos[i];
        }
        else 
        {
            i = (i + k) % JT_M;
        }
    }
    return NULL;
}

/* Funcao de remocao de Jogo por Double Hashing, atraves da pesquisa do indice correspondente a chave dada,
libertacao de memoria do jogo existente, e substituicao da posicao pelo no dummy, representante de um no eliminado
e disponivel para insercao posterior de um novo Jogo */
void JTremove(char* key, pJogo dummy) {
    int i = hash2(key, JT_M);
    int k = hash(key, JT_M);

    while (jogos[i] != NULL)
    {
        if (strcmp(jogos[i]->name, key) == 0)
        {
            break;
        }
        else
        {
            i = (i + k) % JT_M;
        }
    }

    freeGame(jogos[i]);
    jogos[i] = dummy;
}

/* Funcao de atualizacao do resultado do dado jogo atraves da comparacao do novo resultado com o anterior,
e adicao ou remocao de vitorias conforme a diferenca entre ambos os resultados */
void JTupdateScore(pJogo jogo, int score1, int score2) {
    if (score1 > score2)
    {
        if (jogo->score1 < jogo->score2)
        {
            EQupdateVictory(jogo->equipa1, VICTORY);
            EQupdateVictory(jogo->equipa2, DEFEAT);
        }
        else if (jogo->score1 == jogo->score2)
        {
            EQupdateVictory(jogo->equipa1, VICTORY);
        }   
    }
    else if (score1 < score2)
    {
        if (jogo->score1 > jogo->score2)
        {
            EQupdateVictory(jogo->equipa1, DEFEAT);
            EQupdateVictory(jogo->equipa2, VICTORY);
        }
        else if (jogo->score1 == jogo->score2)
        {
            EQupdateVictory(jogo->equipa2, VICTORY);
        }
    }
    else
    {
        if (jogo->score1 > jogo->score2)
        {
            EQupdateVictory(jogo->equipa1, DEFEAT);
        }
        else if (jogo->score1 < jogo->score2)
        {
            EQupdateVictory(jogo->equipa2, DEFEAT);
        }
    }

    jogo->score1 = score1;
    jogo->score2 = score2;
}

/* Funcao de impressao do valores de uma dado jogo e linha de comando */
void JTprintJogo(unsigned int nl, pJogo jogo) {
    printf("%u %s %s %s %d %d\n", nl, jogo->name, jogo->equipa1, jogo->equipa2, jogo->score1, jogo->score2);
}

/* Funcao de impressao de todos o Jogos por ordem de insercao, atraves de uma
lista auxiliar ordenada de nomes de jogos em funcao da ordem de insercao/criacao */
void JTprintJogos(unsigned int nl) {
    pNome temp = headNomesJogos;
    pJogo jogo;

    while (temp != NULL)
    {
        jogo = JTsearch(temp->nome);
        JTprintJogo(nl, jogo);
        temp = temp->next;
    }   
}


int main() {
    /* inicializacao de variaveis e estruturas utilizadas em contexto da execucao */
    char comando; /* variavel referento ao comando inserido pelo utilizador */
    unsigned int nl = 0; /* variavel referente ao numero de linha do comando atual */ 
    pJogo dummy = newGame(RESERVED_NAME, DUMMY, DUMMY);
    EQinit(TABLE_EQUIPA_SIZE);
    JTinit(TABLE_JOGOS_SIZE);
    NJinit();
    NEinit();
    
    while (1)
    {
        /* inicializacao de variaveis e ponteiros utilizados durante o ciclo */
        char nome[STRING_SIZE];
        char equipa1[STRING_SIZE];
        char equipa2[STRING_SIZE];
        int score1;
        int score2;
        pEquipa equipa;
        pJogo jogo;
        pNome nomeJogo;
        pNome nomeEquipa;

        comando = getchar();

        switch (comando) {
            case 'a':

                nl += 1;
                
                scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%i:%i", nome, equipa1, equipa2, &score1, &score2);

                if (JTsearch(nome) != NULL)
                {
                    printf("%u Jogo existente.\n", nl);
                }
                else if ((EQsearch(equipa1) == NULL) | (EQsearch(equipa2) == NULL))
                {
                    printf("%u Equipa inexistente.\n", nl);
                }
                else
                {
                    jogo = newGame(nome, equipa1, equipa2);
                    nomeJogo = newNomeElemento(nome);
                    JTinsert(jogo);
                    JTupdateScore(jogo, score1, score2);
                    NJinsert(nomeJogo);
                }

                break;
            case 'A':

                nl += 1;
                scanf(" %[^:\n]", nome);
                
                if (EQsearch(nome) != NULL)
                {
                    printf("%u Equipa existente.\n", nl);
                } else
                {
                    equipa = newTeam(nome);
                    nomeEquipa = newNomeElemento(nome);
                    EQinsert(equipa);
                    NEinsert(nomeEquipa);
                }
                
                break;
            case 'l':

                nl += 1;

                JTprintJogos(nl);
                
                break;
            case 'p':
                nl += 1;
                scanf(" %[^:\n]", nome);
                jogo = JTsearch(nome);

                if (jogo != NULL)
                {
                    JTprintJogo(nl, jogo);
                }
                else
                {
                    printf("%u Jogo inexistente.\n", nl);
                }

                break;

            case 'P':
                nl += 1;
                scanf(" %[^:\n]", nome);
                equipa = EQsearch(nome);

                if (equipa != NULL)
                {
                    printf("%u %s %d\n", nl, equipa->name, equipa->wins);
                }
                else
                {
                    printf("%u Equipa inexistente.\n", nl);
                }

                break;
            
            case 'r':
                nl += 1;
                scanf(" %[^:\n]", nome);
                jogo = JTsearch(nome);

                if (jogo != NULL)
                {
                    JTupdateScore(jogo, 0, 0);
                    JTremove(nome, dummy);
                    NJdelete(nome);
                }
                else
                {
                    printf("%u Jogo inexistente.\n", nl);
                }

                break;

            case 's':
                nl += 1;
                scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);
                jogo = JTsearch(nome);

                if (jogo != NULL)
                {
                    JTupdateScore(jogo, score1, score2);
                }
                else
                {
                    printf("%u Jogo inexistente.\n", nl);
                }
                
                break;

            case 'g':
                nl += 1;
                if (headNomesEquipas == NULL) /* verificacao de existencia de equipas para listar */
                {
                    break;
                }
                
                EQmaxVictories(nl);
                
                break;
                
            case 'x':
                freeGame(dummy);
                return EXIT_SUCCESS;
        
            default:
                printf("ERRO: Comando desconhecido\n");
                break;
        }
        getchar();
    }
    

    return EXIT_FAILURE;
}