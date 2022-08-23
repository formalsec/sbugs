/* jose maria figueira janarra ist192505 al125 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BUFF 1000000

typedef struct cruz{
  int a;
  int r;
} cruz;

typedef struct caminho {
  cruz *cruz;
  int numv;
} caminho;

typedef struct tc{
  int s;
  int c;
  cruz cruz;
  cruz *adj;
  int numadj;
  caminho *cams;
  int numc;
  int v;
} tc;

typedef struct arrc {
  tc *tc;
} arrc;

struct node {
  tc tc;
  struct node *next;
  struct node *next2;
  struct node *prev;
};

int sreal;
int ccreal;
int contint;
int contfinal;

int *cut(char buffaux[]) {
  int *mn=(int*)malloc(sizeof(int)*2);
  char delim[]=" ";
  char *token=strtok(buffaux, delim);
  mn[0]=atoi(token);
  delim[0]='\n';
  token=strtok(NULL, delim);
  mn[1]=atoi(token);
  return mn;
}

void initmatrixmn(arrc *ac, int m, int n) {
  int i;
  int j;
  for (i=0; i<m; i++) {
    ac[i].tc=(tc*)malloc(sizeof(struct tc)*n);
    for (j=0; j<n; j++) {
      ac[i].tc[j].s=0;
      ac[i].tc[j].c=0;
      ac[i].tc[j].cruz.a=i;
      ac[i].tc[j].cruz.r=j;
      ac[i].tc[j].v=0;
      ac[i].tc[j].numc=0;
      if (i==0 && j==0) {
        ac[0].tc[0].adj=(cruz*)malloc(sizeof(struct cruz)*2);
        ac[0].tc[0].adj[0].a=0;
        ac[0].tc[0].adj[0].r=1;
        ac[0].tc[0].adj[1].a=1;
        ac[0].tc[0].adj[1].r=0;
        ac[0].tc[0].numadj=2;
      }
      if (i==0 && j==n-1) {
        ac[i].tc[j].adj=(cruz*)malloc(sizeof(struct cruz)*2);
        ac[i].tc[j].adj[0].a=0;
        ac[i].tc[j].adj[0].r=j-1;
        ac[i].tc[j].adj[1].a=1;
        ac[i].tc[j].adj[1].r=j;
        ac[i].tc[j].numadj=2;
      }
      if (i==m-1 && j==0) {
        ac[i].tc[j].adj=(cruz*)malloc(sizeof(struct cruz)*2);
        ac[i].tc[j].adj[0].a=i;
        ac[i].tc[j].adj[0].r=1;
        ac[i].tc[j].adj[1].a=i-1;
        ac[i].tc[j].adj[1].r=j;
        ac[i].tc[j].numadj=2;
      }
      if (i==m-1 && j==n-1) {
        ac[i].tc[j].adj=(cruz*)malloc(sizeof(struct cruz)*2);
        ac[i].tc[j].adj[0].a=i;
        ac[i].tc[j].adj[0].r=j-1;
        ac[i].tc[j].adj[1].a=i-1;
        ac[i].tc[j].adj[1].r=j;
        ac[i].tc[j].numadj=2;
      }
      if (i==0 && j>0 && j<n-1) {
        ac[i].tc[j].adj=(cruz*)malloc(sizeof(struct cruz)*3);
        ac[i].tc[j].adj[0].a=i;
        ac[i].tc[j].adj[0].r=j+1;
        ac[i].tc[j].adj[1].a=i;
        ac[i].tc[j].adj[1].r=j-1;
        ac[i].tc[j].adj[2].a=1;
        ac[i].tc[j].adj[2].r=j;
        ac[i].tc[j].numadj=3;
      }
      if (i==m-1 && j>0 && j<n-1) {
        ac[i].tc[j].adj=(cruz*)malloc(sizeof(struct cruz)*3);
        ac[i].tc[j].adj[0].a=i;
        ac[i].tc[j].adj[0].r=j+1;
        ac[i].tc[j].adj[1].a=i;
        ac[i].tc[j].adj[1].r=j-1;
        ac[i].tc[j].adj[2].a=i-1;
        ac[i].tc[j].adj[2].r=j;
        ac[i].tc[j].numadj=3;
      }
      if (i>0 && i<m-1 && j==n-1) {
        ac[i].tc[j].adj=(cruz*)malloc(sizeof(struct cruz)*3);
        ac[i].tc[j].adj[0].a=i;
        ac[i].tc[j].adj[0].r=j-1;
        ac[i].tc[j].adj[1].a=i+1;
        ac[i].tc[j].adj[1].r=j;
        ac[i].tc[j].adj[2].a=i-1;
        ac[i].tc[j].adj[2].r=j;
        ac[i].tc[j].numadj=3;
      }
      if (i>0 && i<m-1 && j==0) {
        ac[i].tc[j].adj=(cruz*)malloc(sizeof(struct cruz)*3);
        ac[i].tc[j].adj[0].a=i;
        ac[i].tc[j].adj[0].r=j+1;
        ac[i].tc[j].adj[1].a=i+1;
        ac[i].tc[j].adj[1].r=j;
        ac[i].tc[j].adj[2].a=i-1;
        ac[i].tc[j].adj[2].r=j;
        ac[i].tc[j].numadj=3;
      }
      if (i>0 && i<m-1 && j>0 && j<n-1) {
        ac[i].tc[j].adj=(cruz*)malloc(sizeof(struct cruz)*4);
        ac[i].tc[j].adj[0].a=i;
        ac[i].tc[j].adj[0].r=j+1;
        ac[i].tc[j].adj[1].a=i;
        ac[i].tc[j].adj[1].r=j-1;
        ac[i].tc[j].adj[2].a=i+1;
        ac[i].tc[j].adj[2].r=j;
        ac[i].tc[j].adj[3].a=i-1;
        ac[i].tc[j].adj[3].r=j;
        ac[i].tc[j].numadj=4;
      }
    }
  }
}

void initmatrix11(arrc *ac, int m, int n) {
  int i;
  if (m==1 && n==1) {
    ac[0].tc=(tc*)malloc(sizeof(struct tc)*1);
    ac[0].tc[0].s=0;
    ac[0].tc[0].c=0;
    ac[0].tc[0].cruz.a=0;
    ac[0].tc[0].cruz.r=0;
    ac[0].tc[0].v=0;
    ac[0].tc[0].numc=0;
    ac[0].tc[0].numadj=0;
  }
  if (m==1 && n>1) {
    ac[0].tc=(tc*)malloc(sizeof(struct tc)*n);
    for (i=0; i<n; i++) {
      ac[0].tc[i].s=0;
      ac[0].tc[i].c=0;
      ac[0].tc[i].cruz.a=0;
      ac[0].tc[i].cruz.r=i;
      ac[0].tc[i].v=0;
      ac[0].tc[i].numc=0;
      if (i==0) {
        ac[0].tc[i].adj=(cruz*)malloc(sizeof(struct cruz)*1);
        ac[0].tc[i].adj[0].a=0;
        ac[0].tc[i].adj[0].r=i+1;
        ac[0].tc[i].numadj=1;
      }
      if (i>0 && i<n-1) {
        ac[0].tc[i].adj=(cruz*)malloc(sizeof(struct cruz)*2);
        ac[0].tc[i].adj[0].a=0;
        ac[0].tc[i].adj[0].r=i+1;
        ac[0].tc[i].adj[1].a=0;
        ac[0].tc[i].adj[1].r=i-1;
        ac[0].tc[i].numadj=2;
      }
      if (i==n-1) {
        ac[0].tc[i].adj=(cruz*)malloc(sizeof(struct cruz)*1);
        ac[0].tc[i].adj[0].a=0;
        ac[0].tc[i].adj[0].r=i-1;
        ac[0].tc[i].numadj=1;
      }
    }
  }
  if (m>1 && n==1) {
    for (i=0; i<m; i++) {
      ac[i].tc=(tc*)malloc(sizeof(struct tc)*1);
      ac[i].tc[0].s=0;
      ac[i].tc[0].c=0;
      ac[i].tc[0].cruz.a=i;
      ac[i].tc[0].cruz.r=0;
      ac[i].tc[0].v=0;
      ac[i].tc[0].numc=0;
      if (i==0) {
        ac[0].tc[0].adj=(cruz*)malloc(sizeof(struct cruz)*1);
        ac[0].tc[0].adj[0].a=i+1;
        ac[0].tc[0].adj[0].r=0;
        ac[0].tc[0].numadj=1;
      }
      if (i>0 && i<m-1) {
        ac[i].tc[0].adj=(cruz*)malloc(sizeof(struct cruz)*2);
        ac[i].tc[0].adj[0].a=i+1;
        ac[i].tc[0].adj[0].r=0;
        ac[i].tc[0].adj[1].a=i-1;
        ac[i].tc[0].adj[1].r=0;
        ac[i].tc[0].numadj=2;
      }
      if (i==m-1) {
        ac[i].tc[0].adj=(cruz*)malloc(sizeof(struct cruz)*1);
        ac[i].tc[0].adj[0].a=i-1;
        ac[i].tc[0].adj[0].r=0;
        ac[i].tc[0].numadj=1;
      }
    }
  }
}

void organize(char buff[], int s, int c, int m, int n, arrc *ac, cruz *cc, cruz *ss) {
  int i;
  int aa;
  int ra;
  int k=1;
  int p=0;
  char delim[]=" ";
  char *token=strtok(buff, delim);
  if (m==1 || n==1) {
    initmatrix11(ac, m, n);
  }
  else {
    initmatrixmn(ac, m, n);
  }
  aa=atoi(token);
  delim[0]='\n';
  token=strtok(NULL, delim);
  ra=atoi(token);
  ac[aa-1].tc[ra-1].s=1;
  ss[0].a=aa-1;
  ss[0].r=ra-1;
  for (i=1; i<s; i++) {
    delim[0]=' ';
    token=strtok(NULL, delim);
    aa=atoi(token);
    delim[0]='\n';
    token=strtok(NULL, delim);
    ra=atoi(token);
    if (ac[aa-1].tc[ra-1].s==1) {
      sreal--;
    }
    else {
      ac[aa-1].tc[ra-1].s=1;
      ss[k].a=aa-1;
      ss[k].r=ra-1;
      k++;
    }
  }
  i=s;
  c=c+s;
  while (i<c) {
    delim[0]=' ';
    token=strtok(NULL, delim);
    aa=atoi(token);
    delim[0]='\n';
    token=strtok(NULL, delim);
    ra=atoi(token);
    if (ac[aa-1].tc[ra-1].c==1) {
      ccreal--;
    }
    else {
      if (ac[aa-1].tc[ra-1].s==1) {
        contfinal++;
        ac[aa-1].tc[ra-1].c=1;
      }
      else {
        ac[aa-1].tc[ra-1].c=1;
        cc[p].a=aa-1;
        cc[p].r=ra-1;
        p++;
      }
    }
    i++;
  }
}

struct node *eliminarQ(struct node *head) {
  struct node *aux=head->next;
  head=aux;
  return head;
}

struct node *inserirQ(struct node *head, struct node *node) {
  struct node *i;
  for (i=head; i->next!=NULL; i=i->next);
  i->next=node;
  return head;
}

struct node *inserirL(struct node *head, struct node *node) {
  if (head==NULL) {
    head=node;
    return head;
  }
  node->next2=head;
  head=node;
  return head;
}

struct node *verifyHelper(struct node *head, struct node *currentnode, arrc *ac) {
  int i;
  int numv=0;
  int numc=0;
  struct node *nextnode;
  struct node *p;
  tc s=currentnode->tc;
  if (s.c==1 && s.s==1) {
    return head;
  }
  for (i=0; i<s.numadj;i++) {
    if (ac[s.adj[i].a].tc[s.adj[i].r].c==1  && ac[s.adj[i].a].tc[s.adj[i].r].s==0 && ac[s.adj[i].a].tc[s.adj[i].r].v==0) {
      if (ac[s.adj[i].a].tc[s.adj[i].r].numc==0) {
        ac[s.adj[i].a].tc[s.adj[i].r].cams=(caminho*)malloc(sizeof(struct caminho)*1);
        ac[s.adj[i].a].tc[s.adj[i].r].cams[0].cruz=(cruz*)malloc(sizeof(struct cruz)*1);
        numv=1;
        ac[s.adj[i].a].tc[s.adj[i].r].cams[0].cruz[0]=ac[s.adj[i].a].tc[s.adj[i].r].cruz;
        for (p=currentnode; p!=NULL; p=p->prev) {
          ac[s.adj[i].a].tc[s.adj[i].r].cams[0].cruz=realloc(ac[s.adj[i].a].tc[s.adj[i].r].cams[0].cruz, sizeof(struct cruz)*(numv+1));
          ac[s.adj[i].a].tc[s.adj[i].r].cams[0].cruz[numv]=p->tc.cruz;

          numv++;
        }
        ac[s.adj[i].a].tc[s.adj[i].r].cams[0].numv=numv;
      }
      else {
        numc=ac[s.adj[i].a].tc[s.adj[i].r].numc;
        numv=1;
        ac[s.adj[i].a].tc[s.adj[i].r].cams=realloc(ac[s.adj[i].a].tc[s.adj[i].r].cams, sizeof(struct caminho)*(numc+1));
        ac[s.adj[i].a].tc[s.adj[i].r].cams[numc].cruz=(cruz*)malloc(sizeof(struct cruz)*1);
        ac[s.adj[i].a].tc[s.adj[i].r].cams[numc].cruz[0]=ac[s.adj[i].a].tc[s.adj[i].r].cruz;
        for (p=currentnode; p!=NULL; p=p->prev) {
          ac[s.adj[i].a].tc[s.adj[i].r].cams[numc].cruz=realloc(ac[s.adj[i].a].tc[s.adj[i].r].cams[numc].cruz, sizeof(struct cruz)*(numv+1));
          ac[s.adj[i].a].tc[s.adj[i].r].cams[numc].cruz[numv]=p->tc.cruz;
          numv++;
        }
        ac[s.adj[i].a].tc[s.adj[i].r].cams[numc].numv=numv;
      }
      ac[s.adj[i].a].tc[s.adj[i].r].numc++;
    }
    if (ac[s.adj[i].a].tc[s.adj[i].r].c==0 && ac[s.adj[i].a].tc[s.adj[i].r].s==0 && ac[s.adj[i].a].tc[s.adj[i].r].v==0) {
      ac[s.adj[i].a].tc[s.adj[i].r].v=1;
      nextnode=malloc(sizeof(struct node));
      nextnode->tc=ac[s.adj[i].a].tc[s.adj[i].r];
      nextnode->next2=NULL;
      nextnode->next=NULL;
      nextnode->prev=currentnode;
      head=inserirQ(head, nextnode);
    }
  }
  return head;
}

void verify(tc s, arrc *ac, int m, int n) {
  int v=0;
  struct node *head=malloc(sizeof(struct node));
  struct node *head2=NULL;
  struct node *currentnode;
  struct node *i;
  head->tc=s;
  head->next2=NULL;
  head->next=NULL;
  head->prev=NULL;
  while(v!=1) {
    if (head==NULL) {
      break;
    }
    currentnode=head;
    head=verifyHelper(head, currentnode, ac);
    head2=inserirL(head2, currentnode);
    head=eliminarQ(head);
  }
  for (i=head2; i!=NULL; i=i->next2) {
    ac[i->tc.cruz.a].tc[i->tc.cruz.r].v=0;
    free(i);
  }
}

int calc(arrc *ac, cruz *cc, int cont, int c, int ret, caminho *cmsesc) {
  int i;
  int j;
  int p;
  int numc;
  int numv;
  int a;
  int r;
  int gret;
  int failed=0;
  if (ret==c) {
    if (cont>contint) {
      contint=cont;
    }
    return 0;
  }
  a=cc[ret].a;
  r=cc[ret].r;
  numc=ac[a].tc[r].numc;
  for (i=0; i<numc;i++ ) {
    if (ret==0) {
      numv=ac[a].tc[r].cams[i].numv;
      cmsesc[ret]=ac[a].tc[r].cams[i];
      calc(ac, cc, cont+1, c, ret+1, cmsesc);
      if (contint==c || contint==sreal) {
        break;
      }
    }
    else {
      gret=ret-1;
      numv=ac[a].tc[r].cams[i].numv;
      while (gret>=0) {
        for (p=0; p<numv; p++) {
          for (j=0; j<cmsesc[gret].numv; j++) {
            if (ac[a].tc[r].cams[i].cruz[p].a==cmsesc[gret].cruz[j].a && ac[a].tc[r].cams[i].cruz[p].r==cmsesc[gret].cruz[j].r) {
              break;
            }
          }
          if (j<cmsesc[gret].numv) {
            break;
          }
        }
        if (p<numv) {
          failed++;
          break;
        }
        gret--;
      }
      if (gret==-1) {
        cmsesc[ret]=ac[a].tc[r].cams[i];
        calc(ac, cc, cont+1, c, ret+1, cmsesc);
        if (contint==c || contint==sreal) {
          break;
        }
      }
    }
  }
  if (failed==numc) {
    cmsesc[ret].numv=0;
    calc(ac, cc, cont, c, ret+1, cmsesc);
  }
  return 0;
}

void max(arrc *ac, cruz *cc, cruz *ss, int m, int n, int c, int s) {
  int j;
  int cont=0;
  int ret=0;
  caminho *cmsesc=(caminho*)malloc(sizeof(struct caminho)*c);
  for (j=0; j<s; j++) {
    verify(ac[ss[j].a].tc[ss[j].r], ac, m , n);
  }
  calc(ac, cc, cont, c, ret, cmsesc);
}

int main() {
  int i;
  cruz *ss;
  cruz *cc;
  arrc *ac;
  char buff[BUFF];
  char buffaux[BUFF];
  int tot;
  int s;
  int c;
  int m;
  int n;
  int *l;
  fgets(buffaux, BUFF, stdin);
  l=cut(buffaux);
  m=l[0];
  n=l[1];
  fgets(buffaux, BUFF, stdin);
  l=cut(buffaux);
  s=l[0];
  c=l[1];
  tot=s+c;
  fgets(buff, BUFF, stdin);
  for(i=1; i<tot;i++) {
    fgets(buffaux, BUFF, stdin);
    strcat(buff, buffaux);
  }
  sreal=s;
  ccreal=c;
  ss=(cruz*)malloc(sizeof(struct cruz)*s);
  cc=(cruz*)malloc(sizeof(struct cruz)*c);
  ac=(arrc*)malloc(sizeof(struct arrc)*(m));
  contfinal=0;
  contint=0;
  organize(buff, s, c, m, n, ac, cc, ss);
  s=sreal;
  c=ccreal;
  max(ac, cc, ss, m, n, c, s);
  printf("%d\n", contint+contfinal);
  return 0;
}
