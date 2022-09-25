/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


typedef struct equipa
{
  char *nome;
  int vitorias;
} Equipa;
typedef struct node_equipas
{
  Equipa *equipa;
  struct node_equipas *next;
  struct node_equipas *prev;
} Nd_Eq;
typedef struct 
{
  struct node_equipas *head;
  struct node_equipas *last;
} Lst_Eqs;
typedef struct hash_equipa
{
  Nd_Eq *node_e;
  struct hash_equipa *next;
  struct hash_equipa *prev;
} Hsh_Eq;
typedef struct jogo
{
  char *nome;
  char *equipa1;
  char *equipa2;
  int score1;
  int score2;
} Jogo;
typedef struct node_jogos
{
  Jogo *jogo;
  struct node_jogos *next;
  struct node_jogos *prev;
} Nd_Jg;
typedef struct 
{
  struct node_jogos *head;
  struct node_jogos *last;
} Lst_Jgs;
typedef struct hash_jogo
{
  Nd_Jg *node_j;
  struct hash_jogo *next;
  struct hash_jogo *prev;
} Hsh_Jg;
int hash(char *nome, int M);
Equipa *encontra_equipa(char *nome, Hsh_Eq **tabela);
Equipa *encontra_equipa_hash(char *nome, Hsh_Eq *indice);
Jogo *encontra_jogo(char *nome, Hsh_Jg **tabela);
Nd_Jg *encontra_jogo_node(char *nome, Hsh_Jg *indice);
Hsh_Jg *encontra_jogo_hash(char *nome, Hsh_Jg *indice);
void free_jogo(Jogo *j);
void free_equipa(Equipa *e);
void free_Nd_Eq(Nd_Eq *node_e);
void free_Nd_Jg(Nd_Jg *node_j);
Equipa *criar_equipa(char *nome_eq);
Lst_Eqs *criar_lst_equipas();
Hsh_Eq **criar_tabela_eq(int M);
Nd_Eq *push_equipa_node(Equipa *eq, Lst_Eqs *l);
void push_equipa_hash(Nd_Eq *node, Hsh_Eq **tabela);
Jogo *criar_jogo(char *nome, char *e1, char *e2, int s1, int s2);
Lst_Jgs *criar_lst_jogos();
Hsh_Jg **criar_tabela_jogos(int M);
Nd_Jg *push_jogo_node(Jogo *j, Lst_Jgs *l);
void push_jogo_hash(Nd_Jg *node, Hsh_Jg **tabela_jg);
int vencedor(Jogo *j);
void alterar_vitorias(char operacao, char *nome_eq, Hsh_Eq **tabela);
void print_lst_eq(Lst_Eqs *l);
void print_lst_jg(Lst_Jgs *l);
void print_hash_eq(Hsh_Eq **tabela, int i);
void print_hash_jg(Hsh_Jg **tabela, int i);
void NovaEquipa_aux(Hsh_Eq **tabela_eq, Lst_Eqs *lst_eqs, char *nome);
void A_NovaEquipa(int *NL, Hsh_Eq **tabela_eq, Lst_Eqs *lst_eqs);
void NovoJogo_aux(char *nome_j, char *nome_e1, char *nome_e2, int s1, int s2, Hsh_Eq **tabela_e, Hsh_Jg **tabela_j, Lst_Jgs *lst_j);
void a_NovoJogo(int *NL, Hsh_Eq **tabela_e, Hsh_Jg **tabela_j, Lst_Jgs *lst_j);
void l_JogosPorData(int *NL, Lst_Jgs *l);
void p_ProcuraJogo(int *NL, Hsh_Jg **tabela_j);
void P_ProcuraEquipa(int *NL, Hsh_Eq **tabela_eq);
int hash(char *nome, int M)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*nome) != '\0'; nome++, a = (a * b) % (M - 1))
    h = ((a * h) + (*nome)) % M;

  return h;
}

Equipa *encontra_equipa(char *nome, Hsh_Eq **tabela)
{
  int i = hash(nome, 1709);
  return encontra_equipa_hash(nome, tabela[i]);
}

Equipa *encontra_equipa_hash(char *nome, Hsh_Eq *indice)
{
  Hsh_Eq *aux;
  for (aux = indice; aux != 0; aux = aux->next)
    if (strcmp(aux->node_e->equipa->nome, nome) == 0)
  {
    return aux->node_e->equipa;
  }
  else
  {
    
  }


  return 0;
}

Jogo *encontra_jogo(char *nome, Hsh_Jg **tabela)
{
  int i = hash(nome, 1709);
  Nd_Jg *node_j;
  node_j = encontra_jogo_node(nome, tabela[i]);
  if (node_j != 0)
  {
    return node_j->jogo;
  }
  else
  {
    
  }

  return 0;
}

Nd_Jg *encontra_jogo_node(char *nome, Hsh_Jg *indice)
{
  Hsh_Jg *aux;
  aux = encontra_jogo_hash(nome, indice);
  if (aux != 0)
  {
    return aux->node_j;
  }
  else
  {
    
  }

  return 0;
}

Hsh_Jg *encontra_jogo_hash(char *nome, Hsh_Jg *indice)
{
  Hsh_Jg *aux;
  for (aux = indice; aux != 0; aux = aux->next)
    if (strcmp(aux->node_j->jogo->nome, nome) == 0)
  {
    return aux;
  }
  else
  {
    
  }


  return 0;
}

void free_jogo(Jogo *j)
{
  free(j->nome);
  free(j->equipa1);
  free(j->equipa2);
  free(j);
  return;
}

void free_equipa(Equipa *e)
{
  free(e->nome);
  free(e);
  return;
}

void free_Nd_Eq(Nd_Eq *node_e)
{
  free_equipa(node_e->equipa);
  free(node_e);
  return;
}

void free_Nd_Jg(Nd_Jg *node_j)
{
  free_jogo(node_j->jogo);
  free(node_j);
  return;
}

Equipa *criar_equipa(char *nome_eq)
{
  Equipa *eq = malloc(sizeof(Equipa));
  eq->nome = malloc((strlen(nome_eq) + 1) * (sizeof(char)));
  strcpy(eq->nome, nome_eq);
  eq->vitorias = 0;
  return eq;
}

Lst_Eqs *criar_lst_equipas()
{
  Lst_Eqs *l = malloc(sizeof(Lst_Eqs));
  l->head = (l->last = 0);
  return l;
}

Hsh_Eq **criar_tabela_eq(int M)
{
  Hsh_Eq **tabela = malloc(M * (sizeof(Hsh_Eq *)));
  int i;
  for (i = 0; i < M; i++)
    tabela[i] = 0;

  return tabela;
}

Nd_Eq *push_equipa_node(Equipa *eq, Lst_Eqs *l)
{
  Nd_Eq *new = malloc(sizeof(Nd_Eq));
  new->equipa = eq;
  new->prev = l->last;
  new->next = 0;
  if (l->last)
  {
    l->last->next = new;
  }
  else
  {
    l->head = new;
  }

  l->last = new;
  return new;
}

void push_equipa_hash(Nd_Eq *node, Hsh_Eq **tabela)
{
  Hsh_Eq *hash_e = malloc(sizeof(Hsh_Eq));
  int i = hash(node->equipa->nome, 1709);
  hash_e->node_e = node;
  hash_e->next = tabela[i];
  hash_e->prev = 0;
  tabela[i] = hash_e;
  return;
}

Jogo *criar_jogo(char *nome, char *e1, char *e2, int s1, int s2)
{
  Jogo *j = malloc(sizeof(Jogo));
  j->nome = malloc((strlen(nome) + 1) * (sizeof(char)));
  j->equipa1 = malloc((strlen(e1) + 1) * (sizeof(char)));
  j->equipa2 = malloc((strlen(e2) + 1) * (sizeof(char)));
  strcpy(j->nome, nome);
  strcpy(j->equipa1, e1);
  strcpy(j->equipa2, e2);
  j->score1 = s1;
  j->score2 = s2;
  return j;
}

Lst_Jgs *criar_lst_jogos()
{
  Lst_Jgs *l = malloc(sizeof(Lst_Jgs));
  l->head = (l->last = 0);
  return l;
}

Hsh_Jg **criar_tabela_jogos(int M)
{
  Hsh_Jg **tabela = malloc(M * (sizeof(Hsh_Jg *)));
  int i;
  for (i = 0; i < M; i++)
    tabela[i] = 0;

  return tabela;
}

Nd_Jg *push_jogo_node(Jogo *j, Lst_Jgs *l)
{
  Nd_Jg *new = malloc(sizeof(Nd_Jg));
  new->jogo = j;
  new->prev = l->last;
  new->next = 0;
  if (l->last)
  {
    l->last->next = new;
  }
  else
  {
    l->head = new;
  }

  l->last = new;
  return new;
}

void push_jogo_hash(Nd_Jg *node, Hsh_Jg **tabela_jg)
{
  Hsh_Jg *hash_jg = malloc(sizeof(Hsh_Jg));
  int i = hash(node->jogo->nome, 1709);
  hash_jg->node_j = node;
  hash_jg->prev = 0;
  hash_jg->next = tabela_jg[i];
  tabela_jg[i] = hash_jg;
  return;
}

int vencedor(Jogo *j)
{
  if (j->score1 > j->score2)
  {
    return 1;
  }
  else
  {
    if (j->score2 > j->score1)
    {
      return 2;
    }
    else
    {
      return 3;
    }

  }

}

void alterar_vitorias(char operacao, char *nome_eq, Hsh_Eq **tabela)
{
  Equipa *e = encontra_equipa(nome_eq, tabela);
  if (operacao == '+')
  {
    e->vitorias++;
  }
  else
  {
    if (operacao == '-')
    {
      e->vitorias--;
    }
    else
    {
      
    }

  }

  return;
}

void NovaEquipa_aux(Hsh_Eq **tabela_eq, Lst_Eqs *lst_eqs, char *nome)
{
  Equipa *e;
  Nd_Eq *node_e;
  e = criar_equipa(nome);
  node_e = push_equipa_node(e, lst_eqs);
  push_equipa_hash(node_e, tabela_eq);
  return;
}

void A_NovaEquipa(int *NL, Hsh_Eq **tabela_eq, Lst_Eqs *lst_eqs)
{
  char *nome_eq = malloc((1023 + 1) * (sizeof(char)));
  for (int nome_eq_index = 0; nome_eq_index < 10; nome_eq_index++)
  {
    nome_eq[nome_eq_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_eq[10 - 1] = '\0';
  if (encontra_equipa(nome_eq, tabela_eq) != 0)
  {
    printf("%d Equipa existente.\n", *NL);
  }
  else
  {
    NovaEquipa_aux(tabela_eq, lst_eqs, nome_eq);
  }

  free(nome_eq);
  return;
}

void NovoJogo_aux(char *nome_j, char *nome_e1, char *nome_e2, int s1, int s2, Hsh_Eq **tabela_e, Hsh_Jg **tabela_j, Lst_Jgs *lst_j)
{
  Jogo *j;
  Nd_Jg *node_j;
  int venceu;
  j = criar_jogo(nome_j, nome_e1, nome_e2, s1, s2);
  node_j = push_jogo_node(j, lst_j);
  push_jogo_hash(node_j, tabela_j);
  venceu = vencedor(j);
  if (venceu == 1)
  {
    alterar_vitorias('+', nome_e1, tabela_e);
  }
  else
  {
    if (venceu == 2)
    {
      alterar_vitorias('+', nome_e2, tabela_e);
    }
    else
    {
      
    }

  }

  return;
}

void a_NovoJogo(int *NL, Hsh_Eq **tabela_e, Hsh_Jg **tabela_j, Lst_Jgs *lst_j)
{
  char *nome_j = malloc((1023 + 1) * (sizeof(char)));
  char *nome_e1 = malloc((1023 + 1) * (sizeof(char)));
  char *nome_e2 = malloc((1023 + 1) * (sizeof(char)));
  int s1;
  int s2;
  for (int nome_j_index = 0; nome_j_index < 10; nome_j_index++)
  {
    nome_j[nome_j_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_j[10 - 1] = '\0';
  for (int nome_e1_index = 0; nome_e1_index < 10; nome_e1_index++)
  {
    nome_e1[nome_e1_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_e1[10 - 1] = '\0';
  for (int nome_e2_index = 0; nome_e2_index < 10; nome_e2_index++)
  {
    nome_e2[nome_e2_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_e2[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  if (encontra_jogo(nome_j, tabela_j) != 0)
  {
    printf("%d Jogo existente.\n", *NL);
  }
  else
  {
    if ((encontra_equipa(nome_e1, tabela_e) == 0) || (encontra_equipa(nome_e2, tabela_e) == 0))
    {
      printf("%d Equipa inexistente.\n", *NL);
    }
    else
    {
      NovoJogo_aux(nome_j, nome_e1, nome_e2, s1, s2, tabela_e, tabela_j, lst_j);
    }

  }

  free(nome_j);
  free(nome_e1);
  free(nome_e2);
  return;
}

void l_JogosPorData(int *NL, Lst_Jgs *l)
{
  Nd_Jg *aux;
  for (aux = l->head; aux != 0; aux = aux->next)
    printf("%d %s %s %s %d %d\n", *NL, aux->jogo->nome, aux->jogo->equipa1, aux->jogo->equipa2, aux->jogo->score1, aux->jogo->score2);

  return;
}

void p_ProcuraJogo(int *NL, Hsh_Jg **tabela_j)
{
  Jogo *j;
  char *nome = malloc((1023 + 1) * (sizeof(char)));
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  j = encontra_jogo(nome, tabela_j);
  if (j == 0)
  {
    printf("%d Jogo inexistente.\n", *NL);
  }
  else
  {
    printf("%d %s %s %s %d %d\n", *NL, j->nome, j->equipa1, j->equipa2, j->score1, j->score2);
  }

  free(nome);
  return;
}

void P_ProcuraEquipa(int *NL, Hsh_Eq **tabela_eq)
{
  Equipa *e;
  char *nome = malloc((1023 + 1) * (sizeof(char)));
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  e = encontra_equipa(nome, tabela_eq);
  if (e == 0)
  {
    printf("%d Equipa inexistente.\n", *NL);
  }
  else
  {
    printf("%d %s %d\n", *NL, e->nome, e->vitorias);
  }

  return;
  free(nome);
}

int nr_vitorias(Nd_Eq *nd_e)
{
  return nd_e->equipa->vitorias;
}

void s_AlteraScore(int *NL, Hsh_Jg **tabela_j, Hsh_Eq **tabela_e)
{
  char *nome = malloc((1023 + 1) * (sizeof(char)));
  Jogo *j;
  int s1;
  int s2;
  int venceu_antes;
  int venceu_agora;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  j = encontra_jogo(nome, tabela_j);
  if (j == 0)
  {
    printf("%d Jogo inexistente.\n", *NL);
  }
  else
  {
    venceu_antes = vencedor(j);
    j->score1 = s1;
    j->score2 = s2;
    venceu_agora = vencedor(j);
    if (venceu_antes == 3)
    {
      if (venceu_agora == 1)
      {
        alterar_vitorias('+', j->equipa1, tabela_e);
      }
      else
      {
        if (venceu_agora == 2)
        {
          alterar_vitorias('+', j->equipa2, tabela_e);
        }
        else
        {
          
        }

      }

    }
    else
    {
      if (venceu_antes == 1)
      {
        if (venceu_agora == 2)
        {
          alterar_vitorias('-', j->equipa1, tabela_e);
          alterar_vitorias('+', j->equipa2, tabela_e);
        }
        else
        {
          if (venceu_agora == 3)
          {
            alterar_vitorias('-', j->equipa1, tabela_e);
          }
          else
          {
            
          }

        }

      }
      else
      {
        if (venceu_antes == 2)
        {
          if (venceu_agora == 1)
          {
            alterar_vitorias('+', j->equipa1, tabela_e);
            alterar_vitorias('-', j->equipa2, tabela_e);
          }
          else
          {
            if (venceu_agora == 3)
            {
              alterar_vitorias('-', j->equipa2, tabela_e);
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

  }

  free(nome);
  return;
}

int peso_nome(char *nome)
{
  int p;
  int a = 3;
  for (p = 0; (*nome) != '\0'; nome++)
    p = (a * p) + (*nome);

  return p;
}

int less(char *nome1, char *nome2)
{
  return peso_nome(nome1) <= peso_nome(nome2);
}

void trocar(char *nome1, char *nome2)
{
  char *aux;
  aux = nome1;
  nome1 = nome2;
  nome2 = aux;
  return;
}

int partition(char **lst, int l, int r)
{
  int i = l - 1;
  int j = r;
  char *nome_eq = lst[r];
  while (i < j)
  {
    while (less(lst[++i], nome_eq))
      ;

    while (less(nome_eq, lst[--j]))
      if (j == l)
    {
      break;
    }
    else
    {
      
    }


    if (i < j)
    {
      trocar(lst[i], lst[j]);
    }
    else
    {
      
    }

  }

  trocar(lst[i], lst[r]);
  return i;
}

void quicksort(char **lst, int l, int r)
{
  int i;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  i = partition(lst, l, r);
  quicksort(lst, l, i - 1);
  quicksort(lst, i + 1, r);
}

void g_MelhoresEquipas(int *NL, Lst_Eqs *lst_e)
{
  int size_tabela = 5;
  int size_nome_eq;
  int nr_melhores_equipas = 0;
  int max_vitorias = 0;
  int i;
  Nd_Eq *aux;
  char *nome_eq = 0;
  char **a_ordenar = malloc(size_tabela * (sizeof(char *)));
  if (lst_e->head == 0)
  {
    return;
  }
  else
  {
    
  }

  for (aux = lst_e->head; aux != 0; aux = aux->next)
  {
    if (nr_vitorias(aux) > max_vitorias)
    {
      max_vitorias = nr_vitorias(aux);
      nr_melhores_equipas = 0;
    }
    else
    {
      
    }

    if (nr_vitorias(aux) == max_vitorias)
    {
      size_nome_eq = strlen(aux->equipa->nome);
      nome_eq = malloc((size_nome_eq + 1) * (sizeof(char)));
      strcpy(nome_eq, aux->equipa->nome);
      a_ordenar[nr_melhores_equipas] = nome_eq;
      nr_melhores_equipas++;
    }
    else
    {
      
    }

    if (nr_melhores_equipas == size_tabela)
    {
      size_tabela = size_tabela * 2;
      a_ordenar = (char **) realloc(a_ordenar, size_tabela * (sizeof(char *)));
    }
    else
    {
      
    }

  }

  a_ordenar = (char **) realloc(a_ordenar, nr_melhores_equipas * (sizeof(char *)));
  quicksort(a_ordenar, 0, nr_melhores_equipas - 1);
  printf("%d Melhores %d\n", *NL, max_vitorias);
  for (i = 0; i < nr_melhores_equipas; i++)
    printf("%d * %s\n", *NL, a_ordenar[i]);

  return;
}

void r_ApagaJogo(int *NL, Hsh_Jg **tabela_j, Lst_Jgs *lst_j, Hsh_Eq **tabela_e)
{
  int i;
  int venceu_antes = 0;
  char *nome = malloc((1023 + 1) * (sizeof(char)));
  Jogo *j = 0;
  Nd_Jg *node_j = 0;
  Hsh_Jg *hash_j = 0;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  j = encontra_jogo(nome, tabela_j);
  if (j == 0)
  {
    printf("%d Jogo inexistente.\n", *NL);
  }
  else
  {
    venceu_antes = vencedor(j);
    if (venceu_antes == 1)
    {
      alterar_vitorias('-', j->equipa1, tabela_e);
    }
    else
    {
      if (venceu_antes == 2)
      {
        alterar_vitorias('-', j->equipa2, tabela_e);
      }
      else
      {
        
      }

    }

    i = hash(nome, 1709);
    hash_j = encontra_jogo_hash(nome, tabela_j[i]);
    node_j = hash_j->node_j;
    if (node_j->prev == 0)
    {
      lst_j->head = node_j->next;
    }
    else
    {
      node_j->prev->next = node_j->next;
    }

    if (node_j->next == 0)
    {
      lst_j->last = node_j->prev;
    }
    else
    {
      node_j->next->prev = node_j->prev;
    }

    free_Nd_Jg(node_j);
    if (hash_j->prev == 0)
    {
      tabela_j[i] = hash_j->next;
    }
    else
    {
      hash_j->prev->next = hash_j->next;
    }

    if (hash_j->next != 0)
    {
      hash_j->next->prev = hash_j->prev;
    }
    else
    {
      
    }

    free(hash_j);
  }

  return;
}

int main()
{
  char comando;
  int *NL;
  int linha = 1;
  Hsh_Jg **tabela_j = criar_tabela_jogos(1709);
  Hsh_Eq **tabela_e = criar_tabela_eq(1709);
  Lst_Jgs *lst_jgs = criar_lst_jogos();
  Lst_Eqs *lst_eqs = criar_lst_equipas();
  NL = &linha;
  comando = new_sym_var(sizeof(char) * 8);
  while (comando != 'x')
  {
    switch (comando)
    {
      case 'a':
        a_NovoJogo(NL, tabela_e, tabela_j, lst_jgs);
        break;

      case 'A':
        A_NovaEquipa(NL, tabela_e, lst_eqs);
        break;

      case 'l':
        l_JogosPorData(NL, lst_jgs);
        break;

      case 'p':
        p_ProcuraJogo(NL, tabela_j);
        break;

      case 'P':
        P_ProcuraEquipa(NL, tabela_e);
        break;

      case 'r':
        r_ApagaJogo(NL, tabela_j, lst_jgs, tabela_e);
        break;

      case 's':
        s_AlteraScore(NL, tabela_j, tabela_e);
        break;

      case 'g':
        g_MelhoresEquipas(NL, lst_eqs);
        break;

    }

    comando = new_sym_var(sizeof(char) * 8);
    (*NL)++;
  }

  return 0;
}

