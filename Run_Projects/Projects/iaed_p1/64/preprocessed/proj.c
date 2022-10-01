/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdbool.h>


typedef int ll;
typedef unsigned long ull;
ll i1;
ll i2;
ll i3;
ll i4;
ll i5;
ll i6;
struct pl
{
  ll ff;
  ll ss;
};
struct pl mp(ll a, ll b)
{
  struct pl x;
  x.ff = a;
  x.ss = b;
  return x;
}

struct vl
{
  ll v[205];
  ll si;
};
struct vpl
{
  struct pl v[205];
  ll si;
};
struct vplbig
{
  struct pl v[10005];
  ll si;
};
struct vplbig tosort1;
ll cmppl(struct pl a, struct pl b)
{
  if (a.ff < b.ff)
  {
    return 0;
  }
  else
  {
    
  }

  if (a.ff > b.ff)
  {
    return 1;
  }
  else
  {
    
  }

  if (a.ss <= b.ss)
  {
    return 0;
  }
  else
  {
    
  }

  return 1;
}

void sortvpl(ll l, ll r)
{
  ll i;
  ll mid = (r + l) / 2;
  struct vpl ans;
  ll ptr1 = 0;
  ll ptr2 = 0;
  if (l == r)
  {
    return;
  }
  else
  {
    
  }

  sortvpl(l, mid);
  sortvpl(mid + 1, r);
  ans.si = 0;
  ;
  while ((ptr1 < ((mid - l) + 1)) || (ptr2 < (r - mid)))
  {
    if (ptr1 == ((mid - l) + 1))
    {
      ans.v[ans.si] = tosort1.v[(ptr2 + mid) + 1];
      ans.si++;
      ;
      ptr2++;
    }
    else
    {
      if (ptr2 == (r - mid))
      {
        ans.v[ans.si] = tosort1.v[ptr1 + l];
        ans.si++;
        ;
        ptr1++;
      }
      else
      {
        if (cmppl(tosort1.v[ptr1 + l], tosort1.v[(ptr2 + mid) + 1]) == 0)
        {
          ans.v[ans.si] = tosort1.v[ptr1 + l];
          ans.si++;
          ;
          ptr1++;
        }
        else
        {
          ans.v[ans.si] = tosort1.v[(ptr2 + mid) + 1L];
          ans.si++;
          ;
          ptr2++;
        }

      }

    }

  }

  for (i = (ll) l; i < (((ll) r) + 1); i++)
  {
    tosort1.v[i] = ans.v[i - l];
  }

}

struct string
{
  char str[100];
  ll si;
};
void Outstring(struct string s)
{
  ll i;
  for (i = (ll) 0; i < ((ll) s.si); i++)
  {
    printf("%c", s.str[i]);
  }

}

ll cmpstr(struct string a, struct string b)
{
  ll d;
  ll i;
  if (a.si >= b.si)
  {
    d = b.si;
  }
  else
  {
    d = a.si;
  }

  for (i = (ll) 0; i < ((ll) d); i++)
  {
    if (((ll) a.str[i]) < ((ll) b.str[i]))
    {
      return 0;
    }
    else
    {
      if (((ll) a.str[i]) > ((ll) b.str[i]))
      {
        return 1;
      }
      else
      {
        
      }

    }

  }

  if (d == a.si)
  {
    return 0;
  }
  else
  {
    
  }

  return 1;
}

struct vs
{
  struct string s[205];
  ll si;
};
struct vs inp;
struct pspl
{
  struct string ff;
  struct pl ss;
};
struct pspl mp2(struct string s, struct pl p)
{
  struct pspl x;
  x.ff = s;
  x.ss = p;
  return x;
}

struct vpspl
{
  struct pspl v[10005];
  ll si;
};
struct vpspl tosort2;
void sortvpspl(ll l, ll r)
{
  ll i;
  ll mid = (l + r) / 2;
  struct vpspl ans;
  ll ptr1 = 0;
  ll ptr2 = 0;
  if (l == r)
  {
    return;
  }
  else
  {
    
  }

  sortvpspl(l, mid);
  sortvpspl(mid + 1, r);
  ans.si = 0;
  ;
  while ((ptr1 < ((mid - l) + 1)) || (ptr2 < (r - mid)))
  {
    if (ptr1 == ((mid - l) + 1))
    {
      ans.v[ans.si] = tosort2.v[(ptr2 + mid) + 1];
      ans.si++;
      ;
      ptr2++;
    }
    else
    {
      if (ptr2 == (r - mid))
      {
        ans.v[ans.si] = tosort2.v[ptr1 + l];
        ans.si++;
        ;
        ptr1++;
      }
      else
      {
        if (cmpstr(tosort2.v[ptr1 + l].ff, tosort2.v[(ptr2 + mid) + 1].ff) == 0)
        {
          ans.v[ans.si] = tosort2.v[ptr1 + l];
          ans.si++;
          ;
          ptr1++;
        }
        else
        {
          ans.v[ans.si] = tosort2.v[(ptr2 + mid) + 1];
          ans.si++;
          ;
          ptr2++;
        }

      }

    }

  }

  for (i = (ll) l; i < (((ll) r) + 1); i++)
  {
    tosort2.v[i] = ans.v[i - l];
  }

}

ll fastexp(ll a, ll e, ll mod)
{
  if (e == 0)
  {
    return 1;
  }
  else
  {
    if ((e % 2) == 0)
    {
      ll ans = fastexp(a, e / 2, mod);
      ans = ans * ans;
      ans %= mod;
      return ans;
    }
    else
    {
      ll ans = fastexp(a, e / 2, mod);
      ans = ((ans * a) % mod) * ans;
      ans %= mod;
      return ans;
    }

  }

}

struct product
{
  struct string description;
  ll price;
  ll weight;
  ll stock;
};
struct vproduct
{
  struct product pp[10005];
  ll si;
};
struct order
{
  struct vpl prod;
  ll weight;
};
struct vorder
{
  struct order oo[505];
  ll si;
};
ll ToInt(struct string s)
{
  ll d;
  ll ans = 0L;
  for (i5 = (ll) 0; i5 < ((ll) s.si); i5++)
  {
    d = (ll) (s.str[i5] - '0');
    ans += d * fastexp(10L, (s.si - 1L) - i5, 100000);
  }

  return ans;
}

void Read()
{
  struct string s;
  struct string cur;
  s.si = 0;
  ;
  for (int s_index = 0; s_index < 10; s_index++)
  {
    s.str[s_index] = new_sym_var(sizeof(char) * 8);
  }

  s.str[10 - 1] = '\0';
  for (i3 = (ll) 0; i3 < ((ll) 100); i3++)
  {
    ll d = (ll) s.str[i3];
    if ((d < 33) || (d > 126))
    {
      s.si = i3;
      break;
    }
    else
    {
      
    }

  }

  ;
  cur.si = 0;
  ;
  inp.si = 0;
  for (i6 = (ll) 0; i6 < ((ll) s.si); i6++)
  {
    if (s.str[i6] == ':')
    {
      inp.s[inp.si] = cur;
      inp.si++;
      ;
      cur.si = 0;
    }
    else
    {
      cur.str[cur.si] = s.str[i6];
      cur.si++;
    }

  }

  inp.s[inp.si] = cur;
  inp.si++;
  ;
}

int main()
{
  ll counter;
  struct vproduct p;
  struct vorder o;
  char com;
  struct string d;
  ll idp;
  ll ide;
  ll w;
  ll s;
  ll pr;
  inp.si = 0;
  ;
  inp.si = 5;
  p.si = 0;
  ;
  o.si = 0;
  ;
  d.si = 0;
  ;
  inp.si = 0;
  ;
  for (counter = (ll) 0; counter < ((ll) 100000); counter++)
  {
    com = new_sym_var(sizeof(char) * 8);
    if (com == 'a')
    {
      struct product x;
      Read();
      if (inp.si >= 1)
      {
        d = inp.s[0];
      }
      else
      {
        
      }

      if (inp.si >= 2)
      {
        pr = ToInt(inp.s[1]);
      }
      else
      {
        
      }

      if (inp.si >= 3)
      {
        w = ToInt(inp.s[2]);
      }
      else
      {
        
      }

      if (inp.si >= 4)
      {
        s = ToInt(inp.s[3]);
      }
      else
      {
        
      }

      x.description = d;
      x.price = pr;
      x.weight = w;
      x.stock = s;
      ;
      p.pp[p.si] = x;
      p.si++;
      printf("%s%d%s\n", "Novo produto ", p.si - 1, ".");
    }
    else
    {
      if (com == 'q')
      {
        Read();
        idp = ToInt(inp.s[0]);
        if (inp.si >= 2)
        {
          s = ToInt(inp.s[1]);
        }
        else
        {
          
        }

        if (p.si <= idp)
        {
          printf("%s%d%s\n", "Impossivel adicionar produto ", idp, " ao stock. Produto inexistente.");
        }
        else
        {
          p.pp[idp].stock += s;
        }

      }
      else
      {
        if (com == 'N')
        {
          struct order O;
          O.prod.si = 0;
          o.oo[o.si] = O;
          o.si++;
          printf("%s%d%s\n", "Nova encomenda ", o.si - 1, ".");
        }
        else
        {
          if (com == 'A')
          {
            Read();
            ide = ToInt(inp.s[0]);
            idp = ToInt(inp.s[1]);
            s = ToInt(inp.s[2]);
            if (ide >= o.si)
            {
              printf("%s%d%s%d%s\n", "Impossivel adicionar produto ", idp, " a encomenda ", ide, ". Encomenda inexistente.");
            }
            else
            {
              if (idp >= p.si)
              {
                printf("%s%d%s%d%s\n", "Impossivel adicionar produto ", idp, " a encomenda ", ide, ". Produto inexistente.");
              }
              else
              {
                if (s > p.pp[idp].stock)
                {
                  printf("%s%d%s%d%s\n", "Impossivel adicionar produto ", idp, " a encomenda ", ide, ". Quantidade em stock insuficiente.");
                }
                else
                {
                  if ((o.oo[ide].weight + (p.pp[idp].weight * s)) > 200)
                  {
                    printf("%s%d%s%d%s\n", "Impossivel adicionar produto ", idp, " a encomenda ", ide, ". Peso da encomenda excede o maximo de 200.");
                  }
                  else
                  {
                    ll i;
                    bool al = false;
                    o.oo[ide].weight += p.pp[idp].weight * s;
                    p.pp[idp].stock -= s;
                    for (i = (ll) 0; i < ((ll) o.oo[ide].prod.si); i++)
                    {
                      if (o.oo[ide].prod.v[i].ff == idp)
                      {
                        o.oo[ide].prod.v[i].ss += s;
                        al = true;
                        break;
                      }
                      else
                      {
                        
                      }

                    }

                    if (!al)
                    {
                      o.oo[ide].prod.v[o.oo[ide].prod.si] = mp(idp, s);
                      o.oo[ide].prod.si++;
                      ;
                    }
                    else
                    {
                      
                    }

                  }

                }

              }

            }

          }
          else
          {
            if (com == 'r')
            {
              Read();
              idp = ToInt(inp.s[0]);
              if (inp.si >= 2)
              {
                s = ToInt(inp.s[1]);
              }
              else
              {
                
              }

              if (idp >= p.si)
              {
                printf("%s%d%s\n", "Impossivel remover stock do produto ", idp, ". Produto inexistente.");
              }
              else
              {
                if (p.pp[idp].stock < s)
                {
                  printf("%s%d%s%d%s\n", "Impossivel remover ", s, " unidades do produto ", idp, " do stock. Quantidade insuficiente.");
                }
                else
                {
                  p.pp[idp].stock -= s;
                }

              }

            }
            else
            {
              if (com == 'R')
              {
                Read();
                ide = ToInt(inp.s[0]);
                idp = ToInt(inp.s[1]);
                if (ide >= o.si)
                {
                  printf("%s%d%s%d%s\n", "Impossivel remover produto ", idp, " a encomenda ", ide, ". Encomenda inexistente.");
                }
                else
                {
                  if (idp >= p.si)
                  {
                    printf("%s%d%s%d%s\n", "Impossivel remover produto ", idp, " a encomenda ", ide, ". Produto inexistente.");
                  }
                  else
                  {
                    ll i;
                    for (i = (ll) 0; i < ((ll) o.oo[ide].prod.si); i++)
                    {
                      if (o.oo[ide].prod.v[i].ff == idp)
                      {
                        o.oo[ide].weight -= p.pp[idp].weight * o.oo[ide].prod.v[i].ss;
                        p.pp[idp].stock += o.oo[ide].prod.v[i].ss;
                        for (i1 = ((ll) i) + 1; i1 < ((ll) o.oo[ide].prod.si); i1++)
                        {
                          o.oo[ide].prod.v[i1 - 1] = o.oo[ide].prod.v[i1];
                        }

                        o.oo[ide].prod.si--;
                        ;
                        break;
                      }
                      else
                      {
                        
                      }

                    }

                  }

                }

              }
              else
              {
                if (com == 'C')
                {
                  Read();
                  ide = ToInt(inp.s[0]);
                  if (ide >= o.si)
                  {
                    printf("%s%d%s\n", "Impossivel calcular custo da encomenda ", ide, ". Encomenda inexistente.");
                  }
                  else
                  {
                    ll i;
                    ll ans = 0;
                    for (i = (ll) 0; i < ((ll) o.oo[ide].prod.si); i++)
                    {
                      ans += p.pp[o.oo[ide].prod.v[i].ff].price * o.oo[ide].prod.v[i].ss;
                    }

                    printf("%s%d%s%d%s\n", "Custo da encomenda ", ide, " ", ans, ".");
                  }

                }
                else
                {
                  if (com == 'p')
                  {
                    Read();
                    idp = ToInt(inp.s[0]);
                    pr = ToInt(inp.s[1]);
                    if (idp >= p.si)
                    {
                      printf("%s%d%s\n", "Impossivel alterar preco do produto ", idp, ". Produto inexistente.");
                    }
                    else
                    {
                      p.pp[idp].price = pr;
                    }

                  }
                  else
                  {
                    if (com == 'E')
                    {
                      ll i;
                      ll qtd = 0;
                      Read();
                      ide = ToInt(inp.s[0]);
                      if (inp.si >= 2)
                      {
                        idp = ToInt(inp.s[1]);
                      }
                      else
                      {
                        
                      }

                      if (ide >= o.si)
                      {
                        printf("%s%d%s\n", "Impossivel listar encomenda ", ide, ". Encomenda inexistente.");
                      }
                      else
                      {
                        if (idp >= p.si)
                        {
                          printf("%s%d%s\n", "Impossivel listar produto ", idp, ". Produto inexistente.");
                        }
                        else
                        {
                          for (i = (ll) 0; i < ((ll) o.oo[ide].prod.si); i++)
                          {
                            if (o.oo[ide].prod.v[i].ff == idp)
                            {
                              qtd = o.oo[ide].prod.v[i].ss;
                              break;
                            }
                            else
                            {
                              
                            }

                          }

                          Outstring(p.pp[idp].description);
                          printf("%s%d%s\n", " ", qtd, ".");
                        }

                      }

                    }
                    else
                    {
                      if (com == 'm')
                      {
                        Read();
                        idp = ToInt(inp.s[0]);
                        if (idp >= p.si)
                        {
                          printf("%s%d%s\n", "Impossivel listar maximo do produto ", idp, ". Produto inexistente.");
                        }
                        else
                        {
                          ll i;
                          ll maxoc = -1;
                          for (i = (ll) 0; i < ((ll) o.si); i++)
                          {
                            ll j;
                            ll oc = 0;
                            for (j = (ll) 0; j < ((ll) o.oo[i].prod.si); j++)
                            {
                              if (o.oo[i].prod.v[j].ff == idp)
                              {
                                oc = o.oo[i].prod.v[j].ss;
                                break;
                              }
                              else
                              {
                                
                              }

                            }

                            if (oc > maxoc)
                            {
                              ide = i;
                              maxoc = oc;
                            }
                            else
                            {
                              
                            }

                          }

                          if (maxoc > 0)
                          {
                            printf("%s%d%s%d%s%d%s\n", "Maximo produto ", idp, " ", ide, " ", maxoc, ".");
                          }
                          else
                          {
                            
                          }

                        }

                      }
                      else
                      {
                        if (com == 'l')
                        {
                          ll i;
                          tosort1.si = 0;
                          ;
                          for (i = (ll) 0; i < ((ll) p.si); i++)
                          {
                            tosort1.v[tosort1.si] = mp(p.pp[i].price, i);
                            tosort1.si++;
                            ;
                          }

                          sortvpl(0, p.si - 1);
                          printf("Produtos\n");
                          for (i = (ll) 0; i < ((ll) p.si); i++)
                          {
                            printf("%s", "* ");
                            Outstring(p.pp[tosort1.v[i].ss].description);
                            printf("%s%d%s%d\n", " ", p.pp[tosort1.v[i].ss].price, " ", p.pp[tosort1.v[i].ss].stock);
                          }

                        }
                        else
                        {
                          if (com == 'L')
                          {
                            Read();
                            ide = ToInt(inp.s[0]);
                            if (ide >= o.si)
                            {
                              printf("%s%d%s\n", "Impossivel listar encomenda ", ide, ". Encomenda inexistente.");
                            }
                            else
                            {
                              ll i;
                              tosort2.si = 0;
                              ;
                              for (i = (ll) 0; i < ((ll) o.oo[ide].prod.si); i++)
                              {
                                tosort2.v[tosort2.si] = mp2(p.pp[o.oo[ide].prod.v[i].ff].description, o.oo[ide].prod.v[i]);
                                tosort2.si++;
                                ;
                              }

                              if (tosort2.si > 0)
                              {
                                sortvpspl(0, tosort2.si - 1L);
                              }
                              else
                              {
                                
                              }

                              printf("%s%d\n", "Encomenda ", ide);
                              for (i = (ll) 0; i < ((ll) tosort2.si); i++)
                              {
                                printf("%s", "* ");
                                Outstring(tosort2.v[i].ff);
                                printf("%s%d%s%d\n", " ", p.pp[tosort2.v[i].ss.ff].price, " ", tosort2.v[i].ss.ss);
                              }

                            }

                          }
                          else
                          {
                            if (com == 'x')
                            {
                              return 0;
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

              }

            }

          }

        }

      }

    }

  }

  return 0;
}
