/*File generated by PreProcessor.py*/


#include <stdio.h>
#include "struct.h"
#include "equipa.h"
#include "jogo.h"
#include "interface.h"


void inicializarHT(ItemFirstHT **headsJogo, lista *listaJogo, ItemSecondHT **headsEquipa, int capacidadeJ, int capacidadeE)
{
  HTInitFirst(headsJogo, listaJogo, capacidadeJ);
  InitSecondHT(headsEquipa, capacidadeE);
}

int hash(char *key, int capacidade)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*key) != '\0'; key++, a = (a * b) % (capacidade - 1))
    h = ((a * h) + (*key)) % capacidade;

  return h;
}

void adicionarEquipa(ItemSecondHT **headsEquipa, int capacidadeE, int linha)
{
  char nomeEquipa[1024];
  for (int nomeEquipa_index = 0; nomeEquipa_index < 10; nomeEquipa_index++)
  {
    nomeEquipa[nomeEquipa_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeEquipa[10 - 1] = '\0';
  if (HTInserirElementoS(nomeEquipa, headsEquipa, capacidadeE) == 0)
  {
    printf("%d Equipa existente.\n", linha);
  }
  else
  {
    
  }

}

void procurarMelhoresEquipas(ItemSecondHT **headsEquipa, int capacidadeE, int linha)
{
  HTencontraEquipasVencedoras(headsEquipa, capacidadeE, linha);
}

void imprimirEquipa(equipa *eq)
{
  printf("%s %d\n", eq->nome, eq->vitorias);
}

void procurarEquipa(ItemSecondHT **headsEquipa, int capacidadeE, int linha)
{
  char nomeEquipa[1024];
  equipa *e;
  for (int nomeEquipa_index = 0; nomeEquipa_index < 10; nomeEquipa_index++)
  {
    nomeEquipa[nomeEquipa_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeEquipa[10 - 1] = '\0';
  e = HTProcurarElementoS(nomeEquipa, headsEquipa, capacidadeE);
  if (e == 0)
  {
    printf("%d Equipa inexistente.\n", linha);
  }
  else
  {
    printf("%d ", linha);
    imprimirEquipa(e);
  }

}

void adicionarJogo(ItemFirstHT **headsJogo, lista *listaJogo, ItemSecondHT **headsEquipa, int capacidadeE, int capacidadeJ, int linha)
{
  int s1;
  int s2;
  equipa *e1;
  equipa *e2;
  char nomeJogo[1024];
  char nomeEquipa[1024];
  char nomeEquipa2[1024];
  for (int nomeJogo_index = 0; nomeJogo_index < 10; nomeJogo_index++)
  {
    nomeJogo[nomeJogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeJogo[10 - 1] = '\0';
  for (int nomeEquipa_index = 0; nomeEquipa_index < 10; nomeEquipa_index++)
  {
    nomeEquipa[nomeEquipa_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeEquipa[10 - 1] = '\0';
  for (int nomeEquipa2_index = 0; nomeEquipa2_index < 10; nomeEquipa2_index++)
  {
    nomeEquipa2[nomeEquipa2_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeEquipa2[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  if (HTProcurarElementoF(nomeJogo, capacidadeJ, headsJogo) != 0)
  {
    printf("%d Jogo existente.\n", linha);
  }
  else
  {
    if (((e1 = HTProcurarElementoS(nomeEquipa, headsEquipa, capacidadeE)) == 0) || ((e2 = HTProcurarElementoS(nomeEquipa2, headsEquipa, capacidadeE)) == 0))
    {
      printf("%d Equipa inexistente.\n", linha);
    }
    else
    {
      HTInserirElementoF(nomeJogo, s1, s2, capacidadeJ, headsJogo, listaJogo, e1, e2);
    }

  }

}

void encontrarJogo(int capacidadeJ, ItemFirstHT **headsJogo, int linha)
{
  char nomeJogo[1024];
  jogo *pJogo;
  for (int nomeJogo_index = 0; nomeJogo_index < 10; nomeJogo_index++)
  {
    nomeJogo[nomeJogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeJogo[10 - 1] = '\0';
  pJogo = HTProcurarElementoF(nomeJogo, capacidadeJ, headsJogo);
  if (pJogo == 0)
  {
    printf("%d Jogo inexistente.\n", linha);
  }
  else
  {
    imprimirJogo(pJogo, linha);
  }

}

void imprimirJogo(jogo *jogo, int linha)
{
  printf("%d %s %s %s %d %d\n", linha, jogo->nome, jogo->pEquipa->nome, jogo->sEquipa->nome, jogo->pScore, jogo->sScore);
}

void listarJogos(lista *listaJogo, int linha)
{
  HTListarElementos(linha, listaJogo);
}

void alterarPontuacao(int capacidadeJ, ItemFirstHT **headsJogo, int linha)
{
  int s1;
  int s2;
  int i;
  char nomeJogo[1024];
  for (int nomeJogo_index = 0; nomeJogo_index < 10; nomeJogo_index++)
  {
    nomeJogo[nomeJogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeJogo[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  i = HTAlterarPontuacao(nomeJogo, s1, s2, capacidadeJ, headsJogo);
  if (i == 0)
  {
    printf("%d Jogo inexistente.\n", linha);
  }
  else
  {
    
  }

}

void removerJogo(ItemFirstHT **headsJogo, int capacidadeJ, lista *listaJogo, int linha)
{
  int i;
  char nomeJogo[1024];
  for (int nomeJogo_index = 0; nomeJogo_index < 10; nomeJogo_index++)
  {
    nomeJogo[nomeJogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeJogo[10 - 1] = '\0';
  if ((i = HTRemoverElemento(headsJogo, capacidadeJ, nomeJogo, listaJogo)) == 0)
  {
    printf("%d Jogo inexistente.\n", linha);
  }
  else
  {
    
  }

}

void freeAll(ItemFirstHT **headsJogo, ItemSecondHT **headsEquipa, lista *listaJogo, int capacidadeE, int capacidadeJ)
{
  freeAllEquipa(headsEquipa, capacidadeE);
  freeAllJogo(headsJogo, capacidadeJ, listaJogo);
}

