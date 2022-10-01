/*File generated by PreProcessor.py*/


#include "equipas.h"


pt_equipa nova_equipa(char *nome)
{
  pt_equipa equipa_nova;
  int comp = strlen(nome) + 1;
  equipa_nova = (pt_equipa) malloc(sizeof(struct equipa));
  equipa_nova->nome = (char *) malloc(comp * (sizeof(char)));
  strcpy(equipa_nova->nome, nome);
  equipa_nova->vitorias = 0;
  return equipa_nova;
}

pt_equipa procura_equipa(char *nome, link_equipa *equipas)
{
  int indice = hash_equipa(nome);
  link_equipa tmp;
  tmp = equipas[indice];
  while ((tmp != 0) && (strcmp(tmp->equipa->nome, nome) != 0))
    tmp = tmp->next;

  if (tmp == 0)
  {
    return 0;
  }
  else
  {
    return tmp->equipa;
  }

}

bool equipa_existe(char *nome, link_equipa *equipas)
{
  return procura_equipa(nome, equipas) != 0;
}

void free_equipa(pt_equipa equipa)
{
  free(equipa->nome);
  free(equipa);
}

link_equipa *init_equipas(link_equipa *tabela)
{
  int i;
  for (i = 0; i < (1009 / 2); i++)
    tabela[i] = 0;

  return tabela;
}

void insere_equipa_tabela(pt_equipa equipa, link_equipa *equipas)
{
  int indice = hash_equipa(equipa->nome);
  link_equipa new = (link_equipa) malloc(sizeof(struct node_equipa));
  new->equipa = equipa;
  new->next = equipas[indice];
  equipas[indice] = new;
}

int compara(const void *a, const void *b)
{
  return strcmp((const char *) a, (const char *) b);
}

int max_vitorias(link_equipa *equipas)
{
  int i;
  int max = 0;
  link_equipa aux;
  for (i = 0; i < (1009 / 2); i++)
  {
    aux = equipas[i];
    while (aux != 0)
    {
      if (aux->equipa->vitorias > max)
      {
        max = aux->equipa->vitorias;
      }
      else
      {
        
      }

      aux = aux->next;
    }

  }

  return max;
}
