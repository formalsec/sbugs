#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "commands.h"
#include <stdio.h>

/* variaveis alvo de scan e reader */
char reader;
char var_nome[1024];
char var_eq1[1024];
char var_eq2[1024];
unsigned int var_s1;
unsigned int var_s2;

int main () {
    /* leitura do comando */
    while (reader != EOF) {
        /* retira o char do comando */
        reader = getchar();
        /* chama o comando correspondente */
        if(reader == 'a') {
            scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%u:%u",var_nome,var_eq1,var_eq2,&var_s1,&var_s2);
            adiciona_novo_jogo(var_nome,var_eq1,var_eq2,var_s1,var_s2);
        }
        else if(reader == 'A') {
            scanf(" %[^:\n]",var_nome);
            adiciona_nova_equipa(var_nome);
        }
        else if(reader == 'l') {
            lista_jogos();
        }
        else if(reader == 'p') {
            scanf(" %[^:\n]",var_nome);
            procura_jogo(var_nome);
        }
        else if(reader == 'P') {
            scanf(" %[^:\n]",var_nome);
            procura_equipa(var_nome);
        }
        else if(reader == 'r') {
            scanf(" %[^:\n]",var_nome);
            apaga_jogo(var_nome);
        }
        else if(reader == 's') {
            scanf(" %[^:\n]:%u:%u",var_nome,&var_s1,&var_s2);
            altera_score(var_nome,var_s1,var_s2);
        }
        else if(reader == 'g') {
            lista_vencedores();
        }
    }
    liberta_memoria();
    return 0;
}