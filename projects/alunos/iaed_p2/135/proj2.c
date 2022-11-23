#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_equipa.h"
#include "hash_jogo.h"
#include "lista_jogo.h"
#include "jogo.h"

/* Valor maximo de caracteres nos nomes das equipas e dos jogos */
#define MAX 1023
/* Valor da dimensao das hash */
#define DIM_HASH 1057

/* Prototipos das Funcoes */
void adiciona_novo_jogo(list* ls, hashtable_jogo* ht_jogo,
                        hashtable_equipa* ht_equipa, const int n_comando);
void adiciona_nova_equipa(hashtable_equipa* ht_equipa, const int n_comando);
void lista_jogos(list* ls, const int n_comando);
void procura_jogo(hashtable_jogo* ht_jogo, const int n_comando);
void procura_equipa(hashtable_equipa* ht_equipa, const int n_comando);
void apaga_jogo(list* ls, hashtable_jogo* ht_jogo,
                hashtable_equipa* ht_equipa, const int n_comando);
void altera_score(hashtable_jogo* ht_jogo, hashtable_equipa* ht_equipa,
                  const int n_comando);
void lista_equipa_mais_ganhos(hashtable_equipa* ht_equipa, const int n_comando);

/* Funcao principal
 * Recebe um comando e faz o que a acao que esta definida para o comando
*/
int main(){
    int input, n_comando = 0;

    list* ls = cria_lista_dupla();
    hashtable_jogo* ht_jogo = cria_hash_jogo(DIM_HASH);
    hashtable_equipa* ht_equipa = cria_hash_equipa(DIM_HASH);

    while ((input=getchar())!='x'){
        n_comando++;
        /* Identifica o comando e faz a acao */
        switch (input){
            case 'a':
                adiciona_novo_jogo(ls, ht_jogo, ht_equipa, n_comando);
                break;
            case 'A':
                adiciona_nova_equipa(ht_equipa, n_comando);
                break;
            case 'l':
                lista_jogos(ls, n_comando);
                break;
            case 'p':
                procura_jogo(ht_jogo, n_comando);
                break;
            case 'P':
                procura_equipa(ht_equipa, n_comando);
                break;
            case 'r':
                apaga_jogo(ls, ht_jogo, ht_equipa, n_comando);
                break;
            case 's':
                altera_score(ht_jogo, ht_equipa, n_comando);
                break;
            case 'g':
                lista_equipa_mais_ganhos(ht_equipa, n_comando);
                break;
        }
        getchar();
    }
    FREEhash_equipa(ht_equipa);
    FREEhash_jogo(ht_jogo);
    FREElista(ls);
    return 0;
}

/* (Comando a) Adiciona um novo jogo */
void adiciona_novo_jogo(list* ls, hashtable_jogo* ht_jogo, hashtable_equipa* ht_equipa,
                        const int n_comando){
    int s1,s2;
    char nome[MAX+1], e1[MAX+1], e2[MAX+1];
    pJogo j = NULL;
    el_lista_jogo* el_j = NULL;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, e1, e2, &s1, &s2);
    if(procuraHash_jogo(ht_jogo, nome)){
        printf("%d Jogo existente.\n", n_comando);
    }
    else if(!(procuraHash_equipa(ht_equipa, e1)) || 
            !(procuraHash_equipa(ht_equipa, e2))){
        printf("%d Equipa inexistente.\n", n_comando);
    }else{
        j = cria_jogo(nome, e1, e2, s1, s2);

        if(j->vencedora){
            procuraHash_equipa(ht_equipa, j->vencedora)->n_ganhos++;
        }

        el_j = adiciona_elemento(ls, j);
        insereHash_jogo(ht_jogo, el_j);
    }
}

/* (Comando A) Adiciona uma nova equipa */
void adiciona_nova_equipa(hashtable_equipa* ht_equipa, const int n_comando){
    char nome[MAX+1];
    pEquipa e = NULL;
    
    scanf(" %[^:\n]", nome);
    if(procuraHash_equipa(ht_equipa, nome)){
        printf("%d Equipa existente.\n", n_comando);
    }else{
        e = can_fail_malloc(sizeof(equipa));
        e->nome = strdup(nome);
        e->n_ganhos = 0;

        insereHash_equipa(ht_equipa,e);
    }
}

/* (Comando l) Lista todos os jogos pela ordem que foram introduzidos*/
void lista_jogos(list* ls, const int n_comando){
    imprime_lista_jogo(ls, n_comando);
}

/* (Comando p) Procura um jogo */
void procura_jogo(hashtable_jogo* ht_jogo, const int n_comando){
    char nome[MAX+1];
    el_lista_jogo* e = NULL;
    pJogo j = NULL;

    scanf(" %[^:\n]", nome);
    e = procuraHash_jogo(ht_jogo, nome);
    if(!e){
        printf("%d Jogo inexistente.\n", n_comando);
    }else{
        j = e->j;
        printf("%d %s %s %s %d %d\n", n_comando,
        nome, j->equipa1, j->equipa2, j->score1, j->score2);
    }
}

/* (Comando P) Procura uma equipa */
void procura_equipa(hashtable_equipa* ht_equipa, const int n_comando){
    char nome[MAX+1];
    pEquipa e = NULL;;

    scanf(" %[^:\n]", nome);
    if((e=procuraHash_equipa(ht_equipa, nome))){
        printf("%d %s %d\n", n_comando, nome, e->n_ganhos);
    }else{
        printf("%d Equipa inexistente.\n", n_comando);
    }
}

/* (Comando r) Apaga um jogo */
void apaga_jogo(list* ls, hashtable_jogo* ht_jogo, hashtable_equipa* ht_equipa, 
                const int n_comando){
    char nome[MAX+1];
    el_lista_jogo* el = NULL;
    pEquipa equipa = NULL;

    scanf(" %[^:\n]", nome);
    el = procuraHash_jogo(ht_jogo, nome);
    if(!el){
        printf("%d Jogo inexistente.\n", n_comando);
    }else{
        if(el->j->vencedora){
            equipa = procuraHash_equipa(ht_equipa, el->j->vencedora);
            equipa->n_ganhos--;
        }
        remove_elemento(ls, el);
        apagaHash_jogo(ht_jogo, nome);
    }
}

/* (Comando s) Altera a pontuacao (score) de um jogo */
void altera_score(hashtable_jogo* ht_jogo, hashtable_equipa* ht_equipa, 
                  const int n_comando){
    char nome[MAX+1];
    char* vencedora_ant;
    int s1, s2;
    el_lista_jogo* el = NULL;

    scanf(" %[^:\n]:%d:%d", nome, &s1, &s2);
    el = procuraHash_jogo(ht_jogo, nome);
    if(!el){
        printf("%d Jogo inexistente.\n", n_comando);
    }else{
        if(el->j->vencedora){
            vencedora_ant=strdup(el->j->vencedora);
        }else{
            vencedora_ant=NULL;
        }

        altera_score_jogo(el->j, s1, s2);

        if(el->j->vencedora && vencedora_ant){
            if(strcmp(el->j->vencedora, vencedora_ant)){
                procuraHash_equipa(ht_equipa, el->j->vencedora)->n_ganhos++;
                procuraHash_equipa(ht_equipa, vencedora_ant)->n_ganhos--;
            }
        }else if(el->j->vencedora){
            procuraHash_equipa(ht_equipa, el->j->vencedora)->n_ganhos++;
        }else if(vencedora_ant){
            procuraHash_equipa(ht_equipa, vencedora_ant)->n_ganhos--;
        }

        if(vencedora_ant) free(vencedora_ant);
    }
}

/* (Comando g) Encontra as equipas que venceram mais jogos */
void lista_equipa_mais_ganhos(hashtable_equipa* ht_equipa, const int n_comando){
    int maior_n_ganhos = 0, n_equipas = 0;

    maior_ganhos(ht_equipa, &maior_n_ganhos, &n_equipas);
    if(n_equipas){
        nome_equipas_maior_ganhos(ht_equipa, maior_n_ganhos, n_equipas, n_comando);
    }
}
