#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"
#include "hash_jogos.h"
#include "hash_equipas.h"


int main()
{
  Jogo *J;
  Jogo **JHash;
  Jogos *Match_Lst;
  Equipa *E;
  Equipa *E1;
  Equipa *E2;
  Equipa **EHash;
  Equipas *Team_Lst;
  int Init = 7;
  int JN = 0;
  int JM = Init;
  int EN = 0;
  int EM = Init;
  unsigned int NL = 1;
  unsigned int Score1;
  unsigned int Score2;
  unsigned int Max;
  int i;
  int NEquipas;
  char C;
  char **Nomes;
  char buffer[1024];
  JHash = JNova_Hash(JM);
  EHash = ENova_Hash(EM);
  Match_Lst = init_jogos();
  Team_Lst = init_equipas();
  do
  {
    C = getchar();
    switch (C)
    {
      case 'a':
        J = novo_jogo();
        for (int buffer_index = 0; buffer_index < 10; buffer_index++)
      {
        buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
      }

        buffer[10 - 1] = '\0';
        J->nome = (char *) malloc((sizeof(char)) * (strlen(buffer) + 1));
        strcpy(J->nome, buffer);
        for (int buffer_index = 0; buffer_index < 10; buffer_index++)
      {
        buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
      }

        buffer[10 - 1] = '\0';
        J->Equipas[0] = (char *) malloc((sizeof(char)) * (strlen(buffer) + 1));
        strcpy(J->Equipas[0], buffer);
        for (int buffer_index = 0; buffer_index < 10; buffer_index++)
      {
        buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
      }

        buffer[10 - 1] = '\0';
        J->Equipas[1] = (char *) malloc((sizeof(char)) * (strlen(buffer) + 1));
        strcpy(J->Equipas[1], buffer);
        J->score[0] = new_sym_var(sizeof(unsigned int) * 8);
        J->score[1] = new_sym_var(sizeof(unsigned int) * 8);
        E1 = EProcura_Hash(EHash, J->Equipas[0], EM);
        E2 = EProcura_Hash(EHash, J->Equipas[1], EM);
        if (JProcura_Hash(JHash, J->nome, JM) != 0)
      {
        printf("%u Jogo existente.\n", NL++);
        elimina_jogo(J);
        continue;
      }
      else
      {
        
      }

        if (E1 == 0)
      {
        printf("%u Equipa inexistente.\n", NL++);
        elimina_jogo(J);
        continue;
      }
      else
      {
        
      }

        if (E2 == 0)
      {
        printf("%u Equipa inexistente.\n", NL++);
        elimina_jogo(J);
        continue;
      }
      else
      {
        
      }

        if (J->score[0] > J->score[1])
      {
        E1->jganhos++;
      }
      else
      {
        if (J->score[0] < J->score[1])
        {
          E2->jganhos++;
        }
        else
        {
          
        }

      }

        JInsere_Hash(JHash, J, JM);
        if ((++JN) > (JM / 2))
      {
        JM = JM + JM;
        JHash = Jexpande(JHash, JM);
      }
      else
      {
        
      }

        if (Match_Lst->head == 0)
      {
        Match_Lst->head = J;
        Match_Lst->last = J;
      }
      else
      {
        Match_Lst->last->next = J;
        J->prev = Match_Lst->last;
        Match_Lst->last = J;
      }

        ++NL;
        continue;

      case 'l':
        if (Match_Lst->head != 0)
      {
        for (J = Match_Lst->head; J != 0; J = J->next)
          printf("%u %s %s %s %u %u\n", NL, J->nome, J->Equipas[0], J->Equipas[1], J->score[0], J->score[1]);

      }
      else
      {
        
      }

        ++NL;
        continue;

      case 'p':
        for (int buffer_index = 0; buffer_index < 10; buffer_index++)
      {
        buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
      }

        buffer[10 - 1] = '\0';
        J = JProcura_Hash(JHash, buffer, JM);
        if (J == 0)
      {
        printf("%u Jogo inexistente.\n", NL++);
        continue;
      }
      else
      {
        
      }

        printf("%u %s %s %s %u %u\n", NL, J->nome, J->Equipas[0], J->Equipas[1], J->score[0], J->score[1]);
        ++NL;
        continue;

      case 'r':
        for (int buffer_index = 0; buffer_index < 10; buffer_index++)
      {
        buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
      }

        buffer[10 - 1] = '\0';
        J = JProcura_Hash(JHash, buffer, JM);
        if (J == 0)
      {
        printf("%u Jogo inexistente.\n", NL++);
        continue;
      }
      else
      {
        
      }

        if (J->score[0] > J->score[1])
      {
        E1 = EProcura_Hash(EHash, J->Equipas[0], EM);
        E1->jganhos--;
      }
      else
      {
        if (J->score[0] < J->score[1])
        {
          E2 = EProcura_Hash(EHash, J->Equipas[1], EM);
          E2->jganhos--;
        }
        else
        {
          
        }

      }

        JN = JRemove_Hash(JHash, buffer, JM, JN);
        Match_Lst = remove_jogo(Match_Lst, buffer);
        ++NL;
        continue;

      case 's':
        for (int buffer_index = 0; buffer_index < 10; buffer_index++)
      {
        buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
      }

        buffer[10 - 1] = '\0';
        Score1 = new_sym_var(sizeof(unsigned int) * 8);
        Score2 = new_sym_var(sizeof(unsigned int) * 8);
        J = JProcura_Hash(JHash, buffer, JM);
        if (J == 0)
      {
        printf("%u Jogo inexistente.\n", NL++);
        continue;
      }
      else
      {
        
      }

        E1 = EProcura_Hash(EHash, J->Equipas[0], EM);
        E2 = EProcura_Hash(EHash, J->Equipas[1], EM);
        if (J->score[0] > J->score[1])
      {
        E1->jganhos--;
      }
      else
      {
        if (J->score[0] < J->score[1])
        {
          E2->jganhos--;
        }
        else
        {
          
        }

      }

        if (Score1 > Score2)
      {
        E1->jganhos++;
      }
      else
      {
        if (Score1 < Score2)
        {
          E2->jganhos++;
        }
        else
        {
          
        }

      }

        J->score[0] = Score1;
        J->score[1] = Score2;
        ++NL;
        continue;

      case 'A':
        E = nova_equipa();
        for (int buffer_index = 0; buffer_index < 10; buffer_index++)
      {
        buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
      }

        buffer[10 - 1] = '\0';
        E->nome = (char *) malloc((sizeof(char)) * (strlen(buffer) + 1));
        strcpy(E->nome, buffer);
        if (EProcura_Hash(EHash, E->nome, EM) != 0)
      {
        printf("%u Equipa existente.\n", NL++);
        elimina_equipa(E);
        continue;
      }
      else
      {
        
      }

        EInsere_Hash(EHash, E, EM);
        if ((++EN) > (EM / 2))
      {
        EM = EM + EM;
        EHash = Eexpande(EHash, EM);
      }
      else
      {
        
      }

        if (Team_Lst->head == 0)
      {
        Team_Lst->head = E;
        Team_Lst->last = E;
      }
      else
      {
        Team_Lst->last->next = E;
        Team_Lst->last = E;
      }

        ++NL;
        continue;

      case 'P':
        for (int buffer_index = 0; buffer_index < 10; buffer_index++)
      {
        buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
      }

        buffer[10 - 1] = '\0';
        E = EProcura_Hash(EHash, buffer, EM);
        if (E == 0)
      {
        printf("%u Equipa inexistente.\n", NL++);
        continue;
      }
      else
      {
        
      }

        printf("%u %s %u\n", NL, E->nome, E->jganhos);
        ++NL;
        continue;

      case 'g':
        if (EN)
      {
        Max = encontra_max(Team_Lst);
        Nomes = (char **) malloc((sizeof(char *)) * EN);
        NEquipas = encontra_melhores(Team_Lst, Max, Nomes);
        qsort(Nomes, NEquipas, sizeof(char *), compare);
        printf("%u Melhores %u\n", NL, Max);
        for (i = 0; i < NEquipas; ++i)
        {
          printf("%u * %s\n", NL, Nomes[i]);
        }

        free(Nomes);
      }
      else
      {
        
      }

        ++NL;
        continue;

    }

  }
  while (C != 'x');
  JDestroi_Hash(JHash, Match_Lst);
  EDestroi_Hash(EHash, Team_Lst);
  free(Team_Lst);
  free(Match_Lst);
  return 0;
}
