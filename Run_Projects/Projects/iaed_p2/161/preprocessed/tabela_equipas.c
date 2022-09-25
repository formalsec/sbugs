/*File generated by PreProcessor.py*/


#include "tabela_equipas.h"


pTabela_equipas inicializa_tabela_equipas(unsigned int max)
{
  unsigned int i;
  pTabela_equipas tabela = (pTabela_equipas) malloc(sizeof(struct tabela_equipas));
  tabela->num_equipas = 0;
  tabela->tamanho = max;
  tabela->equipas = (pEquipa *) malloc(max * (sizeof(pEquipa)));
  for (i = 0; i < tabela->tamanho; i++)
    tabela->equipas[i] = 0;

  return tabela;
}

void expande_tabela_equipas(pTabela_equipas tabela)
{
  unsigned int i;
  pTabela_equipas tabela_aux;
  tabela_aux = inicializa_tabela_equipas(tabela->tamanho * 2);
  for (i = 0; i < tabela->tamanho; i++)
    if (tabela->equipas[i] != 0)
  {
    adiciona_equipa_tabela(tabela_aux, tabela->equipas[i]);
  }
  else
  {
    
  }


  free(tabela->equipas);
  tabela->equipas = tabela_aux->equipas;
  tabela->tamanho = tabela_aux->tamanho;
  free(tabela_aux);
  return;
}

void adiciona_equipa_tabela(pTabela_equipas tabela, pEquipa equipa)
{
  unsigned int i = gera_hash(obtem_nome_equipa(equipa), tabela->tamanho);
  while (tabela->equipas[i] != 0)
    i = (i + 1) % tabela->tamanho;

  tabela->equipas[i] = equipa;
  if ((tabela->num_equipas++) > (tabela->tamanho / 2))
  {
    expande_tabela_equipas(tabela);
  }
  else
  {
    
  }

  return;
}

pEquipa procura_equipa_tabela(pTabela_equipas tabela, char *nome_equipa)
{
  int i = gera_hash(nome_equipa, tabela->tamanho);
  while (tabela->equipas[i] != 0)
    if (strcmp(obtem_nome_equipa(tabela->equipas[i]), nome_equipa) == 0)
  {
    return tabela->equipas[i];
  }
  else
  {
    i = (i + 1) % tabela->tamanho;
  }


  return 0;
}

void print_vetor_equipas(char **vetor_equipas, unsigned int tamanho, unsigned int Num_Linha)
{
  unsigned int i;
  for (i = 0; i < tamanho; i++)
    printf("%u * %s\n", Num_Linha, vetor_equipas[i]);

  return;
}

int comparador(const void *equipa1, const void *equipa2)
{
  return strcmp(*((char **) equipa1), *((char **) equipa2));
}

void print_melhores_equipas(pTabela_equipas tabela, unsigned int Num_Linha)
{
  unsigned int i;
  unsigned int j;
  unsigned int num_equipas_percorridas;
  unsigned int vitorias_equipa;
  unsigned int maximo_vitorias;
  char **melhores_equipas_buffer;
  char **melhores_equipas;
  if (tabela->num_equipas == 0)
  {
    return;
  }
  else
  {
    
  }

  melhores_equipas_buffer = (char **) malloc((sizeof(char *)) * tabela->num_equipas);
  num_equipas_percorridas = 0;
  maximo_vitorias = 0;
  for (i = 0, j = 0; num_equipas_percorridas < tabela->num_equipas; i++)
  {
    if (tabela->equipas[i] != 0)
    {
      num_equipas_percorridas++;
      if ((vitorias_equipa = obtem_vitorias_equipa(tabela->equipas[i])) > maximo_vitorias)
      {
        maximo_vitorias = vitorias_equipa;
        j = 0;
        melhores_equipas_buffer[j++] = obtem_nome_equipa(tabela->equipas[i]);
      }
      else
      {
        if (vitorias_equipa == maximo_vitorias)
        {
          melhores_equipas_buffer[j++] = obtem_nome_equipa(tabela->equipas[i]);
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

  if (j == tabela->num_equipas)
  {
    melhores_equipas = melhores_equipas_buffer;
  }
  else
  {
    melhores_equipas = (char **) malloc((sizeof(char *)) * j);
    for (i = 0; i < j; i++)
      melhores_equipas[i] = melhores_equipas_buffer[i];

    free(melhores_equipas_buffer);
  }

  qsort(melhores_equipas, (int) j, sizeof(char *), comparador);
  printf("%u Melhores %u\n", Num_Linha, maximo_vitorias);
  print_vetor_equipas(melhores_equipas, j, Num_Linha);
  free(melhores_equipas);
  return;
}

void destroi_tabela_equipas(pTabela_equipas tabela)
{
  unsigned int i;
  for (i = 0; i < tabela->tamanho; i++)
    if (tabela->equipas[i] != 0)
  {
    free_equipa(tabela->equipas[i]);
  }
  else
  {
    
  }


  free(tabela->equipas);
  free(tabela);
  return;
}

