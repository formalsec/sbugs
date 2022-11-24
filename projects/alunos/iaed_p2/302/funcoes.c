#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "funcoes.h"

#define SIM 1
#define NAO 0
#define STR_SIZE 1023
#define INICAP 1237

/*funcao correspondente ao comando A, adiciona um jogo*/
node_jogo *func_a(int cont, hash_table_jogo *syst_jogos, hash_table_equipa *syst_eq, node_jogo *head_lista_jogos){
   char buf_jg[STR_SIZE], buf_t1[STR_SIZE], buf_t2[STR_SIZE];
   int s1, s2;
   node_jogo *tmp;
   node_equipa *tmp2;

   scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", buf_jg, buf_t1, buf_t2, &s1, &s2);

   if(encontra_hash_jg(syst_jogos, buf_jg) != NULL) /*verificacao*/
      printf("%d Jogo existente.\n", cont);
   else if(encontra_hash_eq(syst_eq, buf_t1) == NULL ||
           encontra_hash_eq(syst_eq, buf_t2) == NULL) /*verificacao*/
      printf("%d Equipa inexistente.\n", cont);
   else{
      tmp = cria_node_jg(buf_jg, buf_t1, buf_t2, s1, s2); /*cria jogo*/

      if(s1 > s2){ /*se a primeira equipa ganhou a segunda*/
         tmp2 = encontra_hash_eq(syst_eq, buf_t1);
         tmp2->vitorias++; /*aumenta as vitorias da primeira equipa*/
      } else if(s1 < s2){ /*se a segunda equipa ganhou a segunda*/
         tmp2 = encontra_hash_eq(syst_eq, buf_t2);
         tmp2->vitorias++; /*aumenta as vitorias da segunda equipa*/
      }
      insere_jogo_hash(syst_jogos, tmp); /*insere na hash table*/
      head_lista_jogos = _insere_jogo_lista(head_lista_jogos, tmp, &syst_jogos->last); /*insere na lista*/
   }
   return head_lista_jogos;
}

/*funcao correspondente ao comando l, imprime os jogos inseridos pela ordem
de insercao*/
void func_l(int cont, node_jogo *head_lista_jogos){
   printlist_jogo(head_lista_jogos, cont);
}

/*funcao correspondente ao comando p, imprime o jogo correspondente ao nome
inserido*/
void func_p(int cont, hash_table_jogo *syst_jogos){
   node_jogo *tmp;
   char buf_jg[STR_SIZE];

   scanf(" %[^:\n]", buf_jg);
   tmp = encontra_hash_jg(syst_jogos, buf_jg);

   if(tmp == NULL) /*verificacao*/
      printf("%d Jogo inexistente.\n", cont);
   else
      printf("%d %s %s %s %d %d\n", cont, tmp->nome, tmp->t1, tmp->t2, tmp->s1, tmp->s2);
}

/*funcao correspondente ao comando r, remove o jogo correspondente ao nome
inserido*/
node_jogo *func_r(int cont, hash_table_jogo *syst_jogos, hash_table_equipa *syst_eq, node_jogo *head_lista_jogos){
   node_jogo *tmp;
   node_equipa *tmp2;
   char buf_jg[STR_SIZE];

   scanf(" %[^:\n]", buf_jg);
   tmp = encontra_hash_jg(syst_jogos, buf_jg);

   if(tmp == NULL) /*verificacao*/
      printf("%d Jogo inexistente.\n", cont);
   else{

      if(tmp->s1 > tmp->s2){ /*se a primeira equipa ganhou no jogo*/
         tmp2 = encontra_hash_eq(syst_eq, tmp->t1);
         tmp2->vitorias--; /*diminui as suas vitorias pois o jogo vai ser removido*/
      }

      else if(tmp->s2 > tmp->s1){ /*se a segunda equipa ganhou no jogo*/
         tmp2 = encontra_hash_eq(syst_eq, tmp->t2);
         tmp2->vitorias--; /*diminui as suas vitorias pois o jogo vai ser removido*/
      }
      head_lista_jogos = remove_node_list(head_lista_jogos, tmp, &syst_jogos->last); /*remove da lista*/
      remove_jogo_hash(syst_jogos, buf_jg); /*remove da hash table*/
   }
   return head_lista_jogos;
}

/*funcao correspondente ao comando s, altera a pontuacao de um jogo*/
void func_s(int cont, hash_table_jogo *syst_jogos, hash_table_equipa *syst_eq){
   node_jogo *tmp;
   node_equipa *t1, *t2;
   char buf_jg[STR_SIZE];
   int estado1 = NAO, estado2 = NAO, s1, s2;

   scanf(" %[^:\n]:%d:%d", buf_jg, &s1, &s2);
   tmp = encontra_hash_jg(syst_jogos, buf_jg);

   if(tmp == NULL) /*verificacao*/
      printf("%d Jogo inexistente.\n", cont);
   else{
      /*encontra as equipas do jogo*/
      t1 = encontra_hash_eq(syst_eq, tmp->t1);
      t2 = encontra_hash_eq(syst_eq, tmp->t2);

      /*verificacao de se ha um vencedor ou um empate*/
      if(tmp->s1 > tmp->s2) estado1 = SIM;
      else if(tmp->s1 < tmp->s2) estado2 = SIM;

      if(estado1){ /*se a equipa 1 era a vencedora*/
         if(s1 == s2){ /*e o novo resultado for um empate*/
            diminui_vitorias(t1);
         }
         else if(s2 > s1){ /*e o novo resultado der uma vitoria a equipa 2*/
            diminui_vitorias(t1);
            aumenta_vitorias(t2);
         }
      } else if(estado2){ /*se a equipa 2 era a vencedora*/
         if(s1 == s2){ /*e o novo resultado for um empate*/
            diminui_vitorias(t2);
         }
         else if(s1 > s2){ /*e o novo resultado der uma vitoria a equipa 1*/
            aumenta_vitorias(t1);
            diminui_vitorias(t2);
         }
      } else { /*se havia um empate entre as equipas*/
         if(s1 > s2){ /*e o novo resultado der uma vitoria a equipa 1*/
            aumenta_vitorias(t1);
         } else if(s2 > s1){ /*e o novo resultado der uma vitoria a equipa 2*/
            aumenta_vitorias(t2);
         }
      }
      tmp->s1 = s1; /*atualiza os valores na hashtable*/
      tmp->s2 = s2;
   }
}

/*funcao correspondente ao comando A, adiciona uma equipa*/
void func_A(int cont, hash_table_equipa *syst_eq){
   node_equipa *tmp;
   char buf_t1[STR_SIZE];

   scanf(" %[^:\n]", buf_t1);

   if(encontra_hash_eq(syst_eq, buf_t1) != NULL) /*verificacao*/
      printf("%d Equipa existente.\n", cont);
   else{
      tmp = cria_node_eq(buf_t1);
      insere_eq_hash(syst_eq, tmp); /*insere na hashtable*/
   }

}

/*funcao correspondente ao comando P, imprime uma equipa correspondente ao nome
inserido*/
void func_P(int cont, hash_table_equipa *syst_eq){
   node_equipa *tmp;
   char buf_t1[STR_SIZE];

   scanf(" %[^:\n]", buf_t1);
   tmp = encontra_hash_eq(syst_eq, buf_t1);

   if(tmp == NULL) /*verificacao*/
      printf("%d Equipa inexistente.\n", cont);
   else
      printf("%d %s %d\n", cont, tmp->nome, tmp->vitorias);
}

/*funcao correspondente ao comando g, imprime uma lista ordenada alfabeticamente
das equipas com mais vitorias*/
void func_g(int cont, hash_table_equipa *syst_eq){
   size_t i;
   int vitorias = 0, k = 0, j, contem = NAO;
   char *vetor[INICAP]; /*vetor a ordenar*/
   node_equipa *tmp;

   /*loop para percorrer a hashtable*/
   for(i = 0; i < INICAP; i++){
      tmp = syst_eq->tb[i];
      while(tmp != NULL){
         contem = SIM;
         /*se o numero de vitorias da equipa for igual ao maior numero de vitorias*/
         if(tmp->vitorias == vitorias){
            vetor[k] = tmp->nome; /*acrescenta ao vetor*/
            k++;
         } else if(tmp->vitorias > vitorias){ /*se o Numero de vitorias for maior*/
            k = 0; /*reset do indice*/
            vetor[k] = tmp->nome; /*acrescenta ao vetor*/
            k++;
            vitorias = tmp->vitorias; /*atualiza o maior numero de vitorias*/
         }
         tmp = tmp->next;
      }
   }
   if(contem){ /*se houver equipas*/
      qsort(vetor, k, sizeof(char*), compara);
      printf("%d Melhores %d\n", cont, vitorias);
      for(j = 0; j < k; j++){
         printf("%d * %s\n", cont, vetor[j]);
      }
   }
}
