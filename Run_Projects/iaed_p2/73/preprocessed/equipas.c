/*File generated by PreProcessor.py*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "equipas.h"


int hash_function_equipas(char *string, int tamanho_max)
{
  int hash;
  int a = 31415;
  int b = 27183;
  for (hash = 0; (*string) != '\0'; string++, a = (a * b) % (tamanho_max - 1))
    hash = ((a * hash) + (*string)) % tamanho_max;

  return hash;
}

int qsort_funcao_comparacao(const void *a, const void *b)
{
  link_equipa **equipaA = (link_equipa **) a;
  link_equipa **equipaB = (link_equipa **) b;
  return strcmp((*equipaA)->nome_equipa, (*equipaB)->nome_equipa);
}

hashtable_equipas *inicializa_equipas(int tamanho_maximo)
{
  int i;
  hashtable_equipas *tabela_equipas;
  tabela_equipas = (hashtable_equipas *) malloc(sizeof(hashtable_equipas));
  tabela_equipas->tamanho_maximo = tamanho_maximo;
  tabela_equipas->vetor_hashes = (link_hashtable_equipas *) malloc(tamanho_maximo * (sizeof(link_hashtable_equipas)));
  for (i = 0; i < tamanho_maximo; i++)
    tabela_equipas->vetor_hashes[i].next = 0;

  return tabela_equipas;
}

void adicionar_equipa(char *nome_equipa, hashtable_equipas *equipas)
{
  int hash;
  link_equipa *nova_equipa;
  link_equipa *equipa_seguinte;
  nova_equipa = (link_equipa *) malloc(sizeof(link_equipa));
  nova_equipa->numero_vitorias = 0;
  nova_equipa->nome_equipa = (char *) malloc((strlen(nome_equipa) + 1) * (sizeof(char)));
  strcpy(nova_equipa->nome_equipa, nome_equipa);
  nova_equipa->next = 0;
  hash = hash_function_equipas(nome_equipa, equipas->tamanho_maximo);
  if (equipas->vetor_hashes[hash].next == 0)
  {
    equipas->vetor_hashes[hash].next = nova_equipa;
  }
  else
  {
    {
      equipa_seguinte = equipas->vetor_hashes[hash].next;
      equipas->vetor_hashes[hash].next = nova_equipa;
      nova_equipa->next = equipa_seguinte;
    }
  }

}

link_equipa *procurar_equipa(char *nome_equipa, hashtable_equipas *equipas)
{
  int hash;
  link_equipa *link_atual;
  hash = hash_function_equipas(nome_equipa, equipas->tamanho_maximo);
  if (equipas->vetor_hashes[hash].next == 0)
  {
    return 0;
  }
  else
  {
    {
      link_atual = equipas->vetor_hashes[hash].next;
      while (link_atual != 0)
      {
        if (!strcmp(link_atual->nome_equipa, nome_equipa))
        {
          return link_atual;
        }
        else
        {
          link_atual = link_atual->next;
        }

      }

      return 0;
    }
  }

}

void listar_melhores_equipas(hashtable_equipas *equipas, int linha_input)
{
  int hash;
  int maior_nmr_vitorias = 0;
  int numero_equipas = 0;
  int indice = 0;
  link_equipa *equipa_atual;
  link_equipa **array_equipas_vitoriosas;
  for (hash = 0; hash < equipas->tamanho_maximo; hash++)
  {
    equipa_atual = equipas->vetor_hashes[hash].next;
    while (equipa_atual != 0)
    {
      if (equipa_atual->numero_vitorias == maior_nmr_vitorias)
      {
        numero_equipas++;
      }
      else
      {
        if (equipa_atual->numero_vitorias > maior_nmr_vitorias)
        {
          {
            maior_nmr_vitorias = equipa_atual->numero_vitorias;
            numero_equipas = 1;
          }
        }
        else
        {
          
        }

      }

      equipa_atual = equipa_atual->next;
    }

  }

  array_equipas_vitoriosas = (link_equipa **) malloc(numero_equipas * (sizeof(link_equipa *)));
  while (indice < numero_equipas)
  {
    for (hash = 0; hash < equipas->tamanho_maximo; hash++)
    {
      equipa_atual = equipas->vetor_hashes[hash].next;
      while (equipa_atual != 0)
      {
        if (equipa_atual->numero_vitorias == maior_nmr_vitorias)
        {
          {
            array_equipas_vitoriosas[indice] = equipa_atual;
            indice++;
          }
        }
        else
        {
          
        }

        equipa_atual = equipa_atual->next;
      }

    }

  }

  qsort(array_equipas_vitoriosas, numero_equipas, sizeof(link_equipa *), qsort_funcao_comparacao);
  printf("%d Melhores %d\n", linha_input, maior_nmr_vitorias);
  for (indice = 0; indice < numero_equipas; indice++)
    printf("%d * %s\n", linha_input, array_equipas_vitoriosas[indice]->nome_equipa);

  free(array_equipas_vitoriosas);
}

void destruir_equipas(hashtable_equipas *equipas)
{
  int hash;
  link_equipa *head;
  link_equipa *temp;
  for (hash = 0; hash < equipas->tamanho_maximo; hash++)
  {
    head = equipas->vetor_hashes[hash].next;
    while (head != 0)
    {
      temp = head->next;
      free(head->nome_equipa);
      free(head);
      head = temp;
    }

  }

  free(equipas->vetor_hashes);
  free(equipas);
}

