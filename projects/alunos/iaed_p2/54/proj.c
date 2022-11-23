#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef int ll;
typedef unsigned long ull;
ll i,i1,i2;
#define REP(i,a,b) for(i=a; i<b; i++)
#define mp make_pair
#define pl pair<ll,ll>
#define ff first
#define ss second
#define INF 1000000L
#define DEBUG(x) printf("Pedro Is The Master %d\n",x)
ll insig;
#define In(vecBRO, LENBRO) REP(IBRO,0,LENBRO) {scanf("%ld",&insig); vecBRO[IBRO]=insig;}
void Out(ll x[], ll s) {REP(i,0,s) {printf("%d ",x[i]);} printf("\n");}
int line;

int min(int a, int b)
{
    if(a<b) {return a;}
    else {return b;}
}

int max(int a, int b)
{
    if(a<b) {return b;}
    else {return a;}
}

void swap(int *a, int *b)
{
    int *c=a; a=b; b=c;
}


struct string
{
    char * s;
    ll si;
};

struct string inp()
{
    struct string ans; 
    char c; bool now;
    ans.s=(char*) can_fail_malloc(sizeof(char));
    ans.si=0;
    now=false;
    while(1>0)
    {
        scanf("%c",&c);
        if(now && (c=='\n' || c==':')) {break;}
        if(c=='\n' || c==':') {continue;}
        if(!now && c==' ') {continue;}
        now=true;
        ans.si++;
        ans.s=can_fail_realloc(ans.s,(ans.si)*sizeof(char));
        ans.s[ans.si-1]=c;
    }
    return ans;
}

void print(struct string s)
{
    REP(i1,0,s.si)
    {
        printf("%c",s.s[i1]);
    }
}

bool eq(struct string s, struct string t)
{
    int i2=0;
    if(s.si!=t.si) {return false;}
    REP(i2,0,s.si) {if(s.s[i2]!=t.s[i2]) {return false;}}
    return true;
}

struct pair
{
    int a; struct string s;
};

ll cmp(struct pair p1, struct pair p2)
{
    int i3=0;
    if(p1.a>p2.a) {return 0;}
    if(p1.a<p2.a) {return 1;}
    if(p1.a==INF) {return -1;}
    REP(i3,0,min(p1.s.si,p2.s.si)) 
    {
        if(p1.s.s[i3]<p2.s.s[i3]) {return 1;}
        else if(p1.s.s[i3]>p2.s.s[i3]) {return 0;}
    }
    if(p1.s.si>p2.s.si) {return 0;}
    else if(p1.s.si<p2.s.si) {return 1;}
    return (-1);
}

#define TYP3 struct pair

TYP3 inp3()
{
    TYP3 ans;
    scanf("%d",&(ans.a));
    ans.s=inp();
    return ans;
}

void print3(TYP3 val)
{
    printf("%d ",val.a); print(val.s);
}

struct node3
{
    TYP3 val;
    ll h;
    struct node3 *par;
    struct node3 *lson, *rson; 
    struct node3 *prv,*nxt;
};

struct AVL3 
{
    ll N; 
    
    struct node3 * root, *beg, *en;
};

struct AVL3 init3()
{
    struct AVL3 s; struct pair p; struct string str;
    p.a=INF; str.s=(char*) can_fail_malloc(sizeof(char)); str.s[0]='a'; str.si=1; p.s=str;
    s.en=(struct node3 *) can_fail_malloc(sizeof(struct node3));
    s.en->lson=NULL; s.en->rson=NULL; s.en->par=NULL; s.en->h=0;
    s.en->val=p; (s.en->val).s=str; 
    s.en->prv=NULL; s.en->nxt=NULL;
    s.root=s.en; s.beg=s.en;
    s.N=0L;
    return  s;
}

struct node3 * begin3(struct AVL3 *s)
{
    return s->beg;
}

struct node3 * end3(struct AVL3 *s)
{
    return s->en;
}

void display3(struct AVL3 *s)
{
    struct node3 * X = begin3(s);
    while(X!=end3(s))
    {
        printf("%d ",(X->val).a); print((X->val).s); printf("\n");   
        X=X->nxt;
    }
    printf("\n");
}

struct node3 * find3(struct AVL3 *s, TYP3 val)
{
    struct node3 * cur = s->root;
    while(1>0)
    {
        if(cmp(cur->val,val)==-1) {return cur;}
        else if(cmp(cur->val,val)==0 && cur->lson != NULL) {cur=cur->lson;}
        else if(cmp(cur->val,val)==1 && cur->rson != NULL) {cur=cur->rson;}
        else {return s->en;}
    }
}

struct node3 * lower_bound3(struct AVL3 *s, TYP3 val)
{
    struct node3 * cur = s->root; struct node3 * ans=s->en;
    while(1>0)
    {
        if(cmp(cur->val,val)==-1) {return cur;}
        if(cmp(cur->val,val)==0 && cmp(cur->val,ans->val)==1) {ans=cur;}
        if(cmp(cur->val,val)==0 && cur->lson != NULL) {cur=cur->lson;}
        else if(cmp(cur->val,val)==1 && cur->rson != NULL) {cur=cur->rson;}
        else {break;}
    }
    return ans;
}

struct node3 * upper_bound3(struct AVL3 *s, TYP3 val)
{
    struct node3 * cur = s->root; struct node3 * ans=s->en;
    while(1>0)
    {
        if(cmp(cur->val,val)==0 && cmp(cur->val,ans->val)==1) {ans=cur;}
        if(cmp(cur->val,val)==0 && cur->lson != NULL) {cur=cur->lson;}
        else if(cmp(cur->val,val)!=0 && cur->rson != NULL) {cur=cur->rson;}
        else {return ans;}
    }
}

void Balance3(struct AVL3 *s, struct node3 *X)
{
    ll h1,h2;
    struct node3 * cur; bool balanced;
    struct node3 * A, * B, * C, * D, * E;
    balanced=true;
    cur=X;
    while(1>0)
    {
        h1=0, h2=0;
        if(cur->lson!=NULL) {h1=cur->lson->h +1;}
        if(cur->rson!=NULL) {h2=cur->rson->h +1;}
        if(abs(h1-h2)>1) {balanced=false; break;}
        if(cur==s->root) {break;}
        cur=cur->par;
    }
    if(balanced) {return;}
    h1=0; h2=0;
    if(cur->lson!=NULL) {h1=cur->lson->h +1;}
    if(cur->rson!=NULL) {h2=cur->rson->h +1;}
    if(h2 > h1)
    {
        ll hl=0, hr=0;
        if(cur->rson->lson!=NULL) {hl=cur->rson->lson->h +1;}
        if(cur->rson->rson!=NULL) {hr=cur->rson->rson->h +1;}
        if(hr>hl)
        {
            (cur->h)-=2;
            A = cur->rson; if(cur->par==NULL) {s->root=A;}
            A->par=cur->par; cur->par=A; 
            cur->rson=A->lson; if(A->lson!=NULL) {A->lson->par=cur;}
            A->lson=cur;
            if(A->par != NULL)
            {
                if(A->par->rson==cur) {A->par->rson=A;}
                if(A->par->lson==cur) {A->par->lson=A;}
            }
            cur=A; 
            while(cur!=s->root)
            {
                cur=cur->par; (cur->h)--;
            }
        }
        else
        {
            A = cur; B = A->rson; C = B->lson; D = C->lson; E = C->rson;
            if(s->root==A) {s->root=C;}
            C->par=A->par; 
            if(C->par != NULL)
            {
                if(C->par->rson==A) {C->par->rson=C;}
                if(C->par->lson==A) {C->par->lson=C;}
            }
            A->par=C; C->lson=A;
            A->rson=D; if(D!=NULL) {D->par=A;}
            B->lson=E; if(E!=NULL) {E->par=B;}
            B->par=C; C->rson=B;
            B->h=0; if(B->rson!=NULL) {B->h=B->rson->h + 1;}
            A->h=0; if(A->lson!=NULL) {A->h=A->lson->h + 1;}
            (C->h)++;
            cur=C;
            while(cur!=s->root)
            {
                cur=cur->par; (cur->h)--;
            }
        }
    }
    else
    {
        ll hl=0, hr=0;
        if(cur->lson->lson!=NULL) {hl=cur->lson->lson->h +1;}
        if(cur->lson->rson!=NULL) {hr=cur->lson->rson->h +1;}
        if(hl>hr)
        {
            (cur->h)-=2;
            A = cur->lson; if(cur->par==NULL) {s->root=A;}
            A->par=cur->par; cur->par=A; 
            cur->lson=A->rson; if(A->rson!=NULL) {A->rson->par=cur;}
            A->rson=cur;
            if(A->par != NULL)
            {
                if(A->par->rson==cur) {A->par->rson=A;}
                if(A->par->lson==cur) {A->par->lson=A;}
            }
            cur=A;
            while(cur!=s->root)
            {
                cur=cur->par; (cur->h)--;
            }
        }
        else
        {
            A = cur; B = A->lson; C = B->rson; D = C->rson; E = C->lson;
            if(s->root==A) {s->root=C;}
            C->par=A->par; A->par=C; A->lson=D; 
            B->rson=E; B->par=C;
            C->rson=A; C->lson=B;
            if(D!=NULL) {D->par=A;}
            if(E!=NULL) {E->par=B;}
            B->h=0; if(B->lson!=NULL) {B->h=B->lson->h + 1;}
            A->h=0; if(A->rson!=NULL) {A->h=A->rson->h + 1;}
            (C->h)++;
            if(C->par != NULL)
            {
                if(C->par->rson==cur) {C->par->rson=C;}
                if(C->par->lson==cur) {C->par->lson=C;}
            }
            cur=C;
            while(cur!=s->root)
            {
                cur=cur->par; (cur->h)--;
            }
        }
    }
    return;
}

void insert3(struct AVL3 *s, TYP3 val)
{
    struct node3 * next, * X, *cur;
    next = lower_bound3(s, val); 
    X = (struct node3 *) can_fail_malloc(sizeof(struct node3));
    X->val=val; X->h=0; X->par=NULL; X->lson=NULL; X->rson=NULL;
    cur=s->root;
    (s->N)++; 
    while(cur->lson != NULL && cur->rson !=NULL)
    {
        (cur->h)++;
        if(cmp(cur->val,X->val)!=1) {cur=cur->lson;}
        else {cur=cur->rson;}
    }
    (cur->h)++;
    if(cur->lson==NULL && cur->rson==NULL) 
    {
        if(cmp(cur->val, X->val)!=1) {cur->lson=X; X->par=cur;}
        else {cur->rson=X; X->par=cur;}
    }
    else if(cur->lson==NULL)
    {
        if(cmp(cur->val, X->val)!=1) {cur->lson=X; X->par=cur;}
        else 
        {
            cur=cur->rson; (cur->h)++;
            if(cmp(X->val,cur->val)!=1) {cur->rson=X; X->par=cur;}
            else {cur->lson=X; X->par=cur;}
        }
    }
    else if(cur->rson==NULL)
    {
        if(cmp(cur->val, X->val)!=0) {cur->rson=X; X->par=cur;}
        else 
        {
            cur=cur->lson; (cur->h)++;
            if(cmp(X->val, cur->val)!=1) {cur->rson=X; X->par=cur;}
            else {cur->lson=X; X->par=cur;}
        }
    }
    if(cmp(X->val, s->beg->val)==1) {s->beg=X;}
    Balance3(s,X);
    X->nxt=next; X->prv=(X->nxt->prv);
    X->nxt->prv=X; if(X->prv !=NULL) {X->prv->nxt=X;}
}

void erase3(struct AVL3 *s, struct node3 *X)
{
    struct node3 *p, *cur; struct pair aux;
    if((X->val).a==INF) {return;}
    if(X->lson==NULL && X->rson==NULL) 
    {
        cur=X; p = cur->par;  
        cur->h=-1; cur=p;
        while(1>0)
        {
            ll h1=0; ll h2=0;
            if(cur->lson!=NULL) {h1=cur->lson->h +1;}
            if(cur->rson!=NULL) {h2=cur->rson->h +1;}
            cur->h=max(h1,h2);
            if(cur==s->root) {break;}
            cur=cur->par;
        }
        cur=X;
        if((cur->par)->rson==cur) {(cur->par)->rson=NULL;}
        if((cur->par)->lson==cur) {(cur->par)->lson=NULL;}
        X->nxt->prv=X->prv;
        if(X->prv!=NULL) {X->prv->nxt=X->nxt;}
        if(X==s->beg) {s->beg=s->beg->nxt;}
        free(cur); 
        (s->N)--;
        Balance3(s,p);
        return;
    }
    if(X->rson==NULL)
    {
        cur=X; p = cur->lson;
        cur->h=-1; cur=p;
        while(1>0)
        {
            ll h1=0; ll h2=0;
            if(cur->lson!=NULL) {h1=cur->lson->h +1;}
            if(cur->rson!=NULL) {h2=cur->rson->h +1;}
            cur->h=max(h1,h2);
            if(cur==s->root) {break;}
            cur=cur->par;
        }
        cur=X;
        if(X==s->root) {p->par=NULL; s->root=p; return;}
        if((cur->par)->rson==cur) {(cur->par)->rson=p;}
        if((cur->par)->lson==cur) {(cur->par)->lson=p;}
        p->par=cur->par;
        X->nxt->prv=X->prv;
        if(X->prv!=NULL) {X->prv->nxt=X->nxt;}
        if(X==s->beg) {s->beg=s->beg->nxt;}
        free(cur); 
        (s->N)--;
        Balance3(s,p);
        return;
    }
    if(X->lson==NULL)
    {
        cur=X; p = cur->rson;
        cur->h=-1; cur=p;
        while(1>0)
        {
            ll h1=0; ll h2=0;
            if(cur->lson!=NULL) {h1=cur->lson->h +1;}
            if(cur->rson!=NULL) {h2=cur->rson->h +1;}
            cur->h=max(h1,h2);
            if(cur==s->root) {break;}
            cur=cur->par;
        }
        cur=X;
        if(X==s->root) {p->par=NULL; s->root=p; return;}
        if((cur->par)->rson==cur) {(cur->par)->rson=p;}
        if((cur->par)->lson==cur) {(cur->par)->lson=p;}
        p->par=cur->par;
        X->nxt->prv=X->prv;
        if(X->prv!=NULL) {X->prv->nxt=X->nxt;}
        if(X==s->beg) {s->beg=s->beg->nxt;}
        free(cur); 
        (s->N)--;
        Balance3(s,p);
        return;
    }
    p = X->lson;
    while(p->rson!=NULL) {p=p->rson;}
    aux = X->val; X->val=p->val; p->val=aux;
    erase3(s,p);
}

#define TYP6 struct string
#define KEY6 struct string
struct string unid; 

TYP6 inp6()
{
    TYP6 ans;
    ans=inp();
    return ans;
}

void print6(TYP6 val)
{
    print(val);
}

struct node6
{
    TYP6 val, t1,t2;
    int s1,s2; 
    KEY6 k;
    bool visited; 
    struct node6 * nxt, *prv;
};

#define TYP7 struct node6

TYP7 inp7()
{
    TYP7 ans;
    ans.val=inp();
    return ans;
}

void print7(TYP7 val)
{
    print(val.val);
}

struct vector7
{
    TYP7 *a;
    ll size;
};

void disp7(struct vector7 v)
{
    int i4;
    REP(i4,0,v.size)
    {
        print7(*(v.a+i4)); printf(" ");
    }
    printf("\n");
}

struct vector7 init7(int N)
{
    int i5;
    struct vector7 v;
    v.a= (TYP7*) can_fail_malloc(N*sizeof(TYP7));
    v.size=N;
    REP(i5,0,N)
    {
        *(v.a+i5)=inp7();
    }
    return v;
}

void push_back7(struct vector7 *v, TYP7 val)
{
    (*v).size++;
    (*v).a=(TYP7*) can_fail_realloc((*v).a,((*v).size)*sizeof(TYP7));
    (*v).a[(*v).size-1]=val;
}

void pop_back7(struct vector7 *v)
{
    (*v).size--;
    (*v).a=(TYP7*) can_fail_realloc((*v).a,((*v).size)*sizeof(TYP7));
}

struct unordered_map6
{
    ll M; ll N;
    
    struct vector7 a;
    struct node6 * be, *en;
};

struct unordered_map6 init6(ll m) /*unordered_set with hashing*/
{
    int i6;
    struct unordered_map6 H; struct node6 X;
    unid.si=10L; unid.s=(char*) can_fail_malloc(10*sizeof(char)); 
    unid.s = "impossible";
    H.a=init7(0);
    H.M=m; X = *((struct node6 *) can_fail_malloc(sizeof(struct node6)));
    REP(i6,0,H.M) {push_back7(&(H.a), X);}
    H.be=(struct node6 *) can_fail_malloc(sizeof(struct node6));
    H.en=(struct node6 *) can_fail_malloc(sizeof(struct node6));
    H.be->prv=NULL; H.be->nxt=H.en;
    H.en->prv=H.be; H.en->nxt=NULL;
    H.N=0;
    return H;
}

struct node6 * begin6(struct unordered_map6 *H) 
{
    return H->be;
}

struct node6 * end6(struct unordered_map6 *H) 
{
    return H->en;
}

ll hash6(struct unordered_map6 *H, KEY6 k) 
{
    ll i7;
    ll ans=0L; ll val=1L;
    REP(i7,0,k.si)
    {
        ll cur_val = (ll) (k.s[i7]);
        ans+=(cur_val*val); ans=ans%(H->M);
        val*=10L;
        val=val%(H->M);
    }
    return ans;
}

void insert6(struct unordered_map6 *H, KEY6 k, TYP6 val, TYP6 t1, TYP6 t2, int s1, int s2) 
{
    struct node6 *X; ll ind;
    X= (struct node6*) can_fail_malloc(sizeof(struct node6));
    X->visited=true; X->k=k; X->val=val; X->t1=t1; X->t2=t2; X->s1=s1; X->s2=s2;
    ind=hash6(H, k);
    while(H->a.a[ind].visited)
    {
        if(eq(H->a.a[ind].k,k)) {H->a.a[ind] = *X;return;}
        ind=(ind+1)%(H->M);
    }
    H->a.a[ind]=*X; (H->N)++;
    H->a.a[ind].nxt=end6(H); H->a.a[ind].prv=H->en->prv; H->a.a[ind].prv->nxt=&(H->a.a[ind]); H->en->prv=&(H->a.a[ind]);
    if(H->N==1) {H->be=&(H->a.a[ind]); return;}

}

struct node6 * find6(struct unordered_map6 *H, KEY6 k)
{
    ll ind=hash6(H, k);
    while(H->a.a[ind].visited)
    {
        if(eq(H->a.a[ind].k,k)) {return &(H->a.a[ind]);}
        ind=(ind+1)%(H->M);
    }
    return end6(H);
}

void erase6(struct unordered_map6 *H, struct node6 * X)
{
    (H->N)--;
    X->k=unid;
    X->nxt->prv=X->prv;
    if(X->prv !=NULL) {X->prv->nxt=X->nxt;}
    if(H->be==X) {H->be=X->nxt;}
}






#define TYP8 struct string
#define KEY8 struct string
struct string unid; 

TYP8 inp8()
{
    TYP8 ans;
    ans=inp();
    return ans;
}

void print8(TYP8 val)
{
    print(val);
}

struct node8
{
    TYP8 val; 
    int pts;
    KEY8 k;
    bool visited; 
    struct node8 * nxt, *prv;
};

#define TYP9 struct node8

TYP9 inp9()
{
    TYP9 ans;
    ans.val=inp(); ans.pts=0;
    return ans;
}

void print9(TYP9 val)
{
    print(val.val);
}

struct vector9
{
    TYP9 *a;
    ll size;
};

void disp9(struct vector9 v)
{
    int i8;
    REP(i8,0,v.size)
    {
        print9(*(v.a+i8)); printf(" ");
    }
    printf("\n");
}

struct vector9 init9(int N)
{
    int i9;
    struct vector9 v;
    v.a= (TYP9*) can_fail_malloc(N*sizeof(TYP9));
    v.size=N;
    REP(i9,0,N)
    {
        *(v.a+i9)=inp9();
    }
    return v;
}

void push_back9(struct vector9 *v, TYP9 val)
{
    (*v).size++;
    (*v).a=(TYP9*) can_fail_realloc((*v).a,((*v).size)*sizeof(TYP9));
    (*v).a[(*v).size-1]=val;
}

void pop_back9(struct vector9 *v)
{
    (*v).size--;
    (*v).a=(TYP9*) can_fail_realloc((*v).a,((*v).size)*sizeof(TYP9));
}

struct unordered_map8
{
    ll M; ll N;
    
    struct vector9 a;
    struct node8 * be, *en;
};

struct unordered_map8 init8(ll m) /*unordered_set with hashing*/
{
    int i10;
    struct unordered_map8 H; struct node8 X;
    unid.si=10L; unid.s=(char*) can_fail_malloc(10*sizeof(char)); 
    unid.s = "impossible";
    H.a=init9(0);
    H.M=m; X = *((struct node8 *) can_fail_malloc(sizeof(struct node8)));
    REP(i10,0,H.M) {push_back9(&(H.a), X);}
    H.be=(struct node8 *) can_fail_malloc(sizeof(struct node8));
    H.en=(struct node8 *) can_fail_malloc(sizeof(struct node8));
    H.be->prv=NULL; H.be->nxt=H.en;
    H.en->prv=H.be; H.en->nxt=NULL;
    H.N=0;
    return H;
}

struct node8 * begin8(struct unordered_map8 *H) 
{
    return H->be;
}

struct node8 * end8(struct unordered_map8 *H) 
{
    return H->en;
}

ll hash8(struct unordered_map8 *H, KEY8 k) 
{
    int i11;
    ll ans=0L; ll val=1L;
    REP(i11,0,k.si)
    {
        ll cur_val = (ll) (k.s[i11]);
        ans+=(cur_val*val); ans=ans%(H->M);
        val*=10L;
        val=val%(H->M);
    }
    return ans;
}

void insert8(struct unordered_map8 *H, KEY8 k, TYP8 val) 
{
    ll ind;
    struct node8 *X = (struct node8*) can_fail_malloc(sizeof(struct node8));
    X->visited=true; X->k=k; X->val=val; X->pts=0L;
    ind=hash8(H, k);
    while(H->a.a[ind].visited)
    {
        if(eq(H->a.a[ind].k,k)) {H->a.a[ind] = *X;return;}
        ind=(ind+1)%(H->M);
    }
    H->a.a[ind]=*X; (H->N)++;
    H->a.a[ind].nxt=end8(H); H->a.a[ind].prv=H->en->prv; H->a.a[ind].prv->nxt=&(H->a.a[ind]); H->en->prv=&(H->a.a[ind]);
    if(H->N==1) {H->be=&(H->a.a[ind]); return;}

}

struct node8 * find8(struct unordered_map8 *H, KEY8 k)
{
    ll ind=hash8(H, k);
    while(H->a.a[ind].visited)
    {
        if(eq(H->a.a[ind].k,k)) {return &(H->a.a[ind]);}
        ind=(ind+1)%(H->M);
    }
    return end8(H);
}

void erase8(struct unordered_map8 *H, struct node8 * X)
{
    (H->N)--;
    X->k=unid;
    X->nxt->prv=X->prv;
    if(X->prv !=NULL) {X->prv->nxt=X->nxt;}
    if(H->be==X) {H->be=X->nxt;}
}

int main()
{
    struct unordered_map6 mg = init6(9973L);
    struct unordered_map8 mt = init8(9973L);
    struct pair p;
    struct node3 * Z;
    struct AVL3 s= init3();
    char c; line=0;
    while(1>0)
    {
        line++; 
        scanf("%c",&c);
        if(c=='a')
        {
            struct string name,t1,t2;
            struct node6 * X;
            struct node8 * Y;
            int s1,s2; char insig;
            name=inp(); t1=inp(); t2=inp(); scanf("%d%c%d%c",&s1,&insig,&s2,&insig);
            X = find6(&mg,name);
            if(X!=end6(&mg)) {printf("%d Jogo existente.\n", line); continue;}
            Y =find8(&mt,t1);
            if(Y==end8(&mt)) {printf("%d Equipa inexistente.\n", line); continue;}
            Y =find8(&mt,t2);
            if(Y==end8(&mt)) {printf("%d Equipa inexistente.\n", line);continue;}
            insert6(&mg,name,name,t1,t2,s1,s2);
            Y= find8(&mt,t1);
            p.a=Y->pts; p.s=t1; 
            Z = find3(&s,p);
            erase3(&s,Z);
            Y= find8(&mt,t2);
            p.a=Y->pts; p.s=t2;
            Z = find3(&s,p);
            erase3(&s,Z);
            if(s1>s2)
            {
                Y = find8(&mt,t1);
                (Y->pts)++;
            }
            else if(s2>s1)
            {
                Y = find8(&mt,t2); 
                (Y->pts)++;
            }
            Y= find8(&mt,t1);
            p.a=Y->pts; p.s=t1;
            insert3(&s,p);
            Y= find8(&mt,t2);
            p.a=Y->pts; p.s=t2;
            insert3(&s,p);
        }
        else if (c=='A')
        {
            struct string name=inp();
            struct node8 * X;
            X= find8(&mt,name);
            if(X!=end8(&mt)) {printf("%d Equipa existente.\n", line); continue;}
            else 
            {
                insert8(&mt,name,name);
            }
            p.a=0; p.s=name;
            insert3(&s,p);
        }
        else if (c=='l')
        {
            char insig;
            struct node6 * cur = begin6(&mg);
            REP(i,0,mg.N)
            {
                printf("%d ", line);
                print(cur->val); printf(" ");
                print(cur->t1); printf(" ");
                print(cur->t2); printf(" ");
                printf("%d %d\n",cur->s1,cur->s2);
                cur=cur->nxt;
            }
            scanf("%c",&insig);
        }
        else if (c=='p')
        {
            struct string name;
            struct node6 * X;
            name=inp();
            X=find6(&mg,name);
            if(X==end6(&mg)) {printf("%d Jogo inexistente.\n", line);continue;}
            printf("%d ", line); 
            print(name); printf(" ");
            print(X->t1); printf(" ");
            print(X->t2); printf(" ");
            printf("%d %d\n", X->s1,X->s2);
            
        }
        else if (c=='P')
        {
            struct string name=inp();
            struct node8 * X = find8(&mt,name);
            if(X==end8(&mt)) {printf("%d Equipa inexistente.\n", line); }
            else
            {
                printf("%d ", line); print(name); printf(" %d\n",X->pts);
            }
        }
        else if (c=='r')
        {
            struct node8 * Y;
            struct string name = inp();
            struct node6 * X = find6(&mg,name);
            if(X==end6(&mg)) {printf("%d Jogo inexistente.\n", line); continue;}
            if(X->s1>X->s2)
            {
                Y = find8(&mt,X->t1); 
                p.a=Y->pts; p.s=X->t1;
                Z=find3(&s,p);
                erase3(&s,Z);
                (Y->pts)--;
                p.a--; 
                insert3(&s,p);
            }
            else if(X->s2>X->s1)
            {
                Y = find8(&mt,X->t2); 
                p.a=Y->pts; p.s=X->t2;
                Z=find3(&s,p);
                erase3(&s,Z);
                (Y->pts)--;
                p.a--; 
                insert3(&s,p);
            }
            erase6(&mg,X);
        }
        else if (c=='s')
        {
            struct string name = inp(); int s1,s2; char insig; 
            struct node6 * X;
            struct node8 *Y;
            scanf("%d%c%d%c",&s1,&insig,&s2,&insig);
            X= find6(&mg,name);
            if(X==end6(&mg)) {printf("%d Jogo inexistente.\n", line); continue;}
            Y=find8(&mt,X->t1);
            p.a=Y->pts; p.s=X->t1; Z=find3(&s,p); erase3(&s,Z);
            Y=find8(&mt,X->t2);
            p.a=Y->pts; p.s=X->t2; Z=find3(&s,p); erase3(&s,Z);
            if(X->s1>X->s2)
            {
                Y = find8(&mt,X->t1); (Y->pts)--;
            }
            else if(X->s2>X->s1)
            {
                Y = find8(&mt,X->t2); (Y->pts)--;
            }
            X->s1=s1; X->s2=s2;
            if(s1>s2)
            {
                Y = find8(&mt,X->t1); 
                (Y->pts)++;
            }
            else if(s2>s1)
            {
                Y = find8(&mt,X->t2); 
                (Y->pts)++;
            }
            Y=find8(&mt,X->t1);
            p.a=Y->pts; p.s=X->t1; insert3(&s,p);
            Y=find8(&mt,X->t2);
            p.a=Y->pts; p.s=X->t2; insert3(&s,p);
                
        }
        else if (c=='g')
        {
            char insig; int maxvalue;scanf("%c",&insig);
            if(s.N==0) {continue;}
            Z = end3(&s); Z=Z->prv; maxvalue=(Z->val).a;
            while((Z->val).a==maxvalue)
            {
                if(Z==begin3(&s)) {break;}
                if((Z->prv->val).a==maxvalue) {Z=Z->prv;} 
                else {break;}
            }
            printf("%d Melhores %d\n",line,maxvalue);
            while(Z!=end3(&s))
            {
                printf("%d * ",line);print((Z->val).s); printf("\n");
                Z=Z->nxt;
            }
        }
        else if (c=='x')
        {
            break;
        }
    }
    return 0;
}
