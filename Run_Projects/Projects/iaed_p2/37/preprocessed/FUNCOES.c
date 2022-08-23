/*File generated by PreProcessor.py*/


#include "FUNCOES.h"


void adicionaJogo(int NL, glink *pLGhead, glink *pLGtail, tlink *HashTeams, glink *HashGames)
{
  char buffer[1024];
  char equipa1[1024];
  char equipa2[1024];
  int score1;
  int score2;
  int aux;
  int indice;
  pGame NovoJogo;
  pGame JogoExistente;
  pTeam pTeam1;
  pTeam pTeam2;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  for (int equipa1_index = 0; equipa1_index < 10; equipa1_index++)
  {
    equipa1[equipa1_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa1[10 - 1] = '\0';
  for (int equipa2_index = 0; equipa2_index < 10; equipa2_index++)
  {
    equipa2[equipa2_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa2[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  aux = searchGameHash(buffer + 1, HashGames, &JogoExistente);
  if (aux == 1)
  {
    {
      printf("%d Jogo existente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  aux = adicionaJogo_aux(equipa1, equipa2, HashTeams, &pTeam1, &pTeam2);
  if (aux == 0)
  {
    {
      NovoJogo = malloc(sizeof(struct Game));
      NovoJogo->score1 = score1;
      NovoJogo->score2 = score2;
      NovoJogo->pEquipa1 = pTeam1;
      NovoJogo->pEquipa2 = pTeam2;
      NovoJogo->name = malloc((sizeof(char)) * (strlen(buffer) + 1));
      strcpy(NovoJogo->name, buffer + 1);
      put_game(NovoJogo, pLGhead, pLGtail);
      indice = hash(buffer + 1);
      Ginsert(&HashGames[indice], NovoJogo);
      atualizaVitorias(NovoJogo, 0, 0, 0);
    }
  }
  else
  {
    printf("%d Equipa inexistente.\n", NL);
  }

}

void adicionaEquipa(int NL, tlink *pLThead, tlink *pLTtail, tlink *HashTeams)
{
  char buffer[1024];
  int aux;
  int indice;
  pTeam NovaEquipa;
  pTeam EquipaExistente;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  aux = searchTeamHash(buffer + 1, HashTeams, &EquipaExistente);
  if (aux == 0)
  {
    {
      NovaEquipa = malloc(sizeof(struct Team));
      NovaEquipa->vitorias = 0;
      NovaEquipa->name = malloc((sizeof(char)) * (strlen(buffer + 1) + 1));
      strcpy(NovaEquipa->name, buffer + 1);
      put_team(NovaEquipa, pLThead, pLTtail);
      indice = hash(buffer + 1);
      Tinsert(&HashTeams[indice], NovaEquipa);
    }
  }
  else
  {
    printf("%d Equipa existente.\n", NL);
  }

}

void listaJogos(int NL, glink *pLGhead)
{
  glink c;
  char *name;
  char *nameTeam1;
  char *nameTeam2;
  int score1;
  int score2;
  for (c = *pLGhead; c != 0; c = c->next)
  {
    name = c->pJogo->name;
    nameTeam1 = c->pJogo->pEquipa1->name;
    nameTeam2 = c->pJogo->pEquipa2->name;
    score1 = c->pJogo->score1;
    score2 = c->pJogo->score2;
    printf("%d %s %s %s %d %d\n", NL, name, nameTeam1, nameTeam2, score1, score2);
  }

}

void procuraJogo(int NL, glink *HashGames)
{
  char buffer[1024];
  char *nameTeam1;
  char *nameTeam2;
  int aux;
  int score1;
  int score2;
  pGame hit;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  aux = searchGameHash(buffer + 1, HashGames, &hit);
  if (aux == 1)
  {
    {
      nameTeam1 = hit->pEquipa1->name;
      nameTeam2 = hit->pEquipa2->name;
      score1 = hit->score1;
      score2 = hit->score2;
      printf("%d %s %s %s %d %d\n", NL, buffer + 1, nameTeam1, nameTeam2, score1, score2);
    }
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void procuraEquipa(int NL, tlink *HashTeams)
{
  char buffer[1024];
  int aux;
  pTeam hit;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  aux = searchTeamHash(buffer + 1, HashTeams, &hit);
  if (aux != 1)
  {
    printf("%d Equipa inexistente.\n", NL);
  }
  else
  {
    printf("%d %s %d\n", NL, hit->name, hit->vitorias);
  }

}

void apagaJogo(int NL, glink *pLGhead, glink *pLGtail, glink *HashGames)
{
  char buffer[1024];
  int aux;
  pGame hit;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  aux = searchGameHash(buffer + 1, HashGames, &hit);
  if (aux == 1)
  {
    {
      atualizaVitorias(hit, 1, 0, 0);
      apagaJogoHash(buffer + 1, HashGames, hit);
      apagaJogoLista(pLGhead, pLGtail, hit);
    }
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void alteraScore(int NL, glink *HashGames)
{
  char buffer[1024];
  int aux;
  int newscore1;
  int newscore2;
  pGame hit;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  newscore1 = new_sym_var(sizeof(int) * 8);
  newscore2 = new_sym_var(sizeof(int) * 8);
  aux = searchGameHash(buffer + 1, HashGames, &hit);
  if (aux == 1)
  {
    {
      atualizaVitorias(hit, 2, newscore1, newscore2);
      hit->score1 = newscore1;
      hit->score2 = newscore2;
    }
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void melhoresEquipas(int NL, tlink *pLThead)
{
  tlink c;
  char *melhores[20];
  int i;
  int count;
  int maxvitorias = 0;
  for (c = *pLThead; c != 0; c = c->next)
  {
    if (c->pEquipa->vitorias > maxvitorias)
    {
      maxvitorias = c->pEquipa->vitorias;
    }
    else
    {
      
    }

  }

  for (c = *pLThead, i = 0, count = 0; c != 0; c = c->next)
  {
    if (c->pEquipa->vitorias == maxvitorias)
    {
      {
        melhores[i] = c->pEquipa->name;
        count++;
        i++;
      }
    }
    else
    {
      
    }

  }

  qsort(melhores, count, sizeof(char *), cstring_cmp);
  if (count != 0)
  {
    {
      printf("%d Melhores %d\n", NL, maxvitorias);
      for (i = 0; i < count; i++)
        printf("%d * %s\n", NL, melhores[i]);

    }
  }
  else
  {
    
  }

}

void sair(tlink *pLThead, tlink *pLTtail, glink *pLGh, glink *pLGt, tlink *HashT, glink *HashG)
{
  limpaFilaEquipa(pLThead, pLTtail);
  limpaFilaJogo(pLGh, pLGt);
  limpaHashTeams(HashT);
  limpaHashGames(HashG);
}

