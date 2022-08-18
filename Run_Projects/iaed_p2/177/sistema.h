#ifndef SISTEMA_H
#define SISTEMA_H

/*Estrutura com o nome e numero de jogos ganhos das equipas.*/
typedef struct no {
    char *equipa;
    int ganhos;
} *sist;

/*Estrutura da hash table que contem as equipas.*/
typedef struct sis {
    sist *v;
    int elementos, tamanho;
}*sistema;

/*hash table onde guardo o as equipas e o numero de vitorias de cada equipa*/

/*Inicializa a hash table onde vou guardar as equipas
 e o numero de vitorias de cada equipa.*/
sistema inicializa_sistema(sistema st1, int m);
/*Liberta toda a memoria ocupada pela hash table.*/
sistema destroi_sistema(sistema st);
/*Funcao auxiliar da funcao re_hash.*/
sistema insere_eq(sistema st, char *nome, int ganhos);
/*Fucao auxiliar da funcao insere_equipa. Insere todos 
os elementos da hash antiga numa nova mas com o dobro
do tamanho.*/
sistema re_hash(sistema st, char *nome, int ganhos);
/*Insere uma nova equipa na hash table e caso o numero 
de elementos seja metade do tamanho da hash aumenta o seu
tamanho para o dobro.*/
sistema insere_equipa(sistema st, char*name, int ganhos);
/*Averigua se existe alguma equipa com o nome nome 
na hash table.
Caso exista retorna 1 e caso contrario retorna 0.*/
int pertence_equipa(sistema st1, char *name);
/*Averigua qual das equipas, equipa1 e equipa2, tem
um score mais elevado, e caso isso aconteca retorna 
a equipa vencedora.*/
char *vencedor(char *equipa1, char *equipa2, int score1, int score2);
/*Decrementa o numero de vitorias da equipa vencedor.*/
sistema decrementa_jogos_ganhos(sistema st, char *vencedor);
/*Incrementa o numero de vitorias da equipa vencedor.*/
sistema incrementa_jogos_ganhos(sistema st, char *vencedor);
/*Averigua se com a alteracao do score se altera o numero 
de vitorias de alguma equipa e em caso afirmativo altera 
esse numero.*/
sistema atualiza_vitoria(sistema st, jogo st1, char *nome, int score1, int score2);
/*Verifica se com a remocao de um jogo se altera o numero de vitorias 
de alguma equipa e em caso afirmativo altera esse numero.*/
sistema elimina_vitoria(sistema st, jogo st1, char *nome);
/*Atualiza o numero de vitorias das equipas presentes
no novo jogo inserido na hash table dos jogos.*/
sistema insere_vitoria(sistema st, char *equipa1,char *equipa2, int score1, int score2);
/*Retorna o numero de jogos ganhos da equipanome.*/
int jogos_ganhos(sistema st1, char *name);
/*Funcao auxiliar do algoritmo de ordenacao qsort.*/
int comparastr(const void *pa, const void *pb);
/*Averigua quais as equipas com mais vitorias e faz print 
dessas equipas por ordem lexicografica.*/
void tabela(sistema st, int nl);

#endif