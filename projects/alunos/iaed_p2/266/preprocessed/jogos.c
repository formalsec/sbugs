#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h" /* Ficheiro que contem as funcoes que geram os jogos e as equipas */


int Hash(char *received)
{
  int h;
  int a = 127;
  for (h = 0; strcmp(received, "\0"); received++)
  {
    h = ((a * h) + (*received)) % 2497;
  }

  return h;
}

void Printar(listajogos *list)
{
  int i;
  for (i = 0; i < 2497; ++i)
  {
    jogo *entry = list->hashjogos[i];
    if (entry == 0)
    {
      continue;
    }
    else
    {
      
    }

    printf("slot[%4d]: ", i);
    for (;;)
    {
      printf("%s %s %s", entry->nomej, entry->equipa1->nomeeq, entry->equipa2->nomeeq);
      if (entry->proximoj == 0)
      {
        break;
      }
      else
      {
        
      }

      entry = entry->proximoj;
    }

    printf("\n");
  }

}

listajogos *NovaListaJogos()
{
  int i = 0;
  listajogos *novalista = malloc(sizeof(struct listajogos));
  novalista->fimj = 0;
  novalista->inicioj = 0;
  while (i < 2497)
  {
    novalista->hashjogos[i] = malloc((sizeof(struct jogo)) * 2497);
    novalista->hashjogos[i] = 0;
    i++;
  }

  return novalista;
}

listaequipas *NovaListaEquipas()
{
  int i = 0;
  listaequipas *novalista = malloc(sizeof(struct listaequipas));
  novalista->fimeq = 0;
  novalista->inicioeq = 0;
  while (i < 2497)
  {
    novalista->hashequipas[i] = malloc((sizeof(struct equipa)) * 2497);
    novalista->hashequipas[i] = 0;
    i++;
  }

  return novalista;
}

jogo *ProcuraJogoAuxiliar(listajogos *list, char *nomejogo)
{
  int key = Hash(nomejogo);
  int i = 1;
  jogo *procurar = list->hashjogos[key];
  while (procurar != 0)
  {
    if (strcmp(procurar->nomej, nomejogo) == 0)
    {
      return procurar;
      break;
    }
    else
    {
      int tentativa = (i + key) % 2497;
      procurar = list->hashjogos[tentativa];
      i++;
    }

  }

  return procurar;
}

equipa *ProcuraEquipaAuxiliar(listaequipas *list1, char *equipanome)
{
  int key = Hash(equipanome);
  int i = 1;
  equipa *procurar = list1->hashequipas[key];
  while (procurar != 0)
  {
    if (strcmp(procurar->nomeeq, equipanome) == 0)
    {
      return procurar;
      break;
    }
    else
    {
      int tentativa = (i + key) % 2497;
      procurar = list1->hashequipas[tentativa];
      i++;
    }

  }

  return procurar;
}

equipa *NovaEquipa(char *equipanome, listaequipas *list1)
{
  equipa *novaequipa = malloc(sizeof(struct equipa));
  novaequipa->proximoeq = 0;
  novaequipa->anterioreq = list1->fimeq;
  novaequipa->nomeeq = malloc((sizeof(char)) * 1024);
  novaequipa->nomeeq = strcpy(novaequipa->nomeeq, equipanome);
  novaequipa->vitorias = 0;
  return novaequipa;
}

jogo *NovoJogo(char *nomejogo, char *equipa1nome, char *equipa2nome, int score1recebido, int score2recebido, listajogos *list)
{
  jogo *novojogo = malloc(sizeof(struct jogo));
  novojogo->proximoj = 0;
  novojogo->anteriorj = list->fimj;
  novojogo->nomej = malloc((sizeof(char)) * 1024);
  novojogo->equipa1 = malloc((sizeof(char)) * 1024);
  novojogo->equipa2 = malloc((sizeof(char)) * 1024);
  novojogo->nomej = strcpy(novojogo->nomej, nomejogo);
  novojogo->equipa1->nomeeq = (char *) memcpy(malloc((sizeof(char)) * (strlen(equipa1nome) + 1)), equipa1nome, (sizeof(char)) * (strlen(equipa1nome) + 1));
  novojogo->equipa2->nomeeq = (char *) memcpy(malloc((sizeof(char)) * (strlen(equipa2nome) + 1)), equipa2nome, (sizeof(char)) * (strlen(equipa2nome) + 1));
  novojogo->score1 = score1recebido;
  novojogo->score2 = score2recebido;
  return novojogo;
}

listajogos *AdicionaJogo(listajogos *list, listaequipas *list1, char *nomejogo, char *equipa1nome, char *equipa2nome, int score1recebido, int score2recebido, int comando)
{
  jogo *procurajogo;
  jogo *novojogo;
  equipa *procuraequipa1;
  equipa *procuraequipa2;
  int key = Hash(nomejogo);
  int i;
  int vitoria1;
  int vitoria2;
  procurajogo = ProcuraJogoAuxiliar(list, nomejogo);
  procuraequipa1 = ProcuraEquipaAuxiliar(list1, equipa1nome);
  procuraequipa2 = ProcuraEquipaAuxiliar(list1, equipa2nome);
  if (procurajogo != 0)
  {
    printf("%d Jogo existente.\n", comando);
    return list;
  }
  else
  {
    
  }

  if (procuraequipa1 == 0)
  {
    printf("%d Equipa inexistente.\n", comando);
    return list;
  }
  else
  {
    
  }

  if (procuraequipa2 == 0)
  {
    printf("%d Equipa inexistente.\n", comando);
    return list;
  }
  else
  {
    novojogo = NovoJogo(nomejogo, equipa1nome, equipa2nome, score1recebido, score2recebido, list);
    if (score1recebido > score2recebido)
    {
      vitoria1 = Hash(equipa1nome);
      list1->hashequipas[vitoria1]->vitorias++;
    }
    else
    {
      
    }

    if (score1recebido < score2recebido)
    {
      vitoria2 = Hash(equipa2nome);
      list1->hashequipas[vitoria2]->vitorias++;
    }
    else
    {
      
    }

    if (list->hashjogos[key] == 0)
    {
      list->hashjogos[key] = novojogo;
    }
    else
    {
      for (i = 0; i < 2497; i++)
      {
        int tentativa = (i + key) % 2497;
        novojogo->proximoj = list->hashjogos[tentativa];
        if (novojogo->proximoj == 0)
        {
          list->hashjogos[tentativa] = novojogo;
          break;
        }
        else
        {
          
        }

      }

    }

    if (list->inicioj == 0)
    {
      list->inicioj = novojogo;
    }
    else
    {
      list->fimj->proximoj = novojogo;
      novojogo->anteriorj = list->fimj;
    }

    list->fimj = novojogo;
  }

  return list;
}

listaequipas *AdicionaEquipa(listaequipas *list1, char *equipanome, int comando)
{
  equipa *procuraequipa = ProcuraEquipaAuxiliar(list1, equipanome);
  int key = Hash(equipanome);
  int i;
  if (procuraequipa != 0)
  {
    printf("%d Equipa existente.\n", comando);
    return list1;
  }
  else
  {
    equipa *novaequipa = NovaEquipa(equipanome, list1);
    if (list1->hashequipas[key] == 0)
    {
      list1->hashequipas[key] = novaequipa;
    }
    else
    {
      for (i = 0; i < 2497; i++)
      {
        int tentativa = (i + key) % 2497;
        novaequipa->proximoeq = list1->hashequipas[tentativa];
        if (novaequipa->proximoeq == 0)
        {
          list1->hashequipas[tentativa] = novaequipa;
          break;
        }
        else
        {
          
        }

      }

    }

    if (list1->inicioeq == 0)
    {
      list1->inicioeq = novaequipa;
    }
    else
    {
      list1->fimeq->proximoeq = novaequipa;
      novaequipa->anterioreq = list1->fimeq;
    }

    list1->fimeq = novaequipa;
  }

  return list1;
}

void ListaJogos(listajogos *list, int comando)
{
  jogo *listar = list->inicioj;
  if (listar == 0)
  {
    return;
  }
  else
  {
    
  }

  while (listar != 0)
  {
    printf("%d %s %s %s %d %d\n", comando, listar->nomej, listar->equipa1->nomeeq, listar->equipa2->nomeeq, listar->score1, listar->score2);
    listar = listar->proximoj;
  }

  return;
}

jogo *ProcuraJogo(listajogos *list, char *nomejogo, int comando)
{
  jogo *procurar = ProcuraJogoAuxiliar(list, nomejogo);
  if (procurar == 0)
  {
    printf("%d Jogo inexistente.\n", comando);
    return procurar;
  }
  else
  {
    
  }

  printf("%d %s %s %s %d %d\n", comando, procurar->nomej, procurar->equipa1->nomeeq, procurar->equipa2->nomeeq, procurar->score1, procurar->score2);
  return procurar;
}

equipa *ProcuraEquipa(listaequipas *list1, char *equipanome, int comando)
{
  equipa *procurar = ProcuraEquipaAuxiliar(list1, equipanome);
  if (procurar == 0)
  {
    printf("%d Equipa inexistente.\n", comando);
    return procurar;
  }
  else
  {
    
  }

  printf("%d %s %d\n", comando, procurar->nomeeq, procurar->vitorias);
  return procurar;
}

listajogos *ApagaJogo(listajogos *list, listaequipas *list1, char *nomejogo, int comando)
{
  int key = Hash(nomejogo);
  int i;
  int vitoria1;
  int vitoria2;
  jogo *remover = ProcuraJogoAuxiliar(list, nomejogo);
  if (remover == 0)
  {
    printf("%d Jogo inexistente.\n", comando);
    return list;
  }
  else
  {
    if (remover->score1 > remover->score2)
    {
      vitoria1 = Hash(remover->equipa1->nomeeq);
      list1->hashequipas[vitoria1]->vitorias--;
    }
    else
    {
      
    }

    if (remover->score1 < remover->score2)
    {
      vitoria2 = Hash(remover->equipa2->nomeeq);
      list1->hashequipas[vitoria2]->vitorias--;
    }
    else
    {
      
    }

    if (remover->anteriorj != 0)
    {
      remover->anteriorj->proximoj = remover->proximoj;
    }
    else
    {
      
    }

    if (remover->proximoj != 0)
    {
      remover->proximoj->anteriorj = remover->anteriorj;
    }
    else
    {
      
    }

    if (remover == list->inicioj)
    {
      list->inicioj = remover->proximoj;
    }
    else
    {
      
    }

    if (remover == list->fimj)
    {
      list->fimj = remover->anteriorj;
    }
    else
    {
      
    }

    if (strcmp(nomejogo, list->hashjogos[key]->nomej) == 0)
    {
      list->hashjogos[key] = remover->proximoj;
    }
    else
    {
      for (i = 0; i < 2497; i++)
      {
        int tentativa = (i + key) % 2497;
        remover->proximoj = list->hashjogos[tentativa];
        if (strcmp(nomejogo, list->hashjogos[tentativa]->nomej) == 0)
        {
          list->hashjogos[tentativa] = remover->proximoj;
        }
        else
        {
          
        }

      }

    }

    free(remover->nomej);
    free(remover->equipa1);
    free(remover->equipa2);
    free(remover);
  }

  return list;
}

listajogos *AlteraScore(listajogos *list, listaequipas *list1, char *nomejogo, int score1recebido, int score2recebido, int comando)
{
  int key = Hash(nomejogo);
  int i;
  int vitoria1;
  int vitoria2;
  jogo *alterar = ProcuraJogoAuxiliar(list, nomejogo);
  if (alterar == 0)
  {
    printf("%d Jogo inexistente.\n", comando);
    return list;
  }
  else
  {
    
  }

  if (strcmp(nomejogo, list->hashjogos[key]->nomej) == 0)
  {
    if (list->hashjogos[key]->score1 > list->hashjogos[key]->score2)
    {
      vitoria1 = Hash(list->hashjogos[key]->equipa1->nomeeq);
      list1->hashequipas[vitoria1]->vitorias--;
    }
    else
    {
      
    }

    if (list->hashjogos[key]->score1 < list->hashjogos[key]->score2)
    {
      vitoria2 = Hash(list->hashjogos[key]->equipa2->nomeeq);
      list1->hashequipas[vitoria2]->vitorias--;
    }
    else
    {
      
    }

    list->hashjogos[key]->score1 = score1recebido;
    list->hashjogos[key]->score2 = score2recebido;
    if (score1recebido > score2recebido)
    {
      vitoria1 = Hash(list->hashjogos[key]->equipa1->nomeeq);
      list1->hashequipas[vitoria1]->vitorias++;
    }
    else
    {
      
    }

    if (score1recebido < score2recebido)
    {
      vitoria2 = Hash(list->hashjogos[key]->equipa2->nomeeq);
      list1->hashequipas[vitoria2]->vitorias++;
    }
    else
    {
      
    }

  }
  else
  {
    for (i = 0; i < 2497; i++)
    {
      int tentativa = (i + key) % 2497;
      alterar->proximoj = list->hashjogos[tentativa];
      if (strcmp(nomejogo, list->hashjogos[tentativa]->nomej) == 0)
      {
        if (list->hashjogos[tentativa]->score1 > list->hashjogos[tentativa]->score2)
        {
          vitoria1 = Hash(list->hashjogos[tentativa]->equipa1->nomeeq);
          list1->hashequipas[vitoria1]->vitorias--;
        }
        else
        {
          
        }

        if (list->hashjogos[tentativa]->score1 < list->hashjogos[tentativa]->score2)
        {
          vitoria2 = Hash(list->hashjogos[tentativa]->equipa2->nomeeq);
          list1->hashequipas[vitoria2]->vitorias--;
        }
        else
        {
          
        }

        list->hashjogos[tentativa]->score1 = score1recebido;
        list->hashjogos[tentativa]->score2 = score2recebido;
        if (score1recebido > score2recebido)
        {
          vitoria1 = Hash(list->hashjogos[tentativa]->equipa1->nomeeq);
          list1->hashequipas[vitoria1]->vitorias++;
        }
        else
        {
          
        }

        if (score1recebido < score2recebido)
        {
          vitoria2 = Hash(list->hashjogos[tentativa]->equipa2->nomeeq);
          list1->hashequipas[vitoria2]->vitorias++;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

  }

  return list;
}

static int cmp_str(const void *lhs, const void *rhs)
{
  return strcmp(lhs, rhs);
}

void OrdenaEquipas(listaequipas *list1, int comando)
{
  int wins = 0;
  equipa *comeco = list1->inicioeq;
  equipa *head = list1->inicioeq;
  listaequipas *new = NovaListaEquipas();
  while (comeco != 0)
  {
    if (comeco->vitorias > wins)
    {
      wins = comeco->vitorias;
    }
    else
    {
      
    }

    comeco = comeco->proximoeq;
  }

  while (head != 0)
  {
    if (head->vitorias == wins)
    {
      strcpy(new->inicioeq->nomeeq, head->nomeeq);
    }
    else
    {
      
    }

    head = head->proximoeq;
    new->inicioeq = new->inicioeq->proximoeq;
  }

  if (new->inicioeq != 0)
  {
    printf("%d Melhores %d\n", comando, wins);
    qsort(new, 1024, sizeof(new->inicioeq), cmp_str);
    for (; new->inicioeq->proximoeq != 0; new->inicioeq = new->inicioeq->proximoeq)
    {
      printf("%d * %s\n", comando, new->inicioeq->proximoeq->nomeeq);
    }

  }
  else
  {
    
  }

}

