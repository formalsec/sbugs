/*File generated by PreProcessor.py*/


#include "jogos.h"


int JogoJaAdicionado(HashTableJogos *HTJ, int hash, char *nome)
{
  HashNoJogos *aux = HTJ->listasjog[hash];
  for (; aux; aux = aux->proxjogoh)
  {
    if (!strcmp(aux->dadosjogo->nomejogo, nome))
    {
      return 1;
    }
    else
    {
      
    }

  }

  return 0;
}

void RemoveVitoria(char *equipa, HashTableEquipas *HTE)
{
  int hashequipa = Hash(equipa, HTE->capacidade);
  HashNoEquipas *aux = EquipaJaAdicionada(HTE, hashequipa, equipa);
  aux->dadosequipa->vitorias--;
}

void AdicionaVitoria(char *equipa, HashTableEquipas *HTE)
{
  int hashequipa = Hash(equipa, HTE->capacidade);
  HashNoEquipas *aux = EquipaJaAdicionada(HTE, hashequipa, equipa);
  aux->dadosequipa->vitorias++;
}

void AlteraGolos(HashNoJogos *nojogo, int golose1, int golose2)
{
  nojogo->dadosjogo->golos1 = golose1;
  nojogo->dadosjogo->golos2 = golose2;
}

void AdicionarJogo(int *contacomandos, ListaDuplaJogo *listajogos, HashTableJogos *HTJ, HashTableEquipas *HTE)
{
  char bufferequipa1[1023 + 1];
  char bufferequipa2[1023 + 1];
  char buffernome[1023 + 1];
  int hashbuffer1;
  int hashbuffer2;
  int hashnome;
  int golose1;
  int golose2;
  NoDuploJogos *novo;
  getchar();
  for (int buffernome_index = 0; buffernome_index < (1023 + 1); buffernome_index++)
  {
    buffernome[buffernome_index] = new_sym_var(sizeof(char) * 8);
  }

  buffernome[(1023 + 1) - 1] = '\0';
  for (int bufferequipa1_index = 0; bufferequipa1_index < (1023 + 1); bufferequipa1_index++)
  {
    bufferequipa1[bufferequipa1_index] = new_sym_var(sizeof(char) * 8);
  }

  bufferequipa1[(1023 + 1) - 1] = '\0';
  for (int bufferequipa2_index = 0; bufferequipa2_index < (1023 + 1); bufferequipa2_index++)
  {
    bufferequipa2[bufferequipa2_index] = new_sym_var(sizeof(char) * 8);
  }

  bufferequipa2[(1023 + 1) - 1] = '\0';
  golose1 = new_sym_var(sizeof(int) * 8);
  golose2 = new_sym_var(sizeof(int) * 8);
  hashnome = Hash(buffernome, HTJ->capacidade);
  if (JogoJaAdicionado(HTJ, hashnome, buffernome))
  {
    printf("%d Jogo existente.\n", *contacomandos);
    (*contacomandos)++;
    return;
  }
  else
  {
    
  }

  hashbuffer1 = Hash(bufferequipa1, HTE->capacidade);
  hashbuffer2 = Hash(bufferequipa2, HTE->capacidade);
  if ((!EquipaJaAdicionada(HTE, hashbuffer1, bufferequipa1)) || (!EquipaJaAdicionada(HTE, hashbuffer2, bufferequipa2)))
  {
    printf("%d Equipa inexistente.\n", *contacomandos);
    (*contacomandos)++;
    return;
  }
  else
  {
    
  }

  novo = malloc(sizeof(NoDuploJogos));
  novo->equipa1 = malloc((sizeof(char)) * (strlen(bufferequipa1) + 1));
  novo->equipa2 = malloc((sizeof(char)) * (strlen(bufferequipa2) + 1));
  novo->nomejogo = malloc((sizeof(char)) * (strlen(buffernome) + 1));
  strcpy(novo->equipa1, bufferequipa1);
  strcpy(novo->equipa2, bufferequipa2);
  strcpy(novo->nomejogo, buffernome);
  novo->antjogo = listajogos->ultimo;
  novo->proxjogo = 0;
  novo->golos1 = golose1;
  novo->golos2 = golose2;
  if (golose1 > golose2)
  {
    AdicionaVitoria(novo->equipa1, HTE);
  }
  else
  {
    
  }

  if (golose1 < golose2)
  {
    AdicionaVitoria(novo->equipa2, HTE);
  }
  else
  {
    
  }

  if (listajogos->ultimo)
  {
    listajogos->ultimo->proxjogo = novo;
  }
  else
  {
    listajogos->cabeca = novo;
  }

  listajogos->ultimo = novo;
  AdicionarHTJogos(HTJ, hashnome, novo);
  (*contacomandos)++;
}

void LibertaNomes(char *equipa1, char *equipa2)
{
  free(equipa1);
  free(equipa2);
}

void LibertaJogo(char *nomejogo, NoDuploJogos *jogo, HashNoJogos *aux)
{
  free(nomejogo);
  free(jogo);
  free(aux);
}

void TrocaPonteiros(HashNoJogos *auxprocura, ListaDuplaJogo *listajogos)
{
  if (auxprocura->dadosjogo->antjogo)
  {
    auxprocura->dadosjogo->antjogo->proxjogo = auxprocura->dadosjogo->proxjogo;
  }
  else
  {
    listajogos->cabeca = auxprocura->dadosjogo->proxjogo;
  }

  if (auxprocura->dadosjogo->proxjogo)
  {
    auxprocura->dadosjogo->proxjogo->antjogo = auxprocura->dadosjogo->antjogo;
  }
  else
  {
    listajogos->ultimo = auxprocura->dadosjogo->antjogo;
  }

}

void RemocaoJogo(HashNoJogos *auxprocura, HashNoJogos *auxcabeca, HashNoJogos *anterior, ListaDuplaJogo *listajogos, char *buffer, HashTableJogos *HTJ, int hashbuffer, int *contacomandos)
{
  TrocaPonteiros(auxprocura, listajogos);
  LibertaNomes(auxprocura->dadosjogo->equipa1, auxprocura->dadosjogo->equipa2);
  if (!strcmp(auxcabeca->dadosjogo->nomejogo, buffer))
  {
    HTJ->listasjog[hashbuffer] = auxcabeca->proxjogoh;
    LibertaJogo(auxprocura->dadosjogo->nomejogo, auxprocura->dadosjogo, auxcabeca);
  }
  else
  {
    for (; strcmp(auxcabeca->dadosjogo->nomejogo, buffer); auxcabeca = auxcabeca->proxjogoh)
    {
      anterior = auxcabeca;
    }

    anterior->proxjogoh = auxcabeca->proxjogoh;
    LibertaJogo(auxprocura->dadosjogo->nomejogo, auxprocura->dadosjogo, auxcabeca);
  }

  (*contacomandos)++;
}

void RemoverJogo(int *contacomandos, HashTableJogos *HTJ, ListaDuplaJogo *listajogos, HashTableEquipas *HTE)
{
  int hashbuffer;
  char buffer[1023 + 1];
  HashNoJogos *auxprocura;
  HashNoJogos *auxcabeca;
  HashNoJogos *anterior = 0;
  getchar();
  for (int buffer_index = 0; buffer_index < (1023 + 1); buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[(1023 + 1) - 1] = '\0';
  hashbuffer = Hash(buffer, HTJ->capacidade);
  if (!JogoJaAdicionado(HTJ, hashbuffer, buffer))
  {
    printf("%d Jogo inexistente.\n", *contacomandos);
    (*contacomandos)++;
    return;
  }
  else
  {
    
  }

  for (auxprocura = HTJ->listasjog[hashbuffer], auxcabeca = HTJ->listasjog[hashbuffer]; strcmp(auxprocura->dadosjogo->nomejogo, buffer); auxprocura = auxprocura->proxjogoh)
    ;

  if (auxprocura->dadosjogo->golos1 == auxprocura->dadosjogo->golos2)
  {
    RemocaoJogo(auxprocura, auxcabeca, anterior, listajogos, buffer, HTJ, hashbuffer, contacomandos);
  }
  else
  {
    if (auxprocura->dadosjogo->golos1 > auxprocura->dadosjogo->golos2)
    {
      RemoveVitoria(auxprocura->dadosjogo->equipa1, HTE);
      RemocaoJogo(auxprocura, auxcabeca, anterior, listajogos, buffer, HTJ, hashbuffer, contacomandos);
    }
    else
    {
      if (auxprocura->dadosjogo->golos1 < auxprocura->dadosjogo->golos2)
      {
        RemoveVitoria(auxprocura->dadosjogo->equipa2, HTE);
        RemocaoJogo(auxprocura, auxcabeca, anterior, listajogos, buffer, HTJ, hashbuffer, contacomandos);
      }
      else
      {
        
      }

    }

  }

}

void ProcuraJogo(int *contacomandos, HashTableJogos *HTJ)
{
  int hashbuffer;
  char buffer[1023 + 1];
  HashNoJogos *auxprocura;
  getchar();
  for (int buffer_index = 0; buffer_index < (1023 + 1); buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[(1023 + 1) - 1] = '\0';
  hashbuffer = Hash(buffer, HTJ->capacidade);
  for (auxprocura = HTJ->listasjog[hashbuffer]; auxprocura; auxprocura = auxprocura->proxjogoh)
  {
    if (!strcmp(auxprocura->dadosjogo->nomejogo, buffer))
    {
      printf("%d %s %s %s %d %d\n", *contacomandos, buffer, auxprocura->dadosjogo->equipa1, auxprocura->dadosjogo->equipa2, auxprocura->dadosjogo->golos1, auxprocura->dadosjogo->golos2);
      (*contacomandos)++;
      return;
    }
    else
    {
      
    }

  }

  printf("%d Jogo inexistente.\n", *contacomandos);
  (*contacomandos)++;
}

void TrocaVitorias(HashTableEquipas *HTE, char *equipa1, char *equipa2)
{
  RemoveVitoria(equipa1, HTE);
  AdicionaVitoria(equipa2, HTE);
}

void AlteraPontuacao(int *contacomandos, HashTableEquipas *HTE, HashTableJogos *HTJ)
{
  int hashbuffer;
  int novosgolos1;
  int novosgolos2;
  char buffer[1023 + 1];
  HashNoJogos *auxprocura;
  getchar();
  for (int buffer_index = 0; buffer_index < (1023 + 1); buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[(1023 + 1) - 1] = '\0';
  novosgolos1 = new_sym_var(sizeof(int) * 8);
  novosgolos2 = new_sym_var(sizeof(int) * 8);
  hashbuffer = Hash(buffer, HTJ->capacidade);
  if (!JogoJaAdicionado(HTJ, hashbuffer, buffer))
  {
    printf("%d Jogo inexistente.\n", *contacomandos);
    (*contacomandos)++;
    return;
  }
  else
  {
    
  }

  for (auxprocura = HTJ->listasjog[hashbuffer]; strcmp(auxprocura->dadosjogo->nomejogo, buffer); auxprocura = auxprocura->proxjogoh)
    ;

  if (novosgolos1 == novosgolos2)
  {
    if (auxprocura->dadosjogo->golos1 > auxprocura->dadosjogo->golos2)
    {
      RemoveVitoria(auxprocura->dadosjogo->equipa1, HTE);
    }
    else
    {
      if (auxprocura->dadosjogo->golos1 < auxprocura->dadosjogo->golos2)
      {
        RemoveVitoria(auxprocura->dadosjogo->equipa2, HTE);
      }
      else
      {
        
      }

    }

  }
  else
  {
    if (novosgolos1 > novosgolos2)
    {
      if (auxprocura->dadosjogo->golos1 < auxprocura->dadosjogo->golos2)
      {
        TrocaVitorias(HTE, auxprocura->dadosjogo->equipa2, auxprocura->dadosjogo->equipa1);
      }
      else
      {
        if (auxprocura->dadosjogo->golos1 == auxprocura->dadosjogo->golos2)
        {
          AdicionaVitoria(auxprocura->dadosjogo->equipa1, HTE);
        }
        else
        {
          
        }

      }

    }
    else
    {
      if (novosgolos1 < novosgolos2)
      {
        if (auxprocura->dadosjogo->golos1 == auxprocura->dadosjogo->golos2)
        {
          AdicionaVitoria(auxprocura->dadosjogo->equipa2, HTE);
        }
        else
        {
          if (auxprocura->dadosjogo->golos1 > auxprocura->dadosjogo->golos2)
          {
            TrocaVitorias(HTE, auxprocura->dadosjogo->equipa1, auxprocura->dadosjogo->equipa2);
          }
          else
          {
            
          }

        }

      }
      else
      {
        
      }

    }

  }

  AlteraGolos(auxprocura, novosgolos1, novosgolos2);
  (*contacomandos)++;
}

void ListarJogos(int *contacomandos, ListaDuplaJogo *jogos)
{
  NoDuploJogos *aux = jogos->cabeca;
  for (; aux; aux = aux->proxjogo)
  {
    printf("%d %s %s %s %d %d\n", *contacomandos, aux->nomejogo, aux->equipa1, aux->equipa2, aux->golos1, aux->golos2);
  }

  (*contacomandos)++;
}

void ApagarJogos(ListaDuplaJogo *jogos)
{
  NoDuploJogos *aux;
  while (jogos->cabeca)
  {
    aux = jogos->cabeca;
    jogos->cabeca = jogos->cabeca->proxjogo;
    free(aux->equipa1);
    free(aux->equipa2);
    free(aux->nomejogo);
    free(aux);
  }

  free(jogos);
}
