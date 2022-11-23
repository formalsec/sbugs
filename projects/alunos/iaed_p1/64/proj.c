#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdbool.h>
typedef int ll;
typedef unsigned long ull;
ll i1,i2,i3,i4,i5,i6;
#define REP(i,a,b) for(i=(ll) a; i<(ll) b; i++)
#define INF 100000
#define size1_vector 10005
#define size2_vector 505
#define size3_vector 205
#define size4_vector 7
#define size_string 100

struct pl /*pair<ll,ll>*/
{
    ll ff; ll ss; /*first,second  */
};
struct pl mp(ll a, ll b) {struct pl x; x.ff=a; x.ss=b; return x;} /*o equivalente a make_pair*/

struct vl /*vector<ll>*/
{
    ll v[size3_vector];
    ll si; /*size*/
};
#define initvl(v) v.si=0; /*inicializacao*/
#define pbll(vv,s) vv.v[vv.si]=s; vv.si++; /*push_back(ll s)*/
#define pop_backvl(v) v.si--;  /*pop_back()*/

struct vpl /*vector<pair<ll,ll> >*/
{
    struct pl v[size3_vector];
    ll si; /*size*/
};
#define initvpl(v) v.si=0; /*inicializacao*/
#define pbpl(vv,s) vv.v[vv.si]=s; vv.si++; /*push_back(pl p)*/
#define vplerase(x,pos) REP(i1,pos+1,x.si) {x.v[i1-1]=x.v[i1];}x.si--; /*erase um elemento em O(N)*/

struct vplbig /*vector<pair<ll,ll> >*/
{
    struct pl v[size1_vector];
    ll si; /*size*/
};
struct vplbig tosort1; /*variavel global para ser usada mais tarde*/

ll cmppl(struct pl a, struct pl b)  /*criterio de comparacao entre dois pair<ll,ll>, retorna 0 se o primeiro par e menor, 1 se e maior*/
{
    if(a.ff<b.ff) {return 0;}
    if(a.ff>b.ff) {return 1;}
    if(a.ss<=b.ss) {return 0;}
    return 1;
}

void sortvpl(ll l, ll r) /*merge sort de um vetor de pares, neste caso do vetor tosort1*/
{
    ll i;
    ll mid=(r+l)/2;
    struct vpl ans; 
    ll ptr1=0,ptr2=0;
    if(l==r) {return;} /*intervalo para sort tem 1 elemento ==> ja esta sorted*/
    sortvpl(l,mid); sortvpl(mid+1,r); /*divide and conquer*/
    initvpl(ans); /*array sorted que representa o intervalo [l,r] sorted*/
    while(ptr1<mid-l+1 || ptr2<r-mid) /*merge com 2-pointer method em O(r-l+1)*/
    {
        if(ptr1==mid-l+1) {pbpl(ans,tosort1.v[ptr2+mid+1]); ptr2++;}
        else if(ptr2==r-mid) {pbpl(ans,tosort1.v[ptr1+l]); ptr1++;}
        else if(cmppl(tosort1.v[ptr1+l],tosort1.v[ptr2+mid+1])==0) {pbpl(ans,tosort1.v[ptr1+l]); ptr1++;}
        else {pbpl(ans,tosort1.v[ptr2+mid+1L]); ptr2++;}
    }
    REP(i,l,r+1) {tosort1.v[i]=ans.v[i-l];} /*intervalo [l,r] ja sorted e copiado para a array tosort1*/
}

struct string 
{
    char str[size_string];
    ll si; /*size*/
};
#define initstring(s) s.si=0; /*inicializacao*/
#define readstring(s) scanf("%s",s.str); REP(i3,0,size_string) {ll d=(ll) (s.str[i3]); if(d<33||d>126) {s.si=i3; break;}} 
void Outstring(struct string s) {ll i; REP(i,0,s.si) {printf("%c",s.str[i]);}}
ll cmpstr(struct string a,struct string b)
{
    ll d;
    ll i;
    if(a.si>=b.si) {d=b.si;}
    else {d=a.si;}
    REP(i,0,d) 
    {
        if(((ll) (a.str[i])) < ((ll) b.str[i])) {return 0;}
        else if(((ll) (a.str[i])) > ((ll) b.str[i])) {return 1;}
    }
    if(d==a.si) {return 0;}
    return 1;
}

struct vs /*vector<string>*/
{
    struct string s[size3_vector];
    ll si; /*size*/
};
#define initvs(s) s.si=0; /*inicializacao*/
#define pbvs(vv,st) vv.s[vv.si]=st; vv.si++; /*push_back(string s)*/
struct vs inp;  /*input na forma {str1,str2,...,strN}*/

struct pspl /*pair<string,pair<ll,ll> >*/
{
    struct string ff;
    struct pl ss;
};
struct pspl mp2(struct string s, struct pl p) {struct pspl x; x.ff=s; x.ss=p; return x;} /*push_back(pspl p)*/

struct vpspl /*vector<pspl>*/
{
    struct pspl v[size1_vector];
    ll si; /*size*/
};
#define initvpspl(x) x.si=0; /*inicializacao*/
#define pbpspl(vv,st) vv.v[vv.si]=st; vv.si++; /*push_back()*/
struct vpspl tosort2; /*variavel global para ser usada mais tarde*/

void sortvpspl(ll l, ll r) /*merge sort de um vetor de pspl, neste caso tosort2*/
{
    ll i;
    ll mid=(l+r)/2;
    struct vpspl ans; 
    ll ptr1=0,ptr2=0;
    if(l==r) {return;} /*intervalo para sort tem 1 elemento ==> ja esta sorted*/
    sortvpspl(l,mid); sortvpspl(mid+1,r); /*divide and conquer*/
    initvpspl(ans); /*array sorted que representa o intervalo [l,r] sorted*/
    while(ptr1<mid-l+1 || ptr2<r-mid) /*merge com 2-pointer method em O(r-l+1)*/
    {
        if(ptr1==mid-l+1) {pbpspl(ans,tosort2.v[ptr2+mid+1]); ptr2++;}
        else if(ptr2==r-mid) {pbpspl(ans,tosort2.v[ptr1+l]); ptr1++;}
        else if(cmpstr(tosort2.v[ptr1+l].ff,tosort2.v[ptr2+mid+1].ff)==0) {pbpspl(ans,tosort2.v[ptr1+l]); ptr1++;}
        else {pbpspl(ans,tosort2.v[ptr2+mid+1]); ptr2++;}
    }
    REP(i,l,r+1) {tosort2.v[i]=ans.v[i-l];} /*intervalo [l,r] ja sorted e copiado para a array tosort2*/
}

ll fastexp(ll a,ll e, ll mod) /*exponenciacao em O(log e)*/
{
    if(e==0) {return 1;}
    else if(e%2==0) 
    {
        ll ans=fastexp(a,e/2,mod); ans=ans*ans; ans%=mod; return ans;
    }
    else 
    {
        ll ans=fastexp(a,e/2,mod); ans=((ans*a)%mod)*ans; ans%=mod; return ans;
    }
}

struct product /*produto*/
{
    struct string description;
    ll price;
    ll weight;
    ll stock;
};
#define initproduct(pr,d,p,w,s) pr.description=d; pr.price=p; pr.weight=w; pr.stock=s; /*constructor de um produto*/

struct vproduct /*vector<product>*/
{
    struct product pp[size1_vector];
    ll si; /*size*/
};
#define initvproduct(v) v.si=0; /*inicializacao*/

struct order /*encomenda*/
{
    struct vpl prod;
    ll weight;
};
#define initorder(o,p,w) o.prod=p;o.weight=w; /*constructor de uma encomenda*/

struct vorder /*vector<order>*/
{
    struct order oo[size2_vector];
    ll si; /*size*/
};
#define initvorder(v) v.si=0; /*inicializacao*/

ll ToInt(struct string s) /*transforma uma string num long*/
{
    ll d; ll ans=0L;
    REP(i5,0,s.si)
    {
        d=(ll) (s.str[i5]-'0');
        ans+=d*fastexp(10L,s.si-1L-i5,INF);
    }
    return ans;
}

void Read() /*le uma linha de input, separando a string str1:str2:...:strN no vetor {str1,str2,...,strN}*/
{
    struct string s;
    struct string cur;
    initstring(s);
    readstring(s);
    initstring(cur);
    inp.si=0;
    REP(i6,0,s.si)
    {
        if(s.str[i6]==':') {pbvs(inp,cur); cur.si=0;} /*se o char atual e ':', entao da-se a separacao*/
        else {cur.str[cur.si]=s.str[i6]; cur.si++;}
    }
    pbvs(inp,cur);
}

int main()
{
    ll counter;
    struct vproduct p; struct vorder o; /*listas principais de produto e encomendas*/
    char com; /*caracter do comando*/
    struct string d; ll idp,ide; ll w; ll s; ll pr; /*variaveis a ser lidas: string descricao, idproduto, idencomenda, peso, stock, preco*/
    initvs(inp); inp.si=5;
    initvproduct(p); initvorder(o); initstring(d); initvs(inp);
    REP(counter,0,INF)
    {
        scanf("%c",&com); 
        if(com=='a') /*adicionar produto*/
        {
            struct product x;
            Read();
            if(inp.si>=1) {d=inp.s[0];} 
            if(inp.si>=2) {pr=ToInt(inp.s[1]);} 
            if(inp.si>=3) {w=ToInt(inp.s[2]);}
            if(inp.si>=4) {s=ToInt(inp.s[3]);}
            initproduct(x,d,pr,w,s); /*cria produto*/
            p.pp[p.si]=x; p.si++; /*adiciona produto criado a array de produtos*/
            printf("%s%d%s\n","Novo produto ",p.si-1,".");
        }
        else if(com=='q') /*adiciona stock a um produto*/
        {
            Read();
            idp=ToInt(inp.s[0]);
            if(inp.si>=2) {s=ToInt(inp.s[1]);}
            if(p.si<=idp) {printf("%s%d%s\n","Impossivel adicionar produto ",idp," ao stock. Produto inexistente.");}
            else
            {
                p.pp[idp].stock+=s;
            }
        }
        else if(com=='N') /*cria encomenda*/
        {
            struct order O; /*nova encomenda O*/
            O.prod.si=0;
            o.oo[o.si]=O; o.si++; /*O e adicionada a array de encomendas*/
            printf("%s%d%s\n","Nova encomenda ",o.si-1,"."); 
        }
        else if(com=='A') /*adiciona produto a encomenda*/
        {
            Read();
            ide=ToInt(inp.s[0]);
            idp=ToInt(inp.s[1]);
            s=ToInt(inp.s[2]);
            if(ide>=o.si) {printf("%s%d%s%d%s\n","Impossivel adicionar produto ",idp," a encomenda ",ide,". Encomenda inexistente.");}
            else if(idp>=p.si) {printf("%s%d%s%d%s\n","Impossivel adicionar produto ",idp," a encomenda ",ide,". Produto inexistente.");}
            else if(s>p.pp[idp].stock) {printf("%s%d%s%d%s\n","Impossivel adicionar produto ",idp," a encomenda ",ide,". Quantidade em stock insuficiente.");}
            else if(o.oo[ide].weight+p.pp[idp].weight*s>200) {printf("%s%d%s%d%s\n","Impossivel adicionar produto ",idp," a encomenda ",ide,". Peso da encomenda excede o maximo de 200.");}
            else
            {
                ll i;
                bool al=false; /*al e contracao de already, verifica se o produto ja esta na array da encomenda ou nao*/
                o.oo[ide].weight+=p.pp[idp].weight*s; /*peso da encomenda e atualizado*/
                p.pp[idp].stock-=s; /*stock do produto e atualizado*/
                REP(i,0,o.oo[ide].prod.si) 
                {
                    if(o.oo[ide].prod.v[i].ff==idp) {o.oo[ide].prod.v[i].ss+=s; al=true; break;} /*se sim, adiciona a quantidade*/
                }
                if(!al) {pbpl(o.oo[ide].prod,(mp(idp,s)));} /*se nao, cria novo produto na encomenda*/
            }
        }
        else if(com=='r') /*remove sotck a produto*/
        {
            Read();
            idp=ToInt(inp.s[0]);
            if(inp.si>=2) {s=ToInt(inp.s[1]);}
            if(idp>=p.si) {printf("%s%d%s\n","Impossivel remover stock do produto ",idp,". Produto inexistente.");}
            else if(p.pp[idp].stock<s) {printf("%s%d%s%d%s\n","Impossivel remover ",s," unidades do produto ",idp," do stock. Quantidade insuficiente.");}
            else {p.pp[idp].stock-=s;}
        }
        else if(com=='R') /*remove produto a encomenda*/
        {
            Read();
            ide=ToInt(inp.s[0]);
            idp=ToInt(inp.s[1]);
            if(ide>=o.si) {printf("%s%d%s%d%s\n","Impossivel remover produto ",idp," a encomenda ",ide,". Encomenda inexistente.");}
            else if(idp>=p.si) {printf("%s%d%s%d%s\n","Impossivel remover produto ",idp," a encomenda ",ide,". Produto inexistente.");}
            else 
            {
                ll i;
                REP(i,0,o.oo[ide].prod.si)
                {
                    if(o.oo[ide].prod.v[i].ff==idp) /*produto indicado*/
                    {
                        o.oo[ide].weight-=p.pp[idp].weight*o.oo[ide].prod.v[i].ss; /*atualiza peso da encomenda*/
                        p.pp[idp].stock+=o.oo[ide].prod.v[i].ss; /*stock do produto e atualizado*/
                        vplerase(o.oo[ide].prod,i); /*remove elemento da array de produtos da encomenda*/
                        break;
                    }
                }
            }
        }
        else if(com=='C') /*calcula custo de encomenda*/
        {
            Read();
            ide=ToInt(inp.s[0]);
            if(ide>=o.si) {printf("%s%d%s\n","Impossivel calcular custo da encomenda ",ide,". Encomenda inexistente.");}
            else 
            {
                ll i;
                ll ans=0;
                REP(i,0,o.oo[ide].prod.si) /*itera pelos produtos da encomenda*/
                {
                    ans+=p.pp[o.oo[ide].prod.v[i].ff].price*o.oo[ide].prod.v[i].ss;
                }
                printf("%s%d%s%d%s\n","Custo da encomenda ",ide," ",ans,".");
            }
        }
        else if(com=='p') /*altera preco de um produto*/
        {
            Read();
            idp=ToInt(inp.s[0]);
            pr=ToInt(inp.s[1]);
            if(idp>=p.si) {printf("%s%d%s\n","Impossivel alterar preco do produto ",idp,". Produto inexistente.");}
            else {p.pp[idp].price=pr;}
        }
        else if(com=='E') /*retorna informacao de um produto numa dada encomenda*/
        {
            ll i;
            ll qtd=0;
            Read();
            ide=ToInt(inp.s[0]);
            if(inp.si>=2) {idp=ToInt(inp.s[1]);}
            if(ide>=o.si) {printf("%s%d%s\n","Impossivel listar encomenda ",ide,". Encomenda inexistente.");}
            else if(idp>=p.si) {printf("%s%d%s\n","Impossivel listar produto ",idp,". Produto inexistente.");}
            else
            {
                REP(i,0,o.oo[ide].prod.si) 
                {
                    if(o.oo[ide].prod.v[i].ff==idp) {qtd=o.oo[ide].prod.v[i].ss; break;}
                }
                Outstring(p.pp[idp].description); printf("%s%d%s\n"," ",qtd,".");
            }
        }
        else if(com=='m') /*retorna o ide da encomenda em que um dado produto occorre mais vezes*/
        {
            Read();
            idp=ToInt(inp.s[0]);
            if(idp>=p.si) {printf("%s%d%s\n","Impossivel listar maximo do produto ",idp,". Produto inexistente.");}
            else
            {
                ll i;
                ll maxoc=-1; /*maxima ocorrencia*/
                REP(i,0,o.si)
                {
                    ll j;
                    ll oc=0;  /*ocorrencias do produto idp na encomenda i*/
                    REP(j,0,o.oo[i].prod.si)
                    {
                        if(o.oo[i].prod.v[j].ff==idp) {oc=o.oo[i].prod.v[j].ss; break;}
                    }
                    if(oc>maxoc) {ide=i;maxoc=oc;}
                }
                if(maxoc>0) {printf("%s%d%s%d%s%d%s\n","Maximo produto ",idp," ",ide," ",maxoc,".");}
            }
        }
        else if(com=='l') /*lista os produtos por ordem crescente de preco*/
        {
            ll i;
            initvpl(tosort1);
            REP(i,0,p.si) {pbpl(tosort1,mp(p.pp[i].price,i));}
            sortvpl(0,p.si-1);
            printf("Produtos\n");
            REP(i,0,p.si) 
            {
                printf("%s","* ");Outstring(p.pp[tosort1.v[i].ss].description);printf("%s%d%s%d\n"," ",p.pp[tosort1.v[i].ss].price," ",p.pp[tosort1.v[i].ss].stock);
            }
        }
        else if(com=='L') /*lista os produtos de uma dada encomenda por ordem alfabetica*/
        {
            Read();
            ide=ToInt(inp.s[0]);
            if(ide>=o.si) {printf("%s%d%s\n","Impossivel listar encomenda ",ide,". Encomenda inexistente.");}
            else 
            {
                ll i;
                initvpspl(tosort2);
                REP(i,0,o.oo[ide].prod.si) {pbpspl(tosort2, mp2(p.pp[o.oo[ide].prod.v[i].ff].description,o.oo[ide].prod.v[i]));}
                if(tosort2.si>0) {sortvpspl(0,tosort2.si-1L);}
                printf("%s%d\n","Encomenda ",ide);
                REP(i,0,tosort2.si) 
                {
                    printf("%s","* ");Outstring(tosort2.v[i].ff); printf("%s%d%s%d\n"," ",p.pp[tosort2.v[i].ss.ff].price," ",tosort2.v[i].ss.ss);
                }
            }
        }
        else if(com=='x') /*termina o programa*/
        {
           
            return 0;
        }
    }
    return 0;
}
