#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "estruturas_equipa.h"


Equipas init_equipas()
{
  return calloc(1, sizeof(struct equipas));
}

void insere_equipa(Equipas equipas, Equipa equipa)
{
  int ind;
  ind = hash(equipa->nome, 5059);
  equipas->ht[ind] = push_equipa(equipas->ht[ind], equipa);
  if (equipas->primeiro == 0)
  {
    equipas->primeiro = equipas->ht[ind];
  }
  else
  {
    equipas->ultimo->prox_inserido = equipas->ht[ind];
  }

  equipas->ht[ind]->prox_inserido = 0;
  equipas->ultimo = equipas->ht[ind];
}

No_Equipa push_equipa(No_Equipa atual, Equipa equipa)
{
  No_Equipa novo;
  novo = malloc(sizeof(struct no_equipa));
  novo->equipa = equipa;
  novo->prox = atual;
  return novo;
}

Equipa procura_equipa(Equipas equipas, char *nome)
{
  int ind;
  ind = hash(nome, 5059);
  return procura_ht_equipas(equipas->ht[ind], nome);
}

Equipa procura_ht_equipas(No_Equipa no, char *nome)
{
  while (no != 0)
  {
    if (!strcmp(nome, no->equipa->nome))
    {
      return no->equipa;
    }
    else
    {
      
    }

    no = no->prox;
  }

  return 0;
}

void destroi_equipas(Equipas equipas)
{
  No_Equipa temp;
  while (equipas->primeiro != 0)
  {
    temp = equipas->primeiro->prox_inserido;
    free_equipa(equipas->primeiro->equipa);
    free(equipas->primeiro);
    equipas->primeiro = temp;
  }

  free(equipas);
}

void print_vencedores(Equipas equipas, unsigned int NL)
{
  No_Equipa no;
  char **vencedores;
  char **tmp;
  int i;
  int max = 0;
  int size_max = 1;
  int size = 0;
  if (equipas->primeiro == 0)
  {
    return;
  }
  else
  {
    
  }

  no = equipas->primeiro;
  vencedores = malloc(size_max * (sizeof(char *)));
  while (no != 0)
  {
    if (no->equipa->vitorias > max)
    {
      max = no->equipa->vitorias;
      size = 0;
      vencedores[size++] = no->equipa->nome;
    }
    else
    {
      if (no->equipa->vitorias == max)
      {
        vencedores[size++] = no->equipa->nome;
      }
      else
      {
        
      }

    }

    if (size >= size_max)
    {
      size_max++;
      tmp = realloc(vencedores, size_max * (sizeof(char *)));
      if (tmp == 0)
      {
        return;
      }
      else
      {
        vencedores = tmp;
      }

    }
    else
    {
      
    }

    no = no->prox_inserido;
  }

  qsort(vencedores, size, sizeof(char *), compara_strings);
  printf("%u Melhores %d\n", NL, max);
  for (i = 0; i < size; i++)
    printf("%u * %s\n", NL, vencedores[i]);

  free(vencedores);
}
