#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct equipa
{
  char *equipa;
  int vitorias;
} team;
typedef struct jogo
{
  char *nome;
  team *equipa1;
  team *equipa2;
  int score1;
  int score2;
} game;
typedef struct node_jogo
{
  game *jogo;
  struct node_jogo *next;
} node_jogo;
typedef struct node_equipa
{
  team *equipa;
  struct node_equipa *next;
} node_equipa;
node_jogo *jogos_l = 0;
node_equipa *equipas_l = 0;
node_jogo *jogos_h[26];
node_equipa *equipas_h[26];
int NL = 1;
void novo_jogo();
void nova_equipa();
void lista_jogos();
void procura_jogo();
void procura_equipa();
void apaga_jogo();
void altera_score();
void equipa_mais_vitorias();
int main()
{
  int i;
  char op;
  node_equipa *e_l;
  node_equipa *aux_e_l;
  node_jogo *j_l;
  node_jogo *aux_j_l;
  for (i = 0; i < 26; i++)
  {
    equipas_h[i] = 0;
    jogos_h[i] = 0;
  }

  op = getchar();
  while (op != 'x')
  {
    if (op == 'a')
    {
      novo_jogo();
      NL = NL + 1;
    }
    else
    {
      
    }

    if (op == 'A')
    {
      nova_equipa();
      NL = NL + 1;
    }
    else
    {
      
    }

    if (op == 'l')
    {
      lista_jogos();
      NL = NL + 1;
    }
    else
    {
      
    }

    if (op == 'p')
    {
      procura_jogo();
      NL = NL + 1;
    }
    else
    {
      
    }

    if (op == 'P')
    {
      procura_equipa();
      NL = NL + 1;
    }
    else
    {
      
    }

    if (op == 'r')
    {
      apaga_jogo();
      NL = NL + 1;
    }
    else
    {
      
    }

    if (op == 's')
    {
      altera_score();
      NL = NL + 1;
    }
    else
    {
      
    }

    if (op == 'g')
    {
      equipa_mais_vitorias();
      NL = NL + 1;
    }
    else
    {
      
    }

    op = getchar();
  }

  e_l = equipas_l;
  while (e_l != 0)
  {
    aux_e_l = e_l->next;
    free(e_l->equipa->equipa);
    free(e_l->equipa);
    free(e_l);
    e_l = aux_e_l;
  }

  j_l = jogos_l;
  while (j_l != 0)
  {
    aux_j_l = j_l->next;
    free(j_l->jogo->nome);
    free(j_l->jogo);
    free(j_l);
    j_l = aux_j_l;
  }

  for (i = 0; i < 26; i++)
  {
    node_equipa *e_h;
    node_equipa *aux_e_h;
    node_jogo *j_h;
    node_jogo *aux_j_h;
    e_h = equipas_h[i];
    j_h = jogos_h[i];
    while (e_h != 0)
    {
      aux_e_h = e_h->next;
      free(e_h);
      e_h = aux_e_h;
    }

    while (j_h != 0)
    {
      aux_j_h = j_h->next;
      free(j_h);
      j_h = aux_j_h;
    }

  }

  return 0;
}

void novo_jogo()
{
  char j_aux[1023];
  char *j_aux1;
  char e1_aux[1023];
  char e2_aux[1023];
  int score1;
  int score2;
  int existe_equipa1 = 0;
  int existe_equipa2 = 0;
  int lenght_j;
  int j;
  int g_1;
  int g_2;
  node_jogo *k;
  node_equipa *e1;
  node_equipa *e2;
  team *equipa1;
  team *equipa2;
  game *jogo;
  node_jogo *j1;
  node_jogo *j2;
  getchar();
  for (int j_aux_index = 0; j_aux_index < 10; j_aux_index++)
  {
    j_aux[j_aux_index] = new_sym_var(sizeof(char) * 8);
  }

  j_aux[10 - 1] = '\0';
  getchar();
  for (int e1_aux_index = 0; e1_aux_index < 10; e1_aux_index++)
  {
    e1_aux[e1_aux_index] = new_sym_var(sizeof(char) * 8);
  }

  e1_aux[10 - 1] = '\0';
  getchar();
  for (int e2_aux_index = 0; e2_aux_index < 10; e2_aux_index++)
  {
    e2_aux[e2_aux_index] = new_sym_var(sizeof(char) * 8);
  }

  e2_aux[10 - 1] = '\0';
  getchar();
  score1 = new_sym_var(sizeof(int) * 8);
  getchar();
  score2 = new_sym_var(sizeof(int) * 8);
  lenght_j = strlen(j_aux);
  j_aux1 = (char *) malloc((lenght_j * (sizeof(char))) + 1);
  strcpy(j_aux1, j_aux);
  j = j_aux1[0] % 26;
  for (k = jogos_h[j]; k != 0; k = k->next)
    if (strcmp(j_aux1, k->jogo->nome) == 0)
  {
    printf("%d Jogo existente.\n", NL);
    free(j_aux1);
    return;
  }
  else
  {
    
  }


  g_1 = e1_aux[0] % 26;
  g_2 = e2_aux[0] % 26;
  for (e1 = equipas_h[g_1]; e1 != 0; e1 = e1->next)
    if (strcmp(e1_aux, e1->equipa->equipa) == 0)
  {
    existe_equipa1 = 1;
    equipa1 = e1->equipa;
    break;
  }
  else
  {
    
  }


  for (e2 = equipas_h[g_2]; e2 != 0; e2 = e2->next)
    if (strcmp(e2_aux, e2->equipa->equipa) == 0)
  {
    existe_equipa2 = 1;
    equipa2 = e2->equipa;
    break;
  }
  else
  {
    
  }


  if ((existe_equipa1 == 0) || (existe_equipa2 == 0))
  {
    printf("%d Equipa inexistente.\n", NL);
    free(j_aux1);
    return;
  }
  else
  {
    
  }

  jogo = (game *) malloc(sizeof(game));
  j1 = (node_jogo *) malloc(sizeof(node_jogo));
  j2 = (node_jogo *) malloc(sizeof(node_jogo));
  jogo->score1 = score1;
  jogo->score2 = score2;
  jogo->equipa1 = equipa1;
  jogo->equipa2 = equipa2;
  jogo->nome = j_aux1;
  if (score1 > score2)
  {
    jogo->equipa1->vitorias++;
  }
  else
  {
    if (score2 > score1)
    {
      jogo->equipa2->vitorias++;
    }
    else
    {
      
    }

  }

  j1->jogo = jogo;
  j1->next = 0;
  j2->jogo = jogo;
  j2->next = 0;
  if (jogos_l == 0)
  {
    jogos_l = j1;
  }
  else
  {
    node_jogo *i1 = jogos_l;
    for (; i1->next != 0; i1 = i1->next)
      ;

    i1->next = j1;
  }

  if (jogos_h[j] == 0)
  {
    jogos_h[j] = j2;
  }
  else
  {
    node_jogo *aux;
    aux = jogos_h[j];
    j2->next = aux;
    jogos_h[j] = j2;
  }

}

void nova_equipa()
{
  char e_aux[1023];
  char *e_aux1;
  team *equipa;
  node_equipa *e1;
  node_equipa *e2;
  int lenght;
  int j;
  node_equipa *k;
  getchar();
  for (int e_aux_index = 0; e_aux_index < 10; e_aux_index++)
  {
    e_aux[e_aux_index] = new_sym_var(sizeof(char) * 8);
  }

  e_aux[10 - 1] = '\0';
  lenght = strlen(e_aux);
  e_aux1 = (char *) malloc((lenght + 1) * (sizeof(char)));
  strcpy(e_aux1, e_aux);
  j = e_aux1[0] % 26;
  for (k = equipas_h[j]; k != 0; k = k->next)
    if (strcmp(e_aux1, k->equipa->equipa) == 0)
  {
    printf("%d Equipa existente.\n", NL);
    free(e_aux1);
    return;
  }
  else
  {
    
  }


  equipa = (team *) malloc(sizeof(team));
  e1 = (node_equipa *) malloc(sizeof(node_equipa));
  e2 = (node_equipa *) malloc(sizeof(node_equipa));
  equipa->equipa = e_aux1;
  equipa->vitorias = 0;
  e1->equipa = equipa;
  e1->next = 0;
  e2->equipa = equipa;
  e2->next = 0;
  if (equipas_l == 0)
  {
    equipas_l = e1;
    e1->next = 0;
  }
  else
  {
    node_equipa *i;
    for (i = equipas_l; i != 0; i = i->next)
    {
      if (strcmp(e1->equipa->equipa, equipas_l->equipa->equipa) < 0)
      {
        e1->next = equipas_l;
        equipas_l = e1;
        break;
      }
      else
      {
        if ((i->next == 0) && (strcmp(e1->equipa->equipa, i->equipa->equipa) >= 0))
        {
          e1->next = i->next;
          i->next = e1;
          break;
        }
        else
        {
          if (strcmp(e1->equipa->equipa, i->next->equipa->equipa) < 0)
          {
            e1->next = i->next;
            i->next = e1;
            break;
          }
          else
          {
            
          }

        }

      }

    }

  }

  if (equipas_h[j] == 0)
  {
    equipas_h[j] = e2;
  }
  else
  {
    node_equipa *aux;
    aux = equipas_h[j];
    e2->next = aux;
    equipas_h[j] = e2;
  }

}

void lista_jogos()
{
  node_jogo *i = jogos_l;
  for (; i != 0; i = i->next)
    printf("%d %s %s %s %d %d\n", NL, i->jogo->nome, i->jogo->equipa1->equipa, i->jogo->equipa2->equipa, i->jogo->score1, i->jogo->score2);

}

void procura_jogo()
{
  char j_aux[1023];
  int j;
  int existe = 0;
  node_jogo *k;
  getchar();
  for (int j_aux_index = 0; j_aux_index < 10; j_aux_index++)
  {
    j_aux[j_aux_index] = new_sym_var(sizeof(char) * 8);
  }

  j_aux[10 - 1] = '\0';
  j = j_aux[0] % 26;
  for (k = jogos_h[j]; k != 0; k = k->next)
    if (strcmp(j_aux, k->jogo->nome) == 0)
  {
    printf("%d %s %s %s %d %d\n", NL, j_aux, k->jogo->equipa1->equipa, k->jogo->equipa2->equipa, k->jogo->score1, k->jogo->score2);
    existe = 1;
    break;
  }
  else
  {
    
  }


  if (existe == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    
  }

}

void procura_equipa()
{
  char e_aux[1023];
  int existe = 0;
  int j;
  node_equipa *k;
  getchar();
  for (int e_aux_index = 0; e_aux_index < 10; e_aux_index++)
  {
    e_aux[e_aux_index] = new_sym_var(sizeof(char) * 8);
  }

  e_aux[10 - 1] = '\0';
  j = e_aux[0] % 26;
  for (k = equipas_h[j]; k != 0; k = k->next)
    if (strcmp(e_aux, k->equipa->equipa) == 0)
  {
    printf("%d %s %d\n", NL, k->equipa->equipa, k->equipa->vitorias);
    existe = 1;
    break;
  }
  else
  {
    
  }


  if (existe == 0)
  {
    printf("%d Equipa inexistente.\n", NL);
  }
  else
  {
    
  }

}

void apaga_jogo()
{
  char j_aux[1023];
  int existe = 0;
  int j;
  node_jogo *k;
  getchar();
  for (int j_aux_index = 0; j_aux_index < 10; j_aux_index++)
  {
    j_aux[j_aux_index] = new_sym_var(sizeof(char) * 8);
  }

  j_aux[10 - 1] = '\0';
  j = j_aux[0] % 26;
  for (k = jogos_h[j]; k != 0; k = k->next)
  {
    if (strcmp(j_aux, k->jogo->nome) == 0)
    {
      existe = 1;
      if (k->jogo->score1 > k->jogo->score2)
      {
        k->jogo->equipa1->vitorias--;
      }
      else
      {
        if (k->jogo->score1 < k->jogo->score2)
        {
          k->jogo->equipa2->vitorias--;
        }
        else
        {
          
        }

      }

      break;
    }
    else
    {
      
    }

  }

  if (existe == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    node_jogo *prev_h;
    node_jogo *i_h;
    node_jogo *aux_h;
    node_jogo *prev_l;
    node_jogo *i_l;
    node_jogo *aux_l;
    prev_h = jogos_h[j];
    i_h = prev_h->next;
    prev_l = jogos_l;
    i_l = prev_l->next;
    if ((strcmp(j_aux, jogos_h[j]->jogo->nome) == 0) && (i_h == 0))
    {
      aux_h = jogos_h[j];
      jogos_h[j] = i_h;
      free(aux_h);
    }
    else
    {
      
    }

    for (; i_h != 0; prev_h = prev_h->next, i_h = i_h->next)
    {
      if (strcmp(j_aux, jogos_h[j]->jogo->nome) == 0)
      {
        aux_h = jogos_h[j];
        jogos_h[j] = i_h;
        free(aux_h);
        break;
      }
      else
      {
        if ((strcmp(j_aux, i_h->jogo->nome) == 0) && (i_h->next == 0))
        {
          prev_h->next = 0;
          free(i_h);
          break;
        }
        else
        {
          if (strcmp(j_aux, i_h->jogo->nome) == 0)
          {
            aux_h = i_h;
            prev_h->next = i_h->next;
            free(aux_h);
            break;
          }
          else
          {
            
          }

        }

      }

    }

    if ((strcmp(j_aux, jogos_l->jogo->nome) == 0) && (i_l == 0))
    {
      aux_l = jogos_l;
      jogos_l = i_l;
      free(aux_l->jogo->nome);
      free(aux_l->jogo);
      free(aux_l);
    }
    else
    {
      
    }

    for (; i_l != 0; prev_l = prev_l->next, i_l = i_l->next)
    {
      if (strcmp(j_aux, prev_l->jogo->nome) == 0)
      {
        aux_l = jogos_l;
        jogos_l = i_l;
        free(aux_l->jogo->nome);
        free(aux_l->jogo);
        free(aux_l);
        break;
      }
      else
      {
        if ((strcmp(j_aux, i_l->jogo->nome) == 0) && (i_l->next == 0))
        {
          prev_l->next = 0;
          free(i_l->jogo->nome);
          free(i_l->jogo);
          free(i_l);
          break;
        }
        else
        {
          if (strcmp(j_aux, i_l->jogo->nome) == 0)
          {
            aux_l = i_l;
            prev_l->next = i_l->next;
            free(aux_l->jogo->nome);
            free(aux_l->jogo);
            free(aux_l);
            break;
          }
          else
          {
            
          }

        }

      }

    }

  }

}

void altera_score()
{
  char j_aux[1023];
  int new_score1;
  int new_score2;
  int old_score1;
  int old_score2;
  int existe = 0;
  int j;
  node_jogo *k;
  getchar();
  for (int j_aux_index = 0; j_aux_index < 10; j_aux_index++)
  {
    j_aux[j_aux_index] = new_sym_var(sizeof(char) * 8);
  }

  j_aux[10 - 1] = '\0';
  getchar();
  new_score1 = new_sym_var(sizeof(int) * 8);
  getchar();
  new_score2 = new_sym_var(sizeof(int) * 8);
  j = j_aux[0] % 26;
  for (k = jogos_h[j]; k != 0; k = k->next)
    if (strcmp(j_aux, k->jogo->nome) == 0)
  {
    existe = 1;
    break;
  }
  else
  {
    
  }


  if (existe == 1)
  {
    old_score1 = k->jogo->score1;
    old_score2 = k->jogo->score2;
    k->jogo->score1 = new_score1;
    k->jogo->score2 = new_score2;
    if ((old_score1 > old_score2) && (new_score1 < new_score2))
    {
      if (k->jogo->equipa1->vitorias != 0)
      {
        k->jogo->equipa1->vitorias--;
      }
      else
      {
        
      }

      k->jogo->equipa2->vitorias++;
    }
    else
    {
      if ((old_score1 < old_score2) && (new_score1 > new_score2))
      {
        k->jogo->equipa1->vitorias++;
        if (k->jogo->equipa2->vitorias != 0)
        {
          k->jogo->equipa2->vitorias--;
        }
        else
        {
          
        }

      }
      else
      {
        if ((old_score1 == old_score2) && (new_score1 > new_score2))
        {
          k->jogo->equipa1->vitorias++;
        }
        else
        {
          if ((old_score1 == old_score2) && (new_score1 < new_score2))
          {
            k->jogo->equipa2->vitorias++;
          }
          else
          {
            if ((old_score1 < old_score2) && (new_score1 == new_score2))
            {
              k->jogo->equipa2->vitorias--;
            }
            else
            {
              if ((old_score1 > old_score2) && (new_score1 == new_score2))
              {
                k->jogo->equipa1->vitorias--;
              }
              else
              {
                
              }

            }

          }

        }

      }

    }

  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void equipa_mais_vitorias()
{
  if (equipas_l == 0)
  {
    return;
  }
  else
  {
    node_equipa *i;
    node_equipa *j;
    int max = 0;
    for (i = equipas_l; i != 0; i = i->next)
      if (i->equipa->vitorias > max)
    {
      max = i->equipa->vitorias;
    }
    else
    {
      
    }


    printf("%d Melhores %d\n", NL, max);
    for (j = equipas_l; j != 0; j = j->next)
      if (j->equipa->vitorias == max)
    {
      printf("%d * %s\n", NL, j->equipa->equipa);
    }
    else
    {
      
    }


  }

}

