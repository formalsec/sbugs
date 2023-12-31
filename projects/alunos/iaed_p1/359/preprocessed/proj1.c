#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct Produto
{
  long int idp;
  char desc[63];
  int preco;
  int peso;
  int qtd;
} produto;
typedef struct Encomenda
{
  int ide;
  int peso;
  produto lista[200];
} encomenda;
produto sistemaprod[10000];
encomenda sistemaenc[500];
produto aux[10000];
encomenda auxenc[500];
void inicializa()
{
  int i;
  for (i = 0; i < 500; i++)
  {
    sistemaenc[i].ide = -1;
  }

  for (i = 0; i < 10000; i++)
  {
    sistemaprod[i].preco = -1;
    sistemaprod[i].idp = -1;
  }

}

produto novoprod(int contador)
{
  produto novo;
  novo.idp = contador;
  for (int novo_index = 0; novo_index < 10; novo_index++)
  {
    novo.desc[novo_index] = new_sym_var(sizeof(char) * 8);
  }

  novo.desc[10 - 1] = '\0';
  novo.preco = new_sym_var(sizeof(int) * 8);
  novo.peso = new_sym_var(sizeof(int) * 8);
  novo.qtd = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", contador);
  return novo;
}

encomenda novaencomenda(int contador)
{
  int i;
  encomenda novo;
  novo.ide = contador;
  novo.peso = 0;
  for (i = 0; i < 200; i++)
  {
    novo.lista[i].idp = -1;
    novo.lista[i].preco = -1;
    novo.lista[i].qtd = 0;
    novo.lista[i].peso = 0;
  }

  printf("Nova encomenda %d.\n", contador);
  return novo;
}

void adicionastock()
{
  int i;
  int id;
  int qtd;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < 10000; i++)
  {
    if (sistemaprod[i].idp == id)
    {
      sistemaprod[i].qtd += qtd;
      return;
    }
    else
    {
      
    }

  }

  printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
}

int verificaaux(int ide, int idp, char operacao[])
{
  int i;
  int estado = 0;
  for (i = 0; i < 500; i++)
  {
    if (sistemaenc[i].ide >= 0)
    {
      if (sistemaenc[i].ide == ide)
      {
        estado = 1;
        break;
      }
      else
      {
        
      }

    }
    else
    {
      break;
    }

  }

  if (estado)
  {
    for (i = 0; i < 10000; i++)
    {
      if (sistemaprod[i].preco >= 0)
      {
        if (sistemaprod[i].idp == idp)
        {
          return 1;
        }
        else
        {
          
        }

      }
      else
      {
        break;
      }

    }

    if (strcmp(operacao, "listar") != 0)
    {
      printf("Impossivel %s produto %d a encomenda %d. Produto inexistente.\n", operacao, idp, ide);
    }
    else
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }

  }
  else
  {
    if (strcmp(operacao, "listar") != 0)
    {
      printf("Impossivel %s produto %d a encomenda %d. Encomenda inexistente.\n", operacao, idp, ide);
    }
    else
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }

  }

  return 0;
}

int adicionaprod_aux(int ide, int idp, int qtd)
{
  int i;
  int r;
  for (i = 0; i < 10000; i++)
  {
    if (sistemaprod[i].idp >= 0)
    {
      if (sistemaprod[i].idp == idp)
      {
        if (sistemaprod[i].qtd < qtd)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
          return 0;
        }
        else
        {
          
        }

        for (r = 0; r < 500; r++)
        {
          if (sistemaenc[r].ide >= 0)
          {
            if (sistemaenc[r].ide == ide)
            {
              if ((sistemaenc[r].peso + (sistemaprod[i].peso * qtd)) > 200)
              {
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
                return 0;
              }
              else
              {
                
              }

            }
            else
            {
              
            }

          }
          else
          {
            break;
          }

        }

      }
      else
      {
        
      }

    }
    else
    {
      break;
    }

  }

  return 1;
}

void adicionaprod()
{
  int i;
  int r;
  int idp;
  int ide;
  int indaux;
  int indaux_enc;
  int qtd;
  produto aux;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (verificaaux(ide, idp, "adicionar"))
  {
    if (adicionaprod_aux(ide, idp, qtd))
    {
      for (i = 0; i < 10000; i++)
      {
        if (sistemaprod[i].idp == idp)
        {
          indaux = i;
          break;
        }
        else
        {
          
        }

      }

      for (i = 0; i < 500; i++)
      {
        if (sistemaenc[i].ide == ide)
        {
          for (r = 0; r < 200; r++)
          {
            if (sistemaenc[i].lista[r].idp == idp)
            {
              sistemaenc[i].lista[r].qtd += qtd;
              sistemaprod[indaux].qtd -= qtd;
              sistemaenc[i].peso += sistemaprod[indaux].peso * qtd;
              return;
            }
            else
            {
              
            }

          }

          for (r = 0; r < 200; r++)
          {
            if (sistemaenc[i].lista[r].qtd == 0)
            {
              indaux_enc = r;
              break;
            }
            else
            {
              
            }

          }

          aux = sistemaprod[indaux];
          aux.qtd = qtd;
          sistemaenc[i].lista[indaux_enc] = aux;
          sistemaprod[indaux].qtd -= qtd;
          sistemaenc[i].peso += aux.peso * aux.qtd;
          return;
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
  else
  {
    
  }

}

void removestock()
{
  int i;
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < 10000; i++)
  {
    if (sistemaprod[i].idp >= 0)
    {
      if (sistemaprod[i].idp == idp)
      {
        if (sistemaprod[i].qtd >= qtd)
        {
          sistemaprod[i].qtd -= qtd;
          return;
        }
        else
        {
          
        }

        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
      }
      else
      {
        
      }

    }
    else
    {
      break;
    }

  }

  printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
}

void removeprodencomenda()
{
  int i;
  int r;
  int ide;
  int idp;
  int indaux;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (verificaaux(ide, idp, "remover"))
  {
    for (i = 0; i < 10000; i++)
    {
      if (sistemaprod[i].idp >= 0)
      {
        if (sistemaprod[i].idp == idp)
        {
          indaux = i;
          break;
        }
        else
        {
          
        }

      }
      else
      {
        break;
      }

    }

    for (r = 0; r < 500; r++)
    {
      if (sistemaenc[r].ide >= 0)
      {
        if (sistemaenc[r].ide == ide)
        {
          for (i = 0; i < 200; i++)
          {
            if (sistemaenc[r].lista[i].idp >= 0)
            {
              if (sistemaenc[r].lista[i].idp == idp)
              {
                sistemaenc[r].peso -= sistemaenc[r].lista[i].qtd * sistemaprod[indaux].peso;
                sistemaprod[indaux].qtd += sistemaenc[r].lista[i].qtd;
                sistemaenc[r].lista[i].qtd = 0;
                return;
              }
              else
              {
                
              }

            }
            else
            {
              break;
            }

          }

        }
        else
        {
          
        }

      }
      else
      {
        break;
      }

    }

  }
  else
  {
    
  }

}

void custoencomenda()
{
  int i;
  int r;
  int ide;
  int custo = 0;
  ide = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < 500; i++)
  {
    if (sistemaenc[i].ide >= 0)
    {
      if (sistemaenc[i].ide == ide)
      {
        for (r = 0; r < 200; r++)
        {
          if (sistemaenc[i].lista[r].preco > 0)
          {
            custo += sistemaenc[i].lista[r].qtd * sistemaenc[i].lista[r].preco;
          }
          else
          {
            break;
          }

        }

        printf("Custo da encomenda %d %d.\n", ide, custo);
        return;
      }
      else
      {
        
      }

    }
    else
    {
      break;
    }

  }

  printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
}

void alterapreco()
{
  int idp;
  int preco;
  int i;
  int r;
  int estado = 1;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < 10000; i++)
  {
    if (sistemaprod[i].preco > 0)
    {
      if (sistemaprod[i].idp == idp)
      {
        estado = 0;
        sistemaprod[i].preco = preco;
      }
      else
      {
        
      }

    }
    else
    {
      break;
    }

  }

  if (estado)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (i = 0; i < 500; i++)
    {
      if (sistemaenc[i].ide >= 0)
      {
        for (r = 0; r < 200; r++)
        {
          if (sistemaenc[i].lista[r].idp >= 0)
          {
            if (sistemaenc[i].lista[r].idp == idp)
            {
              sistemaenc[i].lista[r].preco = preco;
            }
            else
            {
              
            }

          }
          else
          {
            break;
          }

        }

      }
      else
      {
        break;
      }

    }

  }

}

void prodsencomenda()
{
  int i;
  int r;
  int idp;
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (verificaaux(ide, idp, "listar"))
  {
    for (r = 0; r < 500; r++)
    {
      if (sistemaenc[r].ide >= 0)
      {
        if (sistemaenc[r].ide == ide)
        {
          for (i = 0; i < 200; i++)
          {
            if (sistemaenc[r].lista[i].idp >= 0)
            {
              if (sistemaenc[r].lista[i].idp == idp)
              {
                printf("%s %d.\n", sistemaenc[r].lista[i].desc, sistemaenc[r].lista[i].qtd);
                return;
              }
              else
              {
                
              }

            }
            else
            {
              break;
            }

          }

        }
        else
        {
          
        }

      }
      else
      {
        break;
      }

    }

    for (i = 0; i < 10000; i++)
    {
      if (sistemaprod[i].idp >= 0)
      {
        if (sistemaprod[i].idp == idp)
        {
          printf("%s 0.\n", sistemaprod[i].desc);
          return;
        }
        else
        {
          
        }

      }
      else
      {
        break;
      }

    }

  }
  else
  {
    
  }

}

void nrprodmax()
{
  int max = 0;
  int maxide;
  int i;
  int r;
  int idp;
  int estado = 0;
  idp = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < 10000; i++)
  {
    if (sistemaprod[i].idp >= 0)
    {
      if (sistemaprod[i].idp == idp)
      {
        estado = 1;
        break;
      }
      else
      {
        
      }

    }
    else
    {
      break;
    }

  }

  if (estado)
  {
    for (i = 0; i < 500; i++)
    {
      if (sistemaenc[i].ide >= 0)
      {
        for (r = 0; r < 200; r++)
        {
          if (sistemaenc[i].lista[r].qtd >= 0)
          {
            if ((sistemaenc[i].lista[r].idp == idp) && (sistemaenc[i].lista[r].qtd > max))
            {
              max = sistemaenc[i].lista[r].qtd;
              maxide = i;
              break;
            }
            else
            {
              
            }

          }
          else
          {
            break;
          }

        }

      }
      else
      {
        break;
      }

    }

  }
  else
  {
    
  }

  if (estado == 0)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (max > 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, maxide, max);
    }
    else
    {
      
    }

  }

}

void mergeprods(int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
  {
    aux[i - 1] = sistemaprod[i - 1];
  }

  for (j = m; j < r; j++)
  {
    aux[(r + m) - j] = sistemaprod[j + 1];
  }

  for (k = l; k <= r; k++)
  {
    if (aux[j].preco < aux[i].preco)
    {
      sistemaprod[k] = aux[j--];
    }
    else
    {
      if ((aux[j].preco == aux[i].preco) && (aux[j].idp < aux[i].idp))
      {
        ;
        sistemaprod[k] = aux[j--];
      }
      else
      {
        sistemaprod[k] = aux[i++];
      }

    }

  }

}

void ordena_prod(int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  ordena_prod(l, m);
  ordena_prod(m + 1, r);
  mergeprods(l, m, r);
}

void todosprod()
{
  int i;
  int r = 10000 - 1;
  for (i = 0; i < 10000; i++)
  {
    if (sistemaprod[i].idp == (-1))
    {
      r = i - 1;
      break;
    }
    else
    {
      
    }

  }

  ordena_prod(0, r);
  printf("Produtos\n");
  for (i = 0; i <= r; i++)
  {
    printf("* %s %d %d\n", sistemaprod[i].desc, sistemaprod[i].preco, sistemaprod[i].qtd);
  }

}

void merge_enc(int ide, int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
  {
    auxenc[ide].lista[i - 1] = sistemaenc[ide].lista[i - 1];
  }

  for (j = m; j < r; j++)
  {
    auxenc[ide].lista[(r + m) - j] = sistemaenc[ide].lista[j + 1];
  }

  for (k = l; k <= r; k++)
  {
    if (strcmp(auxenc[ide].lista[j].desc, auxenc[ide].lista[i].desc) < 0)
    {
      sistemaenc[ide].lista[k] = auxenc[ide].lista[j--];
    }
    else
    {
      sistemaenc[ide].lista[k] = auxenc[ide].lista[i++];
    }

  }

}

void ordena_encomenda(int ide, int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  ordena_encomenda(ide, l, m);
  ordena_encomenda(ide, m + 1, r);
  merge_enc(ide, l, m, r);
}

void tdsprosencomenda()
{
  int i;
  int r = 200 - 1;
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < 200; i++)
  {
    if (sistemaenc[ide].lista[i].idp == (-1))
    {
      r = i - 1;
      break;
    }
    else
    {
      
    }

  }

  ordena_encomenda(ide, 0, r);
  for (i = 0; i < 500; i++)
  {
    if (sistemaenc[i].ide == ide)
    {
      printf("Encomenda %d\n", ide);
      for (r = 0; r < 200; r++)
      {
        if (sistemaenc[i].lista[r].qtd > 0)
        {
          printf("* %s %d %d\n", sistemaenc[i].lista[r].desc, sistemaenc[i].lista[r].preco, sistemaenc[i].lista[r].qtd);
        }
        else
        {
          
        }

      }

      return;
    }
    else
    {
      
    }

  }

  printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}

int main()
{
  int in;
  int nrprod = 0;
  int nrenc = 0;
  inicializa();
  while ((in = getchar()) != 'x')
  {
    switch (in)
    {
      case 'a':
        sistemaprod[nrprod] = novoprod(nrprod);
        nrprod++;
        break;

      case 'q':
        adicionastock();
        break;

      case 'N':
        sistemaenc[nrenc] = novaencomenda(nrenc);
        nrenc++;
        break;

      case 'A':
        adicionaprod();
        break;

      case 'r':
        removestock();
        break;

      case 'R':
        removeprodencomenda();
        break;

      case 'C':
        custoencomenda();
        break;

      case 'p':
        alterapreco();
        break;

      case 'E':
        prodsencomenda();
        break;

      case 'm':
        nrprodmax();
        break;

      case 'l':
        todosprod();
        break;

      case 'L':
        tdsprosencomenda();
        break;

    }

  }

  return 0;
}

