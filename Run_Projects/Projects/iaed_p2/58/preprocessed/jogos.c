/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"
#include "LISTAS.h"
#include "HASHTABLES.h"


link_jogo AdicionaJogo(link_equipa *tab_equipas, pJogo *tab_dispersao, link_jogo Jogos_head, int NL, unsigned int M, unsigned int *NJ)
{
  char nome[1024];
  char equipa1[1024];
  char equipa2[1024];
  int score1;
  int score2;
  link_equipa equipa1_ptr = 0;
  link_equipa equipa2_ptr = 0;
  pJogo jogo_ptr = 0;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
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
  if (procura_tab_dispersao(tab_dispersao, nome, M) != 0)
  {
    printf("%d Jogo existente.\n", NL);
    return Jogos_head;
  }
  else
  {
    
  }

  equipa1_ptr = procura_equipa_lista(tab_equipas, equipa1);
  equipa2_ptr = procura_equipa_lista(tab_equipas, equipa2);
  if ((equipa1_ptr == 0) || (equipa2_ptr == 0))
  {
    printf("%d Equipa inexistente.\n", NL);
    return Jogos_head;
  }
  else
  {
    
  }

  if (score1 > score2)
  {
    equipa1_ptr->vitorias++;
  }
  else
  {
    if (score2 > score1)
    {
      equipa2_ptr->vitorias++;
    }
    else
    {
      
    }

  }

  jogo_ptr = tab_dispersao_insere(tab_dispersao, nome, equipa1_ptr->equipa, equipa2_ptr->equipa, score1, score2, M);
  *NJ = (*NJ) + 1;
  return insere_jogo_lista(Jogos_head, jogo_ptr);
}

void AdicionaEquipa(link_equipa *tab_equipas, int NL)
{
  char equipa[1024];
  for (int equipa_index = 0; equipa_index < 10; equipa_index++)
  {
    equipa[equipa_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa[10 - 1] = '\0';
  if (procura_equipa_lista(tab_equipas, equipa) != 0)
  {
    printf("%d Equipa existente.\n", NL);
    return;
  }
  else
  {
    
  }

  insere_equipa_lista(tab_equipas, equipa);
  return;
}

link_jogo ApagaJogo(link_equipa *tab_equipas, pJogo *tab_dispersao, link_jogo Jogos_head, unsigned int M, int NL, unsigned int *NJ)
{
  char nome[1024];
  pJogo jogo_ptr = 0;
  link_equipa equipa1_ptr = 0;
  link_equipa equipa2_ptr = 0;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  jogo_ptr = procura_tab_dispersao(tab_dispersao, nome, M);
  if (jogo_ptr == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return Jogos_head;
  }
  else
  {
    
  }

  equipa1_ptr = procura_equipa_lista(tab_equipas, jogo_ptr->equipa1);
  equipa2_ptr = procura_equipa_lista(tab_equipas, jogo_ptr->equipa2);
  if (jogo_ptr->score1 > jogo_ptr->score2)
  {
    equipa1_ptr->vitorias--;
  }
  else
  {
    if (jogo_ptr->score1 < jogo_ptr->score2)
    {
      equipa2_ptr->vitorias--;
    }
    else
    {
      
    }

  }

  Jogos_head = apaga_jogo_lista(Jogos_head, nome);
  apaga_tab_dispersao(tab_dispersao, nome, M);
  *NJ = (*NJ) - 1;
  return Jogos_head;
}

void ListaJogos(link_jogo head, int NL)
{
  if (head == 0)
  {
    return;
  }
  else
  {
    
  }

  ListaJogos(head->next, NL);
  printf("%d %s %s %s %d %d\n", NL, head->jogo->nome, head->jogo->equipa1, head->jogo->equipa2, head->jogo->score1, head->jogo->score2);
  return;
}

void ProcuraEquipa(link_equipa *tab_equipas, int NL)
{
  char equipa[1024];
  link_equipa equipa_ptr = 0;
  for (int equipa_index = 0; equipa_index < 10; equipa_index++)
  {
    equipa[equipa_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa[10 - 1] = '\0';
  equipa_ptr = procura_equipa_lista(tab_equipas, equipa);
  if (equipa_ptr == 0)
  {
    printf("%d Equipa inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  printf("%d %s %d\n", NL, equipa_ptr->equipa, equipa_ptr->vitorias);
  return;
}

void ProcuraJogo(pJogo *tab_dispersao, int NL, unsigned int M)
{
  char nome[1024];
  pJogo jogo_ptr = 0;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  jogo_ptr = procura_tab_dispersao(tab_dispersao, nome, M);
  if (jogo_ptr != 0)
  {
    printf("%d %s %s %s %d %d\n", NL, jogo_ptr->nome, jogo_ptr->equipa1, jogo_ptr->equipa2, jogo_ptr->score1, jogo_ptr->score2);
    return;
  }
  else
  {
    
  }

  printf("%d Jogo inexistente.\n", NL);
  return;
}

void AlteraPontuacao(link_equipa *tab_equipas, pJogo *tab_dispersao, int NL, unsigned int M)
{
  char nome[1024];
  int score1_new;
  int score2_new;
  pJogo jogo_ptr = 0;
  link_equipa equipa1_ptr = 0;
  link_equipa equipa2_ptr = 0;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score1_new = new_sym_var(sizeof(int) * 8);
  score2_new = new_sym_var(sizeof(int) * 8);
  jogo_ptr = procura_tab_dispersao(tab_dispersao, nome, M);
  if (jogo_ptr == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  equipa1_ptr = procura_equipa_lista(tab_equipas, jogo_ptr->equipa1);
  equipa2_ptr = procura_equipa_lista(tab_equipas, jogo_ptr->equipa2);
  if ((jogo_ptr->score1 > jogo_ptr->score2) && (score1_new < score2_new))
  {
    equipa1_ptr->vitorias--;
    equipa2_ptr->vitorias++;
  }
  else
  {
    
  }

  if ((jogo_ptr->score1 < jogo_ptr->score2) && (score1_new > score2_new))
  {
    equipa1_ptr->vitorias++;
    equipa2_ptr->vitorias--;
  }
  else
  {
    
  }

  if ((jogo_ptr->score1 < jogo_ptr->score2) && (score1_new == score2_new))
  {
    equipa2_ptr->vitorias--;
  }
  else
  {
    
  }

  if ((jogo_ptr->score1 > jogo_ptr->score2) && (score1_new == score2_new))
  {
    equipa1_ptr->vitorias--;
  }
  else
  {
    
  }

  if ((jogo_ptr->score1 == jogo_ptr->score2) && (score1_new < score2_new))
  {
    equipa2_ptr->vitorias++;
  }
  else
  {
    
  }

  if ((jogo_ptr->score1 == jogo_ptr->score2) && (score1_new > score2_new))
  {
    equipa1_ptr->vitorias++;
  }
  else
  {
    
  }

  jogo_ptr->score1 = score1_new;
  jogo_ptr->score2 = score2_new;
  return;
}

int compara(const void *c_equipa1, const void *c_equipa2)
{
  char **equipa1 = (char **) c_equipa1;
  char **equipa2 = (char **) c_equipa2;
  return strcmp(*equipa1, *equipa2);
}

void EquipasVencedoras(link_equipa *tab_equipas, int NL)
{
  link_equipa x;
  link_equipa aux = 0;
  int max = 0;
  int tamanho_vetor = 0;
  int i = 0;
  int j;
  int p = 0;
  char **equipas_vencedoras;
  for (j = 0; j < 512; j++)
  {
    x = tab_equipas[j];
    if (x != 0)
    {
      p = 1;
      for (aux = x; aux != 0; aux = aux->next)
      {
        if (aux->vitorias > max)
        {
          max = aux->vitorias;
          tamanho_vetor = 1;
        }
        else
        {
          if (aux->vitorias == max)
          {
            tamanho_vetor++;
          }
          else
          {
            
          }

        }

      }

    }
    else
    {
      
    }

  }

  if (p == 0)
  {
    return;
  }
  else
  {
    
  }

  equipas_vencedoras = malloc(tamanho_vetor * (sizeof(char *)));
  for (j = 0; j < 256; j++)
  {
    for (aux = tab_equipas[j]; aux != 0; aux = aux->next)
    {
      if (aux->vitorias == max)
      {
        equipas_vencedoras[i] = (char *) malloc((sizeof(char)) * (strlen(aux->equipa) + 1));
        strcpy(equipas_vencedoras[i++], aux->equipa);
      }
      else
      {
        
      }

    }

  }

  qsort(equipas_vencedoras, tamanho_vetor, sizeof(char *), compara);
  printf("%d Melhores %d\n", NL, max);
  for (i = 0; i < tamanho_vetor; i++)
  {
    if (equipas_vencedoras[i] != 0)
    {
      printf("%d * %s\n", NL, equipas_vencedoras[i]);
    }
    else
    {
      
    }

  }

  for (i = 0; i < tamanho_vetor; i++)
    free(equipas_vencedoras[i]);

  free(equipas_vencedoras);
}

