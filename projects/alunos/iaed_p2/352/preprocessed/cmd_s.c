#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "header.h"


void cmd_s()
{
  Jogo *aux;
  Equipa *aux1;
  Equipa *aux2;
  char nome_jogo[1025];
  int indice_jogo;
  int indice_equipa1;
  int indice_equipa2;
  int score_1;
  int score_2;
  int score_antigo_1;
  int score_antigo_2;
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  score_1 = new_sym_var(sizeof(int) * 8);
  score_2 = new_sym_var(sizeof(int) * 8);
  indice_jogo = hash(nome_jogo);
  if (HashGames[indice_jogo] == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
    return;
  }
  else
  {
    
  }

  if (strcmp(HashGames[indice_jogo]->nome, nome_jogo) != 0)
  {
    aux = HashGames[indice_jogo];
    while ((aux != 0) && (strcmp(aux->nome, nome_jogo) != 0))
      aux = aux->next;

    if (aux == 0)
    {
      printf("%d Jogo inexistente.\n", nl);
      return;
    }
    else
    {
      
    }

    score_antigo_1 = aux->score_1;
    score_antigo_2 = aux->score_2;
    aux->score_1 = score_1;
    aux->score_2 = score_2;
  }
  else
  {
    score_antigo_1 = HashGames[indice_jogo]->score_1;
    score_antigo_2 = HashGames[indice_jogo]->score_2;
    aux = HashGames[indice_jogo];
    HashGames[indice_jogo]->score_1 = score_1;
    HashGames[indice_jogo]->score_2 = score_2;
  }

  indice_equipa1 = hash(aux->equipa_1);
  indice_equipa2 = hash(aux->equipa_2);
  aux1 = HashTeams[indice_equipa1];
  aux2 = HashTeams[indice_equipa2];
  if (strcmp(aux1->nome_equipa, aux->equipa_1) != 0)
  {
    while (strcmp(aux1->nome_equipa, aux->equipa_1) != 0)
      aux1 = aux1->next;

  }
  else
  {
    
  }

  if (strcmp(aux2->nome_equipa, aux->equipa_2) != 0)
  {
    while (strcmp(aux2->nome_equipa, aux->equipa_2) != 0)
      aux2 = aux2->next;

  }
  else
  {
    
  }

  if ((score_antigo_1 > score_antigo_2) && (score_1 < score_2))
  {
    aux1->vitorias--;
    aux2->vitorias++;
    return;
  }
  else
  {
    
  }

  if ((score_antigo_1 < score_antigo_2) && (score_1 > score_2))
  {
    aux1->vitorias++;
    aux2->vitorias--;
    return;
  }
  else
  {
    
  }

  if ((score_antigo_1 == score_antigo_2) && (score_1 < score_2))
  {
    aux2->vitorias++;
    return;
  }
  else
  {
    
  }

  if ((score_antigo_1 == score_antigo_2) && (score_1 > score_2))
  {
    aux1->vitorias++;
    return;
  }
  else
  {
    
  }

  if ((score_antigo_1 > score_antigo_2) && (score_1 == score_2))
  {
    aux1->vitorias--;
    return;
  }
  else
  {
    
  }

  if ((score_antigo_1 < score_antigo_2) && (score_1 == score_2))
  {
    aux2->vitorias--;
  }
  else
  {
    
  }

}

