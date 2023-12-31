#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "hashtable.h"


size_t hash(char *v, size_t M)
{
  size_t h = 0;
  size_t a = 127;
  for (; (*v) != '\0'; v++)
  {
    h = ((a * h) + (*v)) % M;
  }

  return h;
}

Hequipas *init_hashE()
{
  Hequipas *nova_hashequipas;
  nova_hashequipas = malloc(sizeof(Hequipas));
  nova_hashequipas->cabecas = calloc(1501, sizeof(NodeE *));
  nova_hashequipas->capacidade = 1501;
  return nova_hashequipas;
}

Equipa *hash_insertE(Hequipas *h_eq, Equipa *e, char *buffer)
{
  Equipa *eq_add = malloc(sizeof(Equipa));
  NodeE *aux = malloc(sizeof(NodeE));
  size_t index = hash(buffer, h_eq->capacidade);
  eq_add->nome = malloc(strlen(buffer) + 1);
  strcpy(eq_add->nome, buffer);
  eq_add->proximo = e;
  eq_add->vitorias = 0;
  aux->proximo = h_eq->cabecas[index];
  aux->aponta_equipa = eq_add;
  e = eq_add;
  h_eq->cabecas[index] = aux;
  return e;
}

void free_Hequipas(Hequipas *t)
{
  NodeE *aux;
  size_t i;
  for (i = 0; i < t->capacidade; i++)
  {
    while (t->cabecas[i])
    {
      aux = t->cabecas[i];
      t->cabecas[i] = t->cabecas[i]->proximo;
      free(aux);
    }

  }

  free(t->cabecas);
  free(t);
}

void free_listaE(Equipa *c)
{
  Equipa *aux;
  while (c != 0)
  {
    aux = c;
    c = c->proximo;
    free(aux->nome);
    free(aux);
  }

}

int procuraE(Hequipas *h_eq, char *nome)
{
  int index;
  NodeE *tmp;
  index = hash(nome, h_eq->capacidade);
  tmp = h_eq->cabecas[index];
  while (tmp != 0)
  {
    if (strcmp(tmp->aponta_equipa->nome, nome) == 0)
    {
      return 1;
    }
    else
    {
      
    }

    tmp = tmp->proximo;
  }

  return 0;
}

Hjogos *init_hashJ()
{
  Hjogos *nova_hashjogos;
  nova_hashjogos = malloc(sizeof(Hjogos));
  nova_hashjogos->cabecas = calloc(1501, sizeof(NodeJ *));
  nova_hashjogos->capacidade = 1501;
  return nova_hashjogos;
}

void hash_insertJ(Hjogos *h_j, Cabeca_cauda *extremos_lista_jogos, char *buffer, char *equipa1_aux, char *equipa2_aux, int pontos1, int pontos2)
{
  Jogo *j_add = malloc(sizeof(Jogo));
  NodeJ *aux = malloc(sizeof(NodeJ));
  size_t index = hash(buffer, h_j->capacidade);
  j_add->nome = malloc(strlen(buffer) + 1);
  strcpy(j_add->nome, buffer);
  j_add->equipa1 = malloc(strlen(equipa1_aux) + 1);
  strcpy(j_add->equipa1, equipa1_aux);
  j_add->equipa2 = malloc(strlen(equipa2_aux) + 1);
  strcpy(j_add->equipa2, equipa2_aux);
  j_add->proximo = 0;
  j_add->anterior = extremos_lista_jogos->cauda;
  j_add->pontos1 = pontos1;
  j_add->pontos2 = pontos2;
  if (extremos_lista_jogos->cauda != 0)
  {
    extremos_lista_jogos->cauda->proximo = j_add;
  }
  else
  {
    extremos_lista_jogos->cabeca = j_add;
  }

  extremos_lista_jogos->cauda = j_add;
  aux->proximo = h_j->cabecas[index];
  if (h_j->cabecas[index])
  {
    h_j->cabecas[index]->anterior = aux;
  }
  else
  {
    
  }

  aux->anterior = 0;
  aux->aponta_jogo = j_add;
  h_j->cabecas[index] = aux;
}

void free_Hjogos(Hjogos *t)
{
  NodeJ *aux;
  size_t i;
  for (i = 0; i < t->capacidade; i++)
  {
    while (t->cabecas[i])
    {
      aux = t->cabecas[i];
      t->cabecas[i] = t->cabecas[i]->proximo;
      free(aux);
    }

  }

  free(t->cabecas);
  free(t);
}

void free_listaJ(Cabeca_cauda *c)
{
  Jogo *aux;
  while (c->cabeca != 0)
  {
    aux = c->cabeca;
    c->cabeca = c->cabeca->proximo;
    free(aux->nome);
    free(aux->equipa1);
    free(aux->equipa2);
    free(aux);
  }

  free(c);
}

int procuraJ(Hjogos *h_j, char *nome)
{
  int index;
  NodeJ *tmp;
  index = hash(nome, h_j->capacidade);
  tmp = h_j->cabecas[index];
  while (tmp != 0)
  {
    if (strcmp(tmp->aponta_jogo->nome, nome) == 0)
    {
      return 1;
    }
    else
    {
      
    }

    tmp = tmp->proximo;
  }

  return 0;
}

