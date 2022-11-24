#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(){
   char comando;
   int cont = 1, run = SIM;
   hash_table_jogo *syst_jogos = mk_hash_table_jg(INICAP);
   hash_table_equipa *syst_eq = mk_hash_table_eq(INICAP);
   node_jogo *head_lista_jogos = NULL;

   while(run){
      comando = getchar(); /*le o caracter inicial*/
      switch (comando) {
         case 'a':
            head_lista_jogos = func_a(cont, syst_jogos, syst_eq, head_lista_jogos);
            break;

         case 'l':
            func_l(cont, head_lista_jogos);
            break;

         case 'p':
            func_p(cont, syst_jogos);
            break;

         case 'r':
            head_lista_jogos = func_r(cont, syst_jogos, syst_eq, head_lista_jogos);
            break;

         case 's':
            func_s(cont, syst_jogos, syst_eq);
            break;

         case 'A':
            func_A(cont, syst_eq);
            break;

         case 'P':
            func_P(cont, syst_eq);
            break;

         case 'g':
            func_g(cont, syst_eq);
            break;

         case 'x':
            run = NAO; /*desativa a variavel de estado do main loop*/
            break;

         default:
            cont++;
            continue;
      }
   }
   /*libertacoes de memoria*/
   
   free_hashtable_eq(syst_eq);
   free_hashtable_jg(syst_jogos);
   return 0;
}
