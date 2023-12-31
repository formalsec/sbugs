#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "Equipas.h"
#include "func_hash.h"


ptr_equipas nova_equipa(char *nome, int vitorias)
{
  ptr_equipas novo = (ptr_equipas) malloc(sizeof(struct equipas));
  novo->nome = nome;
  novo->vitorias = vitorias;
  return novo;
}

link_e insere_alfabetica(link_e primeiro, link_e y)
{
  link_e x;
  link_e anterior;
  if ((primeiro == 0) || (strcmp(y->equipa->nome, primeiro->equipa->nome) < 0))
  {
    y->proximo = primeiro;
    return y;
  }
  else
  {
    anterior = primeiro;
    x = primeiro->proximo;
    while ((x != 0) && (strcmp(y->equipa->nome, x->equipa->nome) > 0))
    {
      anterior = x;
      x = x->proximo;
    }

    y->proximo = x;
    anterior->proximo = y;
  }

  return primeiro;
}

link_e insere_inicio_e(link_e primeiro, link_e y)
{
  y->proximo = primeiro;
  return y;
}

link_e procura_e(link_e primeiro, char *nome)
{
  link_e x;
  for (x = primeiro; x != 0; x = x->proximo)
    if (strcmp(x->equipa->nome, nome) == 0)
  {
    return x;
  }
  else
  {
    
  }


  return 0;
}

void FreeNode_e(link_e x)
{
  free(x->equipa);
  free(x);
}

void FreeNome_e(link_e x)
{
  free(x->equipa->nome);
  free(x->equipa);
}

link_e *inicializa_e(link_e *primeiros)
{
  int p;
  primeiros = (link_e *) malloc(1009 * (sizeof(link_e)));
  for (p = 0; p < 1009; p++)
    primeiros[p] = 0;

  return primeiros;
}

void insere_equipa(link_e *primeiros, link_e y)
{
  int i = func_hash(y->equipa->nome);
  primeiros[i] = insere_inicio_e(primeiros[i], y);
}

link_e procura_equipa(link_e *primeiros, char *nome)
{
  link_e p;
  int i = func_hash(nome);
  p = procura_e(primeiros[i], nome);
  return p;
}

