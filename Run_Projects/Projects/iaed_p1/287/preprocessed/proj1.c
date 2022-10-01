/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  int identificador;
  char descricao[63];
  int preco;
  int peso;
  int stock;
} produto;
typedef struct 
{
  int identificador;
  int peso;
  int produtos[200][2];
} encomenda;
produto vec_prod[10000];
encomenda vec_encomendas[500];
void apaga_letra_comando(char input[])
{
  int i;
  int tamanho = strlen(input);
  for (i = 2; i < tamanho; i++)
  {
    input[i - 2] = input[i];
  }

  input[i - 2] = '\0';
}

void separa_input(char input[], char dados[][63])
{
  int i = 0;
  int e = 0;
  int o = 0;
  while (input[o] != '\0')
  {
    if (input[o] == ':')
    {
      dados[i][e] = '\0';
      e = 0;
      i++;
    }
    else
    {
      dados[i][e] = input[o];
      e++;
    }

    o++;
  }

  dados[i][e] = '\0';
}

int str_para_int(char input[])
{
  int resultado = 0;
  int i;
  int p;
  p = strlen(input);
  for (i = 0; i < p; i++)
  {
    resultado = (resultado * 10) + (input[i] - '0');
  }

  return resultado;
}

void merge(int a[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  int aux[10000];
  for (i = m + 1; i > l; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < r; j++)
    aux[(r + m) - j] = a[j + 1];

  for (k = l; k <= r; k++)
    if (((aux[j] - aux[i]) < 0) || (i > m))
  {
    a[k] = aux[j--];
  }
  else
  {
    a[k] = aux[i++];
  }


}

void merge_sort(int a[], int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  merge_sort(a, l, m);
  merge_sort(a, m + 1, r);
  merge(a, l, m, r);
}

void merge_funcao_L(int a[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  int aux[200];
  for (i = m + 1; i > l; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < r; j++)
    aux[(r + m) - j] = a[j + 1];

  for (k = l; k <= r; k++)
  {
    if (strcmp(vec_prod[j].descricao, vec_prod[i].descricao) < 0)
    {
      a[k] = aux[j--];
    }
    else
    {
      a[k] = aux[i++];
    }

  }

}

void merge_sort_funcao_L(int a[], int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  merge_sort_funcao_L(a, l, m);
  merge_sort_funcao_L(a, m + 1, r);
  merge_funcao_L(a, l, m, r);
}

void adicionanovoproduto(char input[])
{
  int i;
  int e;
  int euros = 0;
  int kg = 0;
  int quantidade = 0;
  char dados[4][63];
  apaga_letra_comando(input);
  separa_input(input, dados);
  euros = str_para_int(dados[1]);
  kg = str_para_int(dados[2]);
  quantidade = str_para_int(dados[3]);
  for (e = 0; e < 10000; e++)
  {
    if (vec_prod[e].preco == (-1))
    {
      vec_prod[e].preco = euros;
      vec_prod[e].peso = kg;
      vec_prod[e].stock = quantidade;
      vec_prod[e].identificador = e;
      for (i = 0; i < 63; i++)
      {
        vec_prod[e].descricao[i] = dados[0][i];
      }

      vec_prod[e].descricao[i] = '\0';
      break;
    }
    else
    {
      
    }

  }

  printf("Novo produto %d.\n", vec_prod[e].identificador);
}

void adicionastock(char input[])
{
  char dados[2][63];
  int quantidade;
  int idp;
  apaga_letra_comando(input);
  separa_input(input, dados);
  idp = str_para_int(dados[0]);
  quantidade = str_para_int(dados[1]);
  if (vec_prod[idp].identificador == idp)
  {
    vec_prod[idp].stock += quantidade;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }

}

void remove_stock(char input[])
{
  char dados[2][63];
  int quantidade;
  int idp;
  apaga_letra_comando(input);
  separa_input(input, dados);
  idp = str_para_int(dados[0]);
  quantidade = str_para_int(dados[1]);
  if (vec_prod[idp].identificador == idp)
  {
    if (vec_prod[idp].stock >= quantidade)
    {
      vec_prod[idp].stock -= quantidade;
    }
    else
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
    }

  }
  else
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }

}

void altera_preco(char input[])
{
  char dados[2][63];
  int euros;
  int idp;
  apaga_letra_comando(input);
  separa_input(input, dados);
  idp = str_para_int(dados[0]);
  euros = str_para_int(dados[1]);
  if (vec_prod[idp].identificador == idp)
  {
    vec_prod[idp].preco = euros;
  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }

}

void ordena_produtos_sistema()
{
  int vetor_precos[10000];
  int i;
  int p = 0;
  int contador = 0;
  int e;
  int m;
  int l;
  for (i = 0; i < 10000; i++)
  {
    vetor_precos[i] = -1;
  }

  for (i = 0; i < 10000; i++)
  {
    if (vec_prod[i].preco != (-1))
    {
      vetor_precos[p] = vec_prod[i].preco;
      p++;
    }
    else
    {
      
    }

  }

  for (i = 0; i < 10000; i++)
  {
    if (vetor_precos[i] != (-1))
    {
      contador++;
    }
    else
    {
      
    }

  }

  merge_sort(vetor_precos, 0, contador - 1);
  printf("Produtos\n");
  for (e = 0; e < contador; e++)
  {
    for (i = 0; i < 10000; i++)
    {
      if (vetor_precos[e] != vetor_precos[e - 1])
      {
        if (vec_prod[i].preco == vetor_precos[e])
        {
          printf("* ");
          l = strlen(vec_prod[i].descricao);
          for (m = 0; m < l; m++)
          {
            putchar(vec_prod[i].descricao[m]);
          }

          printf(" %d %d\n", vec_prod[i].preco, vec_prod[i].stock);
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

}

void cria_encomenda()
{
  int i;
  for (i = 0; i < 500; i++)
  {
    if (vec_encomendas[i].identificador == (-1))
    {
      vec_encomendas[i].identificador = i;
      vec_encomendas[i].peso = 0;
      break;
    }
    else
    {
      
    }

  }

  printf("Nova encomenda %d.\n", vec_encomendas[i].identificador);
}

void adiciona_prod_encomenda(char input[])
{
  char dados[3][63];
  int ide;
  int idp;
  int quantidade;
  int i;
  int contador = 0;
  int e;
  int contador2 = 0;
  int contador3 = 0;
  int contador4 = 0;
  int peso_prod;
  int peso_enc;
  int contador5 = 0;
  apaga_letra_comando(input);
  separa_input(input, dados);
  ide = str_para_int(dados[0]);
  idp = str_para_int(dados[1]);
  quantidade = str_para_int(dados[2]);
  for (i = 0; i < 500; i++)
  {
    if (vec_encomendas[i].identificador == ide)
    {
      contador++;
      peso_enc = vec_encomendas[i].peso;
    }
    else
    {
      
    }

  }

  if (contador == 0)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    
  }

  for (i = 0; i < 10000; i++)
  {
    if (vec_prod[i].identificador == idp)
    {
      peso_prod = vec_prod[i].peso;
      contador5++;
      e = i;
      if ((vec_prod[i].stock < quantidade) && (contador != 0))
      {
        contador2++;
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  if ((contador5 == 0) && (contador != 0))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  }
  else
  {
    
  }

  if (((((peso_enc + (quantidade * peso_prod)) > 200) && (contador5 != 0)) && (contador != 0)) && (contador2 == 0))
  {
    contador4++;
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
  }
  else
  {
    
  }

  if ((((contador2 == 0) && (contador == 1)) && (contador4 == 0)) && (contador5 != 0))
  {
    vec_prod[e].stock -= quantidade;
    for (i = 0; i < 500; i++)
    {
      if (vec_encomendas[i].identificador == ide)
      {
        vec_encomendas[i].peso = peso_enc + (quantidade * peso_prod);
        for (e = 0; e < 200; e++)
        {
          if (vec_encomendas[i].produtos[e][0] == idp)
          {
            vec_encomendas[i].produtos[e][1] += quantidade;
            contador3++;
            break;
          }
          else
          {
            
          }

        }

        if (contador3 == 0)
        {
          for (e = 0; e < 200; e++)
          {
            if (vec_encomendas[i].produtos[e][0] == (-1))
            {
              vec_encomendas[i].produtos[e][0] = idp;
              vec_encomendas[i].produtos[e][1] = quantidade;
              break;
            }
            else
            {
              
            }

          }

        }
        else
        {
          
        }

        break;
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

void remove_prod_encomenda(char input[])
{
  int ide;
  int idp;
  int contador = 0;
  int contador2 = 0;
  int i;
  int e;
  int peso_produto;
  char dados[2][63];
  apaga_letra_comando(input);
  separa_input(input, dados);
  ide = str_para_int(dados[0]);
  idp = str_para_int(dados[1]);
  if (vec_encomendas[ide].identificador == ide)
  {
    contador++;
  }
  else
  {
    
  }

  if (contador == 0)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    
  }

  for (i = 0; i < 10000; i++)
  {
    if (vec_prod[i].identificador == idp)
    {
      contador2++;
      peso_produto = vec_prod[i].peso;
    }
    else
    {
      
    }

  }

  if ((contador2 == 0) && (contador != 0))
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  }
  else
  {
    
  }

  if ((contador2 == 1) && (contador == 1))
  {
    for (i = 0; i < 500; i++)
    {
      if (vec_encomendas[i].identificador == ide)
      {
        for (e = 0; e < 200; e++)
        {
          if (vec_encomendas[i].produtos[e][0] == idp)
          {
            vec_prod[idp].stock += vec_encomendas[i].produtos[e][1];
            vec_encomendas[i].peso -= peso_produto * vec_encomendas[i].produtos[e][1];
            vec_encomendas[i].produtos[e][0] = -1;
            vec_encomendas[i].produtos[e][1] = -1;
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

  }
  else
  {
    
  }

}

void calcula_custo(char input[])
{
  int soma = 0;
  int ide;
  int i;
  int e;
  int idp_qnt[200][2];
  int precos[200];
  char dados[1][63];
  apaga_letra_comando(input);
  separa_input(input, dados);
  ide = str_para_int(dados[0]);
  for (i = 0; i < 200; i++)
  {
    idp_qnt[i][0] = vec_encomendas[ide].produtos[i][0];
    idp_qnt[i][1] = vec_encomendas[ide].produtos[i][1];
  }

  for (i = 0; i < 200; i++)
  {
    for (e = 0; e < 10000; e++)
    {
      if (vec_prod[e].identificador == vec_encomendas[ide].produtos[i][0])
      {
        precos[i] = vec_prod[e].preco;
      }
      else
      {
        
      }

    }

  }

  for (i = 0; i < 200; i++)
  {
    if (precos[i] != (-1))
    {
      soma += idp_qnt[i][1] * precos[i];
    }
    else
    {
      
    }

  }

  if (vec_encomendas[ide].identificador != ide)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    printf("Custo da encomenda %d %d.\n", ide, soma);
  }

}

void lista_descricao_quantidade(char input[])
{
  int i;
  int m;
  int n;
  int ide;
  int idp;
  int contador = 0;
  int contador1 = 0;
  int contador2 = 0;
  char dados[2][63];
  apaga_letra_comando(input);
  separa_input(input, dados);
  ide = str_para_int(dados[0]);
  idp = str_para_int(dados[1]);
  if (vec_prod[idp].identificador == idp)
  {
    contador++;
  }
  else
  {
    
  }

  if (vec_encomendas[ide].identificador != ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    contador2++;
  }
  else
  {
    
  }

  if ((contador == 0) && (contador2 == 0))
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

  for (i = 0; i < 200; i++)
  {
    if (vec_encomendas[ide].produtos[i][0] == idp)
    {
      contador1++;
      break;
    }
    else
    {
      
    }

  }

  if (((contador != 0) && (contador1 != 0)) && (contador2 == 0))
  {
    if (vec_encomendas[ide].identificador == ide)
    {
      for (i = 0; i < 200; i++)
      {
        if (vec_encomendas[ide].produtos[i][0] == idp)
        {
          for (m = 0; m < 10000; m++)
          {
            if (vec_prod[m].identificador == idp)
            {
              for (n = 0; (n < 63) && (vec_prod[m].descricao[n] != '\0'); n++)
                putchar(vec_prod[m].descricao[n]);

              printf(" %d.\n", vec_encomendas[ide].produtos[i][1]);
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
    else
    {
      
    }

  }
  else
  {
    
  }

  if (((contador != 0) && (contador1 == 0)) && (contador2 == 0))
  {
    for (m = 0; m < 10000; m++)
    {
      if (vec_prod[m].identificador == idp)
      {
        for (n = 0; (n < 63) && (vec_prod[m].descricao[n] != '\0'); n++)
          putchar(vec_prod[m].descricao[n]);

        printf(" 0.\n");
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

void max_prod(char input[])
{
  int i;
  int e;
  int max = 0;
  int ide;
  int idp;
  int contador = 0;
  int contador1 = 0;
  char dados[1][63];
  apaga_letra_comando(input);
  separa_input(input, dados);
  idp = str_para_int(dados[0]);
  if (vec_prod[idp].identificador != idp)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    contador++;
  }
  else
  {
    
  }

  for (i = 0; i < 500; i++)
  {
    for (e = 0; e < 200; e++)
    {
      if ((vec_encomendas[i].produtos[e][0] == idp) && (vec_encomendas[i].produtos[e][1] > max))
      {
        max = vec_encomendas[i].produtos[e][1];
        ide = i;
        contador1++;
      }
      else
      {
        
      }

    }

  }

  if ((contador == 0) && (contador1 != 0))
  {
    printf("Maximo produto %d %d %d.\n", idp, ide, max);
  }
  else
  {
    
  }

}

void ordena_produtos_encomeda(char input[])
{
  int ide;
  int i;
  int k;
  int vec_indices[200];
  int e;
  int tamanho = 0;
  int quantidade;
  char dados[1][63];
  apaga_letra_comando(input);
  separa_input(input, dados);
  ide = str_para_int(dados[0]);
  if (vec_encomendas[ide].identificador != ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (i = 0; i < 200; i++)
    {
      for (e = 0; e < 10000; e++)
      {
        if ((vec_prod[e].identificador == vec_encomendas[ide].produtos[i][0]) && (vec_prod[e].identificador != (-1)))
        {
          vec_indices[tamanho] = e;
          tamanho++;
          break;
        }
        else
        {
          
        }

      }

    }

    merge_sort_funcao_L(vec_indices, 0, tamanho - 1);
    printf("Encomenda %d\n", ide);
    for (i = 0; i < tamanho; i++)
    {
      printf("* ");
      for (e = 0; (e < 63) && (vec_prod[vec_indices[i]].descricao[e] != '\0'); e++)
      {
        putchar(vec_prod[vec_indices[i]].descricao[e]);
      }

      for (k = 0; k < 200; k++)
      {
        if (vec_encomendas[ide].produtos[k][0] == vec_indices[i])
        {
          quantidade = vec_encomendas[ide].produtos[k][1];
          break;
        }
        else
        {
          
        }

      }

      printf(" %d %d\n", vec_prod[vec_indices[i]].preco, quantidade);
    }

  }

}

int main()
{
  char input[100];
  int c;
  int i;
  int e;
  int running = 1;
  for (i = 0; i < 10000; i++)
  {
    vec_prod[i].identificador = -1;
    vec_prod[i].peso = -1;
    vec_prod[i].preco = -1;
    vec_prod[i].stock = -1;
    for (e = 0; e < 63; e++)
    {
      vec_prod[i].descricao[e] = ' ';
    }

  }

  for (i = 0; i < 500; i++)
  {
    vec_encomendas[i].identificador = -1;
    vec_encomendas[i].peso = -1;
    for (e = 0; e < 200; e++)
    {
      vec_encomendas[i].produtos[e][0] = -1;
      vec_encomendas[i].produtos[e][1] = -1;
    }

  }

  while (running == 1)
  {
    c = getchar();
    for (i = 0; (c != '\n') && (c != EOF); i++)
    {
      input[i] = c;
      c = getchar();
    }

    input[i] = '\0';
    switch (input[0])
    {
      case 'a':
        adicionanovoproduto(input);
        break;

      case 'q':
        adicionastock(input);
        break;

      case 'r':
        remove_stock(input);
        break;

      case 'p':
        altera_preco(input);
        break;

      case 'l':
        ordena_produtos_sistema();
        break;

      case 'N':
        cria_encomenda();
        break;

      case 'A':
        adiciona_prod_encomenda(input);
        break;

      case 'R':
        remove_prod_encomenda(input);
        break;

      case 'C':
        calcula_custo(input);
        break;

      case 'E':
        lista_descricao_quantidade(input);
        break;

      case 'm':
        max_prod(input);
        break;

      case 'L':
        ordena_produtos_encomeda(input);
        break;

      case 'x':
        running = 0;
        break;

    }

  }

  return 0;
}
