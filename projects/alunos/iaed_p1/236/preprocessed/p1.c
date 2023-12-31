#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct 
{
  int idProd;
  char descricao[64];
  int preco;
  int peso;
  int quantidade;
} Produto;
typedef struct 
{
  int idEnc;
  int peso;
  Produto product[10000];
} Encomenda;
void add_produto(char [], Produto [10000]);
void add_qtd(char [], Produto [10000]);
void new_encomenda(Encomenda [500]);
void add_encomenda(char [], Encomenda [500], Produto [10000]);
void remove_qtd(char [], Produto [10000]);
void remove_produto(char [], Encomenda [500], Produto [10000]);
void calc_custo(char [], Encomenda [500]);
void altera_preco(char [], Produto [10000]);
void lista_descricao(char [], Encomenda [500], Produto [10000]);
void listar_produto(Produto [10000]);
int check_idProd(int, Produto [10000], int);
int check_idEnc(int, Encomenda [500], int);
int check_peso(int, int);
void produto_vazio(Produto [10000]);
void ordena_produto(Produto [1024], int);
void print_infoP(Produto [1024], int);
int main()
{
  int running = 1;
  char command = '0';
  char input[1024];
  Produto prod[10000];
  Encomenda enc[500];
  produto_vazio(prod);
  while (running == 1)
  {
    fgets(input, 1024, stdin);
    command = input[0];
    switch (command)
    {
      case 'a':
        add_produto(input, prod);
        break;

      case 'q':
        add_qtd(input, prod);
        break;

      case 'N':
        new_encomenda(enc);
        break;

      case 'A':
        add_encomenda(input, enc, prod);
        break;

      case 'r':
        remove_qtd(input, prod);
        break;

      case 'R':
        remove_produto(input, enc, prod);
        break;

      case 'C':
        calc_custo(input, enc);
        break;

      case 'p':
        altera_preco(input, prod);
        break;

      case 'E':
        lista_descricao(input, enc, prod);
        break;

      case 'l':
        listar_produto(prod);
        break;

      case 'x':
        running = 0;
        break;

      default:
        printf("Invalid command\n");

    }

  }

  return 0;
}

int check_idProd(int idProd, Produto prod[10000], int sinal)
{
  int i;
  for (i = 0; i < 10000; i++)
  {
    if (idProd == prod[i].idProd)
    {
      return sinal = 1;
    }
    else
    {
      
    }

  }

  return sinal = 0;
}

int check_idEnc(int idEnc, Encomenda enc[500], int sinal)
{
  int i;
  for (i = 0; i < 500; i++)
  {
    if (idEnc == enc[i].idEnc)
    {
      return sinal = 1;
    }
    else
    {
      
    }

  }

  return sinal = 0;
}

int check_peso(int peso, int sinal)
{
  int i;
  for (i = 0; i < 500; i++)
  {
    if (peso > 200)
    {
      return sinal = 0;
    }
    else
    {
      
    }

  }

  return sinal = 1;
}

void produto_vazio(Produto prod[10000])
{
  int i;
  for (i = 0; i < 10000; i++)
    strcpy(prod[i].descricao, "VAZIO");

}

void ordena_produto(Produto aux[1024], int n)
{
  Produto save;
  save = aux[n];
  aux[n] = aux[n - 1];
  aux[n - 1] = save;
}

void add_produto(char input[], Produto prod[10000])
{
  Produto new;
  int i;
  for (int new_index = 0; new_index < 10; new_index++)
  {
    new.descricao[new_index] = new_sym_var(sizeof(char) * 8);
  }

  new.descricao[10 - 1] = '\0';
  new.preco = new_sym_var(sizeof(int) * 8);
  new.peso = new_sym_var(sizeof(int) * 8);
  new.quantidade = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < 10000; i++)
  {
    if (strcmp(prod[i].descricao, "VAZIO") == 0)
    {
      prod[i] = new;
      printf("Novo Produto %d.\n", new.idProd);
      break;
    }
    else
    {
      
    }

  }

}

void add_qtd(char input[], Produto prod[10000])
{
  int qtd;
  int sinal = 0;
  int idp;
  int i;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  sinal = check_idProd(idp, prod, sinal);
  if (sinal == 0)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

  for (i = 0; i < 10000; i++)
  {
    if (prod[i].idProd == idp)
    {
      prod[i].quantidade += qtd;
    }
    else
    {
      
    }

  }

}

void new_encomenda(Encomenda enc[500])
{
  int i;
  Encomenda new;
  memset(&new, 0, sizeof(new));
  for (i = 0; i < 500; i++)
  {
    enc[i] = new;
    new.idEnc = i;
    printf("Nova encomenda %d.\n", new.idEnc);
    break;
  }

}

void add_encomenda(char input[], Encomenda enc[500], Produto prod[10000])
{
  int ide;
  int idp;
  int qtd;
  int sinalE = 0;
  int sinalP = 0;
  int peso_aux;
  int cp;
  int i;
  int j;
  int k;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  sinalE = check_idEnc(ide, enc, sinalE);
  if (sinalE == 0)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    
  }

  sinalP = check_idProd(idp, prod, sinalP);
  if (sinalP == 0)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  }
  else
  {
    
  }

  for (i = 0; i < 500; i++)
  {
    if (enc[i].idEnc == ide)
    {
      for (k = 0; k < 10000; k++)
      {
        if (enc[i].product[k].idProd == idp)
        {
          enc[i].product[k].quantidade += qtd;
        }
        else
        {
          
        }

      }

      for (j = 0; j < 10000; j++)
      {
        if (prod[j].idProd == idp)
        {
          peso_aux = prod[j].peso;
          if (prod[j].quantidade >= qtd)
          {
            enc[i].product[j] = prod[j];
            prod[j].quantidade -= qtd;
          }
          else
          {
            if (prod[j].quantidade < qtd)
            {
              printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
            }
            else
            {
              
            }

          }

          cp = check_peso(peso_aux, cp);
          if (cp == 1)
          {
            int pt = enc[i].peso;
            pt += peso_aux;
            if (pt > 200)
            {
              printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
            }
            else
            {
              if (cp != 1)
              {
                enc[i].peso = pt;
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

    }
    else
    {
      
    }

  }

}

void remove_qtd(char input[], Produto prod[10000])
{
  int idp;
  int qtd;
  int sinal = 0;
  int i;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  sinal = check_idProd(idp, prod, sinal);
  if (sinal == 0)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

  for (i = 0; i < 10000; i++)
  {
    if (prod[i].idProd == idp)
    {
      if (prod[i].quantidade >= qtd)
      {
        prod[i].quantidade -= qtd;
      }
      else
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
      }

    }
    else
    {
      
    }

  }

}

void remove_produto(char input[], Encomenda enc[500], Produto prod[10000])
{
  int ide;
  int idp;
  int sinalE = 0;
  int sinalP = 0;
  int i;
  int j;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  sinalE = check_idEnc(ide, enc, sinalE);
  if (sinalE == 0)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    
  }

  sinalP = check_idProd(idp, prod, sinalP);
  if (sinalP == 0)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  }
  else
  {
    
  }

  for (i = 0; i < 500; i++)
  {
    if (enc[i].idEnc == ide)
    {
      for (j = 0; j < 10000; j++)
      {
        if (enc[i].product[j].idProd == idp)
        {
          enc[i].product[j] = enc[i].product[j + 1];
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

void calc_custo(char input[], Encomenda enc[500])
{
  int ide;
  int sinal = 0;
  int i;
  int j;
  int total;
  ide = new_sym_var(sizeof(int) * 8);
  sinal = check_idEnc(ide, enc, sinal);
  if (sinal == 0)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    
  }

  for (i = 0; i < 500; i++)
  {
    if (enc[i].idEnc == ide)
    {
      for (j = 0; j < 10000; j++)
      {
        total += enc[i].product[j].preco;
      }

    }
    else
    {
      
    }

  }

  printf("Custo da encomenda %d %d.\n", ide, total);
}

void altera_preco(char input[], Produto prod[10000])
{
  int idp;
  int novo_preco;
  int i;
  int sinal = 0;
  idp = new_sym_var(sizeof(int) * 8);
  novo_preco = new_sym_var(sizeof(int) * 8);
  sinal = check_idProd(idp, prod, sinal);
  if (sinal == 0)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

  for (i = 0; i < 10000; i++)
  {
    if (prod[i].idProd == idp)
    {
      prod[i].preco = novo_preco;
    }
    else
    {
      
    }

  }

}

void lista_descricao(char input[], Encomenda enc[500], Produto prod[10000])
{
  int ide;
  int idp;
  int sinalE = 0;
  int sinalP = 0;
  int qtd;
  int i;
  int j;
  char nome[64] = "";
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  sinalE = check_idEnc(ide, enc, sinalE);
  if (sinalE == 0)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    
  }

  sinalP = check_idProd(idp, prod, sinalP);
  if (sinalP == 0)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

  for (i = 0; i < 500; i++)
  {
    if (enc[i].idEnc == ide)
    {
      for (j = 0; j < 10000; j++)
      {
        if (enc[i].product[j].idProd == idp)
        {
          strcpy(nome, enc[i].product[j].descricao);
          qtd = enc[i].product[j].quantidade;
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

  printf("%s %d\n", nome, qtd);
}

void listar_produto(Produto prod[10000])
{
  int i;
  int l = 0;
  Produto aux[10000];
  for (i = 0; i < 10000; i++)
  {
    if (strcmp(prod[i].descricao, "VAZIO") != 0)
    {
      aux[l] = prod[i];
      l++;
    }
    else
    {
      
    }

  }

  print_infoP(aux, l);
}

void print_infoP(Produto aux[1024], int l)
{
  int n;
  int i;
  int preco;
  int max_preco;
  int id;
  int max_id;
  for (i = 1; i < l; i++)
  {
    n = i;
    while (n > 0)
    {
      preco = aux[n].preco;
      max_preco = aux[n - 1].preco;
      id = aux[n].idProd;
      max_id = aux[n - 1].idProd;
      if (preco > max_preco)
      {
        ordena_produto(aux, n);
        n--;
      }
      else
      {
        
      }

      if ((preco == max_preco) && (id > max_id))
      {
        ordena_produto(aux, n);
        n--;
      }
      else
      {
        
      }

      break;
    }

  }

  printf("Produtos\n");
  for (i = 0; i < l; i++)
  {
    printf("* %s %d %d em stock\n", aux[i].descricao, aux[i].preco, aux[i].quantidade);
  }

}

