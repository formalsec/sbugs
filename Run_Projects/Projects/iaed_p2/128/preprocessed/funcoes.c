/*File generated by PreProcessor.py*/


#include "funcoes.h"


void adiciona_equipa(link *heads, int n_linha)
{
  char buffer[1024];
  char *nome;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  nome = (char *) malloc((sizeof(char)) * (strlen(buffer) + 1));
  strcpy(nome, buffer);
  if (existe_el(heads, nome) == 1)
  {
    printf("%d Equipa existente.\n", n_linha);
  }
  else
  {
    insere_na_lista(heads, nome);
  }

  free(nome);
}

void devolve_equipa(link *heads, int n_linha)
{
  char buffer[1024];
  Equipa *equipa;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  equipa = procura_equipa(heads, buffer);
  if (equipa != 0)
  {
    printf("%d %s %d\n", n_linha, equipa->nome, equipa->jogos_ganhos);
  }
  else
  {
    printf("%d Equipa inexistente.\n", n_linha);
  }

}

void adiciona_jogo(limites_lista *lista, link_jogo *heads_jogos, link *heads, int n_linha)
{
  int score1;
  int score2;
  char buffer[1024];
  char *nome;
  char *equipa1;
  char *equipa2;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  nome = (char *) malloc((sizeof(char)) * (strlen(buffer) + 1));
  strcpy(nome, buffer);
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  equipa1 = (char *) malloc((sizeof(char)) * (strlen(buffer) + 1));
  strcpy(equipa1, buffer);
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  equipa2 = (char *) malloc((sizeof(char)) * (strlen(buffer) + 1));
  strcpy(equipa2, buffer);
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (existe_jogo(heads_jogos, nome) == 1)
  {
    printf("%d Jogo existente.\n", n_linha);
  }
  else
  {
    if ((existe_el(heads, equipa1) == 0) || (existe_el(heads, equipa2) == 0))
    {
      printf("%d Equipa inexistente.\n", n_linha);
    }
    else
    {
      insere_jogo_hash(lista, heads, heads_jogos, nome, equipa1, equipa2, score1, score2);
    }

  }

  free(nome);
  free(equipa1);
  free(equipa2);
}

void print_jogos(limites_lista *lista, int n_linha)
{
  link_lista aux;
  for (aux = lista->head; aux != 0; aux = aux->next)
    printf("%d %s %s %s %d %d\n", n_linha, aux->jogo->nome, aux->jogo->equipa1->nome, aux->jogo->equipa2->nome, aux->jogo->score1, aux->jogo->score2);

}

void devolve_jogo(link_jogo *heads_jogos, int n_linha)
{
  char buffer[1024];
  Jogo *jogo;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  jogo = procura_jogo(heads_jogos, buffer);
  if (jogo != 0)
  {
    printf("%d %s %s %s %d %d\n", n_linha, jogo->nome, jogo->equipa1->nome, jogo->equipa2->nome, jogo->score1, jogo->score2);
  }
  else
  {
    printf("%d Jogo inexistente.\n", n_linha);
  }

}

void altera_score(link_jogo *heads_jogos, int n_linha)
{
  int score1;
  int score2;
  int empate = 0;
  int derrota = 0;
  int vitoria = 0;
  char buffer[1024];
  Jogo *jogo;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (existe_jogo(heads_jogos, buffer) == 1)
  {
    jogo = procura_jogo(heads_jogos, buffer);
    if (jogo->score1 == jogo->score2)
    {
      empate = 1;
    }
    else
    {
      if (jogo->score1 > jogo->score2)
      {
        vitoria = 1;
      }
      else
      {
        derrota = 1;
      }

    }

    jogo->score1 = score1;
    jogo->score2 = score2;
    if (score1 > score2)
    {
      if (empate == 1)
      {
        jogo->equipa1->jogos_ganhos += 1;
      }
      else
      {
        if (derrota == 1)
        {
          jogo->equipa1->jogos_ganhos += 1;
          jogo->equipa2->jogos_ganhos -= 1;
        }
        else
        {
          
        }

      }

    }
    else
    {
      if (score2 > score1)
      {
        if (empate == 1)
        {
          jogo->equipa2->jogos_ganhos += 1;
        }
        else
        {
          if (vitoria == 1)
          {
            jogo->equipa2->jogos_ganhos += 1;
            jogo->equipa1->jogos_ganhos -= 1;
          }
          else
          {
            
          }

        }

      }
      else
      {
        if (vitoria == 1)
        {
          jogo->equipa1->jogos_ganhos -= 1;
        }
        else
        {
          if (derrota == 1)
          {
            jogo->equipa2->jogos_ganhos -= 1;
          }
          else
          {
            
          }

        }

      }

    }

  }
  else
  {
    printf("%d Jogo inexistente.\n", n_linha);
  }

}

void apaga_jogo(link_jogo *head_jogos, limites_lista *lista, int n_linha)
{
  char buffer[1024];
  char *nome;
  Jogo *jogo;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  nome = (char *) malloc((sizeof(char)) * (strlen(buffer) + 1));
  strcpy(nome, buffer);
  if (existe_jogo(head_jogos, nome) == 1)
  {
    jogo = procura_jogo(head_jogos, nome);
    apaga_jogo_hash(head_jogos, nome);
    apaga_jogo_lista(lista, nome);
    if (jogo->score1 > jogo->score2)
    {
      jogo->equipa1->jogos_ganhos -= 1;
    }
    else
    {
      if (jogo->score2 > jogo->score1)
      {
        jogo->equipa2->jogos_ganhos -= 1;
      }
      else
      {
        
      }

    }

    free(jogo->nome);
    free(jogo);
  }
  else
  {
    printf("%d Jogo inexistente.\n", n_linha);
  }

  free(nome);
}

void equipas_mais_vitorias(link *heads, int M, int n_linha)
{
  char **nomes;
  int max = 0;
  int n_el = 0;
  int i;
  link head;
  link aux;
  link lista = 0;
  for (i = 0; i < M; i++)
  {
    head = heads[i];
    while (head != 0)
    {
      if (head->equipa->jogos_ganhos > max)
      {
        max = head->equipa->jogos_ganhos;
        lista = destroi(lista);
        lista = insere_el_char(lista, head->equipa);
        n_el = 1;
      }
      else
      {
        if (head->equipa->jogos_ganhos == max)
        {
          lista = insere_el_char(lista, head->equipa);
          n_el++;
        }
        else
        {
          
        }

      }

      head = head->next;
    }

  }

  nomes = (char **) malloc(n_el * (sizeof(char *)));
  for (i = 0, aux = lista; i < n_el; i++)
  {
    nomes[i] = (char *) malloc((sizeof(char)) * (strlen(aux->equipa->nome) + 1));
    strcpy(nomes[i], aux->equipa->nome);
    aux = aux->next;
  }

  qsort(nomes, n_el, sizeof(char *), comparar_nome);
  if (n_el > 0)
  {
    printf("%d Melhores %d\n", n_linha, max);
    for (i = 0; i < n_el; i++)
      printf("%d * %s\n", n_linha, nomes[i]);

  }
  else
  {
    
  }

  for (i = 0; i < n_el; i++)
  {
    free(nomes[i]);
  }

  free(nomes);
  lista = destroi(lista);
}

void destroi_tudo(link_jogo *head_jogos, limites_lista *lista, link *heads, int M, int n)
{
  destroi_hash_equipa(heads, n);
  destroi_lista_jogos(lista);
  destroi_hash_jogos(head_jogos, M);
}

