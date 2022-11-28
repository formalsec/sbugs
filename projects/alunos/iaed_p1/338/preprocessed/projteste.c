#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


int idp = 0;
int ide = 0;
int arrayL[10000];
int array[10000];
typedef struct 
{
  int preco;
  int peso;
  int qtd;
  int id;
  char desc[63];
} Produto;
Produto produto[10000];
typedef struct 
{
  Produto prods[200];
  int idpe;
} Encomenda;
Encomenda encomenda[500];
int id_para_idpe(int enc, int id)
{
  int idpe;
  for (idpe = 0; idpe < encomenda[enc].idpe; idpe++)
  {
    if (encomenda[enc].prods[idpe].id == id)
    {
      return idpe;
    }
    else
    {
      
    }

  }

  return encomenda[enc].idpe;
}

void cout(int idp)
{
  int i;
  for (i = 0; i < idp; i++)
  {
    array[i] = i;
  }

}

void coutL(int idpe)
{
  int i;
  for (i = 0; i < idpe; i++)
  {
    arrayL[i] = i;
  }

}

int pesoaux(int enc, int prod, int qua)
{
  int i;
  int peso = 0;
  peso += qua * produto[prod].peso;
  for (i = 0; i < encomenda[enc].idpe; i++)
  {
    peso += encomenda[enc].prods[i].qtd * encomenda[enc].prods[i].peso;
  }

  return peso;
}

void mergel(int a[], int left, int m, int right)
{
  int i;
  int j;
  int k;
  int aux[10000];
  for (i = m + 1; i > left; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = a[j + 1];

  for (k = left; k <= right; k++)
    if ((produto[aux[j]].preco < produto[aux[i]].preco) || (i > m))
  {
    a[k] = aux[j--];
  }
  else
  {
    a[k] = aux[i++];
  }


}

void mergeSortl(int a[], int l, int r)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergeSortl(a, l, m);
    mergeSortl(a, m + 1, r);
    mergel(a, l, m, r);
  }
  else
  {
    
  }

}

void mergeL(int a[], int left, int m, int right, int enc)
{
  int i;
  int j;
  int k;
  int aux[10000];
  for (i = m + 1; i > left; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = a[j + 1];

  for (k = left; k <= right; k++)
    if (strcmp(encomenda[enc].prods[id_para_idpe(enc, aux[j])].desc, encomenda[enc].prods[id_para_idpe(enc, aux[i])].desc) < 0)
  {
    a[k] = aux[j--];
  }
  else
  {
    a[k] = aux[i++];
  }


}

void mergeSortL(int a[], int l, int r, int enc)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergeSortL(a, l, m, enc);
    mergeSortL(a, m + 1, r, enc);
    mergeL(a, l, m, r, enc);
  }
  else
  {
    
  }

}

void funcaoa()
{
  for (int produto_index = 0; produto_index < 10; produto_index++)
  {
    produto[idp].desc[produto_index] = new_sym_var(sizeof(char) * 8);
  }

  produto[idp].desc[10 - 1] = '\0';
  produto[idp].preco = new_sym_var(sizeof(int) * 8);
  produto[idp].peso = new_sym_var(sizeof(int) * 8);
  produto[idp].qtd = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", idp);
  idp++;
}

void funcaoq()
{
  int prod;
  int addstock;
  prod = new_sym_var(sizeof(int) * 8);
  addstock = new_sym_var(sizeof(int) * 8);
  if (prod >= idp)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prod);
  }
  else
  {
    produto[prod].qtd += addstock;
  }

}

void funcaoN()
{
  printf("Nova encomenda %d.\n", ide);
  encomenda[ide].idpe = 0;
  ide++;
}

void funcaoA()
{
  int enc;
  int prod;
  int quant;
  enc = new_sym_var(sizeof(int) * 8);
  prod = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  if (enc >= ide)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
  }
  else
  {
    if (prod >= idp)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
    }
    else
    {
      if ((produto[prod].qtd - quant) < 0)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prod, enc);
      }
      else
      {
        if (pesoaux(enc, prod, quant) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prod, enc);
        }
        else
        {
          if (encomenda[enc].prods[id_para_idpe(enc, prod)].qtd == 0)
          {
            encomenda[enc].prods[id_para_idpe(enc, prod)].qtd += quant;
            encomenda[enc].prods[id_para_idpe(enc, prod)].preco = produto[prod].preco;
            encomenda[enc].prods[id_para_idpe(enc, prod)].peso = produto[prod].peso;
            strcpy(encomenda[enc].prods[id_para_idpe(enc, prod)].desc, produto[prod].desc);
            encomenda[enc].prods[id_para_idpe(enc, prod)].id = prod;
            produto[prod].qtd -= quant;
            encomenda[enc].idpe++;
          }
          else
          {
            encomenda[enc].prods[id_para_idpe(enc, prod)].qtd += quant;
            produto[prod].qtd -= quant;
          }

        }

      }

    }

  }

}

void funcaor()
{
  int prod;
  int remstock;
  prod = new_sym_var(sizeof(int) * 8);
  remstock = new_sym_var(sizeof(int) * 8);
  if (prod >= idp)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod);
  }
  else
  {
    if ((produto[prod].qtd - remstock) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", remstock, prod);
    }
    else
    {
      produto[prod].qtd -= remstock;
    }

  }

}

void funcaoR()
{
  int enc;
  int prod;
  enc = new_sym_var(sizeof(int) * 8);
  prod = new_sym_var(sizeof(int) * 8);
  if (enc >= ide)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
  }
  else
  {
    if (prod >= idp)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
    }
    else
    {
      produto[prod].qtd += encomenda[enc].prods[id_para_idpe(enc, prod)].qtd;
      encomenda[enc].prods[id_para_idpe(enc, prod)].qtd = 0;
    }

  }

}

void funcaoC()
{
  int enc;
  int preco = 0;
  int i;
  enc = new_sym_var(sizeof(int) * 8);
  if (enc >= ide)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", enc);
  }
  else
  {
    for (i = 0; i < encomenda[enc].idpe; i++)
    {
      preco += produto[encomenda[enc].prods[i].id].preco * encomenda[enc].prods[i].qtd;
    }

    printf("Custo da encomenda %d %d.\n", enc, preco);
  }

}

void funcaop()
{
  int prod;
  int mudpreco;
  int i;
  prod = new_sym_var(sizeof(int) * 8);
  mudpreco = new_sym_var(sizeof(int) * 8);
  if (prod >= idp)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", prod);
  }
  else
  {
    produto[prod].preco = mudpreco;
    for (i = 0; i < ide; i++)
    {
      encomenda[i].prods[id_para_idpe(i, prod)].preco = mudpreco;
    }

  }

}

void funcaoE()
{
  int enc;
  int prod;
  enc = new_sym_var(sizeof(int) * 8);
  prod = new_sym_var(sizeof(int) * 8);
  if (enc >= ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
  }
  else
  {
    if (prod >= idp)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", prod);
    }
    else
    {
      printf("%s %d.\n", produto[prod].desc, encomenda[enc].prods[id_para_idpe(enc, prod)].qtd);
    }

  }

}

void funcaom()
{
  int prod;
  int i;
  int maior = 0;
  int imaior = 0;
  prod = new_sym_var(sizeof(int) * 8);
  if (prod >= idp)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prod);
  }
  else
  {
    for (i = 0; i < ide; i++)
    {
      if (encomenda[i].prods[id_para_idpe(i, prod)].qtd > maior)
      {
        maior = encomenda[i].prods[id_para_idpe(i, prod)].qtd;
        imaior = i;
      }
      else
      {
        
      }

    }

    if (maior > 0)
    {
      printf("Maximo produto %d %d %d.\n", prod, imaior, maior);
    }
    else
    {
      
    }

  }

}

void funcaol()
{
  int i;
  cout(idp);
  mergeSortl(array, 0, idp - 1);
  printf("Produtos\n");
  for (i = 0; i < idp; i++)
  {
    printf("* %s %d %d\n", produto[array[i]].desc, produto[array[i]].preco, produto[array[i]].qtd);
  }

}

void funcaoL()
{
  int i;
  int enc;
  int id;
  enc = new_sym_var(sizeof(int) * 8);
  if (enc >= ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
  }
  else
  {
    coutL(idp);
    mergeSortL(arrayL, 0, idp - 1, enc);
    printf("Encomenda %d\n", enc);
    for (i = 0; i < idp; i++)
    {
      id = id_para_idpe(enc, arrayL[i]);
      if (encomenda[enc].prods[id].qtd > 0)
      {
        printf("* %s %d %d\n", produto[encomenda[enc].prods[id].id].desc, produto[encomenda[enc].prods[id].id].preco, encomenda[enc].prods[id].qtd);
      }
      else
      {
        
      }

    }

  }

}

int main()
{
  char comando;
  while (1)
  {
    comando = new_sym_var(sizeof(char) * 8);
    switch (comando)
    {
      case 'a':
        funcaoa();
        break;

      case 'q':
        funcaoq();
        break;

      case 'N':
        funcaoN();
        break;

      case 'A':
        funcaoA();
        break;

      case 'r':
        funcaor();
        break;

      case 'R':
        funcaoR();
        break;

      case 'C':
        funcaoC();
        break;

      case 'p':
        funcaop();
        break;

      case 'E':
        funcaoE();
        break;

      case 'm':
        funcaom();
        break;

      case 'l':
        funcaol();
        break;

      case 'L':
        funcaoL();
        break;

      case 'x':
        return 0;

    }

  }

  return 0;
}
