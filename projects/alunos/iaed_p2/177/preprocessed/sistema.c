#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"
#include "sistema.h"


sistema inicializa_sistema(sistema st1, int m)
{
  int i;
  st1 = (sistema) malloc(sizeof(struct sis));
  st1->tamanho = m;
  st1->elementos = 0;
  st1->v = (sist *) malloc(st1->tamanho * (sizeof(sist)));
  for (i = 0; i < m; i++)
  {
    st1->v[i] = 0;
  }

  return st1;
}

sistema destroi_sistema(sistema st)
{
  int i;
  for (i = 0; i < st->tamanho; i++)
  {
    if (st->v[i] != 0)
    {
      free(st->v[i]->equipa);
      free(st->v[i]);
    }
    else
    {
      
    }

  }

  free(st->v);
  free(st);
  return st;
}

sistema insere_eq(sistema st, char *nome, int ganhos)
{
  int i;
  i = hash(nome, st->tamanho);
  while (st->v[i] != 0)
  {
    i = (i + 1) % st->tamanho;
  }

  st->v[i] = (sist) malloc(sizeof(struct no));
  st->v[i]->ganhos = ganhos;
  st->v[i]->equipa = (char *) malloc((sizeof(char)) * (strlen(nome) + 1));
  strcpy(st->v[i]->equipa, nome);
  return st;
}

sistema re_hash(sistema st, char *nome, int ganhos)
{
  sistema st1 = 0;
  int i;
  st1 = inicializa_sistema(st1, st->tamanho * 2);
  st1->elementos = st->elementos;
  for (i = 0; i < st->tamanho; i++)
  {
    if (st->v[i] != 0)
    {
      st1 = insere_eq(st1, st->v[i]->equipa, st->v[i]->ganhos);
    }
    else
    {
      
    }

  }

  st1 = insere_eq(st1, nome, ganhos);
  st = destroi_sistema(st);
  return st1;
}

sistema insere_equipa(sistema st, char *name, int ganhos)
{
  st->elementos += 1;
  if ((2 * st->elementos) >= st->tamanho)
  {
    st = re_hash(st, name, ganhos);
    return st;
  }
  else
  {
    
  }

  st = insere_eq(st, name, ganhos);
  return st;
}

int pertence_equipa(sistema st1, char *name)
{
  int i;
  i = hash(name, st1->tamanho);
  while (st1->v[i] != 0)
  {
    if (strcmp(st1->v[i]->equipa, name) == 0)
    {
      return 1;
    }
    else
    {
      i = (i + 1) % st1->tamanho;
    }

  }

  return 0;
}

char *vencedor(char *equipa1, char *equipa2, int score1, int score2)
{
  char *vencedor;
  if (score1 > score2)
  {
    vencedor = (char *) malloc((sizeof(char)) * (strlen(equipa1) + 1));
    strcpy(vencedor, equipa1);
    return vencedor;
  }
  else
  {
    if (score1 < score2)
    {
      vencedor = (char *) malloc((sizeof(char)) * (strlen(equipa2) + 1));
      strcpy(vencedor, equipa2);
      return vencedor;
    }
    else
    {
      
    }

  }

  vencedor = (char *) malloc(sizeof(char));
  return vencedor;
}

sistema decrementa_jogos_ganhos(sistema st, char *vencedor)
{
  int e2 = hash(vencedor, st->tamanho);
  while (st->v[e2] != 0)
  {
    if (strcmp(st->v[e2]->equipa, vencedor) == 0)
    {
      st->v[e2]->ganhos -= 1;
      free(vencedor);
      return st;
    }
    else
    {
      e2 = (e2 + 1) % st->tamanho;
    }

  }

  return st;
}

sistema incrementa_jogos_ganhos(sistema st, char *vencedor)
{
  int e2 = hash(vencedor, st->tamanho);
  while (st->v[e2] != 0)
  {
    if (strcmp(st->v[e2]->equipa, vencedor) == 0)
    {
      st->v[e2]->ganhos += 1;
      free(vencedor);
      return st;
    }
    else
    {
      e2 = (e2 + 1) % st->tamanho;
    }

  }

  return st;
}

sistema atualiza_vitoria(sistema st, jogo st1, char *nome, int score1, int score2)
{
  char *vencedor1;
  char *vencedor2;
  int e2;
  e2 = hash(nome, st1->tamanho);
  if (score1 == score2)
  {
    while (st1->v[e2] != 0)
    {
      if ((strcmp(st1->v[e2]->nome, nome) == 0) && (st1->v[e2]->eliminado == 0))
      {
        if (st1->v[e2]->score1 == st1->v[e2]->score2)
        {
          return st;
        }
        else
        {
          
        }

        vencedor1 = vencedor(st1->v[e2]->equipa1, st1->v[e2]->equipa2, st1->v[e2]->score1, st1->v[e2]->score2);
        st = decrementa_jogos_ganhos(st, vencedor1);
        return st;
      }
      else
      {
        e2 = (e2 + 1) % st1->tamanho;
      }

    }

  }
  else
  {
    
  }

  e2 = hash(nome, st1->tamanho);
  while (st1->v[e2] != 0)
  {
    if ((strcmp(st1->v[e2]->nome, nome) == 0) && (st1->v[e2]->eliminado == 0))
    {
      if (st1->v[e2]->score1 == st1->v[e2]->score2)
      {
        vencedor2 = vencedor(st1->v[e2]->equipa1, st1->v[e2]->equipa2, score1, score2);
        st = incrementa_jogos_ganhos(st, vencedor2);
        return st;
      }
      else
      {
        
      }

      vencedor1 = vencedor(st1->v[e2]->equipa1, st1->v[e2]->equipa2, st1->v[e2]->score1, st1->v[e2]->score2);
      vencedor2 = vencedor(st1->v[e2]->equipa1, st1->v[e2]->equipa2, score1, score2);
      break;
    }
    else
    {
      e2 = (e2 + 1) % st1->tamanho;
    }

  }

  if (strcmp(vencedor1, vencedor2) == 0)
  {
    free(vencedor1);
    free(vencedor2);
    return st;
  }
  else
  {
    
  }

  st = incrementa_jogos_ganhos(st, vencedor2);
  st = decrementa_jogos_ganhos(st, vencedor1);
  return st;
}

sistema elimina_vitoria(sistema st, jogo st1, char *nome)
{
  char *vencedor1;
  int e2;
  e2 = hash(nome, st1->tamanho);
  while (st1->v[e2] != 0)
  {
    if ((strcmp(st1->v[e2]->nome, nome) == 0) && (st1->v[e2]->eliminado == 0))
    {
      if (st1->v[e2]->score1 == st1->v[e2]->score2)
      {
        return st;
      }
      else
      {
        
      }

      vencedor1 = vencedor(st1->v[e2]->equipa1, st1->v[e2]->equipa2, st1->v[e2]->score1, st1->v[e2]->score2);
      break;
    }
    else
    {
      e2 = (e2 + 1) % st1->tamanho;
    }

  }

  st = decrementa_jogos_ganhos(st, vencedor1);
  return st;
}

sistema insere_vitoria(sistema st, char *equipa1, char *equipa2, int score1, int score2)
{
  char *vencedor1;
  if (score1 == score2)
  {
    return st;
  }
  else
  {
    
  }

  vencedor1 = vencedor(equipa1, equipa2, score1, score2);
  st = incrementa_jogos_ganhos(st, vencedor1);
  return st;
}

int jogos_ganhos(sistema st1, char *name)
{
  int i;
  int ganhos;
  i = hash(name, st1->tamanho);
  while (st1->v[i] != 0)
  {
    if (strcmp(st1->v[i]->equipa, name) == 0)
    {
      ganhos = st1->v[i]->ganhos;
      return ganhos;
    }
    else
    {
      i = (i + 1) % st1->tamanho;
    }

  }

  return 0;
}

int comparastr(const void *pa, const void *pb)
{
  char **v1;
  char **v2;
  v1 = (char **) pa;
  v2 = (char **) pb;
  return strcmp(*v1, *v2);
}

void tabela(sistema st, int nl)
{
  int i;
  int e;
  int cont = 0;
  int maior = 0;
  int n = 0;
  char **vencedoras;
  for (e = 0; e < st->tamanho; e++)
  {
    if (st->v[e] != 0)
    {
      i = st->v[e]->ganhos;
      if (i > maior)
      {
        maior = i;
        n = 1;
      }
      else
      {
        if (i == maior)
        {
          n += 1;
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

  if (n == 0)
  {
    return;
  }
  else
  {
    
  }

  vencedoras = (char **) malloc((sizeof(char *)) * n);
  for (e = 0; e < st->tamanho; e++)
  {
    if (st->v[e] != 0)
    {
      i = st->v[e]->ganhos;
      if (i == maior)
      {
        vencedoras[cont] = (char *) malloc((sizeof(char)) * (strlen(st->v[e]->equipa) + 1));
        strcpy(vencedoras[cont], st->v[e]->equipa);
        cont += 1;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  qsort(vencedoras, n, sizeof(char *), comparastr);
  printf("%d Melhores %d\n", nl, maior);
  for (cont = 0; cont < n; cont++)
  {
    printf("%d * %s\n", nl, vencedoras[cont]);
    free(vencedoras[cont]);
  }

  free(vencedoras);
  return;
}

