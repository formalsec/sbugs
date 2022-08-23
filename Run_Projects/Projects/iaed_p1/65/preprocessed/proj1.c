/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct produto
{
  int idp_prod;
  char descricao[63];
  int preco;
  int peso;
  int quantidade;
} Produto;
Produto estoque[10000];
typedef struct encomenda
{
  int ide;
  int custo;
  int peso_enco;
  int qtd_prod;
  Produto produto[200];
} Encomenda;
Encomenda encomenda[5000];
int qpe = -1;
int qes = -1;
char aL_aux[10000][63] = {""};
int bL_aux[10000];
int al_aux[10000];
int bl_aux[10000];
void seleciona_funcao(char);
int procura_idp_encomenda(int, int);
void mergesort(char [][63], int [], int [], int, int, char);
void merge_char(char [][63], int [], int, int, int);
void merge_int(int [], int [], int, int, int);
void a();
void q();
void N();
void A();
void A_ad_qtd(int, int, int, int);
void A_ad_prod(int, int, int);
void r();
void R();
void R_move(int, int);
void C();
void p();
void p_altera_preco(int, int, int);
void E();
void m();
int m_gera_vetores(int, int [], int []);
int m_proc_maior(int, int []);
void l();
void L();
int main()
{
  char comando;
  while ((comando = getchar()) != 'x')
  {
    seleciona_funcao(comando);
  }

  return 0;
}

void seleciona_funcao(char comando)
{
  switch (comando)
  {
    case 'a':
      a();
      break;

    case 'q':
      q();
      break;

    case 'N':
      N();
      break;

    case 'A':
      A();
      break;

    case 'r':
      r();
      break;

    case 'R':
      R();
      break;

    case 'C':
      C();
      break;

    case 'p':
      p();
      break;

    case 'E':
      E();
      break;

    case 'm':
      m();
      break;

    case 'l':
      l();
      break;

    case 'L':
      L();
      break;

    case 'x':
      return;

  }

}

int procura_idp_encomenda(int ide, int idp)
{
  int i;
  int qtd_prod = encomenda[ide].qtd_prod;
  for (i = 0; i < qtd_prod; i++)
  {
    if (idp == encomenda[ide].produto[i].idp_prod)
    {
      {
        return i;
      }
    }
    else
    {
      
    }

  }

  return -1;
}

void mergesort(char aL[10000][63], int al[10000], int b[10000], int left, int right, char type)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergesort(aL, al, b, left, m, type);
  mergesort(aL, al, b, m + 1, right, type);
  if (type == 'L')
  {
    {
      merge_char(aL, b, left, m, right);
    }
  }
  else
  {
    
  }

  if ((type == 'l') || (type == 'm'))
  {
    {
      merge_int(al, b, left, m, right);
    }
  }
  else
  {
    
  }

}

void merge_char(char aL[10000][63], int b[10000], int left, int m, int right)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
  {
    strcpy(aL_aux[i - 1], aL[i - 1]);
    bL_aux[i - 1] = b[i - 1];
  }

  for (j = m; j < right; j++)
  {
    strcpy(aL_aux[(right + m) - j], aL[j + 1]);
    bL_aux[(right + m) - j] = b[j + 1];
  }

  for (k = left; k <= right; k++)
  {
    if (strcmp(aL_aux[j], aL_aux[i]) < 0)
    {
      {
        strcpy(aL[k], aL_aux[j]);
        b[k] = bL_aux[j--];
      }
    }
    else
    {
      {
        strcpy(aL[k], aL_aux[i]);
        b[k] = bL_aux[i++];
      }
    }

  }

}

void merge_int(int al[10000], int b[10000], int left, int m, int right)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
  {
    al_aux[i - 1] = al[i - 1];
    bl_aux[i - 1] = b[i - 1];
  }

  for (j = m; j < right; j++)
  {
    al_aux[(right + m) - j] = al[j + 1];
    bl_aux[(right + m) - j] = b[j + 1];
  }

  for (k = left; k <= right; k++)
  {
    if ((al_aux[j] < al_aux[i]) || (i > m))
    {
      {
        al[k] = al_aux[j];
        b[k] = bl_aux[j--];
      }
    }
    else
    {
      {
        al[k] = al_aux[i];
        b[k] = bl_aux[i++];
      }
    }

  }

}

void a()
{
  ++qpe;
  for (int estoque_index = 0; estoque_index < 10; estoque_index++)
  {
    estoque[qpe].descricao[estoque_index] = new_sym_var(sizeof(char) * 8);
  }

  estoque[qpe].descricao[10 - 1] = '\0';
  estoque[qpe].preco = new_sym_var(sizeof(int) * 8);
  estoque[qpe].peso = new_sym_var(sizeof(int) * 8);
  estoque[qpe].quantidade = new_sym_var(sizeof(int) * 8);
  if (0)
  {
    printf("a %s:%d:%d:%d##\n", estoque[qpe].descricao, estoque[qpe].preco, estoque[qpe].peso, estoque[qpe].quantidade);
  }
  else
  {
    
  }

  estoque[qpe].idp_prod = qpe;
  printf("Novo produto %d.\n", qpe);
}

void q()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (0)
  {
    printf("q %d:%d##\n", idp, qtd);
  }
  else
  {
    
  }

  if (idp > qpe)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      estoque[idp].quantidade += qtd;
    }
  }

}

void N()
{
  ++qes;
  printf("Nova encomenda %d.\n", qes);
  encomenda[qes].ide = qes;
  encomenda[qes].custo = 0;
  encomenda[qes].peso_enco = 0;
  encomenda[qes].qtd_prod = 0;
}

void A()
{
  int ide;
  int idp;
  int qtd;
  int idp_exi_eco;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (0)
  {
    printf("A %d:%d:%d##\n", ide, idp, qtd);
  }
  else
  {
    
  }

  idp_exi_eco = procura_idp_encomenda(ide, idp);
  if (ide > qes)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
  }
  else
  {
    if (idp > qpe)
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
    }
    else
    {
      if (qtd > estoque[idp].quantidade)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        }
      }
      else
      {
        if (((estoque[idp].peso * qtd) + encomenda[ide].peso_enco) > 200)
        {
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
          }
        }
        else
        {
          if (idp_exi_eco != (-1))
          {
            {
              A_ad_qtd(ide, idp, idp_exi_eco, qtd);
            }
          }
          else
          {
            {
              A_ad_prod(ide, idp, qtd);
            }
          }

        }

      }

    }

  }

}

void A_ad_qtd(int ide, int idp, int idp_exi_eco, int qtd)
{
  encomenda[ide].produto[idp_exi_eco].quantidade += qtd;
  encomenda[ide].custo += estoque[idp].preco * qtd;
  encomenda[ide].peso_enco += estoque[idp].peso * qtd;
  estoque[idp].quantidade -= qtd;
}

void A_ad_prod(int ide, int idp, int qtd)
{
  int idp_eco;
  encomenda[ide].custo += estoque[idp].preco * qtd;
  encomenda[ide].peso_enco += estoque[idp].peso * qtd;
  encomenda[ide].qtd_prod++;
  idp_eco = encomenda[ide].qtd_prod - 1;
  encomenda[ide].produto[idp_eco].idp_prod = idp;
  encomenda[ide].produto[idp_eco].preco = estoque[idp].preco;
  encomenda[ide].produto[idp_eco].peso = estoque[idp].peso;
  encomenda[ide].produto[idp_eco].quantidade += qtd;
  strcpy(encomenda[ide].produto[idp_eco].descricao, estoque[idp].descricao);
  estoque[idp].quantidade -= qtd;
}

void r()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (0)
  {
    printf("r %d:%d##\n", idp, qtd);
  }
  else
  {
    
  }

  if (idp > qpe)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    if (estoque[idp].quantidade < qtd)
    {
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
      }
    }
    else
    {
      {
        estoque[idp].quantidade -= qtd;
      }
    }

  }

}

void R()
{
  int ide;
  int idp;
  int qtd;
  int idp_eco;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (0)
  {
    printf("R %d:%d##\n", ide, idp);
  }
  else
  {
    
  }

  idp_eco = procura_idp_encomenda(ide, idp);
  if (ide > qes)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
  }
  else
  {
    if (idp > qpe)
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
    }
    else
    {
      if (encomenda[ide].qtd_prod == 0)
      {
        {
          return;
        }
      }
      else
      {
        if (idp_eco == (-1))
        {
          {
            return;
          }
        }
        else
        {
          {
            qtd = encomenda[ide].produto[idp_eco].quantidade;
            estoque[idp].quantidade += qtd;
            encomenda[ide].custo -= estoque[idp].preco * qtd;
            encomenda[ide].peso_enco -= estoque[idp].peso * qtd;
            R_move(ide, idp_eco);
            encomenda[ide].qtd_prod--;
          }
        }

      }

    }

  }

  return;
}

void R_move(int ide, int idp_eco)
{
  int i;
  int j;
  int qtd_prod = encomenda[ide].qtd_prod;
  for (i = idp_eco; i < qtd_prod; i++)
  {
    for (j = 0; j <= 63; j++)
    {
      encomenda[ide].produto[i].descricao[j] = encomenda[ide].produto[i + 1].descricao[j];
    }

    encomenda[ide].produto[i].idp_prod = encomenda[ide].produto[i + 1].idp_prod;
    encomenda[ide].produto[i].peso = encomenda[ide].produto[i + 1].peso;
    encomenda[ide].produto[i].preco = encomenda[ide].produto[i + 1].preco;
    encomenda[ide].produto[i].quantidade = encomenda[ide].produto[i + 1].quantidade;
  }

}

void C()
{
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide > qes)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    {
      printf("Custo da encomenda %d %d.\n", ide, encomenda[ide].custo);
    }
  }

}

void p()
{
  int idp;
  int novo_preco;
  int preco_atual;
  idp = new_sym_var(sizeof(int) * 8);
  novo_preco = new_sym_var(sizeof(int) * 8);
  if (0)
  {
    printf("p %d:%d##\n", idp, novo_preco);
  }
  else
  {
    
  }

  if (idp > qpe)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      preco_atual = estoque[idp].preco;
      estoque[idp].preco = novo_preco;
      p_altera_preco(idp, novo_preco, preco_atual);
    }
  }

}

void p_altera_preco(int idp, int novo_preco, int preco_atual)
{
  int i;
  int j;
  int qtd_prod;
  int quantidade;
  for (i = 0; i <= qes; i++)
  {
    qtd_prod = encomenda[i].qtd_prod;
    for (j = 0; j < qtd_prod; j++)
    {
      if (idp == encomenda[i].produto[j].idp_prod)
      {
        {
          quantidade = encomenda[i].produto[j].quantidade;
          encomenda[i].produto[j].preco = novo_preco;
          encomenda[i].custo += (novo_preco - preco_atual) * quantidade;
        }
      }
      else
      {
        
      }

    }

  }

}

void E()
{
  int ide;
  int idp;
  int idp_eco;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (0)
  {
    printf("E %d:%d##\n", ide, idp);
  }
  else
  {
    
  }

  idp_eco = procura_idp_encomenda(ide, idp);
  if (ide > qes)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    if (idp > qpe)
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
      }
    }
    else
    {
      if (encomenda[ide].qtd_prod == 0)
      {
        {
          printf("%s %d.\n", estoque[idp].descricao, 0);
        }
      }
      else
      {
        if (idp_eco == (-1))
        {
          {
            printf("%s %d.\n", estoque[idp].descricao, 0);
          }
        }
        else
        {
          {
            printf("%s %d.\n", encomenda[ide].produto[idp_eco].descricao, encomenda[ide].produto[idp_eco].quantidade);
          }
        }

      }

    }

  }

  return;
}

void m()
{
  int idp;
  int i;
  int k;
  int maior;
  int vet_ide[5000];
  int vet_qtd[5000];
  idp = new_sym_var(sizeof(int) * 8);
  if (idp > qpe)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    if (qes == (-1))
    {
      {
        return;
      }
    }
    else
    {
      {
        k = m_gera_vetores(idp, vet_ide, vet_qtd);
        if (k == 0)
        {
          {
            return;
          }
        }
        else
        {
          
        }

        maior = m_proc_maior(k, vet_qtd);
        mergesort(aL_aux, vet_qtd, vet_ide, 0, k - 1, 'm');
        for (i = 0; i < k; i++)
        {
          if (vet_qtd[i] == maior)
          {
            {
              printf("Maximo produto %d %d %d.\n", idp, vet_ide[i], maior);
              break;
            }
          }
          else
          {
            
          }

        }

      }
    }

  }

}

int m_gera_vetores(int idp, int vet_ide[5000], int vet_qtd[5000])
{
  int i;
  int j;
  int k = 0;
  int qtd_prod;
  for (i = 0; i <= qes; i++)
  {
    qtd_prod = encomenda[i].qtd_prod;
    for (j = 0; j < qtd_prod; j++)
    {
      if (encomenda[i].produto[j].idp_prod == idp)
      {
        {
          vet_ide[k] = i;
          vet_qtd[k++] = encomenda[i].produto[j].quantidade;
        }
      }
      else
      {
        
      }

    }

  }

  return k;
}

int m_proc_maior(int k, int vet_qtd[5000])
{
  int i;
  int maior;
  maior = vet_qtd[0];
  for (i = 0; i < k; i++)
  {
    if (vet_qtd[i] > maior)
    {
      {
        maior = vet_qtd[i];
      }
    }
    else
    {
      
    }

  }

  return maior;
}

void l()
{
  int i;
  int id;
  int vet_preco[10000] = {0};
  int vet_id[10000] = {0};
  for (i = 0; i <= qpe; i++)
  {
    vet_preco[i] = estoque[i].preco;
    vet_id[i] = i;
  }

  mergesort(aL_aux, vet_preco, vet_id, 0, qpe, 'l');
  printf("Produtos\n");
  for (i = 0; i <= qpe; i++)
  {
    id = vet_id[i];
    printf("* %s %d %d\n", estoque[id].descricao, estoque[id].preco, estoque[id].quantidade);
  }

}

void L()
{
  int i;
  int id;
  int ide;
  int qtd_prod;
  int vet_id[10000] = {0};
  char vet_cc[10000][63] = {""};
  ide = new_sym_var(sizeof(int) * 8);
  qtd_prod = encomenda[ide].qtd_prod;
  if (ide > qes)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    {
      for (i = 0; i < qtd_prod; i++)
      {
        strcpy(vet_cc[i], encomenda[ide].produto[i].descricao);
        vet_id[i] = i;
      }

      mergesort(vet_cc, al_aux, vet_id, 0, qtd_prod - 1, 'L');
      printf("Encomenda %d\n", ide);
      for (i = 0; i < qtd_prod; i++)
      {
        id = vet_id[i];
        printf("* %s %d ", encomenda[ide].produto[id].descricao, encomenda[ide].produto[id].preco);
        printf("%d\n", encomenda[ide].produto[id].quantidade);
      }

    }
  }

}

