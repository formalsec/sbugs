/*File generated by PreProcessor.py*/


#include "header.h"


void cmd_A()
{
  Equipa *t;
  Equipa *temp;
  EquipasOrd *aux;
  EquipasOrd *temp1;
  char aux_ler[1025];
  int indice_equipa;
  for (int aux_ler_index = 0; aux_ler_index < 10; aux_ler_index++)
  {
    aux_ler[aux_ler_index] = new_sym_var(sizeof(char) * 8);
  }

  aux_ler[10 - 1] = '\0';
  t = malloc(sizeof(Equipa));
  aux = malloc(sizeof(EquipasOrd));
  t->nome_equipa = malloc((sizeof(char)) * (strlen(aux_ler) + 1));
  strcpy(t->nome_equipa, aux_ler);
  t->vitorias = 0;
  t->next = 0;
  if (!equipa_nao_existe(t->nome_equipa))
  {
    {
      free(t->nome_equipa);
      free(t);
      free(aux);
      printf("%d Equipa existente.\n", nl);
      return;
    }
  }
  else
  {
    
  }

  indice_equipa = hash(t->nome_equipa);
  if (HashTeams[indice_equipa] != 0)
  {
    {
      temp = HashTeams[indice_equipa];
      while (temp->next != 0)
      {
        temp = temp->next;
      }

      temp->next = t;
    }
  }
  else
  {
    HashTeams[indice_equipa] = t;
  }

  if (headteam == 0)
  {
    {
      aux->team = t;
      aux->next = 0;
      headteam = aux;
    }
  }
  else
  {
    {
      temp1 = headteam;
      while (temp1->next != 0)
        temp1 = temp1->next;

      aux->team = t;
      aux->next = 0;
      temp1->next = aux;
    }
  }

}

