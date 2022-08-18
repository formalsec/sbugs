/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h" /* atraves deste include, acesso os ficheiros hashtable.h, equipa.h e Jogo.h */


int main()
{
  char comando;
  char nome[1024];
  char equipa_casa[1024];
  char equipa_fora[1024];
  int score_equipa_casa;
  int score_equipa_fora;
  int NL = 1;
  Jogo *HashTable_Jogos = 0;
  Jogo jogo = 0;
  Equipa *HashTable_Equipas = 0;
  Equipa equipa = 0;
  Lista lista = 0;
  Lista_Equipas lista_equipas = 0;
  HashTable_Jogos = inicializa(50051);
  HashTable_Equipas = inicializa_equipas(50051);
  comando = getchar();
  while (comando != 'x')
  {
    switch (comando)
    {
      case 'a':
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        for (int equipa_casa_index = 0; equipa_casa_index < 10; equipa_casa_index++)
      {
        equipa_casa[equipa_casa_index] = new_sym_var(sizeof(char) * 8);
      }

        equipa_casa[10 - 1] = '\0';
        for (int equipa_fora_index = 0; equipa_fora_index < 10; equipa_fora_index++)
      {
        equipa_fora[equipa_fora_index] = new_sym_var(sizeof(char) * 8);
      }

        equipa_fora[10 - 1] = '\0';
        score_equipa_casa = new_sym_var(sizeof(int) * 8);
        score_equipa_fora = new_sym_var(sizeof(int) * 8);
        if (procura(nome, HashTable_Jogos, 50051) == 0)
      {
        {
          if (verifica_equipas(equipa_casa, equipa_fora, HashTable_Equipas, 50051) == 0)
          {
            {
              jogo = novo_jogo(nome, equipa_casa, equipa_fora, score_equipa_casa, score_equipa_fora);
              HashTable_Jogos = insere(jogo, HashTable_Jogos, 50051);
              lista = insere_lista(lista, jogo);
              HashTable_Equipas = atribui_vitoria(HashTable_Equipas, jogo->Equipa_Casa, jogo->Equipa_Fora, jogo->Score_Equipa_Casa, jogo->Score_Equipa_Fora, 50051);
            }
          }
          else
          {
            {
              printf("%d Equipa inexistente.\n", NL);
            }
          }

        }
      }
      else
      {
        {
          printf("%d Jogo existente.\n", NL);
        }
      }

        NL += 1;
        break;

      case 'A':
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        if (equipa_nova(nome, HashTable_Equipas, 50051) == 0)
      {
        {
          equipa = nova_equipa(nome);
          HashTable_Equipas = insere_equipa(equipa, HashTable_Equipas, 50051);
          lista_equipas = insere_lista_equipas(lista_equipas, equipa);
        }
      }
      else
      {
        {
          printf("%d Equipa existente.\n", NL);
        }
      }

        NL += 1;
        break;

      case 'P':
        procura_equipa(HashTable_Equipas, 50051, NL);
        NL += 1;
        break;

      case 'l':
        print_lista(lista, NL);
        NL += 1;
        break;

      case 'p':
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        jogo = procura(nome, HashTable_Jogos, 50051);
        if (jogo != 0)
      {
        {
          printf("%d %s %s %s %d %d\n", NL, jogo->Nome, jogo->Equipa_Casa, jogo->Equipa_Fora, jogo->Score_Equipa_Casa, jogo->Score_Equipa_Fora);
        }
      }
      else
      {
        {
          printf("%d Jogo inexistente.\n", NL);
        }
      }

        NL += 1;
        break;

      case 'r':
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        jogo = procura(nome, HashTable_Jogos, 50051);
        if (jogo != 0)
      {
        {
          HashTable_Equipas = retira_vitoria(HashTable_Equipas, jogo->Equipa_Casa, jogo->Equipa_Fora, jogo->Score_Equipa_Casa, jogo->Score_Equipa_Fora, 50051);
          lista = apaga_na_lista(lista, nome);
          HashTable_Jogos = apaga_jogo(HashTable_Jogos, nome, 50051);
        }
      }
      else
      {
        {
          printf("%d Jogo inexistente.\n", NL);
        }
      }

        NL += 1;
        break;

      case 's':
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        jogo = procura(nome, HashTable_Jogos, 50051);
        if (jogo != 0)
      {
        {
          HashTable_Equipas = retira_vitoria(HashTable_Equipas, jogo->Equipa_Casa, jogo->Equipa_Fora, jogo->Score_Equipa_Casa, jogo->Score_Equipa_Fora, 50051);
          HashTable_Jogos = altera_score(nome, HashTable_Jogos, 50051);
          HashTable_Equipas = atribui_vitoria(HashTable_Equipas, jogo->Equipa_Casa, jogo->Equipa_Fora, jogo->Score_Equipa_Casa, jogo->Score_Equipa_Fora, 50051);
        }
      }
      else
      {
        {
          printf("%d Jogo inexistente.\n", NL);
        }
      }

        NL += 1;
        break;

      case 'g':
        print_lista_equipas(lista_equipas, NL);
        NL += 1;
        break;

    }

    comando = getchar();
  }

  free_equipas(lista_equipas);
  free_jogos(lista);
  free(HashTable_Jogos);
  free(HashTable_Equipas);
  return 0;
}

