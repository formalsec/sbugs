/*File generated by PreProcessor.py*/


#include "listaJogos.h"


listaJogo novoJogoLista(pJogo novoJogo, int ordem)
{
  listaJogo novoNO = (listaJogo) malloc(sizeof(struct noJogo));
  novoNO->ptJogo = novoJogo;
  adicionaVitoria(novoJogo);
  novoNO->ordem = ordem;
  novoNO->proximo = 0;
  return novoNO;
}

listaJogo adicionarNovoJogo(pJogo novoJogo, listaJogo *listaJogos, int ordem, int numINP)
{
  listaJogo no;
  listaJogo noAnt;
  if ((*listaJogos) == 0)
  {
    {
      return novoJogoLista(novoJogo, ordem);
    }
  }
  else
  {
    
  }

  for (no = *listaJogos, noAnt = 0; no != 0; noAnt = no, no = no->proximo)
  {
    if (strcmp(no->ptJogo->nome, novoJogo->nome) == 0)
    {
      {
        printf("%d Jogo existente.\n", numINP);
        return *listaJogos;
      }
    }
    else
    {
      
    }

  }

  noAnt->proximo = novoJogoLista(novoJogo, ordem);
  return *listaJogos;
}

pJogo procurarJogoLista(listaJogo *listaJogos, char *nome)
{
  listaJogo no = *listaJogos;
  for (; no != 0; no = no->proximo)
  {
    if (strcmp(no->ptJogo->nome, nome) == 0)
    {
      {
        return no->ptJogo;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

void apagarJogoLista(listaJogo *listaJogos, char *nome, int numINP)
{
  listaJogo no;
  listaJogo noAnt;
  if ((*listaJogos) == 0)
  {
    {
      printf("%d Jogo inexistente.\n", numINP);
      return;
    }
  }
  else
  {
    {
      for (no = *listaJogos, noAnt = 0; no != 0; noAnt = no, no = no->proximo)
      {
        if (strcmp(no->ptJogo->nome, nome) == 0)
        {
          {
            if (noAnt == 0)
            {
              {
                *listaJogos = no->proximo;
                retiraVitoria(no->ptJogo);
                libertarJogo(no->ptJogo);
                free(no);
                return;
              }
            }
            else
            {
              
            }

            noAnt->proximo = no->proximo;
            retiraVitoria(no->ptJogo);
            libertarJogo(no->ptJogo);
            free(no);
            return;
          }
        }
        else
        {
          
        }

      }

      printf("%d Jogo inexistente.\n", numINP);
    }
  }

}

void libertarListaJogos(listaJogo *listaJogos)
{
  listaJogo no;
  listaJogo temp;
  no = *listaJogos;
  while (no != 0)
  {
    temp = no->proximo;
    libertarJogo(no->ptJogo);
    no = temp;
  }

  free(*listaJogos);
}

