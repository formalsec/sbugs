#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"


hashJ *lista_jogos;
hashE *lista_equipas;
int nl;
int get_string(char c[])
{
  char ch;
  int i = 0;
  while ((((ch = getchar()) != ':') && (ch != '\0')) && (ch != '\n'))
  {
    c[i++] = ch;
  }

  c[i] = '\0';
  return 0;
}

int get_int()
{
  char ch;
  int i = 0;
  while ((((ch = getchar()) != ':') && (ch != '\0')) && (ch != '\n'))
  {
    i = (i * 10) + (ch - '0');
  }

  return i;
}

int main()
{
  char comando = 'y';
  nl = 0;
  lista_jogos = criaHash();
  lista_equipas = criaHashE();
  while (comando != 'x')
  {
    switch (comando = getchar())
    {
      case 'a':
      {
        char nomejogo[1024];
        char equipa1[1024];
        char equipa2[1024];
        int pontos1;
        int pontos2;
        int aux;
        nl++;
        getchar();
        get_string(nomejogo);
        get_string(equipa1);
        get_string(equipa2);
        pontos1 = get_int();
        pontos2 = get_int();
        aux = adicionaJogo(lista_jogos, lista_equipas, nomejogo, equipa1, equipa2, pontos1, pontos2);
        if (aux == 1)
        {
          printf("%d Jogo existente.\n", nl);
        }
        else
        {
          
        }

        if (aux == 2)
        {
          printf("%d Equipa inexistente.\n", nl);
        }
        else
        {
          
        }

        break;
      }

      case 'r':
      {
        char nome[1024];
        nl++;
        getchar();
        get_string(nome);
        removeJogo(lista_jogos, lista_equipas, nome, nl);
        break;
      }

      case 'P':
      {
        equipa *temporario;
        char nome[1024];
        nl++;
        getchar();
        get_string(nome);
        temporario = procuraEquipa(lista_equipas, nome);
        if (temporario != 0)
        {
          printf("%d %s %d\n", nl, nome, temporario->vitorias);
          break;
        }
        else
        {
          
        }

        printf("%d Equipa inexistente.\n", nl);
        break;
      }

      case 'A':
      {
        char nome[1024];
        nl++;
        getchar();
        get_string(nome);
        if (adicionaEquipa(lista_equipas, nome) == 0)
        {
          printf("%d Equipa existente.\n", nl);
        }
        else
        {
          
        }

        break;
      }

      case 'p':
      {
        char nome[1024];
        jogo *j;
        getchar();
        nl++;
        get_string(nome);
        j = procuraJogo(lista_jogos, nome);
        if (!j)
        {
          printf("%d Jogo inexistente.\n", nl);
          break;
        }
        else
        {
          
        }

        printf("%d %s %s %s %d %d\n", nl, j->nome, j->equipa1, j->equipa2, j->pontos1, j->pontos2);
        break;
      }

      case 'l':
        nl++;
        imprimeLista(nl);
        break;

      case 's':
      {
        char nome[1024];
        int pontos1;
        int pontos2;
        nl++;
        getchar();
        get_string(nome);
        pontos1 = get_int();
        pontos2 = get_int();
        alterapontos(lista_jogos, lista_equipas, nome, pontos1, pontos2, nl);
        break;
      }

      case 'g':
        break;

      case 'x':
        break;

    }

  }

  return 0;
}

